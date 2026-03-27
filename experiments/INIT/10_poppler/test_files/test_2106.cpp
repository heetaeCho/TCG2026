// File: poppler-annot-callout-line-new-test-2106.cc
//
// Unit tests for:
//   PopplerAnnotCalloutLine *poppler_annot_callout_line_new(void);
//
// Notes:
// - Treat as black box: we only test observable behavior from the public interface.
// - Here, observable behavior is: returns a valid pointer and returns distinct allocations.
// - We do NOT inspect struct internals (even if they are zeroed by g_new0).

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "poppler.h"  // Provides PopplerAnnotCalloutLine and poppler_annot_callout_line_new
}

class PopplerAnnotCalloutLineNewTest_2106 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Ensure GLib allocations from tests are released.
    for (auto* p : allocated_) {
      g_free(p);
    }
    allocated_.clear();
  }

  void Track(PopplerAnnotCalloutLine* p) {
    if (p) allocated_.push_back(p);
  }

 private:
  std::vector<PopplerAnnotCalloutLine*> allocated_;
};

TEST_F(PopplerAnnotCalloutLineNewTest_2106, ReturnsNonNullPointer_2106) {
  PopplerAnnotCalloutLine* line = poppler_annot_callout_line_new();
  Track(line);

  ASSERT_NE(line, nullptr);
}

TEST_F(PopplerAnnotCalloutLineNewTest_2106, MultipleCallsReturnDistinctPointers_2106) {
  PopplerAnnotCalloutLine* a = poppler_annot_callout_line_new();
  PopplerAnnotCalloutLine* b = poppler_annot_callout_line_new();
  Track(a);
  Track(b);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a, b);
}

TEST_F(PopplerAnnotCalloutLineNewTest_2106, ManyAllocationsAreAllNonNullAndUnique_2106) {
  // Boundary-ish check: allocate several objects to ensure behavior is consistent under repetition.
  constexpr int kCount = 64;

  std::vector<PopplerAnnotCalloutLine*> ptrs;
  ptrs.reserve(kCount);

  for (int i = 0; i < kCount; ++i) {
    PopplerAnnotCalloutLine* p = poppler_annot_callout_line_new();
    Track(p);
    ASSERT_NE(p, nullptr) << "Allocation failed at index " << i;
    ptrs.push_back(p);
  }

  // Verify uniqueness (no reuse within this batch).
  for (int i = 0; i < kCount; ++i) {
    for (int j = i + 1; j < kCount; ++j) {
      EXPECT_NE(ptrs[i], ptrs[j]) << "Pointers at " << i << " and " << j << " are identical";
    }
  }
}

TEST_F(PopplerAnnotCalloutLineNewTest_2106, FreeingAllocatedPointerDoesNotCrash_2106) {
  // Error/exceptional behavior is not exposed via API; best we can do is verify
  // the returned pointer can be freed with the matching GLib deallocator.
  PopplerAnnotCalloutLine* line = poppler_annot_callout_line_new();
  ASSERT_NE(line, nullptr);

  // Free immediately; if this mismatched allocator or returned invalid memory, we'd likely crash.
  g_free(line);
  // Do not Track(line) since we already freed it.
}