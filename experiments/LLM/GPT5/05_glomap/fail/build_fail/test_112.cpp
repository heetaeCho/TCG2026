// File: rotation_averager_test_112.cc

#include <unordered_map>

#include <gtest/gtest.h>

#include "glomap/controllers/rotation_averager.h"
#include "glomap/estimators/global_rotation_averaging.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/rig.h"

namespace glomap {

// Forward declaration of the function under test, in case it is not
// exposed by the included headers.
bool SolveRotationAveraging(ViewGraph& view_graph,
                            std::unordered_map<rig_t, Rig>& rigs,
                            std::unordered_map<frame_t, Frame>& frames,
                            std::unordered_map<image_t, Image>& images,
                            const RotationAveragerOptions& options);

}  // namespace glomap

class SolveRotationAveragingTest_112 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default options; individual tests may tweak fields.
  }

  glomap::ViewGraph view_graph_;
  std::unordered_map<glomap::rig_t, glomap::Rig> rigs_;
  std::unordered_map<glomap::frame_t, glomap::Frame> frames_;
  std::unordered_map<glomap::image_t, glomap::Image> images_;
  glomap::RotationAveragerOptions options_;
};

//------------------------------------------------------------------------------
// 1. Empty inputs, default options: function should be callable without throwing
//------------------------------------------------------------------------------
TEST_F(SolveRotationAveragingTest_112,
       EmptyInputs_NoGravityOptions_NoThrow_112) {
  EXPECT_NO_THROW({
    bool result =
        glomap::SolveRotationAveraging(view_graph_, rigs_, frames_, images_,
                                       options_);
    (void)result;  // We do not assert specific success/failure semantics.
  });
}

//------------------------------------------------------------------------------
// 2. Gravity + stratified options enabled, but still empty graph
//    This should still be safely callable (no exceptions).
//------------------------------------------------------------------------------
TEST_F(SolveRotationAveragingTest_112,
       GravityStratifiedOptionsWithEmptyGraph_NoThrow_112) {
  options_.use_gravity = true;
  options_.use_stratified = true;

  EXPECT_NO_THROW({
    bool result =
        glomap::SolveRotationAveraging(view_graph_, rigs_, frames_, images_,
                                       options_);
    (void)result;
  });
}

//------------------------------------------------------------------------------
// 3. Non-empty view graph with a single valid image pair
//    Verifies the function can operate on minimal but non-trivial data.
//------------------------------------------------------------------------------
TEST_F(SolveRotationAveragingTest_112,
       NonEmptyViewGraphWithSinglePair_NoThrow_112) {
  // Create two images with distinct IDs and cameras.
  const glomap::image_t kImageId1 = 1;
  const glomap::image_t kImageId2 = 2;

  glomap::Image image1(kImageId1, /*camera_id=*/1, "image1.jpg");
  glomap::Image image2(kImageId2, /*camera_id=*/2, "image2.jpg");

  images_.emplace(kImageId1, image1);
  images_.emplace(kImageId2, image2);

  // Create a single valid image pair in the view graph.
  glomap::ImagePair image_pair(kImageId1, kImageId2);
  image_pair.is_valid = true;

  view_graph_.image_pairs.emplace(image_pair.pair_id, image_pair);

  // Use gravity / stratified settings to exercise related branches,
  // without making assumptions about specific estimator behavior.
  options_.use_gravity = true;
  options_.use_stratified = true;

  EXPECT_NO_THROW({
    bool result =
        glomap::SolveRotationAveraging(view_graph_, rigs_, frames_, images_,
                                       options_);
    (void)result;
  });
}

//------------------------------------------------------------------------------
// 4. Verify that the const options argument is not modified by the function
//    (interface-level guarantee: it is passed as const reference).
//------------------------------------------------------------------------------
TEST_F(SolveRotationAveragingTest_112,
       SkipInitializationOptionRemainsUnchanged_112) {
  options_.skip_initialization = true;

  EXPECT_NO_THROW({
    bool result =
        glomap::SolveRotationAveraging(view_graph_, rigs_, frames_, images_,
                                       options_);
    (void)result;
  });

  // Since options is passed as a const reference, we can at least
  // assert that our local copy hasn't been modified by the call.
  EXPECT_TRUE(options_.skip_initialization);
}
