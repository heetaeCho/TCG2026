// generator_exception_tests_311.cpp
#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <exception>

// Include the class under test
#include "catch2/generators/catch_generator_exception.hpp"

class GeneratorExceptionTest_311 : public ::testing::Test {};

TEST_F(GeneratorExceptionTest_311, WhatReturnsMessage_Normal_311) {
    const char* msg = "generator failed at step 3";
    Catch::GeneratorException ex(msg);

    // Observable behavior: what() returns a C string with the message content.
    EXPECT_STREQ(msg, ex.what());
}

TEST_F(GeneratorExceptionTest_311, WhatNoThrow_IsNoexcept_311) {
    const char* msg = "noexcept check";
    Catch::GeneratorException ex(msg);

    // Verify noexcept at compile time and also call it to ensure no throw at runtime.
    static_assert(noexcept(ex.what()), "what() must be noexcept");
    EXPECT_NO_THROW({
        (void)ex.what();
    });
}

TEST_F(GeneratorExceptionTest_311, EmptyMessage_YieldsEmptyCStr_311) {
    const char* empty = "";
    Catch::GeneratorException ex(empty);

    // Should be a valid empty C string (null-terminated).
    EXPECT_STREQ("", ex.what());
    EXPECT_EQ(0u, std::strlen(ex.what()));
}

TEST_F(GeneratorExceptionTest_311, LongMessage_ContentPreserved_311) {
    // Build a long message to test boundary-like behavior on reasonable lengths.
    std::string longMsg(16 * 1024, 'a'); // 16KB of 'a'
    Catch::GeneratorException ex(longMsg.c_str());

    // Do not assume pointer identity; only verify visible string content.
    EXPECT_STREQ(longMsg.c_str(), ex.what());

    // Additionally, ensure it's null-terminated by comparing strlen.
    EXPECT_EQ(longMsg.size(), std::strlen(ex.what()));
}

TEST_F(GeneratorExceptionTest_311, PolymorphicAccess_ViaStdException_311) {
    const char* msg = "polymorphic what()";
    Catch::GeneratorException ex(msg);

    // Treat as std::exception to verify it behaves through the public base interface.
    const std::exception& base = ex;
    EXPECT_STREQ(msg, base.what());
}

TEST_F(GeneratorExceptionTest_311, NonAsciiUtf8Content_Preserved_311) {
    // UTF-8 content (Korean): "제너레이터 오류"
    const char* utf8 = "제너레이터 오류";
    Catch::GeneratorException ex(utf8);

    // As bytes, what() should return the same content.
    EXPECT_STREQ(utf8, ex.what());
    // Length in bytes should match strlen of the literal.
    EXPECT_EQ(std::strlen(utf8), std::strlen(ex.what()));
}
