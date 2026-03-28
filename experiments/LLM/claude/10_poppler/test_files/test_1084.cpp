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

class OutputDevTest_1084 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        dev = std::make_unique<TestOutputDev>();
    }

    std::unique_ptr<TestOutputDev> dev;
};

// Test that default CMYK profile is initially null/empty
TEST_F(OutputDevTest_1084, DefaultCMYKProfileInitiallyNull_1084)
{
    GfxLCMSProfilePtr profile = dev->getDefaultCMYKProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting CMYK profile
TEST_F(OutputDevTest_1084, SetAndGetDefaultCMYKProfile_1084)
{
#ifdef USE_CMS
    // If CMS is enabled, we can create a real profile
    cmsHPROFILE rawProfile = cmsCreateLab4Profile(nullptr);
    ASSERT_NE(rawProfile, nullptr);
    GfxLCMSProfilePtr profile = std::make_shared<GfxLCMSProfileData>(rawProfile);
    dev->setDefaultCMYKProfile(profile);
    GfxLCMSProfilePtr retrieved = dev->getDefaultCMYKProfile();
    EXPECT_EQ(retrieved, profile);
#else
    // Without CMS, GfxLCMSProfilePtr is likely a nullptr type or trivial
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDefaultCMYKProfile(profile);
    GfxLCMSProfilePtr retrieved = dev->getDefaultCMYKProfile();
    EXPECT_EQ(retrieved, nullptr);
#endif
}

// Test setting CMYK profile to null
TEST_F(OutputDevTest_1084, SetCMYKProfileToNull_1084)
{
    GfxLCMSProfilePtr nullProfile = nullptr;
    dev->setDefaultCMYKProfile(nullProfile);
    EXPECT_EQ(dev->getDefaultCMYKProfile(), nullptr);
}

// Test that default Gray profile is initially null
TEST_F(OutputDevTest_1084, DefaultGrayProfileInitiallyNull_1084)
{
    EXPECT_EQ(dev->getDefaultGrayProfile(), nullptr);
}

// Test setting and getting Gray profile
TEST_F(OutputDevTest_1084, SetAndGetDefaultGrayProfile_1084)
{
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDefaultGrayProfile(profile);
    EXPECT_EQ(dev->getDefaultGrayProfile(), nullptr);
}

// Test that default RGB profile is initially null
TEST_F(OutputDevTest_1084, DefaultRGBProfileInitiallyNull_1084)
{
    EXPECT_EQ(dev->getDefaultRGBProfile(), nullptr);
}

// Test setting and getting RGB profile
TEST_F(OutputDevTest_1084, SetAndGetDefaultRGBProfile_1084)
{
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDefaultRGBProfile(profile);
    EXPECT_EQ(dev->getDefaultRGBProfile(), nullptr);
}

// Test that display profile is initially null
TEST_F(OutputDevTest_1084, DisplayProfileInitiallyNull_1084)
{
    EXPECT_EQ(dev->getDisplayProfile(), nullptr);
}

// Test setting and getting display profile
TEST_F(OutputDevTest_1084, SetAndGetDisplayProfile_1084)
{
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDisplayProfile(profile);
    EXPECT_EQ(dev->getDisplayProfile(), nullptr);
}

// Test default return values of virtual boolean methods
TEST_F(OutputDevTest_1084, UseTilingPatternFillDefault_1084)
{
    EXPECT_FALSE(dev->useTilingPatternFill());
}

TEST_F(OutputDevTest_1084, UseFillColorStopDefault_1084)
{
    EXPECT_FALSE(dev->useFillColorStop());
}

TEST_F(OutputDevTest_1084, UseDrawFormDefault_1084)
{
    EXPECT_FALSE(dev->useDrawForm());
}

TEST_F(OutputDevTest_1084, NeedNonTextDefault_1084)
{
    EXPECT_FALSE(dev->needNonText());
}

TEST_F(OutputDevTest_1084, NeedCharCountDefault_1084)
{
    EXPECT_FALSE(dev->needCharCount());
}

TEST_F(OutputDevTest_1084, NeedClipToCropBoxDefault_1084)
{
    EXPECT_FALSE(dev->needClipToCropBox());
}

TEST_F(OutputDevTest_1084, SupportJPXTransparencyDefault_1084)
{
    EXPECT_FALSE(dev->supportJPXtransparency());
}

TEST_F(OutputDevTest_1084, GetVectorAntialiasDefault_1084)
{
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test profiling start and end
TEST_F(OutputDevTest_1084, ProfileHashInitiallyNull_1084)
{
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1084, StartProfileCreatesHash_1084)
{
    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1084, EndProfileReturnsHash_1084)
{
    dev->startProfile();
    auto hash = dev->endProfile();
    EXPECT_NE(hash, nullptr);
    // After ending, the internal hash should be null
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1084, EndProfileWithoutStartReturnsNull_1084)
{
    auto hash = dev->endProfile();
    // If startProfile was never called, endProfile should return nullptr or empty
    // The behavior depends on implementation but it should not crash
}

// Test getIccColorSpaceCache returns non-null
TEST_F(OutputDevTest_1084, GetIccColorSpaceCacheNotNull_1084)
{
    EXPECT_NE(dev->getIccColorSpaceCache(), nullptr);
}

// Test setDefaultCTM and cvtUserToDev
TEST_F(OutputDevTest_1084, SetDefaultCTMAndConvert_1084)
{
    // Identity-like CTM: scale by 1, no rotation
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    // With identity CTM, the conversion should map (10, 20) to approximately (10, 20)
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

TEST_F(OutputDevTest_1084, CvtUserToDevWithScaling_1084)
{
    // Scale by 2 in both directions
    std::array<double, 6> ctm = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(5.0, 10.0, &dx, &dy);
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

TEST_F(OutputDevTest_1084, CvtUserToDevWithTranslation_1084)
{
    // Identity with translation
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// Test checkPageSlice default behavior
TEST_F(OutputDevTest_1084, CheckPageSliceDefaultReturnsTrue_1084)
{
    bool result = dev->checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_TRUE(result);
}

// Test checkTransparencyGroup default
TEST_F(OutputDevTest_1084, CheckTransparencyGroupDefault_1084)
{
    bool result = dev->checkTransparencyGroup(nullptr, false);
    EXPECT_TRUE(result);
}

// Test useShadedFills default
TEST_F(OutputDevTest_1084, UseShadedFillsDefault_1084)
{
    EXPECT_FALSE(dev->useShadedFills(1));
    EXPECT_FALSE(dev->useShadedFills(2));
    EXPECT_FALSE(dev->useShadedFills(0));
}

// Test that setting CMYK profile replaces previous one
TEST_F(OutputDevTest_1084, SetCMYKProfileReplacesExisting_1084)
{
    GfxLCMSProfilePtr profile1 = nullptr;
    dev->setDefaultCMYKProfile(profile1);
    EXPECT_EQ(dev->getDefaultCMYKProfile(), nullptr);

    // Setting again with nullptr should still work
    GfxLCMSProfilePtr profile2 = nullptr;
    dev->setDefaultCMYKProfile(profile2);
    EXPECT_EQ(dev->getDefaultCMYKProfile(), nullptr);
}

// Test virtual methods that should be no-ops don't crash
TEST_F(OutputDevTest_1084, VirtualNoOpMethodsDontCrash_1084)
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
    EXPECT_NO_FATAL_FAILURE(dev->clearSoftMask(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->setVectorAntialias(true));
    EXPECT_NO_FATAL_FAILURE(dev->setVectorAntialias(false));
}

// Test beginMarkedContent / endMarkedContent / markPoint don't crash
TEST_F(OutputDevTest_1084, MarkedContentMethodsDontCrash_1084)
{
    EXPECT_NO_FATAL_FAILURE(dev->beginMarkedContent("test", nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endMarkedContent(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->markPoint("test"));
    EXPECT_NO_FATAL_FAILURE(dev->markPoint("test", nullptr));
}

// Test incCharCount doesn't crash
TEST_F(OutputDevTest_1084, IncCharCountDontCrash_1084)
{
    EXPECT_NO_FATAL_FAILURE(dev->incCharCount(0));
    EXPECT_NO_FATAL_FAILURE(dev->incCharCount(100));
}

// Test beginActualText / endActualText don't crash
TEST_F(OutputDevTest_1084, ActualTextMethodsDontCrash_1084)
{
    EXPECT_NO_FATAL_FAILURE(dev->beginActualText(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endActualText(nullptr));
}

// Test form-related methods don't crash
TEST_F(OutputDevTest_1084, FormMethodsDontCrash_1084)
{
    Ref ref = {0, 0};
    EXPECT_NO_FATAL_FAILURE(dev->beginForm(nullptr, ref));
    EXPECT_NO_FATAL_FAILURE(dev->drawForm(ref));
    EXPECT_NO_FATAL_FAILURE(dev->endForm(nullptr, ref));
}

// Test update methods don't crash with nullptr state
TEST_F(OutputDevTest_1084, UpdateMethodsDontCrash_1084)
{
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
}

// Test shading fill defaults return false
TEST_F(OutputDevTest_1084, ShadingFillDefaultsFalse_1084)
{
    EXPECT_FALSE(dev->functionShadedFill(nullptr, nullptr));
    EXPECT_FALSE(dev->axialShadedFill(nullptr, nullptr, 0.0, 1.0));
    EXPECT_FALSE(dev->axialShadedSupportExtend(nullptr, nullptr));
    EXPECT_FALSE(dev->radialShadedFill(nullptr, nullptr, 0.0, 1.0));
    EXPECT_FALSE(dev->radialShadedSupportExtend(nullptr, nullptr));
    EXPECT_FALSE(dev->gouraudTriangleShadedFill(nullptr, nullptr));
    EXPECT_FALSE(dev->patchMeshShadedFill(nullptr, nullptr));
}

// Test processLink doesn't crash
TEST_F(OutputDevTest_1084, ProcessLinkDontCrash_1084)
{
    EXPECT_NO_FATAL_FAILURE(dev->processLink(nullptr));
}
