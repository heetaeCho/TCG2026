#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "olympusmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMakerNoteTest_888 : public ::testing::Test {
 protected:
  std::ostringstream oss;
};

// ==================== tagListEq tests ====================

TEST_F(OlympusMakerNoteTest_888, TagListEqReturnsNonNull_888) {
  auto tagList = OlympusMakerNote::tagListEq();
  ASSERT_NE(tagList, nullptr);
}

// ==================== tagList tests ====================

TEST_F(OlympusMakerNoteTest_888, TagListReturnsNonNull_888) {
  auto tagList = OlympusMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_888, TagListCsReturnsNonNull_888) {
  auto tagList = OlympusMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_888, TagListRdReturnsNonNull_888) {
  auto tagList = OlympusMakerNote::tagListRd();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_888, TagListRd2ReturnsNonNull_888) {
  auto tagList = OlympusMakerNote::tagListRd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_888, TagListIpReturnsNonNull_888) {
  auto tagList = OlympusMakerNote::tagListIp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_888, TagListFiReturnsNonNull_888) {
  auto tagList = OlympusMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_888, TagListFeReturnsNonNull_888) {
  auto tagList = OlympusMakerNote::tagListFe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_888, TagListRiReturnsNonNull_888) {
  auto tagList = OlympusMakerNote::tagListRi();
  ASSERT_NE(tagList, nullptr);
}

// ==================== print0x0200 tests ====================

TEST_F(OlympusMakerNoteTest_888, Print0x0200WithThreeValues_888) {
  ULongValue value;
  value.read("0 1 2");
  OlympusMakerNote::print0x0200(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_888, Print0x0200WithSingleValue_888) {
  ULongValue value;
  value.read("0");
  OlympusMakerNote::print0x0200(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_888, Print0x0200WithEmptyValue_888) {
  ULongValue value;
  OlympusMakerNote::print0x0200(oss, value, nullptr);
  std::string result = oss.str();
  // Should handle gracefully
}

// ==================== print0x0204 tests ====================

TEST_F(OlympusMakerNoteTest_888, Print0x0204WithZero_888) {
  URationalValue value;
  value.read("0/1");
  OlympusMakerNote::print0x0204(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_888, Print0x0204WithNonZero_888) {
  URationalValue value;
  value.read("100/10");
  OlympusMakerNote::print0x0204(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ==================== print0x1015 tests ====================

TEST_F(OlympusMakerNoteTest_888, Print0x1015WithTwoValues_888) {
  UShortValue value;
  value.read("0 0");
  OlympusMakerNote::print0x1015(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_888, Print0x1015WithSingleValue_888) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x1015(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ==================== print0x0201 tests ====================

TEST_F(OlympusMakerNoteTest_888, Print0x0201WithKnownValue_888) {
  UShortValue value;
  value.read("0 0");
  OlympusMakerNote::print0x0201(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_888, Print0x0201WithSingleValue_888) {
  UShortValue value;
  value.read("1");
  OlympusMakerNote::print0x0201(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ==================== print0x0209 tests ====================

TEST_F(OlympusMakerNoteTest_888, Print0x0209WithValue_888) {
  ULongValue value;
  value.read("0");
  OlympusMakerNote::print0x0209(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ==================== printEq0x0301 tests ====================

TEST_F(OlympusMakerNoteTest_888, PrintEq0x0301WithValue_888) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::printEq0x0301(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_888, PrintEq0x0301WithUnknownValue_888) {
  UShortValue value;
  value.read("9999");
  OlympusMakerNote::printEq0x0301(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ==================== printCs0x0301 tests ====================

TEST_F(OlympusMakerNoteTest_888, PrintCs0x0301WithKnownValue_888) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::printCs0x0301(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_888, PrintCs0x0301WithUnknownValue_888) {
  UShortValue value;
  value.read("65535");
  OlympusMakerNote::printCs0x0301(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ==================== print0x050f tests ====================

TEST_F(OlympusMakerNoteTest_888, Print0x050fWithValue_888) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x050f(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ==================== print0x0527 tests ====================

TEST_F(OlympusMakerNoteTest_888, Print0x0527WithValue_888) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0527(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ==================== print0x0529 tests ====================

TEST_F(OlympusMakerNoteTest_888, Print0x0529WithNullMetadata_888) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0529(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_888, Print0x0529WithMetadata_888) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0529(oss, value, &exifData);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ==================== print0x1209 tests ====================

TEST_F(OlympusMakerNoteTest_888, Print0x1209WithValue_888) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x1209(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ==================== print0x0305 tests ====================

TEST_F(OlympusMakerNoteTest_888, Print0x0305WithValue_888) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0305(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ==================== print0x0308 tests ====================

TEST_F(OlympusMakerNoteTest_888, Print0x0308WithNullMetadata_888) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0308(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_888, Print0x0308WithMetadata_888) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0308(oss, value, &exifData);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ==================== Stream reference return tests ====================

TEST_F(OlympusMakerNoteTest_888, Print0x0200ReturnsStreamReference_888) {
  ULongValue value;
  value.read("0 1 2");
  std::ostream& ref = OlympusMakerNote::print0x0200(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

TEST_F(OlympusMakerNoteTest_888, Print0x0204ReturnsStreamReference_888) {
  URationalValue value;
  value.read("0/1");
  std::ostream& ref = OlympusMakerNote::print0x0204(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

TEST_F(OlympusMakerNoteTest_888, Print0x1015ReturnsStreamReference_888) {
  UShortValue value;
  value.read("0 0");
  std::ostream& ref = OlympusMakerNote::print0x1015(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

TEST_F(OlympusMakerNoteTest_888, Print0x0201ReturnsStreamReference_888) {
  UShortValue value;
  value.read("0 0");
  std::ostream& ref = OlympusMakerNote::print0x0201(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

TEST_F(OlympusMakerNoteTest_888, Print0x0209ReturnsStreamReference_888) {
  ULongValue value;
  value.read("0");
  std::ostream& ref = OlympusMakerNote::print0x0209(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

TEST_F(OlympusMakerNoteTest_888, PrintEq0x0301ReturnsStreamReference_888) {
  UShortValue value;
  value.read("0");
  std::ostream& ref = OlympusMakerNote::printEq0x0301(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

TEST_F(OlympusMakerNoteTest_888, PrintCs0x0301ReturnsStreamReference_888) {
  UShortValue value;
  value.read("0");
  std::ostream& ref = OlympusMakerNote::printCs0x0301(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

TEST_F(OlympusMakerNoteTest_888, Print0x050fReturnsStreamReference_888) {
  UShortValue value;
  value.read("0");
  std::ostream& ref = OlympusMakerNote::print0x050f(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

TEST_F(OlympusMakerNoteTest_888, Print0x0527ReturnsStreamReference_888) {
  UShortValue value;
  value.read("0");
  std::ostream& ref = OlympusMakerNote::print0x0527(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

TEST_F(OlympusMakerNoteTest_888, Print0x0529ReturnsStreamReference_888) {
  UShortValue value;
  value.read("0");
  std::ostream& ref = OlympusMakerNote::print0x0529(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

TEST_F(OlympusMakerNoteTest_888, Print0x1209ReturnsStreamReference_888) {
  UShortValue value;
  value.read("0");
  std::ostream& ref = OlympusMakerNote::print0x1209(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

TEST_F(OlympusMakerNoteTest_888, Print0x0305ReturnsStreamReference_888) {
  UShortValue value;
  value.read("0");
  std::ostream& ref = OlympusMakerNote::print0x0305(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

TEST_F(OlympusMakerNoteTest_888, Print0x0308ReturnsStreamReference_888) {
  UShortValue value;
  value.read("0");
  std::ostream& ref = OlympusMakerNote::print0x0308(oss, value, nullptr);
  EXPECT_EQ(&ref, &oss);
}

// ==================== Consistency tests ====================

TEST_F(OlympusMakerNoteTest_888, TagListEqConsistentAcrossCalls_888) {
  auto tagList1 = OlympusMakerNote::tagListEq();
  auto tagList2 = OlympusMakerNote::tagListEq();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(OlympusMakerNoteTest_888, TagListConsistentAcrossCalls_888) {
  auto tagList1 = OlympusMakerNote::tagList();
  auto tagList2 = OlympusMakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(OlympusMakerNoteTest_888, TagListCsConsistentAcrossCalls_888) {
  auto tagList1 = OlympusMakerNote::tagListCs();
  auto tagList2 = OlympusMakerNote::tagListCs();
  EXPECT_EQ(tagList1, tagList2);
}

// ==================== Boundary tests for print functions ====================

TEST_F(OlympusMakerNoteTest_888, Print0x0200WithLargeValue_888) {
  ULongValue value;
  value.read("4294967295 4294967295 4294967295");
  OlympusMakerNote::print0x0200(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_888, Print0x0209WithLargeValue_888) {
  ULongValue value;
  value.read("4294967295");
  OlympusMakerNote::print0x0209(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_888, Print0x0305WithLargeValue_888) {
  UShortValue value;
  value.read("65535");
  OlympusMakerNote::print0x0305(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_888, Print0x1209WithLargeValue_888) {
  UShortValue value;
  value.read("65535");
  OlympusMakerNote::print0x1209(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}
