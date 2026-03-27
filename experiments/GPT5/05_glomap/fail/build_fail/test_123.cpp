// File: colmap_converter_create_frame_for_image_test_123.cc

#include <gtest/gtest.h>

#include <unordered_map>

#include "glomap/io/colmap_converter.h"
#include "glomap/scene/image.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/types_sfm.h"

// If COLMAP constants are exposed via a different header in your setup,
// you may need to adjust this include accordingly.
#include <colmap/base/reconstruction.h>

namespace {

using glomap::CreateFrameForImage;
using glomap::Image;
using glomap::Frame;
using glomap::Rigid3d;
using glomap::frame_t;
using glomap::image_t;
using glomap::camera_t;
// rig_t / Rig are brought in by the colmap_converter header chain.
using glomap::rig_t;
using glomap::Rig;

}  // namespace

// ----------------------------------------------------------------------------
// TEST 1: Normal operation with explicitly provided frame_id and rig_id.
// Verifies that:
//  - A new entry is added to `frames` with the given frame_id.
//  - Image::frame_id is set to the provided frame_id.
//  - Image::frame_ptr points to the corresponding Frame in the map.
// ----------------------------------------------------------------------------
TEST(CreateFrameForImageTest_123, UsesProvidedIdsAndUpdatesImageAndFrames_123) {
  // Arrange
  const image_t kImageId = 10;
  const camera_t kCameraId = 20;
  Image image(kImageId, kCameraId, "test_image_123.jpg");

  // Make sure initial state is “uninitialized”.
  image.frame_id = -1;
  image.frame_ptr = nullptr;

  Rigid3d cam_from_world;  // Default-constructed pose is fine; we treat as opaque.

  std::unordered_map<rig_t, Rig> rigs;      // No rigs needed for this test.
  std::unordered_map<frame_t, Frame> frames;

  const rig_t kRigId = static_cast<rig_t>(7);
  const frame_t kFrameId = static_cast<frame_t>(11);

  // Act
  CreateFrameForImage(cam_from_world, image, rigs, frames, kRigId, kFrameId);

  // Assert: frames map updated with the provided frame_id.
  ASSERT_EQ(frames.size(), 1u);
  auto it = frames.find(kFrameId);
  ASSERT_NE(it, frames.end());

  // Assert: image now references that frame.
  EXPECT_EQ(image.frame_id, kFrameId);
  ASSERT_NE(image.frame_ptr, nullptr);
  EXPECT_EQ(image.frame_ptr, &it->second);
}

// ----------------------------------------------------------------------------
// TEST 2: Invalid frame & rig IDs -> fall back to image_id and camera_id.
// Verifies that when frame_id == colmap::kInvalidFrameId and
// rig_id == colmap::kInvalidRigId, the function:
//  - Uses image.image_id as frame_id (key in frames and image.frame_id).
//  - Still sets image.frame_ptr to the frame stored in `frames` under that key.
// ----------------------------------------------------------------------------
TEST(CreateFrameForImageTest_123, UsesImageAndCameraIdsWhenInvalidIdsProvided_123) {
  // Arrange
  const image_t kImageId = 5;
  const camera_t kCameraId = 6;
  Image image(kImageId, kCameraId, "fallback_ids_123.png");

  image.frame_id = -1;
  image.frame_ptr = nullptr;

  Rigid3d cam_from_world;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  const rig_t invalid_rig_id = colmap::kInvalidRigId;
  const frame_t invalid_frame_id = colmap::kInvalidFrameId;

  // Act
  CreateFrameForImage(
      cam_from_world, image, rigs, frames, invalid_rig_id, invalid_frame_id);

  // Assert: frame keyed by image_id exists.
  ASSERT_EQ(frames.size(), 1u);
  auto it = frames.find(static_cast<frame_t>(kImageId));
  ASSERT_NE(it, frames.end());

  // Assert: image.frame_id falls back to image_id.
  EXPECT_EQ(image.frame_id, static_cast<frame_t>(kImageId));

  // Assert: image.frame_ptr points to that stored frame.
  ASSERT_NE(image.frame_ptr, nullptr);
  EXPECT_EQ(image.frame_ptr, &it->second);
}

// ----------------------------------------------------------------------------
// TEST 3: Invalid frame_id but valid rig_id.
// From the interface we can only *observe* that:
//  - The frame_id still falls back to image.image_id.
//  - Image's frame pointer points into the frames map for that key.
// We do NOT inspect any rig-related internal state of Frame.
// ----------------------------------------------------------------------------
TEST(CreateFrameForImageTest_123, FallsBackFrameIdButKeepsProvidedRigId_123) {
  // Arrange
  const image_t kImageId = 42;
  const camera_t kCameraId = 9;
  Image image(kImageId, kCameraId, "partial_fallback_123.jpg");

  image.frame_id = -1;
  image.frame_ptr = nullptr;

  Rigid3d cam_from_world;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  // Provide a “valid looking” rig_id and an invalid frame_id.
  const rig_t valid_rig_id = static_cast<rig_t>(3);
  const frame_t invalid_frame_id = colmap::kInvalidFrameId;

  // Act
  CreateFrameForImage(
      cam_from_world, image, rigs, frames, valid_rig_id, invalid_frame_id);

  // Assert: frame keyed by image_id exists.
  ASSERT_EQ(frames.size(), 1u);
  auto it = frames.find(static_cast<frame_t>(kImageId));
  ASSERT_NE(it, frames.end());

  // Assert: frame_id still falls back to image_id.
  EXPECT_EQ(image.frame_id, static_cast<frame_t>(kImageId));

  // Assert: image points to the frame stored in the map.
  ASSERT_NE(image.frame_ptr, nullptr);
  EXPECT_EQ(image.frame_ptr, &it->second);
}

// ----------------------------------------------------------------------------
// TEST 4: Multiple calls for the same Image.
// Verifies that:
//  - A first call creates a frame and sets image.frame_id / frame_ptr.
//  - A second call with a different frame_id creates another entry and updates
//    image.frame_id / frame_ptr to the new one.
// This checks that repeated use keeps the public Image/frames relationship
// consistent.
// ----------------------------------------------------------------------------
TEST(CreateFrameForImageTest_123, SubsequentCallsUpdateImageFrameReference_123) {
  // Arrange
  const image_t kImageId = 100;
  const camera_t kCameraId = 200;
  Image image(kImageId, kCameraId, "multi_call_123.jpg");

  image.frame_id = -1;
  image.frame_ptr = nullptr;

  Rigid3d cam_from_world;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  const rig_t rig_id_1 = static_cast<rig_t>(1);
  const frame_t frame_id_1 = static_cast<frame_t>(10);

  const rig_t rig_id_2 = static_cast<rig_t>(2);
  const frame_t frame_id_2 = static_cast<frame_t>(20);

  // Act: first call.
  CreateFrameForImage(
      cam_from_world, image, rigs, frames, rig_id_1, frame_id_1);

  // Check intermediate state.
  ASSERT_EQ(frames.size(), 1u);
  auto it1 = frames.find(frame_id_1);
  ASSERT_NE(it1, frames.end());
  EXPECT_EQ(image.frame_id, frame_id_1);
  ASSERT_NE(image.frame_ptr, nullptr);
  EXPECT_EQ(image.frame_ptr, &it1->second);

  // Act: second call with different frame_id / rig_id.
  CreateFrameForImage(
      cam_from_world, image, rigs, frames, rig_id_2, frame_id_2);

  // Assert: two distinct frame entries now exist.
  ASSERT_EQ(frames.size(), 2u);
  auto it2 = frames.find(frame_id_2);
  ASSERT_NE(it2, frames.end());

  // Assert: image now references the second frame.
  EXPECT_EQ(image.frame_id, frame_id_2);
  ASSERT_NE(image.frame_ptr, nullptr);
  EXPECT_EQ(image.frame_ptr, &it2->second);
}
