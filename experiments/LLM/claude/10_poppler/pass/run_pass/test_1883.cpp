#include <gtest/gtest.h>
#include <lcms2.h>
#include "GfxState.h"

// Test fixture for make_GfxLCMSProfilePtr tests
class MakeGfxLCMSProfilePtrTest_1883 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr returns an empty/null GfxLCMSProfilePtr
TEST_F(MakeGfxLCMSProfilePtrTest_1883, NullptrReturnsEmptyPtr_1883)
{
    GfxLCMSProfilePtr result = make_GfxLCMSProfilePtr(nullptr);
    EXPECT_EQ(result.get(), nullptr);
}

// Test that passing a valid LCMS profile returns a non-null GfxLCMSProfilePtr
TEST_F(MakeGfxLCMSProfilePtrTest_1883, ValidProfileReturnsNonNullPtr_1883)
{
    // Create a valid LCMS sRGB profile
    cmsHPROFILE profile = cmsCreate_sRGBProfile();
    ASSERT_NE(profile, nullptr);

    // make_GfxLCMSProfilePtr takes ownership, so we should NOT close it manually
    GfxLCMSProfilePtr result = make_GfxLCMSProfilePtr(profile);
    EXPECT_NE(result.get(), nullptr);
    EXPECT_EQ(result.get(), profile);
}

// Test that the returned smart pointer holds the same pointer value that was passed in
TEST_F(MakeGfxLCMSProfilePtrTest_1883, ReturnedPtrHoldsSameAddress_1883)
{
    cmsHPROFILE profile = cmsCreate_sRGBProfile();
    ASSERT_NE(profile, nullptr);

    void *rawPtr = static_cast<void *>(profile);
    GfxLCMSProfilePtr result = make_GfxLCMSProfilePtr(rawPtr);
    EXPECT_EQ(result.get(), rawPtr);
}

// Test that the empty GfxLCMSProfilePtr evaluates to false in boolean context
TEST_F(MakeGfxLCMSProfilePtrTest_1883, NullptrResultIsFalsy_1883)
{
    GfxLCMSProfilePtr result = make_GfxLCMSProfilePtr(nullptr);
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test that a valid GfxLCMSProfilePtr evaluates to true in boolean context
TEST_F(MakeGfxLCMSProfilePtrTest_1883, ValidProfileResultIsTruthy_1883)
{
    cmsHPROFILE profile = cmsCreate_sRGBProfile();
    ASSERT_NE(profile, nullptr);

    GfxLCMSProfilePtr result = make_GfxLCMSProfilePtr(profile);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that copying the smart pointer shares ownership correctly
TEST_F(MakeGfxLCMSProfilePtrTest_1883, CopySharesOwnership_1883)
{
    cmsHPROFILE profile = cmsCreate_sRGBProfile();
    ASSERT_NE(profile, nullptr);

    GfxLCMSProfilePtr result = make_GfxLCMSProfilePtr(profile);
    GfxLCMSProfilePtr copy = result;

    EXPECT_EQ(result.get(), copy.get());
    EXPECT_NE(result.get(), nullptr);
}

// Test that after the smart pointer goes out of scope, 
// the profile is properly managed (no crash on destruction)
TEST_F(MakeGfxLCMSProfilePtrTest_1883, DestructionDoesNotCrash_1883)
{
    {
        cmsHPROFILE profile = cmsCreate_sRGBProfile();
        ASSERT_NE(profile, nullptr);
        GfxLCMSProfilePtr result = make_GfxLCMSProfilePtr(profile);
        EXPECT_NE(result.get(), nullptr);
        // result goes out of scope here, custom deleter should be called
    }
    // If we reach here without crashing, the deleter worked correctly
    SUCCEED();
}

// Test with a different type of LCMS profile (Lab profile)
TEST_F(MakeGfxLCMSProfilePtrTest_1883, LabProfileReturnsValidPtr_1883)
{
    cmsHPROFILE profile = cmsCreateLab4Profile(nullptr);
    ASSERT_NE(profile, nullptr);

    GfxLCMSProfilePtr result = make_GfxLCMSProfilePtr(profile);
    EXPECT_NE(result.get(), nullptr);
    EXPECT_EQ(result.get(), profile);
}

// Test that use_count is 1 after creation (if shared_ptr-based)
TEST_F(MakeGfxLCMSProfilePtrTest_1883, UseCountIsOneAfterCreation_1883)
{
    cmsHPROFILE profile = cmsCreate_sRGBProfile();
    ASSERT_NE(profile, nullptr);

    GfxLCMSProfilePtr result = make_GfxLCMSProfilePtr(profile);
    EXPECT_EQ(result.use_count(), 1);
}

// Test that nullptr result has use_count of 0
TEST_F(MakeGfxLCMSProfilePtrTest_1883, NullptrResultUseCountIsZero_1883)
{
    GfxLCMSProfilePtr result = make_GfxLCMSProfilePtr(nullptr);
    EXPECT_EQ(result.use_count(), 0);
}
