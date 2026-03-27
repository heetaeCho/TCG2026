#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "nikonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(Nikon3MakerNoteTest, PrintIiIso_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printIiIso(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, Print0x0002_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::print0x0002(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_MetadataNullptr_Exceptional_423) {

    Exiv2::Internal::Nikon3MakerNote::printAf2AreaMode(oss, mockValue, nullptr);

    EXPECT_TRUE(oss.str().empty()); // Assuming no output on null metadata

}



TEST_F(Nikon3MakerNoteTest, Print0x0089_MetadataNullptr_Exceptional_423) {

    Exiv2::Internal::Nikon3MakerNote::print0x0089(oss, mockValue, nullptr);

    EXPECT_TRUE(oss.str().empty()); // Assuming no output on null metadata

}



TEST_F(Nikon3MakerNoteTest, PrintLensId_MetadataNullptr_Exceptional_423) {

    Exiv2::Internal::Nikon3MakerNote::printLensId(oss, mockValue, nullptr, "group");

    EXPECT_TRUE(oss.str().empty()); // Assuming no output on null metadata

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistance_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printFocusDistance(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAperture_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printAperture(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocal_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printFocal(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFStops_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printFStops(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExitPupilPosition_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printExitPupilPosition(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashFocalLength_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printFlashFocalLength(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashRate_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printRepeatingFlashRate(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashCount_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printRepeatingFlashCount(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_MetadataNullptr_Exceptional_423) {

    Exiv2::Internal::Nikon3MakerNote::printExternalFlashData1Fl6(oss, mockValue, nullptr);

    EXPECT_TRUE(oss.str().empty()); // Assuming no output on null metadata

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2_MetadataNullptr_Exceptional_423) {

    Exiv2::Internal::Nikon3MakerNote::printExternalFlashData2(oss, mockValue, nullptr);

    EXPECT_TRUE(oss.str().empty()); // Assuming no output on null metadata

}



TEST_F(Nikon3MakerNoteTest, PrintFlashMasterDataFl6_MetadataNullptr_Exceptional_423) {

    Exiv2::Internal::Nikon3MakerNote::printFlashMasterDataFl6(oss, mockValue, nullptr);

    EXPECT_TRUE(oss.str().empty()); // Assuming no output on null metadata

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupAControlData_MetadataNullptr_Exceptional_423) {

    Exiv2::Internal::Nikon3MakerNote::printFlashGroupAControlData(oss, mockValue, nullptr);

    EXPECT_TRUE(oss.str().empty()); // Assuming no output on null metadata

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData3_MetadataNullptr_Exceptional_423) {

    Exiv2::Internal::Nikon3MakerNote::printExternalFlashData3(oss, mockValue, nullptr);

    EXPECT_TRUE(oss.str().empty()); // Assuming no output on null metadata

}



TEST_F(Nikon3MakerNoteTest, PrintCameraExposureCompensation_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printCameraExposureCompensation(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData4_MetadataNullptr_Exceptional_423) {

    Exiv2::Internal::Nikon3MakerNote::printExternalFlashData4(oss, mockValue, nullptr);

    EXPECT_TRUE(oss.str().empty()); // Assuming no output on null metadata

}



TEST_F(Nikon3MakerNoteTest, PrintFlashZoomHeadPosition_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printFlashZoomHeadPosition(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintTimeZone_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printTimeZone(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintPictureControl_NormalOperation_423) {

    Exiv2::Internal::Nikon3MakerNote::printPictureControl(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}
