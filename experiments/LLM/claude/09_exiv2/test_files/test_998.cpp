#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "minoltamn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class MinoltaMakerNoteTest_998 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// =============================================================================
// Tests for tagListCs5D()
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, TagListCs5DReturnsNonNull_998) {
    auto tagList = MinoltaMakerNote::tagListCs5D();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(MinoltaMakerNoteTest_998, TagListCs5DConsistentOnMultipleCalls_998) {
    auto tagList1 = MinoltaMakerNote::tagListCs5D();
    auto tagList2 = MinoltaMakerNote::tagListCs5D();
    EXPECT_EQ(tagList1, tagList2);
}

// =============================================================================
// Tests for tagList()
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, TagListReturnsNonNull_998) {
    auto tagList = MinoltaMakerNote::tagList();
    ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for tagListCsStd()
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, TagListCsStdReturnsNonNull_998) {
    auto tagList = MinoltaMakerNote::tagListCsStd();
    ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for tagListCs7D()
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, TagListCs7DReturnsNonNull_998) {
    auto tagList = MinoltaMakerNote::tagListCs7D();
    ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for tagListCsA100()
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, TagListCsA100ReturnsNonNull_998) {
    auto tagList = MinoltaMakerNote::tagListCsA100();
    ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for printMinoltaExposureSpeedStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintExposureSpeedStdNormalValue_998) {
    ULongValue value;
    value.read("104");
    MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintExposureSpeedStdZeroValue_998) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaExposureTimeStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintExposureTimeStdNormalValue_998) {
    ULongValue value;
    value.read("128");
    MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintExposureTimeStdZeroValue_998) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaFNumberStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintFNumberStdNormalValue_998) {
    ULongValue value;
    value.read("56");
    MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintFNumberStdZeroValue_998) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaExposureCompensationStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintExposureCompensationStdNormalValue_998) {
    ULongValue value;
    value.read("100");
    MinoltaMakerNote::printMinoltaExposureCompensationStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintExposureCompensationStdZero_998) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaExposureCompensationStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaFocalLengthStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintFocalLengthStdNormalValue_998) {
    ULongValue value;
    value.read("50");
    MinoltaMakerNote::printMinoltaFocalLengthStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintFocalLengthStdZeroValue_998) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaFocalLengthStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaDateStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintDateStdNormalValue_998) {
    ULongValue value;
    value.read("20230115");
    MinoltaMakerNote::printMinoltaDateStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintDateStdZeroValue_998) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaDateStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaTimeStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintTimeStdNormalValue_998) {
    ULongValue value;
    value.read("123456");
    MinoltaMakerNote::printMinoltaTimeStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintTimeStdZeroValue_998) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaTimeStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaFlashExposureCompStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintFlashExposureCompStdNormalValue_998) {
    ULongValue value;
    value.read("100");
    MinoltaMakerNote::printMinoltaFlashExposureCompStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintFlashExposureCompStdZeroValue_998) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaFlashExposureCompStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaWhiteBalanceStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintWhiteBalanceStdNormalValue_998) {
    ULongValue value;
    value.read("5");
    MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintWhiteBalanceStdZeroValue_998) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaBrightnessStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintBrightnessStdNormalValue_998) {
    ULongValue value;
    value.read("128");
    MinoltaMakerNote::printMinoltaBrightnessStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintBrightnessStdZeroValue_998) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaBrightnessStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaExposureManualBias5D
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintExposureManualBias5DNormalValue_998) {
    ULongValue value;
    value.read("100");
    MinoltaMakerNote::printMinoltaExposureManualBias5D(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintExposureManualBias5DZeroValue_998) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaExposureManualBias5D(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaExposureCompensation5D
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintExposureCompensation5DNormalValue_998) {
    ULongValue value;
    value.read("100");
    MinoltaMakerNote::printMinoltaExposureCompensation5D(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintExposureCompensation5DZeroValue_998) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaExposureCompensation5D(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for return reference of ostream
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintFunctionsReturnSameStream_998) {
    ULongValue value;
    value.read("100");
    std::ostream& ref = MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
    EXPECT_EQ(&ref, &os);
}

TEST_F(MinoltaMakerNoteTest_998, PrintExposureTimeReturnsSameStream_998) {
    ULongValue value;
    value.read("128");
    std::ostream& ref = MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
    EXPECT_EQ(&ref, &os);
}

TEST_F(MinoltaMakerNoteTest_998, PrintFNumberReturnsSameStream_998) {
    ULongValue value;
    value.read("56");
    std::ostream& ref = MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
    EXPECT_EQ(&ref, &os);
}

TEST_F(MinoltaMakerNoteTest_998, PrintDateReturnsSameStream_998) {
    ULongValue value;
    value.read("20230115");
    std::ostream& ref = MinoltaMakerNote::printMinoltaDateStd(os, value, nullptr);
    EXPECT_EQ(&ref, &os);
}

TEST_F(MinoltaMakerNoteTest_998, PrintTimeReturnsSameStream_998) {
    ULongValue value;
    value.read("123456");
    std::ostream& ref = MinoltaMakerNote::printMinoltaTimeStd(os, value, nullptr);
    EXPECT_EQ(&ref, &os);
}

TEST_F(MinoltaMakerNoteTest_998, PrintWhiteBalanceReturnsSameStream_998) {
    ULongValue value;
    value.read("5");
    std::ostream& ref = MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, value, nullptr);
    EXPECT_EQ(&ref, &os);
}

TEST_F(MinoltaMakerNoteTest_998, PrintBrightnessReturnsSameStream_998) {
    ULongValue value;
    value.read("128");
    std::ostream& ref = MinoltaMakerNote::printMinoltaBrightnessStd(os, value, nullptr);
    EXPECT_EQ(&ref, &os);
}

TEST_F(MinoltaMakerNoteTest_998, PrintFlashExposureCompReturnsSameStream_998) {
    ULongValue value;
    value.read("100");
    std::ostream& ref = MinoltaMakerNote::printMinoltaFlashExposureCompStd(os, value, nullptr);
    EXPECT_EQ(&ref, &os);
}

TEST_F(MinoltaMakerNoteTest_998, PrintExposureCompensationReturnsSameStream_998) {
    ULongValue value;
    value.read("100");
    std::ostream& ref = MinoltaMakerNote::printMinoltaExposureCompensationStd(os, value, nullptr);
    EXPECT_EQ(&ref, &os);
}

TEST_F(MinoltaMakerNoteTest_998, PrintFocalLengthReturnsSameStream_998) {
    ULongValue value;
    value.read("50");
    std::ostream& ref = MinoltaMakerNote::printMinoltaFocalLengthStd(os, value, nullptr);
    EXPECT_EQ(&ref, &os);
}

TEST_F(MinoltaMakerNoteTest_998, PrintExposureManualBias5DReturnsSameStream_998) {
    ULongValue value;
    value.read("100");
    std::ostream& ref = MinoltaMakerNote::printMinoltaExposureManualBias5D(os, value, nullptr);
    EXPECT_EQ(&ref, &os);
}

TEST_F(MinoltaMakerNoteTest_998, PrintExposureCompensation5DReturnsSameStream_998) {
    ULongValue value;
    value.read("100");
    std::ostream& ref = MinoltaMakerNote::printMinoltaExposureCompensation5D(os, value, nullptr);
    EXPECT_EQ(&ref, &os);
}

// =============================================================================
// Tests for boundary / large values
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, PrintExposureSpeedStdLargeValue_998) {
    ULongValue value;
    value.read("4294967295");  // max uint32
    MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintExposureTimeStdLargeValue_998) {
    ULongValue value;
    value.read("4294967295");
    MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_998, PrintFNumberStdLargeValue_998) {
    ULongValue value;
    value.read("4294967295");
    MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for TagInfo content from tagListCs5D
// =============================================================================

TEST_F(MinoltaMakerNoteTest_998, TagListCs5DFirstEntryHasValidTag_998) {
    auto tagList = MinoltaMakerNote::tagListCs5D();
    ASSERT_NE(tagList, nullptr);
    // The first entry should be a valid TagInfo (tag >= 0 typically, or some sentinel)
    // We just check that we can access it without crashing
    EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(MinoltaMakerNoteTest_998, TagListFirstEntryHasValidTag_998) {
    auto tagList = MinoltaMakerNote::tagList();
    ASSERT_NE(tagList, nullptr);
    EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(MinoltaMakerNoteTest_998, TagListCsStdFirstEntryHasValidTag_998) {
    auto tagList = MinoltaMakerNote::tagListCsStd();
    ASSERT_NE(tagList, nullptr);
    EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(MinoltaMakerNoteTest_998, TagListCs7DFirstEntryHasValidTag_998) {
    auto tagList = MinoltaMakerNote::tagListCs7D();
    ASSERT_NE(tagList, nullptr);
    EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(MinoltaMakerNoteTest_998, TagListCsA100FirstEntryHasValidTag_998) {
    auto tagList = MinoltaMakerNote::tagListCsA100();
    ASSERT_NE(tagList, nullptr);
    EXPECT_GE(tagList[0].tag_, 0);
}
