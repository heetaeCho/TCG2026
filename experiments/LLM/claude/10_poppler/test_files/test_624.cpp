#include <gtest/gtest.h>
#include "GfxState.h"

// Helper to create a GfxState with reasonable defaults
class GfxStateTest_624 : public ::testing::Test {
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

// Test isPath() on a fresh GfxState (no path operations done)
TEST_F(GfxStateTest_624, IsPathReturnsFalseOnFreshState_624) {
    // A freshly created GfxState should not have a path
    EXPECT_FALSE(state->isPath());
}

// Test isPath() after moveTo only (moveTo alone is not a path)
TEST_F(GfxStateTest_624, IsPathReturnsFalseAfterMoveToOnly_624) {
    state->moveTo(10.0, 20.0);
    EXPECT_FALSE(state->isPath());
}

// Test isPath() after moveTo and lineTo (this creates an actual path)
TEST_F(GfxStateTest_624, IsPathReturnsTrueAfterLineTo_624) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
}

// Test isPath() after moveTo and curveTo
TEST_F(GfxStateTest_624, IsPathReturnsTrueAfterCurveTo_624) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
}

// Test isPath() after clearPath resets the path state
TEST_F(GfxStateTest_624, IsPathReturnsFalseAfterClearPath_624) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    EXPECT_TRUE(state->isPath());
    state->clearPath();
    EXPECT_FALSE(state->isPath());
}

// Test isCurPt() on fresh state
TEST_F(GfxStateTest_624, IsCurPtReturnsFalseOnFreshState_624) {
    EXPECT_FALSE(state->isCurPt());
}

// Test isCurPt() after moveTo
TEST_F(GfxStateTest_624, IsCurPtReturnsTrueAfterMoveTo_624) {
    state->moveTo(5.0, 10.0);
    EXPECT_TRUE(state->isCurPt());
}

// Test basic getters after construction
TEST_F(GfxStateTest_624, GetHDPIReturnsCorrectValue_624) {
    EXPECT_DOUBLE_EQ(72.0, state->getHDPI());
}

TEST_F(GfxStateTest_624, GetVDPIReturnsCorrectValue_624) {
    EXPECT_DOUBLE_EQ(72.0, state->getVDPI());
}

TEST_F(GfxStateTest_624, GetPageWidthReturnsCorrectValue_624) {
    EXPECT_DOUBLE_EQ(612.0, state->getPageWidth());
}

TEST_F(GfxStateTest_624, GetPageHeightReturnsCorrectValue_624) {
    EXPECT_DOUBLE_EQ(792.0, state->getPageHeight());
}

TEST_F(GfxStateTest_624, GetRotateReturnsCorrectValue_624) {
    EXPECT_EQ(0, state->getRotate());
}

// Test line width set/get
TEST_F(GfxStateTest_624, SetAndGetLineWidth_624) {
    state->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(2.5, state->getLineWidth());
}

// Test fill opacity set/get
TEST_F(GfxStateTest_624, SetAndGetFillOpacity_624) {
    state->setFillOpacity(0.5);
    EXPECT_DOUBLE_EQ(0.5, state->getFillOpacity());
}

// Test stroke opacity set/get
TEST_F(GfxStateTest_624, SetAndGetStrokeOpacity_624) {
    state->setStrokeOpacity(0.75);
    EXPECT_DOUBLE_EQ(0.75, state->getStrokeOpacity());
}

// Test flatness set/get
TEST_F(GfxStateTest_624, SetAndGetFlatness_624) {
    state->setFlatness(5);
    EXPECT_EQ(5, state->getFlatness());
}

// Test line join set/get
TEST_F(GfxStateTest_624, SetAndGetLineJoin_624) {
    state->setLineJoin(LineJoinStyle::Round);
    EXPECT_EQ(LineJoinStyle::Round, state->getLineJoin());
}

// Test line cap set/get
TEST_F(GfxStateTest_624, SetAndGetLineCap_624) {
    state->setLineCap(LineCapStyle::Round);
    EXPECT_EQ(LineCapStyle::Round, state->getLineCap());
}

// Test miter limit set/get
TEST_F(GfxStateTest_624, SetAndGetMiterLimit_624) {
    state->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(15.0, state->getMiterLimit());
}

// Test char space set/get
TEST_F(GfxStateTest_624, SetAndGetCharSpace_624) {
    state->setCharSpace(1.5);
    EXPECT_DOUBLE_EQ(1.5, state->getCharSpace());
}

// Test word space set/get
TEST_F(GfxStateTest_624, SetAndGetWordSpace_624) {
    state->setWordSpace(2.0);
    EXPECT_DOUBLE_EQ(2.0, state->getWordSpace());
}

// Test horiz scaling set/get
TEST_F(GfxStateTest_624, SetAndGetHorizScaling_624) {
    state->setHorizScaling(1.5);
    EXPECT_DOUBLE_EQ(1.5, state->getHorizScaling());
}

// Test leading set/get
TEST_F(GfxStateTest_624, SetAndGetLeading_624) {
    state->setLeading(14.0);
    EXPECT_DOUBLE_EQ(14.0, state->getLeading());
}

// Test rise set/get
TEST_F(GfxStateTest_624, SetAndGetRise_624) {
    state->setRise(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getRise());
}

// Test render set/get
TEST_F(GfxStateTest_624, SetAndGetRender_624) {
    state->setRender(2);
    EXPECT_EQ(2, state->getRender());
}

// Test fill overprint set/get
TEST_F(GfxStateTest_624, SetAndGetFillOverprint_624) {
    state->setFillOverprint(true);
    EXPECT_TRUE(state->getFillOverprint());
    state->setFillOverprint(false);
    EXPECT_FALSE(state->getFillOverprint());
}

// Test stroke overprint set/get
TEST_F(GfxStateTest_624, SetAndGetStrokeOverprint_624) {
    state->setStrokeOverprint(true);
    EXPECT_TRUE(state->getStrokeOverprint());
    state->setStrokeOverprint(false);
    EXPECT_FALSE(state->getStrokeOverprint());
}

// Test overprint mode set/get
TEST_F(GfxStateTest_624, SetAndGetOverprintMode_624) {
    state->setOverprintMode(1);
    EXPECT_EQ(1, state->getOverprintMode());
}

// Test stroke adjust set/get
TEST_F(GfxStateTest_624, SetAndGetStrokeAdjust_624) {
    state->setStrokeAdjust(true);
    EXPECT_TRUE(state->getStrokeAdjust());
    state->setStrokeAdjust(false);
    EXPECT_FALSE(state->getStrokeAdjust());
}

// Test alpha is shape set/get
TEST_F(GfxStateTest_624, SetAndGetAlphaIsShape_624) {
    state->setAlphaIsShape(true);
    EXPECT_TRUE(state->getAlphaIsShape());
}

// Test text knockout set/get
TEST_F(GfxStateTest_624, SetAndGetTextKnockout_624) {
    state->setTextKnockout(true);
    EXPECT_TRUE(state->getTextKnockout());
}

// Test rendering intent set/get
TEST_F(GfxStateTest_624, SetAndGetRenderingIntent_624) {
    state->setRenderingIntent("Perceptual");
    EXPECT_STREQ("Perceptual", state->getRenderingIntent());
}

// Test save and restore
TEST_F(GfxStateTest_624, SaveAndRestore_624) {
    state->setLineWidth(5.0);
    GfxState *saved = state->save();
    EXPECT_TRUE(state->hasSaves());
    
    state->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(10.0, state->getLineWidth());
    
    GfxState *restored = state->restore();
    EXPECT_DOUBLE_EQ(5.0, restored->getLineWidth());
}

// Test hasSaves on fresh state
TEST_F(GfxStateTest_624, HasSavesReturnsFalseOnFreshState_624) {
    EXPECT_FALSE(state->hasSaves());
}

// Test hasSaves after save
TEST_F(GfxStateTest_624, HasSavesReturnsTrueAfterSave_624) {
    state->save();
    EXPECT_TRUE(state->hasSaves());
}

// Test moveTo followed by closePath
TEST_F(GfxStateTest_624, ClosePathAfterLineTo_624) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
}

// Test getCurX and getCurY after moveTo
TEST_F(GfxStateTest_624, GetCurXYAfterMoveTo_624) {
    state->moveTo(100.0, 200.0);
    EXPECT_DOUBLE_EQ(100.0, state->getCurX());
    EXPECT_DOUBLE_EQ(200.0, state->getCurY());
}

// Test path after lineTo updates current point
TEST_F(GfxStateTest_624, GetCurXYAfterLineTo_624) {
    state->moveTo(0.0, 0.0);
    state->lineTo(50.0, 75.0);
    EXPECT_DOUBLE_EQ(50.0, state->getCurX());
    EXPECT_DOUBLE_EQ(75.0, state->getCurY());
}

// Test getPath returns non-null
TEST_F(GfxStateTest_624, GetPathReturnsNonNull_624) {
    EXPECT_NE(nullptr, state->getPath());
}

// Test getPath number of subpaths on fresh state
TEST_F(GfxStateTest_624, GetPathNumSubpathsOnFreshState_624) {
    const GfxPath *path = state->getPath();
    EXPECT_EQ(0, path->getNumSubpaths());
}

// Test getPath number of subpaths after moveTo
TEST_F(GfxStateTest_624, GetPathNumSubpathsAfterMoveTo_624) {
    state->moveTo(10.0, 20.0);
    const GfxPath *path = state->getPath();
    EXPECT_EQ(1, path->getNumSubpaths());
}

// Test textMoveTo
TEST_F(GfxStateTest_624, TextMoveTo_624) {
    state->textMoveTo(10.0, 20.0);
    // After textMoveTo, lineX and lineY should be updated
    EXPECT_DOUBLE_EQ(10.0, state->getLineX());
    EXPECT_DOUBLE_EQ(20.0, state->getLineY());
}

// Test setTextMat and getTextMat
TEST_F(GfxStateTest_624, SetAndGetTextMat_624) {
    state->setTextMat(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
    const auto &mat = state->getTextMat();
    EXPECT_DOUBLE_EQ(1.0, mat[0]);
    EXPECT_DOUBLE_EQ(0.0, mat[1]);
    EXPECT_DOUBLE_EQ(0.0, mat[2]);
    EXPECT_DOUBLE_EQ(1.0, mat[3]);
    EXPECT_DOUBLE_EQ(10.0, mat[4]);
    EXPECT_DOUBLE_EQ(20.0, mat[5]);
}

// Test setCTM and getCTM
TEST_F(GfxStateTest_624, SetAndGetCTM_624) {
    state->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
    const auto &ctm = state->getCTM();
    EXPECT_DOUBLE_EQ(2.0, ctm[0]);
    EXPECT_DOUBLE_EQ(0.0, ctm[1]);
    EXPECT_DOUBLE_EQ(0.0, ctm[2]);
    EXPECT_DOUBLE_EQ(2.0, ctm[3]);
    EXPECT_DOUBLE_EQ(100.0, ctm[4]);
    EXPECT_DOUBLE_EQ(200.0, ctm[5]);
}

// Test transform
TEST_F(GfxStateTest_624, TransformWithIdentityCTM_624) {
    // Default CTM should map user coords to device coords based on the page setup
    double x2, y2;
    state->transform(0.0, 0.0, &x2, &y2);
    // Just verify it doesn't crash and returns finite values
    EXPECT_TRUE(std::isfinite(x2));
    EXPECT_TRUE(std::isfinite(y2));
}

// Test clipToRect and getClipBBox
TEST_F(GfxStateTest_624, ClipToRectAndGetClipBBox_624) {
    state->clipToRect(10.0, 20.0, 100.0, 200.0);
    double xMin, yMin, xMax, yMax;
    state->getClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_LE(xMin, 100.0);
    EXPECT_LE(yMin, 200.0);
    EXPECT_GE(xMax, 10.0);
    EXPECT_GE(yMax, 20.0);
}

// Test copy
TEST_F(GfxStateTest_624, CopyState_624) {
    state->setLineWidth(3.0);
    state->setFillOpacity(0.8);
    GfxState *copied = state->copy();
    ASSERT_NE(nullptr, copied);
    EXPECT_DOUBLE_EQ(3.0, copied->getLineWidth());
    EXPECT_DOUBLE_EQ(0.8, copied->getFillOpacity());
    delete copied;
}

// Test copy with path
TEST_F(GfxStateTest_624, CopyStateWithPath_624) {
    state->moveTo(10.0, 20.0);
    state->lineTo(30.0, 40.0);
    GfxState *copied = state->copy(true);
    ASSERT_NE(nullptr, copied);
    EXPECT_TRUE(copied->isPath());
    delete copied;
}

// Test blend mode set/get
TEST_F(GfxStateTest_624, SetAndGetBlendMode_624) {
    state->setBlendMode(GfxBlendMode::Multiply);
    EXPECT_EQ(GfxBlendMode::Multiply, state->getBlendMode());
}

// Test setLineDash and getLineDash
TEST_F(GfxStateTest_624, SetAndGetLineDash_624) {
    std::vector<double> dash = {3.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);
    double start;
    const auto &retrievedDash = state->getLineDash(&start);
    EXPECT_DOUBLE_EQ(1.0, start);
    ASSERT_EQ(2u, retrievedDash.size());
    EXPECT_DOUBLE_EQ(3.0, retrievedDash[0]);
    EXPECT_DOUBLE_EQ(5.0, retrievedDash[1]);
}

// Test rendering intent with long string (boundary, buffer is 32 chars)
TEST_F(GfxStateTest_624, SetRenderingIntentBoundary_624) {
    // The internal buffer is 32 chars, test with exactly 31 characters + null
    state->setRenderingIntent("AbsoluteColorimetric"); // 20 chars
    EXPECT_STREQ("AbsoluteColorimetric", state->getRenderingIntent());
}

// Test getX1, getY1, getX2, getY2
TEST_F(GfxStateTest_624, GetPageBounds_624) {
    double x1 = state->getX1();
    double y1 = state->getY1();
    double x2 = state->getX2();
    double y2 = state->getY2();
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test fontSize set/get via setFont (with nullptr font)
TEST_F(GfxStateTest_624, GetFontSizeDefault_624) {
    // Font size should have some default value
    double fontSize = state->getFontSize();
    EXPECT_TRUE(std::isfinite(fontSize));
}

// Test isPath after multiple path operations and clear
TEST_F(GfxStateTest_624, IsPathAfterMultipleOperationsAndClear_624) {
    state->moveTo(0.0, 0.0);
    state->lineTo(10.0, 0.0);
    state->lineTo(10.0, 10.0);
    state->lineTo(0.0, 10.0);
    state->closePath();
    EXPECT_TRUE(state->isPath());
    
    state->clearPath();
    EXPECT_FALSE(state->isPath());
    EXPECT_FALSE(state->isCurPt());
}

// Test curveTo updates path
TEST_F(GfxStateTest_624, CurveToCreatesPath_624) {
    state->moveTo(0.0, 0.0);
    state->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);
    EXPECT_TRUE(state->isPath());
    EXPECT_DOUBLE_EQ(50.0, state->getCurX());
    EXPECT_DOUBLE_EQ(60.0, state->getCurY());
}

// Test construction with rotation
TEST(GfxStateConstructionTest_624, ConstructWithRotation_624) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState rotatedState(72.0, 72.0, &pageBox, 90, true);
    EXPECT_EQ(90, rotatedState.getRotate());
}

// Test construction with different DPI values
TEST(GfxStateConstructionTest_624, ConstructWithDifferentDPI_624) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;
    GfxState highDpiState(300.0, 600.0, &pageBox, 0, true);
    EXPECT_DOUBLE_EQ(300.0, highDpiState.getHDPI());
    EXPECT_DOUBLE_EQ(600.0, highDpiState.getVDPI());
}

// Test concatCTM
TEST_F(GfxStateTest_624, ConcatCTM_624) {
    const auto &ctmBefore = state->getCTM();
    double a0 = ctmBefore[0];
    state->concatCTM(2.0, 0.0, 0.0, 2.0, 0.0, 0.0);
    const auto &ctmAfter = state->getCTM();
    // After concatenating a scaling matrix, the CTM should change
    EXPECT_DOUBLE_EQ(a0 * 2.0, ctmAfter[0]);
}

// Test getUserClipBBox
TEST_F(GfxStateTest_624, GetUserClipBBox_624) {
    double xMin, yMin, xMax, yMax;
    state->getUserClipBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_TRUE(std::isfinite(xMin));
    EXPECT_TRUE(std::isfinite(yMin));
    EXPECT_TRUE(std::isfinite(xMax));
    EXPECT_TRUE(std::isfinite(yMax));
    EXPECT_LE(xMin, xMax);
    EXPECT_LE(yMin, yMax);
}

// Test save/restore preserves path state
TEST_F(GfxStateTest_624, SaveRestorePreservesLineWidth_624) {
    state->setLineWidth(7.0);
    GfxState *afterSave = state->save();
    EXPECT_TRUE(state->hasSaves());
    state->setLineWidth(14.0);
    GfxState *afterRestore = state->restore();
    EXPECT_DOUBLE_EQ(7.0, afterRestore->getLineWidth());
}

// Test multiple saves and restores
TEST_F(GfxStateTest_624, MultipleSaveRestore_624) {
    state->setLineWidth(1.0);
    state->save();
    state->setLineWidth(2.0);
    state->save();
    state->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(3.0, state->getLineWidth());
    
    state->restore();
    EXPECT_DOUBLE_EQ(2.0, state->getLineWidth());
    
    state->restore();
    EXPECT_DOUBLE_EQ(1.0, state->getLineWidth());
    EXPECT_FALSE(state->hasSaves());
}
