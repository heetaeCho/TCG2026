#include <gtest/gtest.h>

#include "XMPMeta-Parse.cpp"

#include "XMPCore_Impl.hpp"

#include "XMPUtils.hpp"



using namespace std;



class FixGPSTimeStampTest_1966 : public ::testing::Test {

protected:

    XMP_Node exifSchema;

    XMP_Node gpsDateTime;



    void SetUp() override {

        exifSchema = XMP_Node(nullptr, "exif", 0);

        gpsDateTime = XMP_Node(&exifSchema, "GPSDateTime", "", 0);

    }



    void TearDown() override {

        exifSchema.RemoveChildren();

        exifSchema.RemoveQualifiers();

        gpsDateTime.RemoveChildren();

        gpsDateTime.RemoveQualifiers();

    }

};



TEST_F(FixGPSTimeStampTest_1966, NormalOperation_GoodDate_1966) {

    XMP_Node dateTimeOriginal = XMP_Node(&exifSchema, "exif:DateTimeOriginal", "2023:04:15T12:34:56", 0);

    exifSchema.children.push_back(dateTimeOriginal);



    FixGPSTimeStamp(&exifSchema, &gpsDateTime);



    EXPECT_EQ(gpsDateTime.value, "2023-04-15");

}



TEST_F(FixGPSTimeStampTest_1966, NormalOperation_GoodDateInDigitized_1966) {

    XMP_Node dateTimeDigitized = XMP_Node(&exifSchema, "exif:DateTimeDigitized", "2023:04:15T12:34:56", 0);

    exifSchema.children.push_back(dateTimeDigitized);



    FixGPSTimeStamp(&exifSchema, &gpsDateTime);



    EXPECT_EQ(gpsDateTime.value, "2023-04-15");

}



TEST_F(FixGPSTimeStampTest_1966, BoundaryCondition_EmptyGPSDate_1966) {

    XMP_Node dateTimeOriginal = XMP_Node(&exifSchema, "exif:DateTimeOriginal", "", 0);

    exifSchema.children.push_back(dateTimeOriginal);



    FixGPSTimeStamp(&exifSchema, &gpsDateTime);



    EXPECT_EQ(gpsDateTime.value, "");

}



TEST_F(FixGPSTimeStampTest_1966, BoundaryCondition_NoDateNodes_1966) {

    FixGPSTimeStamp(&exifSchema, &gpsDateTime);



    EXPECT_EQ(gpsDateTime.value, "");

}



TEST_F(FixGPSTimeStampTest_1966, ExceptionalCase_BadOriginalDate_1966) {

    XMP_Node dateTimeOriginal = XMP_Node(&exifSchema, "exif:DateTimeOriginal", "invalid-date", 0);

    exifSchema.children.push_back(dateTimeOriginal);



    FixGPSTimeStamp(&exifSchema, &gpsDateTime);



    EXPECT_EQ(gpsDateTime.value, "");

}



TEST_F(FixGPSTimeStampTest_1966, ExceptionalCase_BadDigitizedDate_1966) {

    XMP_Node dateTimeDigitized = XMP_Node(&exifSchema, "exif:DateTimeDigitized", "invalid-date", 0);

    exifSchema.children.push_back(dateTimeDigitized);



    FixGPSTimeStamp(&exifSchema, &gpsDateTime);



    EXPECT_EQ(gpsDateTime.value, "");

}
