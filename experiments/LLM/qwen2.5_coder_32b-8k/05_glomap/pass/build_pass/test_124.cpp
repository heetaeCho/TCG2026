#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/io/pose_io.cc"

#include "glomap/scene/image.h"

#include "glomap/scene/image_pair.h"

#include "glomap/scene/view_graph.h"

#include <fstream>

#include <sstream>



using namespace glomap;

using ::testing::Eq;



class ReadRelPoseTest_124 : public ::testing::Test {

protected:

    std::unordered_map<image_t, Image> images;

    ViewGraph view_graph;

};



TEST_F(ReadRelPoseTest_124, NormalOperation_124) {

    // Arrange

    std::string file_path = "test_data.txt";

    std::ofstream test_file(file_path);

    test_file << "img1 img2 0.1 0.2 0.3 0.4 5.6 7.8 9.0\n";

    test_file.close();



    // Act

    ReadRelPose(file_path, images, view_graph);



    // Assert

    ASSERT_EQ(images.size(), 2);

    ASSERT_EQ(view_graph.image_pairs.size(), 1);



    const auto& image_pair = view_graph.image_pairs.begin()->second;

    EXPECT_EQ(image_pair.image_id1, 1);

    EXPECT_EQ(image_pair.image_id2, 2);

    EXPECT_TRUE(image_pair.is_valid);

    EXPECT_NEAR(image_pair.cam2_from_cam1.rotation.coeffs()[0], 0.1, 1e-9);

    EXPECT_NEAR(image_pair.cam2_from_cam1.translation[0], 5.6, 1e-9);



    std::remove(file_path.c_str());

}



TEST_F(ReadRelPoseTest_124, BoundaryConditions_EmptyFile_124) {

    // Arrange

    std::string file_path = "test_data.txt";

    std::ofstream test_file(file_path);

    test_file.close();



    // Act

    ReadRelPose(file_path, images, view_graph);



    // Assert

    EXPECT_EQ(images.size(), 0);

    EXPECT_EQ(view_graph.image_pairs.size(), 0);



    std::remove(file_path.c_str());

}



TEST_F(ReadRelPoseTest_124, BoundaryConditions_SingleLine_124) {

    // Arrange

    std::string file_path = "test_data.txt";

    std::ofstream test_file(file_path);

    test_file << "img1 img2 0.1 0.2 0.3 0.4 5.6 7.8 9.0\n";

    test_file.close();



    // Act

    ReadRelPose(file_path, images, view_graph);



    // Assert

    EXPECT_EQ(images.size(), 2);

    EXPECT_EQ(view_graph.image_pairs.size(), 1);



    std::remove(file_path.c_str());

}



TEST_F(ReadRelPoseTest_124, ExceptionalCase_InvalidFile_124) {

    // Arrange

    std::string file_path = "non_existent_file.txt";



    // Act & Assert

    EXPECT_THROW(ReadRelPose(file_path, images, view_graph), std::ios_base::failure);

}



TEST_F(ReadRelPoseTest_124, ExceptionalCase_MissingData_124) {

    // Arrange

    std::string file_path = "test_data.txt";

    std::ofstream test_file(file_path);

    test_file << "img1 img2 0.1 0.2\n"; // Missing data

    test_file.close();



    // Act & Assert

    EXPECT_THROW(ReadRelPose(file_path, images, view_graph), std::invalid_argument);



    std::remove(file_path.c_str());

}



TEST_F(ReadRelPoseTest_124, VerifyExternalInteractions_UpdateExistingPair_124) {

    // Arrange

    std::string file_path = "test_data.txt";

    std::ofstream test_file(file_path);

    test_file << "img1 img2 0.1 0.2 0.3 0.4 5.6 7.8 9.0\n"

              << "img1 img2 0.9 0.8 0.7 0.6 1.2 3.4 5.6\n"; // Update existing pair

    test_file.close();



    images.insert({1, Image(1, -1, "img1")});

    images.insert({2, Image(2, -1, "img2")});



    view_graph.image_pairs.insert({

        colmap::ImagePairToPairId(1, 2),

        ImagePair(1, 2)

    });



    // Act

    ReadRelPose(file_path, images, view_graph);



    // Assert

    EXPECT_EQ(images.size(), 2);

    EXPECT_EQ(view_graph.image_pairs.size(), 1);



    const auto& image_pair = view_graph.image_pairs.begin()->second;

    EXPECT_TRUE(image_pair.is_valid);

    EXPECT_NEAR(image_pair.cam2_from_cam1.rotation.coeffs()[0], 0.9, 1e-9);

    EXPECT_NEAR(image_pair.cam2_from_cam1.translation[0], 1.2, 1e-9);



    std::remove(file_path.c_str());

}
