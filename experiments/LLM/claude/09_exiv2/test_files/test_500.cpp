#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to include the internal header or replicate the class declaration
// Based on the provided code, we work with the Nikon3MakerNote class
namespace Exiv2 {
namespace Internal {
class Nikon3MakerNote {
 public:
  std::ostream& printCameraExposureCompensation(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_500 : public ::testing::Test {
 protected:
  Nikon3MakerNote maker_note_;
  std::ostringstream oss_;
};

// Test: When value count is not 1, output should be "(" + value + ")"
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_MultipleValues_500) {
  // Create a value with more than one component
  Exiv2::ValueType<uint8_t> value;
  value.value_.push_back(10);
  value.value_.push_back(20);

  maker_note_.printCameraExposureCompensation(oss_, value, nullptr);
  std::string result = oss_.str();

  // Should start with "(" and end with ")"
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: When value type is not unsignedByte, output should be "(" + value + ")"
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_WrongType_500) {
  // Create a value with correct count but wrong type (signedShort instead of unsignedByte)
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(42);

  maker_note_.printCameraExposureCompensation(oss_, value, nullptr);
  std::string result = oss_.str();

  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: When value count is 1 and type is unsignedByte with value 0
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_ZeroValue_500) {
  Exiv2::ValueType<uint8_t> value;
  value.value_.push_back(0);

  maker_note_.printCameraExposureCompensation(oss_, value, nullptr);
  std::string result = oss_.str();

  // Value 0 should produce some valid output (likely "0")
  EXPECT_FALSE(result.empty());
  // Should NOT be wrapped in parentheses since it's valid input
  EXPECT_NE(result.front(), '(');
}

// Test: When value count is 1 and type is unsignedByte with typical compensation value
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_TypicalValue_500) {
  Exiv2::ValueType<uint8_t> value;
  // A typical exposure compensation value
  value.value_.push_back(6);  // Some compensation step

  maker_note_.printCameraExposureCompensation(oss_, value, nullptr);
  std::string result = oss_.str();

  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.front(), '(');
}

// Test: When value count is 1 and type is unsignedByte with max value 255
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_MaxByteValue_500) {
  Exiv2::ValueType<uint8_t> value;
  value.value_.push_back(255);

  maker_note_.printCameraExposureCompensation(oss_, value, nullptr);
  std::string result = oss_.str();

  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.front(), '(');
}

// Test: When value count is 0 (empty value), should fall into error branch
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_EmptyValue_500) {
  Exiv2::ValueType<uint8_t> value;
  // No values pushed - count should be 0

  maker_note_.printCameraExposureCompensation(oss_, value, nullptr);
  std::string result = oss_.str();

  // count != 1, so should be parenthesized
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: nullptr ExifData parameter should not cause crash
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_NullExifData_500) {
  Exiv2::ValueType<uint8_t> value;
  value.value_.push_back(12);

  EXPECT_NO_THROW(maker_note_.printCameraExposureCompensation(oss_, value, nullptr));
}

// Test: Valid ExifData pointer should not cause crash
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_ValidExifData_500) {
  Exiv2::ValueType<uint8_t> value;
  value.value_.push_back(12);
  ExifData exifData;

  EXPECT_NO_THROW(maker_note_.printCameraExposureCompensation(oss_, value, &exifData));
}

// Test: Return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_ReturnsSameStream_500) {
  Exiv2::ValueType<uint8_t> value;
  value.value_.push_back(0);

  std::ostream& result = maker_note_.printCameraExposureCompensation(oss_, value, nullptr);
  EXPECT_EQ(&result, &oss_);
}

// Test: Return value is the same ostream reference for error branch
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_ReturnsSameStreamErrorBranch_500) {
  Exiv2::ValueType<uint8_t> value;
  // Empty value triggers error branch

  std::ostream& result = maker_note_.printCameraExposureCompensation(oss_, value, nullptr);
  EXPECT_EQ(&result, &oss_);
}

// Test: Value of 128 (0x80) - potentially a negative compensation in signed interpretation
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_MidValue128_500) {
  Exiv2::ValueType<uint8_t> value;
  value.value_.push_back(128);

  maker_note_.printCameraExposureCompensation(oss_, value, nullptr);
  std::string result = oss_.str();

  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.front(), '(');
}

// Test: Common Nikon exposure compensation values
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_CommonValue_500) {
  // Test with value that typically represents 1 EV compensation
  Exiv2::ValueType<uint8_t> value;
  value.value_.push_back(6);  // 6/6 = 1 EV in typical Nikon encoding

  maker_note_.printCameraExposureCompensation(oss_, value, nullptr);
  std::string result = oss_.str();

  EXPECT_FALSE(result.empty());
}

// Test: Using signedByte type (wrong type, should use parenthesized format)
TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_SignedByteType_500) {
  Exiv2::ValueType<int8_t> value;
  value.value_.push_back(10);

  maker_note_.printCameraExposureCompensation(oss_, value, nullptr);
  std::string result = oss_.str();

  // signedByte != unsignedByte, so should be parenthesized
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}
