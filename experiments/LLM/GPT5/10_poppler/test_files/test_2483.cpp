// poppler-link-mapping-new-test_2483.cc
//
// Unit tests for poppler_link_mapping_new()
// Interface-under-test (black box):
//   PopplerLinkMapping *poppler_link_mapping_new(void);
//
// Constraints honored:
// - No re-implementation or inference of internal logic beyond observable interface.
// - No access to private/internal state.
// - Tests focus on observable behavior: non-null return, independence across calls,
//   and safe cleanup via GLib slice free for the returned pointer type.

#include <gtest/gtest.h>

#include <glib.h>

// Include the public header that declares PopplerLinkMapping and poppler_link_mapping_new.
// Adjust include path if your build uses a different layout.
#include <poppler.h>

namespace {

class PopplerLinkMappingNewTest_2483 : public ::testing::Test {
protected:
  void TearDown() override {
    // Ensure we don't leave GLib in a bad state (no global teardown required here).
  }
};

TEST_F(PopplerLinkMappingNewTest_2483, ReturnsNonNullPointer_2483) {
  PopplerLinkMapping* mapping = poppler_link_mapping_new();
  ASSERT_NE(mapping, nullptr);

  // Clean up using the matching GLib slice free for the allocation type.
  g_slice_free(PopplerLinkMapping, mapping);
}

TEST_F(PopplerLinkMappingNewTest_2483, MultipleCallsReturnDistinctPointers_2483) {
  PopplerLinkMapping* a = poppler_link_mapping_new();
  PopplerLinkMapping* b = poppler_link_mapping_new();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  // Observable behavior: two allocations should not alias the same memory.
  EXPECT_NE(a, b);

  g_slice_free(PopplerLinkMapping, a);
  g_slice_free(PopplerLinkMapping, b);
}

TEST_F(PopplerLinkMappingNewTest_2483, ManyAllocationsAreAllNonNullAndDistinct_2483) {
  // Boundary-ish: allocate a modest batch to ensure stability under repeated calls.
  // Keep small to avoid stressing allocators in unit test environments.
  constexpr int kCount = 64;

  PopplerLinkMapping* ptrs[kCount] = {};
  for (int i = 0; i < kCount; ++i) {
    ptrs[i] = poppler_link_mapping_new();
    ASSERT_NE(ptrs[i], nullptr) << "Allocation failed at index " << i;
  }

  // Check uniqueness (no duplicates).
  for (int i = 0; i < kCount; ++i) {
    for (int j = i + 1; j < kCount; ++j) {
      EXPECT_NE(ptrs[i], ptrs[j]) << "Duplicate pointer at indices " << i << " and " << j;
    }
  }

  for (int i = 0; i < kCount; ++i) {
    g_slice_free(PopplerLinkMapping, ptrs[i]);
  }
}

TEST_F(PopplerLinkMappingNewTest_2483, FreeingReturnedPointerIsSafe_2483) {
  // Exceptional/error cases are not observable via the interface (no error return, no params).
  // The best we can do is validate that the allocation is compatible with slice free
  // and does not crash for a valid pointer.
  PopplerLinkMapping* mapping = poppler_link_mapping_new();
  ASSERT_NE(mapping, nullptr);

  // Should not crash.
  g_slice_free(PopplerLinkMapping, mapping);
}

}  // namespace