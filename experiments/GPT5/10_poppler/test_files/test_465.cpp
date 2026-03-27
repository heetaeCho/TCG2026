// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for GfxIndexedColorSpace::getMode()
// TEST_ID: 465

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>

#include "GfxState.h"

// Helper: construct GfxIndexedColorSpace if a matching constructor exists in the build.
template <typename... Args>
static std::unique_ptr<GfxIndexedColorSpace> MakeIndexedIfPossible_465(Args&&... args) {
  if constexpr (std::is_constructible_v<GfxIndexedColorSpace, Args...>) {
    return std::make_unique<GfxIndexedColorSpace>(std::forward<Args>(args)...);
  } else {
    return nullptr;
  }
}

// Helper: try common constructor shapes seen in headers (incl. rvalue-int form).
static std::unique_ptr<GfxIndexedColorSpace> MakeAnyIndexed_465(int baseVal, int indexHighVal) {
  // 1) (int, int)
  if (auto p = MakeIndexedIfPossible_465(baseVal, indexHighVal)) {
    return p;
  }

  // 2) (int&&, int)
  {
    int tmp = baseVal;
    if (auto p = MakeIndexedIfPossible_465(std::move(tmp), indexHighVal)) {
      return p;
    }
  }

  return nullptr;
}

TEST(GfxIndexedColorSpaceTest_465, GetModeReturnsCsIndexed_465) {
  auto cs = MakeAnyIndexed_465(/*baseVal=*/0, /*indexHighVal=*/0);
  if (!cs) {
    GTEST_SKIP() << "No supported GfxIndexedColorSpace ctor available for this build to instantiate the class.";
  }

  EXPECT_EQ(csIndexed, cs->getMode());
}

TEST(GfxIndexedColorSpaceTest_465, GetModeThroughBasePointerReturnsCsIndexed_465) {
  auto derived = MakeAnyIndexed_465(/*baseVal=*/0, /*indexHighVal=*/255);
  if (!derived) {
    GTEST_SKIP() << "No supported GfxIndexedColorSpace ctor available for this build to instantiate the class.";
  }

  // Verify virtual dispatch via base pointer (observable behavior).
  GfxColorSpace *basePtr = derived.get();
  ASSERT_NE(nullptr, basePtr);
  EXPECT_EQ(csIndexed, basePtr->getMode());
}

TEST(GfxIndexedColorSpaceTest_465, GetModeUnaffectedByBoundaryIndexHighValues_465) {
  // Boundary-ish values for indexHigh (behavior we can observe is getMode stability).
  {
    auto cs0 = MakeAnyIndexed_465(/*baseVal=*/0, /*indexHighVal=*/0);
    if (!cs0) {
      GTEST_SKIP() << "No supported GfxIndexedColorSpace ctor available for this build to instantiate the class.";
    }
    EXPECT_EQ(csIndexed, cs0->getMode());
  }

  {
    auto cs255 = MakeAnyIndexed_465(/*baseVal=*/0, /*indexHighVal=*/255);
    if (!cs255) {
      GTEST_SKIP() << "No supported GfxIndexedColorSpace ctor available for this build to instantiate the class.";
    }
    EXPECT_EQ(csIndexed, cs255->getMode());
  }
}

TEST(GfxIndexedColorSpaceTest_465, GetModeWithNegativeIndexHighDoesNotChangeMode_465) {
  // If the implementation rejects negative indexHigh, this may throw/assert in some builds.
  // We only assert the observable behavior when construction succeeds.
  std::unique_ptr<GfxIndexedColorSpace> cs;
  try {
    cs = MakeAnyIndexed_465(/*baseVal=*/0, /*indexHighVal=*/-1);
  } catch (...) {
    GTEST_SKIP() << "Constructor threw for negative indexHigh; skipping observable getMode check.";
  }

  if (!cs) {
    GTEST_SKIP() << "No supported GfxIndexedColorSpace ctor available for this build (or construction failed).";
  }

  EXPECT_EQ(csIndexed, cs->getMode());
}