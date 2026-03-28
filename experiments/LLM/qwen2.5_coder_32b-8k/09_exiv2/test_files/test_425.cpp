#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class Nikon3MakerNoteTest_425 : public ::testing::Test {

protected:

    std::ostringstream os_;

    Value mockValue_; // Mock Value object, assuming it's default-constructible

    ExifData mockMetadata_; // Mock ExifData object, assuming it's default-constructible

};



TEST_F(Nikon3MakerNoteTest_425, TagListAf21_ReturnsConstant_425) {

    auto result = Nikon3MakerNote::tagListAf21();

    EXPECT_EQ(result, Nikon3MakerNote::tagInfoAf21_);

}



TEST_F(Nikon3MakerNoteTest_425, PrintIiIso_NormalOperation_425) {

    Nikon3MakerNote::printIiIso(os_, mockValue_, &mockMetadata_);

    // Assuming printIiIso writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintAf2AreaMode_NormalOperation_425) {

    Nikon3MakerNote::printAf2AreaMode(os_, mockValue_, &mockMetadata_);

    // Assuming printAf2AreaMode writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintLensId_NormalOperation_425) {

    Nikon3MakerNote::printLensId(os_, mockValue_, &mockMetadata_, "group");

    // Assuming printLensId writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintFocusDistance_NormalOperation_425) {

    Nikon3MakerNote::printFocusDistance(os_, mockValue_, &mockMetadata_);

    // Assuming printFocusDistance writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintAperture_NormalOperation_425) {

    Nikon3MakerNote::printAperture(os_, mockValue_, &mockMetadata_);

    // Assuming printAperture writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintFocal_NormalOperation_425) {

    Nikon3MakerNote::printFocal(os_, mockValue_, &mockMetadata_);

    // Assuming printFocal writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintFStops_NormalOperation_425) {

    Nikon3MakerNote::printFStops(os_, mockValue_, &mockMetadata_);

    // Assuming printFStops writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintExitPupilPosition_NormalOperation_425) {

    Nikon3MakerNote::printExitPupilPosition(os_, mockValue_, &mockMetadata_);

    // Assuming printExitPupilPosition writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintFlashFocalLength_NormalOperation_425) {

    Nikon3MakerNote::printFlashFocalLength(os_, mockValue_, &mockMetadata_);

    // Assuming printFlashFocalLength writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintRepeatingFlashRate_NormalOperation_425) {

    Nikon3MakerNote::printRepeatingFlashRate(os_, mockValue_, &mockMetadata_);

    // Assuming printRepeatingFlashRate writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintRepeatingFlashCount_NormalOperation_425) {

    Nikon3MakerNote::printRepeatingFlashCount(os_, mockValue_, &mockMetadata_);

    // Assuming printRepeatingFlashCount writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintExternalFlashData1Fl6_NormalOperation_425) {

    Nikon3MakerNote::printExternalFlashData1Fl6(os_, mockValue_, &mockMetadata_);

    // Assuming printExternalFlashData1Fl6 writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintExternalFlashData1Fl7_NormalOperation_425) {

    Nikon3MakerNote::printExternalFlashData1Fl7(os_, mockValue_, &mockMetadata_);

    // Assuming printExternalFlashData1Fl7 writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintExternalFlashData2_NormalOperation_425) {

    Nikon3MakerNote::printExternalFlashData2(os_, mockValue_, &mockMetadata_);

    // Assuming printExternalFlashData2 writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintFlashMasterDataFl6_NormalOperation_425) {

    Nikon3MakerNote::printFlashMasterDataFl6(os_, mockValue_, &mockMetadata_);

    // Assuming printFlashMasterDataFl6 writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintFlashMasterDataFl7_NormalOperation_425) {

    Nikon3MakerNote::printFlashMasterDataFl7(os_, mockValue_, &mockMetadata_);

    // Assuming printFlashMasterDataFl7 writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintFlashGroupAControlData_NormalOperation_425) {

    Nikon3MakerNote::printFlashGroupAControlData(os_, mockValue_, &mockMetadata_);

    // Assuming printFlashGroupAControlData writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintFlashGroupBCControlData_NormalOperation_425) {

    Nikon3MakerNote::printFlashGroupBCControlData(os_, mockValue_, &mockMetadata_);

    // Assuming printFlashGroupBCControlData writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintExternalFlashData3_NormalOperation_425) {

    Nikon3MakerNote::printExternalFlashData3(os_, mockValue_, &mockMetadata_);

    // Assuming printExternalFlashData3 writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintCameraExposureCompensation_NormalOperation_425) {

    Nikon3MakerNote::printCameraExposureCompensation(os_, mockValue_, &mockMetadata_);

    // Assuming printCameraExposureCompensation writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintExternalFlashData4_NormalOperation_425) {

    Nikon3MakerNote::printExternalFlashData4(os_, mockValue_, &mockMetadata_);

    // Assuming printExternalFlashData4 writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintFlashZoomHeadPosition_NormalOperation_425) {

    Nikon3MakerNote::printFlashZoomHeadPosition(os_, mockValue_, &mockMetadata_);

    // Assuming printFlashZoomHeadPosition writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintTimeZone_NormalOperation_425) {

    Nikon3MakerNote::printTimeZone(os_, mockValue_, &mockMetadata_);

    // Assuming printTimeZone writes something to os_

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(Nikon3MakerNoteTest_425, PrintPictureControl_NormalOperation_425) {

    Nikon3MakerNote::printPictureControl(os_, mockValue_, &mockMetadata_);

    // Assuming printPictureControl writes something to os_

    EXPECT_FALSE(os_.str().empty());

}
