#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/nikonmn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::StrEq;



class Nikon3MakerNoteTest_479 : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

    std::ostringstream os;

    Value value;

};



TEST_F(Nikon3MakerNoteTest_479, PrintFocal_ValueCountNotOne_479) {

    Value valueWithCountTwo;

    valueWithCountTwo.makeArray(unsignedByte, 2);

    EXPECT_EQ("(0)", nikon3MakerNote.printFocal(os, valueWithCountTwo, nullptr).str());

}



TEST_F(Nikon3MakerNoteTest_479, PrintFocal_ValueTypeNotUnsignedByte_479) {

    Value valueWithDifferentType;

    valueWithDifferentType.makeArray(int16, 1);

    EXPECT_EQ("(0)", nikon3MakerNote.printFocal(os, valueWithDifferentType, nullptr).str());

}



TEST_F(Nikon3MakerNoteTest_479, PrintFocal_ValueZero_479) {

    value.makeArray(unsignedByte, 1);

    value[0] = 0;

    EXPECT_EQ("n/a", nikon3MakerNote.printFocal(os, value, nullptr).str());

}



TEST_F(Nikon3MakerNoteTest_479, PrintFocal_ValueNonZero_479) {

    value.makeArray(unsignedByte, 1);

    value[0] = 24;

    EXPECT_EQ("5.0 mm", nikon3MakerNote.printFocal(os, value, nullptr).str());

}



TEST_F(Nikon3MakerNoteTest_479, PrintFocal_ValueBoundaryCondition_479) {

    value.makeArray(unsignedByte, 1);

    value[0] = 0;

    EXPECT_EQ("n/a", nikon3MakerNote.printFocal(os, value, nullptr).str());



    value[0] = 255;

    EXPECT_EQ("6871.9 mm", nikon3MakerNote.printFocal(os, value, nullptr).str());

}
