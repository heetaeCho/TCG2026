#include <gtest/gtest.h>
#include "helper_functions.h"  // Include the header file for the function

// Test suite for the string_from_unterminated function
TEST_F(StringFromUnterminatedTest_115, HandlesEmptyData_115) {
    const char* data = "";
    size_t data_length = 0;

    // Test: When data_length is 0, the result should be an empty string
    std::string result = string_from_unterminated(data, data_length);

    EXPECT_EQ(result, "");
}

TEST_F(StringFromUnterminatedTest_115, HandlesNonEmptyDataWithinLength_115) {
    const char* data = "Hello, World!";
    size_t data_length = 15;  // Longer than the actual string

    // Test: When the data length is longer than the actual string, it should still return the correct string
    std::string result = string_from_unterminated(data, data_length);

    EXPECT_EQ(result, "Hello, World!");
}

TEST_F(StringFromUnterminatedTest_115, HandlesDataWithTruncation_115) {
    const char* data = "Hello, World!";
    size_t data_length = 5;  // Shorter than the actual string

    // Test: When the data length is shorter than the actual string, it should truncate and return "Hello"
    std::string result = string_from_unterminated(data, data_length);

    EXPECT_EQ(result, "Hello");
}

TEST_F(StringFromUnterminatedTest_115, HandlesNullPointer_115) {
    const char* data = nullptr;
    size_t data_length = 10;

    // Test: When data is a null pointer, the function should return an empty string
    std::string result = string_from_unterminated(data, data_length);

    EXPECT_EQ(result, "");
}

TEST_F(StringFromUnterminatedTest_115, HandlesZeroLength_115) {
    const char* data = "NonEmptyString";
    size_t data_length = 0;

    // Test: When data_length is 0, the function should return an empty string
    std::string result = string_from_unterminated(data, data_length);

    EXPECT_EQ(result, "");
}

TEST_F(StringFromUnterminatedTest_115, HandlesMaxLength_115) {
    const char* data = "MaxLengthTest";
    size_t data_length = strnlen(data, 50);  // Assuming data_length is within a max size limit

    // Test: Function should work normally for a string of maximum valid length
    std::string result = string_from_unterminated(data, data_length);

    EXPECT_EQ(result, "MaxLengthTest");
}