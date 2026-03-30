// poppler-color-copy-test-2481.cc
//
// Unit tests for poppler_color_copy().
//
// Constraints respected:
// - Treat implementation as black box (only observable behavior via interface).
// - No private/internal state access.
// - Cover normal, boundary, and observable error/exception-ish cases.
// - No re-implementation of function logic.
//
// NOTE: poppler_color_copy() uses GLib allocation (g_new). These tests assume GLib
// is available in the test environment.

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "poppler-page.h"

// Function under test (defined in poppler-page.cc)
PopplerColor *poppler_color_copy(PopplerColor *color);
}

namespace {

class PopplerColorCopyTest_2481 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Ensure we didn't leave any allocations behind in tests that forgot to free.
    // (No global tracking; each test should free explicitly.)
  }
};

TEST_F(PopplerColorCopyTest_2481, CopiesValuesAndReturnsDistinctObject_2481) {
  PopplerColor src;
  src.red = 10;
  src.green = 20;
  src.blue = 30;

  PopplerColor *dst = poppler_color_copy(&src);
  ASSERT_NE(dst, nullptr);

  // Should be a distinct allocation, not aliasing the source.
  EXPECT_NE(dst, &src);

  // Observable behavior: value copy.
  EXPECT_EQ(dst->red, src.red);
  EXPECT_EQ(dst->green, src.green);
  EXPECT_EQ(dst->blue, src.blue);

  g_free(dst);
}

TEST_F(PopplerColorCopyTest_2481, CopyDoesNotChangeWhenSourceMutatesAfterCopy_2481) {
  PopplerColor src;
  src.red = 1;
  src.green = 2;
  src.blue = 3;

  PopplerColor *dst = poppler_color_copy(&src);
  ASSERT_NE(dst, nullptr);

  // Mutate source after copy; destination should retain original values if it
  // truly copied the struct (observable independence).
  src.red = 111;
  src.green = 222;
  src.blue = 333;

  EXPECT_EQ(dst->red, 1);
  EXPECT_EQ(dst->green, 2);
  EXPECT_EQ(dst->blue, 3);

  g_free(dst);
}

TEST_F(PopplerColorCopyTest_2481, BoundaryValuesAllZeros_2481) {
  PopplerColor src;
  src.red = 0;
  src.green = 0;
  src.blue = 0;

  PopplerColor *dst = poppler_color_copy(&src);
  ASSERT_NE(dst, nullptr);

  EXPECT_EQ(dst->red, 0);
  EXPECT_EQ(dst->green, 0);
  EXPECT_EQ(dst->blue, 0);

  g_free(dst);
}

TEST_F(PopplerColorCopyTest_2481, BoundaryValuesNegativeAndLargeInts_2481) {
  // The interface uses plain int, so we verify it copies whatever bit-pattern
  // is provided, including negatives and large values (no assumptions about
  // clamping, since that's not specified by the interface).
  PopplerColor src;
  src.red = G_MININT;
  src.green = -1;
  src.blue = G_MAXINT;

  PopplerColor *dst = poppler_color_copy(&src);
  ASSERT_NE(dst, nullptr);

  EXPECT_EQ(dst->red, G_MININT);
  EXPECT_EQ(dst->green, -1);
  EXPECT_EQ(dst->blue, G_MAXINT);

  g_free(dst);
}

TEST_F(PopplerColorCopyTest_2481, MultipleCopiesAreIndependentAllocations_2481) {
  PopplerColor src;
  src.red = 7;
  src.green = 8;
  src.blue = 9;

  PopplerColor *a = poppler_color_copy(&src);
  PopplerColor *b = poppler_color_copy(&src);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  EXPECT_NE(a, b);

  EXPECT_EQ(a->red, 7);
  EXPECT_EQ(a->green, 8);
  EXPECT_EQ(a->blue, 9);

  EXPECT_EQ(b->red, 7);
  EXPECT_EQ(b->green, 8);
  EXPECT_EQ(b->blue, 9);

  // Mutate one copy; the other should remain unchanged.
  a->red = 100;
  a->green = 200;
  a->blue = 300;

  EXPECT_EQ(b->red, 7);
  EXPECT_EQ(b->green, 8);
  EXPECT_EQ(b->blue, 9);

  g_free(a);
  g_free(b);
}

// Observable error/exceptional case:
// Passing nullptr is not documented. In C code, a common observable behavior is
// a crash (segfault) due to dereference. We encode this as a death test.
// If the production code later adds a null-check and returns nullptr, this test
// can be updated accordingly.
TEST_F(PopplerColorCopyTest_2481, NullInputDies_2481) {
#if GTEST_HAS_DEATH_TEST
  // Use a broad matcher because exact message/behavior is platform-dependent.
  EXPECT_DEATH(
      {
        PopplerColor *out = poppler_color_copy(nullptr);
        // Prevent "unused variable" warnings in the death-test block.
        (void)out;
      },
      ".*");
#else
  GTEST_SKIP() << "Death tests are not supported in this build configuration.";
#endif
}

}  // namespace