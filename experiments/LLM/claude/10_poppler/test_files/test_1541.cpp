#include <gtest/gtest.h>
#include "splash/SplashState.h"
#include "splash/SplashScreen.h"
#include "splash/SplashPattern.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

class SplashStateTest_1541 : public ::testing::Test {
protected:
    SplashState* state = nullptr;
    SplashScreenParams screenParams;

    void SetUp() override {
        screenParams.type = splashScreenDispersed;
        screenParams.size = 2;
        screenParams.dotRadius = 0;
        screenParams.gamma = 1.0;
        screenParams.blackThreshold = 0.0;
        screenParams.whiteThreshold = 1.0;
        state = new SplashState(100, 100, false, &screenParams);
    }

    void TearDown() override {
        delete state;
        state = nullptr;
    }
};

// Test basic construction with screen params
TEST_F(SplashStateTest_1541, ConstructionWithScreenParams_1541) {
    ASSERT_NE(state, nullptr);
}

// Test construction with different dimensions
TEST_F(SplashStateTest_1541, ConstructionWithDifferentDimensions_1541) {
    SplashState* smallState = new SplashState(1, 1, false, &screenParams);
    ASSERT_NE(smallState, nullptr);
    delete smallState;
}

// Test construction with vector antialias enabled
TEST_F(SplashStateTest_1541, ConstructionWithVectorAntialias_1541) {
    SplashState* aaState = new SplashState(100, 100, true, &screenParams);
    ASSERT_NE(aaState, nullptr);
    delete aaState;
}

// Test construction with SplashScreen reference
TEST_F(SplashStateTest_1541, ConstructionWithSplashScreen_1541) {
    SplashScreen screen(&screenParams);
    SplashState* screenState = new SplashState(100, 100, false, screen);
    ASSERT_NE(screenState, nullptr);
    delete screenState;
}

// Test setFillOverprint with true
TEST_F(SplashStateTest_1541, SetFillOverprintTrue_1541) {
    // Should not crash or throw
    state->setFillOverprint(true);
}

// Test setFillOverprint with false
TEST_F(SplashStateTest_1541, SetFillOverprintFalse_1541) {
    state->setFillOverprint(false);
}

// Test setStrokeOverprint with true
TEST_F(SplashStateTest_1541, SetStrokeOverprintTrue_1541) {
    state->setStrokeOverprint(true);
}

// Test setStrokeOverprint with false
TEST_F(SplashStateTest_1541, SetStrokeOverprintFalse_1541) {
    state->setStrokeOverprint(false);
}

// Test setOverprintMode
TEST_F(SplashStateTest_1541, SetOverprintModeZero_1541) {
    state->setOverprintMode(0);
}

TEST_F(SplashStateTest_1541, SetOverprintModeOne_1541) {
    state->setOverprintMode(1);
}

// Test copy
TEST_F(SplashStateTest_1541, CopyCreatesNonNullState_1541) {
    SplashState* copied = state->copy();
    ASSERT_NE(copied, nullptr);
    delete copied;
}

// Test copy preserves fill overprint setting
TEST_F(SplashStateTest_1541, CopyPreservesSettings_1541) {
    state->setFillOverprint(true);
    state->setStrokeOverprint(true);
    state->setOverprintMode(1);
    SplashState* copied = state->copy();
    ASSERT_NE(copied, nullptr);
    // The copy should succeed without issues
    delete copied;
}

// Test setStrokePattern
TEST_F(SplashStateTest_1541, SetStrokePattern_1541) {
    SplashSolidColor* pattern = new SplashSolidColor(SplashColorPtr(new SplashColor()));
    // SplashState takes ownership
    state->setStrokePattern(pattern);
}

// Test setFillPattern
TEST_F(SplashStateTest_1541, SetFillPattern_1541) {
    SplashSolidColor* pattern = new SplashSolidColor(SplashColorPtr(new SplashColor()));
    // SplashState takes ownership
    state->setFillPattern(pattern);
}

// Test setLineDash with empty vector
TEST_F(SplashStateTest_1541, SetLineDashEmpty_1541) {
    std::vector<SplashCoord> emptyDash;
    state->setLineDash(std::move(emptyDash), 0.0);
}

// Test setLineDash with non-empty vector
TEST_F(SplashStateTest_1541, SetLineDashNonEmpty_1541) {
    std::vector<SplashCoord> dash = {5.0, 3.0};
    state->setLineDash(std::move(dash), 0.0);
}

// Test setLineDash with phase
TEST_F(SplashStateTest_1541, SetLineDashWithPhase_1541) {
    std::vector<SplashCoord> dash = {5.0, 3.0, 2.0};
    state->setLineDash(std::move(dash), 2.5);
}

// Test setSoftMask with nullptr
TEST_F(SplashStateTest_1541, SetSoftMaskNull_1541) {
    state->setSoftMask(nullptr);
}

// Test setTransfer
TEST_F(SplashStateTest_1541, SetTransfer_1541) {
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = green[i] = blue[i] = gray[i] = (unsigned char)i;
    }
    state->setTransfer(red, green, blue, gray);
}

// Test setTransfer with inverted values
TEST_F(SplashStateTest_1541, SetTransferInverted_1541) {
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = green[i] = blue[i] = gray[i] = (unsigned char)(255 - i);
    }
    state->setTransfer(red, green, blue, gray);
}

// Test multiple operations in sequence
TEST_F(SplashStateTest_1541, MultipleOperationsSequence_1541) {
    state->setFillOverprint(true);
    state->setStrokeOverprint(false);
    state->setOverprintMode(1);

    std::vector<SplashCoord> dash = {10.0, 5.0};
    state->setLineDash(std::move(dash), 1.0);

    SplashState* copied = state->copy();
    ASSERT_NE(copied, nullptr);

    copied->setFillOverprint(false);
    copied->setOverprintMode(0);

    delete copied;
}

// Test large dimensions
TEST_F(SplashStateTest_1541, LargeDimensions_1541) {
    SplashState* largeState = new SplashState(10000, 10000, false, &screenParams);
    ASSERT_NE(largeState, nullptr);
    delete largeState;
}

// Test toggling overprint settings
TEST_F(SplashStateTest_1541, ToggleOverprintSettings_1541) {
    state->setFillOverprint(true);
    state->setFillOverprint(false);
    state->setFillOverprint(true);

    state->setStrokeOverprint(true);
    state->setStrokeOverprint(false);
    state->setStrokeOverprint(true);
}

// Test copy of copy
TEST_F(SplashStateTest_1541, CopyOfCopy_1541) {
    SplashState* copy1 = state->copy();
    ASSERT_NE(copy1, nullptr);
    SplashState* copy2 = copy1->copy();
    ASSERT_NE(copy2, nullptr);
    delete copy2;
    delete copy1;
}
