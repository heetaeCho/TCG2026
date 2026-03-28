#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "panasonicmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PanasonicMakerNoteTest_706 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test that tagList() returns a non-null pointer
TEST_F(PanasonicMakerNoteTest_706, TagListReturnsNonNull_706) {
  auto tagList = PanasonicMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListRaw() returns a non-null pointer
TEST_F(PanasonicMakerNoteTest_706, TagListRawReturnsNonNull_706) {
  auto tagListRaw = PanasonicMakerNote::tagListRaw();
  ASSERT_NE(tagListRaw, nullptr);
}

// Test print0x000f with a known value
TEST_F(PanasonicMakerNoteTest_706, Print0x000f_NormalValue_706) {
  UShortValue value;
  value.read("1");
  PanasonicMakerNote::print0x000f(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test print0x000f with zero value
TEST_F(PanasonicMakerNoteTest_706, Print0x000f_ZeroValue_706) {
  UShortValue value;
  value.read("0");
  PanasonicMakerNote::print0x000f(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test print0x0023 with a normal value
TEST_F(PanasonicMakerNoteTest_706, Print0x0023_NormalValue_706) {
  UShortValue value;
  value.read("1");
  PanasonicMakerNote::print0x0023(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test print0x0023 with zero
TEST_F(PanasonicMakerNoteTest_706, Print0x0023_ZeroValue_706) {
  UShortValue value;
  value.read("0");
  PanasonicMakerNote::print0x0023(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test print0x0029 with a normal value
TEST_F(PanasonicMakerNoteTest_706, Print0x0029_NormalValue_706) {
  UShortValue value;
  value.read("1");
  PanasonicMakerNote::print0x0029(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test print0x0033 with a normal value
TEST_F(PanasonicMakerNoteTest_706, Print0x0033_NormalValue_706) {
  UShortValue value;
  value.read("1");
  PanasonicMakerNote::print0x0033(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test print0x0036 with a normal value
TEST_F(PanasonicMakerNoteTest_706, Print0x0036_NormalValue_706) {
  UShortValue value;
  value.read("1");
  PanasonicMakerNote::print0x0036(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test print0x003c with a normal value
TEST_F(PanasonicMakerNoteTest_706, Print0x003c_NormalValue_706) {
  UShortValue value;
  value.read("1");
  PanasonicMakerNote::print0x003c(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test printPressure with a normal value
TEST_F(PanasonicMakerNoteTest_706, PrintPressure_NormalValue_706) {
  UShortValue value;
  value.read("1013");
  PanasonicMakerNote::printPressure(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test printPressure with zero value
TEST_F(PanasonicMakerNoteTest_706, PrintPressure_ZeroValue_706) {
  UShortValue value;
  value.read("0");
  PanasonicMakerNote::printPressure(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test printPanasonicText with ASCII text
TEST_F(PanasonicMakerNoteTest_706, PrintPanasonicText_NormalText_706) {
  DataValue value(invalidTypeId);
  const byte text[] = "Hello World";
  value.read(text, sizeof(text) - 1);
  PanasonicMakerNote::printPanasonicText(os, value, nullptr);
  std::string result = os.str();
  // The output should contain some text
  EXPECT_FALSE(result.empty());
}

// Test printPanasonicText with empty value
TEST_F(PanasonicMakerNoteTest_706, PrintPanasonicText_EmptyValue_706) {
  DataValue value(invalidTypeId);
  PanasonicMakerNote::printPanasonicText(os, value, nullptr);
  std::string result = os.str();
  // Should still produce some output or handle gracefully
}

// Test printAccelerometer with a normal value
TEST_F(PanasonicMakerNoteTest_706, PrintAccelerometer_NormalValue_706) {
  UShortValue value;
  value.read("100");
  PanasonicMakerNote::printAccelerometer(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test printAccelerometer with zero value
TEST_F(PanasonicMakerNoteTest_706, PrintAccelerometer_ZeroValue_706) {
  UShortValue value;
  value.read("0");
  PanasonicMakerNote::printAccelerometer(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test printRollAngle with a normal value
TEST_F(PanasonicMakerNoteTest_706, PrintRollAngle_NormalValue_706) {
  UShortValue value;
  value.read("100");
  PanasonicMakerNote::printRollAngle(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test printRollAngle with zero value
TEST_F(PanasonicMakerNoteTest_706, PrintRollAngle_ZeroValue_706) {
  UShortValue value;
  value.read("0");
  PanasonicMakerNote::printRollAngle(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test printPitchAngle with a normal value
TEST_F(PanasonicMakerNoteTest_706, PrintPitchAngle_NormalValue_706) {
  UShortValue value;
  value.read("100");
  PanasonicMakerNote::printPitchAngle(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test printPitchAngle with zero value
TEST_F(PanasonicMakerNoteTest_706, PrintPitchAngle_ZeroValue_706) {
  UShortValue value;
  value.read("0");
  PanasonicMakerNote::printPitchAngle(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test that print functions return the ostream reference
TEST_F(PanasonicMakerNoteTest_706, Print0x000f_ReturnsOstream_706) {
  UShortValue value;
  value.read("1");
  std::ostream& result = PanasonicMakerNote::print0x000f(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(PanasonicMakerNoteTest_706, Print0x0023_ReturnsOstream_706) {
  UShortValue value;
  value.read("1");
  std::ostream& result = PanasonicMakerNote::print0x0023(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(PanasonicMakerNoteTest_706, Print0x0029_ReturnsOstream_706) {
  UShortValue value;
  value.read("1");
  std::ostream& result = PanasonicMakerNote::print0x0029(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(PanasonicMakerNoteTest_706, Print0x0033_ReturnsOstream_706) {
  UShortValue value;
  value.read("1");
  std::ostream& result = PanasonicMakerNote::print0x0033(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(PanasonicMakerNoteTest_706, Print0x0036_ReturnsOstream_706) {
  UShortValue value;
  value.read("1");
  std::ostream& result = PanasonicMakerNote::print0x0036(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(PanasonicMakerNoteTest_706, Print0x003c_ReturnsOstream_706) {
  UShortValue value;
  value.read("1");
  std::ostream& result = PanasonicMakerNote::print0x003c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(PanasonicMakerNoteTest_706, PrintPressure_ReturnsOstream_706) {
  UShortValue value;
  value.read("1013");
  std::ostream& result = PanasonicMakerNote::printPressure(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(PanasonicMakerNoteTest_706, PrintAccelerometer_ReturnsOstream_706) {
  UShortValue value;
  value.read("100");
  std::ostream& result = PanasonicMakerNote::printAccelerometer(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(PanasonicMakerNoteTest_706, PrintRollAngle_ReturnsOstream_706) {
  UShortValue value;
  value.read("100");
  std::ostream& result = PanasonicMakerNote::printRollAngle(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(PanasonicMakerNoteTest_706, PrintPitchAngle_ReturnsOstream_706) {
  UShortValue value;
  value.read("100");
  std::ostream& result = PanasonicMakerNote::printPitchAngle(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(PanasonicMakerNoteTest_706, PrintPanasonicText_ReturnsOstream_706) {
  DataValue value(invalidTypeId);
  const byte text[] = "Test";
  value.read(text, sizeof(text) - 1);
  std::ostream& result = PanasonicMakerNote::printPanasonicText(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test with large values for boundary conditions
TEST_F(PanasonicMakerNoteTest_706, PrintAccelerometer_LargeValue_706) {
  UShortValue value;
  value.read("65535");
  PanasonicMakerNote::printAccelerometer(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(PanasonicMakerNoteTest_706, PrintRollAngle_LargeValue_706) {
  UShortValue value;
  value.read("65535");
  PanasonicMakerNote::printRollAngle(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(PanasonicMakerNoteTest_706, PrintPitchAngle_LargeValue_706) {
  UShortValue value;
  value.read("65535");
  PanasonicMakerNote::printPitchAngle(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(PanasonicMakerNoteTest_706, PrintPressure_LargeValue_706) {
  UShortValue value;
  value.read("65535");
  PanasonicMakerNote::printPressure(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test tagList entries have valid tag information
TEST_F(PanasonicMakerNoteTest_706, TagListFirstEntryValid_706) {
  auto tagList = PanasonicMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  // First entry should have a valid tag (non-negative tag number is typical)
  EXPECT_GE(tagList[0].tag_, 0);
}

// Test tagListRaw entries have valid tag information  
TEST_F(PanasonicMakerNoteTest_706, TagListRawFirstEntryValid_706) {
  auto tagListRaw = PanasonicMakerNote::tagListRaw();
  ASSERT_NE(tagListRaw, nullptr);
  EXPECT_GE(tagListRaw[0].tag_, 0);
}

// Test print0x000f with various known enum values
TEST_F(PanasonicMakerNoteTest_706, Print0x000f_MultipleValues_706) {
  for (int i = 0; i < 10; ++i) {
    std::ostringstream localOs;
    UShortValue value;
    value.read(std::to_string(i));
    PanasonicMakerNote::print0x000f(localOs, value, nullptr);
    EXPECT_FALSE(localOs.str().empty()) << "Failed for value: " << i;
  }
}

// Test print0x0023 with various values
TEST_F(PanasonicMakerNoteTest_706, Print0x0023_MultipleValues_706) {
  for (int i = 0; i < 10; ++i) {
    std::ostringstream localOs;
    UShortValue value;
    value.read(std::to_string(i));
    PanasonicMakerNote::print0x0023(localOs, value, nullptr);
    EXPECT_FALSE(localOs.str().empty()) << "Failed for value: " << i;
  }
}
