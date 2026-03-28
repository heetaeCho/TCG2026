#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Nikon3MakerNoteTest() = default;

    ~Nikon3MakerNoteTest() override = default;



    std::ostringstream oss;

    Value dummyValue; // Assuming Value is some type defined elsewhere

    ExifData* mockExifData = nullptr; // Assuming ExifData is some type defined elsewhere

};



TEST_F(Nikon3MakerNoteTest, TagListFl3_ReturnsValidPointer_432) {

    const auto& tagList = Nikon3MakerNote::tagListFl3();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(Nikon3MakerNoteTest, Print0x0002_NormalOperation_432) {

    Nikon3MakerNote::print0x0002(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printAf2AreaMode(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0007_NormalOperation_432) {

    Nikon3MakerNote::print0x0007(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0083_NormalOperation_432) {

    Nikon3MakerNote::print0x0083(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0084_NormalOperation_432) {

    Nikon3MakerNote::print0x0084(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0085_NormalOperation_432) {

    Nikon3MakerNote::print0x0085(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0086_NormalOperation_432) {

    Nikon3MakerNote::print0x0086(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0088_NormalOperation_432) {

    Nikon3MakerNote::print0x0088(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAfPointsInFocus_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printAfPointsInFocus(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0089_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::print0x0089(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x008b_NormalOperation_432) {

    Nikon3MakerNote::print0x008b(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId1_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printLensId1(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId2_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printLensId2(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId3_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printLensId3(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId4_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printLensId4(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId_NormalOperationWithMetadataAndGroup_432) {

    ExifData exifData;

    Nikon3MakerNote::printLensId(oss, dummyValue, &exifData, "group");

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistance_NormalOperation_432) {

    Nikon3MakerNote::printFocusDistance(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAperture_NormalOperation_432) {

    Nikon3MakerNote::printAperture(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocal_NormalOperation_432) {

    Nikon3MakerNote::printFocal(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFStops_NormalOperation_432) {

    Nikon3MakerNote::printFStops(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExitPupilPosition_NormalOperation_432) {

    Nikon3MakerNote::printExitPupilPosition(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashFocalLength_NormalOperation_432) {

    Nikon3MakerNote::printFlashFocalLength(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashRate_NormalOperation_432) {

    Nikon3MakerNote::printRepeatingFlashRate(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashCount_NormalOperation_432) {

    Nikon3MakerNote::printRepeatingFlashCount(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printExternalFlashData1Fl6(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2Fl6_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printExternalFlashData2Fl6(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl7_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printExternalFlashData1Fl7(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printExternalFlashData2(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashMasterDataFl6_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printFlashMasterDataFl6(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashMasterDataFl7_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printFlashMasterDataFl7(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupAControlData_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printFlashGroupAControlData(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBCControlData_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printFlashGroupBCControlData(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupADataFl6_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printFlashGroupADataFl6(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupADataFl7_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printFlashGroupADataFl7(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBDataFl6_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printFlashGroupBDataFl6(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBDataFl7_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printFlashGroupBDataFl7(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupCDataFl6_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printFlashGroupCDataFl6(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupCDataFl7_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printFlashGroupCDataFl7(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData3_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printExternalFlashData3(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintCameraExposureCompensation_NormalOperation_432) {

    Nikon3MakerNote::printCameraExposureCompensation(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData4_NormalOperationWithMetadata_432) {

    ExifData exifData;

    Nikon3MakerNote::printExternalFlashData4(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashZoomHeadPosition_NormalOperation_432) {

    Nikon3MakerNote::printFlashZoomHeadPosition(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintTimeZone_NormalOperation_432) {

    Nikon3MakerNote::printTimeZone(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintPictureControl_NormalOperation_432) {

    Nikon3MakerNote::printPictureControl(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x009a_NormalOperation_432) {

    Nikon3MakerNote::print0x009a(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x009e_NormalOperation_432) {

    Nikon3MakerNote::print0x009e(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintIiIso_NormalOperation_432) {

    Nikon3MakerNote::printIiIso(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintApertureLd4_NormalOperation_432) {

    Nikon3MakerNote::printApertureLd4(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocalLd4_NormalOperation_432) {

    Nikon3MakerNote::printFocalLd4(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistanceLd4_NormalOperation_432) {

    Nikon3MakerNote::printFocusDistanceLd4(oss, dummyValue, mockExifData);

    EXPECT_FALSE(oss.str().empty());

}
