#include <gtest/gtest.h>
#include "OutputDev.h"

// A concrete subclass of OutputDev for testing, since OutputDev has pure virtual methods
class TestOutputDev : public OutputDev
{
public:
    TestOutputDev() : OutputDev() { }
    ~TestOutputDev() override { }

    // Implement required pure virtual methods
    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
};

class OutputDevTest_1080 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        dev = std::make_unique<TestOutputDev>();
    }

    std::unique_ptr<TestOutputDev> dev;
};

// Test that default gray profile is initially null/empty
TEST_F(OutputDevTest_1080, DefaultGrayProfileInitiallyNull_1080)
{
    GfxLCMSProfilePtr profile = dev->getDefaultGrayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting the default gray profile
TEST_F(OutputDevTest_1080, SetAndGetDefaultGrayProfile_1080)
{
#ifdef USE_CMS
    // If CMS is available, create a real profile
    cmsHPROFILE rawProfile = cmsCreateGrayProfile(cmsD50_xyY(), cmsBuildGamma(nullptr, 2.2));
    GfxLCMSProfilePtr profile = std::make_shared<GfxLCMSProfileData>(rawProfile);
    dev->setDefaultGrayProfile(profile);
    EXPECT_EQ(dev->getDefaultGrayProfile(), profile);
#else
    // Without CMS, GfxLCMSProfilePtr is likely a null-capable smart pointer
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDefaultGrayProfile(profile);
    EXPECT_EQ(dev->getDefaultGrayProfile(), nullptr);
#endif
}

// Test setting gray profile to nullptr explicitly
TEST_F(OutputDevTest_1080, SetDefaultGrayProfileToNull_1080)
{
    GfxLCMSProfilePtr nullProfile = nullptr;
    dev->setDefaultGrayProfile(nullProfile);
    EXPECT_EQ(dev->getDefaultGrayProfile(), nullptr);
}

// Test that default RGB profile is initially null/empty
TEST_F(OutputDevTest_1080, DefaultRGBProfileInitiallyNull_1080)
{
    GfxLCMSProfilePtr profile = dev->getDefaultRGBProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting the default RGB profile
TEST_F(OutputDevTest_1080, SetAndGetDefaultRGBProfile_1080)
{
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDefaultRGBProfile(profile);
    EXPECT_EQ(dev->getDefaultRGBProfile(), nullptr);
}

// Test that default CMYK profile is initially null/empty
TEST_F(OutputDevTest_1080, DefaultCMYKProfileInitiallyNull_1080)
{
    GfxLCMSProfilePtr profile = dev->getDefaultCMYKProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting the default CMYK profile
TEST_F(OutputDevTest_1080, SetAndGetDefaultCMYKProfile_1080)
{
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDefaultCMYKProfile(profile);
    EXPECT_EQ(dev->getDefaultCMYKProfile(), nullptr);
}

// Test that display profile is initially null/empty
TEST_F(OutputDevTest_1080, DisplayProfileInitiallyNull_1080)
{
    GfxLCMSProfilePtr profile = dev->getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting the display profile
TEST_F(OutputDevTest_1080, SetAndGetDisplayProfile_1080)
{
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDisplayProfile(profile);
    EXPECT_EQ(dev->getDisplayProfile(), nullptr);
}

// Test default return values for virtual bool methods
TEST_F(OutputDevTest_1080, UseTilingPatternFillDefault_1080)
{
    EXPECT_FALSE(dev->useTilingPatternFill());
}

TEST_F(OutputDevTest_1080, UseFillColorStopDefault_1080)
{
    EXPECT_FALSE(dev->useFillColorStop());
}

TEST_F(OutputDevTest_1080, UseDrawFormDefault_1080)
{
    EXPECT_FALSE(dev->useDrawForm());
}

TEST_F(OutputDevTest_1080, NeedNonTextDefault_1080)
{
    EXPECT_FALSE(dev->needNonText());
}

TEST_F(OutputDevTest_1080, NeedCharCountDefault_1080)
{
    EXPECT_FALSE(dev->needCharCount());
}

TEST_F(OutputDevTest_1080, NeedClipToCropBoxDefault_1080)
{
    EXPECT_FALSE(dev->needClipToCropBox());
}

TEST_F(OutputDevTest_1080, GetVectorAntialiasDefault_1080)
{
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test useShadedFills default returns 0/false for various types
TEST_F(OutputDevTest_1080, UseShadedFillsDefaultType1_1080)
{
    EXPECT_FALSE(dev->useShadedFills(1));
}

TEST_F(OutputDevTest_1080, UseShadedFillsDefaultType0_1080)
{
    EXPECT_FALSE(dev->useShadedFills(0));
}

// Test profiling start/end
TEST_F(OutputDevTest_1080, ProfileHashInitiallyNull_1080)
{
    // Before startProfile, getProfileHash should return nullptr
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1080, StartProfileCreatesProfileHash_1080)
{
    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1080, EndProfileReturnsAndClearsHash_1080)
{
    dev->startProfile();
    auto result = dev->endProfile();
    EXPECT_NE(result, nullptr);
    // After endProfile, the hash should be moved out
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1080, EndProfileWithoutStartReturnsNull_1080)
{
    auto result = dev->endProfile();
    // If profiling was never started, endProfile should return nullptr
    EXPECT_EQ(result, nullptr);
}

// Test getIccColorSpaceCache returns non-null
TEST_F(OutputDevTest_1080, GetIccColorSpaceCacheNotNull_1080)
{
    EXPECT_NE(dev->getIccColorSpaceCache(), nullptr);
}

// Test setDefaultCTM and cvtUserToDev
TEST_F(OutputDevTest_1080, SetDefaultCTMAndConvert_1080)
{
    // Identity-like CTM: scale 1, no translation
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    // With identity CTM, user coords should map approximately to device coords
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

TEST_F(OutputDevTest_1080, SetDefaultCTMWithScale_1080)
{
    // Scale by 2
    std::array<double, 6> ctm = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    EXPECT_EQ(dx, 20);
    EXPECT_EQ(dy, 40);
}

TEST_F(OutputDevTest_1080, SetDefaultCTMWithTranslation_1080)
{
    // Identity with translation of (100, 200)
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// Test checkPageSlice default behavior
TEST_F(OutputDevTest_1080, CheckPageSliceDefaultReturnsTrue_1080)
{
    bool result = dev->checkPageSlice(nullptr, 72.0, 72.0, 0, true, false, 0, 0, 100, 100, false);
    EXPECT_TRUE(result);
}

// Test that overriding gray profile replaces previous value
TEST_F(OutputDevTest_1080, OverwriteDefaultGrayProfile_1080)
{
    GfxLCMSProfilePtr profile1 = nullptr;
    dev->setDefaultGrayProfile(profile1);
    EXPECT_EQ(dev->getDefaultGrayProfile(), nullptr);

    // Set again with nullptr (just verifying no crash and consistency)
    GfxLCMSProfilePtr profile2 = nullptr;
    dev->setDefaultGrayProfile(profile2);
    EXPECT_EQ(dev->getDefaultGrayProfile(), nullptr);
}

// Test setVectorAntialias (default impl may be no-op, but shouldn't crash)
TEST_F(OutputDevTest_1080, SetVectorAntialiasNoOp_1080)
{
    // This should not crash; default implementation is likely a no-op
    dev->setVectorAntialias(true);
    // The default getVectorAntialias may still return false if the base impl ignores it
    // We just test it doesn't crash
}

// Test checkTransparencyGroup default
TEST_F(OutputDevTest_1080, CheckTransparencyGroupDefault_1080)
{
    bool result = dev->checkTransparencyGroup(nullptr, false);
    EXPECT_TRUE(result);
}

// Test supportJPXtransparency default
TEST_F(OutputDevTest_1080, SupportJPXTransparencyDefault_1080)
{
    EXPECT_FALSE(dev->supportJPXtransparency());
}

// Test that multiple startProfile/endProfile cycles work
TEST_F(OutputDevTest_1080, MultipleProfileCycles_1080)
{
    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
    auto result1 = dev->endProfile();
    EXPECT_NE(result1, nullptr);
    EXPECT_EQ(dev->getProfileHash(), nullptr);

    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
    auto result2 = dev->endProfile();
    EXPECT_NE(result2, nullptr);
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}
