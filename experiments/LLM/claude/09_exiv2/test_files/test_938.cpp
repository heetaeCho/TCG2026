#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_938 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(CanonMakerNoteTest_938, TagListHdrNotNull_938) {
  auto tagList = CanonMakerNote::tagListHdr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListNotNull_938) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListCsNotNull_938) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListSiNotNull_938) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListPaNotNull_938) {
  auto tagList = CanonMakerNote::tagListPa();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListCfNotNull_938) {
  auto tagList = CanonMakerNote::tagListCf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListPiNotNull_938) {
  auto tagList = CanonMakerNote::tagListPi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListTiNotNull_938) {
  auto tagList = CanonMakerNote::tagListTi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListFiNotNull_938) {
  auto tagList = CanonMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListPrNotNull_938) {
  auto tagList = CanonMakerNote::tagListPr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListMvNotNull_938) {
  auto tagList = CanonMakerNote::tagListMv();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListMcNotNull_938) {
  auto tagList = CanonMakerNote::tagListMc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListFcd3NotNull_938) {
  auto tagList = CanonMakerNote::tagListFcd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListWbiNotNull_938) {
  auto tagList = CanonMakerNote::tagListWbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListCoNotNull_938) {
  auto tagList = CanonMakerNote::tagListCo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListFcd2NotNull_938) {
  auto tagList = CanonMakerNote::tagListFcd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListFcd1NotNull_938) {
  auto tagList = CanonMakerNote::tagListFcd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListAsNotNull_938) {
  auto tagList = CanonMakerNote::tagListAs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListCbiNotNull_938) {
  auto tagList = CanonMakerNote::tagListCbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListFlNotNull_938) {
  auto tagList = CanonMakerNote::tagListFl();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListMoNotNull_938) {
  auto tagList = CanonMakerNote::tagListMo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListPreINotNull_938) {
  auto tagList = CanonMakerNote::tagListPreI();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListCiNotNull_938) {
  auto tagList = CanonMakerNote::tagListCi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListAfMiAdjNotNull_938) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListVigCorNotNull_938) {
  auto tagList = CanonMakerNote::tagListVigCor();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListVigCor2NotNull_938) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListLiOpNotNull_938) {
  auto tagList = CanonMakerNote::tagListLiOp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListLeNotNull_938) {
  auto tagList = CanonMakerNote::tagListLe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListAmNotNull_938) {
  auto tagList = CanonMakerNote::tagListAm();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListMeNotNull_938) {
  auto tagList = CanonMakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListFilNotNull_938) {
  auto tagList = CanonMakerNote::tagListFil();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListAfCNotNull_938) {
  auto tagList = CanonMakerNote::tagListAfC();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_938, TagListRawBNotNull_938) {
  auto tagList = CanonMakerNote::tagListRawB();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print functions
// ============================================================

TEST_F(CanonMakerNoteTest_938, PrintFocalLengthWithSingleValue_938) {
  UShortValue value;
  value.read("1000");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  // Verify stream reference is returned
  EXPECT_EQ(&result, &os);
  // With only one value, it should still produce some output or handle gracefully
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintFocalLengthWithMultipleValues_938) {
  UShortValue value;
  // Focal length tag typically expects multiple unsigned short values
  value.read("1 1000 0 0");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, Print0x0008WithSingleValue_938) {
  UShortValue value;
  value.read("12345");
  std::ostream& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, Print0x000aWithValue_938) {
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, Print0x000cWithValue_938) {
  ULongValue value;
  value.read("12345678");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, Print0x000cWithNullExifData_938) {
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintCs0x0002WithValue_938) {
  UShortValue value;
  value.read("50");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintCsLensTypeWithValue_938) {
  UShortValue value;
  value.read("10");
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintCsLensWithThreeValues_938) {
  UShortValue value;
  // CsLens typically expects short focal, long focal, units
  value.read("24 70 1");
  std::ostream& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintCsLensWithSingleValue_938) {
  UShortValue value;
  value.read("50");
  std::ostream& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintLe0x0000WithValue_938) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0001WithValue_938) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0002WithValue_938) {
  UShortValue value;
  value.read("96");
  std::ostream& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0003WithValue_938) {
  UShortValue value;
  value.read("160");
  std::ostream& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0009WithValue_938) {
  UShortValue value;
  value.read("10");
  std::ostream& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x000cWithValue_938) {
  UShortValue value;
  value.read("10");
  std::ostream& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x000dWithValue_938) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x000eWithNullExifData_938) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x000eWithExifData_938) {
  UShortValue value;
  value.read("5");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0013WithValue_938) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0015WithValue_938) {
  UShortValue value;
  value.read("128");
  std::ostream& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0016WithValue_938) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0017WithValue_938) {
  UShortValue value;
  value.read("3");
  std::ostream& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0018WithValue_938) {
  UShortValue value;
  value.read("3");
  std::ostream& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintFiFocusDistanceWithValue_938) {
  UShortValue value;
  value.read("500");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintFiFocusDistanceWithZero_938) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintFiFocusDistanceWithMaxValue_938) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintFiFileNumberWithValue_938) {
  ULongValue value;
  value.read("1234567");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintFiFileNumberWithExifData_938) {
  ULongValue value;
  value.read("1234567");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0001WithZeroValue_938) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0002WithZeroValue_938) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintCsLensTypeWithExifData_938) {
  UShortValue value;
  value.read("10");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_938, PrintCs0x0002WithZero_938) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary tests for print functions with extreme values
// ============================================================

TEST_F(CanonMakerNoteTest_938, PrintSi0x0009WithZero_938) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0009WithMaxUShort_938) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintLe0x0000WithZero_938) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, Print0x0008WithZero_938) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0013WithZero_938) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x000dWithZero_938) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0016WithZero_938) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_938, PrintSi0x0003WithZero_938) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Multiple calls consistency test
// ============================================================

TEST_F(CanonMakerNoteTest_938, TagListHdrConsistentAcrossCalls_938) {
  auto tagList1 = CanonMakerNote::tagListHdr();
  auto tagList2 = CanonMakerNote::tagListHdr();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(CanonMakerNoteTest_938, TagListConsistentAcrossCalls_938) {
  auto tagList1 = CanonMakerNote::tagList();
  auto tagList2 = CanonMakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(CanonMakerNoteTest_938, TagListCsConsistentAcrossCalls_938) {
  auto tagList1 = CanonMakerNote::tagListCs();
  auto tagList2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(tagList1, tagList2);
}
