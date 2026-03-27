#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking the colmap::Database class to provide controlled inputs for testing

class MockColmapDatabase : public colmap::Database {

public:

    MOCK_METHOD(std::vector<colmap::Image>, ReadAllImages, (), (const));

    MOCK_METHOD(colmap::FeatureKeypoints, ReadKeypoints, (image_t), (const));

    MOCK_METHOD(std::vector<colmap::Camera>, ReadAllCameras, (), (const));

    MOCK_METHOD(std::vector<colmap::Rig>, ReadAllRigs, (), (const));

    MOCK_METHOD(std::vector<colmap::Frame>, ReadAllFrames, (), (const));

    MOCK_METHOD(colmap::TwoViewGeometry, ReadTwoViewGeometry, (image_t, image_t), (const));

    MOCK_METHOD(std::vector<std::pair<colmap::image_pair_t, colmap::FeatureMatches>>, ReadAllMatches, (), (const));

};



using namespace glomap;



// Test fixture for ConvertDatabaseToGlomap

class ConvertDatabaseToGlomapTest_122 : public ::testing::Test {

protected:

    MockColmapDatabase mock_database;

    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

};



// Normal Operation Test

TEST_F(ConvertDatabaseToGlomapTest_122, ConvertWithValidData_122) {

    // Arrange

    colmap::Image mock_image{1, "mock_image.png"};

    colmap::FeatureKeypoints keypoints = {colmap::Point2D(10.0, 15.0)};

    std::vector<colmap::Camera> cameras_colmap = {{1}};

    std::vector<colmap::Rig> rigs_colmap = {{1}};

    std::vector<colmap::Frame> frames_colmap = {{1}};

    colmap::TwoViewGeometry two_view_geometry{colmap::TwoViewGeometry::CALIBRATED};

    std::vector<std::pair<colmap::image_pair_t, colmap::FeatureMatches>> matches = {

        {1, {{0, 1}}}

    };



    EXPECT_CALL(mock_database, ReadAllImages()).WillOnce(::testing::Return(std::vector<colmap::Image>{mock_image}));

    EXPECT_CALL(mock_database, ReadKeypoints(1)).WillOnce(::testing::Return(keypoints));

    EXPECT_CALL(mock_database, ReadAllCameras()).WillOnce(::testing::Return(cameras_colmap));

    EXPECT_CALL(mock_database, ReadAllRigs()).WillOnce(::testing::Return(rigs_colmap));

    EXPECT_CALL(mock_database, ReadAllFrames()).WillOnce(::testing::Return(frames_colmap));

    EXPECT_CALL(mock_database, ReadTwoViewGeometry(1, 2)).WillOnce(::testing::Return(two_view_geometry));

    EXPECT_CALL(mock_database, ReadAllMatches()).WillOnce(::testing::Return(matches));



    // Act

    ConvertDatabaseToGlomap(mock_database, view_graph, rigs, cameras, frames, images);



    // Assert

    ASSERT_EQ(images.size(), 1);

    ASSERT_EQ(cameras.size(), 1);

    ASSERT_EQ(rigs.size(), 1);

    ASSERT_EQ(frames.size(), 1);

    ASSERT_EQ(view_graph.image_pairs.size(), 1);

}



// Boundary Condition Test: No Images

TEST_F(ConvertDatabaseToGlomapTest_122, ConvertWithNoImages_122) {

    // Arrange

    EXPECT_CALL(mock_database, ReadAllImages()).WillOnce(::testing::Return(std::vector<colmap::Image>{}));



    // Act

    ConvertDatabaseToGlomap(mock_database, view_graph, rigs, cameras, frames, images);



    // Assert

    ASSERT_EQ(images.size(), 0);

}



// Boundary Condition Test: No Cameras

TEST_F(ConvertDatabaseToGlomapTest_122, ConvertWithNoCameras_122) {

    // Arrange

    colmap::Image mock_image{1, "mock_image.png"};

    EXPECT_CALL(mock_database, ReadAllImages()).WillOnce(::testing::Return(std::vector<colmap::Image>{mock_image}));

    EXPECT_CALL(mock_database, ReadKeypoints(1)).WillOnce(::testing::Return(colmap::FeatureKeypoints{}));

    EXPECT_CALL(mock_database, ReadAllCameras()).WillOnce(::testing::Return(std::vector<colmap::Camera>{}));



    // Act

    ConvertDatabaseToGlomap(mock_database, view_graph, rigs, cameras, frames, images);



    // Assert

    ASSERT_EQ(images.size(), 1);

    ASSERT_EQ(cameras.size(), 0);

}



// Boundary Condition Test: No Rigs

TEST_F(ConvertDatabaseToGlomapTest_122, ConvertWithNoRigs_122) {

    // Arrange

    colmap::Image mock_image{1, "mock_image.png"};

    EXPECT_CALL(mock_database, ReadAllImages()).WillOnce(::testing::Return(std::vector<colmap::Image>{mock_image}));

    EXPECT_CALL(mock_database, ReadKeypoints(1)).WillOnce(::testing::Return(colmap::FeatureKeypoints{}));

    EXPECT_CALL(mock_database, ReadAllCameras()).WillOnce(::testing::Return(std::vector<colmap::Camera>{{1}}));

    EXPECT_CALL(mock_database, ReadAllRigs()).WillOnce(::testing::Return(std::vector<colmap::Rig>{}));



    // Act

    ConvertDatabaseToGlomap(mock_database, view_graph, rigs, cameras, frames, images);



    // Assert

    ASSERT_EQ(images.size(), 1);

    ASSERT_EQ(rigs.size(), 0);

}



// Boundary Condition Test: No Frames

TEST_F(ConvertDatabaseToGlomapTest_122, ConvertWithNoFrames_122) {

    // Arrange

    colmap::Image mock_image{1, "mock_image.png"};

    EXPECT_CALL(mock_database, ReadAllImages()).WillOnce(::testing::Return(std::vector<colmap::Image>{mock_image}));

    EXPECT_CALL(mock_database, ReadKeypoints(1)).WillOnce(::testing::Return(colmap::FeatureKeypoints{}));

    EXPECT_CALL(mock_database, ReadAllCameras()).WillOnce(::testing::Return(std::vector<colmap::Camera>{{1}}));

    EXPECT_CALL(mock_database, ReadAllRigs()).WillOnce(::testing::Return(std::vector<colmap::Rig>{{1}}));

    EXPECT_CALL(mock_database, ReadAllFrames()).WillOnce(::testing::Return(std::vector<colmap::Frame>{}));



    // Act

    ConvertDatabaseToGlomap(mock_database, view_graph, rigs, cameras, frames, images);



    // Assert

    ASSERT_EQ(images.size(), 1);

    ASSERT_EQ(frames.size(), 0);

}



// Boundary Condition Test: No Matches

TEST_F(ConvertDatabaseToGlomapTest_122, ConvertWithNoMatches_122) {

    // Arrange

    colmap::Image mock_image{1, "mock_image.png"};

    EXPECT_CALL(mock_database, ReadAllImages()).WillOnce(::testing::Return(std::vector<colmap::Image>{mock_image}));

    EXPECT_CALL(mock_database, ReadKeypoints(1)).WillOnce(::testing::Return(colmap::FeatureKeypoints{}));

    EXPECT_CALL(mock_database, ReadAllCameras()).WillOnce(::testing::Return(std::vector<colmap::Camera>{{1}}));

    EXPECT_CALL(mock_database, ReadAllRigs()).WillOnce(::testing::Return(std::vector<colmap::Rig>{{1}}));

    EXPECT_CALL(mock_database, ReadAllFrames()).WillOnce(::testing::Return(std::vector<colmap::Frame>{{1}}));

    EXPECT_CALL(mock_database, ReadAllMatches()).WillOnce(::testing::Return(std::vector<std::pair<colmap::image_pair_t, colmap::FeatureMatches>>{}));



    // Act

    ConvertDatabaseToGlomap(mock_database, view_graph, rigs, cameras, frames, images);



    // Assert

    ASSERT_EQ(images.size(), 1);

    ASSERT_EQ(view_graph.image_pairs.size(), 0);

}



// Exceptional Case Test: Invalid Image ID

TEST_F(ConvertDatabaseToGlomapTest_122, ConvertWithInvalidImageID_122) {

    // Arrange

    colmap::Image mock_image{colmap::kInvalidImageId, "mock_image.png"};

    EXPECT_CALL(mock_database, ReadAllImages()).WillOnce(::testing::Return(std::vector<colmap::Image>{mock_image}));



    // Act

    ConvertDatabaseToGlomap(mock_database, view_graph, rigs, cameras, frames, images);



    // Assert

    ASSERT_EQ(images.size(), 0);

}



// Exceptional Case Test: Invalid Frame ID

TEST_F(ConvertDatabaseToGlomapTest_122, ConvertWithInvalidFrameID_122) {

    // Arrange

    colmap::Image mock_image{1, "mock_image.png"};

    colmap::Frame mock_frame{colmap::kInvalidFrameId};

    EXPECT_CALL(mock_database, ReadAllImages()).WillOnce(::testing::Return(std::vector<colmap::Image>{mock_image}));

    EXPECT_CALL(mock_database, ReadKeypoints(1)).WillOnce(::testing::Return(colmap::FeatureKeypoints{}));

    EXPECT_CALL(mock_database, ReadAllFrames()).WillOnce(::testing::Return(std::vector<colmap::Frame>{mock_frame}));



    // Act

    ConvertDatabaseToGlomap(mock_database, view_graph, rigs, cameras, frames, images);



    // Assert

    ASSERT_EQ(images.size(), 1);

    ASSERT_EQ(frames.size(), 0);

}
