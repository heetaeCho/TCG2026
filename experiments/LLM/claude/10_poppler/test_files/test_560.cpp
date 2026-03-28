#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

class GfxXYZ2DisplayTransformsTest_560 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test constructing with a null/empty display profile
TEST_F(GfxXYZ2DisplayTransformsTest_560, ConstructWithNullProfile_560) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);
    
    // With a null profile, transforms should likely be null
    EXPECT_EQ(transforms.getDisplayProfile(), nullptr);
    EXPECT_EQ(transforms.getAbsCol(), nullptr);
    EXPECT_EQ(transforms.getRelCol(), nullptr);
    EXPECT_EQ(transforms.getSat(), nullptr);
    EXPECT_EQ(transforms.getPerc(), nullptr);
}

// Test that getDisplayProfile returns the profile passed in construction
TEST_F(GfxXYZ2DisplayTransformsTest_560, GetDisplayProfileReturnsConstructedProfile_560) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);
    
    auto retrievedProfile = transforms.getDisplayProfile();
    // Should match what was passed in
    EXPECT_EQ(retrievedProfile, nullProfile);
}

// Test that getAbsCol returns a shared_ptr (possibly null with no valid profile)
TEST_F(GfxXYZ2DisplayTransformsTest_560, GetAbsColReturnsSharedPtr_560) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);
    
    std::shared_ptr<GfxColorTransform> absCol = transforms.getAbsCol();
    // With null profile, expect null transform
    EXPECT_EQ(absCol, nullptr);
}

// Test that getRelCol returns a shared_ptr (possibly null with no valid profile)
TEST_F(GfxXYZ2DisplayTransformsTest_560, GetRelColReturnsSharedPtr_560) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);
    
    std::shared_ptr<GfxColorTransform> relCol = transforms.getRelCol();
    EXPECT_EQ(relCol, nullptr);
}

// Test that getSat returns a shared_ptr (possibly null with no valid profile)
TEST_F(GfxXYZ2DisplayTransformsTest_560, GetSatReturnsSharedPtr_560) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);
    
    std::shared_ptr<GfxColorTransform> sat = transforms.getSat();
    EXPECT_EQ(sat, nullptr);
}

// Test that getPerc returns a shared_ptr (possibly null with no valid profile)
TEST_F(GfxXYZ2DisplayTransformsTest_560, GetPercReturnsSharedPtr_560) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);
    
    std::shared_ptr<GfxColorTransform> perc = transforms.getPerc();
    EXPECT_EQ(perc, nullptr);
}

// Test that all getters are consistent across multiple calls (no side effects)
TEST_F(GfxXYZ2DisplayTransformsTest_560, GettersAreConsistentAcrossMultipleCalls_560) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);
    
    auto absCol1 = transforms.getAbsCol();
    auto absCol2 = transforms.getAbsCol();
    EXPECT_EQ(absCol1, absCol2);
    
    auto relCol1 = transforms.getRelCol();
    auto relCol2 = transforms.getRelCol();
    EXPECT_EQ(relCol1, relCol2);
    
    auto sat1 = transforms.getSat();
    auto sat2 = transforms.getSat();
    EXPECT_EQ(sat1, sat2);
    
    auto perc1 = transforms.getPerc();
    auto perc2 = transforms.getPerc();
    EXPECT_EQ(perc1, perc2);
    
    auto profile1 = transforms.getDisplayProfile();
    auto profile2 = transforms.getDisplayProfile();
    EXPECT_EQ(profile1, profile2);
}

// Test constructing with a valid sRGB display profile if available
#ifdef USE_CMS
TEST_F(GfxXYZ2DisplayTransformsTest_560, ConstructWithValidProfile_560) {
    // Create an sRGB profile using LCMS
    cmsHPROFILE srgbHandle = cmsCreate_sRGBProfile();
    ASSERT_NE(srgbHandle, nullptr);
    
    GfxLCMSProfilePtr srgbProfile = make_GfxLCMSProfilePtr(srgbHandle);
    ASSERT_NE(srgbProfile, nullptr);
    
    GfxXYZ2DisplayTransforms transforms(srgbProfile);
    
    // With a valid profile, the display profile getter should return non-null
    EXPECT_NE(transforms.getDisplayProfile(), nullptr);
    
    // The transforms should be created for a valid display profile
    // These may or may not be null depending on implementation, but we test they don't crash
    auto absCol = transforms.getAbsCol();
    auto relCol = transforms.getRelCol();
    auto sat = transforms.getSat();
    auto perc = transforms.getPerc();
    
    // With a valid sRGB profile, we expect transforms to be created
    EXPECT_NE(absCol, nullptr);
    EXPECT_NE(relCol, nullptr);
    EXPECT_NE(sat, nullptr);
    EXPECT_NE(perc, nullptr);
}

// Test that different rendering intent transforms are distinct objects
TEST_F(GfxXYZ2DisplayTransformsTest_560, DifferentIntentsReturnDifferentTransforms_560) {
    cmsHPROFILE srgbHandle = cmsCreate_sRGBProfile();
    ASSERT_NE(srgbHandle, nullptr);
    
    GfxLCMSProfilePtr srgbProfile = make_GfxLCMSProfilePtr(srgbHandle);
    GfxXYZ2DisplayTransforms transforms(srgbProfile);
    
    auto absCol = transforms.getAbsCol();
    auto relCol = transforms.getRelCol();
    auto sat = transforms.getSat();
    auto perc = transforms.getPerc();
    
    // Different rendering intents should produce different transform objects
    if (absCol && relCol) {
        EXPECT_NE(absCol.get(), relCol.get());
    }
    if (absCol && sat) {
        EXPECT_NE(absCol.get(), sat.get());
    }
    if (absCol && perc) {
        EXPECT_NE(absCol.get(), perc.get());
    }
}
#endif
