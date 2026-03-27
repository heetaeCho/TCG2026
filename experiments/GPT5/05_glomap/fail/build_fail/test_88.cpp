#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

// ==========================================================
// Minimal stubs for compilation (NO internal logic assumed)
// ==========================================================

using image_t = int;
using frame_t = int;
using image_pair_t = int;

enum StrongClusterCriteria { INLIER_NUM, WEIGHT };

struct Frame {
    frame_t id = 0;
};

struct Image {
    frame_t frame_id = 0;
};

struct ImagePair {
    bool is_valid = true;
    image_t image_id1 = 0;
    image_t image_id2 = 0;
    std::vector<int> inliers;
    double weight = 0.0;
};

struct ViewGraph {
    std::unordered_map<image_pair_t, ImagePair> image_pairs;

    // Public methods used by the function under test
    int KeepLargestConnectedComponents(
        std::unordered_map<frame_t, Frame>&,
        std::unordered_map<image_t, Image>&)
    {
        return 0;  // no internal logic assumed
    }

    int MarkConnectedComponents(
        std::unordered_map<frame_t, Frame>&,
        std::unordered_map<image_t, Image>&)
    {
        return 1;  // return a visible value
    }
};

// Minimal stub for UnionFind used only through Find/Union
namespace colmap {
template <typename T>
class UnionFind {
public:
    void Reserve(size_t) {}
    void Union(T, T) {}
    T Find(T v) { return v; }
};
} // namespace colmap

// Class under test
#include "glomap/processors/view_graph_manipulation.cc"

// ==========================================================
// Test fixture
// ==========================================================
class ViewGraphManipulaterTest_88 : public ::testing::Test {
protected:
    glomap::ViewGraphManipulater manip;
    ViewGraph vg;
    std::unordered_map<frame_t, Frame> frames;
    std::unordered_map<image_t, Image> images;
};

// ==========================================================
// TESTS
// ==========================================================

// ----------------------------------------------------------
// Normal operation: No image pairs → expect minimal behavior
// ----------------------------------------------------------
TEST_F(ViewGraphManipulaterTest_88, EmptyGraph_ReturnsExpectedComponentCount_88)
{
    int result = manip.EstablishStrongClusters(
        vg, frames, images,
        INLIER_NUM, /*min_thres=*/5.0, /*min_num_images=*/1);

    EXPECT_EQ(result, 1);  // MarkConnectedComponents returns 1
}

// ----------------------------------------------------------
// Normal operation: Single valid pair, meets criteria
// ----------------------------------------------------------
TEST_F(ViewGraphManipulaterTest_88, SingleValidPair_RemainsValid_88)
{
    frames[0] = Frame{0};
    frames[1] = Frame{1};

    images[0] = Image{0};
    images[1] = Image{1};

    ImagePair pair;
    pair.is_valid = true;
    pair.image_id1 = 0;
    pair.image_id2 = 1;
    pair.inliers = {1, 2, 3, 4, 5, 6};  // size = 6
    pair.weight = 10.0;

    vg.image_pairs[0] = pair;

    int result = manip.EstablishStrongClusters(
        vg, frames, images, INLIER_NUM, 3.0, 1);

    EXPECT_TRUE(vg.image_pairs[0].is_valid);  // still valid
    EXPECT_EQ(result, 1);
}

// ----------------------------------------------------------
// Boundary case: Valid pair fails criteria → invalidated
// ----------------------------------------------------------
TEST_F(ViewGraphManipulaterTest_88, PairFailsThreshold_BecomesInvalid_88)
{
    frames[0] = Frame{0};
    frames[1] = Frame{1};

    images[0] = Image{0};
    images[1] = Image{1};

    ImagePair pair;
    pair.is_valid = true;
    pair.image_id1 = 0;
    pair.image_id2 = 1;
    pair.inliers = {1};  // size = 1
    pair.weight = 0.5;

    vg.image_pairs[0] = pair;

    int result = manip.EstablishStrongClusters(
        vg, frames, images, INLIER_NUM, 5.0, 1);

    EXPECT_FALSE(vg.image_pairs[0].is_valid);
    EXPECT_EQ(result, 1);
}

// ----------------------------------------------------------
// Weight criteria: meets weight threshold but not inlier threshold
// ----------------------------------------------------------
TEST_F(ViewGraphManipulaterTest_88, WeightCriteria_ValidatesByWeight_88)
{
    frames[0] = Frame{0};
    frames[1] = Frame{1};

    images[0] = Image{0};
    images[1] = Image{1};

    ImagePair pair;
    pair.is_valid = true;
    pair.image_id1 = 0;
    pair.image_id2 = 1;
    pair.inliers = {};      // empty, irrelevant
    pair.weight = 20.0;     // high weight

    vg.image_pairs[0] = pair;

    int result = manip.EstablishStrongClusters(
        vg, frames, images, WEIGHT, 5.0, 1);

    EXPECT_TRUE(vg.image_pairs[0].is_valid);
    EXPECT_EQ(result, 1);
}

// ----------------------------------------------------------
// Invalid pair is ignored and stays invalid
// ----------------------------------------------------------
TEST_F(ViewGraphManipulaterTest_88, InvalidPair_IgnoredAndRemainsInvalid_88)
{
    frames[0] = Frame{0};
    frames[1] = Frame{1};

    images[0] = Image{0};
    images[1] = Image{1};

    ImagePair pair;
    pair.is_valid = false;  // initially invalid
    pair.image_id1 = 0;
    pair.image_id2 = 1;

    vg.image_pairs[0] = pair;

    int result = manip.EstablishStrongClusters(
        vg, frames, images, INLIER_NUM, 3.0, 1);

    EXPECT_FALSE(vg.image_pairs[0].is_valid);  // untouched
    EXPECT_EQ(result, 1);
}

