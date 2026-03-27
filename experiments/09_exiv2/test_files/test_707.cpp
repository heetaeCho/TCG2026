#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/src/panasonicmn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class PanasonicMakerNoteTest_707 : public ::testing::Test {

protected:

    PanasonicMakerNote panasonicMakerNote;

    std::ostringstream oss;

};



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_SpotModeOnOr9Area_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(0);

    value.data_.push_back(1);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("Spot mode on or 9 area", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_SpotModeOffOr3AreaHighSpeed_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(0);

    value.data_.push_back(16);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("Spot mode off or 3-area (high speed)", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_23Area_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(0);

    value.data_.push_back(23);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("23-area", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_49Area_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(0);

    value.data_.push_back(49);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("49-area", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_225Area_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(0);

    value.data_.push_back(225);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("225-area", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_SpotFocusing_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(1);

    value.data_.push_back(0);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("Spot focusing", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_5Area_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(1);

    value.data_.push_back(1);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("5-area", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_1Area_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(16);

    value.data_.push_back(0);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("1-area", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_1AreaHighSpeed_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(16);

    value.data_.push_back(16);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("1-area (high speed)", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_3AreaAuto_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(32);

    value.data_.push_back(0);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("3-area (auto)", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_3AreaLeft_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(32);

    value.data_.push_back(1);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("3-area (left)", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_3AreaCenter_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(32);

    value.data_.push_back(2);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("3-area (center)", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_3AreaRight_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(32);

    value.data_.push_back(3);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("3-area (right)", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_FaceDetect_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(64);

    value.data_.push_back(0);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("Face Detect", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_SpotFocusing2_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(128);

    value.data_.push_back(0);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("Spot Focusing 2", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValidValue_Tracking_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(240);

    value.data_.push_back(0);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("Tracking", oss.str());

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_InvalidTypeId_ReturnsOriginalValue_707) {

    Value value;

    value.typeId_ = shortType; // Invalid type

    value.size_ = 2;

    value.data_.push_back(1);

    value.data_.push_back(0);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("1", oss.str()); // Output should be the original value as string

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ValueCountLessThan2_ReturnsOriginalValue_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 1; // Invalid size

    value.data_.push_back(1);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("1", oss.str()); // Output should be the original value as string

}



TEST_F(PanasonicMakerNoteTest_707, Print0x000f_UnmatchedValue_ReturnsOriginalValue_707) {

    Value value;

    value.typeId_ = unsignedByte;

    value.size_ = 2;

    value.data_.push_back(99); // Unmatched values

    value.data_.push_back(99);



    panasonicMakerNote.print0x000f(oss, value, nullptr);



    EXPECT_EQ("99 99", oss.str()); // Output should be the original value as string

}
