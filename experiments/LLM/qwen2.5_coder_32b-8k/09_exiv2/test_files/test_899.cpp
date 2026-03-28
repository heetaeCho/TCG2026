#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "olympusmn_int.cpp"  // Assuming this includes the necessary headers for Exiv2 and its dependencies



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class OlympusMakerNoteTest_899 : public ::testing::Test {

protected:

    OlympusMakerNote olympusMakerNote;

    std::ostringstream os;

    Value value;

};



TEST_F(OlympusMakerNoteTest_899, Print0x1015_TypeNotUnsignedShort_899) {

    EXPECT_CALL(value, typeId()).WillOnce(Return(typeId_t::string));

    olympusMakerNote.print0x1015(os, value, nullptr);

    EXPECT_EQ(os.str(), "");

}



TEST_F(OlympusMakerNoteTest_899, Print0x1015_CountIsZero_899) {

    EXPECT_CALL(value, typeId()).WillOnce(Return(typeId_t::unsignedShort));

    EXPECT_CALL(value, count()).WillOnce(Return(0));

    olympusMakerNote.print0x1015(os, value, nullptr);

    EXPECT_EQ(os.str(), "");

}



TEST_F(OlympusMakerNoteTest_899, Print0x1015_CountIsOne_Auto_899) {

    EXPECT_CALL(value, typeId()).WillOnce(Return(typeId_t::unsignedShort));

    EXPECT_CALL(value, count()).WillOnce(Return(1));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(1LL));

    olympusMakerNote.print0x1015(os, value, nullptr);

    EXPECT_EQ(os.str(), "Auto");

}



TEST_F(OlympusMakerNoteTest_899, Print0x1015_CountIsOne_NotAuto_899) {

    EXPECT_CALL(value, typeId()).WillOnce(Return(typeId_t::unsignedShort));

    EXPECT_CALL(value, count()).WillOnce(Return(1));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(2LL));

    olympusMakerNote.print0x1015(os, value, nullptr);

    EXPECT_EQ(os.str(), "2");

}



TEST_F(OlympusMakerNoteTest_899, Print0x1015_CountIsTwo_Auto_NoSubValue_899) {

    EXPECT_CALL(value, typeId()).WillOnce(Return(typeId_t::unsignedShort));

    EXPECT_CALL(value, count()).WillOnce(Return(2));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(1LL));

    EXPECT_CALL(value, toInt64(1)).WillOnce(Return(0LL));

    olympusMakerNote.print0x1015(os, value, nullptr);

    EXPECT_EQ(os.str(), "Auto");

}



TEST_F(OlympusMakerNoteTest_899, Print0x1015_CountIsTwo_Auto_WithSubValue_899) {

    EXPECT_CALL(value, typeId()).WillOnce(Return(typeId_t::unsignedShort));

    EXPECT_CALL(value, count()).WillOnce(Return(2));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(1LL));

    EXPECT_CALL(value, toInt64(1)).WillOnce(Return(100LL));

    olympusMakerNote.print0x1015(os, value, nullptr);

    EXPECT_EQ(os.str(), "Auto (100)");

}



TEST_F(OlympusMakerNoteTest_899, Print0x1015_CountIsTwo_3000Kelvin_899) {

    EXPECT_CALL(value, typeId()).WillOnce(Return(typeId_t::unsignedShort));

    EXPECT_CALL(value, count()).WillOnce(Return(2));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(2LL));

    EXPECT_CALL(value, toInt64(1)).WillOnce(Return(2LL));

    olympusMakerNote.print0x1015(os, value, nullptr);

    EXPECT_EQ(os.str(), "3000 Kelvin");

}



TEST_F(OlympusMakerNoteTest_899, Print0x1015_CountIsTwo_7500Kelvin_899) {

    EXPECT_CALL(value, typeId()).WillOnce(Return(typeId_t::unsignedShort));

    EXPECT_CALL(value, count()).WillOnce(Return(2));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(2LL));

    EXPECT_CALL(value, toInt64(1)).WillOnce(Return(8LL));

    olympusMakerNote.print0x1015(os, value, nullptr);

    EXPECT_EQ(os.str(), "7500 Kelvin");

}



TEST_F(OlympusMakerNoteTest_899, Print0x1015_CountIsTwo_OneTouch_NoSubValue_899) {

    EXPECT_CALL(value, typeId()).WillOnce(Return(typeId_t::unsignedShort));

    EXPECT_CALL(value, count()).WillOnce(Return(2));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(3LL));

    EXPECT_CALL(value, toInt64(1)).WillOnce(Return(0LL));

    olympusMakerNote.print0x1015(os, value, nullptr);

    EXPECT_EQ(os.str(), "One-touch");

}



TEST_F(OlympusMakerNoteTest_899, Print0x1015_CountIsTwo_OneTouch_WithSubValue_899) {

    EXPECT_CALL(value, typeId()).WillOnce(Return(typeId_t::unsignedShort));

    EXPECT_CALL(value, count()).WillOnce(Return(2));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(3LL));

    EXPECT_CALL(value, toInt64(1)).WillOnce(Return(5LL));

    olympusMakerNote.print0x1015(os, value, nullptr);

    EXPECT_EQ(os.str(), "3 5");

}



TEST_F(OlympusMakerNoteTest_899, Print0x1015_CountIsTwo_UnknownValues_899) {

    EXPECT_CALL(value, typeId()).WillOnce(Return(typeId_t::unsignedShort));

    EXPECT_CALL(value, count()).WillOnce(Return(2));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(4LL));  // Unknown l0

    EXPECT_CALL(value, toInt64(1)).WillOnce(Return(1LL));

    olympusMakerNote.print0x1015(os, value, nullptr);

    EXPECT_EQ(os.str(), "4 1");

}



TEST_F(OlympusMakerNoteTest_899, Print0x1015_CountIsThree_899) {

    EXPECT_CALL(value, typeId()).WillOnce(Return(typeId_t::unsignedShort));

    EXPECT_CALL(value, count()).WillOnce(Return(3));  // Unexpected count

    olympusMakerNote.print0x1015(os, value, nullptr);

    EXPECT_EQ(os.str(), "3");

}
