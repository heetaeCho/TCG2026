#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0x9208(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0x9208Test_1405 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test known light source value: 0 -> "Unknown"
TEST_F(Print0x9208Test_1405, LightSourceUnknown_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Unknown");
}

// Test known light source value: 1 -> "Daylight"
TEST_F(Print0x9208Test_1405, LightSourceDaylight_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Daylight");
}

// Test known light source value: 2 -> "Fluorescent"
TEST_F(Print0x9208Test_1405, LightSourceFluorescent_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Fluorescent");
}

// Test known light source value: 3 -> "Tungsten (incandescent light)"
TEST_F(Print0x9208Test_1405, LightSourceTungsten_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Tungsten (incandescent light)");
}

// Test known light source value: 4 -> "Flash"
TEST_F(Print0x9208Test_1405, LightSourceFlash_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("4");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Flash");
}

// Test known light source value: 9 -> "Fine weather"
TEST_F(Print0x9208Test_1405, LightSourceFineWeather_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("9");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Fine weather");
}

// Test known light source value: 10 -> "Cloudy weather"
TEST_F(Print0x9208Test_1405, LightSourceCloudyWeather_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("10");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Cloudy weather");
}

// Test known light source value: 11 -> "Shade"
TEST_F(Print0x9208Test_1405, LightSourceShade_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("11");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Shade");
}

// Test known light source value: 12 -> "Daylight fluorescent (D 5700 - 7100K)"
TEST_F(Print0x9208Test_1405, LightSourceDaylightFluorescent_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("12");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Daylight fluorescent (D 5700 - 7100K)");
}

// Test known light source value: 13 -> "Day white fluorescent (N 4600 - 5400K)"
TEST_F(Print0x9208Test_1405, LightSourceDayWhiteFluorescent_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("13");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Day white fluorescent (N 4600 - 5400K)");
}

// Test known light source value: 14 -> "Cool white fluorescent (W 3900 - 4500K)"
TEST_F(Print0x9208Test_1405, LightSourceCoolWhiteFluorescent_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("14");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Cool white fluorescent (W 3900 - 4500K)");
}

// Test known light source value: 15 -> "White fluorescent (WW 3200 - 3700K)"
TEST_F(Print0x9208Test_1405, LightSourceWhiteFluorescent_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("15");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "White fluorescent (WW 3200 - 3700K)");
}

// Test known light source value: 17 -> "Standard light A"
TEST_F(Print0x9208Test_1405, LightSourceStandardLightA_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("17");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Standard light A");
}

// Test known light source value: 18 -> "Standard light B"
TEST_F(Print0x9208Test_1405, LightSourceStandardLightB_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("18");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Standard light B");
}

// Test known light source value: 19 -> "Standard light C"
TEST_F(Print0x9208Test_1405, LightSourceStandardLightC_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("19");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Standard light C");
}

// Test known light source value: 20 -> "D55"
TEST_F(Print0x9208Test_1405, LightSourceD55_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("20");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "D55");
}

// Test known light source value: 21 -> "D65"
TEST_F(Print0x9208Test_1405, LightSourceD65_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("21");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "D65");
}

// Test known light source value: 22 -> "D75"
TEST_F(Print0x9208Test_1405, LightSourceD75_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("22");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "D75");
}

// Test known light source value: 23 -> "D50"
TEST_F(Print0x9208Test_1405, LightSourceD50_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("23");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "D50");
}

// Test known light source value: 24 -> "ISO studio tungsten"
TEST_F(Print0x9208Test_1405, LightSourceISOStudioTungsten_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("24");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "ISO studio tungsten");
}

// Test known light source value: 255 -> "Other light source"
TEST_F(Print0x9208Test_1405, LightSourceOther_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("255");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Other light source");
}

// Test unknown/unmapped value: 5 (not in the table, between 4 and 9)
TEST_F(Print0x9208Test_1405, UnknownValueBetweenGaps_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("5");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    std::string result = os.str();
    // Should output something for an unknown tag - typically "(5)"
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Unknown");
    EXPECT_NE(result, "Flash");
}

// Test unknown/unmapped value: 6
TEST_F(Print0x9208Test_1405, UnknownValue6_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("6");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test unknown/unmapped value: 16 (gap between 15 and 17)
TEST_F(Print0x9208Test_1405, UnknownValue16_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("16");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test unknown/unmapped value: 25 (just after last non-255 entry)
TEST_F(Print0x9208Test_1405, UnknownValue25_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("25");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test unknown/unmapped value: 254 (just before 255)
TEST_F(Print0x9208Test_1405, UnknownValue254_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("254");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test unknown/unmapped large value: 256
TEST_F(Print0x9208Test_1405, UnknownValue256_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("256");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test that the function returns a reference to the same ostream
TEST_F(Print0x9208Test_1405, ReturnsOstreamReference_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    std::ostream& returned = Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test with ExifData (non-null metadata)
TEST_F(Print0x9208Test_1405, WithExifDataNonNull_1405) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0x9208(os, *value, &exifData);
    EXPECT_EQ(os.str(), "Daylight");
}

// Test with value using signedShort type
TEST_F(Print0x9208Test_1405, SignedShortValue_1405) {
    auto value = Exiv2::Value::create(Exiv2::signedShort);
    value->read("2");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Fluorescent");
}

// Test with unsignedLong type value
TEST_F(Print0x9208Test_1405, UnsignedLongValue_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("4");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Flash");
}

// Test boundary: value 8 (not in table, between 4 and 9)
TEST_F(Print0x9208Test_1405, UnknownValue8_1405) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("8");
    Exiv2::Internal::print0x9208(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Value 8 is not in the table
    EXPECT_NE(result, "Fine weather");
}
