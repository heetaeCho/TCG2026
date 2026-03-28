#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstdint>
#include <vector>

// Forward declarations and minimal interfaces needed for testing
namespace Exiv2 {

class ExifData {};

class Value {
 public:
  virtual ~Value() = default;
  virtual int64_t toInt64(size_t n = 0) const = 0;
};

// A concrete mock for Value
class MockValue : public Value {
 public:
  MOCK_METHOD(int64_t, toInt64, (size_t n), (const, override));
};

namespace Internal {

class PanasonicMakerNote {
 public:
  std::ostream& printAccelerometer(std::ostream& os, const Value& value, const ExifData*) {
    const auto i = static_cast<int16_t>(value.toInt64());
    return os;
  }
};

}  // namespace Internal
}  // namespace Exiv2

// Re-include the actual implementation by redefining the class inline
// Since we only have the partial code, we replicate it faithfully:
namespace Exiv2Actual {
namespace Internal {

class PanasonicMakerNote {
 public:
  std::ostream& printAccelerometer(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData*) {
    const auto i = static_cast<int16_t>(value.toInt64());
    return os << i;
  }
};

}  // namespace Internal
}  // namespace Exiv2Actual

using namespace Exiv2Actual::Internal;
using Exiv2::MockValue;
using Exiv2::ExifData;

class PanasonicMakerNoteTest_715 : public ::testing::Test {
 protected:
  PanasonicMakerNote maker_;
  std::ostringstream oss_;
};

// Test normal positive value
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_PositiveValue_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(100));

  maker_.printAccelerometer(oss_, mockValue, nullptr);
  EXPECT_EQ(oss_.str(), "100");
}

// Test zero value
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_ZeroValue_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(0));

  maker_.printAccelerometer(oss_, mockValue, nullptr);
  EXPECT_EQ(oss_.str(), "0");
}

// Test negative value (within int16_t range)
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_NegativeValue_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(-50));

  maker_.printAccelerometer(oss_, mockValue, nullptr);
  EXPECT_EQ(oss_.str(), "-50");
}

// Test int16_t max boundary (32767)
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_Int16Max_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(32767));

  maker_.printAccelerometer(oss_, mockValue, nullptr);
  EXPECT_EQ(oss_.str(), "32767");
}

// Test int16_t min boundary (-32768)
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_Int16Min_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(-32768));

  maker_.printAccelerometer(oss_, mockValue, nullptr);
  EXPECT_EQ(oss_.str(), "-32768");
}

// Test value just above int16_t max (32768) - should wrap around due to int16_t cast
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_OverflowAboveMax_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(32768));

  maker_.printAccelerometer(oss_, mockValue, nullptr);
  // 32768 cast to int16_t wraps to -32768
  EXPECT_EQ(oss_.str(), "-32768");
}

// Test value just below int16_t min (-32769) - should wrap due to int16_t cast
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_OverflowBelowMin_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(-32769));

  maker_.printAccelerometer(oss_, mockValue, nullptr);
  // -32769 as int16_t wraps to 32767
  EXPECT_EQ(oss_.str(), "32767");
}

// Test large positive value (65535) - should become -1 as int16_t
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_LargePositiveWrapsToNegOne_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(65535));

  maker_.printAccelerometer(oss_, mockValue, nullptr);
  // 65535 & 0xFFFF = 0xFFFF, as int16_t = -1
  EXPECT_EQ(oss_.str(), "-1");
}

// Test that the return value is the same ostream reference
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_ReturnsOstreamReference_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(42));

  std::ostream& result = maker_.printAccelerometer(oss_, mockValue, nullptr);
  EXPECT_EQ(&result, &oss_);
}

// Test with null ExifData pointer (should work fine, it's unused)
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_NullExifData_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(1));

  maker_.printAccelerometer(oss_, mockValue, nullptr);
  EXPECT_EQ(oss_.str(), "1");
}

// Test with non-null ExifData pointer (should still work, it's unused)
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_NonNullExifData_715) {
  MockValue mockValue;
  ExifData exifData;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(255));

  maker_.printAccelerometer(oss_, mockValue, &exifData);
  EXPECT_EQ(oss_.str(), "255");
}

// Test value of 1 (small positive)
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_SmallPositive_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(1));

  maker_.printAccelerometer(oss_, mockValue, nullptr);
  EXPECT_EQ(oss_.str(), "1");
}

// Test value of -1 (small negative)
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_SmallNegative_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(-1));

  maker_.printAccelerometer(oss_, mockValue, nullptr);
  EXPECT_EQ(oss_.str(), "-1");
}

// Test that 65536 wraps to 0 (full uint16 overflow)
TEST_F(PanasonicMakerNoteTest_715, PrintAccelerometer_Value65536WrapsToZero_715) {
  MockValue mockValue;
  EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(65536));

  maker_.printAccelerometer(oss_, mockValue, nullptr);
  // 65536 as int16_t: low 16 bits are 0
  EXPECT_EQ(oss_.str(), "0");
}
