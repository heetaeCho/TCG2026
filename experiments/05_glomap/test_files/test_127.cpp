#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <fstream>

#include <string>

#include <unordered_map>

#include "TestProjects/glomap/glomap/scene/image.h"

#include "TestProjects/glomap/glomap/io/pose_io.cc"



using namespace glomap;

using ::testing::_;

using ::testing::NiceMock;



class MockImage : public Image {

public:

    MOCK_CONST_METHOD0(IsRegistered, bool());

    MOCK_CONST_METHOD0(CamFromWorld, Rigid3d());

};



TEST_F(PoseIOTest_127, WriteGlobalRotation_EmptyImagesMap_127) {

    std::unordered_map<image_t, Image> images;

    std::string file_path = "test_output.txt";

    WriteGlobalRotation(file_path, images);



    std::ifstream file(file_path);

    EXPECT_FALSE(file.peek() != EOF); // File should be empty

}



TEST_F(PoseIOTest_127, WriteGlobalRotation_SingleRegisteredImage_127) {

    NiceMock<MockImage> image;

    EXPECT_CALL(image, IsRegistered()).WillOnce(::testing::Return(true));

    Rigid3d mock_cam_from_world = Eigen::Quaterniond(1, 0, 0, 0);

    EXPECT_CALL(image, CamFromWorld()).WillRepeatedly(::testing::Return(mock_cam_from_world));



    std::unordered_map<image_t, Image> images = {{1, image}};

    std::string file_path = "test_output.txt";

    WriteGlobalRotation(file_path, images);



    std::ifstream file(file_path);

    std::string line;

    std::getline(file, line);

    EXPECT_EQ(line, " 0 0 0 1");

}



TEST_F(PoseIOTest_127, WriteGlobalRotation_MultipleRegisteredImages_127) {

    NiceMock<MockImage> image1, image2;

    EXPECT_CALL(image1, IsRegistered()).WillOnce(::testing::Return(true));

    Rigid3d mock_cam_from_world1 = Eigen::Quaterniond(1, 0, 0, 0);

    EXPECT_CALL(image1, CamFromWorld()).WillRepeatedly(::testing::Return(mock_cam_from_world1));



    EXPECT_CALL(image2, IsRegistered()).WillOnce(::testing::Return(true));

    Rigid3d mock_cam_from_world2 = Eigen::Quaterniond(0, 1, 0, 0);

    EXPECT_CALL(image2, CamFromWorld()).WillRepeatedly(::testing::Return(mock_cam_from_world2));



    std::unordered_map<image_t, Image> images = {{1, image1}, {2, image2}};

    std::string file_path = "test_output.txt";

    WriteGlobalRotation(file_path, images);



    std::ifstream file(file_path);

    std::string line;

    std::getline(file, line);

    EXPECT_EQ(line, " 0 0 0 1");

    std::getline(file, line);

    EXPECT_EQ(line, " 0 1 0 0");

}



TEST_F(PoseIOTest_127, WriteGlobalRotation_UnregisteredImagesIgnored_127) {

    NiceMock<MockImage> image;

    EXPECT_CALL(image, IsRegistered()).WillOnce(::testing::Return(false));



    std::unordered_map<image_t, Image> images = {{1, image}};

    std::string file_path = "test_output.txt";

    WriteGlobalRotation(file_path, images);



    std::ifstream file(file_path);

    EXPECT_FALSE(file.peek() != EOF); // File should be empty

}



TEST_F(PoseIOTest_127, WriteGlobalRotation_FileWriteFailure_127) {

    NiceMock<MockImage> image;

    EXPECT_CALL(image, IsRegistered()).WillOnce(::testing::Return(true));

    Rigid3d mock_cam_from_world = Eigen::Quaterniond(1, 0, 0, 0);

    EXPECT_CALL(image, CamFromWorld()).WillRepeatedly(::testing::Return(mock_cam_from_world));



    std::unordered_map<image_t, Image> images = {{1, image}};

    std::string file_path = "/nonexistent/path/test_output.txt";

    WriteGlobalRotation(file_path, images);



    // This test case does not have a direct observable effect since exceptions are not thrown.

    // We assume the function handles file writing errors gracefully without crashing.

}
