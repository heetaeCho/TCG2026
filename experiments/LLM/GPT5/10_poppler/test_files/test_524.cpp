// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_gfxpatchmeshshading_getnpatches_524.cpp

#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>

#include "poppler/GfxState.h"

namespace {

class GfxPatchMeshShadingTest_524 : public ::testing::Test {
protected:
  static std::vector<std::unique_ptr<Function>> MakeEmptyFuncs() {
    return std::vector<std::unique_ptr<Function>>{};
  }

  // Helper that allocates an array of patches when n > 0.
  // Ownership is intentionally handed to GfxPatchMeshShading via its constructor,
  // matching the public API contract implied by the raw pointer parameter.
  static GfxPatch *MakePatches(int n) {
    if (n <= 0) {
      return nullptr;
    }
    return new GfxPatch[n];
  }
};

TEST_F(GfxPatchMeshShadingTest_524, ConstructWithZeroPatches_ReturnsZero_524) {
  const int typeA = 6; // Any valid mesh shading type is acceptable for construction tests.
  auto funcs = MakeEmptyFuncs();

  auto *patches = MakePatches(0);
  GfxPatchMeshShading shading(typeA, patches, 0, std::move(funcs));

  EXPECT_EQ(shading.getNPatches(), 0);
}

TEST_F(GfxPatchMeshShadingTest_524, ConstructWithOnePatch_ReturnsOne_524) {
  const int typeA = 6;
  auto funcs = MakeEmptyFuncs();

  auto *patches = MakePatches(1);
  GfxPatchMeshShading shading(typeA, patches, 1, std::move(funcs));

  EXPECT_EQ(shading.getNPatches(), 1);
}

TEST_F(GfxPatchMeshShadingTest_524, ConstructWithManyPatches_ReturnsCount_524) {
  const int typeA = 6;
  auto funcs = MakeEmptyFuncs();

  constexpr int kCount = 1000;
  auto *patches = MakePatches(kCount);
  GfxPatchMeshShading shading(typeA, patches, kCount, std::move(funcs));

  EXPECT_EQ(shading.getNPatches(), kCount);
}

TEST_F(GfxPatchMeshShadingTest_524, CopyConstructor_PreservesPatchCount_524) {
  const int typeA = 6;
  auto funcs = MakeEmptyFuncs();

  constexpr int kCount = 7;
  auto *patches = MakePatches(kCount);
  GfxPatchMeshShading original(typeA, patches, kCount, std::move(funcs));

  GfxPatchMeshShading copy(&original);

  EXPECT_EQ(original.getNPatches(), kCount);
  EXPECT_EQ(copy.getNPatches(), kCount);
}

TEST_F(GfxPatchMeshShadingTest_524, CopyMethod_PreservesPatchCount_524) {
  const int typeA = 6;
  auto funcs = MakeEmptyFuncs();

  constexpr int kCount = 3;
  auto *patches = MakePatches(kCount);
  GfxPatchMeshShading shading(typeA, patches, kCount, std::move(funcs));

  // copy() returns a GfxShading; verify we can observe the same patch count via dynamic type.
  std::unique_ptr<GfxShading> baseCopy = shading.copy();
  ASSERT_NE(baseCopy, nullptr);

  auto *meshCopy = dynamic_cast<GfxPatchMeshShading *>(baseCopy.get());
  ASSERT_NE(meshCopy, nullptr);

  EXPECT_EQ(meshCopy->getNPatches(), kCount);
}

TEST_F(GfxPatchMeshShadingTest_524, GetNPatches_IsIdempotent_524) {
  const int typeA = 6;
  auto funcs = MakeEmptyFuncs();

  constexpr int kCount = 2;
  auto *patches = MakePatches(kCount);
  GfxPatchMeshShading shading(typeA, patches, kCount, std::move(funcs));

  const int first = shading.getNPatches();
  const int second = shading.getNPatches();
  const int third = shading.getNPatches();

  EXPECT_EQ(first, kCount);
  EXPECT_EQ(second, kCount);
  EXPECT_EQ(third, kCount);
}

} // namespace