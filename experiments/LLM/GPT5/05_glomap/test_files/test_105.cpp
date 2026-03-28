// File: global_positioner_initialize_random_positions_test_105.cc

#include <gtest/gtest.h>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/track.h"

namespace glomap {

// Simple wrapper to expose the protected InitializeRandomPositions and GetOptions.
class GlobalPositionerTestWrapper_105 : public GlobalPositioner {
 public:
  explicit GlobalPositionerTestWrapper_105(const GlobalPositionerOptions& options)
      : GlobalPositioner(options) {}

  using GlobalPositioner::InitializeRandomPositions;
  using GlobalPositioner::GetOptions;
};

class GlobalPositionerInitializeRandomPositionsTest_105 : public ::testing::Test {
 protected:
  // Helper to set a known translation for a frame.
  void SetFrameTranslation(Frame& frame, const Eigen::Vector3d& t) {
    frame.RigFromWorld().translation = t;
  }

  Eigen::Vector3d GetFrameTranslation(Frame& frame) {
    return frame.RigFromWorld().translation;
  }

  // Create a simple valid ImagePair and insert into a ViewGraph.
  void AddValidImagePair(ViewGraph& view_graph,
                         image_t image_id1,
                         image_t image_id2) {
    ImagePair pair(image_id1, image_id2);
    pair.is_valid = true;
    view_graph.image_pairs.emplace(pair.pair_id, pair);
  }
};

// -----------------------------------------------------------------------------
// Test 1: When generate_random_positions is false (early-return branch),
//         unconstrained frames must *not* be modified.
// -----------------------------------------------------------------------------
TEST_F(GlobalPositionerInitializeRandomPositionsTest_105,
       UnconstrainedFramesNotModifiedWhenRandomDisabled_105) {
  GlobalPositionerOptions options;
  options.generate_random_positions = false;   // Force the early-return branch.
  options.optimize_positions = true;

  GlobalPositionerTestWrapper_105 positioner(options);

  ViewGraph view_graph;

  // IDs
  const image_t kImg1 = 1;
  const image_t kImg2 = 2;
  const image_t kImg3 = 3;
  const frame_t kFrame1 = 10;
  const frame_t kFrame2 = 20;
  const frame_t kFrame3 = 30;  // will remain unconstrained

  // Images and their frame associations.
  std::unordered_map<image_t, Image> images;
  {
    Image img1(kImg1, /*camera_id=*/0, "img1");
    img1.frame_id = kFrame1;
    images.emplace(kImg1, img1);

    Image img2(kImg2, /*camera_id=*/0, "img2");
    img2.frame_id = kFrame2;
    images.emplace(kImg2, img2);

    Image img3(kImg3, /*camera_id=*/0, "img3");
    img3.frame_id = kFrame3;
    images.emplace(kImg3, img3);
  }

  // One valid pair -> frames {kFrame1, kFrame2} are constrained.
  AddValidImagePair(view_graph, kImg1, kImg2);

  // Frames: 3 total, with different initial translations.
  std::unordered_map<frame_t, Frame> frames;
  frames.emplace(kFrame1, Frame());
  frames.emplace(kFrame2, Frame());
  frames.emplace(kFrame3, Frame());

  const Eigen::Vector3d t1(1.0, 2.0, 3.0);
  const Eigen::Vector3d t2(4.0, 5.0, 6.0);
  const Eigen::Vector3d t3(7.0, 8.0, 9.0);

  SetFrameTranslation(frames[kFrame1], t1);
  SetFrameTranslation(frames[kFrame2], t2);
  SetFrameTranslation(frames[kFrame3], t3);  // unconstrained

  // No tracks – we only test the view_graph-based constraints here.
  std::unordered_map<track_t, Track> tracks;

  positioner.InitializeRandomPositions(view_graph, frames, images, tracks);

  // In the early-return branch, unconstrained frames MUST NOT be modified.
  const Eigen::Vector3d unconstrained_after = GetFrameTranslation(frames[kFrame3]);

  EXPECT_DOUBLE_EQ(unconstrained_after.x(), t3.x());
  EXPECT_DOUBLE_EQ(unconstrained_after.y(), t3.y());
  EXPECT_DOUBLE_EQ(unconstrained_after.z(), t3.z());
}

// -----------------------------------------------------------------------------
// Test 2: When generate_random_positions && optimize_positions are both true,
//         unconstrained frames (not in constrained_positions) should be updated,
//         while the "random disabled" configuration keeps them unchanged.
//         We compare the *same* frame across two different option sets.
// -----------------------------------------------------------------------------
TEST_F(GlobalPositionerInitializeRandomPositionsTest_105,
       UnconstrainedFramesDifferBetweenRandomDisabledAndEnabled_105) {
  // --- Positioner A: random positions disabled -> early-return branch.
  GlobalPositionerOptions options_a;
  options_a.generate_random_positions = false;
  options_a.optimize_positions = true;
  GlobalPositionerTestWrapper_105 positioner_a(options_a);

  // --- Positioner B: random positions enabled (default) -> full branch.
  GlobalPositionerOptions options_b;
  options_b.generate_random_positions = true;
  options_b.optimize_positions = true;
  GlobalPositionerTestWrapper_105 positioner_b(options_b);

  ViewGraph view_graph;

  const image_t kImg1 = 1;
  const image_t kImg2 = 2;
  const frame_t kFrame1 = 10;  // constrained
  const frame_t kFrame2 = 20;  // constrained
  const frame_t kFrame3 = 30;  // *unconstrained* (no image pair uses this)

  // Images for constrained frames.
  std::unordered_map<image_t, Image> images_a;
  std::unordered_map<image_t, Image> images_b;

  {
    Image img1_a(kImg1, /*camera_id=*/0, "img1");
    img1_a.frame_id = kFrame1;
    images_a.emplace(kImg1, img1_a);

    Image img2_a(kImg2, /*camera_id=*/0, "img2");
    img2_a.frame_id = kFrame2;
    images_a.emplace(kImg2, img2_a);

    Image img1_b(kImg1, /*camera_id=*/0, "img1");
    img1_b.frame_id = kFrame1;
    images_b.emplace(kImg1, img1_b);

    Image img2_b(kImg2, /*camera_id=*/0, "img2");
    img2_b.frame_id = kFrame2;
    images_b.emplace(kImg2, img2_b);
  }

  // Only (kImg1, kImg2) is in the graph -> frames {kFrame1, kFrame2} constrained.
  AddValidImagePair(view_graph, kImg1, kImg2);

  // Frames for A
  std::unordered_map<frame_t, Frame> frames_a;
  frames_a.emplace(kFrame1, Frame());
  frames_a.emplace(kFrame2, Frame());
  frames_a.emplace(kFrame3, Frame());

  // Frames for B – identical initial state
  std::unordered_map<frame_t, Frame> frames_b;
  frames_b.emplace(kFrame1, Frame());
  frames_b.emplace(kFrame2, Frame());
  frames_b.emplace(kFrame3, Frame());

  // Same initial translation for the unconstrained frame in both copies.
  const Eigen::Vector3d t_unconstrained(7.0, 8.0, 9.0);
  SetFrameTranslation(frames_a[kFrame3], t_unconstrained);
  SetFrameTranslation(frames_b[kFrame3], t_unconstrained);

  // Tracks unused in this test.
  std::unordered_map<track_t, Track> tracks_a;
  std::unordered_map<track_t, Track> tracks_b;

  // Run with random disabled.
  positioner_a.InitializeRandomPositions(view_graph, frames_a, images_a, tracks_a);

  // Run with random enabled.
  positioner_b.InitializeRandomPositions(view_graph, frames_b, images_b, tracks_b);

  // With random disabled, unconstrained frame remains untouched.
  const Eigen::Vector3d unconstrained_a = GetFrameTranslation(frames_a[kFrame3]);
  EXPECT_DOUBLE_EQ(unconstrained_a.x(), t_unconstrained.x());
  EXPECT_DOUBLE_EQ(unconstrained_a.y(), t_unconstrained.y());
  EXPECT_DOUBLE_EQ(unconstrained_a.z(), t_unconstrained.z());

  // With random+optimize enabled, unconstrained frame should now be set
  // to CenterFromPose(...), which in general is expected to differ from
  // the initial translation.
  const Eigen::Vector3d unconstrained_b = GetFrameTranslation(frames_b[kFrame3]);

  // We only check that it changed, without assuming the exact value.
  EXPECT_FALSE(unconstrained_b.isApprox(t_unconstrained));
}

// -----------------------------------------------------------------------------
// Test 3: Image pairs marked as invalid must be ignored when building
//         constrained_positions. We check that frames referenced only by
//         invalid pairs behave as unconstrained in the "random disabled" branch.
// -----------------------------------------------------------------------------
TEST_F(GlobalPositionerInitializeRandomPositionsTest_105,
       InvalidImagePairsAreIgnoredForConstraints_105) {
  GlobalPositionerOptions options;
  options.generate_random_positions = false;   // early-return branch
  options.optimize_positions = true;

  GlobalPositionerTestWrapper_105 positioner(options);

  ViewGraph view_graph;

  const image_t kImgValid1 = 1;
  const image_t kImgValid2 = 2;
  const image_t kImgInvalid1 = 3;
  const image_t kImgInvalid2 = 4;

  const frame_t kFrameValid1   = 10;
  const frame_t kFrameValid2   = 20;
  const frame_t kFrameInvalid1 = 30;  // only referenced by invalid pair
  const frame_t kFrameInvalid2 = 40;  // only referenced by invalid pair

  std::unordered_map<image_t, Image> images;

  {
    Image img_v1(kImgValid1, /*camera_id=*/0, "valid1");
    img_v1.frame_id = kFrameValid1;
    images.emplace(kImgValid1, img_v1);

    Image img_v2(kImgValid2, /*camera_id=*/0, "valid2");
    img_v2.frame_id = kFrameValid2;
    images.emplace(kImgValid2, img_v2);

    Image img_i1(kImgInvalid1, /*camera_id=*/0, "invalid1");
    img_i1.frame_id = kFrameInvalid1;
    images.emplace(kImgInvalid1, img_i1);

    Image img_i2(kImgInvalid2, /*camera_id=*/0, "invalid2");
    img_i2.frame_id = kFrameInvalid2;
    images.emplace(kImgInvalid2, img_i2);
  }

  // One valid pair -> frames {kFrameValid1, kFrameValid2} are constrained.
  AddValidImagePair(view_graph, kImgValid1, kImgValid2);

  // One invalid pair -> should be ignored by InitializeRandomPositions.
  {
    ImagePair invalid_pair(kImgInvalid1, kImgInvalid2);
    invalid_pair.is_valid = false;
    view_graph.image_pairs.emplace(invalid_pair.pair_id, invalid_pair);
  }

  std::unordered_map<frame_t, Frame> frames;
  frames.emplace(kFrameValid1, Frame());
  frames.emplace(kFrameValid2, Frame());
  frames.emplace(kFrameInvalid1, Frame());
  frames.emplace(kFrameInvalid2, Frame());

  const Eigen::Vector3d t_valid1(1.0, 0.0, 0.0);
  const Eigen::Vector3d t_valid2(0.0, 1.0, 0.0);
  const Eigen::Vector3d t_invalid1(0.0, 0.0, 1.0);
  const Eigen::Vector3d t_invalid2(1.0, 1.0, 1.0);

  SetFrameTranslation(frames[kFrameValid1], t_valid1);
  SetFrameTranslation(frames[kFrameValid2], t_valid2);
  SetFrameTranslation(frames[kFrameInvalid1], t_invalid1);
  SetFrameTranslation(frames[kFrameInvalid2], t_invalid2);

  std::unordered_map<track_t, Track> tracks;

  positioner.InitializeRandomPositions(view_graph, frames, images, tracks);

  // For the "random disabled" branch:
  // * valid frames may be updated to CenterFromPose(...)
  // * frames only referenced by invalid pairs must be treated as unconstrained
  //   and therefore must keep their original translations.

  const Eigen::Vector3d invalid1_after = GetFrameTranslation(frames[kFrameInvalid1]);
  const Eigen::Vector3d invalid2_after = GetFrameTranslation(frames[kFrameInvalid2]);

  EXPECT_DOUBLE_EQ(invalid1_after.x(), t_invalid1.x());
  EXPECT_DOUBLE_EQ(invalid1_after.y(), t_invalid1.y());
  EXPECT_DOUBLE_EQ(invalid1_after.z(), t_invalid1.z());

  EXPECT_DOUBLE_EQ(invalid2_after.x(), t_invalid2.x());
  EXPECT_DOUBLE_EQ(invalid2_after.y(), t_invalid2.y());
  EXPECT_DOUBLE_EQ(invalid2_after.z(), t_invalid2.z());
}

}  // namespace glomap
