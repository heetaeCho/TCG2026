#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <type_traits>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// Test basic integer stringification
TEST(CatchStringifyTest_79, StringifyInt_79) {
    int value = 42;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, "42");
}

TEST(CatchStringifyTest_79, StringifyZero_79) {
    int value = 0;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, "0");
}

TEST(CatchStringifyTest_79, StringifyNegativeInt_79) {
    int value = -123;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, "-123");
}

// Test boolean stringification
TEST(CatchStringifyTest_79, StringifyTrue_79) {
    bool value = true;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, "true");
}

TEST(CatchStringifyTest_79, StringifyFalse_79) {
    bool value = false;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, "false");
}

// Test string stringification
TEST(CatchStringifyTest_79, StringifyStdString_79) {
    std::string value = "hello";
    std::string result = Catch::Detail::stringify(value);
    // Catch typically wraps strings in quotes
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST(CatchStringifyTest_79, StringifyEmptyString_79) {
    std::string value = "";
    std::string result = Catch::Detail::stringify(value);
    // Result should represent an empty string somehow
    EXPECT_FALSE(result.empty());
}

// Test const reference handling (cv qualifiers stripped)
TEST(CatchStringifyTest_79, StringifyConstInt_79) {
    const int value = 99;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, "99");
}

TEST(CatchStringifyTest_79, StringifyConstRefInt_79) {
    int x = 77;
    const int& value = x;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, "77");
}

// Test floating point stringification
TEST(CatchStringifyTest_79, StringifyDouble_79) {
    double value = 3.14;
    std::string result = Catch::Detail::stringify(value);
    // Should contain "3.14" somewhere
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST(CatchStringifyTest_79, StringifyFloat_79) {
    float value = 1.5f;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

// Test char stringification
TEST(CatchStringifyTest_79, StringifyChar_79) {
    char value = 'A';
    std::string result = Catch::Detail::stringify(value);
    EXPECT_NE(result.find("A"), std::string::npos);
}

// Test unsigned int
TEST(CatchStringifyTest_79, StringifyUnsignedInt_79) {
    unsigned int value = 42u;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, "42");
}

// Test long long
TEST(CatchStringifyTest_79, StringifyLongLong_79) {
    long long value = 9999999999LL;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, "9999999999");
}

// Test boundary values
TEST(CatchStringifyTest_79, StringifyIntMax_79) {
    int value = std::numeric_limits<int>::max();
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::max()));
}

TEST(CatchStringifyTest_79, StringifyIntMin_79) {
    int value = std::numeric_limits<int>::min();
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::min()));
}

// Test const char* stringification
TEST(CatchStringifyTest_79, StringifyConstCharPtr_79) {
    const char* value = "test string";
    std::string result = Catch::Detail::stringify(value);
    EXPECT_NE(result.find("test string"), std::string::npos);
}

// Test nullptr
TEST(CatchStringifyTest_79, StringifyNullptr_79) {
    std::nullptr_t value = nullptr;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_FALSE(result.empty());
}

// Test volatile qualifier is stripped
TEST(CatchStringifyTest_79, StringifyVolatileInt_79) {
    volatile int value = 55;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, "55");
}

// Test const volatile qualifier is stripped
TEST(CatchStringifyTest_79, StringifyConstVolatileInt_79) {
    const volatile int value = 33;
    std::string result = Catch::Detail::stringify(value);
    EXPECT_EQ(result, "33");
}
