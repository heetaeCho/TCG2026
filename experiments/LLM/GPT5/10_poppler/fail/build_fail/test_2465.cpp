// File: poppler-rectangle-copy-test_2465.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-page.h"

// The function under test is implemented in poppler-page.cc and linked from the codebase.
// Declare it here (C linkage to match the GLib/Poppler C API style).
extern "C" PopplerRectangle* poppler_rectangle_copy(PopplerRectangle* rectangle);

namespace {

class PopplerRectangleCopyTest_2465 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure GLib is initialized enough for g_test_expect_message usage.
    // (Safe to call multiple times.)
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

TEST_F(PopplerRectangleCopyTest_2465, NullInputReturnsNullAndLogsCritical_2465) {
  // g_return_val_if_fail() reports via GLib logging (typically domain "GLib") at CRITICAL level.
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*rectangle*!=*NULL*failed*");

  PopplerRectangle* out = poppler_rectangle_copy(nullptr);
  EXPECT_EQ(out, nullptr);

  g_test_assert_expected_messages();
}

TEST_F(PopplerRectangleCopyTest_2465, CopiesPublicFieldsAndReturnsDistinctPointer_2465) {
  // We must not rely on internal/private layout (PopplerRectangleExtended). To avoid
  // under-allocation if the implementation copies a larger "extended" struct, allocate a
  // generously sized buffer and treat its beginning as PopplerRectangle.
  constexpr gsize kBigEnough = 1u << 20;  // 1 MiB, far larger than any plausible rectangle struct.
  void* backing = g_malloc0(kBigEnough);
  ASSERT_NE(backing, nullptr);

  auto* in = reinterpret_cast<PopplerRectangle*>(backing);
  in->x2 = 123;
  in->y2 = 456;

  PopplerRectangle* out = poppler_rectangle_copy(in);
  ASSERT_NE(out, nullptr);

  // Should be a different allocation (a copy).
  EXPECT_NE(out, in);

  // Observable public fields should match.
  EXPECT_EQ(out->x2, in->x2);
  EXPECT_EQ(out->y2, in->y2);

  // Mutating the input should not affect the returned copy (deep copy behavior observable via fields).
  in->x2 = 777;
  in->y2 = 888;
  EXPECT_EQ(out->x2, 123);
  EXPECT_EQ(out->y2, 456);

  // Free only what we allocated (input backing). The returned object is allocated via g_slice_dup()
  // with an internal type size, which we cannot safely free here without relying on internal details.
  g_free(backing);
}

TEST_F(PopplerRectangleCopyTest_2465, CopiesExtremeValues_2465) {
  constexpr gsize kBigEnough = 1u << 20;
  void* backing = g_malloc0(kBigEnough);
  ASSERT_NE(backing, nullptr);

  auto* in = reinterpret_cast<PopplerRectangle*>(backing);
  in->x2 = G_MININT;
  in->y2 = G_MAXINT;

  PopplerRectangle* out = poppler_rectangle_copy(in);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->x2, G_MININT);
  EXPECT_EQ(out->y2, G_MAXINT);

  g_free(backing);
}

}  // namespace