#include <gtest/gtest.h>
#include <sstream>
#include <cstdint>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to access the PanasonicMakerNote class from Internal namespace
// Since the class is in the internal namespace, we replicate the minimal declaration
// based on the provided code
namespace Exiv2 {
namespace Internal {
class PanasonicMakerNote {
 public:
  std::ostream& printRollAngle(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

class PanasonicMakerNoteTest_716 : public ::testing::Test {
 protected:
  Exiv2::Internal::PanasonicMakerNote maker_;
  std::ostringstream oss_;
};

// Test normal positive angle
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_PositiveValue_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(150);  // 150 / 10.0 = 15.0

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("15.0", oss_.str());
}

// Test normal negative angle
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_NegativeValue_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(-150);  // -150 / 10.0 = -15.0

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("-15.0", oss_.str());
}

// Test zero angle
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_ZeroValue_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(0);  // 0 / 10.0 = 0.0

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("0.0", oss_.str());
}

// Test value that produces a fractional result
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_FractionalResult_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(125);  // 125 / 10.0 = 12.5

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("12.5", oss_.str());
}

// Test small positive value
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_SmallPositive_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(1);  // 1 / 10.0 = 0.1

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("0.1", oss_.str());
}

// Test small negative value
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_SmallNegative_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(-1);  // -1 / 10.0 = -0.1

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("-0.1", oss_.str());
}

// Test maximum int16_t value
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_MaxInt16_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(INT16_MAX);  // 32767 / 10.0 = 3276.7

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("3276.7", oss_.str());
}

// Test minimum int16_t value
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_MinInt16_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(INT16_MIN);  // -32768 / 10.0 = -3276.8

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("-3276.8", oss_.str());
}

// Test value of 10 (exactly 1.0 degrees)
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_ExactlyOneDegree_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(10);  // 10 / 10.0 = 1.0

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("1.0", oss_.str());
}

// Test value of -10 (exactly -1.0 degrees)
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_ExactlyNegOneDegree_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(-10);  // -10 / 10.0 = -1.0

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("-1.0", oss_.str());
}

// Test that the function returns the same ostream reference
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_ReturnsOstream_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(100);

  std::ostream& result = maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ(&oss_, &result);
}

// Test value with rounding at one decimal place
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_ValueOf3_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(3);  // 3 / 10.0 = 0.3

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("0.3", oss_.str());
}

// Test value 999
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_Value999_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(999);  // 999 / 10.0 = 99.9

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("99.9", oss_.str());
}

// Test with nullptr ExifData (should work fine since it's unused)
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_NullExifData_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(50);

  // Should not crash with nullptr ExifData
  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("5.0", oss_.str());
}

// Test value that is a multiple of 10
TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_MultipleOf10_716) {
  Exiv2::ValueType<int16_t> value;
  value.value_.push_back(1800);  // 1800 / 10.0 = 180.0

  maker_.printRollAngle(oss_, value, nullptr);
  EXPECT_EQ("180.0", oss_.str());
}
