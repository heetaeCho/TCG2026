#include <gtest/gtest.h>
#include "glomap/scene/view_graph.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/types.h"

namespace glomap {
namespace {

// Helper to create an image pair ID from two image IDs
// Using the convention from COLMAP: pair_id = min * MAX + max
inline image_pair_t ImagePairToPairId(image_t image_id1, image_t image_id2) {
    if (image_id1 > image_id2) std::swap(image_id1, image_id2);
    return static_cast<image_pair_t>(image_id1) * 2147483647 + image_id2;
}

class ViewGraphTest_94 : public ::testing::Test {
protected:
    ViewGraph view_graph_;
    std::unordered_map<frame_t, Frame> frames_;
    std::unordered_map<image_t, Image> images_;

    void SetUp() override {
        frames_.clear();
        images_.clear();
        view_graph_.image_pairs.clear();
    }

    // Helper: add an image with a given frame_id
    void AddImage(image_t image_id, frame_t frame_id) {
        Image img;
        img.frame_id = frame_id;
        images_[image_id] = img;
    }

    // Helper: add a frame
    void AddFrame(frame_t frame_id) {
        frames_[frame_id] = Frame();
    }

    // Helper: add an image pair (edge in the view graph)
    void AddImagePair(image_t id1, image_t id2) {
        image_pair_t pair_id = ImagePairToPairId(id1, id2);
        ImagePair ip;
        ip.image_id1 = std::min(id1, id2);
        ip.image_id2 = std::max(id1, id2);
        ip.is_valid = true;
        view_graph_.image_pairs[pair_id] = ip;
    }
};

// Test: Empty graph should return 0 components
TEST_F(ViewGraphTest_94, MarkConnectedComponents_EmptyGraph_94) {
    int result = view_graph_.MarkConnectedComponents(frames_, images_, 1);
    EXPECT_EQ(result, 0);
}

// Test: Single frame with single image, min_num_img = 1
TEST_F(ViewGraphTest_94, MarkConnectedComponents_SingleFrame_94) {
    AddFrame(0);
    AddImage(0, 0);

    int result = view_graph_.MarkConnectedComponents(frames_, images_, 1);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(frames_[0].cluster_id, 0);
}

// Test: Single frame but min_num_img = 2 (component too small)
TEST_F(ViewGraphTest_94, MarkConnectedComponents_SingleFrameBelowMinImg_94) {
    AddFrame(0);
    AddImage(0, 0);

    int result = view_graph_.MarkConnectedComponents(frames_, images_, 2);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(frames_[0].cluster_id, -1);
}

// Test: Two disconnected frames, min_num_img = 1
TEST_F(ViewGraphTest_94, MarkConnectedComponents_TwoDisconnectedFrames_94) {
    AddFrame(0);
    AddFrame(1);
    AddImage(0, 0);
    AddImage(1, 1);

    int result = view_graph_.MarkConnectedComponents(frames_, images_, 1);
    EXPECT_EQ(result, 2);
    // Both should have valid cluster IDs (0 or 1), but different or same depending on ordering
    EXPECT_NE(frames_[0].cluster_id, -1);
    EXPECT_NE(frames_[1].cluster_id, -1);
}

// Test: Two connected frames via an image pair
TEST_F(ViewGraphTest_94, MarkConnectedComponents_TwoConnectedFrames_94) {
    AddFrame(0);
    AddFrame(1);
    AddImage(0, 0);
    AddImage(1, 1);
    AddImagePair(0, 1);

    int result = view_graph_.MarkConnectedComponents(frames_, images_, 1);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(frames_[0].cluster_id, 0);
    EXPECT_EQ(frames_[1].cluster_id, 0);
}

// Test: Two connected components, one with 3 frames, one with 2 frames, min_num_img = 2
TEST_F(ViewGraphTest_94, MarkConnectedComponents_TwoComponents_94) {
    // Component 1: frames 0, 1, 2 connected
    AddFrame(0);
    AddFrame(1);
    AddFrame(2);
    AddImage(0, 0);
    AddImage(1, 1);
    AddImage(2, 2);
    AddImagePair(0, 1);
    AddImagePair(1, 2);

    // Component 2: frames 3, 4 connected
    AddFrame(3);
    AddFrame(4);
    AddImage(3, 3);
    AddImage(4, 4);
    AddImagePair(3, 4);

    int result = view_graph_.MarkConnectedComponents(frames_, images_, 2);
    EXPECT_EQ(result, 2);

    // Largest component (3 frames) should get cluster_id 0
    EXPECT_EQ(frames_[0].cluster_id, frames_[1].cluster_id);
    EXPECT_EQ(frames_[1].cluster_id, frames_[2].cluster_id);
    EXPECT_EQ(frames_[0].cluster_id, 0);

    // Second component should get cluster_id 1
    EXPECT_EQ(frames_[3].cluster_id, frames_[4].cluster_id);
    EXPECT_EQ(frames_[3].cluster_id, 1);
}

// Test: Two components, filter out the smaller one with min_num_img = 3
TEST_F(ViewGraphTest_94, MarkConnectedComponents_FilterSmallComponent_94) {
    // Component 1: frames 0, 1, 2 connected
    AddFrame(0);
    AddFrame(1);
    AddFrame(2);
    AddImage(0, 0);
    AddImage(1, 1);
    AddImage(2, 2);
    AddImagePair(0, 1);
    AddImagePair(1, 2);

    // Component 2: frames 3, 4 connected
    AddFrame(3);
    AddFrame(4);
    AddImage(3, 3);
    AddImage(4, 4);
    AddImagePair(3, 4);

    int result = view_graph_.MarkConnectedComponents(frames_, images_, 3);
    EXPECT_EQ(result, 1);

    // Largest component should be assigned
    EXPECT_EQ(frames_[0].cluster_id, 0);
    EXPECT_EQ(frames_[1].cluster_id, 0);
    EXPECT_EQ(frames_[2].cluster_id, 0);

    // Smaller component should remain -1
    EXPECT_EQ(frames_[3].cluster_id, -1);
    EXPECT_EQ(frames_[4].cluster_id, -1);
}

// Test: min_num_img = 0 should include all components
TEST_F(ViewGraphTest_94, MarkConnectedComponents_MinNumImgZero_94) {
    AddFrame(0);
    AddImage(0, 0);

    int result = view_graph_.MarkConnectedComponents(frames_, images_, 0);
    EXPECT_GE(result, 1);
}

// Test: Multiple images mapping to the same frame, connected via pair
TEST_F(ViewGraphTest_94, MarkConnectedComponents_MultipleImagesPerFrame_94) {
    AddFrame(0);
    AddFrame(1);
    AddImage(0, 0);
    AddImage(1, 0);  // Also maps to frame 0
    AddImage(2, 1);
    AddImagePair(1, 2);  // Connects frame 0 to frame 1

    int result = view_graph_.MarkConnectedComponents(frames_, images_, 1);
    EXPECT_GE(result, 1);
    EXPECT_EQ(frames_[0].cluster_id, frames_[1].cluster_id);
}

// Test: Frames that had prior cluster_id values get reset
TEST_F(ViewGraphTest_94, MarkConnectedComponents_ResetsClusterIds_94) {
    AddFrame(0);
    AddFrame(1);
    AddImage(0, 0);
    AddImage(1, 1);

    // Set initial cluster IDs to something
    frames_[0].cluster_id = 42;
    frames_[1].cluster_id = 99;

    int result = view_graph_.MarkConnectedComponents(frames_, images_, 5);
    EXPECT_EQ(result, 0);

    // All should be reset to -1 since no component meets min threshold
    EXPECT_EQ(frames_[0].cluster_id, -1);
    EXPECT_EQ(frames_[1].cluster_id, -1);
}

// Test: Large min_num_img filters everything out
TEST_F(ViewGraphTest_94, MarkConnectedComponents_LargeMinFiltersAll_94) {
    AddFrame(0);
    AddFrame(1);
    AddFrame(2);
    AddImage(0, 0);
    AddImage(1, 1);
    AddImage(2, 2);
    AddImagePair(0, 1);
    AddImagePair(1, 2);

    int result = view_graph_.MarkConnectedComponents(frames_, images_, 100);
    EXPECT_EQ(result, 0);
    for (auto& [fid, frame] : frames_) {
        EXPECT_EQ(frame.cluster_id, -1);
    }
}

// Test: Three separate components of sizes 4, 3, 2 with min_num_img = 3
TEST_F(ViewGraphTest_94, MarkConnectedComponents_ThreeComponentsPartialFilter_94) {
    // Component 1: 4 frames (0-3)
    for (frame_t f = 0; f < 4; f++) {
        AddFrame(f);
        AddImage(f, f);
    }
    AddImagePair(0, 1);
    AddImagePair(1, 2);
    AddImagePair(2, 3);

    // Component 2: 3 frames (4-6)
    for (frame_t f = 4; f < 7; f++) {
        AddFrame(f);
        AddImage(f, f);
    }
    AddImagePair(4, 5);
    AddImagePair(5, 6);

    // Component 3: 2 frames (7-8)
    for (frame_t f = 7; f < 9; f++) {
        AddFrame(f);
        AddImage(f, f);
    }
    AddImagePair(7, 8);

    int result = view_graph_.MarkConnectedComponents(frames_, images_, 3);
    EXPECT_EQ(result, 2);

    // Largest component (size 4) → cluster 0
    for (frame_t f = 0; f < 4; f++) {
        EXPECT_EQ(frames_[f].cluster_id, 0);
    }

    // Second component (size 3) → cluster 1
    for (frame_t f = 4; f < 7; f++) {
        EXPECT_EQ(frames_[f].cluster_id, 1);
    }

    // Third component (size 2) → filtered out
    for (frame_t f = 7; f < 9; f++) {
        EXPECT_EQ(frames_[f].cluster_id, -1);
    }
}

// Test: CreateImageAdjacencyList with empty graph
TEST_F(ViewGraphTest_94, CreateImageAdjacencyList_Empty_94) {
    auto adj = view_graph_.CreateImageAdjacencyList();
    EXPECT_TRUE(adj.empty());
}

// Test: CreateImageAdjacencyList with one pair
TEST_F(ViewGraphTest_94, CreateImageAdjacencyList_OnePair_94) {
    AddImagePair(0, 1);
    auto adj = view_graph_.CreateImageAdjacencyList();
    EXPECT_TRUE(adj.count(0) > 0);
    EXPECT_TRUE(adj.count(1) > 0);
    EXPECT_TRUE(adj[0].count(1) > 0);
    EXPECT_TRUE(adj[1].count(0) > 0);
}

// Test: CreateFrameAdjacencyList with connected frames
TEST_F(ViewGraphTest_94, CreateFrameAdjacencyList_ConnectedFrames_94) {
    AddImage(0, 0);
    AddImage(1, 1);
    AddImagePair(0, 1);

    auto adj = view_graph_.CreateFrameAdjacencyList(images_);
    EXPECT_TRUE(adj.count(0) > 0);
    EXPECT_TRUE(adj.count(1) > 0);
    EXPECT_TRUE(adj[0].count(1) > 0);
    EXPECT_TRUE(adj[1].count(0) > 0);
}

// Test: CreateFrameAdjacencyList with empty input
TEST_F(ViewGraphTest_94, CreateFrameAdjacencyList_Empty_94) {
    auto adj = view_graph_.CreateFrameAdjacencyList(images_);
    EXPECT_TRUE(adj.empty());
}

// Test: KeepLargestConnectedComponents basic test
TEST_F(ViewGraphTest_94, KeepLargestConnectedComponents_Basic_94) {
    // Component 1: frames 0, 1 connected
    AddFrame(0);
    AddFrame(1);
    AddImage(0, 0);
    AddImage(1, 1);
    AddImagePair(0, 1);

    // Component 2: frame 2 isolated
    AddFrame(2);
    AddImage(2, 2);

    int result = view_graph_.KeepLargestConnectedComponents(frames_, images_);
    // Should keep only the largest component
    EXPECT_GE(result, 1);
}

}  // namespace
}  // namespace glomap
