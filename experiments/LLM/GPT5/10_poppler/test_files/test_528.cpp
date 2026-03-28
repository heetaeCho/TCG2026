// TEST_ID: 528
// File: GfxPatchMeshShading_getParameterDomainMax_528_test.cpp

#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>

#include "poppler/GfxState.h"
#include "poppler/Function.h"

namespace {

// A tiny concrete Function that is safe to query for getDomainMax(0).
// We do NOT assume how Function computes getDomainMax internally; we only
// compare GfxPatchMeshShading's result to Function::getDomainMax(0) on the
// same instance.
class TestFunctionForDomain_528 : public Function {
public:
  TestFunctionForDomain_528(double dmin, double dmax)
  {
    // Function's storage is protected, so we can configure a valid 1D domain.
    m = 1;
    domain[0][0] = dmin;
    domain[0][1] = dmax;
    hasRange = false;
  }

  ~TestFunctionForDomain_528() override = default;
};

class GfxPatchMeshShadingTest_528 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxPatchMeshShading> MakeShadingWithFuncs(
      std::vector<std::unique_ptr<Function>> &&funcs)
  {
    // Minimal patch setup: no patches.
    // The unit tests only exercise the parameter-domain forwarding behavior.
    constexpr int kAnyType = 0;
    return std::make_unique<GfxPatchMeshShading>(
        kAnyType, /*patchesA=*/nullptr, /*nPatchesA=*/0, std::move(funcs));
  }
};

} // namespace

TEST_F(GfxPatchMeshShadingTest_528, ParameterDomainMax_ForwardsToFirstFunction_528)
{
  auto f0 = std::make_unique<TestFunctionForDomain_528>(-1.0, 2.5);
  auto f1 = std::make_unique<TestFunctionForDomain_528>(0.0, 99.0);

  // Capture expected values from the Functions themselves (black-box friendly).
  const double expected0 = f0->getDomainMax(0);
  const double expected1 = f1->getDomainMax(0);

  std::vector<std::unique_ptr<Function>> funcs;
  funcs.push_back(std::move(f0));
  funcs.push_back(std::move(f1));

  auto shading = MakeShadingWithFuncs(std::move(funcs));

  // Observable precondition.
  EXPECT_TRUE(shading->isParameterized());

  // getParameterDomainMax() should match the first function's domain max.
  EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), expected0);

  // And (if it uses the first function) it should not match the second
  // when they differ.
  EXPECT_NE(shading->getParameterDomainMax(), expected1);
}

TEST_F(GfxPatchMeshShadingTest_528, ParameterDomainMax_HandlesNegativeAndLargeValues_528)
{
  // Boundary-ish values (still finite).
  auto f0 = std::make_unique<TestFunctionForDomain_528>(-123456.0, 1.0e300);
  const double expected0 = f0->getDomainMax(0);

  std::vector<std::unique_ptr<Function>> funcs;
  funcs.push_back(std::move(f0));

  auto shading = MakeShadingWithFuncs(std::move(funcs));

  EXPECT_TRUE(shading->isParameterized());
  EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), expected0);
}

TEST_F(GfxPatchMeshShadingTest_528, ParameterDomainMax_DeathWhenNotParameterized_528)
{
  std::vector<std::unique_ptr<Function>> funcs; // empty
  auto shading = MakeShadingWithFuncs(std::move(funcs));

  // Observable precondition: not parameterized.
  EXPECT_FALSE(shading->isParameterized());

  // Implementation shows an assert(isParameterized()) guard; exercise that.
  ASSERT_DEATH(
      {
        (void)shading->getParameterDomainMax();
      },
      "");
}