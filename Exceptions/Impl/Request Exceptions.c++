



#include <string_view>




#include <Request Exceptions>




#if not defined(make_constructor)
    #define make_constructor(name) \
    requests::name::name(std::string_view msg)\
    : requests::except_<requests::name>::except_(msg) {}\
    \
    std::string_view requests::name::message() const {return this->msg_;}\
    \
    std::string_view requests::name::exception_type() const {\
        return #name;\
    }
#endif




make_constructor(unsupported)
make_constructor(illegal_url_exception)
make_constructor(empty_url)



#if defined(make_constructor)
    #undef make_constructor
#endif