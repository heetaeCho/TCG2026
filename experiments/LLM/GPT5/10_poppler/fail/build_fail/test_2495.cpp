// poppler-annot-mapping-new-test_2495.cc
//
// Unit tests for:
//   PopplerAnnotMapping *poppler_annot_mapping_new(void)
//
// Partial code under test (black box):
//   PopplerAnnotMapping *poppler_annot_mapping_new(void) { return g_slice_new0(PopplerAnnotMapping); }

#include <gtest/gtest.h>

#include <glib.h>

// Include the Poppler GLib public header(s). Adjust include path if your build uses a different one.
#include <poppler.h>

namespace {

class PopplerAnnotMappingNewTest_2495 : public ::testing::Test {
protected:
  void TearDown() override {
    // Ensure GLib slice allocator is in a consistent state across tests.
    // (No explicit teardown needed; each test frees what it allocates.)
  }
};

TEST_F(PopplerAnnotMappingNewTest_2495, ReturnsNonNull_2495) {
  PopplerAnnotMapping* mapping = poppler_annot_mapping_new();
  ASSERT_NE(mapping, nullptr);

  // Free with g_slice_free since creation uses g_slice_new0.
  g_slice_free(PopplerAnnotMapping, mapping);
}

TEST_F(PopplerAnnotMappingNewTest_2495, MultipleAllocationsReturnDistinctPointers_2495) {
  PopplerAnnotMapping* a = poppler_annot_mapping_new();
  PopplerAnnotMapping* b = poppler_annot_mapping_new();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  // Observable behavior: independent allocations should not alias.
  EXPECT_NE(a, b);

  g_slice_free(PopplerAnnotMapping, a);
  g_slice_free(PopplerAnnotMapping, b);
}

TEST_F(PopplerAnnotMappingNewTest_2495, CanBeFreedSafely_2495) {
  PopplerAnnotMapping* mapping = poppler_annot_mapping_new();
  ASSERT_NE(mapping, nullptr);

  // Boundary-ish: immediate free without touching fields should be safe.
  g_slice_free(PopplerAnnotMapping, mapping);
}

TEST_F(PopplerAnnotMappingNewTest_2495, RepeatedCreateAndFreeDoesNotCrash_2495) {
  // Boundary: exercise repeated allocation/free to catch allocator misuse.
  for (int i = 0; i < 1000; ++i) {
    PopplerAnnotMapping* mapping = poppler_annot_mapping_new();
    ASSERT_NE(mapping, nullptr);
    g_slice_free(PopplerAnnotMapping, mapping);
  }
}

}  // namespace