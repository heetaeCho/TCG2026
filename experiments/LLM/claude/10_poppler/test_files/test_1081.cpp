#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h"

// A concrete subclass of OutputDev for testing purposes, since OutputDev has pure virtual methods
class TestOutputDev : public OutputDev {
public:
    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
};

class OutputDevTest_1081 : public ::testing::Test {
protected:
    void SetUp() override {
        dev = std::make_unique<TestOutputDev>();
    }

    std::unique_ptr<TestOutputDev> dev;
};

// Test default construction - profiles should be null/empty by default
TEST_F(OutputDevTest_1081, DefaultGrayProfileIsNullInitially_1081) {
    GfxLCMSProfilePtr profile = dev->getDefaultGrayProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1081, DefaultRGBProfileIsNullInitially_1081) {
    GfxLCMSProfilePtr profile = dev->getDefaultRGBProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1081, DefaultCMYKProfileIsNullInitially_1081) {
    GfxLCMSProfilePtr profile = dev->getDefaultCMYKProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1081, DisplayProfileIsNullInitially_1081) {
    GfxLCMSProfilePtr profile = dev->getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting and getting display profile
TEST_F(OutputDevTest_1081, SetAndGetDisplayProfile_1081) {
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDisplayProfile(profile);
    EXPECT_EQ(dev->getDisplayProfile(), nullptr);
}

// Test setting and getting default gray profile
TEST_F(OutputDevTest_1081, SetAndGetDefaultGrayProfile_1081) {
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDefaultGrayProfile(profile);
    EXPECT_EQ(dev->getDefaultGrayProfile(), nullptr);
}

// Test setting and getting default RGB profile
TEST_F(OutputDevTest_1081, SetAndGetDefaultRGBProfile_1081) {
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDefaultRGBProfile(profile);
    EXPECT_EQ(dev->getDefaultRGBProfile(), nullptr);
}

// Test setting and getting default CMYK profile
TEST_F(OutputDevTest_1081, SetAndGetDefaultCMYKProfile_1081) {
    GfxLCMSProfilePtr profile = nullptr;
    dev->setDefaultCMYKProfile(profile);
    EXPECT_EQ(dev->getDefaultCMYKProfile(), nullptr);
}

// Test default virtual method return values
TEST_F(OutputDevTest_1081, UpsideDownReturnsFalse_1081) {
    EXPECT_FALSE(dev->upsideDown());
}

TEST_F(OutputDevTest_1081, UseDrawCharReturnsFalse_1081) {
    EXPECT_FALSE(dev->useDrawChar());
}

TEST_F(OutputDevTest_1081, InterpretType3CharsReturnsFalse_1081) {
    EXPECT_FALSE(dev->interpretType3Chars());
}

TEST_F(OutputDevTest_1081, UseTilingPatternFillDefaultReturnValue_1081) {
    EXPECT_FALSE(dev->useTilingPatternFill());
}

TEST_F(OutputDevTest_1081, UseShadedFillsDefaultReturnValue_1081) {
    EXPECT_FALSE(dev->useShadedFills(0));
    EXPECT_FALSE(dev->useShadedFills(1));
    EXPECT_FALSE(dev->useShadedFills(2));
}

TEST_F(OutputDevTest_1081, UseFillColorStopDefaultReturnValue_1081) {
    EXPECT_FALSE(dev->useFillColorStop());
}

TEST_F(OutputDevTest_1081, UseDrawFormDefaultReturnValue_1081) {
    EXPECT_FALSE(dev->useDrawForm());
}

TEST_F(OutputDevTest_1081, NeedNonTextDefaultReturnValue_1081) {
    EXPECT_TRUE(dev->needNonText());
}

TEST_F(OutputDevTest_1081, NeedCharCountDefaultReturnValue_1081) {
    EXPECT_FALSE(dev->needCharCount());
}

TEST_F(OutputDevTest_1081, NeedClipToCropBoxDefaultReturnValue_1081) {
    EXPECT_FALSE(dev->needClipToCropBox());
}

TEST_F(OutputDevTest_1081, SupportJPXTransparencyDefaultReturnValue_1081) {
    EXPECT_FALSE(dev->supportJPXtransparency());
}

TEST_F(OutputDevTest_1081, GetVectorAntialiasDefaultReturnValue_1081) {
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test profile hash functionality
TEST_F(OutputDevTest_1081, GetProfileHashIsNullBeforeStartProfile_1081) {
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1081, StartProfileEnablesProfileHash_1081) {
    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1081, EndProfileReturnsProfileHash_1081) {
    dev->startProfile();
    auto profileHash = dev->endProfile();
    EXPECT_NE(profileHash, nullptr);
}

TEST_F(OutputDevTest_1081, EndProfileWithoutStartReturnsNull_1081) {
    auto profileHash = dev->endProfile();
    EXPECT_EQ(profileHash, nullptr);
}

TEST_F(OutputDevTest_1081, AfterEndProfileGetProfileHashReturnsNull_1081) {
    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
    auto profileHash = dev->endProfile();
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

// Test ICC color space cache access
TEST_F(OutputDevTest_1081, GetIccColorSpaceCacheReturnsNonNull_1081) {
    EXPECT_NE(dev->getIccColorSpaceCache(), nullptr);
}

// Test setDefaultCTM and cvtUserToDev
TEST_F(OutputDevTest_1081, SetDefaultCTMAndCvtUserToDev_1081) {
    // Identity matrix
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

TEST_F(OutputDevTest_1081, CvtUserToDevWithTranslation_1081) {
    // Translation matrix
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    EXPECT_EQ(dx, 110);
    EXPECT_EQ(dy, 220);
}

TEST_F(OutputDevTest_1081, CvtUserToDevWithScaling_1081) {
    // Scaling matrix (2x)
    std::array<double, 6> ctm = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    EXPECT_EQ(dx, 20);
    EXPECT_EQ(dy, 40);
}

TEST_F(OutputDevTest_1081, CvtUserToDevWithZeroCoordinates_1081) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 0);
    EXPECT_EQ(dy, 0);
}

// Test checkPageSlice default behavior
TEST_F(OutputDevTest_1081, CheckPageSliceDefaultReturnsTrue_1081) {
    bool result = dev->checkPageSlice(nullptr, 72.0, 72.0, 0, true, true, 0, 0, 100, 100, false);
    EXPECT_TRUE(result);
}

// Test checkTransparencyGroup default behavior
TEST_F(OutputDevTest_1081, CheckTransparencyGroupDefaultReturnsFalse_1081) {
    bool result = dev->checkTransparencyGroup(nullptr, false);
    EXPECT_TRUE(result);
}

// Test setVectorAntialias (may be a no-op for base class but should not crash)
TEST_F(OutputDevTest_1081, SetVectorAntialiasDoesNotCrash_1081) {
    EXPECT_NO_FATAL_FAILURE(dev->setVectorAntialias(true));
    EXPECT_NO_FATAL_FAILURE(dev->setVectorAntialias(false));
}

// Test that various virtual methods can be called without crashing (no-op defaults)
TEST_F(OutputDevTest_1081, VirtualMethodsDoNotCrash_1081) {
    EXPECT_NO_FATAL_FAILURE(dev->startPage(1, nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endPage());
    EXPECT_NO_FATAL_FAILURE(dev->dump());
    EXPECT_NO_FATAL_FAILURE(dev->saveState(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->restoreState(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateAll(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->updateCTM(nullptr, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0));
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

TEST_F(OutputDevTest_1081, DrawingMethodsDoNotCrash_1081) {
    EXPECT_NO_FATAL_FAILURE(dev->stroke(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->fill(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->eoFill(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->clip(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->eoClip(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->clipToStrokePath(nullptr));
}

TEST_F(OutputDevTest_1081, StringOperationsDoNotCrash_1081) {
    EXPECT_NO_FATAL_FAILURE(dev->beginStringOp(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endStringOp(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->beginString(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endString(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endType3Char(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->beginTextObject(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endTextObject(nullptr));
}

TEST_F(OutputDevTest_1081, MarkedContentMethodsDoNotCrash_1081) {
    EXPECT_NO_FATAL_FAILURE(dev->endMarkedContent(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->beginMarkedContent("test", nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->markPoint("test"));
    EXPECT_NO_FATAL_FAILURE(dev->markPoint("test", nullptr));
}

TEST_F(OutputDevTest_1081, TransparencyGroupMethodsDoNotCrash_1081) {
    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};
    EXPECT_NO_FATAL_FAILURE(dev->beginTransparencyGroup(nullptr, bbox, nullptr, false, false, false));
    EXPECT_NO_FATAL_FAILURE(dev->endTransparencyGroup(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->paintTransparencyGroup(nullptr, bbox));
    EXPECT_NO_FATAL_FAILURE(dev->clearSoftMask(nullptr));
}

TEST_F(OutputDevTest_1081, ShadedFillDefaultReturnsFalse_1081) {
    EXPECT_FALSE(dev->functionShadedFill(nullptr, nullptr));
    EXPECT_FALSE(dev->axialShadedFill(nullptr, nullptr, 0.0, 1.0));
    EXPECT_FALSE(dev->axialShadedSupportExtend(nullptr, nullptr));
    EXPECT_FALSE(dev->radialShadedFill(nullptr, nullptr, 0.0, 1.0));
    EXPECT_FALSE(dev->radialShadedSupportExtend(nullptr, nullptr));
    EXPECT_FALSE(dev->gouraudTriangleShadedFill(nullptr, nullptr));
    EXPECT_FALSE(dev->patchMeshShadedFill(nullptr, nullptr));
}

TEST_F(OutputDevTest_1081, TilingPatternFillDefaultReturnsFalse_1081) {
    std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_FALSE(dev->tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 100, 100, 1.0, 1.0));
}

TEST_F(OutputDevTest_1081, FormMethodsDoNotCrash_1081) {
    Ref ref = {0, 0};
    EXPECT_NO_FATAL_FAILURE(dev->beginForm(nullptr, ref));
    EXPECT_NO_FATAL_FAILURE(dev->drawForm(ref));
    EXPECT_NO_FATAL_FAILURE(dev->endForm(nullptr, ref));
}

TEST_F(OutputDevTest_1081, Type3MethodsDoNotCrash_1081) {
    EXPECT_NO_FATAL_FAILURE(dev->type3D0(nullptr, 0.0, 0.0));
    EXPECT_NO_FATAL_FAILURE(dev->type3D1(nullptr, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0));
}

TEST_F(OutputDevTest_1081, ActualTextMethodsDoNotCrash_1081) {
    EXPECT_NO_FATAL_FAILURE(dev->beginActualText(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->endActualText(nullptr));
}

TEST_F(OutputDevTest_1081, IncCharCountDoesNotCrash_1081) {
    EXPECT_NO_FATAL_FAILURE(dev->incCharCount(0));
    EXPECT_NO_FATAL_FAILURE(dev->incCharCount(100));
}

TEST_F(OutputDevTest_1081, ProcessLinkDoesNotCrash_1081) {
    EXPECT_NO_FATAL_FAILURE(dev->processLink(nullptr));
}

// Test multiple start/end profile cycles
TEST_F(OutputDevTest_1081, MultipleProfileCycles_1081) {
    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
    auto hash1 = dev->endProfile();
    EXPECT_NE(hash1, nullptr);
    EXPECT_EQ(dev->getProfileHash(), nullptr);

    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
    auto hash2 = dev->endProfile();
    EXPECT_NE(hash2, nullptr);
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

// Test beginType3Char default return value
TEST_F(OutputDevTest_1081, BeginType3CharDefaultReturnsFalse_1081) {
    bool result = dev->beginType3Char(nullptr, 0.0, 0.0, 0.0, 0.0, 0, nullptr, 0);
    EXPECT_FALSE(result);
}
