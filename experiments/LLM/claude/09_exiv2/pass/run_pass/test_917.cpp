#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_917 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(CanonMakerNoteTest_917, TagListMvNotNull_917) {
    auto result = CanonMakerNote::tagListMv();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListNotNull_917) {
    auto result = CanonMakerNote::tagList();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListCsNotNull_917) {
    auto result = CanonMakerNote::tagListCs();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListSiNotNull_917) {
    auto result = CanonMakerNote::tagListSi();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListPaNotNull_917) {
    auto result = CanonMakerNote::tagListPa();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListCfNotNull_917) {
    auto result = CanonMakerNote::tagListCf();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListPiNotNull_917) {
    auto result = CanonMakerNote::tagListPi();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListTiNotNull_917) {
    auto result = CanonMakerNote::tagListTi();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListFiNotNull_917) {
    auto result = CanonMakerNote::tagListFi();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListPrNotNull_917) {
    auto result = CanonMakerNote::tagListPr();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListMcNotNull_917) {
    auto result = CanonMakerNote::tagListMc();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListFcd3NotNull_917) {
    auto result = CanonMakerNote::tagListFcd3();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListWbiNotNull_917) {
    auto result = CanonMakerNote::tagListWbi();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListCoNotNull_917) {
    auto result = CanonMakerNote::tagListCo();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListFcd2NotNull_917) {
    auto result = CanonMakerNote::tagListFcd2();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListFcd1NotNull_917) {
    auto result = CanonMakerNote::tagListFcd1();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListAsNotNull_917) {
    auto result = CanonMakerNote::tagListAs();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListCbiNotNull_917) {
    auto result = CanonMakerNote::tagListCbi();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListFlNotNull_917) {
    auto result = CanonMakerNote::tagListFl();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListMoNotNull_917) {
    auto result = CanonMakerNote::tagListMo();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListPreINotNull_917) {
    auto result = CanonMakerNote::tagListPreI();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListCiNotNull_917) {
    auto result = CanonMakerNote::tagListCi();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListAfMiAdjNotNull_917) {
    auto result = CanonMakerNote::tagListAfMiAdj();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListVigCorNotNull_917) {
    auto result = CanonMakerNote::tagListVigCor();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListVigCor2NotNull_917) {
    auto result = CanonMakerNote::tagListVigCor2();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListLiOpNotNull_917) {
    auto result = CanonMakerNote::tagListLiOp();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListLeNotNull_917) {
    auto result = CanonMakerNote::tagListLe();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListAmNotNull_917) {
    auto result = CanonMakerNote::tagListAm();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListMeNotNull_917) {
    auto result = CanonMakerNote::tagListMe();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListFilNotNull_917) {
    auto result = CanonMakerNote::tagListFil();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListHdrNotNull_917) {
    auto result = CanonMakerNote::tagListHdr();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListAfCNotNull_917) {
    auto result = CanonMakerNote::tagListAfC();
    EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_917, TagListRawBNotNull_917) {
    auto result = CanonMakerNote::tagListRawB();
    EXPECT_NE(result, nullptr);
}

// ============================================================
// Tests for print functions with various value types
// ============================================================

TEST_F(CanonMakerNoteTest_917, PrintFocalLengthWithSingleValue_917) {
    UShortValue value;
    value.read("1");
    auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    // Output should be non-empty or at least the function returns successfully
}

TEST_F(CanonMakerNoteTest_917, PrintFocalLengthWithMultipleValues_917) {
    UShortValue value;
    value.read("1 50 0 0");
    auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, Print0x0008WithValue_917) {
    UShortValue value;
    value.read("12345");
    auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, Print0x000aWithValue_917) {
    ULongValue value;
    value.read("12345678");
    auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, Print0x000cWithNullExifData_917) {
    ULongValue value;
    value.read("12345678");
    auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintCs0x0002WithValue_917) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintCsLensTypeWithValue_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintCsLensWithMultipleValues_917) {
    UShortValue value;
    value.read("50 18 1 1");
    auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintCsLensWithSingleValue_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintLe0x0000WithValue_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0001WithValue_917) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0002WithValue_917) {
    UShortValue value;
    value.read("160");
    auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0003WithValue_917) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0009WithValue_917) {
    UShortValue value;
    value.read("10");
    auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x000cWithValue_917) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x000dWithValue_917) {
    UShortValue value;
    value.read("300");
    auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x000eWithNullExifData_917) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x000eWithExifData_917) {
    UShortValue value;
    value.read("100");
    ExifData exifData;
    auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0013WithValue_917) {
    UShortValue value;
    value.read("50");
    auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0015WithValue_917) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0016WithValue_917) {
    UShortValue value;
    value.read("100");
    auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0017WithValue_917) {
    UShortValue value;
    value.read("5");
    auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0018WithValue_917) {
    UShortValue value;
    value.read("3");
    auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintFiFocusDistanceWithValue_917) {
    UShortValue value;
    value.read("500");
    auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintFiFocusDistanceWithZero_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintFiFocusDistanceWithMaxValue_917) {
    UShortValue value;
    value.read("65535");
    auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintFiFileNumberWithValue_917) {
    ULongValue value;
    value.read("1234567");
    auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintFiFileNumberWithExifData_917) {
    ULongValue value;
    value.read("1234567");
    ExifData exifData;
    auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for boundary conditions
// ============================================================

TEST_F(CanonMakerNoteTest_917, PrintSi0x0001WithZeroValue_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0002WithZeroValue_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintCsLensTypeWithExifData_917) {
    UShortValue value;
    value.read("255");
    ExifData exifData;
    auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, Print0x000cWithExifData_917) {
    ULongValue value;
    value.read("0");
    ExifData exifData;
    auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0009WithZero_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x000dWithZero_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0013WithZero_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0015WithZero_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0016WithZero_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0017WithZero_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0018WithZero_917) {
    UShortValue value;
    value.read("0");
    auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for output content verification
// ============================================================

TEST_F(CanonMakerNoteTest_917, PrintFiFocusDistanceProducesOutput_917) {
    UShortValue value;
    value.read("100");
    CanonMakerNote::printFiFocusDistance(os, value, nullptr);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_917, PrintSi0x0002ProducesOutput_917) {
    UShortValue value;
    value.read("160");
    CanonMakerNote::printSi0x0002(os, value, nullptr);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_917, Print0x0008ProducesOutput_917) {
    UShortValue value;
    value.read("12345");
    CanonMakerNote::print0x0008(os, value, nullptr);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_917, PrintLe0x0000WithNonZeroValue_917) {
    UShortValue value;
    value.read("5");
    auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for tag list consistency
// ============================================================

TEST_F(CanonMakerNoteTest_917, TagListMvReturnsConsistentPointer_917) {
    auto result1 = CanonMakerNote::tagListMv();
    auto result2 = CanonMakerNote::tagListMv();
    EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_917, TagListReturnsConsistentPointer_917) {
    auto result1 = CanonMakerNote::tagList();
    auto result2 = CanonMakerNote::tagList();
    EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_917, TagListCsReturnsConsistentPointer_917) {
    auto result1 = CanonMakerNote::tagListCs();
    auto result2 = CanonMakerNote::tagListCs();
    EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_917, TagListSiReturnsConsistentPointer_917) {
    auto result1 = CanonMakerNote::tagListSi();
    auto result2 = CanonMakerNote::tagListSi();
    EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_917, TagListFiReturnsConsistentPointer_917) {
    auto result1 = CanonMakerNote::tagListFi();
    auto result2 = CanonMakerNote::tagListFi();
    EXPECT_EQ(result1, result2);
}
