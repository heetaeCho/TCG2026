#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the Internal namespace function
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa40c(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0xa40cTest_1419 : public ::testing::Test {
protected:
    std::ostringstream os_;
};

// Test with value 0 -> "Unknown"
TEST_F(Print0xa40cTest_1419, ValueZeroReturnsUnknown_1419) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0xa40c(os_, *value, nullptr);
    EXPECT_EQ(os_.str(), "Unknown");
}

// Test with value 1 -> "Macro"
TEST_F(Print0xa40cTest_1419, ValueOneReturnsMacro_1419) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0xa40c(os_, *value, nullptr);
    EXPECT_EQ(os_.str(), "Macro");
}

// Test with value 2 -> "Close view"
TEST_F(Print0xa40cTest_1419, ValueTwoReturnsCloseView_1419) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0xa40c(os_, *value, nullptr);
    EXPECT_EQ(os_.str(), "Close view");
}

// Test with value 3 -> "Distant view"
TEST_F(Print0xa40cTest_1419, ValueThreeReturnsDistantView_1419) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0xa40c(os_, *value, nullptr);
    EXPECT_EQ(os_.str(), "Distant view");
}

// Test with out-of-range value (4) - should print something indicating unknown/out of range
TEST_F(Print0xa40cTest_1419, ValueOutOfRangeAbove_1419) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("4");
    Exiv2::Internal::print0xa40c(os_, *value, nullptr);
    std::string result = os_.str();
    // Out of range values typically print "(4)" or just the number
    EXPECT_FALSE(result.empty());
    // It should NOT match any of the known strings
    EXPECT_NE(result, "Unknown");
    EXPECT_NE(result, "Macro");
    EXPECT_NE(result, "Close view");
    EXPECT_NE(result, "Distant view");
}

// Test with a large out-of-range value
TEST_F(Print0xa40cTest_1419, ValueLargeOutOfRange_1419) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");
    Exiv2::Internal::print0xa40c(os_, *value, nullptr);
    std::string result = os_.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Unknown");
    EXPECT_NE(result, "Macro");
    EXPECT_NE(result, "Close view");
    EXPECT_NE(result, "Distant view");
}

// Test with ExifData pointer (non-null but empty)
TEST_F(Print0xa40cTest_1419, WithEmptyExifData_1419) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0xa40c(os_, *value, &exifData);
    EXPECT_EQ(os_.str(), "Macro");
}

// Test that the function returns the same ostream reference
TEST_F(Print0xa40cTest_1419, ReturnsOstreamReference_1419) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    std::ostream& result = Exiv2::Internal::print0xa40c(os_, *value, nullptr);
    EXPECT_EQ(&result, &os_);
}

// Test with value using unsignedLong type
TEST_F(Print0xa40cTest_1419, ValueUnsignedLongType_1419) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("3");
    Exiv2::Internal::print0xa40c(os_, *value, nullptr);
    EXPECT_EQ(os_.str(), "Distant view");
}

// Test boundary: value right at boundary of valid range (3, last valid)
TEST_F(Print0xa40cTest_1419, BoundaryLastValidValue_1419) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0xa40c(os_, *value, nullptr);
    EXPECT_EQ(os_.str(), "Distant view");
}

// Test boundary: first valid value (0)
TEST_F(Print0xa40cTest_1419, BoundaryFirstValidValue_1419) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0xa40c(os_, *value, nullptr);
    EXPECT_EQ(os_.str(), "Unknown");
}
