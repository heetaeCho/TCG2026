#include <gtest/gtest.h>
#include <sstream>

// Include necessary Exiv2 headers
#include "casiomn_int.hpp"
#include "tags_int.hpp"
#include "value.hpp"
#include "exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test that tagList returns a non-null pointer
TEST(CasioMakerNoteTest_1352, TagListReturnsNonNull_1352) {
  auto tagList = CasioMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagList returns a valid tag info array with known first entry
TEST(CasioMakerNoteTest_1352, TagListFirstEntryValid_1352) {
  auto tagList = CasioMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  // The first entry should have a valid tag (non-negative typically)
  // We just verify it's accessible without crashing
  auto firstTag = tagList[0];
  // TagInfo typically has a tag_ member; just access it
  (void)firstTag;
}

// Test that tagList is consistent across multiple calls
TEST(CasioMakerNoteTest_1352, TagListConsistentAcrossCalls_1352) {
  auto tagList1 = CasioMakerNote::tagList();
  auto tagList2 = CasioMakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

// Test print0x0006 with a valid value
TEST(CasioMakerNoteTest_1352, Print0x0006WithValidValue_1352) {
  std::ostringstream os;
  ULongValue value;
  value.read("0");
  std::ostream& result = CasioMakerNote::print0x0006(os, value, nullptr);
  // Should produce some output and return the same stream
  EXPECT_EQ(&result, &os);
}

// Test print0x0006 with different values
TEST(CasioMakerNoteTest_1352, Print0x0006WithMultipleValues_1352) {
  std::ostringstream os1;
  ULongValue value1;
  value1.read("1");
  CasioMakerNote::print0x0006(os1, value1, nullptr);
  std::string output1 = os1.str();

  std::ostringstream os2;
  ULongValue value2;
  value2.read("2");
  CasioMakerNote::print0x0006(os2, value2, nullptr);
  std::string output2 = os2.str();

  // Different input values may produce different output
  // At minimum, both should produce non-empty output or at least not crash
  EXPECT_FALSE(output1.empty());
  EXPECT_FALSE(output2.empty());
}

// Test print0x0006 with out of range value
TEST(CasioMakerNoteTest_1352, Print0x0006WithOutOfRangeValue_1352) {
  std::ostringstream os;
  ULongValue value;
  value.read("99999");
  std::ostream& result = CasioMakerNote::print0x0006(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Should still produce some output (possibly "Unknown" or the numeric value)
  EXPECT_FALSE(os.str().empty());
}

// Test print0x0015 with a valid value
TEST(CasioMakerNoteTest_1352, Print0x0015WithValidValue_1352) {
  std::ostringstream os;
  ULongValue value;
  value.read("0");
  std::ostream& result = CasioMakerNote::print0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x0015 with different values
TEST(CasioMakerNoteTest_1352, Print0x0015WithMultipleValues_1352) {
  std::ostringstream os1;
  ULongValue value1;
  value1.read("1");
  CasioMakerNote::print0x0015(os1, value1, nullptr);
  std::string output1 = os1.str();

  std::ostringstream os2;
  ULongValue value2;
  value2.read("2");
  CasioMakerNote::print0x0015(os2, value2, nullptr);
  std::string output2 = os2.str();

  EXPECT_FALSE(output1.empty());
  EXPECT_FALSE(output2.empty());
}

// Test print0x0015 with out of range value
TEST(CasioMakerNoteTest_1352, Print0x0015WithOutOfRangeValue_1352) {
  std::ostringstream os;
  ULongValue value;
  value.read("99999");
  std::ostream& result = CasioMakerNote::print0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test print0x0015 with nullptr ExifData
TEST(CasioMakerNoteTest_1352, Print0x0015WithNullExifData_1352) {
  std::ostringstream os;
  ULongValue value;
  value.read("0");
  // Should not crash with nullptr ExifData
  CasioMakerNote::print0x0015(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// Test print0x0006 with nullptr ExifData
TEST(CasioMakerNoteTest_1352, Print0x0006WithNullExifData_1352) {
  std::ostringstream os;
  ULongValue value;
  value.read("0");
  // Should not crash with nullptr ExifData
  CasioMakerNote::print0x0006(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// Test that tagList entries are terminated properly
// (TagInfo arrays typically end with a sentinel entry)
TEST(CasioMakerNoteTest_1352, TagListHasTerminator_1352) {
  auto tagList = CasioMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  // Iterate until we find a sentinel (tag == 0xffff or similar pattern)
  // We limit iteration to prevent infinite loop
  int count = 0;
  const int maxTags = 1000;
  while (count < maxTags) {
    if (tagList[count].tag_ == 0xffff) {
      break;
    }
    count++;
  }
  // Should have found a terminator within reasonable bounds
  EXPECT_LT(count, maxTags);
}
