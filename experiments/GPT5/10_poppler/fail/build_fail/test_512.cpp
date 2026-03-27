//===----------------------------------------------------------------------===//
// Unit tests for GfxUnivariateShading::getNFuncs()
// File: GfxUnivariateShading_getNFuncs_test_512.cpp
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>

#include "poppler/GfxState.h"
#include "poppler/Function.h"

namespace {

class GfxUnivariateShadingTest_512 : public ::testing::Test
{
protected:
  static std::vector<std::unique_ptr<Function>> MakeIdentityFuncs(int n)
  {
    std::vector<std::unique_ptr<Function>> funcs;
    funcs.reserve(n);
    for (int i = 0; i < n; ++i) {
      funcs.push_back(std::make_unique<IdentityFunction>());
    }
    return funcs;
  }
};

TEST_F(GfxUnivariateShadingTest_512, GetNFuncsReflectsConstructorCount_512)
{
  auto funcs = MakeIdentityFuncs(3);

  GfxAxialShading shading(/*x0A=*/0.0, /*y0A=*/0.0,
                         /*x1A=*/10.0, /*y1A=*/0.0,
                         /*t0A=*/0.0, /*t1A=*/1.0,
                         std::move(funcs),
                         /*extend0A=*/false, /*extend1A=*/true);

  EXPECT_EQ(shading.getNFuncs(), 3);
}

TEST_F(GfxUnivariateShadingTest_512, GetNFuncsOneFunctionBoundary_512)
{
  auto funcs = MakeIdentityFuncs(1);

  GfxAxialShading shading(/*x0A=*/1.0, /*y0A=*/2.0,
                         /*x1A=*/3.0, /*y1A=*/4.0,
                         /*t0A=*/-1.0, /*t1A=*/2.0,
                         std::move(funcs),
                         /*extend0A=*/true, /*extend1A=*/false);

  EXPECT_EQ(shading.getNFuncs(), 1);
}

TEST_F(GfxUnivariateShadingTest_512, GetNFuncsLargerCount_512)
{
  constexpr int kCount = 10;
  auto funcs = MakeIdentityFuncs(kCount);

  GfxRadialShading shading(/*x0A=*/0.0, /*y0A=*/0.0, /*r0A=*/1.0,
                          /*x1A=*/5.0, /*y1A=*/0.0, /*r1A=*/2.0,
                          /*t0A=*/0.0, /*t1A=*/1.0,
                          std::move(funcs),
                          /*extend0A=*/false, /*extend1A=*/false);

  EXPECT_EQ(shading.getNFuncs(), kCount);
}

TEST_F(GfxUnivariateShadingTest_512, CopyConstructorPreservesFunctionCount_512)
{
  auto funcs = MakeIdentityFuncs(4);

  GfxAxialShading original(/*x0A=*/0.0, /*y0A=*/0.0,
                          /*x1A=*/1.0, /*y1A=*/1.0,
                          /*t0A=*/0.0, /*t1A=*/1.0,
                          std::move(funcs),
                          /*extend0A=*/true, /*extend1A=*/true);

  GfxAxialShading copy(&original);

  EXPECT_EQ(original.getNFuncs(), 4);
  EXPECT_EQ(copy.getNFuncs(), 4);
}

TEST_F(GfxUnivariateShadingTest_512, GetNFuncsUnaffectedByReadingFuncs_512)
{
  auto funcs = MakeIdentityFuncs(2);

  GfxRadialShading shading(/*x0A=*/0.0, /*y0A=*/0.0, /*r0A=*/1.0,
                          /*x1A=*/0.0, /*y1A=*/0.0, /*r1A=*/2.0,
                          /*t0A=*/0.0, /*t1A=*/1.0,
                          std::move(funcs),
                          /*extend0A=*/true, /*extend1A=*/false);

  ASSERT_EQ(shading.getNFuncs(), 2);

  // Read back valid function pointers; count should remain stable.
  EXPECT_NE(shading.getFunc(0), nullptr);
  EXPECT_NE(shading.getFunc(1), nullptr);
  EXPECT_EQ(shading.getNFuncs(), 2);
}

} // namespace