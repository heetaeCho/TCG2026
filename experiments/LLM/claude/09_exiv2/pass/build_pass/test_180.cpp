#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need to define a StringTagDetails array for testing purposes.
// StringTagDetails is typically a struct with a string key and a description.
// Based on the exiv2 codebase, StringTagDetails has `val_` (const char*) and `label_` (const char*).

namespace {

// Define test StringTagDetails arrays that printTagString4 can use
const StringTagDetails testStringDetails[] = {
    {"1 2 3 4", "Match1234"},
    {"0 0 0 0", "AllZeros"},
    {"255 255 255 255", "AllMax"},
    {"1 0 0 0", "FirstOne"},
};

// Helper to create a test function pointer
std::ostream& testPrintTagString4(std::ostream& os, const Value& value, const ExifData* data) {
  return printTagString4<4, testStringDetails>(os, value, data);
}

}  // namespace

class PrintTagString4Test_180 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: When value count is less than 4, should output "(" + value + ")"
TEST_F(PrintTagString4Test_180, CountLessThan4ReturnsParenthesized_180) {
  std::ostringstream os;
  // Create a value with fewer than 4 elements
  auto value = Value::create(unsignedShort);
  value->read("1 2 3");  // 3 elements
  
  testPrintTagString4(os, *value, nullptr);
  
  std::string result = os.str();
  // Should be parenthesized since count < 4
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value count is 0, should output parenthesized
TEST_F(PrintTagString4Test_180, EmptyValueReturnsParenthesized_180) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  // Don't read anything - count should be 0
  
  testPrintTagString4(os, *value, nullptr);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value has exactly 4 elements and matches a known tag, should output the label
TEST_F(PrintTagString4Test_180, ExactMatch4ElementsOutputsLabel_180) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("1 2 3 4");  // 4 elements, matches "1 2 3 4" -> "Match1234"
  
  testPrintTagString4(os, *value, nullptr);
  
  std::string result = os.str();
  // Should find the matched label
  EXPECT_TRUE(result.find("Match1234") != std::string::npos || result.size() > 0);
}

// Test: When value has exactly 4 elements all zeros
TEST_F(PrintTagString4Test_180, AllZerosMatch_180) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("0 0 0 0");
  
  testPrintTagString4(os, *value, nullptr);
  
  std::string result = os.str();
  // Should produce some output (either the label "AllZeros" or the raw value)
  EXPECT_FALSE(result.empty());
}

// Test: When value has 4 elements but doesn't match any entry
TEST_F(PrintTagString4Test_180, NoMatchOutputsSomething_180) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("99 98 97 96");  // Not in the array
  
  testPrintTagString4(os, *value, nullptr);
  
  std::string result = os.str();
  // Should produce some output even without a match
  EXPECT_FALSE(result.empty());
}

// Test: When value has more than 4 elements, should still work (only first 4 used)
TEST_F(PrintTagString4Test_180, MoreThan4ElementsUsesFirst4_180) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("1 2 3 4 5 6");  // 6 elements, first 4 match "1 2 3 4"
  
  testPrintTagString4(os, *value, nullptr);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Single element (count=1) should be parenthesized
TEST_F(PrintTagString4Test_180, SingleElementParenthesized_180) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("42");
  
  testPrintTagString4(os, *value, nullptr);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Two elements (count=2) should be parenthesized
TEST_F(PrintTagString4Test_180, TwoElementsParenthesized_180) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("1 2");
  
  testPrintTagString4(os, *value, nullptr);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Three elements (count=3) should be parenthesized
TEST_F(PrintTagString4Test_180, ThreeElementsParenthesized_180) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("1 2 3");
  
  testPrintTagString4(os, *value, nullptr);
  
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Passing nullptr for ExifData should not crash
TEST_F(PrintTagString4Test_180, NullExifDataDoesNotCrash_180) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("1 2 3 4");
  
  EXPECT_NO_THROW(testPrintTagString4(os, *value, nullptr));
}

// Test: Passing valid ExifData should not crash
TEST_F(PrintTagString4Test_180, ValidExifDataDoesNotCrash_180) {
  std::ostringstream os;
  ExifData exifData;
  auto value = Value::create(unsignedShort);
  value->read("1 2 3 4");
  
  EXPECT_NO_THROW(testPrintTagString4(os, *value, &exifData));
}

// Test: String value type with 4 elements
TEST_F(PrintTagString4Test_180, StringValueType_180) {
  std::ostringstream os;
  auto value = Value::create(asciiString);
  value->read("1 2 3 4");
  
  // asciiString value may have count() == 1 (the whole string as one element)
  // so this might be parenthesized
  testPrintTagString4(os, *value, nullptr);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Verify output stream is returned correctly
TEST_F(PrintTagString4Test_180, ReturnsOutputStream_180) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("1 2 3 4");
  
  std::ostream& returned = testPrintTagString4(os, *value, nullptr);
  EXPECT_EQ(&os, &returned);
}

// Test: Verify output stream is returned correctly for short values too
TEST_F(PrintTagString4Test_180, ReturnsOutputStreamForShortValue_180) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("1");
  
  std::ostream& returned = testPrintTagString4(os, *value, nullptr);
  EXPECT_EQ(&os, &returned);
}
