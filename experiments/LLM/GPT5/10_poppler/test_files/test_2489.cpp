// poppler-page-transition-new-test_2489.cc
//
// Unit tests for:
//   PopplerPageTransition *poppler_page_transition_new(void)
//
// Constraints honored:
// - Treat implementation as black-box (only test observable behavior).
// - No private/internal state access.
// - Boundary/error cases only if observable via public interface.
// - TEST_ID suffix on every test name.

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
// Forward-declare the C API under test.
// The real declaration should be provided by the production header in your build.
// If your build exposes a different header, replace this with #include "poppler.h" or similar.
typedef struct _PopplerPageTransition PopplerPageTransition;
PopplerPageTransition *poppler_page_transition_new(void);
}  // extern "C"

namespace {

// A tiny RAII helper to ensure we always free what we allocate.
struct TransitionDeleter {
  void operator()(PopplerPageTransition *p) const { g_free(p); }
};

}  // namespace

// ------------------------------
// Test Fixture
// ------------------------------
class PopplerPageTransitionNewTest_2489 : public ::testing::Test {};

// ------------------------------
// Tests
// ------------------------------

TEST_F(PopplerPageTransitionNewTest_2489, ReturnsNonNullPointer_2489) {
  PopplerPageTransition *t = poppler_page_transition_new();
  ASSERT_NE(t, nullptr);

  g_free(t);
}

TEST_F(PopplerPageTransitionNewTest_2489, ReturnsDistinctPointersOnMultipleCalls_2489) {
  PopplerPageTransition *a = poppler_page_transition_new();
  PopplerPageTransition *b = poppler_page_transition_new();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a, b) << "Each call should allocate a distinct object instance.";

  g_free(a);
  g_free(b);
}

TEST_F(PopplerPageTransitionNewTest_2489, CanBeFreedWithGFree_2489) {
  PopplerPageTransition *t = poppler_page_transition_new();
  ASSERT_NE(t, nullptr);

  // Observable behavior: the returned allocation is compatible with g_free.
  // We can't assert on memory internals; the test passes if it doesn't crash.
  g_free(t);
}

TEST_F(PopplerPageTransitionNewTest_2489, StressManyAllocationsAndFrees_2489) {
  // Boundary-ish: exercise repeated allocations/frees to catch obvious issues.
  // No assumptions about internal fields; just verify allocation works repeatedly.
  constexpr int kCount = 1024;

  GPtrArray *arr = g_ptr_array_new_full(kCount, nullptr);
  ASSERT_NE(arr, nullptr);

  for (int i = 0; i < kCount; ++i) {
    PopplerPageTransition *t = poppler_page_transition_new();
    ASSERT_NE(t, nullptr);
    g_ptr_array_add(arr, t);
  }

  // Free them all (observable: should not crash).
  for (guint i = 0; i < arr->len; ++i) {
    g_free(g_ptr_array_index(arr, i));
  }
  g_ptr_array_free(arr, TRUE);
}

TEST_F(PopplerPageTransitionNewTest_2489, MultipleCallsWithinSingleScopeNoInterference_2489) {
  // Another normal-operation check: holding multiple instances concurrently.
  PopplerPageTransition *t1 = poppler_page_transition_new();
  PopplerPageTransition *t2 = poppler_page_transition_new();
  PopplerPageTransition *t3 = poppler_page_transition_new();

  ASSERT_NE(t1, nullptr);
  ASSERT_NE(t2, nullptr);
  ASSERT_NE(t3, nullptr);

  EXPECT_NE(t1, t2);
  EXPECT_NE(t1, t3);
  EXPECT_NE(t2, t3);

  g_free(t1);
  g_free(t2);
  g_free(t3);
}