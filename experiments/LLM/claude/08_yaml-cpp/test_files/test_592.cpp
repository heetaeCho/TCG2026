#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "yaml-cpp/node/convert.h"

// Test fixture for IsNaN tests
class IsNaNTest_592 : public ::testing::Test {
protected:
    // No setup needed
};

// Normal operation tests

TEST_F(IsNaNTest_592, LowercaseNan_592) {
    EXPECT_TRUE(YAML::conversion::IsNaN(".nan"));
}

TEST_F(IsNaNTest_592, MixedCaseNaN_592) {
    EXPECT_TRUE(YAML::conversion::IsNaN(".NaN"));
}

TEST_F(IsNaNTest_592, UppercaseNAN_592) {
    EXPECT_TRUE(YAML::conversion::IsNaN(".NAN"));
}

// Boundary / edge cases

TEST_F(IsNaNTest_592, EmptyString_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(""));
}

TEST_F(IsNaNTest_592, JustDot_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN("."));
}

TEST_F(IsNaNTest_592, NanWithoutDot_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN("nan"));
}

TEST_F(IsNaNTest_592, NANWithoutDot_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN("NAN"));
}

TEST_F(IsNaNTest_592, NaNWithoutDot_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN("NaN"));
}

TEST_F(IsNaNTest_592, LeadingSpace_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(" .nan"));
}

TEST_F(IsNaNTest_592, TrailingSpace_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(".nan "));
}

TEST_F(IsNaNTest_592, LeadingAndTrailingSpaces_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(" .nan "));
}

TEST_F(IsNaNTest_592, DotNanUpperN_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(".Nan"));
}

TEST_F(IsNaNTest_592, DotNAn_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(".NAn"));
}

TEST_F(IsNaNTest_592, DotNAn_MixedCase2_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(".nAn"));
}

TEST_F(IsNaNTest_592, DotNaN_MixedCase3_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(".naN"));
}

TEST_F(IsNaNTest_592, DotNAN_MixedCase4_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(".nAN"));
}

TEST_F(IsNaNTest_592, DotNaN_ExtraChars_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(".nanx"));
}

TEST_F(IsNaNTest_592, DotNaN_Prefix_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN("x.nan"));
}

TEST_F(IsNaNTest_592, NumberString_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN("123"));
}

TEST_F(IsNaNTest_592, InfString_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(".inf"));
}

TEST_F(IsNaNTest_592, RandomString_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN("hello"));
}

TEST_F(IsNaNTest_592, NullCharString_592) {
    std::string nullStr("\0", 1);
    EXPECT_FALSE(YAML::conversion::IsNaN(nullStr));
}

TEST_F(IsNaNTest_592, DotNanWithNullAppended_592) {
    std::string s = ".nan";
    s.push_back('\0');
    EXPECT_FALSE(YAML::conversion::IsNaN(s));
}

TEST_F(IsNaNTest_592, CaseSensitivity_AllLowerExceptFirst_592) {
    // .nAn is not one of the three accepted forms
    EXPECT_FALSE(YAML::conversion::IsNaN(".nAn"));
}

TEST_F(IsNaNTest_592, DoubleDotNan_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN("..nan"));
}

TEST_F(IsNaNTest_592, SingleCharN_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN("n"));
}

TEST_F(IsNaNTest_592, DotOnly_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(".n"));
}

TEST_F(IsNaNTest_592, DotNa_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(".na"));
}

TEST_F(IsNaNTest_592, DotNA_592) {
    EXPECT_FALSE(YAML::conversion::IsNaN(".NA"));
}
