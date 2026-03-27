#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/controllers/rotation_averager.h"

#include "./TestProjects/glomap/glomap/scene/frame.h"

#include "./TestProjects/glomap/glomap/scene/image.h"

#include "./TestProjects/glomap/glomap/scene/image_pair.h"

#include "./TestProjects/glomap/glomap/scene/view_graph.h"



using namespace glomap;

using ::testing::_;

using ::testing::NiceMock;



// Mocking RotationEstimator

class MockRotationEstimator : public RotationEstimator {

public:

    MOCK_METHOD(bool, EstimateRotations, (const ViewGraph&, std::unordered_map<rig_t, Rig>&, std::unordered_map<frame_t, Frame>&, std::unordered_map<image_t, Image>&), (override));

};



// Test fixture for SolveRotationAveraging

class RotationAveragerTest_112 : public ::testing::Test {

protected:

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    RotationAveragerOptions options;



    NiceMock<MockRotationEstimator>* mock_rotation_estimator = new NiceMock<MockRotationEstimator>(options);



    void SetUp() override {

        // Initialize test data

        // Example initialization of view_graph, rigs, frames, and images

        // Add more if necessary for the tests

    }



    void TearDown() override {

        delete mock_rotation_estimator;

    }

};



// Test normal operation

TEST_F(RotationAveragerTest_112, NormalOperation_112) {

    EXPECT_CALL(*mock_rotation_estimator, EstimateRotations(_, _, _, _)).WillOnce(::testing::Return(true));

    bool result = SolveRotationAveraging(view_graph, rigs, frames, images, options);

    EXPECT_TRUE(result);

}



// Test boundary condition: no image pairs

TEST_F(RotationAveragerTest_112, NoImagePairs_112) {

    view_graph.image_pairs.clear();

    EXPECT_CALL(*mock_rotation_estimator, EstimateRotations(_, _, _, _)).WillOnce(::testing::Return(true));

    bool result = SolveRotationAveraging(view_graph, rigs, frames, images, options);

    EXPECT_TRUE(result);

}



// Test boundary condition: all image pairs invalid

TEST_F(RotationAveragerTest_112, AllImagePairsInvalid_112) {

    for (auto& [pair_id, image_pair] : view_graph.image_pairs) {

        image_pair.is_valid = false;

    }

    EXPECT_CALL(*mock_rotation_estimator, EstimateRotations(_, _, _, _)).WillOnce(::testing::Return(true));

    bool result = SolveRotationAveraging(view_graph, rigs, frames, images, options);

    EXPECT_TRUE(result);

}



// Test boundary condition: no registered images

TEST_F(RotationAveragerTest_112, NoRegisteredImages_112) {

    for (auto& [image_id, image] : images) {

        const_cast<Image&>(image).is_registered = false;

    }

    EXPECT_CALL(*mock_rotation_estimator, EstimateRotations(_, _, _, _)).WillOnce(::testing::Return(true));

    bool result = SolveRotationAveraging(view_graph, rigs, frames, images, options);

    EXPECT_TRUE(result);

}



// Test exceptional case: gravity pairs exceed threshold

TEST_F(RotationAveragerTest_112, GravityPairsExceedThreshold_112) {

    // Setup to have more than 95% of image pairs with gravity

    for (auto& [pair_id, image_pair] : view_graph.image_pairs) {

        if (!image_pair.is_valid) continue;

        const Image& image1 = images[image_pair.image_id1];

        const Image& image2 = images[image_pair.image_id2];

        if (!image1.IsRegistered() || !image2.IsRegistered()) continue;



        const_cast<Image&>(image1).gravity_info.has_gravity = true;

        const_cast<Image&>(image2).gravity_info.has_gravity = true;

    }

    EXPECT_CALL(*mock_rotation_estimator, EstimateRotations(_, _, _, _)).WillOnce(::testing::Return(true));

    bool result = SolveRotationAveraging(view_graph, rigs, frames, images, options);

    EXPECT_TRUE(result);

}



// Test exceptional case: Estimation failure

TEST_F(RotationAveragerTest_112, EstimationFailure_112) {

    EXPECT_CALL(*mock_rotation_estimator, EstimateRotations(_, _, _, _)).WillOnce(::testing::Return(false));

    bool result = SolveRotationAveraging(view_graph, rigs, frames, images, options);

    EXPECT_FALSE(result);

}
