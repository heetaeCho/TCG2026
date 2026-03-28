#include <gtest/gtest.h>

#include <unordered_map>
#include <limits>

#include "glomap/scene/view_graph.h"

namespace glomap {

class ViewGraphTest_5 : public ::testing::Test {
protected:
    ViewGraph view_graph_;
};

// [Boundary] When min_num_img is extremely large, no component should be accepted,
// all existing frames should have cluster_id reset to -1, and the return value
// should be 0. The set of frame keys must remain unchanged.
// (This follows from the public, observable behavior of MarkConnectedComponents.)
TEST_F(ViewGraphTest_5, ReturnsZeroAndResetsClustersWhenThresholdTooHigh_5) {
    std::unordered_map<frame_t, Frame> frames;
    std::unordered_map<image_t, Image> images;

    // Prepare a few frames with non-default cluster_id values.
    Frame frame1;
    frame1.cluster_id = 10;
    Frame frame2;
    frame2.cluster_id = 20;

    const frame_t id1 = static_cast<frame_t>(1);
    const frame_t id2 = static_cast<frame_t>(2);

    frames[id1] = frame1;
    frames[id2] = frame2;

    // Capture the keys before the call.
    std::unordered_set<frame_t> original_keys;
    for (const auto& kv : frames) {
        original_keys.insert(kv.first);
    }

    const int min_num_img = std::numeric_limits<int>::max();
    const int result =
        view_graph_.MarkConnectedComponents(frames, images, min_num_img);

    // With an unrealistically high threshold, no component should be accepted.
    EXPECT_EQ(result, 0);

    // The set of keys should not change when no component is accepted.
    std::unordered_set<frame_t> new_keys;
    for (const auto& kv : frames) {
        new_keys.insert(kv.first);
    }
    EXPECT_EQ(new_keys, original_keys);

    // All existing frames should have cluster_id reset to -1.
    for (const auto& kv : frames) {
        EXPECT_EQ(kv.second.cluster_id, -1);
    }
}

// [General behavior] For any inputs, the function should return a non-negative
// integer, and each frame's cluster_id after the call must be either -1 or
// in the range [0, returned_value - 1]. If the function reports that it
// assigned at least one component (return > 0), then at least one frame
// must have a non-negative cluster_id.
TEST_F(ViewGraphTest_5, ClusterIdsAreConsistentWithReturnValue_5) {
    std::unordered_map<frame_t, Frame> frames;
    std::unordered_map<image_t, Image> images;

    // Prepare some frames with arbitrary initial cluster_id values.
    Frame frame1;
    frame1.cluster_id = 42;
    Frame frame2;
    frame2.cluster_id = 99;

    const frame_t id1 = static_cast<frame_t>(1);
    const frame_t id2 = static_cast<frame_t>(2);

    frames[id1] = frame1;
    frames[id2] = frame2;

    // Use a non-restrictive threshold (0) so that, if any connected components
    // exist, they are eligible to be assigned.
    const int min_num_img = 0;
    const int result =
        view_graph_.MarkConnectedComponents(frames, images, min_num_img);

    // The return value is the number of accepted components and must be >= 0.
    EXPECT_GE(result, 0);

    bool has_non_negative_cluster = false;

    for (const auto& kv : frames) {
        const int cluster_id = kv.second.cluster_id;

        if (cluster_id >= 0) {
            has_non_negative_cluster = true;
            // Any non-negative cluster_id must be strictly less than result.
            EXPECT_LT(cluster_id, result);
        } else {
            // Frames not belonging to accepted components should remain -1.
            EXPECT_EQ(cluster_id, -1);
        }
    }

    if (result == 0) {
        // If no components are reported as accepted, no frame should have a
        // non-negative cluster_id.
        EXPECT_FALSE(has_non_negative_cluster);
    } else {
        // If at least one component is reported as accepted, at least one frame
        // must have a non-negative cluster_id.
        EXPECT_TRUE(has_non_negative_cluster);
    }
}

}  // namespace glomap
