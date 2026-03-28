#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "splash/SplashState.h"
#include "splash/SplashPattern.h"
#include "splash/SplashScreen.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"
#include "splash/SplashClip.h"

class SplashStateTest_1540 : public ::testing::Test {
protected:
    void SetUp() override {
        screenParams.type = splashScreenDispersed;
        screenParams.size = 2;
        screenParams.dotRadius = 0;
        screenParams.gamma = 1.0;
        screenParams.blackThreshold = 0.0;
        screenParams.whiteThreshold = 1.0;
    }

    void TearDown() override {
    }

    SplashScreenParams screenParams;
};

// Test basic construction with screen params
TEST_F(SplashStateTest_1540, ConstructWithScreenParams_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    ASSERT_NE(state, nullptr);
    delete state;
}

// Test construction with different dimensions
TEST_F(SplashStateTest_1540, ConstructWithVariousDimensions_1540) {
    SplashState *state1 = new SplashState(1, 1, false, &screenParams);
    ASSERT_NE(state1, nullptr);
    delete state1;

    SplashState *state2 = new SplashState(1000, 1000, true, &screenParams);
    ASSERT_NE(state2, nullptr);
    delete state2;
}

// Test construction with vector antialias enabled
TEST_F(SplashStateTest_1540, ConstructWithVectorAntialias_1540) {
    SplashState *state = new SplashState(200, 200, true, &screenParams);
    ASSERT_NE(state, nullptr);
    delete state;
}

// Test copy method returns a non-null distinct object
TEST_F(SplashStateTest_1540, CopyReturnsNonNull_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    SplashState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    ASSERT_NE(copied, state);
    delete copied;
    delete state;
}

// Test copy method produces independent object (modifying one doesn't affect the other)
TEST_F(SplashStateTest_1540, CopyProducesIndependentObject_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    SplashState *copied = state->copy();
    ASSERT_NE(copied, nullptr);

    // Modify original after copy - should not crash
    state->setFillOverprint(true);
    state->setStrokeOverprint(true);

    delete copied;
    delete state;
}

// Test setStrokePattern
TEST_F(SplashStateTest_1540, SetStrokePattern_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 0;
    SplashSolidColor *pattern = new SplashSolidColor(color);
    // setStrokePattern takes ownership
    state->setStrokePattern(pattern);
    delete state;
}

// Test setFillPattern
TEST_F(SplashStateTest_1540, SetFillPattern_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    SplashColor color;
    color[0] = 0;
    color[1] = 255;
    color[2] = 0;
    SplashSolidColor *pattern = new SplashSolidColor(color);
    // setFillPattern takes ownership
    state->setFillPattern(pattern);
    delete state;
}

// Test setLineDash with vector
TEST_F(SplashStateTest_1540, SetLineDashVector_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    std::vector<SplashCoord> dash = {5.0, 3.0, 1.0};
    state->setLineDash(std::move(dash), 0.0);
    delete state;
}

// Test setLineDash with empty vector
TEST_F(SplashStateTest_1540, SetLineDashEmptyVector_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    std::vector<SplashCoord> dash;
    state->setLineDash(std::move(dash), 0.0);
    delete state;
}

// Test setLineDash with non-zero phase
TEST_F(SplashStateTest_1540, SetLineDashWithPhase_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    std::vector<SplashCoord> dash = {10.0, 5.0};
    state->setLineDash(std::move(dash), 3.0);
    delete state;
}

// Test setSoftMask with null
TEST_F(SplashStateTest_1540, SetSoftMaskNull_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    state->setSoftMask(nullptr);
    delete state;
}

// Test setTransfer
TEST_F(SplashStateTest_1540, SetTransfer_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = (unsigned char)i;
        green[i] = (unsigned char)i;
        blue[i] = (unsigned char)i;
        gray[i] = (unsigned char)i;
    }
    state->setTransfer(red, green, blue, gray);
    delete state;
}

// Test setTransfer with inverted values
TEST_F(SplashStateTest_1540, SetTransferInverted_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = (unsigned char)(255 - i);
        green[i] = (unsigned char)(255 - i);
        blue[i] = (unsigned char)(255 - i);
        gray[i] = (unsigned char)(255 - i);
    }
    state->setTransfer(red, green, blue, gray);
    delete state;
}

// Test setFillOverprint
TEST_F(SplashStateTest_1540, SetFillOverprint_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    state->setFillOverprint(true);
    state->setFillOverprint(false);
    delete state;
}

// Test setStrokeOverprint
TEST_F(SplashStateTest_1540, SetStrokeOverprint_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    state->setStrokeOverprint(true);
    state->setStrokeOverprint(false);
    delete state;
}

// Test setOverprintMode
TEST_F(SplashStateTest_1540, SetOverprintMode_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    state->setOverprintMode(0);
    state->setOverprintMode(1);
    delete state;
}

// Test construction with SplashScreen reference
TEST_F(SplashStateTest_1540, ConstructWithScreenReference_1540) {
    SplashScreen screen(&screenParams);
    SplashState *state = new SplashState(100, 100, false, screen);
    ASSERT_NE(state, nullptr);
    delete state;
}

// Test copy after setting various properties
TEST_F(SplashStateTest_1540, CopyAfterSettingProperties_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);

    state->setFillOverprint(true);
    state->setStrokeOverprint(true);
    state->setOverprintMode(1);

    std::vector<SplashCoord> dash = {4.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);

    SplashState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    ASSERT_NE(copied, state);

    delete copied;
    delete state;
}

// Test multiple copies from the same state
TEST_F(SplashStateTest_1540, MultipleCopies_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    SplashState *copy1 = state->copy();
    SplashState *copy2 = state->copy();
    SplashState *copy3 = state->copy();

    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    ASSERT_NE(copy3, nullptr);
    ASSERT_NE(copy1, copy2);
    ASSERT_NE(copy2, copy3);
    ASSERT_NE(copy1, copy3);

    delete copy3;
    delete copy2;
    delete copy1;
    delete state;
}

// Test copy of a copy
TEST_F(SplashStateTest_1540, CopyOfCopy_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    SplashState *copy1 = state->copy();
    SplashState *copy2 = copy1->copy();

    ASSERT_NE(copy2, nullptr);
    ASSERT_NE(copy2, copy1);
    ASSERT_NE(copy2, state);

    delete copy2;
    delete copy1;
    delete state;
}

// Test setting patterns then copying
TEST_F(SplashStateTest_1540, SetPatternsThenCopy_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);

    SplashColor strokeColor;
    strokeColor[0] = 255;
    strokeColor[1] = 0;
    strokeColor[2] = 0;
    state->setStrokePattern(new SplashSolidColor(strokeColor));

    SplashColor fillColor;
    fillColor[0] = 0;
    fillColor[1] = 0;
    fillColor[2] = 255;
    state->setFillPattern(new SplashSolidColor(fillColor));

    SplashState *copied = state->copy();
    ASSERT_NE(copied, nullptr);

    delete copied;
    delete state;
}

// Test with minimum dimensions
TEST_F(SplashStateTest_1540, MinimumDimensions_1540) {
    SplashState *state = new SplashState(1, 1, false, &screenParams);
    ASSERT_NE(state, nullptr);
    SplashState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    delete copied;
    delete state;
}

// Test with large dimensions
TEST_F(SplashStateTest_1540, LargeDimensions_1540) {
    SplashState *state = new SplashState(5000, 5000, false, &screenParams);
    ASSERT_NE(state, nullptr);
    delete state;
}

// Test setting soft mask then deleting state
TEST_F(SplashStateTest_1540, SetSoftMaskThenDelete_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    SplashBitmap *softMask = new SplashBitmap(50, 50, 1, splashModeMono8, false);
    state->setSoftMask(softMask);
    delete state;
}

// Test replacing soft mask
TEST_F(SplashStateTest_1540, ReplaceSoftMask_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    SplashBitmap *softMask1 = new SplashBitmap(50, 50, 1, splashModeMono8, false);
    state->setSoftMask(softMask1);
    SplashBitmap *softMask2 = new SplashBitmap(30, 30, 1, splashModeMono8, false);
    state->setSoftMask(softMask2);
    delete state;
}

// Test replacing stroke pattern multiple times
TEST_F(SplashStateTest_1540, ReplaceStrokePatternMultipleTimes_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    SplashColor color;

    color[0] = 255; color[1] = 0; color[2] = 0;
    state->setStrokePattern(new SplashSolidColor(color));

    color[0] = 0; color[1] = 255; color[2] = 0;
    state->setStrokePattern(new SplashSolidColor(color));

    color[0] = 0; color[1] = 0; color[2] = 255;
    state->setStrokePattern(new SplashSolidColor(color));

    delete state;
}

// Test replacing fill pattern multiple times
TEST_F(SplashStateTest_1540, ReplaceFillPatternMultipleTimes_1540) {
    SplashState *state = new SplashState(100, 100, false, &screenParams);
    SplashColor color;

    color[0] = 100; color[1] = 100; color[2] = 100;
    state->setFillPattern(new SplashSolidColor(color));

    color[0] = 200; color[1] = 200; color[2] = 200;
    state->setFillPattern(new SplashSolidColor(color));

    delete state;
}
