#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstdint>

// We need to include or replicate the minimal interface dependencies
// Since we're testing against the provided interface, we need Exiv2's Value and ExifData types

// Minimal mock/stub for the Value interface
namespace Exiv2 {

class ExifData {};

class Value {
 public:
  virtual ~Value() = default;
  virtual int64_t toInt64(size_t n = 0) const = 0;
};

// A concrete Value implementation for testing purposes
class TestValue : public Value {
 public:
  explicit TestValue(int64_t val) : val_(val) {}
  int64_t toInt64(size_t /*n*/ = 0) const override { return val_; }
 private:
  int64_t val_;
};

namespace Internal {

class MinoltaMakerNote {
 public:
  std::ostream& printMinoltaWhiteBalanceStd(std::ostream& os, const Value& value, const ExifData*) {
    os << value.toInt64() / 256;
    return os;
  }
};

}  // namespace Internal
}  // namespace Exiv2

// Test fixture
class MinoltaMakerNoteTest_1008 : public ::testing::Test {
 protected:
  Exiv2::Internal::MinoltaMakerNote makerNote_;
};

// Test normal operation: a typical value that divides evenly by 256
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_NormalValue_1008) {
  Exiv2::TestValue value(512);
  std::ostringstream os;
  auto& result = makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_EQ(os.str(), "2");
  EXPECT_EQ(&result, &os);  // Verify it returns the same stream reference
}

// Test with value 256 -> should output 1
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_Value256_1008) {
  Exiv2::TestValue value(256);
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_EQ(os.str(), "1");
}

// Test boundary: value of 0 -> should output 0
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_ZeroValue_1008) {
  Exiv2::TestValue value(0);
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_EQ(os.str(), "0");
}

// Test boundary: value less than 256 -> integer division should truncate to 0
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_ValueLessThan256_1008) {
  Exiv2::TestValue value(255);
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_EQ(os.str(), "0");
}

// Test with value 1 -> should output 0
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_ValueOne_1008) {
  Exiv2::TestValue value(1);
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_EQ(os.str(), "0");
}

// Test negative value -> integer division behavior
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_NegativeValue_1008) {
  Exiv2::TestValue value(-256);
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_EQ(os.str(), "-1");
}

// Test negative value that doesn't divide evenly
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_NegativeNonEvenValue_1008) {
  Exiv2::TestValue value(-255);
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_EQ(os.str(), "0");  // -255 / 256 = 0 in integer division (truncation toward zero)
}

// Test negative value -512 -> should output -2
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_NegativeValue512_1008) {
  Exiv2::TestValue value(-512);
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_EQ(os.str(), "-2");
}

// Test large value
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_LargeValue_1008) {
  Exiv2::TestValue value(65536);  // 256 * 256
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_EQ(os.str(), "256");
}

// Test with non-null ExifData pointer (should be ignored, but function should still work)
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_WithExifData_1008) {
  Exiv2::ExifData exifData;
  Exiv2::TestValue value(1024);
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value, &exifData);
  EXPECT_EQ(os.str(), "4");
}

// Test that the function returns the same ostream reference
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_ReturnsStreamReference_1008) {
  Exiv2::TestValue value(768);
  std::ostringstream os;
  std::ostream& returned = makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_EQ(&returned, &os);
  EXPECT_EQ(os.str(), "3");
}

// Test value that doesn't divide evenly (truncation check)
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_TruncationValue_1008) {
  Exiv2::TestValue value(300);  // 300 / 256 = 1 (integer division)
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_EQ(os.str(), "1");
}

// Test consecutive calls append to the stream
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_ConsecutiveCalls_1008) {
  Exiv2::TestValue value1(256);
  Exiv2::TestValue value2(512);
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value1, nullptr);
  makerNote_.printMinoltaWhiteBalanceStd(os, value2, nullptr);
  EXPECT_EQ(os.str(), "12");
}

// Test very large int64 value
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_VeryLargeValue_1008) {
  Exiv2::TestValue value(INT64_MAX);
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  int64_t expected = INT64_MAX / 256;
  EXPECT_EQ(os.str(), std::to_string(expected));
}

// Test minimum int64 value
TEST_F(MinoltaMakerNoteTest_1008, WhiteBalanceStd_MinInt64Value_1008) {
  Exiv2::TestValue value(INT64_MIN);
  std::ostringstream os;
  makerNote_.printMinoltaWhiteBalanceStd(os, value, nullptr);
  int64_t expected = INT64_MIN / 256;
  EXPECT_EQ(os.str(), std::to_string(expected));
}
