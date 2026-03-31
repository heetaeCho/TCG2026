#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_924 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList accessor functions (they should return non-null)
// ============================================================

TEST_F(CanonMakerNoteTest_924, TagListAsReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListAs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListReturnsNonNull_924) {
  auto result = CanonMakerNote::tagList();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListCsReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListCs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListSiReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListSi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListPaReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListPa();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListCfReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListCf();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListPiReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListPi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListTiReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListTi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListFiReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListFi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListPrReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListPr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListMvReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListMv();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListMcReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListMc();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListFcd3ReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListFcd3();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListWbiReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListWbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListCoReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListCo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListFcd2ReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListFcd2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListFcd1ReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListFcd1();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListCbiReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListCbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListFlReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListFl();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListMoReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListMo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListPreIReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListPreI();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListCiReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListCi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListAfMiAdjReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListVigCorReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListVigCor();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListVigCor2ReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListLiOpReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListLiOp();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListLeReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListLe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListAmReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListAm();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListMeReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListMe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListFilReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListFil();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListHdrReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListHdr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListAfCReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListAfC();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_924, TagListRawBReturnsNonNull_924) {
  auto result = CanonMakerNote::tagListRawB();
  EXPECT_NE(result, nullptr);
}

// ============================================================
// Tests for print functions
// ============================================================

TEST_F(CanonMakerNoteTest_924, PrintFocalLengthWithSingleValue_924) {
  UShortValue value;
  value.read("1000");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Output should be non-empty or at least the function should not crash
}

TEST_F(CanonMakerNoteTest_924, PrintFocalLengthWithMultipleValues_924) {
  UShortValue value;
  value.read("1 2 3 4");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, Print0x0008WithValue_924) {
  UShortValue value;
  value.read("12345");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, Print0x000aWithValue_924) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, Print0x000cWithNullExifData_924) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintCs0x0002WithSingleValue_924) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintCsLensTypeWithValue_924) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintCsLensWithThreeValues_924) {
  UShortValue value;
  value.read("50 18 1");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintCsLensWithSingleValue_924) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintLe0x0000WithValue_924) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0001WithValue_924) {
  UShortValue value;
  value.read("96");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0002WithValue_924) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0003WithValue_924) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0009WithValue_924) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x000cWithValue_924) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x000dWithValue_924) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x000eWithNullExifData_924) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0013WithValue_924) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0015WithValue_924) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0016WithValue_924) {
  UShortValue value;
  value.read("32767");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0017WithValue_924) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0018WithValue_924) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintFiFocusDistanceWithValue_924) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintFiFocusDistanceZero_924) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintFiFocusDistanceMaxValue_924) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_924, PrintFiFileNumberWithValue_924) {
  ULongValue value;
  value.read("1234567");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x000eWithExifData_924) {
  ExifData exifData;
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintCsLensTypeWithMetadata_924) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, Print0x000cWithExifData_924) {
  ExifData exifData;
  ULongValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary tests for print functions with zero values
// ============================================================

TEST_F(CanonMakerNoteTest_924, PrintSi0x0001WithZero_924) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0002WithZero_924) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0003WithZero_924) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0009WithZero_924) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintCs0x0002WithZero_924) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for tag list consistency
// ============================================================

TEST_F(CanonMakerNoteTest_924, TagListAsCalledTwiceReturnsSamePointer_924) {
  auto result1 = CanonMakerNote::tagListAs();
  auto result2 = CanonMakerNote::tagListAs();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_924, TagListCalledTwiceReturnsSamePointer_924) {
  auto result1 = CanonMakerNote::tagList();
  auto result2 = CanonMakerNote::tagList();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_924, TagListCsCalledTwiceReturnsSamePointer_924) {
  auto result1 = CanonMakerNote::tagListCs();
  auto result2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(result1, result2);
}

// ============================================================
// Tests with large values
// ============================================================

TEST_F(CanonMakerNoteTest_924, Print0x0008WithLargeValue_924) {
  ULongValue value;
  value.read("4294967295");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x000dWithMaxUShort_924) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0013WithMaxUShort_924) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Test output content for specific known behaviors
// ============================================================

TEST_F(CanonMakerNoteTest_924, PrintFiFocusDistanceProducesOutput_924) {
  UShortValue value;
  value.read("500");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0015ProducesOutput_924) {
  UShortValue value;
  value.read("5");
  CanonMakerNote::printSi0x0015(os, value, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_924, PrintSi0x0016ProducesOutput_924) {
  UShortValue value;
  value.read("100");
  CanonMakerNote::printSi0x0016(os, value, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_924, PrintLe0x0000ProducesOutput_924) {
  UShortValue value;
  value.read("1");
  CanonMakerNote::printLe0x0000(os, value, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}
