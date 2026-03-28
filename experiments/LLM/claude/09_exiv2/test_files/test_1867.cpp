#include <gtest/gtest.h>
#include <cstring>

// Reproduce the necessary types and macros from XMP toolkit
typedef const char* XMP_StringPtr;
typedef unsigned int XMP_StringLen;

#define XMP_LitNMatch(s1, s2, n) (std::strncmp((s1), (s2), (n)) == 0)

// Copy the function under test
static inline bool IsPathPrefix(XMP_StringPtr fullPath, XMP_StringPtr prefix) {
    bool isPrefix = false;
    XMP_StringLen prefixLen = std::strlen(prefix);
    if (XMP_LitNMatch(prefix, fullPath, prefixLen)) {
        char separator = fullPath[prefixLen];
        if ((separator == 0) || (separator == '/') || (separator == '[') || (separator == '*')) isPrefix = true;
    }
    return isPrefix;
}

class IsPathPrefixTest_1867 : public ::testing::Test {};

// Normal operation: exact match (fullPath equals prefix)
TEST_F(IsPathPrefixTest_1867, ExactMatch_1867) {
    EXPECT_TRUE(IsPathPrefix("xmp:Property", "xmp:Property"));
}

// Normal operation: prefix followed by '/'
TEST_F(IsPathPrefixTest_1867, PrefixFollowedBySlash_1867) {
    EXPECT_TRUE(IsPathPrefix("xmp:Property/subprop", "xmp:Property"));
}

// Normal operation: prefix followed by '['
TEST_F(IsPathPrefixTest_1867, PrefixFollowedByBracket_1867) {
    EXPECT_TRUE(IsPathPrefix("xmp:Property[1]", "xmp:Property"));
}

// Normal operation: prefix followed by '*'
TEST_F(IsPathPrefixTest_1867, PrefixFollowedByStar_1867) {
    EXPECT_TRUE(IsPathPrefix("xmp:Property*wildcard", "xmp:Property"));
}

// Non-matching prefix: completely different strings
TEST_F(IsPathPrefixTest_1867, CompletelyDifferentStrings_1867) {
    EXPECT_FALSE(IsPathPrefix("dc:title", "xmp:Property"));
}

// Non-matching: prefix matches but followed by a regular character (not separator)
TEST_F(IsPathPrefixTest_1867, PrefixMatchButNoValidSeparator_1867) {
    EXPECT_FALSE(IsPathPrefix("xmp:PropertyExtra", "xmp:Property"));
}

// Non-matching: prefix is longer than fullPath
TEST_F(IsPathPrefixTest_1867, PrefixLongerThanFullPath_1867) {
    EXPECT_FALSE(IsPathPrefix("xmp", "xmp:Property"));
}

// Boundary: both empty strings
TEST_F(IsPathPrefixTest_1867, BothEmptyStrings_1867) {
    EXPECT_TRUE(IsPathPrefix("", ""));
}

// Boundary: empty prefix with non-empty fullPath
TEST_F(IsPathPrefixTest_1867, EmptyPrefix_1867) {
    // Empty prefix has length 0, so fullPath[0] is checked.
    // If fullPath starts with any character, it depends on the character.
    // fullPath = "abc", fullPath[0] = 'a', which is not a valid separator.
    EXPECT_FALSE(IsPathPrefix("abc", ""));
}

// Boundary: empty prefix with fullPath starting with '/'
TEST_F(IsPathPrefixTest_1867, EmptyPrefixWithSlashFullPath_1867) {
    EXPECT_TRUE(IsPathPrefix("/something", ""));
}

// Boundary: empty prefix with fullPath starting with '['
TEST_F(IsPathPrefixTest_1867, EmptyPrefixWithBracketFullPath_1867) {
    EXPECT_TRUE(IsPathPrefix("[index]", ""));
}

// Boundary: empty prefix with fullPath starting with '*'
TEST_F(IsPathPrefixTest_1867, EmptyPrefixWithStarFullPath_1867) {
    EXPECT_TRUE(IsPathPrefix("*wildcard", ""));
}

// Boundary: empty fullPath with non-empty prefix
TEST_F(IsPathPrefixTest_1867, EmptyFullPathNonEmptyPrefix_1867) {
    EXPECT_FALSE(IsPathPrefix("", "xmp:Property"));
}

// Non-matching: prefix partially matches fullPath but diverges
TEST_F(IsPathPrefixTest_1867, PartialPrefixMatch_1867) {
    EXPECT_FALSE(IsPathPrefix("xmp:Propert", "xmp:Property"));
}

// Prefix followed by separator character that is not valid (e.g., '.')
TEST_F(IsPathPrefixTest_1867, PrefixFollowedByDot_1867) {
    EXPECT_FALSE(IsPathPrefix("xmp:Property.sub", "xmp:Property"));
}

// Prefix followed by space
TEST_F(IsPathPrefixTest_1867, PrefixFollowedBySpace_1867) {
    EXPECT_FALSE(IsPathPrefix("xmp:Property more", "xmp:Property"));
}

// Single character prefix matching
TEST_F(IsPathPrefixTest_1867, SingleCharPrefixExactMatch_1867) {
    EXPECT_TRUE(IsPathPrefix("a", "a"));
}

// Single character prefix with separator after
TEST_F(IsPathPrefixTest_1867, SingleCharPrefixWithSlash_1867) {
    EXPECT_TRUE(IsPathPrefix("a/b", "a"));
}

// Single character prefix followed by non-separator
TEST_F(IsPathPrefixTest_1867, SingleCharPrefixWithNonSeparator_1867) {
    EXPECT_FALSE(IsPathPrefix("ab", "a"));
}

// Case sensitivity: different case should not match
TEST_F(IsPathPrefixTest_1867, CaseSensitive_1867) {
    EXPECT_FALSE(IsPathPrefix("XMP:Property", "xmp:Property"));
}

// Prefix with special characters that are also separators
TEST_F(IsPathPrefixTest_1867, PrefixContainingSlash_1867) {
    EXPECT_TRUE(IsPathPrefix("a/b/c", "a/b"));
}

// Prefix containing bracket
TEST_F(IsPathPrefixTest_1867, PrefixContainingBracket_1867) {
    EXPECT_TRUE(IsPathPrefix("a[1]/b", "a[1]"));
}

// fullPath has prefix followed by multiple separators
TEST_F(IsPathPrefixTest_1867, PrefixFollowedByMultipleSeparators_1867) {
    EXPECT_TRUE(IsPathPrefix("xmp:Property//sub", "xmp:Property"));
}

// Very long matching prefix
TEST_F(IsPathPrefixTest_1867, LongMatchingPrefix_1867) {
    std::string longPrefix(1000, 'x');
    std::string fullPath = longPrefix + "/rest";
    EXPECT_TRUE(IsPathPrefix(fullPath.c_str(), longPrefix.c_str()));
}

// Very long non-matching prefix
TEST_F(IsPathPrefixTest_1867, LongNonMatchingPrefix_1867) {
    std::string longPrefix(1000, 'x');
    std::string fullPath(1000, 'y');
    EXPECT_FALSE(IsPathPrefix(fullPath.c_str(), longPrefix.c_str()));
}
