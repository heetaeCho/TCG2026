// File: colmap_converter_test_122.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <unordered_map>

#include "glomap/io/colmap_converter.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/image.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/camera.h"
#include "glomap/scene/rig.h"      // assuming this exists
#include "glomap/geometry/rigid3d.h"

using ::testing::_;
using ::testing::Return;
using ::testing::ElementsAre;
using ::testing::NiceMock;

namespace {

// --- Minimal mocking interface for the external COLMAP database -------------

namespace colmap {

class Database {
 public:
  virtual ~Database() = default;

  // The signatures are inferred from the implementation in colmap_converter.cc.
  virtual std::vector<Image> ReadAllImages() const = 0;
  virtual FeatureKeypoints ReadKeypoints(image_t image_id) const = 0;
  virtual std::vector<Camera> ReadAllCameras() const = 0;
  virtual std::vector<Rig> ReadAllRigs() const = 0;
  virtual std::vector<Frame> ReadAllFrames() const = 0;
  virtual std::vector<std::pair<image_pair_t, FeatureMatches>> ReadAllMatches()
      const = 0;
  virtual TwoViewGeometry ReadTwoViewGeometry(image_t image_id1,
                                              image_t image_id2) const = 0;
};

}  // namespace colmap

class MockDatabase : public colmap::Database {
 public:
  MOCK_METHOD(std::vector<colmap::Image>, ReadAllImages, (), (const, override));
  MOCK_METHOD(colmap::FeatureKeypoints,
              ReadKeypoints,
              (colmap::image_t),
              (const, override));
  MOCK_METHOD(std::vector<colmap::Camera>,
              ReadAllCameras,
              (),
              (const, override));
  MOCK_METHOD(std::vector<colmap::Rig>, ReadAllRigs, (), (const, override));
  MOCK_METHOD(std::vector<colmap::Frame>, ReadAllFrames, (), (const, override));
  MOCK_METHOD((std::vector<std::pair<colmap::image_pair_t,
                                     colmap::FeatureMatches>>),
              ReadAllMatches,
              (),
              (const, override));
  MOCK_METHOD(colmap::TwoViewGeometry,
              ReadTwoViewGeometry,
              (colmap::image_t, colmap::image_t),
              (const, override));
};

// -----------------------------------------------------------------------------
// Test fixture
// -----------------------------------------------------------------------------

class ConvertDatabaseToGlomapTest_122 : public ::testing::Test {
 protected:
  void SetUp() override {
    // All containers start empty; each test fills only what it needs.
  }

  // Helper to create a simple COLMAP image.
  colmap::Image MakeColmapImage(colmap::image_t image_id,
                                colmap::camera_t camera_id,
                                const std::string& name) {
    colmap::Image image;
    image.SetImageId(image_id);
    image.SetCameraId(camera_id);
    image.SetName(name);
    return image;
  }

  // Helper to construct a single keypoint.
  colmap::FeatureKeypoint MakeKeypoint(double x, double y) {
    colmap::FeatureKeypoint kp;
    kp.x = x;
    kp.y = y;
    return kp;
  }

  // Containers passed to ConvertDatabaseToGlomap.
  glomap::ViewGraph view_graph_;
  std::unordered_map<glomap::rig_t, glomap::Rig> rigs_;
  std::unordered_map<glomap::camera_t, glomap::Camera> cameras_;
  std::unordered_map<glomap::frame_t, glomap::Frame> frames_;
  std::unordered_map<glomap::image_t, glomap::Image> images_;
};

// -----------------------------------------------------------------------------
// TEST 1: Normal behavior for images and keypoints
//   - Valid images are inserted.
//   - Invalid image IDs are skipped.
//   - Per-image keypoints are converted into glomap::Image::features.
// -----------------------------------------------------------------------------

TEST_F(ConvertDatabaseToGlomapTest_122, LoadsImagesAndKeypoints_122) {
  NiceMock<MockDatabase> db;

  // Arrange: two images, one valid, one invalid.
  const colmap::image_t valid_id = 1;
  const colmap::image_t invalid_id = colmap::kInvalidImageId;
  const colmap::camera_t cam_id = 10;

  std::vector<colmap::Image> colmap_images;
  colmap_images.push_back(MakeColmapImage(valid_id, cam_id, "image_1.jpg"));
  colmap_images.push_back(MakeColmapImage(invalid_id, cam_id, "invalid.jpg"));

  // Keypoints for the valid image.
  colmap::FeatureKeypoints kps;
  kps.push_back(MakeKeypoint(10.0, 20.0));
  kps.push_back(MakeKeypoint(30.0, 40.0));

  EXPECT_CALL(db, ReadAllImages())
      .Times(1)
      .WillOnce(Return(colmap_images));

  EXPECT_CALL(db, ReadKeypoints(valid_id))
      .Times(1)
      .WillOnce(Return(kps));

  // No other images should result in keypoint queries.
  EXPECT_CALL(db, ReadKeypoints(invalid_id)).Times(0);

  // Remaining database methods return empty data so that other parts of
  // ConvertDatabaseToGlomap run but don't do anything observable.
  EXPECT_CALL(db, ReadAllCameras())
      .Times(1)
      .WillOnce(Return(std::vector<colmap::Camera>{}));
  EXPECT_CALL(db, ReadAllRigs())
      .Times(1)
      .WillOnce(Return(std::vector<colmap::Rig>{}));
  EXPECT_CALL(db, ReadAllFrames())
      .Times(1)
      .WillOnce(Return(std::vector<colmap::Frame>{}));
  EXPECT_CALL(db, ReadAllMatches())
      .Times(1)
      .WillOnce(Return(
          std::vector<std::pair<colmap::image_pair_t, colmap::FeatureMatches>>{
          }));
  EXPECT_CALL(db, ReadTwoViewGeometry(_, _)).Times(0);

  // Act
  glomap::ConvertDatabaseToGlomap(
      db, view_graph_, rigs_, cameras_, frames_, images_);

  // Assert: only the valid image is present.
  ASSERT_EQ(images_.size(), 1u);
  auto it = images_.find(valid_id);
  ASSERT_NE(it, images_.end());

  const glomap::Image& img = it->second;
  EXPECT_EQ(img.image_id, valid_id);
  EXPECT_EQ(img.camera_id, cam_id);
  EXPECT_EQ(img.file_name, "image_1.jpg");

  // Features must match the COLMAP keypoints.
  ASSERT_EQ(img.features.size(), kps.size());
  EXPECT_DOUBLE_EQ(img.features[0].x(), 10.0);
  EXPECT_DOUBLE_EQ(img.features[0].y(), 20.0);
  EXPECT_DOUBLE_EQ(img.features[1].x(), 30.0);
  EXPECT_DOUBLE_EQ(img.features[1].y(), 40.0);
}

// -----------------------------------------------------------------------------
// TEST 2: Boundary behavior in feature matches
//   - Only matches with valid point2D indices are kept.
//   - Out-of-range or invalid indices are ignored.
//   - The Eigen::MatrixXi inside ImagePair is resized to the number of
//     actually used matches.
// -----------------------------------------------------------------------------

TEST_F(ConvertDatabaseToGlomapTest_122,
       FiltersInvalidFeatureMatchesAndResizesMatrix_122) {
  NiceMock<MockDatabase> db;

  // Images: two valid images with simple keypoints.
  const colmap::image_t img_id1 = 1;
  const colmap::image_t img_id2 = 2;

  std::vector<colmap::Image> colmap_images;
  colmap_images.push_back(MakeColmapImage(img_id1, 10, "img1.jpg"));
  colmap_images.push_back(MakeColmapImage(img_id2, 20, "img2.jpg"));

  EXPECT_CALL(db, ReadAllImages())
      .Times(1)
      .WillOnce(Return(colmap_images));

  // Keypoints: 3 per image.
  colmap::FeatureKeypoints kps1;
  kps1.push_back(MakeKeypoint(0.0, 0.0));
  kps1.push_back(MakeKeypoint(1.0, 1.0));
  kps1.push_back(MakeKeypoint(2.0, 2.0));

  colmap::FeatureKeypoints kps2;
  kps2.push_back(MakeKeypoint(10.0, 10.0));
  kps2.push_back(MakeKeypoint(20.0, 20.0));
  kps2.push_back(MakeKeypoint(30.0, 30.0));

  EXPECT_CALL(db, ReadKeypoints(img_id1))
      .Times(1)
      .WillOnce(Return(kps1));
  EXPECT_CALL(db, ReadKeypoints(img_id2))
      .Times(1)
      .WillOnce(Return(kps2));

  // Cameras / rigs / frames not needed for this test.
  EXPECT_CALL(db, ReadAllCameras())
      .Times(1)
      .WillOnce(Return(std::vector<colmap::Camera>{}));
  EXPECT_CALL(db, ReadAllRigs())
      .Times(1)
      .WillOnce(Return(std::vector<colmap::Rig>{}));
  EXPECT_CALL(db, ReadAllFrames())
      .Times(1)
      .WillOnce(Return(std::vector<colmap::Frame>{}));

  // Matches: 4 matches.
  //  - two valid,
  //  - one with invalid index,
  //  - one with out-of-range index.
  colmap::FeatureMatches matches;
  {
    colmap::FeatureMatch m;
    m.point2D_idx1 = 0;
    m.point2D_idx2 = 0;
    matches.push_back(m);  // valid
  }
  {
    colmap::FeatureMatch m;
    m.point2D_idx1 = 1;
    m.point2D_idx2 = 2;
    matches.push_back(m);  // valid
  }
  {
    colmap::FeatureMatch m;
    m.point2D_idx1 = colmap::kInvalidPoint2DIdx;
    m.point2D_idx2 = 1;
    matches.push_back(m);  // invalid (skipped)
  }
  {
    colmap::FeatureMatch m;
    m.point2D_idx1 = 5;  // out-of-range (skipped)
    m.point2D_idx2 = 0;
    matches.push_back(m);
  }

  const colmap::image_pair_t pair_id =
      colmap::ImagePairToPairId(img_id1, img_id2);

  std::vector<std::pair<colmap::image_pair_t, colmap::FeatureMatches>>
      all_matches;
  all_matches.emplace_back(pair_id, matches);

  EXPECT_CALL(db, ReadAllMatches())
      .Times(1)
      .WillOnce(Return(all_matches));

  // Two-view geometry: UNCALIBRATED -> only F is set, FundamentalFromMotion...
  // is not called.
  colmap::TwoViewGeometry two_view;
  two_view.config = colmap::TwoViewGeometry::UNCALIBRATED;
  two_view.F = Eigen::Matrix3d::Identity();

  EXPECT_CALL(db, ReadTwoViewGeometry(img_id1, img_id2))
      .Times(1)
      .WillOnce(Return(two_view));

  // Act
  glomap::ConvertDatabaseToGlomap(
      db, view_graph_, rigs_, cameras_, frames_, images_);

  // Assert
  ASSERT_EQ(view_graph_.image_pairs.size(), 1u);
  auto it_pair = view_graph_.image_pairs.find(pair_id);
  ASSERT_NE(it_pair, view_graph_.image_pairs.end());

  const glomap::ImagePair& image_pair = it_pair->second;

  // Config propagated from TwoViewGeometry.
  EXPECT_EQ(image_pair.config, colmap::TwoViewGeometry::UNCALIBRATED);

  // F propagated from TwoViewGeometry for UNCALIBRATED case.
  EXPECT_TRUE(image_pair.F.isApprox(Eigen::Matrix3d::Identity()));

  // Only the two valid matches should be stored.
  EXPECT_EQ(image_pair.matches.rows(), 2);
  EXPECT_EQ(image_pair.matches.cols(), 2);

  // First valid match.
  EXPECT_EQ(image_pair.matches(0, 0), 0);
  EXPECT_EQ(image_pair.matches(0, 1), 0);
  // Second valid match.
  EXPECT_EQ(image_pair.matches(1, 0), 1);
  EXPECT_EQ(image_pair.matches(1, 1), 2);
}

// -----------------------------------------------------------------------------
// TEST 3: Invalid / degenerate TwoViewGeometry configurations
//   - ImagePair::is_valid is set to false.
//   - Config is propagated.
//   - No F / H assignment happens beyond defaults.
// -----------------------------------------------------------------------------

TEST_F(ConvertDatabaseToGlomapTest_122,
       MarksDegenerateTwoViewGeometriesAsInvalid_122) {
  NiceMock<MockDatabase> db;

  const colmap::image_t img_id1 = 3;
  const colmap::image_t img_id2 = 4;

  std::vector<colmap::Image> colmap_images;
  colmap_images.push_back(MakeColmapImage(img_id1, 10, "img3.jpg"));
  colmap_images.push_back(MakeColmapImage(img_id2, 20, "img4.jpg"));

  EXPECT_CALL(db, ReadAllImages())
      .Times(1)
      .WillOnce(Return(colmap_images));

  // No keypoints needed, since invalid / degenerate views will immediately
  // mark the pair as invalid and continue; matches and keypoints are unused.
  EXPECT_CALL(db, ReadKeypoints(_)).Times(2);

  EXPECT_CALL(db, ReadAllCameras())
      .Times(1)
      .WillOnce(Return(std::vector<colmap::Camera>{}));
  EXPECT_CALL(db, ReadAllRigs())
      .Times(1)
      .WillOnce(Return(std::vector<colmap::Rig>{}));
  EXPECT_CALL(db, ReadAllFrames())
      .Times(1)
      .WillOnce(Return(std::vector<colmap::Frame>{}));

  // Just one pair of images with no actual matches; we exercise the
  // invalid/degenerate branching.
  std::vector<std::pair<colmap::image_pair_t, colmap::FeatureMatches>>
      all_matches;
  all_matches.emplace_back(
      colmap::ImagePairToPairId(img_id1, img_id2),
      colmap::FeatureMatches{}  // empty, won't be used
  );

  EXPECT_CALL(db, ReadAllMatches())
      .Times(1)
      .WillOnce(Return(all_matches));

  // Use DEGENERATE configuration as representative of "invalid" configs.
  colmap::TwoViewGeometry two_view;
  two_view.config = colmap::TwoViewGeometry::DEGENERATE;

  EXPECT_CALL(db, ReadTwoViewGeometry(img_id1, img_id2))
      .Times(1)
      .WillOnce(Return(two_view));

  // Act
  glomap::ConvertDatabaseToGlomap(
      db, view_graph_, rigs_, cameras_, frames_, images_);

  // Assert
  ASSERT_EQ(view_graph_.image_pairs.size(), 1u);
  auto it_pair = view_graph_.image_pairs.find(
      colmap::ImagePairToPairId(img_id1, img_id2));
  ASSERT_NE(it_pair, view_graph_.image_pairs.end());

  const glomap::ImagePair& image_pair = it_pair->second;

  // The pair must be flagged as invalid.
  EXPECT_FALSE(image_pair.is_valid);
  EXPECT_EQ(image_pair.config, colmap::TwoViewGeometry::DEGENERATE);

  // Matches should stay in their default-constructed state (no rows).
  EXPECT_EQ(image_pair.matches.rows(), 0);
  EXPECT_EQ(image_pair.matches.cols(), 0);
}

}  // namespace
