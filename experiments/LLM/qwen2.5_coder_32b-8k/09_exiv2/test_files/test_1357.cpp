#include <gtest/gtest.h>

#include <vector>



// Assuming TagInfo is a struct or class defined somewhere in your codebase.

struct TagInfo {

    uint32_t tag;

    const char* tagName;

    const char* description;

    const char* section;

    IfdId ifdId;

    SectionId sectionId;

    DataType dataType;

    int count;

    PrintFunction printFunc;



    // Constructor for easy initialization

    TagInfo(uint32_t t, const char* tn, const char* d, const char* s, IfdId iifdId, SectionId isectionId, DataType idataType, int icount, PrintFunction iprintFunc)

        : tag(t), tagName(tn), description(d), section(s), ifdId(iifdId), sectionId(isectionId), dataType(idataType), count(icount), printFunc(iprintFunc) {}

};



// Mock print functions for testing purposes

void mockPrintValue(const TagInfo& /*tagInfo*/, const std::vector<uint8_t>& /*data*/) {}

void mockPrintFloat(const TagInfo& /*tagInfo*/, const std::vector<uint8_t>& /*data*/) {}



TEST(TagInfoTests, TestTagInitialization) {

    TagInfo tag(306, "DateTime", "Date and time of image creation.", "Image", IfdId::ifd0Id, SectionId::sectionIdNotSet, DataType::asciiString, -1, mockPrintValue);

    EXPECT_EQ(tag.tag, 306);

    EXPECT_STREQ(tag.tagName, "DateTime");

    EXPECT_STREQ(tag.description, "Date and time of image creation.");

    EXPECT_STREQ(tag.section, "Image");

    EXPECT_EQ(static_cast<int>(tag.ifdId), static_cast<int>(IfdId::ifd0Id));

    EXPECT_EQ(static_cast<int>(tag.sectionId), static_cast<int>(SectionId::sectionIdNotSet));

    EXPECT_EQ(static_cast<int>(tag.dataType), static_cast<int>(DataType::asciiString));

    EXPECT_EQ(tag.count, -1);

}



TEST(TagInfoTests, TestTagInitializationWithPrintFunction) {

    TagInfo tag(51109, "BaselineExposureOffset", "Provides a way for color profiles to increase or decrease exposure during raw conversion.", "Image", IfdId::ifd0Id, SectionId::sectionIdNotSet, DataType::signedRational, 1, mockPrintFloat);

    EXPECT_EQ(tag.tag, 51109);

    EXPECT_STREQ(tag.tagName, "BaselineExposureOffset");

    EXPECT_STREQ(tag.description, "Provides a way for color profiles to increase or decrease exposure during raw conversion.");

    EXPECT_STREQ(tag.section, "Image");

    EXPECT_EQ(static_cast<int>(tag.ifdId), static_cast<int>(IfdId::ifd0Id));

    EXPECT_EQ(static_cast<int>(tag.sectionId), static_cast<int>(SectionId::sectionIdNotSet));

    EXPECT_EQ(static_cast<int>(tag.dataType), static_cast<int>(DataType::signedRational));

    EXPECT_EQ(tag.count, 1);

}



TEST(TagInfoTests, TestTagInitializationWithLargeValues) {

    TagInfo tag(52538, "ReductionMatrix3", "ReductionMatrix3 defines a dimensionality reduction matrix for use as the first stage in converting color camera native space values to XYZ values, under the third calibration illuminant. This tag may only be used if ColorPlanes is greater than 3. The matrix is stored in row scan order.", "Image", IfdId::ifd0Id, SectionId::sectionIdNotSet, DataType::signedRational, -1, mockPrintValue);

    EXPECT_EQ(tag.tag, 52538);

    EXPECT_STREQ(tag.tagName, "ReductionMatrix3");

    EXPECT_STREQ(tag.description, "ReductionMatrix3 defines a dimensionality reduction matrix for use as the first stage in converting color camera native space values to XYZ values, under the third calibration illuminant. This tag may only be used if ColorPlanes is greater than 3. The matrix is stored in row scan order.");

    EXPECT_STREQ(tag.section, "Image");

    EXPECT_EQ(static_cast<int>(tag.ifdId), static_cast<int>(IfdId::ifd0Id));

    EXPECT_EQ(static_cast<int>(tag.sectionId), static_cast<int>(SectionId::sectionIdNotSet));

    EXPECT_EQ(static_cast<int>(tag.dataType), static_cast<int>(DataType::signedRational));

    EXPECT_EQ(tag.count, -1);

}



TEST(TagInfoTests, TestTagInitializationWithUnknownTag) {

    TagInfo tag(65535, "(UnknownIfdTag)", "Unknown IFD tag", "Image", IfdId::ifd0Id, SectionId::sectionIdNotSet, DataType::asciiString, -1, mockPrintValue);

    EXPECT_EQ(tag.tag, 65535);

    EXPECT_STREQ(tag.tagName, "(UnknownIfdTag)");

    EXPECT_STREQ(tag.description, "Unknown IFD tag");

    EXPECT_STREQ(tag.section, "Image");

    EXPECT_EQ(static_cast<int>(tag.ifdId), static_cast<int>(IfdId::ifd0Id));

    EXPECT_EQ(static_cast<int>(tag.sectionId), static_cast<int>(SectionId::sectionIdNotSet));

    EXPECT_EQ(static_cast<int>(tag.dataType), static_cast<int>(DataType::asciiString));

    EXPECT_EQ(tag.count, -1);

}
