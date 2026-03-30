#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/src/olympusmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::HasSubstr;



TEST_F(OlympusMakerNoteTest_895, NormalOperation_LowKey_895) {

    Value value;

    value.type(signedShort);

    value.resize(3);

    value.toInt64(0) = -1;

    value.toInt64(1) = -1;

    value.toInt64(2) = 1;



    std::ostringstream os;

    OlympusMakerNote olympusMakerNote;

    olympusMakerNote.print0x050f(os, value, nullptr);



    EXPECT_EQ(os.str(), "Low Key");

}



TEST_F(OlympusMakerNoteTest_895, NormalOperation_Normal_895) {

    Value value;

    value.type(signedShort);

    value.resize(3);

    value.toInt64(0) = 0;

    value.toInt64(1) = -1;

    value.toInt64(2) = 1;



    std::ostringstream os;

    OlympusMakerNote olympusMakerNote;

    olympusMakerNote.print0x050f(os, value, nullptr);



    EXPECT_EQ(os.str(), "Normal");

}



TEST_F(OlympusMakerNoteTest_895, NormalOperation_HighKey_895) {

    Value value;

    value.type(signedShort);

    value.resize(3);

    value.toInt64(0) = 1;

    value.toInt64(1) = -1;

    value.toInt64(2) = 1;



    std::ostringstream os;

    OlympusMakerNote olympusMakerNote;

    olympusMakerNote.print0x050f(os, value, nullptr);



    EXPECT_EQ(os.str(), "High Key");

}



TEST_F(OlympusMakerNoteTest_895, NormalOperation_CustomValues_895) {

    Value value;

    value.type(signedShort);

    value.resize(3);

    value.toInt64(0) = 2;

    value.toInt64(1) = -2;

    value.toInt64(2) = 3;



    std::ostringstream os;

    OlympusMakerNote olympusMakerNote;

    olympusMakerNote.print0x050f(os, value, nullptr);



    EXPECT_EQ(os.str(), "2 -2 3");

}



TEST_F(OlympusMakerNoteTest_895, BoundaryCondition_ValueCount3_UserSelected_895) {

    Value value;

    value.type(signedShort);

    value.resize(4);

    value.toInt64(0) = 0;

    value.toInt64(1) = -1;

    value.toInt64(2) = 1;

    value.toInt64(3) = 0;



    std::ostringstream os;

    OlympusMakerNote olympusMakerNote;

    olympusMakerNote.print0x050f(os, value, nullptr);



    EXPECT_EQ(os.str(), "Normal, User-Selected");

}



TEST_F(OlympusMakerNoteTest_895, BoundaryCondition_ValueCount3_AutoOverride_895) {

    Value value;

    value.type(signedShort);

    value.resize(4);

    value.toInt64(0) = 1;

    value.toInt64(1) = -1;

    value.toInt64(2) = 1;

    value.toInt64(3) = 1;



    std::ostringstream os;

    OlympusMakerNote olympusMakerNote;

    olympusMakerNote.print0x050f(os, value, nullptr);



    EXPECT_EQ(os.str(), "High Key, Auto-Override");

}



TEST_F(OlympusMakerNoteTest_895, BoundaryCondition_ValueCount3_OtherValue_895) {

    Value value;

    value.type(signedShort);

    value.resize(4);

    value.toInt64(0) = -1;

    value.toInt64(1) = -1;

    value.toInt64(2) = 1;

    value.toInt64(3) = 2;



    std::ostringstream os;

    OlympusMakerNote olympusMakerNote;

    olympusMakerNote.print0x050f(os, value, nullptr);



    EXPECT_EQ(os.str(), "Low Key, 2");

}



TEST_F(OlympusMakerNoteTest_895, ExceptionalCase_ValueCountNot3Or4_895) {

    Value value;

    value.type(signedShort);

    value.resize(2);

    value.toInt64(0) = -1;

    value.toInt64(1) = -1;



    std::ostringstream os;

    OlympusMakerNote olympusMakerNote;

    olympusMakerNote.print0x050f(os, value, nullptr);



    EXPECT_EQ(os.str(), "-1 -1");

}



TEST_F(OlympusMakerNoteTest_895, ExceptionalCase_ValueTypeNotSignedShort_895) {

    Value value;

    value.type(unsignedShort);

    value.resize(3);

    value.toInt64(0) = 2;

    value.toInt64(1) = -2;

    value.toInt64(2) = 3;



    std::ostringstream os;

    OlympusMakerNote olympusMakerNote;

    olympusMakerNote.print0x050f(os, value, nullptr);



    EXPECT_EQ(os.str(), "2 -2 3");

}
