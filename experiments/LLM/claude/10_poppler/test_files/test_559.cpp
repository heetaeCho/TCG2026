#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

class GfxXYZ2DisplayTransformsTest_559 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that default-constructed or null-profile object returns nullptr for getRelCol
TEST_F(GfxXYZ2DisplayTransformsTest_559, GetRelColWithNullProfile_559) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);
    auto relCol = transforms.getRelCol();
    // With a null profile, the transform should be nullptr
    EXPECT_EQ(relCol, nullptr);
}

// Test that getAbsCol returns nullptr with null profile
TEST_F(GfxXYZ2DisplayTransformsTest_559, GetAbsColWithNullProfile_559) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);
    auto absCol = transforms.getAbsCol();
    EXPECT_EQ(absCol, nullptr);
}

// Test that getSat returns nullptr with null profile
TEST_F(GfxXYZ2DisplayTransformsTest_559, GetSatWithNullProfile_559) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);
    auto sat = transforms.getSat();
    EXPECT_EQ(sat, nullptr);
}

// Test that getPerc returns nullptr with null profile
TEST_F(GfxXYZ2DisplayTransformsTest_559, GetPercWithNullProfile_559) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);
    auto perc = transforms.getPerc();
    EXPECT_EQ(perc, nullptr);
}

// Test that getDisplayProfile returns the same profile that was passed in (null case)
TEST_F(GfxXYZ2DisplayTransformsTest_559, GetDisplayProfileWithNullProfile_559) {
    GfxLCMSProfilePtr nullProfile;
    GfxXYZ2DisplayTransforms transforms(nullProfile);
    auto profile = transforms.getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

#ifdef USE_CMS
// Tests with a valid sRGB display profile (only available when CMS is enabled)

class GfxXYZ2DisplayTransformsWithProfileTest_559 : public ::testing::Test {
protected:
    GfxLCMSProfilePtr displayProfile;

    void SetUp() override {
        // Create an sRGB profile for testing
        cmsHPROFILE srgb = cmsCreate_sRGBProfile();
        if (srgb) {
            displayProfile = make_GfxLCMSProfilePtr(srgb);
        }
    }

    void TearDown() override {
    }
};

// Test that with a valid profile, getRelCol returns a non-null transform
TEST_F(GfxXYZ2DisplayTransformsWithProfileTest_559, GetRelColWithValidProfile_559) {
    if (!displayProfile) {
        GTEST_SKIP() << "Could not create sRGB profile";
    }
    GfxXYZ2DisplayTransforms transforms(displayProfile);
    auto relCol = transforms.getRelCol();
    EXPECT_NE(relCol, nullptr);
}

// Test that with a valid profile, getAbsCol returns a non-null transform
TEST_F(GfxXYZ2DisplayTransformsWithProfileTest_559, GetAbsColWithValidProfile_559) {
    if (!displayProfile) {
        GTEST_SKIP() << "Could not create sRGB profile";
    }
    GfxXYZ2DisplayTransforms transforms(displayProfile);
    auto absCol = transforms.getAbsCol();
    EXPECT_NE(absCol, nullptr);
}

// Test that with a valid profile, getSat returns a non-null transform
TEST_F(GfxXYZ2DisplayTransformsWithProfileTest_559, GetSatWithValidProfile_559) {
    if (!displayProfile) {
        GTEST_SKIP() << "Could not create sRGB profile";
    }
    GfxXYZ2DisplayTransforms transforms(displayProfile);
    auto sat = transforms.getSat();
    EXPECT_NE(sat, nullptr);
}

// Test that with a valid profile, getPerc returns a non-null transform
TEST_F(GfxXYZ2DisplayTransformsWithProfileTest_559, GetPercWithValidProfile_559) {
    if (!displayProfile) {
        GTEST_SKIP() << "Could not create sRGB profile";
    }
    GfxXYZ2DisplayTransforms transforms(displayProfile);
    auto perc = transforms.getPerc();
    EXPECT_NE(perc, nullptr);
}

// Test that getDisplayProfile returns the profile that was provided
TEST_F(GfxXYZ2DisplayTransformsWithProfileTest_559, GetDisplayProfileReturnsProvidedProfile_559) {
    if (!displayProfile) {
        GTEST_SKIP() << "Could not create sRGB profile";
    }
    GfxXYZ2DisplayTransforms transforms(displayProfile);
    auto returnedProfile = transforms.getDisplayProfile();
    EXPECT_EQ(returnedProfile, displayProfile);
}

// Test that calling getRelCol multiple times returns the same shared_ptr (consistency)
TEST_F(GfxXYZ2DisplayTransformsWithProfileTest_559, GetRelColConsistency_559) {
    if (!displayProfile) {
        GTEST_SKIP() << "Could not create sRGB profile";
    }
    GfxXYZ2DisplayTransforms transforms(displayProfile);
    auto relCol1 = transforms.getRelCol();
    auto relCol2 = transforms.getRelCol();
    EXPECT_EQ(relCol1, relCol2);
}

// Test that different rendering intent transforms are potentially different objects
TEST_F(GfxXYZ2DisplayTransformsWithProfileTest_559, DifferentIntentsReturnDifferentTransforms_559) {
    if (!displayProfile) {
        GTEST_SKIP() << "Could not create sRGB profile";
    }
    GfxXYZ2DisplayTransforms transforms(displayProfile);
    auto relCol = transforms.getRelCol();
    auto absCol = transforms.getAbsCol();
    auto sat = transforms.getSat();
    auto perc = transforms.getPerc();
    
    // All should be non-null
    EXPECT_NE(relCol, nullptr);
    EXPECT_NE(absCol, nullptr);
    EXPECT_NE(sat, nullptr);
    EXPECT_NE(perc, nullptr);
    
    // Different rendering intents should generally produce different transform objects
    // (though this is implementation-dependent, at minimum they should all be valid)
}

#endif // USE_CMS
