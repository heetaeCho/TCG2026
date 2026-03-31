#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h"

// Test fixture for OutputDev
class OutputDevTest_1063 : public ::testing::Test {
protected:
    OutputDev dev;
};

// ============================================================
// Tests for boolean query methods - default return values
// ============================================================

TEST_F(OutputDevTest_1063, NeedClipToCropBox_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.needClipToCropBox());
}

TEST_F(OutputDevTest_1063, UseTilingPatternFill_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.useTilingPatternFill());
}

TEST_F(OutputDevTest_1063, UseShadedFills_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.useShadedFills(0));
    EXPECT_FALSE(dev.useShadedFills(1));
    EXPECT_FALSE(dev.useShadedFills(2));
    EXPECT_FALSE(dev.useShadedFills(3));
    EXPECT_FALSE(dev.useShadedFills(4));
    EXPECT_FALSE(dev.useShadedFills(5));
    EXPECT_FALSE(dev.useShadedFills(6));
    EXPECT_FALSE(dev.useShadedFills(7));
}

TEST_F(OutputDevTest_1063, UseFillColorStop_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.useFillColorStop());
}

TEST_F(OutputDevTest_1063, UseDrawForm_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.useDrawForm());
}

TEST_F(OutputDevTest_1063, NeedNonText_DefaultReturnsTrue_1063) {
    // needNonText typically defaults to true in poppler
    EXPECT_TRUE(dev.needNonText());
}

TEST_F(OutputDevTest_1063, NeedCharCount_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.needCharCount());
}

TEST_F(OutputDevTest_1063, SupportJPXtransparency_DefaultReturnsFalse_1063) {
    // Typically returns false by default
    EXPECT_FALSE(dev.supportJPXtransparency());
}

TEST_F(OutputDevTest_1063, GetVectorAntialias_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.getVectorAntialias());
}

// ============================================================
// Tests for checkPageSlice - default behavior
// ============================================================

TEST_F(OutputDevTest_1063, CheckPageSlice_DefaultReturnsTrue_1063) {
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false, 0, 0, 100, 100, false));
}

TEST_F(OutputDevTest_1063, CheckPageSlice_WithNullCallbacks_1063) {
    EXPECT_TRUE(dev.checkPageSlice(nullptr, 72.0, 72.0, 0, true, true, 0, 0, 100, 100, true, nullptr, nullptr, nullptr, nullptr));
}

// ============================================================
// Tests for checkTransparencyGroup - default behavior
// ============================================================

TEST_F(OutputDevTest_1063, CheckTransparencyGroup_DefaultReturnsTrue_1063) {
    EXPECT_TRUE(dev.checkTransparencyGroup(nullptr, false));
}

TEST_F(OutputDevTest_1063, CheckTransparencyGroup_WithKnockout_1063) {
    EXPECT_TRUE(dev.checkTransparencyGroup(nullptr, true));
}

// ============================================================
// Tests for profiling
// ============================================================

TEST_F(OutputDevTest_1063, GetProfileHash_InitiallyNull_1063) {
    // Before startProfile, profileHash should be null
    EXPECT_EQ(dev.getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1063, StartProfile_CreatesProfileHash_1063) {
    dev.startProfile();
    EXPECT_NE(dev.getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1063, EndProfile_ReturnsProfileMap_1063) {
    dev.startProfile();
    auto profileMap = dev.endProfile();
    EXPECT_NE(profileMap, nullptr);
    // After endProfile, the internal hash should be gone
    EXPECT_EQ(dev.getProfileHash(), nullptr);
}

TEST_F(OutputDevTest_1063, EndProfile_WithoutStart_ReturnsNull_1063) {
    auto profileMap = dev.endProfile();
    // If not started, endProfile should return null/empty
    EXPECT_EQ(profileMap, nullptr);
}

TEST_F(OutputDevTest_1063, StartProfile_Twice_1063) {
    dev.startProfile();
    EXPECT_NE(dev.getProfileHash(), nullptr);
    dev.startProfile();
    EXPECT_NE(dev.getProfileHash(), nullptr);
}

// ============================================================
// Tests for setDefaultCTM and cvtUserToDev
// ============================================================

TEST_F(OutputDevTest_1063, SetDefaultCTM_AndConvert_1063) {
    // Identity-like CTM: [1, 0, 0, 1, 0, 0] but scaled for device coords
    // Typical PDF CTM: [72, 0, 0, -72, 0, 792*72] or similar
    // Use identity for simplicity
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev.setDefaultCTM(ctm);

    int dx, dy;
    dev.cvtUserToDev(10.0, 20.0, &dx, &dy);
    // With identity CTM: dx = round(1*10 + 0*20 + 0) = 10, dy = round(0*10 + 1*20 + 0) = 20
    EXPECT_EQ(dx, 10);
    EXPECT_EQ(dy, 20);
}

TEST_F(OutputDevTest_1063, CvtUserToDev_ScaledCTM_1063) {
    std::array<double, 6> ctm = {2.0, 0.0, 0.0, 3.0, 10.0, 20.0};
    dev.setDefaultCTM(ctm);

    int dx, dy;
    dev.cvtUserToDev(5.0, 5.0, &dx, &dy);
    // dx = round(2*5 + 0*5 + 10) = 20
    // dy = round(0*5 + 3*5 + 20) = 35
    EXPECT_EQ(dx, 20);
    EXPECT_EQ(dy, 35);
}

TEST_F(OutputDevTest_1063, CvtUserToDev_ZeroInput_1063) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 100.0, 200.0};
    dev.setDefaultCTM(ctm);

    int dx, dy;
    dev.cvtUserToDev(0.0, 0.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// ============================================================
// Tests for display/color profile setters and getters
// ============================================================

TEST_F(OutputDevTest_1063, DisplayProfile_InitiallyNull_1063) {
    GfxLCMSProfilePtr profile = dev.getDisplayProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1063, DefaultGrayProfile_InitiallyNull_1063) {
    GfxLCMSProfilePtr profile = dev.getDefaultGrayProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1063, DefaultRGBProfile_InitiallyNull_1063) {
    GfxLCMSProfilePtr profile = dev.getDefaultRGBProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1063, DefaultCMYKProfile_InitiallyNull_1063) {
    GfxLCMSProfilePtr profile = dev.getDefaultCMYKProfile();
    EXPECT_EQ(profile, nullptr);
}

TEST_F(OutputDevTest_1063, SetAndGetDisplayProfile_Null_1063) {
    GfxLCMSProfilePtr nullProfile;
    dev.setDisplayProfile(nullProfile);
    EXPECT_EQ(dev.getDisplayProfile(), nullptr);
}

TEST_F(OutputDevTest_1063, SetAndGetDefaultGrayProfile_Null_1063) {
    GfxLCMSProfilePtr nullProfile;
    dev.setDefaultGrayProfile(nullProfile);
    EXPECT_EQ(dev.getDefaultGrayProfile(), nullptr);
}

TEST_F(OutputDevTest_1063, SetAndGetDefaultRGBProfile_Null_1063) {
    GfxLCMSProfilePtr nullProfile;
    dev.setDefaultRGBProfile(nullProfile);
    EXPECT_EQ(dev.getDefaultRGBProfile(), nullptr);
}

TEST_F(OutputDevTest_1063, SetAndGetDefaultCMYKProfile_Null_1063) {
    GfxLCMSProfilePtr nullProfile;
    dev.setDefaultCMYKProfile(nullProfile);
    EXPECT_EQ(dev.getDefaultCMYKProfile(), nullptr);
}

// ============================================================
// Tests for ICC color space cache
// ============================================================

TEST_F(OutputDevTest_1063, GetIccColorSpaceCache_NotNull_1063) {
    EXPECT_NE(dev.getIccColorSpaceCache(), nullptr);
}

// ============================================================
// Tests for virtual methods that should be callable without crashing
// (These are no-op defaults in the base class)
// ============================================================

TEST_F(OutputDevTest_1063, StartPage_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.startPage(1, nullptr, nullptr));
}

TEST_F(OutputDevTest_1063, EndPage_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.endPage());
}

TEST_F(OutputDevTest_1063, Dump_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.dump());
}

TEST_F(OutputDevTest_1063, SaveState_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.saveState(nullptr));
}

TEST_F(OutputDevTest_1063, RestoreState_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.restoreState(nullptr));
}

TEST_F(OutputDevTest_1063, UpdateAll_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateAll(nullptr));
}

TEST_F(OutputDevTest_1063, Stroke_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.stroke(nullptr));
}

TEST_F(OutputDevTest_1063, Fill_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.fill(nullptr));
}

TEST_F(OutputDevTest_1063, EoFill_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.eoFill(nullptr));
}

TEST_F(OutputDevTest_1063, Clip_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.clip(nullptr));
}

TEST_F(OutputDevTest_1063, EoClip_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.eoClip(nullptr));
}

TEST_F(OutputDevTest_1063, ClipToStrokePath_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.clipToStrokePath(nullptr));
}

TEST_F(OutputDevTest_1063, BeginStringOp_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.beginStringOp(nullptr));
}

TEST_F(OutputDevTest_1063, EndStringOp_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.endStringOp(nullptr));
}

TEST_F(OutputDevTest_1063, BeginString_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.beginString(nullptr, nullptr));
}

TEST_F(OutputDevTest_1063, EndString_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.endString(nullptr));
}

TEST_F(OutputDevTest_1063, EndType3Char_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.endType3Char(nullptr));
}

TEST_F(OutputDevTest_1063, BeginTextObject_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.beginTextObject(nullptr));
}

TEST_F(OutputDevTest_1063, EndTextObject_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.endTextObject(nullptr));
}

TEST_F(OutputDevTest_1063, IncCharCount_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.incCharCount(0));
    EXPECT_NO_THROW(dev.incCharCount(100));
}

TEST_F(OutputDevTest_1063, BeginActualText_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.beginActualText(nullptr, nullptr));
}

TEST_F(OutputDevTest_1063, EndActualText_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.endActualText(nullptr));
}

TEST_F(OutputDevTest_1063, ProcessLink_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.processLink(nullptr));
}

TEST_F(OutputDevTest_1063, SetVectorAntialias_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.setVectorAntialias(true));
    EXPECT_NO_THROW(dev.setVectorAntialias(false));
}

TEST_F(OutputDevTest_1063, ClearSoftMask_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.clearSoftMask(nullptr));
}

TEST_F(OutputDevTest_1063, EndTransparencyGroup_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.endTransparencyGroup(nullptr));
}

TEST_F(OutputDevTest_1063, EndMarkedContent_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.endMarkedContent(nullptr));
}

TEST_F(OutputDevTest_1063, BeginMarkedContent_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.beginMarkedContent("test", nullptr));
}

TEST_F(OutputDevTest_1063, MarkPoint_NoProperties_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.markPoint("test"));
}

TEST_F(OutputDevTest_1063, MarkPoint_WithProperties_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.markPoint("test", nullptr));
}

TEST_F(OutputDevTest_1063, UpdateCTM_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateCTM(nullptr, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0));
}

TEST_F(OutputDevTest_1063, UpdateLineDash_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateLineDash(nullptr));
}

TEST_F(OutputDevTest_1063, UpdateFlatness_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateFlatness(nullptr));
}

TEST_F(OutputDevTest_1063, UpdateLineJoin_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateLineJoin(nullptr));
}

TEST_F(OutputDevTest_1063, UpdateLineCap_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateLineCap(nullptr));
}

TEST_F(OutputDevTest_1063, UpdateMiterLimit_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateMiterLimit(nullptr));
}

TEST_F(OutputDevTest_1063, UpdateLineWidth_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateLineWidth(nullptr));
}

TEST_F(OutputDevTest_1063, UpdateFillColor_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateFillColor(nullptr));
}

TEST_F(OutputDevTest_1063, UpdateStrokeColor_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateStrokeColor(nullptr));
}

TEST_F(OutputDevTest_1063, UpdateFont_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateFont(nullptr));
}

TEST_F(OutputDevTest_1063, UpdateFillOpacity_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateFillOpacity(nullptr));
}

TEST_F(OutputDevTest_1063, UpdateStrokeOpacity_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateStrokeOpacity(nullptr));
}

TEST_F(OutputDevTest_1063, UpdateBlendMode_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.updateBlendMode(nullptr));
}

TEST_F(OutputDevTest_1063, Type3D0_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.type3D0(nullptr, 0.0, 0.0));
}

TEST_F(OutputDevTest_1063, Type3D1_DoesNotCrash_1063) {
    EXPECT_NO_THROW(dev.type3D1(nullptr, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0));
}

// ============================================================
// Tests for shading fill methods - default returns
// ============================================================

TEST_F(OutputDevTest_1063, FunctionShadedFill_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.functionShadedFill(nullptr, nullptr));
}

TEST_F(OutputDevTest_1063, AxialShadedFill_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.axialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

TEST_F(OutputDevTest_1063, AxialShadedSupportExtend_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.axialShadedSupportExtend(nullptr, nullptr));
}

TEST_F(OutputDevTest_1063, RadialShadedFill_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, 0.0, 1.0));
}

TEST_F(OutputDevTest_1063, RadialShadedSupportExtend_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.radialShadedSupportExtend(nullptr, nullptr));
}

TEST_F(OutputDevTest_1063, GouraudTriangleShadedFill_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.gouraudTriangleShadedFill(nullptr, nullptr));
}

TEST_F(OutputDevTest_1063, PatchMeshShadedFill_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.patchMeshShadedFill(nullptr, nullptr));
}

// ============================================================
// Tests for beginType3Char - default returns false
// ============================================================

TEST_F(OutputDevTest_1063, BeginType3Char_DefaultReturnsFalse_1063) {
    EXPECT_FALSE(dev.beginType3Char(nullptr, 0.0, 0.0, 0.0, 0.0, 0, nullptr, 0));
}

// ============================================================
// Test tiling pattern fill default
// ============================================================

TEST_F(OutputDevTest_1063, TilingPatternFill_DefaultReturnsFalse_1063) {
    std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_FALSE(dev.tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 1, 1, 1.0, 1.0));
}

// ============================================================
// Derived class test - verify virtual overrides work
// ============================================================

class TestOutputDev_1063 : public OutputDev {
public:
    bool upsideDown() override { return true; }
    bool useDrawChar() override { return true; }
    bool interpretType3Chars() override { return false; }
    bool needClipToCropBox() override { return true; }
    bool useTilingPatternFill() override { return true; }
};

TEST(OutputDevDerived_1063, OverriddenNeedClipToCropBox_1063) {
    TestOutputDev_1063 derivedDev;
    EXPECT_TRUE(derivedDev.needClipToCropBox());
}

TEST(OutputDevDerived_1063, OverriddenUpsideDown_1063) {
    TestOutputDev_1063 derivedDev;
    EXPECT_TRUE(derivedDev.upsideDown());
}

TEST(OutputDevDerived_1063, OverriddenUseDrawChar_1063) {
    TestOutputDev_1063 derivedDev;
    EXPECT_TRUE(derivedDev.useDrawChar());
}

TEST(OutputDevDerived_1063, OverriddenInterpretType3Chars_1063) {
    TestOutputDev_1063 derivedDev;
    EXPECT_FALSE(derivedDev.interpretType3Chars());
}

TEST(OutputDevDerived_1063, OverriddenUseTilingPatternFill_1063) {
    TestOutputDev_1063 derivedDev;
    EXPECT_TRUE(derivedDev.useTilingPatternFill());
}

// Non-overridden methods should still return defaults
TEST(OutputDevDerived_1063, NonOverriddenUseShadedFills_1063) {
    TestOutputDev_1063 derivedDev;
    EXPECT_FALSE(derivedDev.useShadedFills(1));
}

TEST(OutputDevDerived_1063, NonOverriddenGetVectorAntialias_1063) {
    TestOutputDev_1063 derivedDev;
    EXPECT_FALSE(derivedDev.getVectorAntialias());
}
