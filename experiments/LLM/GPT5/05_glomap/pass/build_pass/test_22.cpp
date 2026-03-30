#include <gtest/gtest.h>

#include <unordered_map>

#include "glomap/estimators/rotation_initializer.h"

namespace {

using glomap::ConvertRotationsFromImageToRig;
using glomap::Frame;
using glomap::Image;
using glomap::Rigid3d;
using glomap::frame_t;
using glomap::image_t;
using glomap::rig_t;
using glomap::Rig;

// Simple helper to construct empty containers for readability.
struct RotationInitializerEnvironment_22 {
  std::unordered_map<image_t, Rigid3d> cam_from_worlds;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
};

// ---------------------------------------------------------------------------
// Test 1: Basic contract — function should succeed and be no-op on empty input.
// ---------------------------------------------------------------------------
TEST(RotationInitializerTest_22, EmptyInputsReturnTrue_22) {
  RotationInitializerEnvironment_22 env;

  const bool result = ConvertRotationsFromImageToRig(
      env.cam_from_worlds, env.images, env.rigs, env.frames);

  EXPECT_TRUE(result);
  EXPECT_TRUE(env.cam_from_worlds.empty());
  EXPECT_TRUE(env.images.empty());
  EXPECT_TRUE(env.rigs.empty());
  EXPECT_TRUE(env.frames.empty());
}

// ---------------------------------------------------------------------------
// Test 2: Non-empty rigs / frames with default-constructed objects.
// Verifies that the function still returns true and does not invalidate the
// containers when there is no useful data to process (e.g., no images).
// ---------------------------------------------------------------------------
TEST(RotationInitializerTest_22, DefaultConstructedRigsAndFramesAreHandled_22) {
  RotationInitializerEnvironment_22 env;

  // Insert a default rig and frame. We intentionally do not attach any images,
  // so the implementation has nothing to convert, but must still succeed.
  const rig_t rig_id = static_cast<rig_t>(1);
  const frame_t frame_id = static_cast<frame_t>(1);

  env.rigs.emplace(rig_id, Rig{});
  env.frames.emplace(frame_id, Frame{});

  ASSERT_EQ(env.rigs.size(), 1u);
  ASSERT_EQ(env.frames.size(), 1u);

  const bool result = ConvertRotationsFromImageToRig(
      env.cam_from_worlds, env.images, env.rigs, env.frames);

  EXPECT_TRUE(result);
  // The function should not erase or invalidate existing entries in this
  // degenerate case.
  EXPECT_EQ(env.rigs.size(), 1u);
  EXPECT_EQ(env.frames.size(), 1u);
}

// ---------------------------------------------------------------------------
// Test 3: Images present but with no usable registration information.
// Verifies that the function still returns true and does not crash or modify
// unrelated data when there is no registered image to work with.
// ---------------------------------------------------------------------------
TEST(RotationInitializerTest_22, UnusableImagesDoNotCauseFailure_22) {
  RotationInitializerEnvironment_22 env;

  const image_t img_id = static_cast<image_t>(5);
  const rig_t rig_id = static_cast<rig_t>(3);
  const frame_t frame_id = static_cast<frame_t>(7);

  // Default Image / Frame / Rig objects. We rely only on the fact that they
  // are default-constructible and that the function must be robust to cases
  // where there is no registered reference image in a frame.
  env.images.emplace(img_id, Image{});
  env.rigs.emplace(rig_id, Rig{});
  env.frames.emplace(frame_id, Frame{});

  const std::size_t rigs_before = env.rigs.size();
  const std::size_t frames_before = env.frames.size();
  const std::size_t images_before = env.images.size();

  const bool result = ConvertRotationsFromImageToRig(
      env.cam_from_worlds, env.images, env.rigs, env.frames);

  EXPECT_TRUE(result);
  // Containers should remain structurally valid.
  EXPECT_EQ(env.rigs.size(), rigs_before);
  EXPECT_EQ(env.frames.size(), frames_before);
  EXPECT_EQ(env.images.size(), images_before);
}

}  // namespace
