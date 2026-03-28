#include <gtest/gtest.h>
#include <string>
#include <set>

// Include the necessary headers
#include "catch2/internal/catch_list.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch;

// Test fixture for TagInfo
class TagInfoTest_603 : public ::testing::Test {
protected:
    TagInfo tagInfo;
};

// Test that all() returns empty string when no spellings are added
TEST_F(TagInfoTest_603, AllReturnsEmptyStringWhenNoSpellings_603) {
    std::string result = tagInfo.all();
    EXPECT_EQ(result, "");
}

// Test that all() returns correct format for a single spelling
TEST_F(TagInfoTest_603, AllReturnsSingleSpellingInBrackets_603) {
    tagInfo.add(StringRef("tag1"));
    std::string result = tagInfo.all();
    EXPECT_EQ(result, "[tag1]");
}

// Test that all() returns correct format for multiple spellings
TEST_F(TagInfoTest_603, AllReturnsMultipleSpellingsInBrackets_603) {
    tagInfo.add(StringRef("alpha"));
    tagInfo.add(StringRef("beta"));
    std::string result = tagInfo.all();
    // Since spellings is a std::set<StringRef>, they should be sorted
    // alpha < beta, so expected order is [alpha][beta]
    EXPECT_EQ(result, "[alpha][beta]");
}

// Test that add() increments the count
TEST_F(TagInfoTest_603, AddIncrementsCount_603) {
    EXPECT_EQ(tagInfo.count, 0u);
    tagInfo.add(StringRef("tag1"));
    EXPECT_EQ(tagInfo.count, 1u);
    tagInfo.add(StringRef("tag2"));
    EXPECT_EQ(tagInfo.count, 2u);
}

// Test that adding duplicate spellings - set should handle uniqueness
TEST_F(TagInfoTest_603, AddDuplicateSpellingBehavior_603) {
    tagInfo.add(StringRef("tag1"));
    tagInfo.add(StringRef("tag1"));
    // count should be incremented twice
    EXPECT_EQ(tagInfo.count, 2u);
    // But the set should contain only one unique spelling
    std::string result = tagInfo.all();
    EXPECT_EQ(result, "[tag1]");
}

// Test that spellings are stored in sorted order (set behavior)
TEST_F(TagInfoTest_603, SpellingsAreSorted_603) {
    tagInfo.add(StringRef("zebra"));
    tagInfo.add(StringRef("apple"));
    tagInfo.add(StringRef("mango"));
    std::string result = tagInfo.all();
    EXPECT_EQ(result, "[apple][mango][zebra]");
}

// Test with empty string spelling
TEST_F(TagInfoTest_603, AddEmptySpelling_603) {
    tagInfo.add(StringRef(""));
    std::string result = tagInfo.all();
    EXPECT_EQ(result, "[]");
    EXPECT_EQ(tagInfo.count, 1u);
}

// Test with single character spellings
TEST_F(TagInfoTest_603, SingleCharacterSpellings_603) {
    tagInfo.add(StringRef("a"));
    tagInfo.add(StringRef("b"));
    std::string result = tagInfo.all();
    EXPECT_EQ(result, "[a][b]");
}

// Test that initial count is zero
TEST_F(TagInfoTest_603, InitialCountIsZero_603) {
    EXPECT_EQ(tagInfo.count, 0u);
}

// Test that initial spellings set is empty
TEST_F(TagInfoTest_603, InitialSpellingsEmpty_603) {
    EXPECT_TRUE(tagInfo.spellings.empty());
}

// Test with many spellings
TEST_F(TagInfoTest_603, ManySpellings_603) {
    tagInfo.add(StringRef("tag1"));
    tagInfo.add(StringRef("tag2"));
    tagInfo.add(StringRef("tag3"));
    tagInfo.add(StringRef("tag4"));
    tagInfo.add(StringRef("tag5"));
    std::string result = tagInfo.all();
    EXPECT_EQ(result, "[tag1][tag2][tag3][tag4][tag5]");
    EXPECT_EQ(tagInfo.count, 5u);
}

// Test with special characters in spellings
TEST_F(TagInfoTest_603, SpecialCharactersInSpellings_603) {
    tagInfo.add(StringRef("tag-with-dashes"));
    tagInfo.add(StringRef("tag.with.dots"));
    std::string result = tagInfo.all();
    // Sorted order: '-' < '.' in ASCII
    EXPECT_EQ(result, "[tag-with-dashes][tag.with.dots]");
}

// Test that all() is const and can be called multiple times consistently
TEST_F(TagInfoTest_603, AllIsIdempotent_603) {
    tagInfo.add(StringRef("hello"));
    tagInfo.add(StringRef("world"));
    std::string result1 = tagInfo.all();
    std::string result2 = tagInfo.all();
    EXPECT_EQ(result1, result2);
}

// Test with spacing in tag names
TEST_F(TagInfoTest_603, SpellingWithSpaces_603) {
    tagInfo.add(StringRef("tag with spaces"));
    std::string result = tagInfo.all();
    EXPECT_EQ(result, "[tag with spaces]");
}
