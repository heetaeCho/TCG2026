#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa217(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0xa217Test_1408 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: Value of 1 should print "Not defined"
TEST_F(Print0xa217Test_1408, SensingMethodNotDefined_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0xa217(os, *value, nullptr);
    EXPECT_NE(os.str().find("Not defined"), std::string::npos);
}

// Test: Value of 2 should print "One-chip color area"
TEST_F(Print0xa217Test_1408, SensingMethodOneChipColorArea_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0xa217(os, *value, nullptr);
    EXPECT_NE(os.str().find("One-chip color area"), std::string::npos);
}

// Test: Value of 3 should print "Two-chip color area"
TEST_F(Print0xa217Test_1408, SensingMethodTwoChipColorArea_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0xa217(os, *value, nullptr);
    EXPECT_NE(os.str().find("Two-chip color area"), std::string::npos);
}

// Test: Value of 4 should print "Three-chip color area"
TEST_F(Print0xa217Test_1408, SensingMethodThreeChipColorArea_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("4");
    Exiv2::Internal::print0xa217(os, *value, nullptr);
    EXPECT_NE(os.str().find("Three-chip color area"), std::string::npos);
}

// Test: Value of 5 should print "Color sequential area"
TEST_F(Print0xa217Test_1408, SensingMethodColorSequentialArea_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("5");
    Exiv2::Internal::print0xa217(os, *value, nullptr);
    EXPECT_NE(os.str().find("Color sequential area"), std::string::npos);
}

// Test: Value of 7 should print "Trilinear sensor"
TEST_F(Print0xa217Test_1408, SensingMethodTrilinearSensor_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("7");
    Exiv2::Internal::print0xa217(os, *value, nullptr);
    EXPECT_NE(os.str().find("Trilinear sensor"), std::string::npos);
}

// Test: Value of 8 should print "Color sequential linear"
TEST_F(Print0xa217Test_1408, SensingMethodColorSequentialLinear_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("8");
    Exiv2::Internal::print0xa217(os, *value, nullptr);
    EXPECT_NE(os.str().find("Color sequential linear"), std::string::npos);
}

// Test: Value of 6 is not in the table (gap between 5 and 7), should print unknown/numeric
TEST_F(Print0xa217Test_1408, SensingMethodUnknownValue6_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("6");
    Exiv2::Internal::print0xa217(os, *value, nullptr);
    std::string result = os.str();
    // Should not match any known sensing method name
    EXPECT_EQ(result.find("One-chip"), std::string::npos);
    EXPECT_EQ(result.find("Two-chip"), std::string::npos);
    EXPECT_EQ(result.find("Three-chip"), std::string::npos);
    EXPECT_EQ(result.find("Color sequential"), std::string::npos);
    EXPECT_EQ(result.find("Trilinear"), std::string::npos);
    EXPECT_EQ(result.find("Not defined"), std::string::npos);
    // The output should not be empty
    EXPECT_FALSE(result.empty());
}

// Test: Value of 0 is not in the table, boundary below minimum
TEST_F(Print0xa217Test_1408, SensingMethodUnknownValue0_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0xa217(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.find("Not defined"), std::string::npos);
    EXPECT_FALSE(result.empty());
}

// Test: Value of 9 is above the maximum known value
TEST_F(Print0xa217Test_1408, SensingMethodUnknownValue9_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("9");
    Exiv2::Internal::print0xa217(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.find("Color sequential linear"), std::string::npos);
    EXPECT_FALSE(result.empty());
}

// Test: Large unknown value
TEST_F(Print0xa217Test_1408, SensingMethodLargeUnknownValue_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("255");
    Exiv2::Internal::print0xa217(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Function returns the same ostream reference
TEST_F(Print0xa217Test_1408, ReturnsOstreamReference_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    std::ostream& returned = Exiv2::Internal::print0xa217(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test: With non-null ExifData pointer
TEST_F(Print0xa217Test_1408, WithExifDataPointer_1408) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0xa217(os, *value, &exifData);
    EXPECT_NE(os.str().find("One-chip color area"), std::string::npos);
}

// Test: Using unsignedLong type for the value
TEST_F(Print0xa217Test_1408, UnsignedLongValue_1408) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("7");
    Exiv2::Internal::print0xa217(os, *value, nullptr);
    EXPECT_NE(os.str().find("Trilinear sensor"), std::string::npos);
}
