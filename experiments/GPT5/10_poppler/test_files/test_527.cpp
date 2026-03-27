// Copyright (C) 2026
// Unit tests for GfxPatchMeshShading::getParameterDomainMin
// TEST_ID: 527

#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <utility>
#include <vector>

#include "poppler/Function.h"
#include "poppler/GfxState.h"

// A simple concrete Function we can pass into GfxPatchMeshShading.
// It uses the public Function base API and only touches protected members
// (which are part of the dependency's interface surface for subclasses).
class TestFunctionForDomain_527 final : public Function {
public:
  TestFunctionForDomain_527(double dmin, double dmax) : Function() {
    // Make the function have at least one input dimension.
    // domain[][] is protected in Function, so it's legal to set from a subclass.
    m = 1;
    domain[0][0] = dmin;
    domain[0][1] = dmax;
  }

  ~TestFunctionForDomain_527() override = default;
};

class GfxPatchMeshShadingTest_527 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxPatchMeshShading>
  MakeShadingWithFuncs(std::vector<std::unique_ptr<Function>> &&funcs) {
    // Patches are irrelevant for getParameterDomainMin() behavior as observed
    // through the public interface. Keep them minimal.
    return std::make_unique<GfxPatchMeshShading>(
        /*typeA=*/0,
        /*patchesA=*/nullptr,
        /*nPatchesA=*/0,
        std::move(funcs));
  }
};

TEST_F(GfxPatchMeshShadingTest_527, ReturnsDomainMinFromFirstFunction_527) {
  auto f0 = std::make_unique<TestFunctionForDomain_527>(-1.25, 2.5);
  const double expected = f0->getDomainMin(0);

  std::vector<std::unique_ptr<Function>> funcs;
  funcs.push_back(std::move(f0));
  funcs.push_back(std::make_unique<TestFunctionForDomain_527>(123.0, 456.0));

  auto shading = MakeShadingWithFuncs(std::move(funcs));
  ASSERT_TRUE(shading);

  EXPECT_DOUBLE_EQ(expected, shading->getParameterDomainMin());
}

TEST_F(GfxPatchMeshShadingTest_527, UsesFirstFunctionEvenWhenMultiplePresent_527) {
  auto f0 = std::make_unique<TestFunctionForDomain_527>(0.0, 1.0);
  const double expected_first = f0->getDomainMin(0);

  auto f1 = std::make_unique<TestFunctionForDomain_527>(-999.0, 999.0);
  const double not_expected_second = f1->getDomainMin(0);
  ASSERT_NE(expected_first, not_expected_second); // sanity for the test

  std::vector<std::unique_ptr<Function>> funcs;
  funcs.push_back(std::move(f0));
  funcs.push_back(std::move(f1));

  auto shading = MakeShadingWithFuncs(std::move(funcs));
  ASSERT_TRUE(shading);

  EXPECT_DOUBLE_EQ(expected_first, shading->getParameterDomainMin());
}

TEST_F(GfxPatchMeshShadingTest_527, BoundaryValuesArePropagated_527) {
  const double kNegLarge = -std::numeric_limits<double>::max() / 4.0;
  const double kPosLarge =  std::numeric_limits<double>::max() / 4.0;

  auto f0 = std::make_unique<TestFunctionForDomain_527>(kNegLarge, kPosLarge);
  const double expected = f0->getDomainMin(0);

  std::vector<std::unique_ptr<Function>> funcs;
  funcs.push_back(std::move(f0));

  auto shading = MakeShadingWithFuncs(std::move(funcs));
  ASSERT_TRUE(shading);

  EXPECT_DOUBLE_EQ(expected, shading->getParameterDomainMin());
}

#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
TEST_F(GfxPatchMeshShadingTest_527, DeathWhenNotParameterized_527) {
  // When not parameterized, getParameterDomainMin() is expected to assert.
  std::vector<std::unique_ptr<Function>> no_funcs;
  auto shading = MakeShadingWithFuncs(std::move(no_funcs));
  ASSERT_TRUE(shading);

  EXPECT_DEATH({ (void)shading->getParameterDomainMin(); }, ".*");
}
#endif