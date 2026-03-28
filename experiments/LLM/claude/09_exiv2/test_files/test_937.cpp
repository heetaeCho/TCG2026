#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_937 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(CanonMakerNoteTest_937, TagListIsNotNull_937) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListCsIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListSiIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListPaIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListPa();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListCfIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListCf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListPiIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListPi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListTiIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListTi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListFiIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListPrIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListPr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListFilIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListFil();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListLeIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListLe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListMvIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListMv();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListMcIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListMc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListFlIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListFl();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListMoIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListMo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListHdrIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListHdr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListAfCIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListAfC();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListRawBIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListRawB();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListWbiIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListWbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListCoIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListCo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListFcd1IsNotNull_937) {
  auto tagList = CanonMakerNote::tagListFcd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListFcd2IsNotNull_937) {
  auto tagList = CanonMakerNote::tagListFcd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListFcd3IsNotNull_937) {
  auto tagList = CanonMakerNote::tagListFcd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListAsIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListAs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListCbiIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListCbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListPreIIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListPreI();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListCiIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListCi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListAfMiAdjIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListVigCorIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListVigCor();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListVigCor2IsNotNull_937) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListLiOpIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListLiOp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListAmIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListAm();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_937, TagListMeIsNotNull_937) {
  auto tagList = CanonMakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print functions with various Value inputs
// ============================================================

TEST_F(CanonMakerNoteTest_937, PrintFocalLengthWithSingleValue_937) {
  UShortValue value;
  value.read("1000");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  // Verify it returns the same ostream reference
  EXPECT_EQ(&result, &os);
  // Output should not be empty (it should print something)
  // We don't verify exact content since that's implementation detail
}

TEST_F(CanonMakerNoteTest_937, PrintFocalLengthWithMultipleValues_937) {
  UShortValue value;
  value.read("1 1000 0 0");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, Print0x0008ReturnsOstream_937) {
  UShortValue value;
  value.read("12345");
  std::ostream& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, Print0x000aReturnsOstream_937) {
  ULongValue value;
  value.read("12345");
  std::ostream& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, Print0x000cReturnsOstream_937) {
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintCs0x0002WithValue_937) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintCsLensTypeReturnsOstream_937) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintCsLensReturnsOstream_937) {
  UShortValue value;
  value.read("50 50 1");
  std::ostream& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintLe0x0000ReturnsOstream_937) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0001ReturnsOstream_937) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0002ReturnsOstream_937) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0003ReturnsOstream_937) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0009ReturnsOstream_937) {
  UShortValue value;
  value.read("10");
  std::ostream& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x000cReturnsOstream_937) {
  UShortValue value;
  value.read("50");
  std::ostream& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x000dReturnsOstream_937) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x000eReturnsOstream_937) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0013ReturnsOstream_937) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0015ReturnsOstream_937) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0016ReturnsOstream_937) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0017ReturnsOstream_937) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0018ReturnsOstream_937) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintFiFocusDistanceReturnsOstream_937) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintFiFileNumberReturnsOstream_937) {
  ULongValue value;
  value.read("1234567");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary tests
// ============================================================

TEST_F(CanonMakerNoteTest_937, PrintFiFocusDistanceZero_937) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Zero distance is a boundary case
}

TEST_F(CanonMakerNoteTest_937, PrintFiFocusDistanceMaxUShort_937) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0001WithZeroValue_937) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0002WithZeroValue_937) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0003WithZeroValue_937) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintCs0x0002WithZeroValue_937) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintCsLensTypeWithZeroValue_937) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintFiFileNumberWithZeroValue_937) {
  ULongValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, Print0x0008WithZeroValue_937) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, Print0x000aWithZeroValue_937) {
  ULongValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x000eWithExifData_937) {
  UShortValue value;
  value.read("100");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x000eWithNullExifData_937) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintFocalLengthWithExifData_937) {
  UShortValue value;
  value.read("1 1000 0 0");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintCsLensTypeWithExifData_937) {
  UShortValue value;
  value.read("1");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintFiFileNumberWithExifData_937) {
  ULongValue value;
  value.read("1234567");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Verify output is non-empty for typical inputs
// ============================================================

TEST_F(CanonMakerNoteTest_937, PrintSi0x0009ProducesOutput_937) {
  UShortValue value;
  value.read("10");
  CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x000cProducesOutput_937) {
  UShortValue value;
  value.read("50");
  CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_937, PrintFiFocusDistanceProducesOutput_937) {
  UShortValue value;
  value.read("100");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0001ProducesOutput_937) {
  UShortValue value;
  value.read("100");
  CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_937, PrintLe0x0000ProducesOutput_937) {
  UShortValue value;
  value.read("5");
  CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_937, Print0x000cProducesOutput_937) {
  ULongValue value;
  value.read("12345678");
  CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for large/edge case values
// ============================================================

TEST_F(CanonMakerNoteTest_937, PrintSi0x0013WithMaxValue_937) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0015WithMaxValue_937) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0016WithMaxValue_937) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0017WithMaxValue_937) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, PrintSi0x0018WithMaxValue_937) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_937, Print0x000cWithExifData_937) {
  ULongValue value;
  value.read("12345678");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}
