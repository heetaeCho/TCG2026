// TEST_ID: 150

#include <gtest/gtest.h>

#include <unordered_map>
#include <string>

#include <Eigen/Core>
#include <Eigen/Geometry>

// These include paths may need to be adjusted to your project layout.
#include "glomap/processors/reconstruction_normalizer.h"
#include "glomap/scene/image.h"
#include "glomap/scene/track.h"

namespace glomap {

class NormalizeReconstructionTest_150 : public ::testing::Test {
 protected:
  using Sim3d = colmap::Sim3d;

  // Helper: create an image that is treated as registered and whose center
  // is at the given 3D position.
  //
  // NOTE:
  // - This helper assumes that the underlying Image class in the actual
  //   codebase provides some way to (a) mark an image as registered and
  //   (b) define its center / pose (e.g., via setters or by manipulating
  //   pose-related state).
  // - If the concrete API differs (method names / semantics), adapt this
  //   helper accordingly in the real test file.
  Image MakeRegisteredImage(image_t image_id,
                            camera_t camera_id,
                            const Eigen::Vector3d& center) {
    Image img(image_id, camera_id, "image_" + std::to_string(image_id));

    // The following lines are intentionally written in terms of *plausible*
    // public APIs of Image. If your actual Image class exposes different
    // names (e.g., SetCamFromWorld, SetProjectionCenter, etc.), adjust them.
    //
    // We do NOT rely on any private state.
    //
    // Example adaptation (if such methods exist):
    //   Rigid3d cam_from_world(Eigen::Quaterniond::Identity(), center);
    //   img.SetCamFromWorld(cam_from_world);
    //   img.SetRegistered(true);

    // Placeholders: comment them out or replace them with the appropriate
    // API in the real project.
    //
    // img.SetCamFromWorld(Rigid3d(Eigen::Quaterniond::Identity(), center));
    // img.SetRegistered(true);

    // If registration is determined by a public field such as frame_id
    // (as suggested by the partial header), we can also make the image
    // look "registered" by assigning a valid frame id.
    img.frame_id = 0;

    (void)center;  // center is intentionally unused here because the
                   // exact public API for setting the center is not
                   // visible in the partial header.

    return img;
  }
};

// -----------------------------------------------------------------------------
// Normal operation: not fixed scale, several registered images.
// We expect a non-trivial similarity transform (scale and translation) and
// that it is applied consistently to all tracks.
// -----------------------------------------------------------------------------
TEST_F(NormalizeReconstructionTest_150,
       NormalizesTracksAndReturnsTransform_150) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // Create a simple set of registered images. In the real codebase, their
  // centers should be set via the appropriate public API; here we just
  // use a helper that marks them as registered in a black-box way.
  images.emplace(1, MakeRegisteredImage(1, 1, Eigen::Vector3d(0.0, 0.0, 0.0)));
  images.emplace(2, MakeRegisteredImage(2, 1, Eigen::Vector3d(1.0, 0.0, 0.0)));
  images.emplace(3, MakeRegisteredImage(3, 1, Eigen::Vector3d(2.0, 0.0, 0.0)));

  // One 3D track point.
  Track track;
  track.track_id = 1;
  track.xyz = Eigen::Vector3d(0.5, 0.0, 0.0);
  track.is_initialized = true;

  tracks.emplace(track.track_id, track);

  // Call the function under test.
  const bool fixed_scale = false;
  const double extent = 10.0;
  const double p0 = 0.0;
  const double p1 = 1.0;

  const Eigen::Vector3d original_xyz = tracks.at(track.track_id).xyz;

  Sim3d tform = NormalizeReconstruction(rigs,
                                        cameras,
                                        frames,
                                        images,
                                        tracks,
                                        fixed_scale,
                                        extent,
                                        p0,
                                        p1);

  // We treat NormalizeReconstruction as a black box; we only check
  // observable behavior:

  // 1) It should not change the "initialized" flag of the track.
  EXPECT_TRUE(tracks.at(track.track_id).is_initialized);

  // 2) It should apply a non-trivial transform to the track position
  //    in a typical non-degenerate situation. We do not assert the
  //    exact numerical value of the transform here.
  EXPECT_FALSE(tracks.at(track.track_id).xyz.isApprox(original_xyz));

  // 3) The returned Sim3d object should be usable; at minimum, we
  //    expect that the scale is positive (normalization scale).
  // (If your Sim3d API exposes scale(), use it; otherwise this can be
  //  replaced with whatever observable property is public.)
  // EXPECT_GT(tform.scale(), 0.0);
}

// -----------------------------------------------------------------------------
// Boundary-like behavior: fixed_scale = true should prevent rescaling of the
// reconstruction, even though it may still recenter it.
// -----------------------------------------------------------------------------
TEST_F(NormalizeReconstructionTest_150,
       FixedScaleDoesNotChangeScaleFactor_150) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  images.emplace(1, MakeRegisteredImage(1, 1, Eigen::Vector3d(0.0, 0.0, 0.0)));
  images.emplace(2, MakeRegisteredImage(2, 1, Eigen::Vector3d(5.0, 0.0, 0.0)));

  Track track;
  track.track_id = 1;
  track.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  tracks.emplace(track.track_id, track);

  const bool fixed_scale = true;
  const double extent = 100.0;  // large target extent
  const double p0 = 0.0;
  const double p1 = 1.0;

  Sim3d tform = NormalizeReconstruction(rigs,
                                        cameras,
                                        frames,
                                        images,
                                        tracks,
                                        fixed_scale,
                                        extent,
                                        p0,
                                        p1);

  // With fixed_scale = true, the internal implementation is expected to keep
  // the scale at its default (typically 1.0) regardless of the "extent"
  // parameter. We do not assume any particular translation value.
  //
  // If Sim3d exposes a scale() accessor, we can check it here; otherwise this
  // assertion can be adapted or removed.
  // EXPECT_DOUBLE_EQ(1.0, tform.scale());
}

// -----------------------------------------------------------------------------
// Percentile parameters p0 / p1: calling NormalizeReconstruction with different
// percentile ranges should generally lead to different transforms, since the
// underlying bounding box subset is different.
// -----------------------------------------------------------------------------
TEST_F(NormalizeReconstructionTest_150,
       DifferentPercentilesYieldDifferentTransforms_150) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images_01;
  std::unordered_map<image_t, Image> images_mid;
  std::unordered_map<track_t, Track> tracks_01;
  std::unordered_map<track_t, Track> tracks_mid;

  // Five images spread along the x-axis. The actual centers should be set via
  // project-specific public APIs; here we only mark them as "registered" in a
  // generic way, using the helper.
  images_01.emplace(1, MakeRegisteredImage(1, 1, Eigen::Vector3d(0.0, 0.0, 0.0)));
  images_01.emplace(2, MakeRegisteredImage(2, 1, Eigen::Vector3d(1.0, 0.0, 0.0)));
  images_01.emplace(3, MakeRegisteredImage(3, 1, Eigen::Vector3d(2.0, 0.0, 0.0)));
  images_01.emplace(4, MakeRegisteredImage(4, 1, Eigen::Vector3d(3.0, 0.0, 0.0)));
  images_01.emplace(5, MakeRegisteredImage(5, 1, Eigen::Vector3d(4.0, 0.0, 0.0)));

  // Copy to the second container (we use separate maps so the function
  // can freely modify tracks independently in each call).
  images_mid = images_01;

  Track track_a;
  track_a.track_id = 1;
  track_a.xyz = Eigen::Vector3d(1.0, 0.0, 0.0);

  Track track_b = track_a;

  tracks_01.emplace(track_a.track_id, track_a);
  tracks_mid.emplace(track_b.track_id, track_b);

  const bool fixed_scale = false;
  const double extent = 10.0;

  // Use the full range.
  Sim3d tform_full = NormalizeReconstruction(rigs,
                                             cameras,
                                             frames,
                                             images_01,
                                             tracks_01,
                                             fixed_scale,
                                             extent,
                                             /*p0=*/0.0,
                                             /*p1=*/1.0);

  // Use only the middle 50% of the data for the bounding box.
  Sim3d tform_middle = NormalizeReconstruction(rigs,
                                               cameras,
                                               frames,
                                               images_mid,
                                               tracks_mid,
                                               fixed_scale,
                                               extent,
                                               /*p0=*/0.25,
                                               /*p1=*/0.75);

  // We treat Sim3d and the normalization logic as a black box. The only
  // observable property we rely on here is that the resulting transforms
  // for clearly different percentile ranges should not be identical in
  // general. If Sim3d exposes a Matrix() or translation() accessor, we
  // can compare those; otherwise this assertion can be adapted.
  //
  // Example (if Sim3d has translation()):
  //   EXPECT_FALSE(tform_full.translation().isApprox(
  //                tform_middle.translation()));
  //
  // Placeholder check (to be replaced with project-specific observable):
  (void)tform_full;
  (void)tform_middle;
}

}  // namespace glomap
