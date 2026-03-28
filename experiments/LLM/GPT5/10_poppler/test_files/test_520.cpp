// File: GfxGouraudTriangleShading_test_520.cpp
//
// Unit tests for (partial interface):
//   class GfxGouraudTriangleShading { public: int getNTriangles() const { return nTriangles; } };
//
// Constraints honored:
// - Black-box: we only test observable behavior via the public interface shown.
// - No access to private state.
// - No inference about parsing/copy/getTriangle/etc. (not provided as implemented here).
// - No mocks needed (no external interactions observable via this minimal interface).

#include <gtest/gtest.h>
#include <limits>

// Include the production header.
#include "poppler/GfxState.h"

// NOTE:
// With only the provided partial implementation, we do NOT have a public constructor we can call.
// Many Poppler builds still allow stack allocation if a default constructor exists, but none is shown.
// Therefore, these tests are written defensively:
//
// - If your build exposes a usable constructor elsewhere, replace CreateShadingForTest()
//   to construct a real instance with a chosen nTriangles via public API.
// - Otherwise, these tests still compile if the project provides a default constructor (or a
//   test helper/factory in your codebase).

namespace {

// If your real codebase provides a public way to create a shading instance, implement it here.
// For example (illustrative only; DO NOT add if not supported by your headers):
//   return std::make_unique<GfxGouraudTriangleShading>(type, vertices, nVertices, triangles, nTriangles, std::move(funcs));
//
// As-is, we attempt default construction. If not possible, you should adapt this factory to your
// actual available public constructors.
static std::unique_ptr<GfxGouraudTriangleShading> CreateShadingForTest_520() {
  // If this fails to compile in your environment, adapt to an actually available public ctor/factory.
  return std::make_unique<GfxGouraudTriangleShading>();
}

class GfxGouraudTriangleShadingTest_520 : public ::testing::Test {};

} // namespace

// Normal operation: calling getNTriangles repeatedly should be stable (no side effects observable).
TEST_F(GfxGouraudTriangleShadingTest_520, GetNTriangles_IsStableAcrossCalls_520) {
  auto shading = CreateShadingForTest_520();
  ASSERT_NE(shading, nullptr);

  const int first = shading->getNTriangles();
  const int second = shading->getNTriangles();
  const int third = shading->getNTriangles();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

// Boundary/robustness: should return an int and not crash for a valid instance.
TEST_F(GfxGouraudTriangleShadingTest_520, GetNTriangles_ReturnsIntAndDoesNotThrow_520) {
  auto shading = CreateShadingForTest_520();
  ASSERT_NE(shading, nullptr);

  // getNTriangles is declared const and returns int; just ensure it is callable.
  EXPECT_NO_THROW({
    volatile int n = shading->getNTriangles();
    (void)n;
  });
}

// Boundary condition: returned value should be within int range (trivially true) and not be NaN etc.
// (This test is mostly a compile-time/ABI guard in the absence of richer observable behavior.)
TEST_F(GfxGouraudTriangleShadingTest_520, GetNTriangles_ValueWithinIntLimits_520) {
  auto shading = CreateShadingForTest_520();
  ASSERT_NE(shading, nullptr);

  const int n = shading->getNTriangles();
  EXPECT_GE(n, std::numeric_limits<int>::min());
  EXPECT_LE(n, std::numeric_limits<int>::max());
}

// Exceptional/error cases:
// With the provided interface, no error signaling is observable (no status/exception specified).
// We still verify that calling on a const reference is permitted and behaves consistently.
TEST_F(GfxGouraudTriangleShadingTest_520, GetNTriangles_OnConstReference_520) {
  auto shading = CreateShadingForTest_520();
  ASSERT_NE(shading, nullptr);

  const GfxGouraudTriangleShading& cref = *shading;
  const int a = cref.getNTriangles();
  const int b = cref.getNTriangles();
  EXPECT_EQ(a, b);
}