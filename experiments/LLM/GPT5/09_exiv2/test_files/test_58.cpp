#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include "exiv2/error.hpp"

// Test case for toBasicString

// Test the basic string conversion from integer
TEST_F(ToBasicStringTest_58, IntegerConversion_58) {
    int input = 123;
    std::string result = Exiv2::toBasicString<char>(input);
    EXPECT_EQ(result, "123");  // Check if the result matches the expected string
}

// Test the basic string conversion from floating-point
TEST_F(ToBasicStringTest_58, FloatConversion_58) {
    float input = 3.14159;
    std::string result = Exiv2::toBasicString<char>(input);
    EXPECT_EQ(result, "3.14159");  // Check if the result matches the expected string
}

// Test the basic string conversion from string
TEST_F(ToBasicStringTest_58, StringConversion_58) {
    std::string input = "Hello, World!";
    std::string result = Exiv2::toBasicString<char>(input);
    EXPECT_EQ(result, "Hello, World!");  // Check if the result matches the expected string
}

// Test the basic string conversion for an empty input
TEST_F(ToBasicStringTest_58, EmptyStringConversion_58) {
    std::string input = "";
    std::string result = Exiv2::toBasicString<char>(input);
    EXPECT_EQ(result, "");  // Check if the result matches the expected string (empty string)
}

// Test the basic string conversion from a boolean
TEST_F(ToBasicStringTest_58, BooleanConversion_58) {
    bool input = true;
    std::string result = Exiv2::toBasicString<char>(input);
    EXPECT_EQ(result, "1");  // Check if the result is "1" for true

    input = false;
    result = Exiv2::toBasicString<char>(input);
    EXPECT_EQ(result, "0");  // Check if the result is "0" for false
}

// Test the basic string conversion for a custom class (non-trivial type)
struct CustomType {
    int a;
    std::string b;
};

std::ostream& operator<<(std::ostream& os, const CustomType& obj) {
    os << obj.a << "-" << obj.b;
    return os;
}

TEST_F(ToBasicStringTest_58, CustomTypeConversion_58) {
    CustomType input{42, "Test"};
    std::string result = Exiv2::toBasicString<char>(input);
    EXPECT_EQ(result, "42-Test");  // Check if the result matches the expected string
}

// Test case to check the exceptional behavior when an invalid type is passed
TEST_F(ToBasicStringTest_58, InvalidConversion_58) {
    // Using a type that doesn't have a meaningful stream insertion operator
    // This test is not directly applicable for 'toBasicString', as it expects streamable types.
    // But, if such behavior was expected, we could check for exceptions (if the implementation supported it).
    // For now, we skip the actual test for non-streamable types.
    EXPECT_THROW({
        // Logic for exception handling would go here, but this is just a placeholder
        std::stringstream ss;
        ss << std::vector<int>{1, 2, 3}; // std::vector does not support direct string conversion
    }, std::exception);  // Expected exception (this can be replaced with a more specific exception type if needed)
}