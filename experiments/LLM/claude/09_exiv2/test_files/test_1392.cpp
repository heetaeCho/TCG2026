#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0x0112(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0x0112Test_1392 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal orientation values (1-8)
TEST_F(Print0x0112Test_1392, Orientation1_TopLeft_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    EXPECT_NE(os.str().find("top, left"), std::string::npos) << "Actual: " << os.str();
}

TEST_F(Print0x0112Test_1392, Orientation2_TopRight_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    EXPECT_NE(os.str().find("top, right"), std::string::npos) << "Actual: " << os.str();
}

TEST_F(Print0x0112Test_1392, Orientation3_BottomRight_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    EXPECT_NE(os.str().find("bottom, right"), std::string::npos) << "Actual: " << os.str();
}

TEST_F(Print0x0112Test_1392, Orientation4_BottomLeft_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("4");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    EXPECT_NE(os.str().find("bottom, left"), std::string::npos) << "Actual: " << os.str();
}

TEST_F(Print0x0112Test_1392, Orientation5_LeftTop_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("5");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    EXPECT_NE(os.str().find("left, top"), std::string::npos) << "Actual: " << os.str();
}

TEST_F(Print0x0112Test_1392, Orientation6_RightTop_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("6");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    EXPECT_NE(os.str().find("right, top"), std::string::npos) << "Actual: " << os.str();
}

TEST_F(Print0x0112Test_1392, Orientation7_RightBottom_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("7");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    EXPECT_NE(os.str().find("right, bottom"), std::string::npos) << "Actual: " << os.str();
}

TEST_F(Print0x0112Test_1392, Orientation8_LeftBottom_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("8");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    EXPECT_NE(os.str().find("left, bottom"), std::string::npos) << "Actual: " << os.str();
}

// Test boundary: value 0 is not in the table (below minimum valid value 1)
TEST_F(Print0x0112Test_1392, OrientationZero_Unknown_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    std::string result = os.str();
    // Value 0 is not in the tag details, so it should not match any known orientation string
    // It likely prints the numeric value or "(0)"
    EXPECT_EQ(result.find("top, left"), std::string::npos) << "Actual: " << result;
    EXPECT_FALSE(result.empty());
}

// Test boundary: value 9 is above the maximum valid value 8
TEST_F(Print0x0112Test_1392, Orientation9_OutOfRange_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("9");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    std::string result = os.str();
    // Value 9 is not in the tag details
    EXPECT_EQ(result.find("left, bottom"), std::string::npos) << "Actual: " << result;
    EXPECT_FALSE(result.empty());
}

// Test with a large out-of-range value
TEST_F(Print0x0112Test_1392, OrientationLargeValue_OutOfRange_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with negative value (using signed short)
TEST_F(Print0x0112Test_1392, OrientationNegativeValue_1392) {
    auto value = Exiv2::Value::create(Exiv2::signedShort);
    value->read("-1");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test that the function returns the same ostream reference
TEST_F(Print0x0112Test_1392, ReturnsOstreamReference_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    std::ostream& returned = Exiv2::Internal::print0x0112(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test with nullptr metadata (should still work)
TEST_F(Print0x0112Test_1392, NullMetadata_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("6");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    EXPECT_NE(os.str().find("right, top"), std::string::npos) << "Actual: " << os.str();
}

// Test with actual ExifData pointer
TEST_F(Print0x0112Test_1392, WithExifData_1392) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0x0112(os, *value, &exifData);
    EXPECT_NE(os.str().find("bottom, right"), std::string::npos) << "Actual: " << os.str();
}

// Test with unsignedLong type value
TEST_F(Print0x0112Test_1392, UnsignedLongValue_1392) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("4");
    Exiv2::Internal::print0x0112(os, *value, nullptr);
    EXPECT_NE(os.str().find("bottom, left"), std::string::npos) << "Actual: " << os.str();
}

// Test consecutive calls to verify stream append behavior
TEST_F(Print0x0112Test_1392, ConsecutiveCalls_1392) {
    auto value1 = Exiv2::Value::create(Exiv2::unsignedShort);
    value1->read("1");
    Exiv2::Internal::print0x0112(os, *value1, nullptr);
    std::string first = os.str();
    EXPECT_FALSE(first.empty());

    auto value2 = Exiv2::Value::create(Exiv2::unsignedShort);
    value2->read("8");
    Exiv2::Internal::print0x0112(os, *value2, nullptr);
    std::string second = os.str();
    // Second call appends to stream, so second should be longer
    EXPECT_GT(second.size(), first.size());
}
