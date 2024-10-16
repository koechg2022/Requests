

#include "../prototypes/requests"






int main(int len, char** args) {

    if (len < 2) {
        std::fprintf(stderr, "Usage : %s url\n", *args);
        return 1;
    }

    try {
        requests::http_requests::http request(std::string(*(args + 1)));
        request.get();
        std::printf("Reached.\n");
    }

    catch(networking::exceptions::connect_failure except) {
        std::fprintf(stderr, "Exception was caught %s\n", except.what());
    }

    catch (networking::exceptions::unexpected_exception except) {
        std::fprintf(stderr, "Exception was caught %s\n", except.what());
    }

    return 0;
}