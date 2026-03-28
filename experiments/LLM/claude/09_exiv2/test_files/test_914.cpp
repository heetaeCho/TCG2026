#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_914 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tag list accessor tests
// ============================================================

TEST_F(CanonMakerNoteTest_914, TagListTiReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListTi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListCsReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListSiReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListPaReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListPa();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListCfReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListCf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListPiReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListPi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListFiReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListPrReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListPr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListMvReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListMv();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListMcReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListMc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListFcd3ReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListFcd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListWbiReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListWbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListCoReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListCo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListFcd2ReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListFcd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListFcd1ReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListFcd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListAsReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListAs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListCbiReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListCbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListFlReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListFl();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListMoReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListMo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListPreIReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListPreI();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListCiReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListCi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListAfMiAdjReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListVigCorReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListVigCor();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListVigCor2ReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListLiOpReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListLiOp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListLeReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListLe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListAmReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListAm();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListMeReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListFilReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListFil();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListHdrReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListHdr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListAfCReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListAfC();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_914, TagListRawBReturnsNonNull_914) {
  auto tagList = CanonMakerNote::tagListRawB();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Print function tests
// ============================================================

TEST_F(CanonMakerNoteTest_914, PrintFocalLengthReturnsSameStream_914) {
  UShortValue value;
  value.read("50 0 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintFocalLengthWithSingleValue_914) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Output should not be empty
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_914, Print0x0008ReturnsSameStream_914) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, Print0x000aReturnsSameStream_914) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, Print0x000cReturnsSameStream_914) {
  ULongValue value;
  value.read("1234567890");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintCs0x0002ReturnsSameStream_914) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintCsLensTypeReturnsSameStream_914) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintCsLensReturnsSameStream_914) {
  UShortValue value;
  value.read("50 0 50");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintCsLensSingleValue_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintLe0x0000ReturnsSameStream_914) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x0001ReturnsSameStream_914) {
  UShortValue value;
  value.read("96");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x0002ReturnsSameStream_914) {
  UShortValue value;
  value.read("168");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x0003ReturnsSameStream_914) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x0009ReturnsSameStream_914) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x000cReturnsSameStream_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x000dReturnsSameStream_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x000eReturnsSameStream_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x0013ReturnsSameStream_914) {
  UShortValue value;
  value.read("3");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x0015ReturnsSameStream_914) {
  UShortValue value;
  value.read("32767");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x0016ReturnsSameStream_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x0017ReturnsSameStream_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x0018ReturnsSameStream_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintFiFocusDistanceReturnsSameStream_914) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintFiFocusDistanceZero_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // When focus distance is 0, it might print "inf" or similar
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_914, PrintFiFocusDistanceMaxValue_914) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintFiFileNumberReturnsSameStream_914) {
  ULongValue value;
  value.read("1001234");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintFiFileNumberZero_914) {
  ULongValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary tests for print functions with zero/edge values
// ============================================================

TEST_F(CanonMakerNoteTest_914, PrintSi0x0001ZeroValue_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x0002ZeroValue_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x0003ZeroValue_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_914, PrintCs0x0002ZeroValue_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_914, Print0x0008ZeroValue_914) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests with ExifData provided (non-null metadata)
// ============================================================

TEST_F(CanonMakerNoteTest_914, PrintCsLensTypeWithMetadata_914) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x000eWithMetadata_914) {
  ExifData exifData;
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintFiFileNumberWithMetadata_914) {
  ExifData exifData;
  ULongValue value;
  value.read("1230456");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, PrintFocalLengthWithMetadata_914) {
  ExifData exifData;
  UShortValue value;
  value.read("50 0 50 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_914, Print0x000cWithMetadata_914) {
  ExifData exifData;
  ULongValue value;
  value.read("1234567890");
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Consistency: calling same function twice produces same output
// ============================================================

TEST_F(CanonMakerNoteTest_914, PrintSi0x0009Consistency_914) {
  UShortValue value;
  value.read("5");

  std::ostringstream os1, os2;
  CanonMakerNote::printSi0x0009(os1, value, nullptr);
  CanonMakerNote::printSi0x0009(os2, value, nullptr);
  EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(CanonMakerNoteTest_914, TagListTiConsistency_914) {
  auto tagList1 = CanonMakerNote::tagListTi();
  auto tagList2 = CanonMakerNote::tagListTi();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(CanonMakerNoteTest_914, TagListConsistency_914) {
  auto tagList1 = CanonMakerNote::tagList();
  auto tagList2 = CanonMakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

// ============================================================
// Test tag list entries have valid structure
// ============================================================

TEST_F(CanonMakerNoteTest_914, TagListFirstEntryHasValidTag_914) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  // The first tag info entry should have a tag >= 0
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(CanonMakerNoteTest_914, TagListTiFirstEntryHasValidTag_914) {
  auto tagList = CanonMakerNote::tagListTi();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(CanonMakerNoteTest_914, TagListSiFirstEntryHasValidTag_914) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(CanonMakerNoteTest_914, TagListCsFirstEntryHasValidTag_914) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(CanonMakerNoteTest_914, TagListFiFirstEntryHasValidTag_914) {
  auto tagList = CanonMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}

// Large value boundary test
TEST_F(CanonMakerNoteTest_914, PrintSi0x0015MaxUShort_914) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_914, PrintSi0x0016MaxUShort_914) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}
