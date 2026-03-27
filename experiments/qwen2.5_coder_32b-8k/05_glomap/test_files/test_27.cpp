#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/estimators/global_rotation_averaging.h"

#include "glomap/scene/image_pair.h"

#include "glomap/scene/view_graph.h"



using namespace glomap;

using ::testing::ElementsAre;



class RotationEstimatorTest : public ::testing::Test {

protected:

    RotationEstimatorOptions options;

    RotationEstimator estimator{options};

};



TEST_F(RotationEstimatorTest_27, InitializeFromMaximumSpanningTree_EmptyGraph_27) {

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    estimator.InitializeFromMaximumSpanningTree(view_graph, rigs, frames, images);



    EXPECT_TRUE(rigs.empty());

    EXPECT_TRUE(frames.empty());

    EXPECT_TRUE(images.empty());

}



TEST_F(RotationEstimatorTest_27, InitializeFromMaximumSpanningTree_SingleImage_27) {

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    Image image{1};

    image.SetRegistered(true);

    std::unordered_map<image_t, Image> images{{1, image}};



    estimator.InitializeFromMaximumSpanningTree(view_graph, rigs, frames, images);



    EXPECT_TRUE(rigs.empty());

    EXPECT_TRUE(frames.empty());

    EXPECT_EQ(images.size(), 1);

}



TEST_F(RotationEstimatorTest_27, InitializeFromMaximumSpanningTree_TwoConnectedImages_27) {

    ViewGraph view_graph;

    ImagePair image_pair{1, 2};

    image_pair.cam2_from_cam1 = Rigid3d::Identity();

    view_graph.image_pairs[ImagePairToPairId(1, 2)] = image_pair;



    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    Image image1{1}, image2{2};

    image1.SetRegistered(true);

    image2.SetRegistered(true);

    std::unordered_map<image_t, Image> images{{1, image1}, {2, image2}};



    estimator.InitializeFromMaximumSpanningTree(view_graph, rigs, frames, images);



    EXPECT_TRUE(rigs.empty());

    EXPECT_TRUE(frames.empty());

    EXPECT_EQ(images.size(), 2);

}



TEST_F(RotationEstimatorTest_27, InitializeFromMaximumSpanningTree_UnregisteredImages_27) {

    ViewGraph view_graph;

    ImagePair image_pair{1, 2};

    image_pair.cam2_from_cam1 = Rigid3d::Identity();

    view_graph.image_pairs[ImagePairToPairId(1, 2)] = image_pair;



    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    Image image1{1}, image2{2};

    // Both images are unregistered

    std::unordered_map<image_t, Image> images{{1, image1}, {2, image2}};



    estimator.InitializeFromMaximumSpanningTree(view_graph, rigs, frames, images);



    EXPECT_TRUE(rigs.empty());

    EXPECT_TRUE(frames.empty());

    EXPECT_EQ(images.size(), 2);

}



TEST_F(RotationEstimatorTest_27, InitializeFromMaximumSpanningTree_MaximumSpanningTreeErrorHandling_27) {

    // Assuming MaximumSpanningTree throws an exception in some error case

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    // This is a placeholder for the actual error condition

    EXPECT_THROW(estimator.InitializeFromMaximumSpanningTree(view_graph, rigs, frames, images), std::exception);

}



TEST_F(RotationEstimatorTest_27, InitializeFromMaximumSpanningTree_LargeGraph_27) {

    ViewGraph view_graph;

    for (int i = 0; i < 100; ++i) {

        for (int j = i + 1; j < 100; ++j) {

            ImagePair image_pair{i, j};

            image_pair.cam2_from_cam1 = Rigid3d::Identity();

            view_graph.image_pairs[ImagePairToPairId(i, j)] = image_pair;

        }

    }



    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<frame_t, Frame> frames;

    for (int i = 0; i < 100; ++i) {

        Image image{i};

        image.SetRegistered(true);

        images[i] = image;

    }



    estimator.InitializeFromMaximumSpanningTree(view_graph, rigs, frames, images);



    EXPECT_TRUE(rigs.empty());

    EXPECT_TRUE(frames.empty());

    EXPECT_EQ(images.size(), 100);

}
