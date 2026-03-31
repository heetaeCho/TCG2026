#include <gtest/gtest.h>
#include <sstream>
#include <string>

// We need Exiv2 headers for Value and ExifData types
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the internal header or declare the class as shown in the partial code
namespace Exiv2 {
namespace Internal {
class CanonMakerNote {
 public:
  std::ostream& print0x0008(std::ostream& os, const Value& value, const ExifData*) {
    std::string n = value.toString();
    if (n.length() < 4)
      return os << "(" << n << ")";
    return os << n.substr(0, n.length() - 4) << "-" << n.substr(n.length() - 4);
  }
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_943 : public ::testing::Test {
 protected:
  CanonMakerNote maker_;
  std::ostringstream os_;
};

// Test: Empty string value (length < 4) should be wrapped in parentheses
TEST_F(CanonMakerNoteTest_943, Print0x0008_EmptyString_943) {
  AsciiValue val;
  val.read("");
  maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "()");
}

// Test: Single character string (length < 4) should be wrapped in parentheses
TEST_F(CanonMakerNoteTest_943, Print0x0008_SingleChar_943) {
  AsciiValue val;
  val.read("A");
  maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "(A)");
}

// Test: Two character string (length < 4) should be wrapped in parentheses
TEST_F(CanonMakerNoteTest_943, Print0x0008_TwoChars_943) {
  AsciiValue val;
  val.read("AB");
  maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "(AB)");
}

// Test: Three character string (length < 4) should be wrapped in parentheses
TEST_F(CanonMakerNoteTest_943, Print0x0008_ThreeChars_943) {
  AsciiValue val;
  val.read("123");
  maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "(123)");
}

// Test: Exactly 4 characters - should split as prefix-suffix with empty prefix portion
TEST_F(CanonMakerNoteTest_943, Print0x0008_ExactlyFourChars_943) {
  AsciiValue val;
  val.read("1234");
  maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "-1234");
}

// Test: Five characters - should split as 1 char prefix and 4 char suffix
TEST_F(CanonMakerNoteTest_943, Print0x0008_FiveChars_943) {
  AsciiValue val;
  val.read("12345");
  maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "1-2345");
}

// Test: Typical serial number-like string (8 digits)
TEST_F(CanonMakerNoteTest_943, Print0x0008_EightDigits_943) {
  AsciiValue val;
  val.read("12345678");
  maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "1234-5678");
}

// Test: Longer string with 10 characters
TEST_F(CanonMakerNoteTest_943, Print0x0008_TenChars_943) {
  AsciiValue val;
  val.read("0123456789");
  maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "012345-6789");
}

// Test: Passing nullptr for ExifData should not cause issues
TEST_F(CanonMakerNoteTest_943, Print0x0008_NullExifData_943) {
  AsciiValue val;
  val.read("ABCD1234");
  maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "ABCD-1234");
}

// Test: String with spaces
TEST_F(CanonMakerNoteTest_943, Print0x0008_StringWithSpaces_943) {
  AsciiValue val;
  val.read("AB CD EF");
  maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "AB C-D EF");
}

// Test: Numeric value using a UShortValue (toString gives numeric string)
TEST_F(CanonMakerNoteTest_943, Print0x0008_NumericUShortValue_943) {
  UShortValue val;
  val.read("99");  // toString() returns "99", length 2 < 4
  maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "(99)");
}

// Test: Returns reference to the same ostream
TEST_F(CanonMakerNoteTest_943, Print0x0008_ReturnsOstream_943) {
  AsciiValue val;
  val.read("ABCDEFGH");
  std::ostream& result = maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test: Six characters
TEST_F(CanonMakerNoteTest_943, Print0x0008_SixChars_943) {
  AsciiValue val;
  val.read("ABCDEF");
  maker_.print0x0008(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "AB-CDEF");
}
