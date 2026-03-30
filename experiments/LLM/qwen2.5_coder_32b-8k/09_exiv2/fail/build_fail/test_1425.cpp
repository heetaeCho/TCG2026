#include <gtest/gtest.h>

#include "tags_int.cpp"



namespace Exiv2 { namespace Internal {



class GroupListTest : public ::testing::Test {

protected:

    const GroupInfo* group_info_list = groupList();

};



TEST_F(GroupListTest, FirstElementIsNotSet_1425) {

    EXPECT_EQ(group_info_list[0].ifdId_, IfdId::ifdIdNotSet);

}



TEST_F(GroupListTest, SecondElementIsIFD0_1425) {

    EXPECT_EQ(group_info_list[1].ifdId_, IfdId::ifd0Id);

    EXPECT_STREQ(group_info_list[1].name_, "IFD0");

    EXPECT_STREQ(group_info_list[1].title_, "Image");

}



TEST_F(GroupListTest, LastElementIsLastId_1425) {

    const GroupInfo* last_element = group_info_list + 124; // Index of last element after increment

    EXPECT_EQ(last_element->ifdId_, IfdId::lastId);

    EXPECT_STREQ(last_element->name_, "(Last IFD info)");

    EXPECT_STREQ(last_element->title_, "(Last IFD item)");

}



TEST_F(GroupListTest, BoundaryConditionFirstElementNotNull_1425) {

    EXPECT_NE(group_info_list[0].tagList_, nullptr);

}



TEST_F(GroupListTest, BoundaryConditionLastElementTagListNull_1425) {

    const GroupInfo* last_element = group_info_list + 124; // Index of last element after increment

    EXPECT_EQ(last_element->tagList_, nullptr);

}



} }  // namespace Exiv2::Internal
