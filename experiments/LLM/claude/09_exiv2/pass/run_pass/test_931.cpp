#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_931 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// ==================== tagList functions tests ====================

TEST_F(CanonMakerNoteTest_931, TagListVigCorNotNull_931) {
    auto tagList = CanonMakerNote::tagListVigCor();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListNotNull_931) {
    auto tagList = CanonMakerNote::tagList();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListCsNotNull_931) {
    auto tagList = CanonMakerNote::tagListCs();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListSiNotNull_931) {
    auto tagList = CanonMakerNote::tagListSi();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListPaNotNull_931) {
    auto tagList = CanonMakerNote::tagListPa();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListCfNotNull_931) {
    auto tagList = CanonMakerNote::tagListCf();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListPiNotNull_931) {
    auto tagList = CanonMakerNote::tagListPi();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListTiNotNull_931) {
    auto tagList = CanonMakerNote::tagListTi();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListFiNotNull_931) {
    auto tagList = CanonMakerNote::tagListFi();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListPrNotNull_931) {
    auto tagList = CanonMakerNote::tagListPr();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListMvNotNull_931) {
    auto tagList = CanonMakerNote::tagListMv();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListMcNotNull_931) {
    auto tagList = CanonMakerNote::tagListMc();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListFcd3NotNull_931) {
    auto tagList = CanonMakerNote::tagListFcd3();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListWbiNotNull_931) {
    auto tagList = CanonMakerNote::tagListWbi();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListCoNotNull_931) {
    auto tagList = CanonMakerNote::tagListCo();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListFcd2NotNull_931) {
    auto tagList = CanonMakerNote::tagListFcd2();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListFcd1NotNull_931) {
    auto tagList = CanonMakerNote::tagListFcd1();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListAsNotNull_931) {
    auto tagList = CanonMakerNote::tagListAs();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListCbiNotNull_931) {
    auto tagList = CanonMakerNote::tagListCbi();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListFlNotNull_931) {
    auto tagList = CanonMakerNote::tagListFl();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListMoNotNull_931) {
    auto tagList = CanonMakerNote::tagListMo();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListPreINotNull_931) {
    auto tagList = CanonMakerNote::tagListPreI();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListCiNotNull_931) {
    auto tagList = CanonMakerNote::tagListCi();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListAfMiAdjNotNull_931) {
    auto tagList = CanonMakerNote::tagListAfMiAdj();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListVigCor2NotNull_931) {
    auto tagList = CanonMakerNote::tagListVigCor2();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListLiOpNotNull_931) {
    auto tagList = CanonMakerNote::tagListLiOp();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListLeNotNull_931) {
    auto tagList = CanonMakerNote::tagListLe();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListAmNotNull_931) {
    auto tagList = CanonMakerNote::tagListAm();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListMeNotNull_931) {
    auto tagList = CanonMakerNote::tagListMe();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListFilNotNull_931) {
    auto tagList = CanonMakerNote::tagListFil();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListHdrNotNull_931) {
    auto tagList = CanonMakerNote::tagListHdr();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListAfCNotNull_931) {
    auto tagList = CanonMakerNote::tagListAfC();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_931, TagListRawBNotNull_931) {
    auto tagList = CanonMakerNote::tagListRawB();
    ASSERT_NE(tagList, nullptr);
}

// ==================== Print function tests ====================

TEST_F(CanonMakerNoteTest_931, PrintFocalLengthWithSingleValue_931) {
    UShortValue value;
    value.read("1000");
    auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    // Output should not be empty
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_931, PrintFocalLengthWithMultipleValues_931) {
    UShortValue value;
    value.read("1 1000 0 0");
    auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, Print0x0008WithValue_931) {
    UShortValue value;
    value.read("12345");
    auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, Print0x000aWithValue_931) {
    ULongValue value;
    value.read("12345");
    auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, Print0x000cWithNullExifData_931) {
    ULongValue value;
    value.read("100");
    auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintCs0x0002WithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintCsLensTypeWithValue_931) {
    UShortValue value;
    value.read("1");
    auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintCsLensWithMultipleValues_931) {
    UShortValue value;
    value.read("100 200 1");
    auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintCsLensWithSingleValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0001WithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0002WithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0003WithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0009WithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x000cWithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x000dWithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x000eWithNullExifData_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0013WithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0015WithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0016WithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0017WithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0018WithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintFiFocusDistanceWithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintFiFocusDistanceZero_931) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintFiFocusDistanceMaxValue_931) {
    UShortValue value;
    value.read("65535");
    auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintLe0x0000WithValue_931) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintFiFileNumberWithNullMetadata_931) {
    ULongValue value;
    value.read("1234");
    auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0001WithZeroValue_931) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0002WithZeroValue_931) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0003WithZeroValue_931) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, Print0x000cWithExifData_931) {
    ExifData exifData;
    ULongValue value;
    value.read("100");
    auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x000eWithExifData_931) {
    ExifData exifData;
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintCsLensTypeWithExifData_931) {
    ExifData exifData;
    UShortValue value;
    value.read("1");
    auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintFiFileNumberWithExifData_931) {
    ExifData exifData;
    ULongValue value;
    value.read("1234567");
    auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

// Test that tagListVigCor returns consistent results on multiple calls
TEST_F(CanonMakerNoteTest_931, TagListVigCorConsistency_931) {
    auto tagList1 = CanonMakerNote::tagListVigCor();
    auto tagList2 = CanonMakerNote::tagListVigCor();
    EXPECT_EQ(tagList1, tagList2);
}

// Test that tagList returns consistent results on multiple calls
TEST_F(CanonMakerNoteTest_931, TagListConsistency_931) {
    auto tagList1 = CanonMakerNote::tagList();
    auto tagList2 = CanonMakerNote::tagList();
    EXPECT_EQ(tagList1, tagList2);
}

// Test print functions return reference to the same stream
TEST_F(CanonMakerNoteTest_931, PrintFunctionsReturnSameStream_931) {
    UShortValue value;
    value.read("50");
    std::ostringstream os1, os2;
    auto& r1 = CanonMakerNote::printSi0x0009(os1, value, nullptr);
    auto& r2 = CanonMakerNote::printSi0x000c(os2, value, nullptr);
    EXPECT_EQ(&r1, &os1);
    EXPECT_EQ(&r2, &os2);
}

// Test with large values for boundary conditions
TEST_F(CanonMakerNoteTest_931, PrintSi0x0009WithLargeValue_931) {
    UShortValue value;
    value.read("65535");
    auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x000dWithZeroValue_931) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0015WithLargeValue_931) {
    UShortValue value;
    value.read("65535");
    auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0016WithLargeValue_931) {
    UShortValue value;
    value.read("65535");
    auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0017WithLargeValue_931) {
    UShortValue value;
    value.read("65535");
    auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0018WithLargeValue_931) {
    UShortValue value;
    value.read("65535");
    auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0013WithLargeValue_931) {
    UShortValue value;
    value.read("65535");
    auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintLe0x0000WithZeroValue_931) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintCs0x0002WithZeroValue_931) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, Print0x0008WithZeroValue_931) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, Print0x000aWithZeroValue_931) {
    ULongValue value;
    value.read("0");
    auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x000cWithLargeValue_931) {
    UShortValue value;
    value.read("65535");
    auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test output is not empty for various print functions
TEST_F(CanonMakerNoteTest_931, PrintSi0x0001OutputNotEmpty_931) {
    UShortValue value;
    value.read("160");
    CanonMakerNote::printSi0x0001(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0002OutputNotEmpty_931) {
    UShortValue value;
    value.read("160");
    CanonMakerNote::printSi0x0002(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_931, PrintSi0x0003OutputNotEmpty_931) {
    UShortValue value;
    value.read("160");
    CanonMakerNote::printSi0x0003(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
}
