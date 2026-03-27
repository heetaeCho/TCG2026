#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <unordered_map>

#include <unordered_set>



namespace glomap {



struct Frame {

    bool is_registered = false;

};



struct Image {

    bool IsRegistered() const { return is_registered; }

    bool is_registered = false;

};



struct ImagePair {

    image_t image_id1;

    image_t image_id2;

    bool is_valid = true;

};



class ViewGraphTest_4 : public ::testing::Test {

protected:

    ViewGraph view_graph_;

    std::unordered_map<frame_t, Frame> frames_;

    std::unordered_map<image_t, Image> images_;

    std::unordered_map<pair_t, ImagePair> image_pairs_;

};



TEST_F(ViewGraphTest_4, KeepLargestConnectedComponents_NoFramesOrImages_4) {

    int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);

    EXPECT_EQ(result, 0);

}



TEST_F(ViewGraphTest_4, KeepLargestConnectedComponents_OneFrameNoConnections_4) {

    frames_[1] = Frame{};

    int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);

    EXPECT_EQ(result, 1);

    EXPECT_TRUE(frames_[1].is_registered);

}



TEST_F(ViewGraphTest_4, KeepLargestConnectedComponents_TwoFramesOneConnection_4) {

    frames_[1] = Frame{};

    frames_[2] = Frame{};

    image_pairs_[1] = ImagePair{1, 2};



    int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);

    EXPECT_EQ(result, 2);

    EXPECT_TRUE(frames_[1].is_registered);

    EXPECT_TRUE(frames_[2].is_registered);

}



TEST_F(ViewGraphTest_4, KeepLargestConnectedComponents_TwoFramesNoConnections_4) {

    frames_[1] = Frame{};

    frames_[2] = Frame{};



    int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);

    EXPECT_EQ(result, 0);

    EXPECT_FALSE(frames_[1].is_registered);

    EXPECT_FALSE(frames_[2].is_registered);

}



TEST_F(ViewGraphTest_4, KeepLargestConnectedComponents_MultipleFramesMultipleConnections_4) {

    frames_[1] = Frame{};

    frames_[2] = Frame{};

    frames_[3] = Frame{};

    frames_[4] = Frame{};

    image_pairs_[1] = ImagePair{1, 2};

    image_pairs_[2] = ImagePair{2, 3};



    int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);

    EXPECT_EQ(result, 3);

    EXPECT_TRUE(frames_[1].is_registered);

    EXPECT_TRUE(frames_[2].is_registered);

    EXPECT_TRUE(frames_[3].is_registered);

    EXPECT_FALSE(frames_[4].is_registered);

}



TEST_F(ViewGraphTest_4, KeepLargestConnectedComponents_ImagePairsInvalidAfterProcessing_4) {

    frames_[1] = Frame{};

    frames_[2] = Frame{};

    images_[1] = Image{};

    images_[2] = Image{};

    image_pairs_[1] = ImagePair{1, 2};



    int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);

    EXPECT_EQ(result, 2);

    EXPECT_TRUE(image_pairs_[1].is_valid);



    frames_[3] = Frame{};

    images_[3] = Image{};

    image_pairs_[2] = ImagePair{1, 3};

    frames_[2].is_registered = false;



    result = view_graph_.KeepLargestConnectedComponents(frames_, images_);

    EXPECT_EQ(result, 2);

    EXPECT_FALSE(image_pairs_[2].is_valid);

}



} // namespace glomap
