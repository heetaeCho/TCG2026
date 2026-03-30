#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming TagInfo structure definition is available somewhere in the codebase

namespace Exiv2 {

namespace Internal {



struct TagInfo {

    int tag;

    const char* name;

    const char* title;

    const char* description;

    IfdId ifdId;

    SectionId sectionId;

    TypeId typeId;

    int count;

    void (*printFunction)(const Value*);

};



const TagInfo iopTagInfo[6] = {

    {1, "InteroperabilityIndex", "Interoperability Index", "Indicates the identification of the Interoperability rule. Use \"R98\" for stating ExifR98 Rules. Four bytes used including the termination code (NULL). see the separate volume of Recommended Exif Interoperability Rules (ExifR98) for other tags used for ExifR98.", IfdId::iopId, SectionId::iopTags, asciiString, 0, nullptr},

    {2, "InteroperabilityVersion", "Interoperability Version", "Interoperability version", IfdId::iopId, SectionId::iopTags, undefined, -1, nullptr},

    {4096, "RelatedImageFileFormat", "Related Image File Format", "File format of image file", IfdId::iopId, SectionId::iopTags, asciiString, 0, nullptr},

    {4097, "RelatedImageWidth", "Related Image Width", "Image width", IfdId::iopId, SectionId::iopTags, unsignedLong, 1, nullptr},

    {4098, "RelatedImageLength", "Related Image Length", "Image height", IfdId::iopId, SectionId::iopTags, unsignedLong, 1, nullptr},

    {65535, "(UnknownIopTag)", "Unknown Exif Interoperability tag", "Unknown Exif Interoperability tag", IfdId::iopId, SectionId::iopTags, asciiString, -1, nullptr}

};



const TagInfo* iopTagList() {

    return iopTagInfo;

}



}  // namespace Internal

}  // namespace Exiv2



class IopTagListTest_1361 : public ::testing::Test {

protected:

    void SetUp() override {

        tagList = Exiv2::Internal::iopTagList();

    }



    const Exiv2::Internal::TagInfo* tagList;

};



TEST_F(IopTagListTest_1361, ReturnsNonNullPointer_1361) {

    EXPECT_NE(tagList, nullptr);

}



TEST_F(IopTagListTest_1361, CorrectNumberOfTags_1361) {

    int count = 0;

    while (tagList[count].name != nullptr && tagList[count].tag != 65535) {

        ++count;

    }

    EXPECT_EQ(count, 6);

}



TEST_F(IopTagListTest_1361, FirstTagCorrect_1361) {

    const Exiv2::Internal::TagInfo& firstTag = tagList[0];

    EXPECT_EQ(firstTag.tag, 1);

    EXPECT_STREQ(firstTag.name, "InteroperabilityIndex");

    EXPECT_STREQ(firstTag.title, "Interoperability Index");

    EXPECT_STREQ(firstTag.description, "Indicates the identification of the Interoperability rule. Use \"R98\" for stating ExifR98 Rules. Four bytes used including the termination code (NULL). see the separate volume of Recommended Exif Interoperability Rules (ExifR98) for other tags used for ExifR98.");

}



TEST_F(IopTagListTest_1361, LastTagCorrect_1361) {

    const Exiv2::Internal::TagInfo& lastTag = tagList[5];

    EXPECT_EQ(lastTag.tag, 65535);

    EXPECT_STREQ(lastTag.name, "(UnknownIopTag)");

    EXPECT_STREQ(lastTag.title, "Unknown Exif Interoperability tag");

    EXPECT_STREQ(lastTag.description, "Unknown Exif Interoperability tag");

}



TEST_F(IopTagListTest_1361, MiddleTagCorrect_1361) {

    const Exiv2::Internal::TagInfo& middleTag = tagList[2];

    EXPECT_EQ(middleTag.tag, 4096);

    EXPECT_STREQ(middleTag.name, "RelatedImageFileFormat");

    EXPECT_STREQ(middleTag.title, "Related Image File Format");

    EXPECT_STREQ(middleTag.description, "File format of image file");

}



TEST_F(IopTagListTest_1361, BoundaryConditionFirstElement_1361) {

    const Exiv2::Internal::TagInfo& boundaryTag = tagList[0];

    EXPECT_EQ(boundaryTag.tag, 1);

    EXPECT_STREQ(boundaryTag.name, "InteroperabilityIndex");

}



TEST_F(IopTagListTest_1361, BoundaryConditionLastElement_1361) {

    const Exiv2::Internal::TagInfo& boundaryTag = tagList[5];

    EXPECT_EQ(boundaryTag.tag, 65535);

    EXPECT_STREQ(boundaryTag.name, "(UnknownIopTag)");

}
