// poppler-page-transition-free-test_2491.cc
#include <glib.h>

#include <gtest/gtest.h>

#include "poppler-page.h"

// Function under test (declared/defined in poppler-page.cc in the real codebase)
extern "C" void poppler_page_transition_free(PopplerPageTransition *transition);

namespace {

class PopplerPageTransitionFreeTest_2491 : public ::testing::Test {};

TEST_F(PopplerPageTransitionFreeTest_2491, FreeNullIsNoop_2491) {
  // g_free(NULL) is defined to be a no-op in GLib.
  EXPECT_NO_THROW(poppler_page_transition_free(nullptr));
}

TEST_F(PopplerPageTransitionFreeTest_2491, FreeValidAllocationSucceeds_2491) {
  // Allocate via GLib allocator to match the expected free function (g_free).
  PopplerPageTransition *t =
      static_cast<PopplerPageTransition *>(g_malloc0(sizeof(PopplerPageTransition)));
  ASSERT_NE(t, nullptr);

  // Fill some fields to ensure it doesn't depend on contents (black-box: just ensure no crash).
  t->scale = 123;
  t->rectangular = 1;
  t->duration_real = 42;

  EXPECT_NO_THROW(poppler_page_transition_free(t));
}

TEST_F(PopplerPageTransitionFreeTest_2491, FreeMultipleDistinctAllocations_2491) {
  PopplerPageTransition *t1 =
      static_cast<PopplerPageTransition *>(g_malloc0(sizeof(PopplerPageTransition)));
  PopplerPageTransition *t2 =
      static_cast<PopplerPageTransition *>(g_malloc0(sizeof(PopplerPageTransition)));
  ASSERT_NE(t1, nullptr);
  ASSERT_NE(t2, nullptr);
  ASSERT_NE(t1, t2);

  EXPECT_NO_THROW(poppler_page_transition_free(t1));
  EXPECT_NO_THROW(poppler_page_transition_free(t2));
}

}  // namespace