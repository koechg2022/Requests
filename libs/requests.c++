#include "../prototypes/requests"

bool debug = false;



namespace requests_library {


    //------------------------------general--------------------------------//

    void tester(char** args, const int len) {
        int index;
        for (index = 1; index < len; index++) {
            std::printf("%s%s", args[index], (index + 1 == len) ? "\n" : ", ");
        }
    }

    void parse_url(const std::string& url, std::string& protocol, std::string& hostname, std::string& port, std::string& path, std::string& hash, const std::string default_protocol) {

        if (url.empty()) {
            std::fprintf(stderr, "The url is empty");
            return;
        }
        unsigned long start = 0, current;

        // Protocol
        current = url.find("://");
        if (current less than url.length()) {
            // protocol is defined
            protocol = url.substr(start, current - start);
            current = current + 3;
            start = current;
        }

        else {
            // There is no protocol defined
            protocol = default_protocol;
            start = current = 0;
        }


        // Hostname
        while (current < url.length() and
                (not string_functions::same_char(url[current], ':')) and
                (not string_functions::same_char(url[current], '/')) and
                (not string_functions::same_char(url[current], '#'))) current++;


        hostname = url.substr(start, current - start);

        // Port
        port = (string_functions::same_string(protocol, "https")) ? "443" : (string_functions::same_string(protocol, "http")) ? DEFAULT_PORT : "8080";

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
            start = current + 1;
            while (current < url.length() and
                    (not string_functions::same_char(url[current], '#'))) current++;
            
            if (start < current) {
                path = url.substr(start, current - start);
            }
        }

        // Hash
        if (current < url.length() and string_functions::same_char(url[current], '#')) {
            start = current + 1;
            while (current < url.length()) current++;

            if (start < current) {
                hash = url.substr(start, current - start);
            }
        }

    }

    //--------------------------general-end--------------------------------//
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    //--------------------------------http---------------------------------//

    // request_structures::http::http() {
    //     networking::initialize_network();
    // }

    // request_structures::http::http(const std::string url) {
    //     std::string protocol, host, port, path, hash;
    //     parse_url(url, protocol, host, port, path, hash, "http");
    //     if (not string_functions::same_string(protocol, "http")) {
    //         throw networking::exceptions::unexpected_exception(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : line " + std::to_string(__LINE__ prev prev) + ". Unrecognized protocol \"" + protocol + "\"");
    //     }
    //     // √ the protocol is http √


    //     if (not string_functions::same_string(port, "80")) {
    //         throw networking::exceptions::unexpected_exception(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : line " + std::to_string(__LINE__ prev prev) + ". Port is \"" + port + "\" instead of port 80");
    //     }

        
    //     this->client.host_name(host);
    //     this->client.port_value(port);

    // }

    // request_structures::http::~http() {
    //     this->disconnect();
    //     networking::uninitialize_network();
    // }

    // bool request_structures::http::connect() {
    //     std::printf("First check...\n");
    //     if (this->client.host_name().empty()) {
    //         throw networking::exceptions::connect_failure(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : " + std::to_string(__LINE__ prev) + ": No hostname specified");
    //     }
    //     std::printf("Second check...\n");
    //     if (this->client.port_value().empty()) {
    //         throw networking::exceptions::connect_failure(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : " + std::to_string(__LINE__ prev) + ": No port specified");
    //     }
    //     std::printf("Third check...\n");
    //     if (not this->client.client_is_connected()) {
    //         std::printf("Not connected. Connecting...\n");
    //         this->client.connect_client();
    //     }
    //     std::printf("Done checking...\n");
    //     return this->client.client_is_connected();
    // }

    // bool request_structures::http::disconnect() {
        
    //     if (this->client.client_is_connected()) {
    //         this->client.disconnect_client();
    //     }
    //     return not this->client.client_is_connected();
    // }

    // bool request_structures::http::sethost(const std::string new_host) {
    //     if (this->client.client_is_connected()) {
    //         throw networking::exceptions::connect_failure(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : " + std::to_string(__LINE__ prev) + ". A http connection is already in place. Cannot change the host while a connection is live.");
    //     }
    //     return this->client.host_name(new_host);
    // }

    // std::string request_structures::http::gethost() const {
    //     return this->client.host_name();
    // }

    // bool request_structures::http::setport(const std::string new_port) {
    //     if (this->client.client_is_connected()) {
    //         throw networking::exceptions::connect_failure(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : " + std::to_string(__LINE__ prev) + ". A http connection is already in place. Cannot change the port while a connection is live.");
    //     }
    //     return this->client.port_value(new_port);
    // }

    // std::string request_structures::http::getport() const {
    //     return this->client.port_value();
    // }

    
    
    //-------------------------------http-end------------------------------//
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    //---------------------------------https-------------------------------//

    // bool request_structures::https::initialize() {
    //     SSL_library_init();
    //     OpenSSL_add_all_algorithms();
    //     SSL_load_error_strings();
    //     return true;
    // }
    
    // request_structures::https::https() : request_structures::http() {
    //     this->context = NULL;
    //     this->certificate = NULL;
    //     this->ssl_socket = NULL;
    //     this->initialized_tls_stuff = false;
    // }

    // request_structures::https::https(const std::string url) : request_structures::http(url) {
    //     // arguments and client are filled in.
    //     this->context = NULL;
    //     this->certificate = NULL;
    //     this->ssl_socket = NULL;
    //     this->initialized_tls_stuff = false;
    //     this->client.port_value("443");
    // }

    // request_structures::https::~https() {
    //     this->disconnect();
    // }

    // bool request_structures::https::connect() {

    //     if (not this->client.client_is_connected()) {
            
    //         (not this->initialized_tls_stuff) ? this->initialize() : true;

    //         this->context = SSL_CTX_new(TLS_client_method());
    //         if (not this->context) {
    //             throw networking::exceptions::unexpected_exception(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : line " + std::to_string(__LINE__ prev prev) + ". Failed to create the context for the secure tunnel.");
    //         }

    //         if (not request_structures::http::connect()) {
    //             throw networking::exceptions::connect_failure(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : line " + std::to_string(__LINE__ prev prev) + ". Failed to establish a TCP connection.");
    //         }

    //         // connected via TCP. Now can establish the SSL/TLS tunnel.
    //         this->ssl_socket = SSL_new(this->context);
    //         if (not this->ssl_socket) {
    //             throw networking::exceptions::unexpected_exception(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : line " + std::to_string(__LINE__ prev prev) + ". Failed to create the ssl socket that the tunnel would use for communication.");
    //         }

    //         // set the hostname for the ssl_socket
    //         if (not SSL_set_tlsext_host_name(this->ssl_socket, this->client.host_name().c_str())) {
    //             throw networking::exceptions::unexpected_exception(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : line " + std::to_string(__LINE__ prev prev) + ". Failed to associate the hostname of the remote machine to the ssl socket that is used for the tunnel communication.");
    //         }

    //         SSL_set_fd(this->ssl_socket, this->client.get_connection_socket());
    //         if (SSL_connect(this->ssl_socket) == -1) {
    //             throw networking::exceptions::connect_failure(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : line " + std::to_string(__LINE__ prev prev) + ". Failed to connect the ssl_socket through the tunnel to the remote machine.");
    //         }

    //         std::printf("Using SSL/TLS via \"%s\"\n", SSL_get_cipher(this->ssl_socket));

    //         // From here on out, it's dealing with the certificate
    //         this->certificate = SSL_get_peer_certificate(this->ssl_socket);
    //         if (not this->certificate) {
    //             throw networking::exceptions::unexpected_exception(std::string(__FILE__) + " : " + std::string(__FUNCTION__) + " : line " + std::to_string(__LINE__ prev prev) + ". Failed to get the certification verification for the remote machine.");
    //         }


    //         if (debug) {
    //             char *tmp;
    //             if ((tmp = X509_NAME_oneline(X509_get_subject_name(this->certificate), 0, 0))) {
    //                 std::printf("subject: %s\n", tmp);
    //                 OPENSSL_free(tmp);
    //             }

    //             if ((tmp = X509_NAME_oneline(X509_get_issuer_name(this->certificate), 0, 0))) {
    //                 std::printf("issuer: %s\n", tmp);
    //                 OPENSSL_free(tmp);
    //             }
    //         }

    //     }
        
    //     return this->client.client_is_connected();
    // }

    // bool request_structures::https::disconnect() {

    //     if (this->certificate) {
    //         X509_free(this->certificate);
    //     }

    //     bool extra = false;

    //     if (this->ssl_socket) {
    //         SSL_shutdown(this->ssl_socket);
    //         extra = true;
    //     }

    //     this->client.disconnect_client();
        
    //     (extra) ? SSL_free(this->ssl_socket) : (void) 0;
    //     SSL_CTX_free(this->context);
    //     return true;
    // }

    //--------------------------------https-end----------------------------//
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    //---------------------------------requests----------------------------//
    requests::requests(const std::string url, bool secure) {
        this->what_to_use = (secure) ? secure_ : not_secure;
        this->URL = url;
    }

    requests::~requests() {
        this->client.disconnect_client();
    }

    http_response requests::get() {
        
        std::string protocol, host, port, path, hash;
        
        parse_url(this->URL, protocol, host, port, path, hash, (this->what_to_use is secure_) ? "https" : "http");
        
        
        this->client.host_name(host);
        this->client.port_value(port);
        
        std::printf("this->client.host_name is \"%s\"\n", this->client.host_name().c_str());
        std::printf("this->client.port_value is \"%s\"\n", this->client.port_value().c_str());

        http_response the_answer;

        return the_answer;
    }





    //------------------------------requests-end---------------------------//

}