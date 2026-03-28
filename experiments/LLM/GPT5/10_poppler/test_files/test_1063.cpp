#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/OutputDev.h"

class OutputDevTest_1063 : public ::testing::Test {
protected:
    OutputDev outputDev;
};

// Test the normal behavior of `needClipToCropBox` which is expected to return `false`
TEST_F(OutputDevTest_1063, NeedClipToCropBox_ReturnsFalse_1063) {
    EXPECT_FALSE(outputDev.needClipToCropBox());
}

// Test boundary condition for any other method returning boolean, e.g., `upsideDown`
TEST_F(OutputDevTest_1063, UpsideDown_ReturnsFalse_1063) {
    EXPECT_FALSE(outputDev.upsideDown());
}

// Test exceptional case if method parameters (in this case, none) cause any issues
TEST_F(OutputDevTest_1063, SetDisplayProfile_ThrowsException_WhenNullProfile_1063) {
    EXPECT_THROW(outputDev.setDisplayProfile(nullptr), std::invalid_argument);
}

// Test external interaction (for example, setting and getting the display profile)
TEST_F(OutputDevTest_1063, SetAndGetDisplayProfile_1063) {
    GfxLCMSProfilePtr profile = std::make_shared<GfxLCMSProfile>();  // Mock or instantiate accordingly
    outputDev.setDisplayProfile(profile);
    EXPECT_EQ(outputDev.getDisplayProfile(), profile);
}

// Test boundary condition for the function that doesn't take any input but returns boolean (e.g., `useDrawChar`)
TEST_F(OutputDevTest_1063, UseDrawChar_ReturnsFalse_1063) {
    EXPECT_FALSE(outputDev.useDrawChar());
}

// Test boundary condition when profileHash is queried but not initialized
TEST_F(OutputDevTest_1063, GetProfileHash_ReturnsNull_1063) {
    EXPECT_EQ(outputDev.getProfileHash(), nullptr);
}

// Test interaction with a non-null profile setting and retrieving default profiles
TEST_F(OutputDevTest_1063, SetAndGetDefaultProfiles_1063) {
    GfxLCMSProfilePtr profile = std::make_shared<GfxLCMSProfile>();  // Mock or instantiate accordingly
    outputDev.setDefaultGrayProfile(profile);
    EXPECT_EQ(outputDev.getDefaultGrayProfile(), profile);

    outputDev.setDefaultRGBProfile(profile);
    EXPECT_EQ(outputDev.getDefaultRGBProfile(), profile);

    outputDev.setDefaultCMYKProfile(profile);
    EXPECT_EQ(outputDev.getDefaultCMYKProfile(), profile);
}

// Test boundary condition on a method with specific return value (e.g., `getVectorAntialias`)
TEST_F(OutputDevTest_1063, GetVectorAntialias_ReturnsFalse_1063) {
    EXPECT_FALSE(outputDev.getVectorAntialias());
}

// Test for edge case for function with complex inputs, such as a method dealing with matrix operations
TEST_F(OutputDevTest_1063, SetDefaultCTM_Success_1063) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};  // Identity matrix example
    outputDev.setDefaultCTM(ctm);
    // No direct output from this, so test if this does not result in an error or unexpected behavior
}

// Test interaction with an uninitialized profile (should return empty or invalid behavior)
TEST_F(OutputDevTest_1063, GetDisplayProfile_EmptyProfile_1063) {
    EXPECT_EQ(outputDev.getDisplayProfile(), nullptr);
}

// Test boundary condition with `beginType3Char` to ensure no errors are thrown on boundary input
TEST_F(OutputDevTest_1063, BeginType3Char_WithBoundaryInput_1063) {
    GfxState state;
    EXPECT_NO_THROW(outputDev.beginType3Char(&state, 0, 0, 0, 0, 0, nullptr, 0));
}

// Verify that the default behavior for `needClipToCropBox` remains as expected
TEST_F(OutputDevTest_1063, NeedClipToCropBox_DefaultBehavior_1063) {
    EXPECT_FALSE(outputDev.needClipToCropBox());
}