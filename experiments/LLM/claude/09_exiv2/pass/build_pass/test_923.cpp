#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_923 : public ::testing::Test {
 protected:
  std::ostringstream os_;
};

// =============================================================================
// Tests for tagList functions - verify they return non-null pointers
// =============================================================================

TEST_F(CanonMakerNoteTest_923, TagListFcd1ReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListFcd1();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListReturnsNonNull_923) {
  auto result = CanonMakerNote::tagList();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListCsReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListCs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListSiReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListSi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListPaReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListPa();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListCfReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListCf();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListPiReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListPi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListTiReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListTi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListFiReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListFi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListPrReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListPr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListMvReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListMv();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListMcReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListMc();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListFcd3ReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListFcd3();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListWbiReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListWbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListCoReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListCo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListFcd2ReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListFcd2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListAsReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListAs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListCbiReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListCbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListFlReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListFl();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListMoReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListMo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListPreIReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListPreI();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListCiReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListCi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListAfMiAdjReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListVigCorReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListVigCor();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListVigCor2ReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListLiOpReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListLiOp();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListLeReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListLe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListAmReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListAm();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListMeReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListMe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListFilReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListFil();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListHdrReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListHdr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListAfCReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListAfC();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_923, TagListRawBReturnsNonNull_923) {
  auto result = CanonMakerNote::tagListRawB();
  EXPECT_NE(result, nullptr);
}

// =============================================================================
// Tests for print functions - normal operation
// =============================================================================

TEST_F(CanonMakerNoteTest_923, PrintFocalLengthWithSingleValue_923) {
  UShortValue value;
  value.read("50");
  std::ostringstream os;
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  // Verify that the function returns the same stream reference
  EXPECT_EQ(&result, &os);
  // The output should not be empty (it should print something)
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_923, PrintFocalLengthWithMultipleValues_923) {
  UShortValue value;
  // Focal length tag usually has multiple values
  value.read("1 50 0 0");
  std::ostringstream os;
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_923, Print0x0008ReturnsStreamRef_923) {
  UShortValue value;
  value.read("1234");
  std::ostringstream os;
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, Print0x000aReturnsStreamRef_923) {
  ULongValue value;
  value.read("5678");
  std::ostringstream os;
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, Print0x000cReturnsStreamRef_923) {
  UShortValue value;
  value.read("12345678");
  std::ostringstream os;
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintCs0x0002ReturnsStreamRef_923) {
  UShortValue value;
  value.read("100");
  std::ostringstream os;
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintCsLensTypeReturnsStreamRef_923) {
  UShortValue value;
  value.read("50");
  std::ostringstream os;
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintCsLensReturnsStreamRef_923) {
  UShortValue value;
  value.read("50 18 1 1");
  std::ostringstream os;
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintLe0x0000ReturnsStreamRef_923) {
  UShortValue value;
  value.read("5");
  std::ostringstream os;
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0001ReturnsStreamRef_923) {
  UShortValue value;
  value.read("100");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0002ReturnsStreamRef_923) {
  UShortValue value;
  value.read("100");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0003ReturnsStreamRef_923) {
  UShortValue value;
  value.read("100");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0009ReturnsStreamRef_923) {
  UShortValue value;
  value.read("10");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x000cReturnsStreamRef_923) {
  UShortValue value;
  value.read("8");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x000dReturnsStreamRef_923) {
  UShortValue value;
  value.read("5");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x000eReturnsStreamRef_923) {
  UShortValue value;
  value.read("10");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0013ReturnsStreamRef_923) {
  UShortValue value;
  value.read("3");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0015ReturnsStreamRef_923) {
  UShortValue value;
  value.read("0");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0016ReturnsStreamRef_923) {
  UShortValue value;
  value.read("0");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0017ReturnsStreamRef_923) {
  UShortValue value;
  value.read("256");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0018ReturnsStreamRef_923) {
  UShortValue value;
  value.read("100");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintFiFocusDistanceReturnsStreamRef_923) {
  UShortValue value;
  value.read("500");
  std::ostringstream os;
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintFiFileNumberReturnsStreamRef_923) {
  ULongValue value;
  value.read("1234567");
  std::ostringstream os;
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Boundary / Edge cases
// =============================================================================

TEST_F(CanonMakerNoteTest_923, PrintFiFocusDistanceZero_923) {
  UShortValue value;
  value.read("0");
  std::ostringstream os;
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Zero distance should produce some output
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_923, PrintFiFocusDistanceMaxUShort_923) {
  UShortValue value;
  value.read("65535");
  std::ostringstream os;
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0001WithZero_923) {
  UShortValue value;
  value.read("0");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0002WithZero_923) {
  UShortValue value;
  value.read("0");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0003WithZero_923) {
  UShortValue value;
  value.read("0");
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x000eWithExifData_923) {
  UShortValue value;
  value.read("10");
  ExifData exifData;
  std::ostringstream os;
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, Print0x000cWithExifData_923) {
  UShortValue value;
  value.read("12345678");
  ExifData exifData;
  std::ostringstream os;
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintCsLensTypeWithExifData_923) {
  UShortValue value;
  value.read("50");
  ExifData exifData;
  std::ostringstream os;
  auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_923, PrintFiFileNumberWithExifData_923) {
  ULongValue value;
  value.read("1234567");
  ExifData exifData;
  std::ostringstream os;
  auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Consistency tests - calling tagList multiple times returns same pointer
// =============================================================================

TEST_F(CanonMakerNoteTest_923, TagListFcd1Consistency_923) {
  auto result1 = CanonMakerNote::tagListFcd1();
  auto result2 = CanonMakerNote::tagListFcd1();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_923, TagListConsistency_923) {
  auto result1 = CanonMakerNote::tagList();
  auto result2 = CanonMakerNote::tagList();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_923, TagListCsConsistency_923) {
  auto result1 = CanonMakerNote::tagListCs();
  auto result2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_923, TagListSiConsistency_923) {
  auto result1 = CanonMakerNote::tagListSi();
  auto result2 = CanonMakerNote::tagListSi();
  EXPECT_EQ(result1, result2);
}

// =============================================================================
// Tests for print functions with various known values
// =============================================================================

TEST_F(CanonMakerNoteTest_923, PrintSi0x0009WithKnownValues_923) {
  // Sequence number value
  UShortValue value;
  value.read("1");
  std::ostringstream os;
  CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_923, PrintLe0x0000WithKnownValue_923) {
  UShortValue value;
  value.read("1");
  std::ostringstream os;
  CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_923, PrintCs0x0002WithKnownTimerLength_923) {
  UShortValue value;
  value.read("0");
  std::ostringstream os;
  CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_923, PrintCsLensWithThreeValues_923) {
  UShortValue value;
  value.read("200 70 1");
  std::ostringstream os;
  CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_923, PrintSi0x0015WithKnownFlashOutput_923) {
  UShortValue value;
  value.read("1");
  std::ostringstream os;
  CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_923, PrintFocalLengthWithExifData_923) {
  UShortValue value;
  value.read("1 50 0 0");
  ExifData exifData;
  std::ostringstream os;
  auto& result = CanonMakerNote::printFocalLength(os, value, &exifData);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}
