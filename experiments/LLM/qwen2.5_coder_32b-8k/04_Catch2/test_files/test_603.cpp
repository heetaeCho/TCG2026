#include <gtest/gtest.h>

#include "catch_list.hpp"

#include "catch_stringref.hpp"



using namespace Catch;



class TagInfoTest_603 : public ::testing::Test {

protected:

    TagInfo tagInfo;

};



TEST_F(TagInfoTest_603, AddSingleSpelling_603) {

    StringRef spelling("test");

    tagInfo.add(spelling);

    EXPECT_EQ(tagInfo.all(), "[test]");

}



TEST_F(TagInfoTest_603, AddMultipleSpellings_603) {

    StringRef spelling1("test1");

    StringRef spelling2("test2");

    tagInfo.add(spelling1);

    tagInfo.add(spelling2);

    EXPECT_EQ(tagInfo.all(), "[test1][test2]");

}



TEST_F(TagInfoTest_603, AddDuplicateSpelling_603) {

    StringRef spelling("duplicate");

    tagInfo.add(spelling);

    tagInfo.add(spelling);

    EXPECT_EQ(tagInfo.all(), "[duplicate]");

}



TEST_F(TagInfoTest_603, AllWithNoSpellings_603) {

    EXPECT_EQ(tagInfo.all(), "");

}



TEST_F(TagInfoTest_603, AddEmptySpelling_603) {

    StringRef emptySpelling("");

    tagInfo.add(emptySpelling);

    EXPECT_EQ(tagInfo.all(), "[]");

}
