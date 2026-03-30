// poppler-path-free-test_2128.cc
#include <gtest/gtest.h>

#include <glib.h>

// The production headers may already declare PopplerPath and poppler_path_free.
// To keep this test robust against header layout changes, we include the known
// private dependency that defines _PopplerPath (per prompt), and declare the
// function if needed.
extern "C" {

// From ./TestProjects/poppler/glib/poppler-private.h (given in prompt)
typedef struct _PopplerPath PopplerPath;
typedef struct _PopplerPoint PopplerPoint; // Only used as an opaque element type in these tests.

struct _PopplerPath {
  PopplerPoint* points;
  int n_points;
};

// From ./TestProjects/poppler/glib/poppler-annot.cc (given in prompt)
void poppler_path_free(PopplerPath* path);
}  // extern "C"

namespace {

class PopplerPathFreeTest_2128 : public ::testing::Test {};

TEST_F(PopplerPathFreeTest_2128, FreesPathWithPoints_NoCrash_2128) {
  // Normal operation: points allocated, path allocated.
  auto* path = static_cast<PopplerPath*>(g_malloc0(sizeof(PopplerPath)));
  ASSERT_NE(path, nullptr);

  path->n_points = 3;
  // We don't need to know PopplerPoint's layout; we only need a non-null buffer.
  path->points = static_cast<PopplerPoint*>(g_malloc0(sizeof(gpointer) * path->n_points));
  ASSERT_NE(path->points, nullptr);

  // Observable behavior: should not crash.
  poppler_path_free(path);
}

TEST_F(PopplerPathFreeTest_2128, FreesPathWithNullPoints_NoCrash_2128) {
  // Boundary condition: points == nullptr (freeing nullptr is OK in GLib),
  // n_points == 0 (should not matter to this function as observed externally).
  auto* path = static_cast<PopplerPath*>(g_malloc0(sizeof(PopplerPath)));
  ASSERT_NE(path, nullptr);

  path->n_points = 0;
  path->points = nullptr;

  // Observable behavior: should not crash.
  poppler_path_free(path);
}

TEST_F(PopplerPathFreeTest_2128, NullPath_Death_2128) {
  // Error case (observable): passing nullptr dereferences path->points in the
  // provided implementation, so this should crash.
  EXPECT_DEATH({ poppler_path_free(nullptr); }, "");
}

}  // namespace