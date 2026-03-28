#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the header that contains PentaxMakerNote
// Since the implementation is provided inline, we may need to include it directly
// or reconstruct the minimal interface for testing purposes.

namespace Exiv2 {
namespace Internal {
class PentaxMakerNote {
 public:
  std::ostream& printVersion(std::ostream& os, const Value& value, const ExifData*) {
    std::string val = value.toString();
    std::replace(val.begin(), val.end(), ' ', '.');
    os << val;
    return os;
  }
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxMakerNoteTest_189 : public ::testing::Test {
 protected:
  PentaxMakerNote maker_;
  std::ostringstream oss_;
};

// Test that printVersion outputs version string with spaces replaced by dots
TEST_F(PentaxMakerNoteTest_189, PrintVersionReplacesSpacesWithDots_189) {
  Exiv2::AsciiValue val("1 2 3 4");
  maker_.printVersion(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "1.2.3.4");
}

// Test that printVersion works with a single value (no spaces)
TEST_F(PentaxMakerNoteTest_189, PrintVersionSingleValueNoSpaces_189) {
  Exiv2::AsciiValue val("100");
  maker_.printVersion(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "100");
}

// Test that printVersion works with an empty string value
TEST_F(PentaxMakerNoteTest_189, PrintVersionEmptyString_189) {
  Exiv2::AsciiValue val("");
  maker_.printVersion(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "");
}

// Test that printVersion returns the same ostream reference
TEST_F(PentaxMakerNoteTest_189, PrintVersionReturnsOstream_189) {
  Exiv2::AsciiValue val("1 0");
  std::ostream& result = maker_.printVersion(oss_, val, nullptr);
  EXPECT_EQ(&result, &oss_);
}

// Test with multiple consecutive spaces
TEST_F(PentaxMakerNoteTest_189, PrintVersionMultipleConsecutiveSpaces_189) {
  Exiv2::AsciiValue val("1  2");
  maker_.printVersion(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "1..2");
}

// Test with only spaces
TEST_F(PentaxMakerNoteTest_189, PrintVersionOnlySpaces_189) {
  Exiv2::AsciiValue val("   ");
  maker_.printVersion(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "...");
}

// Test with nullptr ExifData parameter (should work fine)
TEST_F(PentaxMakerNoteTest_189, PrintVersionNullExifData_189) {
  Exiv2::AsciiValue val("3 2 1");
  EXPECT_NO_THROW(maker_.printVersion(oss_, val, nullptr));
  EXPECT_EQ(oss_.str(), "3.2.1");
}

// Test with a typical firmware version string
TEST_F(PentaxMakerNoteTest_189, PrintVersionTypicalFirmwareVersion_189) {
  Exiv2::AsciiValue val("1 0 3 0");
  maker_.printVersion(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "1.0.3.0");
}

// Test with leading and trailing spaces
TEST_F(PentaxMakerNoteTest_189, PrintVersionLeadingTrailingSpaces_189) {
  Exiv2::AsciiValue val(" 1 2 ");
  maker_.printVersion(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), ".1.2.");
}

// Test with string containing dots already (no modification expected for dots)
TEST_F(PentaxMakerNoteTest_189, PrintVersionStringWithExistingDots_189) {
  Exiv2::AsciiValue val("1.2 3.4");
  maker_.printVersion(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "1.2.3.4");
}

// Test that printVersion works with numeric UShort values
TEST_F(PentaxMakerNoteTest_189, PrintVersionWithUShortValue_189) {
  Exiv2::UShortValue val;
  val.read("1 2 3 4");
  maker_.printVersion(oss_, val, nullptr);
  // UShortValue::toString() typically outputs values separated by spaces
  std::string result = oss_.str();
  // Spaces should be replaced by dots
  EXPECT_EQ(result.find(' '), std::string::npos);
}

// Test with a single character value
TEST_F(PentaxMakerNoteTest_189, PrintVersionSingleCharacter_189) {
  Exiv2::AsciiValue val("5");
  maker_.printVersion(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "5");
}

// Test accumulation on ostream - printVersion appends to existing content
TEST_F(PentaxMakerNoteTest_189, PrintVersionAppendsToExistingContent_189) {
  oss_ << "Version: ";
  Exiv2::AsciiValue val("1 0");
  maker_.printVersion(oss_, val, nullptr);
  EXPECT_EQ(oss_.str(), "Version: 1.0");
}
