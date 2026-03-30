#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_426 : public ::testing::Test {

protected:

    Nikon3MakerNoteTest_426() {}



    std::ostringstream os;

    Value value;

    ExifData metadata;

};



TEST_F(Nikon3MakerNoteTest_426, TagListAf22_ReturnsCorrectTagInfo_426) {

    auto tagList = Nikon3MakerNote::tagListAf22();

    EXPECT_TRUE(tagList != nullptr);

}



TEST_F(Nikon3MakerNoteTest_426, PrintIiIso_ValidInput_PrintsExpectedOutput_426) {

    // Assuming value and metadata are set up correctly

    auto& result = Nikon3MakerNote::printIiIso(os, value, &metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_426, PrintAf2AreaMode_ValidInput_PrintsExpectedOutput_426) {

    // Assuming value and metadata are set up correctly

    auto& result = Nikon3MakerNote::printAf2AreaMode(os, value, &metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_426, PrintLensId_ValidInput_PrintsExpectedOutput_426) {

    // Assuming value and metadata are set up correctly

    auto& result = Nikon3MakerNote::printLensId(os, value, &metadata, "group");

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_426, PrintAperture_ValidInput_PrintsExpectedOutput_426) {

    // Assuming value and metadata are set up correctly

    auto& result = Nikon3MakerNote::printAperture(os, value, &metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_426, PrintFocal_ValidInput_PrintsExpectedOutput_426) {

    // Assuming value and metadata are set up correctly

    auto& result = Nikon3MakerNote::printFocal(os, value, &metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_426, PrintFocusDistance_ValidInput_PrintsExpectedOutput_426) {

    // Assuming value and metadata are set up correctly

    auto& result = Nikon3MakerNote::printFocusDistance(os, value, &metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_426, PrintFStops_ValidInput_PrintsExpectedOutput_426) {

    // Assuming value and metadata are set up correctly

    auto& result = Nikon3MakerNote::printFStops(os, value, &metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_426, PrintExternalFlashData1Fl6_ValidInput_PrintsExpectedOutput_426) {

    // Assuming value and metadata are set up correctly

    auto& result = Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_426, PrintExternalFlashData2_ValidInput_PrintsExpectedOutput_426) {

    // Assuming value and metadata are set up correctly

    auto& result = Nikon3MakerNote::printExternalFlashData2(os, value, &metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_426, PrintRepeatingFlashRate_ValidInput_PrintsExpectedOutput_426) {

    // Assuming value and metadata are set up correctly

    auto& result = Nikon3MakerNote::printRepeatingFlashRate(os, value, &metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_426, PrintRepeatingFlashCount_ValidInput_PrintsExpectedOutput_426) {

    // Assuming value and metadata are set up correctly

    auto& result = Nikon3MakerNote::printRepeatingFlashCount(os, value, &metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}
