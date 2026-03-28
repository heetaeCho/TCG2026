// TEST_ID is 510
#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>

#include "GfxState.h"

// NOTE: These tests treat GfxUnivariateShading as a black box and only verify
// observable behavior through its public interface (getExtend0()).

class GfxUnivariateShadingTest_510 : public ::testing::Test {
protected:
  // Helper to build a shading instance using the public constructor signature.
  // We intentionally pass an empty function vector since this test focuses only
  // on the extend flags exposed by getters.
  static std::unique_ptr<GfxUnivariateShading> MakeShading(bool extend0, bool extend1) {
    std::vector<std::unique_ptr<Function>> funcs; // empty
    return std::make_unique<GfxUnivariateShading>(
        /*typeA=*/2, /*t0A=*/0.0, /*t1A=*/1.0, std::move(funcs), extend0, extend1);
  }
};

TEST_F(GfxUnivariateShadingTest_510, GetExtend0_ReturnsFalseWhenConstructedFalse_510) {
  auto shading = MakeShading(/*extend0=*/false, /*extend1=*/false);
  ASSERT_NE(shading, nullptr);
  EXPECT_FALSE(shading->getExtend0());
}

TEST_F(GfxUnivariateShadingTest_510, GetExtend0_ReturnsTrueWhenConstructedTrue_510) {
  auto shading = MakeShading(/*extend0=*/true, /*extend1=*/false);
  ASSERT_NE(shading, nullptr);
  EXPECT_TRUE(shading->getExtend0());
}

TEST_F(GfxUnivariateShadingTest_510, GetExtend0_DoesNotDependOnExtend1Value_510) {
  auto shadingExtend1False = MakeShading(/*extend0=*/true, /*extend1=*/false);
  auto shadingExtend1True  = MakeShading(/*extend0=*/true, /*extend1=*/true);

  ASSERT_NE(shadingExtend1False, nullptr);
  ASSERT_NE(shadingExtend1True, nullptr);

  EXPECT_TRUE(shadingExtend1False->getExtend0());
  EXPECT_TRUE(shadingExtend1True->getExtend0());
}

TEST_F(GfxUnivariateShadingTest_510, CopyConstructor_PreservesExtend0False_510) {
  auto original = MakeShading(/*extend0=*/false, /*extend1=*/true);
  ASSERT_NE(original, nullptr);

  GfxUnivariateShading copy(original.get());
  EXPECT_FALSE(copy.getExtend0());
}

TEST_F(GfxUnivariateShadingTest_510, CopyConstructor_PreservesExtend0True_510) {
  auto original = MakeShading(/*extend0=*/true, /*extend1=*/false);
  ASSERT_NE(original, nullptr);

  GfxUnivariateShading copy(original.get());
  EXPECT_TRUE(copy.getExtend0());
}