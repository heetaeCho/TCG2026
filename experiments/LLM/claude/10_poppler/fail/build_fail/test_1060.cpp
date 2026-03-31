#include <gtest/gtest.h>
#include <memory>
#include <array>
#include <string>
#include <unordered_map>

#include "OutputDev.h"

// Test fixture for OutputDev
class OutputDevTest_1060 : public ::testing::Test {
protected:
    OutputDev dev;
};

// Test that useDrawForm returns false by default
TEST_F(OutputDevTest_1060, UseDrawFormReturnsFalse_1060) {
    EXPECT_FALSE(dev.useDrawForm());
}

// Test that useTilingPatternFill returns false by default
TEST_F(OutputDevTest_1060, UseTilingPatternFillReturnsFalse_1060) {
    EXPECT_FALSE(dev.useTilingPatternFill());
}

// Test that useFillColorStop returns false by default
TEST_F(OutputDevTest_1060, UseFillColorStopReturnsFalse_1060) {
    EXPECT_FALSE(dev.useFillColorStop());
}

// Test that needNonText returns false by default
TEST_F(OutputDevTest_1060, NeedNonTextReturnsFalse_1060) {
    EXPECT_FALSE(dev.needNonText());
}

// Test that needCharCount returns false by default
TEST_F(OutputDevTest_1060, NeedCharCountReturnsFalse_1060) {
    EXPECT_FALSE(dev.needCharCount());
}

// Test that needClipToCropBox returns false by default
TEST_F(OutputDevTest_1060, NeedClipToCropBoxReturnsFalse_1060) {
    EXPECT_FALSE(dev.needClipToCropBox());
}

// Test that supportJPXtransparency returns false by default
TEST_F(OutputDevTest_1060, SupportJPXtransparencyReturnsFalse_1060) {
    EXPECT_FALSE(dev.supportJPXtransparency());
}

// Test that useShadedFills returns false by default for various types
TEST_F(OutputDevTest_1060, UseShadedFillsReturnsFalseForType0_1060) {
    EXPECT_FALSE(dev.useShadedFills(0));
}

TEST_F(OutputDevTest_1060, UseShadedFillsReturnsFalseForType1_1060) {
    EXPECT_FALSE(dev.useShadedFills(1));
}

TEST_F(OutputDevTest_1060, UseShadedFillsReturnsFalseForType7_1060) {
    EXPECT_FALSE(dev.useShadedFills(7));
}

// Test that getVectorAntialias returns false by default
TEST_F(OutputDevTest_1060, GetVectorAntialiasReturnsFalse_1060) {
    EXPECT_FALSE(dev.getVectorAntialias());
}

// Test that checkPageSlice returns true by default (allows page rendering)
TEST_F(OutputDevTest_1060, CheckPageSliceReturnsTrue_1060) {
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false));
}

// Test that checkTransparencyGroup returns false by default
TEST_F(OutputDevTest_1060, CheckTransparencyGroupReturnsFalse_1060) {
    EXPECT_FALSE(dev.checkTransparencyGroup(nullptr, false));
}

TEST_F(OutputDevTest_1060, CheckTransparencyGroupKnockoutReturnsFalse_1060) {
    EXPECT_FALSE(dev.checkTransparencyGroup(nullptr, true));
}

// Test profile start/end cycle
TEST_F(OutputDevTest_1060, StartAndEndProfileReturnsMap_1060) {
    dev.startProfile();
    auto result = dev.endProfile();
    EXPECT_NE(result, nullptr);
}

// Test that getProfileHash returns null before startProfile
TEST_F(OutputDevTest_1060, GetProfileHashReturnsNullBeforeStart_1060) {
    EXPECT_EQ(dev.getProfileHash(), nullptr);
}

// Test that getProfileHash returns non-null after startProfile
TEST_F(OutputDevTest_1060, GetProfileHashReturnsNonNullAfterStart_1060) {
    dev.startProfile();
    EXPECT_NE(dev.getProfileHash(), nullptr);
    // Clean up
    dev.endProfile();
}

// Test that endProfile returns ownership and getProfileHash becomes null
TEST_F(OutputDevTest_1060, EndProfileTransfersOwnership_1060) {
    dev.startProfile();
    EXPECT_NE(dev.getProfileHash(), nullptr);
    auto result = dev.endProfile();
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(dev.getProfileHash(), nullptr);
}

// Test setDefaultCTM and cvtUserToDev
TEST_F(OutputDevTest_1060, SetDefaultCTMAndCvtUserToDev_1060) {
    // Identity-like CTM
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev.setDefaultCTM(ctm);
    
    int dx = 0, dy = 0;
    dev.cvtUserToDev(10.0, 20.0, &dx, &dy);
    // With identity CTM, result should be (10, 20) rounded to int
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

// Test cvtUserToDev with a scaling CTM
TEST_F(OutputDevTest_1060, CvtUserToDevWithScaling_1060) {
    std::array<double, 6> ctm = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};
    dev.setDefaultCTM(ctm);
    
    int dx = 0, dy = 0;
    dev.cvtUserToDev(5.0, 10.0, &dx, &dy);
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

// Test cvtUserToDev with translation
TEST_F(OutputDevTest_1060, CvtUserToDevWithTranslation_1060) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    dev.setDefaultCTM(ctm);
    
    int dx = 0, dy = 0;
    dev.cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// Test cvtUserToDev at origin with identity
TEST_F(OutputDevTest_1060, CvtUserToDevAtOrigin_1060) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev.setDefaultCTM(ctm);
    
    int dx = 0, dy = 0;
    dev.cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 0);
    EXPECT_EQ(dy, 0);
}

// Test that beginType3Char returns false by default
TEST_F(OutputDevTest_1060, BeginType3CharReturnsFalse_1060) {
    EXPECT_FALSE(dev.beginType3Char(nullptr, 0.0, 0.0, 0.0, 0.0, 0, nullptr, 0));
}

// Test that functionShadedFill returns false by default
TEST_F(OutputDevTest_1060, FunctionShadedFillReturnsFalse_1060) {
    EXPECT_FALSE(dev.functionShadedFill(nullptr, nullptr));
}

// Test that axialShadedFill returns false by default
TEST_F(OutputDevTest_1060, AxialShadedFillReturnsFalse_1060) {
    EXPECT_FALSE(dev.axialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

// Test that axialShadedSupportExtend returns false by default
TEST_F(OutputDevTest_1060, AxialShadedSupportExtendReturnsFalse_1060) {
    EXPECT_FALSE(dev.axialShadedSupportExtend(nullptr, nullptr));
}

// Test that radialShadedFill returns false by default
TEST_F(OutputDevTest_1060, RadialShadedFillReturnsFalse_1060) {
    EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

// Test that radialShadedSupportExtend returns false by default
TEST_F(OutputDevTest_1060, RadialShadedSupportExtendReturnsFalse_1060) {
    EXPECT_FALSE(dev.radialShadedSupportExtend(nullptr, nullptr));
}

// Test that gouraudTriangleShadedFill returns false by default
TEST_F(OutputDevTest_1060, GouraudTriangleShadedFillReturnsFalse_1060) {
    EXPECT_FALSE(dev.gouraudTriangleShadedFill(nullptr, nullptr));
}

// Test that patchMeshShadedFill returns false by default
TEST_F(OutputDevTest_1060, PatchMeshShadedFillReturnsFalse_1060) {
    EXPECT_FALSE(dev.patchMeshShadedFill(nullptr, nullptr));
}

// Test that tilingPatternFill returns false by default
TEST_F(OutputDevTest_1060, TilingPatternFillReturnsFalse_1060) {
    std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_FALSE(dev.tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 1, 1, 1.0, 1.0));
}

// Test that getIccColorSpaceCache returns non-null
TEST_F(OutputDevTest_1060, GetIccColorSpaceCacheReturnsNonNull_1060) {
    EXPECT_NE(dev.getIccColorSpaceCache(), nullptr);
}

// Test that no-op methods can be called without crashing
TEST_F(OutputDevTest_1060, NoOpMethodsDoNotCrash_1060) {
    EXPECT_NO_THROW(dev.startPage(1, nullptr, nullptr));
    EXPECT_NO_THROW(dev.endPage());
    EXPECT_NO_THROW(dev.dump());
    EXPECT_NO_THROW(dev.saveState(nullptr));
    EXPECT_NO_THROW(dev.restoreState(nullptr));
    EXPECT_NO_THROW(dev.updateAll(nullptr));
    EXPECT_NO_THROW(dev.stroke(nullptr));
    EXPECT_NO_THROW(dev.fill(nullptr));
    EXPECT_NO_THROW(dev.eoFill(nullptr));
    EXPECT_NO_THROW(dev.clip(nullptr));
    EXPECT_NO_THROW(dev.eoClip(nullptr));
    EXPECT_NO_THROW(dev.clipToStrokePath(nullptr));
}

// Test update methods don't crash
TEST_F(OutputDevTest_1060, UpdateMethodsDoNotCrash_1060) {
    EXPECT_NO_THROW(dev.updateCTM(nullptr, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0));
    EXPECT_NO_THROW(dev.updateLineDash(nullptr));
    EXPECT_NO_THROW(dev.updateFlatness(nullptr));
    EXPECT_NO_THROW(dev.updateLineJoin(nullptr));
    EXPECT_NO_THROW(dev.updateLineCap(nullptr));
    EXPECT_NO_THROW(dev.updateMiterLimit(nullptr));
    EXPECT_NO_THROW(dev.updateLineWidth(nullptr));
    EXPECT_NO_THROW(dev.updateStrokeAdjust(nullptr));
    EXPECT_NO_THROW(dev.updateAlphaIsShape(nullptr));
    EXPECT_NO_THROW(dev.updateTextKnockout(nullptr));
    EXPECT_NO_THROW(dev.updateFillColorSpace(nullptr));
    EXPECT_NO_THROW(dev.updateStrokeColorSpace(nullptr));
    EXPECT_NO_THROW(dev.updateFillColor(nullptr));
    EXPECT_NO_THROW(dev.updateStrokeColor(nullptr));
    EXPECT_NO_THROW(dev.updateBlendMode(nullptr));
    EXPECT_NO_THROW(dev.updateFillOpacity(nullptr));
    EXPECT_NO_THROW(dev.updateStrokeOpacity(nullptr));
    EXPECT_NO_THROW(dev.updatePatternOpacity(nullptr));
    EXPECT_NO_THROW(dev.clearPatternOpacity(nullptr));
    EXPECT_NO_THROW(dev.updateFillOverprint(nullptr));
    EXPECT_NO_THROW(dev.updateStrokeOverprint(nullptr));
    EXPECT_NO_THROW(dev.updateOverprintMode(nullptr));
    EXPECT_NO_THROW(dev.updateTransfer(nullptr));
    EXPECT_NO_THROW(dev.updateFillColorStop(nullptr, 0.0));
    EXPECT_NO_THROW(dev.updateFont(nullptr));
    EXPECT_NO_THROW(dev.updateTextMat(nullptr));
    EXPECT_NO_THROW(dev.updateCharSpace(nullptr));
    EXPECT_NO_THROW(dev.updateRender(nullptr));
    EXPECT_NO_THROW(dev.updateRise(nullptr));
    EXPECT_NO_THROW(dev.updateWordSpace(nullptr));
    EXPECT_NO_THROW(dev.updateHorizScaling(nullptr));
    EXPECT_NO_THROW(dev.updateTextPos(nullptr));
    EXPECT_NO_THROW(dev.updateTextShift(nullptr, 0.0));
}

// Test text-related methods don't crash
TEST_F(OutputDevTest_1060, TextMethodsDoNotCrash_1060) {
    EXPECT_NO_THROW(dev.beginStringOp(nullptr));
    EXPECT_NO_THROW(dev.endStringOp(nullptr));
    EXPECT_NO_THROW(dev.beginString(nullptr, nullptr));
    EXPECT_NO_THROW(dev.endString(nullptr));
    EXPECT_NO_THROW(dev.drawChar(nullptr, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, nullptr, 0));
    EXPECT_NO_THROW(dev.drawString(nullptr, nullptr));
    EXPECT_NO_THROW(dev.endType3Char(nullptr));
    EXPECT_NO_THROW(dev.beginTextObject(nullptr));
    EXPECT_NO_THROW(dev.endTextObject(nullptr));
    EXPECT_NO_THROW(dev.incCharCount(0));
    EXPECT_NO_THROW(dev.beginActualText(nullptr, nullptr));
    EXPECT_NO_THROW(dev.endActualText(nullptr));
    EXPECT_NO_THROW(dev.saveTextPos(nullptr));
    EXPECT_NO_THROW(dev.restoreTextPos(nullptr));
}

// Test type3 methods don't crash
TEST_F(OutputDevTest_1060, Type3MethodsDoNotCrash_1060) {
    EXPECT_NO_THROW(dev.type3D0(nullptr, 0.0, 0.0));
    EXPECT_NO_THROW(dev.type3D1(nullptr, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0));
}

// Test transparency group methods don't crash
TEST_F(OutputDevTest_1060, TransparencyGroupMethodsDoNotCrash_1060) {
    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};
    EXPECT_NO_THROW(dev.beginTransparencyGroup(nullptr, bbox, nullptr, false, false, false));
    EXPECT_NO_THROW(dev.endTransparencyGroup(nullptr));
    EXPECT_NO_THROW(dev.paintTransparencyGroup(nullptr, bbox));
    EXPECT_NO_THROW(dev.setSoftMask(nullptr, bbox, false, nullptr, nullptr));
    EXPECT_NO_THROW(dev.clearSoftMask(nullptr));
}

// Test marked content methods don't crash
TEST_F(OutputDevTest_1060, MarkedContentMethodsDoNotCrash_1060) {
    EXPECT_NO_THROW(dev.beginMarkedContent("test", nullptr));
    EXPECT_NO_THROW(dev.endMarkedContent(nullptr));
    EXPECT_NO_THROW(dev.markPoint("test"));
    EXPECT_NO_THROW(dev.markPoint("test", nullptr));
}

// Test form methods don't crash
TEST_F(OutputDevTest_1060, FormMethodsDoNotCrash_1060) {
    Ref ref = {0, 0};
    EXPECT_NO_THROW(dev.beginForm(nullptr, ref));
    EXPECT_NO_THROW(dev.drawForm(ref));
    EXPECT_NO_THROW(dev.endForm(nullptr, ref));
}

// Test processLink doesn't crash
TEST_F(OutputDevTest_1060, ProcessLinkDoesNotCrash_1060) {
    EXPECT_NO_THROW(dev.processLink(nullptr));
}

// Test setVectorAntialias doesn't crash
TEST_F(OutputDevTest_1060, SetVectorAntialiasDoesNotCrash_1060) {
    EXPECT_NO_THROW(dev.setVectorAntialias(true));
    EXPECT_NO_THROW(dev.setVectorAntialias(false));
}

// Test multiple startProfile/endProfile cycles
TEST_F(OutputDevTest_1060, MultipleProfileCycles_1060) {
    dev.startProfile();
    auto result1 = dev.endProfile();
    EXPECT_NE(result1, nullptr);
    
    dev.startProfile();
    auto result2 = dev.endProfile();
    EXPECT_NE(result2, nullptr);
}

// Test checkPageSlice with abort callback as nullptr
TEST_F(OutputDevTest_1060, CheckPageSliceWithNullCallbacks_1060) {
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 300.0, 300.0, 90, true, true, 0, 0, 500, 500, true, nullptr, nullptr, nullptr, nullptr));
}

// Test checkPageSlice with various rotations
TEST_F(OutputDevTest_1060, CheckPageSliceVariousRotations_1060) {
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false));
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 90, false, false, 0, 0, 100, 100, false));
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 180, false, false, 0, 0, 100, 100, false));
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 270, false, false, 0, 0, 100, 100, false));
}

// Subclass test to verify virtual methods can be overridden
class DerivedOutputDev : public OutputDev {
public:
    bool upsideDown() override { return true; }
    bool useDrawChar() override { return true; }
    bool interpretType3Chars() override { return true; }
    bool useDrawForm() override { return true; }
    bool needNonText() override { return true; }
};

TEST_F(OutputDevTest_1060, DerivedClassOverridesUseDrawForm_1060) {
    DerivedOutputDev derived;
    EXPECT_TRUE(derived.useDrawForm());
}

TEST_F(OutputDevTest_1060, DerivedClassOverridesNeedNonText_1060) {
    DerivedOutputDev derived;
    EXPECT_TRUE(derived.needNonText());
}

TEST_F(OutputDevTest_1060, DerivedClassOverridesUpsideDown_1060) {
    DerivedOutputDev derived;
    EXPECT_TRUE(derived.upsideDown());
}

TEST_F(OutputDevTest_1060, DerivedClassOverridesUseDrawChar_1060) {
    DerivedOutputDev derived;
    EXPECT_TRUE(derived.useDrawChar());
}

TEST_F(OutputDevTest_1060, DerivedClassOverridesInterpretType3Chars_1060) {
    DerivedOutputDev derived;
    EXPECT_TRUE(derived.interpretType3Chars());
}

// Test image-related no-op methods don't crash
TEST_F(OutputDevTest_1060, ImageMethodsDoNotCrash_1060) {
    EXPECT_NO_THROW(dev.drawImageMask(nullptr, nullptr, nullptr, 100, 100, false, false, false));
    EXPECT_NO_THROW(dev.drawImage(nullptr, nullptr, nullptr, 100, 100, nullptr, false, nullptr, false));
    EXPECT_NO_THROW(dev.drawMaskedImage(nullptr, nullptr, nullptr, 100, 100, nullptr, false, nullptr, 100, 100, false, false));
    EXPECT_NO_THROW(dev.drawSoftMaskedImage(nullptr, nullptr, nullptr, 100, 100, nullptr, false, nullptr, 100, 100, nullptr, false));
}

// Test soft mask from image mask methods don't crash
TEST_F(OutputDevTest_1060, SoftMaskFromImageMaskDoesNotCrash_1060) {
    std::array<double, 6> baseMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_NO_THROW(dev.setSoftMaskFromImageMask(nullptr, nullptr, nullptr, 100, 100, false, false, baseMatrix));
    EXPECT_NO_THROW(dev.unsetSoftMaskFromImageMask(nullptr, baseMatrix));
}

// Test initGfxState doesn't crash
TEST_F(OutputDevTest_1060, InitGfxStateDoesNotCrash_1060) {
    EXPECT_NO_THROW(dev.initGfxState(nullptr));
}

// Test psXObject doesn't crash
TEST_F(OutputDevTest_1060, PsXObjectDoesNotCrash_1060) {
    EXPECT_NO_THROW(dev.psXObject(nullptr, nullptr));
}
