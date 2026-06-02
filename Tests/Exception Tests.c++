


#include <Request Exceptions>



#include <gtest/gtest.h>






TEST(Exception_Tests, illegal_url) {

    const std::string test_string = "Oh the mouth of the river...";
    const requests::illegal_url_exception except =  requests::illegal_url_exception(test_string);

    try {
        throw except;
    }

    catch (requests::Exception& exception) {
        ASSERT_EQ(except.exception_type(), exception.exception_type()) << "The type should have been the same, but it wasn't" << std::endl;
        ASSERT_EQ(except.message(), exception.message()) << "The message should have been the same, but it wasn't" << std::endl;
        ASSERT_EQ(exception.message().length(), std::strlen(exception.what())) << "The length of the exception's message is not equal to what it should be" << std::endl;
        ASSERT_FALSE(not std::strlen(exception.what())) << "the length of the what() is empty, but it shouldn't be" << std::endl;
        ASSERT_STREQ(except.what(), exception.what()) << "The what() should have been the same, but it wasn't" << std::endl;
    }

}

