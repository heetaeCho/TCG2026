#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/frame.h"
#include "glomap/base/types.h"

namespace {

// Helper subclass to expose the protected method and scales_ vector
class TestableGlobalPositioner_106 : public glomap::GlobalPositioner {
 public:
  explicit TestableGlobalPositioner_106(const glomap::GlobalPositionerOptions& options)
      : glomap::GlobalPositioner(options) {}

  // Expose the protected overload under test
  using glomap::GlobalPositioner::AddCameraToCameraConstraints;

  // Controlled access to scales_ for setting capacity and observing size
  std::vector<double>& mutable_scales_106() { return scales_; }
};

// Test fixture
class GlobalPositionerAddCameraToCameraConstraintsTest_106 : public ::testing::Test {
 protected:
  glomap::GlobalPositionerOptions options_;
  TestableGlobalPositioner_106 positioner_{options_};

  void SetUp() override {
    // Ensure we have enough capacity to avoid triggering the CHECK in the method
    positioner_.mutable_scales_106().reserve(16);
  }
};

}  // namespace

// 1. Empty ViewGraph & empty images: no scales are added.
TEST_F(GlobalPositionerAddCameraToCameraConstraintsTest_106,
       EmptyViewGraphDoesNotAddScales_106) {
  glomap::ViewGraph view_graph;
  std::unordered_map<glomap::image_t, glomap::Image> images;

  auto& scales = positioner_.mutable_scales_106();
  const std::size_t before_size = scales.size();

  positioner_.AddCameraToCameraConstraints(view_graph, images);

  EXPECT_EQ(before_size, scales.size());
}

// 2. ImagePair marked invalid should be skipped (no new scale).
TEST_F(GlobalPositionerAddCameraToCameraConstraintsTest_106,
       InvalidImagePairIsSkipped_106) {
  glomap::ViewGraph view_graph;
  std::unordered_map<glomap::image_t, glomap::Image> images;

  // Create two images (details of internal state are treated as black box)
  const glomap::image_t kImageId1 = 1;
  const glomap::image_t kImageId2 = 2;

  images.emplace(kImageId1, glomap::Image(kImageId1, 0, "img1"));
  images.emplace(kImageId2, glomap::Image(kImageId2, 0, "img2"));

  // Create an ImagePair that is marked as invalid
  glomap::ImagePair image_pair(kImageId1, kImageId2);
  auto pair_id = image_pair.pair_id;
  auto inserted = view_graph.image_pairs.emplace(pair_id, image_pair);
  inserted.first->second.is_valid = false;

  auto& scales = positioner_.mutable_scales_106();
  const std::size_t before_size = scales.size();

  positioner_.AddCameraToCameraConstraints(view_graph, images);

  // No new constraint / scale should have been added
  EXPECT_EQ(before_size, scales.size());
}

// 3. Valid ImagePair but missing one image in map -> skipped.
TEST_F(GlobalPositionerAddCameraToCameraConstraintsTest_106,
       MissingImageInMapSkipsPair_106) {
  glomap::ViewGraph view_graph;
  std::unordered_map<glomap::image_t, glomap::Image> images;

  const glomap::image_t kImageId1 = 3;
  const glomap::image_t kImageId2 = 4;

  // Only insert one of the images into the map
  images.emplace(kImageId1, glomap::Image(kImageId1, 0, "img1"));

  glomap::ImagePair image_pair(kImageId1, kImageId2);
  auto pair_id = image_pair.pair_id;
  view_graph.image_pairs.emplace(pair_id, image_pair);  // is_valid defaults to true

  auto& scales = positioner_.mutable_scales_106();
  const std::size_t before_size = scales.size();

  positioner_.AddCameraToCameraConstraints(view_graph, images);

  // Pair should be skipped because kImageId2 is missing
  EXPECT_EQ(before_size, scales.size());
}

// 4. Single valid pair with both images present: one new scale should be added.
TEST_F(GlobalPositionerAddCameraToCameraConstraintsTest_106,
       SingleValidPairAddsOneScale_106) {
  glomap::ViewGraph view_graph;
  std::unordered_map<glomap::image_t, glomap::Image> images;

  const glomap::image_t kImageId1 = 5;
  const glomap::image_t kImageId2 = 6;

  // Construct images; actual registration / frame semantics are treated as black box.
  glomap::Image image1(kImageId1, 0, "img1");
  glomap::Image image2(kImageId2, 0, "img2");

  // Ensure frame_ptrs are non-null so that internal calls to frame_ptr->RigFromWorld()
  // have valid objects to work with.
  auto* frame1 = new glomap::Frame();
  auto* frame2 = new glomap::Frame();
  image1.frame_ptr = frame1;
  image2.frame_ptr = frame2;

  images.emplace(kImageId1, image1);
  images.emplace(kImageId2, image2);

  // Create a valid ImagePair
  glomap::ImagePair image_pair(kImageId1, kImageId2);
  auto pair_id = image_pair.pair_id;
  view_graph.image_pairs.emplace(pair_id, image_pair);  // is_valid defaults to true

  auto& scales = positioner_.mutable_scales_106();
  const std::size_t before_size = scales.size();

  positioner_.AddCameraToCameraConstraints(view_graph, images);

  // Exactly one new scale should be appended
  ASSERT_EQ(before_size + 1, scales.size());
  EXPECT_DOUBLE_EQ(1.0, scales.back());

  delete frame1;
  delete frame2;
}

// 5. Multiple valid pairs should add one scale per pair.
TEST_F(GlobalPositionerAddCameraToCameraConstraintsTest_106,
       MultipleValidPairsAddMultipleScales_106) {
  glomap::ViewGraph view_graph;
  std::unordered_map<glomap::image_t, glomap::Image> images;

  const glomap::image_t kImageId1 = 7;
  const glomap::image_t kImageId2 = 8;
  const glomap::image_t kImageId3 = 9;

  // Images with non-null frames to support internal pose/rig access.
  glomap::Image image1(kImageId1, 0, "img1");
  glomap::Image image2(kImageId2, 0, "img2");
  glomap::Image image3(kImageId3, 0, "img3");

  auto* frame1 = new glomap::Frame();
  auto* frame2 = new glomap::Frame();
  auto* frame3 = new glomap::Frame();

  image1.frame_ptr = frame1;
  image2.frame_ptr = frame2;
  image3.frame_ptr = frame3;

  images.emplace(kImageId1, image1);
  images.emplace(kImageId2, image2);
  images.emplace(kImageId3, image3);

  // Two valid pairs: (1,2) and (2,3)
  glomap::ImagePair pair12(kImageId1, kImageId2);
  glomap::ImagePair pair23(kImageId2, kImageId3);

  view_graph.image_pairs.emplace(pair12.pair_id, pair12);
  view_graph.image_pairs.emplace(pair23.pair_id, pair23);

  auto& scales = positioner_.mutable_scales_106();
  const std::size_t before_size = scales.size();

  positioner_.AddCameraToCameraConstraints(view_graph, images);

  // One scale per valid pair
  ASSERT_EQ(before_size + 2, scales.size());
  EXPECT_DOUBLE_EQ(1.0, scales[before_size]);
  EXPECT_DOUBLE_EQ(1.0, scales[before_size + 1]);

  delete frame1;
  delete frame2;
  delete frame3;
}
