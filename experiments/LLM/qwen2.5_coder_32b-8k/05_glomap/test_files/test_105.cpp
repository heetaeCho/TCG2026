#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/estimators/global_positioning.h"

#include "glomap/scene/view_graph.h"

#include "glomap/scene/image.h"

#include "glomap/scene/image_pair.h"

#include "glomap/scene/track.h"



namespace glomap {

namespace {



using ::testing::ElementsAre;

using ::testing::Pair;



class GlobalPositionerTest_105 : public ::testing::Test {

protected:

    void SetUp() override {

        options.generate_random_positions = true;

        options.optimize_positions = true;

        global_positioner = std::make_unique<GlobalPositioner>(options);

    }



    GlobalPositionerOptions options;

    std::unique_ptr<GlobalPositioner> global_positioner;

};



TEST_F(GlobalPositionerTest_105, InitializeRandomPositions_NoConstraints_105) {

    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}, {2, Frame()}};

    std::unordered_map<image_t, Image> images = {{1, Image(1, 1, "img1")}, {2, Image(2, 2, "img2")}};

    std::unordered_map<track_t, Track> tracks;



    global_positioner->InitializeRandomPositions(view_graph, frames, images, tracks);



    EXPECT_NE(frames[1].RigFromWorld().translation.x(), 0.0);

    EXPECT_NE(frames[1].RigFromWorld().translation.y(), 0.0);

    EXPECT_NE(frames[1].RigFromWorld().translation.z(), 0.0);

    EXPECT_NE(frames[2].RigFromWorld().translation.x(), 0.0);

    EXPECT_NE(frames[2].RigFromWorld().translation.y(), 0.0);

    EXPECT_NE(frames[2].RigFromWorld().translation.z(), 0.0);

}



TEST_F(GlobalPositionerTest_105, InitializeRandomPositions_ConstrainedByImagePair_105) {

    ViewGraph view_graph;

    Image image1(1, 1, "img1");

    Image image2(2, 2, "img2");

    Frame frame1;

    Frame frame2;



    image1.frame_id = 1;

    image2.frame_id = 2;

    image1.frame_ptr = &frame1;

    image2.frame_ptr = &frame2;



    view_graph.image_pairs[0] = ImagePair(1, 2);

    std::unordered_map<frame_t, Frame> frames = {{1, frame1}, {2, frame2}};

    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}};

    std::unordered_map<track_t, Track> tracks;



    global_positioner->InitializeRandomPositions(view_graph, frames, images, tracks);



    EXPECT_EQ(frames[1].RigFromWorld().translation.x(), CenterFromPose(frames[1].RigFromWorld()).x());

    EXPECT_EQ(frames[1].RigFromWorld().translation.y(), CenterFromPose(frames[1].RigFromWorld()).y());

    EXPECT_EQ(frames[1].RigFromWorld().translation.z(), CenterFromPose(frames[1].RigFromWorld()).z());

    EXPECT_EQ(frames[2].RigFromWorld().translation.x(), CenterFromPose(frames[2].RigFromWorld()).x());

    EXPECT_EQ(frames[2].RigFromWorld().translation.y(), CenterFromPose(frames[2].RigFromWorld()).y());

    EXPECT_EQ(frames[2].RigFromWorld().translation.z(), CenterFromPose(frames[2].RigFromWorld()).z());

}



TEST_F(GlobalPositionerTest_105, InitializeRandomPositions_ConstrainedByTrackObservation_105) {

    ViewGraph view_graph;

    Image image1(1, 1, "img1");

    Frame frame1;



    image1.frame_id = 1;

    image1.frame_ptr = &frame1;



    Track track;

    track.observations.emplace_back(image_t(1), feature_t(1));

    std::unordered_map<frame_t, Frame> frames = {{1, frame1}};

    std::unordered_map<image_t, Image> images = {{1, image1}};

    std::unordered_map<track_t, Track> tracks = {{1, track}};



    global_positioner->InitializeRandomPositions(view_graph, frames, images, tracks);



    EXPECT_EQ(frames[1].RigFromWorld().translation.x(), CenterFromPose(frames[1].RigFromWorld()).x());

    EXPECT_EQ(frames[1].RigFromWorld().translation.y(), CenterFromPose(frames[1].RigFromWorld()).y());

    EXPECT_EQ(frames[1].RigFromWorld().translation.z(), CenterFromPose(frames[1].RigFromWorld()).z());

}



TEST_F(GlobalPositionerTest_105, InitializeRandomPositions_NoGenerateRandomPositions_105) {

    options.generate_random_positions = false;

    global_positioner = std::make_unique<GlobalPositioner>(options);



    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}, {2, Frame()}};

    std::unordered_map<image_t, Image> images = {{1, Image(1, 1, "img1")}, {2, Image(2, 2, "img2")}};

    std::unordered_map<track_t, Track> tracks;



    global_positioner->InitializeRandomPositions(view_graph, frames, images, tracks);



    EXPECT_EQ(frames[1].RigFromWorld().translation.x(), CenterFromPose(frames[1].RigFromWorld()).x());

    EXPECT_EQ(frames[1].RigFromWorld().translation.y(), CenterFromPose(frames[1].RigFromWorld()).y());

    EXPECT_EQ(frames[1].RigFromWorld().translation.z(), CenterFromPose(frames[1].RigFromWorld()).z());

    EXPECT_EQ(frames[2].RigFromWorld().translation.x(), CenterFromPose(frames[2].RigFromWorld()).x());

    EXPECT_EQ(frames[2].RigFromWorld().translation.y(), CenterFromPose(frames[2].RigFromWorld()).y());

    EXPECT_EQ(frames[2].RigFromWorld().translation.z(), CenterFromPose(frames[2].RigFromWorld()).z());

}



TEST_F(GlobalPositionerTest_105, InitializeRandomPositions_NoOptimizePositions_105) {

    options.optimize_positions = false;

    global_positioner = std::make_unique<GlobalPositioner>(options);



    ViewGraph view_graph;

    std::unordered_map<frame_t, Frame> frames = {{1, Frame()}, {2, Frame()}};

    std::unordered_map<image_t, Image> images = {{1, Image(1, 1, "img1")}, {2, Image(2, 2, "img2")}};

    std::unordered_map<track_t, Track> tracks;



    global_positioner->InitializeRandomPositions(view_graph, frames, images, tracks);



    EXPECT_EQ(frames[1].RigFromWorld().translation.x(), CenterFromPose(frames[1].RigFromWorld()).x());

    EXPECT_EQ(frames[1].RigFromWorld().translation.y(), CenterFromPose(frames[1].RigFromWorld()).y());

    EXPECT_EQ(frames[1].RigFromWorld().translation.z(), CenterFromPose(frames[1].RigFromWorld()).z());

    EXPECT_EQ(frames[2].RigFromWorld().translation.x(), CenterFromPose(frames[2].RigFromWorld()).x());

    EXPECT_EQ(frames[2].RigFromWorld().translation.y(), CenterFromPose(frames[2].RigFromWorld()).y());

    EXPECT_EQ(frames[2].RigFromWorld().translation.z(), CenterFromPose(frames[2].RigFromWorld()).z());

}



TEST_F(GlobalPositionerTest_105, InitializeRandomPositions_ImageNotRegistered_105) {

    ViewGraph view_graph;

    Image image1(1, 1, "img1");

    Frame frame1;



    image1.frame_id = 1;

    image1.frame_ptr = &frame1;



    Track track;

    track.observations.emplace_back(image_t(1), feature_t(1));

    std::unordered_map<frame_t, Frame> frames = {{1, frame1}};

    std::unordered_map<image_t, Image> images = {{1, image1}};

    std::unordered_map<track_t, Track> tracks = {{1, track}};



    // Mark the image as not registered

    images[1].IsRegistered = []() { return false; };



    global_positioner->InitializeRandomPositions(view_graph, frames, images, tracks);



    EXPECT_EQ(frames[1].RigFromWorld().translation.x(), CenterFromPose(frames[1].RigFromWorld()).x());

    EXPECT_EQ(frames[1].RigFromWorld().translation.y(), CenterFromPose(frames[1].RigFromWorld()).y());

    EXPECT_EQ(frames[1].RigFromWorld().translation.z(), CenterFromPose(frames[1].RigFromWorld()).z());

}



}  // namespace

}  // namespace glomap
