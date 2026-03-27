#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/panasonicmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;



class PanasonicMakerNoteTest_710 : public ::testing::Test {

protected:

    PanasonicMakerNote panasonicMakerNote;

};



TEST_F(PanasonicMakerNoteTest_710, Print0x0033_NotSetCase_710) {

    std::ostringstream os;

    Value value("9999:99:99 00:00:00");

    ExifData exifData;



    panasonicMakerNote.print0x0033(os, value, &exifData);



    EXPECT_EQ(os.str(), "not set");

}



TEST_F(PanasonicMakerNoteTest_710, Print0x0033_NormalCase_710) {

    std::ostringstream os;

    Value value("2023:10:05 14:30:00");

    ExifData exifData;



    panasonicMakerNote.print0x0033(os, value, &exifData);



    EXPECT_EQ(os.str(), "2023:10:05 14:30:00");

}



TEST_F(PanasonicMakerNoteTest_710, Print0x0033_EmptyValueCase_710) {

    std::ostringstream os;

    Value value("");

    ExifData exifData;



    panasonicMakerNote.print0x0033(os, value, &exifData);



    EXPECT_EQ(os.str(), "");

}



TEST_F(PanasonicMakerNoteTest_710, Print0x0033_DifferentFormatCase_710) {

    std::ostringstream os;

    Value value("2023-10-05 14:30:00");

    ExifData exifData;



    panasonicMakerNote.print0x0033(os, value, &exifData);



    EXPECT_EQ(os.str(), "2023-10-05 14:30:00");

}
