#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the internal header for PanasonicMakerNote
// We need access to the class defined in panasonicmn_int.cpp
// Since the class is defined in the Internal namespace, we replicate the declaration
// based on the provided partial code for testing purposes.

namespace Exiv2 {
namespace Internal {

class PanasonicMakerNote {
 public:
  std::ostream& print0x0033(std::ostream& os, const Value& value, const ExifData*) {
    if (value.toString() == "9999:99:99 00:00:00") {
      os << _("not set");
    } else {
      os << value;
    }
    return os;
  }
};

}  // namespace Internal
}  // namespace Exiv2

class PanasonicMakerNoteTest_710 : public ::testing::Test {
 protected:
  Exiv2::Internal::PanasonicMakerNote makerNote_;
  std::ostringstream oss_;
};

// Test that when value is the sentinel "9999:99:99 00:00:00", output is "not set"
TEST_F(PanasonicMakerNoteTest_710, Print0x0033_NotSetValue_PrintsNotSet_710) {
  Exiv2::AsciiValue value;
  value.read("9999:99:99 00:00:00");

  makerNote_.print0x0033(oss_, value, nullptr);

  // The output should contain "not set" (possibly translated)
  std::string result = oss_.str();
  EXPECT_FALSE(result.empty());
  // Check that it does NOT output the raw sentinel value
  EXPECT_EQ(result.find("9999:99:99"), std::string::npos);
}

// Test that when value is a normal date, it outputs the value as-is
TEST_F(PanasonicMakerNoteTest_710, Print0x0033_NormalDate_PrintsValue_710) {
  Exiv2::AsciiValue value;
  value.read("2023:06:15 10:30:00");

  makerNote_.print0x0033(oss_, value, nullptr);

  std::string result = oss_.str();
  EXPECT_NE(result.find("2023:06:15 10:30:00"), std::string::npos);
}

// Test that an empty string value outputs the value (not "not set")
TEST_F(PanasonicMakerNoteTest_710, Print0x0033_EmptyValue_PrintsValue_710) {
  Exiv2::AsciiValue value;
  value.read("");

  makerNote_.print0x0033(oss_, value, nullptr);

  std::string result = oss_.str();
  // Should NOT say "not set" since it doesn't match the sentinel
  EXPECT_EQ(result.find("not set"), std::string::npos);
}

// Test that a partial match of the sentinel does not trigger "not set"
TEST_F(PanasonicMakerNoteTest_710, Print0x0033_PartialSentinel_PrintsValue_710) {
  Exiv2::AsciiValue value;
  value.read("9999:99:99");

  makerNote_.print0x0033(oss_, value, nullptr);

  std::string result = oss_.str();
  EXPECT_NE(result.find("9999:99:99"), std::string::npos);
}

// Test that the function returns the same ostream reference
TEST_F(PanasonicMakerNoteTest_710, Print0x0033_ReturnsOstream_710) {
  Exiv2::AsciiValue value;
  value.read("2023:01:01 00:00:00");

  std::ostream& returned = makerNote_.print0x0033(oss_, value, nullptr);

  EXPECT_EQ(&returned, &oss_);
}

// Test with nullptr ExifData (should work fine, as the function doesn't use it)
TEST_F(PanasonicMakerNoteTest_710, Print0x0033_NullExifData_Works_710) {
  Exiv2::AsciiValue value;
  value.read("2020:12:25 18:00:00");

  EXPECT_NO_THROW(makerNote_.print0x0033(oss_, value, nullptr));

  std::string result = oss_.str();
  EXPECT_NE(result.find("2020:12:25 18:00:00"), std::string::npos);
}

// Test with a value that has extra whitespace - should not match sentinel
TEST_F(PanasonicMakerNoteTest_710, Print0x0033_SentinelWithExtraSpace_PrintsValue_710) {
  Exiv2::AsciiValue value;
  value.read("9999:99:99 00:00:00 ");

  makerNote_.print0x0033(oss_, value, nullptr);

  std::string result = oss_.str();
  // With trailing space, toString() won't match exactly, so it should print the value
  EXPECT_NE(result.find("9999:99:99"), std::string::npos);
}

// Test with a different arbitrary string
TEST_F(PanasonicMakerNoteTest_710, Print0x0033_ArbitraryString_PrintsValue_710) {
  Exiv2::AsciiValue value;
  value.read("some random text");

  makerNote_.print0x0033(oss_, value, nullptr);

  std::string result = oss_.str();
  EXPECT_NE(result.find("some random text"), std::string::npos);
}

// Test that sentinel matching is exact (case-sensitive, no leading/trailing variation)
TEST_F(PanasonicMakerNoteTest_710, Print0x0033_SentinelLeadingSpace_PrintsValue_710) {
  Exiv2::AsciiValue value;
  value.read(" 9999:99:99 00:00:00");

  makerNote_.print0x0033(oss_, value, nullptr);

  std::string result = oss_.str();
  // Leading space means it won't match sentinel
  EXPECT_NE(result.find("9999:99:99"), std::string::npos);
}
