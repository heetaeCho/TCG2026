#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <Eigen/Core>

#include "glomap/processors/track_filter.h"
#include "glomap/scene/image.h"
#include "glomap/scene/track.h"
#include "glomap/scene/view_graph.h"

namespace glomap {
namespace {

// Helper to create an Image with a known pose so that Center() returns a known position.
// We need to set the cam_from_world transform such that Center() returns the desired position.
// Center() typically returns -R^T * t, so we set rotation to identity and translation to -center.
Image CreateImageAtCenter(image_t image_id, const Eigen::Vector3d& center) {
  Image img(image_id, 0, "");
  // Set cam_from_world so that Center() returns the desired center.
  // For a Rigid3d with identity rotation, Center() = -R^T * t = -t
  // So we need t = -center
  Rigid3d cam_from_world;
  cam_from_world.rotation = Eigen::Quaterniond::Identity();
  cam_from_world.translation = -center;
  img.cam_from_world = cam_from_world;
  return img;
}

class TrackFilterTriangulationAngleTest_156 : public ::testing::Test {
 protected:
  ViewGraph view_graph_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

// Test with empty tracks map - should return 0 filtered
TEST_F(TrackFilterTriangulationAngleTest_156, EmptyTracks_156) {
  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 1.0);
  EXPECT_EQ(result, 0);
}

// Test with a single track that has a large triangulation angle (should not be filtered)
TEST_F(TrackFilterTriangulationAngleTest_156, LargeAngleNotFiltered_156) {
  // Two cameras at very different positions, track point in between but offset
  // Camera 1 at origin, Camera 2 at (10, 0, 0), track at (5, 0, 5)
  // Angle between viewing directions should be large (~90 degrees)
  images_[0] = CreateImageAtCenter(0, Eigen::Vector3d(0, 0, 0));
  images_[1] = CreateImageAtCenter(1, Eigen::Vector3d(10, 0, 0));

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(5, 0, 0.01);  // very close to baseline => large angle
  // Actually let's use a point that creates a clear large angle
  track.xyz = Eigen::Vector3d(5, 5, 0);  // ~90 degree angle from the two cameras
  track.observations.push_back({0, 0});
  track.observations.push_back({1, 0});
  tracks_[0] = track;

  double min_angle = 5.0;  // 5 degrees threshold
  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, min_angle);

  // The angle should be large enough, so track should NOT be filtered
  EXPECT_EQ(result, 0);
  EXPECT_FALSE(tracks_[0].observations.empty());
}

// Test with a single track that has a very small triangulation angle (should be filtered)
TEST_F(TrackFilterTriangulationAngleTest_156, SmallAngleFiltered_156) {
  // Two cameras very close together, track point very far away
  // This creates a very small triangulation angle
  images_[0] = CreateImageAtCenter(0, Eigen::Vector3d(0, 0, 0));
  images_[1] = CreateImageAtCenter(1, Eigen::Vector3d(0.001, 0, 0));

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0, 0, 1000);  // Very far away => tiny angle
  track.observations.push_back({0, 0});
  track.observations.push_back({1, 0});
  tracks_[0] = track;

  double min_angle = 5.0;  // 5 degrees threshold
  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, min_angle);

  EXPECT_EQ(result, 1);
  EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test with multiple tracks: some filtered, some not
TEST_F(TrackFilterTriangulationAngleTest_156, MixedTracks_156) {
  images_[0] = CreateImageAtCenter(0, Eigen::Vector3d(0, 0, 0));
  images_[1] = CreateImageAtCenter(1, Eigen::Vector3d(10, 0, 0));

  // Track 0: large angle (should survive)
  Track track0;
  track0.track_id = 0;
  track0.xyz = Eigen::Vector3d(5, 5, 0);
  track0.observations.push_back({0, 0});
  track0.observations.push_back({1, 0});
  tracks_[0] = track0;

  // Track 1: tiny angle (should be filtered)
  Track track1;
  track1.track_id = 1;
  track1.xyz = Eigen::Vector3d(5, 0, 100000);
  track1.observations.push_back({0, 0});
  track1.observations.push_back({1, 0});
  tracks_[1] = track1;

  double min_angle = 5.0;
  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, min_angle);

  EXPECT_EQ(result, 1);
  EXPECT_FALSE(tracks_[0].observations.empty());
  EXPECT_TRUE(tracks_[1].observations.empty());
}

// Test with min_angle = 0: no tracks should be filtered (any angle > 0 passes)
TEST_F(TrackFilterTriangulationAngleTest_156, ZeroMinAngle_156) {
  images_[0] = CreateImageAtCenter(0, Eigen::Vector3d(0, 0, 0));
  images_[1] = CreateImageAtCenter(1, Eigen::Vector3d(0.001, 0, 0));

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(0, 0, 1000);
  track.observations.push_back({0, 0});
  track.observations.push_back({1, 0});
  tracks_[0] = track;

  // min_angle = 0 means cos(0) = 1, so dot < 1 is needed for any non-identical directions
  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 0.0);

  // With 0 angle threshold, even tiny angles should pass
  EXPECT_EQ(result, 0);
  EXPECT_FALSE(tracks_[0].observations.empty());
}

// Test with very large min_angle (close to 180): almost all tracks filtered
TEST_F(TrackFilterTriangulationAngleTest_156, LargeMinAngle_156) {
  images_[0] = CreateImageAtCenter(0, Eigen::Vector3d(0, 0, 0));
  images_[1] = CreateImageAtCenter(1, Eigen::Vector3d(10, 0, 0));

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(5, 5, 0);  // ~90 degree angle
  track.observations.push_back({0, 0});
  track.observations.push_back({1, 0});
  tracks_[0] = track;

  // 120 degrees threshold - the ~90 degree track should be filtered
  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 120.0);

  EXPECT_EQ(result, 1);
  EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test with a track having only one observation (no pair to check => filtered)
TEST_F(TrackFilterTriangulationAngleTest_156, SingleObservation_156) {
  images_[0] = CreateImageAtCenter(0, Eigen::Vector3d(0, 0, 0));

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(5, 5, 5);
  track.observations.push_back({0, 0});
  tracks_[0] = track;

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 1.0);

  // With only one observation, no pair has sufficient angle => filtered
  EXPECT_EQ(result, 1);
  EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test with three observations where only one pair has a large enough angle
TEST_F(TrackFilterTriangulationAngleTest_156, ThreeObservationsOnePairSufficient_156) {
  images_[0] = CreateImageAtCenter(0, Eigen::Vector3d(0, 0, 0));
  images_[1] = CreateImageAtCenter(1, Eigen::Vector3d(0.0001, 0, 0));
  images_[2] = CreateImageAtCenter(2, Eigen::Vector3d(10, 0, 0));

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(5, 5, 0);
  track.observations.push_back({0, 0});
  track.observations.push_back({1, 0});
  track.observations.push_back({2, 0});
  tracks_[0] = track;

  double min_angle = 5.0;
  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, min_angle);

  // Pair (0,2) or (1,2) should have a large angle, so track survives
  EXPECT_EQ(result, 0);
  EXPECT_FALSE(tracks_[0].observations.empty());
}

// Test that all tracks are filtered when all have small angles
TEST_F(TrackFilterTriangulationAngleTest_156, AllTracksFiltered_156) {
  images_[0] = CreateImageAtCenter(0, Eigen::Vector3d(0, 0, 0));
  images_[1] = CreateImageAtCenter(1, Eigen::Vector3d(0.0001, 0, 0));

  for (int i = 0; i < 5; i++) {
    Track track;
    track.track_id = i;
    track.xyz = Eigen::Vector3d(0, 0, 100000 + i);
    track.observations.push_back({0, 0});
    track.observations.push_back({1, 0});
    tracks_[i] = track;
  }

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 10.0);

  EXPECT_EQ(result, 5);
  for (auto& [id, track] : tracks_) {
    EXPECT_TRUE(track.observations.empty());
  }
}

// Test that no tracks are filtered when all have large enough angles
TEST_F(TrackFilterTriangulationAngleTest_156, NoTracksFiltered_156) {
  images_[0] = CreateImageAtCenter(0, Eigen::Vector3d(0, 0, 0));
  images_[1] = CreateImageAtCenter(1, Eigen::Vector3d(10, 0, 0));

  for (int i = 0; i < 5; i++) {
    Track track;
    track.track_id = i;
    track.xyz = Eigen::Vector3d(5, 5 + i, 0);
    track.observations.push_back({0, 0});
    track.observations.push_back({1, 0});
    tracks_[i] = track;
  }

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 1.0);

  EXPECT_EQ(result, 0);
  for (auto& [id, track] : tracks_) {
    EXPECT_FALSE(track.observations.empty());
  }
}

// Test with track at exact 90 degrees
TEST_F(TrackFilterTriangulationAngleTest_156, Exact90DegreeAngle_156) {
  // Camera at (0,0,0) and (2,0,0), track at (1, 0, 0)... 
  // Actually that's degenerate. Let's use (1, 1, 0)
  // Vector from cam0 = (1,1,0), from cam1 = (-1,1,0)
  // dot = -1+1+0 = 0, angle = 90 degrees
  images_[0] = CreateImageAtCenter(0, Eigen::Vector3d(0, 0, 0));
  images_[1] = CreateImageAtCenter(1, Eigen::Vector3d(2, 0, 0));

  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(1, 1, 0);
  track.observations.push_back({0, 0});
  track.observations.push_back({1, 0});
  tracks_[0] = track;

  // With min_angle = 89 degrees, should not be filtered
  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 89.0);
  EXPECT_EQ(result, 0);
  EXPECT_FALSE(tracks_[0].observations.empty());

  // Reset observations for next test
  tracks_[0].observations.push_back({0, 0});
  tracks_[0].observations.push_back({1, 0});

  // With min_angle = 91 degrees, should be filtered
  result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 91.0);
  EXPECT_EQ(result, 1);
  EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test that the return value matches the number of filtered tracks
TEST_F(TrackFilterTriangulationAngleTest_156, ReturnValueMatchesFilteredCount_156) {
  images_[0] = CreateImageAtCenter(0, Eigen::Vector3d(0, 0, 0));
  images_[1] = CreateImageAtCenter(1, Eigen::Vector3d(10, 0, 0));

  // 3 tracks with large angle, 2 with small angle
  for (int i = 0; i < 3; i++) {
    Track track;
    track.track_id = i;
    track.xyz = Eigen::Vector3d(5, 5 + i, 0);  // large angle
    track.observations.push_back({0, 0});
    track.observations.push_back({1, 0});
    tracks_[i] = track;
  }

  images_[2] = CreateImageAtCenter(2, Eigen::Vector3d(0.0001, 0, 0));
  for (int i = 3; i < 5; i++) {
    Track track;
    track.track_id = i;
    track.xyz = Eigen::Vector3d(0, 0, 100000);  // tiny angle
    track.observations.push_back({0, 0});
    track.observations.push_back({2, 0});
    tracks_[i] = track;
  }

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 5.0);

  EXPECT_EQ(result, 2);

  int actual_filtered = 0;
  for (auto& [id, track] : tracks_) {
    if (track.observations.empty()) actual_filtered++;
  }
  EXPECT_EQ(result, actual_filtered);
}

// Test with track having no observations
TEST_F(TrackFilterTriangulationAngleTest_156, TrackWithNoObservations_156) {
  Track track;
  track.track_id = 0;
  track.xyz = Eigen::Vector3d(5, 5, 5);
  // No observations added
  tracks_[0] = track;

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 1.0);

  // No pairs to check => status remains false => filtered
  EXPECT_EQ(result, 1);
}

}  // namespace
}  // namespace glomap
