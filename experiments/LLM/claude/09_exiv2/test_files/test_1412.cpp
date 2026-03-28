#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa402(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0xa402Test_1412 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal case: value 0 should print "Auto"
TEST_F(Print0xa402Test_1412, ValueZeroPrintsAuto_1412) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    Exiv2::Internal::print0xa402(os, value, nullptr);
    EXPECT_EQ(os.str(), "Auto");
}

// Test normal case: value 1 should print "Manual"
TEST_F(Print0xa402Test_1412, ValueOnePrintsManual_1412) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    Exiv2::Internal::print0xa402(os, value, nullptr);
    EXPECT_EQ(os.str(), "Manual");
}

// Test normal case: value 2 should print "Auto bracket"
TEST_F(Print0xa402Test_1412, ValueTwoPrintsAutoBracket_1412) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("2");
    Exiv2::Internal::print0xa402(os, value, nullptr);
    EXPECT_EQ(os.str(), "Auto bracket");
}

// Test boundary/error case: unknown value (3) should print something (likely "(3)")
TEST_F(Print0xa402Test_1412, ValueThreeUnknown_1412) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("3");
    Exiv2::Internal::print0xa402(os, value, nullptr);
    std::string result = os.str();
    // Unknown values typically print "(n)" format
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, "(3)");
}

// Test boundary/error case: large unknown value
TEST_F(Print0xa402Test_1412, LargeUnknownValue_1412) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("65535");
    Exiv2::Internal::print0xa402(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, "(65535)");
}

// Test with non-null metadata pointer (should still work)
TEST_F(Print0xa402Test_1412, WithNonNullMetadata_1412) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    Exiv2::Internal::print0xa402(os, value, &exifData);
    EXPECT_EQ(os.str(), "Auto");
}

// Test that the function returns the same ostream reference
TEST_F(Print0xa402Test_1412, ReturnsOstreamReference_1412) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    std::ostream& result = Exiv2::Internal::print0xa402(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with signed long value type
TEST_F(Print0xa402Test_1412, SignedLongValueTypeZero_1412) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("0");
    Exiv2::Internal::print0xa402(os, value, nullptr);
    EXPECT_EQ(os.str(), "Auto");
}

// Test with signed long value type for Manual
TEST_F(Print0xa402Test_1412, SignedLongValueTypeOne_1412) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("2");
    Exiv2::Internal::print0xa402(os, value, nullptr);
    EXPECT_EQ(os.str(), "Auto bracket");
}

// Test unknown negative-like value (when using unsigned, a very large number)
TEST_F(Print0xa402Test_1412, ValueFourUnknown_1412) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("4");
    Exiv2::Internal::print0xa402(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, "(4)");
}
