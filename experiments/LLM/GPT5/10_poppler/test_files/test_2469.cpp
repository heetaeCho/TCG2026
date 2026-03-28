// poppler-point-new-test_2469.cc
//
// Unit tests for:
//   PopplerPoint *poppler_point_new(void);
//
// File under test:
//   ./TestProjects/poppler/glib/poppler-page.cc
//
// Notes:
// - Treat implementation as a black box.
// - We only test observable behavior via the public interface.
// - Here, the only observable property we can safely validate is that the
//   returned pointer is non-null (successful allocation).
// - We avoid assuming struct layout (no field access), and avoid relying on
//   GLib slice internals.

#include <gtest/gtest.h>

extern "C" {
// Forward declaration from the Poppler GLib API.
// Include the proper header in your tree if available (preferred):
//   #include <poppler.h>
// For this isolated unit-test file, we only need the type + function signature.
typedef struct _PopplerPoint PopplerPoint;

PopplerPoint *poppler_point_new(void);
}  // extern "C"

namespace {

class PopplerPointNewTest_2469 : public ::testing::Test {};

TEST_F(PopplerPointNewTest_2469, ReturnsNonNull_2469) {
  PopplerPoint* p = poppler_point_new();
  ASSERT_NE(p, nullptr);
}

TEST_F(PopplerPointNewTest_2469, MultipleCallsReturnDistinctPointers_2469) {
  PopplerPoint* p1 = poppler_point_new();
  PopplerPoint* p2 = poppler_point_new();

  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);

  // Boundary-ish sanity: two independent allocations should not alias.
  // This does not assume any internal state, only that allocation provides
  // distinct live objects.
  EXPECT_NE(p1, p2);
}

TEST_F(PopplerPointNewTest_2469, StressManyAllocationsAreNonNull_2469) {
  // Boundary: allocate a bunch of points to ensure the API behaves consistently.
  // Keep it modest to avoid memory pressure in constrained CI.
  constexpr int kCount = 1024;

  for (int i = 0; i < kCount; ++i) {
    PopplerPoint* p = poppler_point_new();
    ASSERT_NE(p, nullptr) << "Allocation failed at i=" << i;
  }
}

}  // namespace