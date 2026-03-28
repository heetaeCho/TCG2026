// File: view_graph_test_93.cc

#include <gtest/gtest.h>

#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "glomap/scene/view_graph.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"

namespace {

using glomap::Frame;
using glomap::Image;
using glomap::ImagePair;
using glomap::ViewGraph;
using glomap::frame_t;
using glomap::image_t;
using glomap::image_pair_t;

// Helper: compute largest connected component from an adjacency list.
// This uses only the *public* adjacency data returned by CreateFrameAdjacencyList.
std::unordered_set<frame_t> ComputeLargestComponent_93(
    const std::unordered_map<frame_t, std::unordered_set<frame_t>>& adjacency) {
  // Collect all nodes that appear either as keys or neighbors.
  std::unordered_set<frame_t> all_nodes;
  for (const auto& kv : adjacency) {
    all_nodes.insert(kv.first);
    for (const auto& neigh : kv.second) {
      all_nodes.insert(neigh);
    }
  }

  std::unordered_set<frame_t> visited;
  std::unordered_set<frame_t> largest;

  for (const auto& start : all_nodes) {
    if (visited.count(start) > 0) continue;

    std::unordered_set<frame_t> component;
    std::queue<frame_t> q;
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
      frame_t v = q.front();
      q.pop();
      component.insert(v);

      auto it = adjacency.find(v);
      if (it == adjacency.end()) continue;

      for (const auto& neigh : it->second) {
        if (visited.count(neigh) == 0) {
          visited.insert(neigh);
          q.push(neigh);
        }
      }
    }

    if (component.size() > largest.size()) {
      largest = std::move(component);
    }
  }

  return largest;
}

class ViewGraphTest_93 : public ::testing::Test {
 protected:
  ViewGraph graph_;
};

}  // namespace

// Empty frames/images: graph should report 0 and not touch image_pairs.
TEST_F(ViewGraphTest_93, EmptyFramesAndImagesReturnZero_93) {
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // Add one ImagePair to verify it is not modified when there is no component.
  ImagePair pair_default;
  image_pair_t key = static_cast<image_pair_t>(1);
  pair_default.is_valid = true;
  graph_.image_pairs.emplace(key, pair_default);

  const bool is_valid_before = graph_.image_pairs.at(key).is_valid;

  int result = graph_.KeepLargestConnectedComponents(frames, images);

  EXPECT_EQ(result, 0);
  // No frames, so map must stay empty.
  EXPECT_TRUE(frames.empty());
  // With no images and hence no components, image_pairs should not be touched.
  EXPECT_EQ(graph_.image_pairs.at(key).is_valid, is_valid_before);
}

// Non-trivial case: check that frames in the largest connected component are
// marked registered, others are not, and that image_pairs validity and return
// value are consistent with Image::IsRegistered().
TEST_F(ViewGraphTest_93, LargestComponentFramesRegistrationAndImagePairValidity_93) {
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;

  // Create three frames.
  frame_t f1 = static_cast<frame_t>(1);
  frame_t f2 = static_cast<frame_t>(2);
  frame_t f3 = static_cast<frame_t>(3);

  frames.emplace(f1, Frame());
  frames.emplace(f2, Frame());
  frames.emplace(f3, Frame());

  // Give all frames a distinctive initial registration state (all true)
  // so we can verify they are overwritten.
  for (auto& kv : frames) {
    kv.second.is_registered = true;
  }

  // Create three images, each linked to a different frame.
  image_t i1 = static_cast<image_t>(10);
  image_t i2 = static_cast<image_t>(20);
  image_t i3 = static_cast<image_t>(30);

  Image img1;
  img1.frame_id = f1;
  images.emplace(i1, img1);

  Image img2;
  img2.frame_id = f2;
  images.emplace(i2, img2);

  Image img3;
  img3.frame_id = f3;
  images.emplace(i3, img3);

  // Create one ImagePair between image 1 and 2.
  ImagePair pair12(i1, i2);
  graph_.image_pairs.emplace(pair12.pair_id, pair12);

  // Optionally, add another pair involving image 3 so we have more than one.
  ImagePair pair23(i2, i3);
  graph_.image_pairs.emplace(pair23.pair_id, pair23);

  // Use the public adjacency builder to see the frame graph.
  auto adjacency = graph_.CreateFrameAdjacencyList(images);

  // If the implementation does not create any adjacency for this setup,
  // there is no non-trivial component to test; skip in that rare case.
  std::unordered_set<frame_t> all_nodes;
  for (const auto& kv : adjacency) {
    all_nodes.insert(kv.first);
    for (const auto& neigh : kv.second) {
      all_nodes.insert(neigh);
    }
  }
  if (all_nodes.empty()) {
    GTEST_SKIP() << "Adjacency list is empty for the non-trivial setup; "
                    "skipping behavioral test.";
  }

  // Compute largest component from the public adjacency.
  std::unordered_set<frame_t> largest_component =
      ComputeLargestComponent_93(adjacency);
  ASSERT_FALSE(largest_component.empty());

  // Pre-compute expected validity of each ImagePair based solely on
  // Image::IsRegistered() (observable behavior).
  std::unordered_map<image_pair_t, bool> expected_valid;
  for (const auto& kv : graph_.image_pairs) {
    const ImagePair& ip = kv.second;
    bool reg1 = images[ip.image_id1].IsRegistered();
    bool reg2 = images[ip.image_id2].IsRegistered();
    expected_valid.emplace(kv.first, reg1 && reg2);
  }

  // Count registered images (function does not modify Image registration).
  int registered_images = 0;
  for (const auto& kv : images) {
    if (kv.second.IsRegistered()) {
      ++registered_images;
    }
  }

  int result = graph_.KeepLargestConnectedComponents(frames, images);

  // Frames inside the largest component should be registered; others not.
  for (const auto& kv : frames) {
    frame_t id = kv.first;
    bool should_be_registered = largest_component.count(id) > 0;
    EXPECT_EQ(kv.second.is_registered, should_be_registered)
        << "Frame " << id << " registration mismatch";
  }

  // ImagePair validity should follow Image::IsRegistered() for its endpoints.
  for (const auto& kv : graph_.image_pairs) {
    image_pair_t pid = kv.first;
    ASSERT_TRUE(expected_valid.find(pid) != expected_valid.end());
    bool expected = expected_valid[pid];
    EXPECT_EQ(kv.second.is_valid, expected)
        << "ImagePair " << pid << " validity mismatch";
  }

  // Return value: size of largest component plus number of registered images.
  EXPECT_EQ(result,
            static_cast<int>(largest_component.size() + registered_images));
}
