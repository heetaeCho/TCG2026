#include <gtest/gtest.h>

// Include necessary headers
#include "./TestProjects/Catch2/src/catch2/catch_test_case_info.hpp"
#include "./TestProjects/Catch2/src/catch2/internal/catch_case_insensitive_comparisons.hpp"

// If the above headers don't work, try the amalgamated header
// #include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch;

// Test fixture
class TagLessTest_992 : public ::testing::Test {
protected:
    // Helper to create Tag objects
    Tag makeTag(const char* str) {
        return Tag(StringRef(str));
    }
};

// Normal operation tests

TEST_F(TagLessTest_992, LessThan_LowercaseABeforeLowercaseB_992) {
    Tag a = makeTag("apple");
    Tag b = makeTag("banana");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TagLessTest_992, LessThan_UppercaseABeforeUppercaseB_992) {
    Tag a = makeTag("APPLE");
    Tag b = makeTag("BANANA");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TagLessTest_992, CaseInsensitive_SameStringDifferentCase_992) {
    Tag lower = makeTag("apple");
    Tag upper = makeTag("APPLE");
    // If case insensitive, neither should be less than the other
    EXPECT_FALSE(lower < upper);
    EXPECT_FALSE(upper < lower);
}

TEST_F(TagLessTest_992, CaseInsensitive_MixedCaseComparison_992) {
    Tag a = makeTag("Apple");
    Tag b = makeTag("banana");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TagLessTest_992, CaseInsensitive_MixedCaseComparisonReversed_992) {
    Tag a = makeTag("banana");
    Tag b = makeTag("Apple");
    EXPECT_FALSE(a < b);
    EXPECT_TRUE(b < a);
}

// Boundary condition tests

TEST_F(TagLessTest_992, EmptyStrings_NeitherLessThan_992) {
    Tag a = makeTag("");
    Tag b = makeTag("");
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TagLessTest_992, EmptyStringLessThanNonEmpty_992) {
    Tag empty = makeTag("");
    Tag nonEmpty = makeTag("a");
    EXPECT_TRUE(empty < nonEmpty);
    EXPECT_FALSE(nonEmpty < empty);
}

TEST_F(TagLessTest_992, SingleCharacterComparison_992) {
    Tag a = makeTag("a");
    Tag b = makeTag("b");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TagLessTest_992, SingleCharacterCaseInsensitive_992) {
    Tag lower = makeTag("a");
    Tag upper = makeTag("A");
    EXPECT_FALSE(lower < upper);
    EXPECT_FALSE(upper < lower);
}

TEST_F(TagLessTest_992, PrefixIsLessThanFullString_992) {
    Tag prefix = makeTag("app");
    Tag full = makeTag("apple");
    EXPECT_TRUE(prefix < full);
    EXPECT_FALSE(full < prefix);
}

TEST_F(TagLessTest_992, SameTagNotLessThanItself_992) {
    Tag a = makeTag("test");
    EXPECT_FALSE(a < a);
}

// Strict weak ordering tests

TEST_F(TagLessTest_992, Irreflexivity_992) {
    Tag a = makeTag("hello");
    EXPECT_FALSE(a < a);
}

TEST_F(TagLessTest_992, Asymmetry_992) {
    Tag a = makeTag("aaa");
    Tag b = makeTag("bbb");
    // If a < b, then !(b < a)
    if (a < b) {
        EXPECT_FALSE(b < a);
    }
    if (b < a) {
        EXPECT_FALSE(a < b);
    }
}

TEST_F(TagLessTest_992, Transitivity_992) {
    Tag a = makeTag("alpha");
    Tag b = makeTag("beta");
    Tag c = makeTag("gamma");
    // a < b and b < c implies a < c
    if ((a < b) && (b < c)) {
        EXPECT_TRUE(a < c);
    }
}

// Test with mixed case maintaining case-insensitive ordering

TEST_F(TagLessTest_992, CaseInsensitive_UpperLowerMix_992) {
    Tag a = makeTag("ABC");
    Tag b = makeTag("abd");
    // 'abc' < 'abd' case insensitively
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TagLessTest_992, CaseInsensitive_LowerUpperMix_992) {
    Tag a = makeTag("abc");
    Tag b = makeTag("ABD");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// Test with numbers and special characters

TEST_F(TagLessTest_992, NumericStrings_992) {
    Tag a = makeTag("1");
    Tag b = makeTag("2");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TagLessTest_992, TagsWithSpecialCharacters_992) {
    Tag a = makeTag("[tag1]");
    Tag b = makeTag("[tag2]");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TagLessTest_992, LongIdenticalPrefixDifferentEnding_992) {
    Tag a = makeTag("verylongtagnamea");
    Tag b = makeTag("verylongtagnameb");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// Test CaseInsensitiveLess directly

class CaseInsensitiveLessTest_992 : public ::testing::Test {
protected:
    Catch::Detail::CaseInsensitiveLess cmp;
};

TEST_F(CaseInsensitiveLessTest_992, SameStringDifferentCase_992) {
    EXPECT_FALSE(cmp(StringRef("Hello"), StringRef("hello")));
    EXPECT_FALSE(cmp(StringRef("hello"), StringRef("Hello")));
}

TEST_F(CaseInsensitiveLessTest_992, DifferentStrings_992) {
    EXPECT_TRUE(cmp(StringRef("abc"), StringRef("def")));
    EXPECT_FALSE(cmp(StringRef("def"), StringRef("abc")));
}

TEST_F(CaseInsensitiveLessTest_992, EmptyStrings_992) {
    EXPECT_FALSE(cmp(StringRef(""), StringRef("")));
}

TEST_F(CaseInsensitiveLessTest_992, EmptyVsNonEmpty_992) {
    EXPECT_TRUE(cmp(StringRef(""), StringRef("a")));
    EXPECT_FALSE(cmp(StringRef("a"), StringRef("")));
}
