#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and struct definitions based on the provided interface
struct _PopplerPoint {
    double x;
    double y;
};
typedef struct _PopplerPoint PopplerPoint;

typedef struct {
    PopplerPoint *points;
    gsize n_points;
} PopplerPath;

// Declaration of the function under test
extern "C" PopplerPath *poppler_path_new_from_array(PopplerPoint *points, gsize n_points);

class PopplerPathTest_2127 : public ::testing::Test {
protected:
    void TearDown() override {
        // Note: We don't free the points array in paths since we manage them separately
    }
};

// Test normal operation with a valid array of points
TEST_F(PopplerPathTest_2127, NewFromArrayWithValidPoints_2127) {
    const gsize n = 3;
    PopplerPoint *points = g_new(PopplerPoint, n);
    points[0].x = 1.0; points[0].y = 2.0;
    points[1].x = 3.0; points[1].y = 4.0;
    points[2].x = 5.0; points[2].y = 6.0;

    PopplerPath *path = poppler_path_new_from_array(points, n);

    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->points, points);
    EXPECT_EQ(path->n_points, n);

    // Verify the points are accessible through the path
    EXPECT_DOUBLE_EQ(path->points[0].x, 1.0);
    EXPECT_DOUBLE_EQ(path->points[0].y, 2.0);
    EXPECT_DOUBLE_EQ(path->points[1].x, 3.0);
    EXPECT_DOUBLE_EQ(path->points[1].y, 4.0);
    EXPECT_DOUBLE_EQ(path->points[2].x, 5.0);
    EXPECT_DOUBLE_EQ(path->points[2].y, 6.0);

    g_free(path);
    g_free(points);
}

// Test with a single point
TEST_F(PopplerPathTest_2127, NewFromArrayWithSinglePoint_2127) {
    const gsize n = 1;
    PopplerPoint *points = g_new(PopplerPoint, n);
    points[0].x = 42.0; points[0].y = 84.0;

    PopplerPath *path = poppler_path_new_from_array(points, n);

    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->points, points);
    EXPECT_EQ(path->n_points, n);
    EXPECT_DOUBLE_EQ(path->points[0].x, 42.0);
    EXPECT_DOUBLE_EQ(path->points[0].y, 84.0);

    g_free(path);
    g_free(points);
}

// Test with zero points (boundary condition)
TEST_F(PopplerPathTest_2127, NewFromArrayWithZeroPoints_2127) {
    PopplerPath *path = poppler_path_new_from_array(nullptr, 0);

    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->points, nullptr);
    EXPECT_EQ(path->n_points, 0u);

    g_free(path);
}

// Test that the function stores the pointer, not a copy
TEST_F(PopplerPathTest_2127, NewFromArrayStoresPointerNotCopy_2127) {
    const gsize n = 2;
    PopplerPoint *points = g_new(PopplerPoint, n);
    points[0].x = 10.0; points[0].y = 20.0;
    points[1].x = 30.0; points[1].y = 40.0;

    PopplerPath *path = poppler_path_new_from_array(points, n);

    ASSERT_NE(path, nullptr);
    // The path should store the exact same pointer
    EXPECT_EQ(path->points, points);

    // Modifying through the original pointer should be visible through path
    points[0].x = 99.0;
    EXPECT_DOUBLE_EQ(path->points[0].x, 99.0);

    g_free(path);
    g_free(points);
}

// Test with a large number of points
TEST_F(PopplerPathTest_2127, NewFromArrayWithLargeNumberOfPoints_2127) {
    const gsize n = 10000;
    PopplerPoint *points = g_new(PopplerPoint, n);
    for (gsize i = 0; i < n; i++) {
        points[i].x = static_cast<double>(i);
        points[i].y = static_cast<double>(i * 2);
    }

    PopplerPath *path = poppler_path_new_from_array(points, n);

    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->points, points);
    EXPECT_EQ(path->n_points, n);

    // Spot check some values
    EXPECT_DOUBLE_EQ(path->points[0].x, 0.0);
    EXPECT_DOUBLE_EQ(path->points[9999].x, 9999.0);
    EXPECT_DOUBLE_EQ(path->points[9999].y, 19998.0);

    g_free(path);
    g_free(points);
}

// Test with null points but non-zero n_points (edge case)
TEST_F(PopplerPathTest_2127, NewFromArrayWithNullPointsNonZeroCount_2127) {
    PopplerPath *path = poppler_path_new_from_array(nullptr, 5);

    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->points, nullptr);
    EXPECT_EQ(path->n_points, 5u);

    g_free(path);
}

// Test that multiple calls create independent path objects
TEST_F(PopplerPathTest_2127, NewFromArrayCreatesIndependentObjects_2127) {
    const gsize n1 = 2, n2 = 3;
    PopplerPoint *points1 = g_new(PopplerPoint, n1);
    PopplerPoint *points2 = g_new(PopplerPoint, n2);

    PopplerPath *path1 = poppler_path_new_from_array(points1, n1);
    PopplerPath *path2 = poppler_path_new_from_array(points2, n2);

    ASSERT_NE(path1, nullptr);
    ASSERT_NE(path2, nullptr);
    EXPECT_NE(path1, path2);
    EXPECT_EQ(path1->points, points1);
    EXPECT_EQ(path1->n_points, n1);
    EXPECT_EQ(path2->points, points2);
    EXPECT_EQ(path2->n_points, n2);

    g_free(path1);
    g_free(path2);
    g_free(points1);
    g_free(points2);
}

// Test with maximum gsize value for n_points (boundary)
TEST_F(PopplerPathTest_2127, NewFromArrayWithMaxNPoints_2127) {
    gsize max_n = G_MAXSIZE;
    PopplerPath *path = poppler_path_new_from_array(nullptr, max_n);

    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->n_points, max_n);
    EXPECT_EQ(path->points, nullptr);

    g_free(path);
}
