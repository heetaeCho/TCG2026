#include <gtest/gtest.h>
#include <tuple>
#include <string>
#include "re2/re2.h"

// We need to declare the shim function since it's defined in the python binding source
namespace re2_python {
std::tuple<bool, std::string, std::string> RE2PossibleMatchRangeShim(
    const re2::RE2& self, int maxlen);
}

// Since the shim uses py::bytes which is pybind11-specific, and we can't easily
// include pybind11 in a pure C++ test, we'll test the underlying RE2 functionality
// that the shim wraps: RE2::PossibleMatchRange

class RE2PossibleMatchRangeTest_58 : public ::testing::Test {
protected:
};

// Test basic functionality with a simple literal pattern
TEST_F(RE2PossibleMatchRangeTest_58, SimpleLiteralPattern_58) {
    re2::RE2 re("hello");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 10);
    EXPECT_TRUE(result);
    EXPECT_FALSE(min.empty());
    EXPECT_FALSE(max.empty());
    EXPECT_LE(min, "hello");
    EXPECT_GE(max, "hello");
}

// Test with a pattern that matches a range of strings
TEST_F(RE2PossibleMatchRangeTest_58, PatternWithCharacterClass_58) {
    re2::RE2 re("[a-z]+");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 10);
    EXPECT_TRUE(result);
    // min should be <= "a" and max should be >= "z..."
    EXPECT_LE(min, std::string("a"));
}

// Test with maxlen = 0
TEST_F(RE2PossibleMatchRangeTest_58, MaxlenZero_58) {
    re2::RE2 re("hello");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 0);
    // With maxlen 0, the function may still succeed but produce empty strings
    // or it may return false. We just verify it doesn't crash.
    (void)result;
}

// Test with maxlen = 1
TEST_F(RE2PossibleMatchRangeTest_58, MaxlenOne_58) {
    re2::RE2 re("hello");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 1);
    EXPECT_TRUE(result);
    EXPECT_LE(min.size(), 1u);
    EXPECT_LE(max.size(), 1u);
}

// Test with a pattern that matches everything (.*)
TEST_F(RE2PossibleMatchRangeTest_58, MatchEverything_58) {
    re2::RE2 re(".*");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 10);
    // .* matches everything including empty string
    // min should be empty string
    EXPECT_TRUE(result);
    EXPECT_EQ(min, "");
}

// Test with an anchored pattern
TEST_F(RE2PossibleMatchRangeTest_58, AnchoredPattern_58) {
    re2::RE2 re("^abc$");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 10);
    EXPECT_TRUE(result);
    EXPECT_LE(min, std::string("abc"));
    EXPECT_GE(max, std::string("abc"));
}

// Test with a pattern containing alternation
TEST_F(RE2PossibleMatchRangeTest_58, AlternationPattern_58) {
    re2::RE2 re("abc|xyz");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 10);
    EXPECT_TRUE(result);
    // The range should encompass both "abc" and "xyz"
    EXPECT_LE(min, std::string("abc"));
    EXPECT_GE(max, std::string("xyz"));
}

// Test with empty pattern
TEST_F(RE2PossibleMatchRangeTest_58, EmptyPattern_58) {
    re2::RE2 re("");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 10);
    EXPECT_TRUE(result);
}

// Test with a single character pattern
TEST_F(RE2PossibleMatchRangeTest_58, SingleCharPattern_58) {
    re2::RE2 re("a");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 10);
    EXPECT_TRUE(result);
    EXPECT_LE(min, std::string("a"));
    EXPECT_GE(max, std::string("a"));
}

// Test with a complex pattern
TEST_F(RE2PossibleMatchRangeTest_58, ComplexPattern_58) {
    re2::RE2 re("(foo|bar)baz[0-9]+");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 20);
    EXPECT_TRUE(result);
    EXPECT_LE(min, std::string("barbaz0"));
    EXPECT_GE(max, std::string("foobaz9"));
}

// Test that min <= max
TEST_F(RE2PossibleMatchRangeTest_58, MinLessThanOrEqualMax_58) {
    re2::RE2 re("[a-z]{3}");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 10);
    EXPECT_TRUE(result);
    EXPECT_LE(min, max);
}

// Test with a large maxlen
TEST_F(RE2PossibleMatchRangeTest_58, LargeMaxlen_58) {
    re2::RE2 re("hello");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 1000);
    EXPECT_TRUE(result);
    EXPECT_LE(min, std::string("hello"));
    EXPECT_GE(max, std::string("hello"));
}

// Test with a pattern containing repetition
TEST_F(RE2PossibleMatchRangeTest_58, RepetitionPattern_58) {
    re2::RE2 re("a{2,5}");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 10);
    EXPECT_TRUE(result);
    EXPECT_LE(min, std::string("aa"));
    EXPECT_GE(max, std::string("aaaaa"));
}

// Test with optional pattern
TEST_F(RE2PossibleMatchRangeTest_58, OptionalPattern_58) {
    re2::RE2 re("ab?c");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 10);
    EXPECT_TRUE(result);
    EXPECT_LE(min, std::string("ac"));
    EXPECT_GE(max, std::string("abc"));
}

// Test with a digit pattern
TEST_F(RE2PossibleMatchRangeTest_58, DigitPattern_58) {
    re2::RE2 re("[0-9]+");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 5);
    EXPECT_TRUE(result);
    EXPECT_LE(min, std::string("0"));
}

// Test PossibleMatchRange result consistency - calling twice should give same result
TEST_F(RE2PossibleMatchRangeTest_58, ConsistentResults_58) {
    re2::RE2 re("test[0-9]+");
    ASSERT_TRUE(re.ok());
    
    std::string min1, max1;
    bool result1 = re.PossibleMatchRange(&min1, &max1, 10);
    
    std::string min2, max2;
    bool result2 = re.PossibleMatchRange(&min2, &max2, 10);
    
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(min1, min2);
    EXPECT_EQ(max1, max2);
}

// Test with negative maxlen
TEST_F(RE2PossibleMatchRangeTest_58, NegativeMaxlen_58) {
    re2::RE2 re("hello");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    // Negative maxlen - should handle gracefully
    bool result = re.PossibleMatchRange(&min, &max, -1);
    // Just verify it doesn't crash; result may be false
    (void)result;
}

// Test with a fixed-string pattern using QuoteMeta
TEST_F(RE2PossibleMatchRangeTest_58, QuoteMetaPattern_58) {
    std::string quoted = re2::RE2::QuoteMeta("hello.world");
    re2::RE2 re(quoted);
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 20);
    EXPECT_TRUE(result);
    EXPECT_LE(min, std::string("hello.world"));
    EXPECT_GE(max, std::string("hello.world"));
}

// Test with a pattern containing \xff-like high bytes
TEST_F(RE2PossibleMatchRangeTest_58, HighBytePattern_58) {
    re2::RE2 re("\\xff");
    ASSERT_TRUE(re.ok());
    std::string min, max;
    bool result = re.PossibleMatchRange(&min, &max, 10);
    // Whether it succeeds may depend on the pattern
    (void)result;
}
