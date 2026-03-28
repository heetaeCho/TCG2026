#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



namespace {



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Ref;



class Nikon3MakerNoteTest_441 : public testing::Test {

protected:

    Value dummyValue;

    const ExifData* dummyMetadata = nullptr;

};



TEST_F(Nikon3MakerNoteTest_441, Print0x0002_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0002(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintAf2AreaMode_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printAf2AreaMode(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, Print0x0007_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0007(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, Print0x0083_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0083(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, Print0x0084_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0084(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, Print0x0085_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0085(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, Print0x0086_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0086(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, Print0x0088_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0088(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintAfPointsInFocus_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printAfPointsInFocus(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, Print0x0089_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::print0x0089(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, Print0x008b_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::print0x008b(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintLensId1_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId1(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintLensId2_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId2(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintLensId3_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId3(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintLensId4_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId4(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintLensId_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId(os, dummyValue, dummyMetadata, "SampleGroup");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFocusDistance_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFocusDistance(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintAperture_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printAperture(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFocal_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFocal(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFStops_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFStops(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintExitPupilPosition_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printExitPupilPosition(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintIiIso_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printIiIso(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFlashFocalLength_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashFocalLength(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintRepeatingFlashRate_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printRepeatingFlashRate(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintRepeatingFlashCount_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printRepeatingFlashCount(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintExternalFlashData1Fl6_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData1Fl6(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintExternalFlashData2Fl6_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData2Fl6(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintExternalFlashData1Fl7_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData1Fl7(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintExternalFlashData2_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData2(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFlashMasterDataFl6_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashMasterDataFl6(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFlashMasterDataFl7_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashMasterDataFl7(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupAControlData_DataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupAControlData(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupBCControlData_DataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBCControlData(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupADataFl6_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupADataFl6(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupADataFl7_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupADataFl7(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupBDataFl6_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBDataFl6(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupBDataFl7_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupBDataFl7(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupCDataFl6_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupCDataFl6(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFlashGroupCDataFl7_MetadataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashGroupCDataFl7(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintExternalFlashData3_DataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData3(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintCameraExposureCompensation_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printCameraExposureCompensation(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintExternalFlashData4_DataNullptr_441) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData4(os, dummyValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFlashZoomHeadPosition_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashZoomHeadPosition(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintTimeZone_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printTimeZone(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintPictureControl_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printPictureControl(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, Print0x009a_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::print0x009a(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, Print0x009e_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::print0x009e(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintApertureLd4_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printApertureLd4(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFocalLd4_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFocalLd4(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_441, PrintFocusDistanceLd4_NormalOperation_441) {

    std::ostringstream os;

    Nikon3MakerNote::printFocusDistanceLd4(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



}  // namespace
