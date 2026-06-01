



#include <String Functions>
#include <Url>



#include <gtest/gtest.h>











TEST(Url_Tests, schemes) {
    
    requests::Url example = "scheme://user:pass@domain.com/path";
    ASSERT_FALSE(example.scheme().empty()) << "The scheme should exist, but apparenly it doesn't." << std::endl;
    ASSERT_EQ("scheme", example.scheme()) << "The scheme should have been \"scheme\", but instead it is \"" << example.scheme() << "\"" << std::endl;
    example = "https://www.example.co.uk";
    ASSERT_EQ("https", example.scheme()) << "The new scheme should be \"https\", but instead it is \"" << example.scheme() << "\"" << std::endl;
    example = "example.com";
    ASSERT_TRUE(example.scheme().empty()) << "The example url's scheme should be empty, but it's \"" << example.scheme() << "\" instead. That's not kosher" << std::endl;
    
    example = "ssh://example.com";
    ASSERT_FALSE(example.scheme().empty()) << "The example url's scheme should not be empty, but it is. That's not kosher" << std::endl;
    ASSERT_EQ("ssh", example.scheme()) << "The scheme should be \"ssh\", but instead it is \"" << example.scheme() << "\"" << std::endl;
}

TEST(Url_Tests, authority) {
    requests::Url url = "scheme://user:pass@domain.com/path";
    ASSERT_FALSE(url.username().empty()) << "The username should exist, but it's registering as empty" << std::endl;
    ASSERT_TRUE(string_functions::same_string("user", url.username())) << "The username should have been \"user\", but instead it was \"" << url.username() << "\"" << std::endl;
    ASSERT_FALSE(url.password().empty()) << "The password should exist, but it's registering as empty" << std::endl;
    ASSERT_TRUE(string_functions::same_string("pass", url.password())) << "The password should have been \"pass\", but instead it was \"" << url.password() << "\"" << std::endl;
    // the authority must not bleed into the host
    ASSERT_TRUE(string_functions::same_string("domain", url.domain())) << "The domain should have been \"domain\", but instead it was \"" << url.domain() << "\"" << std::endl;

    // no authority -> both fields empty
    url = "https://www.example.co.uk";
    ASSERT_TRUE(url.username().empty()) << "There is no authority here, so the username should be empty, but it's \"" << url.username() << "\"" << std::endl;
    ASSERT_TRUE(url.password().empty()) << "There is no authority here, so the password should be empty, but it's \"" << url.password() << "\"" << std::endl;

    // authority with a port following it
    url = "ftp://admin:secret@files.example.com:21/";
    ASSERT_TRUE(string_functions::same_string("admin", url.username())) << "The username should have been \"admin\", but instead it was \"" << url.username() << "\"" << std::endl;
    ASSERT_TRUE(string_functions::same_string("secret", url.password())) << "The password should have been \"secret\", but instead it was \"" << url.password() << "\"" << std::endl;
    ASSERT_TRUE(string_functions::same_string("21", url.port())) << "The port should have been \"21\", but instead it was \"" << url.port() << "\"" << std::endl;

    url = "ftp://admin:@tester.com";
    ASSERT_FALSE(url.username().empty()) << "The username passed in should not be empty, but it is" << std::endl;
    ASSERT_TRUE(url.password().empty()) << "The password passed in should be empty, but it's not. Instead it is \"" << url.password() << "\"" << std::endl;
    ASSERT_EQ("admin", url.username()) << "The admin should be equal to \"admin\", but instead it is \"" << url.username() << "\"" << std::endl;

    url = "ftp://:passphrase@testingpro.co.uk";
    ASSERT_TRUE(url.username().empty()) << "The username passed in should be empty, but instead it is \"" << url.username() << "\"" << std::endl;
    ASSERT_FALSE(url.password().empty()) << "The password should not be empty, but they are." << std::endl;
    ASSERT_EQ("passphrase", url.password()) << "The password should be \"passphrase\", but instead it is \"" << url.password() << "\"" << std::endl;
}

TEST(Url_Tests, domain) {
    
    const std::string exp = "www.example.com";
    const std::string yout = "www.youtube.com";

    requests::Url url(exp);
    ASSERT_FALSE(url.domain().empty()) << "The parsed url of \"" << exp << "\" should have a non-empty domain, but it doesn't" << std::endl;
    ASSERT_EQ("www", url.subdomain()) << "The subdomain of the url \"" << exp << "\" should be \"" << exp.substr(0, 3) << "\" but instead it is \"" << url.subdomain() << "\"" << std::endl;
    ASSERT_EQ("example", url.domain()) << "The domain itself didn't resolve to the expected 'example'. Instead it was \"" << url.domain() << "\"" << std::endl;
    ASSERT_EQ("com", url.top_level_domain()) << "The top level domain didn't resolve to 'com' as was expected. Instead it was \"" << url.top_level_domain() << "\"" << std::endl;
    url = yout;
    ASSERT_FALSE(url.domain().empty()) << "The parsed url of \"" << yout << "\" should have a non-empty domain, but it does" << std::endl;
    ASSERT_EQ("www", url.subdomain()) << "The subdomain of the url \"" << yout << "\" should be \"" << yout.substr(0, 3) << "\" but instead it is \"" << url.subdomain() << "\"" << std::endl;
    ASSERT_EQ("youtube", url.domain()) << "The domain itself didn't resolve to the expected 'youtube'. Instead it was \"" << url.domain() << "\"" << std::endl;
    ASSERT_EQ("com", url.top_level_domain()) << "The top level domain didn't resolve to 'com' as was expected. Instead it was \"" << url.top_level_domain() << "\"" << std::endl;

}

TEST(Url_Tests, domain_two) {
    const std::string example = "https://www.example.co.uk";

    const requests::Url url = example;
    ASSERT_FALSE(url.domain().empty()) << "The parsed url of \"" << example << "\" should have a non-empty domain, but it doesn't" << std::endl;
    ASSERT_TRUE(string_functions::same_string("www", url.subdomain(), false)) << "The subdomain should have evalauted to \"www\" but instead it evaluated to \"" << url.subdomain() << "\"" << std::endl;
    ASSERT_TRUE(string_functions::same_string("example", url.domain(), false)) << "The domain should have evaluated to \"example\", but instead it evaluated to \"" << url.domain() << "\"" << std::endl;
    ASSERT_TRUE(string_functions::same_string("co.uk", url.top_level_domain(), false)) << "The top level domain should have evalauted to \"co.uk\", but instead it evaluated to \""  << url.top_level_domain() << "\"" << std::endl;
    ASSERT_TRUE(string_functions::same_string("https", url.scheme())) << "The scheme should be \"https\", but instead it's \"" << url.scheme() << "\"" << std::endl;
    ASSERT_TRUE(string_functions::same_string("example.co.uk", url.usable_domain())) << "The usable domain should have been \"example.co.uk\", but instead it was \"" << url.usable_domain() << "\"" << std::endl;
}

TEST(Url_Tests, paths) {
    requests::Url url = "https://www.imdb.com/fr/name/nm3220744/";
    ASSERT_FALSE(url.empty());
    ASSERT_TRUE(url);
    ASSERT_TRUE(string_functions::same_string("https", url.scheme())) << "The scheme for the url was supposed to be \"https\" but instead it is \"" << url.scheme() << "\"" << std::endl;
    ASSERT_TRUE(string_functions::same_string("www", url.subdomain())) << "The subdomain should have been \"www\", but instead it was \"" << url.subdomain() << "\"" << std::endl;
    ASSERT_TRUE(string_functions::same_string("imdb", url.domain())) << "The domain should have beem \"imdb\", but instead was \"" << url.domain() << "\"" << std::endl;
    ASSERT_TRUE(string_functions::same_string("com", url.top_level_domain())) << "The top level domain should be \"com\", but instead it was \"" << url.top_level_domain() << "\"" << std::endl;
    ASSERT_TRUE(string_functions::same_string("/fr/name/nm3220744/", url.path())) << "The path should have been \"fr/name/nm3220744/\", but instead it was \"" << url.path() << "\"" << std::endl;
    url = "https://www.imdb.com/";
    ASSERT_FALSE(url.path().empty()) << "The path should not be empty, but it's registering as empty" << std::endl;
    url = "https://www.imdb.com";
    ASSERT_EQ("/", url.path()) << "The path should be \"/\", because no path was passed into the original url, but it wasn't. Instead it is \"" << url.path() << "\"" << std::endl;
}

TEST(Url_Tests, queries) {
    requests::Url url = "https://www.example.com/search?q=hello&lang=en";

    // the raw query string, no leading '?'
    ASSERT_FALSE(url.query().empty()) << "The query should exist, but it's registering as empty" << std::endl;
    ASSERT_TRUE(string_functions::same_string("q=hello&lang=en", url.query())) << "The raw query should have been \"q=hello&lang=en\", but instead it was \"" << url.query() << "\"" << std::endl;

    // the parsed key/value map
    ASSERT_EQ(2u, url.queries().size()) << "There should be 2 parsed query pairs, but instead there were " << url.queries().size() << std::endl;
    ASSERT_TRUE(url.queries().contains("q")) << "The parsed queries should contain the key \"q\", but it doesn't" << std::endl;
    ASSERT_EQ("hello", url.queries().at("q").get<std::string>()) << "The value for \"q\" should have been \"hello\", but instead it was \"" << url.queries().at("q").get<std::string>() << "\"" << std::endl;
    ASSERT_TRUE(url.queries().contains("lang")) << "The parsed queries should contain the key \"lang\", but it doesn't" << std::endl;
    ASSERT_EQ("en", url.queries().at("lang").get<std::string>()) << "The value for \"lang\" should have been \"en\", but instead it was \"" << url.queries().at("lang").get<std::string>() << "\"" << std::endl;

    // query coexisting with a fragment: query must stop at the '#'
    url = "https://www.example.com/search?q=hello&lang=en#results";
    ASSERT_TRUE(string_functions::same_string("q=hello&lang=en", url.query())) << "With a fragment present, the query should still be \"q=hello&lang=en\", but instead it was \"" << url.query() << "\"" << std::endl;

    // no query -> empty, and nothing parsed
    url = "https://www.example.com/";
    ASSERT_TRUE(url.query().empty()) << "There is no query here, so it should be empty, but it's \"" << url.query() << "\"" << std::endl;
    ASSERT_TRUE(url.queries().empty()) << "There is no query here, so the parsed map should be empty, but it has " << url.queries().size() << " entries" << std::endl;
}

TEST(Url_Tests, fragments) {
    requests::Url url = "https://www.example.com/page#section2";

    // the fragment, no leading '#'
    ASSERT_FALSE(url.fragment().empty()) << "The fragment should exist, but it's registering as empty" << std::endl;
    ASSERT_TRUE(string_functions::same_string("section2", url.fragment())) << "The fragment should have been \"section2\", but instead it was \"" << url.fragment() << "\"" << std::endl;

    // fragment after a query
    url = "https://www.example.com/search?q=hello#results";
    ASSERT_TRUE(string_functions::same_string("results", url.fragment())) << "The fragment should have been \"results\", but instead it was \"" << url.fragment() << "\"" << std::endl;

    // fragment directly after the host, no path given -> path defaults to "/", fragment still parses
    url = "https://www.example.com#top";
    ASSERT_TRUE(string_functions::same_string("top", url.fragment())) << "The fragment should have been \"top\", but instead it was \"" << url.fragment() << "\"" << std::endl;
    ASSERT_EQ("/", url.path()) << "With no path but a fragment, the path should default to \"/\", but instead it was \"" << url.path() << "\"" << std::endl;

    // no fragment -> empty
    url = "https://www.example.com/page";
    ASSERT_TRUE(url.fragment().empty()) << "There is no fragment here, so it should be empty, but it's \"" << url.fragment() << "\"" << std::endl;
}