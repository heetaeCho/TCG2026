#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_927 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// Tag list function tests
// =============================================================================

TEST_F(CanonMakerNoteTest_927, TagListMoIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListMo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListIsNotNull_927) {
  auto tagList = CanonMakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListCsIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListCs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListSiIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListSi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListPaIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListPa();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListCfIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListCf();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListPiIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListPi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListTiIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListTi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListFiIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListPrIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListPr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListMvIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListMv();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListMcIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListMc();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListFcd3IsNotNull_927) {
  auto tagList = CanonMakerNote::tagListFcd3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListWbiIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListWbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListCoIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListCo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListFcd2IsNotNull_927) {
  auto tagList = CanonMakerNote::tagListFcd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListFcd1IsNotNull_927) {
  auto tagList = CanonMakerNote::tagListFcd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListAsIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListAs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListCbiIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListCbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListFlIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListFl();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListPreIIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListPreI();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListCiIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListCi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListAfMiAdjIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListVigCorIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListVigCor();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListVigCor2IsNotNull_927) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListLiOpIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListLiOp();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListLeIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListLe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListAmIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListAm();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListMeIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListFilIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListFil();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListHdrIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListHdr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListAfCIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListAfC();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_927, TagListRawBIsNotNull_927) {
  auto tagList = CanonMakerNote::tagListRawB();
  EXPECT_NE(tagList, nullptr);
}

// =============================================================================
// Print function tests
// =============================================================================

TEST_F(CanonMakerNoteTest_927, PrintFocalLengthWithSingleValue_927) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  // The function should return the same stream reference
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintFocalLengthWithMultipleValues_927) {
  UShortValue value;
  // FocalLength tag typically has 4 values: FocalType, FocalLength, FocalPlaneXSize, FocalPlaneYSize
  value.read("1 50 0 0");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Should have written something
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_927, Print0x0008WithSingleValue_927) {
  UShortValue value;
  value.read("12345");
  std::ostream& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, Print0x000aWithValue_927) {
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, Print0x000cWithValue_927) {
  ULongValue value;
  value.read("12345678");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, Print0x000cWithNullExifData_927) {
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintCs0x0002WithSingleValue_927) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintCsLensTypeWithValue_927) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintCsLensWithValues_927) {
  UShortValue value;
  // CsLens typically has 3 values: short focal, long focal, focal units
  value.read("50 200 1");
  std::ostream& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_927, PrintLe0x0000WithValue_927) {
  UShortValue value;
  value.read("3");
  std::ostream& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x0001WithValue_927) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x0002WithValue_927) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x0003WithValue_927) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x0009WithValue_927) {
  UShortValue value;
  value.read("10");
  std::ostream& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x000cWithValue_927) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x000dWithValue_927) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x000eWithNullExifData_927) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x000eWithExifData_927) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x0013WithValue_927) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x0015WithValue_927) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x0016WithValue_927) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x0017WithValue_927) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x0018WithValue_927) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintFiFocusDistanceWithValue_927) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_927, PrintFiFocusDistanceWithZero_927) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintFiFocusDistanceWithMaxValue_927) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintFiFileNumberWithValue_927) {
  ULongValue value;
  value.read("1234567");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintFiFileNumberWithExifData_927) {
  ULongValue value;
  value.read("1234567");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Boundary condition tests for print functions
// =============================================================================

TEST_F(CanonMakerNoteTest_927, PrintSi0x0001WithZeroValue_927) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x0002WithZeroValue_927) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x0003WithZeroValue_927) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintCsLensWithZeroFocalUnits_927) {
  UShortValue value;
  // Test with zero focal units - boundary case
  value.read("50 200 0");
  std::ostream& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintCsLensTypeWithZeroValue_927) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintCsLensTypeWithMetadata_927) {
  UShortValue value;
  value.read("1");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintSi0x0009WithZeroValue_927) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_927, PrintCs0x0002WithZeroValue_927) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Tag list consistency tests
// =============================================================================

TEST_F(CanonMakerNoteTest_927, TagListFirstEntryHasValidTag_927) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  // The first entry in the tag list should have tag_ >= 0 (or be a sentinel)
  // We verify it's accessible without crashing
  EXPECT_GE(tagList->tag_, 0);
}

TEST_F(CanonMakerNoteTest_927, TagListMoFirstEntryAccessible_927) {
  auto tagList = CanonMakerNote::tagListMo();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList->tag_, 0);
}

TEST_F(CanonMakerNoteTest_927, TagListCsFirstEntryAccessible_927) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList->tag_, 0);
}

TEST_F(CanonMakerNoteTest_927, TagListSiFirstEntryAccessible_927) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList->tag_, 0);
}

TEST_F(CanonMakerNoteTest_927, TagListLeFirstEntryAccessible_927) {
  auto tagList = CanonMakerNote::tagListLe();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList->tag_, 0);
}

TEST_F(CanonMakerNoteTest_927, TagListFiFirstEntryAccessible_927) {
  auto tagList = CanonMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList->tag_, 0);
}
