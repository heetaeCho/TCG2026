#include <gtest/gtest.h>
#include <sstream>
#include <memory>

#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/types.hpp"

// Include the internal header for CanonMakerNote
// Adjust path as needed based on project structure
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNotePrintSi0x000eTest_959 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test: When value type is not unsignedShort, should print raw value
TEST_F(CanonMakerNotePrintSi0x000eTest_959, NonUnsignedShortType_PrintsRawValue_959) {
  auto value = Value::create(signedShort);
  value->read("42");
  CanonMakerNote::printSi0x000e(os, *value, nullptr);
  // Should just print the value as-is since typeId != unsignedShort
  EXPECT_FALSE(os.str().empty());
}

// Test: When value type is unsignedShort with count == 0, should print raw value
TEST_F(CanonMakerNotePrintSi0x000eTest_959, EmptyUnsignedShort_PrintsRawValue_959) {
  auto value = Value::create(unsignedShort);
  // Don't read any data, count should be 0
  CanonMakerNote::printSi0x000e(os, *value, nullptr);
  // With count == 0, it should fall into the early return path
  std::string result = os.str();
  // The output should be whatever value.operator<< produces
  EXPECT_TRUE(result.find("focus points") == std::string::npos);
}

// Test: Value 0x0000 - 0 focus points, none used
TEST_F(CanonMakerNotePrintSi0x000eTest_959, ZeroValue_ZeroFocusPointsNoneUsed_959) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  CanonMakerNote::printSi0x000e(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("0 focus points"), std::string::npos);
  EXPECT_NE(result.find("none"), std::string::npos);
  EXPECT_NE(result.find("used"), std::string::npos);
}

// Test: Value 0x1000 - 1 focus point, none used
TEST_F(CanonMakerNotePrintSi0x000eTest_959, OneFocusPointNoneUsed_959) {
  auto value = Value::create(unsignedShort);
  // 0x1000 = 4096 decimal; num = (0x1000 & 0xf000) >> 12 = 1; used = 0x1000 & 0x0fff = 0
  value->read("4096");
  CanonMakerNote::printSi0x000e(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("1 focus points"), std::string::npos);
  EXPECT_NE(result.find("none"), std::string::npos);
  EXPECT_NE(result.find("used"), std::string::npos);
}

// Test: Value 0x3002 - 3 focus points, center used
TEST_F(CanonMakerNotePrintSi0x000eTest_959, ThreeFocusPointsCenterUsed_959) {
  auto value = Value::create(unsignedShort);
  // 0x3002 = 12290 decimal; num = (0x3002 & 0xf000) >> 12 = 3; used = 0x3002 & 0x0fff = 2
  // Bitmask 2 => "center"
  value->read("12290");
  CanonMakerNote::printSi0x000e(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("3 focus points"), std::string::npos);
  EXPECT_NE(result.find("center"), std::string::npos);
  EXPECT_NE(result.find("used"), std::string::npos);
}

// Test: Value 0x3004 - 3 focus points, left used
TEST_F(CanonMakerNotePrintSi0x000eTest_959, ThreeFocusPointsLeftUsed_959) {
  auto value = Value::create(unsignedShort);
  // 0x3004 = 12292 decimal; num = 3; used = 4 => bitmask 4 = "left"
  value->read("12292");
  CanonMakerNote::printSi0x000e(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("3 focus points"), std::string::npos);
  EXPECT_NE(result.find("left"), std::string::npos);
  EXPECT_NE(result.find("used"), std::string::npos);
}

// Test: Value 0x3001 - 3 focus points, right used
TEST_F(CanonMakerNotePrintSi0x000eTest_959, ThreeFocusPointsRightUsed_959) {
  auto value = Value::create(unsignedShort);
  // 0x3001 = 12289 decimal; num = 3; used = 1 => bitmask 1 = "right"
  value->read("12289");
  CanonMakerNote::printSi0x000e(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("3 focus points"), std::string::npos);
  EXPECT_NE(result.find("right"), std::string::npos);
  EXPECT_NE(result.find("used"), std::string::npos);
}

// Test: Value 0x3007 - 3 focus points, all three used (left, center, right)
TEST_F(CanonMakerNotePrintSi0x000eTest_959, ThreeFocusPointsAllUsed_959) {
  auto value = Value::create(unsignedShort);
  // 0x3007 = 12295 decimal; num = 3; used = 7 => bitmask 4|2|1 = left, center, right
  value->read("12295");
  CanonMakerNote::printSi0x000e(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("3 focus points"), std::string::npos);
  EXPECT_NE(result.find("left"), std::string::npos);
  EXPECT_NE(result.find("center"), std::string::npos);
  EXPECT_NE(result.find("right"), std::string::npos);
  EXPECT_NE(result.find("used"), std::string::npos);
}

// Test: Value 0x3006 - 3 focus points, left and center used
TEST_F(CanonMakerNotePrintSi0x000eTest_959, ThreeFocusPointsLeftAndCenterUsed_959) {
  auto value = Value::create(unsignedShort);
  // 0x3006 = 12294 decimal; num = 3; used = 6 => bitmask 4|2 = left, center
  value->read("12294");
  CanonMakerNote::printSi0x000e(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("3 focus points"), std::string::npos);
  EXPECT_NE(result.find("left"), std::string::npos);
  EXPECT_NE(result.find("center"), std::string::npos);
  EXPECT_NE(result.find("used"), std::string::npos);
}

// Test: Max focus points value 0xF000 - 15 focus points, none used
TEST_F(CanonMakerNotePrintSi0x000eTest_959, MaxFocusPointsNoneUsed_959) {
  auto value = Value::create(unsignedShort);
  // 0xF000 = 61440 decimal; num = 15; used = 0
  value->read("61440");
  CanonMakerNote::printSi0x000e(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("15 focus points"), std::string::npos);
  EXPECT_NE(result.find("none"), std::string::npos);
  EXPECT_NE(result.find("used"), std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(CanonMakerNotePrintSi0x000eTest_959, ReturnsSameOstream_959) {
  auto value = Value::create(unsignedShort);
  value->read("12290");
  std::ostream& ret = CanonMakerNote::printSi0x000e(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// Test: With non-unsignedShort type, return value is the same ostream reference
TEST_F(CanonMakerNotePrintSi0x000eTest_959, NonUnsignedShortReturnsSameOstream_959) {
  auto value = Value::create(unsignedLong);
  value->read("42");
  std::ostream& ret = CanonMakerNote::printSi0x000e(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// Test: Passing nullptr for ExifData with used AF points
TEST_F(CanonMakerNotePrintSi0x000eTest_959, NullExifDataWithUsedPoints_959) {
  auto value = Value::create(unsignedShort);
  // 0x1002 = 4098 decimal; num = 1; used = 2 => center
  value->read("4098");
  // Should not crash with nullptr ExifData
  EXPECT_NO_THROW(CanonMakerNote::printSi0x000e(os, *value, nullptr));
  std::string result = os.str();
  EXPECT_NE(result.find("1 focus points"), std::string::npos);
  EXPECT_NE(result.find("used"), std::string::npos);
}

// Test: Value with asciiString type should print raw value
TEST_F(CanonMakerNotePrintSi0x000eTest_959, AsciiStringType_PrintsRawValue_959) {
  auto value = Value::create(asciiString);
  value->read("hello");
  CanonMakerNote::printSi0x000e(os, *value, nullptr);
  std::string result = os.str();
  // Should not contain "focus points" since type is wrong
  EXPECT_NE(result.find("hello"), std::string::npos);
}

// Test: Value 0x0001 - 0 focus points, right used (boundary: num=0 but points used)
TEST_F(CanonMakerNotePrintSi0x000eTest_959, ZeroFocusPointsButRightUsed_959) {
  auto value = Value::create(unsignedShort);
  // 0x0001 = 1 decimal; num = 0; used = 1 => right
  value->read("1");
  CanonMakerNote::printSi0x000e(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("0 focus points"), std::string::npos);
  EXPECT_NE(result.find("right"), std::string::npos);
  EXPECT_NE(result.find("used"), std::string::npos);
  // "none" should NOT appear
  EXPECT_EQ(result.find("none"), std::string::npos);
}

// Test: With valid ExifData pointer (non-null)
TEST_F(CanonMakerNotePrintSi0x000eTest_959, ValidExifDataPointer_959) {
  ExifData exifData;
  auto value = Value::create(unsignedShort);
  // 0x3002 = 12290
  value->read("12290");
  EXPECT_NO_THROW(CanonMakerNote::printSi0x000e(os, *value, &exifData));
  std::string result = os.str();
  EXPECT_NE(result.find("3 focus points"), std::string::npos);
  EXPECT_NE(result.find("used"), std::string::npos);
}

// Test: Value with used bits set but not matching any known bitmask entry
TEST_F(CanonMakerNotePrintSi0x000eTest_959, UnknownBitmaskBits_959) {
  auto value = Value::create(unsignedShort);
  // 0x1008 = 4104 decimal; num = 1; used = 8 => bit 3, which is not in the bitmask table
  value->read("4104");
  EXPECT_NO_THROW(CanonMakerNote::printSi0x000e(os, *value, nullptr));
  std::string result = os.str();
  EXPECT_NE(result.find("1 focus points"), std::string::npos);
  EXPECT_NE(result.find("used"), std::string::npos);
}
