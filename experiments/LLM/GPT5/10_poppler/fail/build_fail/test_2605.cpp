// SplashFTFontEngine_test_2605.cc
//
// Unit tests for SplashFTFontEngine::setAA / getAA
// Constraints followed:
// - Treat implementation as black box
// - Test only observable behavior via public interface (getAA / setAA / init / dtor)
// - No private state access
//
// File under test: ./TestProjects/poppler/splash/SplashFTFontEngine.h

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "TestProjects/poppler/splash/SplashFTFontEngine.h"

namespace {

struct SplashFTFontEngineDeleter_2605 {
  void operator()(SplashFTFontEngine* p) const noexcept { delete p; }
};

using EnginePtr_2605 = std::unique_ptr<SplashFTFontEngine, SplashFTFontEngineDeleter_2605>;

static EnginePtr_2605 CreateEngineOrSkip_2605(bool aa) {
  // We don't assume init() always succeeds on every build configuration.
  // If it fails (nullptr), tests that require an instance will be skipped.
  SplashFTFontEngine* raw = SplashFTFontEngine::init(
      aa,
      /*enableFreeTypeHintingA=*/true,
      /*enableSlightHintingA=*/true);
  if (!raw) {
    GTEST_SKIP() << "SplashFTFontEngine::init returned nullptr; FreeType/backend may be unavailable.";
  }
  return EnginePtr_2605(raw);
}

class SplashFTFontEngineTest_2605 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Start from aa=false so tests can flip both directions deterministically.
    engine_ = CreateEngineOrSkip_2605(/*aa=*/false);
  }

  EnginePtr_2605 engine_;
};

}  // namespace

// Compile-time interface/contract checks (based purely on the header).
TEST(SplashFTFontEngineCompileTimeTest_2605, CopyAndAssignAreDeleted_2605) {
  static_assert(!std::is_copy_constructible_v<SplashFTFontEngine>,
                "SplashFTFontEngine should not be copy constructible (copy ctor deleted).");
  static_assert(!std::is_copy_assignable_v<SplashFTFontEngine>,
                "SplashFTFontEngine should not be copy assignable (operator= deleted).");
}

// Normal operation: setting AA true is observable via getAA().
TEST_F(SplashFTFontEngineTest_2605, SetAATrueReflectsInGetAA_2605) {
  ASSERT_NE(engine_.get(), nullptr);

  engine_->setAA(true);
  EXPECT_TRUE(engine_->getAA());
}

// Normal operation: setting AA false is observable via getAA().
TEST_F(SplashFTFontEngineTest_2605, SetAAFalseReflectsInGetAA_2605) {
  ASSERT_NE(engine_.get(), nullptr);

  engine_->setAA(true);
  ASSERT_TRUE(engine_->getAA());

  engine_->setAA(false);
  EXPECT_FALSE(engine_->getAA());
}

// Boundary-ish: calling setAA with the current value should be safe and keep state stable.
TEST_F(SplashFTFontEngineTest_2605, SetAAIdempotentTrue_2605) {
  ASSERT_NE(engine_.get(), nullptr);

  engine_->setAA(true);
  ASSERT_TRUE(engine_->getAA());

  engine_->setAA(true);
  EXPECT_TRUE(engine_->getAA());
}

// Boundary-ish: idempotent for false as well.
TEST_F(SplashFTFontEngineTest_2605, SetAAIdempotentFalse_2605) {
  ASSERT_NE(engine_.get(), nullptr);

  engine_->setAA(false);
  ASSERT_FALSE(engine_->getAA());

  engine_->setAA(false);
  EXPECT_FALSE(engine_->getAA());
}

// Boundary: rapid toggling (sequence) ends in the last value set.
TEST_F(SplashFTFontEngineTest_2605, SetAAToggleSequenceEndsWithLastValue_2605) {
  ASSERT_NE(engine_.get(), nullptr);

  engine_->setAA(false);
  engine_->setAA(true);
  engine_->setAA(false);
  engine_->setAA(true);

  EXPECT_TRUE(engine_->getAA());

  engine_->setAA(false);
  EXPECT_FALSE(engine_->getAA());
}

// Error/exceptional (observable): init may fail (nullptr). Verify caller can handle it.
// This test does not assume success; it only checks that calling init is safe.
TEST(SplashFTFontEngineInitTest_2605, InitMayReturnNullButCallIsSafe_2605) {
  SplashFTFontEngine* e1 = SplashFTFontEngine::init(false, true, true);
  SplashFTFontEngine* e2 = SplashFTFontEngine::init(true, true, true);

  // Observable behavior: pointers are either valid or null; both are acceptable.
  // If valid, ensure we can delete safely to avoid leaks.
  if (e1) {
    delete e1;
  }
  if (e2) {
    delete e2;
  }

  SUCCEED();
}