#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_908 : public ::testing::Test {
 protected:
  std::ostringstream os_;
};

// =====================================================
// tagList() tests
// =====================================================

TEST_F(CanonMakerNoteTest_908, TagListReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListCsReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListCs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListSiReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListSi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListPaReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListPa();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListCfReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListCf();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListPiReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListPi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListTiReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListTi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListFiReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListPrReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListPr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListLeReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListLe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListFlReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListFl();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListMoReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListMo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListMvReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListMv();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListMcReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListMc();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListCoReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListCo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListWbiReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListWbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListAsReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListAs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListCbiReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListCbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListPreIReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListPreI();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListCiReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListCi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListFcd1ReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListFcd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListFcd2ReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListFcd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListFcd3ReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListFcd3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListAfMiAdjReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListVigCorReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListVigCor();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListVigCor2ReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListLiOpReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListLiOp();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListAmReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListAm();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListMeReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListFilReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListFil();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListHdrReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListHdr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListAfCReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListAfC();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_908, TagListRawBReturnsNonNull_908) {
  auto tagList = CanonMakerNote::tagListRawB();
  EXPECT_NE(tagList, nullptr);
}

// =====================================================
// Print function tests
// =====================================================

TEST_F(CanonMakerNoteTest_908, PrintFocalLengthWithSingleValue_908) {
  UShortValue value;
  value.read("50");
  std::ostream& result = CanonMakerNote::printFocalLength(os_, value, nullptr);
  // Should return the same stream
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintFocalLengthWithMultipleValues_908) {
  UShortValue value;
  value.read("1 50 0 0");
  std::ostream& result = CanonMakerNote::printFocalLength(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  // Output should not be empty
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_908, Print0x0008WithValue_908) {
  UShortValue value;
  value.read("12345");
  std::ostream& result = CanonMakerNote::print0x0008(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, Print0x000aWithValue_908) {
  ULongValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::print0x000a(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, Print0x000cWithNullExifData_908) {
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000c(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintCs0x0002WithValue_908) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printCs0x0002(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintCsLensTypeWithValue_908) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printCsLensType(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintCsLensWithMultipleValues_908) {
  UShortValue value;
  value.read("50 18 1 1");
  std::ostream& result = CanonMakerNote::printCsLens(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintCsLensWithSingleValue_908) {
  UShortValue value;
  value.read("50");
  std::ostream& result = CanonMakerNote::printCsLens(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintLe0x0000WithValue_908) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printLe0x0000(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0001WithValue_908) {
  UShortValue value;
  value.read("128");
  std::ostream& result = CanonMakerNote::printSi0x0001(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0002WithValue_908) {
  UShortValue value;
  value.read("200");
  std::ostream& result = CanonMakerNote::printSi0x0002(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0003WithValue_908) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0003(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0009WithValue_908) {
  UShortValue value;
  value.read("10");
  std::ostream& result = CanonMakerNote::printSi0x0009(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x000cWithValue_908) {
  UShortValue value;
  value.read("500");
  std::ostream& result = CanonMakerNote::printSi0x000c(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x000dWithValue_908) {
  UShortValue value;
  value.read("32");
  std::ostream& result = CanonMakerNote::printSi0x000d(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x000eWithNullExifData_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000e(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0013WithValue_908) {
  UShortValue value;
  value.read("256");
  std::ostream& result = CanonMakerNote::printSi0x0013(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0015WithValue_908) {
  UShortValue value;
  value.read("128");
  std::ostream& result = CanonMakerNote::printSi0x0015(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0016WithValue_908) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0016(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0017WithValue_908) {
  UShortValue value;
  value.read("50");
  std::ostream& result = CanonMakerNote::printSi0x0017(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0018WithValue_908) {
  UShortValue value;
  value.read("30");
  std::ostream& result = CanonMakerNote::printSi0x0018(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintFiFocusDistanceWithValue_908) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintFiFocusDistanceWithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintFiFocusDistanceWithMaxValue_908) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintFiFileNumberWithValue_908) {
  ULongValue value;
  value.read("1234567");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintFiFileNumberWithZeroValue_908) {
  ULongValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =====================================================
// Tests with ExifData
// =====================================================

TEST_F(CanonMakerNoteTest_908, PrintSi0x000eWithExifData_908) {
  ExifData exifData;
  UShortValue value;
  value.read("10");
  std::ostream& result = CanonMakerNote::printSi0x000e(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, Print0x000cWithExifData_908) {
  ExifData exifData;
  ULongValue value;
  value.read("999");
  std::ostream& result = CanonMakerNote::print0x000c(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintCsLensTypeWithExifData_908) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCsLensType(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintFocalLengthWithExifData_908) {
  ExifData exifData;
  UShortValue value;
  value.read("1 50 0 0");
  std::ostream& result = CanonMakerNote::printFocalLength(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintFiFileNumberWithExifData_908) {
  ExifData exifData;
  ULongValue value;
  value.read("1000");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

// =====================================================
// Boundary / edge case tests
// =====================================================

TEST_F(CanonMakerNoteTest_908, PrintSi0x0001WithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0001(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0002WithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0002(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0009WithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0009(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x000cWithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000c(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0015WithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0015(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, Print0x0008WithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::print0x0008(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintCs0x0002WithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCs0x0002(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0016WithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0016(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0013WithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0013(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0017WithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0017(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x0018WithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0018(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintSi0x000dWithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000d(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, PrintLe0x0000WithZeroValue_908) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printLe0x0000(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// =====================================================
// Test tag list first entry has valid tag
// =====================================================

TEST_F(CanonMakerNoteTest_908, TagListFirstEntryHasValidTag_908) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  // First entry should have a valid tag (tag >= 0 or tag != -1 typically indicating end)
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(CanonMakerNoteTest_908, TagListCsFirstEntryHasValidTag_908) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(CanonMakerNoteTest_908, TagListSiFirstEntryHasValidTag_908) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
  EXPECT_GE(tagList[0].tag_, 0);
}

// =====================================================
// Large value tests  
// =====================================================

TEST_F(CanonMakerNoteTest_908, PrintSi0x0003WithLargeValue_908) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printSi0x0003(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_908, Print0x000aWithLargeValue_908) {
  ULongValue value;
  value.read("4294967295");
  std::ostream& result = CanonMakerNote::print0x000a(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}
