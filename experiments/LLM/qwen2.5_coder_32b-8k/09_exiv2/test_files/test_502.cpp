#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/src/nikonmn_int.cpp" // Assuming the header file that contains Nikon3MakerNote class



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_502 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

    std::ostringstream os;

    Value value;

};



TEST_F(Nikon3MakerNoteTest_502, PrintFlashZoomHeadPosition_NormalOperation_502) {

    // Setup

    uint8_t data[] = {40};  // Example value for flash zoom head position in millimeters

    value.setValue(data, 1);



    // Exercise

    nikonMakerNote.printFlashZoomHeadPosition(os, value, nullptr);



    // Verify

    EXPECT_EQ(os.str(), "40 mm");

}



TEST_F(Nikon3MakerNoteTest_502, PrintFlashZoomHeadPosition_ZeroValue_502) {

    // Setup

    uint8_t data[] = {0};  // Zero value case

    value.setValue(data, 1);



    // Exercise

    nikonMakerNote.printFlashZoomHeadPosition(os, value, nullptr);



    // Verify

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_502, PrintFlashZoomHeadPosition_CountNotOne_502) {

    // Setup

    uint8_t data[] = {40, 50};  // More than one element in the value

    value.setValue(data, 2);



    // Exercise

    nikonMakerNote.printFlashZoomHeadPosition(os, value, nullptr);



    // Verify

    EXPECT_EQ(os.str(), "(Xmp.GDepth.DepthMap: 2)");

}



TEST_F(Nikon3MakerNoteTest_502, PrintFlashZoomHeadPosition_TypeNotUnsignedByte_502) {

    // Setup

    short data[] = {40};  // Incorrect type (short instead of unsigned byte)

    value.setValue(reinterpret_cast<uint8_t*>(data), 1);

    value.setType(Exiv2::shortType);



    // Exercise

    nikonMakerNote.printFlashZoomHeadPosition(os, value, nullptr);



    // Verify

    EXPECT_EQ(os.str(), "(Xmp.GDepth.DepthMap: 40)");

}
