#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "panasonicmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PanasonicMakerNoteTest_705 : public ::testing::Test {
protected:
    std::ostringstream os;
    ExifData exifData;
};

// Test that tagList returns a non-null pointer
TEST_F(PanasonicMakerNoteTest_705, TagListIsNotNull_705) {
    auto tags = PanasonicMakerNote::tagList();
    ASSERT_NE(tags, nullptr);
}

// Test print0x000f with a valid value
TEST_F(PanasonicMakerNoteTest_705, Print0x000f_NormalValue_705) {
    UShortValue value;
    value.read("1");
    auto& result = PanasonicMakerNote::print0x000f(os, value, &exifData);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// Test print0x000f with zero value
TEST_F(PanasonicMakerNoteTest_705, Print0x000f_ZeroValue_705) {
    UShortValue value;
    value.read("0");
    auto& result = PanasonicMakerNote::print0x000f(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test print0x0023 with a valid value
TEST_F(PanasonicMakerNoteTest_705, Print0x0023_NormalValue_705) {
    UShortValue value;
    value.read("1");
    auto& result = PanasonicMakerNote::print0x0023(os, value, &exifData);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// Test print0x0023 with zero
TEST_F(PanasonicMakerNoteTest_705, Print0x0023_ZeroValue_705) {
    UShortValue value;
    value.read("0");
    auto& result = PanasonicMakerNote::print0x0023(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test print0x0029 with a valid value
TEST_F(PanasonicMakerNoteTest_705, Print0x0029_NormalValue_705) {
    UShortValue value;
    value.read("0");
    auto& result = PanasonicMakerNote::print0x0029(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

// Test print0x0033 with a valid value
TEST_F(PanasonicMakerNoteTest_705, Print0x0033_NormalValue_705) {
    UShortValue value;
    value.read("1");
    auto& result = PanasonicMakerNote::print0x0033(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

// Test print0x0036 with a valid value
TEST_F(PanasonicMakerNoteTest_705, Print0x0036_NormalValue_705) {
    UShortValue value;
    value.read("0");
    auto& result = PanasonicMakerNote::print0x0036(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test print0x003c with a valid value
TEST_F(PanasonicMakerNoteTest_705, Print0x003c_NormalValue_705) {
    UShortValue value;
    value.read("1");
    auto& result = PanasonicMakerNote::print0x003c(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

// Test printPressure with a normal value
TEST_F(PanasonicMakerNoteTest_705, PrintPressure_NormalValue_705) {
    UShortValue value;
    value.read("65535");
    auto& result = PanasonicMakerNote::printPressure(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// Test printPressure with zero
TEST_F(PanasonicMakerNoteTest_705, PrintPressure_ZeroValue_705) {
    UShortValue value;
    value.read("0");
    auto& result = PanasonicMakerNote::printPressure(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test printPanasonicText with an ASCII value
TEST_F(PanasonicMakerNoteTest_705, PrintPanasonicText_AsciiValue_705) {
    StringValue value;
    value.read("Hello Panasonic");
    auto& result = PanasonicMakerNote::printPanasonicText(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test printPanasonicText with empty string
TEST_F(PanasonicMakerNoteTest_705, PrintPanasonicText_EmptyValue_705) {
    StringValue value;
    value.read("");
    auto& result = PanasonicMakerNote::printPanasonicText(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test printAccelerometer with a signed short value
TEST_F(PanasonicMakerNoteTest_705, PrintAccelerometer_NormalValue_705) {
    ShortValue value;
    value.read("100");
    auto& result = PanasonicMakerNote::printAccelerometer(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// Test printAccelerometer with zero value
TEST_F(PanasonicMakerNoteTest_705, PrintAccelerometer_ZeroValue_705) {
    ShortValue value;
    value.read("0");
    auto& result = PanasonicMakerNote::printAccelerometer(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test printRollAngle with a signed short value
TEST_F(PanasonicMakerNoteTest_705, PrintRollAngle_NormalValue_705) {
    ShortValue value;
    value.read("45");
    auto& result = PanasonicMakerNote::printRollAngle(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// Test printRollAngle with zero
TEST_F(PanasonicMakerNoteTest_705, PrintRollAngle_ZeroValue_705) {
    ShortValue value;
    value.read("0");
    auto& result = PanasonicMakerNote::printRollAngle(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test printRollAngle with negative value
TEST_F(PanasonicMakerNoteTest_705, PrintRollAngle_NegativeValue_705) {
    ShortValue value;
    value.read("-45");
    auto& result = PanasonicMakerNote::printRollAngle(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test printPitchAngle with a signed short value
TEST_F(PanasonicMakerNoteTest_705, PrintPitchAngle_NormalValue_705) {
    ShortValue value;
    value.read("30");
    auto& result = PanasonicMakerNote::printPitchAngle(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// Test printPitchAngle with zero
TEST_F(PanasonicMakerNoteTest_705, PrintPitchAngle_ZeroValue_705) {
    ShortValue value;
    value.read("0");
    auto& result = PanasonicMakerNote::printPitchAngle(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test printPitchAngle with negative value
TEST_F(PanasonicMakerNoteTest_705, PrintPitchAngle_NegativeValue_705) {
    ShortValue value;
    value.read("-30");
    auto& result = PanasonicMakerNote::printPitchAngle(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test print0x000f with large/unknown value
TEST_F(PanasonicMakerNoteTest_705, Print0x000f_UnknownValue_705) {
    UShortValue value;
    value.read("9999");
    auto& result = PanasonicMakerNote::print0x000f(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    // Should still produce output even for unknown values
    EXPECT_FALSE(os.str().empty());
}

// Test print0x0029 with a known value
TEST_F(PanasonicMakerNoteTest_705, Print0x0029_KnownValue_705) {
    UShortValue value;
    value.read("1");
    auto& result = PanasonicMakerNote::print0x0029(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test print0x0033 with unknown value
TEST_F(PanasonicMakerNoteTest_705, Print0x0033_UnknownValue_705) {
    UShortValue value;
    value.read("9999");
    auto& result = PanasonicMakerNote::print0x0033(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// Test printAccelerometer with large positive value
TEST_F(PanasonicMakerNoteTest_705, PrintAccelerometer_LargeValue_705) {
    ShortValue value;
    value.read("32767");
    auto& result = PanasonicMakerNote::printAccelerometer(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// Test printAccelerometer with large negative value
TEST_F(PanasonicMakerNoteTest_705, PrintAccelerometer_LargeNegativeValue_705) {
    ShortValue value;
    value.read("-32768");
    auto& result = PanasonicMakerNote::printAccelerometer(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// Test printPressure with a typical atmospheric pressure value
TEST_F(PanasonicMakerNoteTest_705, PrintPressure_TypicalValue_705) {
    UShortValue value;
    value.read("1013");
    auto& result = PanasonicMakerNote::printPressure(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// Test that stream chaining works (return reference is same stream)
TEST_F(PanasonicMakerNoteTest_705, StreamChainingWorks_705) {
    UShortValue value;
    value.read("1");
    std::ostringstream os2;
    PanasonicMakerNote::print0x000f(os2, value, nullptr);
    std::string firstOutput = os2.str();
    
    // Call again to verify it appends
    PanasonicMakerNote::print0x000f(os2, value, nullptr);
    std::string secondOutput = os2.str();
    
    // Second call should have appended, so it should be longer
    EXPECT_GE(secondOutput.size(), firstOutput.size());
}

// Test print0x0036 with large value
TEST_F(PanasonicMakerNoteTest_705, Print0x0036_LargeValue_705) {
    UShortValue value;
    value.read("65535");
    auto& result = PanasonicMakerNote::print0x0036(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// Test print0x003c with large value
TEST_F(PanasonicMakerNoteTest_705, Print0x003c_LargeValue_705) {
    UShortValue value;
    value.read("65535");
    auto& result = PanasonicMakerNote::print0x003c(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// Test printPanasonicText with special characters
TEST_F(PanasonicMakerNoteTest_705, PrintPanasonicText_SpecialChars_705) {
    StringValue value;
    value.read("Test\x00with\x00nulls");
    auto& result = PanasonicMakerNote::printPanasonicText(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test that nullptr ExifData parameter is handled
TEST_F(PanasonicMakerNoteTest_705, NullExifDataHandled_705) {
    UShortValue value;
    value.read("1");
    
    // None of these should crash with nullptr ExifData
    EXPECT_NO_THROW(PanasonicMakerNote::print0x000f(os, value, nullptr));
    EXPECT_NO_THROW(PanasonicMakerNote::print0x0023(os, value, nullptr));
    EXPECT_NO_THROW(PanasonicMakerNote::print0x0029(os, value, nullptr));
    EXPECT_NO_THROW(PanasonicMakerNote::print0x0033(os, value, nullptr));
    EXPECT_NO_THROW(PanasonicMakerNote::print0x0036(os, value, nullptr));
    EXPECT_NO_THROW(PanasonicMakerNote::print0x003c(os, value, nullptr));
    EXPECT_NO_THROW(PanasonicMakerNote::printPressure(os, value, nullptr));
}
