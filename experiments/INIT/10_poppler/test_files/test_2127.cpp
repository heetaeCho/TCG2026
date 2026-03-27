// poppler_path_new_from_array_test_2127.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "poppler-page.h"
#include "poppler-annot.h"
}

class PopplerPathNewFromArrayTest_2127 : public ::testing::Test {
protected:
  static PopplerPoint* NewPoints(gsize n) {
    // PopplerPoint is an (empty) struct in this test project; allocate as a plain array.
    return (n == 0) ? nullptr : (PopplerPoint*)g_new0(PopplerPoint, n);
  }

  static void FreePoints(PopplerPoint* p) { g_free(p); }

  static void FreePath(PopplerPath* path) { g_free(path); }
};

TEST_F(PopplerPathNewFromArrayTest_2127, NonNullReturnForTypicalInput_2127) {
  const gsize n = 3;
  PopplerPoint* points = NewPoints(n);

  PopplerPath* path = poppler_path_new_from_array(points, n);

  ASSERT_NE(path, nullptr);

  // Observable behavior through publicly exposed struct fields (if present in headers).
  EXPECT_EQ(path->points, points);
  EXPECT_EQ(path->n_points, n);

  FreePath(path);
  FreePoints(points);
}

TEST_F(PopplerPathNewFromArrayTest_2127, AllowsNullPointsWithZeroCount_2127) {
  PopplerPath* path = poppler_path_new_from_array(nullptr, 0);

  ASSERT_NE(path, nullptr);
  EXPECT_EQ(path->points, nullptr);
  EXPECT_EQ(path->n_points, (gsize)0);

  FreePath(path);
}

TEST_F(PopplerPathNewFromArrayTest_2127, AllowsNonNullPointsWithZeroCount_2127) {
  PopplerPoint* points = NewPoints(1);

  PopplerPath* path = poppler_path_new_from_array(points, 0);

  ASSERT_NE(path, nullptr);
  EXPECT_EQ(path->points, points);
  EXPECT_EQ(path->n_points, (gsize)0);

  FreePath(path);
  FreePoints(points);
}

TEST_F(PopplerPathNewFromArrayTest_2127, AllowsNullPointsWithNonZeroCount_2127) {
  const gsize n = 5;

  PopplerPath* path = poppler_path_new_from_array(nullptr, n);

  ASSERT_NE(path, nullptr);
  EXPECT_EQ(path->points, nullptr);
  EXPECT_EQ(path->n_points, n);

  FreePath(path);
}

TEST_F(PopplerPathNewFromArrayTest_2127, EachCallReturnsDistinctAllocation_2127) {
  const gsize n = 2;
  PopplerPoint* points = NewPoints(n);

  PopplerPath* path1 = poppler_path_new_from_array(points, n);
  PopplerPath* path2 = poppler_path_new_from_array(points, n);

  ASSERT_NE(path1, nullptr);
  ASSERT_NE(path2, nullptr);
  EXPECT_NE(path1, path2);

  // Also ensure each stores the provided inputs.
  EXPECT_EQ(path1->points, points);
  EXPECT_EQ(path1->n_points, n);
  EXPECT_EQ(path2->points, points);
  EXPECT_EQ(path2->n_points, n);

  FreePath(path1);
  FreePath(path2);
  FreePoints(points);
}