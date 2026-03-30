// File: poppler-path-get-points-test-2130.cc
#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

#if __has_include(<glib.h>)
#include <glib.h>
#else
// Fallback if glib headers aren't available in this unit-test build.
using gsize = std::size_t;
#endif

// Minimal public-facing data types needed by the tested interface.
// (These are based on the provided dependency snippet and typical Poppler GLib API shapes.)
struct PopplerPoint {
  double x;
  double y;
};

struct _PopplerPath {
 public:
  PopplerPoint* points;
  int n_points;
};
using PopplerPath = _PopplerPath;

// Function under test (implemented in production code).
extern "C" PopplerPoint* poppler_path_get_points(PopplerPath* path, gsize* n_points);

class PopplerPathGetPointsTest_2130 : public ::testing::Test {};

TEST_F(PopplerPathGetPointsTest_2130, ReturnsPointsAndSetsCountForNonEmptyPath_2130) {
  PopplerPoint pts[3] = {{1.0, 2.0}, {3.0, 4.0}, {-5.0, 6.5}};
  PopplerPath path;
  path.points = pts;
  path.n_points = 3;

  gsize out_n = 0;
  PopplerPoint* out_pts = poppler_path_get_points(&path, &out_n);

  EXPECT_EQ(out_pts, pts);
  EXPECT_EQ(out_n, static_cast<gsize>(3));
}

TEST_F(PopplerPathGetPointsTest_2130, ReturnsNullAndSetsZeroForEmptyPathWithNullPoints_2130) {
  PopplerPath path;
  path.points = nullptr;
  path.n_points = 0;

  gsize out_n = 123;  // ensure it gets overwritten
  PopplerPoint* out_pts = poppler_path_get_points(&path, &out_n);

  EXPECT_EQ(out_pts, nullptr);
  EXPECT_EQ(out_n, static_cast<gsize>(0));
}

TEST_F(PopplerPathGetPointsTest_2130, ReturnsPointerEvenWhenCountIsZero_2130) {
  PopplerPoint pts[1] = {{9.0, 10.0}};
  PopplerPath path;
  path.points = pts;
  path.n_points = 0;

  gsize out_n = 999;
  PopplerPoint* out_pts = poppler_path_get_points(&path, &out_n);

  EXPECT_EQ(out_pts, pts);
  EXPECT_EQ(out_n, static_cast<gsize>(0));
}

TEST_F(PopplerPathGetPointsTest_2130, BoundaryLargeCountIsReported_2130) {
  PopplerPoint pts[1] = {{0.0, 0.0}};
  PopplerPath path;
  path.points = pts;
  path.n_points = 1000000;  // boundary-ish large positive int

  gsize out_n = 0;
  PopplerPoint* out_pts = poppler_path_get_points(&path, &out_n);

  EXPECT_EQ(out_pts, pts);
  EXPECT_EQ(out_n, static_cast<gsize>(1000000));
}

TEST_F(PopplerPathGetPointsTest_2130, DeathOnNullNPointsPointer_2130) {
  PopplerPoint pts[1] = {{1.0, 1.0}};
  PopplerPath path;
  path.points = pts;
  path.n_points = 1;

  // The interface requires n_points to be a valid pointer.
  ASSERT_DEATH_IF_SUPPORTED(
      {
        (void)poppler_path_get_points(&path, nullptr);
      },
      "");
}

TEST_F(PopplerPathGetPointsTest_2130, DeathOnNullPathPointer_2130) {
  gsize out_n = 0;

  // The interface requires path to be a valid pointer.
  ASSERT_DEATH_IF_SUPPORTED(
      {
        (void)poppler_path_get_points(nullptr, &out_n);
      },
      "");
}