

#include "../prototypes/requests"






int main(int len, char** args) {

    if (len < 2) {
        std::fprintf(stderr, "Usage : %s url\n", *args);
        return 1;
    }

    try {
        std::printf("http GET request.\n");
        requests::http_requests::http request(std::string(*(args + 1)));
        request.get();
        std::printf("Reached.\n");
    }

    catch(networking::exceptions::connect_failure except) {
        std::fprintf(stderr, "Exception was caught with get method \"%s\"\n", except.what());
    }

    catch (networking::exceptions::unexpected_exception except) {
        std::fprintf(stderr, "Exception was caught with get method \"%s\"\n", except.what());
    }

    try {
        std::printf("http HEAD request.\n");
        requests::http_requests::http request(std::string(*(args + 1)));
        request.head();
        std::printf("Reached.\n");
    }

    catch(networking::exceptions::connect_failure except) {
        std::fprintf(stderr, "Exception was caught with head method \"%s\"\n", except.what());
    }

    catch (networking::exceptions::unexpected_exception except) {
        std::fprintf(stderr, "Exception was caught with head method \"%s\"\n", except.what());
    }
    return 0;
}