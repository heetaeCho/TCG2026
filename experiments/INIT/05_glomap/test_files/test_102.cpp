// File: relpose_estimation_test_102.cc

#include <unordered_map>
#include <string>

#include <gtest/gtest.h>

#include "glomap/estimators/relpose_estimation.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/scene/camera.h"

namespace glomap {

class EstimateRelativePosesTest_102 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<image_t, Image> images_;
  RelativePoseEstimationOptions options_;
};

//------------------------------------------------------------------------------
// Boundary case: empty ViewGraph (no image pairs)
// Verifies that the function completes and prints the final 100% message,
// without modifying the empty graph.
//------------------------------------------------------------------------------
TEST_F(EstimateRelativePosesTest_102, HandlesEmptyViewGraph_102) {
  // Sanity: no image pairs at start.
  ASSERT_TRUE(view_graph_.image_pairs.empty());

  // Capture stdout to verify progress / completion output.
  testing::internal::CaptureStdout();
  EstimateRelativePoses(view_graph_, cameras_, images_, options_);
  std::string output = testing::internal::GetCapturedStdout();

  // ViewGraph should still be empty.
  EXPECT_TRUE(view_graph_.image_pairs.empty());

  // Output should contain the final completion line.
  // We do not depend on the exact prefix, only that "100%" appears with the message.
  EXPECT_NE(output.find("Estimating relative pose: 100%"), std::string::npos);
}

//------------------------------------------------------------------------------
// Boundary/normal-ish case: only invalid pairs present
// Verifies that invalid pairs are skipped (never added to the valid_pair_ids
// list inside the implementation) and remain unchanged.
// This path avoids any dependency on cameras/images or poselib behavior.
//------------------------------------------------------------------------------
TEST_F(EstimateRelativePosesTest_102, SkipsInvalidPairs_102) {
  // Create an ImagePair and explicitly mark it as invalid.
  const image_t kImageId1 = static_cast<image_t>(1);
  const image_t kImageId2 = static_cast<image_t>(2);

  ImagePair image_pair(kImageId1, kImageId2);
  image_pair.is_valid = false;

  // Insert into the view graph using its pair_id as key.
  const image_pair_t pair_id = image_pair.pair_id;
  view_graph_.image_pairs.emplace(pair_id, image_pair);

  ASSERT_EQ(view_graph_.image_pairs.size(), 1u);
  ASSERT_FALSE(view_graph_.image_pairs.at(pair_id).is_valid);

  // Call the function under test. Since there are no valid pairs,
  // the internal valid_pair_ids list should stay empty and the lambda body
  // with cameras/images/poselib calls should never execute.
  EstimateRelativePoses(view_graph_, cameras_, images_, options_);

  // The number of pairs must remain the same and the invalid flag unchanged.
  ASSERT_EQ(view_graph_.image_pairs.size(), 1u);
  const auto& stored_pair = view_graph_.image_pairs.at(pair_id);
  EXPECT_FALSE(stored_pair.is_valid);
}

//------------------------------------------------------------------------------
// Idempotency-style check on an empty graph:
// Calling the function multiple times on an empty graph should be safe,
// and the completion message should still be printed each time.
//------------------------------------------------------------------------------
TEST_F(EstimateRelativePosesTest_102, MultipleCallsOnEmptyGraphAreSafe_102) {
  ASSERT_TRUE(view_graph_.image_pairs.empty());

  // First call
  testing::internal::CaptureStdout();
  EstimateRelativePoses(view_graph_, cameras_, images_, options_);
  std::string first_output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(view_graph_.image_pairs.empty());
  EXPECT_NE(first_output.find("Estimating relative pose: 100%"), std::string::npos);

  // Second call – should behave the same way.
  testing::internal::CaptureStdout();
  EstimateRelativePoses(view_graph_, cameras_, images_, options_);
  std::string second_output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(view_graph_.image_pairs.empty());
  EXPECT_NE(second_output.find("Estimating relative pose: 100%"), std::string::npos);
}

}  // namespace glomap
