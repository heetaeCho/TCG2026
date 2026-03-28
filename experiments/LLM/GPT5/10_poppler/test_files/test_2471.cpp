// poppler-point-free-test.cc
//
// Unit tests for poppler_point_free()
// Target: ./TestProjects/poppler/glib/poppler-page.cc
//
// NOTE:
// - We treat poppler_point_free as a black box and only verify observable behavior.
// - Since poppler_point_free uses GLib slice allocator/free, these tests rely on GLib
//   and are intended to be built/ran in the same environment as the Poppler GLib tests.

#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-page.h"

// Function under test (implemented in poppler-page.cc)
extern "C" void poppler_point_free(PopplerPoint *point);

namespace {

class PopplerPointFreeTest_2471 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure GLib is initialized enough for slice allocator usage.
    // g_test_init is not required here; Poppler's test harness may already init GLib.
  }
};

TEST_F(PopplerPointFreeTest_2471, FreeNullIsSafe_2471) {
  // Boundary/error case: freeing NULL should not crash in GLib slice free.
  // Observable behavior: process remains alive.
  poppler_point_free(nullptr);
  SUCCEED();
}

TEST_F(PopplerPointFreeTest_2471, FreeValidSliceAllocatedPointDoesNotCrash_2471) {
  // Normal operation: allocate a PopplerPoint via GLib slice allocator and free it.
  // Observable behavior: no crash.
  PopplerPoint* p = g_slice_new(PopplerPoint);
  ASSERT_NE(p, nullptr);

  poppler_point_free(p);
  SUCCEED();
}

TEST_F(PopplerPointFreeTest_2471, FreeMultipleDistinctPointsDoesNotCrash_2471) {
  // Normal operation / boundary: free multiple separately allocated instances.
  // Observable behavior: no crash.
  PopplerPoint* p1 = g_slice_new(PopplerPoint);
  PopplerPoint* p2 = g_slice_new(PopplerPoint);
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  ASSERT_NE(p1, p2);

  poppler_point_free(p1);
  poppler_point_free(p2);
  SUCCEED();
}

TEST_F(PopplerPointFreeTest_2471, FreeAfterWriteToMemoryDoesNotCrash_2471) {
  // Boundary: since struct is opaque in the header snippet, we can't access fields.
  // But we can still write raw bytes to the allocated block (as a "user payload")
  // and ensure free doesn't crash.
  PopplerPoint* p = g_slice_new(PopplerPoint);
  ASSERT_NE(p, nullptr);

  // Write some bytes into the object storage to simulate non-zero contents.
  // We do not assume any internal layout; we only touch the memory region that
  // is at least sizeof(PopplerPoint) (which is valid for our allocation).
  memset(p, 0xA5, sizeof(PopplerPoint));

  poppler_point_free(p);
  SUCCEED();
}

}  // namespace