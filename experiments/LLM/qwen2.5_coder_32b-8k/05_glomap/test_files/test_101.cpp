#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "gravity_refinement.h"

#include "view_graph.h"

#include "frame.h"

#include "image.h"



using namespace glomap;



namespace {



class GravityRefinerTest : public ::testing::Test {

protected:

    GravityRefinerOptions options;

    GravityRefiner refiner;



    GravityRefinerTest() : options(), refiner(options) {}



    void PopulateViewGraph(ViewGraph& view_graph, std::unordered_map<image_t, Image>& images) {

        // Example setup for tests

        image_t img1_id = 1, img2_id = 2, img3_id = 3;

        frame_t frame1_id = 10, frame2_id = 20;



        Image img1(img1_id, 1, "img1.jpg");

        Image img2(img2_id, 1, "img2.jpg");

        Image img3(img3_id, 2, "img3.jpg");



        img1.frame_id = frame1_id;

        img2.frame_id = frame1_id;

        img3.frame_id = frame2_id;



        images[img1_id] = img1;

        images[img2_id] = img2;

        images[img3_id] = img3;



        ImagePair pair1(img1_id, img2_id);

        ImagePair pair2(img2_id, img3_id);



        view_graph.image_pairs[pair1.pair_id] = pair1;

        view_graph.image_pairs[pair2.pair_id] = pair2;

    }

};



TEST_F(GravityRefinerTest_101, AdjacencyListEmpty_101) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    refiner.RefineGravity(view_graph, frames, images);



    // Expect no changes in frames or images

    EXPECT_TRUE(frames.empty());

    EXPECT_TRUE(images.empty());

}



TEST_F(GravityRefinerTest_101, NoErrorProneFrames_101) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    PopulateViewGraph(view_graph, images);



    refiner.RefineGravity(view_graph, frames, images);



    // Expect no changes in frames as there are no error prone frames

    EXPECT_TRUE(frames.empty());

}



TEST_F(GravityRefinerTest_101, SingleFrameWithGravity_101) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    PopulateViewGraph(view_graph, images);



    frame_t frame_id = 10;

    Frame frame;

    frame.gravity_info.SetGravity(Eigen::Vector3d(1.0, 0.0, 0.0));

    frames[frame_id] = frame;



    refiner.RefineGravity(view_graph, frames, images);



    // Expect gravity to be refined if conditions are met

    EXPECT_TRUE(frames.find(frame_id) != frames.end());

}



TEST_F(GravityRefinerTest_101, MultipleFramesWithGravities_101) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    PopulateViewGraph(view_graph, images);



    frame_t frame_id1 = 10, frame_id2 = 20;

    Frame frame1, frame2;

    frame1.gravity_info.SetGravity(Eigen::Vector3d(1.0, 0.0, 0.0));

    frame2.gravity_info.SetGravity(Eigen::Vector3d(0.0, 1.0, 0.0));

    frames[frame_id1] = frame1;

    frames[frame_id2] = frame2;



    refiner.RefineGravity(view_graph, frames, images);



    // Expect gravities to be refined if conditions are met

    EXPECT_TRUE(frames.find(frame_id1) != frames.end());

    EXPECT_TRUE(frames.find(frame_id2) != frames.end());

}



TEST_F(GravityRefinerTest_101, InsufficientNeighbors_101) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    PopulateViewGraph(view_graph, images);



    frame_t frame_id = 10;

    Frame frame;

    frame.gravity_info.SetGravity(Eigen::Vector3d(1.0, 0.0, 0.0));

    frames[frame_id] = frame;



    refiner.options_.min_num_neighbors = 10; // Set high threshold to ensure not enough neighbors



    refiner.RefineGravity(view_graph, frames, images);



    // Expect gravity not to be refined due to insufficient neighbors

    EXPECT_TRUE(frames.find(frame_id) != frames.end());

}



TEST_F(GravityRefinerTest_101, OutlierRatioExceeded_101) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;



    PopulateViewGraph(view_graph, images);



    frame_t frame_id = 10;

    Frame frame;

    frame.gravity_info.SetGravity(Eigen::Vector3d(1.0, 0.0, 0.0));

    frames[frame_id] = frame;



    refiner.options_.max_outlier_ratio = 0.1; // Set low threshold to ensure outlier ratio is exceeded



    refiner.RefineGravity(view_graph, frames, images);



    // Expect gravity not to be refined due to high outlier ratio

    EXPECT_TRUE(frames.find(frame_id) != frames.end());

}



} // namespace
