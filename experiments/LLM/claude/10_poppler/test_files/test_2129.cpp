#include <gtest/gtest.h>
#include <glib.h>
#include <cstring>

// Include necessary headers
extern "C" {

typedef struct {
    double x;
    double y;
} PopplerPoint;

typedef struct {
    PopplerPoint *points;
    int n_points;
} PopplerPath;

PopplerPath *poppler_path_copy(PopplerPath *path);

}

class PopplerPathCopyTest_2129 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup is done in individual tests
    }
};

TEST_F(PopplerPathCopyTest_2129, CopySinglePoint_2129) {
    PopplerPath path;
    path.n_points = 1;
    path.points = g_new(PopplerPoint, 1);
    path.points[0].x = 3.14;
    path.points[0].y = 2.72;

    PopplerPath *copy = poppler_path_copy(&path);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->n_points, 1);
    ASSERT_NE(copy->points, nullptr);
    EXPECT_NE(copy->points, path.points); // Different memory
    EXPECT_DOUBLE_EQ(copy->points[0].x, 3.14);
    EXPECT_DOUBLE_EQ(copy->points[0].y, 2.72);

    g_free(copy->points);
    g_free(copy);
    g_free(path.points);
}

TEST_F(PopplerPathCopyTest_2129, CopyMultiplePoints_2129) {
    PopplerPath path;
    path.n_points = 3;
    path.points = g_new(PopplerPoint, 3);
    path.points[0].x = 1.0; path.points[0].y = 2.0;
    path.points[1].x = 3.0; path.points[1].y = 4.0;
    path.points[2].x = 5.0; path.points[2].y = 6.0;

    PopplerPath *copy = poppler_path_copy(&path);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->n_points, 3);
    ASSERT_NE(copy->points, nullptr);
    EXPECT_NE(copy->points, path.points);

    for (int i = 0; i < 3; i++) {
        EXPECT_DOUBLE_EQ(copy->points[i].x, path.points[i].x);
        EXPECT_DOUBLE_EQ(copy->points[i].y, path.points[i].y);
    }

    g_free(copy->points);
    g_free(copy);
    g_free(path.points);
}

TEST_F(PopplerPathCopyTest_2129, CopyIsDeepCopy_2129) {
    PopplerPath path;
    path.n_points = 2;
    path.points = g_new(PopplerPoint, 2);
    path.points[0].x = 10.0; path.points[0].y = 20.0;
    path.points[1].x = 30.0; path.points[1].y = 40.0;

    PopplerPath *copy = poppler_path_copy(&path);

    // Modify the original after copy
    path.points[0].x = 999.0;
    path.points[0].y = 888.0;

    // The copy should not be affected
    EXPECT_DOUBLE_EQ(copy->points[0].x, 10.0);
    EXPECT_DOUBLE_EQ(copy->points[0].y, 20.0);

    g_free(copy->points);
    g_free(copy);
    g_free(path.points);
}

TEST_F(PopplerPathCopyTest_2129, CopyPreservesNPoints_2129) {
    PopplerPath path;
    path.n_points = 5;
    path.points = g_new(PopplerPoint, 5);
    for (int i = 0; i < 5; i++) {
        path.points[i].x = (double)i;
        path.points[i].y = (double)(i * 2);
    }

    PopplerPath *copy = poppler_path_copy(&path);

    EXPECT_EQ(copy->n_points, path.n_points);

    g_free(copy->points);
    g_free(copy);
    g_free(path.points);
}

TEST_F(PopplerPathCopyTest_2129, CopyWithZeroPoints_2129) {
    PopplerPath path;
    path.n_points = 0;
    path.points = nullptr;

    PopplerPath *copy = poppler_path_copy(&path);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->n_points, 0);

    g_free(copy->points);
    g_free(copy);
}

TEST_F(PopplerPathCopyTest_2129, CopyWithNegativeCoordinates_2129) {
    PopplerPath path;
    path.n_points = 2;
    path.points = g_new(PopplerPoint, 2);
    path.points[0].x = -100.5; path.points[0].y = -200.5;
    path.points[1].x = -0.001; path.points[1].y = -99999.99;

    PopplerPath *copy = poppler_path_copy(&path);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->n_points, 2);
    EXPECT_DOUBLE_EQ(copy->points[0].x, -100.5);
    EXPECT_DOUBLE_EQ(copy->points[0].y, -200.5);
    EXPECT_DOUBLE_EQ(copy->points[1].x, -0.001);
    EXPECT_DOUBLE_EQ(copy->points[1].y, -99999.99);

    g_free(copy->points);
    g_free(copy);
    g_free(path.points);
}

TEST_F(PopplerPathCopyTest_2129, CopyReturnsNewAllocation_2129) {
    PopplerPath path;
    path.n_points = 1;
    path.points = g_new(PopplerPoint, 1);
    path.points[0].x = 0.0;
    path.points[0].y = 0.0;

    PopplerPath *copy = poppler_path_copy(&path);

    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, &path);
    EXPECT_NE(copy->points, path.points);

    g_free(copy->points);
    g_free(copy);
    g_free(path.points);
}

TEST_F(PopplerPathCopyTest_2129, CopyLargeNumberOfPoints_2129) {
    const int num_points = 1000;
    PopplerPath path;
    path.n_points = num_points;
    path.points = g_new(PopplerPoint, num_points);
    for (int i = 0; i < num_points; i++) {
        path.points[i].x = (double)i * 0.1;
        path.points[i].y = (double)i * 0.2;
    }

    PopplerPath *copy = poppler_path_copy(&path);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->n_points, num_points);
    for (int i = 0; i < num_points; i++) {
        EXPECT_DOUBLE_EQ(copy->points[i].x, path.points[i].x);
        EXPECT_DOUBLE_EQ(copy->points[i].y, path.points[i].y);
    }

    g_free(copy->points);
    g_free(copy);
    g_free(path.points);
}

TEST_F(PopplerPathCopyTest_2129, CopyWithZeroValueCoordinates_2129) {
    PopplerPath path;
    path.n_points = 2;
    path.points = g_new(PopplerPoint, 2);
    path.points[0].x = 0.0; path.points[0].y = 0.0;
    path.points[1].x = 0.0; path.points[1].y = 0.0;

    PopplerPath *copy = poppler_path_copy(&path);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->n_points, 2);
    EXPECT_DOUBLE_EQ(copy->points[0].x, 0.0);
    EXPECT_DOUBLE_EQ(copy->points[0].y, 0.0);
    EXPECT_DOUBLE_EQ(copy->points[1].x, 0.0);
    EXPECT_DOUBLE_EQ(copy->points[1].y, 0.0);

    g_free(copy->points);
    g_free(copy);
    g_free(path.points);
}
