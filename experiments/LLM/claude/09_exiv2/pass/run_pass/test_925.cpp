#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_925 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(CanonMakerNoteTest_925, TagListCbiReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListCbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListReturnsNonNull_925) {
  auto result = CanonMakerNote::tagList();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListCsReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListCs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListSiReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListSi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListPaReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListPa();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListCfReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListCf();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListPiReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListPi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListTiReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListTi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListFiReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListFi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListPrReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListPr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListMvReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListMv();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListMcReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListMc();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListFcd3ReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListFcd3();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListWbiReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListWbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListCoReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListCo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListFcd2ReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListFcd2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListFcd1ReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListFcd1();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListAsReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListAs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListFlReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListFl();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListMoReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListMo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListPreIReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListPreI();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListCiReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListCi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListAfMiAdjReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListVigCorReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListVigCor();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListVigCor2ReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListLiOpReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListLiOp();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListLeReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListLe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListAmReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListAm();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListMeReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListMe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListFilReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListFil();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListHdrReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListHdr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListAfCReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListAfC();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_925, TagListRawBReturnsNonNull_925) {
  auto result = CanonMakerNote::tagListRawB();
  EXPECT_NE(result, nullptr);
}

// ============================================================
// Tests for print functions with various Value inputs
// ============================================================

TEST_F(CanonMakerNoteTest_925, PrintFocalLengthReturnsStream_925) {
  UShortValue value;
  value.read("1 50 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintFocalLengthEmptyValue_925) {
  UShortValue value;
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, Print0x0008ReturnsStream_925) {
  UShortValue value;
  value.read("1234");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, Print0x000aReturnsStream_925) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, Print0x000cReturnsStream_925) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintCs0x0002ReturnsStream_925) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintCsLensTypeReturnsStream_925) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintCsLensReturnsStream_925) {
  UShortValue value;
  value.read("50 18 1");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintCsLensEmptyValue_925) {
  UShortValue value;
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintLe0x0000ReturnsStream_925) {
  UShortValue value;
  value.read("4");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0001ReturnsStream_925) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0002ReturnsStream_925) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0003ReturnsStream_925) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0009ReturnsStream_925) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x000cReturnsStream_925) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x000dReturnsStream_925) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x000eReturnsStream_925) {
  UShortValue value;
  value.read("200");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0013ReturnsStream_925) {
  UShortValue value;
  value.read("3");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0015ReturnsStream_925) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0016ReturnsStream_925) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0017ReturnsStream_925) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0018ReturnsStream_925) {
  UShortValue value;
  value.read("32767");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintFiFocusDistanceReturnsStream_925) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintFiFocusDistanceZero_925) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintFiFocusDistanceMaxValue_925) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // 65535 (0xFFFF) is typically "infinite" for Canon
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_925, PrintFiFileNumberReturnsStream_925) {
  ULongValue value;
  value.read("1234567");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintFiFileNumberEmptyValue_925) {
  ULongValue value;
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print functions with boundary values
// ============================================================

TEST_F(CanonMakerNoteTest_925, PrintSi0x0001ZeroValue_925) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0002ZeroValue_925) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0003ZeroValue_925) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x000eWithExifData_925) {
  UShortValue value;
  value.read("400");
  ExifData exifData;
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, Print0x000cWithExifData_925) {
  ULongValue value;
  value.read("87654321");
  ExifData exifData;
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintCsLensTypeWithMetadata_925) {
  UShortValue value;
  value.read("0");
  ExifData exifData;
  auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests ensuring output is non-empty for valid inputs
// ============================================================

TEST_F(CanonMakerNoteTest_925, Print0x0008ProducesOutput_925) {
  UShortValue value;
  value.read("5");
  CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0009ProducesOutput_925) {
  UShortValue value;
  value.read("10");
  CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_925, PrintFiFocusDistanceProducesOutput_925) {
  UShortValue value;
  value.read("500");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0015ProducesOutput_925) {
  UShortValue value;
  value.read("2");
  CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0016ProducesOutput_925) {
  UShortValue value;
  value.read("10");
  CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for consistency: calling same function twice yields same result
// ============================================================

TEST_F(CanonMakerNoteTest_925, TagListCbiConsistent_925) {
  auto result1 = CanonMakerNote::tagListCbi();
  auto result2 = CanonMakerNote::tagListCbi();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_925, TagListConsistent_925) {
  auto result1 = CanonMakerNote::tagList();
  auto result2 = CanonMakerNote::tagList();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_925, TagListCsConsistent_925) {
  auto result1 = CanonMakerNote::tagListCs();
  auto result2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(result1, result2);
}

// ============================================================
// Additional edge case tests for print functions
// ============================================================

TEST_F(CanonMakerNoteTest_925, PrintLe0x0000ZeroValue_925) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_925, PrintCs0x0002ZeroValue_925) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0013ZeroValue_925) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0017ZeroValue_925) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x0018ZeroValue_925) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x000cZeroValue_925) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_925, PrintSi0x000dZeroValue_925) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}
