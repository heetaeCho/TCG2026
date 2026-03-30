// File: poppler-structure-element-get-column-count-test_2584.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler.h"  // PopplerStructureElement, poppler_structure_element_get_column_count()

namespace {

class PopplerStructureElementGetColumnCountTest_2584 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // GLib log expectation utilities require GLib to be initialized enough for testing.
    // g_test_init() is typically called by GLib's own test runner, but these tests run under gtest.
    // This is safe to call once; if already initialized, GLib will ignore extra init.
    int argc = 0;
    char **argv = nullptr;
    g_test_init(&argc, &argv, nullptr);
  }
};

TEST_F(PopplerStructureElementGetColumnCountTest_2584, NullElementReturnsZeroAndEmitsCritical_2584) {
  // The function uses g_return_val_if_fail(poppler_structure_element_is_grouping(...), 0)
  // so passing NULL should return 0 and emit a critical log message (observable behavior).
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*failed*");

  guint count = poppler_structure_element_get_column_count(nullptr);
  EXPECT_EQ(count, 0u);

  g_test_assert_expected_messages();
}

TEST_F(PopplerStructureElementGetColumnCountTest_2584, NullElementDoesNotCrash_2584) {
  // Boundary / robustness check: calling with NULL should be safe (returns 0).
  // (No log assertion here to keep this test independent of GLib message formatting.)
  EXPECT_EQ(poppler_structure_element_get_column_count(nullptr), 0u);
}

}  // namespace