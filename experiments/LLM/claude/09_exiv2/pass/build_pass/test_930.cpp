#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_930 : public ::testing::Test {
 protected:
  std::ostringstream os_;
};

// ============================================================
// tagList accessor tests - verify they return non-null pointers
// ============================================================

TEST_F(CanonMakerNoteTest_930, TagListAfMiAdj_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagList_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListCs_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListSi_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListPa_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListPa();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListCf_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListCf();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListPi_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListPi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListTi_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListTi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListFi_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListPr_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListPr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListMv_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListMv();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListMc_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListMc();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListFcd3_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListFcd3();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListWbi_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListWbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListCo_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListCo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListFcd2_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListFcd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListFcd1_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListFcd1();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListAs_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListAs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListCbi_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListCbi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListFl_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListFl();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListMo_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListMo();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListPreI_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListPreI();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListCi_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListCi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListVigCor_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListVigCor();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListVigCor2_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListLiOp_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListLiOp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListLe_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListLe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListAm_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListAm();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListMe_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListFil_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListFil();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListHdr_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListHdr();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListAfC_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListAfC();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_930, TagListRawB_ReturnsNonNull_930) {
  auto tagList = CanonMakerNote::tagListRawB();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Print function tests
// ============================================================

TEST_F(CanonMakerNoteTest_930, PrintFocalLength_ReturnsSameStream_930) {
  UShortValue value;
  value.read("50 50 1 50");
  std::ostream& result = CanonMakerNote::printFocalLength(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_930, PrintFocalLength_SingleValue_930) {
  UShortValue value;
  value.read("50");
  std::ostream& result = CanonMakerNote::printFocalLength(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  // Should produce some output (even if it's just the raw value)
  // We verify the stream is not in a bad state
  EXPECT_TRUE(os_.good());
}

TEST_F(CanonMakerNoteTest_930, Print0x0008_WithValue_930) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::print0x0008(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, Print0x000a_WithValue_930) {
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000a(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintCs0x0002_WithValue_930) {
  UShortValue value;
  value.read("2");
  std::ostream& result = CanonMakerNote::printCs0x0002(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintCsLens_WithThreeValues_930) {
  UShortValue value;
  value.read("100 28 1");
  std::ostream& result = CanonMakerNote::printCsLens(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintCsLens_SingleValue_930) {
  UShortValue value;
  value.read("50");
  std::ostream& result = CanonMakerNote::printCsLens(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x0001_WithValue_930) {
  UShortValue value;
  value.read("96");
  std::ostream& result = CanonMakerNote::printSi0x0001(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x0002_WithValue_930) {
  UShortValue value;
  value.read("160");
  std::ostream& result = CanonMakerNote::printSi0x0002(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x0003_WithValue_930) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0003(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x0009_WithValue_930) {
  UShortValue value;
  value.read("10");
  std::ostream& result = CanonMakerNote::printSi0x0009(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x000c_WithValue_930) {
  UShortValue value;
  value.read("32767");
  std::ostream& result = CanonMakerNote::printSi0x000c(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x000d_WithValue_930) {
  UShortValue value;
  value.read("5");
  std::ostream& result = CanonMakerNote::printSi0x000d(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x000e_NullExifData_930) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x000e(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x0013_WithValue_930) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0013(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x0015_WithValue_930) {
  UShortValue value;
  value.read("2");
  std::ostream& result = CanonMakerNote::printSi0x0015(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x0016_WithValue_930) {
  UShortValue value;
  value.read("100");
  std::ostream& result = CanonMakerNote::printSi0x0016(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x0017_WithValue_930) {
  UShortValue value;
  value.read("3");
  std::ostream& result = CanonMakerNote::printSi0x0017(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x0018_WithValue_930) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printSi0x0018(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintFiFocusDistance_WithValue_930) {
  UShortValue value;
  value.read("500");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintFiFocusDistance_ZeroValue_930) {
  UShortValue value;
  value.read("0");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintFiFocusDistance_MaxValue_930) {
  UShortValue value;
  value.read("65535");
  std::ostream& result = CanonMakerNote::printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintCsLensType_NullMetadata_930) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printCsLensType(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintCsLensType_WithExifData_930) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printCsLensType(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, Print0x000c_NullExifData_930) {
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000c(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_930, Print0x000c_WithExifData_930) {
  ExifData exifData;
  ULongValue value;
  value.read("12345678");
  std::ostream& result = CanonMakerNote::print0x000c(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_930, PrintLe0x0000_WithValue_930) {
  UShortValue value;
  value.read("1");
  std::ostream& result = CanonMakerNote::printLe0x0000(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
  EXPECT_FALSE(os_.str().empty());
}

TEST_F(CanonMakerNoteTest_930, PrintFiFileNumber_NullMetadata_930) {
  ULongValue value;
  value.read("1001234");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_930, PrintFiFileNumber_WithMetadata_930) {
  ExifData exifData;
  ULongValue value;
  value.read("1001234");
  std::ostream& result = CanonMakerNote::printFiFileNumber(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

TEST_F(CanonMakerNoteTest_930, PrintSi0x000e_WithExifData_930) {
  ExifData exifData;
  UShortValue value;
  value.read("10");
  std::ostream& result = CanonMakerNote::printSi0x000e(os_, value, &exifData);
  EXPECT_EQ(&result, &os_);
}

// ============================================================
// Multiple consecutive calls on the same stream
// ============================================================

TEST_F(CanonMakerNoteTest_930, MultiplePrintsOnSameStream_930) {
  UShortValue value1;
  value1.read("100");
  UShortValue value2;
  value2.read("200");

  CanonMakerNote::printSi0x0001(os_, value1, nullptr);
  std::string first = os_.str();

  std::ostringstream os2;
  CanonMakerNote::printSi0x0001(os2, value2, nullptr);
  std::string second = os2.str();

  // Both should produce non-empty output
  EXPECT_FALSE(first.empty());
  EXPECT_FALSE(second.empty());
}

// ============================================================
// Boundary: tagList functions called multiple times return same pointer
// ============================================================

TEST_F(CanonMakerNoteTest_930, TagListAfMiAdj_ConsistentReturn_930) {
  auto first = CanonMakerNote::tagListAfMiAdj();
  auto second = CanonMakerNote::tagListAfMiAdj();
  EXPECT_EQ(first, second);
}

TEST_F(CanonMakerNoteTest_930, TagList_ConsistentReturn_930) {
  auto first = CanonMakerNote::tagList();
  auto second = CanonMakerNote::tagList();
  EXPECT_EQ(first, second);
}

TEST_F(CanonMakerNoteTest_930, TagListCs_ConsistentReturn_930) {
  auto first = CanonMakerNote::tagListCs();
  auto second = CanonMakerNote::tagListCs();
  EXPECT_EQ(first, second);
}

TEST_F(CanonMakerNoteTest_930, TagListSi_ConsistentReturn_930) {
  auto first = CanonMakerNote::tagListSi();
  auto second = CanonMakerNote::tagListSi();
  EXPECT_EQ(first, second);
}
