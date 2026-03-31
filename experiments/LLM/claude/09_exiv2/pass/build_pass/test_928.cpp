#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_928 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions - verify they return non-null
// ============================================================

TEST_F(CanonMakerNoteTest_928, TagListReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListCsReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListCs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListSiReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListSi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListPaReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListPa();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListCfReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListCf();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListPiReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListPi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListTiReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListTi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListFiReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListPrReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListPr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListMvReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListMv();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListMcReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListMc();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListFcd3ReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListFcd3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListWbiReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListWbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListCoReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListCo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListFcd2ReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListFcd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListFcd1ReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListFcd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListAsReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListAs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListCbiReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListCbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListFlReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListFl();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListMoReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListMo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListPreIReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListPreI();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListCiReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListCi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListAfMiAdjReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListVigCorReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListVigCor();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListVigCor2ReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListLiOpReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListLiOp();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListLeReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListLe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListAmReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListAm();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListMeReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListFilReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListFil();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListHdrReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListHdr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListAfCReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListAfC();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_928, TagListRawBReturnsNonNull_928) {
  auto tagList = CanonMakerNote::tagListRawB();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print functions with various values
// ============================================================

TEST_F(CanonMakerNoteTest_928, PrintFocalLengthWithSingleValue_928) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Output should be non-empty or at least the function should not crash
}

TEST_F(CanonMakerNoteTest_928, PrintFocalLengthWithMultipleValues_928) {
  UShortValue value;
  value.read("1 50 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, Print0x0008WithValue_928) {
  UShortValue value;
  value.read("12345");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, Print0x000aWithValue_928) {
  ULongValue value;
  value.read("100");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, Print0x000cWithNullExifData_928) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintCs0x0002WithValue_928) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintCsLensTypeWithSingleValue_928) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintCsLensWithThreeValues_928) {
  UShortValue value;
  value.read("50 18 1");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintCsLensWithSingleValue_928) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintLe0x0000WithValue_928) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0001WithValue_928) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0002WithValue_928) {
  UShortValue value;
  value.read("160");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0003WithValue_928) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0009WithValue_928) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x000cWithValue_928) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x000dWithValue_928) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x000eWithNullExifData_928) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0013WithValue_928) {
  UShortValue value;
  value.read("3");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0015WithValue_928) {
  UShortValue value;
  value.read("2");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0016WithValue_928) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0017WithValue_928) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0018WithValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintFiFocusDistanceWithValue_928) {
  UShortValue value;
  value.read("500");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintFiFocusDistanceWithZero_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Zero might indicate infinity or unknown
}

TEST_F(CanonMakerNoteTest_928, PrintFiFocusDistanceWithMaxValue_928) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintFiFileNumberWithValue_928) {
  ULongValue value;
  value.read("1234567");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintFiFileNumberWithZero_928) {
  ULongValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print functions producing non-empty output
// ============================================================

TEST_F(CanonMakerNoteTest_928, PrintSi0x0002ProducesOutput_928) {
  UShortValue value;
  value.read("160");
  CanonMakerNote::printSi0x0002(os, value, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0009ProducesOutput_928) {
  UShortValue value;
  value.read("5");
  CanonMakerNote::printSi0x0009(os, value, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0001ProducesOutput_928) {
  UShortValue value;
  value.read("96");
  CanonMakerNote::printSi0x0001(os, value, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// ============================================================
// Tests with ExifData provided
// ============================================================

TEST_F(CanonMakerNoteTest_928, PrintSi0x000eWithExifData_928) {
  ExifData exifData;
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintCsLensTypeWithExifData_928) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintFiFileNumberWithExifData_928) {
  ExifData exifData;
  ULongValue value;
  value.read("1000");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintFocalLengthWithExifData_928) {
  ExifData exifData;
  UShortValue value;
  value.read("1 50 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, Print0x000cWithExifData_928) {
  ExifData exifData;
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary tests for print functions
// ============================================================

TEST_F(CanonMakerNoteTest_928, PrintSi0x0001WithZeroValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0002WithZeroValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0003WithZeroValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintCs0x0002WithZeroValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0013WithZeroValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0015WithZeroValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0016WithZeroValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0017WithZeroValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x0018WithLargeValue_928) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x000cWithZeroValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintSi0x000dWithZeroValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, PrintLe0x0000WithZeroValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, Print0x0008WithZeroValue_928) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_928, Print0x000aWithZeroValue_928) {
  ULongValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Consistency tests - calling tagList multiple times returns same
// ============================================================

TEST_F(CanonMakerNoteTest_928, TagListConsistentAcrossCalls_928) {
  auto list1 = CanonMakerNote::tagList();
  auto list2 = CanonMakerNote::tagList();
  EXPECT_EQ(list1, list2);
}

TEST_F(CanonMakerNoteTest_928, TagListPreIConsistentAcrossCalls_928) {
  auto list1 = CanonMakerNote::tagListPreI();
  auto list2 = CanonMakerNote::tagListPreI();
  EXPECT_EQ(list1, list2);
}

TEST_F(CanonMakerNoteTest_928, TagListCsConsistentAcrossCalls_928) {
  auto list1 = CanonMakerNote::tagListCs();
  auto list2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(list1, list2);
}
