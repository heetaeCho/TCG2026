#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include necessary exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the Internal namespace
// Since the class is defined in sigmamn_int.cpp, we need to include or replicate the header
// Based on the provided code, we'll include what's needed and declare the class

namespace Exiv2 {
namespace Internal {
class SigmaMakerNote {
 public:
  std::ostream& print0x0009(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

// Helper function to create a Value with a specific string
static std::unique_ptr<Exiv2::Value> makeStringValue(const std::string& str) {
  auto val = Exiv2::Value::create(Exiv2::asciiString);
  val->read(str);
  return val;
}

class SigmaMakerNoteTest_1727 : public ::testing::Test {
 protected:
  Exiv2::Internal::SigmaMakerNote maker_;
  std::ostringstream os_;
};

// Test that 'A' prefix outputs "Average"
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_Average_1727) {
  auto value = makeStringValue("A");
  maker_.print0x0009(os_, *value, nullptr);
  EXPECT_NE(os_.str().find("Average"), std::string::npos);
}

// Test that 'C' prefix outputs "Center"
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_Center_1727) {
  auto value = makeStringValue("C");
  maker_.print0x0009(os_, *value, nullptr);
  EXPECT_NE(os_.str().find("Center"), std::string::npos);
}

// Test that '8' prefix outputs "8-Segment"
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_8Segment_1727) {
  auto value = makeStringValue("8");
  maker_.print0x0009(os_, *value, nullptr);
  EXPECT_NE(os_.str().find("8-Segment"), std::string::npos);
}

// Test that unknown character falls through to default with parentheses
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_DefaultUnknownChar_1727) {
  auto value = makeStringValue("X");
  maker_.print0x0009(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test default case with another unknown character
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_DefaultUnknownCharZ_1727) {
  auto value = makeStringValue("Z");
  maker_.print0x0009(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test that 'A' with additional text still matches Average (first char is 'A')
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_AverageWithSuffix_1727) {
  auto value = makeStringValue("ABC");
  maker_.print0x0009(os_, *value, nullptr);
  EXPECT_NE(os_.str().find("Average"), std::string::npos);
}

// Test that 'C' with additional text still matches Center
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_CenterWithSuffix_1727) {
  auto value = makeStringValue("Center123");
  maker_.print0x0009(os_, *value, nullptr);
  EXPECT_NE(os_.str().find("Center"), std::string::npos);
}

// Test that '8' with additional text still matches 8-Segment
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_8SegmentWithSuffix_1727) {
  auto value = makeStringValue("8xyz");
  maker_.print0x0009(os_, *value, nullptr);
  EXPECT_NE(os_.str().find("8-Segment"), std::string::npos);
}

// Test return value is the same ostream reference
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_ReturnsOstream_1727) {
  auto value = makeStringValue("A");
  std::ostream& result = maker_.print0x0009(os_, *value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test default with numeric character other than '8'
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_DefaultNumeric_1727) {
  auto value = makeStringValue("5");
  maker_.print0x0009(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test with lowercase 'a' - should hit default (case sensitive)
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_LowercaseADefault_1727) {
  auto value = makeStringValue("a");
  maker_.print0x0009(os_, *value, nullptr);
  std::string result = os_.str();
  // Lowercase 'a' is not 'A', so it should be default
  EXPECT_NE(result.find("("), std::string::npos);
}

// Test with lowercase 'c' - should hit default (case sensitive)
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_LowercaseCDefault_1727) {
  auto value = makeStringValue("c");
  maker_.print0x0009(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("("), std::string::npos);
}

// Test with ExifData pointer being nullptr (should not crash)
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_NullExifData_1727) {
  auto value = makeStringValue("A");
  EXPECT_NO_THROW(maker_.print0x0009(os_, *value, nullptr));
}

// Test that default output contains the value itself
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_DefaultContainsValue_1727) {
  auto value = makeStringValue("Q");
  maker_.print0x0009(os_, *value, nullptr);
  std::string result = os_.str();
  // Should contain the value between parentheses
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find("Q"), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test with space character - should hit default
TEST_F(SigmaMakerNoteTest_1727, Print0x0009_SpaceDefault_1727) {
  auto value = makeStringValue(" ");
  maker_.print0x0009(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}
