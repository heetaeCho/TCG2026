#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the internal header for PentaxMakerNote
namespace Exiv2 {
namespace Internal {
class PentaxMakerNote {
 public:
  std::ostream& printResolution(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

// We need access to the implementation
#include "pentaxmn_int.cpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxMakerNoteTest_190 : public ::testing::Test {
 protected:
  PentaxMakerNote maker_;
  std::ostringstream os_;
};

// Test: Normal resolution string with space separator gets replaced by 'x'
TEST_F(PentaxMakerNoteTest_190, PrintResolution_NormalTwoValues_190) {
  AsciiValue val;
  val.read("3000 2000");
  maker_.printResolution(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "3000x2000");
}

// Test: Single value with no spaces remains unchanged
TEST_F(PentaxMakerNoteTest_190, PrintResolution_SingleValue_190) {
  AsciiValue val;
  val.read("3000");
  maker_.printResolution(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "3000");
}

// Test: Empty string produces empty output
TEST_F(PentaxMakerNoteTest_190, PrintResolution_EmptyString_190) {
  AsciiValue val;
  val.read("");
  maker_.printResolution(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "");
}

// Test: Multiple spaces are all replaced with 'x'
TEST_F(PentaxMakerNoteTest_190, PrintResolution_MultipleSpaces_190) {
  AsciiValue val;
  val.read("1 2 3");
  maker_.printResolution(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "1x2x3");
}

// Test: String with only spaces becomes all 'x's
TEST_F(PentaxMakerNoteTest_190, PrintResolution_OnlySpaces_190) {
  AsciiValue val;
  val.read("   ");
  maker_.printResolution(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "xxx");
}

// Test: Passing nullptr for ExifData does not cause crash
TEST_F(PentaxMakerNoteTest_190, PrintResolution_NullExifData_190) {
  AsciiValue val;
  val.read("4000 3000");
  EXPECT_NO_THROW(maker_.printResolution(os_, val, nullptr));
  EXPECT_EQ(os_.str(), "4000x3000");
}

// Test: Return value is a reference to the same ostream
TEST_F(PentaxMakerNoteTest_190, PrintResolution_ReturnsOstream_190) {
  AsciiValue val;
  val.read("100 200");
  std::ostream& result = maker_.printResolution(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test: String without spaces stays the same (no replacement needed)
TEST_F(PentaxMakerNoteTest_190, PrintResolution_NoSpaces_190) {
  AsciiValue val;
  val.read("abcdef");
  maker_.printResolution(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "abcdef");
}

// Test: Leading and trailing spaces are also replaced
TEST_F(PentaxMakerNoteTest_190, PrintResolution_LeadingTrailingSpaces_190) {
  AsciiValue val;
  val.read(" 3000 2000 ");
  maker_.printResolution(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "x3000x2000x");
}

// Test: Numeric values using UShortValue
TEST_F(PentaxMakerNoteTest_190, PrintResolution_UShortValue_190) {
  UShortValue val;
  val.read("3000 2000");
  maker_.printResolution(os_, val, nullptr);
  std::string result = os_.str();
  // Spaces in toString() should be replaced with 'x'
  EXPECT_TRUE(result.find(' ') == std::string::npos);
}
