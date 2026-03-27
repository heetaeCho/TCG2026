#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



// Mocking the tagList function to simulate external behavior

class TagListMock {

public:

    MOCK_METHOD1(tagList, const TagInfo*(IfdId ifdId));

};



// Global mock object for testing

TagListMock* g_tagListMock = nullptr;



// Replacing the actual tagList function with a mock version

const TagInfo* tagList(IfdId ifdId) {

    return g_tagListMock->tagList(ifdId);

}



class TagInfoTest_1367 : public ::testing::Test {

protected:

    void SetUp() override {

        g_tagListMock = new TagListMock();

    }



    void TearDown() override {

        delete g_tagListMock;

        g_tagListMock = nullptr;

    }

};



TEST_F(TagInfoTest_1367, FindExistingTag_1367) {

    IfdId ifdId = IfdId::ifdExif;

    uint16_t tag = 0x9003; // Example tag

    TagInfo expectedTagInfo = {SectionId::exifIFD, TypeId::asciiString, 42, nullptr};



    EXPECT_CALL(*g_tagListMock, tagList(ifdId))

        .WillOnce(::testing::Return(&expectedTagInfo));



    const TagInfo* result = tagInfo(tag, ifdId);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->sectionId_, expectedTagInfo.sectionId_);

    EXPECT_EQ(result->typeId_, expectedTagInfo.typeId_);

    EXPECT_EQ(result->count_, expectedTagInfo.count_);

}



TEST_F(TagInfoTest_1367, FindNonExistingTag_1367) {

    IfdId ifdId = IfdId::ifdExif;

    uint16_t tag = 0xFFFF; // Non-existing tag



    TagInfo emptyTagInfoList[] = {{SectionId::maxSectionId, TypeId::undefined, -1, nullptr}, {0xFFFF, TypeId::undefined, -1, nullptr}};

    EXPECT_CALL(*g_tagListMock, tagList(ifdId))

        .WillOnce(::testing::Return(emptyTagInfoList));



    const TagInfo* result = tagInfo(tag, ifdId);

    ASSERT_EQ(result, &emptyTagInfoList[1]); // Should return the last element with 0xFFFF

}



TEST_F(TagInfoTest_1367, NullTagList_1367) {

    IfdId ifdId = IfdId::ifdExif;

    uint16_t tag = 0x9003; // Example tag



    EXPECT_CALL(*g_tagListMock, tagList(ifdId))

        .WillOnce(::testing::Return(nullptr));



    const TagInfo* result = tagInfo(tag, ifdId);

    ASSERT_EQ(result, nullptr);

}



TEST_F(TagInfoTest_1367, BoundaryConditionFirstTag_1367) {

    IfdId ifdId = IfdId::ifdExif;

    uint16_t tag = 0x9000; // First tag in the list

    TagInfo firstTagInfo = {SectionId::exifIFD, TypeId::asciiString, 42, nullptr};



    TagInfo tagInfoList[] = {{firstTagInfo}, {SectionId::maxSectionId, TypeId::undefined, -1, nullptr}, {0xFFFF, TypeId::undefined, -1, nullptr}};

    EXPECT_CALL(*g_tagListMock, tagList(ifdId))

        .WillOnce(::testing::Return(tagInfoList));



    const TagInfo* result = tagInfo(tag, ifdId);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->sectionId_, firstTagInfo.sectionId_);

    EXPECT_EQ(result->typeId_, firstTagInfo.typeId_);

    EXPECT_EQ(result->count_, firstTagInfo.count_);

}



TEST_F(TagInfoTest_1367, BoundaryConditionLastTag_1367) {

    IfdId ifdId = IfdId::ifdExif;

    uint16_t tag = 0x90FF; // Last tag in the list

    TagInfo lastTagInfo = {SectionId::exifIFD, TypeId::asciiString, 42, nullptr};



    TagInfo tagInfoList[] = {{SectionId::maxSectionId, TypeId::undefined, -1, nullptr}, {lastTagInfo}, {0xFFFF, TypeId::undefined, -1, nullptr}};

    EXPECT_CALL(*g_tagListMock, tagList(ifdId))

        .WillOnce(::testing::Return(tagInfoList));



    const TagInfo* result = tagInfo(tag, ifdId);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->sectionId_, lastTagInfo.sectionId_);

    EXPECT_EQ(result->typeId_, lastTagInfo.typeId_);

    EXPECT_EQ(result->count_, lastTagInfo.count_);

}
