#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Helper to create a basic GfxState for testing
// Using a simple page box and common parameters
class GfxStateTest_667 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;  // Letter width in points
        pageBox.y2 = 792;  // Letter height in points
        state = new GfxState(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        delete state;
    }

    GfxState *state;
};

// Test basic construction and DPI getters
TEST_F(GfxStateTest_667, ConstructionAndDPI_667) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_667, PageDimensions_667) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test page width and height
TEST_F(GfxStateTest_667, PageWidthHeight_667) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_667, GetRotate_667) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test default blend mode
TEST_F(GfxStateTest_667, DefaultBlendMode_667) {
    // Default blend mode should be Normal (0)
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test default opacity values
TEST_F(GfxStateTest_667, DefaultOpacity_667) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test default overprint
TEST_F(GfxStateTest_667, DefaultOverprint_667) {
    EXPECT_FALSE(state->getFillOverprint());
    EXPECT_FALSE(state->getStrokeOverprint());
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test default line properties
TEST_F(GfxStateTest_667, DefaultLineWidth_667) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test default flatness
TEST_F(GfxStateTest_667, DefaultFlatness_667) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test default miter limit
TEST_F(GfxStateTest_667, DefaultMiterLimit_667) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test default text properties
TEST_F(GfxStateTest_667, DefaultTextProperties_667) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
    EXPECT_EQ(state->getRender(), 0);
}

// Test default font size
TEST_F(GfxStateTest_667, DefaultFontSize_667) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test default stroke adjust
TEST_F(GfxStateTest_667, DefaultStrokeAdjust_667) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_667, DefaultAlphaIsShape_667) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_667, DefaultTextKnockout_667) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test setLineWidth and getLineWidth
TEST_F(GfxStateTest_667, SetGetLineWidth_667) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test setFillOpacity and getFillOpacity
TEST_F(GfxStateTest_667, SetGetFillOpacity_667) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test setStrokeOpacity and getStrokeOpacity
TEST_F(GfxStateTest_667, SetGetStrokeOpacity_667) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.75);
}

// Test setFillOverprint and getFillOverprint
TEST_F(GfxStateTest_667, SetGetFillOverprint_667) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test setStrokeOverprint
TEST_F(GfxStateTest_667, SetGetStrokeOverprint_667) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test setOverprintMode
TEST_F(GfxStateTest_667, SetGetOverprintMode_667) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test setCharSpace
TEST_F(GfxStateTest_667, SetGetCharSpace_667) {
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

// Test setWordSpace
TEST_F(GfxStateTest_667, SetGetWordSpace_667) {
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test setHorizScaling
TEST_F(GfxStateTest_667, SetGetHorizScaling_667) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test setLeading
TEST_F(GfxStateTest_667, SetGetLeading_667) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 14.0);
}

// Test setRise
TEST_F(GfxStateTest_667, SetGetRise_667) {
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test setRender
TEST_F(GfxStateTest_667, SetGetRender_667) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test setFlatness
TEST_F(GfxStateTest_667, SetGetFlatness_667) {
    state->setFlatness(50);
    EXPECT_EQ(state->getFlatness(), 50);
}

// Test setMiterLimit
TEST_F(GfxStateTest_667, SetGetMiterLimit_667) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test setStrokeAdjust
TEST_F(GfxStateTest_667, SetGetStrokeAdjust_667) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test setAlphaIsShape
TEST_F(GfxStateTest_667, SetGetAlphaIsShape_667) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test setTextKnockout
TEST_F(GfxStateTest_667, SetGetTextKnockout_667) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test setBlendMode
TEST_F(GfxStateTest_667, SetGetBlendMode_667) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test setLineJoin
TEST_F(GfxStateTest_667, SetGetLineJoin_667) {
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test setLineCap
TEST_F(GfxStateTest_667, SetGetLineCap_667) {
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test save and restore
TEST_F(GfxStateTest_667, SaveRestore_667) {
    state->setLineWidth(5.0);
    GfxState *savedState = state->save();
    ASSERT_NE(savedState, nullptr);
    EXPECT_TRUE(savedState->hasSaves());

    savedState->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(savedState->getLineWidth(), 10.0);

    GfxState *restoredState = savedState->restore();
    ASSERT_NE(restoredState, nullptr);
    EXPECT_DOUBLE_EQ(restoredState->getLineWidth(), 5.0);
    state = restoredState;  // Update for TearDown
}

// Test hasSaves - initially false
TEST_F(GfxStateTest_667, HasSavesInitiallyFalse_667) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves - true after save
TEST_F(GfxStateTest_667, HasSavesAfterSave_667) {
    GfxState *savedState = state->save();
    EXPECT_TRUE(savedState->hasSaves());
    state = savedState->restore();
}

// Test isParentState - basic case
TEST_F(GfxStateTest_667, IsParentStateBasic_667) {
    GfxState *original = state;
    GfxState *savedState = state->save();
    EXPECT_TRUE(savedState->isParentState(original));
    state = savedState->restore();
}

// Test isParentState - not a parent
TEST_F(GfxStateTest_667, IsParentStateNotParent_667) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 100;
    pageBox.y2 = 100;
    GfxState *otherState = new GfxState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_FALSE(state->isParentState(otherState));
    delete otherState;
}

// Test isParentState - nested saves
TEST_F(GfxStateTest_667, IsParentStateNested_667) {
    GfxState *original = state;
    GfxState *s1 = state->save();
    GfxState *s2 = s1->save();
    EXPECT_TRUE(s2->isParentState(original));
    EXPECT_TRUE(s2->isParentState(s1));
    s1 = s2->restore();
    state = s1->restore();
}

// Test transform
TEST_F(GfxStateTest_667, TransformIdentity_667) {
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    // With identity-like CTM, the result should be predictable
    // The exact values depend on CTM setup (DPI and upsideDown)
    // Just verify it doesn't crash and produces finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test transformDelta
TEST_F(GfxStateTest_667, TransformDelta_667) {
    double x2, y2;
    state->transformDelta(1.0, 0.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test setCTM
TEST_F(GfxStateTest_667, SetCTM_667) {
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
TEST_F(GfxStateTest_667, ConcatCTM_667) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test path operations - initially no path
TEST_F(GfxStateTest_667, InitialPathState_667) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test moveTo creates current point
TEST_F(GfxStateTest_667, MoveToCreatesCurPt_667) {
    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test lineTo after moveTo
TEST_F(GfxStateTest_667, LineToAfterMoveTo_667) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test curveTo after moveTo
TEST_F(GfxStateTest_667, CurveToAfterMoveTo_667) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_667, ClosePath_667) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_667, ClearPath_667) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 200.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_667, SetGetTextMat_667) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 2.0);
    EXPECT_DOUBLE_EQ(tm[1], 0.0);
    EXPECT_DOUBLE_EQ(tm[2], 0.0);
    EXPECT_DOUBLE_EQ(tm[3], 2.0);
    EXPECT_DOUBLE_EQ(tm[4], 10.0);
    EXPECT_DOUBLE_EQ(tm[5], 20.0);
}

// Test textMoveTo
TEST_F(GfxStateTest_667, TextMoveTo_667) {
    state->textMoveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_667, SetGetRenderingIntent_667) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

// Test setRenderingIntent with long string (boundary)
TEST_F(GfxStateTest_667, SetRenderingIntentLongString_667) {
    // The internal buffer is char[32], so test with a string at boundary
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test clipToRect
TEST_F(GfxStateTest_667, ClipToRect_667) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip should be intersected with the existing clip
    EXPECT_LE(xMin, 100.0);
    EXPECT_LE(yMin, 200.0);
    EXPECT_GE(xMax, 10.0);
    EXPECT_GE(yMax, 20.0);
}

// Test getClipBBox
TEST_F(GfxStateTest_667, GetClipBBox_667) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_667, GetUserClipBBox_667) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test transformWidth
TEST_F(GfxStateTest_667, TransformWidth_667) {
    double tw = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GE(tw, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_667, GetTransformedLineWidth_667) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GE(tw, 0.0);
}

// Test setLineDash
TEST_F(GfxStateTest_667, SetGetLineDash_667) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 0.5);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 2.0);
    EXPECT_DOUBLE_EQ(start, 0.5);
}

// Test setLineDash with empty dash
TEST_F(GfxStateTest_667, SetLineDashEmpty_667) {
    std::vector<double> dash = {};
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test copy
TEST_F(GfxStateTest_667, CopyState_667) {
    state->setLineWidth(3.5);
    state->setFillOpacity(0.8);
    GfxState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
    delete copied;
}

// Test getCTM with Matrix parameter
TEST_F(GfxStateTest_667, GetCTMMatrix_667) {
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify matrix is populated (exact mapping depends on Matrix structure)
    // Just verify no crash
}

// Test getPath not null
TEST_F(GfxStateTest_667, GetPathNotNull_667) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test save/restore preserves state
TEST_F(GfxStateTest_667, SaveRestorePreservesState_667) {
    state->setLineWidth(7.0);
    state->setCharSpace(1.5);
    state->setWordSpace(2.5);
    
    GfxState *s1 = state->save();
    s1->setLineWidth(12.0);
    s1->setCharSpace(3.0);
    s1->setWordSpace(4.0);
    
    EXPECT_DOUBLE_EQ(s1->getLineWidth(), 12.0);
    EXPECT_DOUBLE_EQ(s1->getCharSpace(), 3.0);
    EXPECT_DOUBLE_EQ(s1->getWordSpace(), 4.0);
    
    state = s1->restore();
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 7.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.5);
}

// Test multiple saves and restores
TEST_F(GfxStateTest_667, MultipleSaveRestore_667) {
    state->setLineWidth(1.0);
    GfxState *s1 = state->save();
    s1->setLineWidth(2.0);
    GfxState *s2 = s1->save();
    s2->setLineWidth(3.0);
    
    EXPECT_DOUBLE_EQ(s2->getLineWidth(), 3.0);
    
    s1 = s2->restore();
    EXPECT_DOUBLE_EQ(s1->getLineWidth(), 2.0);
    
    state = s1->restore();
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test different rotations
TEST(GfxStateRotateTest_667, Rotate90_667) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState *state = new GfxState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(state->getRotate(), 90);
    delete state;
}

TEST(GfxStateRotateTest_667, Rotate180_667) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState *state = new GfxState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(state->getRotate(), 180);
    delete state;
}

TEST(GfxStateRotateTest_667, Rotate270_667) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState *state = new GfxState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(state->getRotate(), 270);
    delete state;
}

// Test different DPI
TEST(GfxStateDPITest_667, HighDPI_667) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState *state = new GfxState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state->getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 300.0);
    delete state;
}

// Test different horizontal and vertical DPI
TEST(GfxStateDPITest_667, AsymmetricDPI_667) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState *state = new GfxState(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state->getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 300.0);
    delete state;
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_667, ShiftCTMAndClip_667) {
    auto ctmBefore = state->getCTM();
    state->shiftCTMAndClip(10.0, 20.0);
    auto ctmAfter = state->getCTM();
    // The CTM should have been shifted
    // At minimum, verify it doesn't crash
    EXPECT_TRUE(std::isfinite(ctmAfter[4]));
    EXPECT_TRUE(std::isfinite(ctmAfter[5]));
}

// Test textTransform
TEST_F(GfxStateTest_667, TextTransform_667) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(10.0, 20.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test textTransformDelta
TEST_F(GfxStateTest_667, TextTransformDelta_667) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(10.0, 20.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test getFillColor and getStrokeColor not null
TEST_F(GfxStateTest_667, GetColorPointersNotNull_667) {
    EXPECT_NE(state->getFillColor(), nullptr);
    EXPECT_NE(state->getStrokeColor(), nullptr);
}

// Test setFillColor
TEST_F(GfxStateTest_667, SetFillColor_667) {
    GfxColor color;
    color.c[0] = 65535;
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    EXPECT_EQ(result->c[0], 65535);
}

// Test setStrokeColor
TEST_F(GfxStateTest_667, SetStrokeColor_667) {
    GfxColor color;
    color.c[0] = 32768;
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    EXPECT_EQ(result->c[0], 32768);
}

// Test getReusablePath doesn't return null
TEST_F(GfxStateTest_667, GetReusablePath_667) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    auto rp = state->getReusablePath();
    EXPECT_NE(rp, nullptr);
}

// Test isParentState with null-like scenario (self is not parent of itself)
TEST_F(GfxStateTest_667, IsNotParentOfSelf_667) {
    EXPECT_FALSE(state->isParentState(state));
}

// Test getCurX and getCurY after operations
TEST_F(GfxStateTest_667, GetCurXY_667) {
    double curX = state->getCurX();
    double curY = state->getCurY();
    EXPECT_TRUE(std::isfinite(curX));
    EXPECT_TRUE(std::isfinite(curY));
}

// Test textShift
TEST_F(GfxStateTest_667, TextShift_667) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->textMoveTo(0.0, 0.0);
    state->textShift(10.0, 20.0);
    // Just verify no crash; values depend on internal text matrix
    EXPECT_TRUE(std::isfinite(state->getCurX()));
    EXPECT_TRUE(std::isfinite(state->getCurY()));
}

// Test upsideDown = false
TEST(GfxStateUpsideDownTest_667, NotUpsideDown_667) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState *state = new GfxState(72.0, 72.0, &pageBox, 0, false);
    EXPECT_EQ(state->getRotate(), 0);
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
    delete state;
}

// Test default fill/stroke color spaces (should be null initially or device-dependent)
TEST_F(GfxStateTest_667, DefaultColorSpaces_667) {
    // Fill and stroke color spaces may be set to DeviceGray by default
    // or could be null - just verify no crash
    GfxColorSpace *fillCS = state->getFillColorSpace();
    GfxColorSpace *strokeCS = state->getStrokeColorSpace();
    // These might be non-null (DeviceGray default) or null depending on implementation
    (void)fillCS;
    (void)strokeCS;
}

// Test default fill/stroke patterns (should be null)
TEST_F(GfxStateTest_667, DefaultPatterns_667) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test getDisplayProfile (should be null when not set)
TEST_F(GfxStateTest_667, DefaultDisplayProfile_667) {
    GfxLCMSProfilePtr profile = state->getDisplayProfile();
    // May or may not be null depending on default; just ensure no crash
    (void)profile;
}

// Test boundary: zero line width
TEST_F(GfxStateTest_667, ZeroLineWidth_667) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test boundary: negative line width
TEST_F(GfxStateTest_667, NegativeLineWidth_667) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// Test boundary: opacity at 0
TEST_F(GfxStateTest_667, ZeroOpacity_667) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
}

// Test getFont (initially null)
TEST_F(GfxStateTest_667, DefaultFontNull_667) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}
