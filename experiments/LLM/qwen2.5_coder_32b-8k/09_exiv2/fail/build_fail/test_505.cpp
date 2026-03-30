#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/src/nikonmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_505 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

};



TEST_F(Nikon3MakerNoteTest_505, Print0x009a_NormalOperation_505) {

    std::ostringstream os;

    Exiv2::Value value;

    value.typeId() = Exiv2::unsignedRational;

    value.size(2);

    value.rational(0).first = 100;

    value.rational(0).second = 1;

    value.rational(1).first = 50;

    value.rational(1).second = 1;



    nikonMakerNote.print0x009a(os, value, nullptr);



    EXPECT_EQ("100 x 50 um", os.str());

}



TEST_F(Nikon3MakerNoteTest_505, Print0x009a_BoundaryCount_505) {

    std::ostringstream os;

    Exiv2::Value value;

    value.typeId() = Exiv2::unsignedRational;



    // Count is 1

    value.size(1);

    nikonMakerNote.print0x009a(os, value, nullptr);

    EXPECT_EQ("", os.str());



    // Reset stream

    os.str("");



    // Count is 3

    value.size(3);

    nikonMakerNote.print0x009a(os, value, nullptr);

    EXPECT_EQ("", os.str());

}



TEST_F(Nikon3MakerNoteTest_505, Print0x009a_BoundaryType_505) {

    std::ostringstream os;

    Exiv2::Value value;



    // Type is not unsignedRational

    value.typeId() = Exiv2::shortType;

    value.size(2);

    nikonMakerNote.print0x009a(os, value, nullptr);



    EXPECT_EQ("Exiv2::Value", os.str());

}



TEST_F(Nikon3MakerNoteTest_505, Print0x009a_ExceptionalCase_505) {

    std::ostringstream os;

    Exiv2::Value value;



    // Invalid type and count

    value.typeId() = Exiv2::shortType;

    value.size(1);

    nikonMakerNote.print0x009a(os, value, nullptr);



    EXPECT_EQ("Exiv2::Value", os.str());

}
