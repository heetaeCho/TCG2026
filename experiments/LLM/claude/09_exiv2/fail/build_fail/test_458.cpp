#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cmath>

// We need to access the static function. Since it's defined in a .cpp file and is static,
// we need to include it or recreate the declaration. Since we're testing as black box,
// we'll include the source file directly to access the static function.
// This is a common technique for testing static functions in C++ files.

// Forward declaration approach won't work for static functions, so we include the source.
// However, we need the necessary headers that the source file depends on.

#include "exiv2/exiv2.hpp"

// Since the function is static within the .cpp file, we need to access it.
// We'll use a workaround: include the cpp file to get access to the static function.
// This requires careful handling of potential multiple definitions.

// Re-declare the namespace and function signature for testing purposes.
// We'll need to pull in the actual implementation.
namespace {
// We'll redefine the function access by including the cpp file in our test translation unit
}

// Include the source file to get access to the static function
#include "nikonmn_int.cpp"

using namespace Exiv2::Internal;

// Helper to call printFlashCompensationValue and return the result as string
static std::string callPrintFlash(unsigned char value, bool manualScale) {
    std::ostringstream os;
    printFlashCompensationValue(os, value, manualScale);
    return os.str();
}

// =============================================================================
// Tests for Manual Scale mode (manualScale == true)
// =============================================================================

class PrintFlashCompensationManualTest_458 : public ::testing::Test {};

TEST_F(PrintFlashCompensationManualTest_458, Value0_FullPower_458) {
    // value=0 => "1/1" with no modifier (mod=0)
    std::string result = callPrintFlash(0, true);
    EXPECT_NE(result.find("1/1"), std::string::npos);
    // No modifier portion
    EXPECT_EQ(result.find("(-"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value1_FullPowerMinus1_6_458) {
    // value=1 => "1/1 (-1/6 EV)"
    std::string result = callPrintFlash(1, true);
    EXPECT_NE(result.find("1/1"), std::string::npos);
    EXPECT_NE(result.find("1/6 EV)"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value2_FullPowerMinus1_3_458) {
    // value=2 => "1/1 (-1/3 EV)"
    std::string result = callPrintFlash(2, true);
    EXPECT_NE(result.find("1/1"), std::string::npos);
    EXPECT_NE(result.find("1/3 EV)"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value3_FullPowerMinus1_2_458) {
    // value=3 => "1/1 (-1/2 EV)"
    std::string result = callPrintFlash(3, true);
    EXPECT_NE(result.find("1/1"), std::string::npos);
    EXPECT_NE(result.find("1/2 EV)"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value4_FullPowerMinus2_3_458) {
    // value=4 => "1/1 (-2/3 EV)"
    std::string result = callPrintFlash(4, true);
    EXPECT_NE(result.find("1/1"), std::string::npos);
    EXPECT_NE(result.find("2/3 EV)"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value5_FullPowerMinus5_6_458) {
    // value=5 => "1/1 (-5/6 EV)"
    std::string result = callPrintFlash(5, true);
    EXPECT_NE(result.find("1/1"), std::string::npos);
    EXPECT_NE(result.find("5/6 EV)"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value6_HalfPower_458) {
    // value=6 => "1/2" with no modifier
    std::string result = callPrintFlash(6, true);
    EXPECT_NE(result.find("1/2"), std::string::npos);
    EXPECT_EQ(result.find("(-"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value7_HalfPowerMinus1_6_458) {
    // value=7 => "1/2 (-1/6 EV)"
    std::string result = callPrintFlash(7, true);
    EXPECT_NE(result.find("1/2"), std::string::npos);
    EXPECT_NE(result.find("1/6 EV)"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value12_QuarterPower_458) {
    // value=12 => "1/4" with no modifier
    std::string result = callPrintFlash(12, true);
    EXPECT_NE(result.find("1/4"), std::string::npos);
    EXPECT_EQ(result.find("(-"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value18_EighthPower_458) {
    // value=18 => "1/8"
    std::string result = callPrintFlash(18, true);
    EXPECT_NE(result.find("1/8"), std::string::npos);
    EXPECT_EQ(result.find("(-"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value24_SixteenthPower_458) {
    // value=24 => "1/16"
    std::string result = callPrintFlash(24, true);
    EXPECT_NE(result.find("1/16"), std::string::npos);
    EXPECT_EQ(result.find("(-"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value30_ThirtySecondPower_458) {
    // value=30 => "1/32"
    std::string result = callPrintFlash(30, true);
    EXPECT_NE(result.find("1/32"), std::string::npos);
    EXPECT_EQ(result.find("(-"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value36_SixtyFourthPower_458) {
    // value=36 => "1/64"
    std::string result = callPrintFlash(36, true);
    EXPECT_NE(result.find("1/64"), std::string::npos);
    EXPECT_EQ(result.find("(-"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value42_128thPower_458) {
    // value=42 => "1/128"
    std::string result = callPrintFlash(42, true);
    EXPECT_NE(result.find("1/128"), std::string::npos);
    EXPECT_EQ(result.find("(-"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value48_256thPower_458) {
    // value=48 => "1/256"
    std::string result = callPrintFlash(48, true);
    EXPECT_NE(result.find("1/256"), std::string::npos);
    EXPECT_EQ(result.find("(-"), std::string::npos);
}

TEST_F(PrintFlashCompensationManualTest_458, Value49_OutOfRange_458) {
    // value=49 => out of range, should output "(49)"
    std::string result = callPrintFlash(49, true);
    EXPECT_EQ(result, "(49)");
}

TEST_F(PrintFlashCompensationManualTest_458, Value100_OutOfRange_458) {
    // value=100 => out of range
    std::string result = callPrintFlash(100, true);
    EXPECT_EQ(result, "(100)");
}

TEST_F(PrintFlashCompensationManualTest_458, Value255_OutOfRange_458) {
    // value=255 => out of range
    std::string result = callPrintFlash(255, true);
    EXPECT_EQ(result, "(255)");
}

TEST_F(PrintFlashCompensationManualTest_458, Value13_QuarterWithMod1_458) {
    // value=13 => 1/4 (-1/6 EV)
    std::string result = callPrintFlash(13, true);
    EXPECT_NE(result.find("1/4"), std::string::npos);
    EXPECT_NE(result.find("1/6 EV)"), std::string::npos);
}

// =============================================================================
// Tests for Non-Manual Scale mode (manualScale == false)
// =============================================================================

class PrintFlashCompensationAutoTest_458 : public ::testing::Test {};

TEST_F(PrintFlashCompensationAutoTest_458, Value0_ZeroEV_458) {
    // value=0 => "0.0 EV" (no sign)
    std::string result = callPrintFlash(0, false);
    // Should contain "0.0" and "EV"
    EXPECT_NE(result.find("0.0"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
    // Should NOT have + or - sign since value is 0
    EXPECT_EQ(result.find("+"), std::string::npos);
    EXPECT_EQ(result.find("-"), std::string::npos);
}

TEST_F(PrintFlashCompensationAutoTest_458, Value1_Minus0_2EV_458) {
    // value=1 => output = -1.0, output/6 = -0.166... => "-0.2 EV" (with precision 1)
    std::string result = callPrintFlash(1, false);
    EXPECT_NE(result.find("-0.2"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationAutoTest_458, Value2_Minus0_3EV_458) {
    // value=2 => output = -2.0, output/6 = -0.333... => "-0.3 EV"
    std::string result = callPrintFlash(2, false);
    EXPECT_NE(result.find("-0.3"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationAutoTest_458, Value3_Minus0_5EV_458) {
    // value=3 => output = -3.0, output/6 = -0.5 => "-0.5 EV"
    std::string result = callPrintFlash(3, false);
    EXPECT_NE(result.find("-0.5"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationAutoTest_458, Value6_Minus1_0EV_458) {
    // value=6 => output = -6.0, output/6 = -1.0 => "-1.0 EV"
    std::string result = callPrintFlash(6, false);
    EXPECT_NE(result.find("-1.0"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationAutoTest_458, Value12_Minus2_0EV_458) {
    // value=12 => output = -12.0, output/6 = -2.0 => "-2.0 EV"
    std::string result = callPrintFlash(12, false);
    EXPECT_NE(result.find("-2.0"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationAutoTest_458, Value127_Minus21_2EV_458) {
    // value=127 => output = -127.0, output/6 = -21.1666... => "-21.2 EV"
    std::string result = callPrintFlash(127, false);
    EXPECT_NE(result.find("-21.2"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationAutoTest_458, Value128_Plus21_3EV_458) {
    // value=128 => output = 256-128 = 128, output/6 = 21.333... => "+21.3 EV"
    std::string result = callPrintFlash(128, false);
    EXPECT_NE(result.find("+21.3"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationAutoTest_458, Value129_Plus21_2EV_458) {
    // value=129 => output = 256-129 = 127, output/6 = 21.166... => "+21.2 EV"
    std::string result = callPrintFlash(129, false);
    EXPECT_NE(result.find("+21.2"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationAutoTest_458, Value255_Plus0_2EV_458) {
    // value=255 => output = 256-255 = 1, output/6 = 0.166... => "+0.2 EV"
    std::string result = callPrintFlash(255, false);
    EXPECT_NE(result.find("+0.2"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationAutoTest_458, Value250_Plus1_0EV_458) {
    // value=250 => output = 256-250 = 6, output/6 = 1.0 => "+1.0 EV"
    std::string result = callPrintFlash(250, false);
    EXPECT_NE(result.find("+1.0"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationAutoTest_458, Value244_Plus2_0EV_458) {
    // value=244 => output = 256-244 = 12, output/6 = 2.0 => "+2.0 EV"
    std::string result = callPrintFlash(244, false);
    EXPECT_NE(result.find("+2.0"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationAutoTest_458, Value130_Plus21_0EV_458) {
    // value=130 => output = 256-130 = 126, output/6 = 21.0 => "+21.0 EV"
    std::string result = callPrintFlash(130, false);
    EXPECT_NE(result.find("+21.0"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

// =============================================================================
// Tests verifying stream state is preserved
// =============================================================================

class PrintFlashCompensationStreamTest_458 : public ::testing::Test {};

TEST_F(PrintFlashCompensationStreamTest_458, StreamFlagsPreservedManual_458) {
    std::ostringstream os;
    auto flags_before = os.flags();
    printFlashCompensationValue(os, 6, true);
    auto flags_after = os.flags();
    EXPECT_EQ(flags_before, flags_after);
}

TEST_F(PrintFlashCompensationStreamTest_458, StreamFlagsPreservedAuto_458) {
    std::ostringstream os;
    auto flags_before = os.flags();
    printFlashCompensationValue(os, 0, false);
    auto flags_after = os.flags();
    EXPECT_EQ(flags_before, flags_after);
}

TEST_F(PrintFlashCompensationStreamTest_458, StreamFlagsPreservedOutOfRange_458) {
    std::ostringstream os;
    auto flags_before = os.flags();
    printFlashCompensationValue(os, 100, true);
    auto flags_after = os.flags();
    EXPECT_EQ(flags_before, flags_after);
}

TEST_F(PrintFlashCompensationStreamTest_458, ReturnsSameStream_458) {
    std::ostringstream os;
    auto& returned = printFlashCompensationValue(os, 0, true);
    EXPECT_EQ(&returned, &os);
}

TEST_F(PrintFlashCompensationStreamTest_458, ReturnsSameStreamAuto_458) {
    std::ostringstream os;
    auto& returned = printFlashCompensationValue(os, 128, false);
    EXPECT_EQ(&returned, &os);
}

// =============================================================================
// Boundary tests for manual scale
// =============================================================================

class PrintFlashCompensationBoundaryTest_458 : public ::testing::Test {};

TEST_F(PrintFlashCompensationBoundaryTest_458, ManualBoundaryValue47_458) {
    // value=47 => temp = (47-5)/6 = 7, 2^7 = 128, mod=5 => "1/128 (-5/6 EV)"
    std::string result = callPrintFlash(47, true);
    EXPECT_NE(result.find("1/128"), std::string::npos);
    EXPECT_NE(result.find("5/6 EV)"), std::string::npos);
}

TEST_F(PrintFlashCompensationBoundaryTest_458, ManualBoundaryValue48_458) {
    // value=48 => last valid value, "1/256"
    std::string result = callPrintFlash(48, true);
    EXPECT_NE(result.find("1/256"), std::string::npos);
    EXPECT_EQ(result.find("(-"), std::string::npos);
}

TEST_F(PrintFlashCompensationBoundaryTest_458, ManualBoundaryValue49_458) {
    // value=49 => first invalid value
    std::string result = callPrintFlash(49, true);
    EXPECT_EQ(result, "(49)");
}

TEST_F(PrintFlashCompensationBoundaryTest_458, AutoValue4_Minus0_7EV_458) {
    // value=4 => output = -4.0, output/6 = -0.666... => "-0.7 EV"
    std::string result = callPrintFlash(4, false);
    EXPECT_NE(result.find("-0.7"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationBoundaryTest_458, AutoValue5_Minus0_8EV_458) {
    // value=5 => output = -5.0, output/6 = -0.833... => "-0.8 EV"
    std::string result = callPrintFlash(5, false);
    EXPECT_NE(result.find("-0.8"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationBoundaryTest_458, AutoValue254_Plus0_3EV_458) {
    // value=254 => output = 256-254 = 2, output/6 = 0.333... => "+0.3 EV"
    std::string result = callPrintFlash(254, false);
    EXPECT_NE(result.find("+0.3"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}

TEST_F(PrintFlashCompensationBoundaryTest_458, AutoValue253_Plus0_5EV_458) {
    // value=253 => output = 256-253 = 3, output/6 = 0.5 => "+0.5 EV"
    std::string result = callPrintFlash(253, false);
    EXPECT_NE(result.find("+0.5"), std::string::npos);
    EXPECT_NE(result.find("EV"), std::string::npos);
}
