#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal function and tag details
namespace Exiv2 {
namespace Internal {
std::ostream& printExifUnit(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class PrintExifUnitTest_1381 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test that value 1 prints "none"
TEST_F(PrintExifUnitTest_1381, Value1PrintsNone_1381) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::printExifUnit(os, *value, nullptr);
    EXPECT_EQ(os.str(), "none");
}

// Test that value 2 prints "inch"
TEST_F(PrintExifUnitTest_1381, Value2PrintsInch_1381) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::printExifUnit(os, *value, nullptr);
    EXPECT_EQ(os.str(), "inch");
}

// Test that value 3 prints "cm"
TEST_F(PrintExifUnitTest_1381, Value3PrintsCm_1381) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::printExifUnit(os, *value, nullptr);
    EXPECT_EQ(os.str(), "cm");
}

// Test that an unknown value (0) prints the numeric value (not a known string)
TEST_F(PrintExifUnitTest_1381, Value0PrintsUnknown_1381) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::printExifUnit(os, *value, nullptr);
    std::string result = os.str();
    // Value 0 is not in the tag details, so it should print something indicating unknown
    // Typically prints "(0)" or the raw number
    EXPECT_NE(result, "none");
    EXPECT_NE(result, "inch");
    EXPECT_NE(result, "cm");
}

// Test that an unknown value (4) prints something other than the known strings
TEST_F(PrintExifUnitTest_1381, Value4PrintsUnknown_1381) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("4");
    Exiv2::Internal::printExifUnit(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result, "none");
    EXPECT_NE(result, "inch");
    EXPECT_NE(result, "cm");
}

// Test that a large unknown value prints something other than the known strings
TEST_F(PrintExifUnitTest_1381, LargeValuePrintsUnknown_1381) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");
    Exiv2::Internal::printExifUnit(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result, "none");
    EXPECT_NE(result, "inch");
    EXPECT_NE(result, "cm");
}

// Test with ExifData pointer (non-null but empty)
TEST_F(PrintExifUnitTest_1381, WithEmptyExifData_1381) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::printExifUnit(os, *value, &exifData);
    EXPECT_EQ(os.str(), "inch");
}

// Test that the function returns the ostream reference
TEST_F(PrintExifUnitTest_1381, ReturnsOstreamReference_1381) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    std::ostream& result = Exiv2::Internal::printExifUnit(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with unsignedLong type value for value 2
TEST_F(PrintExifUnitTest_1381, UnsignedLongValue2PrintsInch_1381) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("2");
    Exiv2::Internal::printExifUnit(os, *value, nullptr);
    EXPECT_EQ(os.str(), "inch");
}

// Test negative value prints unknown
TEST_F(PrintExifUnitTest_1381, NegativeValuePrintsUnknown_1381) {
    auto value = Exiv2::Value::create(Exiv2::signedShort);
    value->read("-1");
    Exiv2::Internal::printExifUnit(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result, "none");
    EXPECT_NE(result, "inch");
    EXPECT_NE(result, "cm");
}
