

#include "../prototypes/requests"






int main(int len, char** args) {

    if (len < 2) {
        std::fprintf(stderr, "Usage : %s url\n", *args);
        return 1;
    }

    try {
        requests::http_requests::request the_request;
    }
    catch (networking::exceptions::base_exception except) {
        std::printf("%s\n", except.what());
    }
    std::printf("Reached.\n");
    return 0;
}