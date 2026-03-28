// File: colmap_converter_test_120.cc

#include <gtest/gtest.h>

#include "glomap/io/colmap_converter.h"
#include "glomap/scene/camera.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/image.h"
// If Rig / Track / type aliases are defined in separate headers, include them here.
#include "glomap/scene/rig.h"
#include "glomap/scene/track.h"

#include <colmap/scene/reconstruction.h>

namespace {

using glomap::Camera;
using glomap::Frame;
using glomap::Image;
using glomap::Rig;
using glomap::Track;

class ConvertColmapToGlomapTest_120 : public ::testing::Test {
 protected:
  colmap::Reconstruction reconstruction_;

  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

// -----------------------------------------------------------------------------
// 1) Boundary: empty reconstruction; existing cameras/images must be cleared,
//    rigs / frames must not be cleared implicitly.
// -----------------------------------------------------------------------------
TEST_F(ConvertColmapToGlomapTest_120,
       ClearsExistingCamerasAndImagesWhenNoColmapData_120) {
  // Pre-populate maps to observe clearing behavior.
  rigs_.emplace(static_cast<rig_t>(10), Rig());
  frames_.emplace(static_cast<frame_t>(20), Frame());
  cameras_.emplace(static_cast<camera_t>(1), Camera());
  images_.emplace(static_cast<image_t>(2), Image());

  const std::size_t rigs_before   = rigs_.size();
  const std::size_t frames_before = frames_.size();

  glomap::ConvertColmapToGlomap(
      reconstruction_, rigs_, cameras_, frames_, images_, tracks_);

  // Cameras and images must be cleared unconditionally.
  EXPECT_TRUE(cameras_.empty());
  EXPECT_TRUE(images_.empty());

  // Rigs / frames should not be cleared just because reconstruction is empty.
  EXPECT_EQ(rigs_before, rigs_.size());
  EXPECT_EQ(frames_before, frames_.size());
}

// -----------------------------------------------------------------------------
// 2) Normal: cameras in colmap::Reconstruction are copied into glomap cameras_.
// -----------------------------------------------------------------------------
TEST_F(ConvertColmapToGlomapTest_120,
       PopulatesCamerasFromReconstruction_120) {
  // Create a simple COLMAP camera and add it to the reconstruction.
  colmap::Camera colmap_camera;
  // The exact intrinsic values are irrelevant for this black-box test.
  const camera_t camera_id = reconstruction_.AddCamera(colmap_camera);

  ASSERT_TRUE(cameras_.empty());

  glomap::ConvertColmapToGlomap(
      reconstruction_, rigs_, cameras_, frames_, images_, tracks_);

  // One camera should be present with the same ID.
  EXPECT_EQ(1u, cameras_.size());
  auto it = cameras_.find(camera_id);
  EXPECT_NE(it, cameras_.end());
}

// -----------------------------------------------------------------------------
// 3) Normal: images in colmap::Reconstruction become glomap::Image entries,
//    with camera id, file name, frame id and 2D feature positions copied.
// -----------------------------------------------------------------------------
TEST_F(ConvertColmapToGlomapTest_120,
       PopulatesImagesAndFeaturesFromReconstruction_120) {
  // Prepare a camera so the COLMAP image can reference it.
  colmap::Camera colmap_camera;
  const camera_t camera_id = reconstruction_.AddCamera(colmap_camera);

  // Prepare a frame in the glomap frame map and let the image refer to it.
  const frame_t frame_id = static_cast<frame_t>(7);
  frames_.emplace(frame_id, Frame());

  // Build a COLMAP image.
  colmap::Image colmap_image;
  colmap_image.SetImageId(static_cast<image_t>(3));
  colmap_image.SetCameraId(camera_id);
  colmap_image.SetName("test_image.jpg");
  colmap_image.SetFrameId(frame_id);

  // Create a couple of 2D points.
  std::vector<Eigen::Vector2d> xy(2);
  xy[0] = Eigen::Vector2d(10.0, 20.0);
  xy[1] = Eigen::Vector2d(30.0, 40.0);

  // Set them on the image via the public COLMAP API.
  colmap_image.SetPoints2D(xy);

  // Add the image to the reconstruction.
  const image_t image_id = reconstruction_.AddImage(colmap_image);

  glomap::ConvertColmapToGlomap(
      reconstruction_, rigs_, cameras_, frames_, images_, tracks_);

  // One image should be present.
  ASSERT_EQ(1u, images_.size());
  auto img_it = images_.find(image_id);
  ASSERT_NE(img_it, images_.end());

  const Image& glomap_image = img_it->second;

  // Camera id and filename should be propagated.
  EXPECT_EQ(camera_id, glomap_image.camera_id);
  EXPECT_EQ(std::string("test_image.jpg"), glomap_image.file_name);

  // Frame relationship: id is copied and frame_ptr points to the stored frame.
  EXPECT_EQ(frame_id, glomap_image.frame_id);
  ASSERT_NE(nullptr, glomap_image.frame_ptr);
  EXPECT_EQ(&frames_[frame_id], glomap_image.frame_ptr);

  // 2D features should match the COLMAP Points2D XY coordinates.
  ASSERT_EQ(xy.size(), glomap_image.features.size());
  EXPECT_EQ(xy[0], glomap_image.features[0]);
  EXPECT_EQ(xy[1], glomap_image.features[1]);
}

// -----------------------------------------------------------------------------
// 4) Boundary / error path: image refers to a frame that is *not* in frames_;
//    frame_ptr should be nullptr, but frame_id should still be copied.
// -----------------------------------------------------------------------------
TEST_F(ConvertColmapToGlomapTest_120,
       SetsNullFramePtrWhenFrameIsMissing_120) {
  // Camera for the image.
  colmap::Camera colmap_camera;
  const camera_t camera_id = reconstruction_.AddCamera(colmap_camera);

  // No corresponding entry in frames_ for this frame id.
  const frame_t missing_frame_id = static_cast<frame_t>(42);

  colmap::Image colmap_image;
  colmap_image.SetImageId(static_cast<image_t>(5));
  colmap_image.SetCameraId(camera_id);
  colmap_image.SetName("no_frame.jpg");
  colmap_image.SetFrameId(missing_frame_id);

  // A single 2D point is enough to exercise the feature loop.
  std::vector<Eigen::Vector2d> xy(1);
  xy[0] = Eigen::Vector2d(1.0, 2.0);
  colmap_image.SetPoints2D(xy);

  const image_t image_id = reconstruction_.AddImage(colmap_image);

  glomap::ConvertColmapToGlomap(
      reconstruction_, rigs_, cameras_, frames_, images_, tracks_);

  auto img_it = images_.find(image_id);
  ASSERT_NE(img_it, images_.end());

  const Image& glomap_image = img_it->second;

  // Frame id is copied, but pointer should be null because the frame map
  // doesn't contain that frame id.
  EXPECT_EQ(missing_frame_id, glomap_image.frame_id);
  EXPECT_EQ(nullptr, glomap_image.frame_ptr);

  // Features still copied correctly.
  ASSERT_EQ(1u, glomap_image.features.size());
  EXPECT_EQ(xy[0], glomap_image.features[0]);
}

// -----------------------------------------------------------------------------
// 5) Boundary: Frames coming from COLMAP should set is_registered depending
//    on HasPose() result. Here we only check default (no pose) path, treating
//    the COLMAP Frame as a black box.
// -----------------------------------------------------------------------------
TEST_F(ConvertColmapToGlomapTest_120,
       SetsFrameRegisteredFlagFromColmapFramePose_120) {
  // Create a default COLMAP frame (assumed to have no pose).
  colmap::Frame colmap_frame;
  const frame_t frame_id = static_cast<frame_t>(11);

  // Insert it directly into the reconstruction's frames container using
  // its public non-const accessor, without assuming anything about internals.
  reconstruction_.Frames().emplace(frame_id, colmap_frame);

  glomap::ConvertColmapToGlomap(
      reconstruction_, rigs_, cameras_, frames_, images_, tracks_);

  auto fr_it = frames_.find(frame_id);
  ASSERT_NE(fr_it, frames_.end());

  const Frame& glomap_frame = fr_it->second;

  // With default-constructed COLMAP frame, HasPose() is expected to be false,
  // so is_registered should be false as well.
  EXPECT_FALSE(glomap_frame.is_registered);
}

}  // namespace
