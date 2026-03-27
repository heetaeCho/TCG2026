#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



namespace {



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Ref;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(Nikon3MakerNoteTest, tagListSi4_ReturnsExpectedTagInfo_438) {

    auto result = Nikon3MakerNote::tagListSi4();

    EXPECT_NE(result, nullptr);

}



TEST_F(Nikon3MakerNoteTest, printIiIso_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printIiIso(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, print0x0002_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printAf2AreaMode_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printAf2AreaMode(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, print0x0007_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0007(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, print0x0083_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0083(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, print0x0084_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0084(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, print0x0085_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0085(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, print0x0086_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0086(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, print0x0088_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0088(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printAfPointsInFocus_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printAfPointsInFocus(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, print0x0089_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0089(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, print0x008b_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::print0x008b(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printLensId1_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId1(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printLensId2_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId2(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printLensId3_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId3(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printLensId4_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printLensId_GroupProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId(os, mockValue, &mockMetadata, "GROUP");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFocusDistance_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFocusDistance(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printAperture_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printAperture(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFocal_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFocal(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFStops_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFStops(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printExitPupilPosition_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printExitPupilPosition(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFlashFocalLength_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashFocalLength(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printRepeatingFlashRate_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printRepeatingFlashRate(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printRepeatingFlashCount_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printRepeatingFlashCount(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printExternalFlashData1Fl6_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData1Fl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printExternalFlashData2Fl6_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData2Fl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printExternalFlashData1Fl7_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData1Fl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printExternalFlashData2_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData2(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFlashMasterDataFl6_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashMasterDataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFlashMasterDataFl7_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashMasterDataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFlashGroupAControlData_DataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupAControlData(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFlashGroupBCControlData_DataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBCControlData(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFlashGroupADataFl6_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFlashGroupADataFl7_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupADataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFlashGroupBDataFl6_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBDataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFlashGroupBDataFl7_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBDataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFlashGroupCDataFl6_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupCDataFl6(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFlashGroupCDataFl7_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupCDataFl7(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printExternalFlashData3_DataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData3(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printCameraExposureCompensation_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printCameraExposureCompensation(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printExternalFlashData4_MetadataProvided_438) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFlashZoomHeadPosition_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashZoomHeadPosition(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printTimeZone_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printTimeZone(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printPictureControl_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printPictureControl(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, print0x009a_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::print0x009a(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, print0x009e_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::print0x009e(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printApertureLd4_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printApertureLd4(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFocalLd4_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFocalLd4(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, printFocusDistanceLd4_NormalOperation_438) {

    std::ostringstream os;

    Nikon3MakerNote::printFocusDistanceLd4(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



}  // namespace
