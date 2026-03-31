#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_909 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(CanonMakerNoteTest_909, TagListCsIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListIsNotNull_909) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListSiIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListPaIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListPa();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListCfIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListCf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListPiIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListPi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListTiIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListTi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListFiIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListPrIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListPr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListLeIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListLe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListFlIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListFl();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListMoIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListMo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListMvIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListMv();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListMcIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListMc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListFcd3IsNotNull_909) {
  auto tagList = CanonMakerNote::tagListFcd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListWbiIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListWbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListCoIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListCo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListFcd2IsNotNull_909) {
  auto tagList = CanonMakerNote::tagListFcd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListFcd1IsNotNull_909) {
  auto tagList = CanonMakerNote::tagListFcd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListAsIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListAs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListCbiIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListCbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListPreIIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListPreI();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListCiIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListCi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListAfMiAdjIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListVigCorIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListVigCor();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListVigCor2IsNotNull_909) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListLiOpIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListLiOp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListAmIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListAm();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListMeIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListFilIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListFil();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListHdrIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListHdr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListAfCIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListAfC();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListRawBIsNotNull_909) {
  auto tagList = CanonMakerNote::tagListRawB();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print functions
// ============================================================

TEST_F(CanonMakerNoteTest_909, PrintFocalLengthWithSingleValue_909) {
  UShortValue value;
  value.read("1000");
  std::ostringstream oss;
  CanonMakerNote::printFocalLength(oss, value, nullptr);
  // Should produce some output (not empty)
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintFocalLengthWithMultipleValues_909) {
  UShortValue value;
  value.read("1 1000 0 0");
  std::ostringstream oss;
  CanonMakerNote::printFocalLength(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, Print0x0008WithSingleValue_909) {
  UShortValue value;
  value.read("12345");
  std::ostringstream oss;
  CanonMakerNote::print0x0008(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, Print0x000aWithSingleValue_909) {
  ULongValue value;
  value.read("12345678");
  std::ostringstream oss;
  CanonMakerNote::print0x000a(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintCs0x0002WithValue_909) {
  UShortValue value;
  value.read("50");
  std::ostringstream oss;
  CanonMakerNote::printCs0x0002(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintCsLensWithThreeValues_909) {
  UShortValue value;
  value.read("200 50 1");
  std::ostringstream oss;
  CanonMakerNote::printCsLens(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintCsLensTypeWithValue_909) {
  UShortValue value;
  value.read("255");
  std::ostringstream oss;
  CanonMakerNote::printCsLensType(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0001WithValue_909) {
  UShortValue value;
  value.read("100");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0001(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0002WithValue_909) {
  UShortValue value;
  value.read("100");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0002(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0003WithValue_909) {
  UShortValue value;
  value.read("400");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0003(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0009WithValue_909) {
  UShortValue value;
  value.read("10");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0009(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x000cWithValue_909) {
  UShortValue value;
  value.read("50");
  std::ostringstream oss;
  CanonMakerNote::printSi0x000c(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x000dWithValue_909) {
  UShortValue value;
  value.read("3");
  std::ostringstream oss;
  CanonMakerNote::printSi0x000d(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x000eWithValueNullMetadata_909) {
  UShortValue value;
  value.read("128");
  std::ostringstream oss;
  CanonMakerNote::printSi0x000e(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0013WithValue_909) {
  UShortValue value;
  value.read("50");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0013(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0015WithValue_909) {
  UShortValue value;
  value.read("100");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0015(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0016WithValue_909) {
  UShortValue value;
  value.read("32767");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0016(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0017WithValue_909) {
  UShortValue value;
  value.read("100");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0017(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0018WithValue_909) {
  UShortValue value;
  value.read("50");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0018(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintFiFocusDistanceWithValue_909) {
  UShortValue value;
  value.read("100");
  std::ostringstream oss;
  CanonMakerNote::printFiFocusDistance(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintFiFocusDistanceZero_909) {
  UShortValue value;
  value.read("0");
  std::ostringstream oss;
  CanonMakerNote::printFiFocusDistance(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintFiFocusDistanceMaxValue_909) {
  UShortValue value;
  value.read("65535");
  std::ostringstream oss;
  CanonMakerNote::printFiFocusDistance(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintLe0x0000WithValue_909) {
  UShortValue value;
  value.read("1");
  std::ostringstream oss;
  CanonMakerNote::printLe0x0000(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, Print0x000cWithValue_909) {
  ULongValue value;
  value.read("12345678");
  std::ostringstream oss;
  ExifData exifData;
  CanonMakerNote::print0x000c(oss, value, &exifData);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, Print0x000cWithNullMetadata_909) {
  ULongValue value;
  value.read("12345678");
  std::ostringstream oss;
  CanonMakerNote::print0x000c(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintFiFileNumberWithValue_909) {
  ULongValue value;
  value.read("1234567");
  std::ostringstream oss;
  CanonMakerNote::printFiFileNumber(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x000eWithExifData_909) {
  UShortValue value;
  value.read("128");
  ExifData exifData;
  std::ostringstream oss;
  CanonMakerNote::printSi0x000e(oss, value, &exifData);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for return value (stream reference)
// ============================================================

TEST_F(CanonMakerNoteTest_909, PrintFunctionsReturnSameStream_909) {
  UShortValue value;
  value.read("100");
  std::ostringstream oss;
  std::ostream& ret = CanonMakerNote::printSi0x0001(oss, value, nullptr);
  EXPECT_EQ(&ret, &oss);
}

TEST_F(CanonMakerNoteTest_909, PrintFocalLengthReturnsSameStream_909) {
  UShortValue value;
  value.read("500");
  std::ostringstream oss;
  std::ostream& ret = CanonMakerNote::printFocalLength(oss, value, nullptr);
  EXPECT_EQ(&ret, &oss);
}

TEST_F(CanonMakerNoteTest_909, PrintCsLensReturnsSameStream_909) {
  UShortValue value;
  value.read("200 50 1");
  std::ostringstream oss;
  std::ostream& ret = CanonMakerNote::printCsLens(oss, value, nullptr);
  EXPECT_EQ(&ret, &oss);
}

TEST_F(CanonMakerNoteTest_909, PrintFiFocusDistanceReturnsSameStream_909) {
  UShortValue value;
  value.read("500");
  std::ostringstream oss;
  std::ostream& ret = CanonMakerNote::printFiFocusDistance(oss, value, nullptr);
  EXPECT_EQ(&ret, &oss);
}

// ============================================================
// Boundary condition tests
// ============================================================

TEST_F(CanonMakerNoteTest_909, PrintSi0x0002WithZeroValue_909) {
  UShortValue value;
  value.read("0");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0002(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0003WithZeroValue_909) {
  UShortValue value;
  value.read("0");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0003(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0001WithZeroValue_909) {
  UShortValue value;
  value.read("0");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0001(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0016WithZeroValue_909) {
  UShortValue value;
  value.read("0");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0016(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintCsLensTypeWithZero_909) {
  UShortValue value;
  value.read("0");
  std::ostringstream oss;
  CanonMakerNote::printCsLensType(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintCs0x0002WithZeroValue_909) {
  UShortValue value;
  value.read("0");
  std::ostringstream oss;
  CanonMakerNote::printCs0x0002(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_909, PrintSi0x0009WithZeroValue_909) {
  UShortValue value;
  value.read("0");
  std::ostringstream oss;
  CanonMakerNote::printSi0x0009(oss, value, nullptr);
  std::string result = oss.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for tagList first element validity
// ============================================================

TEST_F(CanonMakerNoteTest_909, TagListCsFirstElementHasValidTag_909) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
  // The first tag info entry should have a valid tag number (usually >= 0)
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(CanonMakerNoteTest_909, TagListSiFirstElementHasValidTag_909) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(CanonMakerNoteTest_909, TagListFirstElementHasValidTag_909) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}
