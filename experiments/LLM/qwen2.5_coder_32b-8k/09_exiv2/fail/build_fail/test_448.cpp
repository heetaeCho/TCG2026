#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



// Mocking Value and ExifData as they are not provided in the interface.

class MockValue : public Exiv2::Value {

public:

    MOCK_CONST_METHOD0(typeName, std::string());

    MOCK_CONST_METHOD0(count, size_t());

};



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_CONST_METHOD1(findKey, const_iterator(const Exiv2::ExifKey&));

};



TEST(Nikon3MakerNoteTest_448, TagListLd3_ReturnsConstantValue_448) {

    auto result = Nikon3MakerNote::tagListLd3();

    EXPECT_NE(result, nullptr);

}



TEST(Nikon3MakerNoteTest_448, PrintIiIso_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printIiIso(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, Print0x0002_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::print0x0002(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintAf2AreaMode_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printAf2AreaMode(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, Print0x0007_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::print0x0007(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, Print0x0083_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::print0x0083(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, Print0x0084_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::print0x0084(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, Print0x0085_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::print0x0085(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, Print0x0086_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::print0x0086(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, Print0x0088_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::print0x0088(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintAfPointsInFocus_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printAfPointsInFocus(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, Print0x0089_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::print0x0089(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, Print0x008b_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::print0x008b(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintLensId1_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printLensId1(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintLensId2_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printLensId2(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintLensId3_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printLensId3(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintLensId4_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printLensId4(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintLensId_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printLensId(os, mockValue, &mockMetadata, "group");



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFocusDistance_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFocusDistance(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintAperture_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printAperture(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFocal_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFocal(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFStops_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFStops(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintExitPupilPosition_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printExitPupilPosition(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFlashFocalLength_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFlashFocalLength(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintRepeatingFlashRate_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printRepeatingFlashRate(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintRepeatingFlashCount_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printRepeatingFlashCount(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintExternalFlashData1Fl6_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printExternalFlashData1Fl6(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintExternalFlashData2Fl6_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printExternalFlashData2Fl6(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintExternalFlashData1Fl7_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printExternalFlashData1Fl7(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintExternalFlashData2_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printExternalFlashData2(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFlashMasterDataFl6_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFlashMasterDataFl6(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFlashMasterDataFl7_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFlashMasterDataFl7(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFlashGroupAControlData_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFlashGroupAControlData(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFlashGroupBCControlData_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFlashGroupBCControlData(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFlashGroupADataFl6_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFlashGroupADataFl7_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFlashGroupADataFl7(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFlashGroupBDataFl6_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFlashGroupBDataFl6(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFlashGroupBDataFl7_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFlashGroupBDataFl7(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFlashGroupCDataFl6_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFlashGroupCDataFl6(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFlashGroupCDataFl7_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFlashGroupCDataFl7(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintExternalFlashData3_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printExternalFlashData3(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintCameraExposureCompensation_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printCameraExposureCompensation(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintExternalFlashData4_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printExternalFlashData4(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFlashZoomHeadPosition_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFlashZoomHeadPosition(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintTimeZone_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printTimeZone(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintPictureControl_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printPictureControl(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, Print0x009a_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::print0x009a(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, Print0x009e_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::print0x009e(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintApertureLd4_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printApertureLd4(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFocalLd4_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFocalLd4(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}



TEST(Nikon3MakerNoteTest_448, PrintFocusDistanceLd4_NormalOperation_448) {

    MockValue mockValue;

    MockExifData mockMetadata;



    std::ostringstream os;

    auto result = Nikon3MakerNote::printFocusDistanceLd4(os, mockValue, &mockMetadata);



    EXPECT_EQ(&os, &result);

}
