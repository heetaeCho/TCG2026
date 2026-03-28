// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Unit tests for GfxShadingPattern (Poppler)
// File: gfxshadingpattern_test_500.cc

#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/GfxState.h"

namespace {

class GfxShadingPatternTest_500 : public ::testing::Test {};

// Normal / exceptional: parse() with clearly invalid / null inputs should fail safely (observable via nullptr).
TEST_F(GfxShadingPatternTest_500, ParseWithAllNullInputsReturnsNull_500) {
  // parse(GfxResources *res, Object *patObj, OutputDev *out, GfxState *state, int patternRefNum)
  auto pat = GfxShadingPattern::parse(nullptr, nullptr, nullptr, nullptr, 0);
  EXPECT_EQ(pat.get(), nullptr);
}

// Boundary: patternRefNum negative should also fail safely with null inputs (no crash, returns nullptr).
TEST_F(GfxShadingPatternTest_500, ParseWithNegativePatternRefNumAndNullInputsReturnsNull_500) {
  auto pat = GfxShadingPattern::parse(nullptr, nullptr, nullptr, nullptr, -1);
  EXPECT_EQ(pat.get(), nullptr);
}

// Boundary: large patternRefNum should fail safely with null inputs (no crash, returns nullptr).
TEST_F(GfxShadingPatternTest_500, ParseWithLargePatternRefNumAndNullInputsReturnsNull_500) {
  auto pat = GfxShadingPattern::parse(nullptr, nullptr, nullptr, nullptr, 0x7fffffff);
  EXPECT_EQ(pat.get(), nullptr);
}

// Note:
// getShading() is only safely testable when we can obtain a non-null GfxShadingPattern instance
// through the public interface (e.g., successful parse()), without accessing private constructors/state.
// With only the provided interface fragment and no guaranteed way to construct a valid pattern object
// here, these tests focus on observable error-handling behavior of parse().

} // namespace