#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_940 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagListRawB
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListRawBReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListRawB();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagList (main tag list)
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListCs
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListCsReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListCs();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListSi
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListSiReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListSi();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListPa
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListPaReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListPa();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListCf
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListCfReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListCf();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListPi
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListPiReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListPi();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListTi
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListTiReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListTi();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListFi
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListFiReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListPr
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListPrReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListPr();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListLe
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListLeReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListLe();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListFl
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListFlReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListFl();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListAfC
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListAfCReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListAfC();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListHdr
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListHdrReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListHdr();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListFil
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListFilReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListFil();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListMe
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListMeReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListAm
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListAmReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListAm();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListMv
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListMvReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListMv();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListMc
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListMcReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListMc();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListFcd1, Fcd2, Fcd3
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListFcd1ReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListFcd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_940, TagListFcd2ReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListFcd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_940, TagListFcd3ReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListFcd3();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListWbi
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListWbiReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListWbi();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListCo
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListCoReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListCo();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListAs
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListAsReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListAs();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListCbi
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListCbiReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListCbi();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListMo
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListMoReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListMo();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListPreI
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListPreIReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListPreI();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListCi
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListCiReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListCi();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListAfMiAdj
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListAfMiAdjReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListVigCor
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListVigCorReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListVigCor();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListVigCor2
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListVigCor2ReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for tagListLiOp
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListLiOpReturnsNonNull_940) {
  auto tagList = CanonMakerNote::tagListLiOp();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Print function tests
// ============================================================

TEST_F(CanonMakerNoteTest_940, PrintFocalLengthWithSingleValue_940) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Output should be non-empty (some representation of the value)
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_940, PrintFocalLengthWithMultipleValues_940) {
  UShortValue value;
  value.read("1 50 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_940, Print0x0008WithValue_940) {
  UShortValue value;
  value.read("12345");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, Print0x000aWithValue_940) {
  ULongValue value;
  value.read("100");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintCs0x0002WithValue_940) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_940, PrintCsLensWithThreeValues_940) {
  UShortValue value;
  value.read("50 18 1");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_940, PrintCsLensTypeSingleValue_940) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x0001WithValue_940) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x0002WithValue_940) {
  UShortValue value;
  value.read("160");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x0003WithValue_940) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x0009WithValue_940) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x000cWithValue_940) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x000dWithValue_940) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x000eWithValue_940) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x0013WithValue_940) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x0015WithValue_940) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x0016WithValue_940) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x0017WithValue_940) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintSi0x0018WithValue_940) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintLe0x0000WithValue_940) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintFiFocusDistanceWithValue_940) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_940, PrintFiFocusDistanceZero_940) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_940, PrintFiFileNumberWithValue_940) {
  ULongValue value;
  value.read("1000");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, Print0x000cWithNullExifData_940) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Test that tagListRawB returns same pointer on multiple calls (constexpr)
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListRawBConsistentAcrossCalls_940) {
  auto tagList1 = CanonMakerNote::tagListRawB();
  auto tagList2 = CanonMakerNote::tagListRawB();
  EXPECT_EQ(tagList1, tagList2);
}

// ============================================================
// Test that tagList returns same pointer on multiple calls
// ============================================================

TEST_F(CanonMakerNoteTest_940, TagListConsistentAcrossCalls_940) {
  auto tagList1 = CanonMakerNote::tagList();
  auto tagList2 = CanonMakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

// ============================================================
// Boundary: large value in print functions
// ============================================================

TEST_F(CanonMakerNoteTest_940, PrintSi0x0002WithLargeValue_940) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintFiFocusDistanceMaxUShort_940) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// ============================================================
// Test with ExifData provided
// ============================================================

TEST_F(CanonMakerNoteTest_940, PrintSi0x000eWithExifData_940) {
  UShortValue value;
  value.read("100");
  ExifData exifData;
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintCsLensTypeWithExifData_940) {
  UShortValue value;
  value.read("1");
  ExifData exifData;
  auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_940, PrintFiFileNumberWithExifData_940) {
  ULongValue value;
  value.read("5000100");
  ExifData exifData;
  auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_940, PrintFocalLengthWithExifData_940) {
  UShortValue value;
  value.read("1 50 0 0");
  ExifData exifData;
  auto& result = CanonMakerNote::printFocalLength(os, value, &exifData);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_940, Print0x000cWithExifData_940) {
  UShortValue value;
  value.read("50");
  ExifData exifData;
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Test print functions return the same ostream reference
// ============================================================

TEST_F(CanonMakerNoteTest_940, PrintSi0x0001ReturnsSameStream_940) {
  UShortValue value;
  value.read("0");
  std::ostringstream localOs;
  auto& result = CanonMakerNote::printSi0x0001(localOs, value, nullptr);
  EXPECT_EQ(&result, &localOs);
}
