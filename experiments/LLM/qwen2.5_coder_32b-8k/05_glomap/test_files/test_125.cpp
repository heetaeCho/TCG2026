#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/scene/image.h"

#include "glomap/scene/view_graph.h"

#include "glomap/io/pose_io.cc"



using namespace glomap;

using ::testing::ElementsAre;



TEST(ReadRelWeightTest_125, NormalOperation_125) {

    std::unordered_map<image_t, Image> images = {

        {1, Image(1, 0, "file1")},

        {2, Image(2, 0, "file2")}

    };

    ViewGraph view_graph;

    view_graph.image_pairs[colmap::ImagePairToPairId(1, 2)] = ImagePair(1, 2);



    std::string file_content = R"(file1 file2 0.5)";

    std::ofstream temp_file("temp.txt");

    temp_file << file_content;

    temp_file.close();



    ReadRelWeight("temp.txt", images, view_graph);



    EXPECT_EQ(view_graph.image_pairs[colmap::ImagePairToPairId(1, 2)].weight, 0.5);

}



TEST(ReadRelWeightTest_125, BoundaryCondition_EmptyFile_125) {

    std::unordered_map<image_t, Image> images = {

        {1, Image(1, 0, "file1")},

        {2, Image(2, 0, "file2")}

    };

    ViewGraph view_graph;

    view_graph.image_pairs[colmap::ImagePairToPairId(1, 2)] = ImagePair(1, 2);



    std::ofstream temp_file("temp.txt");

    temp_file.close();



    ReadRelWeight("temp.txt", images, view_graph);



    EXPECT_EQ(view_graph.image_pairs[colmap::ImagePairToPairId(1, 2)].weight, -1);

}



TEST(ReadRelWeightTest_125, BoundaryCondition_MissingImages_125) {

    std::unordered_map<image_t, Image> images = {

        {1, Image(1, 0, "file1")}

    };

    ViewGraph view_graph;

    view_graph.image_pairs[colmap::ImagePairToPairId(1, 2)] = ImagePair(1, 2);



    std::string file_content = R"(file1 file2 0.5)";

    std::ofstream temp_file("temp.txt");

    temp_file << file_content;

    temp_file.close();



    ReadRelWeight("temp.txt", images, view_graph);



    EXPECT_EQ(view_graph.image_pairs[colmap::ImagePairToPairId(1, 2)].weight, -1);

}



TEST(ReadRelWeightTest_125, BoundaryCondition_NoMatchingPairs_125) {

    std::unordered_map<image_t, Image> images = {

        {1, Image(1, 0, "file1")},

        {2, Image(2, 0, "file2")}

    };

    ViewGraph view_graph;



    std::string file_content = R"(file1 file2 0.5)";

    std::ofstream temp_file("temp.txt");

    temp_file << file_content;

    temp_file.close();



    ReadRelWeight("temp.txt", images, view_graph);



    EXPECT_TRUE(view_graph.image_pairs.empty());

}



TEST(ReadRelWeightTest_125, ExceptionalCase_FileNotFound_125) {

    std::unordered_map<image_t, Image> images = {

        {1, Image(1, 0, "file1")},

        {2, Image(2, 0, "file2")}

    };

    ViewGraph view_graph;

    view_graph.image_pairs[colmap::ImagePairToPairId(1, 2)] = ImagePair(1, 2);



    EXPECT_THROW({

        ReadRelWeight("non_existent_file.txt", images, view_graph);

    }, std::ifstream::failure);

}



TEST(ReadRelWeightTest_125, ExceptionalCase_InvalidFormat_125) {

    std::unordered_map<image_t, Image> images = {

        {1, Image(1, 0, "file1")},

        {2, Image(2, 0, "file2")}

    };

    ViewGraph view_graph;

    view_graph.image_pairs[colmap::ImagePairToPairId(1, 2)] = ImagePair(1, 2);



    std::string file_content = R"(file1 file2 invalid_weight)";

    std::ofstream temp_file("temp.txt");

    temp_file << file_content;

    temp_file.close();



    ReadRelWeight("temp.txt", images, view_graph);



    EXPECT_EQ(view_graph.image_pairs[colmap::ImagePairToPairId(1, 2)].weight, -1);

}
