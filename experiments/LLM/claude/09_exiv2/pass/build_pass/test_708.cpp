#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the necessary headers for the class under test
// We need to access PanasonicMakerNote from Internal namespace
namespace Exiv2 {
namespace Internal {
class PanasonicMakerNote {
 public:
  std::ostream& print0x0023(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class PanasonicMakerNoteTest_708 : public ::testing::Test {
 protected:
  PanasonicMakerNote maker_;
  std::ostringstream os_;
};

// Test normal positive value that divides evenly by 3
TEST_F(PanasonicMakerNoteTest_708, Print0x0023_PositiveValueDivisibleBy3_708) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.read("9");
  maker_.print0x0023(os_, value, nullptr);
  std::string result = os_.str();
  // 9/3 = 3, so expect "3 EV"
  EXPECT_TRUE(result.find("3") != std::string::npos);
  EXPECT_TRUE(result.find("EV") != std::string::npos);
}

// Test value of zero
TEST_F(PanasonicMakerNoteTest_708, Print0x0023_ZeroValue_708) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.read("0");
  maker_.print0x0023(os_, value, nullptr);
  std::string result = os_.str();
  // 0/3 = 0, so expect "0 EV"
  EXPECT_TRUE(result.find("0") != std::string::npos);
  EXPECT_TRUE(result.find("EV") != std::string::npos);
}

// Test negative value
TEST_F(PanasonicMakerNoteTest_708, Print0x0023_NegativeValue_708) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.read("-6");
  maker_.print0x0023(os_, value, nullptr);
  std::string result = os_.str();
  // -6/3 = -2, so expect "-2 EV"
  EXPECT_TRUE(result.find("-2") != std::string::npos);
  EXPECT_TRUE(result.find("EV") != std::string::npos);
}

// Test value not divisible by 3 (integer division truncates)
TEST_F(PanasonicMakerNoteTest_708, Print0x0023_ValueNotDivisibleBy3_708) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.read("7");
  maker_.print0x0023(os_, value, nullptr);
  std::string result = os_.str();
  // 7/3 = 2 (integer division), so expect "2 EV"
  EXPECT_TRUE(result.find("2") != std::string::npos);
  EXPECT_TRUE(result.find("EV") != std::string::npos);
}

// Test value of 3 (1 EV)
TEST_F(PanasonicMakerNoteTest_708, Print0x0023_ValueThree_708) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.read("3");
  maker_.print0x0023(os_, value, nullptr);
  std::string result = os_.str();
  // 3/3 = 1, so expect "1 EV"
  EXPECT_TRUE(result.find("1") != std::string::npos);
  EXPECT_TRUE(result.find("EV") != std::string::npos);
}

// Test that the function returns the same ostream reference
TEST_F(PanasonicMakerNoteTest_708, Print0x0023_ReturnsOstream_708) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.read("6");
  std::ostream& result = maker_.print0x0023(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test with nullptr ExifData (should not crash)
TEST_F(PanasonicMakerNoteTest_708, Print0x0023_NullExifData_708) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.read("12");
  EXPECT_NO_THROW(maker_.print0x0023(os_, value, nullptr));
  std::string result = os_.str();
  // 12/3 = 4
  EXPECT_TRUE(result.find("4") != std::string::npos);
  EXPECT_TRUE(result.find("EV") != std::string::npos);
}

// Test small positive value (1) - integer division should give 0
TEST_F(PanasonicMakerNoteTest_708, Print0x0023_SmallPositiveValue_708) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.read("1");
  maker_.print0x0023(os_, value, nullptr);
  std::string result = os_.str();
  // 1/3 = 0
  EXPECT_TRUE(result.find("0") != std::string::npos);
  EXPECT_TRUE(result.find("EV") != std::string::npos);
}

// Test small negative value (-1) - integer division behavior
TEST_F(PanasonicMakerNoteTest_708, Print0x0023_SmallNegativeValue_708) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.read("-1");
  maker_.print0x0023(os_, value, nullptr);
  std::string result = os_.str();
  // -1/3 = 0 (truncation toward zero)
  EXPECT_TRUE(result.find("EV") != std::string::npos);
}

// Test large positive value
TEST_F(PanasonicMakerNoteTest_708, Print0x0023_LargePositiveValue_708) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.read("300");
  maker_.print0x0023(os_, value, nullptr);
  std::string result = os_.str();
  // 300/3 = 100
  EXPECT_TRUE(result.find("100") != std::string::npos);
  EXPECT_TRUE(result.find("EV") != std::string::npos);
}

// Test large negative value
TEST_F(PanasonicMakerNoteTest_708, Print0x0023_LargeNegativeValue_708) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.read("-300");
  maker_.print0x0023(os_, value, nullptr);
  std::string result = os_.str();
  // -300/3 = -100
  EXPECT_TRUE(result.find("-100") != std::string::npos);
  EXPECT_TRUE(result.find("EV") != std::string::npos);
}
