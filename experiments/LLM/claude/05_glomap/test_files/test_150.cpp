#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/processors/reconstruction_normalizer.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/scene/image.h"
#include "glomap/scene/track.h"
#include "glomap/types.h"

#include <unordered_map>
#include <cmath>
#include <limits>

namespace glomap {
namespace {

class NormalizeReconstructionTest_150 : public ::testing::Test {
 protected:
  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;

  // Helper to create a registered image with a specific center position.
  // We set cam_from_world such that Center() returns the desired position.
  // Center() = -rotation^T * translation for a Rigid3d.
  // For identity rotation, Center() = -translation.
  void AddRegisteredImage(image_t id, const Eigen::Vector3d& center, frame_t frame_id) {
    Image img(id, 0, "img_" + std::to_string(id));
    img.camera_id = 0;
    img.frame_id = frame_id;

    // Ensure the frame exists and has a pose
    if (frames_.find(frame_id) == frames_.end()) {
      Frame frame;
      frame.frame_id = frame_id;
      frame.rig_id = 0;
      // Set pose: for identity rotation, translation = -center gives Center() = center
      Rigid3d rig_from_world;
      rig_from_world.rotation = Eigen::Quaterniond::Identity();
      rig_from_world.translation = -center;
      frame.SetRigFromWorld(rig_from_world);
      frames_[frame_id] = frame;
    }

    img.frame_ptr = &frames_[frame_id];

    // Ensure rig exists with identity sensor_from_rig for sensor 0
    if (rigs_.find(0) == rigs_.end()) {
      Rig rig;
      rig.rig_id = 0;
      rigs_[0] = rig;
    }

    images_[id] = img;
  }

  void AddUnregisteredImage(image_t id) {
    Image img(id, 0, "unreg_" + std::to_string(id));
    img.camera_id = 0;
    img.frame_id = -1;
    img.frame_ptr = nullptr;
    images_[id] = img;
  }

  void AddTrack(track_t id, const Eigen::Vector3d& xyz) {
    Track track;
    track.track_id = id;
    track.xyz = xyz;
    track.is_initialized = true;
    tracks_[id] = track;
  }
};

// Test basic normalization with a simple configuration
TEST_F(NormalizeReconstructionTest_150, BasicNormalization_150) {
  // Create 4 registered images at known positions
  AddRegisteredImage(0, Eigen::Vector3d(0, 0, 0), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 0, 0), 1);
  AddRegisteredImage(2, Eigen::Vector3d(0, 10, 0), 2);
  AddRegisteredImage(3, Eigen::Vector3d(10, 10, 10), 3);

  AddTrack(0, Eigen::Vector3d(5, 5, 5));

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  // The transformation should be valid (scale > 0)
  EXPECT_GT(tform.scale, 0.0);
}

// Test with fixed_scale = true (scale should remain 1.0)
TEST_F(NormalizeReconstructionTest_150, FixedScaleKeepsScaleOne_150) {
  AddRegisteredImage(0, Eigen::Vector3d(0, 0, 0), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 0, 0), 1);
  AddRegisteredImage(2, Eigen::Vector3d(0, 10, 0), 2);
  AddRegisteredImage(3, Eigen::Vector3d(10, 10, 10), 3);

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, true, 10.0, 0.1, 0.9);

  EXPECT_DOUBLE_EQ(tform.scale, 1.0);
}

// Test that tracks are transformed
TEST_F(NormalizeReconstructionTest_150, TracksAreTransformed_150) {
  AddRegisteredImage(0, Eigen::Vector3d(0, 0, 0), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 0, 0), 1);
  AddRegisteredImage(2, Eigen::Vector3d(0, 10, 0), 2);
  AddRegisteredImage(3, Eigen::Vector3d(0, 0, 10), 3);

  Eigen::Vector3d original_xyz(5, 5, 5);
  AddTrack(0, original_xyz);

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  // Track should be transformed: new_xyz = tform * original_xyz
  Eigen::Vector3d expected = tform * original_xyz;
  EXPECT_NEAR(tracks_[0].xyz(0), expected(0), 1e-6);
  EXPECT_NEAR(tracks_[0].xyz(1), expected(1), 1e-6);
  EXPECT_NEAR(tracks_[0].xyz(2), expected(2), 1e-6);
}

// Test with all images at the same position (zero extent)
TEST_F(NormalizeReconstructionTest_150, AllImagesAtSamePosition_150) {
  AddRegisteredImage(0, Eigen::Vector3d(5, 5, 5), 0);
  AddRegisteredImage(1, Eigen::Vector3d(5, 5, 5), 1);
  AddRegisteredImage(2, Eigen::Vector3d(5, 5, 5), 2);
  AddRegisteredImage(3, Eigen::Vector3d(5, 5, 5), 3);

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  // When extent is zero (all same position), scale should remain 1.0
  EXPECT_DOUBLE_EQ(tform.scale, 1.0);
}

// Test with exactly 3 images (boundary for P0/P1 calculation: size <= 3)
TEST_F(NormalizeReconstructionTest_150, ThreeRegisteredImages_150) {
  AddRegisteredImage(0, Eigen::Vector3d(0, 0, 0), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 10, 10), 1);
  AddRegisteredImage(2, Eigen::Vector3d(5, 5, 5), 2);

  AddTrack(0, Eigen::Vector3d(3, 3, 3));

  // With 3 images, P0 = 0, P1 = size-1 = 2
  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  EXPECT_GT(tform.scale, 0.0);
}

// Test with exactly 2 registered images
TEST_F(NormalizeReconstructionTest_150, TwoRegisteredImages_150) {
  AddRegisteredImage(0, Eigen::Vector3d(0, 0, 0), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 10, 10), 1);

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  EXPECT_GT(tform.scale, 0.0);
}

// Test with exactly 1 registered image (P0=0, P1=0, so single point)
TEST_F(NormalizeReconstructionTest_150, OneRegisteredImage_150) {
  AddRegisteredImage(0, Eigen::Vector3d(5, 5, 5), 0);

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  // Scale should be 1.0 since bbox_max == bbox_min
  EXPECT_DOUBLE_EQ(tform.scale, 1.0);
}

// Test that unregistered images are ignored
TEST_F(NormalizeReconstructionTest_150, UnregisteredImagesIgnored_150) {
  AddRegisteredImage(0, Eigen::Vector3d(0, 0, 0), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 10, 10), 1);
  AddRegisteredImage(2, Eigen::Vector3d(5, 5, 5), 2);
  AddRegisteredImage(3, Eigen::Vector3d(7, 7, 7), 3);
  AddUnregisteredImage(4);
  AddUnregisteredImage(5);

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  // Should succeed; unregistered images don't contribute to coordinate computation
  EXPECT_GT(tform.scale, 0.0);
}

// Test the returned transform is a Sim3d with identity rotation
TEST_F(NormalizeReconstructionTest_150, ReturnedTransformHasIdentityRotation_150) {
  AddRegisteredImage(0, Eigen::Vector3d(0, 0, 0), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 0, 0), 1);
  AddRegisteredImage(2, Eigen::Vector3d(0, 10, 0), 2);
  AddRegisteredImage(3, Eigen::Vector3d(0, 0, 10), 3);

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  // The code uses Identity rotation
  Eigen::Quaterniond identity = Eigen::Quaterniond::Identity();
  EXPECT_NEAR(tform.rotation.w(), identity.w(), 1e-10);
  EXPECT_NEAR(tform.rotation.x(), identity.x(), 1e-10);
  EXPECT_NEAR(tform.rotation.y(), identity.y(), 1e-10);
  EXPECT_NEAR(tform.rotation.z(), identity.z(), 1e-10);
}

// Test with different extent values
TEST_F(NormalizeReconstructionTest_150, DifferentExtentValues_150) {
  AddRegisteredImage(0, Eigen::Vector3d(0, 0, 0), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 0, 0), 1);
  AddRegisteredImage(2, Eigen::Vector3d(0, 10, 0), 2);
  AddRegisteredImage(3, Eigen::Vector3d(0, 0, 10), 3);

  auto rigs_copy = rigs_;
  auto cameras_copy = cameras_;
  auto frames_copy = frames_;
  auto images_copy = images_;
  auto tracks_copy = tracks_;

  colmap::Sim3d tform1 = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  colmap::Sim3d tform2 = NormalizeReconstruction(
      rigs_copy, cameras_copy, frames_copy, images_copy, tracks_copy, false, 20.0, 0.1, 0.9);

  // Scale with extent=20 should be double the scale with extent=10
  EXPECT_NEAR(tform2.scale, 2.0 * tform1.scale, 1e-6);
}

// Test with many images
TEST_F(NormalizeReconstructionTest_150, ManyImages_150) {
  for (int i = 0; i < 100; ++i) {
    Eigen::Vector3d center(static_cast<double>(i), 
                           static_cast<double>(i * 2), 
                           static_cast<double>(i * 3));
    AddRegisteredImage(i, center, i);
  }

  AddTrack(0, Eigen::Vector3d(50, 100, 150));

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  EXPECT_GT(tform.scale, 0.0);
  
  // Verify the track was transformed
  Eigen::Vector3d expected = tform * Eigen::Vector3d(50, 100, 150);
  EXPECT_NEAR(tracks_[0].xyz(0), expected(0), 1e-4);
  EXPECT_NEAR(tracks_[0].xyz(1), expected(1), 1e-4);
  EXPECT_NEAR(tracks_[0].xyz(2), expected(2), 1e-4);
}

// Test p0=0 and p1=1 uses full range
TEST_F(NormalizeReconstructionTest_150, FullPercentileRange_150) {
  AddRegisteredImage(0, Eigen::Vector3d(-10, -10, -10), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 10, 10), 1);
  AddRegisteredImage(2, Eigen::Vector3d(0, 0, 0), 2);
  AddRegisteredImage(3, Eigen::Vector3d(5, 5, 5), 3);

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.0, 1.0);

  EXPECT_GT(tform.scale, 0.0);
}

// Test with empty tracks map
TEST_F(NormalizeReconstructionTest_150, EmptyTracks_150) {
  AddRegisteredImage(0, Eigen::Vector3d(0, 0, 0), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 10, 10), 1);
  AddRegisteredImage(2, Eigen::Vector3d(5, 5, 5), 2);
  AddRegisteredImage(3, Eigen::Vector3d(7, 7, 7), 3);

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  EXPECT_GT(tform.scale, 0.0);
}

// Test that multiple tracks are all transformed
TEST_F(NormalizeReconstructionTest_150, MultipleTracksTransformed_150) {
  AddRegisteredImage(0, Eigen::Vector3d(0, 0, 0), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 0, 0), 1);
  AddRegisteredImage(2, Eigen::Vector3d(0, 10, 0), 2);
  AddRegisteredImage(3, Eigen::Vector3d(0, 0, 10), 3);

  Eigen::Vector3d p1(1, 2, 3);
  Eigen::Vector3d p2(4, 5, 6);
  Eigen::Vector3d p3(7, 8, 9);
  AddTrack(0, p1);
  AddTrack(1, p2);
  AddTrack(2, p3);

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  Eigen::Vector3d exp1 = tform * p1;
  Eigen::Vector3d exp2 = tform * p2;
  Eigen::Vector3d exp3 = tform * p3;

  EXPECT_NEAR(tracks_[0].xyz(0), exp1(0), 1e-6);
  EXPECT_NEAR(tracks_[0].xyz(1), exp1(1), 1e-6);
  EXPECT_NEAR(tracks_[0].xyz(2), exp1(2), 1e-6);

  EXPECT_NEAR(tracks_[1].xyz(0), exp2(0), 1e-6);
  EXPECT_NEAR(tracks_[1].xyz(1), exp2(1), 1e-6);
  EXPECT_NEAR(tracks_[1].xyz(2), exp2(2), 1e-6);

  EXPECT_NEAR(tracks_[2].xyz(0), exp3(0), 1e-6);
  EXPECT_NEAR(tracks_[2].xyz(1), exp3(1), 1e-6);
  EXPECT_NEAR(tracks_[2].xyz(2), exp3(2), 1e-6);
}

// Test centering: with fixed_scale, mean of registered images should map to origin
TEST_F(NormalizeReconstructionTest_150, CenteringWithFixedScale_150) {
  // Symmetric configuration: mean at (5,5,5)
  AddRegisteredImage(0, Eigen::Vector3d(0, 0, 0), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 10, 10), 1);
  AddRegisteredImage(2, Eigen::Vector3d(5, 5, 5), 2);
  AddRegisteredImage(3, Eigen::Vector3d(5, 5, 5), 3);

  // Add a track at what we expect the mean to be
  AddTrack(0, Eigen::Vector3d(5, 5, 5));

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, true, 10.0, 0.0, 1.0);

  // With fixed scale=1 and full percentile range, mean should be (5,5,5)
  // Track at (5,5,5) should be near origin after transformation
  EXPECT_NEAR(tracks_[0].xyz(0), 0.0, 1e-6);
  EXPECT_NEAR(tracks_[0].xyz(1), 0.0, 1e-6);
  EXPECT_NEAR(tracks_[0].xyz(2), 0.0, 1e-6);
}

// Test translation component of returned transform
TEST_F(NormalizeReconstructionTest_150, TranslationIsNegativeScaledMean_150) {
  AddRegisteredImage(0, Eigen::Vector3d(0, 0, 0), 0);
  AddRegisteredImage(1, Eigen::Vector3d(10, 10, 10), 1);
  AddRegisteredImage(2, Eigen::Vector3d(5, 5, 5), 2);
  AddRegisteredImage(3, Eigen::Vector3d(5, 5, 5), 3);

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, true, 10.0, 0.0, 1.0);

  // With full range p0=0, p1=1 and 4 images, mean = (0+5+5+10)/4 = 5 for each coord
  // translation = -scale * mean = -1 * (5,5,5) = (-5,-5,-5)
  EXPECT_NEAR(tform.translation(0), -5.0, 1e-6);
  EXPECT_NEAR(tform.translation(1), -5.0, 1e-6);
  EXPECT_NEAR(tform.translation(2), -5.0, 1e-6);
}

// Test with negative coordinates
TEST_F(NormalizeReconstructionTest_150, NegativeCoordinates_150) {
  AddRegisteredImage(0, Eigen::Vector3d(-10, -20, -30), 0);
  AddRegisteredImage(1, Eigen::Vector3d(-5, -10, -15), 1);
  AddRegisteredImage(2, Eigen::Vector3d(-2, -4, -6), 2);
  AddRegisteredImage(3, Eigen::Vector3d(-1, -2, -3), 3);

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  EXPECT_GT(tform.scale, 0.0);
}

// Test large number of images for percentile robustness
TEST_F(NormalizeReconstructionTest_150, PercentileTrimming_150) {
  // Add outlier images far away
  AddRegisteredImage(0, Eigen::Vector3d(-1000, -1000, -1000), 0);
  AddRegisteredImage(99, Eigen::Vector3d(1000, 1000, 1000), 99);
  
  // Add normal images
  for (int i = 1; i < 99; ++i) {
    Eigen::Vector3d center(static_cast<double>(i), 
                           static_cast<double>(i), 
                           static_cast<double>(i));
    AddRegisteredImage(i, center, i);
  }

  colmap::Sim3d tform = NormalizeReconstruction(
      rigs_, cameras_, frames_, images_, tracks_, false, 10.0, 0.1, 0.9);

  // The scale should be determined by the trimmed range, not the outliers
  // With p0=0.1, p1=0.9 and 100 images, P0=9, P1=89
  // The range should be around [9,89] not [-1000,1000]
  EXPECT_GT(tform.scale, 0.0);
}

}  // namespace
}  // namespace glomap
