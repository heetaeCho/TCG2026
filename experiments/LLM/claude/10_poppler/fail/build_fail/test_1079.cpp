#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h"

// A concrete subclass of OutputDev for testing purposes, since OutputDev has pure virtual methods
class TestOutputDev : public OutputDev
{
public:
    TestOutputDev() : OutputDev() { }

    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
};

class OutputDevTest_1079 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        dev = std::make_unique<TestOutputDev>();
    }

    std::unique_ptr<TestOutputDev> dev;
};

// Test that a freshly constructed OutputDev has a null display profile
TEST_F(OutputDevTest_1079, DefaultDisplayProfileIsNull_1079)
{
    GfxLCMSProfilePtr profile = dev->getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test that a freshly constructed OutputDev has a null default gray profile
TEST_F(OutputDevTest_1079, DefaultGrayProfileIsNull_1079)
{
    GfxLCMSProfilePtr profile = dev->getDefaultGrayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test that a freshly constructed OutputDev has a null default RGB profile
TEST_F(OutputDevTest_1079, DefaultRGBProfileIsNull_1079)
{
    GfxLCMSProfilePtr profile = dev->getDefaultRGBProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test that a freshly constructed OutputDev has a null default CMYK profile
TEST_F(OutputDevTest_1079, DefaultCMYKProfileIsNull_1079)
{
    GfxLCMSProfilePtr profile = dev->getDefaultCMYKProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setDisplayProfile and getDisplayProfile round-trip
TEST_F(OutputDevTest_1079, SetAndGetDisplayProfile_1079)
{
#ifdef USE_CMS
    // If CMS is available, we can create a profile; otherwise this tests with nullptr
    GfxLCMSProfilePtr profile = make_GfxLCMSProfilePtr(cmsCreate_sRGBProfile());
    dev->setDisplayProfile(profile);
    EXPECT_EQ(dev->getDisplayProfile(), profile);
#else
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDisplayProfile(profile);
    EXPECT_EQ(dev->getDisplayProfile(), nullptr);
#endif
}

// Test setDefaultGrayProfile and getDefaultGrayProfile round-trip
TEST_F(OutputDevTest_1079, SetAndGetDefaultGrayProfile_1079)
{
#ifdef USE_CMS
    GfxLCMSProfilePtr profile = make_GfxLCMSProfilePtr(cmsCreate_sRGBProfile());
    dev->setDefaultGrayProfile(profile);
    EXPECT_EQ(dev->getDefaultGrayProfile(), profile);
#else
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDefaultGrayProfile(profile);
    EXPECT_EQ(dev->getDefaultGrayProfile(), nullptr);
#endif
}

// Test setDefaultRGBProfile and getDefaultRGBProfile round-trip
TEST_F(OutputDevTest_1079, SetAndGetDefaultRGBProfile_1079)
{
#ifdef USE_CMS
    GfxLCMSProfilePtr profile = make_GfxLCMSProfilePtr(cmsCreate_sRGBProfile());
    dev->setDefaultRGBProfile(profile);
    EXPECT_EQ(dev->getDefaultRGBProfile(), profile);
#else
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDefaultRGBProfile(profile);
    EXPECT_EQ(dev->getDefaultRGBProfile(), nullptr);
#endif
}

// Test setDefaultCMYKProfile and getDefaultCMYKProfile round-trip
TEST_F(OutputDevTest_1079, SetAndGetDefaultCMYKProfile_1079)
{
#ifdef USE_CMS
    GfxLCMSProfilePtr profile = make_GfxLCMSProfilePtr(cmsCreate_sRGBProfile());
    dev->setDefaultCMYKProfile(profile);
    EXPECT_EQ(dev->getDefaultCMYKProfile(), profile);
#else
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDefaultCMYKProfile(profile);
    EXPECT_EQ(dev->getDefaultCMYKProfile(), nullptr);
#endif
}

// Test that setting display profile to null works
TEST_F(OutputDevTest_1079, SetDisplayProfileToNull_1079)
{
    GfxLCMSProfilePtr nullProfile = nullptr;
    dev->setDisplayProfile(nullProfile);
    EXPECT_EQ(dev->getDisplayProfile(), nullptr);
}

// Test that profileHash is initially null (before startProfile)
TEST_F(OutputDevTest_1079, GetProfileHashInitiallyNull_1079)
{
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

// Test startProfile and endProfile
TEST_F(OutputDevTest_1079, StartAndEndProfile_1079)
{
    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);

    auto result = dev->endProfile();
    // After endProfile, the hash should have been moved out
    // The returned result should be a valid unique_ptr (possibly empty map)
    EXPECT_NE(result, nullptr);
}

// Test endProfile without startProfile returns nullptr
TEST_F(OutputDevTest_1079, EndProfileWithoutStart_1079)
{
    auto result = dev->endProfile();
    EXPECT_EQ(result, nullptr);
}

// Test getIccColorSpaceCache returns non-null
TEST_F(OutputDevTest_1079, GetIccColorSpaceCacheNotNull_1079)
{
    auto *cache = dev->getIccColorSpaceCache();
    EXPECT_NE(cache, nullptr);
}

// Test default virtual method return values
TEST_F(OutputDevTest_1079, DefaultUseTilingPatternFill_1079)
{
    EXPECT_FALSE(dev->useTilingPatternFill());
}

TEST_F(OutputDevTest_1079, DefaultUseShadedFills_1079)
{
    EXPECT_FALSE(dev->useShadedFills(0));
    EXPECT_FALSE(dev->useShadedFills(1));
}

TEST_F(OutputDevTest_1079, DefaultUseFillColorStop_1079)
{
    EXPECT_FALSE(dev->useFillColorStop());
}

TEST_F(OutputDevTest_1079, DefaultUseDrawForm_1079)
{
    EXPECT_FALSE(dev->useDrawForm());
}

TEST_F(OutputDevTest_1079, DefaultNeedNonText_1079)
{
    EXPECT_TRUE(dev->needNonText());
}

TEST_F(OutputDevTest_1079, DefaultNeedCharCount_1079)
{
    EXPECT_FALSE(dev->needCharCount());
}

TEST_F(OutputDevTest_1079, DefaultNeedClipToCropBox_1079)
{
    EXPECT_FALSE(dev->needClipToCropBox());
}

TEST_F(OutputDevTest_1079, DefaultGetVectorAntialias_1079)
{
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test checkPageSlice default returns true
TEST_F(OutputDevTest_1079, DefaultCheckPageSlice_1079)
{
    EXPECT_TRUE(dev->checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false));
}

// Test that setDefaultCTM can be called without crashing
TEST_F(OutputDevTest_1079, SetDefaultCTMDoesNotCrash_1079)
{
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_NO_THROW(dev->setDefaultCTM(ctm));
}

// Test cvtUserToDev after setting identity CTM
TEST_F(OutputDevTest_1079, CvtUserToDevIdentityCTM_1079)
{
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

// Test cvtUserToDev with a scaling CTM
TEST_F(OutputDevTest_1079, CvtUserToDevScalingCTM_1079)
{
    std::array<double, 6> ctm = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(5.0, 10.0, &dx, &dy);
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

// Test cvtUserToDev with translation CTM
TEST_F(OutputDevTest_1079, CvtUserToDevTranslationCTM_1079)
{
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// Test that checkTransparencyGroup default returns false
TEST_F(OutputDevTest_1079, DefaultCheckTransparencyGroup_1079)
{
    EXPECT_FALSE(dev->checkTransparencyGroup(nullptr, false));
    EXPECT_FALSE(dev->checkTransparencyGroup(nullptr, true));
}

// Test default supportJPXtransparency
TEST_F(OutputDevTest_1079, DefaultSupportJPXTransparency_1079)
{
    EXPECT_FALSE(dev->supportJPXtransparency());
}

// Test that various no-op virtual methods don't crash
TEST_F(OutputDevTest_1079, NoOpMethodsDoNotCrash_1079)
{
    EXPECT_NO_THROW(dev->startPage(1, nullptr, nullptr));
    EXPECT_NO_THROW(dev->endPage());
    EXPECT_NO_THROW(dev->dump());
    EXPECT_NO_THROW(dev->saveState(nullptr));
    EXPECT_NO_THROW(dev->restoreState(nullptr));
    EXPECT_NO_THROW(dev->stroke(nullptr));
    EXPECT_NO_THROW(dev->fill(nullptr));
    EXPECT_NO_THROW(dev->eoFill(nullptr));
    EXPECT_NO_THROW(dev->clip(nullptr));
    EXPECT_NO_THROW(dev->eoClip(nullptr));
    EXPECT_NO_THROW(dev->clipToStrokePath(nullptr));
    EXPECT_NO_THROW(dev->beginStringOp(nullptr));
    EXPECT_NO_THROW(dev->endStringOp(nullptr));
    EXPECT_NO_THROW(dev->endType3Char(nullptr));
    EXPECT_NO_THROW(dev->beginTextObject(nullptr));
    EXPECT_NO_THROW(dev->endTextObject(nullptr));
    EXPECT_NO_THROW(dev->incCharCount(0));
    EXPECT_NO_THROW(dev->incCharCount(100));
    EXPECT_NO_THROW(dev->endActualText(nullptr));
    EXPECT_NO_THROW(dev->clearSoftMask(nullptr));
    EXPECT_NO_THROW(dev->processLink(nullptr));
    EXPECT_NO_THROW(dev->setVectorAntialias(true));
    EXPECT_NO_THROW(dev->setVectorAntialias(false));
    EXPECT_NO_THROW(dev->endMarkedContent(nullptr));
    EXPECT_NO_THROW(dev->beginMarkedContent("test", nullptr));
    EXPECT_NO_THROW(dev->markPoint("test"));
    EXPECT_NO_THROW(dev->markPoint("test", nullptr));
}

// Test profile workflow: start, get hash, end
TEST_F(OutputDevTest_1079, ProfileWorkflow_1079)
{
    // Before starting, hash should be null
    EXPECT_EQ(dev->getProfileHash(), nullptr);

    dev->startProfile();

    // After starting, hash should exist
    auto *hash = dev->getProfileHash();
    EXPECT_NE(hash, nullptr);

    // End profile returns the hash
    auto result = dev->endProfile();
    EXPECT_NE(result, nullptr);

    // After ending, hash should be null again
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

// Test setting display profile overwrites previous
TEST_F(OutputDevTest_1079, SetDisplayProfileOverwritesPrevious_1079)
{
#ifdef USE_CMS
    GfxLCMSProfilePtr profile1 = make_GfxLCMSProfilePtr(cmsCreate_sRGBProfile());
    GfxLCMSProfilePtr profile2 = make_GfxLCMSProfilePtr(cmsCreate_sRGBProfile());
    dev->setDisplayProfile(profile1);
    EXPECT_EQ(dev->getDisplayProfile(), profile1);
    dev->setDisplayProfile(profile2);
    EXPECT_EQ(dev->getDisplayProfile(), profile2);
    EXPECT_NE(dev->getDisplayProfile(), profile1);
#else
    // Without CMS, profiles are just nullptr
    dev->setDisplayProfile(nullptr);
    EXPECT_EQ(dev->getDisplayProfile(), nullptr);
#endif
}

// Test default shaded fill methods return false
TEST_F(OutputDevTest_1079, DefaultShadedFillMethodsReturnFalse_1079)
{
    EXPECT_FALSE(dev->functionShadedFill(nullptr, nullptr));
    EXPECT_FALSE(dev->axialShadedFill(nullptr, nullptr, 0.0, 1.0));
    EXPECT_FALSE(dev->axialShadedSupportExtend(nullptr, nullptr));
    EXPECT_FALSE(dev->radialShadedFill(nullptr, nullptr, 0.0, 1.0));
    EXPECT_FALSE(dev->radialShadedSupportExtend(nullptr, nullptr));
    EXPECT_FALSE(dev->gouraudTriangleShadedFill(nullptr, nullptr));
    EXPECT_FALSE(dev->patchMeshShadedFill(nullptr, nullptr));
}

// Test default tilingPatternFill returns false
TEST_F(OutputDevTest_1079, DefaultTilingPatternFillReturnsFalse_1079)
{
    std::array<double, 6> mat = {1, 0, 0, 1, 0, 0};
    EXPECT_FALSE(dev->tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 1, 1, 1.0, 1.0));
}
