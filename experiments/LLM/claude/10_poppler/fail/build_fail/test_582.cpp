#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

// Helper to create a basic GfxState for testing
class GfxStateTest_582 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and DPI retrieval
TEST_F(GfxStateTest_582, ConstructionGetHDPI_582) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_582, ConstructionGetVDPI_582) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_582, GetPageWidth_582) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_582, GetPageHeight_582) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_582, GetRotate_582) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test page box coordinates
TEST_F(GfxStateTest_582, GetX1Y1X2Y2_582) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test default fill/stroke opacity
TEST_F(GfxStateTest_582, DefaultFillOpacity_582) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_582, DefaultStrokeOpacity_582) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set/get fill opacity
TEST_F(GfxStateTest_582, SetFillOpacity_582) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_582, SetStrokeOpacity_582) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test default overprint
TEST_F(GfxStateTest_582, DefaultFillOverprint_582) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_582, DefaultStrokeOverprint_582) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set/get overprint
TEST_F(GfxStateTest_582, SetFillOverprint_582) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_582, SetStrokeOverprint_582) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_582, DefaultOverprintMode_582) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_582, SetOverprintMode_582) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test line width
TEST_F(GfxStateTest_582, DefaultLineWidth_582) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_582, SetLineWidth_582) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_582, SetLineWidthZero_582) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test flatness
TEST_F(GfxStateTest_582, DefaultFlatness_582) {
    EXPECT_EQ(state->getFlatness(), 1);
}

TEST_F(GfxStateTest_582, SetFlatness_582) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test line join
TEST_F(GfxStateTest_582, SetLineJoin_582) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

// Test line cap
TEST_F(GfxStateTest_582, SetLineCap_582) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// Test miter limit
TEST_F(GfxStateTest_582, DefaultMiterLimit_582) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_582, SetMiterLimit_582) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test stroke adjust
TEST_F(GfxStateTest_582, DefaultStrokeAdjust_582) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_582, SetStrokeAdjust_582) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_582, DefaultAlphaIsShape_582) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_582, SetAlphaIsShape_582) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_582, DefaultTextKnockout_582) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_582, SetTextKnockout_582) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test font size
TEST_F(GfxStateTest_582, DefaultFontSize_582) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test char space
TEST_F(GfxStateTest_582, DefaultCharSpace_582) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_582, SetCharSpace_582) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

// Test word space
TEST_F(GfxStateTest_582, DefaultWordSpace_582) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_582, SetWordSpace_582) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test horizontal scaling
TEST_F(GfxStateTest_582, DefaultHorizScaling_582) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_582, SetHorizScaling_582) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test leading
TEST_F(GfxStateTest_582, DefaultLeading_582) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_582, SetLeading_582) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test rise
TEST_F(GfxStateTest_582, DefaultRise_582) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_582, SetRise_582) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test render
TEST_F(GfxStateTest_582, DefaultRender_582) {
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_582, SetRender_582) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test rendering intent
TEST_F(GfxStateTest_582, SetRenderingIntent_582) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test blend mode
TEST_F(GfxStateTest_582, DefaultBlendMode_582) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

TEST_F(GfxStateTest_582, SetBlendMode_582) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// Test save/restore
TEST_F(GfxStateTest_582, SaveRestore_582) {
    state->setFillOpacity(0.5);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setFillOpacity(0.2);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.2);
    
    GfxState *restored = state->restore();
    // After restore, we should be back in the saved state context
    EXPECT_NE(restored, nullptr);
}

TEST_F(GfxStateTest_582, HasSavesInitiallyFalse_582) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_582, HasSavesAfterSave_582) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test path operations
TEST_F(GfxStateTest_582, InitiallyNoPath_582) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_582, MoveToCreatesCurPt_582) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_582, LineToCreatesPath_582) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_582, ClearPathResetsState_582) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_582, CurveTo_582) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_582, ClosePath_582) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test transform
TEST_F(GfxStateTest_582, Transform_582) {
    double x2, y2;
    state->transform(1.0, 1.0, &x2, &y2);
    // We just verify it doesn't crash and produces some result
    // The exact result depends on the CTM
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

TEST_F(GfxStateTest_582, TransformDelta_582) {
    double x2, y2;
    state->transformDelta(1.0, 1.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test text transform
TEST_F(GfxStateTest_582, TextTransform_582) {
    double x2, y2;
    state->textTransform(1.0, 1.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

TEST_F(GfxStateTest_582, TextTransformDelta_582) {
    double x2, y2;
    state->textTransformDelta(1.0, 1.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test setCTM
TEST_F(GfxStateTest_582, SetCTM_582) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 0.0);
    EXPECT_DOUBLE_EQ(ctm[5], 0.0);
}

// Test concatCTM
TEST_F(GfxStateTest_582, ConcatCTM_582) {
    auto ctmBefore = state->getCTM();
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    auto ctmAfter = state->getCTM();
    // After concatenating a translation, the CTM should change
    // We don't know the exact values without implementation details,
    // but the transform matrix elements should be finite
    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(std::isfinite(ctmAfter[i]));
    }
}

// Test clip bounding box
TEST_F(GfxStateTest_582, GetClipBBox_582) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

TEST_F(GfxStateTest_582, GetUserClipBBox_582) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test clipToRect
TEST_F(GfxStateTest_582, ClipToRect_582) {
    state->clipToRect(10.0, 10.0, 100.0, 100.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the bbox should be no larger than the clip rect
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test set/get fill color
TEST_F(GfxStateTest_582, SetFillColor_582) {
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test set/get stroke color
TEST_F(GfxStateTest_582, SetStrokeColor_582) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 16384);
}

// Test line dash
TEST_F(GfxStateTest_582, SetLineDash_582) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 2u);
    EXPECT_DOUBLE_EQ(retrievedDash[0], 3.0);
    EXPECT_DOUBLE_EQ(retrievedDash[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

TEST_F(GfxStateTest_582, SetLineDashWithOffset_582) {
    std::vector<double> dash = {2.0, 4.0, 6.0};
    state->setLineDash(std::move(dash), 1.5);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_EQ(retrievedDash.size(), 3u);
    EXPECT_DOUBLE_EQ(start, 1.5);
}

TEST_F(GfxStateTest_582, EmptyLineDash_582) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_TRUE(retrievedDash.empty());
}

// Test text mat
TEST_F(GfxStateTest_582, SetTextMat_582) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &textMat = state->getTextMat();
    EXPECT_DOUBLE_EQ(textMat[0], 1.0);
    EXPECT_DOUBLE_EQ(textMat[1], 2.0);
    EXPECT_DOUBLE_EQ(textMat[2], 3.0);
    EXPECT_DOUBLE_EQ(textMat[3], 4.0);
    EXPECT_DOUBLE_EQ(textMat[4], 5.0);
    EXPECT_DOUBLE_EQ(textMat[5], 6.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_582, TextMoveTo_582) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test copy
TEST_F(GfxStateTest_582, CopyState_582) {
    state->setFillOpacity(0.7);
    state->setLineWidth(3.0);
    GfxState *copied = state->copy();
    EXPECT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    delete copied;
}

// Test getFillColorSpace - should have default
TEST_F(GfxStateTest_582, DefaultFillColorSpace_582) {
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_582, DefaultStrokeColorSpace_582) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test fill pattern initially null
TEST_F(GfxStateTest_582, DefaultFillPattern_582) {
    GfxPattern *pat = state->getFillPattern();
    EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxStateTest_582, DefaultStrokePattern_582) {
    GfxPattern *pat = state->getStrokePattern();
    EXPECT_EQ(pat, nullptr);
}

// Test getCurX/getCurY with moveTo
TEST_F(GfxStateTest_582, CurXYAfterMoveTo_582) {
    state->moveTo(42.0, 84.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 42.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 84.0);
}

// Test transformWidth
TEST_F(GfxStateTest_582, TransformWidth_582) {
    double w = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(w));
    EXPECT_GE(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_582, GetTransformedLineWidth_582) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GE(tw, 0.0);
}

// Test with different rotations
TEST(GfxStateRotation_582, Rotate90_582) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state.getRotate(), 90);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 792.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 612.0);
}

TEST(GfxStateRotation_582, Rotate180_582) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(state.getRotate(), 180);
}

TEST(GfxStateRotation_582, Rotate270_582) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(state.getRotate(), 270);
}

// Test different DPI values
TEST(GfxStateDPI_582, HighDPI_582) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

TEST(GfxStateDPI_582, AsymmetricDPI_582) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState state(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test getFillDeviceN - the function under primary focus
TEST_F(GfxStateTest_582, GetFillDeviceN_582) {
    GfxColor deviceN;
    memset(&deviceN, 0, sizeof(deviceN));
    // The default fill color space should handle getDeviceN
    state->getFillDeviceN(&deviceN);
    // We can't predict exact values without knowing the color space,
    // but it should not crash and deviceN should be filled
    // Just verify the call completes successfully
    SUCCEED();
}

// Test getStrokeDeviceN
TEST_F(GfxStateTest_582, GetStrokeDeviceN_582) {
    GfxColor deviceN;
    memset(&deviceN, 0, sizeof(deviceN));
    state->getStrokeDeviceN(&deviceN);
    SUCCEED();
}

// Test getFillGray
TEST_F(GfxStateTest_582, GetFillGray_582) {
    GfxGray gray;
    state->getFillGray(&gray);
    // Default should produce a valid gray value
    SUCCEED();
}

// Test getStrokeGray
TEST_F(GfxStateTest_582, GetStrokeGray_582) {
    GfxGray gray;
    state->getStrokeGray(&gray);
    SUCCEED();
}

// Test getFillRGB
TEST_F(GfxStateTest_582, GetFillRGB_582) {
    GfxRGB rgb;
    state->getFillRGB(&rgb);
    SUCCEED();
}

// Test getStrokeRGB
TEST_F(GfxStateTest_582, GetStrokeRGB_582) {
    GfxRGB rgb;
    state->getStrokeRGB(&rgb);
    SUCCEED();
}

// Test getFillCMYK
TEST_F(GfxStateTest_582, GetFillCMYK_582) {
    GfxCMYK cmyk;
    state->getFillCMYK(&cmyk);
    SUCCEED();
}

// Test getStrokeCMYK
TEST_F(GfxStateTest_582, GetStrokeCMYK_582) {
    GfxCMYK cmyk;
    state->getStrokeCMYK(&cmyk);
    SUCCEED();
}

// Test getPath
TEST_F(GfxStateTest_582, GetPath_582) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test save/restore chain
TEST_F(GfxStateTest_582, SaveRestoreChain_582) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setLineWidth(2.0);
    GfxState *s2 = state->save();
    
    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);
    
    GfxState *r1 = state->restore();
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.0);
    
    GfxState *r2 = state->restore();
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
    EXPECT_FALSE(state->hasSaves());
}

// Test isParentState
TEST_F(GfxStateTest_582, IsParentState_582) {
    GfxState *saved = state->save();
    EXPECT_TRUE(state->isParentState(saved));
}

// Test getReusablePath
TEST_F(GfxStateTest_582, GetReusablePath_582) {
    state->moveTo(0, 0);
    state->lineTo(10, 10);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_582, ShiftCTMAndClip_582) {
    auto ctmBefore = state->getCTM();
    state->shiftCTMAndClip(10.0, 20.0);
    auto ctmAfter = state->getCTM();
    // Verify the CTM has changed
    bool changed = false;
    for (int i = 0; i < 6; i++) {
        if (ctmBefore[i] != ctmAfter[i]) {
            changed = true;
            break;
        }
    }
    EXPECT_TRUE(changed);
}

// Test parseBlendMode static method
TEST_F(GfxStateTest_582, ParseBlendModeNormal_582) {
    Object obj;
    GfxBlendMode mode;
    // We can test with a name object for "Normal"
    obj = Object(new GooString("Normal"));
    // Note: The exact Object construction depends on the implementation
    // If Object doesn't support this construction, the test may need adjustment
}

// Test font-related
TEST_F(GfxStateTest_582, DefaultFont_582) {
    const auto &font = state->getFont();
    // Default font might be nullptr
    // Just verify this doesn't crash
    SUCCEED();
}

// Test getColorSpaceModeName static
TEST_F(GfxStateTest_582, GetNumColorSpaceModes_582) {
    int num = GfxColorSpace::getNumColorSpaceModes();
    EXPECT_GT(num, 0);
}

TEST_F(GfxStateTest_582, GetColorSpaceModeName_582) {
    const char *name = GfxColorSpace::getColorSpaceModeName(0);
    EXPECT_NE(name, nullptr);
}

// Test boundary: very large coordinates
TEST_F(GfxStateTest_582, MoveToLargeCoordinates_582) {
    state->moveTo(1e10, 1e10);
    EXPECT_DOUBLE_EQ(state->getCurX(), 1e10);
    EXPECT_DOUBLE_EQ(state->getCurY(), 1e10);
}

// Test boundary: negative coordinates
TEST_F(GfxStateTest_582, MoveToNegativeCoordinates_582) {
    state->moveTo(-100.0, -200.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), -100.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), -200.0);
}

// Test boundary: zero-size page
TEST(GfxStateBoundary_582, ZeroSizePage_582) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 0;
    pageBox.y2 = 0;
    GfxState state(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 0.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 0.0);
}

// Test textShift
TEST_F(GfxStateTest_582, TextShift_582) {
    state->textMoveTo(10.0, 20.0);
    double beforeX = state->getCurTextX();
    double beforeY = state->getCurTextY();
    state->textShift(5.0, 3.0);
    // Text position should have changed
    // Exact result depends on text matrix
    SUCCEED();
}

// Test multiple fill color changes
TEST_F(GfxStateTest_582, MultipleFillColorChanges_582) {
    GfxColor color1, color2;
    color1.c[0] = 100;
    color2.c[0] = 200;
    
    state->setFillColor(&color1);
    EXPECT_EQ(state->getFillColor()->c[0], 100);
    
    state->setFillColor(&color2);
    EXPECT_EQ(state->getFillColor()->c[0], 200);
}
