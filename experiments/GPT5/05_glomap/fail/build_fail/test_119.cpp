// TEST_ID: 119

#include <gtest/gtest.h>

#include <unordered_map>

#include "glomap/io/colmap_converter.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/image.h"
#include "glomap/scene/track.h"

// If these headers exist in your codebase, prefer them for Camera/Rig/Reconstruction.
#include "colmap/base/reconstruction.h"
#include "colmap/base/camera.h"
#include "colmap/base/camera_rig.h"

namespace glomap {

class ConvertGlomapToColmapTest_119 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to create a simple track with given observations.
  Track MakeTrack(track_t id,
                  const Eigen::Vector3d& xyz,
                  const Eigen::Vector3ub& color,
                  const std::vector<Observation>& observations) {
    Track t;
    t.track_id = id;
    t.xyz = xyz;
    t.color = color;
    t.observations = observations;
    return t;
  }

  // Helper to create a simple image with N features.
  Image MakeImage(image_t image_id,
                  camera_t camera_id,
                  const std::string& name,
                  size_t num_features) {
    Image img(image_id, camera_id, name);
    img.features.resize(num_features);
    return img;
  }

  // Helper to create a simple frame.
  Frame MakeFrame(frame_t /*frame_id*/, bool is_registered, int cluster_id) {
    Frame f;
    f.is_registered = is_registered;
    f.cluster_id = cluster_id;
    return f;
  }
};

//------------------------------------------------------------------------------
// 1) Empty input → empty reconstruction
//------------------------------------------------------------------------------

TEST_F(ConvertGlomapToColmapTest_119, EmptyInputLeavesReconstructionEmpty_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  colmap::Reconstruction reconstruction;

  ConvertGlomapToColmap(rigs,
                        cameras,
                        frames,
                        images,
                        tracks,
                        reconstruction,
                        /*cluster_id=*/-1,
                        /*include_image_points=*/false);

  EXPECT_EQ(reconstruction.NumCameras(), 0);
  EXPECT_EQ(reconstruction.NumImages(), 0);
  EXPECT_EQ(reconstruction.NumPoints3D(), 0);
}

//------------------------------------------------------------------------------
// 2) Cameras are copied into the reconstruction
//------------------------------------------------------------------------------

TEST_F(ConvertGlomapToColmapTest_119, CamerasAreAddedToReconstruction_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  camera_t cam_id1 = 1;
  camera_t cam_id2 = 2;

  Camera cam1;
  Camera cam2;

  cameras.emplace(cam_id1, cam1);
  cameras.emplace(cam_id2, cam2);

  colmap::Reconstruction reconstruction;

  ConvertGlomapToColmap(rigs,
                        cameras,
                        frames,
                        images,
                        tracks,
                        reconstruction,
                        /*cluster_id=*/-1,
                        /*include_image_points=*/false);

  EXPECT_EQ(reconstruction.NumCameras(), cameras.size());
}

//------------------------------------------------------------------------------
// 3) Tracks with fewer than 2 observations are NOT turned into 3D points
//------------------------------------------------------------------------------

TEST_F(ConvertGlomapToColmapTest_119,
       TracksWithInsufficientObservationsAreIgnored_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // One camera & one image with a single feature.
  camera_t cam_id = 1;
  Camera cam;
  cameras.emplace(cam_id, cam);

  image_t img_id = 1;
  Image img = MakeImage(img_id, cam_id, "img1", /*num_features=*/1);
  images.emplace(img_id, img);

  // Track with only ONE observation (min_supports = 2 ⇒ this should be ignored).
  track_t track_id = 10;
  std::vector<Observation> observations = {Observation(img_id, 0)};
  Track tr = MakeTrack(track_id,
                       Eigen::Vector3d(1.0, 2.0, 3.0),
                       Eigen::Vector3ub(255, 0, 0),
                       observations);
  tracks.emplace(track_id, tr);

  colmap::Reconstruction reconstruction;

  ConvertGlomapToColmap(rigs,
                        cameras,
                        frames,
                        images,
                        tracks,
                        reconstruction,
                        /*cluster_id=*/-1,
                        /*include_image_points=*/false);

  // No 3D points should be created.
  EXPECT_EQ(reconstruction.NumPoints3D(), 0);
  EXPECT_FALSE(reconstruction.ExistsPoint3D(track_id));
}

//------------------------------------------------------------------------------
// 4) Tracks with at least 2 observations become 3D points
//------------------------------------------------------------------------------

TEST_F(ConvertGlomapToColmapTest_119,
       TracksWithEnoughObservationsBecomePoints3D_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  // One camera & one image with two features.
  camera_t cam_id = 1;
  Camera cam;
  cameras.emplace(cam_id, cam);

  image_t img_id = 1;
  Image img = MakeImage(img_id, cam_id, "img1", /*num_features=*/2);
  images.emplace(img_id, img);

  // Track with TWO observations on the same image (meets min_supports = 2).
  track_t track_id = 20;
  std::vector<Observation> observations = {
      Observation(img_id, 0),
      Observation(img_id, 1),
  };
  Track tr = MakeTrack(track_id,
                       Eigen::Vector3d(1.0, 2.0, 3.0),
                       Eigen::Vector3ub(10, 20, 30),
                       observations);
  tracks.emplace(track_id, tr);

  colmap::Reconstruction reconstruction;

  ConvertGlomapToColmap(rigs,
                        cameras,
                        frames,
                        images,
                        tracks,
                        reconstruction,
                        /*cluster_id=*/-1,
                        /*include_image_points=*/false);

  // A single 3D point should be created with this track_id.
  EXPECT_EQ(reconstruction.NumPoints3D(), 1);
  EXPECT_TRUE(reconstruction.ExistsPoint3D(track_id));

  const colmap::Point3D& p3d = reconstruction.Point3D(track_id);
  // Track must have at least 2 elements due to the min_supports condition.
  EXPECT_GE(p3d.track.Length(), 2);
}

//------------------------------------------------------------------------------
// 5) Image points get linked to 3D points when keep_points is true
//------------------------------------------------------------------------------

TEST_F(ConvertGlomapToColmapTest_119,
       ImagePointsAreAssociatedWithPoint3D_119) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  camera_t cam_id = 1;
  Camera cam;
  cameras.emplace(cam_id, cam);

  image_t img_id = 1;
  // Two features → indices 0 and 1.
  Image img = MakeImage(img_id, cam_id, "img1", /*num_features=*/2);
  images.emplace(img_id, img);

  // Track with two observations → enough to create a 3D point.
  track_t track_id = 30;
  std::vector<Observation> observations = {
      Observation(img_id, 0),
      Observation(img_id, 1),
  };
  Track tr = MakeTrack(track_id,
                       Eigen::Vector3d(1.0, 0.0, 0.0),
                       Eigen::Vector3ub(100, 150, 200),
                       observations);
  tracks.emplace(track_id, tr);

  colmap::Reconstruction reconstruction;

  // include_image_points = true ⇒ internal image_to_point3D logic is activated.
  ConvertGlomapToColmap(rigs,
                        cameras,
                        frames,
                        images,
                        tracks,
                        reconstruction,
                        /*cluster_id=*/-1,
                        /*include_image_points=*/true);

  ASSERT_TRUE(reconstruction.ExistsPoint3D(track_id));
  ASSERT_EQ(reconstruction.NumImages(), 1);

  const colmap::Image& colmap_img = reconstruction.Image(img_id);

  // In COLMAP, each 2D point can store a 3D point id; we expect them to be set.
  EXPECT_TRUE(colmap_img.HasPoint3D(0));
  EXPECT_TRUE(colmap_img.HasPoint3D(1));
  EXPECT_EQ(colmap_img.Point3DId(0), track_id);
  EXPECT_EQ(colmap_img.Point3DId(1), track_id);
}

}  // namespace glomap
