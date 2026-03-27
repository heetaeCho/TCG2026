#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-annot.cc"

#include "./TestProjects/poppler/glib/poppler-page.h"



struct PopplerPath {

    PopplerPoint *points;

    gsize n_points;

};



TEST(PopplerPathTest_2127, CreatePathWithValidPoints_2127) {

    PopplerPoint points[] = {{0.0, 0.0}, {1.0, 1.0}};

    gsize n_points = sizeof(points) / sizeof(points[0]);

    PopplerPath *path = poppler_path_new_from_array(points, n_points);



    ASSERT_NE(path, nullptr);

    EXPECT_EQ(path->points, points);

    EXPECT_EQ(path->n_points, n_points);



    g_free(path);

}



TEST(PopplerPathTest_2127, CreatePathWithNoPoints_2127) {

    PopplerPoint *points = nullptr;

    gsize n_points = 0;

    PopplerPath *path = poppler_path_new_from_array(points, n_points);



    ASSERT_NE(path, nullptr);

    EXPECT_EQ(path->points, points);

    EXPECT_EQ(path->n_points, n_points);



    g_free(path);

}



TEST(PopplerPathTest_2127, CreatePathWithSinglePoint_2127) {

    PopplerPoint points[] = {{0.5, 0.5}};

    gsize n_points = sizeof(points) / sizeof(points[0]);

    PopplerPath *path = poppler_path_new_from_array(points, n_points);



    ASSERT_NE(path, nullptr);

    EXPECT_EQ(path->points, points);

    EXPECT_EQ(path->n_points, n_points);



    g_free(path);

}
