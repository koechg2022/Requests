

#include "../prototypes/requests"






int main(int len, char** args) {

    if (len < 2) {
        std::fprintf(stderr, "Usage : \"%s\" url\n", *args);
        return 1;
    }

    // requests::tester(args, len);
    std::string protocol,
                hostname, 
                port,
                path,
                hash;
    requests_library::parse_url(std::string(*(args + 1)), protocol, hostname, port, path, hash);
    std::printf("Here's the parsed url:\n");
    std::printf("\tProtocol: \"%s\"\n", protocol.c_str());
    std::printf("\tHostname: \"%s\"\n", hostname.c_str());
    std::printf("\tPort: \"%s\"\n", port.c_str());
    std::printf("\tPath: \"%s\"\n", path.c_str());
    std::printf("\tHash: \"%s\"\n", hash.c_str());

    requests_library::requests request_http(std::string((*args + 1)));
    requests_library::requests request_https(std::string(*args + 1), true);

    std::printf("Reached.\n");

    return 0;
}