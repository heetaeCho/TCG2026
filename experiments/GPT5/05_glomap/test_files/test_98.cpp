#include <gtest/gtest.h>

#include "glomap/estimators/bundle_adjustment.h"

namespace {

class BundleAdjusterTest_98 : public ::testing::Test {
protected:
  void SetUp() override {
    // Use default options; we treat BundleAdjuster as a black box
    options_ = glomap::BundleAdjusterOptions();
  }

  glomap::BundleAdjusterOptions options_;
};

// Images map is empty -> Solve should return false without attempting optimization.
TEST_F(BundleAdjusterTest_98, SolveReturnsFalseWhenImagesEmpty_98) {
  glomap::BundleAdjuster adjuster(options_);

  std::unordered_map<glomap::rig_t, glomap::Rig> rigs;
  std::unordered_map<glomap::camera_t, glomap::Camera> cameras;
  std::unordered_map<glomap::frame_t, glomap::Frame> frames;
  std::unordered_map<glomap::image_t, glomap::Image> images;  // empty
  std::unordered_map<glomap::track_t, glomap::Track> tracks;

  const bool result = adjuster.Solve(rigs, cameras, frames, images, tracks);

  EXPECT_FALSE(result);
}

// Tracks map is empty but images is non-empty -> Solve should return false.
TEST_F(BundleAdjusterTest_98, SolveReturnsFalseWhenTracksEmpty_98) {
  glomap::BundleAdjuster adjuster(options_);

  std::unordered_map<glomap::rig_t, glomap::Rig> rigs;
  std::unordered_map<glomap::camera_t, glomap::Camera> cameras;
  std::unordered_map<glomap::frame_t, glomap::Frame> frames;
  std::unordered_map<glomap::image_t, glomap::Image> images;
  std::unordered_map<glomap::track_t, glomap::Track> tracks;  // empty

  // Ensure at least one image is present so we pass the first early-exit check.
  images.emplace(static_cast<glomap::image_t>(1), glomap::Image());

  const bool result = adjuster.Solve(rigs, cameras, frames, images, tracks);

  EXPECT_FALSE(result);
}

// Normal case: both images and tracks are non-empty. We only verify that
// Solve can be called without throwing, treating it as a smoke test.
// We do NOT assert on the return value, since that depends on the underlying
// optimizer (ceres) which we treat as a black box.
TEST_F(BundleAdjusterTest_98, SolveDoesNotThrowWhenImagesAndTracksNonEmpty_98) {
  glomap::BundleAdjuster adjuster(options_);

  std::unordered_map<glomap::rig_t, glomap::Rig> rigs;
  std::unordered_map<glomap::camera_t, glomap::Camera> cameras;
  std::unordered_map<glomap::frame_t, glomap::Frame> frames;
  std::unordered_map<glomap::image_t, glomap::Image> images;
  std::unordered_map<glomap::track_t, glomap::Track> tracks;

  // Insert minimal entries to satisfy the preconditions.
  rigs.emplace(static_cast<glomap::rig_t>(1), glomap::Rig());
  cameras.emplace(static_cast<glomap::camera_t>(1), glomap::Camera());
  frames.emplace(static_cast<glomap::frame_t>(1), glomap::Frame());
  images.emplace(static_cast<glomap::image_t>(1), glomap::Image());
  tracks.emplace(static_cast<glomap::track_t>(1), glomap::Track());

  EXPECT_NO_THROW({
    (void)adjuster.Solve(rigs, cameras, frames, images, tracks);
  });
}

}  // namespace
