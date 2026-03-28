#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "view_graph_manipulation.h"

#include "image.h"

#include "image_pair.h"

#include "view_graph.h"



using namespace glomap;



class ViewGraphManipulaterTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize test data

        view_graph.image_pairs = {

            {1, ImagePair(1, 2)},

            {2, ImagePair(2, 3)},

            {3, ImagePair(3, 4)}

        };



        images = {

            {1, Image(1, 10, "image1")},

            {2, Image(2, 10, "image2")},

            {3, Image(3, 20, "image3")},

            {4, Image(4, 20, "image4")}

        };



        cameras = {

            {10, Camera()},

            {20, Camera()}

        };

    }



    ViewGraph view_graph;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<image_t, Image> images;

};



TEST_F(ViewGraphManipulaterTest_159, UpdateImagePairsConfig_NoValidPairs_159) {

    for (auto& [pair_id, image_pair] : view_graph.image_pairs) {

        image_pair.is_valid = false;

    }



    ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);



    for (const auto& [pair_id, image_pair] : view_graph.image_pairs) {

        EXPECT_EQ(image_pair.config, colmap::TwoViewGeometry::UNDEFINED);

    }

}



TEST_F(ViewGraphManipulaterTest_159, UpdateImagePairsConfig_AllUncalibratedPairs_159) {

    for (auto& [pair_id, image_pair] : view_graph.image_pairs) {

        image_pair.config = colmap::TwoViewGeometry::UNCALIBRATED;

    }



    ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);



    EXPECT_EQ(view_graph.image_pairs[1].config, colmap::TwoViewGeometry::CALIBRATED);

    EXPECT_EQ(view_graph.image_pairs[2].config, colmap::TwoViewGeometry::UNCALIBRATED); // Different camera

    EXPECT_EQ(view_graph.image_pairs[3].config, colmap::TwoViewGeometry::CALIBRATED);

}



TEST_F(ViewGraphManipulaterTest_159, UpdateImagePairsConfig_AllCalibratedPairs_159) {

    for (auto& [pair_id, image_pair] : view_graph.image_pairs) {

        image_pair.config = colmap::TwoViewGeometry::CALIBRATED;

    }



    ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);



    EXPECT_EQ(view_graph.image_pairs[1].config, colmap::TwoViewGeometry::CALIBRATED);

    EXPECT_EQ(view_graph.image_pairs[2].config, colmap::TwoViewGeometry::CALIBRATED); // Same camera

    EXPECT_EQ(view_graph.image_pairs[3].config, colmap::TwoViewGeometry::CALIBRATED);

}



TEST_F(ViewGraphManipulaterTest_159, UpdateImagePairsConfig_MixedPairs_159) {

    view_graph.image_pairs[1].config = colmap::TwoViewGeometry::UNCALIBRATED;

    view_graph.image_pairs[2].config = colmap::TwoViewGeometry::CALIBRATED;



    ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);



    EXPECT_EQ(view_graph.image_pairs[1].config, colmap::TwoViewGeometry::CALIBRATED); // Valid calibration

    EXPECT_EQ(view_graph.image_pairs[2].config, colmap::TwoViewGeometry::CALIBRATED);

}



TEST_F(ViewGraphManipulaterTest_159, UpdateImagePairsConfig_CameraWithoutPriorFocalLength_159) {

    cameras[10].has_prior_focal_length = false;



    ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);



    EXPECT_EQ(view_graph.image_pairs[1].config, colmap::TwoViewGeometry::UNCALIBRATED); // Invalid calibration

}



TEST_F(ViewGraphManipulaterTest_159, UpdateImagePairsConfig_CameraWithValidFocalLengths_159) {

    cameras[10].has_prior_focal_length = true;

    cameras[20].has_prior_focal_length = true;



    ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);



    EXPECT_EQ(view_graph.image_pairs[1].config, colmap::TwoViewGeometry::CALIBRATED); // Valid calibration

}
