#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "olympusmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for OlympusMakerNote tests
class OlympusMakerNoteTest_889 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions - they should return non-null pointers
// ============================================================

TEST_F(OlympusMakerNoteTest_889, TagListRdReturnsNonNull_889) {
  auto tagList = OlympusMakerNote::tagListRd();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_889, TagListReturnsNonNull_889) {
  auto tagList = OlympusMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_889, TagListCsReturnsNonNull_889) {
  auto tagList = OlympusMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_889, TagListEqReturnsNonNull_889) {
  auto tagList = OlympusMakerNote::tagListEq();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_889, TagListRd2ReturnsNonNull_889) {
  auto tagList = OlympusMakerNote::tagListRd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_889, TagListIpReturnsNonNull_889) {
  auto tagList = OlympusMakerNote::tagListIp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_889, TagListFiReturnsNonNull_889) {
  auto tagList = OlympusMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_889, TagListFeReturnsNonNull_889) {
  auto tagList = OlympusMakerNote::tagListFe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_889, TagListRiReturnsNonNull_889) {
  auto tagList = OlympusMakerNote::tagListRi();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print0x0200 - Special Picture Mode
// ============================================================

TEST_F(OlympusMakerNoteTest_889, Print0x0200WithThreeValues_889) {
  ULongValue value;
  value.read("0 0 0");
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_889, Print0x0200WithSingleValue_889) {
  ULongValue value;
  value.read("1");
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0204 - Digital Zoom
// ============================================================

TEST_F(OlympusMakerNoteTest_889, Print0x0204WithZeroValue_889) {
  URationalValue value;
  value.read("0/1");
  OlympusMakerNote::print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_889, Print0x0204WithNonZeroValue_889) {
  URationalValue value;
  value.read("200/100");
  OlympusMakerNote::print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x1015 - White Balance related
// ============================================================

TEST_F(OlympusMakerNoteTest_889, Print0x1015WithTwoValues_889) {
  UShortValue value;
  value.read("0 0");
  OlympusMakerNote::print0x1015(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_889, Print0x1015WithSingleValue_889) {
  UShortValue value;
  value.read("1");
  OlympusMakerNote::print0x1015(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0201 - Quality
// ============================================================

TEST_F(OlympusMakerNoteTest_889, Print0x0201WithTwoValues_889) {
  UShortValue value;
  value.read("1 0");
  OlympusMakerNote::print0x0201(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_889, Print0x0201WithSingleValue_889) {
  UShortValue value;
  value.read("3");
  OlympusMakerNote::print0x0201(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0209 - Camera ID
// ============================================================

TEST_F(OlympusMakerNoteTest_889, Print0x0209WithAsciiValue_889) {
  AsciiValue value;
  value.read("TestCamera");
  OlympusMakerNote::print0x0209(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printEq0x0301 - Equipment lens type
// ============================================================

TEST_F(OlympusMakerNoteTest_889, PrintEq0x0301WithValues_889) {
  UShortValue value;
  value.read("0 0 0");
  OlympusMakerNote::printEq0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_889, PrintEq0x0301WithSingleValue_889) {
  UShortValue value;
  value.read("6");
  OlympusMakerNote::printEq0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printCs0x0301 - Camera Settings WhiteBalance
// ============================================================

TEST_F(OlympusMakerNoteTest_889, PrintCs0x0301WithKnownValue_889) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::printCs0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_889, PrintCs0x0301WithUnknownValue_889) {
  UShortValue value;
  value.read("9999");
  OlympusMakerNote::printCs0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x050f - Focus Info related
// ============================================================

TEST_F(OlympusMakerNoteTest_889, Print0x050fWithValue_889) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x050f(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0527
// ============================================================

TEST_F(OlympusMakerNoteTest_889, Print0x0527WithValue_889) {
  UShortValue value;
  value.read("0 0 0 0");
  OlympusMakerNote::print0x0527(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_889, Print0x0527WithSingleValue_889) {
  UShortValue value;
  value.read("1");
  OlympusMakerNote::print0x0527(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0529
// ============================================================

TEST_F(OlympusMakerNoteTest_889, Print0x0529WithNullMetadata_889) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0529(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_889, Print0x0529WithMetadata_889) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0529(os, value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x1209
// ============================================================

TEST_F(OlympusMakerNoteTest_889, Print0x1209WithZeroValue_889) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x1209(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0305
// ============================================================

TEST_F(OlympusMakerNoteTest_889, Print0x0305WithValue_889) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0305(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0308
// ============================================================

TEST_F(OlympusMakerNoteTest_889, Print0x0308WithNullMetadata_889) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0308(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_889, Print0x0308WithMetadata_889) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0308(os, value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printGeneric
// ============================================================

TEST_F(OlympusMakerNoteTest_889, PrintGenericWithSingleValue_889) {
  UShortValue value;
  value.read("42");
  OlympusMakerNote::printGeneric(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_889, PrintGenericWithMultipleValues_889) {
  UShortValue value;
  value.read("1 2 3 4 5");
  OlympusMakerNote::printGeneric(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for stream return reference
// ============================================================

TEST_F(OlympusMakerNoteTest_889, Print0x0200ReturnsOstream_889) {
  ULongValue value;
  value.read("0 0 0");
  std::ostream& ret = OlympusMakerNote::print0x0200(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, Print0x0204ReturnsOstream_889) {
  URationalValue value;
  value.read("0/1");
  std::ostream& ret = OlympusMakerNote::print0x0204(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, Print0x1015ReturnsOstream_889) {
  UShortValue value;
  value.read("0 0");
  std::ostream& ret = OlympusMakerNote::print0x1015(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, PrintGenericReturnsOstream_889) {
  UShortValue value;
  value.read("1");
  std::ostream& ret = OlympusMakerNote::printGeneric(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, PrintCs0x0301ReturnsOstream_889) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::printCs0x0301(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, PrintEq0x0301ReturnsOstream_889) {
  UShortValue value;
  value.read("0 0 0");
  std::ostream& ret = OlympusMakerNote::printEq0x0301(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, Print0x050fReturnsOstream_889) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x050f(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, Print0x0527ReturnsOstream_889) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0527(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, Print0x0529ReturnsOstream_889) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0529(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, Print0x1209ReturnsOstream_889) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x1209(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, Print0x0305ReturnsOstream_889) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0305(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, Print0x0308ReturnsOstream_889) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0308(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, Print0x0201ReturnsOstream_889) {
  UShortValue value;
  value.read("1");
  std::ostream& ret = OlympusMakerNote::print0x0201(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_889, Print0x0209ReturnsOstream_889) {
  AsciiValue value;
  value.read("Test");
  std::ostream& ret = OlympusMakerNote::print0x0209(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Boundary: tag list entries have valid structure
// ============================================================

TEST_F(OlympusMakerNoteTest_889, TagListRdFirstEntryHasValidTag_889) {
  auto tagList = OlympusMakerNote::tagListRd();
  ASSERT_NE(tagList, nullptr);
  // First entry should have a valid tag (non-negative when cast)
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(OlympusMakerNoteTest_889, TagListFirstEntryHasValidTag_889) {
  auto tagList = OlympusMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(OlympusMakerNoteTest_889, TagListCsFirstEntryHasValidTag_889) {
  auto tagList = OlympusMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(OlympusMakerNoteTest_889, TagListEqFirstEntryHasValidTag_889) {
  auto tagList = OlympusMakerNote::tagListEq();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}
