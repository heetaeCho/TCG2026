// TEST_ID: 523
#include <gtest/gtest.h>

#include <cassert>
#include <cmath>
#include <memory>
#include <vector>

#include "GfxState.h"
#include "Function.h"

// A small helper Function that lets tests control the input domain.
// We do NOT re-implement poppler logic; we only set protected fields
// so that the public, non-virtual Function::getDomainMax() returns
// an observable value through the shading API.
class TestDomainFunction_523 final : public Function {
public:
  explicit TestDomainFunction_523(double domainMin0, double domainMax0) : Function() {
    // Ensure index 0 is valid for getDomainMax(0).
    m = 1;
    domain[0][0] = domainMin0;
    domain[0][1] = domainMax0;
  }

  ~TestDomainFunction_523() override = default;
};

class GfxGouraudTriangleShadingTest_523 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxGouraudTriangleShading> MakeShadingWithFuncs(
      std::vector<std::unique_ptr<Function>> &&funcs) {
    // Minimal geometry: 3 vertices, 1 triangle (0,1,2).
    // We rely only on the public constructor; internals are black-box.
    auto *vertices = new GfxGouraudVertex[3]();
    vertices[0].x = 0.0;
    vertices[0].y = 0.0;
    vertices[1].x = 1.0;
    vertices[1].y = 0.0;
    vertices[2].x = 0.0;
    vertices[2].y = 1.0;

    auto *triangles = new int[1][3];
    (*triangles)[0] = 0;
    (*triangles)[1] = 1;
    (*triangles)[2] = 2;

    // typeA: pass a valid Gouraud triangle shading type used by poppler.
    // We avoid assuming semantics beyond being accepted by the constructor.
    // Commonly, Gouraud triangle mesh shadings are type 4 or 5.
    const int typeA = 4;

    return std::make_unique<GfxGouraudTriangleShading>(
        typeA, vertices, 3, triangles, 1, std::move(funcs));
  }
};

TEST_F(GfxGouraudTriangleShadingTest_523, ParameterDomainMaxReflectsFunctionDomainMax_523) {
  std::vector<std::unique_ptr<Function>> funcs;
  funcs.emplace_back(std::make_unique<TestDomainFunction_523>(-1.0, 42.25));

  auto shading = MakeShadingWithFuncs(std::move(funcs));

  // Observable behavior: getParameterDomainMax() returns funcs[0]->getDomainMax(0)
  // when parameterized (as enforced by the assert in the implementation).
  EXPECT_TRUE(shading->isParameterized());
  EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), 42.25);
}

TEST_F(GfxGouraudTriangleShadingTest_523, ParameterDomainMaxHandlesZeroDomainMax_523) {
  std::vector<std::unique_ptr<Function>> funcs;
  funcs.emplace_back(std::make_unique<TestDomainFunction_523>(0.0, 0.0));

  auto shading = MakeShadingWithFuncs(std::move(funcs));

  EXPECT_TRUE(shading->isParameterized());
  EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), 0.0);
}

TEST_F(GfxGouraudTriangleShadingTest_523, ParameterDomainMaxHandlesNegativeDomainMax_523) {
  std::vector<std::unique_ptr<Function>> funcs;
  funcs.emplace_back(std::make_unique<TestDomainFunction_523>(-10.0, -0.5));

  auto shading = MakeShadingWithFuncs(std::move(funcs));

  EXPECT_TRUE(shading->isParameterized());
  EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), -0.5);
}

TEST_F(GfxGouraudTriangleShadingTest_523, ParameterDomainMaxHandlesLargeMagnitudeDomainMax_523) {
  const double kLarge = 1.0e300;
  std::vector<std::unique_ptr<Function>> funcs;
  funcs.emplace_back(std::make_unique<TestDomainFunction_523>(0.0, kLarge));

  auto shading = MakeShadingWithFuncs(std::move(funcs));

  EXPECT_TRUE(shading->isParameterized());
  EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), kLarge);
}

TEST_F(GfxGouraudTriangleShadingTest_523, ParameterDomainMaxDiesWhenNotParameterizedIfAssertsEnabled_523) {
#if !defined(NDEBUG)
  // Build a shading that (ideally) is not parameterized.
  // We do not assume how parameterization is determined; we observe it.
  std::vector<std::unique_ptr<Function>> funcs; // empty
  auto shading = MakeShadingWithFuncs(std::move(funcs));

  if (shading->isParameterized()) {
    GTEST_SKIP() << "Shading reports parameterized even with empty function set; "
                    "cannot reliably trigger the assertion via public API.";
  }

  // The implementation contains: assert(isParameterized());
  EXPECT_DEATH((void)shading->getParameterDomainMax(), "");
#else
  GTEST_SKIP() << "Assertions are disabled (NDEBUG); EXPECT_DEATH would be ineffective.";
#endif
}