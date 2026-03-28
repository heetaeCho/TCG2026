#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration for the internal function we're testing
namespace Exiv2 {
namespace Internal {
std::ostream& print0x8822(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0x8822Test_1397 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal operation: value 0 should print "Not defined"
TEST_F(Print0x8822Test_1397, ValueZero_PrintsNotDefined_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Not defined");
}

// Test normal operation: value 1 should print "Manual"
TEST_F(Print0x8822Test_1397, ValueOne_PrintsManual_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Manual");
}

// Test normal operation: value 2 should print "Auto"
TEST_F(Print0x8822Test_1397, ValueTwo_PrintsAuto_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Auto");
}

// Test normal operation: value 3 should print "Aperture priority"
TEST_F(Print0x8822Test_1397, ValueThree_PrintsAperturePriority_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Aperture priority");
}

// Test normal operation: value 4 should print "Shutter priority"
TEST_F(Print0x8822Test_1397, ValueFour_PrintsShutterPriority_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("4");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Shutter priority");
}

// Test normal operation: value 5 should print "Creative program"
TEST_F(Print0x8822Test_1397, ValueFive_PrintsCreativeProgram_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("5");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Creative program");
}

// Test normal operation: value 6 should print "Action program"
TEST_F(Print0x8822Test_1397, ValueSix_PrintsActionProgram_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("6");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Action program");
}

// Test normal operation: value 7 should print "Portrait mode"
TEST_F(Print0x8822Test_1397, ValueSeven_PrintsPortraitMode_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("7");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Portrait mode");
}

// Test normal operation: value 8 should print "Landscape mode"
TEST_F(Print0x8822Test_1397, ValueEight_PrintsLandscapeMode_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("8");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Landscape mode");
}

// Test boundary: value 9 is out of range, should print the numeric value
TEST_F(Print0x8822Test_1397, ValueNine_OutOfRange_PrintsNumeric_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("9");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    std::string result = os.str();
    // Out-of-range values typically print as "(9)"
    EXPECT_NE(result, "Landscape mode");
    EXPECT_NE(result, "Not defined");
    // Should contain the number 9 in some form
    EXPECT_NE(result.find("9"), std::string::npos);
}

// Test boundary: large value that is out of range
TEST_F(Print0x8822Test_1397, ValueLarge_OutOfRange_PrintsNumeric_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("255");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    std::string result = os.str();
    // Should contain 255 in some form
    EXPECT_NE(result.find("255"), std::string::npos);
}

// Test with nullptr metadata - should still work
TEST_F(Print0x8822Test_1397, NullMetadata_StillWorks_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Auto");
}

// Test with actual ExifData pointer
TEST_F(Print0x8822Test_1397, WithExifData_StillWorks_1397) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0x8822(os, *value, &exifData);
    EXPECT_EQ(os.str(), "Manual");
}

// Test that the function returns the ostream reference
TEST_F(Print0x8822Test_1397, ReturnsOstreamReference_1397) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    std::ostream& result = Exiv2::Internal::print0x8822(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with signed long type value
TEST_F(Print0x8822Test_1397, SignedLongValue_PrintsCorrectly_1397) {
    auto value = Exiv2::Value::create(Exiv2::signedLong);
    value->read("4");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Shutter priority");
}

// Test with negative value (out of range)
TEST_F(Print0x8822Test_1397, NegativeValue_OutOfRange_1397) {
    auto value = Exiv2::Value::create(Exiv2::signedShort);
    value->read("-1");
    Exiv2::Internal::print0x8822(os, *value, nullptr);
    std::string result = os.str();
    // Negative value should not match any known tag
    EXPECT_NE(result, "Not defined");
    EXPECT_NE(result, "Manual");
}
