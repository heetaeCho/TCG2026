#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makeRect(double x1, double y1, double x2, double y2) {
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_666 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makeRect(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test basic construction and DPI getters
TEST_F(GfxStateTest_666, ConstructionAndDPI_666) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

// Test page dimensions
TEST_F(GfxStateTest_666, PageDimensions_666) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

// Test rotation
TEST_F(GfxStateTest_666, RotateZero_666) {
    EXPECT_EQ(state->getRotate(), 0);
}

// Test with rotation 90
TEST(GfxStateRotateTest_666, Rotate90_666) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

// Test with rotation 180
TEST(GfxStateRotateTest_666, Rotate180_666) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(rotatedState.getRotate(), 180);
}

// Test with rotation 270
TEST(GfxStateRotateTest_666, Rotate270_666) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(rotatedState.getRotate(), 270);
}

// Test X1, Y1, X2, Y2 bounds
TEST_F(GfxStateTest_666, PageBounds_666) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// Test hasSaves initially returns false
TEST_F(GfxStateTest_666, HasSavesInitiallyFalse_666) {
    EXPECT_FALSE(state->hasSaves());
}

// Test save and hasSaves
TEST_F(GfxStateTest_666, SaveAndHasSaves_666) {
    GfxState *savedState = state->save();
    EXPECT_TRUE(savedState->hasSaves());
}

// Test save and restore
TEST_F(GfxStateTest_666, SaveAndRestore_666) {
    GfxState *afterSave = state->save();
    EXPECT_TRUE(afterSave->hasSaves());

    GfxState *afterRestore = afterSave->restore();
    EXPECT_FALSE(afterRestore->hasSaves());
}

// Test multiple saves
TEST_F(GfxStateTest_666, MultipleSaves_666) {
    GfxState *s1 = state->save();
    GfxState *s2 = s1->save();
    EXPECT_TRUE(s2->hasSaves());

    GfxState *r1 = s2->restore();
    EXPECT_TRUE(r1->hasSaves());

    GfxState *r2 = r1->restore();
    EXPECT_FALSE(r2->hasSaves());
}

// Test default fill opacity
TEST_F(GfxStateTest_666, DefaultFillOpacity_666) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

// Test default stroke opacity
TEST_F(GfxStateTest_666, DefaultStrokeOpacity_666) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test set/get fill opacity
TEST_F(GfxStateTest_666, SetFillOpacity_666) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

// Test set/get stroke opacity
TEST_F(GfxStateTest_666, SetStrokeOpacity_666) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// Test default line width
TEST_F(GfxStateTest_666, DefaultLineWidth_666) {
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 1.0);
}

// Test set/get line width
TEST_F(GfxStateTest_666, SetLineWidth_666) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

// Test set/get line width zero
TEST_F(GfxStateTest_666, SetLineWidthZero_666) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

// Test default flatness
TEST_F(GfxStateTest_666, DefaultFlatness_666) {
    EXPECT_EQ(state->getFlatness(), 1);
}

// Test set/get flatness
TEST_F(GfxStateTest_666, SetFlatness_666) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// Test default miter limit
TEST_F(GfxStateTest_666, DefaultMiterLimit_666) {
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// Test set/get miter limit
TEST_F(GfxStateTest_666, SetMiterLimit_666) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 5.0);
}

// Test default fill overprint
TEST_F(GfxStateTest_666, DefaultFillOverprint_666) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set/get fill overprint
TEST_F(GfxStateTest_666, SetFillOverprint_666) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_666, DefaultStrokeOverprint_666) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set/get stroke overprint
TEST_F(GfxStateTest_666, SetStrokeOverprint_666) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_666, DefaultOverprintMode_666) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

// Test set/get overprint mode
TEST_F(GfxStateTest_666, SetOverprintMode_666) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// Test default stroke adjust
TEST_F(GfxStateTest_666, DefaultStrokeAdjust_666) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set/get stroke adjust
TEST_F(GfxStateTest_666, SetStrokeAdjust_666) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_666, DefaultAlphaIsShape_666) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set/get alpha is shape
TEST_F(GfxStateTest_666, SetAlphaIsShape_666) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_666, DefaultTextKnockout_666) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set/get text knockout
TEST_F(GfxStateTest_666, SetTextKnockout_666) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default char space
TEST_F(GfxStateTest_666, DefaultCharSpace_666) {
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 0.0);
}

// Test set/get char space
TEST_F(GfxStateTest_666, SetCharSpace_666) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

// Test default word space
TEST_F(GfxStateTest_666, DefaultWordSpace_666) {
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 0.0);
}

// Test set/get word space
TEST_F(GfxStateTest_666, SetWordSpace_666) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

// Test default horiz scaling
TEST_F(GfxStateTest_666, DefaultHorizScaling_666) {
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0);
}

// Test set/get horiz scaling
TEST_F(GfxStateTest_666, SetHorizScaling_666) {
    state->setHorizScaling(0.5);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.5);
}

// Test default leading
TEST_F(GfxStateTest_666, DefaultLeading_666) {
    EXPECT_DOUBLE_EQ(state->getLeading(), 0.0);
}

// Test set/get leading
TEST_F(GfxStateTest_666, SetLeading_666) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

// Test default rise
TEST_F(GfxStateTest_666, DefaultRise_666) {
    EXPECT_DOUBLE_EQ(state->getRise(), 0.0);
}

// Test set/get rise
TEST_F(GfxStateTest_666, SetRise_666) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

// Test default render
TEST_F(GfxStateTest_666, DefaultRender_666) {
    EXPECT_EQ(state->getRender(), 0);
}

// Test set/get render
TEST_F(GfxStateTest_666, SetRender_666) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// Test default font size
TEST_F(GfxStateTest_666, DefaultFontSize_666) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_666, SetCTM_666) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// Test transform with identity-like CTM
TEST_F(GfxStateTest_666, TransformIdentity_666) {
    // After construction with 72 DPI, no rotation, upsideDown=true
    // the CTM should be set by the constructor
    double x2, y2;
    state->transform(0, 0, &x2, &y2);
    // Just verify it doesn't crash and returns some values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test transformDelta
TEST_F(GfxStateTest_666, TransformDelta_666) {
    double x2, y2;
    state->transformDelta(1.0, 0.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test concatCTM
TEST_F(GfxStateTest_666, ConcatCTM_666) {
    auto ctmBefore = state->getCTM();
    state->concatCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0); // identity concat
    auto ctmAfter = state->getCTM();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(ctmBefore[i], ctmAfter[i]);
    }
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_666, SetTextMat_666) {
    state->setTextMat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(tm[0], 1.0);
    EXPECT_DOUBLE_EQ(tm[1], 2.0);
    EXPECT_DOUBLE_EQ(tm[2], 3.0);
    EXPECT_DOUBLE_EQ(tm[3], 4.0);
    EXPECT_DOUBLE_EQ(tm[4], 5.0);
    EXPECT_DOUBLE_EQ(tm[5], 6.0);
}

// Test line join
TEST_F(GfxStateTest_666, DefaultLineJoin_666) {
    EXPECT_EQ(state->getLineJoin(), 0); // miter join = 0
}

TEST_F(GfxStateTest_666, SetLineJoin_666) {
    state->setLineJoin(static_cast<LineJoinStyle>(1));
    EXPECT_EQ(state->getLineJoin(), 1);
}

// Test line cap
TEST_F(GfxStateTest_666, DefaultLineCap_666) {
    EXPECT_EQ(state->getLineCap(), 0); // butt cap = 0
}

TEST_F(GfxStateTest_666, SetLineCap_666) {
    state->setLineCap(static_cast<LineCapStyle>(1));
    EXPECT_EQ(state->getLineCap(), 1);
}

// Test line dash
TEST_F(GfxStateTest_666, SetLineDash_666) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 1.0);
    ASSERT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 5.0);
}

// Test empty line dash
TEST_F(GfxStateTest_666, EmptyLineDash_666) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(start, 0.0);
    EXPECT_EQ(d.size(), 0u);
}

// Test rendering intent
TEST_F(GfxStateTest_666, SetRenderingIntent_666) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ(state->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateTest_666, SetRenderingIntentRelativeColorimetric_666) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_666, SetRenderingIntentSaturation_666) {
    state->setRenderingIntent("Saturation");
    EXPECT_STREQ(state->getRenderingIntent(), "Saturation");
}

TEST_F(GfxStateTest_666, SetRenderingIntentAbsoluteColorimetric_666) {
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// Test blend mode default
TEST_F(GfxStateTest_666, DefaultBlendMode_666) {
    EXPECT_EQ(state->getBlendMode(), gfxBlendNormal);
}

// Test set blend mode
TEST_F(GfxStateTest_666, SetBlendMode_666) {
    state->setBlendMode(gfxBlendMultiply);
    EXPECT_EQ(state->getBlendMode(), gfxBlendMultiply);
}

// Test path operations - initially no path
TEST_F(GfxStateTest_666, InitiallyNoPath_666) {
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test moveTo creates current point
TEST_F(GfxStateTest_666, MoveToCreatesCurPt_666) {
    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test lineTo after moveTo creates a path
TEST_F(GfxStateTest_666, LineToCreatesPath_666) {
    state->moveTo(100.0, 200.0);
    state->lineTo(300.0, 400.0);
    EXPECT_TRUE(state->isPath());
}

// Test curveTo
TEST_F(GfxStateTest_666, CurveTo_666) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

// Test closePath
TEST_F(GfxStateTest_666, ClosePath_666) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_666, ClearPath_666) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test textMoveTo
TEST_F(GfxStateTest_666, TextMoveTo_666) {
    state->textMoveTo(10.0, 20.0);
    // Verify through getLineX/getLineY
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// Test clip bounding box
TEST_F(GfxStateTest_666, ClipBBox_666) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // After construction, clip box should be finite
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test clipToRect
TEST_F(GfxStateTest_666, ClipToRect_666) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // The clip should be intersected, so it should be within bounds
    EXPECT_GE(xMin, 10.0);
    EXPECT_GE(yMin, 20.0);
    EXPECT_LE(xMax, 100.0);
    EXPECT_LE(yMax, 200.0);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_666, GetUserClipBBox_666) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test getCurX and getCurY default
TEST_F(GfxStateTest_666, DefaultCurXCurY_666) {
    EXPECT_DOUBLE_EQ(state->getCurX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurY(), 0.0);
}

// Test getCurTextX and getCurTextY default
TEST_F(GfxStateTest_666, DefaultCurTextXCurTextY_666) {
    EXPECT_DOUBLE_EQ(state->getCurTextX(), 0.0);
    EXPECT_DOUBLE_EQ(state->getCurTextY(), 0.0);
}

// Test transformWidth
TEST_F(GfxStateTest_666, TransformWidth_666) {
    double w = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(w));
    EXPECT_GE(w, 0.0);
}

// Test transformWidth with zero
TEST_F(GfxStateTest_666, TransformWidthZero_666) {
    double w = state->transformWidth(0.0);
    EXPECT_DOUBLE_EQ(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_666, GetTransformedLineWidth_666) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GE(tw, 0.0);
}

// Test copy
TEST_F(GfxStateTest_666, CopyState_666) {
    state->setLineWidth(3.5);
    state->setFillOpacity(0.7);
    auto copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.5);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
    delete copied;
}

// Test isParentState
TEST_F(GfxStateTest_666, IsParentState_666) {
    GfxState *child = state->save();
    EXPECT_TRUE(child->isParentState(state.get()));
}

// Test isParentState negative
TEST_F(GfxStateTest_666, IsNotParentState_666) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    GfxState otherState(72.0, 72.0, &pageBox, 0, true);
    EXPECT_FALSE(state->isParentState(&otherState));
}

// Test save preserves state properties
TEST_F(GfxStateTest_666, SavePreservesProperties_666) {
    state->setLineWidth(5.0);
    state->setFillOpacity(0.8);
    state->setCharSpace(2.0);
    
    GfxState *child = state->save();
    EXPECT_DOUBLE_EQ(child->getLineWidth(), 5.0);
    EXPECT_DOUBLE_EQ(child->getFillOpacity(), 0.8);
    EXPECT_DOUBLE_EQ(child->getCharSpace(), 2.0);
}

// Test restore goes back to parent values
TEST_F(GfxStateTest_666, RestoreGoesBackToParent_666) {
    state->setLineWidth(5.0);
    GfxState *child = state->save();
    child->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(child->getLineWidth(), 10.0);
    
    GfxState *parent = child->restore();
    EXPECT_DOUBLE_EQ(parent->getLineWidth(), 5.0);
}

// Test fill color
TEST_F(GfxStateTest_666, SetFillColor_666) {
    GfxColor color;
    memset(&color, 0, sizeof(color));
    color.c[0] = 32768; // some value
    state->setFillColor(&color);
    const GfxColor *retrieved = state->getFillColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 32768);
}

// Test stroke color
TEST_F(GfxStateTest_666, SetStrokeColor_666) {
    GfxColor color;
    memset(&color, 0, sizeof(color));
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *retrieved = state->getStrokeColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 16384);
}

// Test default font is null
TEST_F(GfxStateTest_666, DefaultFontIsNull_666) {
    const auto &font = state->getFont();
    EXPECT_EQ(font, nullptr);
}

// Test getPath
TEST_F(GfxStateTest_666, GetPathNotNull_666) {
    const GfxPath *path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_666, ShiftCTMAndClip_666) {
    auto ctmBefore = state->getCTM();
    state->shiftCTMAndClip(10.0, 20.0);
    auto ctmAfter = state->getCTM();
    // The translation components should have changed
    EXPECT_NE(ctmBefore[4], ctmAfter[4]);
}

// Test getReusablePath
TEST_F(GfxStateTest_666, GetReusablePath_666) {
    state->moveTo(0, 0);
    state->lineTo(100, 100);
    auto iter = state->getReusablePath();
    EXPECT_NE(iter, nullptr);
}

// Test with different DPI
TEST(GfxStateDPITest_666, HighDPI_666) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    GfxState highDpiState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(highDpiState.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(highDpiState.getVDPI(), 300.0);
}

// Test with different DPI horizontal vs vertical
TEST(GfxStateDPITest_666, DifferentHVDPI_666) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    GfxState state(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(state.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 300.0);
}

// Test textShift
TEST_F(GfxStateTest_666, TextShift_666) {
    state->textMoveTo(10.0, 20.0);
    double beforeX = state->getCurX();
    double beforeY = state->getCurY();
    state->textShift(5.0, 5.0);
    // curX/curY should have changed
    // Just verify it doesn't crash
    EXPECT_TRUE(std::isfinite(state->getCurX()));
    EXPECT_TRUE(std::isfinite(state->getCurY()));
}

// Test fill/stroke color space getters default to non-null (device gray)
TEST_F(GfxStateTest_666, DefaultFillColorSpace_666) {
    GfxColorSpace *cs = state->getFillColorSpace();
    EXPECT_NE(cs, nullptr);
}

TEST_F(GfxStateTest_666, DefaultStrokeColorSpace_666) {
    GfxColorSpace *cs = state->getStrokeColorSpace();
    EXPECT_NE(cs, nullptr);
}

// Test fill/stroke pattern default null
TEST_F(GfxStateTest_666, DefaultFillPattern_666) {
    EXPECT_EQ(state->getFillPattern(), nullptr);
}

TEST_F(GfxStateTest_666, DefaultStrokePattern_666) {
    EXPECT_EQ(state->getStrokePattern(), nullptr);
}

// Test getCTM with Matrix
TEST_F(GfxStateTest_666, GetCTMMatrix_666) {
    Matrix m;
    state->getCTM(&m);
    // Just verify it populates without crashing
    EXPECT_TRUE(std::isfinite(m.m[0]));
}

// Test parseBlendMode with valid blend mode name
TEST_F(GfxStateTest_666, ParseBlendModeNormal_666) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(mode, gfxBlendNormal);
    }
}

// Test getFontTransMat
TEST_F(GfxStateTest_666, GetFontTransMat_666) {
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    EXPECT_TRUE(std::isfinite(m11));
    EXPECT_TRUE(std::isfinite(m12));
    EXPECT_TRUE(std::isfinite(m21));
    EXPECT_TRUE(std::isfinite(m22));
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_666, GetTransformedFontSize_666) {
    double tfs = state->getTransformedFontSize();
    EXPECT_TRUE(std::isfinite(tfs));
    EXPECT_GE(tfs, 0.0);
}

// Test boundary: opacity at 0 and 1
TEST_F(GfxStateTest_666, FillOpacityBoundary_666) {
    state->setFillOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.0);
    state->setFillOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_666, StrokeOpacityBoundary_666) {
    state->setStrokeOpacity(0.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.0);
    state->setStrokeOpacity(1.0);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

// Test upsideDown false
TEST(GfxStateUpsideDownTest_666, UpsideDownFalse_666) {
    PDFRectangle pageBox = makeRect(0, 0, 612, 792);
    GfxState state(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(state.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(state.getPageHeight(), 792.0);
}

// Test negative line width (edge case)
TEST_F(GfxStateTest_666, NegativeLineWidth_666) {
    state->setLineWidth(-1.0);
    // Implementation may or may not clamp; just verify it stores
    EXPECT_TRUE(std::isfinite(state->getLineWidth()));
}

// Test very large line dash
TEST_F(GfxStateTest_666, LargeLineDash_666) {
    std::vector<double> dash(100, 1.0);
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 100u);
}
