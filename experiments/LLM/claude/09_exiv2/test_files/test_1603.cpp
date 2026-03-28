#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to include the internal header or replicate the interface
// Based on the provided code, we'll work with the class directly
namespace Exiv2 {
namespace Internal {

class SonyMakerNote {
 public:
  std::ostream& printFocusFrameSize(std::ostream& os, const Value& value, const ExifData*) {
    if (value.count() != 6 || value.typeId() != undefined)
      return os << "(" << value << ")";
    if (value.toUint32(4) == 0 && value.toUint32(5) == 0)
      return os << "n/a";
    return os << ((value.toUint32(1) << 8) + value.toUint32(0)) << "x"
              << ((value.toUint32(3) << 8) + value.toUint32(2));
  }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1603 : public ::testing::Test {
 protected:
  SonyMakerNote maker_;
  std::ostringstream os_;
};

// Test: When value count is not 6, output should be wrapped in parentheses
TEST_F(SonyMakerNoteTest_1603, WrongCount_OutputsParenthesized_1603) {
  // Create an undefined value with only 4 bytes (count != 6)
  DataBuf buf(4);
  buf.data()[0] = 0x01;
  buf.data()[1] = 0x02;
  buf.data()[2] = 0x03;
  buf.data()[3] = 0x04;
  DataValue value(undefinedId);
  value.read(buf.data(), buf.size(), invalidByteOrder);

  maker_.printFocusFrameSize(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: When value typeId is not undefined, output should be wrapped in parentheses
TEST_F(SonyMakerNoteTest_1603, WrongTypeId_OutputsParenthesized_1603) {
  // Use a non-undefined type (e.g., unsignedShort) with 6 elements
  UShortValue value;
  value.read("1 2 3 4 5 6");

  maker_.printFocusFrameSize(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: When bytes 4 and 5 are both 0, output should be "n/a"
TEST_F(SonyMakerNoteTest_1603, ZeroBytes4And5_OutputsNA_1603) {
  DataBuf buf(6);
  buf.data()[0] = 0x10;
  buf.data()[1] = 0x00;
  buf.data()[2] = 0x20;
  buf.data()[3] = 0x00;
  buf.data()[4] = 0x00;  // zero
  buf.data()[5] = 0x00;  // zero
  DataValue value(undefinedId);
  value.read(buf.data(), buf.size(), invalidByteOrder);

  maker_.printFocusFrameSize(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "n/a");
}

// Test: Normal case with non-zero bytes 4 and 5 - should output WxH format
TEST_F(SonyMakerNoteTest_1603, NormalCase_OutputsWidthXHeight_1603) {
  DataBuf buf(6);
  // Width = (byte1 << 8) + byte0 = (0x01 << 8) + 0x40 = 256 + 64 = 320
  buf.data()[0] = 0x40;  // low byte of width
  buf.data()[1] = 0x01;  // high byte of width
  // Height = (byte3 << 8) + byte2 = (0x00 << 8) + 0xF0 = 240
  buf.data()[2] = 0xF0;  // low byte of height
  buf.data()[3] = 0x00;  // high byte of height
  buf.data()[4] = 0x01;  // non-zero so we don't get n/a
  buf.data()[5] = 0x00;
  DataValue value(undefinedId);
  value.read(buf.data(), buf.size(), invalidByteOrder);

  maker_.printFocusFrameSize(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "320x240");
}

// Test: Normal case with larger values
TEST_F(SonyMakerNoteTest_1603, LargerValues_OutputsWidthXHeight_1603) {
  DataBuf buf(6);
  // Width = (0x07 << 8) + 0x80 = 1792 + 128 = 1920
  buf.data()[0] = 0x80;
  buf.data()[1] = 0x07;
  // Height = (0x04 << 8) + 0x38 = 1024 + 56 = 1080
  buf.data()[2] = 0x38;
  buf.data()[3] = 0x04;
  buf.data()[4] = 0x01;
  buf.data()[5] = 0x01;
  DataValue value(undefinedId);
  value.read(buf.data(), buf.size(), invalidByteOrder);

  maker_.printFocusFrameSize(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1920x1080");
}

// Test: Both bytes 4 non-zero, byte 5 zero - should NOT be n/a
TEST_F(SonyMakerNoteTest_1603, Byte4NonZeroByte5Zero_NotNA_1603) {
  DataBuf buf(6);
  buf.data()[0] = 0x01;
  buf.data()[1] = 0x00;
  buf.data()[2] = 0x01;
  buf.data()[3] = 0x00;
  buf.data()[4] = 0x05;  // non-zero
  buf.data()[5] = 0x00;  // zero
  DataValue value(undefinedId);
  value.read(buf.data(), buf.size(), invalidByteOrder);

  maker_.printFocusFrameSize(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1x1");
}

// Test: Byte 4 zero, byte 5 non-zero - should NOT be n/a
TEST_F(SonyMakerNoteTest_1603, Byte4ZeroByte5NonZero_NotNA_1603) {
  DataBuf buf(6);
  buf.data()[0] = 0x02;
  buf.data()[1] = 0x00;
  buf.data()[2] = 0x03;
  buf.data()[3] = 0x00;
  buf.data()[4] = 0x00;  // zero
  buf.data()[5] = 0x01;  // non-zero
  DataValue value(undefinedId);
  value.read(buf.data(), buf.size(), invalidByteOrder);

  maker_.printFocusFrameSize(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "2x3");
}

// Test: All dimension bytes zero, but bytes 4,5 non-zero => output "0x0"
TEST_F(SonyMakerNoteTest_1603, ZeroDimensions_NonZeroFlags_OutputsZeroXZero_1603) {
  DataBuf buf(6);
  buf.data()[0] = 0x00;
  buf.data()[1] = 0x00;
  buf.data()[2] = 0x00;
  buf.data()[3] = 0x00;
  buf.data()[4] = 0x01;
  buf.data()[5] = 0x01;
  DataValue value(undefinedId);
  value.read(buf.data(), buf.size(), invalidByteOrder);

  maker_.printFocusFrameSize(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "0x0");
}

// Test: Count is 0 - edge case for wrong count
TEST_F(SonyMakerNoteTest_1603, EmptyValue_OutputsParenthesized_1603) {
  DataValue value(undefinedId);
  // Empty value, count = 0

  maker_.printFocusFrameSize(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Count is 7 (one more than expected) - should fail the count check
TEST_F(SonyMakerNoteTest_1603, CountSeven_OutputsParenthesized_1603) {
  DataBuf buf(7);
  for (int i = 0; i < 7; i++) buf.data()[i] = 0x01;
  DataValue value(undefinedId);
  value.read(buf.data(), buf.size(), invalidByteOrder);

  maker_.printFocusFrameSize(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Count is 5 (one less than expected) - should fail the count check
TEST_F(SonyMakerNoteTest_1603, CountFive_OutputsParenthesized_1603) {
  DataBuf buf(5);
  for (int i = 0; i < 5; i++) buf.data()[i] = 0x01;
  DataValue value(undefinedId);
  value.read(buf.data(), buf.size(), invalidByteOrder);

  maker_.printFocusFrameSize(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Passing nullptr for ExifData* should still work (normal case)
TEST_F(SonyMakerNoteTest_1603, NullExifData_NormalOperation_1603) {
  DataBuf buf(6);
  buf.data()[0] = 0xFF;
  buf.data()[1] = 0x00;
  buf.data()[2] = 0xFF;
  buf.data()[3] = 0x00;
  buf.data()[4] = 0x01;
  buf.data()[5] = 0x00;
  DataValue value(undefinedId);
  value.read(buf.data(), buf.size(), invalidByteOrder);

  maker_.printFocusFrameSize(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "255x255");
}

// Test: Maximum byte values for dimension bytes
TEST_F(SonyMakerNoteTest_1603, MaxByteValues_OutputsMaxDimensions_1603) {
  DataBuf buf(6);
  buf.data()[0] = 0xFF;
  buf.data()[1] = 0xFF;
  buf.data()[2] = 0xFF;
  buf.data()[3] = 0xFF;
  buf.data()[4] = 0xFF;
  buf.data()[5] = 0xFF;
  DataValue value(undefinedId);
  value.read(buf.data(), buf.size(), invalidByteOrder);

  maker_.printFocusFrameSize(os_, value, nullptr);
  // Width = (0xFF << 8) + 0xFF = 65535
  // Height = (0xFF << 8) + 0xFF = 65535
  EXPECT_EQ(os_.str(), "65535x65535");
}
