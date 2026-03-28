// endsWith_tests_586.cpp
#include <gtest/gtest.h>
#include <string>

// Forward declaration of the function under test (no re-implementation).
namespace Catch {
    bool endsWith(std::string const& s, std::string const& suffix);
}

using Catch::endsWith;

TEST(EndsWithTest_586, ReturnsTrueWhenSuffixMatchesAtEnd_586) {
    EXPECT_TRUE(endsWith("hello", "lo"));
    EXPECT_TRUE(endsWith("abc123", "123"));
}

TEST(EndsWithTest_586, ReturnsFalseWhenSuffixDoesNotMatch_586) {
    EXPECT_FALSE(endsWith("hello", "he"));
    EXPECT_FALSE(endsWith("testing", "stingy"));
}

TEST(EndsWithTest_586, ReturnsTrueWhenSuffixEqualsWholeString_586) {
    EXPECT_TRUE(endsWith("match", "match"));
}

TEST(EndsWithTest_586, EmptySuffixAlwaysMatches_586) {
    EXPECT_TRUE(endsWith("anything", ""));
    EXPECT_TRUE(endsWith("", ""));
}

TEST(EndsWithTest_586, SuffixLongerThanStringDoesNotMatch_586) {
    EXPECT_FALSE(endsWith("short", "muchlonger"));
    EXPECT_FALSE(endsWith("", "nonempty"));
}

TEST(EndsWithTest_586, SingleCharacterSuffix_586) {
    EXPECT_TRUE(endsWith("abc", "c"));
    EXPECT_FALSE(endsWith("abc", "a"));
}

TEST(EndsWithTest_586, CaseSensitivityIsObserved_586) {
    EXPECT_TRUE(endsWith("Hello", "lo"));
    EXPECT_FALSE(endsWith("Hello", "LO")); // Case-sensitive
}

TEST(EndsWithTest_586, WorksWithUTF8MultibyteCharacters_586) {
    // UTF-8 strings: treat as bytes; exact suffix bytes must match.
    // "안녕하세요" ends with "세요"
    EXPECT_TRUE(endsWith(u8"안녕하세요", u8"세요"));
    EXPECT_FALSE(endsWith(u8"안녕하세요", u8"하세")); // not a suffix
}

TEST(EndsWithTest_586, WorksWithWhitespaceAndSpecialChars_586) {
    EXPECT_TRUE(endsWith("line\n", "\n"));
    EXPECT_TRUE(endsWith("path/to/file.cpp", ".cpp"));
    EXPECT_FALSE(endsWith("path/to/file.cpp", " .cpp")); // leading space differs
}

TEST(EndsWithTest_586, OverlappingPatternsHandledCorrectly_586) {
    // Ensures comparison is suffix-based, not substring elsewhere
    EXPECT_TRUE(endsWith("aaaaab", "ab"));
    EXPECT_FALSE(endsWith("aaaaab", "aaab"));
}
