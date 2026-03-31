#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h"

// Test fixture for OutputDev
class OutputDevTest_1061 : public ::testing::Test {
protected:
    OutputDev dev;
};

// A derived class to test virtual method defaults and overriding
class DerivedOutputDev : public OutputDev {
public:
    bool upsideDown() override { return true; }
    bool useDrawChar() override { return true; }
    bool interpretType3Chars() override { return true; }
};

// ==================== Normal Operation Tests ====================

TEST_F(OutputDevTest_1061, NeedNonTextDefaultReturnsTrue_1061) {
    EXPECT_TRUE(dev.needNonText());
}

TEST_F(OutputDevTest_1061, UseTilingPatternFillDefaultReturnsFalse_1061) {
    EXPECT_FALSE(dev.useTilingPatternFill());
}

TEST_F(OutputDevTest_1061, UseShadedFillsDefaultReturnsFalse_1061) {
    EXPECT_FALSE(dev.useShadedFills(0));
    EXPECT_FALSE(dev.useShadedFills(1));
    EXPECT_FALSE(dev.useShadedFills(7));
}

TEST_F(OutputDevTest_1061, UseFillColorStopDefaultReturnsFalse_1061) {
    EXPECT_FALSE(dev.useFillColorStop());
}

TEST_F(OutputDevTest_1061, UseDrawFormDefaultReturnsFalse_1061) {
    EXPECT_FALSE(dev.useDrawForm());
}

TEST_F(OutputDevTest_1061, NeedCharCountDefaultReturnsFalse_1061) {
    EXPECT_FALSE(dev.needCharCount());
}

TEST_F(OutputDevTest_1061, NeedClipToCropBoxDefaultReturnsFalse_1061) {
    EXPECT_FALSE(dev.needClipToCropBox());
}

TEST_F(OutputDevTest_1061, SupportJPXtransparencyDefaultReturnsFalse_1061) {
    EXPECT_FALSE(dev.supportJPXtransparency());
}

TEST_F(OutputDevTest_1061, GetVectorAntialiasDefaultReturnsFalse_1061) {
    EXPECT_FALSE(dev.getVectorAntialias());
}

TEST_F(OutputDevTest_1061, CheckTransparencyGroupDefaultReturnsFalse_1061) {
    EXPECT_FALSE(dev.checkTransparencyGroup(nullptr, false));
    EXPECT_FALSE(dev.checkTransparencyGroup(nullptr, true));
}

TEST_F(OutputDevTest_1061, CheckPageSliceDefaultReturnsTrue_1061) {
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false));
}

// ==================== Profile Tests ====================

TEST_F(OutputDevTest_1061, StartAndEndProfileReturnsMap_1061) {
    dev.startProfile();
    auto profileResult = dev.endProfile();
    EXPECT_NE(profileResult, nullptr);
}

TEST_F(OutputDevTest_1061, GetProfileHashBeforeStartProfileReturnsNull_1061) {
    // Before starting profile, profileHash should be null
    EXPECT_EQ(dev.getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1061, GetProfileHashAfterStartProfileReturnsNonNull_1061) {
    dev.startProfile();
    EXPECT_NE(dev.getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1061, EndProfileWithoutStartReturnsNull_1061) {
    auto result = dev.endProfile();
    // If profile was never started, endProfile should return nullptr or empty
    // This tests the boundary condition
    EXPECT_EQ(result, nullptr);
}

// ==================== ICC Color Space Cache Tests ====================

TEST_F(OutputDevTest_1061, GetIccColorSpaceCacheReturnsNonNull_1061) {
    auto* cache = dev.getIccColorSpaceCache();
    EXPECT_NE(cache, nullptr);
}

// ==================== Color Profile Tests ====================

TEST_F(OutputDevTest_1061, DisplayProfileInitiallyNull_1061) {
    auto profile = dev.getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1061, DefaultGrayProfileInitiallyNull_1061) {
    auto profile = dev.getDefaultGrayProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1061, DefaultRGBProfileInitiallyNull_1061) {
    auto profile = dev.getDefaultRGBProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1061, DefaultCMYKProfileInitiallyNull_1061) {
    auto profile = dev.getDefaultCMYKProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1061, SetAndGetDisplayProfile_1061) {
    GfxLCMSProfilePtr nullProfile = nullptr;
    dev.setDisplayProfile(nullProfile);
    EXPECT_EQ(dev.getDisplayProfile(), nullptr);
}

TEST_F(OutputDevTest_1061, SetAndGetDefaultGrayProfile_1061) {
    GfxLCMSProfilePtr nullProfile = nullptr;
    dev.setDefaultGrayProfile(nullProfile);
    EXPECT_EQ(dev.getDefaultGrayProfile(), nullptr);
}

TEST_F(OutputDevTest_1061, SetAndGetDefaultRGBProfile_1061) {
    GfxLCMSProfilePtr nullProfile = nullptr;
    dev.setDefaultRGBProfile(nullProfile);
    EXPECT_EQ(dev.getDefaultRGBProfile(), nullptr);
}

TEST_F(OutputDevTest_1061, SetAndGetDefaultCMYKProfile_1061) {
    GfxLCMSProfilePtr nullProfile = nullptr;
    dev.setDefaultCMYKProfile(nullProfile);
    EXPECT_EQ(dev.getDefaultCMYKProfile(), nullptr);
}

// ==================== CTM Tests ====================

TEST_F(OutputDevTest_1061, SetDefaultCTMAndConvert_1061) {
    // Identity-like CTM: scale of 1.0
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev.setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev.cvtUserToDev(10.0, 20.0, &dx, &dy);
    // After setting identity CTM, user coords should map predictably
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

TEST_F(OutputDevTest_1061, SetDefaultCTMWithScaling_1061) {
    // CTM with scaling factor of 2
    std::array<double, 6> ctm = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};
    dev.setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev.cvtUserToDev(10.0, 20.0, &dx, &dy);
    EXPECT_EQ(dx, 20);
    EXPECT_EQ(dy, 40);
}

TEST_F(OutputDevTest_1061, SetDefaultCTMWithTranslation_1061) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    dev.setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev.cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// ==================== Derived Class Tests ====================

TEST(DerivedOutputDevTest_1061, OverriddenVirtualMethods_1061) {
    DerivedOutputDev derived;
    EXPECT_TRUE(derived.upsideDown());
    EXPECT_TRUE(derived.useDrawChar());
    EXPECT_TRUE(derived.interpretType3Chars());
    // Inherited defaults should still work
    EXPECT_TRUE(derived.needNonText());
    EXPECT_FALSE(derived.useTilingPatternFill());
}

// ==================== No-op method calls (should not crash) ====================

TEST_F(OutputDevTest_1061, StartPageDoesNotCrash_1061) {
    EXPECT_NO_THROW(dev.startPage(1, nullptr, nullptr));
}

TEST_F(OutputDevTest_1061, EndPageDoesNotCrash_1061) {
    EXPECT_NO_THROW(dev.endPage());
}

TEST_F(OutputDevTest_1061, DumpDoesNotCrash_1061) {
    EXPECT_NO_THROW(dev.dump());
}

TEST_F(OutputDevTest_1061, SaveRestoreStateDoesNotCrash_1061) {
    EXPECT_NO_THROW(dev.saveState(nullptr));
    EXPECT_NO_THROW(dev.restoreState(nullptr));
}

TEST_F(OutputDevTest_1061, UpdateAllDoesNotCrash_1061) {
    EXPECT_NO_THROW(dev.updateAll(nullptr));
}

TEST_F(OutputDevTest_1061, StrokeFillDoNotCrash_1061) {
    EXPECT_NO_THROW(dev.stroke(nullptr));
    EXPECT_NO_THROW(dev.fill(nullptr));
    EXPECT_NO_THROW(dev.eoFill(nullptr));
}

TEST_F(OutputDevTest_1061, ClipDoesNotCrash_1061) {
    EXPECT_NO_THROW(dev.clip(nullptr));
    EXPECT_NO_THROW(dev.eoClip(nullptr));
    EXPECT_NO_THROW(dev.clipToStrokePath(nullptr));
}

TEST_F(OutputDevTest_1061, StringOpsDoNotCrash_1061) {
    EXPECT_NO_THROW(dev.beginStringOp(nullptr));
    EXPECT_NO_THROW(dev.endStringOp(nullptr));
    EXPECT_NO_THROW(dev.beginString(nullptr, nullptr));
    EXPECT_NO_THROW(dev.endString(nullptr));
}

TEST_F(OutputDevTest_1061, TextObjectOpsDoNotCrash_1061) {
    EXPECT_NO_THROW(dev.beginTextObject(nullptr));
    EXPECT_NO_THROW(dev.endTextObject(nullptr));
}

TEST_F(OutputDevTest_1061, ActualTextOpsDoNotCrash_1061) {
    EXPECT_NO_THROW(dev.beginActualText(nullptr, nullptr));
    EXPECT_NO_THROW(dev.endActualText(nullptr));
}

TEST_F(OutputDevTest_1061, MarkedContentOpsDoNotCrash_1061) {
    EXPECT_NO_THROW(dev.endMarkedContent(nullptr));
    EXPECT_NO_THROW(dev.beginMarkedContent("test", nullptr));
    EXPECT_NO_THROW(dev.markPoint("test"));
    EXPECT_NO_THROW(dev.markPoint("test", nullptr));
}

TEST_F(OutputDevTest_1061, TransparencyGroupOpsDoNotCrash_1061) {
    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};
    EXPECT_NO_THROW(dev.beginTransparencyGroup(nullptr, bbox, nullptr, false, false, false));
    EXPECT_NO_THROW(dev.endTransparencyGroup(nullptr));
    EXPECT_NO_THROW(dev.paintTransparencyGroup(nullptr, bbox));
}

TEST_F(OutputDevTest_1061, SoftMaskOpsDoNotCrash_1061) {
    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};
    EXPECT_NO_THROW(dev.setSoftMask(nullptr, bbox, false, nullptr, nullptr));
    EXPECT_NO_THROW(dev.clearSoftMask(nullptr));
}

TEST_F(OutputDevTest_1061, IncCharCountDoesNotCrash_1061) {
    EXPECT_NO_THROW(dev.incCharCount(0));
    EXPECT_NO_THROW(dev.incCharCount(10));
    EXPECT_NO_THROW(dev.incCharCount(-1));
}

TEST_F(OutputDevTest_1061, SetVectorAntialiasDoesNotCrash_1061) {
    EXPECT_NO_THROW(dev.setVectorAntialias(true));
    EXPECT_NO_THROW(dev.setVectorAntialias(false));
}

TEST_F(OutputDevTest_1061, ProcessLinkDoesNotCrash_1061) {
    EXPECT_NO_THROW(dev.processLink(nullptr));
}

TEST_F(OutputDevTest_1061, UpdateMethodsDoNotCrash_1061) {
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
    EXPECT_NO_THROW(dev.saveTextPos(nullptr));
    EXPECT_NO_THROW(dev.restoreTextPos(nullptr));
}

TEST_F(OutputDevTest_1061, ShadedFillDefaultReturnsFalse_1061) {
    EXPECT_FALSE(dev.functionShadedFill(nullptr, nullptr));
    EXPECT_FALSE(dev.axialShadedFill(nullptr, nullptr, 0.0, 1.0));
    EXPECT_FALSE(dev.axialShadedSupportExtend(nullptr, nullptr));
    EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, 0.0, 1.0));
    EXPECT_FALSE(dev.radialShadedSupportExtend(nullptr, nullptr));
    EXPECT_FALSE(dev.gouraudTriangleShadedFill(nullptr, nullptr));
    EXPECT_FALSE(dev.patchMeshShadedFill(nullptr, nullptr));
}

TEST_F(OutputDevTest_1061, BeginType3CharDefaultReturnsFalse_1061) {
    EXPECT_FALSE(dev.beginType3Char(nullptr, 0.0, 0.0, 0.0, 0.0, 0, nullptr, 0));
}

TEST_F(OutputDevTest_1061, Type3DOpsDoNotCrash_1061) {
    EXPECT_NO_THROW(dev.type3D0(nullptr, 0.0, 0.0));
    EXPECT_NO_THROW(dev.type3D1(nullptr, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0));
    EXPECT_NO_THROW(dev.endType3Char(nullptr));
}

TEST_F(OutputDevTest_1061, FormOpsDoNotCrash_1061) {
    Ref ref = {0, 0};
    EXPECT_NO_THROW(dev.beginForm(nullptr, ref));
    EXPECT_NO_THROW(dev.drawForm(ref));
    EXPECT_NO_THROW(dev.endForm(nullptr, ref));
}

// ==================== Boundary Conditions ====================

TEST_F(OutputDevTest_1061, CvtUserToDevZeroCoordinates_1061) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev.setDefaultCTM(ctm);

    int dx = -1, dy = -1;
    dev.cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 0);
    EXPECT_EQ(dy, 0);
}

TEST_F(OutputDevTest_1061, CvtUserToDevNegativeCoordinates_1061) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev.setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev.cvtUserToDev(-10.0, -20.0, &dx, &dy);
    EXPECT_EQ(dx, -10);
    EXPECT_EQ(dy, -20);
}

TEST_F(OutputDevTest_1061, CheckPageSliceWithCallbacks_1061) {
    // Test with null callbacks (default)
    bool result = dev.checkPageSlice(nullptr, 72.0, 72.0, 0, true, true, 0, 0, 612, 792, true, nullptr, nullptr, nullptr, nullptr);
    EXPECT_TRUE(result);
}

TEST_F(OutputDevTest_1061, InitGfxStateDoesNotCrash_1061) {
    EXPECT_NO_THROW(dev.initGfxState(nullptr));
}

// ==================== Multiple profile start/end cycles ====================

TEST_F(OutputDevTest_1061, MultipleProfileCycles_1061) {
    dev.startProfile();
    auto result1 = dev.endProfile();
    EXPECT_NE(result1, nullptr);

    // After ending, profile hash should be null again
    EXPECT_EQ(dev.getProfileHash(), nullptr);

    dev.startProfile();
    EXPECT_NE(dev.getProfileHash(), nullptr);
    auto result2 = dev.endProfile();
    EXPECT_NE(result2, nullptr);
}
