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
class OlympusMakerNoteTest_887 : public ::testing::Test {
 protected:
  std::ostringstream os_;
};

// ============================================================
// tagListCs tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, TagListCsReturnsNonNull_887) {
  auto tagList = OlympusMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_887, TagListCsFirstEntryValid_887) {
  auto tagList = OlympusMakerNote::tagListCs();
  // The first entry should have a valid tag (non-negative typically)
  // and a non-null title
  EXPECT_NE(tagList[0].title_, nullptr);
}

// ============================================================
// tagList tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, TagListReturnsNonNull_887) {
  auto tagList = OlympusMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_887, TagListFirstEntryValid_887) {
  auto tagList = OlympusMakerNote::tagList();
  EXPECT_NE(tagList[0].title_, nullptr);
}

// ============================================================
// tagListEq tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, TagListEqReturnsNonNull_887) {
  auto tagList = OlympusMakerNote::tagListEq();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// tagListRd tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, TagListRdReturnsNonNull_887) {
  auto tagList = OlympusMakerNote::tagListRd();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// tagListRd2 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, TagListRd2ReturnsNonNull_887) {
  auto tagList = OlympusMakerNote::tagListRd2();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// tagListIp tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, TagListIpReturnsNonNull_887) {
  auto tagList = OlympusMakerNote::tagListIp();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// tagListFi tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, TagListFiReturnsNonNull_887) {
  auto tagList = OlympusMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// tagListFe tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, TagListFeReturnsNonNull_887) {
  auto tagList = OlympusMakerNote::tagListFe();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// tagListRi tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, TagListRiReturnsNonNull_887) {
  auto tagList = OlympusMakerNote::tagListRi();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// print0x0200 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x0200WithThreeValues_887) {
  ULongValue value;
  value.read("0 1 2");
  OlympusMakerNote::print0x0200(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x0200WithEmptyValue_887) {
  ULongValue value;
  OlympusMakerNote::print0x0200(os_, value, nullptr);
  std::string result = os_.str();
  // Should produce some output even with empty value
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x0200WithSingleValue_887) {
  ULongValue value;
  value.read("0");
  OlympusMakerNote::print0x0200(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0204 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x0204WithValue_887) {
  URationalValue value;
  value.read("0/1");
  OlympusMakerNote::print0x0204(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x0204WithEmptyValue_887) {
  URationalValue value;
  OlympusMakerNote::print0x0204(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x1015 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x1015WithTwoValues_887) {
  UShortValue value;
  value.read("0 0");
  OlympusMakerNote::print0x1015(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x1015WithEmptyValue_887) {
  UShortValue value;
  OlympusMakerNote::print0x1015(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0201 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x0201WithValues_887) {
  UShortValue value;
  value.read("0 1");
  OlympusMakerNote::print0x0201(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x0201WithEmptyValue_887) {
  UShortValue value;
  OlympusMakerNote::print0x0201(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0209 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x0209WithValue_887) {
  ULongValue value;
  value.read("0");
  OlympusMakerNote::print0x0209(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x0209WithEmptyValue_887) {
  ULongValue value;
  OlympusMakerNote::print0x0209(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printEq0x0301 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, PrintEq0x0301WithValue_887) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::printEq0x0301(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, PrintEq0x0301WithEmptyValue_887) {
  UShortValue value;
  OlympusMakerNote::printEq0x0301(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// printCs0x0301 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, PrintCs0x0301WithValue_887) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::printCs0x0301(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, PrintCs0x0301WithEmptyValue_887) {
  UShortValue value;
  OlympusMakerNote::printCs0x0301(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x050f tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x050fWithValue_887) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x050fWithEmptyValue_887) {
  UShortValue value;
  OlympusMakerNote::print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0527 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x0527WithValue_887) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0527(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x0527WithEmptyValue_887) {
  UShortValue value;
  OlympusMakerNote::print0x0527(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0529 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x0529WithValue_887) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0529(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x0529WithEmptyValue_887) {
  UShortValue value;
  OlympusMakerNote::print0x0529(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x0529WithMetadata_887) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  OlympusMakerNote::print0x0529(os_, value, &exifData);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x1209 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x1209WithValue_887) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x1209(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x1209WithEmptyValue_887) {
  UShortValue value;
  OlympusMakerNote::print0x1209(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0305 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x0305WithValue_887) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0305(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x0305WithEmptyValue_887) {
  UShortValue value;
  OlympusMakerNote::print0x0305(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0308 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x0308WithValue_887) {
  AsciiValue value;
  value.read("test");
  OlympusMakerNote::print0x0308(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x0308WithMetadata_887) {
  AsciiValue value;
  value.read("test");
  ExifData exifData;
  OlympusMakerNote::print0x0308(os_, value, &exifData);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Return value tests (os reference)
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x0200ReturnsOstream_887) {
  ULongValue value;
  value.read("0");
  std::ostream& result = OlympusMakerNote::print0x0200(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(OlympusMakerNoteTest_887, Print0x0204ReturnsOstream_887) {
  URationalValue value;
  value.read("1/2");
  std::ostream& result = OlympusMakerNote::print0x0204(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(OlympusMakerNoteTest_887, Print0x1015ReturnsOstream_887) {
  UShortValue value;
  value.read("0 0");
  std::ostream& result = OlympusMakerNote::print0x1015(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(OlympusMakerNoteTest_887, Print0x0201ReturnsOstream_887) {
  UShortValue value;
  value.read("0");
  std::ostream& result = OlympusMakerNote::print0x0201(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(OlympusMakerNoteTest_887, Print0x0209ReturnsOstream_887) {
  ULongValue value;
  value.read("0");
  std::ostream& result = OlympusMakerNote::print0x0209(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(OlympusMakerNoteTest_887, PrintEq0x0301ReturnsOstream_887) {
  UShortValue value;
  value.read("0");
  std::ostream& result = OlympusMakerNote::printEq0x0301(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(OlympusMakerNoteTest_887, PrintCs0x0301ReturnsOstream_887) {
  UShortValue value;
  value.read("0");
  std::ostream& result = OlympusMakerNote::printCs0x0301(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(OlympusMakerNoteTest_887, Print0x050fReturnsOstream_887) {
  UShortValue value;
  value.read("0");
  std::ostream& result = OlympusMakerNote::print0x050f(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(OlympusMakerNoteTest_887, Print0x0527ReturnsOstream_887) {
  UShortValue value;
  value.read("0");
  std::ostream& result = OlympusMakerNote::print0x0527(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(OlympusMakerNoteTest_887, Print0x0529ReturnsOstream_887) {
  UShortValue value;
  value.read("0");
  std::ostream& result = OlympusMakerNote::print0x0529(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(OlympusMakerNoteTest_887, Print0x1209ReturnsOstream_887) {
  UShortValue value;
  value.read("0");
  std::ostream& result = OlympusMakerNote::print0x1209(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(OlympusMakerNoteTest_887, Print0x0305ReturnsOstream_887) {
  UShortValue value;
  value.read("0");
  std::ostream& result = OlympusMakerNote::print0x0305(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(OlympusMakerNoteTest_887, Print0x0308ReturnsOstream_887) {
  AsciiValue value;
  value.read("test");
  std::ostream& result = OlympusMakerNote::print0x0308(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// ============================================================
// Consistency tests - all tag lists should be stable
// ============================================================

TEST_F(OlympusMakerNoteTest_887, TagListCsIsConsistentAcrossCalls_887) {
  auto tagList1 = OlympusMakerNote::tagListCs();
  auto tagList2 = OlympusMakerNote::tagListCs();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(OlympusMakerNoteTest_887, TagListIsConsistentAcrossCalls_887) {
  auto tagList1 = OlympusMakerNote::tagList();
  auto tagList2 = OlympusMakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(OlympusMakerNoteTest_887, TagListEqIsConsistentAcrossCalls_887) {
  auto tagList1 = OlympusMakerNote::tagListEq();
  auto tagList2 = OlympusMakerNote::tagListEq();
  EXPECT_EQ(tagList1, tagList2);
}

// ============================================================
// Boundary: print functions with multiple values
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x0200WithManyValues_887) {
  ULongValue value;
  value.read("0 1 2 3 4 5 6 7");
  OlympusMakerNote::print0x0200(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x0201WithMultipleValues_887) {
  UShortValue value;
  value.read("0 1 2 3");
  OlympusMakerNote::print0x0201(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x1015WithSingleValue_887) {
  UShortValue value;
  value.read("1");
  OlympusMakerNote::print0x1015(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Specific known values to explore behavior
// ============================================================

TEST_F(OlympusMakerNoteTest_887, Print0x0209WithKnownCameraType_887) {
  ULongValue value;
  value.read("1");
  OlympusMakerNote::print0x0209(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, Print0x0209WithLargeValue_887) {
  ULongValue value;
  value.read("65535");
  OlympusMakerNote::print0x0209(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, PrintCs0x0301WithKnownValue_887) {
  UShortValue value;
  value.read("1");
  OlympusMakerNote::printCs0x0301(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_887, PrintEq0x0301WithKnownValue_887) {
  UShortValue value;
  value.read("1");
  OlympusMakerNote::printEq0x0301(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}
