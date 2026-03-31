#include "gtest/gtest.h"
#include "catch2/internal/catch_list.hpp"
#include "catch2/internal/catch_stringref.hpp"

class TagInfoTest_602 : public ::testing::Test {
protected:
    Catch::TagInfo tagInfo;
};

// Test that a newly constructed TagInfo has count 0
TEST_F(TagInfoTest_602, InitialCountIsZero_602) {
    EXPECT_EQ(tagInfo.count, 0u);
}

// Test that a newly constructed TagInfo has empty spellings
TEST_F(TagInfoTest_602, InitialSpellingsAreEmpty_602) {
    EXPECT_TRUE(tagInfo.spellings.empty());
}

// Test that adding one spelling increases count to 1
TEST_F(TagInfoTest_602, AddOneSpellingIncreasesCountToOne_602) {
    tagInfo.add(Catch::StringRef("tag1"));
    EXPECT_EQ(tagInfo.count, 1u);
}

// Test that adding one spelling inserts it into spellings set
TEST_F(TagInfoTest_602, AddOneSpellingInsertsIntoSet_602) {
    tagInfo.add(Catch::StringRef("tag1"));
    EXPECT_EQ(tagInfo.spellings.size(), 1u);
    EXPECT_NE(tagInfo.spellings.find(Catch::StringRef("tag1")), tagInfo.spellings.end());
}

// Test that adding multiple different spellings increases count for each
TEST_F(TagInfoTest_602, AddMultipleDifferentSpellingsIncreasesCount_602) {
    tagInfo.add(Catch::StringRef("tag1"));
    tagInfo.add(Catch::StringRef("tag2"));
    tagInfo.add(Catch::StringRef("tag3"));
    EXPECT_EQ(tagInfo.count, 3u);
}

// Test that adding multiple different spellings inserts all into set
TEST_F(TagInfoTest_602, AddMultipleDifferentSpellingsInsertsAll_602) {
    tagInfo.add(Catch::StringRef("tag1"));
    tagInfo.add(Catch::StringRef("tag2"));
    tagInfo.add(Catch::StringRef("tag3"));
    EXPECT_EQ(tagInfo.spellings.size(), 3u);
}

// Test that adding the same spelling twice increases count twice
TEST_F(TagInfoTest_602, AddDuplicateSpellingIncreasesCountTwice_602) {
    tagInfo.add(Catch::StringRef("tag1"));
    tagInfo.add(Catch::StringRef("tag1"));
    EXPECT_EQ(tagInfo.count, 2u);
}

// Test that adding the same spelling twice only has one entry in spellings set
TEST_F(TagInfoTest_602, AddDuplicateSpellingOnlyOneEntryInSet_602) {
    tagInfo.add(Catch::StringRef("tag1"));
    tagInfo.add(Catch::StringRef("tag1"));
    EXPECT_EQ(tagInfo.spellings.size(), 1u);
}

// Test adding an empty string as spelling
TEST_F(TagInfoTest_602, AddEmptyStringSpelling_602) {
    tagInfo.add(Catch::StringRef(""));
    EXPECT_EQ(tagInfo.count, 1u);
    EXPECT_EQ(tagInfo.spellings.size(), 1u);
}

// Test that all() returns something meaningful after adding spellings
TEST_F(TagInfoTest_602, AllReturnsNonEmptyAfterAdding_602) {
    tagInfo.add(Catch::StringRef("tag1"));
    std::string result = tagInfo.all();
    EXPECT_FALSE(result.empty());
}

// Test that all() on empty TagInfo returns an appropriate value
TEST_F(TagInfoTest_602, AllOnEmptyTagInfo_602) {
    std::string result = tagInfo.all();
    // Just verify it doesn't crash and returns a string
    // The exact content depends on implementation
    EXPECT_TRUE(result.empty() || !result.empty()); // no crash
}

// Test that all() contains the added spelling
TEST_F(TagInfoTest_602, AllContainsAddedSpelling_602) {
    tagInfo.add(Catch::StringRef("myTag"));
    std::string result = tagInfo.all();
    EXPECT_NE(result.find("myTag"), std::string::npos);
}

// Test that all() contains all different spellings when multiple are added
TEST_F(TagInfoTest_602, AllContainsAllDifferentSpellings_602) {
    tagInfo.add(Catch::StringRef("alpha"));
    tagInfo.add(Catch::StringRef("beta"));
    std::string result = tagInfo.all();
    EXPECT_NE(result.find("alpha"), std::string::npos);
    EXPECT_NE(result.find("beta"), std::string::npos);
}

// Test adding a large number of spellings
TEST_F(TagInfoTest_602, AddManySpellings_602) {
    for (int i = 0; i < 100; ++i) {
        std::string tag = "tag" + std::to_string(i);
        tagInfo.add(Catch::StringRef(tag));
    }
    EXPECT_EQ(tagInfo.count, 100u);
    EXPECT_EQ(tagInfo.spellings.size(), 100u);
}

// Test adding from std::string via StringRef conversion
TEST_F(TagInfoTest_602, AddFromStdString_602) {
    std::string tag = "fromStdString";
    tagInfo.add(Catch::StringRef(tag));
    EXPECT_EQ(tagInfo.count, 1u);
    EXPECT_EQ(tagInfo.spellings.size(), 1u);
}

// Test that count increments correctly with mix of duplicates and unique
TEST_F(TagInfoTest_602, MixedDuplicateAndUniqueSpellings_602) {
    tagInfo.add(Catch::StringRef("a"));
    tagInfo.add(Catch::StringRef("b"));
    tagInfo.add(Catch::StringRef("a"));
    tagInfo.add(Catch::StringRef("c"));
    tagInfo.add(Catch::StringRef("b"));
    EXPECT_EQ(tagInfo.count, 5u);
    EXPECT_EQ(tagInfo.spellings.size(), 3u);
}
