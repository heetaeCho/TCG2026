// File: poppler-link-mapping-copy-test_2484.cc
#include <gtest/gtest.h>

#include <glib.h>

// Poppler GLib headers (available in the codebase).
#include "poppler.h"
#include "poppler-page.h"

extern "C" {
PopplerLinkMapping *poppler_link_mapping_copy(PopplerLinkMapping *mapping);
}

namespace {

class PopplerLinkMappingCopyTest_2484 : public ::testing::Test {
protected:
  void TearDown() override {
    // Ensure GLib slice allocator is in a consistent state between tests.
    // (No-op if not enabled; safe to call.)
    g_slice_debug_tree_statistics();
  }
};

TEST_F(PopplerLinkMappingCopyTest_2484, CopiesAreaAndNullAction_2484) {
  PopplerLinkMapping *mapping = g_new0(PopplerLinkMapping, 1);
  ASSERT_NE(mapping, nullptr);

  mapping->area.x1 = 1.25;
  mapping->area.y1 = -2.5;
  mapping->area.x2 = 300.0;
  mapping->area.y2 = 400.5;
  mapping->action = nullptr;

  PopplerLinkMapping *copy = poppler_link_mapping_copy(mapping);
  ASSERT_NE(copy, nullptr);

  // The returned mapping should be a distinct object.
  EXPECT_NE(copy, mapping);

  // Observable behavior: area is copied.
  EXPECT_DOUBLE_EQ(copy->area.x1, mapping->area.x1);
  EXPECT_DOUBLE_EQ(copy->area.y1, mapping->area.y1);
  EXPECT_DOUBLE_EQ(copy->area.x2, mapping->area.x2);
  EXPECT_DOUBLE_EQ(copy->area.y2, mapping->area.y2);

  // Observable behavior: null action remains null.
  EXPECT_EQ(copy->action, nullptr);

  g_free(copy);
  g_free(mapping);
}

TEST_F(PopplerLinkMappingCopyTest_2484, CopyIsIndependentFromSourceAfterCopy_2484) {
  PopplerLinkMapping *mapping = g_new0(PopplerLinkMapping, 1);
  ASSERT_NE(mapping, nullptr);

  mapping->area.x1 = 10.0;
  mapping->area.y1 = 20.0;
  mapping->area.x2 = 30.0;
  mapping->area.y2 = 40.0;
  mapping->action = nullptr;

  PopplerLinkMapping *copy = poppler_link_mapping_copy(mapping);
  ASSERT_NE(copy, nullptr);

  // Mutate the source after copy; the copy should not change (separate allocation).
  mapping->area.x1 = -999.0;
  mapping->area.y2 = 999.0;

  EXPECT_DOUBLE_EQ(copy->area.x1, 10.0);
  EXPECT_DOUBLE_EQ(copy->area.y1, 20.0);
  EXPECT_DOUBLE_EQ(copy->area.x2, 30.0);
  EXPECT_DOUBLE_EQ(copy->area.y2, 40.0);
  EXPECT_EQ(copy->action, nullptr);

  g_free(copy);
  g_free(mapping);
}

TEST_F(PopplerLinkMappingCopyTest_2484, HandlesBoundaryRectangleValues_2484) {
  PopplerLinkMapping *mapping = g_new0(PopplerLinkMapping, 1);
  ASSERT_NE(mapping, nullptr);

  // Boundary-ish values: zeros, negatives, and inverted coordinates.
  mapping->area.x1 = 0.0;
  mapping->area.y1 = 0.0;
  mapping->area.x2 = -0.0;     // still 0.0, but keep as written
  mapping->area.y2 = -1234.0;  // negative
  mapping->action = nullptr;

  PopplerLinkMapping *copy = poppler_link_mapping_copy(mapping);
  ASSERT_NE(copy, nullptr);

  EXPECT_NE(copy, mapping);
  EXPECT_DOUBLE_EQ(copy->area.x1, mapping->area.x1);
  EXPECT_DOUBLE_EQ(copy->area.y1, mapping->area.y1);
  EXPECT_DOUBLE_EQ(copy->area.x2, mapping->area.x2);
  EXPECT_DOUBLE_EQ(copy->area.y2, mapping->area.y2);
  EXPECT_EQ(copy->action, nullptr);

  g_free(copy);
  g_free(mapping);
}

TEST_F(PopplerLinkMappingCopyTest_2484, NullInputDies_2484) {
  // The implementation dereferences `mapping` unconditionally; passing nullptr
  // is an invalid usage and should crash (observable as process death).
  ASSERT_DEATH(
      {
        volatile PopplerLinkMapping *result = poppler_link_mapping_copy(nullptr);
        (void)result;
      },
      ".*");
}

}  // namespace