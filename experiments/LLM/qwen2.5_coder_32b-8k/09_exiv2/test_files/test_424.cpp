#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



// Mock classes and objects if needed (none in this case since there are no external collaborators)



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(Nikon3MakerNoteTest, TagListAfReturnsConstant_424) {

    auto tagList = Nikon3MakerNote::tagListAf();

    EXPECT_NE(tagList, nullptr);

}



// Test for print functions

#define TEST_PRINT_FUNCTION(functionName) \

TEST_F(Nikon3MakerNoteTest, functionName##OutputsToStream_424) { \

    std::ostringstream oss; \

    auto result = Nikon3MakerNote::functionName(oss, mockValue, &mockMetadata); \

    EXPECT_EQ(&result, &oss); \

}



// Generate tests for each print function

TEST_PRINT_FUNCTION(print0x0002)

TEST_PRINT_FUNCTION(printAf2AreaMode)

TEST_PRINT_FUNCTION(print0x0007)

TEST_PRINT_FUNCTION(print0x0083)

TEST_PRINT_FUNCTION(print0x0084)

TEST_PRINT_FUNCTION(print0x0085)

TEST_PRINT_FUNCTION(print0x0086)

TEST_PRINT_FUNCTION(print0x0088)

TEST_PRINT_FUNCTION(printAfPointsInFocus)

TEST_PRINT_FUNCTION(print0x0089)

TEST_PRINT_FUNCTION(print0x008b)

TEST_PRINT_FUNCTION(printLensId1)

TEST_PRINT_FUNCTION(printLensId2)

TEST_PRINT_FUNCTION(printLensId3)

TEST_PRINT_FUNCTION(printLensId4)

TEST_PRINT_FUNCTION(printLensId)

TEST_PRINT_FUNCTION(printFocusDistance)

TEST_PRINT_FUNCTION(printAperture)

TEST_PRINT_FUNCTION(printFocal)

TEST_PRINT_FUNCTION(printFStops)

TEST_PRINT_FUNCTION(printExitPupilPosition)

TEST_PRINT_FUNCTION(printFlashFocalLength)

TEST_PRINT_FUNCTION(printRepeatingFlashRate)

TEST_PRINT_FUNCTION(printRepeatingFlashCount)

TEST_PRINT_FUNCTION(printExternalFlashData1Fl6)

TEST_PRINT_FUNCTION(printExternalFlashData2Fl6)

TEST_PRINT_FUNCTION(printExternalFlashData1Fl7)

TEST_PRINT_FUNCTION(printExternalFlashData2)

TEST_PRINT_FUNCTION(printFlashMasterDataFl6)

TEST_PRINT_FUNCTION(printFlashMasterDataFl7)

TEST_PRINT_FUNCTION(printFlashGroupAControlData)

TEST_PRINT_FUNCTION(printFlashGroupBCControlData)

TEST_PRINT_FUNCTION(printFlashGroupADataFl6)

TEST_PRINT_FUNCTION(printFlashGroupADataFl7)

TEST_PRINT_FUNCTION(printFlashGroupBDataFl6)

TEST_PRINT_FUNCTION(printFlashGroupBDataFl7)

TEST_PRINT_FUNCTION(printFlashGroupCDataFl6)

TEST_PRINT_FUNCTION(printFlashGroupCDataFl7)

TEST_PRINT_FUNCTION(printExternalFlashData3)

TEST_PRINT_FUNCTION(printCameraExposureCompensation)

TEST_PRINT_FUNCTION(printExternalFlashData4)

TEST_PRINT_FUNCTION(printFlashZoomHeadPosition)

TEST_PRINT_FUNCTION(printTimeZone)

TEST_PRINT_FUNCTION(printPictureControl)

TEST_PRINT_FUNCTION(print0x009a)

TEST_PRINT_FUNCTION(print0x009e)

TEST_PRINT_FUNCTION(printIiIso)

TEST_PRINT_FUNCTION(printApertureLd4)

TEST_PRINT_FUNCTION(printFocalLd4)

TEST_PRINT_FUNCTION(printFocusDistanceLd4)



#undef TEST_PRINT_FUNCTION
