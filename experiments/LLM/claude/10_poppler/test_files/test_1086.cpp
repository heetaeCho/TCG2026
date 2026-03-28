#include <gtest/gtest.h>
#include <gmock/gmock.h>
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

class OutputDevTest_1086 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        dev = std::make_unique<TestOutputDev>();
    }

    void TearDown() override
    {
        dev.reset();
    }

    std::unique_ptr<TestOutputDev> dev;
};

// Test that getIccColorSpaceCache returns a non-null pointer
TEST_F(OutputDevTest_1086, GetIccColorSpaceCacheReturnsNonNull_1086)
{
    auto *cache = dev->getIccColorSpaceCache();
    ASSERT_NE(cache, nullptr);
}

// Test that getIccColorSpaceCache returns the same pointer on repeated calls
TEST_F(OutputDevTest_1086, GetIccColorSpaceCacheReturnsSamePointer_1086)
{
    auto *cache1 = dev->getIccColorSpaceCache();
    auto *cache2 = dev->getIccColorSpaceCache();
    EXPECT_EQ(cache1, cache2);
}

// Test default virtual method return values
TEST_F(OutputDevTest_1086, DefaultUseTilingPatternFillReturnsFalse_1086)
{
    EXPECT_FALSE(dev->useTilingPatternFill());
}

TEST_F(OutputDevTest_1086, DefaultUseShadedFillsReturnsFalse_1086)
{
    EXPECT_FALSE(dev->useShadedFills(0));
    EXPECT_FALSE(dev->useShadedFills(1));
    EXPECT_FALSE(dev->useShadedFills(2));
}

TEST_F(OutputDevTest_1086, DefaultUseFillColorStopReturnsFalse_1086)
{
    EXPECT_FALSE(dev->useFillColorStop());
}

TEST_F(OutputDevTest_1086, DefaultUseDrawFormReturnsFalse_1086)
{
    EXPECT_FALSE(dev->useDrawForm());
}

TEST_F(OutputDevTest_1086, DefaultNeedNonTextReturnsFalse_1086)
{
    EXPECT_FALSE(dev->needNonText());
}

TEST_F(OutputDevTest_1086, DefaultNeedCharCountReturnsFalse_1086)
{
    EXPECT_FALSE(dev->needCharCount());
}

TEST_F(OutputDevTest_1086, DefaultNeedClipToCropBoxReturnsFalse_1086)
{
    EXPECT_FALSE(dev->needClipToCropBox());
}

TEST_F(OutputDevTest_1086, DefaultSupportJPXtransparencyReturnsFalse_1086)
{
    EXPECT_FALSE(dev->supportJPXtransparency());
}

TEST_F(OutputDevTest_1086, DefaultGetVectorAntialiasReturnsFalse_1086)
{
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test that setVectorAntialias doesn't crash (default implementation is no-op)
TEST_F(OutputDevTest_1086, SetVectorAntialiasDoesNotCrash_1086)
{
    EXPECT_NO_FATAL_FAILURE(dev->setVectorAntialias(true));
    EXPECT_NO_FATAL_FAILURE(dev->setVectorAntialias(false));
}

// Test profile hash starts as null before startProfile
TEST_F(OutputDevTest_1086, GetProfileHashInitiallyNull_1086)
{
    auto *hash = dev->getProfileHash();
    EXPECT_EQ(hash, nullptr);
}

// Test startProfile and endProfile
TEST_F(OutputDevTest_1086, StartProfileCreatesProfileHash_1086)
{
    dev->startProfile();
    auto *hash = dev->getProfileHash();
    EXPECT_NE(hash, nullptr);
}

TEST_F(OutputDevTest_1086, EndProfileReturnsProfileHash_1086)
{
    dev->startProfile();
    auto result = dev->endProfile();
    EXPECT_NE(result, nullptr);
}

TEST_F(OutputDevTest_1086, EndProfileWithoutStartReturnsNull_1086)
{
    auto result = dev->endProfile();
    // When no profiling was started, endProfile should return nullptr or empty
    // The behavior depends on implementation, but we test it doesn't crash
    // and the pointer is null (since profileHash was never initialized)
    EXPECT_EQ(result, nullptr);
}

TEST_F(OutputDevTest_1086, AfterEndProfileGetProfileHashReturnsNull_1086)
{
    dev->startProfile();
    auto result = dev->endProfile();
    auto *hash = dev->getProfileHash();
    EXPECT_EQ(hash, nullptr);
}

// Test display profile setter/getter
TEST_F(OutputDevTest_1086, DefaultDisplayProfileIsNull_1086)
{
    auto profile = dev->getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test default gray profile setter/getter
TEST_F(OutputDevTest_1086, DefaultGrayProfileIsNull_1086)
{
    auto profile = dev->getDefaultGrayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test default RGB profile setter/getter
TEST_F(OutputDevTest_1086, DefaultRGBProfileIsNull_1086)
{
    auto profile = dev->getDefaultRGBProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test default CMYK profile setter/getter
TEST_F(OutputDevTest_1086, DefaultCMYKProfileIsNull_1086)
{
    auto profile = dev->getDefaultCMYKProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setDefaultCTM doesn't crash
TEST_F(OutputDevTest_1086, SetDefaultCTMDoesNotCrash_1086)
{
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_NO_FATAL_FAILURE(dev->setDefaultCTM(ctm));
}

// Test cvtUserToDev with identity CTM
TEST_F(OutputDevTest_1086, CvtUserToDevWithIdentityCTM_1086)
{
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

// Test cvtUserToDev with a scaling CTM
TEST_F(OutputDevTest_1086, CvtUserToDevWithScalingCTM_1086)
{
    std::array<double, 6> ctm = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(5.0, 10.0, &dx, &dy);
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

// Test cvtUserToDev with translation CTM
TEST_F(OutputDevTest_1086, CvtUserToDevWithTranslationCTM_1086)
{
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// Test cvtUserToDev with zero coordinates
TEST_F(OutputDevTest_1086, CvtUserToDevZeroCoordinates_1086)
{
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = -1, dy = -1;
    dev->cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 0);
    EXPECT_EQ(dy, 0);
}

// Test checkPageSlice default returns true
TEST_F(OutputDevTest_1086, CheckPageSliceDefaultReturnsTrue_1086)
{
    bool result = dev->checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_TRUE(result);
}

// Test checkTransparencyGroup default returns true
TEST_F(OutputDevTest_1086, CheckTransparencyGroupDefaultReturnsTrue_1086)
{
    bool result = dev->checkTransparencyGroup(nullptr, false);
    EXPECT_TRUE(result);
}

// Test that various virtual no-op methods don't crash
TEST_F(OutputDevTest_1086, NoOpMethodsDoNotCrash_1086)
{
    EXPECT_NO_FATAL_FAILURE(dev->startPage(1, nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endPage());
    EXPECT_NO_FATAL_FAILURE(dev->dump());
    EXPECT_NO_FATAL_FAILURE(dev->saveState(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->restoreState(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateAll(nullptr));
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
    EXPECT_NO_FATAL_FAILURE(dev->stroke(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->fill(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->eoFill(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->clip(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->eoClip(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->clipToStrokePath(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->beginStringOp(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endStringOp(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->beginString(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endString(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endType3Char(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->beginTextObject(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endTextObject(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->incCharCount(0));
    EXPECT_NO_FATAL_FAILURE(dev->beginActualText(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endActualText(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endMarkedContent(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->beginMarkedContent("test", nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->markPoint("test"));
    EXPECT_NO_FATAL_FAILURE(dev->markPoint("test", nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->processLink(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->clearSoftMask(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endTransparencyGroup(nullptr));
}

// Test beginType3Char default returns false
TEST_F(OutputDevTest_1086, BeginType3CharDefaultReturnsFalse_1086)
{
    bool result = dev->beginType3Char(nullptr, 0, 0, 0, 0, 0, nullptr, 0);
    EXPECT_FALSE(result);
}

// Test shaded fill default returns false
TEST_F(OutputDevTest_1086, FunctionShadedFillDefaultReturnsFalse_1086)
{
    EXPECT_FALSE(dev->functionShadedFill(nullptr, nullptr));
}

TEST_F(OutputDevTest_1086, AxialShadedFillDefaultReturnsFalse_1086)
{
    EXPECT_FALSE(dev->axialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

TEST_F(OutputDevTest_1086, AxialShadedSupportExtendDefaultReturnsFalse_1086)
{
    EXPECT_FALSE(dev->axialShadedSupportExtend(nullptr, nullptr));
}

TEST_F(OutputDevTest_1086, RadialShadedFillDefaultReturnsFalse_1086)
{
    EXPECT_FALSE(dev->radialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

TEST_F(OutputDevTest_1086, RadialShadedSupportExtendDefaultReturnsFalse_1086)
{
    EXPECT_FALSE(dev->radialShadedSupportExtend(nullptr, nullptr));
}

TEST_F(OutputDevTest_1086, GouraudTriangleShadedFillDefaultReturnsFalse_1086)
{
    EXPECT_FALSE(dev->gouraudTriangleShadedFill(nullptr, nullptr));
}

TEST_F(OutputDevTest_1086, PatchMeshShadedFillDefaultReturnsFalse_1086)
{
    EXPECT_FALSE(dev->patchMeshShadedFill(nullptr, nullptr));
}

// Test tilingPatternFill default returns false
TEST_F(OutputDevTest_1086, TilingPatternFillDefaultReturnsFalse_1086)
{
    std::array<double, 6> mat = {1, 0, 0, 1, 0, 0};
    EXPECT_FALSE(dev->tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 1, 1, 1.0, 1.0));
}

// Test multiple instances have independent caches
TEST_F(OutputDevTest_1086, MultipleInstancesHaveIndependentCaches_1086)
{
    TestOutputDev dev2;
    auto *cache1 = dev->getIccColorSpaceCache();
    auto *cache2 = dev2.getIccColorSpaceCache();
    EXPECT_NE(cache1, cache2);
}

// Test startProfile followed by multiple endProfile calls
TEST_F(OutputDevTest_1086, MultipleEndProfileAfterSingleStart_1086)
{
    dev->startProfile();
    auto result1 = dev->endProfile();
    EXPECT_NE(result1, nullptr);

    // Second endProfile without another startProfile
    auto result2 = dev->endProfile();
    EXPECT_EQ(result2, nullptr);
}

// Test type3D0 and type3D1 don't crash
TEST_F(OutputDevTest_1086, Type3DMethodsDoNotCrash_1086)
{
    EXPECT_NO_FATAL_FAILURE(dev->type3D0(nullptr, 0.0, 0.0));
    EXPECT_NO_FATAL_FAILURE(dev->type3D1(nullptr, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0));
}

// Test beginForm/drawForm/endForm don't crash
TEST_F(OutputDevTest_1086, FormMethodsDoNotCrash_1086)
{
    Ref ref = {0, 0};
    EXPECT_NO_FATAL_FAILURE(dev->beginForm(nullptr, ref));
    EXPECT_NO_FATAL_FAILURE(dev->drawForm(ref));
    EXPECT_NO_FATAL_FAILURE(dev->endForm(nullptr, ref));
}

// Test set/get display profile with null
TEST_F(OutputDevTest_1086, SetDisplayProfileNull_1086)
{
    GfxLCMSProfilePtr nullProfile;
    dev->setDisplayProfile(nullProfile);
    auto result = dev->getDisplayProfile();
    EXPECT_EQ(result, nullptr);
}

// Test set/get default gray profile with null
TEST_F(OutputDevTest_1086, SetDefaultGrayProfileNull_1086)
{
    GfxLCMSProfilePtr nullProfile;
    dev->setDefaultGrayProfile(nullProfile);
    auto result = dev->getDefaultGrayProfile();
    EXPECT_EQ(result, nullptr);
}

// Test set/get default RGB profile with null
TEST_F(OutputDevTest_1086, SetDefaultRGBProfileNull_1086)
{
    GfxLCMSProfilePtr nullProfile;
    dev->setDefaultRGBProfile(nullProfile);
    auto result = dev->getDefaultRGBProfile();
    EXPECT_EQ(result, nullptr);
}

// Test set/get default CMYK profile with null
TEST_F(OutputDevTest_1086, SetDefaultCMYKProfileNull_1086)
{
    GfxLCMSProfilePtr nullProfile;
    dev->setDefaultCMYKProfile(nullProfile);
    auto result = dev->getDefaultCMYKProfile();
    EXPECT_EQ(result, nullptr);
}
