

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
            protocol = "http";
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

        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        //---------------------------------https----------------------------------//

        request::request() {
            this->initialized_ssl = false;
            this->ssl = NULL;
            this->context = NULL;
        }

        request& request::url(const std::string url_link) {
            if (this->client.client_is_connected()) {
                throw networking::exceptions::unexpected_exception(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + ". Cannot add and connect a new URL while client is currently connected to another host");
            }
            std::string hostname, port, protocol;
            parse_url(url_link, protocol, hostname, port, this->path, this->hash);
            this->client = networking::network_structures::tcp_client(hostname, port);
            if (not string_functions::same_string(hostname, this->client.host_name())) {
                throw networking::exceptions::unexpected_exception(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + ". Failed to update new connection information.");
            }

            // To get here, the client has been successfully updated.
            return *this;
        }

        http_response request::get(std::map<std::string, std::vector<std::string> > headers) {
            SSL_library_init();
            OpenSSL_add_all_algorithms();
            SSL_load_error_strings();

            SSL_CTX* context = SSL_CTX_new(TLS_client_method());
            if (not context) {
                throw networking::exceptions::unexpected_exception(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : " + std::to_string(__LINE__ prev prev) + ". Failed to create SSL context.");
            }

            if (not this->client.connect_client()) {
                this->client.disconnect_client();
                throw networking::exceptions::connect_failure(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : " + std::to_string(__LINE__ prev prev) + ". Failed to connect client to remote host");
            }

            SSL* ssl = SSL_new(context);
            if (not ssl) {
                throw networking::exceptions::connect_failure(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : " + std::to_string(__LINE__ prev prev) + ". Failed to create the SSL tunnel instance to use for communication");
            }

            if (not SSL_set_tlsext_host_name(ssl, this->client.host_name().c_str())) {
                throw networking::exceptions::getaddrinfo_failure(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : " + std::to_string(__LINE__ prev) + ". Failed to set the hostname for the server.");
            }

            SSL_set_fd(ssl, this->client.get_connection_socket());
            if (SSL_connect(ssl) == -1) {
                throw networking::exceptions::connect_failure(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : " + std::to_string(__LINE__ prev) + ". Failed to connect the secure tunnel.");
            }

            X509* certificate = SSL_get_peer_certificate(ssl);

            if (not certificate) {
                this->client.disconnect_client();
                SSL_shutdown(ssl);
                SSL_free(ssl);
                SSL_CTX_free(context);
            }

            SSL_shutdown(ssl);
            this->client.disconnect_client();
            SSL_free(ssl);
            SSL_CTX_free(context);

            http_response the_answer;

            return the_answer;
        }

        //--------------------------------https-end-------------------------------//

    }


}