#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <exiv2/exiv2.hpp>

// We need access to the Internal namespace
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNotePrintAperture_478 : public ::testing::Test {
protected:
    Nikon3MakerNote maker_;
    std::ostringstream os_;
};

// Test: When value count is not 1, should print "(" value ")"
TEST_F(Nikon3MakerNotePrintAperture_478, MultipleValuesReturnsParenthesized_478) {
    // Create a value with more than one element
    Exiv2::DataBuf buf(2);
    buf.write_uint8(0, 48);
    buf.write_uint8(1, 96);

    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read(buf.c_data(), 2, Exiv2::bigEndian);

    maker_.printAperture(os_, *value, nullptr);
    std::string result = os_.str();
    // Should be in parenthesized format
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: When value type is not unsignedByte, should print "(" value ")"
TEST_F(Nikon3MakerNotePrintAperture_478, WrongTypeReturnsParenthesized_478) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("48");

    maker_.printAperture(os_, *value, nullptr);
    std::string result = os_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: When value is 0, should print "n/a" (or its translation)
TEST_F(Nikon3MakerNotePrintAperture_478, ZeroValueReturnsNA_478) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    Exiv2::DataBuf buf(1);
    buf.write_uint8(0, 0);
    value->read(buf.c_data(), 1, Exiv2::bigEndian);

    maker_.printAperture(os_, *value, nullptr);
    std::string result = os_.str();
    // Should contain "n/a" (possibly translated, but in default locale it's "n/a")
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: Normal aperture value - value of 48 should give F2.8 (2^(48/24) = 2^2 = 4... wait)
// Actually 2^(48/24) = 2^2 = 4, so F4.0
TEST_F(Nikon3MakerNotePrintAperture_478, Value48ReturnsF4_478) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    Exiv2::DataBuf buf(1);
    buf.write_uint8(0, 48);
    value->read(buf.c_data(), 1, Exiv2::bigEndian);

    maker_.printAperture(os_, *value, nullptr);
    std::string result = os_.str();
    EXPECT_EQ(result, "F4.0");
}

// Test: Value of 24 should give F2.0 (2^(24/24) = 2^1 = 2)
TEST_F(Nikon3MakerNotePrintAperture_478, Value24ReturnsF2_478) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    Exiv2::DataBuf buf(1);
    buf.write_uint8(0, 24);
    value->read(buf.c_data(), 1, Exiv2::bigEndian);

    maker_.printAperture(os_, *value, nullptr);
    std::string result = os_.str();
    EXPECT_EQ(result, "F2.0");
}

// Test: Value of 1 should give F1.0 approximately (2^(1/24) ≈ 1.029)
TEST_F(Nikon3MakerNotePrintAperture_478, Value1ReturnsSmallAperture_478) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    Exiv2::DataBuf buf(1);
    buf.write_uint8(0, 1);
    value->read(buf.c_data(), 1, Exiv2::bigEndian);

    maker_.printAperture(os_, *value, nullptr);
    std::string result = os_.str();
    // 2^(1/24) ≈ 1.029, so should be "F1.0"
    EXPECT_EQ(result.substr(0, 1), "F");
}

// Test: Value of 72 should give F8.0 (2^(72/24) = 2^3 = 8)
TEST_F(Nikon3MakerNotePrintAperture_478, Value72ReturnsF8_478) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    Exiv2::DataBuf buf(1);
    buf.write_uint8(0, 72);
    value->read(buf.c_data(), 1, Exiv2::bigEndian);

    maker_.printAperture(os_, *value, nullptr);
    std::string result = os_.str();
    EXPECT_EQ(result, "F8.0");
}

// Test: Value of 96 should give F16.0 (2^(96/24) = 2^4 = 16)
TEST_F(Nikon3MakerNotePrintAperture_478, Value96ReturnsF16_478) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    Exiv2::DataBuf buf(1);
    buf.write_uint8(0, 96);
    value->read(buf.c_data(), 1, Exiv2::bigEndian);

    maker_.printAperture(os_, *value, nullptr);
    std::string result = os_.str();
    EXPECT_EQ(result, "F16.0");
}

// Test: Value of 255 (max unsigned byte) should still produce a valid F-number string
TEST_F(Nikon3MakerNotePrintAperture_478, Value255ReturnsValidFNumber_478) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    Exiv2::DataBuf buf(1);
    buf.write_uint8(0, 255);
    value->read(buf.c_data(), 1, Exiv2::bigEndian);

    maker_.printAperture(os_, *value, nullptr);
    std::string result = os_.str();
    // Should start with 'F'
    EXPECT_EQ(result.substr(0, 1), "F");
    // 2^(255/24) = 2^10.625 ≈ 1579.7
    // So something like F1579.7 or similar
    EXPECT_GT(result.size(), 1u);
}

// Test: ExifData pointer is nullptr - should still work fine
TEST_F(Nikon3MakerNotePrintAperture_478, NullExifDataWorks_478) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    Exiv2::DataBuf buf(1);
    buf.write_uint8(0, 48);
    value->read(buf.c_data(), 1, Exiv2::bigEndian);

    // Should not crash with nullptr ExifData
    EXPECT_NO_THROW(maker_.printAperture(os_, *value, nullptr));
}

// Test: Returns the same ostream reference
TEST_F(Nikon3MakerNotePrintAperture_478, ReturnsOstreamReference_478) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    Exiv2::DataBuf buf(1);
    buf.write_uint8(0, 48);
    value->read(buf.c_data(), 1, Exiv2::bigEndian);

    std::ostream& result = maker_.printAperture(os_, *value, nullptr);
    EXPECT_EQ(&result, &os_);
}

// Test: Value of 34 should give F2.8 approximately (2^(34/24) ≈ 2.67, close to 2.7)
// Actually 2^(34/24) = 2^1.4167 ≈ 2.67
TEST_F(Nikon3MakerNotePrintAperture_478, Value34ReturnsApproxF2p7_478) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    Exiv2::DataBuf buf(1);
    buf.write_uint8(0, 34);
    value->read(buf.c_data(), 1, Exiv2::bigEndian);

    maker_.printAperture(os_, *value, nullptr);
    std::string result = os_.str();
    EXPECT_EQ(result.substr(0, 1), "F");
    // Verify the numeric part is reasonable
    double expected = std::exp2(34.0 / 24.0);
    std::ostringstream expectedOs;
    expectedOs << std::fixed;
    expectedOs.precision(1);
    expectedOs << "F" << expected;
    EXPECT_EQ(result, expectedOs.str());
}

// Test: Value type is signedByte (not unsignedByte) - should trigger parenthesized output
TEST_F(Nikon3MakerNotePrintAperture_478, SignedByteTypeReturnsParenthesized_478) {
    auto value = Exiv2::Value::create(Exiv2::signedByte);
    value->read("48");

    maker_.printAperture(os_, *value, nullptr);
    std::string result = os_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Empty value (count == 0) should return parenthesized
TEST_F(Nikon3MakerNotePrintAperture_478, EmptyValueReturnsParenthesized_478) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    // Don't read any data - count should be 0

    maker_.printAperture(os_, *value, nullptr);
    std::string result = os_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}
