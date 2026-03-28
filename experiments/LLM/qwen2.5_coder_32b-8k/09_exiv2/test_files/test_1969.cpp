#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPMeta.hpp"

#include "XMP_Const.h"



class XMPMetaTest : public ::testing::Test {

protected:

    XMPMeta xmpMeta;

};



TEST_F(XMPMetaTest_1969, TouchUpDataModel_NoExifSchema_1969) {

    // Arrange

    // No EXIF schema in the XMP tree



    // Act

    TouchUpDataModel(&xmpMeta);



    // Assert

    EXPECT_FALSE(xmpMeta.DoesPropertyExist(kXMP_NS_EXIF, "exif:GPSTimeStamp"));

    EXPECT_FALSE(xmpMeta.DoesPropertyExist(kXMP_NS_EXIF, "exif:UserComment"));

}



TEST_F(XMPMetaTest_1969, TouchUpDataModel_ExifSchemaWithoutGPSDateTime_1969) {

    // Arrange

    xmpMeta.SetProperty(kXMP_NS_EXIF, "exif:UserComment", "Sample Comment", 0);



    // Act

    TouchUpDataModel(&xmpMeta);



    // Assert

    EXPECT_FALSE(xmpMeta.DoesPropertyExist(kXMP_NS_EXIF, "exif:GPSTimeStamp"));

    EXPECT_TRUE(xmpMeta.DoesPropertyExist(kXMP_NS_EXIF, "exif:UserComment"));



    XMP_StringPtr value;

    XMP_StringLen size;

    xmpMeta.GetProperty(kXMP_NS_EXIF, "exif:UserComment", &value, &size, nullptr);

    EXPECT_STREQ(value, "Sample Comment");



    // Verify that the UserComment is now an array with lang qualifier

    EXPECT_TRUE(xmpMeta.DoesArrayItemExist(kXMP_NS_EXIF, "exif:UserComment", 1));



    XMP_StringPtr itemValue;

    xmpMeta.GetArrayItem(kXMP_NS_EXIF, "exif:UserComment", 1, &itemValue, &size, nullptr);

    EXPECT_STREQ(itemValue, "Sample Comment");



    EXPECT_TRUE(xmpMeta.DoesQualifierExist(kXMP_NS_EXIF, "exif:UserComment[1]", "xml", "lang"));

}



TEST_F(XMPMetaTest_1969, TouchUpDataModel_ExifSchemaWithGPSDateTime_1969) {

    // Arrange

    xmpMeta.SetProperty(kXMP_NS_EXIF, "exif:GPSTimeStamp", "2023-10-01T12:34:56", 0);

    xmpMeta.SetProperty(kXMP_NS_EXIF, "exif:UserComment", "Sample Comment", 0);



    // Act

    TouchUpDataModel(&xmpMeta);



    // Assert

    EXPECT_TRUE(xmpMeta.DoesPropertyExist(kXMP_NS_EXIF, "exif:GPSTimeStamp"));

    EXPECT_TRUE(xmpMeta.DoesPropertyExist(kXMP_NS_EXIF, "exif:UserComment"));



    XMP_StringPtr value;

    XMP_StringLen size;

    xmpMeta.GetProperty(kXMP_NS_EXIF, "exif:UserComment", &value, &size, nullptr);

    EXPECT_STREQ(value, "");



    // Verify that the UserComment is now an array with lang qualifier

    EXPECT_TRUE(xmpMeta.DoesArrayItemExist(kXMP_NS_EXIF, "exif:UserComment", 1));



    XMP_StringPtr itemValue;

    xmpMeta.GetArrayItem(kXMP_NS_EXIF, "exif:UserComment", 1, &itemValue, &size, nullptr);

    EXPECT_STREQ(itemValue, "Sample Comment");



    EXPECT_TRUE(xmpMeta.DoesQualifierExist(kXMP_NS_EXIF, "exif:UserComment[1]", "xml", "lang"));

}



TEST_F(XMPMetaTest_1969, TouchUpDataModel_NoDMSchema_1969) {

    // Arrange

    // No DM schema in the XMP tree



    // Act

    TouchUpDataModel(&xmpMeta);



    // Assert

    EXPECT_FALSE(xmpMeta.DoesPropertyExist(kXMP_NS_DM, "xmpDM:copyright"));

}



TEST_F(XMPMetaTest_1969, TouchUpDataModel_DMSchemaWithoutCopyright_1969) {

    // Arrange

    xmpMeta.SetProperty(kXMP_NS_DC, "dc:title", "Sample Title", 0);



    // Act

    TouchUpDataModel(&xmpMeta);



    // Assert

    EXPECT_FALSE(xmpMeta.DoesPropertyExist(kXMP_NS_DM, "xmpDM:copyright"));

}



TEST_F(XMPMetaTest_1969, TouchUpDataModel_DCSubjectWithOrderedArray_1969) {

    // Arrange

    xmpMeta.SetProperty(kXMP_NS_DC, "dc:subject", "", kXMP_PropArrayIsOrdered);



    // Act

    TouchUpDataModel(&xmpMeta);



    // Assert

    XMP_OptionBits options;

    xmpMeta.GetProperty(kXMP_NS_DC, "dc:subject", nullptr, nullptr, &options);

    EXPECT_FALSE(options & kXMP_PropArrayIsOrdered);

}



TEST_F(XMPMetaTest_1969, TouchUpDataModel_RepairAltTextOnVariousProperties_1969) {

    // Arrange

    xmpMeta.SetProperty(kXMP_NS_DC, "dc:description", "Description", 0);

    xmpMeta.SetProperty(kXMP_NS_XMP_Rights, "xmpRights:UsageTerms", "Usage Terms", 0);



    // Act

    TouchUpDataModel(&xmpMeta);



    // Assert

    EXPECT_TRUE(xmpMeta.DoesPropertyExist(kXMP_NS_DC, "dc:description"));

    EXPECT_TRUE(xmpMeta.DoesPropertyExist(kXMP_NS_XMP_Rights, "xmpRights:UsageTerms"));

}



TEST_F(XMPMetaTest_1969, TouchUpDataModel_TreeNameIsUUID_1969) {

    // Arrange

    xmpMeta.SetObjectName("uuid:123e4567-e89b-12d3-a456-426614174000");



    // Act

    TouchUpDataModel(&xmpMeta);



    // Assert

    XMP_StringPtr value;

    XMP_StringLen size;

    xmpMeta.GetProperty(kXMP_NS_XMP_MM, "InstanceID", &value, &size, nullptr);

    EXPECT_STREQ(value, "uuid:123e4567-e89b-12d3-a456-426614174000");



    XMP_StringPtr name;

    xmpMeta.GetObjectName(&name, &size);

    EXPECT_STREQ(name, "");

}



TEST_F(XMPMetaTest_1969, TouchUpDataModel_TreeNameIsNotUUID_1969) {

    // Arrange

    xmpMeta.SetObjectName("not-a-uuid");



    // Act

    TouchUpDataModel(&xmpMeta);



    // Assert

    EXPECT_FALSE(xmpMeta.DoesPropertyExist(kXMP_NS_XMP_MM, "InstanceID"));



    XMP_StringPtr name;

    xmpMeta.GetObjectName(&name, &size);

    EXPECT_STREQ(name, "not-a-uuid");

}
