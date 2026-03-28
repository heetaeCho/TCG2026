#include <gtest/gtest.h>
#include <string>

// Since matchi is static in the .cpp file, we need to include the source
// to access it for testing. We redefine the function signature for testing
// based on the known implementation pattern.
#include "exiv2/exiv2.hpp"

// To test the static function, we include the cpp file in a namespace wrapper
// or test through the public interface. Since it's static, we replicate the
// known logic for testing the internal helpers it depends on.
namespace TestHelpers {
    static bool matchi(const std::string& key, const char* substr) {
        return Exiv2::Internal::contains(Exiv2::Internal::lower(key), substr);
    }
}

class MatchiTest_1717 : public ::testing::Test {
protected:
    bool matchi(const std::string& key, const char* substr) {
        return TestHelpers::matchi(key, substr);
    }
};

// Normal operation tests
TEST_F(MatchiTest_1717, ExactMatchLowerCase_1717) {
    EXPECT_TRUE(matchi("hello", "hello"));
}

TEST_F(MatchiTest_1717, SubstringMatchLowerCase_1717) {
    EXPECT_TRUE(matchi("helloworld", "world"));
}

TEST_F(MatchiTest_1717, CaseInsensitiveMatchUpperKey_1717) {
    EXPECT_TRUE(matchi("HELLO", "hello"));
}

TEST_F(MatchiTest_1717, CaseInsensitiveMatchMixedKey_1717) {
    EXPECT_TRUE(matchi("HeLLo", "hello"));
}

TEST_F(MatchiTest_1717, CaseInsensitiveSubstringMatch_1717) {
    EXPECT_TRUE(matchi("SomeXmpKeyValue", "xmp"));
}

TEST_F(MatchiTest_1717, SubstringAtBeginning_1717) {
    EXPECT_TRUE(matchi("StartOfString", "start"));
}

TEST_F(MatchiTest_1717, SubstringAtEnd_1717) {
    EXPECT_TRUE(matchi("EndOfString", "string"));
}

TEST_F(MatchiTest_1717, SubstringInMiddle_1717) {
    EXPECT_TRUE(matchi("SomeMiddleValue", "middle"));
}

// Negative tests - no match
TEST_F(MatchiTest_1717, NoMatchReturnsfalse_1717) {
    EXPECT_FALSE(matchi("hello", "xyz"));
}

TEST_F(MatchiTest_1717, SubstrNotInKey_1717) {
    EXPECT_FALSE(matchi("abcdef", "xyz"));
}

TEST_F(MatchiTest_1717, PartialOverlapNoMatch_1717) {
    EXPECT_FALSE(matchi("hel", "hello"));
}

// Boundary conditions
TEST_F(MatchiTest_1717, EmptyKeyEmptySubstr_1717) {
    EXPECT_TRUE(matchi("", ""));
}

TEST_F(MatchiTest_1717, EmptySubstrMatchesAny_1717) {
    EXPECT_TRUE(matchi("anything", ""));
}

TEST_F(MatchiTest_1717, EmptyKeyNonEmptySubstr_1717) {
    EXPECT_FALSE(matchi("", "something"));
}

TEST_F(MatchiTest_1717, SingleCharMatchCaseInsensitive_1717) {
    EXPECT_TRUE(matchi("A", "a"));
}

TEST_F(MatchiTest_1717, SingleCharNoMatch_1717) {
    EXPECT_FALSE(matchi("a", "b"));
}

TEST_F(MatchiTest_1717, SubstrWithUpperCaseNotMatched_1717) {
    // substr is expected to be lowercase for matching since key is lowered
    EXPECT_FALSE(matchi("hello", "HELLO"));
}

TEST_F(MatchiTest_1717, LongStringMatch_1717) {
    std::string longKey(1000, 'A');
    std::string longSubstr(500, 'a');
    EXPECT_TRUE(matchi(longKey, longSubstr.c_str()));
}

TEST_F(MatchiTest_1717, SpecialCharacters_1717) {
    EXPECT_TRUE(matchi("key.with.dots", ".with."));
}

TEST_F(MatchiTest_1717, NumericCharacters_1717) {
    EXPECT_TRUE(matchi("abc123def", "123"));
}
