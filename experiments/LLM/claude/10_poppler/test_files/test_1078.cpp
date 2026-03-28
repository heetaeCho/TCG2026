#include <gtest/gtest.h>
#include "OutputDev.h"

// Concrete subclass for testing since OutputDev has pure virtual methods
class TestOutputDev : public OutputDev
{
public:
    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
};

class OutputDevTest_1078 : public ::testing::Test
{
protected:
    void SetUp() override { dev = std::make_unique<TestOutputDev>(); }

    std::unique_ptr<TestOutputDev> dev;
};

// Test that default display profile is null/empty
TEST_F(OutputDevTest_1078, DefaultDisplayProfileIsNull_1078)
{
    GfxLCMSProfilePtr profile = dev->getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting display profile
TEST_F(OutputDevTest_1078, SetAndGetDisplayProfile_1078)
{
#ifdef USE_CMS
    // If CMS is available, we can create a profile
    cmsHPROFILE h = cmsCreate_sRGBProfile();
    GfxLCMSProfilePtr profile = std::make_shared<GfxLCMSProfileData>(h);
    dev->setDisplayProfile(profile);
    EXPECT_EQ(dev->getDisplayProfile(), profile);
#else
    // Without CMS, GfxLCMSProfilePtr is likely nullptr-like
    GfxLCMSProfilePtr profile;
    dev->setDisplayProfile(profile);
    EXPECT_EQ(dev->getDisplayProfile(), nullptr);
#endif
}

// Test setting display profile to null
TEST_F(OutputDevTest_1078, SetDisplayProfileToNull_1078)
{
    GfxLCMSProfilePtr nullProfile;
    dev->setDisplayProfile(nullProfile);
    EXPECT_EQ(dev->getDisplayProfile(), nullptr);
}

// Test default gray profile is null
TEST_F(OutputDevTest_1078, DefaultGrayProfileIsNull_1078)
{
    EXPECT_EQ(dev->getDefaultGrayProfile(), nullptr);
}

// Test set and get default gray profile
TEST_F(OutputDevTest_1078, SetAndGetDefaultGrayProfile_1078)
{
    GfxLCMSProfilePtr profile;
    dev->setDefaultGrayProfile(profile);
    EXPECT_EQ(dev->getDefaultGrayProfile(), nullptr);
}

// Test default RGB profile is null
TEST_F(OutputDevTest_1078, DefaultRGBProfileIsNull_1078)
{
    EXPECT_EQ(dev->getDefaultRGBProfile(), nullptr);
}

// Test set and get default RGB profile
TEST_F(OutputDevTest_1078, SetAndGetDefaultRGBProfile_1078)
{
    GfxLCMSProfilePtr profile;
    dev->setDefaultRGBProfile(profile);
    EXPECT_EQ(dev->getDefaultRGBProfile(), nullptr);
}

// Test default CMYK profile is null
TEST_F(OutputDevTest_1078, DefaultCMYKProfileIsNull_1078)
{
    EXPECT_EQ(dev->getDefaultCMYKProfile(), nullptr);
}

// Test set and get default CMYK profile
TEST_F(OutputDevTest_1078, SetAndGetDefaultCMYKProfile_1078)
{
    GfxLCMSProfilePtr profile;
    dev->setDefaultCMYKProfile(profile);
    EXPECT_EQ(dev->getDefaultCMYKProfile(), nullptr);
}

// Test that getIccColorSpaceCache returns non-null
TEST_F(OutputDevTest_1078, GetIccColorSpaceCacheNotNull_1078)
{
    auto *cache = dev->getIccColorSpaceCache();
    EXPECT_NE(cache, nullptr);
}

// Test default virtual method return values
TEST_F(OutputDevTest_1078, UpsideDownReturnsFalse_1078)
{
    EXPECT_FALSE(dev->upsideDown());
}

TEST_F(OutputDevTest_1078, UseDrawCharReturnsFalse_1078)
{
    EXPECT_FALSE(dev->useDrawChar());
}

TEST_F(OutputDevTest_1078, InterpretType3CharsReturnsFalse_1078)
{
    EXPECT_FALSE(dev->interpretType3Chars());
}

TEST_F(OutputDevTest_1078, UseTilingPatternFillDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->useTilingPatternFill());
}

TEST_F(OutputDevTest_1078, UseShadedFillsDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->useShadedFills(0));
    EXPECT_FALSE(dev->useShadedFills(1));
}

TEST_F(OutputDevTest_1078, UseFillColorStopDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->useFillColorStop());
}

TEST_F(OutputDevTest_1078, UseDrawFormDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->useDrawForm());
}

TEST_F(OutputDevTest_1078, NeedNonTextDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->needNonText());
}

TEST_F(OutputDevTest_1078, NeedCharCountDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->needCharCount());
}

TEST_F(OutputDevTest_1078, NeedClipToCropBoxDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->needClipToCropBox());
}

TEST_F(OutputDevTest_1078, GetVectorAntialiasDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test profiling: startProfile / endProfile
TEST_F(OutputDevTest_1078, ProfileHashInitiallyNull_1078)
{
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1078, StartProfileCreatesProfileHash_1078)
{
    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1078, EndProfileReturnsAndClearsProfileHash_1078)
{
    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
    auto result = dev->endProfile();
    EXPECT_NE(result, nullptr);
    // After endProfile, the internal hash should be gone
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1078, EndProfileWithoutStartReturnsNull_1078)
{
    auto result = dev->endProfile();
    // No startProfile was called, so result should be null
    EXPECT_EQ(result, nullptr);
}

// Test setDefaultCTM and cvtUserToDev
TEST_F(OutputDevTest_1078, SetDefaultCTMAndConvert_1078)
{
    // Identity-like CTM
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    // With identity CTM, the conversion should map (10, 20) to approximately (10, 20)
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

TEST_F(OutputDevTest_1078, CvtUserToDevWithScaling_1078)
{
    // CTM that scales by 2x
    std::array<double, 6> ctm = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(5.0, 10.0, &dx, &dy);
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

TEST_F(OutputDevTest_1078, CvtUserToDevWithTranslation_1078)
{
    // CTM with translation
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// Test checkPageSlice default behavior
TEST_F(OutputDevTest_1078, CheckPageSliceDefaultReturnsTrue_1078)
{
    bool result = dev->checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false);
    EXPECT_TRUE(result);
}

// Test that setting display profile overwrites previous one
TEST_F(OutputDevTest_1078, SetDisplayProfileOverwritesPrevious_1078)
{
    GfxLCMSProfilePtr profile1;
    GfxLCMSProfilePtr profile2;
    dev->setDisplayProfile(profile1);
    EXPECT_EQ(dev->getDisplayProfile(), profile1);
    dev->setDisplayProfile(profile2);
    EXPECT_EQ(dev->getDisplayProfile(), profile2);
}

// Test checkTransparencyGroup default
TEST_F(OutputDevTest_1078, CheckTransparencyGroupDefaultReturnsTrue_1078)
{
    bool result = dev->checkTransparencyGroup(nullptr, false);
    EXPECT_TRUE(result);
}

// Test supportJPXtransparency default
TEST_F(OutputDevTest_1078, SupportJPXTransparencyDefault_1078)
{
    // Default implementation likely returns false
    // We just verify it doesn't crash
    bool result = dev->supportJPXtransparency();
    // Not asserting specific value since we treat as black box, but verify it returns a bool
    (void)result;
}

// Test setVectorAntialias doesn't crash
TEST_F(OutputDevTest_1078, SetVectorAntialiasNoCrash_1078)
{
    EXPECT_NO_THROW(dev->setVectorAntialias(true));
    EXPECT_NO_THROW(dev->setVectorAntialias(false));
}

// Test various virtual methods don't crash when called with nullptr
TEST_F(OutputDevTest_1078, VirtualMethodsDoNotCrashWithNull_1078)
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
}

// Test update methods don't crash
TEST_F(OutputDevTest_1078, UpdateMethodsDoNotCrash_1078)
{
    EXPECT_NO_THROW(dev->updateLineDash(nullptr));
    EXPECT_NO_THROW(dev->updateFlatness(nullptr));
    EXPECT_NO_THROW(dev->updateLineJoin(nullptr));
    EXPECT_NO_THROW(dev->updateLineCap(nullptr));
    EXPECT_NO_THROW(dev->updateMiterLimit(nullptr));
    EXPECT_NO_THROW(dev->updateLineWidth(nullptr));
    EXPECT_NO_THROW(dev->updateStrokeAdjust(nullptr));
    EXPECT_NO_THROW(dev->updateAlphaIsShape(nullptr));
    EXPECT_NO_THROW(dev->updateTextKnockout(nullptr));
    EXPECT_NO_THROW(dev->updateFillColorSpace(nullptr));
    EXPECT_NO_THROW(dev->updateStrokeColorSpace(nullptr));
    EXPECT_NO_THROW(dev->updateFillColor(nullptr));
    EXPECT_NO_THROW(dev->updateStrokeColor(nullptr));
    EXPECT_NO_THROW(dev->updateBlendMode(nullptr));
    EXPECT_NO_THROW(dev->updateFillOpacity(nullptr));
    EXPECT_NO_THROW(dev->updateStrokeOpacity(nullptr));
    EXPECT_NO_THROW(dev->updateFillOverprint(nullptr));
    EXPECT_NO_THROW(dev->updateStrokeOverprint(nullptr));
    EXPECT_NO_THROW(dev->updateOverprintMode(nullptr));
    EXPECT_NO_THROW(dev->updateTransfer(nullptr));
    EXPECT_NO_THROW(dev->updateFont(nullptr));
    EXPECT_NO_THROW(dev->updateTextMat(nullptr));
    EXPECT_NO_THROW(dev->updateCharSpace(nullptr));
    EXPECT_NO_THROW(dev->updateRender(nullptr));
    EXPECT_NO_THROW(dev->updateRise(nullptr));
    EXPECT_NO_THROW(dev->updateWordSpace(nullptr));
    EXPECT_NO_THROW(dev->updateHorizScaling(nullptr));
    EXPECT_NO_THROW(dev->updateTextPos(nullptr));
    EXPECT_NO_THROW(dev->updateTextShift(nullptr, 0.0));
}

// Test type3D0 and type3D1 don't crash
TEST_F(OutputDevTest_1078, Type3MethodsDoNotCrash_1078)
{
    EXPECT_NO_THROW(dev->type3D0(nullptr, 1.0, 2.0));
    EXPECT_NO_THROW(dev->type3D1(nullptr, 1.0, 2.0, 0.0, 0.0, 10.0, 10.0));
}

// Test markPoint doesn't crash
TEST_F(OutputDevTest_1078, MarkPointDoesNotCrash_1078)
{
    EXPECT_NO_THROW(dev->markPoint("test"));
    EXPECT_NO_THROW(dev->markPoint("test", nullptr));
}

// Test beginMarkedContent / endMarkedContent don't crash
TEST_F(OutputDevTest_1078, MarkedContentDoesNotCrash_1078)
{
    EXPECT_NO_THROW(dev->beginMarkedContent("test", nullptr));
    EXPECT_NO_THROW(dev->endMarkedContent(nullptr));
}

// Test shaded fill defaults return false
TEST_F(OutputDevTest_1078, FunctionShadedFillDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->functionShadedFill(nullptr, nullptr));
}

TEST_F(OutputDevTest_1078, AxialShadedFillDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->axialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

TEST_F(OutputDevTest_1078, AxialShadedSupportExtendDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->axialShadedSupportExtend(nullptr, nullptr));
}

TEST_F(OutputDevTest_1078, RadialShadedFillDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->radialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

TEST_F(OutputDevTest_1078, RadialShadedSupportExtendDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->radialShadedSupportExtend(nullptr, nullptr));
}

TEST_F(OutputDevTest_1078, GouraudTriangleShadedFillDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->gouraudTriangleShadedFill(nullptr, nullptr));
}

TEST_F(OutputDevTest_1078, PatchMeshShadedFillDefaultReturnsFalse_1078)
{
    EXPECT_FALSE(dev->patchMeshShadedFill(nullptr, nullptr));
}
