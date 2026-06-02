








#include <regex>
#include <sstream>
#include <string>
#include <string_view>




#include <String Functions>
#include <Request Exceptions>
#include <Url>




requests::Url& requests::Url::reset(std::string_view& the_view) {
    the_view = std::string_view();
    return *this;
}

requests::Url& requests::Url::reset_all(const bool raw) {
    if (raw) this->raw_url_ = "";
    this->queries_.clear();
    return this->reset(this->scheme_)
    .reset(this->username_).reset(this->password_)
    .reset(this->subdomain_).reset(this->domain_).reset(this->top_level_domain_)
    .reset(this->port_)
    .reset(this->path_)
    .reset(this->query_)
    .reset(this->fragment_);
}

requests::Url& requests::Url::parse() {

    if (this->raw_url_.empty()) throw requests::empty_url("No url defined");

    this->reset_all();

    std::string_view the_url(this->raw_url_);
    std::match_results<std::string_view::const_iterator> matches;

    if (std::regex_search(the_url.begin(), the_url.end(), matches, requests::detail::complete_url)) {

        if (matches[requests::detail::THE_SCHEME].matched) this->scheme_ = { matches[requests::detail::THE_SCHEME].first, matches[requests::detail::THE_SCHEME].second};

        if (matches[requests::detail::THE_AUTHORITY].matched) {
            const std::regex authority_pattern(R"regex(([^:@\r\n]*):([^:@\r\n]*)@)regex", std::regex_constants::icase);
            std::match_results<std::string_view::const_iterator> authority_matches;
            std::string_view this_authority = {matches[requests::detail::THE_AUTHORITY].first, matches[requests::detail::THE_AUTHORITY].second};
            if (std::regex_search(this_authority.begin(), this_authority.end(), authority_matches, authority_pattern)) {

                this->username_ = { authority_matches[1].first, authority_matches[1].second};

                this->password_ = { authority_matches[2].first, authority_matches[2].second};
            }
        }

        {   // THE_DOMAIN (group 5) is mandatory in complete_url -> always matched once the url matched
            std::string_view complete_domain = { matches[requests::detail::THE_DOMAIN].first, matches[requests::detail::THE_DOMAIN].second };
            const requests::detail::host_parts parts = requests::detail::split_host(requests::detail::the_psl(), complete_domain);
            if (parts.ok) {
                this->subdomain_        = parts.subdomain;
                this->domain_           = parts.domain;
                this->top_level_domain_ = parts.top_level_domain;
            }
            else {
                this->domain_ = complete_domain;   // localhost, bare TLDs, single-label hosts
            }
        }

        if (matches[requests::detail::THE_PORT].matched) this->port_ = { matches[requests::detail::THE_PORT].first, matches[requests::detail::THE_PORT].second};

        if (matches[requests::detail::THE_PATH].matched) this->path_ = { matches[requests::detail::THE_PATH].first, matches[requests::detail::THE_PATH].second};
        else this->path_ = "/";

        if (matches[requests::detail::THE_QUERY].matched) {
            this->query_ = { matches[requests::detail::THE_QUERY].first, matches[requests::detail::THE_QUERY].second};
            const std::string query(this->query_);
            const char delim = '&';
            std::string line;
            std::stringstream stream(query);
            while (std::getline(stream, line, delim)) {

                const std::size_t delim_index = string_functions::index_of(line, '=');
                if (delim_index == std::string::npos) throw requests::illegal_url_exception("No delimiter fond to segregate the key/value pair within a query");
                const std::string_view line_view = line;
                const std::string_view key = string_functions::strip(line_view.substr(0, delim_index));
                const std::string_view value = string_functions::strip(line_view.substr(delim_index + 1));
                this->queries_[key] = value;
            }
        }

        if (matches[requests::detail::THE_FRAGMENT].matched) this->fragment_ = { matches[requests::detail::THE_FRAGMENT].first, matches[requests::detail::THE_FRAGMENT].second};

    }

    return *this;
}

requests::Url::Url(const requests::Url& other) : raw_url_(other.raw_url_) {
    this->parse();
}

requests::Url::Url(requests::Url&& other) noexcept : raw_url_(std::move(other.raw_url_)) {
    if (!this->raw_url_.empty()) this->parse();
    else this->reset_all();
    other.reset_all(true);
}

requests::Url& requests::Url::operator=(const requests::Url& other) {
    if (this == &other) return *this;
    this->raw_url_ = other.raw_url_;
    this->parse();
    return *this;
}

requests::Url& requests::Url::operator=(requests::Url&& other) noexcept {
    if (this == &other) return *this;
    this->raw_url_ = std::move(other.raw_url_);
    other.reset_all(true);
    if (!this->raw_url_.empty()) this->parse();
    else this->reset_all();
    return *this;
}

bool requests::Url::equals(const requests::Url& other, const bool ignore_case) const {
    return string_functions::same_string(this->raw_url_, other.raw_url_, ignore_case);
}

bool requests::Url::operator==(const requests::Url& other) const {
    return this->equals(other);
}

requests::Url::operator std::string_view() const {
    return this->raw_url_;
}

requests::Url::operator bool() const {
    return not this->raw_url_.empty();
}

std::string_view requests::Url::operator[](const std::string_view key) const {
    const auto value = this->queries_.find(key);
    if (value == this->queries_.end()) return "";
    return this->queries_.at(key).get_ref<const nlohmann::json::string_t&>();
}

std::string_view requests::Url::url() const {
    return this->raw_url_;
}

std::string_view requests::Url::scheme() const {
    return this->scheme_;
}

std::string_view requests::Url::username() const {
    return this->username_;
}

std::string_view requests::Url::password() const {
    return this->password_;
}

std::string_view requests::Url::subdomain() const {
    return this->subdomain_;
}

std::string_view requests::Url::domain() const {
    return this->domain_;
}

std::string_view requests::Url::top_level_domain() const {
    return this->top_level_domain_;
}

const std::string requests::Url::usable_domain() const {
    if (this->domain_.empty() or this->top_level_domain_.empty()) return std::string(this->domain_).append(this->top_level_domain_);
    return std::string(this->domain_).append(".").append(this->top_level_domain_);
}

std::string_view requests::Url::port() const {
    return this->port_;
}

std::string_view requests::Url::path() const {
    return this->path_;
}

std::string_view requests::Url::query() const {
    return this->query_;
}

const nlohmann::json& requests::Url::queries() const {
    return this->queries_;
}

std::string_view requests::Url::fragment() const {
    return this->fragment_;
}

bool requests::Url::empty() const {
    return this->raw_url_.empty();
}

std::size_t requests::Url::hash() const {
    return std::hash<std::string>{}(this->raw_url_);
}

requests::Url& requests::Url::assign(std::string raw_url) {
    if (string_functions::same_string(this->raw_url_, raw_url, false)) return *this;
    this->raw_url_ = std::move(raw_url);
    this->parse();
    return *this;
}