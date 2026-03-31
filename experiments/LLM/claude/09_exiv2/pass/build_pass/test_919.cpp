#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_919 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ==================== tagList* tests ====================

TEST_F(CanonMakerNoteTest_919, TagListFcd3ReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListFcd3();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListReturnsNonNull_919) {
  auto result = CanonMakerNote::tagList();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListCsReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListCs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListSiReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListSi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListPaReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListPa();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListCfReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListCf();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListPiReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListPi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListTiReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListTi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListFiReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListFi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListPrReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListPr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListMvReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListMv();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListMcReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListMc();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListWbiReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListWbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListCoReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListCo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListFcd2ReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListFcd2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListFcd1ReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListFcd1();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListAsReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListAs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListCbiReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListCbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListFlReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListFl();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListMoReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListMo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListPreIReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListPreI();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListCiReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListCi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListAfMiAdjReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListVigCorReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListVigCor();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListVigCor2ReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListLiOpReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListLiOp();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListLeReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListLe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListAmReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListAm();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListMeReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListMe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListFilReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListFil();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListHdrReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListHdr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListAfCReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListAfC();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_919, TagListRawBReturnsNonNull_919) {
  auto result = CanonMakerNote::tagListRawB();
  EXPECT_NE(result, nullptr);
}

// ==================== Print function tests ====================

TEST_F(CanonMakerNoteTest_919, PrintFocalLengthWithSingleValue_919) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Output should contain something (we don't check exact format)
  // Just verify it doesn't crash and returns the stream
}

TEST_F(CanonMakerNoteTest_919, PrintFocalLengthWithMultipleValues_919) {
  UShortValue value;
  value.read("1 50 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, Print0x0008WithSingleValue_919) {
  UShortValue value;
  value.read("12345");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, Print0x000aWithSingleValue_919) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintCs0x0002WithValue_919) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintCsLensTypeWithValue_919) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintCsLensWithMultipleValues_919) {
  UShortValue value;
  value.read("50 18 1 1");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintCsLensWithSingleValue_919) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintLe0x0000WithValue_919) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0001WithValue_919) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0002WithValue_919) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0003WithValue_919) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0009WithValue_919) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x000cWithValue_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x000dWithValue_919) {
  UShortValue value;
  value.read("128");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x000eWithNullExifData_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0013WithValue_919) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0015WithValue_919) {
  UShortValue value;
  value.read("32767");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0016WithValue_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0017WithValue_919) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0018WithValue_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintFiFocusDistanceWithValue_919) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintFiFocusDistanceWithZero_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_919, PrintFiFocusDistanceWithMaxValue_919) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintFiFileNumberWithValue_919) {
  ULongValue value;
  value.read("1234567");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, Print0x000cWithValue_919) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0001WithZeroValue_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0002WithZeroValue_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// ==================== Consistency tests ====================

TEST_F(CanonMakerNoteTest_919, TagListFcd3ReturnsSamePointerOnMultipleCalls_919) {
  auto result1 = CanonMakerNote::tagListFcd3();
  auto result2 = CanonMakerNote::tagListFcd3();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_919, TagListReturnsSamePointerOnMultipleCalls_919) {
  auto result1 = CanonMakerNote::tagList();
  auto result2 = CanonMakerNote::tagList();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_919, TagListCsReturnsSamePointerOnMultipleCalls_919) {
  auto result1 = CanonMakerNote::tagListCs();
  auto result2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_919, TagListSiReturnsSamePointerOnMultipleCalls_919) {
  auto result1 = CanonMakerNote::tagListSi();
  auto result2 = CanonMakerNote::tagListSi();
  EXPECT_EQ(result1, result2);
}

// ==================== Print with ExifData tests ====================

TEST_F(CanonMakerNoteTest_919, PrintSi0x000eWithExifData_919) {
  ExifData exifData;
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintCsLensTypeWithExifData_919) {
  ExifData exifData;
  UShortValue value;
  value.read("137");
  auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintFiFileNumberWithExifData_919) {
  ExifData exifData;
  ULongValue value;
  value.read("1000100");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintFocalLengthWithExifData_919) {
  ExifData exifData;
  UShortValue value;
  value.read("1 50 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ==================== Boundary value tests ====================

TEST_F(CanonMakerNoteTest_919, PrintSi0x0009WithZero_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x000dWithZero_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintLe0x0000WithZero_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0015WithZero_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0013WithZero_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, Print0x000cWithZeroValue_919) {
  ULongValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, Print0x0008WithZeroValue_919) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_919, Print0x000aWithZeroValue_919) {
  ULongValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ==================== Output non-empty tests ====================

TEST_F(CanonMakerNoteTest_919, PrintSi0x0003OutputNotEmpty_919) {
  UShortValue value;
  value.read("160");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0016OutputNotEmpty_919) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0017OutputNotEmpty_919) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_919, PrintSi0x0018OutputNotEmpty_919) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}
