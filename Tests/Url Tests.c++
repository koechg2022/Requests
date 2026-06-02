



#include <Request Exceptions>
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
    ASSERT_TRUE(string_functions::same_string("domain", url.domain())) << "The domain should have been \"domain\", but instead it was \"" << url.domain() << "\"" << std::endl;

    url = "https://www.example.co.uk";
    ASSERT_TRUE(url.username().empty()) << "There is no authority here, so the username should be empty, but it's \"" << url.username() << "\"" << std::endl;
    ASSERT_TRUE(url.password().empty()) << "There is no authority here, so the password should be empty, but it's \"" << url.password() << "\"" << std::endl;

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

    ASSERT_FALSE(url.query().empty()) << "The query should exist, but it's registering as empty" << std::endl;
    ASSERT_TRUE(string_functions::same_string("q=hello&lang=en", url.query())) << "The raw query should have been \"q=hello&lang=en\", but instead it was \"" << url.query() << "\"" << std::endl;

    ASSERT_EQ(2u, url.queries().size()) << "There should be 2 parsed query pairs, but instead there were " << url.queries().size() << std::endl;
    ASSERT_TRUE(url.queries().contains("q")) << "The parsed queries should contain the key \"q\", but it doesn't" << std::endl;
    ASSERT_EQ("hello", url.queries().at("q").get<std::string>()) << "The value for \"q\" should have been \"hello\", but instead it was \"" << url.queries().at("q").get<std::string>() << "\"" << std::endl;
    ASSERT_TRUE(url.queries().contains("lang")) << "The parsed queries should contain the key \"lang\", but it doesn't" << std::endl;
    ASSERT_EQ("en", url.queries().at("lang").get<std::string>()) << "The value for \"lang\" should have been \"en\", but instead it was \"" << url.queries().at("lang").get<std::string>() << "\"" << std::endl;

    url = "https://www.example.com/search?q=hello&lang=en#results";
    ASSERT_TRUE(string_functions::same_string("q=hello&lang=en", url.query())) << "With a fragment present, the query should still be \"q=hello&lang=en\", but instead it was \"" << url.query() << "\"" << std::endl;
    ASSERT_EQ("hello", url.queries()["q"]) << "The queries should have a value of \"hello\" associated with the key value of \"q\"" << std::endl;
    ASSERT_EQ("hello", url["q"]) << "The queries should have a value of \"hello\" associated with the key value of \"q\"" << std::endl;
    ASSERT_EQ("en", url.queries()["lang"]) << "The language should be \"en\", but instead it was \"" << url.queries()["lang"] << "\"" << std::endl;


    url = "https://www.example.com/";
    ASSERT_TRUE(url.query().empty()) << "There is no query here, so it should be empty, but it's \"" << url.query() << "\"" << std::endl;
    ASSERT_TRUE(url.queries().empty()) << "There is no query here, so the parsed map should be empty, but it has " << url.queries().size() << " entries" << std::endl;

    ASSERT_THROW(url = "https://www.example.com/search?q&msg=hello%20world", requests::illegal_url_exception);
}

TEST(Url_Tests, fragments) {
    requests::Url url = "https://www.example.com/page#section2";

    ASSERT_FALSE(url.fragment().empty()) << "The fragment should exist, but it's registering as empty" << std::endl;
    ASSERT_EQ("section2", url.fragment()) << "The fragment should have been \"section2\", but instead it was \"" << url.fragment() << "\"" << std::endl;

    url = "https://www.example.com/search?q=hello#results";
    ASSERT_EQ("results", url.fragment()) << "The fragment should have been \"results\", but instead it was \"" << url.fragment() << "\"" << std::endl;

    url = "https://www.example.com#top";
    ASSERT_EQ("top", url.fragment()) << "The fragment should have been \"top\", but instead it was \"" << url.fragment() << "\"" << std::endl;
    ASSERT_EQ("/", url.path()) << "With no path but a fragment, the path should default to \"/\", but instead it was \"" << url.path() << "\"" << std::endl;

    url = "https://www.example.com/page";
    ASSERT_TRUE(url.fragment().empty()) << "There is no fragment here, so it should be empty, but it's \"" << url.fragment() << "\"" << std::endl;
}

TEST(Url_Tests, hashing) {
    const requests::Url example = "https://www.example.com/page#section2";
    const requests::Url imdb = "https://www.imdb.com/fr/name/nm3220744/";

    ASSERT_NE(example.hash(), imdb.hash()) << "The hashes of the two different urls should be different, but they are not evaluating to different hashes" << std::endl;
    ASSERT_EQ(std::hash<requests::Url>{}(example), example.hash()) << "The hashing function and the hashing method should evaluate to the same thing, but they aren't" << std::endl;
    ASSERT_EQ(std::hash<requests::Url>{}(imdb), imdb.hash()) << "The hashing function and the hashing method should evaluate to the same thing, but they aren't" << std::endl;

}

TEST(Url_Tests, url_user_overloads) {
    const requests::Url imdb = "https://www.imdb.com/fr/name/nm3220744/";
    std::string_view msg = imdb;
    ASSERT_EQ(msg, imdb.url()) << "The extracted url and the url retrived from the url itself are not the same even though they should be" << std::endl;
    const requests::Url other_imdb = imdb;
    const requests::Url third_imdb = "https://www.imdb.com/fr/name/nm3220744/";
    ASSERT_EQ(imdb, imdb) << "The imdb being compared to itself is not the same thing" << std::endl;
    ASSERT_EQ(imdb, other_imdb) << "The imdb set by assignment of the original is not the same as the original. That shouldn't be the case" << std::endl;
    ASSERT_EQ(imdb.url(), other_imdb.url()) << "The urls of the imdb that was set via the assignment of the original imdb is not set" << std::endl;

    const requests::Url copy_source = "https://www.example.com";
    requests::Url copy_target = "http://other.org";
    copy_target = copy_source;
    ASSERT_EQ(copy_target.domain(), "example");
}

TEST(Url_Tests, hostless_and_bare_suffix) {
    requests::Url local = "http://localhost";
    ASSERT_EQ(local.domain(), "localhost");
    ASSERT_EQ(local.top_level_domain(), "");
    ASSERT_EQ(local.usable_domain(), "localhost");
    requests::Url suffix = "https://co.uk";
    ASSERT_EQ(suffix.domain(), "co.uk");
}

TEST(Url_Tests, copy_and_move_semantics) {
    requests::Url original = "https://www.example.com/path?k=v#frag";

    requests::Url copy = original;
    ASSERT_EQ(copy.subdomain(), "www");
    ASSERT_EQ(copy.domain(), "example");
    ASSERT_EQ(original.domain(), "example");
    requests::Url copy_target = "http://other.org";
    copy_target = original;
    ASSERT_EQ(copy_target.domain(), "example");

    requests::Url moved = std::move(original);
    ASSERT_EQ(moved.domain(), "example");
    ASSERT_TRUE(original.empty());

    requests::Url move_target = "http://other.org";
    requests::Url move_source = "https://api.example.com";
    move_target = std::move(move_source);
    ASSERT_EQ(move_target.subdomain(), "api");
    ASSERT_TRUE(move_source.empty());
}

TEST(Url_Tests, self_assignment_and_moved_from) {
    requests::Url a = "https://www.example.com";

    const requests::Url& self = a;
    a = self;
    ASSERT_EQ(a.domain(), "example");

    requests::Url* alias = &a;
    a = *alias;
    ASSERT_EQ(a.domain(), "example");
    a = std::move(*alias);
    ASSERT_EQ(a.domain(), "example");

    requests::Url b = std::move(a);
    requests::Url c = std::move(a);
    ASSERT_TRUE(c.empty());

    requests::Url d = "http://x.org";
    d = std::move(a);
    ASSERT_TRUE(d.empty());
}

TEST(Exception_Tests, unsupported_and_empty_url) {
    requests::unsupported u("nope");
    ASSERT_EQ(u.exception_type(), "unsupported");
    ASSERT_EQ(u.message(), "nope");
    ASSERT_STREQ(u.what(), "nope");

    requests::empty_url e;
    ASSERT_EQ(e.exception_type(), "empty_url");
    ASSERT_EQ(e.message(), "Empty url passed in");
    ASSERT_FALSE(not std::strlen(e.what()));
}

TEST(Url_Tests, psl_wildcard_and_exception) {
    requests::Url wild = "http://blog.foo.ck";   // matches *.ck wildcard rule
    ASSERT_EQ(wild.domain(), "blog");
    ASSERT_EQ(wild.top_level_domain(), "foo.ck");

    requests::Url exc = "http://www.ck";          // !www.ck exception rule
    ASSERT_EQ(exc.domain(), "www");
    ASSERT_EQ(exc.top_level_domain(), "ck");
}

TEST(Url_Tests, empty_url_and_missing_query_key) {
    ASSERT_THROW(requests::Url e = "", requests::empty_url);   // parse() empty-guard throw

    requests::Url u = "http://x.com/?a=1";
    ASSERT_EQ(u["missing"], "");                  // operator[] not-found path
}


TEST(Url_Tests, non_matching_input) {
    requests::Url u = "/";        // fails the URL grammar -> regex_search returns false
    ASSERT_EQ(u.scheme(), "");
    ASSERT_EQ(u.domain(), "");
    ASSERT_EQ(u.path(), "");      // the else-branch path "/" sits inside the matched block, so it's skipped
    ASSERT_FALSE(u.empty());      // empty() reflects raw_url_, which is "/"
}

TEST(Url_Tests, psl_internal_paths) {
    requests::detail::psl_list p;
    p.load_from_text("  !x.example  \r\n  *.example  \r\n");
    ASSERT_TRUE(p.has_exception("x.example"));
    ASSERT_TRUE(p.has_rule("*.example"));
    ASSERT_FALSE(requests::detail::split_host(p, "").ok);
    requests::Url u = "localhost";
    u.usable_domain();
}

TEST(Url_Tests, assign_same_value_short_circuit) {
    requests::Url u = "https://www.example.com";
    u = "https://www.example.com";
    std::string s = "https://www.example.com";
    u = s;
    u = std::string_view("https://www.example.com");
    requests::Url v = "https://www.example.com";
    u = v;
    ASSERT_EQ(u.domain(), "example");
}

// Add this test to Tests/Url Tests.c++

TEST(Url_Tests, branch_coverage_additions) {
    requests::Url a = "http://user@host.com";
    ASSERT_TRUE(a.username().empty());
    requests::Url b = "http://user:pw@host.com";
    ASSERT_EQ(b.username(), "user");

    requests::Url c = "/";
    ASSERT_EQ(c.usable_domain(), "");
    requests::Url d = "https://www.example.com";
    ASSERT_EQ(d.usable_domain(), "example.com");

    requests::Url e = "http://a.b.ocs.customer-oci.com";
    ASSERT_FALSE(e.domain().empty());

    requests::Url f = "https://www.example.com";
    f = "https://www.example.com";
    ASSERT_EQ(f.domain(), "example");
    f = "https://www.other.org";
    ASSERT_EQ(f.domain(), "other");
}