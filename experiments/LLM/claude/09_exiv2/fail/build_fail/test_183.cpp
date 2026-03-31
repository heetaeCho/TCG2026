#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

#include "exiv2/exiv2.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Define TagDetails arrays for testing
static const TagDetails testTagDetails1[] = {
    {0, "Zero"},
    {1, "One"},
    {2, "Two"},
    {3, "Three"},
};

static const TagDetails testTagDetails2[] = {
    {42, "FortyTwo"},
};

static const TagDetails testTagDetails3[] = {
    {-1, "NegativeOne"},
    {0, "Zero"},
    {100, "Hundred"},
    {255, "TwoFiftyFive"},
    {1000, "Thousand"},
};

class PrintTagTest_183 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test that a known value in the tag details array prints the correct label
TEST_F(PrintTagTest_183, KnownValuePrintsLabel_183) {
  auto value = Value::create(unsignedLong);
  value->read("1");
  
  printTag<4, testTagDetails1>(os, *value, nullptr);
  
  EXPECT_NE(os.str().find("One"), std::string::npos);
}

// Test that value 0 maps correctly
TEST_F(PrintTagTest_183, ZeroValuePrintsCorrectLabel_183) {
  auto value = Value::create(unsignedLong);
  value->read("0");
  
  printTag<4, testTagDetails1>(os, *value, nullptr);
  
  EXPECT_NE(os.str().find("Zero"), std::string::npos);
}

// Test with a single-element array
TEST_F(PrintTagTest_183, SingleElementArrayKnownValue_183) {
  auto value = Value::create(unsignedLong);
  value->read("42");
  
  printTag<1, testTagDetails2>(os, *value, nullptr);
  
  EXPECT_NE(os.str().find("FortyTwo"), std::string::npos);
}

// Test with an unknown value (not in the array)
TEST_F(PrintTagTest_183, UnknownValuePrintsSomething_183) {
  auto value = Value::create(unsignedLong);
  value->read("999");
  
  printTag<4, testTagDetails1>(os, *value, nullptr);
  
  // Should produce some output (either "(999)" or the numeric value)
  EXPECT_FALSE(os.str().empty());
}

// Test with negative value in the details
TEST_F(PrintTagTest_183, NegativeValueInArray_183) {
  auto value = Value::create(signedLong);
  value->read("-1");
  
  printTag<5, testTagDetails3>(os, *value, nullptr);
  
  EXPECT_NE(os.str().find("NegativeOne"), std::string::npos);
}

// Test with a large value in the details
TEST_F(PrintTagTest_183, LargeValueInArray_183) {
  auto value = Value::create(unsignedLong);
  value->read("1000");
  
  printTag<5, testTagDetails3>(os, *value, nullptr);
  
  EXPECT_NE(os.str().find("Thousand"), std::string::npos);
}

// Test that the last element in the array is found
TEST_F(PrintTagTest_183, LastElementInArray_183) {
  auto value = Value::create(unsignedLong);
  value->read("3");
  
  printTag<4, testTagDetails1>(os, *value, nullptr);
  
  EXPECT_NE(os.str().find("Three"), std::string::npos);
}

// Test with nullptr ExifData (should not crash)
TEST_F(PrintTagTest_183, NullExifDataDoesNotCrash_183) {
  auto value = Value::create(unsignedLong);
  value->read("2");
  
  EXPECT_NO_THROW(printTag<4, testTagDetails1>(os, *value, nullptr));
}

// Test that the function returns the ostream reference
TEST_F(PrintTagTest_183, ReturnsOstreamReference_183) {
  auto value = Value::create(unsignedLong);
  value->read("1");
  
  std::ostream& result = printTag<4, testTagDetails1>(os, *value, nullptr);
  
  EXPECT_EQ(&result, &os);
}

// Test with ExifData object (non-null)
TEST_F(PrintTagTest_183, NonNullExifData_183) {
  ExifData exifData;
  auto value = Value::create(unsignedLong);
  value->read("2");
  
  EXPECT_NO_THROW(printTag<4, testTagDetails1>(os, *value, &exifData));
  EXPECT_NE(os.str().find("Two"), std::string::npos);
}

// Test with value that doesn't match single-element array
TEST_F(PrintTagTest_183, SingleElementArrayUnknownValue_183) {
  auto value = Value::create(unsignedLong);
  value->read("0");
  
  printTag<1, testTagDetails2>(os, *value, nullptr);
  
  // The output should contain something (either unknown marker or the numeric value)
  EXPECT_FALSE(os.str().empty());
}

// Test with signed short value type
TEST_F(PrintTagTest_183, SignedShortValueType_183) {
  auto value = Value::create(signedShort);
  value->read("100");
  
  printTag<5, testTagDetails3>(os, *value, nullptr);
  
  EXPECT_NE(os.str().find("Hundred"), std::string::npos);
}

// Test with unsigned short value type  
TEST_F(PrintTagTest_183, UnsignedShortValueType_183) {
  auto value = Value::create(unsignedShort);
  value->read("255");
  
  printTag<5, testTagDetails3>(os, *value, nullptr);
  
  EXPECT_NE(os.str().find("TwoFiftyFive"), std::string::npos);
}
