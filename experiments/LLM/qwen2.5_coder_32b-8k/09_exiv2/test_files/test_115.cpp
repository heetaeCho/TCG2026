#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>



// Assuming the function to be tested is in a header file named helper_functions.hpp

#include "helper_functions.hpp"



class StringFromUnterminatedTest : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(StringFromUnterminatedTest, NormalOperation_115) {

    const char* data = "Hello";

    size_t data_length = 6; // Includes null terminator

    std::string result = string_from_unterminated(data, data_length);

    EXPECT_EQ(result, "Hello");

}



TEST_F(StringFromUnterminatedTest, UnterminatedString_115) {

    const char* data = "HelloWorld";

    size_t data_length = 5; // Does not include null terminator

    std::string result = string_from_unterminated(data, data_length);

    EXPECT_EQ(result, "Hello");

}



TEST_F(StringFromUnterminatedTest, ZeroLength_115) {

    const char* data = "";

    size_t data_length = 0;

    std::string result = string_from_unterminated(data, data_length);

    EXPECT_TRUE(result.empty());

}



TEST_F(StringFromUnterminatedTest, EmptyString_115) {

    const char* data = "";

    size_t data_length = 1; // Includes null terminator

    std::string result = string_from_unterminated(data, data_length);

    EXPECT_TRUE(result.empty());

}



TEST_F(StringFromUnterminatedTest, LongString_115) {

    const char* data = "ThisIsALongStringThatShouldBeHandledCorrectly";

    size_t data_length = 40; // Includes null terminator

    std::string result = string_from_unterminated(data, data_length);

    EXPECT_EQ(result, "ThisIsALongStringThatShouldBeHandledCorrectly");

}



TEST_F(StringFromUnterminatedTest, LongStringTruncated_115) {

    const char* data = "ThisIsALongStringThatShouldBeTruncated";

    size_t data_length = 20; // Does not include null terminator

    std::string result = string_from_unterminated(data, data_length);

    EXPECT_EQ(result, "ThisIsALongStrin");

}
