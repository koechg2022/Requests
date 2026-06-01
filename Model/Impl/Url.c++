



// #include <filesystem>
#include <cctype>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>




#include <String Functions>
#include <Request Exceptions>
#include <Url>




namespace {


    // scheme://username:password@subdomain.domain.tld:port/path?query=key&value#fragment

    const std::regex complete_url(R"regex(^((.+?):\/\/)?(?:(([^@\/?#\r\n]+)@))?([^:\/?#\r\n]+)(?::(\d+))?(?=[\/?#]|$)(?:\/([^?#\r\n]*))?(?=[?#\r\n]|$)(?:\?([^\#\r\n]*))?(?=#[^\r\n]*|$)(?:#([^\r\n]*))?$)regex", std::regex_constants::icase);
    
    using components = enum {
        THE_SCHEME    = 2,   // group 1 is "scheme://"; group 2 is the bare scheme name
        THE_AUTHORITY = 3,   // "user:pass@" (group 4 is the userinfo without the @)
        THE_DOMAIN    = 5,
        THE_PORT      = 6,
        THE_PATH      = 7,
        THE_QUERY     = 8,
        THE_FRAGMENT  = 9,
    };

    class psl_list {

        std::unordered_set<std::string> rules_, exceptions_;

        public:

            psl_list& load_from_text(std::string_view text) {
                std::size_t start = 0;
                while (start <= text.size()) {
                    std::size_t nl = text.find('\n', start);
                    std::string_view line = (nl == std::string_view::npos)
                        ? text.substr(start) : text.substr(start, nl - start);
                    while (!line.empty() && (line.front() == ' ' || line.front() == '\t')) line.remove_prefix(1);
                    while (!line.empty() && (line.back() == ' ' || line.back() == '\t' || line.back() == '\r')) line.remove_suffix(1);
                    if (!line.empty() && !(line.size() >= 2 && line[0] == '/' && line[1] == '/')) {
                        if (line.front() == '!') this->exceptions_.emplace(line.substr(1));
                        else                     this->rules_.emplace(line);
                    }
                    if (nl == std::string_view::npos) break;
                    start = nl + 1;
                }
                return *this;
            }

            // psl_list& load_from_file(std::filesystem::path& path) {
            //     #embed "public_suffix_list.dat"
            //     return *this;
            // }

            psl_list& load_built_in() {
                static constexpr unsigned char suffix_list[] = {
                    #embed "public_suffix_list.dat"
                };
                return this->load_from_text(std::string_view(reinterpret_cast<const char*>(suffix_list), sizeof(suffix_list)));
            }

            bool has_rule(const std::string& rule) const {
                return this->rules_.contains(rule);
            }

            bool has_exception(const std::string& except) const {
                return this->exceptions_.contains(except);
            }

    };

    struct host_parts { std::string_view subdomain, domain, top_level_domain; bool ok = false; };

    std::vector<std::string_view> split_labels(std::string_view h) {
        std::vector<std::string_view> labels;
        std::size_t start = 0;
        for (;;) {
            std::size_t dot = h.find('.', start);
            if (dot == std::string_view::npos) { labels.push_back(h.substr(start)); break; }
            labels.push_back(h.substr(start, dot - start));
            start = dot + 1;
        }
        return labels;
    }
    std::size_t public_suffix_labels(const psl_list& psl, const std::vector<std::string_view>& labels) {
        const std::size_t n = labels.size();
        auto join_from = [&](std::size_t i) {
            std::string s;
            for (std::size_t k = i; k < n; ++k) { if (k > i) s += '.'; s += labels[k]; }
            return s;
        };
        for (std::size_t i = 0; i < n; ++i)                 // exception rules take priority
            if (psl.has_exception(join_from(i))) return (n - i) - 1;
        std::size_t best = 0; bool matched = false;         // else longest normal/wildcard rule
        for (std::size_t i = 0; i < n; ++i) {
            const std::size_t len = n - i;
            if (psl.has_rule(join_from(i))) { matched = true; if (len > best) best = len; }
            if (i + 1 < n && psl.has_rule("*." + join_from(i + 1))) { matched = true; if (len > best) best = len; }
        }
        return matched ? best : 1; 
    }
    host_parts split_host(const psl_list& psl, std::string_view host) {
        host_parts result;
        if (host.empty()) return result;

        std::string lower(host);                                // lowercase copy, for matching only
        for (char& c : lower) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

        const std::vector<std::string_view> lower_labels = split_labels(lower);
        const std::size_t n = lower_labels.size();
        std::size_t suffix_n = public_suffix_labels(psl, lower_labels);
        if (suffix_n > n) suffix_n = n;

        if (n <= suffix_n) {                                    // host is itself a public suffix
            result.top_level_domain = host;
            result.ok = false;
            return result;
        }

        const std::vector<std::string_view> orig = split_labels(host);   // slice ORIGINAL (case preserved)
        const std::size_t domain_label = n - suffix_n - 1;
        const std::size_t domain_off = static_cast<std::size_t>(orig[domain_label].data() - host.data());
        const std::size_t tld_off    = static_cast<std::size_t>(orig[n - suffix_n].data() - host.data());

        result.top_level_domain = host.substr(tld_off);
        result.domain           = host.substr(domain_off, orig[domain_label].size());
        result.subdomain        = (domain_label == 0) ? std::string_view{} : host.substr(0, domain_off - 1);
        result.ok = true;
        return result;
    }

    // the lazily-loaded singleton
    const psl_list& the_psl() {
        static const psl_list list = [] {
            psl_list l;
            // l.load_from_file(PSL_PATH);
            l.load_built_in();
            return l;
        }();
        return list;
    }

}




requests::Url& requests::Url::reset(std::string_view& the_view) {
    the_view = std::string_view();
    return *this;
}

requests::Url& requests::Url::reset_all(const bool raw) {
    if (raw) this->raw_url_ = "";
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
            // std::string_view complete_domain = { matches[THE_DOMAIN].first, matches[THE_DOMAIN].second};
            // const std::regex domain_pattern(R"regex(^([^.]+)\.([^.]+)\.(.+)$)regex", std::regex_constants::icase);
            // std::match_results<std::string_view::const_iterator> domain_matches;
            // // std::string_view this_domain = {matches[THE_DOMAIN].first, matches[THE_DOMAIN].second};
            // if (std::regex_search(complete_domain.begin(), complete_domain.end(), domain_matches, domain_pattern)) {

            //     if (domain_matches[1].matched) this->subdomain_ = { domain_matches[1].first, domain_matches[1].second};

            //     if (domain_matches[2].matched) this->domain_ = { domain_matches[2].first, domain_matches[2].second};

            //     if (domain_matches[3].matched) this->top_level_domain_ = { domain_matches[3].first, domain_matches[3].second};
            // }
            // else this->domain_ = complete_domain;
            std::string_view complete_domain = { matches[THE_DOMAIN].first, matches[THE_DOMAIN].second };
            const host_parts parts = split_host(the_psl(), complete_domain);
            if (parts.ok) {
                this->subdomain_        = parts.subdomain;
                this->domain_           = parts.domain;
                this->top_level_domain_ = parts.top_level_domain;
            }
            else {
                this->domain_ = complete_domain;   // localhost, bare TLDs, single-label hosts
            }
        }

        if (matches[THE_PORT].matched) this->port_ = { matches[THE_PORT].first, matches[THE_PORT].second};

        if (matches[THE_PATH].matched) this->path_ = { matches[THE_PATH].first, matches[THE_PATH].second};

        if (matches[THE_QUERY].matched) {
            this->query_ = { matches[THE_QUERY].first, matches[THE_QUERY].second};
            const std::string query(this->query_);
            const char delim = '&';
            std::string line;
            std::stringstream stream(query);
            while (std::getline(stream, line, delim)) {
                
                const std::size_t delim_index = string_functions::index_of(line, '=');
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
    this->parse();
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
    this->parse();
    return *this;
}

requests::Url& requests::Url::operator=(std::string_view other) {
    if (string_functions::same_string(this->raw_url_, other, false)) return *this;
    this->raw_url_.append(other.begin(), other.end());
    this->parse();
    return *this;
}

requests::Url& requests::Url::operator()(std::string_view other) {
    if (string_functions::same_string(this->raw_url_, other, false)) return *this;
    this->raw_url_.append(other.begin(), other.end());
    this->parse();
    return *this;
}

requests::Url::operator std::string_view() const {
    return this->raw_url_;
}

requests::Url::operator bool() const {
    return not this->raw_url_.empty();
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