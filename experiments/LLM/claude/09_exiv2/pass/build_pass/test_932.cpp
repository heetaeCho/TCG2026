#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_932 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList accessor functions (constexpr tag list getters)
// ============================================================

TEST_F(CanonMakerNoteTest_932, TagListVigCor2NotNull_932) {
  auto result = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListNotNull_932) {
  auto result = CanonMakerNote::tagList();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListCsNotNull_932) {
  auto result = CanonMakerNote::tagListCs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListSiNotNull_932) {
  auto result = CanonMakerNote::tagListSi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListPaNotNull_932) {
  auto result = CanonMakerNote::tagListPa();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListCfNotNull_932) {
  auto result = CanonMakerNote::tagListCf();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListPiNotNull_932) {
  auto result = CanonMakerNote::tagListPi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListTiNotNull_932) {
  auto result = CanonMakerNote::tagListTi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListFiNotNull_932) {
  auto result = CanonMakerNote::tagListFi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListPrNotNull_932) {
  auto result = CanonMakerNote::tagListPr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListMvNotNull_932) {
  auto result = CanonMakerNote::tagListMv();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListMcNotNull_932) {
  auto result = CanonMakerNote::tagListMc();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListFcd3NotNull_932) {
  auto result = CanonMakerNote::tagListFcd3();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListWbiNotNull_932) {
  auto result = CanonMakerNote::tagListWbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListCoNotNull_932) {
  auto result = CanonMakerNote::tagListCo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListFcd2NotNull_932) {
  auto result = CanonMakerNote::tagListFcd2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListFcd1NotNull_932) {
  auto result = CanonMakerNote::tagListFcd1();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListAsNotNull_932) {
  auto result = CanonMakerNote::tagListAs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListCbiNotNull_932) {
  auto result = CanonMakerNote::tagListCbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListFlNotNull_932) {
  auto result = CanonMakerNote::tagListFl();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListMoNotNull_932) {
  auto result = CanonMakerNote::tagListMo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListPreINotNull_932) {
  auto result = CanonMakerNote::tagListPreI();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListCiNotNull_932) {
  auto result = CanonMakerNote::tagListCi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListAfMiAdjNotNull_932) {
  auto result = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListVigCorNotNull_932) {
  auto result = CanonMakerNote::tagListVigCor();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListLiOpNotNull_932) {
  auto result = CanonMakerNote::tagListLiOp();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListLeNotNull_932) {
  auto result = CanonMakerNote::tagListLe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListAmNotNull_932) {
  auto result = CanonMakerNote::tagListAm();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListMeNotNull_932) {
  auto result = CanonMakerNote::tagListMe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListFilNotNull_932) {
  auto result = CanonMakerNote::tagListFil();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListHdrNotNull_932) {
  auto result = CanonMakerNote::tagListHdr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListAfCNotNull_932) {
  auto result = CanonMakerNote::tagListAfC();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_932, TagListRawBNotNull_932) {
  auto result = CanonMakerNote::tagListRawB();
  EXPECT_NE(result, nullptr);
}

// ============================================================
// Tests for print functions
// ============================================================

TEST_F(CanonMakerNoteTest_932, PrintFocalLengthWithSingleValue_932) {
  UShortValue value;
  value.read("1");
  CanonMakerNote::printFocalLength(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintFocalLengthWithMultipleValues_932) {
  UShortValue value;
  value.read("3 50 0 0");
  CanonMakerNote::printFocalLength(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, Print0x0008WithValue_932) {
  UShortValue value;
  value.read("12345");
  CanonMakerNote::print0x0008(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, Print0x000aWithValue_932) {
  ULongValue value;
  value.read("100");
  CanonMakerNote::print0x000a(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, Print0x000cWithNullExifData_932) {
  ULongValue value;
  value.read("100");
  CanonMakerNote::print0x000c(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintCs0x0002WithSingleValue_932) {
  UShortValue value;
  value.read("100");
  CanonMakerNote::printCs0x0002(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintCsLensWithThreeValues_932) {
  UShortValue value;
  value.read("50 18 1");
  CanonMakerNote::printCsLens(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintCsLensWithFewerValues_932) {
  UShortValue value;
  value.read("50");
  CanonMakerNote::printCsLens(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintCsLensTypeWithValue_932) {
  UShortValue value;
  value.read("1");
  CanonMakerNote::printCsLensType(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintLe0x0000WithValue_932) {
  UShortValue value;
  value.read("5");
  CanonMakerNote::printLe0x0000(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x0001WithValue_932) {
  UShortValue value;
  value.read("100");
  CanonMakerNote::printSi0x0001(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x0002WithValue_932) {
  UShortValue value;
  value.read("200");
  CanonMakerNote::printSi0x0002(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x0003WithValue_932) {
  UShortValue value;
  value.read("300");
  CanonMakerNote::printSi0x0003(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x0009WithValue_932) {
  UShortValue value;
  value.read("5");
  CanonMakerNote::printSi0x0009(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x000cWithValue_932) {
  UShortValue value;
  value.read("10");
  CanonMakerNote::printSi0x000c(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x000dWithValue_932) {
  UShortValue value;
  value.read("15");
  CanonMakerNote::printSi0x000d(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x000eWithNullExifData_932) {
  UShortValue value;
  value.read("20");
  CanonMakerNote::printSi0x000e(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x0013WithValue_932) {
  UShortValue value;
  value.read("3");
  CanonMakerNote::printSi0x0013(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x0015WithValue_932) {
  UShortValue value;
  value.read("7");
  CanonMakerNote::printSi0x0015(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x0016WithValue_932) {
  UShortValue value;
  value.read("25");
  CanonMakerNote::printSi0x0016(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x0017WithValue_932) {
  UShortValue value;
  value.read("30");
  CanonMakerNote::printSi0x0017(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x0018WithValue_932) {
  UShortValue value;
  value.read("35");
  CanonMakerNote::printSi0x0018(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintFiFocusDistanceWithValue_932) {
  UShortValue value;
  value.read("100");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintFiFocusDistanceWithZero_932) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintFiFileNumberWithValue_932) {
  ULongValue value;
  value.read("1234567");
  CanonMakerNote::printFiFileNumber(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintFunctionsReturnOstream_932) {
  UShortValue value;
  value.read("50");
  std::ostream& ret = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(CanonMakerNoteTest_932, PrintSi0x000eWithExifData_932) {
  ExifData exifData;
  UShortValue value;
  value.read("20");
  CanonMakerNote::printSi0x000e(os, value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintCsLensTypeWithExifData_932) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  CanonMakerNote::printCsLensType(os, value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, Print0x000cWithExifData_932) {
  ExifData exifData;
  ULongValue value;
  value.read("100");
  CanonMakerNote::print0x000c(os, value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test that tagListVigCor2 returns consistently the same value
TEST_F(CanonMakerNoteTest_932, TagListVigCor2ConsistentReturn_932) {
  auto result1 = CanonMakerNote::tagListVigCor2();
  auto result2 = CanonMakerNote::tagListVigCor2();
  EXPECT_EQ(result1, result2);
}

// Test that different tagList functions return different results (they should be distinct tag arrays)
TEST_F(CanonMakerNoteTest_932, TagListsDifferent_932) {
  auto tagList = CanonMakerNote::tagList();
  auto tagListCs = CanonMakerNote::tagListCs();
  auto tagListSi = CanonMakerNote::tagListSi();
  EXPECT_NE(tagList, tagListCs);
  EXPECT_NE(tagList, tagListSi);
  EXPECT_NE(tagListCs, tagListSi);
}

// Boundary: large value for print functions
TEST_F(CanonMakerNoteTest_932, PrintSi0x0002LargeValue_932) {
  UShortValue value;
  value.read("65535");
  CanonMakerNote::printSi0x0002(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Boundary: value of 1 for print function
TEST_F(CanonMakerNoteTest_932, PrintSi0x0002MinValue_932) {
  UShortValue value;
  value.read("1");
  CanonMakerNote::printSi0x0002(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test printing focal length with various edge cases
TEST_F(CanonMakerNoteTest_932, PrintFocalLengthZeroValue_932) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printFocalLength(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(CanonMakerNoteTest_932, PrintFiFocusDistanceMaxUShort_932) {
  UShortValue value;
  value.read("65535");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
