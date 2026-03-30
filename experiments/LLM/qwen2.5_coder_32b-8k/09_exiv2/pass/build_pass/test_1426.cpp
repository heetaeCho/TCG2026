#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {

    namespace Internal {

        const TagInfo* tagList(const std::string& groupName);

    }

}



using namespace Exiv2;

using namespace Exiv2::Internal;



class TagListTest_1426 : public ::testing::Test {};



TEST_F(TagListTest_1426, ValidGroupName_ReturnsTagList_1426) {

    const char* expectedGroupName = "Image";

    const TagInfo* result = tagList(expectedGroupName);

    ASSERT_NE(result, nullptr);

}



TEST_F(TagListTest_1426, ValidGroupName_ReturnsCorrectTagList_1426) {

    const char* expectedGroupName = "Exif";

    const TagInfo* result = tagList(expectedGroupName);

    ASSERT_NE(result, nullptr);

}



TEST_F(TagListTest_1426, InvalidGroupName_ReturnsNullptr_1426) {

    const char* invalidGroupName = "NonExistentGroup";

    const TagInfo* result = tagList(invalidGroupName);

    EXPECT_EQ(result, nullptr);

}



TEST_F(TagListTest_1426, EmptyGroupName_ReturnsNullptr_1426) {

    const std::string emptyGroupName = "";

    const TagInfo* result = tagList(emptyGroupName);

    EXPECT_EQ(result, nullptr);

}



TEST_F(TagListTest_1426, BoundaryCase_GroupNameAtStart_ReturnsTagList_1426) {

    const char* expectedGroupName = "Unknown";

    const TagInfo* result = tagList(expectedGroupName);

    ASSERT_NE(result, nullptr);

}



TEST_F(TagListTest_1426, BoundaryCase_GroupNameAtEnd_ReturnsTagList_1426) {

    const char* expectedGroupName = "(Last IFD item)";

    const TagInfo* result = tagList(expectedGroupName);

    EXPECT_EQ(result, nullptr); // The last entry has a null tagList_

}
