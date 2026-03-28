#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Object.h"

// Helper to create a PDFRectangle
static PDFRectangle makePageBox(double x1, double y1, double x2, double y2) {
    PDFRectangle r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;
    return r;
}

class GfxStateTest_585 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test constructor sets DPI values correctly
TEST_F(GfxStateTest_585, ConstructorSetsDPI_585) {
    EXPECT_DOUBLE_EQ(72.0, state->getHDPI());
    EXPECT_DOUBLE_EQ(72.0, state->getVDPI());
}

// Test constructor sets page dimensions
TEST_F(GfxStateTest_585, ConstructorSetsPageDimensions_585) {
    EXPECT_DOUBLE_EQ(612.0, state->getPageWidth());
    EXPECT_DOUBLE_EQ(792.0, state->getPageHeight());
}

// Test constructor sets rotation
TEST_F(GfxStateTest_585, ConstructorSetsRotation_585) {
    EXPECT_EQ(0, state->getRotate());
}

// Test page box coordinates
TEST_F(GfxStateTest_585, ConstructorSetsPageBox_585) {
    EXPECT_DOUBLE_EQ(0.0, state->getX1());
    EXPECT_DOUBLE_EQ(0.0, state->getY1());
    EXPECT_DOUBLE_EQ(612.0, state->getX2());
    EXPECT_DOUBLE_EQ(792.0, state->getY2());
}

// Test default fill opacity
TEST_F(GfxStateTest_585, DefaultFillOpacity_585) {
    EXPECT_DOUBLE_EQ(1.0, state->getFillOpacity());
}

// Test default stroke opacity
TEST_F(GfxStateTest_585, DefaultStrokeOpacity_585) {
    EXPECT_DOUBLE_EQ(1.0, state->getStrokeOpacity());
}

// Test set and get fill opacity
TEST_F(GfxStateTest_585, SetGetFillOpacity_585) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(0.5, state->getFillOpacity());
}

// Test set and get stroke opacity
TEST_F(GfxStateTest_585, SetGetStrokeOpacity_585) {
    state->setStrokeOpacity(0.25);
    EXPECT_DOUBLE_EQ(0.25, state->getStrokeOpacity());
}

// Test default line width
TEST_F(GfxStateTest_585, DefaultLineWidth_585) {
    EXPECT_DOUBLE_EQ(1.0, state->getLineWidth());
}

// Test set and get line width
TEST_F(GfxStateTest_585, SetGetLineWidth_585) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(2.5, state->getLineWidth());
}

// Test set line width to zero (boundary)
TEST_F(GfxStateTest_585, SetLineWidthZero_585) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, state->getLineWidth());
}

// Test default miter limit
TEST_F(GfxStateTest_585, DefaultMiterLimit_585) {
    EXPECT_DOUBLE_EQ(10.0, state->getMiterLimit());
}

// Test set and get miter limit
TEST_F(GfxStateTest_585, SetGetMiterLimit_585) {
    state->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(5.0, state->getMiterLimit());
}

// Test default flatness
TEST_F(GfxStateTest_585, DefaultFlatness_585) {
    EXPECT_EQ(1, state->getFlatness());
}

// Test set and get flatness
TEST_F(GfxStateTest_585, SetGetFlatness_585) {
    state->setFlatness(50);
    EXPECT_EQ(50, state->getFlatness());
}

// Test default line join
TEST_F(GfxStateTest_585, DefaultLineJoin_585) {
    EXPECT_EQ(0, static_cast<int>(state->getLineJoin()));
}

// Test set and get line join
TEST_F(GfxStateTest_585, SetGetLineJoin_585) {
    state->setLineJoin(static_cast<LineJoinStyle>(1));
    EXPECT_EQ(1, static_cast<int>(state->getLineJoin()));
}

// Test default line cap
TEST_F(GfxStateTest_585, DefaultLineCap_585) {
    EXPECT_EQ(0, static_cast<int>(state->getLineCap()));
}

// Test set and get line cap
TEST_F(GfxStateTest_585, SetGetLineCap_585) {
    state->setLineCap(static_cast<LineCapStyle>(2));
    EXPECT_EQ(2, static_cast<int>(state->getLineCap()));
}

// Test default fill overprint
TEST_F(GfxStateTest_585, DefaultFillOverprint_585) {
    EXPECT_FALSE(state->getFillOverprint());
}

// Test set and get fill overprint
TEST_F(GfxStateTest_585, SetGetFillOverprint_585) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

// Test default stroke overprint
TEST_F(GfxStateTest_585, DefaultStrokeOverprint_585) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test set and get stroke overprint
TEST_F(GfxStateTest_585, SetGetStrokeOverprint_585) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

// Test default overprint mode
TEST_F(GfxStateTest_585, DefaultOverprintMode_585) {
    EXPECT_EQ(0, state->getOverprintMode());
}

// Test set and get overprint mode
TEST_F(GfxStateTest_585, SetGetOverprintMode_585) {
    state->setOverprintMode(1);
    EXPECT_EQ(1, state->getOverprintMode());
}

// Test default stroke adjust
TEST_F(GfxStateTest_585, DefaultStrokeAdjust_585) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test set and get stroke adjust
TEST_F(GfxStateTest_585, SetGetStrokeAdjust_585) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// Test default alpha is shape
TEST_F(GfxStateTest_585, DefaultAlphaIsShape_585) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

// Test set and get alpha is shape
TEST_F(GfxStateTest_585, SetGetAlphaIsShape_585) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test default text knockout
TEST_F(GfxStateTest_585, DefaultTextKnockout_585) {
    EXPECT_FALSE(state->getTextKnockout());
}

// Test set and get text knockout
TEST_F(GfxStateTest_585, SetGetTextKnockout_585) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test default char space
TEST_F(GfxStateTest_585, DefaultCharSpace_585) {
    EXPECT_DOUBLE_EQ(0.0, state->getCharSpace());
}

// Test set and get char space
TEST_F(GfxStateTest_585, SetGetCharSpace_585) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(1.5, state->getCharSpace());
}

// Test default word space
TEST_F(GfxStateTest_585, DefaultWordSpace_585) {
    EXPECT_DOUBLE_EQ(0.0, state->getWordSpace());
}

// Test set and get word space
TEST_F(GfxStateTest_585, SetGetWordSpace_585) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(2.0, state->getWordSpace());
}

// Test default horiz scaling
TEST_F(GfxStateTest_585, DefaultHorizScaling_585) {
    EXPECT_DOUBLE_EQ(1.0, state->getHorizScaling());
}

// Test set and get horiz scaling
TEST_F(GfxStateTest_585, SetGetHorizScaling_585) {
    state->setHorizScaling(0.8);
    EXPECT_DOUBLE_EQ(0.8, state->getHorizScaling());
}

// Test default leading
TEST_F(GfxStateTest_585, DefaultLeading_585) {
    EXPECT_DOUBLE_EQ(0.0, state->getLeading());
}

// Test set and get leading
TEST_F(GfxStateTest_585, SetGetLeading_585) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(12.0, state->getLeading());
}

// Test default rise
TEST_F(GfxStateTest_585, DefaultRise_585) {
    EXPECT_DOUBLE_EQ(0.0, state->getRise());
}

// Test set and get rise
TEST_F(GfxStateTest_585, SetGetRise_585) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getRise());
}

// Test default render
TEST_F(GfxStateTest_585, DefaultRender_585) {
    EXPECT_EQ(0, state->getRender());
}

// Test set and get render
TEST_F(GfxStateTest_585, SetGetRender_585) {
    state->setRender(2);
    EXPECT_EQ(2, state->getRender());
}

// Test default font size
TEST_F(GfxStateTest_585, DefaultFontSize_585) {
    EXPECT_DOUBLE_EQ(0.0, state->getFontSize());
}

// Test default font is null
TEST_F(GfxStateTest_585, DefaultFontIsNull_585) {
    EXPECT_EQ(nullptr, state->getFont().get());
}

// Test save and restore
TEST_F(GfxStateTest_585, SaveAndRestore_585) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());

    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(10.0, state->getLineWidth());

    GfxState *restored = state->restore();
    // After restore, the state should have the saved line width
    EXPECT_DOUBLE_EQ(5.0, state->getLineWidth());
}

// Test hasSaves initially false
TEST_F(GfxStateTest_585, HasSavesInitiallyFalse_585) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_585, HasSavesAfterSave_585) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_585, SetGetCTM_585) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(10.0, ctm[4]);
    EXPECT_DOUBLE_EQ(20.0, ctm[5]);
}

// Test transform
TEST_F(GfxStateTest_585, TransformIdentity_585) {
    // Default CTM should be set based on constructor params
    double x2, y2;
    state->transform(0, 0, &x2, &y2);
    // Result depends on the CTM set by constructor; just verify it doesn't crash
    // and produces finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test transformDelta
TEST_F(GfxStateTest_585, TransformDelta_585) {
    double x2, y2;
    state->transformDelta(1.0, 0.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test moveTo and path state
TEST_F(GfxStateTest_585, MoveToCreatesCurrentPoint_585) {
    state->moveTo(100.0, 200.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test initially no current point
TEST_F(GfxStateTest_585, InitiallyNoCurPt_585) {
    EXPECT_FALSE(state->isCurPt());
}

// Test initially no path
TEST_F(GfxStateTest_585, InitiallyNoPath_585) {
    EXPECT_FALSE(state->isPath());
}

// Test lineTo after moveTo
TEST_F(GfxStateTest_585, LineToAfterMoveTo_585) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test curveTo after moveTo
TEST_F(GfxStateTest_585, CurveToAfterMoveTo_585) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

// Test closePath after moveTo and lineTo
TEST_F(GfxStateTest_585, ClosePath_585) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test clearPath
TEST_F(GfxStateTest_585, ClearPath_585) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->clearPath();
    EXPECT_FALSE(state->isCurPt());
    EXPECT_FALSE(state->isPath());
}

// Test clip bounding box
TEST_F(GfxStateTest_585, GetClipBBox_585) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test getUserClipBBox
TEST_F(GfxStateTest_585, GetUserClipBBox_585) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test setRenderingIntent and getRenderingIntent
TEST_F(GfxStateTest_585, SetGetRenderingIntent_585) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ("Perceptual", state->getRenderingIntent());
}

// Test setRenderingIntent with different values
TEST_F(GfxStateTest_585, SetGetRenderingIntentRelativeColorimetric_585) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ("RelativeColorimetric", state->getRenderingIntent());
}

// Test setRenderingIntent with long string (boundary - renderingIntent is char[32])
TEST_F(GfxStateTest_585, SetRenderingIntentLongString_585) {
    // Should truncate or handle gracefully
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ("AbsoluteColorimetric", state->getRenderingIntent());
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_585, SetGetTextMat_585) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &tm = state->getTextMat();
    EXPECT_DOUBLE_EQ(1.0, tm[0]);
    EXPECT_DOUBLE_EQ(0.0, tm[1]);
    EXPECT_DOUBLE_EQ(0.0, tm[2]);
    EXPECT_DOUBLE_EQ(1.0, tm[3]);
    EXPECT_DOUBLE_EQ(10.0, tm[4]);
    EXPECT_DOUBLE_EQ(20.0, tm[5]);
}

// Test textMoveTo
TEST_F(GfxStateTest_585, TextMoveTo_585) {
    state->textMoveTo(5.0, 10.0);
    // After textMoveTo, lineX and lineY should be updated
    EXPECT_TRUE(std::isfinite(state->getLineX()));
    EXPECT_TRUE(std::isfinite(state->getLineY()));
}

// Test concatCTM
TEST_F(GfxStateTest_585, ConcatCTM_585) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 5.0, 10.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(5.0, ctm[4]);
    EXPECT_DOUBLE_EQ(10.0, ctm[5]);
}

// Test getPath returns non-null
TEST_F(GfxStateTest_585, GetPathNotNull_585) {
    EXPECT_NE(nullptr, state->getPath());
}

// Test getCurX and getCurY defaults
TEST_F(GfxStateTest_585, DefaultCurXY_585) {
    EXPECT_DOUBLE_EQ(0.0, state->getCurX());
    EXPECT_DOUBLE_EQ(0.0, state->getCurY());
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_585, SetGetLineDash_585) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(1.0, start);
    ASSERT_EQ(2u, result.size());
    EXPECT_DOUBLE_EQ(3.0, result[0]);
    EXPECT_DOUBLE_EQ(5.0, result[1]);
}

// Test empty line dash
TEST_F(GfxStateTest_585, EmptyLineDash_585) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto &result = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(0.0, start);
    EXPECT_EQ(0u, result.size());
}

// Test setFillColor and getFillColor
TEST_F(GfxStateTest_585, SetGetFillColor_585) {
    GfxColor color;
    color.c[0] = 32768; // 0.5 in fixed point
    state->setFillColor(&color);
    const GfxColor *result = state->getFillColor();
    EXPECT_EQ(color.c[0], result->c[0]);
}

// Test setStrokeColor and getStrokeColor
TEST_F(GfxStateTest_585, SetGetStrokeColor_585) {
    GfxColor color;
    color.c[0] = 16384;
    state->setStrokeColor(&color);
    const GfxColor *result = state->getStrokeColor();
    EXPECT_EQ(color.c[0], result->c[0]);
}

// Test setBlendMode and getBlendMode
TEST_F(GfxStateTest_585, SetGetBlendMode_585) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(GfxBlendMode::Multiply, state->getBlendMode());
}

// Test default blend mode is Normal
TEST_F(GfxStateTest_585, DefaultBlendModeNormal_585) {
    EXPECT_EQ(GfxBlendMode::Normal, state->getBlendMode());
}

// Test copy
TEST_F(GfxStateTest_585, CopyState_585) {
    state->setLineWidth(7.5);
    state->setFillOpacity(0.3);
    auto *copied = state->copy();
    ASSERT_NE(nullptr, copied);
    EXPECT_DOUBLE_EQ(7.5, copied->getLineWidth());
    EXPECT_DOUBLE_EQ(0.3, copied->getFillOpacity());
    delete copied;
}

// Test clipToRect
TEST_F(GfxStateTest_585, ClipToRect_585) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Clip should be intersected; just verify finite values
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
}

// Test transformWidth
TEST_F(GfxStateTest_585, TransformWidth_585) {
    double w = state->transformWidth(1.0);
    EXPECT_TRUE(std::isfinite(w));
    EXPECT_GE(w, 0.0);
}

// Test getTransformedLineWidth
TEST_F(GfxStateTest_585, GetTransformedLineWidth_585) {
    state->setLineWidth(2.0);
    double tw = state->getTransformedLineWidth();
    EXPECT_TRUE(std::isfinite(tw));
    EXPECT_GE(tw, 0.0);
}

// Test with rotation
TEST_F(GfxStateTest_585, ConstructorWithRotation90_585) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(90, rotState.getRotate());
    EXPECT_DOUBLE_EQ(612.0, rotState.getPageWidth());
    EXPECT_DOUBLE_EQ(792.0, rotState.getPageHeight());
}

// Test with rotation 180
TEST_F(GfxStateTest_585, ConstructorWithRotation180_585) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotState(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(180, rotState.getRotate());
}

// Test with rotation 270
TEST_F(GfxStateTest_585, ConstructorWithRotation270_585) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotState(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(270, rotState.getRotate());
}

// Test with different DPI values
TEST_F(GfxStateTest_585, DifferentDPIValues_585) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState hiDpiState(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(300.0, hiDpiState.getHDPI());
    EXPECT_DOUBLE_EQ(300.0, hiDpiState.getVDPI());
}

// Test with non-square DPI
TEST_F(GfxStateTest_585, NonSquareDPI_585) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState nsState(72.0, 144.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(72.0, nsState.getHDPI());
    EXPECT_DOUBLE_EQ(144.0, nsState.getVDPI());
}

// Test fill color space initially not null (default DeviceGray)
TEST_F(GfxStateTest_585, DefaultFillColorSpaceNotNull_585) {
    EXPECT_NE(nullptr, state->getFillColorSpace());
}

// Test stroke color space initially not null
TEST_F(GfxStateTest_585, DefaultStrokeColorSpaceNotNull_585) {
    EXPECT_NE(nullptr, state->getStrokeColorSpace());
}

// Test fill pattern initially null
TEST_F(GfxStateTest_585, DefaultFillPatternNull_585) {
    EXPECT_EQ(nullptr, state->getFillPattern());
}

// Test stroke pattern initially null
TEST_F(GfxStateTest_585, DefaultStrokePatternNull_585) {
    EXPECT_EQ(nullptr, state->getStrokePattern());
}

// Test multiple save/restore cycles
TEST_F(GfxStateTest_585, MultipleSaveRestore_585) {
    state->setLineWidth(1.0);
    state->save();
    state->setLineWidth(2.0);
    state->save();
    state->setLineWidth(3.0);

    EXPECT_DOUBLE_EQ(3.0, state->getLineWidth());
    EXPECT_TRUE(state->hasSaves());

    state->restore();
    EXPECT_DOUBLE_EQ(2.0, state->getLineWidth());
    EXPECT_TRUE(state->hasSaves());

    state->restore();
    EXPECT_DOUBLE_EQ(1.0, state->getLineWidth());
    EXPECT_FALSE(state->hasSaves());
}

// Test getTransformedFontSize
TEST_F(GfxStateTest_585, GetTransformedFontSize_585) {
    double fs = state->getTransformedFontSize();
    EXPECT_TRUE(std::isfinite(fs));
}

// Test getFontTransMat
TEST_F(GfxStateTest_585, GetFontTransMat_585) {
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    EXPECT_TRUE(std::isfinite(m11));
    EXPECT_TRUE(std::isfinite(m12));
    EXPECT_TRUE(std::isfinite(m21));
    EXPECT_TRUE(std::isfinite(m22));
}

// Test textTransform
TEST_F(GfxStateTest_585, TextTransform_585) {
    double x2, y2;
    state->textTransform(1.0, 1.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test textTransformDelta
TEST_F(GfxStateTest_585, TextTransformDelta_585) {
    double x2, y2;
    state->textTransformDelta(1.0, 0.0, &x2, &y2);
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test shiftCTMAndClip
TEST_F(GfxStateTest_585, ShiftCTMAndClip_585) {
    state->shiftCTMAndClip(10.0, 20.0);
    const auto &ctm = state->getCTM();
    EXPECT_TRUE(std::isfinite(ctm[4]));
    EXPECT_TRUE(std::isfinite(ctm[5]));
}

// Test parseBlendMode with Normal
TEST_F(GfxStateTest_585, ParseBlendModeNormal_585) {
    Object obj;
    obj = Object(new GooString("Normal"));
    GfxBlendMode mode;
    bool result = GfxState::parseBlendMode(&obj, &mode);
    if (result) {
        EXPECT_EQ(GfxBlendMode::Normal, mode);
    }
}

// Test getReusablePath
TEST_F(GfxStateTest_585, GetReusablePath_585) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto iter = state->getReusablePath();
    EXPECT_NE(nullptr, iter.get());
}

// Test getCTM with Matrix output
TEST_F(GfxStateTest_585, GetCTMMatrix_585) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    Matrix m;
    state->getCTM(&m);
    EXPECT_DOUBLE_EQ(1.0, m.m[0]);
    EXPECT_DOUBLE_EQ(0.0, m.m[1]);
    EXPECT_DOUBLE_EQ(0.0, m.m[2]);
    EXPECT_DOUBLE_EQ(1.0, m.m[3]);
}

// Test upsideDown false
TEST_F(GfxStateTest_585, ConstructorUpsideDownFalse_585) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState udState(72.0, 72.0, &pageBox, 0, false);
    // Just ensure construction succeeds and basic properties work
    EXPECT_DOUBLE_EQ(72.0, udState.getHDPI());
    EXPECT_DOUBLE_EQ(72.0, udState.getVDPI());
}

// Test isParentState
TEST_F(GfxStateTest_585, IsParentState_585) {
    state->save();
    // After save, the current state's saved pointer should point to previous
    // isParentState checks if a state is an ancestor
    EXPECT_FALSE(state->isParentState(state.get()));
}
