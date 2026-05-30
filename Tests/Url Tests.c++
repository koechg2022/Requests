


#include <Hosts>
#include <Network Headers>



#include <gtest/gtest.h>









class Url_Tests : public ::testing::Test {

    protected:

        static void SetUpTestSuite() {
            ASSERT_TRUE(networking::initialize()) << "Did not successfully initialize the non-secure networking libraru" << std::endl;
        }
        static void TearDownTestSuite() {
            ASSERT_TRUE(networking::uninitialize()) << "Did not successfully uninitialize the non-secure networking library" << std::endl;
        }

};




TEST_F(Url_Tests, create_url) {
    ASSERT_TRUE(true);
}