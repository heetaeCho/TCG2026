#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_933 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================================
// tagList* function tests - verify they return non-null function pointers / arrays
// ============================================================================

TEST_F(CanonMakerNoteTest_933, TagListLiOpReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListLiOp();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListReturnsNonNull_933) {
  auto result = CanonMakerNote::tagList();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListCsReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListCs();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListSiReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListSi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListPaReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListPa();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListCfReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListCf();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListPiReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListPi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListTiReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListTi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListFiReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListFi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListPrReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListPr();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListMvReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListMv();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListMcReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListMc();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListFcd3ReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListFcd3();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListWbiReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListWbi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListCoReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListCo();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListFcd2ReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListFcd2();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListFcd1ReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListFcd1();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListAsReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListAs();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListCbiReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListCbi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListFlReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListFl();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListMoReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListMo();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListPreIReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListPreI();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListCiReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListCi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListAfMiAdjReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListAfMiAdj();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListVigCorReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListVigCor();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListVigCor2ReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListVigCor2();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListLeReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListLe();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListAmReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListAm();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListMeReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListMe();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListFilReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListFil();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListHdrReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListHdr();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListAfCReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListAfC();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_933, TagListRawBReturnsNonNull_933) {
  auto result = CanonMakerNote::tagListRawB();
  ASSERT_NE(result, nullptr);
}

// ============================================================================
// Print function tests
// ============================================================================

TEST_F(CanonMakerNoteTest_933, PrintFocalLengthWithSingleValue_933) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Output should contain something (we don't know exact format, just non-empty or same stream)
}

TEST_F(CanonMakerNoteTest_933, PrintFocalLengthWithMultipleValues_933) {
  UShortValue value;
  value.read("1 50 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, Print0x0008WithValue_933) {
  UShortValue value;
  value.read("1234");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, Print0x000aWithValue_933) {
  ULongValue value;
  value.read("5678");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, Print0x000cWithNullExifData_933) {
  ULongValue value;
  value.read("100");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintCs0x0002WithValue_933) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintCsLensTypeWithValue_933) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintCsLensWithMultipleValues_933) {
  UShortValue value;
  value.read("70 200 1 0");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintCsLensWithSingleValue_933) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintLe0x0000WithValue_933) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0001WithValue_933) {
  UShortValue value;
  value.read("96");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0002WithValue_933) {
  UShortValue value;
  value.read("160");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0003WithValue_933) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0009WithValue_933) {
  UShortValue value;
  value.read("30");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x000cWithValue_933) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x000dWithValue_933) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x000eWithNullExifData_933) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0013WithValue_933) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0015WithValue_933) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0016WithValue_933) {
  UShortValue value;
  value.read("128");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0017WithValue_933) {
  UShortValue value;
  value.read("200");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0018WithValue_933) {
  UShortValue value;
  value.read("3");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintFiFocusDistanceWithValue_933) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintFiFocusDistanceWithZero_933) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintFiFocusDistanceWithMaxValue_933) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // 65535 (0xFFFF) often means "infinite" in Canon data
}

TEST_F(CanonMakerNoteTest_933, PrintFiFileNumberWithValue_933) {
  ULongValue value;
  value.read("1180001");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintFiFileNumberWithZero_933) {
  ULongValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================================
// Test with ExifData provided
// ============================================================================

TEST_F(CanonMakerNoteTest_933, PrintSi0x000eWithExifData_933) {
  UShortValue value;
  value.read("10");
  ExifData exifData;
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintCsLensTypeWithExifData_933) {
  UShortValue value;
  value.read("255");
  ExifData exifData;
  auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, Print0x000cWithExifData_933) {
  ULongValue value;
  value.read("100");
  ExifData exifData;
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintFiFileNumberWithExifData_933) {
  ULongValue value;
  value.read("1230456");
  ExifData exifData;
  auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintFocalLengthWithExifData_933) {
  UShortValue value;
  value.read("1 50 0 0");
  ExifData exifData;
  auto& result = CanonMakerNote::printFocalLength(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================================
// Boundary and edge cases
// ============================================================================

TEST_F(CanonMakerNoteTest_933, PrintSi0x0001WithZeroValue_933) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0002WithZeroValue_933) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0003WithZeroValue_933) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0015WithMaxValue_933) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x0016WithZeroValue_933) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintCs0x0002WithZero_933) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_933, PrintLe0x0000WithZero_933) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================================
// Verify stream output is not empty for typical values
// ============================================================================

TEST_F(CanonMakerNoteTest_933, PrintSi0x0009ProducesOutput_933) {
  UShortValue value;
  value.read("10");
  CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x000cProducesOutput_933) {
  UShortValue value;
  value.read("50");
  CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_933, PrintFiFocusDistanceProducesOutput_933) {
  UShortValue value;
  value.read("200");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_933, Print0x0008ProducesOutput_933) {
  UShortValue value;
  value.read("12345");
  CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_933, PrintSi0x000dProducesOutput_933) {
  UShortValue value;
  value.read("5");
  CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================================
// Consistency tests - calling same function twice yields same result
// ============================================================================

TEST_F(CanonMakerNoteTest_933, TagListLiOpConsistency_933) {
  auto result1 = CanonMakerNote::tagListLiOp();
  auto result2 = CanonMakerNote::tagListLiOp();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_933, TagListConsistency_933) {
  auto result1 = CanonMakerNote::tagList();
  auto result2 = CanonMakerNote::tagList();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_933, TagListCsConsistency_933) {
  auto result1 = CanonMakerNote::tagListCs();
  auto result2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(result1, result2);
}
