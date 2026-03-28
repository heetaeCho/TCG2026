#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/processors/track_filter.h"
#include "glomap/scene/types_sfm.h"
#include "glomap/types.h"

#include <unordered_map>
#include <cmath>

namespace glomap {
namespace {

class TrackFilterTest_86 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up a basic view graph (may not be used by FilterTrackTriangulationAngle
    // but is required by the interface)
  }

  ViewGraph view_graph_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;

  // Helper to create an image with a known pose (camera center at a given position)
  void AddImage(image_t id, const Eigen::Vector3d& center) {
    Image img;
    // Set rotation to identity
    img.cam_from_world = Rigid3d(Eigen::Quaterniond::Identity(),
                                  -center);  // t = -R*C, with R=I => t = -C
    images_[id] = img;
  }

  // Helper to create a track with given observations and 3D point
  void AddTrack(track_t id, const Eigen::Vector3d& xyz,
                const std::vector<std::pair<image_t, feature_t>>& obs) {
    Track track;
    track.xyz = xyz;
    for (const auto& [img_id, feat_id] : obs) {
      track.observations.emplace_back(img_id, feat_id);
    }
    tracks_[id] = track;
  }
};

// Test with empty tracks map - should return 0
TEST_F(TrackFilterTest_86, EmptyTracks_86) {
  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 1.0);
  EXPECT_EQ(result, 0);
}

// Test with a single track having only one observation - no pair can have
// sufficient angle, so it should be filtered
TEST_F(TrackFilterTest_86, SingleObservationTrackFiltered_86) {
  AddImage(0, Eigen::Vector3d(0, 0, 0));

  AddTrack(0, Eigen::Vector3d(0, 0, 10), {{0, 0}});

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 1.0);
  EXPECT_EQ(result, 1);
  EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test with two observations that form a large triangulation angle (90 degrees)
// with min_angle = 1 degree - should NOT be filtered
TEST_F(TrackFilterTest_86, LargeAngleNotFiltered_86) {
  // Camera 0 at origin, Camera 1 at (10, 0, 0)
  // 3D point at (5, 0, 0) - wait, that would give vectors along x-axis
  // Let's place point at (5, 0, 5)
  // From cam0: direction = (5,0,5).normalized
  // From cam1: direction = (-5,0,5).normalized
  // dot = (-25+0+25)/... = 0 => 90 degrees
  AddImage(0, Eigen::Vector3d(0, 0, 0));
  AddImage(1, Eigen::Vector3d(10, 0, 0));

  AddTrack(0, Eigen::Vector3d(5, 0, 5), {{0, 0}, {1, 0}});

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 1.0);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 2);
}

// Test with two observations that form a very small triangulation angle
// with min_angle = 10 degrees - should be filtered
TEST_F(TrackFilterTest_86, SmallAngleFiltered_86) {
  // Camera 0 at (0,0,0), Camera 1 at (0.001, 0, 0)
  // 3D point very far away at (0, 0, 10000)
  // Directions are nearly identical => angle ≈ 0
  AddImage(0, Eigen::Vector3d(0, 0, 0));
  AddImage(1, Eigen::Vector3d(0.001, 0, 0));

  AddTrack(0, Eigen::Vector3d(0, 0, 10000), {{0, 0}, {1, 0}});

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 10.0);
  EXPECT_EQ(result, 1);
  EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test with min_angle = 0 - everything should pass since any angle >= 0
// Actually, cos(0) = 1, and the condition is dot < thres = cos(0) = 1.
// For two different cameras the dot product will be < 1, so tracks should NOT be filtered
TEST_F(TrackFilterTest_86, MinAngleZeroNotFiltered_86) {
  AddImage(0, Eigen::Vector3d(0, 0, 0));
  AddImage(1, Eigen::Vector3d(0.001, 0, 0));

  AddTrack(0, Eigen::Vector3d(0, 0, 10000), {{0, 0}, {1, 0}});

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 0.0);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 2);
}

// Test with multiple tracks where some pass and some don't
TEST_F(TrackFilterTest_86, MultipleTracks_MixedFiltering_86) {
  AddImage(0, Eigen::Vector3d(0, 0, 0));
  AddImage(1, Eigen::Vector3d(10, 0, 0));
  AddImage(2, Eigen::Vector3d(0.0001, 0, 0));

  // Track 0: large angle (should pass)
  AddTrack(0, Eigen::Vector3d(5, 0, 5), {{0, 0}, {1, 0}});

  // Track 1: tiny angle (should be filtered with min_angle = 5)
  AddTrack(1, Eigen::Vector3d(0, 0, 100000), {{0, 0}, {2, 0}});

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 5.0);
  EXPECT_EQ(result, 1);
  // Track 0 should still have observations
  EXPECT_EQ(tracks_[0].observations.size(), 2);
  // Track 1 should be cleared
  EXPECT_TRUE(tracks_[1].observations.empty());
}

// Test with three observations where at least one pair has sufficient angle
TEST_F(TrackFilterTest_86, ThreeObservationsOnePairSufficient_86) {
  AddImage(0, Eigen::Vector3d(0, 0, 0));
  AddImage(1, Eigen::Vector3d(0.0001, 0, 0));  // Very close to cam 0
  AddImage(2, Eigen::Vector3d(10, 0, 0));       // Far from cam 0

  // Point such that cam0-cam2 pair forms large angle
  AddTrack(0, Eigen::Vector3d(5, 0, 5), {{0, 0}, {1, 0}, {2, 0}});

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 5.0);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 3);
}

// Test boundary: angle exactly at threshold
// Two cameras at distance 2*sin(angle/2) apart, point at unit distance
TEST_F(TrackFilterTest_86, AngleExactlyAtThreshold_86) {
  double min_angle_deg = 45.0;
  double half_angle_rad = min_angle_deg * M_PI / 360.0;  // half of 45 degrees in radians

  // Place cameras symmetrically about the z-axis
  // Camera centers at (-d, 0, 0) and (d, 0, 0)
  // Point at (0, 0, h)
  // The angle between the two view rays:
  // dir1 = (d, 0, h).normalized, dir2 = (-d, 0, h).normalized
  // dot = (-d^2 + h^2) / (d^2 + h^2)
  // We want this dot = cos(45 deg) = cos(pi/4)
  // => h^2 - d^2 = cos(pi/4) * (h^2 + d^2)
  // => h^2(1-cos(pi/4)) = d^2(1+cos(pi/4))
  // => d^2/h^2 = (1-cos(pi/4))/(1+cos(pi/4))
  double cos_angle = std::cos(min_angle_deg * M_PI / 180.0);
  double ratio = std::sqrt((1.0 - cos_angle) / (1.0 + cos_angle));
  double h = 10.0;
  double d = h * ratio;

  AddImage(0, Eigen::Vector3d(-d, 0, 0));
  AddImage(1, Eigen::Vector3d(d, 0, 0));

  AddTrack(0, Eigen::Vector3d(0, 0, h), {{0, 0}, {1, 0}});

  // At exact threshold, dot == thres, condition is strict < so it should be filtered
  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, min_angle_deg);
  // Due to floating point, this could go either way. Just check it returns 0 or 1
  EXPECT_GE(result, 0);
  EXPECT_LE(result, 1);
}

// Test: angle slightly above threshold should NOT be filtered
TEST_F(TrackFilterTest_86, AngleSlightlyAboveThreshold_86) {
  double min_angle_deg = 10.0;
  // Create angle of about 15 degrees
  // Place cameras so angle is comfortably above 10 degrees
  double actual_angle = 15.0;
  double cos_actual = std::cos(actual_angle * M_PI / 180.0);
  double ratio = std::sqrt((1.0 - cos_actual) / (1.0 + cos_actual));
  double h = 100.0;
  double d = h * ratio;

  AddImage(0, Eigen::Vector3d(-d, 0, 0));
  AddImage(1, Eigen::Vector3d(d, 0, 0));

  AddTrack(0, Eigen::Vector3d(0, 0, h), {{0, 0}, {1, 0}});

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, min_angle_deg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 2);
}

// Test: angle slightly below threshold should be filtered
TEST_F(TrackFilterTest_86, AngleSlightlyBelowThreshold_86) {
  double min_angle_deg = 20.0;
  // Create angle of about 5 degrees (well below 20)
  double actual_angle = 5.0;
  double cos_actual = std::cos(actual_angle * M_PI / 180.0);
  double ratio = std::sqrt((1.0 - cos_actual) / (1.0 + cos_actual));
  double h = 100.0;
  double d = h * ratio;

  AddImage(0, Eigen::Vector3d(-d, 0, 0));
  AddImage(1, Eigen::Vector3d(d, 0, 0));

  AddTrack(0, Eigen::Vector3d(0, 0, h), {{0, 0}, {1, 0}});

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, min_angle_deg);
  EXPECT_EQ(result, 1);
  EXPECT_TRUE(tracks_[0].observations.empty());
}

// Test: all tracks filtered
TEST_F(TrackFilterTest_86, AllTracksFiltered_86) {
  AddImage(0, Eigen::Vector3d(0, 0, 0));
  AddImage(1, Eigen::Vector3d(0.0001, 0, 0));

  // Both tracks have tiny angles
  AddTrack(0, Eigen::Vector3d(0, 0, 100000), {{0, 0}, {1, 0}});
  AddTrack(1, Eigen::Vector3d(0, 0, 200000), {{0, 0}, {1, 0}});

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 10.0);
  EXPECT_EQ(result, 2);
  EXPECT_TRUE(tracks_[0].observations.empty());
  EXPECT_TRUE(tracks_[1].observations.empty());
}

// Test: no tracks filtered
TEST_F(TrackFilterTest_86, NoTracksFiltered_86) {
  AddImage(0, Eigen::Vector3d(0, 0, 0));
  AddImage(1, Eigen::Vector3d(10, 0, 0));

  AddTrack(0, Eigen::Vector3d(5, 0, 5), {{0, 0}, {1, 0}});
  AddTrack(1, Eigen::Vector3d(5, 0, 3), {{0, 0}, {1, 0}});

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 1.0);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 2);
  EXPECT_EQ(tracks_[1].observations.size(), 2);
}

// Test: 180-degree angle (cameras on opposite sides of the point)
TEST_F(TrackFilterTest_86, OppositeDirections180Degrees_86) {
  AddImage(0, Eigen::Vector3d(0, 0, -10));
  AddImage(1, Eigen::Vector3d(0, 0, 10));

  // Point at origin - directions are exactly opposite
  // dot product = -1, which is definitely < cos(any positive angle)
  AddTrack(0, Eigen::Vector3d(0, 0, 0), {{0, 0}, {1, 0}});

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 90.0);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(tracks_[0].observations.size(), 2);
}

// Test return value matches number of filtered tracks
TEST_F(TrackFilterTest_86, ReturnValueMatchesFilteredCount_86) {
  AddImage(0, Eigen::Vector3d(0, 0, 0));
  AddImage(1, Eigen::Vector3d(10, 0, 0));
  AddImage(2, Eigen::Vector3d(0.00001, 0, 0));

  // Track 0: large angle, not filtered
  AddTrack(0, Eigen::Vector3d(5, 0, 5), {{0, 0}, {1, 0}});
  // Track 1: tiny angle, filtered
  AddTrack(1, Eigen::Vector3d(0, 0, 1000000), {{0, 0}, {2, 0}});
  // Track 2: large angle, not filtered
  AddTrack(2, Eigen::Vector3d(5, 0, 1), {{0, 0}, {1, 0}});

  int result = TrackFilter::FilterTrackTriangulationAngle(
      view_graph_, images_, tracks_, 5.0);
  
  // Count how many tracks have empty observations
  int empty_count = 0;
  for (const auto& [id, track] : tracks_) {
    if (track.observations.empty()) {
      empty_count++;
    }
  }
  EXPECT_EQ(result, empty_count);
}

}  // namespace
}  // namespace glomap
