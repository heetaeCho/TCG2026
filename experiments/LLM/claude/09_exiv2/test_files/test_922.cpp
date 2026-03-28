#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_922 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(CanonMakerNoteTest_922, TagListFcd2IsNotNull_922) {
  auto tagList = CanonMakerNote::tagListFcd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListIsNotNull_922) {
  auto tagList = CanonMakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListCsIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListCs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListSiIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListSi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListPaIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListPa();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListCfIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListCf();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListPiIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListPi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListTiIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListTi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListFiIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListPrIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListPr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListMvIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListMv();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListMcIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListMc();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListFcd3IsNotNull_922) {
  auto tagList = CanonMakerNote::tagListFcd3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListWbiIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListWbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListCoIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListCo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListFcd1IsNotNull_922) {
  auto tagList = CanonMakerNote::tagListFcd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListAsIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListAs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListCbiIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListCbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListFlIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListFl();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListMoIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListMo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListPreIIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListPreI();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListCiIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListCi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListAfMiAdjIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListVigCorIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListVigCor();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListVigCor2IsNotNull_922) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListLiOpIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListLiOp();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListLeIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListLe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListAmIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListAm();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListMeIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListFilIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListFil();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListHdrIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListHdr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListAfCIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListAfC();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_922, TagListRawBIsNotNull_922) {
  auto tagList = CanonMakerNote::tagListRawB();
  EXPECT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print functions
// ============================================================

TEST_F(CanonMakerNoteTest_922, PrintFocalLengthWithSingleValue_922) {
  UShortValue value;
  value.read("50");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  // Should return the same stream reference
  EXPECT_EQ(&result, &os);
  // Output should not be empty
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintFocalLengthWithMultipleValues_922) {
  UShortValue value;
  // FocalLength tag typically has 4 ushort values
  value.read("1 50 0 0");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, Print0x0008ReturnsStream_922) {
  UShortValue value;
  value.read("1234");
  std::ostream& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, Print0x000aReturnsStream_922) {
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, Print0x000cReturnsStream_922) {
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintCs0x0002ReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintCsLensTypeReturnsStream_922) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintCsLensWithThreeValues_922) {
  UShortValue value;
  value.read("50 18 1");
  std::ostream& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintCsLensWithSingleValue_922) {
  UShortValue value;
  value.read("50");
  std::ostream& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintLe0x0000ReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0001ReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0002ReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0003ReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0009ReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x000cReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x000dReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x000eReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0013ReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0015ReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0016ReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0017ReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0018ReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintFiFocusDistanceReturnsStream_922) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintFiFocusDistanceZero_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  // Zero focus distance should produce some output
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintFiFocusDistanceMaxValue_922) {
  UShortValue value;
  value.read("65535");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintFiFileNumberReturnsStream_922) {
  ULongValue value;
  value.read("1001234");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintFiFileNumberZero_922) {
  ULongValue value;
  value.read("0");
  CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0001ZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0002ZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0009ZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintCsLensTypeWithMetadata_922) {
  UShortValue value;
  value.read("137");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x000eWithExifData_922) {
  UShortValue value;
  value.read("100");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, Print0x000cWithExifData_922) {
  ULongValue value;
  value.read("12345678");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_922, PrintLe0x0000ZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x000cZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x000dZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0013ZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0015ZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0016ZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0017ZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0018ZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintCs0x0002ZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, PrintSi0x0003ZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, Print0x0008ZeroValue_922) {
  UShortValue value;
  value.read("0");
  CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_922, Print0x000aZeroValue_922) {
  ULongValue value;
  value.read("0");
  CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}
