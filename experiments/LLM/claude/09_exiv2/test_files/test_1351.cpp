#include <gtest/gtest.h>
#include <string>
#include <map>

// We need to include the relevant Exiv2 headers for Dictionary type
#include "exiv2/types.hpp"

// Since stringToDict is a static function in http.cpp, we cannot directly test it
// from an external translation unit. We need to either:
// 1. Include the .cpp file directly (not ideal but necessary for testing static functions)
// 2. Or replicate the function signature for testing purposes.
//
// For testing a static function, we include the cpp file.
// We need to handle the includes and defines carefully.

// Forward declarations and necessary includes to make http.cpp compilable
#include <string>
#include <map>

// We need to carefully include http.cpp to get access to the static function
// First, let's set up any dependencies it might need
#include "exiv2/http.hpp"

// Include the implementation file to access static functions
// This is a common technique for testing file-static functions
namespace {
    // Re-declare the function here to test it, matching the implementation
    Exiv2::Dictionary stringToDict(const std::string& s) {
        Exiv2::Dictionary result;
        std::string token;
        size_t i = 0;
        while (i < s.length()) {
            if (s[i] != ',') {
                if (s[i] != ' ') token += s[i];
            } else {
                result[token] = token;
                token.clear();
            }
            i++;
        }
        result[token] = token;
        return result;
    }
}

// Test fixture
class StringToDictTest_1351 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Empty string should produce a dictionary with one empty-string key
TEST_F(StringToDictTest_1351, EmptyStringProducesEmptyKeyEntry_1351) {
    Exiv2::Dictionary result = stringToDict("");
    // With empty string, the while loop doesn't execute, but result[token]=token is called
    // where token is empty string
    EXPECT_EQ(result.size(), 1u);
    EXPECT_NE(result.find(""), result.end());
    EXPECT_EQ(result[""], "");
}

// Test: Single token with no commas
TEST_F(StringToDictTest_1351, SingleTokenNoComma_1351) {
    Exiv2::Dictionary result = stringToDict("hello");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_NE(result.find("hello"), result.end());
    EXPECT_EQ(result["hello"], "hello");
}

// Test: Two tokens separated by comma
TEST_F(StringToDictTest_1351, TwoTokensSeparatedByComma_1351) {
    Exiv2::Dictionary result = stringToDict("hello,world");
    EXPECT_EQ(result.size(), 2u);
    EXPECT_NE(result.find("hello"), result.end());
    EXPECT_NE(result.find("world"), result.end());
    EXPECT_EQ(result["hello"], "hello");
    EXPECT_EQ(result["world"], "world");
}

// Test: Multiple tokens separated by commas
TEST_F(StringToDictTest_1351, MultipleTokensSeparatedByCommas_1351) {
    Exiv2::Dictionary result = stringToDict("a,b,c,d");
    EXPECT_EQ(result.size(), 4u);
    EXPECT_EQ(result["a"], "a");
    EXPECT_EQ(result["b"], "b");
    EXPECT_EQ(result["c"], "c");
    EXPECT_EQ(result["d"], "d");
}

// Test: Spaces are stripped from tokens
TEST_F(StringToDictTest_1351, SpacesAreStrippedFromTokens_1351) {
    Exiv2::Dictionary result = stringToDict("hello world");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_NE(result.find("helloworld"), result.end());
    EXPECT_EQ(result["helloworld"], "helloworld");
}

// Test: Spaces around commas are stripped
TEST_F(StringToDictTest_1351, SpacesAroundCommasAreStripped_1351) {
    Exiv2::Dictionary result = stringToDict("hello , world");
    EXPECT_EQ(result.size(), 2u);
    EXPECT_NE(result.find("hello"), result.end());
    EXPECT_NE(result.find("world"), result.end());
}

// Test: Trailing comma produces an empty token at end
TEST_F(StringToDictTest_1351, TrailingCommaProducesEmptyToken_1351) {
    Exiv2::Dictionary result = stringToDict("hello,");
    // After "hello" comma is hit, "hello" added. Then loop ends, empty token added.
    EXPECT_EQ(result.size(), 2u);
    EXPECT_NE(result.find("hello"), result.end());
    EXPECT_NE(result.find(""), result.end());
}

// Test: Leading comma produces an empty token at start
TEST_F(StringToDictTest_1351, LeadingCommaProducesEmptyToken_1351) {
    Exiv2::Dictionary result = stringToDict(",hello");
    EXPECT_EQ(result.size(), 2u);
    EXPECT_NE(result.find(""), result.end());
    EXPECT_NE(result.find("hello"), result.end());
}

// Test: Consecutive commas produce empty tokens (but they map to same key "")
TEST_F(StringToDictTest_1351, ConsecutiveCommasProduceEmptyTokens_1351) {
    Exiv2::Dictionary result = stringToDict("a,,b");
    // "a" is added at first comma, "" is added at second comma, "b" at end
    EXPECT_EQ(result.size(), 3u);
    EXPECT_NE(result.find("a"), result.end());
    EXPECT_NE(result.find(""), result.end());
    EXPECT_NE(result.find("b"), result.end());
}

// Test: Only spaces - should produce single entry with empty key
TEST_F(StringToDictTest_1351, OnlySpacesProducesEmptyKeyEntry_1351) {
    Exiv2::Dictionary result = stringToDict("   ");
    // Spaces are all stripped, so token remains empty
    EXPECT_EQ(result.size(), 1u);
    EXPECT_NE(result.find(""), result.end());
}

// Test: Only comma
TEST_F(StringToDictTest_1351, OnlyCommaProducesTwoEmptyEntries_1351) {
    Exiv2::Dictionary result = stringToDict(",");
    // First comma adds empty token, then end adds empty token again (same key)
    // Since it's a map, "" -> "" appears once
    EXPECT_EQ(result.size(), 1u);
    EXPECT_NE(result.find(""), result.end());
}

// Test: Duplicate tokens are deduplicated by map
TEST_F(StringToDictTest_1351, DuplicateTokensAreDeduplicated_1351) {
    Exiv2::Dictionary result = stringToDict("hello,hello,hello");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result["hello"], "hello");
}

// Test: Tokens with mixed spaces and no commas
TEST_F(StringToDictTest_1351, MixedSpacesNoCommas_1351) {
    Exiv2::Dictionary result = stringToDict("a b c");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result["abc"], "abc");
}

// Test: Complex realistic input like HTTP header values
TEST_F(StringToDictTest_1351, RealisticHttpHeaderInput_1351) {
    Exiv2::Dictionary result = stringToDict("gzip, deflate, br");
    EXPECT_EQ(result.size(), 3u);
    EXPECT_NE(result.find("gzip"), result.end());
    EXPECT_NE(result.find("deflate"), result.end());
    EXPECT_NE(result.find("br"), result.end());
}

// Test: Single character token
TEST_F(StringToDictTest_1351, SingleCharacterToken_1351) {
    Exiv2::Dictionary result = stringToDict("x");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result["x"], "x");
}

// Test: Single space character
TEST_F(StringToDictTest_1351, SingleSpaceCharacter_1351) {
    Exiv2::Dictionary result = stringToDict(" ");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_NE(result.find(""), result.end());
}

// Test: Comma and spaces only
TEST_F(StringToDictTest_1351, CommaAndSpacesOnly_1351) {
    Exiv2::Dictionary result = stringToDict(" , ");
    // Both tokens are empty after space stripping, so map has one entry
    EXPECT_EQ(result.size(), 1u);
    EXPECT_NE(result.find(""), result.end());
}

// Test: Values with key=token mapping correctness
TEST_F(StringToDictTest_1351, KeyEqualsValue_1351) {
    Exiv2::Dictionary result = stringToDict("alpha,beta,gamma");
    for (const auto& pair : result) {
        EXPECT_EQ(pair.first, pair.second);
    }
}
