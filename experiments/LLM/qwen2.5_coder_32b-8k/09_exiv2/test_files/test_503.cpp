#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <cmath>

#include "TestProjects/exiv2/src/nikonmn_int.cpp"



using namespace Exiv2::Internal;

using namespace ::testing;



class Nikon3MakerNoteTest : public Test {

protected:

    Nikon3MakerNote nikonMakerNote;

};



TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_NormalOperation_PositiveOffset_503) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeArray(Exiv2::signedShort);

    value[0] = 120; // 2 hours

    nikonMakerNote.printTimeZone(os, value, nullptr);

    EXPECT_EQ(os.str(), "UTC +02:00");

}



TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_NormalOperation_NegativeOffset_503) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeArray(Exiv2::signedShort);

    value[0] = -120; // -2 hours

    nikonMakerNote.printTimeZone(os, value, nullptr);

    EXPECT_EQ(os.str(), "UTC -02:00");

}



TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_BoundaryCondition_ZeroOffset_503) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeArray(Exiv2::signedShort);

    value[0] = 0; // 0 hours

    nikonMakerNote.printTimeZone(os, value, nullptr);

    EXPECT_EQ(os.str(), "UTC +00:00");

}



TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_ExceptionalCase_ValueCountNotOne_503) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeArray(Exiv2::signedShort);

    value[0] = 120;

    value[1] = 60; // More than one element

    nikonMakerNote.printTimeZone(os, value, nullptr);

    EXPECT_EQ(os.str(), "(120 60)");

}



TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_ExceptionalCase_WrongType_503) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeArray(Exiv2::asciiString);

    value.readString("120"); // Wrong type

    nikonMakerNote.printTimeZone(os, value, nullptr);

    EXPECT_EQ(os.str(), "(120)");

}



TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_BoundaryCondition_MaxPositiveOffset_503) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeArray(Exiv2::signedShort);

    value[0] = 1439; // 23:59

    nikonMakerNote.printTimeZone(os, value, nullptr);

    EXPECT_EQ(os.str(), "UTC +23:59");

}



TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_BoundaryCondition_MaxNegativeOffset_503) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeArray(Exiv2::signedShort);

    value[0] = -1439; // -23:59

    nikonMakerNote.printTimeZone(os, value, nullptr);

    EXPECT_EQ(os.str(), "UTC -23:59");

}
