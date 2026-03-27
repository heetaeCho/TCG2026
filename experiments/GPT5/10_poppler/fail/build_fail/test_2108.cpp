// poppler-annot-callout-line-free-ut-2108.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
// Include the public header for the struct definition.
#include "poppler-annot.h"

// Function under test (implemented in poppler-annot.cc in the codebase).
void poppler_annot_callout_line_free(PopplerAnnotCalloutLine *callout);
}

namespace {

class PopplerAnnotCalloutLineFreeTest_2108 : public ::testing::Test {};

TEST_F(PopplerAnnotCalloutLineFreeTest_2108, FreeNullPointerDoesNotCrash_2108) {
  // g_free(NULL) is defined to be safe; this should not crash.
  EXPECT_NO_THROW(poppler_annot_callout_line_free(nullptr));
}

TEST_F(PopplerAnnotCalloutLineFreeTest_2108, FreeValidPointerDoesNotCrash_2108) {
  // Allocate with g_malloc0 so it matches the expected allocator.
  auto *callout = static_cast<PopplerAnnotCalloutLine *>(g_malloc0(sizeof(PopplerAnnotCalloutLine)));
  ASSERT_NE(callout, nullptr);

  // Touch fields to ensure the memory is writable (observable via no crash).
  callout->multiline = 1;
  callout->x3 = 123;
  callout->y3 = -456;

  EXPECT_NO_THROW(poppler_annot_callout_line_free(callout));
}

TEST_F(PopplerAnnotCalloutLineFreeTest_2108, FreePointerWithDifferentFieldValuesDoesNotCrash_2108) {
  // Boundary-ish values for the public fields (still just ensuring free is safe).
  auto *callout = static_cast<PopplerAnnotCalloutLine *>(g_malloc0(sizeof(PopplerAnnotCalloutLine)));
  ASSERT_NE(callout, nullptr);

  callout->multiline = 0;
  callout->x3 = G_MAXINT;
  callout->y3 = G_MININT;

  EXPECT_NO_THROW(poppler_annot_callout_line_free(callout));
}

}  // namespace