#include <gtest/gtest.h>
#include <sstream>
#include <cmath>

// We need to include or replicate the minimal Exiv2 types needed for testing.
// Since we're treating the implementation as a black box, we need the Value interface
// and related types that the function expects.

#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the internal header for Nikon3MakerNote
// We need to access the class from the partial code provided
namespace Exiv2 {
namespace Internal {

class Nikon3MakerNote {
 public:
  std::ostream& printTimeZone(std::ostream& os, const Value& value, const ExifData*) {
    if (value.count() != 1 || value.typeId() != signedShort)
      return os << "(" << value << ")";
    char sign = value.toInt64() < 0 ? '-' : '+';
    long h = static_cast<long>(std::fabs(value.toFloat() / 60.0F)) % 24;
    long min = static_cast<long>(std::fabs(value.toFloat() - (h * 60))) % 60;
    return os << stringFormat("UTC {}{:02}:{:02}", sign, h, min);
  }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_503 : public ::testing::Test {
 protected:
  Nikon3MakerNote maker_;
  std::ostringstream os_;
};

// Test: UTC+00:00 for value 0
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_Zero_503) {
  auto val = Value::create(signedShort);
  val->read("0");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC +00:00");
}

// Test: Positive offset, e.g., +5:30 (330 minutes)
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_PositiveOffset330_503) {
  auto val = Value::create(signedShort);
  val->read("330");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC +05:30");
}

// Test: Negative offset, e.g., -5:00 (-300 minutes)
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_NegativeOffset300_503) {
  auto val = Value::create(signedShort);
  val->read("-300");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC -05:00");
}

// Test: Positive offset +9:00 (540 minutes)
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_PositiveOffset540_503) {
  auto val = Value::create(signedShort);
  val->read("540");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC +09:00");
}

// Test: Negative offset -9:30 (-570 minutes)
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_NegativeOffset570_503) {
  auto val = Value::create(signedShort);
  val->read("-570");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC -09:30");
}

// Test: +1:00 offset (60 minutes)
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_PositiveOffset60_503) {
  auto val = Value::create(signedShort);
  val->read("60");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC +01:00");
}

// Test: -1:00 offset (-60 minutes)
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_NegativeOffset60_503) {
  auto val = Value::create(signedShort);
  val->read("-60");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC -01:00");
}

// Test: Wrong type (unsignedShort instead of signedShort) should produce parenthesized output
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_WrongType_503) {
  auto val = Value::create(unsignedShort);
  val->read("60");
  maker_.printTimeZone(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Multiple values (count != 1) should produce parenthesized output
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_MultipleValues_503) {
  auto val = Value::create(signedShort);
  val->read("60 120");
  ASSERT_EQ(val->count(), 2u);
  maker_.printTimeZone(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Empty value (count == 0) should produce parenthesized output
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_EmptyValue_503) {
  auto val = Value::create(signedShort);
  // Don't read anything, count should be 0
  ASSERT_EQ(val->count(), 0u);
  maker_.printTimeZone(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: +12:00 offset (720 minutes)
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_PositiveOffset720_503) {
  auto val = Value::create(signedShort);
  val->read("720");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC +12:00");
}

// Test: -12:00 offset (-720 minutes)
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_NegativeOffset720_503) {
  auto val = Value::create(signedShort);
  val->read("-720");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC -12:00");
}

// Test: Small positive offset +0:30 (30 minutes)
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_PositiveOffset30_503) {
  auto val = Value::create(signedShort);
  val->read("30");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC +00:30");
}

// Test: Small negative offset -0:30 (-30 minutes)
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_NegativeOffset30_503) {
  auto val = Value::create(signedShort);
  val->read("-30");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC -00:30");
}

// Test: +5:45 offset (345 minutes) - Nepal timezone
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_PositiveOffset345_503) {
  auto val = Value::create(signedShort);
  val->read("345");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC +05:45");
}

// Test: nullptr ExifData should still work
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_NullExifData_503) {
  auto val = Value::create(signedShort);
  val->read("0");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC +00:00");
}

// Test: Wrong type (asciiString) should produce parenthesized output
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_AsciiStringType_503) {
  auto val = Value::create(asciiString);
  val->read("hello");
  maker_.printTimeZone(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: -1 minute offset
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_NegativeOffset1_503) {
  auto val = Value::create(signedShort);
  val->read("-1");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC -00:01");
}

// Test: +1 minute offset
TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_PositiveOffset1_503) {
  auto val = Value::create(signedShort);
  val->read("1");
  maker_.printTimeZone(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "UTC +00:01");
}
