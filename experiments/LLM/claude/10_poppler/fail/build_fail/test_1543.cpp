#include <gtest/gtest.h>
#include "splash/SplashState.h"
#include "splash/SplashScreen.h"
#include "splash/SplashPattern.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

class SplashStateTest_1543 : public ::testing::Test {
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
TEST_F(SplashStateTest_1543, ConstructWithScreenParams_1543) {
    ASSERT_NE(state, nullptr);
}

// Test construction with different dimensions
TEST_F(SplashStateTest_1543, ConstructWithDifferentDimensions_1543) {
    SplashState* smallState = new SplashState(1, 1, false, &screenParams);
    ASSERT_NE(smallState, nullptr);
    delete smallState;
}

// Test construction with vector antialias enabled
TEST_F(SplashStateTest_1543, ConstructWithVectorAntialias_1543) {
    SplashState* aaState = new SplashState(100, 100, true, &screenParams);
    ASSERT_NE(aaState, nullptr);
    delete aaState;
}

// Test construction with SplashScreen reference
TEST_F(SplashStateTest_1543, ConstructWithScreenReference_1543) {
    SplashScreen screen(&screenParams);
    SplashState* state2 = new SplashState(100, 100, false, screen);
    ASSERT_NE(state2, nullptr);
    delete state2;
}

// Test setOverprintMode with value 0
TEST_F(SplashStateTest_1543, SetOverprintModeZero_1543) {
    // Should not crash or throw
    state->setOverprintMode(0);
}

// Test setOverprintMode with value 1
TEST_F(SplashStateTest_1543, SetOverprintModeOne_1543) {
    state->setOverprintMode(1);
}

// Test setOverprintMode with negative value
TEST_F(SplashStateTest_1543, SetOverprintModeNegative_1543) {
    state->setOverprintMode(-1);
}

// Test setOverprintMode with large value
TEST_F(SplashStateTest_1543, SetOverprintModeLargeValue_1543) {
    state->setOverprintMode(999);
}

// Test setFillOverprint
TEST_F(SplashStateTest_1543, SetFillOverprintTrue_1543) {
    state->setFillOverprint(true);
}

TEST_F(SplashStateTest_1543, SetFillOverprintFalse_1543) {
    state->setFillOverprint(false);
}

// Test setStrokeOverprint
TEST_F(SplashStateTest_1543, SetStrokeOverprintTrue_1543) {
    state->setStrokeOverprint(true);
}

TEST_F(SplashStateTest_1543, SetStrokeOverprintFalse_1543) {
    state->setStrokeOverprint(false);
}

// Test copy
TEST_F(SplashStateTest_1543, CopyCreatesNonNullState_1543) {
    SplashState* copied = state->copy();
    ASSERT_NE(copied, nullptr);
    delete copied;
}

// Test copy after setting overprint mode
TEST_F(SplashStateTest_1543, CopyAfterSettingOverprintMode_1543) {
    state->setOverprintMode(1);
    SplashState* copied = state->copy();
    ASSERT_NE(copied, nullptr);
    delete copied;
}

// Test copy is a separate object
TEST_F(SplashStateTest_1543, CopyIsSeparateObject_1543) {
    SplashState* copied = state->copy();
    ASSERT_NE(copied, state);
    delete copied;
}

// Test setStrokePattern
TEST_F(SplashStateTest_1543, SetStrokePattern_1543) {
    SplashSolidColor* pattern = new SplashSolidColor(SplashColorPtr(new SplashColor{0, 0, 0, 0}));
    // SplashState takes ownership
    state->setStrokePattern(pattern);
}

// Test setFillPattern
TEST_F(SplashStateTest_1543, SetFillPattern_1543) {
    SplashSolidColor* pattern = new SplashSolidColor(SplashColorPtr(new SplashColor{255, 0, 0, 0}));
    // SplashState takes ownership
    state->setFillPattern(pattern);
}

// Test setLineDash with empty vector
TEST_F(SplashStateTest_1543, SetLineDashEmpty_1543) {
    std::vector<SplashCoord> dash;
    state->setLineDash(std::move(dash), 0.0);
}

// Test setLineDash with values
TEST_F(SplashStateTest_1543, SetLineDashWithValues_1543) {
    std::vector<SplashCoord> dash = {5.0, 3.0};
    state->setLineDash(std::move(dash), 0.0);
}

// Test setLineDash with non-zero phase
TEST_F(SplashStateTest_1543, SetLineDashWithPhase_1543) {
    std::vector<SplashCoord> dash = {5.0, 3.0, 2.0};
    state->setLineDash(std::move(dash), 2.5);
}

// Test setSoftMask with nullptr
TEST_F(SplashStateTest_1543, SetSoftMaskNull_1543) {
    state->setSoftMask(nullptr);
}

// Test setTransfer
TEST_F(SplashStateTest_1543, SetTransfer_1543) {
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = green[i] = blue[i] = gray[i] = (unsigned char)i;
    }
    state->setTransfer(red, green, blue, gray);
}

// Test setTransfer with inverted values
TEST_F(SplashStateTest_1543, SetTransferInverted_1543) {
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = green[i] = blue[i] = gray[i] = (unsigned char)(255 - i);
    }
    state->setTransfer(red, green, blue, gray);
}

// Test multiple operations in sequence
TEST_F(SplashStateTest_1543, MultipleOperationsInSequence_1543) {
    state->setOverprintMode(1);
    state->setFillOverprint(true);
    state->setStrokeOverprint(true);

    std::vector<SplashCoord> dash = {4.0, 2.0};
    state->setLineDash(std::move(dash), 0.0);

    SplashState* copied = state->copy();
    ASSERT_NE(copied, nullptr);
    delete copied;
}

// Test large dimensions
TEST_F(SplashStateTest_1543, ConstructWithLargeDimensions_1543) {
    SplashState* largeState = new SplashState(10000, 10000, false, &screenParams);
    ASSERT_NE(largeState, nullptr);
    delete largeState;
}

// Test zero dimensions
TEST_F(SplashStateTest_1543, ConstructWithZeroDimensions_1543) {
    SplashState* zeroState = new SplashState(0, 0, false, &screenParams);
    ASSERT_NE(zeroState, nullptr);
    delete zeroState;
}
