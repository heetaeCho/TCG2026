#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/io/pose_io.cc"

#include "TestProjects/glomap/glomap/scene/frame.h"

#include "TestProjects/glomap/glomap/scene/image.h"

#include <fstream>

#include <unordered_map>



using namespace glomap;

using testing::ElementsAre;



class ReadGravityTest_126 : public ::testing::Test {

protected:

    void SetUp() override {

        images.clear();

        image_t img_id = 0;

        camera_t cam_id = 0;

        std::string file_name = "test_image.jpg";

        images[img_id] = Image(img_id, cam_id, file_name);

        images[img_id].frame_ptr = new Frame();

    }



    void TearDown() override {

        for (auto& [id, img] : images) {

            delete img.frame_ptr;

        }

        images.clear();

    }



    std::unordered_map<image_t, Image> images;

};



TEST_F(ReadGravityTest_126, NormalOperation_126) {

    std::string gravity_path = "test_gravity.txt";

    std::ofstream file(gravity_path);

    file << "test_image.jpg 0.1 0.2 0.3\n";

    file.close();



    ReadGravity(gravity_path, images);



    EXPECT_TRUE(images[0].HasTrivialFrame());

    EXPECT_EQ(images[0].frame_ptr->gravity_info.GetGravity(), Eigen::Vector3d(0.1, 0.2, 0.3));

}



TEST_F(ReadGravityTest_126, BoundaryCondition_EmptyFile_126) {

    std::string gravity_path = "test_gravity_empty.txt";

    std::ofstream file(gravity_path);

    file.close();



    ReadGravity(gravity_path, images);



    EXPECT_FALSE(images[0].HasTrivialFrame());

}



TEST_F(ReadGravityTest_126, BoundaryCondition_NoMatchingImage_126) {

    std::string gravity_path = "test_gravity_no_match.txt";

    std::ofstream file(gravity_path);

    file << "nonexistent_image.jpg 0.1 0.2 0.3\n";

    file.close();



    ReadGravity(gravity_path, images);



    EXPECT_FALSE(images[0].HasTrivialFrame());

}



TEST_F(ReadGravityTest_126, ExceptionalCase_FileNotFound_126) {

    std::string gravity_path = "nonexistent_gravity.txt";



    testing::internal::CaptureStderr();

    ReadGravity(gravity_path, images);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_TRUE(output.find("cannot open file") != std::string::npos);

}



TEST_F(ReadGravityTest_126, ExceptionalCase_InvalidFormat_126) {

    std::string gravity_path = "test_gravity_invalid_format.txt";

    std::ofstream file(gravity_path);

    file << "test_image.jpg 0.1 0.2\n"; // Invalid format

    file.close();



    testing::internal::CaptureStderr();

    ReadGravity(gravity_path, images);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_TRUE(output.find("invalid gravity data") != std::string::npos || 

                output.find("std::stod") != std::string::npos); // Depending on how the error is logged

}
