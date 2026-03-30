// File: tag_less_tests_992.cpp
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <string>

// Prefer the amalgamated header if available in your build; it brings in Tag + StringRef.
// If your project does not use the amalgamated header, include the specific headers instead.
// #include "catch_amalgamated.hpp"
#include <catch2/catch_test_case_info.hpp> // defines Catch::Tag, Catch::StringRef

using Catch::Tag;

// Small helper to construct tags without depending on internal details.
static Tag makeTag(const char* s) {
    return Tag{Catch::StringRef{s}};
}

class TagLessTest_992 : public ::testing::Test {};

// Normal operation: case-insensitive lexicographic order
TEST_F(TagLessTest_992, CaseInsensitiveLexicographicOrder_992) {
    Tag a = makeTag("Apple");
    Tag b = makeTag("banana");

    // "apple" < "banana" -> true
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// Boundary: identical text with different casing should not be less either way
TEST_F(TagLessTest_992, EqualIgnoringCase_NoLessEitherWay_992) {
    Tag lower = makeTag("feature");
    Tag mixed = makeTag("FeAtUrE");

    EXPECT_FALSE(lower < mixed);
    EXPECT_FALSE(mixed < lower);
}

// Boundary: empty vs non-empty
TEST_F(TagLessTest_992, EmptyVsNonEmpty_992) {
    Tag empty = makeTag("");
    Tag nonempty = makeTag("x");

    EXPECT_TRUE(empty < nonempty);
    EXPECT_FALSE(nonempty < empty);
}

// Normal operation: transitivity (strict-weak-ordering property)
TEST_F(TagLessTest_992, TransitivityHolds_992) {
    Tag a = makeTag("a");
    Tag b = makeTag("b");
    Tag c = makeTag("c");

    ASSERT_TRUE(a < b);
    ASSERT_TRUE(b < c);
    EXPECT_TRUE(a < c);
}

// Exceptional-ish observable case: non-alpha characters should compare by lexicographic order
TEST_F(TagLessTest_992, NonAlphabeticCharacters_992) {
    Tag t1 = makeTag("tag-1");
    Tag t2 = makeTag("Tag-2");
    Tag t3 = makeTag("TAG!");

    // "tag-1" vs "tag-2" => '1' < '2'
    EXPECT_TRUE(t1 < t2);
    EXPECT_FALSE(t2 < t1);

    // Same characters ignoring case -> neither is less
    EXPECT_FALSE(t3 < makeTag("tag!"));
    EXPECT_FALSE(makeTag("tag!") < t3);
}

// Verification via external interaction (std::set using operator<):
// inserting equivalent tags differing only by case should yield 1 logical key.
TEST_F(TagLessTest_992, SetEliminatesCaseVariants_992) {
    std::set<Tag> tags; // uses Tag::operator< (free function) for ordering
    tags.insert(makeTag("foo"));
    tags.insert(makeTag("FOO"));
    tags.insert(makeTag("FoO"));
    tags.insert(makeTag("bar"));

    // Only two unique keys case-insensitively: "bar", "foo"
    ASSERT_EQ(tags.size(), 2u);

    // Verify ordering inside the set is case-insensitive lexicographic
    auto it = tags.begin();
    ASSERT_NE(it, tags.end());
    EXPECT_FALSE(makeTag("bar") < *it); // first is "bar" (case-insensitively)
    EXPECT_FALSE(*it < makeTag("bar"));
    ++it;
    ASSERT_NE(it, tags.end());
    EXPECT_FALSE(makeTag("foo") < *it); // second is "foo" (case-insensitively)
    EXPECT_FALSE(*it < makeTag("foo"));
    ++it;
    EXPECT_EQ(it, tags.end());
}

// Symmetry check: if lhs < rhs then rhs < lhs must be false
TEST_F(TagLessTest_992, Asymmetry_992) {
    Tag lhs = makeTag("alpha");
    Tag rhs = makeTag("BETA");

    ASSERT_TRUE(lhs < rhs);
    EXPECT_FALSE(rhs < lhs);
}
