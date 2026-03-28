#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include "nikonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



// Mocking ExifData since it's an external dependency

class MockExifData : public ExifData {

public:

    MOCK_METHOD(void, dummyMethod, (), (const));

};



TEST(Nikon3MakerNoteTest_422, TagListWtReturnsConstant_422) {

    auto tagList = Nikon3MakerNote::tagListWt();

    EXPECT_EQ(tagList, Nikon3MakerNote::tagInfoWt_);

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintIiIso_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue; // Assuming Value is a valid type in the context



    Nikon3MakerNote::printIiIso(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, Print0x0002_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::print0x0002(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintAf2AreaMode_NonEmptyOutputWithMetadata_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printAf2AreaMode(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, Print0x0089_NonEmptyOutputWithMetadata_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::print0x0089(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintLensId_NonEmptyOutputWithMetadataAndGroup_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printLensId(os, dummyValue, &mockMetadata, "SampleGroup");

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintFocusDistance_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printFocusDistance(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintAperture_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printAperture(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintFocal_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printFocal(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintFStops_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printFStops(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintExitPupilPosition_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printExitPupilPosition(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintFlashFocalLength_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printFlashFocalLength(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintRepeatingFlashRate_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printRepeatingFlashRate(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintRepeatingFlashCount_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printRepeatingFlashCount(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintExternalFlashData1Fl6_NonEmptyOutputWithMetadata_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printExternalFlashData1Fl6(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintExternalFlashData2_NonEmptyOutputWithMetadata_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printExternalFlashData2(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintFlashMasterDataFl6_NonEmptyOutputWithMetadata_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printFlashMasterDataFl6(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintFlashGroupAControlData_NonEmptyOutputWithMetadata_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printFlashGroupAControlData(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintExternalFlashData3_NonEmptyOutputWithMetadata_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printExternalFlashData3(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintCameraExposureCompensation_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printCameraExposureCompensation(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintExternalFlashData4_NonEmptyOutputWithMetadata_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printExternalFlashData4(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintFlashZoomHeadPosition_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printFlashZoomHeadPosition(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintTimeZone_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printTimeZone(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST(Nikon3MakerNotePrintFunctions_422, PrintPictureControl_NonEmptyOutput_422) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Value dummyValue;



    Nikon3MakerNote::printPictureControl(os, dummyValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}
