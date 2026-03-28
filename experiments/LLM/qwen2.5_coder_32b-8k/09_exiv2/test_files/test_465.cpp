#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/nikonmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

    std::ostringstream os;

};



TEST_F(Nikon3MakerNoteTest_465, Print0x0085_NormalOperation_465) {

    Exiv2::Value value;

    value.makeArray(Exiv2::urational);

    value.rational(0) = {1, 2};

    

    nikon3MakerNote.print0x0085(os, value, nullptr);



    EXPECT_EQ(os.str(), "0.50 m");

}



TEST_F(Nikon3MakerNoteTest_465, Print0x0085_RatioZeroNumerator_465) {

    Exiv2::Value value;

    value.makeArray(Exiv2::urational);

    value.rational(0) = {0, 1};



    nikon3MakerNote.print0x0085(os, value, nullptr);



    EXPECT_EQ(os.str(), "Unknown");

}



TEST_F(Nikon3MakerNoteTest_465, Print0x0085_RatioZeroDenominator_465) {

    Exiv2::Value value;

    value.makeArray(Exiv2::urational);

    value.rational(0) = {1, 0};



    nikon3MakerNote.print0x0085(os, value, nullptr);



    EXPECT_EQ(os.str(), "(1/0)");

}



TEST_F(Nikon3MakerNoteTest_465, Print0x0085_LargeValues_465) {

    Exiv2::Value value;

    value.makeArray(Exiv2::urational);

    value.rational(0) = {999999, 1};



    nikon3MakerNote.print0x0085(os, value, nullptr);



    EXPECT_EQ(os.str(), "999999.00 m");

}



TEST_F(Nikon3MakerNoteTest_465, Print0x0085_SmallValues_465) {

    Exiv2::Value value;

    value.makeArray(Exiv2::urational);

    value.rational(0) = {1, 999999};



    nikon3MakerNote.print0x0085(os, value, nullptr);



    EXPECT_EQ(os.str(), "0.00 m");

}
