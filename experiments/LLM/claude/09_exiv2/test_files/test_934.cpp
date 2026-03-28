#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_934 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that tagListLe returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListLeReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListLe();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagList returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListCs returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListCsReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListSi returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListSiReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListSi();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListPa returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListPaReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListPa();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListCf returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListCfReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListCf();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListPi returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListPiReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListPi();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListTi returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListTiReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListTi();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListFi returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListFiReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListPr returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListPrReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListPr();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListFcd1 returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListFcd1ReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListFcd1();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListFcd2 returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListFcd2ReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListFcd2();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListFcd3 returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListFcd3ReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListFcd3();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListWbi returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListWbiReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListWbi();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListCo returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListCoReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListCo();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListAs returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListAsReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListAs();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListMv returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListMvReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListMv();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListMc returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListMcReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListMc();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListCbi returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListCbiReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListCbi();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListFl returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListFlReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListFl();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListMo returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListMoReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListMo();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListPreI returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListPreIReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListPreI();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListCi returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListCiReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListCi();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListAfMiAdj returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListAfMiAdjReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListVigCor returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListVigCorReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListVigCor();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListVigCor2 returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListVigCor2ReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListLiOp returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListLiOpReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListLiOp();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListAm returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListAmReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListAm();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListMe returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListMeReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListMe();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListFil returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListFilReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListFil();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListHdr returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListHdrReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListHdr();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListAfC returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListAfCReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListAfC();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagListRawB returns a non-null pointer
TEST_F(CanonMakerNoteTest_934, TagListRawBReturnsNonNull_934) {
  auto tagList = CanonMakerNote::tagListRawB();
  ASSERT_NE(tagList, nullptr);
}

// Test printFocalLength with a short value containing enough elements
TEST_F(CanonMakerNoteTest_934, PrintFocalLengthWithValidValue_934) {
  std::ostringstream os;
  UShortValue value;
  // printFocalLength typically needs at least 2 elements (index 0 and 1)
  value.value_.push_back(0);
  value.value_.push_back(50);
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  // Verify it returns the same stream
  EXPECT_EQ(&result, &os);
  // The output should not be empty
  EXPECT_FALSE(os.str().empty());
}

// Test printSi0x0001 (ISO speed) with a single value
TEST_F(CanonMakerNoteTest_934, PrintSi0x0001WithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(0);
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test printSi0x0002 with a single value
TEST_F(CanonMakerNoteTest_934, PrintSi0x0002WithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(100);
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printSi0x0009 with a single value
TEST_F(CanonMakerNoteTest_934, PrintSi0x0009WithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(1);
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printSi0x000e (White Balance) with a value
TEST_F(CanonMakerNoteTest_934, PrintSi0x000eWithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(0);
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printCsLens with enough values
TEST_F(CanonMakerNoteTest_934, PrintCsLensWithValidValues_934) {
  std::ostringstream os;
  UShortValue value;
  // printCsLens typically expects at least 3 values
  value.value_.push_back(50);
  value.value_.push_back(50);
  value.value_.push_back(1);
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test printLe0x0000 with a value
TEST_F(CanonMakerNoteTest_934, PrintLe0x0000WithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(1);
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x0008 with a value
TEST_F(CanonMakerNoteTest_934, Print0x0008WithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(1234);
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x000a with a value
TEST_F(CanonMakerNoteTest_934, Print0x000aWithValue_934) {
  std::ostringstream os;
  ULongValue value;
  value.value_.push_back(0x01020304);
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFiFocusDistance with a value
TEST_F(CanonMakerNoteTest_934, PrintFiFocusDistanceWithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(100);
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test printFiFocusDistance with zero value (boundary)
TEST_F(CanonMakerNoteTest_934, PrintFiFocusDistanceWithZeroValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(0);
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printSi0x0003 with a value
TEST_F(CanonMakerNoteTest_934, PrintSi0x0003WithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(128);
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printSi0x000c with a value
TEST_F(CanonMakerNoteTest_934, PrintSi0x000cWithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(0);
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printSi0x000d with a value
TEST_F(CanonMakerNoteTest_934, PrintSi0x000dWithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(0);
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printSi0x0013 with a value
TEST_F(CanonMakerNoteTest_934, PrintSi0x0013WithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(32767);
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printSi0x0015 with a value
TEST_F(CanonMakerNoteTest_934, PrintSi0x0015WithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(1);
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printSi0x0016 with a value
TEST_F(CanonMakerNoteTest_934, PrintSi0x0016WithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(1);
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printSi0x0017 with a value
TEST_F(CanonMakerNoteTest_934, PrintSi0x0017WithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(1);
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printSi0x0018 with a value
TEST_F(CanonMakerNoteTest_934, PrintSi0x0018WithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(0);
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printCs0x0002 with a value
TEST_F(CanonMakerNoteTest_934, PrintCs0x0002WithValue_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(0);
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printCsLensType with a value and null metadata
TEST_F(CanonMakerNoteTest_934, PrintCsLensTypeWithNullMetadata_934) {
  std::ostringstream os;
  UShortValue value;
  value.value_.push_back(0);
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test print0x000c with a value
TEST_F(CanonMakerNoteTest_934, Print0x000cWithValue_934) {
  std::ostringstream os;
  ULongValue value;
  value.value_.push_back(0x00020001);
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test printFiFileNumber with a value and null metadata
TEST_F(CanonMakerNoteTest_934, PrintFiFileNumberWithNullMetadata_934) {
  std::ostringstream os;
  ULongValue value;
  value.value_.push_back(1001);
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test that multiple tag list functions return different pointers (they are different arrays)
TEST_F(CanonMakerNoteTest_934, DifferentTagListsReturnDifferentPointers_934) {
  auto tagListMain = CanonMakerNote::tagList();
  auto tagListCs = CanonMakerNote::tagListCs();
  auto tagListSi = CanonMakerNote::tagListSi();
  auto tagListLe = CanonMakerNote::tagListLe();

  // Each tag list should be a different array
  EXPECT_NE(tagListMain, tagListCs);
  EXPECT_NE(tagListCs, tagListSi);
  EXPECT_NE(tagListSi, tagListLe);
  EXPECT_NE(tagListMain, tagListLe);
}

// Test constexpr nature of tagListLe by using it in a compile-time context
TEST_F(CanonMakerNoteTest_934, TagListLeIsConstexpr_934) {
  constexpr auto tagList = CanonMakerNote::tagListLe();
  EXPECT_NE(tagList, nullptr);
}
