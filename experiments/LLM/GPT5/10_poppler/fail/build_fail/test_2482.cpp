// poppler-color-free-test-2482.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-page.h"  // PopplerColor

extern "C" {
// Function under test (implemented in poppler-page.cc in the real codebase)
void poppler_color_free(PopplerColor *color);
}

namespace {

class PopplerColorFreeTest_2482 : public ::testing::Test {};

}  // namespace

TEST_F(PopplerColorFreeTest_2482, FreesNullPointerNoCrash_2482) {
  // g_free(NULL) is defined by GLib to be a no-op.
  ASSERT_NO_FATAL_FAILURE(poppler_color_free(nullptr));
}

TEST_F(PopplerColorFreeTest_2482, FreesHeapAllocatedColorNoCrash_2482) {
  PopplerColor *c = static_cast<PopplerColor *>(g_malloc0(sizeof(PopplerColor)));
  ASSERT_NE(c, nullptr);

  // Touch fields to ensure the struct is usable before freeing.
  c->red = 0;
  c->green = 65535;
  c->blue = 12345;

  ASSERT_NO_FATAL_FAILURE(poppler_color_free(c));

  // Don't dereference `c` after this point (freed).
}

TEST_F(PopplerColorFreeTest_2482, FreesHeapAllocatedColorWithNonZeroPatternNoCrash_2482) {
  PopplerColor *c = static_cast<PopplerColor *>(g_malloc(sizeof(PopplerColor)));
  ASSERT_NE(c, nullptr);

  // Fill with non-zero values to cover "non-zero / boundary-ish" inputs.
  c->red = -1;
  c->green = 0;
  c->blue = 2147483647;

  ASSERT_NO_FATAL_FAILURE(poppler_color_free(c));
}

TEST_F(PopplerColorFreeTest_2482, MultipleDistinctAllocationsCanBeFreedIndependently_2482) {
  PopplerColor *a = static_cast<PopplerColor *>(g_malloc0(sizeof(PopplerColor)));
  PopplerColor *b = static_cast<PopplerColor *>(g_malloc0(sizeof(PopplerColor)));
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  ASSERT_NE(a, b);

  a->red = 1;
  b->red = 2;

  ASSERT_NO_FATAL_FAILURE(poppler_color_free(a));
  ASSERT_NO_FATAL_FAILURE(poppler_color_free(b));
}

TEST_F(PopplerColorFreeTest_2482, FreesPointerFromGNew0NoCrash_2482) {
  // Alternative GLib allocation path.
  PopplerColor *c = g_new0(PopplerColor, 1);
  ASSERT_NE(c, nullptr);

  c->red = 100;
  c->green = 200;
  c->blue = 300;

  ASSERT_NO_FATAL_FAILURE(poppler_color_free(c));
}