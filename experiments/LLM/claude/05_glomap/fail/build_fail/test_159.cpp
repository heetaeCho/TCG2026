#include <gtest/gtest.h>
#include "glomap/processors/view_graph_manipulation.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/image_pair.h"
#include "glomap/types.h"

#include <colmap/scene/two_view_geometry.h>
#include <colmap/util/types.h>

#include <unordered_map>

namespace glomap {
namespace {

class ViewGraphManipulaterTest_159 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to create a Camera with prior focal length set
  Camera MakeCamera(camera_t cam_id, bool has_prior_focal) {
    Camera camera;
    camera.camera_id = cam_id;
    camera.has_prior_focal_length = has_prior_focal;
    return camera;
  }

  // Helper to create an Image
  Image MakeImage(image_t img_id, camera_t cam_id) {
    return Image(img_id, cam_id, "");
  }

  // Helper to create an ImagePair
  ImagePair MakeImagePair(image_t id1, image_t id2, int config, bool is_valid = true) {
    ImagePair pair(id1, id2);
    pair.config = config;
    pair.is_valid = is_valid;
    return pair;
  }
};

// Test: When there are no image pairs, nothing should crash
TEST_F(ViewGraphManipulaterTest_159, EmptyViewGraph_159) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  EXPECT_NO_THROW(
      ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images));
  EXPECT_TRUE(view_graph.image_pairs.empty());
}

// Test: Invalid pairs should be skipped and remain unchanged
TEST_F(ViewGraphManipulaterTest_159, InvalidPairsAreSkipped_159) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[1] = MakeCamera(1, true);
  cameras[2] = MakeCamera(2, true);
  images[10] = MakeImage(10, 1);
  images[20] = MakeImage(20, 2);

  ImagePair pair = MakeImagePair(10, 20, colmap::TwoViewGeometry::UNCALIBRATED, false);
  view_graph.image_pairs[pair.pair_id] = pair;

  ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);

  // The pair should remain UNCALIBRATED and invalid
  EXPECT_EQ(view_graph.image_pairs[pair.pair_id].config,
            colmap::TwoViewGeometry::UNCALIBRATED);
  EXPECT_FALSE(view_graph.image_pairs[pair.pair_id].is_valid);
}

// Test: All CALIBRATED pairs => ratio = 1.0 > 0.5 => UNCALIBRATED pairs get upgraded
TEST_F(ViewGraphManipulaterTest_159, AllCalibratedMakesCameraValid_159) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[1] = MakeCamera(1, true);
  cameras[2] = MakeCamera(2, true);
  cameras[3] = MakeCamera(3, true);

  images[10] = MakeImage(10, 1);
  images[20] = MakeImage(20, 2);
  images[30] = MakeImage(30, 3);

  // Pair 1: calibrated between cam1 and cam2
  ImagePair pair1 = MakeImagePair(10, 20, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[pair1.pair_id] = pair1;

  // Pair 2: uncalibrated between cam1 and cam3
  ImagePair pair2 = MakeImagePair(10, 30, colmap::TwoViewGeometry::UNCALIBRATED);
  view_graph.image_pairs[pair2.pair_id] = pair2;

  // Pair 3: calibrated between cam2 and cam3
  ImagePair pair3 = MakeImagePair(20, 30, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[pair3.pair_id] = pair3;

  ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);

  // Camera 1: 1 calibrated, 1 uncalibrated => total=2, calibrated=1 => ratio=0.5, NOT >0.5 => invalid
  // Camera 2: 2 calibrated => ratio = 1.0 => valid
  // Camera 3: 1 calibrated, 1 uncalibrated => total=2, calibrated=1 => ratio=0.5 => invalid
  // pair2 (uncalibrated): cam1 invalid => should NOT be upgraded
  EXPECT_EQ(view_graph.image_pairs[pair2.pair_id].config,
            colmap::TwoViewGeometry::UNCALIBRATED);
}

// Test: When both cameras are valid (ratio > 0.5), UNCALIBRATED pair gets upgraded to CALIBRATED
TEST_F(ViewGraphManipulaterTest_159, UncalibratedUpgradedWhenBothCamerasValid_159) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[1] = MakeCamera(1, true);
  cameras[2] = MakeCamera(2, true);

  images[10] = MakeImage(10, 1);
  images[20] = MakeImage(20, 2);
  images[11] = MakeImage(11, 1);
  images[21] = MakeImage(21, 2);

  // Create multiple calibrated pairs to make ratio > 0.5 for both cameras
  // cam1-cam2 calibrated pairs
  ImagePair p1 = MakeImagePair(10, 20, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[p1.pair_id] = p1;

  ImagePair p2 = MakeImagePair(11, 21, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[p2.pair_id] = p2;

  // One uncalibrated pair
  ImagePair p3 = MakeImagePair(10, 21, colmap::TwoViewGeometry::UNCALIBRATED);
  view_graph.image_pairs[p3.pair_id] = p3;

  // cam1: total=3 (2 calibrated + 1 uncalibrated), calibrated=2 => ratio=2/3 > 0.5 => valid
  // cam2: total=3 (2 calibrated + 1 uncalibrated), calibrated=2 => ratio=2/3 > 0.5 => valid

  ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);

  // p3 should be upgraded to CALIBRATED
  EXPECT_EQ(view_graph.image_pairs[p3.pair_id].config,
            colmap::TwoViewGeometry::CALIBRATED);
}

// Test: Cameras without prior focal length are skipped in counting
TEST_F(ViewGraphManipulaterTest_159, NoPriorFocalLengthSkipped_159) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[1] = MakeCamera(1, false);  // no prior
  cameras[2] = MakeCamera(2, true);

  images[10] = MakeImage(10, 1);
  images[20] = MakeImage(20, 2);

  ImagePair pair = MakeImagePair(10, 20, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[pair.pair_id] = pair;

  ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);

  // Since camera 1 has no prior focal length, the pair should not be counted
  // and config should remain unchanged
  EXPECT_EQ(view_graph.image_pairs[pair.pair_id].config,
            colmap::TwoViewGeometry::CALIBRATED);
}

// Test: When one camera is invalid (ratio <= 0.5), UNCALIBRATED pair should NOT be upgraded
TEST_F(ViewGraphManipulaterTest_159, OneCameraInvalidNoUpgrade_159) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[1] = MakeCamera(1, true);
  cameras[2] = MakeCamera(2, true);
  cameras[3] = MakeCamera(3, true);

  images[10] = MakeImage(10, 1);
  images[20] = MakeImage(20, 2);
  images[30] = MakeImage(30, 3);

  // cam1-cam2: calibrated
  ImagePair p1 = MakeImagePair(10, 20, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[p1.pair_id] = p1;

  // cam2-cam3: uncalibrated
  ImagePair p2 = MakeImagePair(20, 30, colmap::TwoViewGeometry::UNCALIBRATED);
  view_graph.image_pairs[p2.pair_id] = p2;

  // cam3: total=1 (0 calibrated + 1 uncalibrated), calibrated=0 => ratio=0/1=0 <= 0.5 => invalid
  // cam2: total=2 (1 calibrated + 1 uncalibrated), calibrated=1 => ratio=1/2=0.5 => NOT > 0.5 => invalid

  ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);

  // p2 should remain UNCALIBRATED since cam3 (and cam2) are not valid
  EXPECT_EQ(view_graph.image_pairs[p2.pair_id].config,
            colmap::TwoViewGeometry::UNCALIBRATED);
}

// Test: Already CALIBRATED pairs remain CALIBRATED regardless
TEST_F(ViewGraphManipulaterTest_159, CalibratedPairsRemainCalibrated_159) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[1] = MakeCamera(1, true);
  cameras[2] = MakeCamera(2, true);

  images[10] = MakeImage(10, 1);
  images[20] = MakeImage(20, 2);

  ImagePair pair = MakeImagePair(10, 20, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[pair.pair_id] = pair;

  ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);

  EXPECT_EQ(view_graph.image_pairs[pair.pair_id].config,
            colmap::TwoViewGeometry::CALIBRATED);
}

// Test: Mixed scenario with multiple cameras and various configs
TEST_F(ViewGraphManipulaterTest_159, MixedScenarioMultipleCameras_159) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[1] = MakeCamera(1, true);
  cameras[2] = MakeCamera(2, true);

  images[1] = MakeImage(1, 1);
  images[2] = MakeImage(2, 1);
  images[3] = MakeImage(3, 2);
  images[4] = MakeImage(4, 2);

  // 3 calibrated pairs
  ImagePair p1 = MakeImagePair(1, 3, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[p1.pair_id] = p1;

  ImagePair p2 = MakeImagePair(1, 4, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[p2.pair_id] = p2;

  ImagePair p3 = MakeImagePair(2, 3, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[p3.pair_id] = p3;

  // 1 uncalibrated pair
  ImagePair p4 = MakeImagePair(2, 4, colmap::TwoViewGeometry::UNCALIBRATED);
  view_graph.image_pairs[p4.pair_id] = p4;

  // cam1: total=4 (3 cal + 1 uncal), calibrated_count=3 => ratio=3/4=0.75 > 0.5 => valid
  // cam2: total=4 (3 cal + 1 uncal), calibrated_count=3 => ratio=3/4=0.75 > 0.5 => valid
  // Both valid => p4 should be upgraded

  ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);

  EXPECT_EQ(view_graph.image_pairs[p4.pair_id].config,
            colmap::TwoViewGeometry::CALIBRATED);
}

// Test: Pair with non-UNCALIBRATED and non-CALIBRATED config is not upgraded
TEST_F(ViewGraphManipulaterTest_159, OtherConfigNotUpgraded_159) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[1] = MakeCamera(1, true);
  cameras[2] = MakeCamera(2, true);

  images[10] = MakeImage(10, 1);
  images[20] = MakeImage(20, 2);
  images[11] = MakeImage(11, 1);
  images[21] = MakeImage(21, 2);

  // Calibrated pairs to make cameras valid
  ImagePair p1 = MakeImagePair(10, 20, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[p1.pair_id] = p1;

  ImagePair p2 = MakeImagePair(11, 21, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[p2.pair_id] = p2;

  // A pair with UNDEFINED config
  ImagePair p3 = MakeImagePair(10, 21, colmap::TwoViewGeometry::UNDEFINED);
  view_graph.image_pairs[p3.pair_id] = p3;

  ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);

  // p3 should remain UNDEFINED (only UNCALIBRATED gets upgraded)
  EXPECT_EQ(view_graph.image_pairs[p3.pair_id].config,
            colmap::TwoViewGeometry::UNDEFINED);
}

// Test: Exactly at boundary ratio = 0.5 (not strictly > 0.5) => camera invalid
TEST_F(ViewGraphManipulaterTest_159, ExactlyHalfRatioCameraInvalid_159) {
  ViewGraph view_graph;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<image_t, Image> images;

  cameras[1] = MakeCamera(1, true);
  cameras[2] = MakeCamera(2, true);
  cameras[3] = MakeCamera(3, true);

  images[10] = MakeImage(10, 1);
  images[20] = MakeImage(20, 2);
  images[30] = MakeImage(30, 3);

  // cam1-cam2: calibrated
  ImagePair p1 = MakeImagePair(10, 20, colmap::TwoViewGeometry::CALIBRATED);
  view_graph.image_pairs[p1.pair_id] = p1;

  // cam1-cam3: uncalibrated
  ImagePair p2 = MakeImagePair(10, 30, colmap::TwoViewGeometry::UNCALIBRATED);
  view_graph.image_pairs[p2.pair_id] = p2;

  // cam1: total=2, calibrated=1, ratio=0.5 => NOT > 0.5 => invalid
  // cam3: total=1, calibrated=0, ratio=0 => invalid
  // cam2: total=1, calibrated=1, ratio=1.0 => valid

  ViewGraphManipulater::UpdateImagePairsConfig(view_graph, cameras, images);

  // p2 should remain UNCALIBRATED since cam1 is invalid
  EXPECT_EQ(view_graph.image_pairs[p2.pair_id].config,
            colmap::TwoViewGeometry::UNCALIBRATED);
}

}  // namespace
}  // namespace glomap
