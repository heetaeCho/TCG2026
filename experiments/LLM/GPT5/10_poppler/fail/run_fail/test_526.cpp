// TEST_ID: 526
// File: gfx_patch_mesh_shading_is_parameterized_test.cpp

#include <gtest/gtest.h>

#include <cstring>
#include <memory>
#include <utility>
#include <vector>

// Poppler headers
#include "poppler/GfxState.h"
#include "poppler/Function.h"

namespace {

class GfxPatchMeshShadingTest_526 : public ::testing::Test {
protected:
  // Helper: create a minimal patch buffer that is safe to pass by pointer.
  // We intentionally do not assume any semantic meaning of patch fields.
  static std::vector<GfxPatch> MakePatches(int n) {
    std::vector<GfxPatch> patches(static_cast<size_t>(n));
    // Zero-init to avoid uninitialized bytes being observed by any implementation.
    std::memset(patches.data(), 0, sizeof(GfxPatch) * patches.size());
    return patches;
  }

  // Helper: create a funcs vector with N entries, each nullptr.
  // This avoids needing to construct a concrete Function while still allowing
  // observable behavior through the public interface.
  static std::vector<std::unique_ptr<Function>> MakeNullFuncs(int n) {
    std::vector<std::unique_ptr<Function>> funcs;
    funcs.resize(static_cast<size_t>(n)); // default-initialized unique_ptr => nullptr
    return funcs;
  }
};

TEST_F(GfxPatchMeshShadingTest_526, IsParameterizedReturnsFalseWhenFuncsEmpty_526) {
  auto patches = MakePatches(1);

  std::vector<std::unique_ptr<Function>> funcs; // empty
  GfxPatchMeshShading shading(/*typeA=*/0, patches.data(), /*nPatchesA=*/1, std::move(funcs));

  EXPECT_FALSE(shading.isParameterized());
}

TEST_F(GfxPatchMeshShadingTest_526, IsParameterizedReturnsTrueWhenFuncsVectorIsNonEmpty_526) {
  auto patches = MakePatches(1);

  auto funcs = MakeNullFuncs(1); // non-empty, contains nullptr
  GfxPatchMeshShading shading(/*typeA=*/0, patches.data(), /*nPatchesA=*/1, std::move(funcs));

  EXPECT_TRUE(shading.isParameterized());
}

TEST_F(GfxPatchMeshShadingTest_526, IsParameterizedRemainsStableAcrossMultipleCalls_526) {
  auto patches = MakePatches(1);

  auto funcs = MakeNullFuncs(1);
  GfxPatchMeshShading shading(/*typeA=*/0, patches.data(), /*nPatchesA=*/1, std::move(funcs));

  const bool first = shading.isParameterized();
  const bool second = shading.isParameterized();
  const bool third = shading.isParameterized();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(GfxPatchMeshShadingTest_526, CopyConstructorPreservesIsParameterizedFalse_526) {
  auto patches = MakePatches(1);

  std::vector<std::unique_ptr<Function>> funcs; // empty
  GfxPatchMeshShading original(/*typeA=*/0, patches.data(), /*nPatchesA=*/1, std::move(funcs));
  ASSERT_FALSE(original.isParameterized());

  GfxPatchMeshShading copy(&original);
  EXPECT_FALSE(copy.isParameterized());
}

TEST_F(GfxPatchMeshShadingTest_526, CopyConstructorPreservesIsParameterizedTrue_526) {
  auto patches = MakePatches(1);

  auto funcs = MakeNullFuncs(1);
  GfxPatchMeshShading original(/*typeA=*/0, patches.data(), /*nPatchesA=*/1, std::move(funcs));
  ASSERT_TRUE(original.isParameterized());

  GfxPatchMeshShading copy(&original);
  EXPECT_TRUE(copy.isParameterized());
}

} // namespace