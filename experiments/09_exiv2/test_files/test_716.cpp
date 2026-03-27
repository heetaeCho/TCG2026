#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/panasonicmn_int.cpp"

#include <sstream>

#include <exiv2/value.hpp>

#include <exiv2/exif.hpp>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class PanasonicMakerNoteTest_716 : public ::testing::Test {

protected:

    PanasonicMakerNote panasonicMakerNote;

    std::ostringstream os;

    Exiv2::ExifData exifData;

};



TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_NormalOperation_716) {

    Exiv2::Value value;

    value.makeArray<int32_t>(1);

    value[0] = 150;



    std::ostringstream os;

    panasonicMakerNote.printRollAngle(os, value, &exifData);



    EXPECT_EQ("15.0", os.str());

}



TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_ZeroValue_716) {

    Exiv2::Value value;

    value.makeArray<int32_t>(1);

    value[0] = 0;



    std::ostringstream os;

    panasonicMakerNote.printRollAngle(os, value, &exifData);



    EXPECT_EQ("0.0", os.str());

}



TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_NegativeValue_716) {

    Exiv2::Value value;

    value.makeArray<int32_t>(1);

    value[0] = -50;



    std::ostringstream os;

    panasonicMakerNote.printRollAngle(os, value, &exifData);



    EXPECT_EQ("-5.0", os.str());

}



TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_BoundaryConditionPositiveMax_716) {

    Exiv2::Value value;

    value.makeArray<int32_t>(1);

    value[0] = 32767;



    std::ostringstream os;

    panasonicMakerNote.printRollAngle(os, value, &exifData);



    EXPECT_EQ("3276.7", os.str());

}



TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_BoundaryConditionNegativeMax_716) {

    Exiv2::Value value;

    value.makeArray<int32_t>(1);

    value[0] = -32768;



    std::ostringstream os;

    panasonicMakerNote.printRollAngle(os, value, &exifData);



    EXPECT_EQ("-3276.8", os.str());

}



TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_ValueTooLarge_716) {

    Exiv2::Value value;

    value.makeArray<int32_t>(1);

    value[0] = 100000;



    std::ostringstream os;

    panasonicMakerNote.printRollAngle(os, value, &exifData);



    EXPECT_EQ("10000.0", os.str());

}



TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_ValueTooSmall_716) {

    Exiv2::Value value;

    value.makeArray<int32_t>(1);

    value[0] = -100000;



    std::ostringstream os;

    panasonicMakerNote.printRollAngle(os, value, &exifData);



    EXPECT_EQ("-10000.0", os.str());

}
