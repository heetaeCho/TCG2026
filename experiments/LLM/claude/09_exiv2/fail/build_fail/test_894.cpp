#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "olympusmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// =============================================================================
// Tests for tagListRi()
// =============================================================================

TEST(OlympusMakerNoteTest_894, TagListRiReturnsNonNull_894) {
  auto tagList = OlympusMakerNote::tagListRi();
  ASSERT_NE(tagList, nullptr);
}

TEST(OlympusMakerNoteTest_894, TagListRiFirstEntryHasValidTag_894) {
  auto tagList = OlympusMakerNote::tagListRi();
  ASSERT_NE(tagList, nullptr);
  // The first entry should have a valid tag number (non-negative typically)
  // and a non-null title
  EXPECT_NE(tagList[0].title_, nullptr);
}

TEST(OlympusMakerNoteTest_894, TagListRiConsistentAcrossCalls_894) {
  auto tagList1 = OlympusMakerNote::tagListRi();
  auto tagList2 = OlympusMakerNote::tagListRi();
  EXPECT_EQ(tagList1, tagList2);
}

// =============================================================================
// Tests for tagList()
// =============================================================================

TEST(OlympusMakerNoteTest_894, TagListReturnsNonNull_894) {
  auto tagList = OlympusMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST(OlympusMakerNoteTest_894, TagListFirstEntryValid_894) {
  auto tagList = OlympusMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  EXPECT_NE(tagList[0].title_, nullptr);
}

// =============================================================================
// Tests for tagListCs()
// =============================================================================

TEST(OlympusMakerNoteTest_894, TagListCsReturnsNonNull_894) {
  auto tagList = OlympusMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for tagListEq()
// =============================================================================

TEST(OlympusMakerNoteTest_894, TagListEqReturnsNonNull_894) {
  auto tagList = OlympusMakerNote::tagListEq();
  ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for tagListRd()
// =============================================================================

TEST(OlympusMakerNoteTest_894, TagListRdReturnsNonNull_894) {
  auto tagList = OlympusMakerNote::tagListRd();
  ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for tagListRd2()
// =============================================================================

TEST(OlympusMakerNoteTest_894, TagListRd2ReturnsNonNull_894) {
  auto tagList = OlympusMakerNote::tagListRd2();
  ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for tagListIp()
// =============================================================================

TEST(OlympusMakerNoteTest_894, TagListIpReturnsNonNull_894) {
  auto tagList = OlympusMakerNote::tagListIp();
  ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for tagListFi()
// =============================================================================

TEST(OlympusMakerNoteTest_894, TagListFiReturnsNonNull_894) {
  auto tagList = OlympusMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for tagListFe()
// =============================================================================

TEST(OlympusMakerNoteTest_894, TagListFeReturnsNonNull_894) {
  auto tagList = OlympusMakerNote::tagListFe();
  ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for print0x0200 (Quality)
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x0200WithSingleValue_894) {
  std::ostringstream os;
  UShortValue value;
  value.read(reinterpret_cast<const byte*>("\x01\x00"), 2, littleEndian);
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_894, Print0x0200WithEmptyValue_894) {
  std::ostringstream os;
  UShortValue value;
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  // Should produce some output even for empty value
}

// =============================================================================
// Tests for print0x0204 (Compression Ratio)
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x0204WithRationalValue_894) {
  std::ostringstream os;
  URationalValue value;
  URational r(30, 10);
  value.value_.push_back(r);
  OlympusMakerNote::print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_894, Print0x0204WithEmptyValue_894) {
  std::ostringstream os;
  URationalValue value;
  OlympusMakerNote::print0x0204(os, value, nullptr);
  std::string result = os.str();
}

// =============================================================================
// Tests for print0x1015 (White Balance)
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x1015WithKnownValue_894) {
  std::ostringstream os;
  UShortValue value;
  // 0 typically means "Auto"
  value.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
  OlympusMakerNote::print0x1015(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for print0x0201
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x0201WithMultipleValues_894) {
  std::ostringstream os;
  UShortValue value;
  // Provide some values
  byte data[] = {0x00, 0x00, 0x01, 0x00};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::print0x0201(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for print0x0209 (Camera ID)
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x0209WithEmptyValue_894) {
  std::ostringstream os;
  ULongValue value;
  OlympusMakerNote::print0x0209(os, value, nullptr);
  std::string result = os.str();
}

// =============================================================================
// Tests for printEq0x0301 (Equipment Lens Type)
// =============================================================================

TEST(OlympusMakerNoteTest_894, PrintEq0x0301WithValue_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::printEq0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printCs0x0301 (Camera Settings Exposure Mode)
// =============================================================================

TEST(OlympusMakerNoteTest_894, PrintCs0x0301WithKnownValue_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0x01, 0x00};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::printCs0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for print0x050f
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x050fWithValue_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0x01, 0x00};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::print0x050f(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for print0x0527
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x0527WithValue_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0x01, 0x00};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::print0x0527(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for print0x0529
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x0529WithEmptyValue_894) {
  std::ostringstream os;
  UShortValue value;
  OlympusMakerNote::print0x0529(os, value, nullptr);
  std::string result = os.str();
}

TEST(OlympusMakerNoteTest_894, Print0x0529WithValue_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0x01, 0x00};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::print0x0529(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for print0x1209
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x1209WithValue_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0x00, 0x00};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::print0x1209(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for print0x0305
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x0305WithValue_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0x00, 0x00};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::print0x0305(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for print0x0308
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x0308WithEmptyValue_894) {
  std::ostringstream os;
  UShortValue value;
  OlympusMakerNote::print0x0308(os, value, nullptr);
  std::string result = os.str();
}

TEST(OlympusMakerNoteTest_894, Print0x0308WithValue_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0x01, 0x00};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::print0x0308(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printGeneric
// =============================================================================

TEST(OlympusMakerNoteTest_894, PrintGenericWithSingleValue_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0x05, 0x00};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::printGeneric(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_894, PrintGenericWithMultipleValues_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0x01, 0x00, 0x02, 0x00, 0x03, 0x00};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::printGeneric(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_894, PrintGenericWithEmptyValue_894) {
  std::ostringstream os;
  UShortValue value;
  OlympusMakerNote::printGeneric(os, value, nullptr);
  std::string result = os.str();
}

// =============================================================================
// Tests for print functions returning ostream reference
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x0200ReturnsOstream_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0x01, 0x00};
  value.read(data, sizeof(data), littleEndian);
  std::ostream& result = OlympusMakerNote::print0x0200(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST(OlympusMakerNoteTest_894, Print0x0204ReturnsOstream_894) {
  std::ostringstream os;
  URationalValue value;
  URational r(10, 5);
  value.value_.push_back(r);
  std::ostream& result = OlympusMakerNote::print0x0204(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST(OlympusMakerNoteTest_894, PrintGenericReturnsOstream_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0x01, 0x00};
  value.read(data, sizeof(data), littleEndian);
  std::ostream& result = OlympusMakerNote::printGeneric(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Boundary tests
// =============================================================================

TEST(OlympusMakerNoteTest_894, Print0x0200WithLargeCount_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[20] = {};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  // Should handle multiple values without crashing
}

TEST(OlympusMakerNoteTest_894, Print0x1015WithUnknownValue_894) {
  std::ostringstream os;
  UShortValue value;
  // Use a presumably unknown/unrecognized white balance value
  byte data[] = {0xFF, 0xFF};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::print0x1015(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_894, PrintCs0x0301WithUnknownValue_894) {
  std::ostringstream os;
  UShortValue value;
  byte data[] = {0xFF, 0xFF};
  value.read(data, sizeof(data), littleEndian);
  OlympusMakerNote::printCs0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tag list last entry sentinel check
// =============================================================================

TEST(OlympusMakerNoteTest_894, TagListRiHasSentinelEntry_894) {
  auto tagList = OlympusMakerNote::tagListRi();
  ASSERT_NE(tagList, nullptr);
  // Walk through the tag list to find the sentinel (tag == 0xffff typically)
  // We just verify we can iterate without crash up to a reasonable limit
  int count = 0;
  while (tagList[count].tag_ != 0xffff && count < 10000) {
    count++;
  }
  EXPECT_LT(count, 10000) << "Tag list seems to lack a sentinel entry";
}

TEST(OlympusMakerNoteTest_894, TagListHasSentinelEntry_894) {
  auto tagList = OlympusMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  int count = 0;
  while (tagList[count].tag_ != 0xffff && count < 10000) {
    count++;
  }
  EXPECT_LT(count, 10000) << "Tag list seems to lack a sentinel entry";
}
