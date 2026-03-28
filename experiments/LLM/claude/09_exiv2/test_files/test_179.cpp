#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "tags_int.hpp"
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Define a simple StringTagDetails array for testing
// We need to know the structure of StringTagDetails to create test arrays.
// Based on typical exiv2 patterns, StringTagDetails has a key string and a label string.

namespace {

// We'll define test arrays that printTagString2 can use.
// StringTagDetails typically has: { const char* val; const char* label; }
const StringTagDetails testStringTags[] = {
    {"1 2", "Tag_1_2"},
    {"3 4", "Tag_3_4"},
    {"0 0", "Tag_0_0"},
    {"255 255", "Tag_255_255"},
};

const StringTagDetails singleEntryTags[] = {
    {"1 2", "SingleEntry"},
};

}  // namespace

class PrintTagString2Test_179 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: When value has count < 2 (count == 0), should print "(" + value + ")"
TEST_F(PrintTagString2Test_179, EmptyValuePrintsParenthesized_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  // Don't read anything - count should be 0
  printTagString2<4, testStringTags>(os, *value, nullptr);
  std::string result = os.str();
  // Should contain parentheses since count < 2
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value has count == 1, should print "(" + value + ")"
TEST_F(PrintTagString2Test_179, SingleValuePrintsParenthesized_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  // Read a single value
  uint16_t data = 5;
  value->read(reinterpret_cast<const byte*>(&data), sizeof(data), littleEndian);
  // count should be 1
  EXPECT_EQ(value->count(), 1u);
  printTagString2<4, testStringTags>(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value has count >= 2 and matches a tag, should print the tag label
TEST_F(PrintTagString2Test_179, TwoValuesMatchingTagPrintsLabel_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  // Read two values: 1 and 2, which should form "1 2" matching testStringTags[0]
  uint16_t data[2] = {1, 2};
  value->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
  EXPECT_EQ(value->count(), 2u);
  printTagString2<4, testStringTags>(os, *value, nullptr);
  std::string result = os.str();
  // Should find "Tag_1_2" in the output
  EXPECT_NE(result.find("Tag_1_2"), std::string::npos);
}

// Test: When value has count >= 2 but doesn't match any tag
TEST_F(PrintTagString2Test_179, TwoValuesNotMatchingTagPrintsValue_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  // Read two values: 99 and 99, which should form "99 99" - not in array
  uint16_t data[2] = {99, 99};
  value->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
  EXPECT_EQ(value->count(), 2u);
  printTagString2<4, testStringTags>(os, *value, nullptr);
  std::string result = os.str();
  // Should NOT find any of our defined labels
  EXPECT_EQ(result.find("Tag_1_2"), std::string::npos);
  EXPECT_EQ(result.find("Tag_3_4"), std::string::npos);
}

// Test: Second matching entry in the array
TEST_F(PrintTagString2Test_179, TwoValuesMatchingSecondTag_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  uint16_t data[2] = {3, 4};
  value->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
  EXPECT_EQ(value->count(), 2u);
  printTagString2<4, testStringTags>(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Tag_3_4"), std::string::npos);
}

// Test: Values 0 0 match the third entry
TEST_F(PrintTagString2Test_179, ZeroZeroMatchesTag_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  uint16_t data[2] = {0, 0};
  value->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
  EXPECT_EQ(value->count(), 2u);
  printTagString2<4, testStringTags>(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Tag_0_0"), std::string::npos);
}

// Test: With single entry array
TEST_F(PrintTagString2Test_179, SingleEntryArrayMatches_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  uint16_t data[2] = {1, 2};
  value->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
  EXPECT_EQ(value->count(), 2u);
  printTagString2<1, singleEntryTags>(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("SingleEntry"), std::string::npos);
}

// Test: With single entry array, no match
TEST_F(PrintTagString2Test_179, SingleEntryArrayNoMatch_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  uint16_t data[2] = {5, 6};
  value->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
  EXPECT_EQ(value->count(), 2u);
  printTagString2<1, singleEntryTags>(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.find("SingleEntry"), std::string::npos);
}

// Test: More than 2 values - should still use first two for lookup
TEST_F(PrintTagString2Test_179, MoreThanTwoValuesUsesFirstTwo_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  uint16_t data[3] = {1, 2, 99};
  value->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
  EXPECT_GE(value->count(), 2u);
  printTagString2<4, testStringTags>(os, *value, nullptr);
  std::string result = os.str();
  // Should match "1 2" from first two values
  EXPECT_NE(result.find("Tag_1_2"), std::string::npos);
}

// Test: Boundary - values 255 255 matching last entry
TEST_F(PrintTagString2Test_179, BoundaryValues255Match_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  uint16_t data[2] = {255, 255};
  value->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
  EXPECT_EQ(value->count(), 2u);
  printTagString2<4, testStringTags>(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Tag_255_255"), std::string::npos);
}

// Test: nullptr ExifData should still work
TEST_F(PrintTagString2Test_179, NullExifDataWorks_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  uint16_t data[2] = {1, 2};
  value->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
  // Should not crash with nullptr
  EXPECT_NO_THROW(printTagString2<4, testStringTags>(os, *value, nullptr));
}

// Test: Return value is reference to the same ostream
TEST_F(PrintTagString2Test_179, ReturnsReferenceToSameStream_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  uint16_t data[2] = {1, 2};
  value->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
  std::ostream& ret = printTagString2<4, testStringTags>(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// Test: Return value is reference to same stream for count < 2 case
TEST_F(PrintTagString2Test_179, ReturnsReferenceToSameStreamForSmallCount_179) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  // Empty value, count = 0
  std::ostream& ret = printTagString2<4, testStringTags>(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// Test: Using string type values
TEST_F(PrintTagString2Test_179, StringTypeValueWithCountLessThanTwo_179) {
  std::ostringstream os;
  auto value = Value::create(asciiString);
  value->read("A");
  // ASCII string - count depends on implementation
  // If count < 2, should get parenthesized output
  printTagString2<4, testStringTags>(os, *value, nullptr);
  std::string result = os.str();
  // Just ensure it doesn't crash and produces some output
  EXPECT_FALSE(result.empty());
}
