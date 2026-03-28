#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_915 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(CanonMakerNoteTest_915, TagListFiReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListFi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListReturnsNonNull_915) {
  auto result = CanonMakerNote::tagList();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListCsReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListCs();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListSiReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListSi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListPaReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListPa();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListCfReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListCf();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListPiReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListPi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListTiReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListTi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListPrReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListPr();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListLeReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListLe();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListFlReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListFl();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListMoReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListMo();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListMvReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListMv();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListMcReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListMc();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListWbiReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListWbi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListCoReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListCo();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListFcd1ReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListFcd1();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListFcd2ReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListFcd2();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListFcd3ReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListFcd3();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListAsReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListAs();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListCbiReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListCbi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListPreIReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListPreI();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListCiReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListCi();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListAfMiAdjReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListAfMiAdj();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListVigCorReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListVigCor();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListVigCor2ReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListVigCor2();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListLiOpReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListLiOp();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListAmReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListAm();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListMeReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListMe();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListFilReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListFil();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListHdrReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListHdr();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListAfCReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListAfC();
  ASSERT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_915, TagListRawBReturnsNonNull_915) {
  auto result = CanonMakerNote::tagListRawB();
  ASSERT_NE(result, nullptr);
}

// ============================================================
// Tests for print functions
// ============================================================

TEST_F(CanonMakerNoteTest_915, PrintFocalLengthWithSingleValue_915) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Output should not be empty
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintFocalLengthWithMultipleValues_915) {
  UShortValue value;
  value.read("1 50 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, Print0x0008WithValue_915) {
  UShortValue value;
  value.read("12345");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, Print0x000aWithValue_915) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, Print0x000cWithNullExifData_915) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintCs0x0002WithValue_915) {
  UShortValue value;
  value.read("2");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintCsLensTypeWithSingleValue_915) {
  UShortValue value;
  value.read("137");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintCsLensWithThreeValues_915) {
  UShortValue value;
  value.read("70 24 1");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintCsLensWithEmptyValue_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0001WithValue_915) {
  UShortValue value;
  value.read("96");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0002WithValue_915) {
  UShortValue value;
  value.read("160");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0003WithValue_915) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0009WithValue_915) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x000cWithValue_915) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x000dWithValue_915) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x000eWithNullExifData_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x000eWithExifData_915) {
  UShortValue value;
  value.read("10");
  ExifData exifData;
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0013WithValue_915) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0015WithValue_915) {
  UShortValue value;
  value.read("3");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0016WithValue_915) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0017WithValue_915) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0018WithValue_915) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintLe0x0000WithValue_915) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintFiFocusDistanceWithValue_915) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintFiFocusDistanceWithZero_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintFiFileNumberWithNullMetadata_915) {
  UShortValue value;
  value.read("1234");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, PrintFiFileNumberWithExifData_915) {
  UShortValue value;
  value.read("5678");
  ExifData exifData;
  auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for print functions with boundary values
// ============================================================

TEST_F(CanonMakerNoteTest_915, PrintSi0x0001WithZeroValue_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0002WithZeroValue_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0003WithZeroValue_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintCs0x0002WithZeroValue_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0009WithZeroValue_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x000dWithZeroValue_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0013WithZeroValue_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0015WithZeroValue_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintFiFocusDistanceMaxValue_915) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintLe0x0000WithZeroValue_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, Print0x0008WithZeroValue_915) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, Print0x000aWithZeroValue_915) {
  ULongValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Test: Return value is the same stream reference
// ============================================================

TEST_F(CanonMakerNoteTest_915, PrintSi0x0016ReturnsSameStream_915) {
  UShortValue value;
  value.read("0");
  std::ostringstream myOs;
  auto& result = CanonMakerNote::printSi0x0016(myOs, value, nullptr);
  EXPECT_EQ(&result, &myOs);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0017ReturnsSameStream_915) {
  UShortValue value;
  value.read("0");
  std::ostringstream myOs;
  auto& result = CanonMakerNote::printSi0x0017(myOs, value, nullptr);
  EXPECT_EQ(&result, &myOs);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x0018ReturnsSameStream_915) {
  UShortValue value;
  value.read("0");
  std::ostringstream myOs;
  auto& result = CanonMakerNote::printSi0x0018(myOs, value, nullptr);
  EXPECT_EQ(&result, &myOs);
}

TEST_F(CanonMakerNoteTest_915, PrintSi0x000cReturnsSameStream_915) {
  UShortValue value;
  value.read("0");
  std::ostringstream myOs;
  auto& result = CanonMakerNote::printSi0x000c(myOs, value, nullptr);
  EXPECT_EQ(&result, &myOs);
}

// ============================================================
// Test with large value
// ============================================================

TEST_F(CanonMakerNoteTest_915, PrintSi0x0001WithLargeValue_915) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_915, PrintCsLensTypeWithLargeValue_915) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_915, Print0x000cWithExifData_915) {
  UShortValue value;
  value.read("50");
  ExifData exifData;
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Multiple tagList calls return consistent results
// ============================================================

TEST_F(CanonMakerNoteTest_915, TagListFiConsistentOnMultipleCalls_915) {
  auto result1 = CanonMakerNote::tagListFi();
  auto result2 = CanonMakerNote::tagListFi();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_915, TagListConsistentOnMultipleCalls_915) {
  auto result1 = CanonMakerNote::tagList();
  auto result2 = CanonMakerNote::tagList();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_915, TagListCsConsistentOnMultipleCalls_915) {
  auto result1 = CanonMakerNote::tagListCs();
  auto result2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_915, TagListSiConsistentOnMultipleCalls_915) {
  auto result1 = CanonMakerNote::tagListSi();
  auto result2 = CanonMakerNote::tagListSi();
  EXPECT_EQ(result1, result2);
}
