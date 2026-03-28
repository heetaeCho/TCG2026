#include <gtest/gtest.h>
#include "exiv2/tags.h"
#include "tags_int.hpp"

namespace {

using namespace Exiv2::Internal;

class MnTagListTest_1362 : public ::testing::Test {
protected:
    const TagInfo* tagList = nullptr;

    void SetUp() override {
        tagList = mnTagList();
    }
};

// Test that mnTagList returns a non-null pointer
TEST_F(MnTagListTest_1362, ReturnsNonNull_1362) {
    ASSERT_NE(tagList, nullptr);
}

// Test the first tag entry (Offset)
TEST_F(MnTagListTest_1362, FirstTagIsOffset_1362) {
    EXPECT_EQ(tagList[0].tag_, 1);
    EXPECT_STREQ(tagList[0].name_, "Offset");
    EXPECT_STREQ(tagList[0].title_, "Offset");
    EXPECT_STREQ(tagList[0].desc_, "Offset of the makernote from the start of the TIFF header.");
    EXPECT_EQ(tagList[0].ifdId_, IfdId::mnId);
    EXPECT_EQ(tagList[0].sectionId_, SectionId::makerTags);
    EXPECT_EQ(tagList[0].typeId_, Exiv2::unsignedLong);
    EXPECT_EQ(tagList[0].count_, 1);
    EXPECT_NE(tagList[0].printFct_, nullptr);
}

// Test the second tag entry (ByteOrder)
TEST_F(MnTagListTest_1362, SecondTagIsByteOrder_1362) {
    EXPECT_EQ(tagList[1].tag_, 2);
    EXPECT_STREQ(tagList[1].name_, "ByteOrder");
    EXPECT_STREQ(tagList[1].title_, "Byte Order");
    EXPECT_STREQ(tagList[1].desc_, "Byte order used to encode MakerNote tags, 'MM' (big-endian) or 'II' (little-endian).");
    EXPECT_EQ(tagList[1].ifdId_, IfdId::mnId);
    EXPECT_EQ(tagList[1].sectionId_, SectionId::makerTags);
    EXPECT_EQ(tagList[1].typeId_, Exiv2::asciiString);
    EXPECT_EQ(tagList[1].count_, 0);
    EXPECT_NE(tagList[1].printFct_, nullptr);
}

// Test the third (sentinel/unknown) tag entry
TEST_F(MnTagListTest_1362, ThirdTagIsUnknownSentinel_1362) {
    EXPECT_EQ(tagList[2].tag_, 65535);
    EXPECT_STREQ(tagList[2].name_, "(UnknownMnTag)");
    EXPECT_STREQ(tagList[2].title_, "Unknown Exiv2 Makernote info tag");
    EXPECT_STREQ(tagList[2].desc_, "Unknown Exiv2 Makernote info tag");
    EXPECT_EQ(tagList[2].ifdId_, IfdId::mnId);
    EXPECT_EQ(tagList[2].sectionId_, SectionId::makerTags);
    EXPECT_EQ(tagList[2].typeId_, Exiv2::asciiString);
    EXPECT_EQ(tagList[2].count_, -1);
    EXPECT_NE(tagList[2].printFct_, nullptr);
}

// Test that calling mnTagList multiple times returns the same pointer (stable static data)
TEST_F(MnTagListTest_1362, ReturnsSamePointerOnMultipleCalls_1362) {
    const TagInfo* firstCall = mnTagList();
    const TagInfo* secondCall = mnTagList();
    EXPECT_EQ(firstCall, secondCall);
}

// Test that all three entries share the same ifdId
TEST_F(MnTagListTest_1362, AllEntriesHaveMnId_1362) {
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(tagList[i].ifdId_, IfdId::mnId) << "Entry " << i << " has wrong ifdId";
    }
}

// Test that all three entries share the same sectionId
TEST_F(MnTagListTest_1362, AllEntriesHaveMakerTagsSection_1362) {
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(tagList[i].sectionId_, SectionId::makerTags) << "Entry " << i << " has wrong sectionId";
    }
}

// Test that tags are in ascending order (boundary: verifying ordering)
TEST_F(MnTagListTest_1362, TagsAreInAscendingOrder_1362) {
    EXPECT_LT(tagList[0].tag_, tagList[1].tag_);
    EXPECT_LT(tagList[1].tag_, tagList[2].tag_);
}

// Test that the sentinel tag has the maximum uint16 value (0xFFFF = 65535)
TEST_F(MnTagListTest_1362, SentinelTagHasMaxUint16Value_1362) {
    EXPECT_EQ(tagList[2].tag_, 0xFFFF);
}

// Test that all print functions are not null (all entries have valid print callbacks)
TEST_F(MnTagListTest_1362, AllPrintFunctionsAreValid_1362) {
    for (int i = 0; i < 3; ++i) {
        EXPECT_NE(tagList[i].printFct_, nullptr) << "Entry " << i << " has null printFct";
    }
}

// Test count field boundary values across entries
TEST_F(MnTagListTest_1362, CountFieldValues_1362) {
    EXPECT_EQ(tagList[0].count_, 1);   // Offset has count 1
    EXPECT_EQ(tagList[1].count_, 0);   // ByteOrder has count 0
    EXPECT_EQ(tagList[2].count_, -1);  // Unknown/sentinel has count -1
}

// Test that name fields are non-null for all entries
TEST_F(MnTagListTest_1362, AllNamesAreNonNull_1362) {
    for (int i = 0; i < 3; ++i) {
        EXPECT_NE(tagList[i].name_, nullptr) << "Entry " << i << " has null name";
        EXPECT_NE(tagList[i].title_, nullptr) << "Entry " << i << " has null title";
        EXPECT_NE(tagList[i].desc_, nullptr) << "Entry " << i << " has null desc";
    }
}

}  // namespace
