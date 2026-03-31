#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_913 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (they should return non-null pointers)
// ============================================================

TEST_F(CanonMakerNoteTest_913, TagListPiReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListPi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListReturnsNonNull_913) {
  auto result = CanonMakerNote::tagList();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListCsReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListCs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListSiReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListSi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListPaReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListPa();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListCfReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListCf();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListTiReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListTi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListFiReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListFi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListPrReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListPr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListMvReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListMv();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListMcReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListMc();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListFcd3ReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListFcd3();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListWbiReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListWbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListCoReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListCo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListFcd2ReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListFcd2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListFcd1ReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListFcd1();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListAsReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListAs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListCbiReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListCbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListFlReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListFl();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListMoReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListMo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListPreIReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListPreI();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListCiReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListCi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListAfMiAdjReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListVigCorReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListVigCor();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListVigCor2ReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListLiOpReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListLiOp();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListLeReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListLe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListAmReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListAm();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListMeReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListMe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListFilReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListFil();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListHdrReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListHdr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListAfCReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListAfC();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_913, TagListRawBReturnsNonNull_913) {
  auto result = CanonMakerNote::tagListRawB();
  EXPECT_NE(result, nullptr);
}

// ============================================================
// Tests for print functions
// ============================================================

TEST_F(CanonMakerNoteTest_913, PrintFocalLengthWithSingleValue_913) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // The output should contain something (not empty necessarily, but stream should be valid)
  // We just verify the function returns the stream reference correctly
}

TEST_F(CanonMakerNoteTest_913, PrintFocalLengthWithMultipleValues_913) {
  UShortValue value;
  value.read("1 50 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, Print0x0008WithValue_913) {
  UShortValue value;
  value.read("12345");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, Print0x000aWithValue_913) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, Print0x000cWithNullExifData_913) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintCs0x0002WithValue_913) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintCsLensTypeWithValue_913) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintCsLensWithMultipleValues_913) {
  UShortValue value;
  value.read("50 18 1 1");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintCsLensWithSingleValue_913) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintLe0x0000WithValue_913) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0001WithValue_913) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0002WithValue_913) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0003WithValue_913) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0009WithValue_913) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x000cWithValue_913) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x000dWithValue_913) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x000eWithNullExifData_913) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0013WithValue_913) {
  UShortValue value;
  value.read("2");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0015WithValue_913) {
  UShortValue value;
  value.read("3");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0016WithValue_913) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0017WithZero_913) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0018WithValue_913) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintFiFocusDistanceWithValue_913) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintFiFocusDistanceWithZero_913) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintFiFocusDistanceWithMaxValue_913) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  // 65535 (0xFFFF) typically means infinity for focus distance
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_913, PrintFiFileNumberWithValue_913) {
  ULongValue value;
  value.read("1230456");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x000eWithExifData_913) {
  UShortValue value;
  value.read("100");
  ExifData exifData;
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintCsLensTypeWithExifData_913) {
  UShortValue value;
  value.read("1");
  ExifData exifData;
  auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, Print0x000cWithExifData_913) {
  ULongValue value;
  value.read("0");
  ExifData exifData;
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary tests
// ============================================================

TEST_F(CanonMakerNoteTest_913, PrintSi0x0001WithZeroValue_913) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0002WithZeroValue_913) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0003WithZeroValue_913) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0009WithZeroValue_913) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintFiFileNumberWithZeroValue_913) {
  ULongValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintLe0x0000WithZeroValue_913) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test that tagList functions return consistent results on multiple calls
TEST_F(CanonMakerNoteTest_913, TagListPiConsistentReturns_913) {
  auto result1 = CanonMakerNote::tagListPi();
  auto result2 = CanonMakerNote::tagListPi();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_913, TagListConsistentReturns_913) {
  auto result1 = CanonMakerNote::tagList();
  auto result2 = CanonMakerNote::tagList();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_913, TagListCsConsistentReturns_913) {
  auto result1 = CanonMakerNote::tagListCs();
  auto result2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(result1, result2);
}

// Test that different tagList functions return different pointers
TEST_F(CanonMakerNoteTest_913, TagListDifferentListsAreDifferent_913) {
  auto tagList = CanonMakerNote::tagList();
  auto tagListCs = CanonMakerNote::tagListCs();
  auto tagListSi = CanonMakerNote::tagListSi();
  auto tagListPi = CanonMakerNote::tagListPi();

  EXPECT_NE(tagList, tagListCs);
  EXPECT_NE(tagList, tagListSi);
  EXPECT_NE(tagList, tagListPi);
  EXPECT_NE(tagListCs, tagListSi);
}

// Test printing with large values
TEST_F(CanonMakerNoteTest_913, PrintSi0x0001WithLargeValue_913) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x000cWithLargeValue_913) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, Print0x0008WithZeroValue_913) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_913, PrintCs0x0002WithZeroValue_913) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Output non-emptiness checks for specific known behaviors
TEST_F(CanonMakerNoteTest_913, PrintFiFocusDistanceProducesOutput_913) {
  UShortValue value;
  value.read("500");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0013ProducesOutput_913) {
  UShortValue value;
  value.read("5");
  CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_913, PrintSi0x0015ProducesOutput_913) {
  UShortValue value;
  value.read("10");
  CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}
