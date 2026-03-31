#include <gtest/gtest.h>
#include "splash/SplashFTFontEngine.h"

class SplashFTFontEngineTest_2604 : public ::testing::Test {
protected:
    SplashFTFontEngine* engine_aa_true = nullptr;
    SplashFTFontEngine* engine_aa_false = nullptr;

    void SetUp() override {
        engine_aa_true = SplashFTFontEngine::init(true, false, false);
        engine_aa_false = SplashFTFontEngine::init(false, false, false);
    }

    void TearDown() override {
        delete engine_aa_true;
        delete engine_aa_false;
    }
};

TEST_F(SplashFTFontEngineTest_2604, InitReturnsNonNull_2604) {
    ASSERT_NE(engine_aa_true, nullptr);
    ASSERT_NE(engine_aa_false, nullptr);
}

TEST_F(SplashFTFontEngineTest_2604, GetAAReturnsTrueWhenInitializedWithTrue_2604) {
    EXPECT_TRUE(engine_aa_true->getAA());
}

TEST_F(SplashFTFontEngineTest_2604, GetAAReturnsFalseWhenInitializedWithFalse_2604) {
    EXPECT_FALSE(engine_aa_false->getAA());
}

TEST_F(SplashFTFontEngineTest_2604, SetAAChangesToTrue_2604) {
    engine_aa_false->setAA(true);
    EXPECT_TRUE(engine_aa_false->getAA());
}

TEST_F(SplashFTFontEngineTest_2604, SetAAChangesToFalse_2604) {
    engine_aa_true->setAA(false);
    EXPECT_FALSE(engine_aa_true->getAA());
}

TEST_F(SplashFTFontEngineTest_2604, SetAASameValueTrue_2604) {
    engine_aa_true->setAA(true);
    EXPECT_TRUE(engine_aa_true->getAA());
}

TEST_F(SplashFTFontEngineTest_2604, SetAASameValueFalse_2604) {
    engine_aa_false->setAA(false);
    EXPECT_FALSE(engine_aa_false->getAA());
}

TEST_F(SplashFTFontEngineTest_2604, SetAAToggleMultipleTimes_2604) {
    engine_aa_true->setAA(false);
    EXPECT_FALSE(engine_aa_true->getAA());
    engine_aa_true->setAA(true);
    EXPECT_TRUE(engine_aa_true->getAA());
    engine_aa_true->setAA(false);
    EXPECT_FALSE(engine_aa_true->getAA());
}

TEST_F(SplashFTFontEngineTest_2604, InitWithDifferentHintingOptions_2604) {
    SplashFTFontEngine* engine1 = SplashFTFontEngine::init(true, true, false);
    ASSERT_NE(engine1, nullptr);
    EXPECT_TRUE(engine1->getAA());
    delete engine1;

    SplashFTFontEngine* engine2 = SplashFTFontEngine::init(false, true, true);
    ASSERT_NE(engine2, nullptr);
    EXPECT_FALSE(engine2->getAA());
    delete engine2;

    SplashFTFontEngine* engine3 = SplashFTFontEngine::init(true, false, true);
    ASSERT_NE(engine3, nullptr);
    EXPECT_TRUE(engine3->getAA());
    delete engine3;

    SplashFTFontEngine* engine4 = SplashFTFontEngine::init(true, true, true);
    ASSERT_NE(engine4, nullptr);
    EXPECT_TRUE(engine4->getAA());
    delete engine4;
}

TEST_F(SplashFTFontEngineTest_2604, GetAAIsConst_2604) {
    const SplashFTFontEngine* constEngine = engine_aa_true;
    EXPECT_TRUE(constEngine->getAA());
}
