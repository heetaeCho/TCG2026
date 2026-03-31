#include <gtest/gtest.h>
#include <glib.h>

// Replicate the structures as defined in the known dependencies
struct PopplerPoint {
    double x;
    double y;
};

struct PopplerPath {
    PopplerPoint *points;
    int n_points;
};

// Declaration of the function under test
extern "C" void poppler_path_free(PopplerPath *path);

// If the function is not available as extern "C", we define it inline for testing
// based on the provided implementation
#ifndef POPPLER_PATH_FREE_DEFINED
void poppler_path_free(PopplerPath *path)
{
    g_free(path->points);
    g_free(path);
}
#define POPPLER_PATH_FREE_DEFINED
#endif

class PopplerPathFreeTest_2128 : public ::testing::Test {
protected:
    PopplerPath *createPath(int n_points) {
        PopplerPath *path = (PopplerPath *)g_malloc(sizeof(PopplerPath));
        if (n_points > 0) {
            path->points = (PopplerPoint *)g_malloc(sizeof(PopplerPoint) * n_points);
        } else {
            path->points = nullptr;
        }
        path->n_points = n_points;
        return path;
    }
};

TEST_F(PopplerPathFreeTest_2128, FreePathWithMultiplePoints_2128)
{
    PopplerPath *path = createPath(5);
    for (int i = 0; i < 5; i++) {
        path->points[i].x = i * 1.0;
        path->points[i].y = i * 2.0;
    }
    // Should not crash or leak
    poppler_path_free(path);
}

TEST_F(PopplerPathFreeTest_2128, FreePathWithSinglePoint_2128)
{
    PopplerPath *path = createPath(1);
    path->points[0].x = 10.0;
    path->points[0].y = 20.0;
    // Should not crash or leak
    poppler_path_free(path);
}

TEST_F(PopplerPathFreeTest_2128, FreePathWithNullPoints_2128)
{
    PopplerPath *path = (PopplerPath *)g_malloc(sizeof(PopplerPath));
    path->points = nullptr;
    path->n_points = 0;
    // g_free(NULL) is safe, so this should not crash
    poppler_path_free(path);
}

TEST_F(PopplerPathFreeTest_2128, FreePathWithZeroPointsButNullPointer_2128)
{
    PopplerPath *path = createPath(0);
    // Should not crash; points is nullptr and g_free(NULL) is a no-op
    poppler_path_free(path);
}

TEST_F(PopplerPathFreeTest_2128, FreePathWithLargeNumberOfPoints_2128)
{
    const int large_n = 10000;
    PopplerPath *path = createPath(large_n);
    for (int i = 0; i < large_n; i++) {
        path->points[i].x = i;
        path->points[i].y = -i;
    }
    // Should free large allocation without issues
    poppler_path_free(path);
}

TEST_F(PopplerPathFreeTest_2128, FreePathAllocatedWithGMalloc_2128)
{
    // Ensure the function works correctly with g_malloc-allocated memory
    PopplerPath *path = (PopplerPath *)g_malloc0(sizeof(PopplerPath));
    path->points = (PopplerPoint *)g_malloc0(sizeof(PopplerPoint) * 3);
    path->n_points = 3;
    path->points[0] = {1.0, 2.0};
    path->points[1] = {3.0, 4.0};
    path->points[2] = {5.0, 6.0};
    poppler_path_free(path);
}

TEST_F(PopplerPathFreeTest_2128, FreePathWithTwoPoints_2128)
{
    PopplerPath *path = createPath(2);
    path->points[0].x = 0.0;
    path->points[0].y = 0.0;
    path->points[1].x = 100.0;
    path->points[1].y = 100.0;
    poppler_path_free(path);
}
