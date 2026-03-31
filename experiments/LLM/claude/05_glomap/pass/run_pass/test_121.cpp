#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/io/colmap_converter.h"
#include "glomap/scene/track.h"

#include <colmap/scene/reconstruction.h>
#include <colmap/scene/point3d.h>
#include <colmap/scene/track.h>

#include <unordered_map>

namespace glomap {
namespace {

class ConvertColmapPoints3DToGlomapTracksTest_121 : public ::testing::Test {
 protected:
  colmap::Reconstruction reconstruction_;
  std::unordered_map<track_t, Track> tracks_;
};

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, EmptyReconstruction_121) {
  // No points added to reconstruction
  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);
  EXPECT_TRUE(tracks_.empty());
}

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, SinglePointNoObservations_121) {
  colmap::Point3D point3D;
  point3D.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  point3D.color = Eigen::Vector3ub(100, 150, 200);
  // No track elements added

  const colmap::point3D_t point3d_id = reconstruction_.AddPoint3D(
      point3D.xyz, colmap::Track());
  // Update color
  reconstruction_.Point3D(point3d_id).color = point3D.color;

  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_EQ(tracks_.size(), 1);
  ASSERT_TRUE(tracks_.count(point3d_id));

  const Track& track = tracks_.at(point3d_id);
  EXPECT_EQ(track.track_id, point3d_id);
  EXPECT_TRUE(track.is_initialized);
  EXPECT_DOUBLE_EQ(track.xyz.x(), 1.0);
  EXPECT_DOUBLE_EQ(track.xyz.y(), 2.0);
  EXPECT_DOUBLE_EQ(track.xyz.z(), 3.0);
  EXPECT_EQ(track.color(0), 100);
  EXPECT_EQ(track.color(1), 150);
  EXPECT_EQ(track.color(2), 200);
  EXPECT_TRUE(track.observations.empty());
}

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, SinglePointWithObservations_121) {
  colmap::Track colmap_track;
  colmap_track.AddElement(1, 10);
  colmap_track.AddElement(2, 20);
  colmap_track.AddElement(3, 30);

  Eigen::Vector3d xyz(4.0, 5.0, 6.0);
  const colmap::point3D_t point3d_id = reconstruction_.AddPoint3D(
      xyz, colmap_track);
  reconstruction_.Point3D(point3d_id).color = Eigen::Vector3ub(50, 60, 70);

  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_EQ(tracks_.size(), 1);
  ASSERT_TRUE(tracks_.count(point3d_id));

  const Track& track = tracks_.at(point3d_id);
  EXPECT_EQ(track.track_id, point3d_id);
  EXPECT_TRUE(track.is_initialized);
  EXPECT_DOUBLE_EQ(track.xyz.x(), 4.0);
  EXPECT_DOUBLE_EQ(track.xyz.y(), 5.0);
  EXPECT_DOUBLE_EQ(track.xyz.z(), 6.0);

  ASSERT_EQ(track.observations.size(), 3);
  EXPECT_EQ(track.observations[0].first, 1);
  EXPECT_EQ(track.observations[0].second, 10);
  EXPECT_EQ(track.observations[1].first, 2);
  EXPECT_EQ(track.observations[1].second, 20);
  EXPECT_EQ(track.observations[2].first, 3);
  EXPECT_EQ(track.observations[2].second, 30);
}

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, MultiplePoints_121) {
  // First point
  colmap::Track track1;
  track1.AddElement(10, 100);
  Eigen::Vector3d xyz1(1.0, 0.0, 0.0);
  const colmap::point3D_t id1 = reconstruction_.AddPoint3D(xyz1, track1);
  reconstruction_.Point3D(id1).color = Eigen::Vector3ub(255, 0, 0);

  // Second point
  colmap::Track track2;
  track2.AddElement(20, 200);
  track2.AddElement(21, 201);
  Eigen::Vector3d xyz2(0.0, 1.0, 0.0);
  const colmap::point3D_t id2 = reconstruction_.AddPoint3D(xyz2, track2);
  reconstruction_.Point3D(id2).color = Eigen::Vector3ub(0, 255, 0);

  // Third point
  colmap::Track track3;
  Eigen::Vector3d xyz3(0.0, 0.0, 1.0);
  const colmap::point3D_t id3 = reconstruction_.AddPoint3D(xyz3, track3);
  reconstruction_.Point3D(id3).color = Eigen::Vector3ub(0, 0, 255);

  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_EQ(tracks_.size(), 3);

  // Verify first point
  ASSERT_TRUE(tracks_.count(id1));
  EXPECT_EQ(tracks_.at(id1).observations.size(), 1);
  EXPECT_DOUBLE_EQ(tracks_.at(id1).xyz.x(), 1.0);

  // Verify second point
  ASSERT_TRUE(tracks_.count(id2));
  EXPECT_EQ(tracks_.at(id2).observations.size(), 2);
  EXPECT_DOUBLE_EQ(tracks_.at(id2).xyz.y(), 1.0);

  // Verify third point
  ASSERT_TRUE(tracks_.count(id3));
  EXPECT_EQ(tracks_.at(id3).observations.size(), 0);
  EXPECT_DOUBLE_EQ(tracks_.at(id3).xyz.z(), 1.0);
}

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, ClearsPreviousTracks_121) {
  // Pre-populate tracks with some data
  Track dummy_track;
  dummy_track.track_id = 999;
  tracks_[999] = dummy_track;
  tracks_[998] = dummy_track;
  ASSERT_EQ(tracks_.size(), 2);

  // Empty reconstruction
  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  EXPECT_TRUE(tracks_.empty());
}

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, ClearsPreviousTracksAndPopulatesNew_121) {
  // Pre-populate tracks
  Track dummy_track;
  dummy_track.track_id = 999;
  tracks_[999] = dummy_track;
  ASSERT_EQ(tracks_.size(), 1);

  // Add one point to reconstruction
  colmap::Track colmap_track;
  colmap_track.AddElement(5, 50);
  Eigen::Vector3d xyz(7.0, 8.0, 9.0);
  const colmap::point3D_t point3d_id = reconstruction_.AddPoint3D(xyz, colmap_track);

  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  // Old entry should be gone
  EXPECT_FALSE(tracks_.count(999));
  // New entry should exist
  ASSERT_EQ(tracks_.size(), 1);
  ASSERT_TRUE(tracks_.count(point3d_id));
  EXPECT_EQ(tracks_.at(point3d_id).observations.size(), 1);
}

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, IsInitializedSetToTrue_121) {
  colmap::Track colmap_track;
  Eigen::Vector3d xyz(0.0, 0.0, 0.0);
  const colmap::point3D_t id = reconstruction_.AddPoint3D(xyz, colmap_track);

  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_TRUE(tracks_.count(id));
  EXPECT_TRUE(tracks_.at(id).is_initialized);
}

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, TrackIdMatchesPoint3DId_121) {
  colmap::Track colmap_track;
  Eigen::Vector3d xyz(1.0, 2.0, 3.0);
  const colmap::point3D_t id = reconstruction_.AddPoint3D(xyz, colmap_track);

  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_TRUE(tracks_.count(id));
  EXPECT_EQ(tracks_.at(id).track_id, id);
}

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, ZeroCoordinatesAndColor_121) {
  colmap::Track colmap_track;
  Eigen::Vector3d xyz(0.0, 0.0, 0.0);
  const colmap::point3D_t id = reconstruction_.AddPoint3D(xyz, colmap_track);
  reconstruction_.Point3D(id).color = Eigen::Vector3ub(0, 0, 0);

  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_TRUE(tracks_.count(id));
  const Track& track = tracks_.at(id);
  EXPECT_DOUBLE_EQ(track.xyz.x(), 0.0);
  EXPECT_DOUBLE_EQ(track.xyz.y(), 0.0);
  EXPECT_DOUBLE_EQ(track.xyz.z(), 0.0);
  EXPECT_EQ(track.color(0), 0);
  EXPECT_EQ(track.color(1), 0);
  EXPECT_EQ(track.color(2), 0);
}

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, NegativeCoordinates_121) {
  colmap::Track colmap_track;
  Eigen::Vector3d xyz(-1.5, -2.5, -3.5);
  const colmap::point3D_t id = reconstruction_.AddPoint3D(xyz, colmap_track);

  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_TRUE(tracks_.count(id));
  EXPECT_DOUBLE_EQ(tracks_.at(id).xyz.x(), -1.5);
  EXPECT_DOUBLE_EQ(tracks_.at(id).xyz.y(), -2.5);
  EXPECT_DOUBLE_EQ(tracks_.at(id).xyz.z(), -3.5);
}

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, LargeNumberOfObservations_121) {
  colmap::Track colmap_track;
  const int num_observations = 1000;
  for (int i = 0; i < num_observations; ++i) {
    colmap_track.AddElement(static_cast<colmap::image_t>(i),
                            static_cast<colmap::point2D_t>(i * 2));
  }

  Eigen::Vector3d xyz(10.0, 20.0, 30.0);
  const colmap::point3D_t id = reconstruction_.AddPoint3D(xyz, colmap_track);

  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_TRUE(tracks_.count(id));
  ASSERT_EQ(tracks_.at(id).observations.size(), num_observations);

  for (int i = 0; i < num_observations; ++i) {
    EXPECT_EQ(tracks_.at(id).observations[i].first,
              static_cast<image_t>(i));
    EXPECT_EQ(tracks_.at(id).observations[i].second,
              static_cast<feature_t>(i * 2));
  }
}

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, ObservationOrderPreserved_121) {
  colmap::Track colmap_track;
  colmap_track.AddElement(100, 5);
  colmap_track.AddElement(50, 10);
  colmap_track.AddElement(200, 1);

  Eigen::Vector3d xyz(0.0, 0.0, 0.0);
  const colmap::point3D_t id = reconstruction_.AddPoint3D(xyz, colmap_track);

  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_TRUE(tracks_.count(id));
  const auto& obs = tracks_.at(id).observations;
  ASSERT_EQ(obs.size(), 3);
  EXPECT_EQ(obs[0].first, 100);
  EXPECT_EQ(obs[0].second, 5);
  EXPECT_EQ(obs[1].first, 50);
  EXPECT_EQ(obs[1].second, 10);
  EXPECT_EQ(obs[2].first, 200);
  EXPECT_EQ(obs[2].second, 1);
}

TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121, MaxColorValues_121) {
  colmap::Track colmap_track;
  Eigen::Vector3d xyz(0.0, 0.0, 0.0);
  const colmap::point3D_t id = reconstruction_.AddPoint3D(xyz, colmap_track);
  reconstruction_.Point3D(id).color = Eigen::Vector3ub(255, 255, 255);

  ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_TRUE(tracks_.count(id));
  EXPECT_EQ(tracks_.at(id).color(0), 255);
  EXPECT_EQ(tracks_.at(id).color(1), 255);
  EXPECT_EQ(tracks_.at(id).color(2), 255);
}

}  // namespace
}  // namespace glomap
