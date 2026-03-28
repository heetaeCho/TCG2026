#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_926 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ==================== tagList functions tests ====================

TEST_F(CanonMakerNoteTest_926, TagListFlReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListFl();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListCsReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListSiReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListPaReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListPa();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListCfReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListCf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListPiReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListPi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListTiReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListTi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListFiReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListPrReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListPr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListMvReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListMv();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListMcReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListMc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListFcd3ReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListFcd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListWbiReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListWbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListCoReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListCo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListFcd2ReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListFcd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListFcd1ReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListFcd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListAsReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListAs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListCbiReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListCbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListMoReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListMo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListPreIReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListPreI();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListCiReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListCi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListAfMiAdjReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListVigCorReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListVigCor();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListVigCor2ReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListLiOpReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListLiOp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListLeReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListLe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListAmReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListAm();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListMeReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListFilReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListFil();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListHdrReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListHdr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListAfCReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListAfC();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_926, TagListRawBReturnsNonNull_926) {
  auto tagList = CanonMakerNote::tagListRawB();
  ASSERT_NE(tagList, nullptr);
}

// ==================== Print functions tests ====================

TEST_F(CanonMakerNoteTest_926, PrintFocalLengthWithValidValue_926) {
  UShortValue value;
  value.read("4 50 0 0");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_926, PrintFocalLengthWithSingleValue_926) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, Print0x0008WithValue_926) {
  UShortValue value;
  value.read("12345");
  std::ostream& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, Print0x000aWithValue_926) {
  ULongValue value;
  value.read("1000");
  std::ostream& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, Print0x000cWithNullExifData_926) {
  ULongValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, Print0x000cWithExifData_926) {
  ULongValue value;
  value.read("1234567");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintCs0x0002WithValue_926) {
  UShortValue value;
  value.read("500");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintCsLensTypeWithValue_926) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintCsLensWithValidValues_926) {
  UShortValue value;
  value.read("200 18 1");
  std::ostream& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintCsLensWithSingleValue_926) {
  UShortValue value;
  value.read("50");
  std::ostream& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintLe0x0000WithValue_926) {
  UShortValue value;
  value.read("3");
  std::ostream& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0001WithValue_926) {
  UShortValue value;
  value.read("96");
  std::ostream& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0002WithValue_926) {
  UShortValue value;
  value.read("160");
  std::ostream& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0003WithValue_926) {
  UShortValue value;
  value.read("168");
  std::ostream& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0009WithValue_926) {
  UShortValue value;
  value.read("10");
  std::ostream& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x000cWithValue_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x000dWithValue_926) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x000eWithNullExifData_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x000eWithExifData_926) {
  UShortValue value;
  value.read("10");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0013WithValue_926) {
  UShortValue value;
  value.read("200");
  std::ostream& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0015WithValue_926) {
  UShortValue value;
  value.read("3");
  std::ostream& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0016WithValue_926) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0017WithValue_926) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0018WithValue_926) {
  UShortValue value;
  value.read("32767");
  std::ostream& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintFiFocusDistanceWithZero_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintFiFocusDistanceWithNonZero_926) {
  UShortValue value;
  value.read("500");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintFiFocusDistanceWithMaxValue_926) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintFiFileNumberWithNullMetadata_926) {
  ULongValue value;
  value.read("1234567");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintFiFileNumberWithExifData_926) {
  ULongValue value;
  value.read("100");
  ExifData exifData;
  std::ostream& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ==================== Boundary / Edge case tests ====================

TEST_F(CanonMakerNoteTest_926, PrintSi0x0001WithZeroValue_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0002WithZeroValue_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0003WithZeroValue_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintCsLensTypeWithZeroValue_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintCsLensTypeWithLargeValue_926) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintCs0x0002WithZeroValue_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintLe0x0000WithZeroValue_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, Print0x0008WithZeroValue_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, Print0x000aWithZeroValue_926) {
  ULongValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ==================== Multiple tagList consistency tests ====================

TEST_F(CanonMakerNoteTest_926, TagListFlIsStable_926) {
  auto tagList1 = CanonMakerNote::tagListFl();
  auto tagList2 = CanonMakerNote::tagListFl();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(CanonMakerNoteTest_926, TagListIsStable_926) {
  auto tagList1 = CanonMakerNote::tagList();
  auto tagList2 = CanonMakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(CanonMakerNoteTest_926, TagListCsIsStable_926) {
  auto tagList1 = CanonMakerNote::tagListCs();
  auto tagList2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(tagList1, tagList2);
}

TEST_F(CanonMakerNoteTest_926, TagListSiIsStable_926) {
  auto tagList1 = CanonMakerNote::tagListSi();
  auto tagList2 = CanonMakerNote::tagListSi();
  EXPECT_EQ(tagList1, tagList2);
}

// ==================== Return reference chaining tests ====================

TEST_F(CanonMakerNoteTest_926, PrintSi0x0009ReturnStreamChaining_926) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  result << " extra";
  std::string output = os.str();
  EXPECT_TRUE(output.find("extra") != std::string::npos);
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x000dReturnStreamChaining_926) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  result << " chained";
  std::string output = os.str();
  EXPECT_TRUE(output.find("chained") != std::string::npos);
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0015WithLargeValue_926) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0016WithZeroValue_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0017WithZeroValue_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0018WithZeroValue_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x000cWithLargeValue_926) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_926, PrintSi0x0013WithZeroValue_926) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}
