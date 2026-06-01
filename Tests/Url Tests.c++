



#include <Hosts>
#include <Network Headers>
#include <String Functions>
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
    ASSERT_FALSE(url.domain().empty()) << "The parsed url of \"" << yout << "\" should have a non-empty domain, but it does" << std::endl;
    ASSERT_EQ("www", url.subdomain()) << "The subdomain of the url \"" << yout << "\" should be \"" << yout.substr(0, 3) << "\" but instead it is \"" << url.subdomain() << "\"" << std::endl;
    ASSERT_EQ("youtube", url.domain()) << "The domain itself didn't resolve to the expected 'youtube'. Instead it was \"" << url.domain() << "\"" << std::endl;
    ASSERT_EQ("com", url.top_level_domain()) << "The top level domain didn't resolve to 'com' as was expected. Instead it was \"" << url.top_level_domain() << "\"" << std::endl;

}


TEST(Url_Tests, exotic_urls) {
    const std::string example = "https://www.example.co.uk";

    const requests::Url url = example;
    ASSERT_FALSE(url.domain().empty()) << "The parsed url of \"" << example << "\" should have a non-empty domain, but it doesn't" << std::endl;
    ASSERT_TRUE(string_functions::same_string("www", url.subdomain(), false)) << "The subdomain should have evalauted to \"www\" but instead it evaluated to \"" << url.subdomain() << "\"" << std::endl;
    ASSERT_TRUE(string_functions::same_string("example", url.domain(), false)) << "The domain should have evaluated to \"example\", but instead it evaluated to \"" << url.domain() << "\"" << std::endl;
    ASSERT_TRUE(string_functions::same_string("co.uk", url.top_level_domain(), false)) << "The top level domain should have evalauted to \"co.uk\", but instead it evaluated to \""  << url.top_level_domain() << "\"" << std::endl;
}