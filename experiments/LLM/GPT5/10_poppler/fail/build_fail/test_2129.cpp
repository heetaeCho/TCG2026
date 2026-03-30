// File: poppler-path-copy-test-2129.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>

// Minimal compatible declarations for this unit test TU.
// (The production implementation is treated as a black box; we only rely on the
// public/visible interface and observable behavior.)
extern "C" {

typedef struct _PopplerPoint {
  double x;
  double y;
} PopplerPoint;

typedef struct _PopplerPath {
  PopplerPoint* points;
  int n_points;
} PopplerPath;

// Function under test (implemented in poppler-annot.cc in the real codebase).
PopplerPath* poppler_path_copy(PopplerPath* path);
}

namespace {

class PopplerPathCopyTest_2129 : public ::testing::Test {
 protected:
  static PopplerPath* MakePathWithPoints(const PopplerPoint* pts, int n) {
    PopplerPath* p = g_new(PopplerPath, 1);
    p->n_points = n;

    if (n > 0) {
      p->points = g_new(PopplerPoint, n);
      std::memcpy(p->points, pts, sizeof(PopplerPoint) * static_cast<size_t>(n));
    } else {
      // Avoid assumptions about whether passing nullptr to memcpy(0) is ok
      // on all platforms/ABIs; provide a valid pointer even for 0 points.
      p->points = g_new(PopplerPoint, 1);
    }
    return p;
  }

  static void FreePath(PopplerPath* p) {
    if (!p) return;
    g_free(p->points);
    g_free(p);
  }
};

TEST_F(PopplerPathCopyTest_2129, CopiesNonEmptyPathDeepCopy_2129) {
  const PopplerPoint pts[] = {{1.0, 2.0}, {3.5, 4.5}, {-7.25, 9.0}};
  PopplerPath* original = MakePathWithPoints(pts, 3);

  PopplerPath* copy = poppler_path_copy(original);

  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, original);
  EXPECT_EQ(copy->n_points, original->n_points);
  ASSERT_NE(copy->points, nullptr);
  ASSERT_NE(copy->points, original->points);

  // Content equality.
  for (int i = 0; i < original->n_points; ++i) {
    EXPECT_DOUBLE_EQ(copy->points[i].x, original->points[i].x);
    EXPECT_DOUBLE_EQ(copy->points[i].y, original->points[i].y);
  }

  // Deep copy check: changing the original does not affect the copy.
  original->points[1].x = 1234.0;
  original->points[1].y = -4321.0;
  EXPECT_DOUBLE_EQ(copy->points[1].x, pts[1].x);
  EXPECT_DOUBLE_EQ(copy->points[1].y, pts[1].y);

  // Deep copy check: changing the copy does not affect the original.
  copy->points[0].x = 777.0;
  copy->points[0].y = 888.0;
  EXPECT_DOUBLE_EQ(original->points[0].x, pts[0].x);
  EXPECT_DOUBLE_EQ(original->points[0].y, pts[0].y);

  FreePath(copy);
  FreePath(original);
}

TEST_F(PopplerPathCopyTest_2129, CopiesZeroPointsPath_2129) {
  // Boundary condition: n_points == 0.
  PopplerPath* original = g_new(PopplerPath, 1);
  original->n_points = 0;
  // Provide a valid pointer to avoid any platform-specific UB concerns with
  // memcpy(0) + nullptr even though many libcs tolerate it.
  original->points = g_new(PopplerPoint, 1);

  PopplerPath* copy = poppler_path_copy(original);

  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, original);
  EXPECT_EQ(copy->n_points, 0);

  // points should be allocated by the copy function; we only assert non-null
  // (since allocation behavior for size 0 can vary by allocator/GLib config).
  EXPECT_NE(copy->points, nullptr);

  // Ensure pointers are independent even in the 0-points case.
  EXPECT_NE(copy->points, original->points);

  FreePath(copy);
  FreePath(original);
}

TEST_F(PopplerPathCopyTest_2129, CopiesLargerPathMaintainsAllPoints_2129) {
  // Boundary-ish: a "larger" number of points.
  const int kN = 1024;
  PopplerPoint* pts = g_new(PopplerPoint, kN);
  for (int i = 0; i < kN; ++i) {
    pts[i].x = static_cast<double>(i) * 0.5;
    pts[i].y = static_cast<double>(-i) * 1.25;
  }

  PopplerPath* original = MakePathWithPoints(pts, kN);
  PopplerPath* copy = poppler_path_copy(original);

  ASSERT_NE(copy, nullptr);
  EXPECT_EQ(copy->n_points, kN);
  ASSERT_NE(copy->points, nullptr);
  ASSERT_NE(copy->points, original->points);

  // Spot-check a few positions including ends.
  const int indices[] = {0, 1, 2, kN / 2, kN - 3, kN - 2, kN - 1};
  for (int idx : indices) {
    EXPECT_DOUBLE_EQ(copy->points[idx].x, original->points[idx].x);
    EXPECT_DOUBLE_EQ(copy->points[idx].y, original->points[idx].y);
  }

  FreePath(copy);
  FreePath(original);
  g_free(pts);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerPathCopyTest_2129, DeathOnNullPath_2129) {
  // Error case (observable): passing nullptr is invalid for this C API; the
  // implementation dereferences the pointer, so this should crash/abort.
  ASSERT_DEATH(
      {
        PopplerPath* out = poppler_path_copy(nullptr);
        (void)out;
      },
      "");
}

TEST_F(PopplerPathCopyTest_2129, DeathOnNullPointsWhenNPointsPositive_2129) {
  // Error case: n_points > 0 but points == nullptr is an invalid object state.
  PopplerPath* bad = g_new(PopplerPath, 1);
  bad->n_points = 1;
  bad->points = nullptr;

  ASSERT_DEATH(
      {
        PopplerPath* out = poppler_path_copy(bad);
        (void)out;
      },
      "");

  g_free(bad);
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace