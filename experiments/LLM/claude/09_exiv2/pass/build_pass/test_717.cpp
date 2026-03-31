#include <gtest/gtest.h>
#include <sstream>
#include <cstdint>
#include <string>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the Internal namespace
namespace Exiv2 {
namespace Internal {

class PanasonicMakerNote {
 public:
  std::ostream& printPitchAngle(std::ostream& os, const Value& value, const ExifData*);
};

}  // namespace Internal
}  // namespace Exiv2

class PanasonicMakerNoteTest_717 : public ::testing::Test {
 protected:
  Exiv2::Internal::PanasonicMakerNote maker_;
  std::ostringstream os_;
};

// Test with a positive value - the output should be negated and divided by 10
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_PositiveValue_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("100");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "-10.0");
}

// Test with zero value
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_ZeroValue_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("0");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "0.0");
}

// Test with a negative value - the output should be positive (negation of negative)
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_NegativeValue_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("-100");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "10.0");
}

// Test with value of 1 - should produce -0.1
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_SmallPositiveValue_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("1");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "-0.1");
}

// Test with value of -1 - should produce 0.1
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_SmallNegativeValue_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("-1");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "0.1");
}

// Test with max int16_t value (32767)
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_MaxInt16Value_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("32767");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "-3276.7");
}

// Test with min int16_t value (-32768)
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_MinInt16Value_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("-32768");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "3276.8");
}

// Test with value 5 - should produce -0.5
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_ValueFive_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("5");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "-0.5");
}

// Test with value 10 - should produce -1.0
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_ValueTen_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("10");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "-1.0");
}

// Test with value -10 - should produce 1.0
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_ValueNegTen_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("-10");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "1.0");
}

// Test with nullptr ExifData - should still work
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_NullExifData_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("250");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "-25.0");
}

// Test that the function returns the same ostream reference
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_ReturnsOstream_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("50");
  std::ostream& result = maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test with value 15 - should produce -1.5
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_FractionalResult_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("15");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "-1.5");
}

// Test with value 999 - should produce -99.9
TEST_F(PanasonicMakerNoteTest_717, PrintPitchAngle_LargerValue_717) {
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
  value->read("999");
  maker_.printPitchAngle(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "-99.9");
}
