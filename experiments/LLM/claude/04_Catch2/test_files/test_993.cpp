#include <gtest/gtest.h>

// Include necessary headers
#include "./TestProjects/Catch2/src/catch2/catch_test_case_info.hpp"
#include "./TestProjects/Catch2/src/catch2/internal/catch_case_insensitive_comparisons.hpp"

// If the above headers don't work directly, try the amalgamated header
// #include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch;

// Test fixture for Tag equality tests
class TagEqualityTest_993 : public ::testing::Test {
protected:
    // Helper to create a Tag from a string
};

// Normal operation: Two identical tags should be equal
TEST_F(TagEqualityTest_993, IdenticalTagsAreEqual_993) {
    Tag tag1("hello");
    Tag tag2("hello");
    EXPECT_TRUE(tag1 == tag2);
}

// Case insensitive: Tags differing only in case should be equal
TEST_F(TagEqualityTest_993, CaseInsensitiveEquality_993) {
    Tag tag1("Hello");
    Tag tag2("hello");
    EXPECT_TRUE(tag1 == tag2);
}

// Case insensitive: All uppercase vs all lowercase
TEST_F(TagEqualityTest_993, AllUpperVsAllLower_993) {
    Tag tag1("HELLO");
    Tag tag2("hello");
    EXPECT_TRUE(tag1 == tag2);
}

// Case insensitive: Mixed case variations
TEST_F(TagEqualityTest_993, MixedCaseEquality_993) {
    Tag tag1("HeLLo");
    Tag tag2("hEllO");
    EXPECT_TRUE(tag1 == tag2);
}

// Different tags should not be equal
TEST_F(TagEqualityTest_993, DifferentTagsAreNotEqual_993) {
    Tag tag1("hello");
    Tag tag2("world");
    EXPECT_FALSE(tag1 == tag2);
}

// Empty tags should be equal
TEST_F(TagEqualityTest_993, EmptyTagsAreEqual_993) {
    Tag tag1("");
    Tag tag2("");
    EXPECT_TRUE(tag1 == tag2);
}

// Empty tag vs non-empty tag should not be equal
TEST_F(TagEqualityTest_993, EmptyVsNonEmptyNotEqual_993) {
    Tag tag1("");
    Tag tag2("hello");
    EXPECT_FALSE(tag1 == tag2);
}

// Tags with different lengths should not be equal
TEST_F(TagEqualityTest_993, DifferentLengthTagsNotEqual_993) {
    Tag tag1("hello");
    Tag tag2("hell");
    EXPECT_FALSE(tag1 == tag2);
}

// Single character tags - same letter different case
TEST_F(TagEqualityTest_993, SingleCharCaseInsensitive_993) {
    Tag tag1("A");
    Tag tag2("a");
    EXPECT_TRUE(tag1 == tag2);
}

// Single character tags - different letters
TEST_F(TagEqualityTest_993, SingleCharDifferentLetters_993) {
    Tag tag1("A");
    Tag tag2("B");
    EXPECT_FALSE(tag1 == tag2);
}

// Tags with numbers (numbers have no case)
TEST_F(TagEqualityTest_993, TagsWithNumbers_993) {
    Tag tag1("test123");
    Tag tag2("TEST123");
    EXPECT_TRUE(tag1 == tag2);
}

// Tags with special characters
TEST_F(TagEqualityTest_993, TagsWithSpecialChars_993) {
    Tag tag1("test-tag");
    Tag tag2("TEST-TAG");
    EXPECT_TRUE(tag1 == tag2);
}

// Tags with special characters that differ
TEST_F(TagEqualityTest_993, DifferentSpecialChars_993) {
    Tag tag1("test-tag");
    Tag tag2("test_tag");
    EXPECT_FALSE(tag1 == tag2);
}

// Reflexivity: A tag should equal itself
TEST_F(TagEqualityTest_993, ReflexiveEquality_993) {
    Tag tag("MyTag");
    EXPECT_TRUE(tag == tag);
}

// Symmetry: If a == b then b == a
TEST_F(TagEqualityTest_993, SymmetricEquality_993) {
    Tag tag1("Hello");
    Tag tag2("hello");
    EXPECT_TRUE(tag1 == tag2);
    EXPECT_TRUE(tag2 == tag1);
}

// Symmetry for inequality
TEST_F(TagEqualityTest_993, SymmetricInequality_993) {
    Tag tag1("Hello");
    Tag tag2("World");
    EXPECT_FALSE(tag1 == tag2);
    EXPECT_FALSE(tag2 == tag1);
}

// Tags with spaces
TEST_F(TagEqualityTest_993, TagsWithSpaces_993) {
    Tag tag1("my tag");
    Tag tag2("MY TAG");
    EXPECT_TRUE(tag1 == tag2);
}

// Tags that are prefix of another
TEST_F(TagEqualityTest_993, PrefixTagNotEqual_993) {
    Tag tag1("test");
    Tag tag2("testing");
    EXPECT_FALSE(tag1 == tag2);
}

// Longer tags with mixed case
TEST_F(TagEqualityTest_993, LongerMixedCaseTags_993) {
    Tag tag1("ThisIsALongerTagName");
    Tag tag2("thisisalongertagname");
    EXPECT_TRUE(tag1 == tag2);
}

// Test CaseInsensitiveEqualTo directly
class CaseInsensitiveEqualToTest_993 : public ::testing::Test {};

TEST_F(CaseInsensitiveEqualToTest_993, SameStringsEqual_993) {
    Detail::CaseInsensitiveEqualTo cmp;
    EXPECT_TRUE(cmp("hello", "hello"));
}

TEST_F(CaseInsensitiveEqualToTest_993, DifferentCaseEqual_993) {
    Detail::CaseInsensitiveEqualTo cmp;
    EXPECT_TRUE(cmp("HELLO", "hello"));
}

TEST_F(CaseInsensitiveEqualToTest_993, DifferentStringsNotEqual_993) {
    Detail::CaseInsensitiveEqualTo cmp;
    EXPECT_FALSE(cmp("hello", "world"));
}

TEST_F(CaseInsensitiveEqualToTest_993, EmptyStringsEqual_993) {
    Detail::CaseInsensitiveEqualTo cmp;
    EXPECT_TRUE(cmp("", ""));
}

TEST_F(CaseInsensitiveEqualToTest_993, EmptyVsNonEmpty_993) {
    Detail::CaseInsensitiveEqualTo cmp;
    EXPECT_FALSE(cmp("", "a"));
}
