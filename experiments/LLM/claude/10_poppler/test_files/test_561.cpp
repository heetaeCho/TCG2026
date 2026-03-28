#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

// Test fixture for GfxXYZ2DisplayTransforms
class GfxXYZ2DisplayTransformsTest_561 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that constructing with a null/empty display profile doesn't crash
// and getters return expected values (possibly null shared_ptrs)
TEST_F(GfxXYZ2DisplayTransformsTest_561, ConstructWithNullProfile_561) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    // With a null profile, transforms should likely be null
    EXPECT_EQ(transforms.getDisplayProfile(), nullptr);
    EXPECT_EQ(transforms.getSat(), nullptr);
    EXPECT_EQ(transforms.getRelCol(), nullptr);
    EXPECT_EQ(transforms.getAbsCol(), nullptr);
    EXPECT_EQ(transforms.getPerc(), nullptr);
}

// Test that getSat returns a shared_ptr (null or not depending on profile)
TEST_F(GfxXYZ2DisplayTransformsTest_561, GetSatReturnsSharedPtr_561) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    std::shared_ptr<GfxColorTransform> sat = transforms.getSat();
    // With null profile, we expect nullptr
    EXPECT_FALSE(sat);
}

// Test that getRelCol returns a shared_ptr
TEST_F(GfxXYZ2DisplayTransformsTest_561, GetRelColReturnsSharedPtr_561) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    std::shared_ptr<GfxColorTransform> relCol = transforms.getRelCol();
    EXPECT_FALSE(relCol);
}

// Test that getAbsCol returns a shared_ptr
TEST_F(GfxXYZ2DisplayTransformsTest_561, GetAbsColReturnsSharedPtr_561) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    std::shared_ptr<GfxColorTransform> absCol = transforms.getAbsCol();
    EXPECT_FALSE(absCol);
}

// Test that getPerc returns a shared_ptr
TEST_F(GfxXYZ2DisplayTransformsTest_561, GetPercReturnsSharedPtr_561) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    std::shared_ptr<GfxColorTransform> perc = transforms.getPerc();
    EXPECT_FALSE(perc);
}

// Test that getDisplayProfile returns the profile that was passed in
TEST_F(GfxXYZ2DisplayTransformsTest_561, GetDisplayProfileReturnsPassedProfile_561) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    GfxLCMSProfilePtr retrieved = transforms.getDisplayProfile();
    EXPECT_EQ(retrieved, nullProfile);
}

// Test consistency: calling getters multiple times returns the same result
TEST_F(GfxXYZ2DisplayTransformsTest_561, GettersAreConsistent_561) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    auto sat1 = transforms.getSat();
    auto sat2 = transforms.getSat();
    EXPECT_EQ(sat1, sat2);

    auto relCol1 = transforms.getRelCol();
    auto relCol2 = transforms.getRelCol();
    EXPECT_EQ(relCol1, relCol2);

    auto absCol1 = transforms.getAbsCol();
    auto absCol2 = transforms.getAbsCol();
    EXPECT_EQ(absCol1, absCol2);

    auto perc1 = transforms.getPerc();
    auto perc2 = transforms.getPerc();
    EXPECT_EQ(perc1, perc2);
}

#ifdef USE_CMS
// Test with a valid sRGB display profile if CMS is available
TEST_F(GfxXYZ2DisplayTransformsTest_561, ConstructWithValidProfile_561) {
    // Create an sRGB profile using LCMS
    cmsHPROFILE srgbHandle = cmsCreate_sRGBProfile();
    ASSERT_NE(srgbHandle, nullptr);

    GfxLCMSProfilePtr srgbProfile = make_GfxLCMSProfilePtr(srgbHandle);
    ASSERT_NE(srgbProfile, nullptr);

    GfxXYZ2DisplayTransforms transforms(srgbProfile);

    // With a valid profile, we expect the display profile to be set
    EXPECT_NE(transforms.getDisplayProfile(), nullptr);

    // With a valid display profile, transforms should be created
    EXPECT_NE(transforms.getSat(), nullptr);
    EXPECT_NE(transforms.getRelCol(), nullptr);
    EXPECT_NE(transforms.getAbsCol(), nullptr);
    EXPECT_NE(transforms.getPerc(), nullptr);
}

// Test that different rendering intents produce different (or at least valid) transforms
TEST_F(GfxXYZ2DisplayTransformsTest_561, DifferentIntentsProduceDifferentTransforms_561) {
    cmsHPROFILE srgbHandle = cmsCreate_sRGBProfile();
    ASSERT_NE(srgbHandle, nullptr);

    GfxLCMSProfilePtr srgbProfile = make_GfxLCMSProfilePtr(srgbHandle);
    GfxXYZ2DisplayTransforms transforms(srgbProfile);

    auto sat = transforms.getSat();
    auto relCol = transforms.getRelCol();
    auto absCol = transforms.getAbsCol();
    auto perc = transforms.getPerc();

    // All should be non-null with a valid profile
    EXPECT_NE(sat, nullptr);
    EXPECT_NE(relCol, nullptr);
    EXPECT_NE(absCol, nullptr);
    EXPECT_NE(perc, nullptr);

    // They represent different rendering intents, so they should generally
    // be different transform objects
    // (Though some may coincidentally be equal, we just verify they exist)
}
#endif // USE_CMS
