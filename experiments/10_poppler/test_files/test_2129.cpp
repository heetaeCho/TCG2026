#include <gtest/gtest.h>

#include "poppler-annot.cc"

#include "poppler-private.h"



class PopplerPathTest_2129 : public ::testing::Test {

protected:

    void SetUp() override {

        path = g_new(PopplerPath, 1);

        path->n_points = 3;

        path->points = g_new(PopplerPoint, path->n_points);

        for (int i = 0; i < path->n_points; ++i) {

            path->points[i].x = static_cast<double>(i);

            path->points[i].y = static_cast<double>(i * 2);

        }

    }



    void TearDown() override {

        g_free(path->points);

        g_free(path);

    }



    PopplerPath* path;

};



TEST_F(PopplerPathTest_2129, CopyCreatesNewInstance_2129) {

    PopplerPath* new_path = poppler_path_copy(path);

    EXPECT_NE(new_path, path);

    g_free(new_path->points);

    g_free(new_path);

}



TEST_F(PopplerPathTest_2129, CopyPreservesNumberOfPoints_2129) {

    PopplerPath* new_path = poppler_path_copy(path);

    EXPECT_EQ(new_path->n_points, path->n_points);

    g_free(new_path->points);

    g_free(new_path);

}



TEST_F(PopplerPathTest_2129, CopyPreservesPointValues_2129) {

    PopplerPath* new_path = poppler_path_copy(path);

    for (int i = 0; i < path->n_points; ++i) {

        EXPECT_EQ(new_path->points[i].x, path->points[i].x);

        EXPECT_EQ(new_path->points[i].y, path->points[i].y);

    }

    g_free(new_path->points);

    g_free(new_path);

}



TEST_F(PopplerPathTest_2129, CopyHandlesZeroPoints_2129) {

    path->n_points = 0;

    PopplerPath* new_path = poppler_path_copy(path);

    EXPECT_EQ(new_path->n_points, 0);

    g_free(new_path->points);

    g_free(new_path);

}



TEST_F(PopplerPathTest_2129, CopyHandlesSinglePoint_2129) {

    path->n_points = 1;

    PopplerPath* new_path = poppler_path_copy(path);

    EXPECT_EQ(new_path->n_points, 1);

    EXPECT_EQ(new_path->points[0].x, path->points[0].x);

    EXPECT_EQ(new_path->points[0].y, path->points[0].y);

    g_free(new_path->points);

    g_free(new_path);

}
