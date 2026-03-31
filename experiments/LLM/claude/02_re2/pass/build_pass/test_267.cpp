#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"

// Test the Parse<std::string> template specialization

namespace re2 {
namespace re2_internal {
template <>
bool Parse(const char* str, size_t n, std::string* dest);
}
}

class ParseStringTest_267 : public ::testing::Test {
protected:
};

// Normal operation: Parse assigns the string correctly
TEST_F(ParseStringTest_267, ParseAssignsStringCorrectly_267) {
    std::string dest;
    const char* input = "hello";
    bool result = re2::re2_internal::Parse(input, 5, &dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(dest, "hello");
}

// Normal operation: Parse with empty string
TEST_F(ParseStringTest_267, ParseEmptyString_267) {
    std::string dest = "previous";
    const char* input = "";
    bool result = re2::re2_internal::Parse(input, 0, &dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(dest, "");
}

// Normal operation: Parse with null destination returns true without crashing
TEST_F(ParseStringTest_267, ParseNullDestReturnsTrue_267) {
    const char* input = "hello";
    bool result = re2::re2_internal::Parse(input, 5, static_cast<std::string*>(nullptr));
    EXPECT_TRUE(result);
}

// Normal operation: Parse with partial length
TEST_F(ParseStringTest_267, ParsePartialLength_267) {
    std::string dest;
    const char* input = "hello world";
    bool result = re2::re2_internal::Parse(input, 5, &dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(dest, "hello");
}

// Boundary: Parse with length zero on non-empty string
TEST_F(ParseStringTest_267, ParseZeroLengthOnNonEmptyString_267) {
    std::string dest = "old";
    const char* input = "hello";
    bool result = re2::re2_internal::Parse(input, 0, &dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(dest, "");
}

// Normal operation: Parse overwrites existing content
TEST_F(ParseStringTest_267, ParseOverwritesExistingContent_267) {
    std::string dest = "old content that is long";
    const char* input = "new";
    bool result = re2::re2_internal::Parse(input, 3, &dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(dest, "new");
}

// Normal operation: Parse with embedded null characters
TEST_F(ParseStringTest_267, ParseWithEmbeddedNulls_267) {
    std::string dest;
    const char input[] = "hel\0lo";
    bool result = re2::re2_internal::Parse(input, 6, &dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(dest.size(), 6u);
    EXPECT_EQ(dest, std::string("hel\0lo", 6));
}

// Normal operation: Parse single character
TEST_F(ParseStringTest_267, ParseSingleCharacter_267) {
    std::string dest;
    const char* input = "x";
    bool result = re2::re2_internal::Parse(input, 1, &dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(dest, "x");
}

// Boundary: Parse with a large string
TEST_F(ParseStringTest_267, ParseLargeString_267) {
    std::string large_input(10000, 'A');
    std::string dest;
    bool result = re2::re2_internal::Parse(large_input.c_str(), large_input.size(), &dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(dest, large_input);
    EXPECT_EQ(dest.size(), 10000u);
}

// Verify return value is always true
TEST_F(ParseStringTest_267, AlwaysReturnsTrue_267) {
    std::string dest;
    // With valid dest
    EXPECT_TRUE(re2::re2_internal::Parse("abc", 3, &dest));
    // With null dest
    EXPECT_TRUE(re2::re2_internal::Parse("abc", 3, static_cast<std::string*>(nullptr)));
    // With empty input
    EXPECT_TRUE(re2::re2_internal::Parse("", 0, &dest));
}

// Test using RE2 full match extracting a string (integration-level)
TEST_F(ParseStringTest_267, RE2FullMatchExtractsString_267) {
    std::string result;
    EXPECT_TRUE(RE2::FullMatch("hello123", "([a-z]+)\\d+", &result));
    EXPECT_EQ(result, "hello");
}

TEST_F(ParseStringTest_267, RE2PartialMatchExtractsString_267) {
    std::string result;
    EXPECT_TRUE(RE2::PartialMatch("abc123def", "(\\d+)", &result));
    EXPECT_EQ(result, "123");
}

TEST_F(ParseStringTest_267, RE2FullMatchNoCapture_267) {
    EXPECT_TRUE(RE2::FullMatch("hello", "[a-z]+"));
    EXPECT_FALSE(RE2::FullMatch("hello123", "[a-z]+"));
}
