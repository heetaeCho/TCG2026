#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



// Mock the ExifData class if needed for testing

class MockExifData : public Exiv2::ExifData {

public:

    MOCK_CONST_METHOD0(begin, iterator());

    MOCK_CONST_METHOD0(end, iterator());

};



TEST(Nikon3MakerNoteTest_443, TagListCb2b_ReturnsValidPointer_443) {

    auto tagInfo = Nikon3MakerNote::tagListCb2b();

    EXPECT_NE(tagInfo, nullptr);

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintIiIso_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printIiIso(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, Print0x0002_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::print0x0002(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintAf2AreaMode_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printAf2AreaMode(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, Print0x0007_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::print0x0007(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, Print0x0083_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::print0x0083(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, Print0x0084_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::print0x0084(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, Print0x0085_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::print0x0085(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, Print0x0086_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::print0x0086(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, Print0x0088_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::print0x0088(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintAfPointsInFocus_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printAfPointsInFocus(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, Print0x0089_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::print0x0089(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, Print0x008b_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::print0x008b(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintLensId1_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printLensId1(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintLensId2_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printLensId2(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintLensId3_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printLensId3(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintLensId4_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printLensId4(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintLensId_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printLensId(os, value, &metadata, "SampleGroup");

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFocusDistance_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFocusDistance(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintAperture_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printAperture(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFocal_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFocal(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFStops_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFStops(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintExitPupilPosition_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printExitPupilPosition(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFlashFocalLength_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFlashFocalLength(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintRepeatingFlashRate_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printRepeatingFlashRate(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintRepeatingFlashCount_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printRepeatingFlashCount(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintExternalFlashData1Fl6_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintExternalFlashData2Fl6_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printExternalFlashData2Fl6(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintExternalFlashData1Fl7_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printExternalFlashData1Fl7(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintExternalFlashData2_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printExternalFlashData2(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFlashMasterDataFl6_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFlashMasterDataFl6(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFlashMasterDataFl7_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFlashMasterDataFl7(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFlashGroupAControlData_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFlashGroupAControlData(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFlashGroupBCControlData_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFlashGroupBCControlData(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFlashGroupADataFl6_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFlashGroupADataFl6(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFlashGroupADataFl7_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFlashGroupADataFl7(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFlashGroupBDataFl6_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFlashGroupBDataFl6(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFlashGroupBDataFl7_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFlashGroupBDataFl7(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFlashGroupCDataFl6_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFlashGroupCDataFl6(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFlashGroupCDataFl7_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFlashGroupCDataFl7(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintExternalFlashData3_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printExternalFlashData3(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintCameraExposureCompensation_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printCameraExposureCompensation(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintExternalFlashData4_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printExternalFlashData4(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFlashZoomHeadPosition_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFlashZoomHeadPosition(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintTimeZone_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printTimeZone(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintPictureControl_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printPictureControl(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, Print0x009a_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::print0x009a(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, Print0x009e_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::print0x009e(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintApertureLd4_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printApertureLd4(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFocalLd4_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFocal(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctionsTest_443, PrintFocusDistanceLd4_NormalOperation_443) {

    std::ostringstream os;

    MockExifData metadata;

    Exiv2::Value value; // Assuming Value can be default constructed



    Nikon3MakerNote::printFocusDistance(os, value, &metadata);

    EXPECT_FALSE(os.str().empty());

}
