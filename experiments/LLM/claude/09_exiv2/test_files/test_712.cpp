#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the header that contains PanasonicMakerNote or replicate the minimal interface
namespace Exiv2 {
namespace Internal {

class PanasonicMakerNote {
 public:
  std::ostream& print0x003c(std::ostream& os, const Value& value, const ExifData*);
};

}  // namespace Internal
}  // namespace Exiv2

// Since the implementation is in panasonicmn_int.cpp, we need to link against it.
// For testing purposes, we include the implementation directly if needed.
// The actual linking should be handled by the build system.

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

class PanasonicMakerNoteTest_712 : public ::testing::Test {
 protected:
  PanasonicMakerNote maker_note_;
  std::ostringstream os_;
};

// Test that value 65534 prints "Intelligent ISO"
TEST_F(PanasonicMakerNoteTest_712, Print0x003c_IntelligentISO_712) {
  Exiv2::ValueType<uint16_t> value;
  value.read("65534");
  maker_note_.print0x003c(os_, value, nullptr);
  EXPECT_NE(os_.str().find("Intelligent ISO"), std::string::npos);
}

// Test that value 65535 prints "n/a"
TEST_F(PanasonicMakerNoteTest_712, Print0x003c_NotApplicable_712) {
  Exiv2::ValueType<uint16_t> value;
  value.read("65535");
  maker_note_.print0x003c(os_, value, nullptr);
  EXPECT_NE(os_.str().find("n/a"), std::string::npos);
}

// Test that a default/other value prints the value itself
TEST_F(PanasonicMakerNoteTest_712, Print0x003c_DefaultValue_712) {
  Exiv2::ValueType<uint16_t> value;
  value.read("100");
  maker_note_.print0x003c(os_, value, nullptr);
  EXPECT_NE(os_.str().find("100"), std::string::npos);
}

// Test with value 0 (boundary - minimum)
TEST_F(PanasonicMakerNoteTest_712, Print0x003c_ZeroValue_712) {
  Exiv2::ValueType<uint16_t> value;
  value.read("0");
  maker_note_.print0x003c(os_, value, nullptr);
  EXPECT_NE(os_.str().find("0"), std::string::npos);
}

// Test with value 1 (small positive value)
TEST_F(PanasonicMakerNoteTest_712, Print0x003c_ValueOne_712) {
  Exiv2::ValueType<uint16_t> value;
  value.read("1");
  maker_note_.print0x003c(os_, value, nullptr);
  EXPECT_NE(os_.str().find("1"), std::string::npos);
}

// Test with value 65533 (one less than Intelligent ISO)
TEST_F(PanasonicMakerNoteTest_712, Print0x003c_JustBelowIntelligentISO_712) {
  Exiv2::ValueType<uint16_t> value;
  value.read("65533");
  maker_note_.print0x003c(os_, value, nullptr);
  EXPECT_NE(os_.str().find("65533"), std::string::npos);
  // Make sure it does NOT print "Intelligent ISO"
  EXPECT_EQ(os_.str().find("Intelligent ISO"), std::string::npos);
}

// Test that the function returns a reference to the same ostream
TEST_F(PanasonicMakerNoteTest_712, Print0x003c_ReturnsOstream_712) {
  Exiv2::ValueType<uint16_t> value;
  value.read("100");
  std::ostream& result = maker_note_.print0x003c(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test with nullptr ExifData (should not crash)
TEST_F(PanasonicMakerNoteTest_712, Print0x003c_NullExifData_712) {
  Exiv2::ValueType<uint16_t> value;
  value.read("65534");
  EXPECT_NO_THROW(maker_note_.print0x003c(os_, value, nullptr));
}

// Test with a typical ISO value like 200
TEST_F(PanasonicMakerNoteTest_712, Print0x003c_TypicalISOValue_712) {
  Exiv2::ValueType<uint16_t> value;
  value.read("200");
  maker_note_.print0x003c(os_, value, nullptr);
  EXPECT_NE(os_.str().find("200"), std::string::npos);
}

// Test with a typical ISO value like 3200
TEST_F(PanasonicMakerNoteTest_712, Print0x003c_HighISOValue_712) {
  Exiv2::ValueType<uint16_t> value;
  value.read("3200");
  maker_note_.print0x003c(os_, value, nullptr);
  EXPECT_NE(os_.str().find("3200"), std::string::npos);
}

// Test that 65534 does NOT contain "n/a"
TEST_F(PanasonicMakerNoteTest_712, Print0x003c_IntelligentISO_NotNA_712) {
  Exiv2::ValueType<uint16_t> value;
  value.read("65534");
  maker_note_.print0x003c(os_, value, nullptr);
  EXPECT_EQ(os_.str().find("n/a"), std::string::npos);
}

// Test that 65535 does NOT contain "Intelligent ISO"
TEST_F(PanasonicMakerNoteTest_712, Print0x003c_NA_NotIntelligentISO_712) {
  Exiv2::ValueType<uint16_t> value;
  value.read("65535");
  maker_note_.print0x003c(os_, value, nullptr);
  EXPECT_EQ(os_.str().find("Intelligent ISO"), std::string::npos);
}

}  // namespace
