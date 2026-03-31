#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_935 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(CanonMakerNoteTest_935, TagListIsNotNull_935) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListCsIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListSiIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListPaIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListPa();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListCfIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListCf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListPiIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListPi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListTiIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListTi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListFiIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListPrIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListPr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListAmIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListAm();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListMeIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListFilIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListFil();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListHdrIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListHdr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListAfCIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListAfC();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListRawBIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListRawB();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListMvIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListMv();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListMcIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListMc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListFcd3IsNotNull_935) {
  auto tagList = CanonMakerNote::tagListFcd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListWbiIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListWbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListCoIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListCo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListFcd2IsNotNull_935) {
  auto tagList = CanonMakerNote::tagListFcd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListFcd1IsNotNull_935) {
  auto tagList = CanonMakerNote::tagListFcd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListAsIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListAs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListCbiIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListCbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListFlIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListFl();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListMoIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListMo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListPreIIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListPreI();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListCiIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListCi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListAfMiAdjIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListVigCorIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListVigCor();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListVigCor2IsNotNull_935) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListLiOpIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListLiOp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_935, TagListLeIsNotNull_935) {
  auto tagList = CanonMakerNote::tagListLe();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print functions
// ============================================================

TEST_F(CanonMakerNoteTest_935, PrintFocalLengthWithSingleValue_935) {
  UShortValue value;
  value.read("50");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // The function should produce some output
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_935, PrintFocalLengthWithMultipleValues_935) {
  UShortValue value;
  // Focal length tag typically has multiple values
  value.read("1 50 0 0");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_935, Print0x0008WithValue_935) {
  UShortValue value;
  value.read("12345");
  std::ostream& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, Print0x000aWithValue_935) {
  ULongValue value;
  value.read("12345");
  std::ostream& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, Print0x000cWithNullExifData_935) {
  ULongValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintCs0x0002WithValue_935) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_935, PrintCsLensTypeWithValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintCsLensWithMultipleValues_935) {
  UShortValue value;
  value.read("70 24 1");
  std::ostream& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_935, PrintCsLensWithSingleValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintLe0x0000WithValue_935) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0001WithValue_935) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0002WithValue_935) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0003WithValue_935) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0009WithValue_935) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x000cWithValue_935) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x000dWithValue_935) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x000eWithNullExifData_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0013WithValue_935) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0015WithValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0016WithValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0017WithValue_935) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0018WithValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintFiFocusDistanceWithValue_935) {
  UShortValue value;
  value.read("500");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_935, PrintFiFocusDistanceWithZero_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_935, PrintFiFocusDistanceWithMaxValue_935) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintFiFileNumberWithValue_935) {
  ULongValue value;
  value.read("1234567");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintFiFileNumberWithZero_935) {
  ULongValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print functions with ExifData
// ============================================================

TEST_F(CanonMakerNoteTest_935, PrintSi0x000eWithExifData_935) {
  ExifData exifData;
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, Print0x000cWithExifData_935) {
  ExifData exifData;
  ULongValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintCsLensTypeWithExifData_935) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintFiFileNumberWithExifData_935) {
  ExifData exifData;
  ULongValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for return value chaining
// ============================================================

TEST_F(CanonMakerNoteTest_935, PrintFunctionsReturnSameStream_935) {
  UShortValue value;
  value.read("50");
  
  std::ostringstream os1, os2;
  std::ostream& r1 = CanonMakerNote::printSi0x0001(os1, value, nullptr);
  std::ostream& r2 = CanonMakerNote::printSi0x0002(os2, value, nullptr);
  
  EXPECT_EQ(&r1, &os1);
  EXPECT_EQ(&r2, &os2);
}

// ============================================================
// Boundary tests with various value counts
// ============================================================

TEST_F(CanonMakerNoteTest_935, PrintSi0x0009WithZeroValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x000dWithZeroValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, Print0x0008WithZeroValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0001WithZeroValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0002WithZeroValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0003WithZeroValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x000cWithZeroValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0013WithZeroValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0017WithZeroValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintLe0x0000WithZeroValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Tag list consistency tests
// ============================================================

TEST_F(CanonMakerNoteTest_935, TagListConsistentOnMultipleCalls_935) {
  auto list1 = CanonMakerNote::tagList();
  auto list2 = CanonMakerNote::tagList();
  EXPECT_EQ(list1, list2);
}

TEST_F(CanonMakerNoteTest_935, TagListAmConsistentOnMultipleCalls_935) {
  auto list1 = CanonMakerNote::tagListAm();
  auto list2 = CanonMakerNote::tagListAm();
  EXPECT_EQ(list1, list2);
}

TEST_F(CanonMakerNoteTest_935, TagListCsConsistentOnMultipleCalls_935) {
  auto list1 = CanonMakerNote::tagListCs();
  auto list2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(list1, list2);
}

TEST_F(CanonMakerNoteTest_935, TagListSiConsistentOnMultipleCalls_935) {
  auto list1 = CanonMakerNote::tagListSi();
  auto list2 = CanonMakerNote::tagListSi();
  EXPECT_EQ(list1, list2);
}

// ============================================================
// Tests for large/boundary values
// ============================================================

TEST_F(CanonMakerNoteTest_935, PrintSi0x0015WithLargeValue_935) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0016WithLargeValue_935) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintSi0x0018WithLargeValue_935) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintCs0x0002WithZeroValue_935) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_935, PrintCs0x0002WithLargeValue_935) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}
