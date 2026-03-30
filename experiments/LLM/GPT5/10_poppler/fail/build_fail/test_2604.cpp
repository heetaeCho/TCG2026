// File: SplashFTFontEngine_test_2604.cpp

#include <gtest/gtest.h>

#include <memory>

#include "TestProjects/poppler/splash/SplashFTFontEngine.h"

namespace {

using EnginePtr = std::unique_ptr<SplashFTFontEngine>;

EnginePtr CreateEngineOrSkip(bool aa, bool enableFreeTypeHinting, bool enableSlightHinting) {
  SplashFTFontEngine* raw = SplashFTFontEngine::init(aa, enableFreeTypeHinting, enableSlightHinting);
  if (!raw) {
    GTEST_SKIP() << "SplashFTFontEngine::init returned nullptr (likely missing/disabled FreeType in this build).";
  }
  return EnginePtr(raw);
}

class SplashFTFontEngineTest_2604 : public ::testing::Test {};

TEST_F(SplashFTFontEngineTest_2604, GetAAIsCallableOnConst_2604) {
  auto engine = CreateEngineOrSkip(/*aa=*/false, /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/false);

  const SplashFTFontEngine& const_ref = *engine;
  // This test primarily verifies const-correctness of the public interface.
  (void)const_ref.getAA();
}

TEST_F(SplashFTFontEngineTest_2604, SetAATrueThenGetAAReportsTrue_2604) {
  auto engine = CreateEngineOrSkip(/*aa=*/false, /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/false);

  engine->setAA(true);
  EXPECT_TRUE(engine->getAA());
}

TEST_F(SplashFTFontEngineTest_2604, SetAAFalseThenGetAAReportsFalse_2604) {
  auto engine = CreateEngineOrSkip(/*aa=*/true, /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/false);

  engine->setAA(false);
  EXPECT_FALSE(engine->getAA());
}

TEST_F(SplashFTFontEngineTest_2604, SetAATogglesState_2604) {
  auto engine = CreateEngineOrSkip(/*aa=*/false, /*enableFreeTypeHinting=*/false, /*enableSlightHinting=*/false);

  engine->setAA(true);
  ASSERT_TRUE(engine->getAA());

  engine->setAA(false);
  EXPECT_FALSE(engine->getAA());

  engine->setAA(true);
  EXPECT_TRUE(engine->getAA());
}

TEST_F(SplashFTFontEngineTest_2604, SetAAIsIdempotent_2604) {
  auto engine = CreateEngineOrSkip(/*aa=*/false, /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/true);

  engine->setAA(true);
  ASSERT_TRUE(engine->getAA());

  // Setting to the same value repeatedly should not change the observable value.
  engine->setAA(true);
  EXPECT_TRUE(engine->getAA());

  engine->setAA(false);
  ASSERT_FALSE(engine->getAA());

  engine->setAA(false);
  EXPECT_FALSE(engine->getAA());
}

TEST_F(SplashFTFontEngineTest_2604, MultipleInstancesMaintainIndependentAAState_2604) {
  auto engine1 = CreateEngineOrSkip(/*aa=*/false, /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/false);
  auto engine2 = CreateEngineOrSkip(/*aa=*/false, /*enableFreeTypeHinting=*/true, /*enableSlightHinting=*/false);

  engine1->setAA(true);
  engine2->setAA(false);

  EXPECT_TRUE(engine1->getAA());
  EXPECT_FALSE(engine2->getAA());

  engine1->setAA(false);
  engine2->setAA(true);

  EXPECT_FALSE(engine1->getAA());
  EXPECT_TRUE(engine2->getAA());
}

}  // namespace