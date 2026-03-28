// File: colmap_converter_test_121.cc

#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

#include "glomap/scene/track.h"

// ---- Minimal stubs for external COLMAP types (external dependency) ----
// These are *not* part of the code under test; they are simple stand-ins
// so we can exercise glomap::ConvertColmapPoints3DToGlomapTracks.

namespace colmap {

struct TrackElement {
  int image_id;
  int point2D_idx;

  TrackElement() = default;
  TrackElement(int img_id, int pt2d_idx)
      : image_id(img_id), point2D_idx(pt2d_idx) {}
};

class Track {
 public:
  const std::vector<TrackElement>& Elements() const { return elements_; }
  size_t Length() const { return elements_.size(); }

  void AddElement(int image_id, int point2D_idx) {
    elements_.emplace_back(image_id, point2D_idx);
  }

 private:
  std::vector<TrackElement> elements_;
};

struct Point3D {
  Eigen::Vector3d xyz = Eigen::Vector3d::Zero();
  Eigen::Vector3ub color = Eigen::Vector3ub::Zero();
  Track track;
};

class Reconstruction {
 public:
  using Points3DMap = std::unordered_map<glomap::track_t, Point3D>;

  const Points3DMap& Points3D() const { return points3d_; }
  Points3DMap& Points3D() { return points3d_; }

  size_t NumPoints3D() const { return points3d_.size(); }

  void AddPoint3D(glomap::track_t id, const Point3D& point) {
    points3d_.emplace(id, point);
  }

 private:
  Points3DMap points3d_;
};

}  // namespace colmap

// ---- Function under test (only declaration; implementation is elsewhere) ----
namespace glomap {

void ConvertColmapPoints3DToGlomapTracks(
    const colmap::Reconstruction& reconstruction,
    std::unordered_map<track_t, Track>& tracks);

}  // namespace glomap

// ---- Test fixture ----
class ConvertColmapPoints3DToGlomapTracksTest_121 : public ::testing::Test {
 protected:
  using TracksMap = std::unordered_map<glomap::track_t, glomap::Track>;

  colmap::Reconstruction reconstruction_;
  TracksMap tracks_;
};

// Empty reconstruction should clear and leave tracks empty.
TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121,
       EmptyReconstructionClearsTracks_121) {
  // Pre-populate tracks_ to verify it gets cleared.
  glomap::Track existing_track;
  existing_track.track_id = 999;
  existing_track.is_initialized = true;
  tracks_.emplace(999, existing_track);

  ASSERT_FALSE(tracks_.empty());

  glomap::ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  EXPECT_TRUE(tracks_.empty());
}

// Single 3D point with one observation should be converted correctly.
TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121,
       SinglePointCopiesFieldsAndObservation_121) {
  const glomap::track_t point_id = 42;

  colmap::Point3D point;
  point.xyz = Eigen::Vector3d(1.0, 2.0, 3.0);
  point.color = Eigen::Vector3ub(10, 20, 30);
  point.track.AddElement(/*image_id*/ 5, /*point2D_idx*/ 7);

  reconstruction_.AddPoint3D(point_id, point);

  glomap::ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_EQ(tracks_.size(), 1u);
  auto it = tracks_.find(point_id);
  ASSERT_NE(it, tracks_.end());

  const glomap::Track& track = it->second;

  // track_id should match the point3d_id
  EXPECT_EQ(track.track_id, point_id);

  // xyz should be copied
  EXPECT_DOUBLE_EQ(track.xyz.x(), 1.0);
  EXPECT_DOUBLE_EQ(track.xyz.y(), 2.0);
  EXPECT_DOUBLE_EQ(track.xyz.z(), 3.0);

  // color should be copied
  EXPECT_EQ(track.color[0], 10);
  EXPECT_EQ(track.color[1], 20);
  EXPECT_EQ(track.color[2], 30);

  // is_initialized must be set to true
  EXPECT_TRUE(track.is_initialized);

  // Single observation from TrackElement
  ASSERT_EQ(track.observations.size(), 1u);
  const glomap::Observation& obs = track.observations[0];
  EXPECT_EQ(obs.first, 5);   // image_id
  EXPECT_EQ(obs.second, 7);  // point2D_idx
}

// Point with no observations should still produce a Track with empty observations.
TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121,
       PointWithoutObservationsProducesEmptyObservationList_121) {
  const glomap::track_t point_id = 11;

  colmap::Point3D point;
  point.xyz = Eigen::Vector3d(4.0, 5.0, 6.0);
  point.color = Eigen::Vector3ub(1, 2, 3);
  // No elements added to point.track

  reconstruction_.AddPoint3D(point_id, point);

  glomap::ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_EQ(tracks_.size(), 1u);
  auto it = tracks_.find(point_id);
  ASSERT_NE(it, tracks_.end());

  const glomap::Track& track = it->second;
  EXPECT_EQ(track.track_id, point_id);
  EXPECT_TRUE(track.is_initialized);
  EXPECT_TRUE(track.observations.empty());
}

// Multiple 3D points with multiple observations each should all be converted.
TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121,
       MultiplePointsAndObservations_121) {
  // Point A
  colmap::Point3D point_a;
  point_a.xyz = Eigen::Vector3d(1.0, 0.0, 0.0);
  point_a.color = Eigen::Vector3ub(100, 0, 0);
  point_a.track.AddElement(1, 10);
  point_a.track.AddElement(1, 11);

  // Point B
  colmap::Point3D point_b;
  point_b.xyz = Eigen::Vector3d(0.0, 1.0, 0.0);
  point_b.color = Eigen::Vector3ub(0, 100, 0);
  point_b.track.AddElement(2, 20);

  reconstruction_.AddPoint3D(1, point_a);
  reconstruction_.AddPoint3D(2, point_b);

  glomap::ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  ASSERT_EQ(tracks_.size(), 2u);

  // Check Point A
  {
    auto it = tracks_.find(1);
    ASSERT_NE(it, tracks_.end());
    const glomap::Track& track_a = it->second;

    EXPECT_EQ(track_a.track_id, 1);
    EXPECT_TRUE(track_a.is_initialized);
    EXPECT_EQ(track_a.observations.size(), 2u);
    EXPECT_EQ(track_a.observations[0].first, 1);
    EXPECT_EQ(track_a.observations[0].second, 10);
    EXPECT_EQ(track_a.observations[1].first, 1);
    EXPECT_EQ(track_a.observations[1].second, 11);
  }

  // Check Point B
  {
    auto it = tracks_.find(2);
    ASSERT_NE(it, tracks_.end());
    const glomap::Track& track_b2 = it->second;

    EXPECT_EQ(track_b2.track_id, 2);
    EXPECT_TRUE(track_b2.is_initialized);
    ASSERT_EQ(track_b2.observations.size(), 1u);
    EXPECT_EQ(track_b2.observations[0].first, 2);
    EXPECT_EQ(track_b2.observations[0].second, 20);
  }
}

// Existing entries in tracks should be cleared before inserting new ones.
TEST_F(ConvertColmapPoints3DToGlomapTracksTest_121,
       ExistingTracksAreClearedBeforeInsert_121) {
  // Pre-populate tracks_ with different ids
  glomap::Track old_track1;
  old_track1.track_id = 100;
  tracks_.emplace(100, old_track1);

  glomap::Track old_track2;
  old_track2.track_id = 200;
  tracks_.emplace(200, old_track2);

  ASSERT_EQ(tracks_.size(), 2u);

  // Reconstruction with a single new point
  colmap::Point3D point;
  point.xyz = Eigen::Vector3d(7.0, 8.0, 9.0);
  point.color = Eigen::Vector3ub(9, 8, 7);
  reconstruction_.AddPoint3D(300, point);

  glomap::ConvertColmapPoints3DToGlomapTracks(reconstruction_, tracks_);

  // Old entries should be removed; only new track should remain
  ASSERT_EQ(tracks_.size(), 1u);
  auto it = tracks_.find(300);
  ASSERT_NE(it, tracks_.end());
  EXPECT_EQ(it->second.track_id, 300);
  EXPECT_TRUE(it->second.is_initialized);
}
