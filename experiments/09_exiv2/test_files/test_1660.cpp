#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 { namespace Internal {



// Mock structure to simulate a list of TagInfo

struct MockTagList {

    TagInfo tags[4];

    MockTagList() {

        tags[0] = {SectionId::image, TypeId::unsignedShort, 1, nullptr};

        tags[1] = {SectionId::exif, TypeId::asciiString, 5, nullptr};

        tags[2] = {SectionId::gps, TypeId::rational, 3, nullptr};

        tags[3] = {0xffff, TypeId::undefined, 0, nullptr}; // End marker

    }

};



// Test fixture for the findTag function

class FindTagTest_1660 : public ::testing::Test {

protected:

    MockTagList mockTagList;

};



TEST_F(FindTagTest_1660, NormalOperation_TagFound_1660) {

    const TagInfo* result = findTag(mockTagList.tags, 0);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->tag_, 0); // Assuming tag_ is implicitly set to the index in this mock

}



TEST_F(FindTagTest_1660, NormalOperation_TagNotFound_1660) {

    const TagInfo* result = findTag(mockTagList.tags, 99);

    EXPECT_EQ(result, nullptr);

}



TEST_F(FindTagTest_1660, BoundaryCondition_FirstTag_1660) {

    const TagInfo* result = findTag(mockTagList.tags, mockTagList.tags[0].tag_);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->sectionId_, SectionId::image);

}



TEST_F(FindTagTest_1660, BoundaryCondition_LastTag_1660) {

    const TagInfo* result = findTag(mockTagList.tags, mockTagList.tags[2].tag_);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->sectionId_, SectionId::gps);

}



TEST_F(FindTagTest_1660, BoundaryCondition_EndMarker_1660) {

    const TagInfo* result = findTag(mockTagList.tags, 0xffff);

    EXPECT_EQ(result, nullptr); // End marker should not be returned

}



}} // namespace Exiv2::Internal
