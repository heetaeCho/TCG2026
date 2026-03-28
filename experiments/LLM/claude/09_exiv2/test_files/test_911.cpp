#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_911 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tag list accessor tests
// ============================================================

TEST_F(CanonMakerNoteTest_911, TagListPaReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListPa();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListCsReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListCs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListSiReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListSi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListCfReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListCf();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListPiReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListPi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListTiReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListTi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListFiReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListPrReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListPr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListLeReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListLe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListFlReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListFl();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListMoReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListMo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListCoReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListCo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListWbiReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListWbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListMvReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListMv();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListMcReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListMc();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListFcd1ReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListFcd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListFcd2ReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListFcd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListFcd3ReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListFcd3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListAsReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListAs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListCbiReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListCbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListPreIReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListPreI();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListCiReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListCi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListAfMiAdjReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListVigCorReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListVigCor();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListVigCor2ReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListLiOpReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListLiOp();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListAmReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListAm();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListMeReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListFilReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListFil();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListHdrReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListHdr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListAfCReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListAfC();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_911, TagListRawBReturnsNonNull_911) {
  auto tagList = CanonMakerNote::tagListRawB();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Print function tests
// ============================================================

TEST_F(CanonMakerNoteTest_911, PrintFocalLengthWithSingleValue_911) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Output should have some content
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_911, PrintFocalLengthWithMultipleValues_911) {
  UShortValue value;
  value.read("1 100 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, Print0x0008ReturnsStream_911) {
  UShortValue value;
  value.read("12345");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, Print0x000aReturnsStream_911) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, Print0x000cReturnsStream_911) {
  ULongValue value;
  value.read("1234567890");
  ExifData exifData;
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, Print0x000cWithNullExifData_911) {
  ULongValue value;
  value.read("1234567890");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintCs0x0002ReturnsStream_911) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintCsLensTypeReturnsStream_911) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintCsLensReturnsStream_911) {
  UShortValue value;
  value.read("50 18 1");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintCsLensSingleValue_911) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintLe0x0000ReturnsStream_911) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0001ReturnsStream_911) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0002ReturnsStream_911) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0003ReturnsStream_911) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0009ReturnsStream_911) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x000cReturnsStream_911) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x000dReturnsStream_911) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x000eReturnsStream_911) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x000eWithExifData_911) {
  UShortValue value;
  value.read("10");
  ExifData exifData;
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0013ReturnsStream_911) {
  UShortValue value;
  value.read("3");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0015ReturnsStream_911) {
  UShortValue value;
  value.read("2");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0016ReturnsStream_911) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0017ReturnsStream_911) {
  UShortValue value;
  value.read("256");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0018ReturnsStream_911) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintFiFocusDistanceReturnsStream_911) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintFiFocusDistanceZero_911) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintFiFocusDistanceMaxValue_911) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintFiFileNumberReturnsStream_911) {
  ULongValue value;
  value.read("1234567");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintFiFileNumberWithMetadata_911) {
  ULongValue value;
  value.read("1234567");
  ExifData exifData;
  auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary/Edge case tests for print functions
// ============================================================

TEST_F(CanonMakerNoteTest_911, PrintSi0x0001ZeroValue_911) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0002ZeroValue_911) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0003ZeroValue_911) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintCs0x0002ZeroValue_911) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintCsLensTypeZeroValue_911) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0009ZeroValue_911) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x000eZeroValue_911) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0016ZeroValue_911) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintLe0x0000ZeroValue_911) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tag list consistency tests
// ============================================================

TEST_F(CanonMakerNoteTest_911, TagListPaConsistentAcrossCalls_911) {
  auto tagList1 = CanonMakerNote::tagListPa();
  auto tagList2 = CanonMakerNote::tagListPa();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(CanonMakerNoteTest_911, TagListConsistentAcrossCalls_911) {
  auto tagList1 = CanonMakerNote::tagList();
  auto tagList2 = CanonMakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(CanonMakerNoteTest_911, TagListCsConsistentAcrossCalls_911) {
  auto tagList1 = CanonMakerNote::tagListCs();
  auto tagList2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(CanonMakerNoteTest_911, TagListSiConsistentAcrossCalls_911) {
  auto tagList1 = CanonMakerNote::tagListSi();
  auto tagList2 = CanonMakerNote::tagListSi();
  EXPECT_EQ(tagList1, tagList2);
}

// ============================================================
// Large value tests
// ============================================================

TEST_F(CanonMakerNoteTest_911, PrintSi0x0017LargeValue_911) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0018LargeValue_911) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x000dLargeValue_911) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x000cLargeValue_911) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0013LargeValue_911) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0015LargeValue_911) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_911, Print0x0008ProducesOutput_911) {
  UShortValue value;
  value.read("1");
  CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_911, PrintSi0x0001ProducesOutput_911) {
  UShortValue value;
  value.read("160");
  CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}
