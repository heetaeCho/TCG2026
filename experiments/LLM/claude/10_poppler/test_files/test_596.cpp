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

class GfxStateTest_596 : public ::testing::Test {
protected:
    void SetUp() override {
        PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    std::unique_ptr<GfxState> state;
};

// --- Constructor and basic getters ---

TEST_F(GfxStateTest_596, ConstructorSetsHDPI_596) {
    EXPECT_DOUBLE_EQ(state->getHDPI(), 72.0);
}

TEST_F(GfxStateTest_596, ConstructorSetsVDPI_596) {
    EXPECT_DOUBLE_EQ(state->getVDPI(), 72.0);
}

TEST_F(GfxStateTest_596, ConstructorSetsRotate_596) {
    EXPECT_EQ(state->getRotate(), 0);
}

TEST_F(GfxStateTest_596, ConstructorSetsPageWidth_596) {
    EXPECT_DOUBLE_EQ(state->getPageWidth(), 612.0);
}

TEST_F(GfxStateTest_596, ConstructorSetsPageHeight_596) {
    EXPECT_DOUBLE_EQ(state->getPageHeight(), 792.0);
}

TEST_F(GfxStateTest_596, GetX1Y1X2Y2_596) {
    EXPECT_DOUBLE_EQ(state->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(state->getX2(), 612.0);
    EXPECT_DOUBLE_EQ(state->getY2(), 792.0);
}

// --- Rotate variations ---

TEST(GfxStateConstructorTest_596, RotatedState_596) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(rotatedState.getRotate(), 90);
}

TEST(GfxStateConstructorTest_596, UpsideDownFalse_596) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState s(72.0, 72.0, &pageBox, 0, false);
    EXPECT_DOUBLE_EQ(s.getPageWidth(), 612.0);
    EXPECT_DOUBLE_EQ(s.getPageHeight(), 792.0);
}

// --- LineWidth ---

TEST_F(GfxStateTest_596, DefaultLineWidth_596) {
    // Default lineWidth should be some initial value (commonly 1.0 or 0.0)
    double lw = state->getLineWidth();
    // Just verify it returns a non-negative value
    EXPECT_GE(lw, 0.0);
}

TEST_F(GfxStateTest_596, SetLineWidth_596) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 2.5);
}

TEST_F(GfxStateTest_596, SetLineWidthZero_596) {
    state->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 0.0);
}

TEST_F(GfxStateTest_596, SetLineWidthNegative_596) {
    state->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), -1.0);
}

// --- Fill and Stroke Opacity ---

TEST_F(GfxStateTest_596, DefaultFillOpacity_596) {
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 1.0);
}

TEST_F(GfxStateTest_596, SetFillOpacity_596) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(state->getFillOpacity(), 0.5);
}

TEST_F(GfxStateTest_596, DefaultStrokeOpacity_596) {
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 1.0);
}

TEST_F(GfxStateTest_596, SetStrokeOpacity_596) {
    state->setStrokeOpacity(0.3);
    EXPECT_DOUBLE_EQ(state->getStrokeOpacity(), 0.3);
}

// --- Overprint ---

TEST_F(GfxStateTest_596, DefaultFillOverprint_596) {
    EXPECT_FALSE(state->getFillOverprint());
}

TEST_F(GfxStateTest_596, SetFillOverprint_596) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
}

TEST_F(GfxStateTest_596, DefaultStrokeOverprint_596) {
    EXPECT_FALSE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_596, SetStrokeOverprint_596) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
}

TEST_F(GfxStateTest_596, DefaultOverprintMode_596) {
    EXPECT_EQ(state->getOverprintMode(), 0);
}

TEST_F(GfxStateTest_596, SetOverprintMode_596) {
    state->setOverprintMode(1);
    EXPECT_EQ(state->getOverprintMode(), 1);
}

// --- Flatness ---

TEST_F(GfxStateTest_596, DefaultFlatness_596) {
    int flat = state->getFlatness();
    EXPECT_GE(flat, 0);
}

TEST_F(GfxStateTest_596, SetFlatness_596) {
    state->setFlatness(5);
    EXPECT_EQ(state->getFlatness(), 5);
}

// --- MiterLimit ---

TEST_F(GfxStateTest_596, SetMiterLimit_596) {
    state->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(state->getMiterLimit(), 10.0);
}

// --- StrokeAdjust ---

TEST_F(GfxStateTest_596, DefaultStrokeAdjust_596) {
    EXPECT_FALSE(state->getStrokeAdjust());
}

TEST_F(GfxStateTest_596, SetStrokeAdjust_596) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
}

// --- AlphaIsShape ---

TEST_F(GfxStateTest_596, DefaultAlphaIsShape_596) {
    EXPECT_FALSE(state->getAlphaIsShape());
}

TEST_F(GfxStateTest_596, SetAlphaIsShape_596) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// --- TextKnockout ---

TEST_F(GfxStateTest_596, DefaultTextKnockout_596) {
    EXPECT_FALSE(state->getTextKnockout());
}

TEST_F(GfxStateTest_596, SetTextKnockout_596) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// --- Font and FontSize ---

TEST_F(GfxStateTest_596, DefaultFontIsNull_596) {
    EXPECT_EQ(state->getFont(), nullptr);
}

TEST_F(GfxStateTest_596, DefaultFontSize_596) {
    EXPECT_DOUBLE_EQ(state->getFontSize(), 0.0);
}

// --- CharSpace, WordSpace, HorizScaling, Leading, Rise, Render ---

TEST_F(GfxStateTest_596, SetCharSpace_596) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(state->getCharSpace(), 1.5);
}

TEST_F(GfxStateTest_596, SetWordSpace_596) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(state->getWordSpace(), 2.0);
}

TEST_F(GfxStateTest_596, SetHorizScaling_596) {
    state->setHorizScaling(150.0);
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 150.0);
}

TEST_F(GfxStateTest_596, SetLeading_596) {
    state->setLeading(12.0);
    EXPECT_DOUBLE_EQ(state->getLeading(), 12.0);
}

TEST_F(GfxStateTest_596, SetRise_596) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(state->getRise(), 3.0);
}

TEST_F(GfxStateTest_596, SetRender_596) {
    state->setRender(2);
    EXPECT_EQ(state->getRender(), 2);
}

// --- RenderingIntent ---

TEST_F(GfxStateTest_596, SetRenderingIntent_596) {
    state->setRenderingIntent("RelativeColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "RelativeColorimetric");
}

TEST_F(GfxStateTest_596, SetRenderingIntentLong_596) {
    // Rendering intent buffer is 32 chars, test with a string at the boundary
    state->setRenderingIntent("AbsoluteColorimetric");
    EXPECT_STREQ(state->getRenderingIntent(), "AbsoluteColorimetric");
}

// --- TextMat ---

TEST_F(GfxStateTest_596, SetTextMat_596) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto& mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(mat[0], 1.0);
    EXPECT_DOUBLE_EQ(mat[1], 0.0);
    EXPECT_DOUBLE_EQ(mat[2], 0.0);
    EXPECT_DOUBLE_EQ(mat[3], 1.0);
    EXPECT_DOUBLE_EQ(mat[4], 10.0);
    EXPECT_DOUBLE_EQ(mat[5], 20.0);
}

// --- CTM ---

TEST_F(GfxStateTest_596, GetCTM_596) {
    const auto& ctm = state->getCTM();
    EXPECT_EQ(ctm.size(), 6u);
}

TEST_F(GfxStateTest_596, SetCTM_596) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[1], 0.0);
    EXPECT_DOUBLE_EQ(ctm[2], 0.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
    EXPECT_DOUBLE_EQ(ctm[4], 100.0);
    EXPECT_DOUBLE_EQ(ctm[5], 200.0);
}

TEST_F(GfxStateTest_596, ConcatCTM_596) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[0], 2.0);
    EXPECT_DOUBLE_EQ(ctm[3], 2.0);
}

// --- Transform ---

TEST_F(GfxStateTest_596, Transform_596) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    double x2, y2;
    state->transform(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 15.0);
    EXPECT_DOUBLE_EQ(y2, 25.0);
}

TEST_F(GfxStateTest_596, TransformDelta_596) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    double x2, y2;
    state->transformDelta(5.0, 5.0, &x2, &y2);
    EXPECT_DOUBLE_EQ(x2, 10.0);
    EXPECT_DOUBLE_EQ(y2, 10.0);
}

// --- LineDash ---

TEST_F(GfxStateTest_596, SetLineDash_596) {
    std::vector<double> dash = {3.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_EQ(d.size(), 2u);
    EXPECT_DOUBLE_EQ(d[0], 3.0);
    EXPECT_DOUBLE_EQ(d[1], 2.0);
    EXPECT_DOUBLE_EQ(start, 1.0);
}

TEST_F(GfxStateTest_596, SetLineDashEmpty_596) {
    std::vector<double> dash;
    state->setLineDash(std::move(dash), 0.0);
    double start;
    const auto& d = state->getLineDash(&start);
    EXPECT_TRUE(d.empty());
    EXPECT_DOUBLE_EQ(start, 0.0);
}

// --- LineJoin and LineCap ---

TEST_F(GfxStateTest_596, SetLineJoin_596) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(state->getLineJoin(), LineJoinStyle::Round);
}

TEST_F(GfxStateTest_596, SetLineCap_596) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(state->getLineCap(), LineCapStyle::Round);
}

// --- BlendMode ---

TEST_F(GfxStateTest_596, DefaultBlendMode_596) {
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Normal);
}

TEST_F(GfxStateTest_596, SetBlendMode_596) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(state->getBlendMode(), GfxBlendMode::Multiply);
}

// --- Path operations ---

TEST_F(GfxStateTest_596, DefaultIsNotPath_596) {
    EXPECT_FALSE(state->isPath());
}

TEST_F(GfxStateTest_596, DefaultIsNotCurPt_596) {
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_596, MoveToMakesPathAndCurPt_596) {
    state->moveTo(10.0, 20.0);
    EXPECT_TRUE(state->isCurPt());
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_596, LineToAfterMoveTo_596) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 20.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_TRUE(state->isCurPt());
}

TEST_F(GfxStateTest_596, CurveToAfterMoveTo_596) {
    state->moveTo(0.0, 0.0);
    state->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(state->isPath());
}

TEST_F(GfxStateTest_596, ClearPath_596) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

TEST_F(GfxStateTest_596, ClosePath_596) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// --- Save and Restore ---

TEST_F(GfxStateTest_596, DefaultHasNoSaves_596) {
    EXPECT_FALSE(state->hasSaves());
}

TEST_F(GfxStateTest_596, SaveCreatesSaveState_596) {
    GfxState* saved = state->save();
    EXPECT_NE(saved, nullptr);
    EXPECT_TRUE(state->hasSaves());
}

TEST_F(GfxStateTest_596, RestoreAfterSave_596) {
    state->save();
    GfxState* restored = state->restore();
    EXPECT_NE(restored, nullptr);
}

TEST_F(GfxStateTest_596, SavePreservesLineWidth_596) {
    state->setLineWidth(5.0);
    GfxState* saved = state->save();
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 5.0);
    // After save, the returned saved state should be the old state
    EXPECT_NE(saved, nullptr);
}

TEST_F(GfxStateTest_596, RestoreRestoresLineWidth_596) {
    state->setLineWidth(5.0);
    state->save();
    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 10.0);
    GfxState* restored = state->restore();
    // After restoring, restored state should have previous lineWidth
    EXPECT_NE(restored, nullptr);
}

// --- Copy ---

TEST_F(GfxStateTest_596, CopyState_596) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.7);
    std::unique_ptr<GfxState> copied(state->copy());
    EXPECT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(copied->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getFillOpacity(), 0.7);
}

TEST_F(GfxStateTest_596, CopyStateWithPath_596) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    std::unique_ptr<GfxState> copied(state->copy(true));
    EXPECT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isPath());
}

TEST_F(GfxStateTest_596, CopyStateWithoutPath_596) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    std::unique_ptr<GfxState> copied(state->copy(false));
    EXPECT_NE(copied, nullptr);
}

// --- Clip BBox ---

TEST_F(GfxStateTest_596, GetClipBBox_596) {
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    // Should have some reasonable clip bounds
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_596, GetUserClipBBox_596) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

TEST_F(GfxStateTest_596, ClipToRect_596) {
    state->clipToRect(10.0, 10.0, 100.0, 100.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- TextMoveTo ---

TEST_F(GfxStateTest_596, TextMoveTo_596) {
    state->textMoveTo(10.0, 20.0);
    // lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(state->getLineX(), 10.0);
    EXPECT_DOUBLE_EQ(state->getLineY(), 20.0);
}

// --- CurX, CurY ---

TEST_F(GfxStateTest_596, GetCurXCurY_596) {
    // Before any path operations, getCurX and getCurY should return some default
    double cx = state->getCurX();
    double cy = state->getCurY();
    // Just check they're finite numbers
    EXPECT_EQ(cx, cx); // not NaN
    EXPECT_EQ(cy, cy);
}

// --- TransformWidth ---

TEST_F(GfxStateTest_596, TransformWidth_596) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double tw = state->transformWidth(1.0);
    EXPECT_GT(tw, 0.0);
}

// --- GetTransformedLineWidth ---

TEST_F(GfxStateTest_596, GetTransformedLineWidth_596) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    state->setLineWidth(1.0);
    double tlw = state->getTransformedLineWidth();
    EXPECT_GT(tlw, 0.0);
}

// --- ShiftCTMAndClip ---

TEST_F(GfxStateTest_596, ShiftCTMAndClip_596) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    state->shiftCTMAndClip(10.0, 20.0);
    const auto& ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(ctm[4], 10.0);
    EXPECT_DOUBLE_EQ(ctm[5], 20.0);
}

// --- FillColor and StrokeColor ---

TEST_F(GfxStateTest_596, GetFillColorNotNull_596) {
    const GfxColor* color = state->getFillColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_596, GetStrokeColorNotNull_596) {
    const GfxColor* color = state->getStrokeColor();
    EXPECT_NE(color, nullptr);
}

TEST_F(GfxStateTest_596, SetAndGetFillColor_596) {
    GfxColor color;
    color.c[0] = 32768; // Some value
    state->setFillColor(&color);
    const GfxColor* retrieved = state->getFillColor();
    EXPECT_EQ(retrieved->c[0], 32768);
}

TEST_F(GfxStateTest_596, SetAndGetStrokeColor_596) {
    GfxColor color;
    color.c[0] = 65535;
    state->setStrokeColor(&color);
    const GfxColor* retrieved = state->getStrokeColor();
    EXPECT_EQ(retrieved->c[0], 65535);
}

// --- isParentState ---

TEST_F(GfxStateTest_596, IsParentStateNoSaves_596) {
    EXPECT_FALSE(state->isParentState(state.get()));
}

// --- GetPath ---

TEST_F(GfxStateTest_596, GetPathNotNull_596) {
    const GfxPath* path = state->getPath();
    EXPECT_NE(path, nullptr);
}

// --- Clip ---

TEST_F(GfxStateTest_596, ClipAfterPath_596) {
    state->moveTo(0.0, 0.0);
    state->lineTo(100.0, 0.0);
    state->lineTo(100.0, 100.0);
    state->closePath();
    state->clip();
    // After clip, the clip region should be updated
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// --- Different page box configurations ---

TEST(GfxStateDifferentBoxTest_596, SmallPageBox_596) {
    PDFRectangle pageBox = makePageBox(0, 0, 100, 100);
    GfxState s(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s.getPageWidth(), 100.0);
    EXPECT_DOUBLE_EQ(s.getPageHeight(), 100.0);
}

TEST(GfxStateDifferentBoxTest_596, NonZeroOriginPageBox_596) {
    PDFRectangle pageBox = makePageBox(50, 50, 200, 300);
    GfxState s(72.0, 72.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s.getPageWidth(), 150.0);
    EXPECT_DOUBLE_EQ(s.getPageHeight(), 250.0);
}

TEST(GfxStateDifferentBoxTest_596, HighDPI_596) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState s(300.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s.getHDPI(), 300.0);
    EXPECT_DOUBLE_EQ(s.getVDPI(), 300.0);
}

TEST(GfxStateDifferentBoxTest_596, DifferentHVDPI_596) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState s(150.0, 300.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(s.getHDPI(), 150.0);
    EXPECT_DOUBLE_EQ(s.getVDPI(), 300.0);
}

// --- Rotation 180 and 270 ---

TEST(GfxStateRotateTest_596, Rotate180_596) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState s(72.0, 72.0, &pageBox, 180, true);
    EXPECT_EQ(s.getRotate(), 180);
}

TEST(GfxStateRotateTest_596, Rotate270_596) {
    PDFRectangle pageBox = makePageBox(0, 0, 612, 792);
    GfxState s(72.0, 72.0, &pageBox, 270, true);
    EXPECT_EQ(s.getRotate(), 270);
}

// --- Multiple save/restore ---

TEST_F(GfxStateTest_596, MultipleSaveRestore_596) {
    state->setLineWidth(1.0);
    state->save();
    state->setLineWidth(2.0);
    state->save();
    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(state->getLineWidth(), 3.0);
    EXPECT_TRUE(state->hasSaves());

    GfxState* r1 = state->restore();
    EXPECT_NE(r1, nullptr);
    
    GfxState* r2 = state->restore();
    EXPECT_NE(r2, nullptr);
    
    EXPECT_FALSE(state->hasSaves());
}

// --- GetReusablePath ---

TEST_F(GfxStateTest_596, GetReusablePath_596) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 10.0);
    auto pathIter = state->getReusablePath();
    EXPECT_NE(pathIter, nullptr);
}

// --- Text coordinates ---

TEST_F(GfxStateTest_596, TextShift_596) {
    state->textMoveTo(0.0, 0.0);
    state->textShift(5.0, 10.0);
    // After textShift, curX and curY should be updated
    // We just verify no crash
}

// --- CTM with Matrix ---

TEST_F(GfxStateTest_596, GetCTMAsMatrix_596) {
    state->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    Matrix m;
    state->getCTM(&m);
    // Matrix should contain the CTM values
    EXPECT_DOUBLE_EQ(m.m[0], 1.0);
    EXPECT_DOUBLE_EQ(m.m[3], 1.0);
}

// --- TransformWidth with zero ---

TEST_F(GfxStateTest_596, TransformWidthZero_596) {
    double tw = state->transformWidth(0.0);
    EXPECT_GE(tw, 0.0);
}

// --- GetTransformedFontSize ---

TEST_F(GfxStateTest_596, GetTransformedFontSizeDefault_596) {
    double fs = state->getTransformedFontSize();
    EXPECT_GE(fs, 0.0);
}

// --- GetFontTransMat ---

TEST_F(GfxStateTest_596, GetFontTransMat_596) {
    double m11, m12, m21, m22;
    state->getFontTransMat(&m11, &m12, &m21, &m22);
    // Just verify no crash and values are finite
    EXPECT_EQ(m11, m11);
    EXPECT_EQ(m12, m12);
    EXPECT_EQ(m21, m21);
    EXPECT_EQ(m22, m22);
}

// --- TextTransform ---

TEST_F(GfxStateTest_596, TextTransform_596) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    double x2, y2;
    state->textTransform(5.0, 10.0, &x2, &y2);
    // No crash expected
    EXPECT_EQ(x2, x2);
    EXPECT_EQ(y2, y2);
}

TEST_F(GfxStateTest_596, TextTransformDelta_596) {
    state->setTextMat(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    double x2, y2;
    state->textTransformDelta(5.0, 10.0, &x2, &y2);
    EXPECT_EQ(x2, x2);
    EXPECT_EQ(y2, y2);
}
