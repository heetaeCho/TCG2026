#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include "TestProjects/exiv2/src/olympusmn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::StrEq;



class OlympusMakerNoteTest_896 : public ::testing::Test {

protected:

    OlympusMakerNote olympusMakerNote;

    std::ostringstream output;

};



TEST_F(OlympusMakerNoteTest_896, Print0x0527_ValueCountNot3_ReturnsOriginalValue_896) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::signedShort;

    value.count_ = 4; // Not equal to 3

    olympusMakerNote.print0x0527(output, value, nullptr);

    EXPECT_EQ(output.str(), "Exiv2::Value");

}



TEST_F(OlympusMakerNoteTest_896, Print0x0527_ValueTypeNotSignedShort_ReturnsOriginalValue_896) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::unsignedLong; // Not equal to signedShort

    value.count_ = 3;

    olympusMakerNote.print0x0527(output, value, nullptr);

    EXPECT_EQ(output.str(), "Exiv2::Value");

}



TEST_F(OlympusMakerNoteTest_896, Print0x0527_SecondValueNotMinusTwo_ReturnsOriginalValue_896) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::signedShort;

    value.count_ = 3;

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(-1)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(0)), sizeof(int16_t))); // Not equal to -2

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(1)), sizeof(int16_t)));

    olympusMakerNote.print0x0527(output, value, nullptr);

    EXPECT_EQ(output.str(), "Exiv2::Value");

}



TEST_F(OlympusMakerNoteTest_896, Print0x0527_ThirdValueNotOne_ReturnsOriginalValue_896) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::signedShort;

    value.count_ = 3;

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(-1)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(-2)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(0)), sizeof(int16_t))); // Not equal to 1

    olympusMakerNote.print0x0527(output, value, nullptr);

    EXPECT_EQ(output.str(), "Exiv2::Value");

}



TEST_F(OlympusMakerNoteTest_896, Print0x0527_ValueFirstMinusTwo_ReturnsOff_896) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::signedShort;

    value.count_ = 3;

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(-2)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(-2)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(1)), sizeof(int16_t)));

    olympusMakerNote.print0x0527(output, value, nullptr);

    EXPECT_THAT(output.str(), StrEq("Off"));

}



TEST_F(OlympusMakerNoteTest_896, Print0x0527_ValueFirstMinusOne_ReturnsLow_896) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::signedShort;

    value.count_ = 3;

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(-1)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(-2)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(1)), sizeof(int16_t)));

    olympusMakerNote.print0x0527(output, value, nullptr);

    EXPECT_THAT(output.str(), StrEq("Low"));

}



TEST_F(OlympusMakerNoteTest_896, Print0x0527_ValueFirstZero_ReturnsStandard_896) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::signedShort;

    value.count_ = 3;

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(0)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(-2)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(1)), sizeof(int16_t)));

    olympusMakerNote.print0x0527(output, value, nullptr);

    EXPECT_THAT(output.str(), StrEq("Standard"));

}



TEST_F(OlympusMakerNoteTest_896, Print0x0527_ValueFirstOne_ReturnsHigh_896) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::signedShort;

    value.count_ = 3;

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(1)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(-2)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(1)), sizeof(int16_t)));

    olympusMakerNote.print0x0527(output, value, nullptr);

    EXPECT_THAT(output.str(), StrEq("High"));

}



TEST_F(OlympusMakerNoteTest_896, Print0x0527_ValueFirstOther_ReturnsValue_896) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::signedShort;

    value.count_ = 3;

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(2)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(-2)), sizeof(int16_t)));

    value.data_.push_back(Exiv2::DataBuf(reinterpret_cast<const byte*>(new int16_t(1)), sizeof(int16_t)));

    olympusMakerNote.print0x0527(output, value, nullptr);

    EXPECT_THAT(output.str(), StrEq("2"));

}
