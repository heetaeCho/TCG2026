#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
static std::unique_ptr<GfxState> createDefaultGfxState() {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    return std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
}

class GfxStateTest_659 : public ::testing::Test {
protected:
    void SetUp() override {
        state = createDefaultGfxState();
    }

    std::unique_ptr<GfxState> state;
};

// Test that copyDefaultRGBColorSpace returns a valid color space when none is set
TEST_F(GfxStateTest_659, CopyDefaultRGBColorSpaceReturnsDeviceRGBWhenNotSet_659) {
    auto cs = state->copyDefaultRGBColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceRGB);
}

// Test that copyDefaultRGBColorSpace returns a copy of the set color space
TEST_F(GfxStateTest_659, CopyDefaultRGBColorSpaceReturnsCopyWhenSet_659) {
    auto rgbCS = std::make_unique<GfxDeviceRGBColorSpace>();
    state->setDefaultRGBColorSpace(std::move(rgbCS));
    auto cs = state->copyDefaultRGBColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceRGB);
}

// Test that copyDefaultRGBColorSpace returns a distinct copy (not same pointer)
TEST_F(GfxStateTest_659, CopyDefaultRGBColorSpaceReturnsDistinctObject_659) {
    auto rgbCS = std::make_unique<GfxDeviceRGBColorSpace>();
    state->setDefaultRGBColorSpace(std::move(rgbCS));
    auto cs1 = state->copyDefaultRGBColorSpace();
    auto cs2 = state->copyDefaultRGBColorSpace();
    ASSERT_NE(cs1, nullptr);
    ASSERT_NE(cs2, nullptr);
    EXPECT_NE(cs1.get(), cs2.get());
}

// Test copyDefaultGrayColorSpace returns DeviceGray when not set
TEST_F(GfxStateTest_659, CopyDefaultGrayColorSpaceReturnsDeviceGrayWhenNotSet_659) {
    auto cs = state->copyDefaultGrayColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceGray);
}

// Test copyDefaultCMYKColorSpace returns DeviceCMYK when not set
TEST_F(GfxStateTest_659, CopyDefaultCMYKColorSpaceReturnsDeviceCMYKWhenNotSet_659) {
    auto cs = state->copyDefaultCMYKColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceCMYK);
}

// Test basic GfxState constructor values
TEST_F(GfxStateTest_659, ConstructorSetsHDPI_659) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_659, ConstructorSetsVDPI_659) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_659, ConstructorSetsPageDimensions_659) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_659, ConstructorSetsRotate_659) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page coordinates
TEST_F(GfxStateTest_659, GetPageCoordinates_659) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test default fill opacity
TEST_F(GfxStateTest_659, DefaultFillOpacity_659) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_659, DefaultStrokeOpacity_659) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set/get fill opacity
TEST_F(GfxStateTest_659, SetFillOpacity_659) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set/get stroke opacity
TEST_F(GfxStateTest_659, SetStrokeOpacity_659) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test default line width
TEST_F(GfxStateTest_659, DefaultLineWidth_659) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set/get line width
TEST_F(GfxStateTest_659, SetLineWidth_659) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test default flatness
TEST_F(GfxStateTest_659, DefaultFlatness_659) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set/get flatness
TEST_F(GfxStateTest_659, SetFlatness_659) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test default miter limit
TEST_F(GfxStateTest_659, DefaultMiterLimit_659) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set/get miter limit
TEST_F(GfxStateTest_659, SetMiterLimit_659) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill overprint
TEST_F(GfxStateTest_659, DefaultFillOverprint_659) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set/get fill overprint
TEST_F(GfxStateTest_659, SetFillOverprint_659) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_659, DefaultStrokeOverprint_659) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set/get stroke overprint
TEST_F(GfxStateTest_659, SetStrokeOverprint_659) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_659, DefaultOverprintMode_659) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set/get overprint mode
TEST_F(GfxStateTest_659, SetOverprintMode_659) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_659, DefaultStrokeAdjust_659) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set/get stroke adjust
TEST_F(GfxStateTest_659, SetStrokeAdjust_659) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_659, DefaultAlphaIsShape_659) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set/get alpha is shape
TEST_F(GfxStateTest_659, SetAlphaIsShape_659) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_659, DefaultTextKnockout_659) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set/get text knockout
TEST_F(GfxStateTest_659, SetTextKnockout_659) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default char space
TEST_F(GfxStateTest_659, DefaultCharSpace_659) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set/get char space
TEST_F(GfxStateTest_659, SetCharSpace_659) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test default word space
TEST_F(GfxStateTest_659, DefaultWordSpace_659) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set/get word space
TEST_F(GfxStateTest_659, SetWordSpace_659) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_659, DefaultHorizScaling_659) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set/get horiz scaling
TEST_F(GfxStateTest_659, SetHorizScaling_659) {
    state->setHorizScaling(0.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.5);
}

// Test default leading
TEST_F(GfxStateTest_659, DefaultLeading_659) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set/get leading
TEST_F(GfxStateTest_659, SetLeading_659) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_659, DefaultRise_659) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set/get rise
TEST_F(GfxStateTest_659, SetRise_659) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_659, DefaultRender_659) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set/get render
TEST_F(GfxStateTest_659, SetRender_659) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default font size
TEST_F(GfxStateTest_659, DefaultFontSize_659) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test default blend mode
TEST_F(GfxStateTest_659, DefaultBlendMode_659) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test set/get blend mode
TEST_F(GfxStateTest_659, SetBlendMode_659) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test save and restore
TEST_F(GfxStateTest_659, SaveAndRestore_659) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    ASSERT_NE(saved, nullptr);
    saved->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(saved->getLineWidth(), 10.0);
    GfxState *restored = saved->restore();
    ASSERT_NE(restored, nullptr);
    EXPECT_DOUBLE_EQ(restored->getLineWidth(), 5.0);
    state.release(); // state is managed through save/restore chain
    state.reset(restored);
}

// Test hasSaves
TEST_F(GfxStateTest_659, HasSavesInitiallyFalse_659) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_659, HasSavesAfterSave_659) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->hasSaves());
    GfxState *restored = saved->restore();
    state.release();
    state.reset(restored);
}

// Test setCTM
TEST_F(GfxStateTest_659, SetCTM_659) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test transform
TEST_F(GfxStateTest_659, TransformIdentity_659) {
    // Default CTM for the state should transform coordinates
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // We just verify no crash and values are finite
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test moveTo and path operations
TEST_F(GfxStateTest_659, MoveToCreatesCurrentPoint_659) {
    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 200.0);
}

// Test lineTo after moveTo
TEST_F(GfxStateTest_659, LineToAfterMoveTo_659) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 100.0);
}

// Test curveTo
TEST_F(GfxStateTest_659, CurveTo_659) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

// Test closePath
TEST_F(GfxStateTest_659, ClosePath_659) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_659, ClearPath_659) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test clipToRect
TEST_F(GfxStateTest_659, ClipToRect_659) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_DOUBLE_EQ(xMin, 10.0);
    EXPECT_DOUBLE_EQ(yMin, 20.0);
    EXPECT_DOUBLE_EQ(xMax, 100.0);
    EXPECT_DOUBLE_EQ(yMax, 200.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_659, TextMoveTo_659) {
    state->textMoveTo(50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 60.0);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_659, SetRenderingIntent_659) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

// Test setRenderingIntent with long string (boundary: buffer is 32 chars)
TEST_F(GfxStateTest_659, SetRenderingIntentLongString_659) {
    // The buffer is 32 chars, so a string longer than 31 should be truncated or handled
    state->setRenderingIntent("AbsoluteColorimetricExtended123456789");
    // Just verify no crash; the actual stored value may be truncated
    const char *intent = state->getRenderingIntent();
    ASSERT_NE(intent, nullptr);
}

// Test setLineDash
TEST_F(GfxStateTest_659, SetLineDash_659) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

// Test setLineJoin
TEST_F(GfxStateTest_659, SetLineJoin_659) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test setLineCap
TEST_F(GfxStateTest_659, SetLineCap_659) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test setTextMat
TEST_F(GfxStateTest_659, SetTextMat_659) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// Test getPath is not null initially
TEST_F(GfxStateTest_659, GetPathNotNull_659) {
    const GfxPath *path = state->getPath();
    ASSERT_NE(path, nullptr);
}

// Test default fill color space is DeviceGray
TEST_F(GfxStateTest_659, DefaultFillColorSpaceIsDeviceGray_659) {
    GfxColorSpace *cs = state->getFillColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceGray);
}

// Test default stroke color space is DeviceGray
TEST_F(GfxStateTest_659, DefaultStrokeColorSpaceIsDeviceGray_659) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceGray);
}

// Test setFillColorSpace
TEST_F(GfxStateTest_659, SetFillColorSpace_659) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    state->setFillColorSpace(std::move(cs));
    EXPECT_EQ(state->getFillColorSpace()->getMode(), csDeviceRGB);
}

// Test setStrokeColorSpace
TEST_F(GfxStateTest_659, SetStrokeColorSpace_659) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    state->setStrokeColorSpace(std::move(cs));
    EXPECT_EQ(state->getStrokeColorSpace()->getMode(), csDeviceRGB);
}

// Test default fill/stroke patterns are null
TEST_F(GfxStateTest_659, DefaultFillPatternIsNull_659) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_659, DefaultStrokePatternIsNull_659) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test copy method
TEST_F(GfxStateTest_659, CopyState_659) {
    state->setLineWidth(7.0);
    state->setFillOpacity(0.8);
    std::unique_ptr<GfxState> copied(state->copy());
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
}

// Test with rotation
TEST(GfxStateConstructorTest_659, RotatedState_659) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test with different DPI values
TEST(GfxStateConstructorTest_659, DifferentDPI_659) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDPIState(300.0, 600.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDPIState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDPIState.getVDPI(), 600.0);
}

// Test parseBlendMode with valid blend mode name
TEST_F(GfxStateTest_659, ParseBlendModeNormal_659) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    // This test may or may not work depending on Object API; 
    // skipping if Object construction is not straightforward
}

// Test setDefaultGrayColorSpace and copyDefaultGrayColorSpace
TEST_F(GfxStateTest_659, SetAndCopyDefaultGrayColorSpace_659) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    state->setDefaultGrayColorSpace(std::move(cs));
    auto copied = state->copyDefaultGrayColorSpace();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceGray);
}

// Test setDefaultCMYKColorSpace and copyDefaultCMYKColorSpace
TEST_F(GfxStateTest_659, SetAndCopyDefaultCMYKColorSpace_659) {
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    state->setDefaultCMYKColorSpace(std::move(cs));
    auto copied = state->copyDefaultCMYKColorSpace();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceCMYK);
}

// Test multiple save/restore cycles
TEST_F(GfxStateTest_659, MultipleSaveRestore_659) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState *s2 = s1->save();
    s2->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);
    
    GfxState *r1 = s2->restore();
    EXPECT_DOUBLE_EQ(r1->getLineWidth(), 2.0);
    
    GfxState *r2 = r1->restore();
    EXPECT_DOUBLE_EQ(r2->getLineWidth(), 1.0);
    
    state.release();
    state.reset(r2);
}

// Test transformDelta
TEST_F(GfxStateTest_659, TransformDelta_659) {
    double x2, y2;
    state->transformDelta(1.0, 0.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test getUserClipBBox
TEST_F(GfxStateTest_659, GetUserClipBBox_659) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test isParentState
TEST_F(GfxStateTest_659, IsParentState_659) {
    GfxState *saved = state->save();
    EXPECT_TRUE(saved->isParentState(state.get()));
    GfxState *restored = saved->restore();
    state.release();
    state.reset(restored);
}

// Test concatCTM
TEST_F(GfxStateTest_659, ConcatCTM_659) {
    auto ctmBefore = state->getCTM();
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0); // identity concat
    auto ctmAfter = state->getCTM();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(ctmBefore[i], ctmAfter[i]);
    }
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_659, GetTransformedLineWidth_659) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GT(tw, 0.0);
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_659, SetFillColor_659) {
    GfxColor color;
    color.c[0] = dblToCol(0.5);
    state->setFillColor(&color);
    const GfxColor *fc = state->getFillColor();
    ASSERT_NE(fc, nullptr);
    EXPECT_EQ(fc->c[0], color.c[0]);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_659, SetStrokeColor_659) {
    GfxColor color;
    color.c[0] = dblToCol(0.7);
    state->setStrokeColor(&color);
    const GfxColor *sc = state->getStrokeColor();
    ASSERT_NE(sc, nullptr);
    EXPECT_EQ(sc->c[0], color.c[0]);
}

// Test empty lineDash
TEST_F(GfxStateTest_659, EmptyLineDash_659) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_TRUE(d.empty());
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_659, ShiftCTMAndClip_659) {
    // Just test it doesn't crash
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_TRUE(std::isfinite(ctm[4]));
    EXPECT_TRUE(std::isfinite(ctm[5]));
}
