// TEST_ID = 521
// Unit tests for GfxGouraudTriangleShading::isParameterized()

#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>

#if __has_include("poppler/GfxState.h")
#include "poppler/GfxState.h"
#elif __has_include("GfxState.h")
#include "GfxState.h"
#else
#error "Cannot find poppler GfxState.h (tried <poppler/GfxState.h> and <GfxState.h>)"
#endif

namespace {

class GfxGouraudTriangleShadingTest_521 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxGouraudTriangleShading> MakeShadingWithFuncsCount(int funcsCount) {
    std::vector<std::unique_ptr<Function>> funcs;
    funcs.reserve(funcsCount);
    for (int i = 0; i < funcsCount; ++i) {
      // We don't need a concrete Function implementation for this test:
      // a non-empty vector is observable through isParameterized().
      funcs.emplace_back(std::unique_ptr<Function>(nullptr));
    }

    // Boundary-safe construction: no vertices/triangles, null pointers with counts = 0.
    // We treat the implementation as a black box and only rely on public behavior.
    return std::make_unique<GfxGouraudTriangleShading>(
        /*typeA=*/4,
        /*verticesA=*/nullptr,
        /*nVerticesA=*/0,
        /*trianglesA=*/static_cast<int (*)[3]>(nullptr),
        /*nTrianglesA=*/0,
        std::move(funcs));
  }
};

} // namespace

TEST_F(GfxGouraudTriangleShadingTest_521, IsParameterizedFalseWhenNoFunctions_521) {
  auto shading = MakeShadingWithFuncsCount(0);
  ASSERT_NE(shading, nullptr);
  EXPECT_FALSE(shading->isParameterized());
}

TEST_F(GfxGouraudTriangleShadingTest_521, IsParameterizedTrueWhenAtLeastOneFunction_521) {
  auto shading = MakeShadingWithFuncsCount(1);
  ASSERT_NE(shading, nullptr);
  EXPECT_TRUE(shading->isParameterized());
}

TEST_F(GfxGouraudTriangleShadingTest_521, IsParameterizedPreservedByCopyCtor_521) {
  auto shadingFalse = MakeShadingWithFuncsCount(0);
  ASSERT_NE(shadingFalse, nullptr);
  EXPECT_FALSE(shadingFalse->isParameterized());

  GfxGouraudTriangleShading copiedFalse(shadingFalse.get());
  EXPECT_FALSE(copiedFalse.isParameterized());

  auto shadingTrue = MakeShadingWithFuncsCount(1);
  ASSERT_NE(shadingTrue, nullptr);
  EXPECT_TRUE(shadingTrue->isParameterized());

  GfxGouraudTriangleShading copiedTrue(shadingTrue.get());
  EXPECT_TRUE(copiedTrue.isParameterized());
}

TEST_F(GfxGouraudTriangleShadingTest_521, IsParameterizedPreservedByVirtualCopy_521) {
  auto shading = MakeShadingWithFuncsCount(1);
  ASSERT_NE(shading, nullptr);
  const bool expected = shading->isParameterized();

  auto baseCopy = shading->copy();
  ASSERT_NE(baseCopy, nullptr);

  auto *derivedCopy = dynamic_cast<GfxGouraudTriangleShading *>(baseCopy.get());
  ASSERT_NE(derivedCopy, nullptr);

  EXPECT_EQ(expected, derivedCopy->isParameterized());
}