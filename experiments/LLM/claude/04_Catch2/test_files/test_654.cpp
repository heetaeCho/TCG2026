#include <gtest/gtest.h>
#include <string>

// Include the necessary headers from Catch2's Clara implementation
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;
using namespace Catch::Clara;

class ConvertIntoBoolTest_654 : public ::testing::Test {
protected:
    bool target = false;
};

// ==================== True values ====================

TEST_F(ConvertIntoBoolTest_654, ConvertY_ReturnsTrue_654) {
    auto result = convertInto(std::string("y"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertUpperY_ReturnsTrue_654) {
    auto result = convertInto(std::string("Y"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(target);
}

TEST_F(ConvertIntoBoolTest_654, Convert1_ReturnsTrue_654) {
    auto result = convertInto(std::string("1"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertTrue_ReturnsTrue_654) {
    auto result = convertInto(std::string("true"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertTrueUpperCase_ReturnsTrue_654) {
    auto result = convertInto(std::string("TRUE"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertTrueMixedCase_ReturnsTrue_654) {
    auto result = convertInto(std::string("True"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertYes_ReturnsTrue_654) {
    auto result = convertInto(std::string("yes"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertYesUpperCase_ReturnsTrue_654) {
    auto result = convertInto(std::string("YES"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertOn_ReturnsTrue_654) {
    auto result = convertInto(std::string("on"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertOnUpperCase_ReturnsTrue_654) {
    auto result = convertInto(std::string("ON"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(target);
}

// ==================== False values ====================

TEST_F(ConvertIntoBoolTest_654, ConvertN_ReturnsFalse_654) {
    target = true; // Set to true first to verify it changes
    auto result = convertInto(std::string("n"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertUpperN_ReturnsFalse_654) {
    target = true;
    auto result = convertInto(std::string("N"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(target);
}

TEST_F(ConvertIntoBoolTest_654, Convert0_ReturnsFalse_654) {
    target = true;
    auto result = convertInto(std::string("0"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertFalse_ReturnsFalse_654) {
    target = true;
    auto result = convertInto(std::string("false"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertFalseUpperCase_ReturnsFalse_654) {
    target = true;
    auto result = convertInto(std::string("FALSE"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertFalseMixedCase_ReturnsFalse_654) {
    target = true;
    auto result = convertInto(std::string("False"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertNo_ReturnsFalse_654) {
    target = true;
    auto result = convertInto(std::string("no"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertNoUpperCase_ReturnsFalse_654) {
    target = true;
    auto result = convertInto(std::string("NO"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertOff_ReturnsFalse_654) {
    target = true;
    auto result = convertInto(std::string("off"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertOffUpperCase_ReturnsFalse_654) {
    target = true;
    auto result = convertInto(std::string("OFF"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(target);
}

// ==================== Error / Invalid values ====================

TEST_F(ConvertIntoBoolTest_654, InvalidString_ReturnsError_654) {
    auto result = convertInto(std::string("invalid"), target);
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(ConvertIntoBoolTest_654, EmptyString_ReturnsError_654) {
    auto result = convertInto(std::string(""), target);
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(ConvertIntoBoolTest_654, RandomText_ReturnsError_654) {
    auto result = convertInto(std::string("maybe"), target);
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(ConvertIntoBoolTest_654, NumericNonBool_ReturnsError_654) {
    auto result = convertInto(std::string("2"), target);
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(ConvertIntoBoolTest_654, WhitespaceString_ReturnsError_654) {
    auto result = convertInto(std::string(" "), target);
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(ConvertIntoBoolTest_654, TrueWithSpaces_ReturnsError_654) {
    auto result = convertInto(std::string(" true "), target);
    EXPECT_FALSE(static_cast<bool>(result));
}

TEST_F(ConvertIntoBoolTest_654, ErrorMessageContainsInput_654) {
    std::string input = "foobar";
    auto result = convertInto(input, target);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_NE(result.errorMessage().find(input), std::string::npos);
}

// ==================== Result type verification ====================

TEST_F(ConvertIntoBoolTest_654, SuccessResultTypeIsMatched_654) {
    auto result = convertInto(std::string("true"), target);
    EXPECT_EQ(result.type(), ResultBase::Ok);
}

TEST_F(ConvertIntoBoolTest_654, ErrorResultTypeIsRuntimeError_654) {
    auto result = convertInto(std::string("garbage"), target);
    EXPECT_FALSE(static_cast<bool>(result));
}

// ==================== Target not modified on error ====================

TEST_F(ConvertIntoBoolTest_654, TargetUnchangedOnError_WhenInitiallyFalse_654) {
    target = false;
    auto result = convertInto(std::string("invalid"), target);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_FALSE(target); // target should remain unchanged
}

TEST_F(ConvertIntoBoolTest_654, TargetUnchangedOnError_WhenInitiallyTrue_654) {
    target = true;
    auto result = convertInto(std::string("invalid"), target);
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_TRUE(target); // target should remain unchanged
}

// ==================== Negative number string ====================

TEST_F(ConvertIntoBoolTest_654, NegativeNumber_ReturnsError_654) {
    auto result = convertInto(std::string("-1"), target);
    EXPECT_FALSE(static_cast<bool>(result));
}

// ==================== Case insensitivity edge cases ====================

TEST_F(ConvertIntoBoolTest_654, ConvertOnMixedCase_ReturnsTrue_654) {
    auto result = convertInto(std::string("On"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertOffMixedCase_ReturnsFalse_654) {
    target = true;
    auto result = convertInto(std::string("Off"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertYesMixedCase_ReturnsTrue_654) {
    auto result = convertInto(std::string("yEs"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(target);
}

TEST_F(ConvertIntoBoolTest_654, ConvertNoMixedCase_ReturnsFalse_654) {
    target = true;
    auto result = convertInto(std::string("No"), target);
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(target);
}
