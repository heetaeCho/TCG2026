#include <gtest/gtest.h>
#include "splash/SplashState.h"
#include "splash/SplashScreen.h"
#include "splash/SplashPattern.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

class SplashStateTest_1542 : public ::testing::Test {
protected:
    SplashState *state = nullptr;
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
TEST_F(SplashStateTest_1542, ConstructWithScreenParams_1542) {
    ASSERT_NE(state, nullptr);
}

// Test construction with different dimensions
TEST_F(SplashStateTest_1542, ConstructWithVariousDimensions_1542) {
    SplashState *s1 = new SplashState(1, 1, false, &screenParams);
    ASSERT_NE(s1, nullptr);
    delete s1;

    SplashState *s2 = new SplashState(1000, 1000, true, &screenParams);
    ASSERT_NE(s2, nullptr);
    delete s2;
}

// Test setStrokeOverprint with true
TEST_F(SplashStateTest_1542, SetStrokeOverprintTrue_1542) {
    // Should not crash; we can only verify no exception is thrown
    EXPECT_NO_THROW(state->setStrokeOverprint(true));
}

// Test setStrokeOverprint with false
TEST_F(SplashStateTest_1542, SetStrokeOverprintFalse_1542) {
    EXPECT_NO_THROW(state->setStrokeOverprint(false));
}

// Test setStrokeOverprint toggle
TEST_F(SplashStateTest_1542, SetStrokeOverprintToggle_1542) {
    EXPECT_NO_THROW(state->setStrokeOverprint(true));
    EXPECT_NO_THROW(state->setStrokeOverprint(false));
    EXPECT_NO_THROW(state->setStrokeOverprint(true));
}

// Test setFillOverprint with true
TEST_F(SplashStateTest_1542, SetFillOverprintTrue_1542) {
    EXPECT_NO_THROW(state->setFillOverprint(true));
}

// Test setFillOverprint with false
TEST_F(SplashStateTest_1542, SetFillOverprintFalse_1542) {
    EXPECT_NO_THROW(state->setFillOverprint(false));
}

// Test setOverprintMode
TEST_F(SplashStateTest_1542, SetOverprintModeZero_1542) {
    EXPECT_NO_THROW(state->setOverprintMode(0));
}

// Test setOverprintMode with 1
TEST_F(SplashStateTest_1542, SetOverprintModeOne_1542) {
    EXPECT_NO_THROW(state->setOverprintMode(1));
}

// Test copy method
TEST_F(SplashStateTest_1542, CopyState_1542) {
    state->setStrokeOverprint(true);
    state->setFillOverprint(true);
    state->setOverprintMode(1);
    
    SplashState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied, state);
    delete copied;
}

// Test copy of default state
TEST_F(SplashStateTest_1542, CopyDefaultState_1542) {
    SplashState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    delete copied;
}

// Test setLineDash with empty vector
TEST_F(SplashStateTest_1542, SetLineDashEmpty_1542) {
    std::vector<SplashCoord> emptyDash;
    EXPECT_NO_THROW(state->setLineDash(std::move(emptyDash), 0.0));
}

// Test setLineDash with values
TEST_F(SplashStateTest_1542, SetLineDashWithValues_1542) {
    std::vector<SplashCoord> dash = {3.0, 2.0, 1.0};
    EXPECT_NO_THROW(state->setLineDash(std::move(dash), 0.5));
}

// Test setLineDash with single element
TEST_F(SplashStateTest_1542, SetLineDashSingleElement_1542) {
    std::vector<SplashCoord> dash = {5.0};
    EXPECT_NO_THROW(state->setLineDash(std::move(dash), 0.0));
}

// Test setLineDash phase boundary
TEST_F(SplashStateTest_1542, SetLineDashZeroPhase_1542) {
    std::vector<SplashCoord> dash = {2.0, 3.0};
    EXPECT_NO_THROW(state->setLineDash(std::move(dash), 0.0));
}

// Test setSoftMask with nullptr
TEST_F(SplashStateTest_1542, SetSoftMaskNull_1542) {
    EXPECT_NO_THROW(state->setSoftMask(nullptr));
}

// Test setTransfer
TEST_F(SplashStateTest_1542, SetTransfer_1542) {
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = green[i] = blue[i] = gray[i] = (unsigned char)i;
    }
    EXPECT_NO_THROW(state->setTransfer(red, green, blue, gray));
}

// Test setTransfer with identity mapping
TEST_F(SplashStateTest_1542, SetTransferIdentity_1542) {
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = (unsigned char)i;
        green[i] = (unsigned char)i;
        blue[i] = (unsigned char)i;
        gray[i] = (unsigned char)i;
    }
    EXPECT_NO_THROW(state->setTransfer(red, green, blue, gray));
}

// Test setTransfer with inverted mapping
TEST_F(SplashStateTest_1542, SetTransferInverted_1542) {
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = green[i] = blue[i] = gray[i] = (unsigned char)(255 - i);
    }
    EXPECT_NO_THROW(state->setTransfer(red, green, blue, gray));
}

// Test construction with SplashScreen
TEST_F(SplashStateTest_1542, ConstructWithSplashScreen_1542) {
    SplashScreen screen(&screenParams);
    SplashState *s = new SplashState(200, 200, true, screen);
    ASSERT_NE(s, nullptr);
    delete s;
}

// Test copy preserves through multiple copies
TEST_F(SplashStateTest_1542, MultipleCopies_1542) {
    state->setStrokeOverprint(true);
    state->setFillOverprint(false);
    state->setOverprintMode(1);

    SplashState *copy1 = state->copy();
    ASSERT_NE(copy1, nullptr);
    
    SplashState *copy2 = copy1->copy();
    ASSERT_NE(copy2, nullptr);
    
    delete copy2;
    delete copy1;
}

// Test setting all overprint related properties
TEST_F(SplashStateTest_1542, SetAllOverprintProperties_1542) {
    EXPECT_NO_THROW({
        state->setStrokeOverprint(true);
        state->setFillOverprint(true);
        state->setOverprintMode(1);
    });
}

// Test with vector antialias enabled
TEST_F(SplashStateTest_1542, ConstructWithVectorAntialias_1542) {
    SplashState *s = new SplashState(50, 50, true, &screenParams);
    ASSERT_NE(s, nullptr);
    s->setStrokeOverprint(true);
    s->setFillOverprint(false);
    delete s;
}

// Test zero dimension
TEST_F(SplashStateTest_1542, ConstructWithZeroDimensions_1542) {
    // Boundary: zero-sized state
    SplashState *s = new SplashState(0, 0, false, &screenParams);
    ASSERT_NE(s, nullptr);
    delete s;
}

// Test setStrokePattern with a SplashSolidColor
TEST_F(SplashStateTest_1542, SetStrokePatternSolidColor_1542) {
    SplashColor color;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    SplashSolidColor *pattern = new SplashSolidColor(color);
    EXPECT_NO_THROW(state->setStrokePattern(pattern));
    // Note: state takes ownership, so don't delete pattern
}

// Test setFillPattern with a SplashSolidColor
TEST_F(SplashStateTest_1542, SetFillPatternSolidColor_1542) {
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 0;
    SplashSolidColor *pattern = new SplashSolidColor(color);
    EXPECT_NO_THROW(state->setFillPattern(pattern));
}

// Test repeated overprint mode changes
TEST_F(SplashStateTest_1542, RepeatedOverprintModeChanges_1542) {
    for (int i = 0; i < 100; i++) {
        EXPECT_NO_THROW(state->setOverprintMode(i % 2));
    }
}

// Test repeated stroke/fill overprint changes
TEST_F(SplashStateTest_1542, RepeatedOverprintChanges_1542) {
    for (int i = 0; i < 100; i++) {
        EXPECT_NO_THROW(state->setStrokeOverprint(i % 2 == 0));
        EXPECT_NO_THROW(state->setFillOverprint(i % 2 != 0));
    }
}

// Test copy after modifying line dash
TEST_F(SplashStateTest_1542, CopyAfterLineDashModification_1542) {
    std::vector<SplashCoord> dash = {4.0, 2.0};
    state->setLineDash(std::move(dash), 1.0);
    
    SplashState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    delete copied;
}

// Test copy after setting soft mask to null
TEST_F(SplashStateTest_1542, CopyAfterNullSoftMask_1542) {
    state->setSoftMask(nullptr);
    SplashState *copied = state->copy();
    ASSERT_NE(copied, nullptr);
    delete copied;
}
