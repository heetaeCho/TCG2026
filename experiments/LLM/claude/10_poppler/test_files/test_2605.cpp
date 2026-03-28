#include <gtest/gtest.h>
#include "SplashFTFontEngine.h"

class SplashFTFontEngineTest_2605 : public ::testing::Test {
protected:
    SplashFTFontEngine* engine = nullptr;

    void SetUp() override {
        // Use the static init method to create an instance
        engine = SplashFTFontEngine::init(true, false, false);
    }

    void TearDown() override {
        delete engine;
        engine = nullptr;
    }
};

// Test that init returns a non-null pointer
TEST_F(SplashFTFontEngineTest_2605, InitReturnsNonNull_2605) {
    ASSERT_NE(engine, nullptr);
}

// Test that AA is initially set to the value passed in init (true)
TEST_F(SplashFTFontEngineTest_2605, InitialAAIsTrue_2605) {
    ASSERT_NE(engine, nullptr);
    EXPECT_TRUE(engine->getAA());
}

// Test setAA to false and verify with getAA
TEST_F(SplashFTFontEngineTest_2605, SetAAToFalse_2605) {
    ASSERT_NE(engine, nullptr);
    engine->setAA(false);
    EXPECT_FALSE(engine->getAA());
}

// Test setAA to true and verify with getAA
TEST_F(SplashFTFontEngineTest_2605, SetAAToTrue_2605) {
    ASSERT_NE(engine, nullptr);
    engine->setAA(false);
    EXPECT_FALSE(engine->getAA());
    engine->setAA(true);
    EXPECT_TRUE(engine->getAA());
}

// Test toggling AA multiple times
TEST_F(SplashFTFontEngineTest_2605, ToggleAAMultipleTimes_2605) {
    ASSERT_NE(engine, nullptr);
    for (int i = 0; i < 10; ++i) {
        engine->setAA(false);
        EXPECT_FALSE(engine->getAA());
        engine->setAA(true);
        EXPECT_TRUE(engine->getAA());
    }
}

// Test setting AA to the same value repeatedly
TEST_F(SplashFTFontEngineTest_2605, SetAASameValueRepeatedly_2605) {
    ASSERT_NE(engine, nullptr);
    engine->setAA(true);
    EXPECT_TRUE(engine->getAA());
    engine->setAA(true);
    EXPECT_TRUE(engine->getAA());
    engine->setAA(false);
    EXPECT_FALSE(engine->getAA());
    engine->setAA(false);
    EXPECT_FALSE(engine->getAA());
}

// Test init with AA set to false
TEST(SplashFTFontEngineInitTest_2605, InitWithAAFalse_2605) {
    SplashFTFontEngine* eng = SplashFTFontEngine::init(false, false, false);
    ASSERT_NE(eng, nullptr);
    EXPECT_FALSE(eng->getAA());
    delete eng;
}

// Test init with different hinting options
TEST(SplashFTFontEngineInitTest_2605, InitWithHintingEnabled_2605) {
    SplashFTFontEngine* eng = SplashFTFontEngine::init(true, true, false);
    ASSERT_NE(eng, nullptr);
    EXPECT_TRUE(eng->getAA());
    delete eng;
}

// Test init with slight hinting enabled
TEST(SplashFTFontEngineInitTest_2605, InitWithSlightHintingEnabled_2605) {
    SplashFTFontEngine* eng = SplashFTFontEngine::init(false, false, true);
    ASSERT_NE(eng, nullptr);
    EXPECT_FALSE(eng->getAA());
    delete eng;
}

// Test init with all options enabled
TEST(SplashFTFontEngineInitTest_2605, InitWithAllOptionsEnabled_2605) {
    SplashFTFontEngine* eng = SplashFTFontEngine::init(true, true, true);
    ASSERT_NE(eng, nullptr);
    EXPECT_TRUE(eng->getAA());
    delete eng;
}

// Test that multiple engines can coexist independently
TEST(SplashFTFontEngineInitTest_2605, MultipleEnginesIndependent_2605) {
    SplashFTFontEngine* eng1 = SplashFTFontEngine::init(true, false, false);
    SplashFTFontEngine* eng2 = SplashFTFontEngine::init(false, false, false);
    ASSERT_NE(eng1, nullptr);
    ASSERT_NE(eng2, nullptr);

    EXPECT_TRUE(eng1->getAA());
    EXPECT_FALSE(eng2->getAA());

    eng1->setAA(false);
    EXPECT_FALSE(eng1->getAA());
    EXPECT_FALSE(eng2->getAA());

    eng2->setAA(true);
    EXPECT_FALSE(eng1->getAA());
    EXPECT_TRUE(eng2->getAA());

    delete eng1;
    delete eng2;
}
