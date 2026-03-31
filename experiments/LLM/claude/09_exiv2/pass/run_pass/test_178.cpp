#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "tags_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Define test StringTagDetails arrays for testing
static const StringTagDetails testStringTags[] = {
    {"alpha", "Alpha Label"},
    {"beta", "Beta Label"},
    {"gamma", "Gamma Label"},
};

static const StringTagDetails singleElementArray[] = {
    {"only", "Only Element"},
};

// Test fixture
class PrintTagStringTest_178 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test: When a matching string value is found in the array, the label is printed
TEST_F(PrintTagStringTest_178, MatchingStringValue_PrintsLabel_178) {
  std::string value = "alpha";
  printTagString<3, testStringTags>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Alpha Label");
}

// Test: When a matching string value "beta" is found, the correct label is printed
TEST_F(PrintTagStringTest_178, MatchingSecondElement_PrintsLabel_178) {
  std::string value = "beta";
  printTagString<3, testStringTags>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Beta Label");
}

// Test: When a matching string value "gamma" is found, the correct label is printed
TEST_F(PrintTagStringTest_178, MatchingThirdElement_PrintsLabel_178) {
  std::string value = "gamma";
  printTagString<3, testStringTags>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Gamma Label");
}

// Test: When no matching string value is found, the value is printed in parentheses
TEST_F(PrintTagStringTest_178, NonMatchingStringValue_PrintsValueInParens_178) {
  std::string value = "unknown";
  printTagString<3, testStringTags>(os, value, nullptr);
  EXPECT_EQ(os.str(), "(unknown)");
}

// Test: Empty string does not match any entry
TEST_F(PrintTagStringTest_178, EmptyStringValue_PrintsValueInParens_178) {
  std::string value = "";
  printTagString<3, testStringTags>(os, value, nullptr);
  EXPECT_EQ(os.str(), "()");
}

// Test: Single element array - matching value
TEST_F(PrintTagStringTest_178, SingleElementArray_MatchingValue_178) {
  std::string value = "only";
  printTagString<1, singleElementArray>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Only Element");
}

// Test: Single element array - non-matching value
TEST_F(PrintTagStringTest_178, SingleElementArray_NonMatchingValue_178) {
  std::string value = "none";
  printTagString<1, singleElementArray>(os, value, nullptr);
  EXPECT_EQ(os.str(), "(none)");
}

// Test: Case sensitivity - "Alpha" should not match "alpha"
TEST_F(PrintTagStringTest_178, CaseSensitivity_NoMatch_178) {
  std::string value = "Alpha";
  printTagString<3, testStringTags>(os, value, nullptr);
  EXPECT_EQ(os.str(), "(Alpha)");
}

// Test: With Exiv2::Value type - matching value
TEST_F(PrintTagStringTest_178, ValueType_MatchingValue_178) {
  auto value = Exiv2::Value::create(Exiv2::asciiString);
  value->read("alpha");
  printTagString<3, testStringTags>(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Alpha Label");
}

// Test: With Exiv2::Value type - non-matching value
TEST_F(PrintTagStringTest_178, ValueType_NonMatchingValue_178) {
  auto value = Exiv2::Value::create(Exiv2::asciiString);
  value->read("notfound");
  printTagString<3, testStringTags>(os, *value, nullptr);
  // Should contain parentheses around the value
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: ExifData pointer is nullptr - function should still work
TEST_F(PrintTagStringTest_178, NullExifData_StillWorks_178) {
  std::string value = "beta";
  printTagString<3, testStringTags>(os, value, nullptr);
  EXPECT_EQ(os.str(), "Beta Label");
}

// Test: Whitespace string value - no match expected
TEST_F(PrintTagStringTest_178, WhitespaceStringValue_NoMatch_178) {
  std::string value = " alpha";
  printTagString<3, testStringTags>(os, value, nullptr);
  EXPECT_EQ(os.str(), "( alpha)");
}
