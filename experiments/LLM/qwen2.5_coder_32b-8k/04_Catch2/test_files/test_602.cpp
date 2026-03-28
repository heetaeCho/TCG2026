#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_list.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using ::testing::Eq;



class TagInfoTest_602 : public ::testing::Test {

protected:

    TagInfo tagInfo;

};



TEST_F(TagInfoTest_602, AddIncreasesCount_602) {

    StringRef spelling("test");

    tagInfo.add(spelling);

    EXPECT_EQ(tagInfo.count, 1);

}



TEST_F(TagInfoTest_602, AddUniqueSpelling_602) {

    StringRef spelling("unique");

    tagInfo.add(spelling);

    EXPECT_EQ(tagInfo.spellings.size(), 1);

}



TEST_F(TagInfoTest_602, AddDuplicateSpelling_602) {

    StringRef spelling("duplicate");

    tagInfo.add(spelling);

    tagInfo.add(spelling);

    EXPECT_EQ(tagInfo.count, 2);

    EXPECT_EQ(tagInfo.spellings.size(), 1);

}



TEST_F(TagInfoTest_602, AllReturnsEmptyStringWhenNoTags_602) {

    EXPECT_EQ(tagInfo.all(), "");

}



TEST_F(TagInfoTest_602, AllReturnsCorrectStringWithOneTag_602) {

    StringRef spelling("tag");

    tagInfo.add(spelling);

    EXPECT_EQ(tagInfo.all(), "tag");

}



TEST_F(TagInfoTest_602, AllReturnsConcatenatedTagsSorted_602) {

    StringRef tag1("zebra");

    StringRef tag2("apple");

    tagInfo.add(tag1);

    tagInfo.add(tag2);

    EXPECT_EQ(tagInfo.all(), "apple, zebra");

}



TEST_F(TagInfoTest_602, AddEmptyStringSpelling_602) {

    StringRef emptySpelling("");

    tagInfo.add(emptySpelling);

    EXPECT_EQ(tagInfo.spellings.size(), 1);

    EXPECT_EQ(tagInfo.count, 1);

}



TEST_F(TagInfoTest_602, AllHandlesMultipleEmptyStringsCorrectly_602) {

    StringRef emptySpelling("");

    tagInfo.add(emptySpelling);

    tagInfo.add(emptySpelling);

    EXPECT_EQ(tagInfo.spellings.size(), 1);

    EXPECT_EQ(tagInfo.count, 2);

    EXPECT_EQ(tagInfo.all(), "");

}
