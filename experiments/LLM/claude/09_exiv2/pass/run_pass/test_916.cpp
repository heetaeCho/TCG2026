#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_916 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions - verify they return non-null
// ============================================================

TEST_F(CanonMakerNoteTest_916, TagListReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListCsReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListCs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListSiReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListSi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListPaReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListPa();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListCfReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListCf();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListPiReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListPi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListTiReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListTi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListFiReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListPrReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListPr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListMvReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListMv();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListMcReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListMc();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListFcd3ReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListFcd3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListWbiReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListWbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListCoReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListCo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListFcd2ReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListFcd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListFcd1ReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListFcd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListAsReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListAs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListCbiReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListCbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListFlReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListFl();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListMoReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListMo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListPreIReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListPreI();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListCiReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListCi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListAfMiAdjReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListVigCorReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListVigCor();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListVigCor2ReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListLiOpReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListLiOp();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListLeReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListLe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListAmReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListAm();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListMeReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListFilReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListFil();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListHdrReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListHdr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListAfCReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListAfC();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_916, TagListRawBReturnsNonNull_916) {
  auto tagList = CanonMakerNote::tagListRawB();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print functions with various value types
// ============================================================

TEST_F(CanonMakerNoteTest_916, PrintFocalLengthReturnsSameStream_916) {
  UShortValue value;
  value.read("50 0 0 0");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintFocalLengthOutputsNonEmpty_916) {
  UShortValue value;
  value.read("50 0 0 0");
  CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_916, Print0x0008ReturnsSameStream_916) {
  UShortValue value;
  value.read("12345");
  std::ostream& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, Print0x000aReturnsSameStream_916) {
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, Print0x000cReturnsSameStream_916) {
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintCs0x0002ReturnsSameStream_916) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintCsLensTypeReturnsSameStream_916) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintCsLensReturnsSameStream_916) {
  UShortValue value;
  value.read("50 18 1");
  std::ostream& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintLe0x0000ReturnsSameStream_916) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0001ReturnsSameStream_916) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0002ReturnsSameStream_916) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0003ReturnsSameStream_916) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0009ReturnsSameStream_916) {
  UShortValue value;
  value.read("10");
  std::ostream& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x000cReturnsSameStream_916) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x000dReturnsSameStream_916) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x000eReturnsSameStream_916) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0013ReturnsSameStream_916) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0015ReturnsSameStream_916) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0016ReturnsSameStream_916) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0017ReturnsSameStream_916) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0018ReturnsSameStream_916) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintFiFocusDistanceReturnsSameStream_916) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintFiFocusDistanceOutputsNonEmpty_916) {
  UShortValue value;
  value.read("100");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_916, PrintFiFileNumberReturnsSameStream_916) {
  ULongValue value;
  value.read("1234567");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_916, PrintFiFileNumberOutputsNonEmpty_916) {
  ULongValue value;
  value.read("1234567");
  CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for boundary / edge cases with zero values
// ============================================================

TEST_F(CanonMakerNoteTest_916, PrintFiFocusDistanceZero_916) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  // Zero distance should still produce some output
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0001ZeroValue_916) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0002ZeroValue_916) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0003ZeroValue_916) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for print functions with ExifData provided
// ============================================================

TEST_F(CanonMakerNoteTest_916, PrintFocalLengthWithExifData_916) {
  ExifData exifData;
  UShortValue value;
  value.read("50 0 0 0");
  CanonMakerNote::printFocalLength(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_916, PrintCsLensTypeWithExifData_916) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x000eWithExifData_916) {
  ExifData exifData;
  UShortValue value;
  value.read("100");
  CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_916, PrintFiFileNumberWithExifData_916) {
  ExifData exifData;
  ULongValue value;
  value.read("1234567");
  CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests with large values
// ============================================================

TEST_F(CanonMakerNoteTest_916, PrintFiFocusDistanceLargeValue_916) {
  UShortValue value;
  value.read("65535");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_916, Print0x000cLargeValue_916) {
  ULongValue value;
  value.read("4294967295");
  CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_916, PrintCsLensEmptyLikeValues_916) {
  UShortValue value;
  value.read("0 0 0");
  CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for consistency - calling same function twice
// ============================================================

TEST_F(CanonMakerNoteTest_916, PrintFiFocusDistanceConsistency_916) {
  UShortValue value;
  value.read("500");

  std::ostringstream os1, os2;
  CanonMakerNote::printFiFocusDistance(os1, value, nullptr);
  CanonMakerNote::printFiFocusDistance(os2, value, nullptr);
  EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(CanonMakerNoteTest_916, PrintSi0x0009Consistency_916) {
  UShortValue value;
  value.read("5");

  std::ostringstream os1, os2;
  CanonMakerNote::printSi0x0009(os1, value, nullptr);
  CanonMakerNote::printSi0x0009(os2, value, nullptr);
  EXPECT_EQ(os1.str(), os2.str());
}
