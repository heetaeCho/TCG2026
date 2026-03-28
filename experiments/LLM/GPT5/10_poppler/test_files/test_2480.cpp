// File: ./TestProjects/poppler/glib/poppler-page-color-new-test_2480.cc
//
// Unit tests for poppler_color_new()
// NOTE: We treat the implementation as a black box. We only test observable behavior:
// - Returns a non-null pointer
// - Returned memory appears zero-initialized (since it's an allocator returning a struct pointer)
//
// These tests assume PopplerColor is a GLib-visible struct type (as in Poppler GLib API).
// If PopplerColor's definition changes, update the field checks accordingly.

#include <gtest/gtest.h>

#include <glib.h>

// Include the Poppler GLib headers that declare PopplerColor and poppler_color_new.
// Depending on your build, one of these may be correct.
#include <poppler.h>
// If your project uses a different include path, adjust accordingly, e.g.
// #include "poppler.h"

namespace {

class PopplerColorNewTest_2480 : public ::testing::Test {};

TEST_F(PopplerColorNewTest_2480, ReturnsNonNull_2480) {
  PopplerColor* color = poppler_color_new();
  ASSERT_NE(color, nullptr);

  // Free with GLib allocator counterpart.
  g_free(color);
}

TEST_F(PopplerColorNewTest_2480, ReturnedObjectIsZeroInitialized_2480) {
  PopplerColor* color = poppler_color_new();
  ASSERT_NE(color, nullptr);

  // Observable effect: memory is expected to be zeroed.
  // We avoid inferring internals beyond what can be observed from the public struct fields.
  //
  // PopplerColor in Poppler GLib is typically { guint16 red, green, blue }.
  // If it differs in your version, update these checks to match the public fields.
  EXPECT_EQ(color->red, 0u);
  EXPECT_EQ(color->green, 0u);
  EXPECT_EQ(color->blue, 0u);

  g_free(color);
}

TEST_F(PopplerColorNewTest_2480, MultipleAllocationsReturnDistinctPointers_2480) {
  PopplerColor* a = poppler_color_new();
  PopplerColor* b = poppler_color_new();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  // Boundary-ish / sanity: distinct allocations should not alias.
  EXPECT_NE(a, b);

  g_free(a);
  g_free(b);
}

TEST_F(PopplerColorNewTest_2480, CanFreeWithGFreeWithoutCrashing_2480) {
  PopplerColor* color = poppler_color_new();
  ASSERT_NE(color, nullptr);

  // If allocation used g_new0, g_free should be the correct deallocator.
  // We can't assert "no crash" directly, but the test will fail if it crashes.
  g_free(color);
}

}  // namespace