




#include "../prototypes/networking.h++"











namespace networking {
    
    
    namespace network_address_families {

        std::set<std::string> get_address_families() {
            std::set<std::string> the_answer;
            the_answer.insert(unspec_address_family);
            the_answer.insert(unrecognized_address_family);
            the_answer.insert(ip_version4_address_family);
            the_answer.insert(ip_version6_address_family);
            #if defined(unix_os)
                #if defined(mac_os)
                    the_answer.insert(link_layer_address_family);
                #else
                    the_answer.insert(netlink_address_family);
                    the_answer.insert(packet_address_family);
                #endif
            #else
                the_answer.insert(netbios_address_family);
                the_answer.insert(irda_address_family);
                the_answer.insert(bluetooth_address_family);
            #endif
            return the_answer;
        }

        std::string resolve_address_family_to_string(socket_family_type the_family) {
            std::string the_answer = unrecognized_address_family;
            switch(the_family) {

                case (AF_UNSPEC) : {
                    the_answer = network_address_families::unspec_address_family;
                    break;
                }

                case (AF_INET) : {
                    the_answer = network_address_families::ip_version4_address_family;
                    break;
                }

                case (AF_INET6) : {
                    the_answer = network_address_families::ip_version6_address_family;
                    break;
                }

                #if defined(unix_os)
                    
                    #if defined(mac_os)

                        case (AF_LINK) : {
                            the_answer = network_address_families::link_layer_address_family;
                            break;
                        }
                    
                    #else

                        case (AF_NETLINK) : {
                            the_answer = network_address_families::netlink_address_family;
                            break;
                        }

                        case (AF_PACKET) : {
                            the_answer = network_address_families::packet_address_family;
                            break;
                        }

                    #endif

                #else

                    case (AF_NETBIOS) : {
                        the_answer = network_address_families::netbios_address_family;
                        break;
                    }

                    case (AF_IRDA) : {
                        the_answer = network_address_families::irda_address_family;
                        break;
                    }

                    case (AF_BTH) : {
                        the_answer = network_address_families::bluetooth_address_family;
                        break;
                    }
                    
                #endif

                default : {
                    the_answer = network_address_families::unrecognized_address_family;
                    break;
                }
            }
            return the_answer;
        }

    }

    namespace exceptions {

        base_exception::base_exception(const std::string name, const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) {
            this->except_name = name;
            this->message = msg;
            this->file = file_name;
            this->line = except_line;
            this->func = function;
            if (print) {
                std::fprintf(stderr, "\"%s\" Thrown:\n%s:%s:line, %d:\n%s\n", this->except_name.c_str(), this->file.c_str(), this->func.c_str(), this->line, this->message.c_str());
            }
        }

        base_exception::~base_exception() throw() {}

        const std::string base_exception::msg() const {
            return "\"" + this->except_name + "\" Thrown:\n" + this->file + ":" + this->func + "line, " + std::to_string(this->line) + "\n" + this->message.c_str() + "\n";
        }
        

        unexpected_exception::unexpected_exception(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("unexpected_exception", msg, print, file_name, except_line, function) {}

        memory_exception::memory_exception(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("memory_exception", msg, print, file_name, except_line, function) {}

        initialize_network_failure::initialize_network_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("initialize_network_failure", msg, print, file_name, except_line, function) {}

        getaddrinfo_failure::getaddrinfo_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("getaddrinfo_failure", msg, print, file_name, except_line, function) {}

        getifaddrs_failure::getifaddrs_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("getifaddrs_failure", msg, print, file_name, except_line, function) {}

        create_socket_failure::create_socket_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("create_socket_failure", msg, print, file_name, except_line, function) {}

        bind_socket_failure::bind_socket_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("bind_socket_failure", msg, print, file_name, except_line, function) {}

        listen_socket_failure::listen_socket_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("listen_socket_failure", msg, print, file_name, except_line, function) {}

        select_failure::select_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("select_failure", msg, print, file_name, except_line, function) {}

        getnameinfo_failure::getnameinfo_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("getnameinfo_failure", msg, print, file_name, except_line, function) {}

        connect_failure::connect_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("connect_failure", msg, print, file_name, except_line, function) {}

        certificate_or_key_error::certificate_or_key_error(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("certificate_or_key_error", msg, print, file_name, except_line, function) {}
        
        secure_sockets_layer_error::secure_sockets_layer_error(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
            base_exception("secure_sockets_layer_error", msg, print, file_name, except_line, function) {}

        certificate_error::certificate_error(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
            base_exception("certificate_error", msg, print, file_name, except_line, function) {}

        accept_failure::accept_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
            base_exception("accept_failure", msg, print, file_name, except_line, function) {}

        create_context_failure::create_context_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
            base_exception("accept_failure", msg, print, file_name, except_line, function) {}

    }

    bool initialize_network() {
        #if defined(crap_os)
            if (not is_init) {
                WSADATA d;
                // std::printf("Initializing network...\n");
                if (WSAStartup(MAKEWORD(2, 2), &d)) {
                    return false;
                }
                is_init = true;
                // std::printf("Network is initialized...\n");
            }
        #endif
        return is_init;
    }

    bool uninitialize_network() {
        #if defined(crap_os)
            if (is_init) {
                // std::printf("Uninitializing network...\n");
                if (WSACleanup()) {
                    return is_init;
                }
                is_init = false;
                // std::printf("Network is uninitialized...\n");
            }
        #endif
        return is_init is false;
    }

    std::vector<std::string> resolve_hostname(const std::string hostname, const std::string port, const bool name) {
        
        bool was_init = is_init;

        if (not was_init) {
            if (not initialize_network()) {
                (clean_on_except) ? uninitialize_network() : true;
                throw exceptions::initialize_network_failure("Failed to initialize. ", true, __FILE__, __LINE__ - 2, "resolve_host_name");
            }
        }
        // To get here, the network was successfully initialized.
        std::vector<std::string> the_answer;
        struct addrinfo hints, *current, *all_addresses;
        char buffer[buffer_size];
        std::memset(&hints, 0, sizeof(hints));
        std::memset(&buffer, 0, buffer_size);
        hints.ai_flags = AI_ALL;

        if (getaddrinfo(hostname.c_str(), port.c_str(), &hints, &all_addresses)) {
            (clean_on_except and not was_init) ? uninitialize_network() : true;
            throw exceptions::getaddrinfo_failure("Failed to get address information for host " + hostname, true, __FILE__, __LINE__ - 2, "resolve_hostname");
        }

        for (current = all_addresses; current NOT null; current = current->ai_next) {

            if (not getnameinfo(current->ai_addr, current->ai_addrlen, buffer, buffer_size, 0, 0, NI_NUMERICHOST | AI_ALL)) {
                the_answer.push_back(std::string(buffer));
            }

            if (name) {
                if (not getnameinfo(current->ai_addr, current->ai_addrlen, buffer, buffer_size, 0, 0, NI_NAMEREQD | AI_ALL)) {
                    the_answer.push_back(std::string(buffer));
                }
            }
        }

        freeaddrinfo(all_addresses);

        if (not was_init) {
            if (not uninitialize_network()) {
                throw exceptions::initialize_network_failure("Failed to uninitialize network", true, __FILE__, __LINE__ - 1, "resolve_hostname");
            }
        }
        return the_answer;
    }

    std::map<std::string, std::map<std::string, std::vector<std::string> > > this_machine_adapters(const bool names) {
        bool was_init = is_init;
        
        if (not was_init) {

            if (not initialize_network()) {
                (clean_on_except) ? uninitialize_network() : true;
                throw exceptions::initialize_network_failure("Failed to initialize. ", true, __FILE__, __LINE__ - 2, __FUNCTION__);
            }
        }
        
        std::map<std::string, std::map<std::string, std::vector<std::string> > > the_answer;

        ifaddrs_adapter_type all_adapters;
        #if defined(crap_os)

            all_adapters = NULL;
            DWORD memory_size = 20000;
            int this_line;
            
            while (not all_adapters) {
                
                all_adapters = (ifaddrs_adapter_type) malloc(memory_size);
                this_line = __LINE__ - 1;

                if (not all_adapters) {
                    (clean_on_except) ? uninitialize_network() : true;
                    throw exceptions::memory_exception("Failed to aquire " + std::to_string(memory_size) + " bytes of memory", true, __FILE__, this_line, __FUNCTION__);
                }

                int resp = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0, all_adapters, &memory_size);
                this_line = __LINE__ - 1;

                if (resp is ERROR_BUFFER_OVERFLOW) {
                    ifaddrs_free_adapters(all_adapters);
                }

                else if (resp is ERROR_SUCCESS) {
                    break;
                }

                else {
                    (clean_on_except) ? uninitialize_network() : true;
                    ifaddrs_free_adapters(all_adapters);
                    throw exceptions::unexpected_exception("An unexpected exception occured while trying to retrieve this machine's network adapter information", true, __FILE__, this_line, __FUNCTION__);
                }

            }
            std::printf("Done with the creation of the pointer for all_adapters.\n");

        #else

            if (getifaddrs(&all_adapters)) {
                (clean_on_except) ? uninitialize_network() : true;
                throw exceptions::getifaddrs_failure("Failed to retrieve adater information", true, __FILE__, __LINE__ - 2, __FUNCTION__);
            }

        #endif

        ifaddrs_adapter_type this_adapter;
        ifaddrs_address_type this_address;
        char buffer[buffer_size];
        std::string adapter_name, address_family, address_name;
        std::memset(buffer, 0, buffer_size);
        for (this_adapter = all_adapters; this_adapter; this_adapter = ifaddrs_get_next_adapter(this_adapter)) {
            // std::printf("Retrieving adapter_name\n");
            adapter_name = ifaddrs_get_adapter_name(this_adapter);
            // std::printf("Retrieved adapter name ('%s')\n", adapter_name.c_str());

            for (this_address = ifaddrs_pull_adapter_address(this_adapter); this_address; this_address = ifaddrs_get_next_address(this_address)) {
                // std::printf("\tRetrieving address family\n");
                address_family = network_address_families::resolve_address_family_to_string(ifaddrs_get_address_family(this_address));
                // std::printf("\tRetrieved address_family ('%s')\n\n", address_family.c_str());
                // now to pull the address
                string_functions::same_char(*buffer, 0, false) ? (void*) 0 : std::memset(buffer, 0, buffer_size);

                switch (getnameinfo(ifaddrs_get_address_sockaddr(this_address), ifaddrs_get_address_sockaddrlen(this_address), buffer, buffer_size, 0, 0, NI_NUMERICHOST)) {

                    case 0 : {

                        address_name = std::string(buffer);
                        if (address_name.empty()) {
                            continue;
                        }
                        else if (not the_answer.count(adapter_name)) {

                            std::map<std::string, std::vector<std::string> > new_map;
                            std::vector<std::string> new_list;
                            new_list.push_back(address_name);
                            new_map.insert(std::make_pair(address_family, new_list));

                            the_answer.insert(std::make_pair(adapter_name, new_map));
                        }

                        else if (not the_answer[adapter_name].count(address_family)) {

                            std::vector<std::string> new_list;
                            new_list.push_back(address_name);

                            the_answer[adapter_name].insert(std::make_pair(address_family, new_list));
                        }

                        else {
                            the_answer[adapter_name][address_family].push_back(address_name);
                        }
                    }


                }

                if (names) {

                    string_functions::same_char(*buffer, 0, false) ? (void*) 0 : std::memset(buffer, 0, buffer_size);

                    switch (getnameinfo(ifaddrs_get_address_sockaddr(this_address), ifaddrs_get_address_sockaddrlen(this_address), buffer, buffer_size, 0, 0, NI_NAMEREQD)) {
    
                        case 0 : {
    
                            address_name = std::string(buffer);
                            if (address_name.empty()) {
                                continue;
                            }
                            else if (not the_answer.count(adapter_name)) {
    
                                std::map<std::string, std::vector<std::string> > new_map;
                                std::vector<std::string> new_list;
                                new_list.push_back(adapter_name);
                                new_map.insert(std::make_pair(address_family, new_list));
    
                                the_answer.insert(std::make_pair(adapter_name, new_map));
                            }
    
                            else if (not the_answer[adapter_name].count(address_family)) {
    
                                std::vector<std::string> new_list;
                                new_list.push_back(address_name);
    
                                the_answer[adapter_name].insert(std::make_pair(address_family, new_list));
                            }
                            
                            else {
                                the_answer[adapter_name][address_family].push_back(address_name);
                            }
                        }
                    }

                }


            }

        }
        
        ifaddrs_free_adapters(all_adapters);
        return the_answer;

    }


    

    bool socket_is_connected(const socket_type the_socket) {
        // int error = 0;
        // socklen_t len = sizeof(error);
        int retval = 0;

        #ifdef _WIN32
            u_long mode = 1;  // 1 to enable non-blocking socket
            ioctlsocket(the_socket, FIONBIO, &mode);
        #else
            int flags = fcntl(the_socket, F_GETFL, 0);
            fcntl(the_socket, F_SETFL, flags | O_NONBLOCK);
        #endif

        char buffer[1];
        retval = recv(the_socket, buffer, 1, MSG_PEEK);

        if (retval == 0) {
            return false;  // Connection closed
        } else if (retval < 0) {
            #if defined(crap_os)
                int error = 0;
                error = WSAGetLastError();
                if (error != WSAEWOULDBLOCK) {
                    return false;  // Error occurred
                }
            #else
                if (errno != EWOULDBLOCK && errno != EAGAIN) {
                    return false;  // Error occurred
                }
            #endif
        }

        return true;  // Connection is still alive
    }

    bool is_ipstring(const std::string the_ip, const bool ip4) {
        if (ip4) {
            std::istringstream ss(the_ip);
            std::string octet;
            int count = 0;

            while (std::getline(ss, octet, '.')) {
                if (++count > 4 || octet.empty() || octet.size() > 3) return false;
                for (char c : octet) {
                    if (!std::isdigit(c)) return false;
                }
                int num = std::stoi(octet);
                if (num < 0 || num > 255 || (octet.size() > 1 && octet[0] == '0')) return false;
            }

            return count == 4 && ss.eof();
        }

        const std::regex ipv6_regex(ip6_regex_pattern);
        
        return std::regex_match(the_ip, ipv6_regex);
    }

    bool network_structures::connected_host::client::operator<(const client& other) const {
        return this->connected_socket < other.connected_socket;
    }

    network_structures::connected_host::client::operator bool() const {
        return valid_socket(this->connected_socket);
    }

    bool network_structures::connected_host::server::operator<(const server& other) const {
        return this->hostname < other.hostname and 
            this->portvalue < other.portvalue;
    }

    network_structures::connected_host::server::operator bool() const {
        return valid_socket(this->connect_socket);
    }

    ////////////////////////host////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////



    network_structures::host::host() {
        this->connect_socket = invalid_socket;
        this->hostname = "";
        this->portvalue = DEFAULT_PORT;
        this->timeout = {0, 100000};
        this->tcp = true;
        this->was_init = is_init;
        initialize_network();
        this->del_on_except = true;
        this->secure_ = this->initialized_secure = this->certificates = false;
        this->context = null;
        this->secure_socket = null;
        this->certificates = false;
        this->certificate = null;
        this->connect_address = 0;
    }


    network_structures::host::host(const std::string host_name, const std::string port, bool use_tcp, long wait_sec, int wait_msec, bool will_del, bool secure) {
        this->connect_socket = invalid_socket;
        this->hostname = host_name;
        this->portvalue = port;
        this->timeout = {wait_sec, wait_msec};
        this->tcp = use_tcp;
        this->was_init = is_init;
        initialize_network();
        this->del_on_except = will_del;
        this->secure_ = secure;
        this->initialized_secure = this->certificates = false;
        this->context = null;
        this->secure_socket = null;
        this->certificates = false;
        this->certificate = null;
        this->connect_address = 0;
    }


    network_structures::host::~host() {
        if (this->connect_address) {
            freeaddrinfo(this->connect_address);
            this->connect_address = null;
        }

        if (this->secure_socket) {
            SSL_shutdown(this->secure_socket);
        }

        if (valid_socket(this->connect_socket)) {
            close_socket(this->connect_socket);
        }

        if (this->secure_socket) {
            SSL_free(secure_socket);
            SSL_CTX_free(this->context);
        }

        if (not this->certificate) {
            X509_free(this->certificate);
            this->certificate = null;
        }

        if (not was_init) {
            uninitialize_network();
        }
    }

    network_structures::host::host(const network_structures::host& other) {
        if (this != &other) {
            this->connect_socket = other.connect_socket;
            this->hostname = other.hostname;
            this->portvalue = other.portvalue;
            this->connect_address = other.connect_address;
            this->timeout = other.timeout;
            this->tcp = other.tcp;
            this->was_init = other.was_init;
            this->del_on_except = other.del_on_except;

            // secure stuff
            this->secure_ = other.secure_;
            this->initialized_secure = other.initialized_secure;
            this->context = other.context;
            this->secure_socket = other.secure_socket;
            this->certificates = other.certificates;
            this->certificate = other.certificate;
        }
    }

    network_structures::host& network_structures::host::operator=(network_structures::host& other) {
        if (this != &other) {
            this->connect_socket = other.connect_socket;
            this->hostname = other.hostname;
            this->portvalue = other.portvalue;
            this->connect_address = other.connect_address;
            this->timeout = other.timeout;
            this->tcp = other.tcp;
            this->was_init = other.was_init;
            this->del_on_except = other.del_on_except;
            this->secure_ = other.secure_;

            this->initialized_secure = other.initialized_secure;
            this->context = other.context;
            this->secure_socket = other.secure_socket;
            this->certificates = other.certificates;
            this->certificate = other.certificate;
        }
        return *this;
    }

    network_structures::host& network_structures::host::operator=(const network_structures::host& other) {
        if (this != &other) {
            this->connect_socket = other.connect_socket;
            this->hostname = other.hostname;
            this->portvalue = other.portvalue;
            this->connect_address = other.connect_address;
            this->timeout = other.timeout;
            this->tcp = other.tcp;
            this->was_init = other.was_init;
            this->del_on_except = other.del_on_except;
            this->secure_ = other.secure_;

            this->initialized_secure = other.initialized_secure;
            this->context = other.context;
            this->secure_socket = other.secure_socket;
            this->certificates = other.certificates;
            this->certificate = other.certificate;
        }
        return *this;
    }


    bool network_structures::host::host_name(const std::string new_host) {
        if (valid_socket(this->connect_socket) and connect_address and ((this->secure_) ? (this->context and this->secure_socket) : true)) {
            return false;
        }
        this->hostname = new_host;
        return string_functions::same_string(new_host, this->hostname);
    }


    std::string network_structures::host::host_name() const {
        return this->hostname;
    }


    bool network_structures::host::port_value(const std::string new_port) {
        if (valid_socket(this->connect_socket) and connect_address and ((this->secure_) ? (this->context and this->secure_socket) : true)) {
            return false;
        }
        this->portvalue = new_port;
        return string_functions::same_string(this->portvalue, new_port);
    }

    
    std::string network_structures::host::port_value() const {
        return this->portvalue;
    }


    bool network_structures::host::create_address() {
        
        if (not this->connect_address) {
            struct addrinfo hints;
            
            if (this->hostname.empty()) {
                
                std::map<std::string, std::map<std::string, std::vector<std::string> > > adapters = this_machine_adapters();

                for (auto adapter = adapters.begin(); adapter != adapters.end(); adapter++) {
                    
                    if (not string_functions::same_string(adapter->first, rel_adapter)) {
                        continue;
                    }
                    
                    for (auto family = adapter->second.begin(); family != adapter->second.end(); family++) {
                        if (not string_functions::same_string(network_address_families::ip_version4_address_family, family->first) and not string_functions::same_string(network_address_families::ip_version6_address_family, family->first)) {
                            continue;
                        }

                        for (auto address = family->second.begin(); address != family->second.end(); address++) {
                            if (address->empty()) {
                                continue;
                            }
                            this->hostname = *address;
                            break;
                        }

                        if (not this->hostname.empty()) {
                            break;
                        }
                    }

                    if (not this->hostname.empty()) {
                        break;
                    }
                }
            }

            if (this->portvalue.empty()) {
                this->portvalue = DEFAULT_PORT;
            }

            std::memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = (this->tcp) ? SOCK_STREAM : SOCK_DGRAM;
            hints.ai_flags = AI_PASSIVE;
            // std::printf("The host is '%s'\n", this->hostname.c_str());
            if (getaddrinfo(this->hostname.c_str(), this->portvalue.c_str(), &hints, &this->connect_address)) {
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::getaddrinfo_failure("Failed to retrieve address information for local machine", true, __FILE__, __LINE__ - 2, __FUNCTION__);
            }
        }
        return this->connect_address;
    }


    bool network_structures::host::create_socket() {

        this->create_address();
        if (not valid_socket(this->connect_socket)) {
            this->connect_socket = socket(this->connect_address->ai_family, this->connect_address->ai_socktype, this->connect_address->ai_protocol);
            if (not valid_socket(this->connect_socket)) {
                (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::create_socket_failure("Failed to create connection socket for host " + this->hostname + ". Error number " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 4, __FUNCTION__);
            }
            // std::printf("Created the connection socket...\n");
            #if defined(unix_os)
                int reuse = 1;
            #else
                char reuse = 1;
            #endif
            // std::printf("setting socket options...\n");
            if (setsockopt(this->connect_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))) {
                std::fprintf(stderr, "Failed to set reusable socket.\n");
            }
        }
        return this->connect_socket;
    }


    bool network_structures::host::initialize_secure() {
        if (this->secure_ and not this->initialized_secure) {
            SSL_library_init();
            OpenSSL_add_all_algorithms();
            SSL_load_error_strings();
            this->initialized_secure = true;
        }
        return (this->secure_) ? this->initialized_secure : not this->initialized_secure;
    }


    bool network_structures::host::create_context() {
        
        if (this->secure_ and not this->initialize_secure()) {
            return false;
        }

        if (this->secure_ and not this->context) {
            this->context = SSL_CTX_new(TLS_client_method());
        }
        return (this->secure_) ? valid_context(this->context) : not valid_context(this->context);
    }


    bool network_structures::host::create_secure_socket() {
        if (this->secure_ and not this->initialize_secure()) {
            return false;
        }

        if (this->secure_ and not this->create_context()) {
            return false;
        }

        if (this->secure_ and not this->secure_socket) {
            this->secure_socket = SSL_new(this->context);
        }
        return this->secure_socket;
    }


    void network_structures::host::update_timeout(long sec, int m_sec) {
        this->timeout = {sec, m_sec};
    }


    bool network_structures::host::will_delete_on_except() const {
        return this->del_on_except;
    }


    void network_structures::host::will_delete_on_except(const bool new_flag) {
        this->del_on_except = new_flag;
    }


    socket_type network_structures::host::get_connection_socket() const {
        return this->connect_socket;
    }


    secure_socket_type network_structures::host::get_secure_connection_socket() const {
        return this->secure_socket;
    }

    bool network_structures::host::secure_host() {
        return this->secure_;
    }

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    //////////////////////host end//////////////////////


    /**************************************************/

    
    /////////////////////tcp_server/////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////



    
    bool network_structures::tcp_server::create_certificates() {
        if (this->secure_ and not this->certificates) {
            this->initialize_secure();
            this->create_context();
            if (not SSL_CTX_use_certificate_file(this->context, this->cert_pem_file.c_str(), SSL_FILETYPE_PEM) or not SSL_CTX_use_PrivateKey_file(this->context, this->key_pem_file.c_str(), SSL_FILETYPE_PEM)) {
                (not this->was_init) ? uninitialize_network() : true;
                char err_buf[256]; unsigned long err = ERR_get_error(); ERR_error_string_n(err, err_buf, sizeof(err_buf));
                throw exceptions::certificate_or_key_error("Failed to create the certificate or private key for this server. Error '" + std::string(err_buf) + "'", true, __FILE__, __LINE__ - 3, __FUNCTION__);
            }
            this->certificates = true;
        }
        return this->certificates;
    }

    bool network_structures::tcp_server::disconnect_client(network_structures::connected_host::client& client) {
        
        if (client.secure_socket != invalid_secure_socket) {
            SSL_shutdown(client.secure_socket);
        }

        if (valid_socket(client.connected_socket)) {

            close_socket(client.connected_socket);
            client.connected_socket = invalid_socket;
        }

        if (client.secure_socket != invalid_secure_socket) {
            SSL_free(client.secure_socket);
            client.secure_socket = invalid_secure_socket;
        }

        if (not client.hostname.empty()) {
            client.hostname = "";
        }

        if (not client.portvalue.empty()) {
            client.portvalue = "";
        }

        #if defined(mac_os)
            if (client.address_info.ss_family and client.address_info.ss_len) {
                client.address_info.ss_family = 0;
                client.address_info.ss_len = 0;
            }
        #else
            if (client.address_info.ss_family) {
                client.address_info.ss_family = 0;
            }
        #endif

        if (this->clients.contains(client.connected_socket)) {
            this->clients.erase(client.connected_socket);
            this->max_socket = invalid_socket;
            this->max_secure_socket = invalid_secure_socket;
            for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
                this->max_socket = (client->first > this->max_socket) ? client->first : this->max_socket;
                this->max_secure_socket = (client->second.secure_socket > this->max_secure_socket) ? client->second.secure_socket : this->max_secure_socket;
            }
        }
        
        
        return not valid_socket(client.connected_socket) and 
                not valid_secure_socket(client.secure_socket) and
                    not this->clients.contains(client.connected_socket) and
                    #if defined(mac_os)
                        client.address_info.ss_len == 0 and 
                    #endif
                            client.address_info.ss_family == 0 and 
                                client.hostname.empty() and 
                                    client.portvalue.empty();
    }

    bool network_structures::tcp_server::bind_socket() {
        if (not this->bound) {
            if (this->secure_) {
                this->initialize_secure();
                this->create_certificates();
            }
            this->create_address();
            this->create_socket();
            
            if (bind(this->connect_socket, this->connect_address->ai_addr, this->connect_address->ai_addrlen)) {
                (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                (this->was_init) ? uninitialize_network() : true;
                throw exceptions::bind_socket_failure("Failed to bind the connecting socket", true, __FILE__, __LINE__- 3, __FUNCTION__);
            }
            this->bound = true;
        }
        return this->bound;
    }

    bool network_structures::tcp_server::start_listening() {
        if (not this->listening) {
            
            if (this->secure_) {
                this->initialize_secure();
                this->create_certificates();
            }

            this->create_address();
            this->create_socket();
            this->bind_socket();

            if (listen(this->connect_socket, this->listen_lim)) {
                (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                (this->was_init) ? uninitialize_network() : true;
                throw exceptions::listen_socket_failure("Failed to start listening on the connection socket", true, __FILE__, __LINE__ - 3, __FUNCTION__);
            }
            this->listening = true;
        }
        return this->listening;
    }

    network_structures::tcp_server::tcp_server(const std::string host, const std::string port, int listen_limit, long seconds_wait, int micro_sec_wait, bool will_del, bool secure) :
        network_structures::host::host(host, port, true, seconds_wait, micro_sec_wait, will_del, secure) {
            this->listen_lim = listen_limit;
            this->listening = this->bound = false;
            this->max_socket = invalid_socket;
            this->max_secure_socket = null;
        }

    network_structures::tcp_server::~tcp_server() {
        this->close_server();
    }

    network_structures::tcp_server::tcp_server(const network_structures::tcp_server& other) {
        if (this != &other) {

            // For the host stuff:
            this->connect_socket = other.connect_socket;
            this->hostname = other.hostname;
            this->portvalue = other.portvalue;
            this->connect_address = other.connect_address;
            this->timeout = other.timeout;
            this->tcp = other.tcp;
            this->was_init = other.was_init;
            this->del_on_except = other.del_on_except;

            // secure stuff
            this->secure_ = other.secure_;
            this->initialized_secure = other.initialized_secure;
            this->context = other.context;
            this->secure_socket = other.secure_socket;
            this->certificates = other.certificates;


            // For the tcp_server
            this->listen_lim = other.listen_lim;
            this->listening = other.listening;
            this->bound = other.bound;
            this->max_socket = other.max_socket;
            this->max_secure_socket = other.max_secure_socket;
            this->clients = other.clients;
        }
    }

    network_structures::tcp_server& network_structures::tcp_server::operator=(network_structures::tcp_server& other) {
        if (this != &other) {
            // For the host stuff:
            this->connect_socket = other.connect_socket;
            this->hostname = other.hostname;
            this->portvalue = other.portvalue;
            this->connect_address = other.connect_address;
            this->timeout = other.timeout;
            this->tcp = other.tcp;
            this->was_init = other.was_init;
            this->del_on_except = other.del_on_except;

            // secure stuff
            this->secure_ = other.secure_;
            this->initialized_secure = other.initialized_secure;
            this->context = other.context;
            this->secure_socket = other.secure_socket;
            this->certificates = other.certificates;


            // For the tcp_server
            this->listen_lim = other.listen_lim;
            this->listening = other.listening;
            this->bound = other.bound;
            this->max_socket = other.max_socket;
            this->max_secure_socket = other.max_secure_socket;
            this->clients = other.clients;
        }
        return *this;
    }

    network_structures::tcp_server& network_structures::tcp_server::operator=(const network_structures::tcp_server& other) {
        if (this != &other) {
            // For the host stuff:
            this->connect_socket = other.connect_socket;
            this->hostname = other.hostname;
            this->portvalue = other.portvalue;
            this->connect_address = other.connect_address;
            this->timeout = other.timeout;
            this->tcp = other.tcp;
            this->was_init = other.was_init;
            this->del_on_except = other.del_on_except;

            // secure stuff
            this->secure_ = other.secure_;
            this->initialized_secure = other.initialized_secure;
            this->context = other.context;
            this->secure_socket = other.secure_socket;
            this->certificates = other.certificates;


            // For the tcp_server
            this->listen_lim = other.listen_lim;
            this->listening = other.listening;
            this->bound = other.bound;
            this->max_socket = other.max_socket;
            this->max_secure_socket = other.max_secure_socket;
            this->clients = other.clients;
        }
        return *this;
    }

    network_structures::tcp_server::operator bool() const {
        return this->running();
    }

    bool network_structures::tcp_server::new_connection(bool accept_new) {
        fd_set ready;
        FD_ZERO(&ready);
        FD_SET(this->connect_socket, &ready);

        if (select(this->connect_socket + 1, &ready, 0, 0, (this->timeout.tv_usec is -1) ? 0 : &this->timeout) < 0) {
            (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::select_failure("Failed to select for the actively listening socket for new connections. Error number " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }

        if (accept_new) {
            const unsigned long old = this->clients.size();
            if (FD_ISSET(this->connect_socket, &ready)) {
                network_structures::connected_host::client new_client;
                new_client.connected_socket = accept(this->connect_socket, (struct sockaddr*) &new_client.address_info, &new_client.address_size);

                if (not valid_socket(new_client.connected_socket)) {
                    (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                    (not this->was_init) ? uninitialize_network() : true;
                    throw exceptions::create_socket_failure("Failed to create a connection to the new client. Error " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
                }

                char address[buffer_size], service[buffer_size];
                std::memset(address, 0, buffer_size);
                std::memset(service, 0, buffer_size);

                if (getnameinfo((struct sockaddr*) &new_client.address_info, new_client.address_size, address, buffer_size, service, buffer_size, NI_NUMERICHOST)) {
                    new_client.hostname = "Unspecified hostname";
                    new_client.portvalue = "Unspecified port";
                }
                else {
                    new_client.hostname = std::string(address);
                    new_client.portvalue = std::string(service);
                }

                this->max_socket = (new_client.connected_socket > this->max_socket) ? new_client.connected_socket : this->max_socket;

                if (this->secure_) {
                    new_client.secure_socket = SSL_new(this->context);
                    if (not valid_secure_socket(new_client.secure_socket)) {
                        (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                        (not this->was_init) ? uninitialize_network() : true;
                        throw exceptions::secure_sockets_layer_error("Failed to create a secure connection with the new client", true, __FILE__, __LINE__ - 4, __FUNCTION__);
                    }

                    SSL_set_fd(new_client.secure_socket, new_client.connected_socket);
                    if (SSL_accept(new_client.secure_socket) <= 0) {
                        this->disconnect_client(new_client);
                        (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                        (not this->was_init) ? uninitialize_network() : true;
                        char err_buf[256]; unsigned long err = ERR_get_error(); ERR_error_string_n(err, err_buf, sizeof(err_buf));
                        throw exceptions::accept_failure("Failed to accept a secure connection to client. Error : " + std::string(err_buf), true, __FILE__, __LINE__ - 5, __FUNCTION__);
                    }
                    this->max_secure_socket = (new_client.secure_socket > this->max_secure_socket) ? new_client.secure_socket : this->max_secure_socket;
                }
                this->clients.insert({new_client.connected_socket, new_client});
            }
            return this->clients.size() > old;
        }
        return FD_ISSET(this->connect_socket, &ready);
    }

    network_structures::connected_host::client network_structures::tcp_server::new_client() {
        
        if (not *this) {
            return {"", "", invalid_socket, invalid_secure_socket, 
            #if defined(unix_os)
                {0, 0, {0}}
            #else
                {0, {0, 0}}
            #endif
            , sizeof(struct sockaddr_storage)};
        }
        fd_set ready;
        FD_ZERO(&ready);
        FD_SET(this->connect_socket, &ready);

        if (select(this->connect_socket + 1, &ready, 0, 0, (this->timeout.tv_usec is -1) ? 0 : &this->timeout) < 0) {
            (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::select_failure("Failed to select for the actively listening socket for new connections. Error number " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }

        network_structures::connected_host::client the_answer = {"", "", invalid_socket, invalid_secure_socket, 
            #if defined(unix_os)
                {0, 0, {0}}
            #else
                {0, {0, 0}}
            #endif
            , sizeof(struct sockaddr_storage)};
        // the_answer.connected_socket = invalid_socket;
        // the_answer.secure_socket = invalid_secure_socket;
        // the_answer.address_info.ss_family = 0;
        // #if defined(mac_os)
        //     the_answer.address_info.ss_len = 0;
        // #endif
        // the_answer.hostname = the_answer.portvalue = "";
        
        if (FD_ISSET(this->connect_socket, &ready)) {
            network_structures::connected_host::client new_client;
            new_client.connected_socket = accept(this->connect_socket, (struct sockaddr*) &new_client.address_info, &new_client.address_size);

            if (not valid_socket(new_client.connected_socket)) {
                (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::create_socket_failure("Failed to create a connection to the new client. Error " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
            }

            char address[buffer_size], service[buffer_size];
            std::memset(address, 0, buffer_size);
            std::memset(service, 0, buffer_size);

            if (getnameinfo((struct sockaddr*) &new_client.address_info, new_client.address_size, address, buffer_size, service, buffer_size, NI_NUMERICHOST)) {
                new_client.hostname = "Unspecified hostname";
                new_client.portvalue = "Unspecified port";
            }
            else {
                new_client.hostname = std::string(address);
                new_client.portvalue = std::string(service);
            }

            this->max_socket = (new_client.connected_socket > this->max_socket) ? new_client.connected_socket : this->max_socket;

            if (this->secure_) {
                new_client.secure_socket = SSL_new(this->context);
                if (not valid_secure_socket(new_client.secure_socket)) {
                    (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                    (not this->was_init) ? uninitialize_network() : true;
                    throw exceptions::secure_sockets_layer_error("Failed to create a secure connection with the new client", true, __FILE__, __LINE__ - 4, __FUNCTION__);
                }

                SSL_set_fd(new_client.secure_socket, new_client.connected_socket);
                if (SSL_accept(new_client.secure_socket) <= 0) {
                    this->disconnect_client(new_client);
                    (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                    (not this->was_init) ? uninitialize_network() : true;
                    char err_buf[256]; unsigned long err = ERR_get_error(); ERR_error_string_n(err, err_buf, sizeof(err_buf));
                    throw exceptions::accept_failure("Failed to accept a secure connection to client. Error : " + std::string(err_buf), true, __FILE__, __LINE__ - 5, __FUNCTION__);
                }
                this->max_secure_socket = (new_client.secure_socket > this->max_secure_socket) ? new_client.secure_socket : this->max_secure_socket;
            }
            this->clients.insert({new_client.connected_socket, new_client});
            return new_client;
        }
        
        return the_answer;
    }

    bool network_structures::tcp_server::close_connection(const socket_type to_close) {
        bool the_answer = false;
        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            if (to_close == client->first) {
                // This is the client to be removed
                // std::printf("Closing secure socket...\n");
                (this->secure_) ? SSL_shutdown(client->second.secure_socket) : 0;
                // std::printf("Closing connection socket...\n");
                (socket_is_connected(client->first)) ? close_socket(client->first) : 0;
                // std::printf("Freeing secure socket...\n");
                (this->secure_) ? SSL_free(client->second.secure_socket) : (void) 0;
                // std::printf("Removing client from database...\n");
                this->clients.erase(client->first);
                the_answer = true;
                goto other;
            }
        }

        other:
        this->max_socket = invalid_socket;
        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            this->max_socket = (client->first > this->max_socket) ? client->first : this->max_socket;
            this->max_secure_socket = (client->second.secure_socket > this->max_secure_socket) ? client->second.secure_socket : this->max_secure_socket;
        }
        return the_answer;
    }

    bool network_structures::tcp_server::close_connection(const std::string hostname, const std::string portvalue) {
        bool the_answer = false;
        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            if (string_functions::same_string(client->second.hostname, hostname) and string_functions::same_string(client->second.portvalue, portvalue)) {
                // This is the client to be removed
                // std::printf("Closing secure socket...\n");
                (this->secure_) ? SSL_shutdown(client->second.secure_socket) : 0;
                // std::printf("Closing connection socket...\n");
                (socket_is_connected(client->first)) ? close_socket(client->first) : 0;
                // std::printf("Freeing secure socket...\n");
                (this->secure_) ? SSL_free(client->second.secure_socket) : (void) 0;
                // std::printf("Removing client from database...\n");
                this->clients.erase(client->first);
                the_answer = true;
                goto other;
            }
        }

        other:
        this->max_socket = invalid_socket;
        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            this->max_socket = (client->first > this->max_socket) ? client->first : this->max_socket;
            this->max_secure_socket = (client->second.secure_socket > this->max_secure_socket) ? client->second.secure_socket : this->max_secure_socket;
        }
        return the_answer;
    }

    bool network_structures::tcp_server::close_server() {
        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            this->disconnect_client(client->second);
        }

        this->listen_lim = 0;
        this->listening = this->bound = false;
        this->max_secure_socket = null;
        this->max_socket = invalid_socket;
        if (this->connect_address) {
            freeaddrinfo(this->connect_address);
            this->connect_address = null;
        }

        if (this->secure_socket) {
            SSL_shutdown(this->secure_socket);
            this->secure_socket = invalid_secure_socket;
        }

        if (valid_socket(this->connect_socket)) {
            close_socket(this->connect_socket);
            this->connect_socket = invalid_socket;
        }

        if (this->secure_socket) {
            SSL_free(secure_socket);
            SSL_CTX_free(this->context);
            this->context = invalid_context;
        }

        if (not this->certificate) {
            X509_free(this->certificate);
            this->certificate = null;
        }

        if (not this->was_init) {
            uninitialize_network();
            this->was_init = true;
        }
        return this->clients.empty() and 
                    not this->listen_lim and 
                        not valid_secure_socket(this->max_secure_socket) and
                            not valid_socket(this->max_socket);
    }

    bool network_structures::tcp_server::update_limit(const int listening_limit) {
        if (not this->listening) {
            this->listen_lim = listening_limit;
        }
        return this->listen_lim == listening_limit;
    }

    int network_structures::tcp_server::listening_limit() const {
        return this->listen_lim;
    }

    bool network_structures::tcp_server::start() {

        if (not this->running()) {

            if (this->secure_ and not this->initialize_secure()) {
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::initialize_network_failure("Failed to initialize secure network functions and algorithms", true, __FILE__, __LINE__ - 2, __FUNCTION__);
            }
            
            if (this->secure_ and not this->create_context()) {
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::create_context_failure("Failed to create the secure network context", true, __FILE__, __LINE__ - 2, __FUNCTION__);
            }

            if (this->secure_ and not this->create_certificates()) {
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::certificate_or_key_error("Failed to create the certificates and/or errors for the secure connection", true, __FILE__, __LINE__ - 2, __FUNCTION__);
            }

            if (not this->create_address()) {
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::getaddrinfo_failure("Failed to get the address information for the connection.", true, __FILE__, __LINE__ - 2, __FUNCTION__);
            }

            if (not this->create_socket()) {
                (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                (this->was_init) ? uninitialize_network() : true;
                throw exceptions::create_socket_failure("Failed to create the connection socket for incomming clients to be received on.", true, __FILE__, __LINE__ - 3, __FUNCTION__);
            }

            if (not this->bind_socket()) {
                (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                (this->was_init) ? uninitialize_network() : true;
                throw exceptions::bind_socket_failure("Failed to bind the connection socket. Error " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
            }

            if (not this->start_listening()) {
                (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                (this->was_init) ? uninitialize_network() : true;
                throw exceptions::listen_socket_failure("Failed to start the server listening.", true, __FILE__, __LINE__ - 3, __FUNCTION__);
            }
            
            this->listening = true;
        }

        return this->listening;
    }

    bool network_structures::tcp_server::running() const {
        return this->bound and this->listening and ((this->secure_ and valid_secure_socket(this->secure_socket)) or (not this->secure_ and valid_socket(this->connect_socket)));
    }

    std::set<network_structures::connected_host::client> network_structures::tcp_server::get_clients() {
        std::set<network_structures::connected_host::client> the_answer;
        if (not this->listening or this->clients.empty()) {
            return the_answer;
        }
        
        fd_set ready;
        FD_ZERO(&ready);
        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            FD_SET(client->first, &ready);
        }

        if (select(this->max_socket + 1, &ready, 0, 0, (this->timeout.tv_usec is -1) ? 0 : &this->timeout) < 0) {
            (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::select_failure("Failed to select any of the connections that are ready with information. Error " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }

        this->max_socket = invalid_socket;
        this->max_secure_socket = invalid_secure_socket;
        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            this->max_socket = (client->first > this->max_socket) ? client->first : this->max_socket;
            this->max_secure_socket = (client->second.secure_socket > this->max_secure_socket) ? client->second.secure_socket : client->second.secure_socket;
            if (FD_ISSET(client->first, &ready)) {
                the_answer.insert(client->second);
            }
        }
        return the_answer;
    }

    std::set<network_structures::connected_host::client> network_structures::tcp_server::get_all_clients() {
        
        std::set<network_structures::connected_host::client> the_answer;

        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            the_answer.insert(client->second);
        }

        return the_answer;
    }

    socket_type network_structures::tcp_server::get_max_socket() const {
        return this->max_socket;
    }

    secure_socket_type network_structures::tcp_server::get_max_secure_socket() const {
        return this->max_secure_socket;
    }

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ///////////////////tcp_server end///////////////////


    /**************************************************/

    
    /////////////////////tcp_client/////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////



    network_structures::tcp_client::tcp_client() : networking::network_structures::host() {
        this->connected = false;
        this->bytes = -1;
    }

    network_structures::tcp_client::tcp_client(const std::string remote_host, const std::string connect_port, const long wait_sec, const int wait_msec, bool will_del, bool secure) :
    networking::network_structures::host(remote_host, connect_port, true, wait_sec, wait_msec, will_del, secure) {
        this->connected = false;
        this->bytes = -1;
    }

    network_structures::tcp_client::~tcp_client() {
        this->disconnect();
    }

    network_structures::tcp_client::operator bool() {
        return this->connected;
    }

    bool network_structures::tcp_client::connect_client() {
        if (this->secure_) {
            this->initialize_secure();
            this->create_context();
        }
        // std::printf("Creating address...\n");
        this->create_address();
        // std::printf("Created address...\n");

        // std::printf("Creating socket...\n");
        this->create_socket();
        // std::printf("Successfully created socket");


        if (connect(this->connect_socket, this->connect_address->ai_addr, this->connect_address->ai_addrlen)) {
            (this->del_on_except) ? this->disconnect() : true;
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::connect_failure("Failed to connect to remote machine. Error " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }
        // std::printf("Connected.\n");
        
        if (this->secure_) {
            this->create_secure_socket();
            if (not valid_secure_socket(this->secure_socket)) {
                (this->del_on_except) ? this->disconnect() : true;
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::create_socket_failure("Failed to create the secure connection socket. ", true, __FILE__, __LINE__ - 4, __FUNCTION__);
            }
            
            if (not SSL_set_tlsext_host_name(this->secure_socket, this->hostname.c_str())) {
                (this->del_on_except) ? this->disconnect() : true;
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::unexpected_exception("Failed to set the TLS host name", true, __FILE__, __LINE__ - 3, __FUNCTION__);
            }

            SSL_set_fd(this->secure_socket, this->connect_socket);
            if (SSL_connect(this->secure_socket) == -1) {
                (this->del_on_except) ? this->disconnect() : true;
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::select_failure("Failed to set the secure socket connection over the open connection", true, __FILE__, __LINE__ - 3, __FUNCTION__);
            }

            this->certificate = SSL_get_peer_certificate(this->secure_socket);
            if (not this->certificate) {
                (this->del_on_except) ? this->disconnect() : true;
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::certificate_error("Failed to get the peer certificate", true, __FILE__, __LINE__ - 4, __FUNCTION__);
            }
            this->connected = true;
        }
        else {
            this->connected = valid_socket(this->connect_socket);
        }
        return this->connected;
    }

    bool network_structures::tcp_client::disconnect() {
        if (valid_secure_socket(this->secure_socket)) {
            SSL_shutdown(this->secure_socket);
            close_socket(this->connect_socket);
            SSL_free(this->secure_socket);
            SSL_CTX_free(this->context);
            this->secure_socket = invalid_secure_socket;
            this->connect_socket = invalid_socket;
            this->context = invalid_context;
            (this->certificate) ? X509_free(this->certificate) : (void) 0;
            this->certificate = null;
            this->connected = false;
        }
        else {
            if (valid_socket(this->connect_socket)) {
                close_socket(this->connect_socket);
                this->connect_socket = invalid_socket;
                this->connected = false;
            }
        }
        this->bytes = -1;
        return this->connected;
    }

    network_structures::connected_host::server network_structures::tcp_client::get_server_connection() const {
        return {this->hostname, 
                    this->portvalue, 
                            this->context, 
                            this->secure_socket, 
                                this->connect_socket, 
                                        this->connect_address};
    }

    bool network_structures::tcp_client::server_has_message() {
        fd_set ready;
        FD_ZERO(&ready);
        FD_SET(this->connect_socket, &ready);

        if (select(this->connect_socket + 1, &ready, 0, 0, (this->timeout.tv_usec is -1) ? 0 : &this->timeout) < 0) {
            throw exceptions::select_failure("Failed to select for active sockets", true, __FILE__, __LINE__ - 1, __FUNCTION__);
        }
        return FD_ISSET(this->connect_socket, &ready);
    }



    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ///////////////////tcp_client end///////////////////



    /////////////////////http(s)_server/////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////




    // Code goes here

    void network_structures::http_server::write16(std::ofstream& file, uint16_t value) {
        file.put(value & 0xFF);
        file.put((value >> 8) & 0xFF);
    }

    void network_structures::http_server::write32(std::ofstream& file, uint32_t value) {
        file.put(value & 0xFF);
        file.put((value >> 8) & 0xFF);
        file.put((value >> 16) & 0xFF);
        file.put((value >> 24) & 0xFF);
    }

    void network_structures::http_server::create_favicon_file(const std::string file_name) {
        
        std::ofstream file(file_name, std::ios::binary);

        // ICO file header
        write16(file, 0);  // Reserved. Must always be 0.
        write16(file, 1);  // Specifies image type: 1 for icon (.ICO) image
        write16(file, 1);  // Specifies number of images in the file

        // Image entry
        file.put(16);  // Width, 0 means 256
        file.put(16);  // Height, 0 means 256
        file.put(0);   // Color palette, 0 means no palette
        file.put(0);   // Reserved. Should be 0.
        write16(file, 1);  // Color planes
        write16(file, 32); // Bits per pixel
        write32(file, 40 + 16*16*4); // Size of image data
        write32(file, 22); // Offset of image data from the beginning of the file

        // DIB header
        write32(file, 40);  // DIB header size
        write32(file, 16);  // Width
        write32(file, 32);  // Height (2 * actual height for icons)
        write16(file, 1);   // Color planes
        write16(file, 32);  // Bits per pixel
        write32(file, 0);   // Compression (0 = uncompressed)
        write32(file, 16*16*4); // Image size
        write32(file, 0);   // X pixels per meter
        write32(file, 0);   // Y pixels per meter
        write32(file, 0);   // Total colors
        write32(file, 0);   // Important colors

        // Image data (16x16 pixels, 32 bits per pixel, blue color)
        for (int i = 0; i < 16*16; ++i) {
            file.put(static_cast<char>(255));  // Blue
            file.put(0);    // Green
            file.put(0);    // Red
            file.put(static_cast<char>(255));  // Alpha
        }

        file.close();
    }

    bool network_structures::http_server::file_exists(const std::string directory, const std::string file) {
        std::filesystem::path dir_path = std::filesystem::path(directory).lexically_normal();
        std::filesystem::path file_path = std::filesystem::path(file).lexically_normal();
        std::filesystem::path full_path = dir_path / file_path;

        return std::filesystem::exists(full_path);
    }

    uintmax_t network_structures::http_server::file_size(const std::string directory, const std::string file) {
        std::filesystem::path dir_path = std::filesystem::path(directory).lexically_normal();
        std::filesystem::path file_path = std::filesystem::path(file).lexically_normal();
        std::filesystem::path full_path = dir_path / file_path;

        return std::filesystem::file_size(full_path);
    }

    std::string network_structures::http_server::get_file_content(const std::string directory, const std::string file) {
        
        std::filesystem::path dir_path = std::filesystem::path(directory).lexically_normal();
        std::filesystem::path file_path = std::filesystem::path(file).lexically_normal();
        std::filesystem::path full_path = dir_path / file_path;

        std::ifstream open_file(full_path, std::ios::in | std::ios::binary);
        if (not open_file) {
            throw exceptions::unexpected_exception("Failed to open file '" + full_path.string() + "'", true, __FILE__, __LINE__, __FUNCTION__);
        }

        std::stringstream the_answer;
        the_answer << open_file.rdbuf();

        if (open_file.fail() and not open_file.eof()) {
            throw exceptions::unexpected_exception("Error reading file '" + full_path.string() + "'", true, __FILE__, __LINE__, __FUNCTION__);
        }

        return the_answer.str();
    }

    std::map<std::string, std::string> network_structures::http_server::parse_message(std::string message) {
        std::map<std::string, std::string> the_answer;

        std::stringstream stream;
        std::string line, key, value;

        size_t pos = 0;
        
        while ((pos = message.find(this->ending)) != std::string::npos) {
            stream << message.substr(0, pos) << std::endl;
            message.erase(0, pos + this->ending.length());
        }

        stream << message; // Add the last part

        while (std::getline(stream, line)) {
            pos = line.find_first_of(":");
            if (pos == std::string::npos) {
                if (line.contains("GET")) {
                    pos = line.find_first_of(" ");
                    key = line.substr(0, pos);
                    value = line.substr(pos);
                    the_answer[METHOD] = "GET";
                    string_functions::strip(key, " ");
                    string_functions::strip(value, " ");
                }

                else if (line.contains("PULL")) {
                    pos = line.find_first_of(" ");
                    key = line.substr(0, pos);
                    value = line.substr(pos);
                    the_answer[METHOD] = "PULL";
                    string_functions::strip(key, " ");
                    string_functions::strip(value, " ");
                }
                the_answer[key] = value;
                continue;
            }
            key = line.substr(0, pos);
            value = line.substr(pos + 1);
            string_functions::strip(key, " ");
            string_functions::strip(value, " ");

            the_answer[key] = value;
        }
        return the_answer;
    }

    network_structures::http_server::http_server(const std::string base_page, const std::string base_dir, bool secure, int listen_limit) {
        this->default_page = base_page;
        this->directory = base_dir;
        this->content_options = string_functions::get_file_data("Server/files/content_options.dat");
        this->server_connection = network_structures::tcp_server("", DEFAULT_PORT, listen_limit, 0, 100000, true, secure);
    }

    network_structures::http_server::~http_server() {
        this->content_options.clear();
    }

    bool network_structures::http_server::send_404(network_structures::connected_host::client& client, const std::string message) {
        if (this->server_connection) {
            const std::string msg = "HTTP/1.1 404 Not Found" + this->ending +
                                        "Connection: close" + this->ending +
                                        "Content-Length: " + std::to_string(message.length()) + this->ending + message;
            
            if (valid_socket(client.connected_socket) and socket_is_connected(client.connected_socket)) {
                if (this->server_connection.secure_host()) {
                    return SSL_write(client.secure_socket, message.c_str(), message.length()) > 0;
                }
                return send(client.connected_socket, message.c_str(), message.length(), 0) >= 1;
            }
            else {
                this->server_connection.close_connection(client.connected_socket);
                return false;
            }
        }
        return false;
    }

    bool network_structures::http_server::send_400(network_structures::connected_host::client& client, const std::string message) {
        if (this->server_connection) {
            const std::string msg = "HTTP/1.1 400 Bad Request" + this->ending +
                                        "Connection: close" + this->ending +
                                        "Content-Length: " + std::to_string(message.length()) + this->ending + message;
            
            if (valid_socket(client.connected_socket) and socket_is_connected(client.connected_socket)) {
                if (this->server_connection.secure_host()) {
                    return SSL_write(client.secure_socket, message.c_str(), message.length()) > 0;
                }
                return send(client.connected_socket, message.c_str(), message.length(), 0) >= 1;
            }
            else {
                this->server_connection.close_connection(client.connected_socket);
                return false;
            }
        }
        return false;
    }

    bool network_structures::http_server::serve_resource(network_structures::connected_host::client client, const std::string message_from_host) {


        std::string message, content_type, server_path, buffer;

        uintmax_t file_length;
        int bytes, total;
        // unsigned long index;
        char read[4 * kilo_byte];
        size_t pos;

        std::map<std::string, std::string> headers = this->parse_message(message_from_host);
        if (headers.contains(METHOD) and headers.contains(headers[METHOD])) {
            server_path = headers[headers[METHOD]];
            pos = server_path.find(" HTTP");
            // std::printf("raw server_path is '%s'\n", server_path.c_str());
            if (pos != std::string::npos) {
                server_path = server_path.substr(0, pos);
            }
            string_functions::strip(server_path, " ");
            if (string_functions::same_string(server_path, "/")) {
                server_path = this->directory + this->default_page;//"html/homepage.html";
            }
            else if (server_path.length() > 1 and server_path[0] == '/') {
                server_path = server_path.substr(1);
            }
        }
        else {
            server_path = this->directory + this->default_page;//"html/homepage.html";
        }

        if (server_path.find(this->directory) == 0) {
            server_path = server_path.substr(this->directory.length());
        }

        for (const auto& [encoded, decoded] : this->url_decode_map) {
            string_functions::replace_all(server_path, encoded, decoded);
        }

        // std::printf("Processed server_path is '%s'\n", server_path.c_str());

        if (not this->file_exists(this->directory, server_path)) {
            this->send_404(client, "No directory " + server_path + " found");
            std::fprintf(stderr, "No file '%s%s' found\n", this->directory.c_str(), server_path.c_str());
            return false;
        }
        

        file_length = this->file_size(this->directory, server_path);
        
        
        message = "HTTP/1.1 200 OK" + this->ending;
        bytes = (this->server_connection.secure_host()) ? 
                    SSL_write(client.secure_socket, message.c_str(), message.length()) :
                        send(client.connected_socket, message.c_str(), message.length(), 0);
        


        buffer = this->message_headers[CONNECTION];

        if (headers.contains(CONNECTION)) {
            buffer = headers[CONNECTION];
        }


        message = "Connection: " + buffer + this->ending;
        bytes = (this->server_connection.secure_host()) ? 
                    SSL_write(client.secure_socket, message.c_str(), message.length()) :
                        send(client.connected_socket, message.c_str(), message.length(), 0);


        
        message = "Content-Length: " + std::to_string(file_length) + this->ending;
        bytes = (this->server_connection.secure_host()) ? 
                    SSL_write(client.secure_socket, message.c_str(), message.length()) :
                        send(client.connected_socket, message.c_str(), message.length(), 0);

        
        content_type = this->default_content_type;

        if (server_path.find_last_of(".") != std::string::npos) {
            buffer = server_path.substr(server_path.find_last_of("."));
            if (this->content_options.contains(buffer)) {
                content_type = this->content_options[buffer];
            }
        }


        message = "Content-Type: " + content_type + this->ending;
        bytes = (this->server_connection.secure_host()) ? 
                    SSL_write(client.secure_socket, message.c_str(), message.length()) :
                        send(client.connected_socket, message.c_str(), message.length(), 0);


        

        message = this->ending;
        bytes = (this->server_connection.secure_host()) ? 
                    SSL_write(client.secure_socket, message.c_str(), message.length()) :
                        send(client.connected_socket, message.c_str(), message.length(), 0);




        std::ifstream open_file(this->directory + server_path, std::ios::binary);
        if (!open_file.is_open()) {
            std::fprintf(stderr, "Failed to open file '%s%s'\n", this->directory.c_str(), server_path.c_str());
            this->send_400(client, "Failed to open '" + this->directory + server_path + "'");
            return false;
        }

        total = 0;

        while (open_file.read(read, 4 * kilo_byte) || open_file.gcount()) {
            size_t bytes_read = open_file.gcount();
            bytes = (this->server_connection.secure_host()) ?
                SSL_write(client.secure_socket, read, bytes_read) :
                send(client.connected_socket, read, bytes_read, 0);
            
            if (bytes <= 0) {
                std::fprintf(stderr, "Failed to send data. Error: %d\n", errno);
                open_file.close();
                return false;
            }
            total += bytes;
        }

        open_file.close();
        return (uintmax_t) total == file_length;

    }

    bool network_structures::http_server::serve_resource(network_structures::connected_host::client client, std::map<std::string, std::string> headers) {


        std::string message, content_type, server_path, buffer;

        uintmax_t file_length;
        int bytes, total;
        // unsigned long index;
        char read[4 * kilo_byte];
        size_t pos;


        if (headers.contains(METHOD) and headers.contains(headers[METHOD])) {
            server_path = headers[headers[METHOD]];
            pos = server_path.find(" HTTP");
            // std::printf("raw server_path is '%s'\n", server_path.c_str());
            if (pos != std::string::npos) {
                server_path = server_path.substr(0, pos);
            }
            string_functions::strip(server_path, " ");
            if (string_functions::same_string(server_path, "/")) {
                server_path = this->directory + "html/homepage.html";
            }
            else if (server_path.length() > 1 and server_path[0] == '/') {
                server_path = server_path.substr(1);
            }
        }
        else {
            server_path = this->directory + "html/homepage.html";
        }

        if (server_path.find(this->directory) == 0) {
            server_path = server_path.substr(this->directory.length());
        }

        for (const auto& [encoded, decoded] : this->url_decode_map) {
            string_functions::replace_all(server_path, encoded, decoded);
        }

        // std::printf("Processed server_path is '%s'\n", server_path.c_str());

        if (not this->file_exists(this->directory, server_path)) {
            this->send_404(client, "No directory " + server_path + " found");
            std::fprintf(stderr, "No file '%s%s' found\n", this->directory.c_str(), server_path.c_str());
            return false;
        }
        

        file_length = this->file_size(this->directory, server_path);
        
        
        message = "HTTP/1.1 200 OK" + this->ending;
        bytes = (this->server_connection.secure_host()) ? 
                    SSL_write(client.secure_socket, message.c_str(), message.length()) :
                        send(client.connected_socket, message.c_str(), message.length(), 0);
        


        buffer = this->message_headers[CONNECTION];

        if (headers.contains(CONNECTION)) {
            buffer = headers[CONNECTION];
        }


        message = "Connection: " + buffer + this->ending;
        bytes = (this->server_connection.secure_host()) ? 
                    SSL_write(client.secure_socket, message.c_str(), message.length()) :
                        send(client.connected_socket, message.c_str(), message.length(), 0);


        
        message = "Content-Length: " + std::to_string(file_length) + this->ending;
        bytes = (this->server_connection.secure_host()) ? 
                    SSL_write(client.secure_socket, message.c_str(), message.length()) :
                        send(client.connected_socket, message.c_str(), message.length(), 0);

        
        content_type = this->default_content_type;

        if (server_path.find_last_of(".") != std::string::npos) {
            buffer = server_path.substr(server_path.find_last_of("."));
            if (string_functions::contains<std::string>(this->content_options, buffer, true)) {
                content_type = this->content_options[buffer];
            }
        }


        message = "Content-Type: " + content_type + this->ending;
        bytes = (this->server_connection.secure_host()) ? 
                    SSL_write(client.secure_socket, message.c_str(), message.length()) :
                        send(client.connected_socket, message.c_str(), message.length(), 0);


        

        message = this->ending;
        bytes = (this->server_connection.secure_host()) ? 
                    SSL_write(client.secure_socket, message.c_str(), message.length()) :
                        send(client.connected_socket, message.c_str(), message.length(), 0);




        std::ifstream open_file(this->directory + server_path, std::ios::binary);
        if (!open_file.is_open()) {
            std::fprintf(stderr, "Failed to open file '%s%s'\n", this->directory.c_str(), server_path.c_str());
            this->send_400(client, "Failed to open '" + this->directory + server_path + "'");
            return false;
        }

        total = 0;

        while (open_file.read(read, 4 * kilo_byte) || open_file.gcount()) {
            size_t bytes_read = open_file.gcount();
            bytes = (this->server_connection.secure_host()) ?
                SSL_write(client.secure_socket, read, bytes_read) :
                send(client.connected_socket, read, bytes_read, 0);
            
            if (bytes <= 0) {
                std::fprintf(stderr, "Failed to send data. Error: %d\n", errno);
                open_file.close();
                return false;
            }
            total += bytes;
        }

        open_file.close();
        return (uintmax_t) total == file_length;

    }


    bool network_structures::http_server::run() {
        if (not this->server_connection) {
            this->server_connection.start();
        }
        std::printf("Connect to host using 'http%s://%s:%s\n\n\n", 
                    (this->server_connection.secure_host()) ? "s" : "", 
                        this->server_connection.host_name().c_str(), 
                            this->server_connection.port_value().c_str());

        networking::network_structures::connected_host::client client, last_one;
        std::set<networking::network_structures::connected_host::client> clients;
        std::map<std::string, std::string> headers;
        std::string message;
        char message_buffer[2 * kilo_byte];
        ssize_t bytes;
        bool served;
        std::map<std::string, std::string> header_message;
        last_one.connected_socket = invalid_socket;
        while (this->server_connection) {
            // std::printf("Live...\n");
            client = this->server_connection.new_client();
            if (valid_socket(client.connected_socket) and not string_functions::same_string(client.hostname, last_one.hostname)) {
                std::printf("New connection from 'http%s://%s:%s'\n", 
                            this->server_connection.secure_host() ? "s" : "",
                            client.hostname.c_str(), client.portvalue.c_str());
                last_one = client;
            }

            clients = this->server_connection.get_clients();

            if (not clients.empty()) {
                // std::printf("There is a new message.\n");
                for (auto client = clients.begin(); client != clients.end(); client++) {

                    bytes = recv(client->connected_socket, message_buffer, kilo_byte * 2, 0);
                    if (bytes < 1) {
                        std::printf("Connection with '%s' on port '%s' closed by peer.\n", client->hostname.c_str(), client->portvalue.c_str());
                        this->server_connection.close_connection(client->connected_socket);
                        continue;
                    }

                    // std::printf("Message from '%s':\n\n%.*s\n\n", client->hostname.c_str(), (int) bytes, message_buffer);

                    headers = this->parse_message(std::string(message_buffer, bytes));
                    if (not headers.empty()) {
                        if (headers.contains(METHOD)) {
                            served = this->serve_resource(*client, headers);
                            if ((not served or headers.contains(CONNECTION)) and (string_functions::same_string(headers[CONNECTION], "close"))) {
                                std::printf("Closing connection to client '%s' on port '%s'.\n", client->hostname.c_str(), client->portvalue.c_str());
                                this->server_connection.close_connection(client->connected_socket);
                                continue;
                            }
                        }
                    }
                }
            }

            if (string_functions::has_keyboard_input()) {
                // std::printf("There is a server message.\n");
                message = string_functions::get_input();

                if (string_functions::same_string(message, "exists()") or string_functions::same_string("exit", message)) {
                    std::printf("Server is disconnecting...\n");
                    this->disconnect();
                }

                else if (string_functions::same_string(message, "list_clients()") or string_functions::same_string(message, "lc")) {
                    clients = this->server_connection.get_all_clients();
                    (clients.size() > 0) ? std::printf("------------------------------------------------------\nConnected clients:\n") : 0;
                    if (clients.empty()) {
                        std::printf("\n\tThere are no connected clients.\n\n");
                    }
                    for (auto client = clients.begin(); client != clients.end(); client++) {
                        std::printf("\t%s, ", client->hostname.c_str());
                        std::printf("\t%s,", client->portvalue.c_str());
                        std::printf("\t%s\n", std::to_string(client->connected_socket).c_str());
                        std::printf("\t---------------------------------------------------\n");
                    }
                }

                else if (string_functions::same_string(message, "disconnect_client()") or string_functions::same_string(message, "dc")) {
                    // std::printf("UNDER CONSTRUCTION.\n");
                    message = string_functions::get_input("Client to disconnect: ");
                    clients = this->server_connection.get_all_clients();
                    for (auto client = clients.begin(); client != clients.end(); client++) {
                        if (string_functions::same_string(client->hostname, message) 
                                                        or 
                            string_functions::same_string(client->portvalue, message) 
                                                        or
                            string_functions::same_string(message, std::to_string(client->connected_socket))) {
                                std::printf("FOUND. Closing connection to '%s'\n", client->hostname.c_str());
                                this->server_connection.close_connection(client->connected_socket);
                        }
                    }
                }

                else if (string_functions::same_string(message, "broadcast()") or string_functions::same_string(message, "brdcst")) {
                    message = string_functions::get_input("Message to broadcast: ");
                    clients = this->server_connection.get_all_clients();
                    for (auto client = clients.begin(); client != clients.end(); client++) {
                        bytes = (this->server_connection.secure_host()) ? 
                                SSL_write(client->secure_socket, message.c_str(), message.length()) :
                                    send(client->connected_socket, message.c_str(), message.length(), 0);
                        if ((this->server_connection.secure_host() and bytes <= 0)
                                        or
                        (this->server_connection.secure_host() and bytes < 1)) {
                            std::fprintf(stderr, "Failed to send a message to '%s' on port '%s'\n", client->hostname.c_str(), client->portvalue.c_str());
                            this->server_connection.close_connection(client->connected_socket);
                            continue;
                        }
                    }
                }

                else {
                    std::printf("Unrecognized server command... '%s'\n", message.c_str());
                    std::printf("exists() to close the server.\n");
                    std::printf("list_clients() to list all connected clients.\n");
                    std::printf("disconnect_client() to disconnect a client.\n");
                    std::printf("broadcast() to broadcast a message to all clients connected to this server.\n");
                    std::printf("disconnect_client() to disconnect a connected client\n");
                }
            }
        }
        
        return true;
    }


    bool network_structures::http_server::disconnect() {
        if (this->server_connection) {
            this->server_connection.close_server();
        }
        return not this->server_connection.running();
    }

    network_structures::http_server::operator bool() const {
        return this->server_connection;
    }

    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ///////////////////http(s)_server end///////////////////



}