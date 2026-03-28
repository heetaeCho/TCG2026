#include <gtest/gtest.h>
#include "OutputDev.h"

// A concrete subclass that doesn't override anything, so we test default behavior
class ConcreteOutputDev : public OutputDev {
public:
    // Must implement pure virtual methods
    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
};

class OutputDevTest_1064 : public ::testing::Test {
protected:
    ConcreteOutputDev dev;
};

// Test default return value of supportJPXtransparency
TEST_F(OutputDevTest_1064, SupportJPXtransparencyReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.supportJPXtransparency());
}

// Test default return value of useTilingPatternFill
TEST_F(OutputDevTest_1064, UseTilingPatternFillReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.useTilingPatternFill());
}

// Test default return value of useShadedFills for various types
TEST_F(OutputDevTest_1064, UseShadedFillsReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.useShadedFills(0));
    EXPECT_FALSE(dev.useShadedFills(1));
    EXPECT_FALSE(dev.useShadedFills(2));
    EXPECT_FALSE(dev.useShadedFills(7));
}

// Test default return value of useFillColorStop
TEST_F(OutputDevTest_1064, UseFillColorStopReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.useFillColorStop());
}

// Test default return value of useDrawForm
TEST_F(OutputDevTest_1064, UseDrawFormReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.useDrawForm());
}

// Test default return value of needNonText
TEST_F(OutputDevTest_1064, NeedNonTextReturnsTrueByDefault_1064) {
    EXPECT_TRUE(dev.needNonText());
}

// Test default return value of needCharCount
TEST_F(OutputDevTest_1064, NeedCharCountReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.needCharCount());
}

// Test default return value of needClipToCropBox
TEST_F(OutputDevTest_1064, NeedClipToCropBoxReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.needClipToCropBox());
}

// Test default return value of getVectorAntialias
TEST_F(OutputDevTest_1064, GetVectorAntialiasReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.getVectorAntialias());
}

// Test default return value of checkTransparencyGroup
TEST_F(OutputDevTest_1064, CheckTransparencyGroupReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.checkTransparencyGroup(nullptr, false));
    EXPECT_FALSE(dev.checkTransparencyGroup(nullptr, true));
}

// Test default return value of checkPageSlice (should return true by default)
TEST_F(OutputDevTest_1064, CheckPageSliceReturnsTrueByDefault_1064) {
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false));
}

// Test default return value of beginType3Char
TEST_F(OutputDevTest_1064, BeginType3CharReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.beginType3Char(nullptr, 0.0, 0.0, 0.0, 0.0, 0, nullptr, 0));
}

// Test default return values for shading fill methods
TEST_F(OutputDevTest_1064, FunctionShadedFillReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.functionShadedFill(nullptr, nullptr));
}

TEST_F(OutputDevTest_1064, AxialShadedFillReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.axialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

TEST_F(OutputDevTest_1064, AxialShadedSupportExtendReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.axialShadedSupportExtend(nullptr, nullptr));
}

TEST_F(OutputDevTest_1064, RadialShadedFillReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

TEST_F(OutputDevTest_1064, RadialShadedSupportExtendReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.radialShadedSupportExtend(nullptr, nullptr));
}

TEST_F(OutputDevTest_1064, GouraudTriangleShadedFillReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.gouraudTriangleShadedFill(nullptr, nullptr));
}

TEST_F(OutputDevTest_1064, PatchMeshShadedFillReturnsFalseByDefault_1064) {
    EXPECT_FALSE(dev.patchMeshShadedFill(nullptr, nullptr));
}

// Test tiling pattern fill returns false by default
TEST_F(OutputDevTest_1064, TilingPatternFillReturnsFalseByDefault_1064) {
    std::array<double, 6> mat = {1, 0, 0, 1, 0, 0};
    EXPECT_FALSE(dev.tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 1, 1, 1.0, 1.0));
}

// Test profiling: startProfile and endProfile
TEST_F(OutputDevTest_1064, ProfileHashIsNullBeforeStartProfile_1064) {
    EXPECT_EQ(dev.getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1064, StartProfileCreatesProfileHash_1064) {
    dev.startProfile();
    EXPECT_NE(dev.getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1064, EndProfileReturnsProfileHash_1064) {
    dev.startProfile();
    auto result = dev.endProfile();
    EXPECT_NE(result, nullptr);
    // After endProfile, the internal hash should be moved away
    EXPECT_EQ(dev.getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1064, EndProfileWithoutStartReturnsNull_1064) {
    auto result = dev.endProfile();
    // Should return nullptr or empty since startProfile was never called
    EXPECT_EQ(result, nullptr);
}

// Test setDefaultCTM and cvtUserToDev
TEST_F(OutputDevTest_1064, SetDefaultCTMAndCvtUserToDev_1064) {
    // Identity matrix
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev.setDefaultCTM(ctm);
    int dx = 0, dy = 0;
    dev.cvtUserToDev(10.0, 20.0, &dx, &dy);
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

TEST_F(OutputDevTest_1064, CvtUserToDevWithScaling_1064) {
    // Scale by 2x
    std::array<double, 6> ctm = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};
    dev.setDefaultCTM(ctm);
    int dx = 0, dy = 0;
    dev.cvtUserToDev(10.0, 20.0, &dx, &dy);
    EXPECT_EQ(dx, 20);
    EXPECT_EQ(dy, 40);
}

TEST_F(OutputDevTest_1064, CvtUserToDevWithTranslation_1064) {
    // Identity + translation
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    dev.setDefaultCTM(ctm);
    int dx = 0, dy = 0;
    dev.cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

TEST_F(OutputDevTest_1064, CvtUserToDevZeroCoordinates_1064) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev.setDefaultCTM(ctm);
    int dx = 0, dy = 0;
    dev.cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 0);
    EXPECT_EQ(dy, 0);
}

// Test that default implementations of void methods don't crash
TEST_F(OutputDevTest_1064, VoidMethodsDoNotCrash_1064) {
    EXPECT_NO_FATAL_FAILURE(dev.startPage(1, nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.endPage());
    EXPECT_NO_FATAL_FAILURE(dev.dump());
    EXPECT_NO_FATAL_FAILURE(dev.saveState(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.restoreState(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateAll(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.stroke(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.fill(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.eoFill(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.clip(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.eoClip(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.clipToStrokePath(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.endType3Char(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.beginTextObject(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.endTextObject(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.beginStringOp(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.endStringOp(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.incCharCount(0));
    EXPECT_NO_FATAL_FAILURE(dev.incCharCount(100));
    EXPECT_NO_FATAL_FAILURE(dev.beginActualText(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.endActualText(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.endMarkedContent(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.beginMarkedContent(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.markPoint(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.markPoint(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.processLink(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.setVectorAntialias(true));
    EXPECT_NO_FATAL_FAILURE(dev.setVectorAntialias(false));
    EXPECT_NO_FATAL_FAILURE(dev.clearSoftMask(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.endTransparencyGroup(nullptr));
}

// Test update methods don't crash
TEST_F(OutputDevTest_1064, UpdateMethodsDoNotCrash_1064) {
    EXPECT_NO_FATAL_FAILURE(dev.updateCTM(nullptr, 1, 0, 0, 1, 0, 0));
    EXPECT_NO_FATAL_FAILURE(dev.updateLineDash(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateFlatness(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateLineJoin(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateLineCap(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateMiterLimit(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateLineWidth(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateStrokeAdjust(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateAlphaIsShape(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateTextKnockout(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateFillColorSpace(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateStrokeColorSpace(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateFillColor(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateStrokeColor(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateBlendMode(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateFillOpacity(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateStrokeOpacity(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updatePatternOpacity(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.clearPatternOpacity(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateFillOverprint(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateStrokeOverprint(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateOverprintMode(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateTransfer(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateFillColorStop(nullptr, 0.5));
    EXPECT_NO_FATAL_FAILURE(dev.updateFont(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateTextMat(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateCharSpace(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateRender(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateRise(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateWordSpace(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateHorizScaling(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateTextPos(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.updateTextShift(nullptr, 0.0));
    EXPECT_NO_FATAL_FAILURE(dev.saveTextPos(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.restoreTextPos(nullptr));
}

// Test type3 methods don't crash
TEST_F(OutputDevTest_1064, Type3MethodsDoNotCrash_1064) {
    EXPECT_NO_FATAL_FAILURE(dev.type3D0(nullptr, 0.0, 0.0));
    EXPECT_NO_FATAL_FAILURE(dev.type3D1(nullptr, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0));
}

// Test form methods don't crash
TEST_F(OutputDevTest_1064, FormMethodsDoNotCrash_1064) {
    Ref ref = {0, 0};
    EXPECT_NO_FATAL_FAILURE(dev.beginForm(nullptr, ref));
    EXPECT_NO_FATAL_FAILURE(dev.drawForm(ref));
    EXPECT_NO_FATAL_FAILURE(dev.endForm(nullptr, ref));
}

// Test ICC color space cache accessor
TEST_F(OutputDevTest_1064, GetIccColorSpaceCacheReturnsNonNull_1064) {
    EXPECT_NE(dev.getIccColorSpaceCache(), nullptr);
}

// Test that upsideDown, useDrawChar, interpretType3Chars work on the concrete class
TEST_F(OutputDevTest_1064, PureVirtualMethodsWork_1064) {
    EXPECT_FALSE(dev.upsideDown());
    EXPECT_FALSE(dev.useDrawChar());
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test multiple start/end profile cycles
TEST_F(OutputDevTest_1064, MultipleProfileCycles_1064) {
    dev.startProfile();
    EXPECT_NE(dev.getProfileHash(), nullptr);
    auto result1 = dev.endProfile();
    EXPECT_NE(result1, nullptr);
    EXPECT_EQ(dev.getProfileHash(), nullptr);

    dev.startProfile();
    EXPECT_NE(dev.getProfileHash(), nullptr);
    auto result2 = dev.endProfile();
    EXPECT_NE(result2, nullptr);
    EXPECT_EQ(dev.getProfileHash(), nullptr);
}

// Test display profile setters/getters (with null profiles)
TEST_F(OutputDevTest_1064, DisplayProfileDefaultIsNull_1064) {
    auto profile = dev.getDisplayProfile();
    // Default should be null/empty
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1064, DefaultGrayProfileDefaultIsNull_1064) {
    auto profile = dev.getDefaultGrayProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1064, DefaultRGBProfileDefaultIsNull_1064) {
    auto profile = dev.getDefaultRGBProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1064, DefaultCMYKProfileDefaultIsNull_1064) {
    auto profile = dev.getDefaultCMYKProfile();
    EXPECT_EQ(profile, nullptr);
}

// Test setting null profiles explicitly
TEST_F(OutputDevTest_1064, SetDisplayProfileNull_1064) {
    dev.setDisplayProfile(nullptr);
    EXPECT_EQ(dev.getDisplayProfile(), nullptr);
}

TEST_F(OutputDevTest_1064, SetDefaultGrayProfileNull_1064) {
    dev.setDefaultGrayProfile(nullptr);
    EXPECT_EQ(dev.getDefaultGrayProfile(), nullptr);
}

TEST_F(OutputDevTest_1064, SetDefaultRGBProfileNull_1064) {
    dev.setDefaultRGBProfile(nullptr);
    EXPECT_EQ(dev.getDefaultRGBProfile(), nullptr);
}

TEST_F(OutputDevTest_1064, SetDefaultCMYKProfileNull_1064) {
    dev.setDefaultCMYKProfile(nullptr);
    EXPECT_EQ(dev.getDefaultCMYKProfile(), nullptr);
}

// Test transparency group methods don't crash
TEST_F(OutputDevTest_1064, TransparencyGroupMethodsDoNotCrash_1064) {
    std::array<double, 4> bbox = {0, 0, 100, 100};
    EXPECT_NO_FATAL_FAILURE(dev.beginTransparencyGroup(nullptr, bbox, nullptr, false, false, false));
    EXPECT_NO_FATAL_FAILURE(dev.endTransparencyGroup(nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.paintTransparencyGroup(nullptr, bbox));
}

// Test soft mask methods don't crash
TEST_F(OutputDevTest_1064, SoftMaskMethodsDoNotCrash_1064) {
    std::array<double, 4> bbox = {0, 0, 100, 100};
    EXPECT_NO_FATAL_FAILURE(dev.setSoftMask(nullptr, bbox, false, nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.clearSoftMask(nullptr));
}

// Test initGfxState doesn't crash
TEST_F(OutputDevTest_1064, InitGfxStateDoesNotCrash_1064) {
    EXPECT_NO_FATAL_FAILURE(dev.initGfxState(nullptr));
}

// Test drawChar doesn't crash
TEST_F(OutputDevTest_1064, DrawCharDoesNotCrash_1064) {
    EXPECT_NO_FATAL_FAILURE(dev.drawChar(nullptr, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, nullptr, 0));
}

// Test drawString and beginString/endString don't crash
TEST_F(OutputDevTest_1064, StringMethodsDoNotCrash_1064) {
    EXPECT_NO_FATAL_FAILURE(dev.beginString(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.drawString(nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev.endString(nullptr));
}

// Test psXObject doesn't crash
TEST_F(OutputDevTest_1064, PsXObjectDoesNotCrash_1064) {
    EXPECT_NO_FATAL_FAILURE(dev.psXObject(nullptr, nullptr));
}

// Test checkPageSlice with abort callback
TEST_F(OutputDevTest_1064, CheckPageSliceWithNullCallbacks_1064) {
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, true, true, 0, 0, 612, 792, true, nullptr, nullptr, nullptr, nullptr));
}
