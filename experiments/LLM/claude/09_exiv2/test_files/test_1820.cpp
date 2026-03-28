#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

namespace Exiv2 {
namespace Internal {

class CasioMakerNote {
 public:
  std::ostream& print0x0006(std::ostream& os, const Value& value, const ExifData*) {
    return os << stringFormat("{:.2f} m", value.toInt64() / 1000.0);
  }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class CasioMakerNoteTest_1820 : public ::testing::Test {
 protected:
  CasioMakerNote maker_;
  std::ostringstream oss_;
};

// Test normal value - typical distance in millimeters
TEST_F(CasioMakerNoteTest_1820, Print0x0006_NormalValue_1820) {
  ULongValue value;
  value.read("1500");  // 1500 mm = 1.50 m
  maker_.print0x0006(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "1.50 m");
}

// Test zero value
TEST_F(CasioMakerNoteTest_1820, Print0x0006_ZeroValue_1820) {
  ULongValue value;
  value.read("0");  // 0 mm = 0.00 m
  maker_.print0x0006(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "0.00 m");
}

// Test value of exactly 1000 (1.00 m)
TEST_F(CasioMakerNoteTest_1820, Print0x0006_ExactlyOneThousand_1820) {
  ULongValue value;
  value.read("1000");  // 1000 mm = 1.00 m
  maker_.print0x0006(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "1.00 m");
}

// Test small value resulting in fractional meters
TEST_F(CasioMakerNoteTest_1820, Print0x0006_SmallValue_1820) {
  ULongValue value;
  value.read("1");  // 1 mm = 0.00 m (rounded to 2 decimal places)
  maker_.print0x0006(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "0.00 m");
}

// Test large value
TEST_F(CasioMakerNoteTest_1820, Print0x0006_LargeValue_1820) {
  ULongValue value;
  value.read("100000");  // 100000 mm = 100.00 m
  maker_.print0x0006(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "100.00 m");
}

// Test value with non-zero fractional result
TEST_F(CasioMakerNoteTest_1820, Print0x0006_FractionalResult_1820) {
  ULongValue value;
  value.read("1234");  // 1234 mm = 1.23 m
  maker_.print0x0006(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "1.23 m");
}

// Test value that rounds to two decimal places
TEST_F(CasioMakerNoteTest_1820, Print0x0006_RoundingValue_1820) {
  ULongValue value;
  value.read("1235");  // 1235 mm = 1.24 m (rounding)
  maker_.print0x0006(oss_, value, nullptr);
  // 1235 / 1000.0 = 1.235, with .2f formatting should be 1.24 or 1.23 depending on rounding
  std::string result = oss_.str();
  EXPECT_TRUE(result == "1.24 m" || result == "1.23 m");
}

// Test with nullptr ExifData (should not crash)
TEST_F(CasioMakerNoteTest_1820, Print0x0006_NullExifData_1820) {
  ULongValue value;
  value.read("5000");
  EXPECT_NO_THROW(maker_.print0x0006(oss_, value, nullptr));
  EXPECT_EQ(oss_.str(), "5.00 m");
}

// Test that the function returns the ostream reference
TEST_F(CasioMakerNoteTest_1820, Print0x0006_ReturnsOstream_1820) {
  ULongValue value;
  value.read("2000");
  std::ostream& result = maker_.print0x0006(oss_, value, nullptr);
  EXPECT_EQ(&result, &oss_);
}

// Test value 500 (0.50 m)
TEST_F(CasioMakerNoteTest_1820, Print0x0006_HalfMeter_1820) {
  ULongValue value;
  value.read("500");
  maker_.print0x0006(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "0.50 m");
}

// Test value 10 (0.01 m)
TEST_F(CasioMakerNoteTest_1820, Print0x0006_TenMillimeters_1820) {
  ULongValue value;
  value.read("10");
  maker_.print0x0006(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "0.01 m");
}

// Test value 999 (0.99 or 1.00 depending on rounding)
TEST_F(CasioMakerNoteTest_1820, Print0x0006_JustUnderOneMeter_1820) {
  ULongValue value;
  value.read("999");  // 999 / 1000 = 0.999 -> 1.00 m
  maker_.print0x0006(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "1.00 m");
}
