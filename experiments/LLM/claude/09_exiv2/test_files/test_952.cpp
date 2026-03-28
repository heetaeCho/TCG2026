#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include <exiv2/value.hpp>

// We need to access the internal function, so we include the relevant headers
// and recreate the class interface as provided.

namespace Exiv2 {
namespace Internal {

class CanonMakerNote {
 public:
  std::ostream& printLe0x0000(std::ostream& os, const Value& value, const ExifData*) {
    if (value.typeId() != unsignedByte || value.size() != 5)
      return os << "(" << value << ")";
    for (size_t i = 0; i < value.size(); ++i) {
      os << stringFormat("{:02x}", value.toInt64(i));
    }
    return os;
  }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_952 : public ::testing::Test {
 protected:
  CanonMakerNote maker_;
  std::ostringstream os_;
};

// Test normal operation: unsignedByte type with exactly 5 bytes
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_NormalFiveBytes_952) {
  auto value = Value::create(unsignedByte);
  // Set 5 bytes: e.g., 0x01, 0x02, 0x0A, 0xFF, 0x00
  byte data[] = {0x01, 0x02, 0x0A, 0xFF, 0x00};
  value->read(data, 5, littleEndian);

  maker_.printLe0x0000(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result, "01020aff00");
}

// Test normal operation: all zeros
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_AllZeroBytes_952) {
  auto value = Value::create(unsignedByte);
  byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00};
  value->read(data, 5, littleEndian);

  maker_.printLe0x0000(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result, "0000000000");
}

// Test normal operation: all 0xFF bytes
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_AllFFBytes_952) {
  auto value = Value::create(unsignedByte);
  byte data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  value->read(data, 5, littleEndian);

  maker_.printLe0x0000(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result, "ffffffffff");
}

// Test boundary: wrong size (4 bytes instead of 5) should fallback to parenthesized output
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_FourBytesReturnsParenthesized_952) {
  auto value = Value::create(unsignedByte);
  byte data[] = {0x01, 0x02, 0x03, 0x04};
  value->read(data, 4, littleEndian);

  maker_.printLe0x0000(os_, *value, nullptr);

  std::string result = os_.str();
  // Should be wrapped in parentheses
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test boundary: wrong size (6 bytes instead of 5) should fallback to parenthesized output
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_SixBytesReturnsParenthesized_952) {
  auto value = Value::create(unsignedByte);
  byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  value->read(data, 6, littleEndian);

  maker_.printLe0x0000(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test boundary: empty value (0 bytes) should fallback to parenthesized output
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_EmptyValueReturnsParenthesized_952) {
  auto value = Value::create(unsignedByte);
  // Don't read any data, size should be 0

  maker_.printLe0x0000(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test error case: wrong type (unsignedShort with right number of elements? Still wrong typeId)
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_WrongTypeReturnsParenthesized_952) {
  auto value = Value::create(unsignedShort);
  // Read some short values
  byte data[] = {0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x05, 0x00};
  value->read(data, 10, littleEndian);

  maker_.printLe0x0000(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test error case: unsignedLong type should fallback
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_UnsignedLongTypeReturnsParenthesized_952) {
  auto value = Value::create(unsignedLong);
  byte data[] = {0x01, 0x00, 0x00, 0x00};
  value->read(data, 4, littleEndian);

  maker_.printLe0x0000(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test that nullptr ExifData* doesn't cause issues
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_NullExifDataPtr_952) {
  auto value = Value::create(unsignedByte);
  byte data[] = {0xAB, 0xCD, 0xEF, 0x12, 0x34};
  value->read(data, 5, littleEndian);

  // Should not crash with nullptr ExifData
  maker_.printLe0x0000(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result, "abcdef1234");
}

// Test with valid ExifData pointer (non-null) - should still work the same
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_NonNullExifDataPtr_952) {
  auto value = Value::create(unsignedByte);
  byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
  value->read(data, 5, littleEndian);

  ExifData exifData;
  maker_.printLe0x0000(os_, *value, &exifData);

  std::string result = os_.str();
  EXPECT_EQ(result, "1020304050");
}

// Test that the function returns the ostream reference (chaining)
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_ReturnsOstreamReference_952) {
  auto value = Value::create(unsignedByte);
  byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  value->read(data, 5, littleEndian);

  std::ostream& returned = maker_.printLe0x0000(os_, *value, nullptr);

  EXPECT_EQ(&returned, &os_);
}

// Test boundary: single byte (size != 5)
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_SingleByteReturnsParenthesized_952) {
  auto value = Value::create(unsignedByte);
  byte data[] = {0xAA};
  value->read(data, 1, littleEndian);

  maker_.printLe0x0000(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test hex formatting: values that need leading zeros
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_LeadingZerosInHex_952) {
  auto value = Value::create(unsignedByte);
  byte data[] = {0x00, 0x01, 0x0F, 0x10, 0x09};
  value->read(data, 5, littleEndian);

  maker_.printLe0x0000(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result, "00010f1009");
}

// Test with ascii type (wrong type, should fallback)
TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_AsciiTypeReturnsParenthesized_952) {
  auto value = Value::create(asciiString);
  value->read("hello");

  maker_.printLe0x0000(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}
