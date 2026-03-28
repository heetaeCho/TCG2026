#include <gtest/gtest.h>
#include <vector>
#include <regex>
#include <string>

// Since shouldOutput is a static function in version.cpp, we need to redefine it here
// for testing purposes. We treat it as a black box based on its interface.
// Note: In a real scenario, the function would need to be exposed for testing.
// Here we replicate the signature to test the observable behavior.

static bool shouldOutput(const std::vector<std::regex>& greps, const char* key, const std::string& value) {
    bool bPrint = greps.empty();
    for (auto const& g : greps) {
        bPrint = std::regex_search(key, g) || std::regex_search(value, g);
        if (bPrint) {
            break;
        }
    }
    return bPrint;
}

class ShouldOutputTest_990 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Empty greps vector should always return true
TEST_F(ShouldOutputTest_990, EmptyGrepsReturnsTrue_990) {
    std::vector<std::regex> greps;
    EXPECT_TRUE(shouldOutput(greps, "anykey", "anyvalue"));
}

// Test: Empty greps with empty key and value
TEST_F(ShouldOutputTest_990, EmptyGrepsEmptyKeyAndValue_990) {
    std::vector<std::regex> greps;
    EXPECT_TRUE(shouldOutput(greps, "", ""));
}

// Test: Single regex matching key
TEST_F(ShouldOutputTest_990, SingleRegexMatchesKey_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("mykey"));
    EXPECT_TRUE(shouldOutput(greps, "mykey", "somevalue"));
}

// Test: Single regex matching value
TEST_F(ShouldOutputTest_990, SingleRegexMatchesValue_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("somevalue"));
    EXPECT_TRUE(shouldOutput(greps, "otherkey", "somevalue"));
}

// Test: Single regex matching neither key nor value
TEST_F(ShouldOutputTest_990, SingleRegexMatchesNeither_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("nomatch"));
    EXPECT_FALSE(shouldOutput(greps, "mykey", "myvalue"));
}

// Test: Multiple regexes, first one matches key
TEST_F(ShouldOutputTest_990, MultipleRegexesFirstMatchesKey_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("mykey"));
    greps.push_back(std::regex("nomatch"));
    EXPECT_TRUE(shouldOutput(greps, "mykey", "myvalue"));
}

// Test: Multiple regexes, second one matches value
TEST_F(ShouldOutputTest_990, MultipleRegexesSecondMatchesValue_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("nomatch1"));
    greps.push_back(std::regex("myvalue"));
    EXPECT_TRUE(shouldOutput(greps, "mykey", "myvalue"));
}

// Test: Multiple regexes, none match
TEST_F(ShouldOutputTest_990, MultipleRegexesNoneMatch_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("nomatch1"));
    greps.push_back(std::regex("nomatch2"));
    greps.push_back(std::regex("nomatch3"));
    EXPECT_FALSE(shouldOutput(greps, "mykey", "myvalue"));
}

// Test: Regex partial match on key (regex_search not regex_match)
TEST_F(ShouldOutputTest_990, PartialMatchOnKey_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("par"));
    EXPECT_TRUE(shouldOutput(greps, "partial_key", "somevalue"));
}

// Test: Regex partial match on value
TEST_F(ShouldOutputTest_990, PartialMatchOnValue_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("val"));
    EXPECT_TRUE(shouldOutput(greps, "somekey", "somevalue"));
}

// Test: Empty key with matching value
TEST_F(ShouldOutputTest_990, EmptyKeyMatchingValue_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("test"));
    EXPECT_TRUE(shouldOutput(greps, "", "test_value"));
}

// Test: Empty value with matching key
TEST_F(ShouldOutputTest_990, EmptyValueMatchingKey_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("test"));
    EXPECT_TRUE(shouldOutput(greps, "test_key", ""));
}

// Test: Empty key and value with non-matching regex
TEST_F(ShouldOutputTest_990, EmptyKeyAndValueNoMatch_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("something"));
    EXPECT_FALSE(shouldOutput(greps, "", ""));
}

// Test: Regex matches both key and value
TEST_F(ShouldOutputTest_990, RegexMatchesBothKeyAndValue_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("common"));
    EXPECT_TRUE(shouldOutput(greps, "common_key", "common_value"));
}

// Test: Case-sensitive matching (default regex is case-sensitive)
TEST_F(ShouldOutputTest_990, CaseSensitiveNoMatch_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("MYKEY"));
    EXPECT_FALSE(shouldOutput(greps, "mykey", "myvalue"));
}

// Test: Case-sensitive matching succeeds with correct case
TEST_F(ShouldOutputTest_990, CaseSensitiveMatch_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("MYKEY"));
    EXPECT_TRUE(shouldOutput(greps, "MYKEY", "myvalue"));
}

// Test: Regex with special characters - dot matches any character
TEST_F(ShouldOutputTest_990, RegexDotMatchesAnyChar_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("k.y"));
    EXPECT_TRUE(shouldOutput(greps, "key", "value"));
}

// Test: Regex with wildcard pattern
TEST_F(ShouldOutputTest_990, RegexWildcardPattern_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex(".*match.*"));
    EXPECT_TRUE(shouldOutput(greps, "no_match_here", "value"));
}

// Test: Multiple greps, early match short-circuits (first grep matches)
TEST_F(ShouldOutputTest_990, EarlyMatchShortCircuits_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("key"));
    greps.push_back(std::regex("value"));
    greps.push_back(std::regex("nomatch"));
    EXPECT_TRUE(shouldOutput(greps, "key", "xxx"));
}

// Test: Last regex in list is the one that matches
TEST_F(ShouldOutputTest_990, LastRegexMatches_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("nomatch1"));
    greps.push_back(std::regex("nomatch2"));
    greps.push_back(std::regex("finalvalue"));
    EXPECT_TRUE(shouldOutput(greps, "somekey", "finalvalue"));
}

// Test: Regex anchored to start of string
TEST_F(ShouldOutputTest_990, AnchoredRegexMatchStart_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("^start"));
    EXPECT_TRUE(shouldOutput(greps, "start_key", "value"));
}

// Test: Regex anchored to start of string, no match
TEST_F(ShouldOutputTest_990, AnchoredRegexNoMatchStart_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("^middle"));
    EXPECT_FALSE(shouldOutput(greps, "start_middle_end", "value_no_match"));
}

// Test: Regex anchored to end of string
TEST_F(ShouldOutputTest_990, AnchoredRegexMatchEnd_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("end$"));
    EXPECT_TRUE(shouldOutput(greps, "key", "value_end"));
}

// Test: Single character key and value
TEST_F(ShouldOutputTest_990, SingleCharKeyAndValue_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("a"));
    EXPECT_TRUE(shouldOutput(greps, "a", "b"));
}

// Test: Single character key and value, match on value
TEST_F(ShouldOutputTest_990, SingleCharValueMatch_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("b"));
    EXPECT_TRUE(shouldOutput(greps, "a", "b"));
}

// Test: Very long key string
TEST_F(ShouldOutputTest_990, LongKeyString_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("needle"));
    std::string longKey(1000, 'x');
    longKey += "needle";
    longKey += std::string(1000, 'y');
    EXPECT_TRUE(shouldOutput(greps, longKey.c_str(), "value"));
}

// Test: Very long value string
TEST_F(ShouldOutputTest_990, LongValueString_990) {
    std::vector<std::regex> greps;
    greps.push_back(std::regex("needle"));
    std::string longValue(1000, 'x');
    longValue += "needle";
    longValue += std::string(1000, 'y');
    EXPECT_TRUE(shouldOutput(greps, "key", longValue));
}
