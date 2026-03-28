// TEST_ID = 522
// File: gfx_gouraud_triangle_shading_get_parameter_domain_min_test_522.cpp

#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>

#include "GfxState.h"
#include "Function.h"

// A small concrete Function we can control for testing.
// This is a test collaborator (not re-implementing Poppler logic), used to provide
// deterministic domain min/max values through the public Function API.
class TestDomainFunction_522 : public Function {
public:
  TestDomainFunction_522(double dmin0, double dmax0) : Function() {
    // Function::getDomainMin/Max reads from protected `domain` and uses `m` as input size.
    m = 1;
    domain[0][0] = dmin0;
    domain[0][1] = dmax0;
  }

  // No need to override transform() for these tests.
};

class GfxGouraudTriangleShadingTest_522 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxGouraudTriangleShading> MakeShadingWithFuncs(
      std::vector<std::unique_ptr<Function>> &&funcs) {
    // Minimal vertex/triangle data to satisfy the constructor signature.
    // The tests below only exercise parameter domain getters.
    auto *verts = new GfxGouraudVertex[3](); // value-initialize
    auto *tris = new int[1][3]{{0, 1, 2}};

    // Use a common Gouraud triangle shading type value (4 is a valid PDF shading type for Gouraud triangles).
    // We don't assume internal behavior beyond "this object can be constructed".
    auto shading = std::make_unique<GfxGouraudTriangleShading>(
        /*typeA=*/4, verts, /*nVerticesA=*/3, tris, /*nTrianglesA=*/1, std::move(funcs));

    // Note: GfxGouraudTriangleShading owns/cleans up the passed arrays in Poppler's implementation.
    // The test treats it as a black box and does not delete them here.
    return shading;
  }
};

TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMin_ReturnsFunctionDomainMin_522) {
  std::vector<std::unique_ptr<Function>> funcs;
  funcs.emplace_back(std::make_unique<TestDomainFunction_522>(-3.25, 9.5));

  auto shading = MakeShadingWithFuncs(std::move(funcs));

  // Observable behavior: for parameterized shading, getter returns funcs[0]->getDomainMin(0).
  EXPECT_DOUBLE_EQ(shading->getParameterDomainMin(), -3.25);
}

TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMin_BoundaryLargeMagnitude_522) {
  const double kMin = -1.0e300;
  const double kMax =  1.0e300;

  std::vector<std::unique_ptr<Function>> funcs;
  funcs.emplace_back(std::make_unique<TestDomainFunction_522>(kMin, kMax));

  auto shading = MakeShadingWithFuncs(std::move(funcs));

  EXPECT_DOUBLE_EQ(shading->getParameterDomainMin(), kMin);
}

TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMin_DoesNotDependOnOtherInputs_522) {
  // Provide a domain that would be obviously distinct if anything else leaked into the result.
  std::vector<std::unique_ptr<Function>> funcs;
  funcs.emplace_back(std::make_unique<TestDomainFunction_522>(123.456, 789.012));

  auto shading = MakeShadingWithFuncs(std::move(funcs));

  EXPECT_DOUBLE_EQ(shading->getParameterDomainMin(), 123.456);
}

TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMax_ReturnsFunctionDomainMax_522) {
  // Even though the prompt highlights getParameterDomainMin(), the class interface also provides Max.
  // This test is symmetric and checks the same observable behavior via the public API.
  std::vector<std::unique_ptr<Function>> funcs;
  funcs.emplace_back(std::make_unique<TestDomainFunction_522>(-10.0, 42.0));

  auto shading = MakeShadingWithFuncs(std::move(funcs));

  EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), 42.0);
}

TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMin_DeathWhenNotParameterized_522) {
  // getParameterDomainMin() contains `assert(isParameterized())`.
  // In release builds, assertions may be compiled out; only enforce this in debug.
#if !defined(NDEBUG)
  std::vector<std::unique_ptr<Function>> funcs; // empty => expected "not parameterized" in typical designs
  auto shading = MakeShadingWithFuncs(std::move(funcs));

  ASSERT_DEATH({ (void)shading->getParameterDomainMin(); }, ".*");
#else
  GTEST_SKIP() << "Assertions are disabled (NDEBUG). Death test not applicable.";
#endif
}