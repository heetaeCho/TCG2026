#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "olympusmn_int.cpp"



using namespace Exiv2;

using namespace Internal;



class OlympusMakerNoteTest_897 : public ::testing::Test {

protected:

    OlympusMakerNote olympusMakerNote;

    std::ostringstream os;

    Value value;

};



TEST_F(OlympusMakerNoteTest_897, Print0x0200_NormalCase_L0IsNormal_897) {

    value = Value::create(Exiv2::unsignedLong);

    value.toLong(0) = 0; // L0

    olympusMakerNote.print0x0200(os, value, nullptr);

    EXPECT_EQ(os.str(), "Normal");

}



TEST_F(OlympusMakerNoteTest_897, Print0x0200_NormalCase_L0IsFast_897) {

    value = Value::create(Exiv2::unsignedLong);

    value.toLong(0) = 2; // L0

    olympusMakerNote.print0x0200(os, value, nullptr);

    EXPECT_EQ(os.str(), "Fast");

}



TEST_F(OlympusMakerNoteTest_897, Print0x0200_NormalCase_L0IsPanoramaWithSequenceAndDirection_897) {

    value = Value::create(Exiv2::unsignedLong);

    value.toLong(0) = 3; // L0

    value.toLong(1) = 5; // L1 (sequence number)

    value.toLong(2) = 1; // L2 (direction)

    olympusMakerNote.print0x0200(os, value, nullptr);

    EXPECT_EQ(os.str(), "Panorama, Sequence number 5, Left to right");

}



TEST_F(OlympusMakerNoteTest_897, Print0x0200_BoundaryCase_ValueCountNotThree_897) {

    value = Value::create(Exiv2::unsignedLong);

    value.toLong(0) = 3;

    olympusMakerNote.print0x0200(os, value, nullptr); // Only one element

    EXPECT_EQ(os.str(), "3");

}



TEST_F(OlympusMakerNoteTest_897, Print0x0200_BoundaryCase_ValueTypeNotUnsignedLong_897) {

    value = Value::create(Exiv2::short);

    olympusMakerNote.print0x0200(os, value, nullptr); // Invalid type

    EXPECT_EQ(os.str(), "");

}



TEST_F(OlympusMakerNoteTest_897, Print0x0200_DefaultCase_L0IsUnknown_897) {

    value = Value::create(Exiv2::unsignedLong);

    value.toLong(0) = 9; // L0 (unknown)

    olympusMakerNote.print0x0200(os, value, nullptr);

    EXPECT_EQ(os.str(), "(9)");

}



TEST_F(OlympusMakerNoteTest_897, Print0x0200_DefaultCase_L1IsUnknown_897) {

    value = Value::create(Exiv2::unsignedLong);

    value.toLong(0) = 3; // L0

    value.toLong(1) = 15; // L1 (unknown sequence number)

    olympusMakerNote.print0x0200(os, value, nullptr);

    EXPECT_EQ(os.str(), "Panorama, Sequence number 15");

}



TEST_F(OlympusMakerNoteTest_897, Print0x0200_DefaultCase_L2IsUnknown_897) {

    value = Value::create(Exiv2::unsignedLong);

    value.toLong(0) = 3; // L0

    value.toLong(1) = 5; // L1 (sequence number)

    value.toLong(2) = 6; // L2 (unknown direction)

    olympusMakerNote.print0x0200(os, value, nullptr);

    EXPECT_EQ(os.str(), "Panorama, Sequence number 5, (6)");

}
