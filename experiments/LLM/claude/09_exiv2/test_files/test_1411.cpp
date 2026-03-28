#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal function and tag details
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa401(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0xa401Test_1411 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal operation with value 0 -> "Normal process"
TEST_F(Print0xa401Test_1411, NormalProcess_1411) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0xa401(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Normal process");
}

// Test normal operation with value 1 -> "Custom process"
TEST_F(Print0xa401Test_1411, CustomProcess_1411) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0xa401(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Custom process");
}

// Test with unknown value (out of range) - value 2
TEST_F(Print0xa401Test_1411, UnknownValue2_1411) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0xa401(os, *value, nullptr);
    std::string result = os.str();
    // Unknown values typically print as "(n)" or just the number
    EXPECT_FALSE(result.empty());
    // Should not match either known string
    EXPECT_NE(result, "Normal process");
    EXPECT_NE(result, "Custom process");
}

// Test with unknown negative-like large value
TEST_F(Print0xa401Test_1411, UnknownLargeValue_1411) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");
    Exiv2::Internal::print0xa401(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Normal process");
    EXPECT_NE(result, "Custom process");
}

// Test with ExifData pointer provided (non-null) - value 0
TEST_F(Print0xa401Test_1411, NormalProcessWithMetadata_1411) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0xa401(os, *value, &exifData);
    EXPECT_EQ(os.str(), "Normal process");
}

// Test with ExifData pointer provided (non-null) - value 1
TEST_F(Print0xa401Test_1411, CustomProcessWithMetadata_1411) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0xa401(os, *value, &exifData);
    EXPECT_EQ(os.str(), "Custom process");
}

// Test that the function returns the same ostream reference
TEST_F(Print0xa401Test_1411, ReturnsOstreamReference_1411) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    std::ostream& returned = Exiv2::Internal::print0xa401(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test with value using unsignedLong type
TEST_F(Print0xa401Test_1411, UnsignedLongValue0_1411) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("0");
    Exiv2::Internal::print0xa401(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Normal process");
}

// Test with value using unsignedLong type for value 1
TEST_F(Print0xa401Test_1411, UnsignedLongValue1_1411) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("1");
    Exiv2::Internal::print0xa401(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Custom process");
}

// Test with unknown value 100
TEST_F(Print0xa401Test_1411, UnknownValue100_1411) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("100");
    Exiv2::Internal::print0xa401(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Normal process");
    EXPECT_NE(result, "Custom process");
}

// Test chaining - write to ostream that already has content
TEST_F(Print0xa401Test_1411, AppendToExistingStream_1411) {
    os << "prefix: ";
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0xa401(os, *value, nullptr);
    EXPECT_EQ(os.str(), "prefix: Custom process");
}
