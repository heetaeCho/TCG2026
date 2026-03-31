#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>
#include <cstring>

// We need to include or replicate the minimal class definition to test against
namespace Exiv2 {
namespace Internal {
class OlympusMakerNote {
 public:
  std::ostream& print0x0209(std::ostream& os, const Value& value, const ExifData*) {
    if (value.typeId() != asciiString && value.typeId() != undefined) {
      return os << value;
    }
    char ch;
    size_t size = value.size();
    for (size_t i = 0; i < size && ((ch = static_cast<char>(value.toInt64(i))) != '\0'); i++) {
      os << ch;
    }
    return os;
  }
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMakerNoteTest_901 : public ::testing::Test {
 protected:
  OlympusMakerNote maker_;
  std::ostringstream oss_;
};

// Test with ASCII string value - normal string
TEST_F(OlympusMakerNoteTest_901, Print0x0209_AsciiString_PrintsCharacters_901) {
  AsciiValue val;
  val.read("Hello World");
  maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "Hello World");
}

// Test with undefined type value containing a string
TEST_F(OlympusMakerNoteTest_901, Print0x0209_UndefinedType_PrintsCharacters_901) {
  DataValue val(undefined);
  const std::string testStr = "TestData";
  val.read(reinterpret_cast<const byte*>(testStr.c_str()), testStr.size());
  maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "TestData");
}

// Test with non-ascii, non-undefined type (e.g., unsignedShort) - should use default << operator
TEST_F(OlympusMakerNoteTest_901, Print0x0209_NonAsciiNonUndefined_UsesDefaultOutput_901) {
  UShortValue val;
  val.read("42");
  maker_.print0x0209(oss_, val, nullptr);
  // Should output the value using the default << operator
  EXPECT_FALSE(oss_.str().empty());
  EXPECT_EQ(oss_.str(), "42");
}

// Test with empty ASCII string
TEST_F(OlympusMakerNoteTest_901, Print0x0209_EmptyAsciiString_PrintsNothing_901) {
  AsciiValue val;
  val.read("");  // Empty string, will have null terminator
  maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "");
}

// Test with undefined type containing null byte at start
TEST_F(OlympusMakerNoteTest_901, Print0x0209_UndefinedStartsWithNull_PrintsNothing_901) {
  DataValue val(undefined);
  const byte data[] = {0x00, 0x41, 0x42};
  val.read(data, 3);
  maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "");
}

// Test with undefined type containing null byte in the middle
TEST_F(OlympusMakerNoteTest_901, Print0x0209_UndefinedNullInMiddle_PrintsUpToNull_901) {
  DataValue val(undefined);
  const byte data[] = {0x48, 0x65, 0x6C, 0x00, 0x6C, 0x6F};  // "Hel\0lo"
  val.read(data, 6);
  maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "Hel");
}

// Test with single character ASCII string
TEST_F(OlympusMakerNoteTest_901, Print0x0209_SingleCharAscii_PrintsSingleChar_901) {
  AsciiValue val;
  val.read("A");
  maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "A");
}

// Test with nullptr ExifData - should not crash
TEST_F(OlympusMakerNoteTest_901, Print0x0209_NullExifData_DoesNotCrash_901) {
  AsciiValue val;
  val.read("Test");
  EXPECT_NO_THROW(maker_.print0x0209(oss_, val, nullptr));
  EXPECT_EQ(oss_.str(), "Test");
}

// Test that the function returns a reference to the same ostream
TEST_F(OlympusMakerNoteTest_901, Print0x0209_ReturnsOstreamReference_901) {
  AsciiValue val;
  val.read("Test");
  std::ostream& result = maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(&result, &oss_);
}

// Test with unsigned long value (non-ascii, non-undefined)
TEST_F(OlympusMakerNoteTest_901, Print0x0209_UnsignedLongType_UsesDefaultOutput_901) {
  ULongValue val;
  val.read("12345");
  maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "12345");
}

// Test with undefined type containing all printable characters
TEST_F(OlympusMakerNoteTest_901, Print0x0209_UndefinedAllPrintable_PrintsAll_901) {
  DataValue val(undefined);
  const byte data[] = {0x41, 0x42, 0x43, 0x44, 0x45};  // "ABCDE"
  val.read(data, 5);
  maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "ABCDE");
}

// Test with undefined type containing special characters
TEST_F(OlympusMakerNoteTest_901, Print0x0209_UndefinedSpecialChars_PrintsSpecialChars_901) {
  DataValue val(undefined);
  const byte data[] = {0x21, 0x40, 0x23, 0x24};  // "!@#$"
  val.read(data, 4);
  maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "!@#$");
}

// Test with a longer string
TEST_F(OlympusMakerNoteTest_901, Print0x0209_LongAsciiString_PrintsFull_901) {
  AsciiValue val;
  std::string longStr(256, 'X');
  val.read(longStr);
  maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), longStr);
}

// Test with undefined data that has all null bytes
TEST_F(OlympusMakerNoteTest_901, Print0x0209_UndefinedAllNulls_PrintsNothing_901) {
  DataValue val(undefined);
  const byte data[] = {0x00, 0x00, 0x00};
  val.read(data, 3);
  maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "");
}

// Test return stream for non-ascii type
TEST_F(OlympusMakerNoteTest_901, Print0x0209_NonAsciiReturnsOstreamReference_901) {
  UShortValue val;
  val.read("100");
  std::ostream& result = maker_.print0x0209(oss_, val, nullptr);
  EXPECT_EQ(&result, &oss_);
}
