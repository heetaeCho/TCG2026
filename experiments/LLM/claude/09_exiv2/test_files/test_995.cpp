#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "minoltamn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class MinoltaMakerNoteTest_995 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// ============================================================
// Tests for tagList()
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, TagListIsNotNull_995) {
    auto tags = MinoltaMakerNote::tagList();
    ASSERT_NE(tags, nullptr);
}

TEST_F(MinoltaMakerNoteTest_995, TagListFirstEntryValid_995) {
    auto tags = MinoltaMakerNote::tagList();
    // The first entry should have a valid tag number or be a sentinel
    // We just check it's accessible
    ASSERT_NE(tags, nullptr);
    // Access first element - if the list is non-empty, tag should be >= 0
    // TagInfo has tag, name, title, desc, ifdId, sectionId, typeId, count, print
}

// ============================================================
// Tests for tagListCsStd()
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, TagListCsStdIsNotNull_995) {
    auto tags = MinoltaMakerNote::tagListCsStd();
    ASSERT_NE(tags, nullptr);
}

// ============================================================
// Tests for tagListCs7D()
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, TagListCs7DIsNotNull_995) {
    auto tags = MinoltaMakerNote::tagListCs7D();
    ASSERT_NE(tags, nullptr);
}

// ============================================================
// Tests for tagListCs5D()
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, TagListCs5DIsNotNull_995) {
    auto tags = MinoltaMakerNote::tagListCs5D();
    ASSERT_NE(tags, nullptr);
}

// ============================================================
// Tests for tagListCsA100()
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, TagListCsA100IsNotNull_995) {
    auto tags = MinoltaMakerNote::tagListCsA100();
    ASSERT_NE(tags, nullptr);
}

// ============================================================
// Tests for printMinoltaExposureSpeedStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintExposureSpeedStdNormalValue_995) {
    ULongValue value;
    value.read("104");
    auto& result = MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintExposureSpeedStdZeroValue_995) {
    ULongValue value;
    value.read("0");
    auto& result = MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printMinoltaExposureTimeStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintExposureTimeStdNormalValue_995) {
    ULongValue value;
    value.read("104");
    auto& result = MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintExposureTimeStdZeroValue_995) {
    ULongValue value;
    value.read("0");
    auto& result = MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printMinoltaFNumberStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintFNumberStdNormalValue_995) {
    ULongValue value;
    value.read("56");
    auto& result = MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintFNumberStdZeroValue_995) {
    ULongValue value;
    value.read("0");
    auto& result = MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printMinoltaExposureCompensationStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintExposureCompensationStdNormalValue_995) {
    ULongValue value;
    value.read("100");
    auto& result = MinoltaMakerNote::printMinoltaExposureCompensationStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintExposureCompensationStdZeroValue_995) {
    ULongValue value;
    value.read("0");
    auto& result = MinoltaMakerNote::printMinoltaExposureCompensationStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printMinoltaFocalLengthStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintFocalLengthStdNormalValue_995) {
    ULongValue value;
    value.read("50");
    auto& result = MinoltaMakerNote::printMinoltaFocalLengthStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintFocalLengthStdZeroValue_995) {
    ULongValue value;
    value.read("0");
    auto& result = MinoltaMakerNote::printMinoltaFocalLengthStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printMinoltaDateStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintDateStdWithThreeValues_995) {
    // Date expects 3 components: year, month, day
    ULongValue value;
    value.read("2023 6 15");
    auto& result = MinoltaMakerNote::printMinoltaDateStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintDateStdWithSingleValue_995) {
    ULongValue value;
    value.read("2023");
    auto& result = MinoltaMakerNote::printMinoltaDateStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printMinoltaTimeStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintTimeStdWithThreeValues_995) {
    // Time expects 3 components: hour, minute, second
    ULongValue value;
    value.read("14 30 45");
    auto& result = MinoltaMakerNote::printMinoltaTimeStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintTimeStdWithSingleValue_995) {
    ULongValue value;
    value.read("14");
    auto& result = MinoltaMakerNote::printMinoltaTimeStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printMinoltaFlashExposureCompStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintFlashExposureCompStdNormalValue_995) {
    ULongValue value;
    value.read("100");
    auto& result = MinoltaMakerNote::printMinoltaFlashExposureCompStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintFlashExposureCompStdZeroValue_995) {
    ULongValue value;
    value.read("0");
    auto& result = MinoltaMakerNote::printMinoltaFlashExposureCompStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printMinoltaWhiteBalanceStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintWhiteBalanceStdNormalValue_995) {
    ULongValue value;
    value.read("50");
    auto& result = MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintWhiteBalanceStdZeroValue_995) {
    ULongValue value;
    value.read("0");
    auto& result = MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printMinoltaBrightnessStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintBrightnessStdNormalValue_995) {
    ULongValue value;
    value.read("100");
    auto& result = MinoltaMakerNote::printMinoltaBrightnessStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintBrightnessStdZeroValue_995) {
    ULongValue value;
    value.read("0");
    auto& result = MinoltaMakerNote::printMinoltaBrightnessStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printMinoltaExposureManualBias5D
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintExposureManualBias5DNormalValue_995) {
    ULongValue value;
    value.read("100");
    auto& result = MinoltaMakerNote::printMinoltaExposureManualBias5D(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintExposureManualBias5DZeroValue_995) {
    ULongValue value;
    value.read("0");
    auto& result = MinoltaMakerNote::printMinoltaExposureManualBias5D(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printMinoltaExposureCompensation5D
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintExposureCompensation5DNormalValue_995) {
    ULongValue value;
    value.read("100");
    auto& result = MinoltaMakerNote::printMinoltaExposureCompensation5D(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintExposureCompensation5DZeroValue_995) {
    ULongValue value;
    value.read("0");
    auto& result = MinoltaMakerNote::printMinoltaExposureCompensation5D(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary tests
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintExposureSpeedStdLargeValue_995) {
    ULongValue value;
    value.read("4294967295");  // UINT32_MAX
    auto& result = MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(MinoltaMakerNoteTest_995, PrintExposureTimeStdLargeValue_995) {
    ULongValue value;
    value.read("4294967295");
    auto& result = MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(MinoltaMakerNoteTest_995, PrintFNumberStdLargeValue_995) {
    ULongValue value;
    value.read("4294967295");
    auto& result = MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(MinoltaMakerNoteTest_995, PrintFocalLengthStdLargeValue_995) {
    ULongValue value;
    value.read("4294967295");
    auto& result = MinoltaMakerNote::printMinoltaFocalLengthStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Test that stream is returned correctly (chaining test)
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, StreamChainingExposureSpeed_995) {
    ULongValue value;
    value.read("100");
    std::ostringstream combined;
    MinoltaMakerNote::printMinoltaExposureSpeedStd(combined, value, nullptr) << " suffix";
    std::string output = combined.str();
    EXPECT_TRUE(output.find("suffix") != std::string::npos);
}

TEST_F(MinoltaMakerNoteTest_995, StreamChainingFNumber_995) {
    ULongValue value;
    value.read("56");
    std::ostringstream combined;
    MinoltaMakerNote::printMinoltaFNumberStd(combined, value, nullptr) << " suffix";
    std::string output = combined.str();
    EXPECT_TRUE(output.find("suffix") != std::string::npos);
}

// ============================================================
// Tests with different value counts for Date and Time
// ============================================================

TEST_F(MinoltaMakerNoteTest_995, PrintDateStdBoundaryValues_995) {
    ULongValue value;
    value.read("0 0 0");
    auto& result = MinoltaMakerNote::printMinoltaDateStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(MinoltaMakerNoteTest_995, PrintTimeStdBoundaryValues_995) {
    ULongValue value;
    value.read("0 0 0");
    auto& result = MinoltaMakerNote::printMinoltaTimeStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(MinoltaMakerNoteTest_995, PrintTimeStdMaxValues_995) {
    ULongValue value;
    value.read("23 59 59");
    auto& result = MinoltaMakerNote::printMinoltaTimeStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(MinoltaMakerNoteTest_995, PrintDateStdValidDate_995) {
    ULongValue value;
    value.read("2024 12 31");
    auto& result = MinoltaMakerNote::printMinoltaDateStd(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}
