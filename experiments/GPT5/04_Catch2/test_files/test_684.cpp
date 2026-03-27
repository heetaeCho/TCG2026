// File: tests/stringref_plus_tests_684.cpp

#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_stringref.hpp"  // adjust include path as needed

using Catch::StringRef;

class StringRefPlusTest_684 : public ::testing::Test {};

// Normal operation: simple ASCII concatenation
TEST_F(StringRefPlusTest_684, ConcatenatesSimpleAscii_684) {
    StringRef lhs("Hello, ");
    StringRef rhs("world!");
    std::string result = operator+(lhs, rhs);

    EXPECT_EQ(result, std::string("Hello, world!"));
    // Inputs should remain usable after the call (observable: same bytes when re-used)
    EXPECT_EQ(std::string(lhs.data(), lhs.size()), "Hello, ");
    EXPECT_EQ(std::string(rhs.data(), rhs.size()), "world!");
}

// Boundary: lhs empty, rhs non-empty
TEST_F(StringRefPlusTest_684, LhsEmpty_RhsNonEmpty_684) {
    StringRef lhs;                // default-constructed, expected empty
    StringRef rhs("abc");
    std::string result = operator+(lhs, rhs);

    EXPECT_EQ(result, std::string("abc"));
    EXPECT_TRUE(lhs.empty());
    EXPECT_FALSE(rhs.empty());
}

// Boundary: lhs non-empty, rhs empty
TEST_F(StringRefPlusTest_684, LhsNonEmpty_RhsEmpty_684) {
    StringRef lhs("xyz");
    StringRef rhs;                // empty
    std::string result = operator+(lhs, rhs);

    EXPECT_EQ(result, std::string("xyz"));
    EXPECT_FALSE(lhs.empty());
    EXPECT_TRUE(rhs.empty());
}

// Boundary: both empty
TEST_F(StringRefPlusTest_684, BothEmpty_684) {
    StringRef lhs;
    StringRef rhs;
    std::string result = operator+(lhs, rhs);

    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

// Normal operation: UTF-8 (multibyte) content is concatenated byte-for-byte
TEST_F(StringRefPlusTest_684, ConcatenatesUtf8Bytes_684) {
    // Use common multi-byte sequences (Korean + emoji)
    const std::string a = u8"한글";
    const std::string b = u8"🙈🙉";
    StringRef lhs(a);
    StringRef rhs(b);

    std::string result = operator+(lhs, rhs);
    std::string expected = a + b;

    EXPECT_EQ(result, expected);
    EXPECT_EQ(result.size(), expected.size());  // size checks count raw bytes
}

// Boundary / tricky bytes: embedded NULs are preserved
TEST_F(StringRefPlusTest_684, PreservesEmbeddedNulls_684) {
    const char left_raw[]  = { 'A', '\0', 'B', '\0' }; // 4 bytes
    const char right_raw[] = { '\0', 'X', 'Y' };       // 3 bytes
    StringRef lhs(left_raw,  sizeof(left_raw));
    StringRef rhs(right_raw, sizeof(right_raw));

    std::string result = operator+(lhs, rhs);

    std::string expected(left_raw,  sizeof(left_raw));
    expected.append(right_raw, sizeof(right_raw));

    ASSERT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected); // std::string compares full byte sequences (including NULs)
}

// Larger input: concatenation size and content for long strings
TEST_F(StringRefPlusTest_684, ConcatenatesLargeInputs_684) {
    const std::string a(5000, 'a');
    const std::string b(7000, 'b');

    StringRef lhs(a);
    StringRef rhs(b);

    std::string result = operator+(lhs, rhs);
    std::string expected = a + b;

    ASSERT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected);
}

// Use of temporaries: works directly with rvalue StringRefs
TEST_F(StringRefPlusTest_684, WorksWithTemporaries_684) {
    std::string result = operator+(StringRef("ab"), StringRef("cd"));
    EXPECT_EQ(result, std::string("abcd"));
}
