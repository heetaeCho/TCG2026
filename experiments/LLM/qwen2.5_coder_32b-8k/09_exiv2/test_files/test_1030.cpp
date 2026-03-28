#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exif.hpp>

#include <exiv2/value.hpp>

#include "TestProjects/exiv2/src/minoltamn_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MinoltaSonyLocalAFAreaPointTest_1030 : public ::testing::Test {

protected:

    std::ostringstream oss;

    Value mockValue;

};



TEST_F(MinoltaSonyLocalAFAreaPointTest_1030, ValidTag_PrintsCorrectly_1030) {

    // Setup

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(1));



    // Exercise & Verify

    printMinoltaSonyLocalAFAreaPoint(oss, mockValue, nullptr);

    EXPECT_EQ("Center", oss.str());

}



TEST_F(MinoltaSonyLocalAFAreaPointTest_1030, InvalidTag_PrintsUnknown_1030) {

    // Setup

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(99));



    // Exercise & Verify

    printMinoltaSonyLocalAFAreaPoint(oss, mockValue, nullptr);

    EXPECT_EQ("(unknown)", oss.str());

}



TEST_F(MinoltaSonyLocalAFAreaPointTest_1030, BoundaryTag_PrintsCorrectly_1030) {

    // Setup

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(11));



    // Exercise & Verify

    printMinoltaSonyLocalAFAreaPoint(oss, mockValue, nullptr);

    EXPECT_EQ("Far-Left", oss.str());

}



TEST_F(MinoltaSonyLocalAFAreaPointTest_1030, ZeroTag_PrintsUnknown_1030) {

    // Setup

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(0));



    // Exercise & Verify

    printMinoltaSonyLocalAFAreaPoint(oss, mockValue, nullptr);

    EXPECT_EQ("(unknown)", oss.str());

}



TEST_F(MinoltaSonyLocalAFAreaPointTest_1030, MetadataNull_PrintsCorrectly_1030) {

    // Setup

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(2));



    // Exercise & Verify

    printMinoltaSonyLocalAFAreaPoint(oss, mockValue, nullptr);

    EXPECT_EQ("Top", oss.str());

}



TEST_F(MinoltaSonyLocalAFAreaPointTest_1030, MetadataNonNull_PrintsCorrectly_1030) {

    // Setup

    ExifData exifData;

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(3));



    // Exercise & Verify

    printMinoltaSonyLocalAFAreaPoint(oss, mockValue, &exifData);

    EXPECT_EQ("Top-Right", oss.str());

}



TEST_F(MinoltaSonyLocalAFAreaPointTest_1030, MultipleTags_PrintsCorrectly_1030) {

    // Setup

    ExifData exifData;

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(2))

                                      .WillOnce(::testing::Return(5));



    // Exercise & Verify

    printMinoltaSonyLocalAFAreaPoint(oss, mockValue, &exifData);

    EXPECT_EQ("Top\nBottom-Right", oss.str());

}
