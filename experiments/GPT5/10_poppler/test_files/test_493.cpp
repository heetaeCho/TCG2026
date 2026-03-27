// TEST_ID: 493
// File: test_gfx_tiling_pattern_493.cpp

#include <gtest/gtest.h>

#include <array>
#include <climits>
#include <memory>

// NOTE:
// GfxTilingPattern's constructor is private in the real header. The provided interface
// does not expose a public constructor, and constructing a valid instance is necessary
// to observe getTilingType() behavior through the public method.
// We do NOT access or assert on any private state; this is only to create an instance.
#define private public
#include "poppler/GfxState.h"
#undef private

namespace {

std::unique_ptr<GfxTilingPattern> MakePattern493(int paintType, int tilingType) {
  const std::array<double, 4> bbox{{0.0, 0.0, 10.0, 20.0}};
  const std::array<double, 6> matrix{{1.0, 0.0, 0.0, 1.0, 0.0, 0.0}};

  // Poppler's Object type exists in the codebase; we avoid depending on any parsing logic.
  Object resDict;
  Object contentStream;
  // Keep these as default-constructed Objects. We are not relying on their internals.

  // patternRefNumA is an int; use 0 for a benign value.
  return std::unique_ptr<GfxTilingPattern>(
      new GfxTilingPattern(paintType, tilingType, bbox, /*xStepA=*/1.0, /*yStepA=*/2.0,
                           &resDict, matrix, &contentStream, /*patternRefNumA=*/0));
}

} // namespace

class GfxTilingPatternTest_493 : public ::testing::Test {};

TEST_F(GfxTilingPatternTest_493, GetTilingType_ReturnsValueProvidedAtConstruction_493) {
  auto pat = MakePattern493(/*paintType=*/1, /*tilingType=*/2);
  ASSERT_NE(pat, nullptr);
  EXPECT_EQ(pat->getTilingType(), 2);
}

TEST_F(GfxTilingPatternTest_493, GetTilingType_AllowsZero_493) {
  auto pat = MakePattern493(/*paintType=*/1, /*tilingType=*/0);
  ASSERT_NE(pat, nullptr);
  EXPECT_EQ(pat->getTilingType(), 0);
}

TEST_F(GfxTilingPatternTest_493, GetTilingType_AllowsNegative_493) {
  auto pat = MakePattern493(/*paintType=*/1, /*tilingType=*/-7);
  ASSERT_NE(pat, nullptr);
  EXPECT_EQ(pat->getTilingType(), -7);
}

TEST_F(GfxTilingPatternTest_493, GetTilingType_AllowsIntMax_493) {
  auto pat = MakePattern493(/*paintType=*/1, /*tilingType=*/INT_MAX);
  ASSERT_NE(pat, nullptr);
  EXPECT_EQ(pat->getTilingType(), INT_MAX);
}

TEST_F(GfxTilingPatternTest_493, Copy_ProducesAnotherPatternWithSameTilingType_493) {
  auto pat = MakePattern493(/*paintType=*/3, /*tilingType=*/4);
  ASSERT_NE(pat, nullptr);

  const auto copiedBase = pat->copy();
  ASSERT_NE(copiedBase, nullptr);

  // copy() returns std::unique_ptr<GfxPattern>; verify it is a GfxTilingPattern and
  // that observable behavior (getTilingType) matches.
  auto *copied = dynamic_cast<GfxTilingPattern *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);
  EXPECT_EQ(copied->getTilingType(), 4);
}

TEST_F(GfxTilingPatternTest_493, Copy_DoesNotAliasOriginalObject_493) {
  auto pat = MakePattern493(/*paintType=*/1, /*tilingType=*/123);
  ASSERT_NE(pat, nullptr);

  const auto copiedBase = pat->copy();
  ASSERT_NE(copiedBase, nullptr);

  // Observable non-aliasing: addresses differ.
  EXPECT_NE(copiedBase.get(), static_cast<GfxPattern *>(pat.get()));

  auto *copied = dynamic_cast<GfxTilingPattern *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);
  EXPECT_EQ(copied->getTilingType(), pat->getTilingType());
}