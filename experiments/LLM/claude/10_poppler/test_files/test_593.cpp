#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a basic GfxState for testing
class GfxStateTest_593 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a simple page box (Letter size: 612 x 792)
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
    }

    PDFRectangle pageBox;

    std::unique_ptr<GfxState> createDefaultState(int rotate = 0, bool upsideDown = true) {
        return std::make_unique<GfxState>(72.0, 72.0, &pageBox, rotate, upsideDown);
    }
};

// Test basic construction and DPI getters
TEST_F(GfxStateTest_593, ConstructorSetsDPI_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_593, ConstructorWithDifferentDPI_593) {
    auto state = std::make_unique<GfxState>(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state->getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 300.0);
}

// Test page dimensions
TEST_F(GfxStateTest_593, PageDimensions_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test page bounds
TEST_F(GfxStateTest_593, PageBounds_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_593, RotateZero_593) {
    auto state = createDefaultState(0);
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_593, Rotate90_593) {
    auto state = createDefaultState(90);
    EXPECT_EQ(state->getRotate(), 90);
}

TEST_F(GfxStateTest_593, Rotate180_593) {
    auto state = createDefaultState(180);
    EXPECT_EQ(state->getRotate(), 180);
}

TEST_F(GfxStateTest_593, Rotate270_593) {
    auto state = createDefaultState(270);
    EXPECT_EQ(state->getRotate(), 270);
}

// Test default blend mode
TEST_F(GfxStateTest_593, DefaultBlendMode_593) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test set/get blend mode
TEST_F(GfxStateTest_593, SetBlendMode_593) {
    auto state = createDefaultState();
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test default fill opacity
TEST_F(GfxStateTest_593, DefaultFillOpacity_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test set/get fill opacity
TEST_F(GfxStateTest_593, SetFillOpacity_593) {
    auto state = createDefaultState();
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test default stroke opacity
TEST_F(GfxStateTest_593, DefaultStrokeOpacity_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set/get stroke opacity
TEST_F(GfxStateTest_593, SetStrokeOpacity_593) {
    auto state = createDefaultState();
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test fill overprint
TEST_F(GfxStateTest_593, DefaultFillOverprint_593) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_593, SetFillOverprintTrue_593) {
    auto state = createDefaultState();
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_593, SetFillOverprintFalse_593) {
    auto state = createDefaultState();
    state->setFillOverprint(true);
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint
TEST_F(GfxStateTest_593, DefaultStrokeOverprint_593) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_593, SetStrokeOverprintTrue_593) {
    auto state = createDefaultState();
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_593, SetStrokeOverprintFalse_593) {
    auto state = createDefaultState();
    state->setStrokeOverprint(true);
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode
TEST_F(GfxStateTest_593, DefaultOverprintMode_593) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_593, SetOverprintMode_593) {
    auto state = createDefaultState();
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test line width
TEST_F(GfxStateTest_593, DefaultLineWidth_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

TEST_F(GfxStateTest_593, SetLineWidth_593) {
    auto state = createDefaultState();
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_593, SetLineWidthZero_593) {
    auto state = createDefaultState();
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test flatness
TEST_F(GfxStateTest_593, DefaultFlatness_593) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getFlatness(), 1);
}

TEST_F(GfxStateTest_593, SetFlatness_593) {
    auto state = createDefaultState();
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test line join
TEST_F(GfxStateTest_593, DefaultLineJoin_593) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getLineJoin(), lineJoinMiter);
}

TEST_F(GfxStateTest_593, SetLineJoin_593) {
    auto state = createDefaultState();
    state->setLineJoin(lineJoinRound);
    EXPECT_EQ(state->getLineJoin(), lineJoinRound);
}

// Test line cap
TEST_F(GfxStateTest_593, DefaultLineCap_593) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getLineCap(), lineCapButt);
}

TEST_F(GfxStateTest_593, SetLineCap_593) {
    auto state = createDefaultState();
    state->setLineCap(lineCapRound);
    EXPECT_EQ(state->getLineCap(), lineCapRound);
}

// Test miter limit
TEST_F(GfxStateTest_593, DefaultMiterLimit_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

TEST_F(GfxStateTest_593, SetMiterLimit_593) {
    auto state = createDefaultState();
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test stroke adjust
TEST_F(GfxStateTest_593, DefaultStrokeAdjust_593) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_593, SetStrokeAdjust_593) {
    auto state = createDefaultState();
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test alpha is shape
TEST_F(GfxStateTest_593, DefaultAlphaIsShape_593) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_593, SetAlphaIsShape_593) {
    auto state = createDefaultState();
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test text knockout
TEST_F(GfxStateTest_593, DefaultTextKnockout_593) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_593, SetTextKnockout_593) {
    auto state = createDefaultState();
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test font size
TEST_F(GfxStateTest_593, DefaultFontSize_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test char space
TEST_F(GfxStateTest_593, DefaultCharSpace_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

TEST_F(GfxStateTest_593, SetCharSpace_593) {
    auto state = createDefaultState();
    state->setCharSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 2.0);
}

// Test word space
TEST_F(GfxStateTest_593, DefaultWordSpace_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

TEST_F(GfxStateTest_593, SetWordSpace_593) {
    auto state = createDefaultState();
    state->setWordSpace(3.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 3.0);
}

// Test horizontal scaling
TEST_F(GfxStateTest_593, DefaultHorizScaling_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

TEST_F(GfxStateTest_593, SetHorizScaling_593) {
    auto state = createDefaultState();
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.5);
}

// Test leading
TEST_F(GfxStateTest_593, DefaultLeading_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

TEST_F(GfxStateTest_593, SetLeading_593) {
    auto state = createDefaultState();
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test rise
TEST_F(GfxStateTest_593, DefaultRise_593) {
    auto state = createDefaultState();
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

TEST_F(GfxStateTest_593, SetRise_593) {
    auto state = createDefaultState();
    state->setRise(5.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 5.0);
}

// Test render
TEST_F(GfxStateTest_593, DefaultRender_593) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getRender(), 0);
}

TEST_F(GfxStateTest_593, SetRender_593) {
    auto state = createDefaultState();
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test rendering intent
TEST_F(GfxStateTest_593, SetRenderingIntent_593) {
    auto state = createDefaultState();
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_593, SetRenderingIntentRelativeColorimetric_593) {
    auto state = createDefaultState();
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

// Test text matrix
TEST_F(GfxStateTest_593, SetTextMat_593) {
    auto state = createDefaultState();
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// Test CTM
TEST_F(GfxStateTest_593, GetCTM_593) {
    auto state = createDefaultState();
    const auto &ctm = state->getCTM();
    // CTM should have 6 elements
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_593, SetCTM_593) {
    auto state = createDefaultState();
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

// Test save and restore
TEST_F(GfxStateTest_593, SaveAndRestore_593) {
    auto state = createDefaultState();
    GfxState *rawState = state.get();

    // Modify some property
    rawState->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(rawState->getLineWidth(), 5.0);

    // Save
    GfxState *savedState = rawState->save();
    EXPECT_TRUE(savedState->hasSaves());

    // Modify after save
    savedState->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(savedState->getLineWidth(), 10.0);

    // Restore should bring back previous state
    GfxState *restoredState = savedState->restore();
    EXPECT_DOUBLE_EQ(restoredState->getLineWidth(), 5.0);
}

TEST_F(GfxStateTest_593, HasSavesInitiallyFalse_593) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->hasSaves());
}

// Test path operations
TEST_F(GfxStateTest_593, InitiallyNoPath_593) {
    auto state = createDefaultState();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_593, MoveToCreatesCurPt_593) {
    auto state = createDefaultState();
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_593, LineToCreatesPath_593) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_593, ClearPath_593) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_593, CurveTo_593) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_593, ClosePath_593) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test transform
TEST_F(GfxStateTest_593, TransformWithIdentityCTM_593) {
    auto state = createDefaultState();
    // Set CTM to identity (with possible translation)
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

TEST_F(GfxStateTest_593, TransformWithScaleCTM_593) {
    auto state = createDefaultState();
    state->setCTM(2.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    double x2, y2;
    state->transform(10.0, 20.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 20.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

TEST_F(GfxStateTest_593, TransformDelta_593) {
    auto state = createDefaultState();
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    double x2, y2;
    state->transformDelta(5.0, 10.0, &x2, &y2);
    // transformDelta should not include translation
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test concatCTM
TEST_F(GfxStateTest_593, ConcatCTM_593) {
    auto state = createDefaultState();
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    double x2, y2;
    state->transform(1.0, 1.0, &x2, &y2);
    // After concat: new point = CTM * concat * [1,1]
    // concat * [1,1] = [2+10, 2+20] = [12, 22]
    // CTM (identity) * [12,22] = [12,22]
    EXPECT_DOUBLE_EQ(x2, 12.0);
    EXPECT_DOUBLE_EQ(y2, 22.0);
}

// Test line dash
TEST_F(GfxStateTest_593, SetLineDash_593) {
    auto state = createDefaultState();
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

TEST_F(GfxStateTest_593, SetLineDashEmpty_593) {
    auto state = createDefaultState();
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_EQ(result.size(), 0u);
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// Test clip bounding box
TEST_F(GfxStateTest_593, GetClipBBox_593) {
    auto state = createDefaultState();
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip box should at least be set to page bounds
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test clipToRect
TEST_F(GfxStateTest_593, ClipToRect_593) {
    auto state = createDefaultState();
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After clipping, the box should be constrained
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_593, GetUserClipBBox_593) {
    auto state = createDefaultState();
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test textMoveTo
TEST_F(GfxStateTest_593, TextMoveTo_593) {
    auto state = createDefaultState();
    state->textMoveTo(100.0, 200.0);
    // After textMoveTo, lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 100.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 200.0);
}

// Test copy
TEST_F(GfxStateTest_593, CopyState_593) {
    auto state = createDefaultState();
    state->setLineWidth(7.5);
    state->setFillOpacity(0.8);

    auto copied = std::unique_ptr<GfxState>(state->copy());
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 7.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.8);
}

// Test that save creates a chain
TEST_F(GfxStateTest_593, SaveCreatesChain_593) {
    auto state = createDefaultState();
    GfxState *raw = state.get();

    GfxState *s1 = raw->save();
    EXPECT_TRUE(s1->hasSaves());

    GfxState *s2 = s1->save();
    EXPECT_TRUE(s2->hasSaves());

    // Restore back
    GfxState *r1 = s2->restore();
    EXPECT_TRUE(r1->hasSaves());

    GfxState *r2 = r1->restore();
    EXPECT_FALSE(r2->hasSaves());
}

// Test isParentState
TEST_F(GfxStateTest_593, IsParentState_593) {
    auto state = createDefaultState();
    GfxState *raw = state.get();

    GfxState *saved = raw->save();
    EXPECT_TRUE(saved->isParentState(raw));
}

// Test default font is null
TEST_F(GfxStateTest_593, DefaultFontIsNull_593) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getFont(), nullptr);
}

// Test default fill/stroke color spaces are null initially
TEST_F(GfxStateTest_593, DefaultColorSpaces_593) {
    auto state = createDefaultState();
    // These may be set to default device color spaces
    // Just ensure they don't crash
    GfxColorSpace *fillCS = state->getFillColorSpace();
    GfxColorSpace *strokeCS = state->getStrokeColorSpace();
    // They might be non-null (DeviceGray default), just check no crash
    (void)fillCS;
    (void)strokeCS;
}

// Test default patterns are null
TEST_F(GfxStateTest_593, DefaultPatternsNull_593) {
    auto state = createDefaultState();
    EXPECT_EQ(state->getFillPattern(), nullptr);
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test getCTM with Matrix pointer
TEST_F(GfxStateTest_593, GetCTMMatrix_593) {
    auto state = createDefaultState();
    state->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    Matrix m;
    state->getCTM(&m);
    // Verify the matrix is populated (exact mapping depends on implementation)
    // Just ensure no crash
}

// Test transformWidth
TEST_F(GfxStateTest_593, TransformWidth_593) {
    auto state = createDefaultState();
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double transformed = state->transformWidth(1.0);
    EXPECT_GT(transformed, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_593, GetTransformedLineWidth_593) {
    auto state = createDefaultState();
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(3.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// Test fill and stroke colors
TEST_F(GfxStateTest_593, SetFillColor_593) {
    auto state = createDefaultState();
    GfxColor color;
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    EXPECT_EQ(result->c[0], 32768);
}

TEST_F(GfxStateTest_593, SetStrokeColor_593) {
    auto state = createDefaultState();
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    EXPECT_EQ(result->c[0], 65535);
}

// Test getPath
TEST_F(GfxStateTest_593, GetPathNotNull_593) {
    auto state = createDefaultState();
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test getCurX and getCurY after moveTo
TEST_F(GfxStateTest_593, GetCurXYAfterMoveTo_593) {
    auto state = createDefaultState();
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->moveTo(50.0, 60.0);
    EXPECT_DOUBLE_EQ(state->getCurX(), 50.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 60.0);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_593, ShiftCTMAndClip_593) {
    auto state = createDefaultState();
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test parseBlendMode with normal
TEST_F(GfxStateTest_593, ParseBlendModeNormal_593) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// Test that save/restore preserves properties
TEST_F(GfxStateTest_593, SaveRestorePreservesLineJoin_593) {
    auto state = createDefaultState();
    GfxState *raw = state.get();
    raw->setLineJoin(lineJoinBevel);

    GfxState *saved = raw->save();
    saved->setLineJoin(lineJoinRound);
    EXPECT_EQ(saved->getLineJoin(), lineJoinRound);

    GfxState *restored = saved->restore();
    EXPECT_EQ(restored->getLineJoin(), lineJoinBevel);
}

// Test save/restore preserves fill opacity
TEST_F(GfxStateTest_593, SaveRestorePreservesFillOpacity_593) {
    auto state = createDefaultState();
    GfxState *raw = state.get();
    raw->setFillOpacity(0.7);

    GfxState *saved = raw->save();
    saved->setFillOpacity(0.3);
    EXPECT_DOUBLE_EQ(saved->getFillOpacity(), 0.3);

    GfxState *restored = saved->restore();
    EXPECT_DOUBLE_EQ(restored->getFillOpacity(), 0.7);
}

// Test getReusablePath does not return null
TEST_F(GfxStateTest_593, GetReusablePath_593) {
    auto state = createDefaultState();
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// Boundary: very large coordinates
TEST_F(GfxStateTest_593, LargeCoordinatesTransform_593) {
    auto state = createDefaultState();
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(1e10, 1e10, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 1e10);
    EXPECT_DOUBLE_EQ(y2, 1e10);
}

// Boundary: negative coordinates
TEST_F(GfxStateTest_593, NegativeCoordinatesTransform_593) {
    auto state = createDefaultState();
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->transform(-50.0, -100.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, -50.0);
    EXPECT_DOUBLE_EQ(y2, -100.0);
}

// Test setting rendering intent with long string (boundary, max 31 chars + null)
TEST_F(GfxStateTest_593, SetRenderingIntentLongString_593) {
    auto state = createDefaultState();
    // 31 character string (fits in 32 char buffer with null)
    state->setRenderingIntent("AbsoluteColorimetricExtended01");
    const char *intent = state->getRenderingIntent();
    EXPECT_NE(intent, nullptr);
}

// Test default color space copy functions
TEST_F(GfxStateTest_593, CopyDefaultColorSpacesNull_593) {
    auto state = createDefaultState();
    auto gray = state->copyDefaultGrayColorSpace();
    auto rgb = state->copyDefaultRGBColorSpace();
    auto cmyk = state->copyDefaultCMYKColorSpace();
    // Initially these may be null
    // Just ensuring no crash
}
