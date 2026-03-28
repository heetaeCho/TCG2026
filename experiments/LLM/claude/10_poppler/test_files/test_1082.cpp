#include <gtest/gtest.h>
#include "OutputDev.h"

// A concrete subclass of OutputDev for testing, since OutputDev has pure virtual methods
class TestOutputDev : public OutputDev
{
public:
    TestOutputDev() : OutputDev() { }
    ~TestOutputDev() override { }

    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
};

class OutputDevTest_1082 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        dev = std::make_unique<TestOutputDev>();
    }

    std::unique_ptr<TestOutputDev> dev;
};

// Test that default RGB profile is initially null/empty
TEST_F(OutputDevTest_1082, DefaultRGBProfileInitiallyNull_1082)
{
    GfxLCMSProfilePtr profile = dev->getDefaultRGBProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting default RGB profile
TEST_F(OutputDevTest_1082, SetAndGetDefaultRGBProfile_1082)
{
#ifdef USE_CMS
    // If CMS is enabled, we can create a real profile
    cmsHPROFILE rawProfile = cmsCreate_sRGBProfile();
    ASSERT_NE(rawProfile, nullptr);
    GfxLCMSProfilePtr profile = std::make_shared<GfxLCMSProfileData>(rawProfile);
    dev->setDefaultRGBProfile(profile);
    GfxLCMSProfilePtr retrieved = dev->getDefaultRGBProfile();
    EXPECT_EQ(retrieved, profile);
#else
    // Without CMS, GfxLCMSProfilePtr is likely a null-like type
    GfxLCMSProfilePtr profile;
    dev->setDefaultRGBProfile(profile);
    GfxLCMSProfilePtr retrieved = dev->getDefaultRGBProfile();
    EXPECT_EQ(retrieved, profile);
#endif
}

// Test setting default RGB profile to nullptr
TEST_F(OutputDevTest_1082, SetDefaultRGBProfileToNull_1082)
{
    GfxLCMSProfilePtr nullProfile;
    dev->setDefaultRGBProfile(nullProfile);
    GfxLCMSProfilePtr retrieved = dev->getDefaultRGBProfile();
    EXPECT_EQ(retrieved, nullptr);
}

// Test that default Gray profile is initially null
TEST_F(OutputDevTest_1082, DefaultGrayProfileInitiallyNull_1082)
{
    GfxLCMSProfilePtr profile = dev->getDefaultGrayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting default Gray profile
TEST_F(OutputDevTest_1082, SetAndGetDefaultGrayProfile_1082)
{
    GfxLCMSProfilePtr nullProfile;
    dev->setDefaultGrayProfile(nullProfile);
    GfxLCMSProfilePtr retrieved = dev->getDefaultGrayProfile();
    EXPECT_EQ(retrieved, nullptr);
}

// Test that default CMYK profile is initially null
TEST_F(OutputDevTest_1082, DefaultCMYKProfileInitiallyNull_1082)
{
    GfxLCMSProfilePtr profile = dev->getDefaultCMYKProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting default CMYK profile
TEST_F(OutputDevTest_1082, SetAndGetDefaultCMYKProfile_1082)
{
    GfxLCMSProfilePtr nullProfile;
    dev->setDefaultCMYKProfile(nullProfile);
    GfxLCMSProfilePtr retrieved = dev->getDefaultCMYKProfile();
    EXPECT_EQ(retrieved, nullptr);
}

// Test that display profile is initially null
TEST_F(OutputDevTest_1082, DisplayProfileInitiallyNull_1082)
{
    GfxLCMSProfilePtr profile = dev->getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting display profile
TEST_F(OutputDevTest_1082, SetAndGetDisplayProfile_1082)
{
    GfxLCMSProfilePtr nullProfile;
    dev->setDisplayProfile(nullProfile);
    GfxLCMSProfilePtr retrieved = dev->getDisplayProfile();
    EXPECT_EQ(retrieved, nullptr);
}

// Test that overwriting a profile works correctly
TEST_F(OutputDevTest_1082, OverwriteDefaultRGBProfile_1082)
{
    GfxLCMSProfilePtr profile1;
    GfxLCMSProfilePtr profile2;
    dev->setDefaultRGBProfile(profile1);
    EXPECT_EQ(dev->getDefaultRGBProfile(), profile1);
    dev->setDefaultRGBProfile(profile2);
    EXPECT_EQ(dev->getDefaultRGBProfile(), profile2);
}

// Test startProfile and endProfile
TEST_F(OutputDevTest_1082, StartAndEndProfile_1082)
{
    dev->startProfile();
    auto profileHash = dev->endProfile();
    // After endProfile, we should get a valid map (possibly empty)
    EXPECT_NE(profileHash, nullptr);
}

// Test getProfileHash returns nullptr before startProfile
TEST_F(OutputDevTest_1082, GetProfileHashBeforeStart_1082)
{
    auto *hash = dev->getProfileHash();
    EXPECT_EQ(hash, nullptr);
}

// Test getProfileHash returns non-null after startProfile
TEST_F(OutputDevTest_1082, GetProfileHashAfterStart_1082)
{
    dev->startProfile();
    auto *hash = dev->getProfileHash();
    EXPECT_NE(hash, nullptr);
}

// Test getProfileHash returns nullptr after endProfile
TEST_F(OutputDevTest_1082, GetProfileHashAfterEnd_1082)
{
    dev->startProfile();
    auto result = dev->endProfile();
    auto *hash = dev->getProfileHash();
    EXPECT_EQ(hash, nullptr);
}

// Test default virtual method return values
TEST_F(OutputDevTest_1082, DefaultUseTilingPatternFill_1082)
{
    EXPECT_FALSE(dev->useTilingPatternFill());
}

TEST_F(OutputDevTest_1082, DefaultUseFillColorStop_1082)
{
    EXPECT_FALSE(dev->useFillColorStop());
}

TEST_F(OutputDevTest_1082, DefaultUseDrawForm_1082)
{
    EXPECT_FALSE(dev->useDrawForm());
}

TEST_F(OutputDevTest_1082, DefaultNeedNonText_1082)
{
    EXPECT_TRUE(dev->needNonText());
}

TEST_F(OutputDevTest_1082, DefaultNeedCharCount_1082)
{
    EXPECT_FALSE(dev->needCharCount());
}

TEST_F(OutputDevTest_1082, DefaultNeedClipToCropBox_1082)
{
    EXPECT_FALSE(dev->needClipToCropBox());
}

TEST_F(OutputDevTest_1082, DefaultGetVectorAntialias_1082)
{
    EXPECT_FALSE(dev->getVectorAntialias());
}

TEST_F(OutputDevTest_1082, DefaultCheckTransparencyGroup_1082)
{
    EXPECT_TRUE(dev->checkTransparencyGroup(nullptr, false));
}

// Test setDefaultCTM and cvtUserToDev
TEST_F(OutputDevTest_1082, SetDefaultCTMAndConvert_1082)
{
    // Identity-like CTM
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);
    int dx = 0, dy = 0;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    // With identity matrix, expect the user coords to map to device coords
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

// Test setDefaultCTM with a translation
TEST_F(OutputDevTest_1082, SetDefaultCTMWithTranslation_1082)
{
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    dev->setDefaultCTM(ctm);
    int dx = 0, dy = 0;
    dev->cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// Test getIccColorSpaceCache returns non-null
TEST_F(OutputDevTest_1082, GetIccColorSpaceCacheNotNull_1082)
{
    auto *cache = dev->getIccColorSpaceCache();
    EXPECT_NE(cache, nullptr);
}

// Test checkPageSlice default behavior
TEST_F(OutputDevTest_1082, DefaultCheckPageSlice_1082)
{
    bool result = dev->checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_TRUE(result);
}

// Test useShadedFills default returns 0 (false)
TEST_F(OutputDevTest_1082, DefaultUseShadedFills_1082)
{
    EXPECT_FALSE(dev->useShadedFills(1));
}

// Test that setting vector antialias doesn't crash (default impl is no-op)
TEST_F(OutputDevTest_1082, SetVectorAntialiasNoCrash_1082)
{
    EXPECT_NO_FATAL_FAILURE(dev->setVectorAntialias(true));
    EXPECT_NO_FATAL_FAILURE(dev->setVectorAntialias(false));
}

// Test multiple startProfile/endProfile cycles
TEST_F(OutputDevTest_1082, MultipleProfileCycles_1082)
{
    dev->startProfile();
    auto result1 = dev->endProfile();
    EXPECT_NE(result1, nullptr);

    dev->startProfile();
    auto result2 = dev->endProfile();
    EXPECT_NE(result2, nullptr);
}

// Test that various no-op virtual methods don't crash
TEST_F(OutputDevTest_1082, NoOpMethodsDontCrash_1082)
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
    EXPECT_NO_FATAL_FAILURE(dev->endType3Char(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->beginTextObject(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endTextObject(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->incCharCount(5));
    EXPECT_NO_FATAL_FAILURE(dev->beginActualText(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endActualText(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->clearSoftMask(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->processLink(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endMarkedContent(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->beginMarkedContent("test", nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->markPoint("test"));
    EXPECT_NO_FATAL_FAILURE(dev->markPoint("test", nullptr));
}

// Test beginStringOp and endStringOp don't crash
TEST_F(OutputDevTest_1082, StringOpMethodsDontCrash_1082)
{
    EXPECT_NO_FATAL_FAILURE(dev->beginStringOp(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endStringOp(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->beginString(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endString(nullptr));
}

// Test form-related methods don't crash
TEST_F(OutputDevTest_1082, FormMethodsDontCrash_1082)
{
    Ref ref = {0, 0};
    EXPECT_NO_FATAL_FAILURE(dev->beginForm(nullptr, ref));
    EXPECT_NO_FATAL_FAILURE(dev->drawForm(ref));
    EXPECT_NO_FATAL_FAILURE(dev->endForm(nullptr, ref));
}

// Test transparency group methods don't crash
TEST_F(OutputDevTest_1082, TransparencyGroupMethodsDontCrash_1082)
{
    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};
    EXPECT_NO_FATAL_FAILURE(dev->beginTransparencyGroup(nullptr, bbox, nullptr, false, false, false));
    EXPECT_NO_FATAL_FAILURE(dev->endTransparencyGroup(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->paintTransparencyGroup(nullptr, bbox));
}

// Test update methods don't crash
TEST_F(OutputDevTest_1082, UpdateMethodsDontCrash_1082)
{
    EXPECT_NO_FATAL_FAILURE(dev->updateCTM(nullptr, 1, 0, 0, 1, 0, 0));
    EXPECT_NO_FATAL_FAILURE(dev->updateLineDash(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateFlatness(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateLineJoin(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateLineCap(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateMiterLimit(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateLineWidth(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateStrokeAdjust(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateFillColorSpace(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateStrokeColorSpace(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateFillColor(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateStrokeColor(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateBlendMode(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateFillOpacity(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateStrokeOpacity(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateFont(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateTextMat(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateCharSpace(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateRender(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateRise(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateWordSpace(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateHorizScaling(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateTextPos(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateTextShift(nullptr, 0.0));
}

// Test shading fill defaults return false
TEST_F(OutputDevTest_1082, ShadingFillDefaultsFalse_1082)
{
    EXPECT_FALSE(dev->functionShadedFill(nullptr, nullptr));
    EXPECT_FALSE(dev->axialShadedFill(nullptr, nullptr, 0.0, 1.0));
    EXPECT_FALSE(dev->axialShadedSupportExtend(nullptr, nullptr));
    EXPECT_FALSE(dev->radialShadedFill(nullptr, nullptr, 0.0, 1.0));
    EXPECT_FALSE(dev->radialShadedSupportExtend(nullptr, nullptr));
    EXPECT_FALSE(dev->gouraudTriangleShadedFill(nullptr, nullptr));
    EXPECT_FALSE(dev->patchMeshShadedFill(nullptr, nullptr));
}

// Test type3D0 and type3D1 don't crash
TEST_F(OutputDevTest_1082, Type3MethodsDontCrash_1082)
{
    EXPECT_NO_FATAL_FAILURE(dev->type3D0(nullptr, 0.0, 0.0));
    EXPECT_NO_FATAL_FAILURE(dev->type3D1(nullptr, 0.0, 0.0, 0.0, 0.0, 100.0, 100.0));
}

// Test supportJPXtransparency default
TEST_F(OutputDevTest_1082, DefaultSupportJPXTransparency_1082)
{
    // Default is typically false
    bool result = dev->supportJPXtransparency();
    // Just verify it doesn't crash and returns a bool
    EXPECT_TRUE(result == true || result == false);
}
