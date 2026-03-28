#include <gtest/gtest.h>
#include "OutputDev.h"

// A concrete subclass for testing the base OutputDev defaults
class TestOutputDev : public OutputDev {
public:
    // OutputDev requires these pure virtual methods to be implemented
    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
};

class OutputDevTest_1077 : public ::testing::Test {
protected:
    void SetUp() override {
        dev = std::make_unique<TestOutputDev>();
    }

    std::unique_ptr<TestOutputDev> dev;
};

// Test default return value of getVectorAntialias
TEST_F(OutputDevTest_1077, GetVectorAntialias_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test useTilingPatternFill default
TEST_F(OutputDevTest_1077, UseTilingPatternFill_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->useTilingPatternFill());
}

// Test useShadedFills default with various types
TEST_F(OutputDevTest_1077, UseShadedFills_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->useShadedFills(0));
    EXPECT_FALSE(dev->useShadedFills(1));
    EXPECT_FALSE(dev->useShadedFills(7));
}

// Test useFillColorStop default
TEST_F(OutputDevTest_1077, UseFillColorStop_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->useFillColorStop());
}

// Test useDrawForm default
TEST_F(OutputDevTest_1077, UseDrawForm_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->useDrawForm());
}

// Test needNonText default
TEST_F(OutputDevTest_1077, NeedNonText_DefaultReturnsTrue_1077) {
    EXPECT_TRUE(dev->needNonText());
}

// Test needCharCount default
TEST_F(OutputDevTest_1077, NeedCharCount_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->needCharCount());
}

// Test needClipToCropBox default
TEST_F(OutputDevTest_1077, NeedClipToCropBox_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->needClipToCropBox());
}

// Test supportJPXtransparency default
TEST_F(OutputDevTest_1077, SupportJPXtransparency_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->supportJPXtransparency());
}

// Test checkPageSlice default returns true
TEST_F(OutputDevTest_1077, CheckPageSlice_DefaultReturnsTrue_1077) {
    EXPECT_TRUE(dev->checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false));
}

// Test checkTransparencyGroup default
TEST_F(OutputDevTest_1077, CheckTransparencyGroup_DefaultReturnsTrue_1077) {
    EXPECT_TRUE(dev->checkTransparencyGroup(nullptr, false));
}

// Test profile hash is initially null
TEST_F(OutputDevTest_1077, GetProfileHash_InitiallyNull_1077) {
    EXPECT_EQ(dev->getProfileHash(), nullptr);
}

// Test startProfile and endProfile
TEST_F(OutputDevTest_1077, StartAndEndProfile_1077) {
    dev->startProfile();
    // After starting profile, getProfileHash should be non-null
    EXPECT_NE(dev->getProfileHash(), nullptr);

    auto result = dev->endProfile();
    EXPECT_NE(result, nullptr);
}

// Test endProfile without startProfile returns null
TEST_F(OutputDevTest_1077, EndProfile_WithoutStart_ReturnsNull_1077) {
    auto result = dev->endProfile();
    EXPECT_EQ(result, nullptr);
}

// Test startProfile twice - second call should work
TEST_F(OutputDevTest_1077, StartProfile_CalledTwice_1077) {
    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
    dev->startProfile();
    EXPECT_NE(dev->getProfileHash(), nullptr);
    auto result = dev->endProfile();
    EXPECT_NE(result, nullptr);
}

// Test setDefaultCTM and cvtUserToDev
TEST_F(OutputDevTest_1077, SetDefaultCTM_And_CvtUserToDev_1077) {
    // Identity-like CTM: scale 1, no translation
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(10.0, 20.0, &dx, &dy);
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

// Test cvtUserToDev with scaling CTM
TEST_F(OutputDevTest_1077, CvtUserToDev_WithScaling_1077) {
    std::array<double, 6> ctm = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(5.0, 10.0, &dx, &dy);
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

// Test cvtUserToDev with translation
TEST_F(OutputDevTest_1077, CvtUserToDev_WithTranslation_1077) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// Test cvtUserToDev at origin with identity
TEST_F(OutputDevTest_1077, CvtUserToDev_AtOrigin_1077) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 0);
    EXPECT_EQ(dy, 0);
}

// Test that various no-op virtual methods can be called without crashing
TEST_F(OutputDevTest_1077, NoOpMethods_DoNotCrash_1077) {
    EXPECT_NO_THROW(dev->startPage(1, nullptr, nullptr));
    EXPECT_NO_THROW(dev->endPage());
    EXPECT_NO_THROW(dev->dump());
    EXPECT_NO_THROW(dev->saveState(nullptr));
    EXPECT_NO_THROW(dev->restoreState(nullptr));
    EXPECT_NO_THROW(dev->updateAll(nullptr));
    EXPECT_NO_THROW(dev->updateCTM(nullptr, 1, 0, 0, 1, 0, 0));
    EXPECT_NO_THROW(dev->updateLineDash(nullptr));
    EXPECT_NO_THROW(dev->updateFlatness(nullptr));
    EXPECT_NO_THROW(dev->updateLineJoin(nullptr));
    EXPECT_NO_THROW(dev->updateLineCap(nullptr));
    EXPECT_NO_THROW(dev->updateMiterLimit(nullptr));
    EXPECT_NO_THROW(dev->updateLineWidth(nullptr));
    EXPECT_NO_THROW(dev->updateStrokeAdjust(nullptr));
    EXPECT_NO_THROW(dev->updateFillColorSpace(nullptr));
    EXPECT_NO_THROW(dev->updateStrokeColorSpace(nullptr));
    EXPECT_NO_THROW(dev->updateFillColor(nullptr));
    EXPECT_NO_THROW(dev->updateStrokeColor(nullptr));
    EXPECT_NO_THROW(dev->updateBlendMode(nullptr));
    EXPECT_NO_THROW(dev->updateFillOpacity(nullptr));
    EXPECT_NO_THROW(dev->updateStrokeOpacity(nullptr));
    EXPECT_NO_THROW(dev->updateFont(nullptr));
    EXPECT_NO_THROW(dev->updateTextMat(nullptr));
    EXPECT_NO_THROW(dev->updateCharSpace(nullptr));
    EXPECT_NO_THROW(dev->updateRender(nullptr));
    EXPECT_NO_THROW(dev->updateRise(nullptr));
    EXPECT_NO_THROW(dev->updateWordSpace(nullptr));
    EXPECT_NO_THROW(dev->updateHorizScaling(nullptr));
    EXPECT_NO_THROW(dev->updateTextPos(nullptr));
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
    EXPECT_NO_THROW(dev->processLink(nullptr));
    EXPECT_NO_THROW(dev->clearSoftMask(nullptr));
    EXPECT_NO_THROW(dev->endTransparencyGroup(nullptr));
    EXPECT_NO_THROW(dev->endMarkedContent(nullptr));
    EXPECT_NO_THROW(dev->markPoint("test"));
}

// Test beginType3Char default returns false
TEST_F(OutputDevTest_1077, BeginType3Char_DefaultReturnsFalse_1077) {
    bool result = dev->beginType3Char(nullptr, 0, 0, 0, 0, 0, nullptr, 0);
    EXPECT_FALSE(result);
}

// Test tilingPatternFill default returns false
TEST_F(OutputDevTest_1077, TilingPatternFill_DefaultReturnsFalse_1077) {
    std::array<double, 6> mat = {1, 0, 0, 1, 0, 0};
    bool result = dev->tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 1, 1, 1.0, 1.0);
    EXPECT_FALSE(result);
}

// Test functionShadedFill default returns false
TEST_F(OutputDevTest_1077, FunctionShadedFill_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->functionShadedFill(nullptr, nullptr));
}

// Test axialShadedFill default returns false
TEST_F(OutputDevTest_1077, AxialShadedFill_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->axialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

// Test axialShadedSupportExtend default returns false
TEST_F(OutputDevTest_1077, AxialShadedSupportExtend_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->axialShadedSupportExtend(nullptr, nullptr));
}

// Test radialShadedFill default returns false
TEST_F(OutputDevTest_1077, RadialShadedFill_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->radialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

// Test radialShadedSupportExtend default returns false
TEST_F(OutputDevTest_1077, RadialShadedSupportExtend_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->radialShadedSupportExtend(nullptr, nullptr));
}

// Test gouraudTriangleShadedFill default returns false
TEST_F(OutputDevTest_1077, GouraudTriangleShadedFill_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->gouraudTriangleShadedFill(nullptr, nullptr));
}

// Test patchMeshShadedFill default returns false
TEST_F(OutputDevTest_1077, PatchMeshShadedFill_DefaultReturnsFalse_1077) {
    EXPECT_FALSE(dev->patchMeshShadedFill(nullptr, nullptr));
}

// Test setVectorAntialias (should be callable, even if no-op by default)
TEST_F(OutputDevTest_1077, SetVectorAntialias_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->setVectorAntialias(true));
    EXPECT_NO_THROW(dev->setVectorAntialias(false));
}

// Test getIccColorSpaceCache returns non-null
TEST_F(OutputDevTest_1077, GetIccColorSpaceCache_ReturnsNonNull_1077) {
    auto cache = dev->getIccColorSpaceCache();
    EXPECT_NE(cache, nullptr);
}

#ifdef USE_CMS
// Test display profile set/get
TEST_F(OutputDevTest_1077, DisplayProfile_SetAndGet_1077) {
    // Initially should be null/empty
    auto profile = dev->getDisplayProfile();
    // Set and get
    dev->setDisplayProfile(profile);
    auto retrieved = dev->getDisplayProfile();
}

// Test default gray profile set/get
TEST_F(OutputDevTest_1077, DefaultGrayProfile_SetAndGet_1077) {
    auto profile = dev->getDefaultGrayProfile();
    dev->setDefaultGrayProfile(profile);
    auto retrieved = dev->getDefaultGrayProfile();
}

// Test default RGB profile set/get
TEST_F(OutputDevTest_1077, DefaultRGBProfile_SetAndGet_1077) {
    auto profile = dev->getDefaultRGBProfile();
    dev->setDefaultRGBProfile(profile);
    auto retrieved = dev->getDefaultRGBProfile();
}

// Test default CMYK profile set/get
TEST_F(OutputDevTest_1077, DefaultCMYKProfile_SetAndGet_1077) {
    auto profile = dev->getDefaultCMYKProfile();
    dev->setDefaultCMYKProfile(profile);
    auto retrieved = dev->getDefaultCMYKProfile();
}
#endif

// Test that constructing and destroying OutputDev works
TEST_F(OutputDevTest_1077, ConstructAndDestruct_1077) {
    auto dev2 = std::make_unique<TestOutputDev>();
    EXPECT_NE(dev2, nullptr);
    dev2.reset();
}

// Test checkPageSlice with callbacks as nullptr
TEST_F(OutputDevTest_1077, CheckPageSlice_WithNullCallbacks_1077) {
    EXPECT_TRUE(dev->checkPageSlice(nullptr, 300.0, 300.0, 90, true, true,
                                     0, 0, 612, 792, true,
                                     nullptr, nullptr, nullptr, nullptr));
}

// Test boundary: incCharCount with negative value
TEST_F(OutputDevTest_1077, IncCharCount_NegativeValue_1077) {
    EXPECT_NO_THROW(dev->incCharCount(-1));
}

// Test boundary: incCharCount with zero
TEST_F(OutputDevTest_1077, IncCharCount_Zero_1077) {
    EXPECT_NO_THROW(dev->incCharCount(0));
}

// Test updateTextShift
TEST_F(OutputDevTest_1077, UpdateTextShift_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->updateTextShift(nullptr, 0.0));
    EXPECT_NO_THROW(dev->updateTextShift(nullptr, 100.5));
}

// Test updateFillColorStop
TEST_F(OutputDevTest_1077, UpdateFillColorStop_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->updateFillColorStop(nullptr, 0.0));
    EXPECT_NO_THROW(dev->updateFillColorStop(nullptr, 0.5));
    EXPECT_NO_THROW(dev->updateFillColorStop(nullptr, 1.0));
}

// Test beginMarkedContent and endMarkedContent
TEST_F(OutputDevTest_1077, MarkedContent_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->beginMarkedContent("test", nullptr));
    EXPECT_NO_THROW(dev->endMarkedContent(nullptr));
}

// Test markPoint with properties
TEST_F(OutputDevTest_1077, MarkPointWithProperties_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->markPoint("testpoint", nullptr));
}

// Test type3D0 and type3D1
TEST_F(OutputDevTest_1077, Type3D0_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->type3D0(nullptr, 1.0, 0.0));
}

TEST_F(OutputDevTest_1077, Type3D1_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->type3D1(nullptr, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0));
}

// Test saveTextPos and restoreTextPos
TEST_F(OutputDevTest_1077, SaveRestoreTextPos_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->saveTextPos(nullptr));
    EXPECT_NO_THROW(dev->restoreTextPos(nullptr));
}

// Test beginActualText and endActualText
TEST_F(OutputDevTest_1077, ActualText_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->beginActualText(nullptr, nullptr));
    EXPECT_NO_THROW(dev->endActualText(nullptr));
}

// Test psXObject
TEST_F(OutputDevTest_1077, PsXObject_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->psXObject(nullptr, nullptr));
}

// Test beginTransparencyGroup and related
TEST_F(OutputDevTest_1077, TransparencyGroup_DoesNotCrash_1077) {
    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};
    EXPECT_NO_THROW(dev->beginTransparencyGroup(nullptr, bbox, nullptr, false, false, false));
    EXPECT_NO_THROW(dev->endTransparencyGroup(nullptr));
    EXPECT_NO_THROW(dev->paintTransparencyGroup(nullptr, bbox));
}

// Test setSoftMask and clearSoftMask
TEST_F(OutputDevTest_1077, SoftMask_DoesNotCrash_1077) {
    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};
    EXPECT_NO_THROW(dev->setSoftMask(nullptr, bbox, false, nullptr, nullptr));
    EXPECT_NO_THROW(dev->clearSoftMask(nullptr));
}

// Test drawForm and beginForm/endForm
TEST_F(OutputDevTest_1077, Form_DoesNotCrash_1077) {
    Ref ref = {0, 0};
    EXPECT_NO_THROW(dev->beginForm(nullptr, ref));
    EXPECT_NO_THROW(dev->drawForm(ref));
    EXPECT_NO_THROW(dev->endForm(nullptr, ref));
}

// Test initGfxState
TEST_F(OutputDevTest_1077, InitGfxState_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->initGfxState(nullptr));
}

// Test updateAlphaIsShape
TEST_F(OutputDevTest_1077, UpdateAlphaIsShape_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->updateAlphaIsShape(nullptr));
}

// Test updateTextKnockout
TEST_F(OutputDevTest_1077, UpdateTextKnockout_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->updateTextKnockout(nullptr));
}

// Test updatePatternOpacity and clearPatternOpacity
TEST_F(OutputDevTest_1077, PatternOpacity_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->updatePatternOpacity(nullptr));
    EXPECT_NO_THROW(dev->clearPatternOpacity(nullptr));
}

// Test updateFillOverprint and updateStrokeOverprint
TEST_F(OutputDevTest_1077, Overprint_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->updateFillOverprint(nullptr));
    EXPECT_NO_THROW(dev->updateStrokeOverprint(nullptr));
    EXPECT_NO_THROW(dev->updateOverprintMode(nullptr));
}

// Test updateTransfer
TEST_F(OutputDevTest_1077, UpdateTransfer_DoesNotCrash_1077) {
    EXPECT_NO_THROW(dev->updateTransfer(nullptr));
}
