#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/pentaxmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class PentaxMakerNoteTest_192 : public ::testing::Test {

protected:

    PentaxMakerNote makerNote;

    Value mockValue;

};



TEST_F(PentaxMakerNoteTest_192, PrintTime_ValidInput_192) {

    std::ostringstream oss;

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(13));

    EXPECT_CALL(mockValue, toInt64(1)).WillOnce(::testing::Return(30));

    EXPECT_CALL(mockValue, toInt64(2)).WillOnce(::testing::Return(45));



    makerNote.printTime(oss, mockValue, nullptr);



    EXPECT_EQ("13:30:45", oss.str());

}



TEST_F(PentaxMakerNoteTest_192, PrintTime_ZeroInput_192) {

    std::ostringstream oss;

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockValue, toInt64(1)).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockValue, toInt64(2)).WillOnce(::testing::Return(0));



    makerNote.printTime(oss, mockValue, nullptr);



    EXPECT_EQ("00:00:00", oss.str());

}



TEST_F(PentaxMakerNoteTest_192, PrintTime_MaxInput_192) {

    std::ostringstream oss;

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(23));

    EXPECT_CALL(mockValue, toInt64(1)).WillOnce(::testing::Return(59));

    EXPECT_CALL(mockValue, toInt64(2)).WillOnce(::testing::Return(59));



    makerNote.printTime(oss, mockValue, nullptr);



    EXPECT_EQ("23:59:59", oss.str());

}



TEST_F(PentaxMakerNoteTest_192, PrintTime_NegativeInput_192) {

    std::ostringstream oss;

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(-1));

    EXPECT_CALL(mockValue, toInt64(1)).WillOnce(::testing::Return(-1));

    EXPECT_CALL(mockValue, toInt64(2)).WillOnce(::testing::Return(-1));



    makerNote.printTime(oss, mockValue, nullptr);



    EXPECT_EQ("-1:-1:-1", oss.str());

}



TEST_F(PentaxMakerNoteTest_192, PrintTime_LargeInput_192) {

    std::ostringstream oss;

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(100));

    EXPECT_CALL(mockValue, toInt64(1)).WillOnce(::testing::Return(100));

    EXPECT_CALL(mockValue, toInt64(2)).WillOnce(::testing::Return(100));



    makerNote.printTime(oss, mockValue, nullptr);



    EXPECT_EQ("100:100:100", oss.str());

}
