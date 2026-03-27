// poppler-quadrilateral-new-test-2472.cc
//
// Unit tests for:
//   PopplerQuadrilateral *poppler_quadrilateral_new(void)
//
// Constraints respected:
// - Treat implementation as black box (no internal logic assumptions beyond observable interface)
// - No private/internal state access
// - Focus on observable behavior: returned pointer validity and memory lifecycle
//
// Note: We avoid asserting field values (even though g_slice_new0 suggests zero-init),
// because that would be inferring implementation details beyond the interface.

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
// Forward declaration (kept minimal to match the provided interface).
typedef struct _PopplerQuadrilateral PopplerQuadrilateral;

// Function under test (as provided).
PopplerQuadrilateral *poppler_quadrilateral_new(void);
}

namespace {

class PopplerQuadrilateralNewTest_2472 : public ::testing::Test {};

}  // namespace

TEST_F(PopplerQuadrilateralNewTest_2472, ReturnsNonNullPointer_2472) {
  PopplerQuadrilateral* q = poppler_quadrilateral_new();
  ASSERT_NE(q, nullptr);

  // Free using GLib slice free. If poppler uses slices, this is the matching deallocator
  // for g_slice_new0 (and is safe as long as the allocation came from slice allocator).
  // This is part of the allocation contract implied by the function's type and GLib usage.
  g_slice_free(PopplerQuadrilateral, q);
}

TEST_F(PopplerQuadrilateralNewTest_2472, MultipleCallsReturnDistinctPointers_2472) {
  PopplerQuadrilateral* a = poppler_quadrilateral_new();
  PopplerQuadrilateral* b = poppler_quadrilateral_new();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  // Boundary/behavioral expectation: two allocations should not alias.
  // If an allocator reuses freed memory, these are still live here, so they should differ.
  EXPECT_NE(a, b);

  g_slice_free(PopplerQuadrilateral, a);
  g_slice_free(PopplerQuadrilateral, b);
}

TEST_F(PopplerQuadrilateralNewTest_2472, CanAllocateAndFreeManyTimes_2472) {
  // Boundary-ish stress: allocate a modest number to ensure no obvious crashes/leaks
  // are exposed through the public contract.
  constexpr int kCount = 1024;

  GPtrArray* arr = g_ptr_array_new_with_free_func(nullptr);
  ASSERT_NE(arr, nullptr);

  for (int i = 0; i < kCount; ++i) {
    PopplerQuadrilateral* q = poppler_quadrilateral_new();
    ASSERT_NE(q, nullptr);
    g_ptr_array_add(arr, q);
  }

  for (guint i = 0; i < arr->len; ++i) {
    auto* q = static_cast<PopplerQuadrilateral*>(g_ptr_array_index(arr, i));
    g_slice_free(PopplerQuadrilateral, q);
  }

  g_ptr_array_free(arr, TRUE);
}

TEST_F(PopplerQuadrilateralNewTest_2472, AllocationDoesNotThrowOrAbortOnTypicalUse_2472) {
  // Exceptional/error case (observable): the function should be callable without throwing C++ exceptions.
  // If it aborts due to OOM, that's not reliably testable without global allocator hooks.
  EXPECT_NO_THROW({
    PopplerQuadrilateral* q = poppler_quadrilateral_new();
    ASSERT_NE(q, nullptr);
    g_slice_free(PopplerQuadrilateral, q);
  });
}