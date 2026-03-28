#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "TestProjects/glomap/glomap/estimators/global_rotation_averaging.h"

#include "TestProjects/glomap/glomap/scene/view_graph.h"



using namespace glomap;

using ::testing::_;

using ::testing::Return;



class RotationEstimatorTest : public ::testing::Test {

protected:

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    RotationEstimatorOptions options;

    RotationEstimator estimator;



    RotationEstimatorTest() : options(), estimator(options) {}



    void SetUp() override {

        // Initialize view_graph, frames, and images with minimal data for testing

        view_graph.image_pairs = 1;

        image_t img_id1 = 0, img_id2 = 1;

        frame_t frame_id1 = 0, frame_id2 = 1;

        ImagePair pair_info;

        view_graph.image_pairs[{img_id1, img_id2}] = pair_info;



        Frame frame1, frame2;

        frames[frame_id1] = frame1;

        frames[frame_id2] = frame2;



        Image image1, image2;

        images[img_id1] = image1;

        images[img_id2] = image2;

    }

};



TEST_F(RotationEstimatorTest_30, SolveIRLS_Success_30) {

    // Arrange: Setup view_graph, frames, and images with valid data



    // Act: Call the function under test

    bool result = estimator.SolveIRLS(view_graph, frames, images);



    // Assert: Check if the function returns true indicating success

    EXPECT_TRUE(result);

}



TEST_F(RotationEstimatorTest_30, SolveIRLS_MaxIterationsReached_30) {

    // Arrange: Setup view_graph, frames, and images with data that requires max iterations



    // Modify options to control iteration behavior

    options.max_num_irls_iterations = 1;

    RotationEstimator limited_estimator(options);



    // Act: Call the function under test

    bool result = limited_estimator.SolveIRLS(view_graph, frames, images);



    // Assert: Check if the function returns true even when max iterations are reached

    EXPECT_TRUE(result);

}



TEST_F(RotationEstimatorTest_30, SolveIRLS_NanWeight_30) {

    // Arrange: Setup view_graph, frames, and images with data that causes NaN weight



    // Modify residual to cause NaN weight

    estimator.tangent_space_residual_.setConstant(std::numeric_limits<double>::quiet_NaN());



    // Act: Call the function under test

    bool result = estimator.SolveIRLS(view_graph, frames, images);



    // Assert: Check if the function returns false due to NaN weight

    EXPECT_FALSE(result);

}



TEST_F(RotationEstimatorTest_30, SolveIRLS_NoImagePairs_30) {

    // Arrange: Setup view_graph with no image pairs



    // Clear image_pairs

    view_graph.image_pairs.clear();



    // Act: Call the function under test

    bool result = estimator.SolveIRLS(view_graph, frames, images);



    // Assert: Check if the function returns false or handles gracefully

    EXPECT_FALSE(result);

}



TEST_F(RotationEstimatorTest_30, SolveIRLS_GravityEnabled_NoGravityInImage_30) {

    // Arrange: Setup view_graph, frames, and images with gravity enabled but no gravity in image



    // Enable gravity

    options.use_gravity = true;



    // Act: Call the function under test

    bool result = estimator.SolveIRLS(view_graph, frames, images);



    // Assert: Check if the function handles gracefully without crashing

    EXPECT_TRUE(result);

}



TEST_F(RotationEstimatorTest_30, SolveIRLS_GravityEnabled_GravityInImage_30) {

    // Arrange: Setup view_graph, frames, and images with gravity enabled and gravity in image



    // Enable gravity

    options.use_gravity = true;



    // Set gravity flag in the first image

    images[0].SetGravity(true);



    // Act: Call the function under test

    bool result = estimator.SolveIRLS(view_graph, frames, images);



    // Assert: Check if the function handles gracefully without crashing

    EXPECT_TRUE(result);

}



TEST_F(RotationEstimatorTest_30, SolveIRLS_HalfNormWeightType_30) {

    // Arrange: Setup view_graph, frames, and images with half norm weight type



    // Set weight type to Half Norm

    options.weight_type = RotationEstimatorOptions::HALF_NORM;



    // Act: Call the function under test

    bool result = estimator.SolveIRLS(view_graph, frames, images);



    // Assert: Check if the function handles gracefully without crashing

    EXPECT_TRUE(result);

}
