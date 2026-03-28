#include <gtest/gtest.h>

#include "samsungmn_int.hpp"



using namespace Exiv2::Internal;



class Samsung2MakerNoteTest_1354 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if necessary

};



TEST_F(Samsung2MakerNoteTest_1354, TagList_ReturnsExpectedPointer_1354) {

    auto result = Samsung2MakerNote::tagList();

    EXPECT_NE(result, nullptr);

}



TEST_F(Samsung2MakerNoteTest_1354, TagListPw_ReturnsExpectedPointer_1354) {

    auto result = Samsung2MakerNote::tagListPw();

    EXPECT_NE(result, nullptr);

}



// Assuming tagList and tagListPw are meant to return different pointers

TEST_F(Samsung2MakerNoteTest_1354, TagListAndTagListPw_ReturnDifferentPointers_1354) {

    auto tagListResult = Samsung2MakerNote::tagList();

    auto tagListPwResult = Samsung2MakerNote::tagListPw();

    EXPECT_NE(tagListResult, tagListPwResult);

}
