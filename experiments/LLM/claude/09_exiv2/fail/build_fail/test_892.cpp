#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "olympusmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// ============================================================
// Tests for tagListFi()
// ============================================================

TEST(OlympusMakerNoteTest_892, TagListFiReturnsNonNull_892) {
  auto tagList = OlympusMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST(OlympusMakerNoteTest_892, TagListFiFirstEntryHasValidTag_892) {
  auto tagList = OlympusMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
  // The first entry should have a valid tag number (non-negative typically)
  // and a non-null title
  EXPECT_NE(tagList[0].title_, nullptr);
}

// ============================================================
// Tests for tagList()
// ============================================================

TEST(OlympusMakerNoteTest_892, TagListReturnsNonNull_892) {
  auto tagList = OlympusMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST(OlympusMakerNoteTest_892, TagListFirstEntryHasValidTitle_892) {
  auto tagList = OlympusMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  EXPECT_NE(tagList[0].title_, nullptr);
}

// ============================================================
// Tests for tagListCs()
// ============================================================

TEST(OlympusMakerNoteTest_892, TagListCsReturnsNonNull_892) {
  auto tagList = OlympusMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListEq()
// ============================================================

TEST(OlympusMakerNoteTest_892, TagListEqReturnsNonNull_892) {
  auto tagList = OlympusMakerNote::tagListEq();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListRd()
// ============================================================

TEST(OlympusMakerNoteTest_892, TagListRdReturnsNonNull_892) {
  auto tagList = OlympusMakerNote::tagListRd();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListRd2()
// ============================================================

TEST(OlympusMakerNoteTest_892, TagListRd2ReturnsNonNull_892) {
  auto tagList = OlympusMakerNote::tagListRd2();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListIp()
// ============================================================

TEST(OlympusMakerNoteTest_892, TagListIpReturnsNonNull_892) {
  auto tagList = OlympusMakerNote::tagListIp();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListFe()
// ============================================================

TEST(OlympusMakerNoteTest_892, TagListFeReturnsNonNull_892) {
  auto tagList = OlympusMakerNote::tagListFe();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListRi()
// ============================================================

TEST(OlympusMakerNoteTest_892, TagListRiReturnsNonNull_892) {
  auto tagList = OlympusMakerNote::tagListRi();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print0x0200 (Quality)
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x0200WithSingleValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("1");
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_892, Print0x0200WithMultipleValues_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0 1 2");
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0204 (DigitalZoom)
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x0204WithZeroValue_892) {
  std::ostringstream os;
  URationalValue value;
  value.read("0/1");
  OlympusMakerNote::print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_892, Print0x0204WithNonZeroValue_892) {
  std::ostringstream os;
  URationalValue value;
  value.read("200/100");
  OlympusMakerNote::print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x1015 (WhiteBalance)
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x1015WithSingleValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x1015(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_892, Print0x1015WithTwoValues_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("1 0");
  OlympusMakerNote::print0x1015(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0201
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x0201WithSingleValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0201(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_892, Print0x0201WithMultipleValues_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0 1");
  OlympusMakerNote::print0x0201(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0209 (CameraID)
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x0209WithAsciiValue_892) {
  std::ostringstream os;
  AsciiValue value;
  value.read("OLYMPUS DIGITAL CAMERA");
  OlympusMakerNote::print0x0209(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printEq0x0301
// ============================================================

TEST(OlympusMakerNoteTest_892, PrintEq0x0301WithValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::printEq0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printCs0x0301
// ============================================================

TEST(OlympusMakerNoteTest_892, PrintCs0x0301WithValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::printCs0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x050f
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x050fWithSingleValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x050f(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_892, Print0x050fWithMultipleValues_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0 1");
  OlympusMakerNote::print0x050f(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0527
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x0527WithSingleValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0527(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_892, Print0x0527WithMultipleValues_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0 1 2 3");
  OlympusMakerNote::print0x0527(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0529
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x0529WithValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0529(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x1209
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x1209WithValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x1209(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0305
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x0305WithValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0305(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0308
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x0308WithValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0308(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printGeneric
// ============================================================

TEST(OlympusMakerNoteTest_892, PrintGenericWithSingleValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("42");
  OlympusMakerNote::printGeneric(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_892, PrintGenericWithMultipleValues_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("1 2 3 4 5");
  OlympusMakerNote::printGeneric(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print functions returning ostream reference
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x0200ReturnsOstream_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("1");
  auto& result = OlympusMakerNote::print0x0200(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST(OlympusMakerNoteTest_892, Print0x0204ReturnsOstream_892) {
  std::ostringstream os;
  URationalValue value;
  value.read("100/100");
  auto& result = OlympusMakerNote::print0x0204(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST(OlympusMakerNoteTest_892, Print0x1015ReturnsOstream_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  auto& result = OlympusMakerNote::print0x1015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST(OlympusMakerNoteTest_892, PrintGenericReturnsOstream_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  auto& result = OlympusMakerNote::printGeneric(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Consistency tests across multiple calls
// ============================================================

TEST(OlympusMakerNoteTest_892, TagListFiConsistentAcrossCalls_892) {
  auto tagList1 = OlympusMakerNote::tagListFi();
  auto tagList2 = OlympusMakerNote::tagListFi();
  EXPECT_EQ(tagList1, tagList2);
}

TEST(OlympusMakerNoteTest_892, TagListConsistentAcrossCalls_892) {
  auto tagList1 = OlympusMakerNote::tagList();
  auto tagList2 = OlympusMakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

TEST(OlympusMakerNoteTest_892, TagListCsConsistentAcrossCalls_892) {
  auto tagList1 = OlympusMakerNote::tagListCs();
  auto tagList2 = OlympusMakerNote::tagListCs();
  EXPECT_EQ(tagList1, tagList2);
}

TEST(OlympusMakerNoteTest_892, AllTagListsAreDifferent_892) {
  auto tl = OlympusMakerNote::tagList();
  auto tlCs = OlympusMakerNote::tagListCs();
  auto tlEq = OlympusMakerNote::tagListEq();
  auto tlFi = OlympusMakerNote::tagListFi();
  // These should be different tag info arrays
  // (Not all will necessarily be different, but at least some should be)
  // We test that the main tag list and sub-tag lists are distinct
  EXPECT_NE(tl, tlCs);
  EXPECT_NE(tl, tlEq);
  EXPECT_NE(tl, tlFi);
}

// ============================================================
// Boundary: empty-like value
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x0200WithEmptyStreamInitially_892) {
  std::ostringstream os;
  EXPECT_TRUE(os.str().empty());
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0200(os, value, nullptr);
  // After printing, stream should have content
  EXPECT_FALSE(os.str().empty());
}

TEST(OlympusMakerNoteTest_892, PrintCs0x0301WithMultipleKnownValues_892) {
  // Test with value 1
  {
    std::ostringstream os;
    UShortValue value;
    value.read("1");
    OlympusMakerNote::printCs0x0301(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
  }
  // Test with value 2
  {
    std::ostringstream os;
    UShortValue value;
    value.read("2");
    OlympusMakerNote::printCs0x0301(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
  }
}

TEST(OlympusMakerNoteTest_892, PrintEq0x0301WithMultipleValues_892) {
  {
    std::ostringstream os;
    UShortValue value;
    value.read("1");
    OlympusMakerNote::printEq0x0301(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
  }
  {
    std::ostringstream os;
    UShortValue value;
    value.read("2");
    OlympusMakerNote::printEq0x0301(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
  }
}

// ============================================================
// Test with ExifData pointer (non-null)
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x0529WithExifData_892) {
  std::ostringstream os;
  ExifData exifData;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0529(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST(OlympusMakerNoteTest_892, Print0x0308WithExifData_892) {
  std::ostringstream os;
  ExifData exifData;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0308(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Large unknown value tests
// ============================================================

TEST(OlympusMakerNoteTest_892, Print0x0305WithUnknownValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("65535");
  OlympusMakerNote::print0x0305(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST(OlympusMakerNoteTest_892, Print0x1209WithUnknownValue_892) {
  std::ostringstream os;
  UShortValue value;
  value.read("65535");
  OlympusMakerNote::print0x1209(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
