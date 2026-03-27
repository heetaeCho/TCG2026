#include <gtest/gtest.h>

#include "poppler-annot.cc"

#include "poppler-private.h"



// Test fixture for PopplerPath related tests

class PopplerPathTest : public ::testing::Test {

protected:

    void SetUp() override {

        path = new _PopplerPath();

    }



    void TearDown() override {

        delete path;

    }



    _PopplerPath* path;

};



TEST_F(PopplerPathTest_2130, GetPoints_ReturnsNullForZeroPoints_2130) {

    path->points = nullptr;

    path->n_points = 0;



    gsize n_points = 1; // Initialize to non-zero to check if it gets updated

    PopplerPoint* points = poppler_path_get_points(path, &n_points);



    EXPECT_EQ(points, nullptr);

    EXPECT_EQ(n_points, 0);

}



TEST_F(PopplerPathTest_2130, GetPoints_ReturnsCorrectPointerAndCount_2130) {

    const int numPoints = 5;

    path->points = new PopplerPoint[numPoints];

    path->n_points = numPoints;



    gsize n_points = 0;

    PopplerPoint* points = poppler_path_get_points(path, &n_points);



    EXPECT_EQ(points, path->points);

    EXPECT_EQ(n_points, static_cast<gsize>(numPoints));



    delete[] path->points; // Clean up allocated points

}



TEST_F(PopplerPathTest_2130, GetPoints_ReturnsSamePointerForMultipleCalls_2130) {

    const int numPoints = 3;

    path->points = new PopplerPoint[numPoints];

    path->n_points = numPoints;



    gsize n_points1 = 0;

    PopplerPoint* points1 = poppler_path_get_points(path, &n_points1);



    gsize n_points2 = 0;

    PopplerPoint* points2 = poppler_path_get_points(path, &n_points2);



    EXPECT_EQ(points1, points2);

    EXPECT_EQ(n_points1, n_points2);



    delete[] path->points; // Clean up allocated points

}



TEST_F(PopplerPathTest_2130, GetPoints_HandlesNullNPointsPointer_2130) {

    const int numPoints = 4;

    path->points = new PopplerPoint[numPoints];

    path->n_points = numPoints;



    // Passing nullptr for n_points should not cause any issues

    PopplerPoint* points = poppler_path_get_points(path, nullptr);



    EXPECT_EQ(points, path->points);



    delete[] path->points; // Clean up allocated points

}
