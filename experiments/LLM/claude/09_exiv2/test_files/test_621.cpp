#include <gtest/gtest.h>
#include "fujimn_int.hpp"

using namespace Exiv2::Internal;

class FujiMakerNoteTest_621 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that tagList() returns a non-null pointer
TEST_F(FujiMakerNoteTest_621, TagListReturnsNonNull_621) {
    auto tagList = FujiMakerNote::tagList();
    ASSERT_NE(tagList, nullptr);
}

// Test that tagList() is callable and returns consistently (idempotent)
TEST_F(FujiMakerNoteTest_621, TagListIsConsistent_621) {
    auto tagList1 = FujiMakerNote::tagList();
    auto tagList2 = FujiMakerNote::tagList();
    EXPECT_EQ(tagList1, tagList2);
}

// Test that the first entry in the tag list has a valid tag (tag 0 or known first tag)
TEST_F(FujiMakerNoteTest_621, TagListFirstEntryIsValid_621) {
    auto tagList = FujiMakerNote::tagList();
    ASSERT_NE(tagList, nullptr);
    // The first entry should have a tag value >= 0
    EXPECT_GE(tagList[0].tag_, 0);
}

// Test that tagList is constexpr-compatible (can be called at compile time context)
TEST_F(FujiMakerNoteTest_621, TagListIsConstexpr_621) {
    constexpr auto tagList = FujiMakerNote::tagList();
    EXPECT_NE(tagList, nullptr);
}

// Test that the tag list is terminated properly (last entry should have tag 0xFFFF or similar sentinel)
TEST_F(FujiMakerNoteTest_621, TagListHasTerminator_621) {
    auto tagList = FujiMakerNote::tagList();
    ASSERT_NE(tagList, nullptr);
    
    // Walk the tag list to find a terminating entry
    // Typically Exiv2 tag lists end with a tag value of 0xFFFF or a null title
    int count = 0;
    const int maxEntries = 500; // Safety limit
    while (count < maxEntries && tagList[count].tag_ != 0xffff) {
        count++;
    }
    // We should have found entries and a terminator within the limit
    EXPECT_LT(count, maxEntries);
    EXPECT_GT(count, 0);
}

// Test that multiple entries in the tag list have non-empty names
TEST_F(FujiMakerNoteTest_621, TagListEntriesHaveNames_621) {
    auto tagList = FujiMakerNote::tagList();
    ASSERT_NE(tagList, nullptr);
    
    // Check that the first few entries have non-null names
    // Exiv2 TagInfo typically has a name_ field
    if (tagList[0].tag_ != 0xffff) {
        EXPECT_NE(tagList[0].name_, nullptr);
    }
}

// Test that calling tagList multiple times from different contexts returns same pointer
TEST_F(FujiMakerNoteTest_621, TagListReturnsSamePointerOnMultipleCalls_621) {
    auto ptr1 = FujiMakerNote::tagList();
    auto ptr2 = FujiMakerNote::tagList();
    auto ptr3 = FujiMakerNote::tagList();
    EXPECT_EQ(ptr1, ptr2);
    EXPECT_EQ(ptr2, ptr3);
}
