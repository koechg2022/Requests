

#include <cstring>
#include <string>
#include <string_view>

#include <Network headers>

#include <Exceptions>
#include <url>



requests::url& requests::url::parse(std::string_view raw_url) {
   size_t pos = 0, end;

    // Scheme
    end = raw_url.find("://", pos);
    if (end != std::string_view::npos) {
        this->pairs_.insert({SCHEME, {raw_url.data() + pos, raw_url.data() + end}});
        pos = end + 3; // skip "://"
    }

    // User info and host
    size_t host_start = pos;
    end = raw_url.find('@', pos);
    if (end != std::string_view::npos) {
        this->pairs_.insert({USER_INFO, {raw_url.data() + pos, raw_url.data() + end}});
        host_start = end + 1;
    }

    // Port, path, query, fragment — search from host start
    size_t port_start = raw_url.find(':', host_start);
    size_t path_start = raw_url.find('/', host_start);
    size_t query_start = raw_url.find('?', host_start);
    size_t fragment_start = raw_url.find('#', host_start);

    // Determine fragment
    if (fragment_start != std::string_view::npos) {
        this->pairs_.insert({FRAGMENT, {raw_url.data() + fragment_start + 1, raw_url.data() + raw_url.size()}});
        path_start = std::min(path_start, fragment_start);
        query_start = std::min(query_start, fragment_start);
    }

    // Determine query
    if (query_start != std::string_view::npos && query_start < path_start) {
        this->pairs_.insert({QUERY, {raw_url.data() + query_start + 1, raw_url.data() + fragment_start}});
        path_start = std::min(path_start, query_start);
    }

    // Determine port
    if (port_start != std::string_view::npos && 
        (path_start == std::string_view::npos || port_start < path_start)) {
        size_t port_end = port_start + 1;
        while (port_end < raw_url.size() && std::isdigit(raw_url[port_end])) ++port_end;
        this->pairs_.insert({PORT, {raw_url.data() + port_start + 1, raw_url.data() + port_end}});
    } else {
        port_start = std::string_view::npos;
    }

    // Extract host
    size_t host_end = port_start != std::string_view::npos ? port_start : path_start;
    if (host_end == std::string_view::npos) host_end = fragment_start;
    if (host_end == std::string_view::npos) host_end = query_start;
    if (host_end == std::string_view::npos) host_end = raw_url.size();
    this->pairs_.insert({HOST, {raw_url.data() + host_start, raw_url.data() + host_end}});

    // Extract path
    if (path_start != std::string_view::npos) {
        size_t path_end = fragment_start != std::string_view::npos ? fragment_start : raw_url.size();
        this->pairs_.insert({PATH, {raw_url.data() + path_start, raw_url.data() + path_end}});
    }
    return *this;
}

requests::url::url(std::string_view raw_url) 
: url_(raw_url) {
    this->parse(this->url_);
}

requests::url::url(const requests::url& other) : url_(other.url_) {
    this->parse(this->url_);
}

requests::url::url(requests::url&& other) noexcept : url_(other.url_) {
    this->parse(this->url_);
    other.url_.clear();
}

requests::url::~url() {
    this->pairs_.clear();
}

requests::url& requests::url::operator=(const requests::url& other) {
    if (this == &other) return *this;
    this->url_ = other.url_;
    return *this;
}

requests::url& requests::url::operator=(requests::url&& other) noexcept {
    if (this == &other) return *this;
    this->url_ = std::move(other.url_);
    other.url_.clear();
    return *this;
}

const std::string requests::url::operator[](std::string_view element) const {
    std::string the_answer;
    std::string element_(element);
    if (not (element_ within this->pairs_)) throw networking::unsupported("No element " + element_ + " in this url.");
    const std::pair<const char*, const char*> points = this->pairs_.at(element_);
    return std::string(points.first, points.second);
}

requests::url::operator bool() const {
    return not this->pairs_.empty();
}

bool requests::url::scheme() const {
    return SCHEME within this->pairs_;
}

bool requests::url::user_info() const {
    return USER_INFO within this->pairs_;
}

bool requests::url::host() const {
    return HOST within this->pairs_;
}

bool requests::url::port() const {
    return PORT within this->pairs_;
}

bool requests::url::path() const {
    return PATH within this->pairs_;
}

bool requests::url::query() const {
    return QUERY within this->pairs_;
}

bool requests::url::fragment() const {
    return FRAGMENT within this->pairs_;
}