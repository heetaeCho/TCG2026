#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/nikonmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class Nikon3MakerNoteTest_477 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

};



TEST_F(Nikon3MakerNoteTest_477, PrintFocusDistance_NormalOperation_477) {

    Exiv2::Value value;

    value.setValue(80); // Example value that is neither 0 nor out of range

    ExifData exifData;



    std::ostringstream os;

    nikonMakerNote.printFocusDistance(os, value, &exifData);



    EXPECT_EQ(os.str(), "1.00 m");

}



TEST_F(Nikon3MakerNoteTest_477, PrintFocusDistance_ValueZero_477) {

    Exiv2::Value value;

    value.setValue(0); // Zero value case

    ExifData exifData;



    std::ostringstream os;

    nikonMakerNote.printFocusDistance(os, value, &exifData);



    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_477, PrintFocusDistance_ValueCountNotOne_477) {

    Exiv2::Value value;

    value.setValue(80); // Set a valid value but change count

    value.setSize(2);

    ExifData exifData;



    std::ostringstream os;

    nikonMakerNote.printFocusDistance(os, value, &exifData);



    EXPECT_EQ(os.str(), "(80)");

}



TEST_F(Nikon3MakerNoteTest_477, PrintFocusDistance_ValueTypeNotUnsignedByte_477) {

    Exiv2::Value value;

    value.setValue(80);

    value.setType(Exiv2::shortM); // Change type to short

    ExifData exifData;



    std::ostringstream os;

    nikonMakerNote.printFocusDistance(os, value, &exifData);



    EXPECT_EQ(os.str(), "(80)");

}
