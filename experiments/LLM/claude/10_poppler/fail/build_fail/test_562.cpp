#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

class GfxXYZ2DisplayTransformsTest_562 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that constructing with a null/empty display profile doesn't crash
// and that getters return expected values (likely nullptr for transforms)
TEST_F(GfxXYZ2DisplayTransformsTest_562, ConstructWithNullProfile_562) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    // With a null profile, we expect the display profile to be null
    EXPECT_EQ(transforms.getDisplayProfile(), nullptr);
}

TEST_F(GfxXYZ2DisplayTransformsTest_562, GetPercReturnsSharedPtr_562) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    std::shared_ptr<GfxColorTransform> perc = transforms.getPerc();
    // With null profile, the perceptual transform should be null
    EXPECT_EQ(perc, nullptr);
}

TEST_F(GfxXYZ2DisplayTransformsTest_562, GetRelColReturnsSharedPtr_562) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    std::shared_ptr<GfxColorTransform> relCol = transforms.getRelCol();
    EXPECT_EQ(relCol, nullptr);
}

TEST_F(GfxXYZ2DisplayTransformsTest_562, GetAbsColReturnsSharedPtr_562) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    std::shared_ptr<GfxColorTransform> absCol = transforms.getAbsCol();
    EXPECT_EQ(absCol, nullptr);
}

TEST_F(GfxXYZ2DisplayTransformsTest_562, GetSatReturnsSharedPtr_562) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    std::shared_ptr<GfxColorTransform> sat = transforms.getSat();
    EXPECT_EQ(sat, nullptr);
}

TEST_F(GfxXYZ2DisplayTransformsTest_562, GetDisplayProfileReturnsNullForNullInput_562) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    GfxLCMSProfilePtr profile = transforms.getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test that all getters are consistent when called multiple times
TEST_F(GfxXYZ2DisplayTransformsTest_562, GettersAreConsistent_562) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);

    auto perc1 = transforms.getPerc();
    auto perc2 = transforms.getPerc();
    EXPECT_EQ(perc1, perc2);

    auto relCol1 = transforms.getRelCol();
    auto relCol2 = transforms.getRelCol();
    EXPECT_EQ(relCol1, relCol2);

    auto absCol1 = transforms.getAbsCol();
    auto absCol2 = transforms.getAbsCol();
    EXPECT_EQ(absCol1, absCol2);

    auto sat1 = transforms.getSat();
    auto sat2 = transforms.getSat();
    EXPECT_EQ(sat1, sat2);

    auto dp1 = transforms.getDisplayProfile();
    auto dp2 = transforms.getDisplayProfile();
    EXPECT_EQ(dp1, dp2);
}

// Test with a valid sRGB display profile if LCMS is available
#ifdef USE_CMS
TEST_F(GfxXYZ2DisplayTransformsTest_562, ConstructWithValidProfile_562) {
    // Create an sRGB profile using LCMS
    cmsHPROFILE srgbHandle = cmsCreate_sRGBProfile();
    ASSERT_NE(srgbHandle, nullptr);

    GfxLCMSProfilePtr srgbProfile = make_GfxLCMSProfilePtr(srgbHandle);
    ASSERT_NE(srgbProfile, nullptr);

    GfxXYZ2DisplayTransforms transforms(srgbProfile);

    // With a valid profile, the display profile should not be null
    EXPECT_NE(transforms.getDisplayProfile(), nullptr);

    // With a valid display profile, the transforms should be created
    EXPECT_NE(transforms.getPerc(), nullptr);
    EXPECT_NE(transforms.getRelCol(), nullptr);
    EXPECT_NE(transforms.getAbsCol(), nullptr);
    EXPECT_NE(transforms.getSat(), nullptr);
}

TEST_F(GfxXYZ2DisplayTransformsTest_562, TransformsAreDifferentRenderingIntents_562) {
    cmsHPROFILE srgbHandle = cmsCreate_sRGBProfile();
    ASSERT_NE(srgbHandle, nullptr);

    GfxLCMSProfilePtr srgbProfile = make_GfxLCMSProfilePtr(srgbHandle);
    GfxXYZ2DisplayTransforms transforms(srgbProfile);

    auto perc = transforms.getPerc();
    auto relCol = transforms.getRelCol();
    auto absCol = transforms.getAbsCol();
    auto sat = transforms.getSat();

    // All should be non-null
    EXPECT_NE(perc, nullptr);
    EXPECT_NE(relCol, nullptr);
    EXPECT_NE(absCol, nullptr);
    EXPECT_NE(sat, nullptr);

    // They represent different rendering intents, so they should be distinct objects
    // (though some might potentially share if implementation optimizes, we just verify they exist)
}

TEST_F(GfxXYZ2DisplayTransformsTest_562, DisplayProfileMatchesInput_562) {
    cmsHPROFILE srgbHandle = cmsCreate_sRGBProfile();
    ASSERT_NE(srgbHandle, nullptr);

    GfxLCMSProfilePtr srgbProfile = make_GfxLCMSProfilePtr(srgbHandle);
    GfxXYZ2DisplayTransforms transforms(srgbProfile);

    // The returned display profile should be the same as the one we passed in
    EXPECT_EQ(transforms.getDisplayProfile(), srgbProfile);
}
#endif // USE_CMS
