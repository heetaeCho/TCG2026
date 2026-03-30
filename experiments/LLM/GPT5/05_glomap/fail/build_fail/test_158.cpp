// File: view_graph_manipulation_establish_strong_clusters_test_158.cc

#include <gtest/gtest.h>

#include <string>
#include <unordered_map>
#include <vector>

#include "glomap/base/types.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/view_graph.h"
#include "glomap/processors/view_graph_manipulation.h"

namespace {

using glomap::Frame;
using glomap::Image;
using glomap::ImagePair;
using glomap::ViewGraph;
using glomap::ViewGraphManipulater;

class ViewGraphManipulaterEstablishStrongClustersTest_158
    : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
  std::unordered_map<glomap::frame_t, Frame> frames_;
  std::unordered_map<glomap::image_t, Image> images_;

  void AddImage(glomap::image_t image_id, glomap::frame_t frame_id) {
    Image image(image_id, /*camera_id*/ 0, "image_" + std::to_string(image_id));
    image.frame_id = frame_id;
    images_.emplace(image_id, image);
    frames_.emplace(frame_id, Frame());
  }

  glomap::image_pair_t AddImagePair(glomap::image_t image_id1,
                                    glomap::image_t image_id2,
                                    double weight,
                                    size_t num_inliers,
                                    bool is_valid = true) {
    ImagePair image_pair(image_id1, image_id2);
    image_pair.weight = weight;
    image_pair.is_valid = is_valid;
    image_pair.inliers.resize(num_inliers);
    const auto pair_id = image_pair.pair_id;
    view_graph_.image_pairs.emplace(pair_id, image_pair);
    return pair_id;
  }
};

// Normal case: a single strong connection (by WEIGHT) should remain valid.
TEST_F(ViewGraphManipulaterEstablishStrongClustersTest_158,
       SingleStrongPairRemainsValid_WeightCriteria_158) {
  AddImage(1, 1);
  AddImage(2, 2);
  const auto pair_id =
      AddImagePair(1, 2, /*weight*/ 10.0, /*num_inliers*/ 0u, /*is_valid*/ true);

  const double min_thres = 5.0;
  const int min_num_images = 1;

  auto num_clusters = ViewGraphManipulater::EstablishStrongClusters(
      view_graph_, frames_, images_, ViewGraphManipulater::WEIGHT, min_thres,
      min_num_images);

  (void)num_clusters;  // We do not assume anything about the exact return value.

  const auto& image_pair_after = view_graph_.image_pairs.at(pair_id);
  EXPECT_TRUE(image_pair_after.is_valid);
}

// Boundary case: when the only edge is weaker than the threshold, it should
// be removed (invalidated) under WEIGHT criteria.
TEST_F(ViewGraphManipulaterEstablishStrongClustersTest_158,
       SingleWeakPairBecomesInvalid_WeightCriteria_158) {
  AddImage(1, 1);
  AddImage(2, 2);
  const auto pair_id =
      AddImagePair(1, 2, /*weight*/ 1.0, /*num_inliers*/ 0u, /*is_valid*/ true);

  const double min_thres = 5.0;
  const int min_num_images = 1;

  ViewGraphManipulater::EstablishStrongClusters(
      view_graph_, frames_, images_, ViewGraphManipulater::WEIGHT, min_thres,
      min_num_images);

  const auto& image_pair_after = view_graph_.image_pairs.at(pair_id);
  EXPECT_FALSE(image_pair_after.is_valid);
}

// Criteria switch: under INLIER_NUM, the inlier count (not weight) should
// determine whether the edge is strong.
TEST_F(ViewGraphManipulaterEstablishStrongClustersTest_158,
       StrongByInliersDespiteLowWeight_InlierCriteria_158) {
  AddImage(1, 1);
  AddImage(2, 2);

  // Low weight, but many inliers.
  const auto pair_id =
      AddImagePair(1, 2, /*weight*/ 0.1, /*num_inliers*/ 10u, /*is_valid*/ true);

  const double min_thres = 5.0;  // inlier threshold
  const int min_num_images = 1;

  ViewGraphManipulater::EstablishStrongClusters(
      view_graph_, frames_, images_, ViewGraphManipulater::INLIER_NUM,
      min_thres, min_num_images);

  const auto& image_pair_after = view_graph_.image_pairs.at(pair_id);
  EXPECT_TRUE(image_pair_after.is_valid);
}

// Structural behavior: a weak "bridging" edge between two strong clusters
// should end up invalid when clustering based on WEIGHT.
TEST_F(ViewGraphManipulaterEstablishStrongClustersTest_158,
       WeakBridgingEdgeBetweenStrongClustersBecomesInvalid_158) {
  // Two clusters: (1,2) and (3,4), with strong internal connections.
  AddImage(1, 1);
  AddImage(2, 2);
  AddImage(3, 3);
  AddImage(4, 4);

  const auto pair_12 =
      AddImagePair(1, 2, /*weight*/ 10.0, /*num_inliers*/ 0u, /*is_valid*/ true);
  const auto pair_34 =
      AddImagePair(3, 4, /*weight*/ 10.0, /*num_inliers*/ 0u, /*is_valid*/ true);

  // Weak bridge between the two clusters.
  const auto pair_23 = AddImagePair(
      2, 3,
      /*weight*/ 3.0,        // below 0.75 * min_thres when min_thres = 5.0
      /*num_inliers*/ 0u,
      /*is_valid*/ true);

  const double min_thres = 5.0;
  const int min_num_images = 1;

  ViewGraphManipulater::EstablishStrongClusters(
      view_graph_, frames_, images_, ViewGraphManipulater::WEIGHT, min_thres,
      min_num_images);

  // Internal strong edges should remain valid.
  EXPECT_TRUE(view_graph_.image_pairs.at(pair_12).is_valid);
  EXPECT_TRUE(view_graph_.image_pairs.at(pair_34).is_valid);

  // Weak bridging edge should be removed.
  EXPECT_FALSE(view_graph_.image_pairs.at(pair_23).is_valid);
}

// Error/robustness case: edges that are already marked invalid should not
// become valid again.
TEST_F(ViewGraphManipulaterEstablishStrongClustersTest_158,
       AlreadyInvalidEdgesRemainInvalid_158) {
  AddImage(1, 1);
  AddImage(2, 2);

  // Mark this edge invalid from the beginning, even though it would be strong.
  const auto pair_id = AddImagePair(
      1, 2,
      /*weight*/ 10.0,
      /*num_inliers*/ 10u,
      /*is_valid*/ false);

  const double min_thres = 5.0;
  const int min_num_images = 1;

  ViewGraphManipulater::EstablishStrongClusters(
      view_graph_, frames_, images_, ViewGraphManipulater::WEIGHT, min_thres,
      min_num_images);

  const auto& image_pair_after = view_graph_.image_pairs.at(pair_id);
  EXPECT_FALSE(image_pair_after.is_valid);
}

}  // namespace
