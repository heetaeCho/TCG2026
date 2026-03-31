#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to include the internal header or replicate the minimal interface
// Based on the provided code, we test SonyMakerNote::printExposureStandardAdjustment
#include "sonymn_int.hpp"

// If direct include doesn't work, we can use the namespace directly
// The function signature is:
// std::ostream& printExposureStandardAdjustment(std::ostream& os, const Value& value, const ExifData*)

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1601 : public ::testing::Test {
protected:
    SonyMakerNote sonyMakerNote;
    std::ostringstream os;
};

// Test with a valid signedRational value with count == 1
TEST_F(SonyMakerNoteTest_1601, ValidSignedRational_PositiveValue_1601) {
    RationalValue val; // This won't work; we need SignedRationalValue
    // Use ValueType<Rational> or appropriate Exiv2 value types
    
    auto value = Value::create(signedRational);
    Rational r = {3, 2}; // 1.5
    value->read(reinterpret_cast<const byte*>(&r), sizeof(r), littleEndian);
    
    sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr);
    
    // 3/2 = 1.5, formatted as "1.5"
    EXPECT_EQ(os.str(), "1.5");
}

// Test with a valid signedRational value representing zero
TEST_F(SonyMakerNoteTest_1601, ValidSignedRational_ZeroNumerator_1601) {
    auto value = Value::create(signedRational);
    Rational r = {0, 1};
    value->read(reinterpret_cast<const byte*>(&r), sizeof(r), littleEndian);
    
    sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "0.0");
}

// Test with a valid signedRational negative value
TEST_F(SonyMakerNoteTest_1601, ValidSignedRational_NegativeValue_1601) {
    auto value = Value::create(signedRational);
    Rational r = {-3, 2}; // -1.5
    value->read(reinterpret_cast<const byte*>(&r), sizeof(r), littleEndian);
    
    sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "-1.5");
}

// Test with wrong type (not signedRational) - should print parenthesized value
TEST_F(SonyMakerNoteTest_1601, WrongType_UnsignedRational_1601) {
    auto value = Value::create(unsignedRational);
    URational r = {3, 2};
    value->read(reinterpret_cast<const byte*>(&r), sizeof(r), littleEndian);
    
    sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test with wrong type - unsignedShort
TEST_F(SonyMakerNoteTest_1601, WrongType_UnsignedShort_1601) {
    auto value = Value::create(unsignedShort);
    uint16_t v = 42;
    value->read(reinterpret_cast<const byte*>(&v), sizeof(v), littleEndian);
    
    sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test with count != 1 (multiple signedRational values)
TEST_F(SonyMakerNoteTest_1601, MultipleValues_Count2_1601) {
    auto value = Value::create(signedRational);
    Rational r[2] = {{1, 2}, {3, 4}};
    value->read(reinterpret_cast<const byte*>(r), sizeof(r), littleEndian);
    
    sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr);
    
    std::string result = os.str();
    // count != 1, so should print parenthesized
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test with signedRational value 1/1 = 1.0
TEST_F(SonyMakerNoteTest_1601, ValidSignedRational_WholeNumber_1601) {
    auto value = Value::create(signedRational);
    Rational r = {1, 1};
    value->read(reinterpret_cast<const byte*>(&r), sizeof(r), littleEndian);
    
    sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "1.0");
}

// Test with signedRational value 1/3 ≈ 0.3
TEST_F(SonyMakerNoteTest_1601, ValidSignedRational_OneThird_1601) {
    auto value = Value::create(signedRational);
    Rational r = {1, 3};
    value->read(reinterpret_cast<const byte*>(&r), sizeof(r), littleEndian);
    
    sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "0.3");
}

// Test with nullptr ExifData (should not crash)
TEST_F(SonyMakerNoteTest_1601, NullExifData_1601) {
    auto value = Value::create(signedRational);
    Rational r = {5, 2}; // 2.5
    value->read(reinterpret_cast<const byte*>(&r), sizeof(r), littleEndian);
    
    EXPECT_NO_THROW(sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr));
    EXPECT_EQ(os.str(), "2.5");
}

// Test with large values
TEST_F(SonyMakerNoteTest_1601, ValidSignedRational_LargeValues_1601) {
    auto value = Value::create(signedRational);
    Rational r = {1000000, 3};
    value->read(reinterpret_cast<const byte*>(&r), sizeof(r), littleEndian);
    
    sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr);
    
    // 1000000/3 ≈ 333333.3
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.front(), '3'); // Should start with 3
}

// Test that the function returns the same ostream reference
TEST_F(SonyMakerNoteTest_1601, ReturnsOstreamReference_1601) {
    auto value = Value::create(signedRational);
    Rational r = {1, 2};
    value->read(reinterpret_cast<const byte*>(&r), sizeof(r), littleEndian);
    
    std::ostream& result = sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr);
    
    EXPECT_EQ(&result, &os);
}

// Test with count == 0 (empty value)
TEST_F(SonyMakerNoteTest_1601, EmptyValue_Count0_1601) {
    auto value = Value::create(signedRational);
    // Don't read any data, count should be 0
    
    sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr);
    
    std::string result = os.str();
    // count != 1, so should print parenthesized
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test with negative denominator
TEST_F(SonyMakerNoteTest_1601, ValidSignedRational_NegativeDenominator_1601) {
    auto value = Value::create(signedRational);
    Rational r = {3, -2}; // -1.5
    value->read(reinterpret_cast<const byte*>(&r), sizeof(r), littleEndian);
    
    sonyMakerNote.printExposureStandardAdjustment(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "-1.5");
}
