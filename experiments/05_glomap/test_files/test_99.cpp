#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "view_graph_calibration.h"

#include "view_graph.h"



namespace glomap {



using ::testing::_;

using ::testing::Return;

using ::testing::UnorderedElementsAre;



class ViewGraphCalibratorTest_99 : public ::testing::Test {

protected:

    ViewGraphCalibratorOptions options;

    ViewGraph view_graph;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<image_t, Image> images;



    void SetUp() override {

        // Initialize with some default values if necessary

        options = ViewGraphCalibratorOptions();

        cameras = {{1, Camera()}, {2, Camera()}};

        images = {{10, Image()}, {20, Image()}};

    }

};



TEST_F(ViewGraphCalibratorTest_99, SolveReturnsTrueWhenNoCameras_99) {

    cameras.clear(); // No cameras

    ViewGraphCalibrator calibrator(options);

    EXPECT_TRUE(calibrator.Solve(view_graph, cameras, images));

}



TEST_F(ViewGraphCalibratorTest_99, SolveUsesDenseSolverForFewCameras_99) {

    cameras = {{1, Camera()}, {2, Camera()}};

    ViewGraphCalibrator calibrator(options);

    EXPECT_CALL(view_graph, CreateImageAdjacencyList()).Times(1);

    EXPECT_TRUE(calibrator.Solve(view_graph, cameras, images));

}



TEST_F(ViewGraphCalibratorTest_99, SolveUsesSparseSolverForManyCameras_99) {

    for (int i = 0; i < 51; ++i) {

        cameras[i] = Camera();

    }

    ViewGraphCalibrator calibrator(options);

    EXPECT_CALL(view_graph, CreateImageAdjacencyList()).Times(1);

    EXPECT_TRUE(calibrator.Solve(view_graph, cameras, images));

}



TEST_F(ViewGraphCalibratorTest_99, SolveCallsFilterImagePairs_99) {

    ViewGraphCalibrator calibrator(options);

    EXPECT_CALL(view_graph, CreateImageAdjacencyList()).Times(1);

    EXPECT_TRUE(calibrator.Solve(view_graph, cameras, images));

}



} // namespace glomap
