



#include <regex>
#include <sstream>
#include <string>
#include <string_view>



#include <String Functions>
#include <Request Exceptions>
#include <Url>




namespace {


    // scheme://username:password@subdomain.domain.tld:port/path?query=key&value#fragment

    // ^((.+?):\/\/)?([^:@\r\n]+:[^:@\r\n]+@)?((?<=^|:\/\/|@)[^:\/?#\r\n]+?(?=[:\/?#\r\n]|$))?(:[0-9]+[^\/\?\#\r\n])?(\/[^\?\r\n]*)?(\?[^\#\r\n]*)?(\#[^\r\n]*)?
    // ^((.+?):\/\/)?(?:(([^@\/?#\r\n]+)@))?([^:\/?#\r\n]+)(?::(\d+))?(?=[\/?#]|$)?(?:\/([^?#\r\n]*))?(?=[?#\r\n]|$)?(?:\?([^\#\r\n]*))?(?=#[^\r\n]*|$)?(?:#([^\r\n]*))?$
    const std::regex complete_url(R"regex(^((.+?):\/\/)?(?:(([^@\/?#\r\n]+)@))?([^:\/?#\r\n]+)(?::(\d+))?(?=[\/?#]|$)?(?:\/([^?#\r\n]*))?(?=[?#\r\n]|$)?(?:\?([^\#\r\n]*))?(?=#[^\r\n]*|$)?(?:#([^\r\n]*))?$)regex", std::regex_constants::icase);
    using components = enum {
        THE_SCHEME = 1,
        THE_AUTHORITY,
        THE_DOMAIN,
        THE_PORT,
        THE_PATH,
        THE_QUERY,
        THE_FRAGMENT,
    };

}




requests::Url& requests::Url::reset(std::string_view& the_view) {
    the_view = std::string_view();
    return *this;
}

requests::Url& requests::Url::parse() {

    if (this->raw_url_.empty()) throw requests::empty_url("No url defined");

    this->reset(this->scheme_)
    .reset(this->username_).reset(this->password_)
    .reset(this->subdomain_).reset(this->domain_).reset(this->top_level_domain_)
    .reset(this->port_)
    .reset(this->path_)
    .reset(this->query_)
    .reset(this->fragment_);

    // this->raw_url_ = raw_url;
    std::string_view the_url(this->raw_url_);
    std::match_results<std::string_view::const_iterator> matches;

    if (std::regex_search(the_url.begin(), the_url.end(), matches, complete_url)) {
        
        if (matches[THE_SCHEME].matched) this->scheme_ = { matches[THE_SCHEME].first, matches[THE_SCHEME].second};

        if (matches[THE_AUTHORITY].matched) {
            const std::regex authority_pattern(R"regex(([^:@\r\n]*:[^:@\r\n]*@)?)regex", std::regex_constants::icase);
            std::match_results<std::string_view::const_iterator> authority_matches;
            std::string_view this_authority = {matches[THE_AUTHORITY].first, matches[THE_AUTHORITY].second};
            if (std::regex_search(this_authority.begin(), this_authority.end(), authority_matches, authority_pattern)) {

                if (authority_matches[1].matched) this->username_ = { authority_matches[1].first, authority_matches[1].second};

                if (authority_matches[2].matched) this->password_ = { authority_matches[2].first, authority_matches[2].second};
            }
        }

        if (matches[THE_DOMAIN].matched) {
            this->complete_domain_ = { matches[THE_DOMAIN].first, matches[THE_DOMAIN].second};
            const std::regex domain_pattern(R"regex(([^:\r\n]*)\.([^:\r\n]*)\.([^:\r\n]*))regex", std::regex_constants::icase);
            std::match_results<std::string_view::const_iterator> domain_matches;
            // std::string_view this_domain = {matches[THE_DOMAIN].first, matches[THE_DOMAIN].second};
            if (std::regex_search(this->complete_domain_.begin(), this->complete_domain_.end(), domain_matches, domain_pattern)) {

                if (domain_matches[1].matched) this->subdomain_ = { domain_matches[1].first, domain_matches[1].second};

                if (domain_matches[2].matched) this->domain_ = { domain_matches[2].first, domain_matches[2].second};

                if (domain_matches[3].matched) this->top_level_domain_ = { domain_matches[3].first, domain_matches[3].second};
            }
        }

        if (matches[THE_PORT].matched) this->port_ = { matches[THE_PORT].first, matches[THE_PORT].second};

        if (matches[THE_PATH].matched) this->path_ = { matches[THE_PATH].first, matches[THE_PATH].second};

        if (matches[THE_QUERY].matched) {
            // TODO : pick up here tomorrow
            this->query_ = { matches[THE_QUERY].first, matches[THE_QUERY].second};
            const std::string query(this->query_);
            const char delim = '&';
            std::string line;
            std::stringstream stream(query);
            while (std::getline(stream, line, delim)) {
                
                const std::size_t delim_index = string_functions::index_of(line, delim);
                if (delim_index == std::string::npos) throw requests::illegal_url_exception("No delimiter fond to segregate the key/value pair within a query");
                const std::string_view key = string_functions::strip(line.substr(0, delim_index));
                const std::string_view value = string_functions::strip(line.substr(delim_index + 1));
                this->queries_[key] = value;
            }
        }

        if (matches[THE_FRAGMENT].matched) this->fragment_ = { matches[THE_FRAGMENT].first, matches[THE_FRAGMENT].second};

    }

    return *this;
}






requests::Url::Url(std::string_view raw_url) : raw_url_(raw_url) {
    this->parse();
}

requests::Url::Url(const requests::Url& other) : raw_url_(other.raw_url_) {
    this->parse();
}

requests::Url::Url(requests::Url&& other) noexcept : raw_url_(std::move(other.raw_url_)) {

}