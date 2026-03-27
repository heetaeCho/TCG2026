// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for poppler_rectangle_new()
// File under test: ./TestProjects/poppler/glib/poppler-page.cc
//
// Constraints followed:
// - Treat implementation as black box (no re-implementation of internal logic).
// - Test only observable behavior through public interface.
// - Include normal + boundary + error-ish cases that are observable.
// - Include TEST_ID in every test name.

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include <poppler.h>
}

namespace {

// For simple allocation-returning APIs, observable behavior is mainly:
//  - returns a pointer (often non-null under normal conditions)
//  - returned object can be freed by the library's expected free function
//  - repeated calls return distinct allocations
//
// We intentionally do NOT inspect internal fields/layout, as that's private ABI.
// We also avoid forcing OOM; not reliably testable in unit tests.

class PopplerRectangleNewTest_2464 : public ::testing::Test {};

}  // namespace

TEST_F(PopplerRectangleNewTest_2464, ReturnsNonNullPointer_2464) {
  PopplerRectangle* rect = poppler_rectangle_new();
  ASSERT_NE(rect, nullptr);

  // Clean up using the public API free function (expected for boxed types).
  // If poppler_rectangle_free() is not available in your build, replace with the
  // appropriate deallocator used in your codebase.
  poppler_rectangle_free(rect);
}

TEST_F(PopplerRectangleNewTest_2464, MultipleCallsReturnDistinctPointers_2464) {
  PopplerRectangle* a = poppler_rectangle_new();
  PopplerRectangle* b = poppler_rectangle_new();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  // Typically, fresh allocations should not alias each other.
  EXPECT_NE(a, b);

  poppler_rectangle_free(a);
  poppler_rectangle_free(b);
}

TEST_F(PopplerRectangleNewTest_2464, CanAllocateAndFreeManyTimes_2464) {
  // Boundary-ish: exercise multiple allocations/frees to catch lifecycle issues.
  constexpr int kIters = 128;

  for (int i = 0; i < kIters; ++i) {
    PopplerRectangle* rect = poppler_rectangle_new();
    ASSERT_NE(rect, nullptr) << "Iteration " << i;
    poppler_rectangle_free(rect);
  }
}

TEST_F(PopplerRectangleNewTest_2464, ReturnedPointerIsStableUntilFreed_2464) {
  PopplerRectangle* rect = poppler_rectangle_new();
  ASSERT_NE(rect, nullptr);

  // "Stability" here is just that the pointer value remains the same while in scope.
  // We do not dereference or inspect internals.
  PopplerRectangle* same = rect;
  EXPECT_EQ(same, rect);

  poppler_rectangle_free(rect);
}