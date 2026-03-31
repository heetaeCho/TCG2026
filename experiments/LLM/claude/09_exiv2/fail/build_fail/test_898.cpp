#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>

// We need to access the internal class
// Based on the provided code, the class is in Exiv2::Internal namespace
namespace Exiv2 {
namespace Internal {
class OlympusMakerNote {
public:
  std::ostream& print0x0204(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

// Since we can't include the actual implementation header directly,
// we provide the implementation inline as given in the prompt
#include "exiv2/i18n.h"

namespace {

// Helper to format string like the implementation does
std::string stringFormat(const char* fmt, float val) {
  char buf[64];
  snprintf(buf, sizeof(buf), "%.1fx", val);
  return std::string(buf);
}

}  // namespace

class OlympusMakerNoteTest_898 : public ::testing::Test {
protected:
  Exiv2::Internal::OlympusMakerNote maker;
  std::ostringstream os;
};

// Test with empty value (count == 0)
TEST_F(OlympusMakerNoteTest_898, EmptyValueReturnsParenthesized_898) {
  Exiv2::URationalValue value;
  // count() == 0, should output "(" + value + ")"
  maker.print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test with rational where denominator is 0
TEST_F(OlympusMakerNoteTest_898, ZeroDenominatorReturnsParenthesized_898) {
  Exiv2::URationalValue value;
  value.value_.push_back({1, 0});
  maker.print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test with value == 0.0 (0/1) should return "None"
TEST_F(OlympusMakerNoteTest_898, ZeroValueReturnsNone_898) {
  Exiv2::URationalValue value;
  value.value_.push_back({0, 1});
  maker.print0x0204(os, value, nullptr);
  std::string result = os.str();
  // Should contain "None" (possibly translated)
  EXPECT_NE(result.find("None"), std::string::npos);
}

// Test with value == 1.0 (1/1) should return "None"
TEST_F(OlympusMakerNoteTest_898, OneValueReturnsNone_898) {
  Exiv2::URationalValue value;
  value.value_.push_back({1, 1});
  maker.print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("None"), std::string::npos);
}

// Test with value == 2.0 (2/1) should return "2.0x"
TEST_F(OlympusMakerNoteTest_898, TwoValueReturnsFormatted_898) {
  Exiv2::URationalValue value;
  value.value_.push_back({2, 1});
  maker.print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("2.0x"), std::string::npos);
}

// Test with value == 0.5 (1/2) should return "0.5x"
TEST_F(OlympusMakerNoteTest_898, HalfValueReturnsFormatted_898) {
  Exiv2::URationalValue value;
  value.value_.push_back({1, 2});
  maker.print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("0.5x"), std::string::npos);
}

// Test with value == 1.5 (3/2) should return "1.5x"
TEST_F(OlympusMakerNoteTest_898, OnePointFiveReturnsFormatted_898) {
  Exiv2::URationalValue value;
  value.value_.push_back({3, 2});
  maker.print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("1.5x"), std::string::npos);
}

// Test with nullptr ExifData (should not crash)
TEST_F(OlympusMakerNoteTest_898, NullExifDataDoesNotCrash_898) {
  Exiv2::URationalValue value;
  value.value_.push_back({5, 2});
  EXPECT_NO_THROW(maker.print0x0204(os, value, nullptr));
  std::string result = os.str();
  EXPECT_NE(result.find("2.5x"), std::string::npos);
}

// Test with large rational value
TEST_F(OlympusMakerNoteTest_898, LargeValueReturnsFormatted_898) {
  Exiv2::URationalValue value;
  value.value_.push_back({100, 1});
  maker.print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("100.0x"), std::string::npos);
}

// Test with multiple values (count > 1 but first value matters)
TEST_F(OlympusMakerNoteTest_898, MultipleValuesUsesFirst_898) {
  Exiv2::URationalValue value;
  value.value_.push_back({3, 1});
  value.value_.push_back({5, 1});
  maker.print0x0204(os, value, nullptr);
  std::string result = os.str();
  // The function should use the first rational for toFloat/toRational
  EXPECT_NE(result.find("3.0x"), std::string::npos);
}

// Test return value is the same stream
TEST_F(OlympusMakerNoteTest_898, ReturnsSameStream_898) {
  Exiv2::URationalValue value;
  value.value_.push_back({2, 1});
  std::ostream& returned = maker.print0x0204(os, value, nullptr);
  EXPECT_EQ(&returned, &os);
}

// Test with very small rational (close to zero but not zero)
TEST_F(OlympusMakerNoteTest_898, VerySmallNonZeroValueReturnsFormatted_898) {
  Exiv2::URationalValue value;
  value.value_.push_back({1, 1000});
  maker.print0x0204(os, value, nullptr);
  std::string result = os.str();
  // Should have 'x' suffix since it's not exactly 0.0 or 1.0
  EXPECT_NE(result.find("x"), std::string::npos);
}
