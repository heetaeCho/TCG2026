// -*- mode: c++; tab-width: 2; indent-tabs-mode: nil; -*-
// The TEST_ID is 525
//
// Unit tests for GfxPatchMeshShading::getPatch(int)
//
// Constraints followed:
// - Treat implementation as a black box (no internal-state access).
// - Test only observable behavior via public interface.
// - No re-implementation of logic.

#include <gtest/gtest.h>

#include <memory>
#include <vector>

// Poppler headers
#include "GfxState.h"
#include "Function.h"

namespace {

class GfxPatchMeshShadingTest_525 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxPatchMeshShading> MakeShading(int nPatches) {
    // Allocate patches dynamically. Ownership semantics are intentionally not assumed here;
    // the tests do not compare against the original pointer addresses.
    auto *patches = new GfxPatch[nPatches]{}; // value-initialize

    std::vector<std::unique_ptr<Function>> funcs; // empty (no Function instances)

    // Shading types for patch mesh shadings are typically 6 or 7 in PDF.
    // We avoid asserting on type-specific behavior; we only need a constructible instance.
    const int typeA = 6;

    return std::make_unique<GfxPatchMeshShading>(typeA, patches, nPatches, std::move(funcs));
  }
};

TEST_F(GfxPatchMeshShadingTest_525, GetPatchReturnsNonNullForValidIndices_525) {
  auto shading = MakeShading(3);
  ASSERT_NE(shading, nullptr);

  // Valid indices should return non-null pointers.
  EXPECT_NE(shading->getPatch(0), nullptr);
  EXPECT_NE(shading->getPatch(1), nullptr);
  EXPECT_NE(shading->getPatch(2), nullptr);
}

TEST_F(GfxPatchMeshShadingTest_525, GetPatchIsStableForSameIndex_525) {
  auto shading = MakeShading(2);
  ASSERT_NE(shading, nullptr);

  const GfxPatch *p0a = shading->getPatch(0);
  const GfxPatch *p0b = shading->getPatch(0);

  ASSERT_NE(p0a, nullptr);
  ASSERT_NE(p0b, nullptr);
  EXPECT_EQ(p0a, p0b) << "Repeated calls for the same index should return the same address";
}

TEST_F(GfxPatchMeshShadingTest_525, GetPatchReturnsDistinctPointersForDifferentIndices_525) {
  auto shading = MakeShading(2);
  ASSERT_NE(shading, nullptr);

  const GfxPatch *p0 = shading->getPatch(0);
  const GfxPatch *p1 = shading->getPatch(1);

  ASSERT_NE(p0, nullptr);
  ASSERT_NE(p1, nullptr);
  EXPECT_NE(p0, p1);
}

TEST_F(GfxPatchMeshShadingTest_525, GetPatchPointersAreContiguousAcrossIndices_525) {
  auto shading = MakeShading(4);
  ASSERT_NE(shading, nullptr);

  // Based on the interface contract that getPatch(i) returns a pointer to the i-th patch,
  // we can verify contiguity across adjacent indices via pointer arithmetic.
  const GfxPatch *p0 = shading->getPatch(0);
  const GfxPatch *p1 = shading->getPatch(1);
  const GfxPatch *p2 = shading->getPatch(2);
  const GfxPatch *p3 = shading->getPatch(3);

  ASSERT_NE(p0, nullptr);
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  ASSERT_NE(p3, nullptr);

  EXPECT_EQ(p0 + 1, p1);
  EXPECT_EQ(p1 + 1, p2);
  EXPECT_EQ(p2 + 1, p3);
}

TEST_F(GfxPatchMeshShadingTest_525, GetPatchWorksOnConstObject_525) {
  auto shading = MakeShading(2);
  ASSERT_NE(shading, nullptr);

  const GfxPatchMeshShading &cshading = *shading;

  const GfxPatch *p0 = cshading.getPatch(0);
  const GfxPatch *p1 = cshading.getPatch(1);

  ASSERT_NE(p0, nullptr);
  ASSERT_NE(p1, nullptr);
  EXPECT_NE(p0, p1);
}

TEST_F(GfxPatchMeshShadingTest_525, GetPatchSupportsBoundaryIndices_525) {
  const int n = 5;
  auto shading = MakeShading(n);
  ASSERT_NE(shading, nullptr);

  // Boundary indices: 0 and n-1
  const GfxPatch *first = shading->getPatch(0);
  const GfxPatch *last = shading->getPatch(n - 1);

  ASSERT_NE(first, nullptr);
  ASSERT_NE(last, nullptr);

  // Sanity: last should be (first + (n-1)) if contiguous.
  EXPECT_EQ(first + (n - 1), last);
}

} // namespace