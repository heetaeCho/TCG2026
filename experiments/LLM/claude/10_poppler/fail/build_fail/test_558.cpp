#include <gtest/gtest.h>
#include "GfxState.h"

#ifdef USE_CMS

class GfxXYZ2DisplayTransformsTest_558 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that constructing with a null/empty profile pointer handles gracefully
TEST_F(GfxXYZ2DisplayTransformsTest_558, ConstructWithNullProfile_558)
{
    GfxLCMSProfilePtr nullProfile;
    // Depending on implementation, this may or may not throw
    // We test that getDisplayProfile returns what was passed in
    try {
        GfxXYZ2DisplayTransforms transforms(nullProfile);
        GfxLCMSProfilePtr result = transforms.getDisplayProfile();
        EXPECT_EQ(result, nullProfile);
    } catch (...) {
        // Construction with null profile may throw - that's acceptable behavior
        SUCCEED();
    }
}

// Test that getDisplayProfile returns the profile passed to constructor
TEST_F(GfxXYZ2DisplayTransformsTest_558, GetDisplayProfileReturnsConstructorArg_558)
{
    // Create an sRGB profile for testing
    cmsHPROFILE rawProfile = cmsCreate_sRGBProfile();
    ASSERT_NE(rawProfile, nullptr);

    GfxLCMSProfilePtr profile = make_GfxLCMSProfilePtr(rawProfile);
    ASSERT_NE(profile, nullptr);

    GfxXYZ2DisplayTransforms transforms(profile);
    GfxLCMSProfilePtr retrieved = transforms.getDisplayProfile();

    EXPECT_EQ(retrieved, profile);
}

// Test that transforms are created (non-null) for a valid sRGB profile
TEST_F(GfxXYZ2DisplayTransformsTest_558, TransformsCreatedForValidProfile_558)
{
    cmsHPROFILE rawProfile = cmsCreate_sRGBProfile();
    ASSERT_NE(rawProfile, nullptr);

    GfxLCMSProfilePtr profile = make_GfxLCMSProfilePtr(rawProfile);
    ASSERT_NE(profile, nullptr);

    GfxXYZ2DisplayTransforms transforms(profile);

    // For a valid display profile, we expect transforms to be created
    std::shared_ptr<GfxColorTransform> relCol = transforms.getRelCol();
    std::shared_ptr<GfxColorTransform> absCol = transforms.getAbsCol();
    std::shared_ptr<GfxColorTransform> sat = transforms.getSat();
    std::shared_ptr<GfxColorTransform> perc = transforms.getPerc();

    EXPECT_NE(relCol, nullptr);
    EXPECT_NE(absCol, nullptr);
    EXPECT_NE(sat, nullptr);
    EXPECT_NE(perc, nullptr);
}

// Test that multiple calls to getters return the same cached transforms
TEST_F(GfxXYZ2DisplayTransformsTest_558, GettersReturnConsistentResults_558)
{
    cmsHPROFILE rawProfile = cmsCreate_sRGBProfile();
    ASSERT_NE(rawProfile, nullptr);

    GfxLCMSProfilePtr profile = make_GfxLCMSProfilePtr(rawProfile);
    ASSERT_NE(profile, nullptr);

    GfxXYZ2DisplayTransforms transforms(profile);

    // Call getters twice and verify they return the same pointer
    auto relCol1 = transforms.getRelCol();
    auto relCol2 = transforms.getRelCol();
    EXPECT_EQ(relCol1, relCol2);

    auto absCol1 = transforms.getAbsCol();
    auto absCol2 = transforms.getAbsCol();
    EXPECT_EQ(absCol1, absCol2);

    auto sat1 = transforms.getSat();
    auto sat2 = transforms.getSat();
    EXPECT_EQ(sat1, sat2);

    auto perc1 = transforms.getPerc();
    auto perc2 = transforms.getPerc();
    EXPECT_EQ(perc1, perc2);
}

// Test that different rendering intent transforms are distinct objects
TEST_F(GfxXYZ2DisplayTransformsTest_558, DifferentIntentsYieldDifferentTransforms_558)
{
    cmsHPROFILE rawProfile = cmsCreate_sRGBProfile();
    ASSERT_NE(rawProfile, nullptr);

    GfxLCMSProfilePtr profile = make_GfxLCMSProfilePtr(rawProfile);
    ASSERT_NE(profile, nullptr);

    GfxXYZ2DisplayTransforms transforms(profile);

    auto relCol = transforms.getRelCol();
    auto absCol = transforms.getAbsCol();
    auto sat = transforms.getSat();
    auto perc = transforms.getPerc();

    // Different rendering intents should produce different transform objects
    // (though some might coincidentally be the same, we just check they exist)
    if (relCol && absCol) {
        // They are likely different objects
        EXPECT_NE(relCol.get(), absCol.get());
    }
}

// Test getDisplayProfile is const-correct
TEST_F(GfxXYZ2DisplayTransformsTest_558, GetDisplayProfileConstCorrectness_558)
{
    cmsHPROFILE rawProfile = cmsCreate_sRGBProfile();
    ASSERT_NE(rawProfile, nullptr);

    GfxLCMSProfilePtr profile = make_GfxLCMSProfilePtr(rawProfile);
    ASSERT_NE(profile, nullptr);

    const GfxXYZ2DisplayTransforms transforms(profile);

    // All getters should work on a const object
    auto dp = transforms.getDisplayProfile();
    EXPECT_EQ(dp, profile);

    auto relCol = transforms.getRelCol();
    auto absCol = transforms.getAbsCol();
    auto sat = transforms.getSat();
    auto perc = transforms.getPerc();

    EXPECT_NE(relCol, nullptr);
    EXPECT_NE(absCol, nullptr);
    EXPECT_NE(sat, nullptr);
    EXPECT_NE(perc, nullptr);
}

#else // !USE_CMS

// When CMS is not enabled, provide a trivial test
TEST(GfxXYZ2DisplayTransformsNoCMS_558, CMSNotEnabled_558)
{
    GTEST_SKIP() << "CMS support not enabled, skipping GfxXYZ2DisplayTransforms tests";
}

#endif // USE_CMS
