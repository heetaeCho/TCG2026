// File: poppler-image-mapping-new-test-2486.cc
//
// Unit tests for:
//   PopplerImageMapping *poppler_image_mapping_new(void)
//
// Constraints respected:
// - Treat implementation as black box (no internal logic assumptions beyond public/observable behavior)
// - No private/internal state access
// - Boundary + error-ish cases (as observable)
// - No mocks needed (no external collaborators)
//
// Note: This test assumes GLib is available (g_slice_new0, g_slice_free).
// If your build uses a different allocator or provides a corresponding free API,
// adjust the deallocation accordingly.

#include <gtest/gtest.h>

#include <glib.h>

// Forward-declare the struct and function under test.
// In your real build, you likely include the proper Poppler GLib header instead
// (e.g., <poppler.h> or a local header that declares PopplerImageMapping).
typedef struct _PopplerImageMapping PopplerImageMapping;

extern "C" {
PopplerImageMapping *poppler_image_mapping_new(void);
}

// Helper: free using g_slice_free with the known type name.
// If Poppler provides a dedicated free function (e.g., poppler_image_mapping_free),
// prefer that and replace this helper.
static void FreePopplerImageMapping(PopplerImageMapping *p) {
  if (!p) return;
  g_slice_free(PopplerImageMapping, p);
}

class PopplerImageMappingNewTest_2486 : public ::testing::Test {
 protected:
  void SetUp() override {
    // No global setup required; GLib slice allocator is ready by default.
  }
};

// Normal operation: returns a valid pointer.
TEST_F(PopplerImageMappingNewTest_2486, ReturnsNonNullPointer_2486) {
  PopplerImageMapping *mapping = poppler_image_mapping_new();
  ASSERT_NE(mapping, nullptr);

  FreePopplerImageMapping(mapping);
}

// Normal operation / repeatability: multiple calls return distinct allocations.
TEST_F(PopplerImageMappingNewTest_2486, MultipleCallsReturnDistinctPointers_2486) {
  PopplerImageMapping *a = poppler_image_mapping_new();
  PopplerImageMapping *b = poppler_image_mapping_new();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a, b);

  FreePopplerImageMapping(a);
  FreePopplerImageMapping(b);
}

// Boundary-ish: stress a batch of allocations to ensure the API behaves consistently.
// We avoid asserting performance characteristics; only check non-null and uniqueness
// among a small sample.
TEST_F(PopplerImageMappingNewTest_2486, BatchAllocationsAreNonNullAndMostlyUnique_2486) {
  constexpr int kCount = 128;
  PopplerImageMapping *ptrs[kCount] = {};

  for (int i = 0; i < kCount; ++i) {
    ptrs[i] = poppler_image_mapping_new();
    ASSERT_NE(ptrs[i], nullptr) << "Allocation failed at index " << i;
  }

  // Verify no two pointers in this batch are the same.
  // (In a correct allocator, these should all be distinct live allocations.)
  for (int i = 0; i < kCount; ++i) {
    for (int j = i + 1; j < kCount; ++j) {
      EXPECT_NE(ptrs[i], ptrs[j]) << "Duplicate pointer at indices " << i << " and " << j;
    }
  }

  for (int i = 0; i < kCount; ++i) {
    FreePopplerImageMapping(ptrs[i]);
  }
}

// Error/exceptional cases:
// There is no input and no observable error channel. The only observable failure
// would be returning nullptr. This test intentionally does not *force* OOM,
// but documents the expected behavior if allocation succeeds.
TEST_F(PopplerImageMappingNewTest_2486, DoesNotReturnNullUnderNormalConditions_2486) {
  // Under normal test environments, allocation should succeed.
  PopplerImageMapping *mapping = poppler_image_mapping_new();
  EXPECT_NE(mapping, nullptr);

  FreePopplerImageMapping(mapping);
}