#include <gtest/gtest.h>
#include "yaml-cpp/exceptions.h"
#include "yaml-cpp/mark.h"
#include <string>

// Test fixture for TypedKeyNotFound and MakeTypedKeyNotFound
class MakeTypedKeyNotFoundTest_90 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that MakeTypedKeyNotFound returns a TypedKeyNotFound<int> with correct key
TEST_F(MakeTypedKeyNotFoundTest_90, IntKey_ReturnsTypedKeyNotFoundWithCorrectKey_90) {
    YAML::Mark mark;
    int key = 42;
    auto result = YAML::MakeTypedKeyNotFound(mark, key);
    EXPECT_EQ(result.key, key);
}

// Test that MakeTypedKeyNotFound returns a TypedKeyNotFound<std::string> with correct key
TEST_F(MakeTypedKeyNotFoundTest_90, StringKey_ReturnsTypedKeyNotFoundWithCorrectKey_90) {
    YAML::Mark mark;
    std::string key = "test_key";
    auto result = YAML::MakeTypedKeyNotFound(mark, key);
    EXPECT_EQ(result.key, key);
}

// Test with null mark
TEST_F(MakeTypedKeyNotFoundTest_90, NullMark_ReturnsTypedKeyNotFound_90) {
    YAML::Mark mark = YAML::Mark::null_mark();
    int key = 100;
    auto result = YAML::MakeTypedKeyNotFound(mark, key);
    EXPECT_EQ(result.key, key);
}

// Test with double key
TEST_F(MakeTypedKeyNotFoundTest_90, DoubleKey_ReturnsTypedKeyNotFoundWithCorrectKey_90) {
    YAML::Mark mark;
    double key = 3.14;
    auto result = YAML::MakeTypedKeyNotFound(mark, key);
    EXPECT_DOUBLE_EQ(result.key, key);
}

// Test with empty string key
TEST_F(MakeTypedKeyNotFoundTest_90, EmptyStringKey_ReturnsTypedKeyNotFoundWithEmptyKey_90) {
    YAML::Mark mark;
    std::string key = "";
    auto result = YAML::MakeTypedKeyNotFound(mark, key);
    EXPECT_EQ(result.key, key);
    EXPECT_TRUE(result.key.empty());
}

// Test with negative integer key
TEST_F(MakeTypedKeyNotFoundTest_90, NegativeIntKey_ReturnsTypedKeyNotFoundWithCorrectKey_90) {
    YAML::Mark mark;
    int key = -999;
    auto result = YAML::MakeTypedKeyNotFound(mark, key);
    EXPECT_EQ(result.key, key);
}

// Test with zero key
TEST_F(MakeTypedKeyNotFoundTest_90, ZeroIntKey_ReturnsTypedKeyNotFoundWithZeroKey_90) {
    YAML::Mark mark;
    int key = 0;
    auto result = YAML::MakeTypedKeyNotFound(mark, key);
    EXPECT_EQ(result.key, key);
}

// Test that the result is an instance of TypedKeyNotFound (which should inherit from some exception base)
TEST_F(MakeTypedKeyNotFoundTest_90, ResultIsTypedKeyNotFound_90) {
    YAML::Mark mark;
    int key = 5;
    YAML::TypedKeyNotFound<int> result = YAML::MakeTypedKeyNotFound(mark, key);
    EXPECT_EQ(result.key, key);
}

// Test with char key
TEST_F(MakeTypedKeyNotFoundTest_90, CharKey_ReturnsTypedKeyNotFoundWithCorrectKey_90) {
    YAML::Mark mark;
    char key = 'A';
    auto result = YAML::MakeTypedKeyNotFound(mark, key);
    EXPECT_EQ(result.key, key);
}

// Test that TypedKeyNotFound is throwable and catchable as an exception
TEST_F(MakeTypedKeyNotFoundTest_90, ThrowAndCatchTypedKeyNotFound_90) {
    YAML::Mark mark;
    std::string key = "missing_key";
    auto ex = YAML::MakeTypedKeyNotFound(mark, key);
    
    EXPECT_THROW(throw ex, YAML::TypedKeyNotFound<std::string>);
}

// Test that TypedKeyNotFound can be caught as a base Exception type
TEST_F(MakeTypedKeyNotFoundTest_90, ThrowAndCatchAsBaseException_90) {
    YAML::Mark mark;
    int key = 7;
    auto ex = YAML::MakeTypedKeyNotFound(mark, key);
    
    EXPECT_THROW(throw ex, YAML::Exception);
}

// Test with very large integer key
TEST_F(MakeTypedKeyNotFoundTest_90, LargeIntKey_ReturnsTypedKeyNotFoundWithCorrectKey_90) {
    YAML::Mark mark;
    int key = 2147483647; // INT_MAX
    auto result = YAML::MakeTypedKeyNotFound(mark, key);
    EXPECT_EQ(result.key, key);
}

// Test with long string key
TEST_F(MakeTypedKeyNotFoundTest_90, LongStringKey_ReturnsTypedKeyNotFoundWithCorrectKey_90) {
    YAML::Mark mark;
    std::string key(1000, 'x');
    auto result = YAML::MakeTypedKeyNotFound(mark, key);
    EXPECT_EQ(result.key, key);
    EXPECT_EQ(result.key.size(), 1000u);
}

// Test that what() returns a non-empty message
TEST_F(MakeTypedKeyNotFoundTest_90, WhatReturnsNonEmptyMessage_90) {
    YAML::Mark mark;
    std::string key = "some_key";
    auto ex = YAML::MakeTypedKeyNotFound(mark, key);
    
    const char* msg = ex.what();
    EXPECT_NE(msg, nullptr);
    EXPECT_GT(strlen(msg), 0u);
}
