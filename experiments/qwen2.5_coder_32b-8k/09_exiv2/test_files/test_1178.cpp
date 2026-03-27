#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffimage_int.cpp"



using namespace Exiv2::Internal;



class TiffHeaderBaseTest : public ::testing::Test {

protected:

    TiffHeaderBase tiffHeaderBase;

};



TEST_F(TiffHeaderBaseTest_1178, IsImageTag_ReturnsFalseForArbitraryInput_1178) {

    uint16_t tag = 256; // Arbitrary tag value

    IfdId group = ifd0Id; // Arbitrary IFD group

    PrimaryGroups primaryGroups; // Assuming default constructed is valid



    bool result = tiffHeaderBase.isImageTag(tag, group, primaryGroups);



    EXPECT_FALSE(result);

}



TEST_F(TiffHeaderBaseTest_1178, IsImageTag_ReturnsFalseForBoundaryTagValue_1178) {

    uint16_t tag = 0; // Boundary tag value

    IfdId group = ifd0Id; // Arbitrary IFD group

    PrimaryGroups primaryGroups; // Assuming default constructed is valid



    bool result = tiffHeaderBase.isImageTag(tag, group, primaryGroups);



    EXPECT_FALSE(result);

}



TEST_F(TiffHeaderBaseTest_1178, IsImageTag_ReturnsFalseForMaximumTagValue_1178) {

    uint16_t tag = 65535; // Maximum possible value for a uint16_t

    IfdId group = ifd0Id; // Arbitrary IFD group

    PrimaryGroups primaryGroups; // Assuming default constructed is valid



    bool result = tiffHeaderBase.isImageTag(tag, group, primaryGroups);



    EXPECT_FALSE(result);

}



TEST_F(TiffHeaderBaseTest_1178, IsImageTag_ReturnsFalseForVariousIFdIds_1178) {

    uint16_t tag = 256; // Arbitrary tag value

    PrimaryGroups primaryGroups; // Assuming default constructed is valid



    bool resultIfd0 = tiffHeaderBase.isImageTag(tag, ifd0Id, primaryGroups);

    bool resultExif = tiffHeaderBase.isImageTag(tag, exifId, primaryGroups);

    bool resultGps = tiffHeaderBase.isImageTag(tag, gpsId, primaryGroups);

    bool resultIop = tiffHeaderBase.isImageTag(tag, iopId, primaryGroups);



    EXPECT_FALSE(resultIfd0);

    EXPECT_FALSE(resultExif);

    EXPECT_FALSE(resultGps);

    EXPECT_FALSE(resultIop);

}
