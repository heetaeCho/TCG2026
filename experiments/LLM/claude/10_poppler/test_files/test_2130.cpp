#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and struct definitions based on the known dependencies
extern "C" {

typedef struct {
    double x;
    double y;
} PopplerPoint;

typedef struct _PopplerPath {
    PopplerPoint *points;
    int n_points;
} PopplerPath;

PopplerPoint *poppler_path_get_points(PopplerPath *path, gsize *n_points);

}

class PopplerPathGetPointsTest_2130 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerPathGetPointsTest_2130, ReturnsCorrectPointsPointer_2130) {
    PopplerPoint pts[3] = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
    PopplerPath path;
    path.points = pts;
    path.n_points = 3;

    gsize n_points = 0;
    PopplerPoint *result = poppler_path_get_points(&path, &n_points);

    EXPECT_EQ(result, pts);
}

TEST_F(PopplerPathGetPointsTest_2130, ReturnsCorrectNumberOfPoints_2130) {
    PopplerPoint pts[3] = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
    PopplerPath path;
    path.points = pts;
    path.n_points = 3;

    gsize n_points = 0;
    poppler_path_get_points(&path, &n_points);

    EXPECT_EQ(n_points, 3u);
}

TEST_F(PopplerPathGetPointsTest_2130, SinglePoint_2130) {
    PopplerPoint pt = {10.0, 20.0};
    PopplerPath path;
    path.points = &pt;
    path.n_points = 1;

    gsize n_points = 0;
    PopplerPoint *result = poppler_path_get_points(&path, &n_points);

    EXPECT_EQ(n_points, 1u);
    EXPECT_EQ(result, &pt);
    EXPECT_DOUBLE_EQ(result[0].x, 10.0);
    EXPECT_DOUBLE_EQ(result[0].y, 20.0);
}

TEST_F(PopplerPathGetPointsTest_2130, ZeroPoints_2130) {
    PopplerPath path;
    path.points = nullptr;
    path.n_points = 0;

    gsize n_points = 999;
    PopplerPoint *result = poppler_path_get_points(&path, &n_points);

    EXPECT_EQ(n_points, 0u);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerPathGetPointsTest_2130, PointsDataIntegrity_2130) {
    PopplerPoint pts[4] = {{0.0, 0.0}, {1.5, 2.5}, {-3.0, -4.0}, {100.0, 200.0}};
    PopplerPath path;
    path.points = pts;
    path.n_points = 4;

    gsize n_points = 0;
    PopplerPoint *result = poppler_path_get_points(&path, &n_points);

    ASSERT_EQ(n_points, 4u);
    EXPECT_DOUBLE_EQ(result[0].x, 0.0);
    EXPECT_DOUBLE_EQ(result[0].y, 0.0);
    EXPECT_DOUBLE_EQ(result[1].x, 1.5);
    EXPECT_DOUBLE_EQ(result[1].y, 2.5);
    EXPECT_DOUBLE_EQ(result[2].x, -3.0);
    EXPECT_DOUBLE_EQ(result[2].y, -4.0);
    EXPECT_DOUBLE_EQ(result[3].x, 100.0);
    EXPECT_DOUBLE_EQ(result[3].y, 200.0);
}

TEST_F(PopplerPathGetPointsTest_2130, LargeNumberOfPoints_2130) {
    const int count = 10000;
    PopplerPoint *pts = new PopplerPoint[count];
    for (int i = 0; i < count; i++) {
        pts[i].x = static_cast<double>(i);
        pts[i].y = static_cast<double>(i * 2);
    }

    PopplerPath path;
    path.points = pts;
    path.n_points = count;

    gsize n_points = 0;
    PopplerPoint *result = poppler_path_get_points(&path, &n_points);

    EXPECT_EQ(n_points, static_cast<gsize>(count));
    EXPECT_EQ(result, pts);
    EXPECT_DOUBLE_EQ(result[0].x, 0.0);
    EXPECT_DOUBLE_EQ(result[9999].x, 9999.0);
    EXPECT_DOUBLE_EQ(result[9999].y, 19998.0);

    delete[] pts;
}

TEST_F(PopplerPathGetPointsTest_2130, NPointsOutputOverwritesPreviousValue_2130) {
    PopplerPoint pts[2] = {{1.0, 1.0}, {2.0, 2.0}};
    PopplerPath path;
    path.points = pts;
    path.n_points = 2;

    gsize n_points = 42;
    poppler_path_get_points(&path, &n_points);

    EXPECT_EQ(n_points, 2u);
}

TEST_F(PopplerPathGetPointsTest_2130, NullPointsWithNonZeroCount_2130) {
    // Edge case: n_points set but points is null
    PopplerPath path;
    path.points = nullptr;
    path.n_points = 5;

    gsize n_points = 0;
    PopplerPoint *result = poppler_path_get_points(&path, &n_points);

    EXPECT_EQ(n_points, 5u);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerPathGetPointsTest_2130, ReturnsSamePointerOnMultipleCalls_2130) {
    PopplerPoint pts[2] = {{1.0, 2.0}, {3.0, 4.0}};
    PopplerPath path;
    path.points = pts;
    path.n_points = 2;

    gsize n1 = 0, n2 = 0;
    PopplerPoint *result1 = poppler_path_get_points(&path, &n1);
    PopplerPoint *result2 = poppler_path_get_points(&path, &n2);

    EXPECT_EQ(result1, result2);
    EXPECT_EQ(n1, n2);
}
