

#include "../prototypes/requests"



namespace requests {

    void http_requests::parse_url(const std::string& url, std::string& protocol, std::string& host_name, std::string& port, std::string& path, std::string& hash){
        
        if (url.empty()) {
            std::fprintf(stderr, "The url is empty");
            return;
        }
        unsigned long start = 0, current;
        
        
        // Protocol
        current = url.find("://");
        if (not (current is std::string::npos)) {
            // the protocol is defined
            protocol = url.substr(start, current - start);
            current = current + 3;
            start = current;
        }
        
        else {
            // There is no protocol defined
            start = current = 0;
        }


        // Hostname
        while (current < url.length() and 
                (not string_functions::same_char(url[current], ':')) and
                (not string_functions::same_char(url[current], '/')) and
                (not string_functions::same_char(url[current], '#'))) current++;

        host_name = url.substr(start, current - start);

        // Port
        port = DEFAULT_PORT;
        if (current < url.length() and string_functions::same_char(url[current], ':')) {
            start = current + 1;
            while (current < url.length() and 
                    (not string_functions::same_char(url[current], '/')) and
                    (not string_functions::same_char(url[current], '#'))) current++;
            if (start < current) {
                port = url.substr(start, current - start);
            }
        }

        while (current < url.length() and 
                    (not string_functions::same_char(url[current], '/')) and
                    (not string_functions::same_char(url[current], '#'))) current++;

        // Path
        if (current < url.length() and string_functions::same_char(url[current], '/')) {
            start = current;
            while (current < url.length() and
                    (not string_functions::same_char(url[current], '#'))) current++;
            
            if (start < current) {
                path = url.substr(start, current - start);
            }
        }


        while (current < url.length() and
                (not string_functions::same_char(url[current], '#'))) current++;

        // Hash
        if (current < url.length() and string_functions::same_char(url[current], '#')) {
            start = current + 1;
            while (current < url.length()) current++;

            if (start < current) {
                hash = url.substr(start);
            }
        }

    }

    namespace http_requests {


        http::http(const std::string url, const std::string user_agent, const std::string accept_lang, const std::string accept_, const std::string accept_encoding, const std::string connection, const std::string http_version) {
            
            std::string host_name, port, protocol;
            parse_url(url, protocol, host_name, port, this->path, this->hash);
            std::printf("Parsed the url:\n");
            this->path = (this->path.empty()) ? "/" : this->path;
            this->http_version = http_version;
            this->client = networking::network_structures::tcp_client(host_name, port);
            this->User_agent = user_agent;
            this->Accept_Language = accept_lang;
            this->Accept = accept_;
            this->Accept_Encoding = accept_encoding;
            this->Connection = connection;
        }

        http::~http() {
            this->client.disconnect_client();
        }

        http_response http::get() {

            if (this->path.empty()) {
                this->path = "/";
            }


            const std::string http_msg = "GET /" + this->path + " HTTP/" + this->http_version + "\r\n" +
                                        "Host: " + this->client.host_name() + ":" + this->client.port_value() + "\r\n" +
                                        "Connection: " + this->Connection + "\r\n" +
                                        "User-Agent: " + this->User_agent + "\r\n" +
                                        "\r\n";
                

            
            if (not this->client.connect_client()) {
                throw networking::exceptions::connect_failure("Failed to connect to server.\n");
            }


            const ssize_t sent = send(client.get_connection_socket(), http_msg.c_str(), http_msg.length(), 0);

            if (sent < 1) {
                throw networking::exceptions::unexpected_exception("Failed to send request message.\n");
            }

            std::printf("Sent http request of size %lu of size %lu\n", sent, http_msg.length());

            std::string response_status;
            http_header header;
            std::map<std::string, std::set<std::string> > answer_mapping;
            std::string answer_body;
            char response[response_size + 1];
            char *p = response, *q, *body = 0;
            char* end = response + response_size;
            enum {length, chunked, connection};
            int encoding = 0, remaining = 0;
            ssize_t bytes_received;

            const std::clock_t start_time = std::clock();

            while (client.client_is_connected()) {

                if (((double) (std::clock() - start_time)) / CLOCKS_PER_SEC > TIMEOUT) {
                    std::fprintf(stderr, "timeout after %.2f seconds.\n", TIMEOUT);
                    client.disconnect_client();
                }

                if (p is end) {
                    std::fprintf(stderr, "Out of buffer space.\n");
                    client.disconnect_client();
                    break;
                }

                if (client.server_has_message()) {

                    bytes_received = recv(client.get_connection_socket(), p, end - p, 0);

                    if (bytes_received < 1) {
                        if (encoding is connection and body) {
                            std::printf("%.*s", (int) (end - body), body);
                        }

                        std::printf("\nConnection closed by peer.\n");
                        break;
                    }

                    p = p + bytes_received;
                    *p = 0;

                    // For headers
                    if (not body and (body = std::strstr(response, "\r\n\r\n"))) {
                        *body = 0;
                        body = body + 4;

                        std::printf("Received Headers:\n%s\n", response);

                        q = std::strstr(response, "\nContent-Length: ");

                        if (q) {
                            encoding = length;
                            q = std::strchr(q, ' ');
                            q = q + 1;
                            remaining = strtol(q, 0, 10);

                        }

                        else {
                            q = std::strstr(response, "\nTransfer-Encoding: chunked");

                            if (q) {
                                encoding = chunked;
                                remaining = 0;
                            }

                            else {
                                encoding = connection;
                            }
                        }
                        std::printf("\nReceived Body:\n");
                    }

                    if (body) {

                        if (encoding is length) {
                            if (p - body >= remaining) {
                                std::printf("%.*s", remaining, body);
                                break;
                            }
                        }

                        else if (encoding is chunked) {
                            do {

                                if (remaining is 0) {
                                    if ((q = std::strstr(body, "\r\n"))) {
                                        remaining = strtol(body, 0, 16);
                                        if (not remaining) goto finish;
                                        body = q + 2;
                                    }

                                    else {
                                        break;
                                    }
                                }

                                if (remaining and p - body >= remaining) {
                                    std::printf("%.*s", remaining, body);
                                    body = body + remaining + 2;
                                    remaining = 0;
                                }

                            } while (not remaining);
                        }

                    }

                }

            }
            finish:

            std::printf("\nClosing socket...\n");
            client.disconnect_client();

            return (http_response) { header,answer_body};
        }



    }


}