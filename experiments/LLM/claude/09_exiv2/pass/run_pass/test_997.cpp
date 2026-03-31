#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "minoltamn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class MinoltaMakerNoteTest_997 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// =============================================================================
// Tests for tagListCs7D()
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, TagListCs7DReturnsNonNull_997) {
    auto tagList = MinoltaMakerNote::tagListCs7D();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(MinoltaMakerNoteTest_997, TagListCs7DIsConsistent_997) {
    auto tagList1 = MinoltaMakerNote::tagListCs7D();
    auto tagList2 = MinoltaMakerNote::tagListCs7D();
    EXPECT_EQ(tagList1, tagList2);
}

// =============================================================================
// Tests for tagList()
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, TagListReturnsNonNull_997) {
    auto tagList = MinoltaMakerNote::tagList();
    ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for tagListCsStd()
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, TagListCsStdReturnsNonNull_997) {
    auto tagList = MinoltaMakerNote::tagListCsStd();
    ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for tagListCs5D()
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, TagListCs5DReturnsNonNull_997) {
    auto tagList = MinoltaMakerNote::tagListCs5D();
    ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for tagListCsA100()
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, TagListCsA100ReturnsNonNull_997) {
    auto tagList = MinoltaMakerNote::tagListCsA100();
    ASSERT_NE(tagList, nullptr);
}

// =============================================================================
// Tests for printMinoltaExposureSpeedStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintExposureSpeedStdNormalValue_997) {
    ULongValue value;
    value.read("104");
    MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintExposureSpeedStdZeroValue_997) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaExposureTimeStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintExposureTimeStdNormalValue_997) {
    ULongValue value;
    value.read("104");
    MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintExposureTimeStdZeroValue_997) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaFNumberStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintFNumberStdNormalValue_997) {
    ULongValue value;
    value.read("16");
    MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintFNumberStdZeroValue_997) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaExposureCompensationStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintExposureCompensationStdNormalValue_997) {
    ULongValue value;
    value.read("100");
    MinoltaMakerNote::printMinoltaExposureCompensationStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintExposureCompensationStdZeroValue_997) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaExposureCompensationStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaFocalLengthStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintFocalLengthStdNormalValue_997) {
    ULongValue value;
    value.read("50");
    MinoltaMakerNote::printMinoltaFocalLengthStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintFocalLengthStdZeroValue_997) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaFocalLengthStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaDateStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintDateStdNormalValue_997) {
    ULongValue value;
    value.read("20230615");
    MinoltaMakerNote::printMinoltaDateStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintDateStdZeroValue_997) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaDateStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaTimeStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintTimeStdNormalValue_997) {
    ULongValue value;
    value.read("123045");
    MinoltaMakerNote::printMinoltaTimeStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintTimeStdZeroValue_997) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaTimeStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaFlashExposureCompStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintFlashExposureCompStdNormalValue_997) {
    ULongValue value;
    value.read("100");
    MinoltaMakerNote::printMinoltaFlashExposureCompStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintFlashExposureCompStdZeroValue_997) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaFlashExposureCompStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaWhiteBalanceStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintWhiteBalanceStdNormalValue_997) {
    ULongValue value;
    value.read("50");
    MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintWhiteBalanceStdZeroValue_997) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaBrightnessStd
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintBrightnessStdNormalValue_997) {
    ULongValue value;
    value.read("128");
    MinoltaMakerNote::printMinoltaBrightnessStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintBrightnessStdZeroValue_997) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaBrightnessStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaExposureManualBias5D
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintExposureManualBias5DNormalValue_997) {
    ULongValue value;
    value.read("100");
    MinoltaMakerNote::printMinoltaExposureManualBias5D(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintExposureManualBias5DZeroValue_997) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaExposureManualBias5D(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for printMinoltaExposureCompensation5D
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintExposureCompensation5DNormalValue_997) {
    ULongValue value;
    value.read("100");
    MinoltaMakerNote::printMinoltaExposureCompensation5D(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintExposureCompensation5DZeroValue_997) {
    ULongValue value;
    value.read("0");
    MinoltaMakerNote::printMinoltaExposureCompensation5D(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Tests for return type of print functions (stream reference)
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintFunctionsReturnSameStream_997) {
    ULongValue value;
    value.read("100");
    
    std::ostream& ret1 = MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
    EXPECT_EQ(&ret1, &os);
    
    std::ostringstream os2;
    std::ostream& ret2 = MinoltaMakerNote::printMinoltaExposureTimeStd(os2, value, nullptr);
    EXPECT_EQ(&ret2, &os2);
    
    std::ostringstream os3;
    std::ostream& ret3 = MinoltaMakerNote::printMinoltaFNumberStd(os3, value, nullptr);
    EXPECT_EQ(&ret3, &os3);
    
    std::ostringstream os4;
    std::ostream& ret4 = MinoltaMakerNote::printMinoltaExposureCompensationStd(os4, value, nullptr);
    EXPECT_EQ(&ret4, &os4);
    
    std::ostringstream os5;
    std::ostream& ret5 = MinoltaMakerNote::printMinoltaFocalLengthStd(os5, value, nullptr);
    EXPECT_EQ(&ret5, &os5);
    
    std::ostringstream os6;
    std::ostream& ret6 = MinoltaMakerNote::printMinoltaDateStd(os6, value, nullptr);
    EXPECT_EQ(&ret6, &os6);
    
    std::ostringstream os7;
    std::ostream& ret7 = MinoltaMakerNote::printMinoltaTimeStd(os7, value, nullptr);
    EXPECT_EQ(&ret7, &os7);
    
    std::ostringstream os8;
    std::ostream& ret8 = MinoltaMakerNote::printMinoltaFlashExposureCompStd(os8, value, nullptr);
    EXPECT_EQ(&ret8, &os8);
    
    std::ostringstream os9;
    std::ostream& ret9 = MinoltaMakerNote::printMinoltaWhiteBalanceStd(os9, value, nullptr);
    EXPECT_EQ(&ret9, &os9);
    
    std::ostringstream os10;
    std::ostream& ret10 = MinoltaMakerNote::printMinoltaBrightnessStd(os10, value, nullptr);
    EXPECT_EQ(&ret10, &os10);
    
    std::ostringstream os11;
    std::ostream& ret11 = MinoltaMakerNote::printMinoltaExposureManualBias5D(os11, value, nullptr);
    EXPECT_EQ(&ret11, &os11);
    
    std::ostringstream os12;
    std::ostream& ret12 = MinoltaMakerNote::printMinoltaExposureCompensation5D(os12, value, nullptr);
    EXPECT_EQ(&ret12, &os12);
}

// =============================================================================
// Tests with large values (boundary)
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintExposureSpeedStdLargeValue_997) {
    ULongValue value;
    value.read("4294967295"); // UINT32_MAX
    MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintExposureTimeStdLargeValue_997) {
    ULongValue value;
    value.read("4294967295");
    MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintFNumberStdLargeValue_997) {
    ULongValue value;
    value.read("4294967295");
    MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Consistency tests - calling same function twice with same input
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintExposureSpeedStdConsistency_997) {
    ULongValue value;
    value.read("104");
    
    std::ostringstream os1, os2;
    MinoltaMakerNote::printMinoltaExposureSpeedStd(os1, value, nullptr);
    MinoltaMakerNote::printMinoltaExposureSpeedStd(os2, value, nullptr);
    EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(MinoltaMakerNoteTest_997, PrintFNumberStdConsistency_997) {
    ULongValue value;
    value.read("16");
    
    std::ostringstream os1, os2;
    MinoltaMakerNote::printMinoltaFNumberStd(os1, value, nullptr);
    MinoltaMakerNote::printMinoltaFNumberStd(os2, value, nullptr);
    EXPECT_EQ(os1.str(), os2.str());
}

// =============================================================================
// Tests for tagList consistency across multiple calls
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, AllTagListsAreConsistentAcrossCalls_997) {
    auto tl1a = MinoltaMakerNote::tagList();
    auto tl1b = MinoltaMakerNote::tagList();
    EXPECT_EQ(tl1a, tl1b);
    
    auto tl2a = MinoltaMakerNote::tagListCsStd();
    auto tl2b = MinoltaMakerNote::tagListCsStd();
    EXPECT_EQ(tl2a, tl2b);
    
    auto tl3a = MinoltaMakerNote::tagListCs7D();
    auto tl3b = MinoltaMakerNote::tagListCs7D();
    EXPECT_EQ(tl3a, tl3b);
    
    auto tl4a = MinoltaMakerNote::tagListCs5D();
    auto tl4b = MinoltaMakerNote::tagListCs5D();
    EXPECT_EQ(tl4a, tl4b);
    
    auto tl5a = MinoltaMakerNote::tagListCsA100();
    auto tl5b = MinoltaMakerNote::tagListCsA100();
    EXPECT_EQ(tl5a, tl5b);
}

// =============================================================================
// Test that different tagLists are distinct (or at least callable)
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, DifferentTagListsAreCallable_997) {
    auto tl = MinoltaMakerNote::tagList();
    auto tlCsStd = MinoltaMakerNote::tagListCsStd();
    auto tlCs7D = MinoltaMakerNote::tagListCs7D();
    auto tlCs5D = MinoltaMakerNote::tagListCs5D();
    auto tlCsA100 = MinoltaMakerNote::tagListCsA100();
    
    // All should be non-null
    EXPECT_NE(tl, nullptr);
    EXPECT_NE(tlCsStd, nullptr);
    EXPECT_NE(tlCs7D, nullptr);
    EXPECT_NE(tlCs5D, nullptr);
    EXPECT_NE(tlCsA100, nullptr);
}

// =============================================================================
// Tests with value of 1
// =============================================================================

TEST_F(MinoltaMakerNoteTest_997, PrintExposureSpeedStdValueOne_997) {
    ULongValue value;
    value.read("1");
    MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintFocalLengthStdValueOne_997) {
    ULongValue value;
    value.read("1");
    MinoltaMakerNote::printMinoltaFocalLengthStd(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintWhiteBalanceStdValueOne_997) {
    ULongValue value;
    value.read("1");
    MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintBrightnessStdValueOne_997) {
    ULongValue value;
    value.read("1");
    MinoltaMakerNote::printMinoltaBrightnessStd(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintExposureManualBias5DValueOne_997) {
    ULongValue value;
    value.read("1");
    MinoltaMakerNote::printMinoltaExposureManualBias5D(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_997, PrintExposureCompensation5DValueOne_997) {
    ULongValue value;
    value.read("1");
    MinoltaMakerNote::printMinoltaExposureCompensation5D(os, value, nullptr);
    EXPECT_FALSE(os.str().empty());
}
