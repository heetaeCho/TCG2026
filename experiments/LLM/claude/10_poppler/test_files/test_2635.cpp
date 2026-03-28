#include <gtest/gtest.h>
#include <lcms2.h>
#include <memory>
#include <cstdio>
#include <cstring>

// Include the header that declares checkICCProfile and GfxLCMSProfilePtr
#include "sanitychecks.h"

// If GfxLCMSProfilePtr is not directly available, we may need GfxState.h
// Adjust includes as needed based on the actual project structure
#include "GfxState.h"

class CheckICCProfileTest_2635 : public ::testing::Test {
protected:
    // Helper to create a GfxLCMSProfilePtr wrapping an sRGB profile
    GfxLCMSProfilePtr createSRGBProfile() {
        cmsHPROFILE h = cmsCreate_sRGBProfile();
        return make_GfxLCMSProfilePtr(h);
    }

    // Helper to create a Gray profile
    GfxLCMSProfilePtr createGrayProfile() {
        cmsToneCurve *curve = cmsBuildGamma(nullptr, 2.2);
        cmsHPROFILE h = cmsCreateGrayProfile(cmsD50_xyY(), curve);
        cmsFreeToneCurve(curve);
        return make_GfxLCMSProfilePtr(h);
    }

    // Helper to create a Lab profile (not RGB, not CMYK, not Gray in the usual sense)
    GfxLCMSProfilePtr createLabProfile() {
        cmsHPROFILE h = cmsCreateLab4Profile(nullptr);
        return make_GfxLCMSProfilePtr(h);
    }

    // Helper to create a CMYK profile (using a simple transform-based approach)
    GfxLCMSProfilePtr createCMYKProfile() {
        // Create a minimal CMYK profile
        // We use cmsCreateInkLimitingDeviceLink which creates a CMYK->CMYK devicelink
        // Instead, let's create a null profile or use a built-in approach
        // A simple approach: create a profile from scratch
        cmsHPROFILE h = cmsCreateNULLProfile();
        // NULL profile won't be CMYK, so let's try another approach
        cmsCloseProfile(h);

        // Create a CMYK ICC profile by using the LCMS2 API
        // Use ink-limiting device link as a CMYK-ish profile
        cmsHPROFILE cmyk = cmsCreateInkLimitingDeviceLink(cmsSigCmykData, 300.0);
        return make_GfxLCMSProfilePtr(cmyk);
    }
};

// Test: null profile returns false
TEST_F(CheckICCProfileTest_2635, NullProfileReturnsFalse_2635) {
    GfxLCMSProfilePtr nullProfile;
    bool result = checkICCProfile(nullProfile, "nonexistent.icc", LCMS_USED_AS_OUTPUT, cmsSigRgbData);
    EXPECT_FALSE(result);
}

// Test: valid sRGB profile with expected RGB color space and output direction
TEST_F(CheckICCProfileTest_2635, ValidSRGBAsOutputReturnsTrue_2635) {
    auto profile = createSRGBProfile();
    ASSERT_NE(profile, nullptr);
    bool result = checkICCProfile(profile, "sRGB.icc", LCMS_USED_AS_OUTPUT, cmsSigRgbData);
    EXPECT_TRUE(result);
}

// Test: valid sRGB profile with expected RGB color space and input direction
TEST_F(CheckICCProfileTest_2635, ValidSRGBAsInputReturnsTrue_2635) {
    auto profile = createSRGBProfile();
    ASSERT_NE(profile, nullptr);
    bool result = checkICCProfile(profile, "sRGB.icc", LCMS_USED_AS_INPUT, cmsSigRgbData);
    EXPECT_TRUE(result);
}

// Test: sRGB profile but expecting CMYK color space returns false
TEST_F(CheckICCProfileTest_2635, SRGBProfileExpectingCMYKReturnsFalse_2635) {
    auto profile = createSRGBProfile();
    ASSERT_NE(profile, nullptr);
    bool result = checkICCProfile(profile, "sRGB.icc", LCMS_USED_AS_OUTPUT, cmsSigCmykData);
    EXPECT_FALSE(result);
}

// Test: sRGB profile but expecting Gray color space returns false
TEST_F(CheckICCProfileTest_2635, SRGBProfileExpectingGrayReturnsFalse_2635) {
    auto profile = createSRGBProfile();
    ASSERT_NE(profile, nullptr);
    bool result = checkICCProfile(profile, "sRGB.icc", LCMS_USED_AS_OUTPUT, cmsSigGrayData);
    EXPECT_FALSE(result);
}

// Test: Gray profile with expected gray color space
TEST_F(CheckICCProfileTest_2635, GrayProfileExpectingGrayReturnsTrue_2635) {
    auto profile = createGrayProfile();
    ASSERT_NE(profile, nullptr);
    bool result = checkICCProfile(profile, "gray.icc", LCMS_USED_AS_INPUT, cmsSigGrayData);
    EXPECT_TRUE(result);
}

// Test: Gray profile but expecting RGB color space returns false
TEST_F(CheckICCProfileTest_2635, GrayProfileExpectingRGBReturnsFalse_2635) {
    auto profile = createGrayProfile();
    ASSERT_NE(profile, nullptr);
    bool result = checkICCProfile(profile, "gray.icc", LCMS_USED_AS_INPUT, cmsSigRgbData);
    EXPECT_FALSE(result);
}

// Test: Lab profile expecting RGB returns false (color space mismatch)
TEST_F(CheckICCProfileTest_2635, LabProfileExpectingRGBReturnsFalse_2635) {
    auto profile = createLabProfile();
    ASSERT_NE(profile, nullptr);
    bool result = checkICCProfile(profile, "lab.icc", LCMS_USED_AS_OUTPUT, cmsSigRgbData);
    EXPECT_FALSE(result);
}

// Test: CMYK device link profile (if it has the expected color space)
TEST_F(CheckICCProfileTest_2635, CMYKProfileExpectingCMYK_2635) {
    auto profile = createCMYKProfile();
    if (!profile) {
        GTEST_SKIP() << "Could not create CMYK test profile";
    }
    // The ink-limiting device link may or may not support the required intents
    // We just check it doesn't crash and returns a boolean
    bool result = checkICCProfile(profile, "cmyk.icc", LCMS_USED_AS_OUTPUT, cmsSigCmykData);
    // Result depends on intent support; at minimum, no crash
    (void)result;
}

// Test: null profile with various filenames - error message path coverage
TEST_F(CheckICCProfileTest_2635, NullProfileDifferentFilename_2635) {
    GfxLCMSProfilePtr nullProfile;
    bool result = checkICCProfile(nullProfile, "another_file.icc", LCMS_USED_AS_INPUT, cmsSigCmykData);
    EXPECT_FALSE(result);
}

// Test: Valid sRGB profile used as LCMS_USED_AS_PROOF direction
TEST_F(CheckICCProfileTest_2635, SRGBProfileAsProofDirection_2635) {
    auto profile = createSRGBProfile();
    ASSERT_NE(profile, nullptr);
    // LCMS_USED_AS_PROOF is another valid direction value
    bool result = checkICCProfile(profile, "sRGB.icc", LCMS_USED_AS_PROOF, cmsSigRgbData);
    // Result depends on whether the profile supports proof direction
    // At minimum it should not crash
    (void)result;
}

// Test: Empty filename string with null profile
TEST_F(CheckICCProfileTest_2635, EmptyFilenameNullProfile_2635) {
    GfxLCMSProfilePtr nullProfile;
    bool result = checkICCProfile(nullProfile, "", LCMS_USED_AS_OUTPUT, cmsSigRgbData);
    EXPECT_FALSE(result);
}

// Test: sRGB profile with matching color space and output direction, verify return is exactly true
TEST_F(CheckICCProfileTest_2635, SRGBOutputRGBExactTrue_2635) {
    auto profile = createSRGBProfile();
    ASSERT_NE(profile, nullptr);
    EXPECT_EQ(true, checkICCProfile(profile, "test.icc", LCMS_USED_AS_OUTPUT, cmsSigRgbData));
}

// Test: Gray profile expecting CMYK returns false
TEST_F(CheckICCProfileTest_2635, GrayProfileExpectingCMYKReturnsFalse_2635) {
    auto profile = createGrayProfile();
    ASSERT_NE(profile, nullptr);
    bool result = checkICCProfile(profile, "gray.icc", LCMS_USED_AS_INPUT, cmsSigCmykData);
    EXPECT_FALSE(result);
}
