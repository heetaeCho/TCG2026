#include <gtest/gtest.h>
#include "OutputDev.h"

// A concrete subclass of OutputDev for testing, since OutputDev has pure virtual methods
class TestOutputDev : public OutputDev
{
public:
    TestOutputDev() : OutputDev() { }
    ~TestOutputDev() override = default;

    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
};

class OutputDevTest_1085 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        dev = std::make_unique<TestOutputDev>();
    }

    std::unique_ptr<TestOutputDev> dev;
};

// Test that default CMYK profile is null/empty initially
TEST_F(OutputDevTest_1085, DefaultCMYKProfileIsNullInitially_1085)
{
    GfxLCMSProfilePtr profile = dev->getDefaultCMYKProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting CMYK profile
TEST_F(OutputDevTest_1085, SetAndGetDefaultCMYKProfile_1085)
{
#ifdef USE_CMS
    // If CMS is available, we can create a profile
    cmsHPROFILE rawProfile = cmsCreateLab4Profile(nullptr);
    ASSERT_NE(rawProfile, nullptr);
    GfxLCMSProfilePtr profile = std::make_shared<GfxLCMSProfileData>(rawProfile);
    dev->setDefaultCMYKProfile(profile);
    GfxLCMSProfilePtr retrieved = dev->getDefaultCMYKProfile();
    EXPECT_EQ(retrieved, profile);
#else
    // Without CMS, GfxLCMSProfilePtr is likely a null-like type
    GfxLCMSProfilePtr profile;
    dev->setDefaultCMYKProfile(profile);
    EXPECT_EQ(dev->getDefaultCMYKProfile(), profile);
#endif
}

// Test that default Gray profile is null initially
TEST_F(OutputDevTest_1085, DefaultGrayProfileIsNullInitially_1085)
{
    GfxLCMSProfilePtr profile = dev->getDefaultGrayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting Gray profile
TEST_F(OutputDevTest_1085, SetAndGetDefaultGrayProfile_1085)
{
    GfxLCMSProfilePtr profile;
    dev->setDefaultGrayProfile(profile);
    EXPECT_EQ(dev->getDefaultGrayProfile(), profile);
}

// Test that default RGB profile is null initially
TEST_F(OutputDevTest_1085, DefaultRGBProfileIsNullInitially_1085)
{
    GfxLCMSProfilePtr profile = dev->getDefaultRGBProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting RGB profile
TEST_F(OutputDevTest_1085, SetAndGetDefaultRGBProfile_1085)
{
    GfxLCMSProfilePtr profile;
    dev->setDefaultRGBProfile(profile);
    EXPECT_EQ(dev->getDefaultRGBProfile(), profile);
}

// Test that display profile is null initially
TEST_F(OutputDevTest_1085, DisplayProfileIsNullInitially_1085)
{
    GfxLCMSProfilePtr profile = dev->getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting display profile
TEST_F(OutputDevTest_1085, SetAndGetDisplayProfile_1085)
{
    GfxLCMSProfilePtr profile;
    dev->setDisplayProfile(profile);
    EXPECT_EQ(dev->getDisplayProfile(), profile);
}

// Test that profile hash is null before startProfile
TEST_F(OutputDevTest_1085, ProfileHashIsNullBeforeStart_1085)
{
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

// Test startProfile and endProfile
TEST_F(OutputDevTest_1085, StartAndEndProfile_1085)
{
    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
    auto result = dev->endProfile();
    EXPECT_NE(result, nullptr);
    // After endProfile, the hash should be moved out
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

// Test endProfile without startProfile returns null
TEST_F(OutputDevTest_1085, EndProfileWithoutStartReturnsNull_1085)
{
    auto result = dev->endProfile();
    EXPECT_EQ(result, nullptr);
}

// Test default return values of virtual boolean methods
TEST_F(OutputDevTest_1085, DefaultUseTilingPatternFill_1085)
{
    EXPECT_FALSE(dev->useTilingPatternFill());
}

TEST_F(OutputDevTest_1085, DefaultUseShadedFills_1085)
{
    EXPECT_FALSE(dev->useShadedFills(0));
    EXPECT_FALSE(dev->useShadedFills(1));
}

TEST_F(OutputDevTest_1085, DefaultUseFillColorStop_1085)
{
    EXPECT_FALSE(dev->useFillColorStop());
}

TEST_F(OutputDevTest_1085, DefaultUseDrawForm_1085)
{
    EXPECT_FALSE(dev->useDrawForm());
}

TEST_F(OutputDevTest_1085, DefaultNeedNonText_1085)
{
    EXPECT_TRUE(dev->needNonText());
}

TEST_F(OutputDevTest_1085, DefaultNeedCharCount_1085)
{
    EXPECT_FALSE(dev->needCharCount());
}

TEST_F(OutputDevTest_1085, DefaultNeedClipToCropBox_1085)
{
    EXPECT_FALSE(dev->needClipToCropBox());
}

TEST_F(OutputDevTest_1085, DefaultGetVectorAntialias_1085)
{
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test setVectorAntialias doesn't crash (base implementation is a no-op)
TEST_F(OutputDevTest_1085, SetVectorAntialiasNoOp_1085)
{
    EXPECT_NO_FATAL_FAILURE(dev->setVectorAntialias(true));
    EXPECT_NO_FATAL_FAILURE(dev->setVectorAntialias(false));
}

// Test setDefaultCTM
TEST_F(OutputDevTest_1085, SetDefaultCTM_1085)
{
    std::array<double, 6> ctm = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
    EXPECT_NO_FATAL_FAILURE(dev->setDefaultCTM(ctm));
}

// Test cvtUserToDev with identity CTM
TEST_F(OutputDevTest_1085, CvtUserToDevIdentityCTM_1085)
{
    std::array<double, 6> ctm = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
    dev->setDefaultCTM(ctm);
    int dx, dy;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

// Test cvtUserToDev with scaled CTM
TEST_F(OutputDevTest_1085, CvtUserToDevScaledCTM_1085)
{
    std::array<double, 6> ctm = { 2.0, 0.0, 0.0, 2.0, 0.0, 0.0 };
    dev->setDefaultCTM(ctm);
    int dx, dy;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    EXPECT_EQ(dx, 20);
    EXPECT_EQ(dy, 40);
}

// Test cvtUserToDev with translation
TEST_F(OutputDevTest_1085, CvtUserToDevWithTranslation_1085)
{
    std::array<double, 6> ctm = { 1.0, 0.0, 0.0, 1.0, 100.0, 200.0 };
    dev->setDefaultCTM(ctm);
    int dx, dy;
    dev->cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// Test getIccColorSpaceCache returns non-null
TEST_F(OutputDevTest_1085, GetIccColorSpaceCacheNotNull_1085)
{
    EXPECT_NE(dev->getIccColorSpaceCache(), nullptr);
}

// Test checkPageSlice default returns true
TEST_F(OutputDevTest_1085, CheckPageSliceDefaultReturnsTrue_1085)
{
    bool result = dev->checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_TRUE(result);
}

// Test that calling startProfile twice replaces the first
TEST_F(OutputDevTest_1085, StartProfileTwiceReplacesFirst_1085)
{
    dev->startProfile();
    auto *first = dev->getProfileHash();
    ASSERT_NE(first, nullptr);
    dev->startProfile();
    auto *second = dev->getProfileHash();
    EXPECT_NE(second, nullptr);
}

// Test checkTransparencyGroup default
TEST_F(OutputDevTest_1085, CheckTransparencyGroupDefault_1085)
{
    EXPECT_TRUE(dev->checkTransparencyGroup(nullptr, false));
}

// Test various no-op virtual methods don't crash
TEST_F(OutputDevTest_1085, NoOpMethodsDontCrash_1085)
{
    EXPECT_NO_FATAL_FAILURE(dev->startPage(1, nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endPage());
    EXPECT_NO_FATAL_FAILURE(dev->dump());
    EXPECT_NO_FATAL_FAILURE(dev->saveState(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->restoreState(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateAll(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->stroke(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->fill(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->eoFill(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->clip(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->eoClip(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->clipToStrokePath(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->beginStringOp(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endStringOp(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endType3Char(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->beginTextObject(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endTextObject(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->incCharCount(0));
    EXPECT_NO_FATAL_FAILURE(dev->beginActualText(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endActualText(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->clearSoftMask(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->processLink(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endMarkedContent(nullptr));
}

// Test setting and overwriting CMYK profile
TEST_F(OutputDevTest_1085, OverwriteDefaultCMYKProfile_1085)
{
    GfxLCMSProfilePtr profile1;
    dev->setDefaultCMYKProfile(profile1);
    EXPECT_EQ(dev->getDefaultCMYKProfile(), profile1);

    GfxLCMSProfilePtr profile2;
    dev->setDefaultCMYKProfile(profile2);
    EXPECT_EQ(dev->getDefaultCMYKProfile(), profile2);
}

// Test functionShadedFill default returns false
TEST_F(OutputDevTest_1085, FunctionShadedFillDefault_1085)
{
    EXPECT_FALSE(dev->functionShadedFill(nullptr, nullptr));
}

// Test axialShadedFill default returns false
TEST_F(OutputDevTest_1085, AxialShadedFillDefault_1085)
{
    EXPECT_FALSE(dev->axialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

// Test radialShadedFill default returns false
TEST_F(OutputDevTest_1085, RadialShadedFillDefault_1085)
{
    EXPECT_FALSE(dev->radialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

// Test gouraudTriangleShadedFill default returns false
TEST_F(OutputDevTest_1085, GouraudTriangleShadedFillDefault_1085)
{
    EXPECT_FALSE(dev->gouraudTriangleShadedFill(nullptr, nullptr));
}

// Test patchMeshShadedFill default returns false
TEST_F(OutputDevTest_1085, PatchMeshShadedFillDefault_1085)
{
    EXPECT_FALSE(dev->patchMeshShadedFill(nullptr, nullptr));
}

// Test supportJPXtransparency default
TEST_F(OutputDevTest_1085, SupportJPXtransparencyDefault_1085)
{
    // Default should typically be false
    // Just ensure it doesn't crash
    dev->supportJPXtransparency();
}
