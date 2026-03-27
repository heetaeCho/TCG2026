#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/processors/view_graph_manipulation.h"

#include "TestProjects/glomap/glomap/scene/image.h"

#include "TestProjects/glomap/glomap/scene/image_pair.h"

#include "TestProjects/glomap/glomap/scene/view_graph.h"



using namespace glomap;

using namespace testing;



// Test fixture for ViewGraphManipulater tests

class ViewGraphManipulaterTest_160 : public ::testing::Test {

protected:

    ViewGraphManipulater manipulator;

    ViewGraph view_graph;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<image_t, Image> images;



    void SetUp() override {

        // Setup some default valid image pairs and cameras for testing

        images[1] = Image(1, 10, "image1.jpg");

        images[2] = Image(2, 20, "image2.jpg");

        images[3] = Image(3, 10, "image3.jpg");



        Camera camera1;

        Camera camera2;

        camera1.has_prior_focal_length = true;

        camera2.has_prior_focal_length = false;



        cameras[10] = camera1;

        cameras[20] = camera2;



        ImagePair pair1(1, 2);

        ImagePair pair2(2, 3);



        view_graph.image_pairs[pair1.pair_id] = pair1;

        view_graph.image_pairs[pair2.pair_id] = pair2;

    }

};



TEST_F(ViewGraphManipulaterTest_160, DecomposeRelPose_NoValidPairs_160) {

    // All pairs are invalid due to missing focal length

    cameras[10].has_prior_focal_length = false;



    manipulator.DecomposeRelPose(view_graph, cameras, images);



    for (auto& [pair_id, image_pair] : view_graph.image_pairs) {

        EXPECT_EQ(image_pair.config, colmap::TwoViewGeometry::UNDEFINED);

    }

}



TEST_F(ViewGraphManipulaterTest_160, DecomposeRelPose_OneValidPair_160) {

    // Only pair (1, 3) is valid

    cameras[20].has_prior_focal_length = true;



    manipulator.DecomposeRelPose(view_graph, cameras, images);



    EXPECT_EQ(view_graph.image_pairs.begin()->second.config, colmap::TwoViewGeometry::UNDEFINED);

    EXPECT_NE(view_graph.image_pairs.rbegin()->second.config, colmap::TwoViewGeometry::UNDEFINED);

}



TEST_F(ViewGraphManipulaterTest_160, DecomposeRelPose_AllPairsValid_160) {

    // All pairs are valid

    cameras[20].has_prior_focal_length = true;



    manipulator.DecomposeRelPose(view_graph, cameras, images);



    for (auto& [pair_id, image_pair] : view_graph.image_pairs) {

        EXPECT_NE(image_pair.config, colmap::TwoViewGeometry::UNDEFINED);

    }

}



TEST_F(ViewGraphManipulaterTest_160, DecomposeRelPose_PlanarConfiguration_160) {

    // Set up a planar configuration scenario

    cameras[20].has_prior_focal_length = true;



    for (auto& [pair_id, image_pair] : view_graph.image_pairs) {

        image_pair.config = colmap::TwoViewGeometry::PLANAR;

    }



    manipulator.DecomposeRelPose(view_graph, cameras, images);



    for (auto& [pair_id, image_pair] : view_graph.image_pairs) {

        EXPECT_EQ(image_pair.config, colmap::TwoViewGeometry::CALIBRATED);

    }

}



TEST_F(ViewGraphManipulaterTest_160, DecomposeRelPose_TranslationNormalization_160) {

    // Set up a scenario where translation needs normalization

    cameras[20].has_prior_focal_length = true;



    for (auto& [pair_id, image_pair] : view_graph.image_pairs) {

        image_pair.cam2_from_cam1.translation << 1.0, 2.0, 3.0;

    }



    manipulator.DecomposeRelPose(view_graph, cameras, images);



    for (auto& [pair_id, image_pair] : view_graph.image_pairs) {

        EXPECT_DOUBLE_EQ(image_pair.cam2_from_cam1.translation.norm(), 1.0);

    }

}
