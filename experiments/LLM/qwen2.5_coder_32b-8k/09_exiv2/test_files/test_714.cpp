#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include <string>

#include "exiv2/src/panasonicmn_int.cpp"  // Adjust the include path as necessary



using namespace Exiv2::Internal;

using ::testing::HasSubstr;



class PanasonicMakerNoteTest_714 : public ::testing::Test {

protected:

    PanasonicMakerNote panasonicMakerNote;

    std::ostringstream os;

};



TEST_F(PanasonicMakerNoteTest_714, PrintPressure_NormalValue_714) {

    Exiv2::Value value;

    value.makeLong(1013);  // Example normal pressure value

    panasonicMakerNote.printPressure(os, value, nullptr);

    EXPECT_EQ(os.str(), "1013 hPa");

}



TEST_F(PanasonicMakerNoteTest_714, PrintPressure_MaxValue_714) {

    Exiv2::Value value;

    value.makeLong(65535);  // Maximum value indicating infinite

    panasonicMakerNote.printPressure(os, value, nullptr);

    EXPECT_EQ(os.str(), "infinite");

}



TEST_F(PanasonicMakerNoteTest_714, PrintPressure_ZeroValue_714) {

    Exiv2::Value value;

    value.makeLong(0);  // Zero pressure value

    panasonicMakerNote.printPressure(os, value, nullptr);

    EXPECT_EQ(os.str(), "0 hPa");

}



TEST_F(PanasonicMakerNoteTest_714, PrintPressure_NegativeValue_714) {

    Exiv2::Value value;

    value.makeLong(-1);  // Negative pressure value

    panasonicMakerNote.printPressure(os, value, nullptr);

    EXPECT_EQ(os.str(), "-1 hPa");

}



TEST_F(PanasonicMakerNoteTest_714, PrintPressure_LargeValue_714) {

    Exiv2::Value value;

    value.makeLong(99999);  // Large pressure value

    panasonicMakerNote.printPressure(os, value, nullptr);

    EXPECT_EQ(os.str(), "99999 hPa");

}
