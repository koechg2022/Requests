



#include <Hosts>
#include <Network Headers>
#include <Url>



#include <gtest/gtest.h>










TEST(Url_Tests, create_url) {
    ASSERT_TRUE(true);
    const std::string exp = "www.example.com";
    const std::string yout = "www.youtube.com";

    requests::Url url(exp);
    ASSERT_FALSE(url.domain().empty()) << "The parsed url of \"" << exp << "\" should have a non-empty domain, but it doesn't" << std::endl;
    ASSERT_EQ("www", url.subdomain()) << "The subdomain of the url \"" << exp << "\" should be \"" << exp.substr(0, 3) << "\" but instead it is \"" << url.subdomain() << "\"" << std::endl;
    ASSERT_EQ("example", url.domain()) << "The domain itself didn't resolve to the expected 'example'. Instead it was \"" << url.domain() << "\"" << std::endl;
    ASSERT_EQ("com", url.top_level_domain()) << "The top level domain didn't resolve to 'com' as was expected. Instead it was \"" << url.top_level_domain() << "\"" << std::endl;
    url = yout;
    ASSERT_FALSE(url.domain().empty()) << "The parsed url of \"" << exp << "\" should have a non-empty domain, but it does" << std::endl;

}


TEST(Url_Tests, uk_urls) {
    const std::string example = "https://www.example.co.uk";

    const requests::Url url(example);
    ASSERT_FALSE(url.domain().empty()) << "The parsed url of \"" << example << "\" should have a non-empty domain, but it doesn't" << std::endl;
    ASSERT_EQ("www", url.subdomain());
}