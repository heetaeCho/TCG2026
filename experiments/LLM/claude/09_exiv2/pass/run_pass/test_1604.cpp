#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1604 : public ::testing::Test {
protected:
    SonyMakerNote sonyMakerNote;
    std::ostringstream os;
};

// Test: When value is Auto (0), should print "Auto"
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_Auto_1604) {
    ULongValue value;
    value.read("0");
    
    sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    // "Auto" might be translated, but in default locale it should be "Auto"
    EXPECT_EQ(os.str(), "Auto");
}

// Test: When value is 0xffffffff, should print "n/a"
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_NA_1604) {
    ULongValue value;
    value.read("4294967295"); // 0xffffffff
    
    sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "n/a");
}

// Test: When value is a normal color temperature, should print value followed by " K"
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_NormalValue_1604) {
    ULongValue value;
    value.read("5500");
    
    sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "5500 K");
}

// Test: When value is 1 (boundary just above Auto), should print "1 K"
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_ValueOne_1604) {
    ULongValue value;
    value.read("1");
    
    sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "1 K");
}

// Test: When value is 0xfffffffe (boundary just below n/a), should print value with " K"
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_JustBelowNA_1604) {
    ULongValue value;
    value.read("4294967294"); // 0xfffffffe
    
    sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "4294967294 K");
}

// Test: When value count is not 1 (multiple values), should print in parentheses
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_MultipleValues_1604) {
    ULongValue value;
    value.read("5500 6500");
    
    sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: When value type is not unsignedLong, should print in parentheses
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_WrongType_1604) {
    UShortValue value;
    value.read("5500");
    
    sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: A typical daylight color temperature
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_Daylight_1604) {
    ULongValue value;
    value.read("6500");
    
    sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "6500 K");
}

// Test: A tungsten color temperature
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_Tungsten_1604) {
    ULongValue value;
    value.read("3200");
    
    sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "3200 K");
}

// Test: Return value is reference to the same ostream
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_ReturnsOstream_1604) {
    ULongValue value;
    value.read("5500");
    
    std::ostream& result = sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    EXPECT_EQ(&result, &os);
}

// Test: Return value is reference to the same ostream for Auto case
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_ReturnsOstream_Auto_1604) {
    ULongValue value;
    value.read("0");
    
    std::ostream& result = sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    EXPECT_EQ(&result, &os);
}

// Test: Return value is reference to the same ostream for error case
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_ReturnsOstream_Error_1604) {
    ULongValue value;
    value.read("100 200");
    
    std::ostream& result = sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    EXPECT_EQ(&result, &os);
}

// Test: With ExifData pointer being nullptr should still work
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_NullExifData_1604) {
    ULongValue value;
    value.read("2700");
    
    sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "2700 K");
}

// Test: Large but valid color temperature
TEST_F(SonyMakerNoteTest_1604, PrintColorTemperature_LargeValue_1604) {
    ULongValue value;
    value.read("100000");
    
    sonyMakerNote.printColorTemperature(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "100000 K");
}
