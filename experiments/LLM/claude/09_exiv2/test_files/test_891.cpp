#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "olympusmn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for OlympusMakerNote tests
class OlympusMakerNoteTest_891 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagListIp()
// ============================================================

TEST_F(OlympusMakerNoteTest_891, TagListIpReturnsNonNull_891) {
  auto tagList = OlympusMakerNote::tagListIp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_891, TagListIpFirstEntryValid_891) {
  auto tagList = OlympusMakerNote::tagListIp();
  // The first entry should have a valid tag (non-negative typically) or be a sentinel
  // We just check that we can access it without crashing
  ASSERT_NE(tagList, nullptr);
  // Check first entry's title is not null (if it's a valid entry)
  // TagInfo arrays typically end with a sentinel with tag == 0xffff or similar
  EXPECT_NE(tagList[0].title_, nullptr);
}

// ============================================================
// Tests for tagList()
// ============================================================

TEST_F(OlympusMakerNoteTest_891, TagListReturnsNonNull_891) {
  auto tagList = OlympusMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_891, TagListFirstEntryHasValidTitle_891) {
  auto tagList = OlympusMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  EXPECT_NE(tagList[0].title_, nullptr);
}

// ============================================================
// Tests for tagListCs()
// ============================================================

TEST_F(OlympusMakerNoteTest_891, TagListCsReturnsNonNull_891) {
  auto tagList = OlympusMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListEq()
// ============================================================

TEST_F(OlympusMakerNoteTest_891, TagListEqReturnsNonNull_891) {
  auto tagList = OlympusMakerNote::tagListEq();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListRd()
// ============================================================

TEST_F(OlympusMakerNoteTest_891, TagListRdReturnsNonNull_891) {
  auto tagList = OlympusMakerNote::tagListRd();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListRd2()
// ============================================================

TEST_F(OlympusMakerNoteTest_891, TagListRd2ReturnsNonNull_891) {
  auto tagList = OlympusMakerNote::tagListRd2();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListFi()
// ============================================================

TEST_F(OlympusMakerNoteTest_891, TagListFiReturnsNonNull_891) {
  auto tagList = OlympusMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListFe()
// ============================================================

TEST_F(OlympusMakerNoteTest_891, TagListFeReturnsNonNull_891) {
  auto tagList = OlympusMakerNote::tagListFe();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListRi()
// ============================================================

TEST_F(OlympusMakerNoteTest_891, TagListRiReturnsNonNull_891) {
  auto tagList = OlympusMakerNote::tagListRi();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print0x0200 (Quality)
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x0200WithThreeValues_891) {
  UShortValue value;
  value.read("1 2 3");
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  // Should produce some output without crashing
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_891, Print0x0200WithSingleValue_891) {
  UShortValue value;
  value.read("1");
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0204 (Serial Number)
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x0204WithSingleValue_891) {
  ULongValue value;
  value.read("12345");
  OlympusMakerNote::print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x1015 (White Balance)
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x1015WithTwoValues_891) {
  UShortValue value;
  value.read("0 0");
  OlympusMakerNote::print0x1015(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_891, Print0x1015WithSingleValue_891) {
  UShortValue value;
  value.read("1");
  OlympusMakerNote::print0x1015(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0201
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x0201WithValues_891) {
  UShortValue value;
  value.read("0 0 0");
  OlympusMakerNote::print0x0201(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_891, Print0x0201WithSingleValue_891) {
  UShortValue value;
  value.read("1");
  OlympusMakerNote::print0x0201(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0209
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x0209WithValue_891) {
  ULongValue value;
  value.read("100");
  OlympusMakerNote::print0x0209(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printEq0x0301 (Equipment - Focal Length)
// ============================================================

TEST_F(OlympusMakerNoteTest_891, PrintEq0x0301WithValue_891) {
  URationalValue value;
  value.read("100/10");
  OlympusMakerNote::printEq0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printCs0x0301 (Camera Settings)
// ============================================================

TEST_F(OlympusMakerNoteTest_891, PrintCs0x0301WithValue_891) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::printCs0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x050f
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x050fWithValues_891) {
  UShortValue value;
  value.read("0 0 0 0 0 0");
  OlympusMakerNote::print0x050f(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_891, Print0x050fWithEmptyLikeValue_891) {
  UShortValue value;
  value.read("1");
  OlympusMakerNote::print0x050f(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0527
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x0527WithValues_891) {
  UShortValue value;
  value.read("0 0 0 0");
  OlympusMakerNote::print0x0527(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_891, Print0x0527WithSingleValue_891) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0527(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0529
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x0529WithValues_891) {
  UShortValue value;
  value.read("0 0");
  OlympusMakerNote::print0x0529(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x1209
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x1209WithValue_891) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x1209(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0305
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x0305WithValue_891) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0305(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0308
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x0308WithValue_891) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0308(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printGeneric
// ============================================================

TEST_F(OlympusMakerNoteTest_891, PrintGenericWithSingleValue_891) {
  UShortValue value;
  value.read("42");
  OlympusMakerNote::printGeneric(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_891, PrintGenericWithMultipleValues_891) {
  UShortValue value;
  value.read("1 2 3 4 5");
  OlympusMakerNote::printGeneric(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for consistency: tagList pointers are stable
// ============================================================

TEST_F(OlympusMakerNoteTest_891, TagListIpReturnsSamePointerOnMultipleCalls_891) {
  auto ptr1 = OlympusMakerNote::tagListIp();
  auto ptr2 = OlympusMakerNote::tagListIp();
  EXPECT_EQ(ptr1, ptr2);
}

TEST_F(OlympusMakerNoteTest_891, TagListReturnsSamePointerOnMultipleCalls_891) {
  auto ptr1 = OlympusMakerNote::tagList();
  auto ptr2 = OlympusMakerNote::tagList();
  EXPECT_EQ(ptr1, ptr2);
}

TEST_F(OlympusMakerNoteTest_891, TagListCsReturnsSamePointerOnMultipleCalls_891) {
  auto ptr1 = OlympusMakerNote::tagListCs();
  auto ptr2 = OlympusMakerNote::tagListCs();
  EXPECT_EQ(ptr1, ptr2);
}

TEST_F(OlympusMakerNoteTest_891, TagListEqReturnsSamePointerOnMultipleCalls_891) {
  auto ptr1 = OlympusMakerNote::tagListEq();
  auto ptr2 = OlympusMakerNote::tagListEq();
  EXPECT_EQ(ptr1, ptr2);
}

// ============================================================
// Tests: print functions return the same ostream reference
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x0200ReturnsOstreamRef_891) {
  UShortValue value;
  value.read("1 2 3");
  std::ostream& ret = OlympusMakerNote::print0x0200(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_891, Print0x0204ReturnsOstreamRef_891) {
  ULongValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0204(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_891, PrintGenericReturnsOstreamRef_891) {
  UShortValue value;
  value.read("42");
  std::ostream& ret = OlympusMakerNote::printGeneric(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_891, Print0x1015ReturnsOstreamRef_891) {
  UShortValue value;
  value.read("0 0");
  std::ostream& ret = OlympusMakerNote::print0x1015(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_891, Print0x0201ReturnsOstreamRef_891) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0201(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_891, Print0x0209ReturnsOstreamRef_891) {
  ULongValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0209(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_891, PrintCs0x0301ReturnsOstreamRef_891) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::printCs0x0301(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_891, Print0x050fReturnsOstreamRef_891) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x050f(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_891, Print0x0527ReturnsOstreamRef_891) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0527(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_891, Print0x0529ReturnsOstreamRef_891) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0529(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_891, Print0x1209ReturnsOstreamRef_891) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x1209(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_891, Print0x0305ReturnsOstreamRef_891) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0305(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_891, Print0x0308ReturnsOstreamRef_891) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0308(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Boundary: print functions with ExifData provided
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x0308WithExifData_891) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0308(os, value, &exifData);
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(OlympusMakerNoteTest_891, Print0x0529WithExifData_891) {
  ExifData exifData;
  UShortValue value;
  value.read("0 0");
  std::ostream& ret = OlympusMakerNote::print0x0529(os, value, &exifData);
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Boundary: various known values for print0x0200
// ============================================================

TEST_F(OlympusMakerNoteTest_891, Print0x0200WithZeroValues_891) {
  UShortValue value;
  value.read("0 0 0");
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Boundary: large value for printGeneric
// ============================================================

TEST_F(OlympusMakerNoteTest_891, PrintGenericWithLargeValue_891) {
  UShortValue value;
  value.read("65535");
  OlympusMakerNote::printGeneric(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
