// File: track_filter_test_86.cc

#include <unordered_map>

#include <Eigen/Core>
#include <gtest/gtest.h>

#include "glomap/processors/track_filter.h"
#include "glomap/scene/image.h"
#include "glomap/scene/track.h"
#include "glomap/graph/view_graph.h"

namespace glomap {

class TrackFilterTest_86 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Nothing special for now.
  }

  // Helper to insert an image with a given center into the map.
  void AddImageWithCenter(image_t image_id, const Eigen::Vector3d& center) {
    Image image;
    // We assume Image exposes a way to set the projection / camera center.
    // This must be done via the public interface, e.g., SetCenter or an
    // equivalent pose / projection-center setter.
    image.SetCenter(center);
    images_.emplace(image_id, image);
  }

  ViewGraph view_graph_;  // Not used by FilterTrackTriangulationAngle, but required.
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
  TrackFilter track_filter_;
};

// -----------------------------------------------------------------------------
// 1) Boundary: tracks with a single observation should be filtered.
// -----------------------------------------------------------------------------
TEST_F(TrackFilterTest_86, SingleObservationTrackIsRemoved_86) {
  const image_t kImageId = 1;
  AddImageWithCenter(kImageId, Eigen::Vector3d::Zero());

  Track track;
  track.xyz = Eigen::Vector3d(1.0, 0.0, 0.0);
  track.observations.push_back({kImageId, 0});
  const track_t kTrackId = 1;
  tracks_.emplace(kTrackId, track);

  const double kMinAngleDeg = 5.0;
  const int removed =
      track_filter_.FilterTrackTriangulationAngle(view_graph_, images_,
                                                  tracks_, kMinAngleDeg);

  EXPECT_EQ(1, removed);
  EXPECT_TRUE(tracks_.at(kTrackId).observations.empty());
}

// -----------------------------------------------------------------------------
// 2) Normal case: a track with two cameras forming a large triangulation angle
//    should NOT be filtered.
// -----------------------------------------------------------------------------
TEST_F(TrackFilterTest_86, TrackWithLargeTriangulationAngleIsKept_86) {
  const image_t kImageId1 = 1;
  const image_t kImageId2 = 2;

  // Two cameras on opposite sides of the point: large angle at the 3D point.
  AddImageWithCenter(kImageId1, Eigen::Vector3d(-1.0, 0.0, 0.0));
  AddImageWithCenter(kImageId2, Eigen::Vector3d(1.0, 0.0, 0.0));

  Track track;
  track.xyz = Eigen::Vector3d::Zero();
  track.observations.push_back({kImageId1, 0});
  track.observations.push_back({kImageId2, 1});
  const track_t kTrackId = 1;
  tracks_.emplace(kTrackId, track);

  const double kMinAngleDeg = 10.0;
  const int removed =
      track_filter_.FilterTrackTriangulationAngle(view_graph_, images_,
                                                  tracks_, kMinAngleDeg);

  EXPECT_EQ(0, removed);  // No track should be filtered.
  ASSERT_TRUE(tracks_.count(kTrackId));
  EXPECT_EQ(2u, tracks_.at(kTrackId).observations.size());
}

// -----------------------------------------------------------------------------
// 3) Mixed tracks: some should be filtered, some should be kept.
//    - Track 1: single observation -> filtered
//    - Track 2: two observations but effectively zero baseline (same center)
//               -> filtered as having too small triangulation angle
//    - Track 3: two observations with large baseline -> kept
// -----------------------------------------------------------------------------
TEST_F(TrackFilterTest_86, MixedTracksFilteringBehavior_86) {
  images_.clear();
  tracks_.clear();

  const image_t kImageIdA = 1;
  const image_t kImageIdB = 2;

  // Both cameras initially at the same center for small-angle tracks.
  AddImageWithCenter(kImageIdA, Eigen::Vector3d(0.0, 0.0, 0.0));
  AddImageWithCenter(kImageIdB, Eigen::Vector3d(0.0, 0.0, 0.0));

  // Track 1: single observation -> must be removed.
  Track track1;
  track1.xyz = Eigen::Vector3d(1.0, 0.0, 0.0);
  track1.observations.push_back({kImageIdA, 0});
  const track_t kTrackId1 = 1;
  tracks_.emplace(kTrackId1, track1);

  // Track 2: two observations from cameras at identical centers -> small angle.
  Track track2;
  track2.xyz = Eigen::Vector3d(0.0, 1.0, 0.0);
  track2.observations.push_back({kImageIdA, 0});
  track2.observations.push_back({kImageIdB, 1});
  const track_t kTrackId2 = 2;
  tracks_.emplace(kTrackId2, track2);

  // Track 3: two observations with large baseline.
  // Move camera B to get a large angle at the 3D point.
  images_.at(kImageIdB).SetCenter(Eigen::Vector3d(1.0, 0.0, 0.0));

  Track track3;
  track3.xyz = Eigen::Vector3d::Zero();
  track3.observations.push_back({kImageIdA, 0});
  track3.observations.push_back({kImageIdB, 1});
  const track_t kTrackId3 = 3;
  tracks_.emplace(kTrackId3, track3);

  const double kMinAngleDeg = 5.0;
  const int removed =
      track_filter_.FilterTrackTriangulationAngle(view_graph_, images_,
                                                  tracks_, kMinAngleDeg);

  // Two tracks should have been filtered (track 1 and 2).
  EXPECT_EQ(2, removed);

  ASSERT_TRUE(tracks_.count(kTrackId1));
  ASSERT_TRUE(tracks_.count(kTrackId2));
  ASSERT_TRUE(tracks_.count(kTrackId3));

  EXPECT_TRUE(tracks_.at(kTrackId1).observations.empty());
  EXPECT_TRUE(tracks_.at(kTrackId2).observations.empty());
  EXPECT_EQ(2u, tracks_.at(kTrackId3).observations.size());
}

// -----------------------------------------------------------------------------
// 4) Error / exceptional case: if an observation refers to an image that is not
//    present in the images map, the underlying access (images.at) should throw.
//    We verify that this exception is propagated.
// -----------------------------------------------------------------------------
TEST_F(TrackFilterTest_86, ThrowsWhenObservationImageIsMissing_86) {
  images_.clear();
  tracks_.clear();

  Track track;
  track.xyz = Eigen::Vector3d::Zero();
  // Image id 999 is NOT inserted into images_.
  track.observations.push_back({static_cast<image_t>(999), 0});
  const track_t kTrackId = 1;
  tracks_.emplace(kTrackId, track);

  const double kMinAngleDeg = 5.0;

  EXPECT_THROW(
      {
        TrackFilter local_filter;
        local_filter.FilterTrackTriangulationAngle(view_graph_, images_,
                                                   tracks_, kMinAngleDeg);
      },
      std::out_of_range);
}

}  // namespace glomap
