#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nikonmn_int.cpp" // Assuming the file can be included directly for testing purposes



using namespace Exiv2::Internal;

using namespace ::testing;



class Nikon3MakerNoteTest_467 : public Test {

protected:

    Nikon3MakerNote makerNote;

    std::ostringstream os;

    Value value;

    const ExifData* exifData = nullptr; // Assuming no need to mock or use this for the tests



    void SetUp() override {

        os.str(""); // Clear the output stream before each test

    }

};



TEST_F(Nikon3MakerNoteTest_467, Print0x0088_NormalOperation_SingleArea_467) {

    value.setValue(std::vector<uint8_t>({0x00, 0x01, 0x00, 0x02})); // focusmetering = 0, focuspoint = 1, focusused = 256

    makerNote.print0x0088(os, value, exifData);

    EXPECT_EQ(os.str(), "Single area; Center-lower used");

}



TEST_F(Nikon3MakerNoteTest_467, Print0x0088_NormalOperation_DynamicArea_467) {

    value.setValue(std::vector<uint8_t>({0x01, 0x02, 0x00, 0x04})); // focusmetering = 1, focuspoint = 2, focusused = 512

    makerNote.print0x0088(os, value, exifData);

    EXPECT_EQ(os.str(), "Dynamic area; Center used");

}



TEST_F(Nikon3MakerNoteTest_467, Print0x0088_NormalOperation_ClosestSubject_467) {

    value.setValue(std::vector<uint8_t>({0x02, 0x03, 0x00, 0x00})); // focusmetering = 2, focuspoint = 3, focusused = 0

    makerNote.print0x0088(os, value, exifData);

    EXPECT_EQ(os.str(), "Closest subject none");

}



TEST_F(Nikon3MakerNoteTest_467, Print0x0088_NormalOperation_GroupDynamicAF_467) {

    value.setValue(std::vector<uint8_t>({0x03, 0x01, 0x00, 0x02})); // focusmetering = 3, focuspoint = 1, focusused = 256

    makerNote.print0x0088(os, value, exifData);

    EXPECT_EQ(os.str(), "Group dynamic-AF; Center-lower used");

}



TEST_F(Nikon3MakerNoteTest_467, Print0x0088_NormalOperation_SingleAreaWide_467) {

    value.setValue(std::vector<uint8_t>({0x04, 0x02, 0x00, 0x04})); // focusmetering = 4, focuspoint = 2, focusused = 512

    makerNote.print0x0088(os, value, exifData);

    EXPECT_EQ(os.str(), "Single area (wide); Center used");

}



TEST_F(Nikon3MakerNoteTest_467, Print0x0088_NormalOperation_DynamicAreaWide_467) {

    value.setValue(std::vector<uint8_t>({0x05, 0x03, 0x00, 0x02})); // focusmetering = 5, focuspoint = 3, focusused = 256

    makerNote.print0x0088(os, value, exifData);

    EXPECT_EQ(os.str(), "Dynamic area (wide); Center-lower used");

}



TEST_F(Nikon3MakerNoteTest_467, Print0x0088_NormalOperation_DefaultCase_467) {

    value.setValue(std::vector<uint8_t>({0x06, 0x01, 0x00, 0x02})); // focusmetering = 6 (default case), focuspoint = 1, focusused = 256

    makerNote.print0x0088(os, value, exifData);

    EXPECT_EQ(os.str(), "(6); Center-lower used");

}



TEST_F(Nikon3MakerNoteTest_467, Print0x0088_BoundaryCondition_ValueSizeNotFour_467) {

    value.setValue(std::vector<uint8_t>({0x01})); // Value size is 1

    makerNote.print0x0088(os, value, exifData);

    EXPECT_EQ(os.str(), "(Exiv2::Value*)");

}



TEST_F(Nikon3MakerNoteTest_467, Print0x0088_BoundaryCondition_AllZeroValues_467) {

    value.setValue(std::vector<uint8_t>({0x00, 0x00, 0x00, 0x00})); // All values are zero

    makerNote.print0x0088(os, value, exifData);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_467, Print0x0088_BoundaryCondition_LargeFocusPoint_467) {

    value.setValue(std::vector<uint8_t>({0x01, 0xFF, 0x00, 0x02})); // focuspoint = 255 (out of bounds)

    makerNote.print0x0088(os, value, exifData);

    EXPECT_EQ(os.str(), "Dynamic area; (255) used");

}



TEST_F(Nikon3MakerNoteTest_467, Print0x0088_BoundaryCondition_MultipleFocusPointsUsed_467) {

    value.setValue(std::vector<uint8_t>({0x01, 0x01, 0x00, 0x06})); // focusused = 6 (binary: 110), indicating multiple points

    makerNote.print0x0088(os, value, exifData);

    EXPECT_EQ(os.str(), "Dynamic area; Center-lower, Center used");

}
