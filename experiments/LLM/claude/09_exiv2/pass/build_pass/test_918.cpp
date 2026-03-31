#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_918 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ==================== tagList functions ====================

TEST_F(CanonMakerNoteTest_918, TagListIsNotNull_918) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListCsIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListSiIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListPaIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListPa();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListCfIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListCf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListPiIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListPi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListTiIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListTi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListFiIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListPrIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListPr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListMvIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListMv();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListMcIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListMc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListFcd3IsNotNull_918) {
  auto tagList = CanonMakerNote::tagListFcd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListWbiIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListWbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListCoIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListCo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListFcd2IsNotNull_918) {
  auto tagList = CanonMakerNote::tagListFcd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListFcd1IsNotNull_918) {
  auto tagList = CanonMakerNote::tagListFcd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListAsIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListAs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListCbiIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListCbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListFlIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListFl();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListMoIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListMo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListPreIIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListPreI();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListCiIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListCi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListAfMiAdjIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListVigCorIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListVigCor();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListVigCor2IsNotNull_918) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListLiOpIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListLiOp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListLeIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListLe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListAmIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListAm();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListMeIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListFilIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListFil();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListHdrIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListHdr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListAfCIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListAfC();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_918, TagListRawBIsNotNull_918) {
  auto tagList = CanonMakerNote::tagListRawB();
  ASSERT_NE(tagList, nullptr);
}

// ==================== print functions ====================

TEST_F(CanonMakerNoteTest_918, PrintFocalLengthWithSingleValue_918) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // The output should not be empty
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_918, PrintFocalLengthWithMultipleValues_918) {
  UShortValue value;
  value.read("1 100 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, Print0x0008ReturnsOstream_918) {
  UShortValue value;
  value.read("12345");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, Print0x000aReturnsOstream_918) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, Print0x000cReturnsOstream_918) {
  ULongValue value;
  value.read("12345678");
  ExifData exifData;
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, Print0x000cWithNullExifData_918) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintCs0x0002ReturnsOstream_918) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintCsLensTypeReturnsOstream_918) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintCsLensReturnsOstream_918) {
  UShortValue value;
  value.read("100 24 70");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintCsLensSingleValue_918) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintLe0x0000ReturnsOstream_918) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0001ReturnsOstream_918) {
  UShortValue value;
  value.read("96");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0002ReturnsOstream_918) {
  UShortValue value;
  value.read("160");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0003ReturnsOstream_918) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0009ReturnsOstream_918) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x000cReturnsOstream_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x000dReturnsOstream_918) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x000eReturnsOstream_918) {
  UShortValue value;
  value.read("8");
  ExifData exifData;
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x000eWithNullExifData_918) {
  UShortValue value;
  value.read("8");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0013ReturnsOstream_918) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0015ReturnsOstream_918) {
  UShortValue value;
  value.read("32767");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0016ReturnsOstream_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0017ReturnsOstream_918) {
  UShortValue value;
  value.read("200");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0018ReturnsOstream_918) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintFiFocusDistanceReturnsOstream_918) {
  UShortValue value;
  value.read("500");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintFiFocusDistanceZero_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintFiFocusDistanceMaxValue_918) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintFiFileNumberReturnsOstream_918) {
  ULongValue value;
  value.read("1234567");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintFiFileNumberWithMetadata_918) {
  ULongValue value;
  value.read("1234567");
  ExifData exifData;
  auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ==================== Boundary / Edge cases ====================

TEST_F(CanonMakerNoteTest_918, PrintSi0x0001WithZeroValue_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0002WithZeroValue_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0003WithZeroValue_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintCsLensTypeWithZero_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintCsLensTypeWithMetadata_918) {
  UShortValue value;
  value.read("1");
  ExifData exifData;
  auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0015WithZero_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0013WithZeroValue_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x000eWithZeroValue_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintCs0x0002WithZeroValue_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, PrintLe0x0000WithZeroValue_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, Print0x0008WithZeroValue_918) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_918, Print0x000aWithZeroValue_918) {
  ULongValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ==================== Output content verification ====================

TEST_F(CanonMakerNoteTest_918, PrintFiFocusDistanceOutputsContent_918) {
  UShortValue value;
  value.read("100");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  std::string output = os.str();
  // Should produce some output (distance or "inf" or similar)
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x0009OutputsContent_918) {
  UShortValue value;
  value.read("5");
  CanonMakerNote::printSi0x0009(os, value, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x000dOutputsContent_918) {
  UShortValue value;
  value.read("3");
  CanonMakerNote::printSi0x000d(os, value, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_918, PrintSi0x000cOutputsContent_918) {
  UShortValue value;
  value.read("1");
  CanonMakerNote::printSi0x000c(os, value, nullptr);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// ==================== Multiple tagList calls return consistent results ====================

TEST_F(CanonMakerNoteTest_918, TagListMcConsistentAcrossCalls_918) {
  auto tagList1 = CanonMakerNote::tagListMc();
  auto tagList2 = CanonMakerNote::tagListMc();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(CanonMakerNoteTest_918, TagListConsistentAcrossCalls_918) {
  auto tagList1 = CanonMakerNote::tagList();
  auto tagList2 = CanonMakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(CanonMakerNoteTest_918, TagListCsConsistentAcrossCalls_918) {
  auto tagList1 = CanonMakerNote::tagListCs();
  auto tagList2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(CanonMakerNoteTest_918, TagListSiConsistentAcrossCalls_918) {
  auto tagList1 = CanonMakerNote::tagListSi();
  auto tagList2 = CanonMakerNote::tagListSi();
  EXPECT_EQ(tagList1, tagList2);
}
