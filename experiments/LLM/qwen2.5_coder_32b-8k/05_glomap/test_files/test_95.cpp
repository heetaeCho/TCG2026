#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/scene/view_graph.h"

#include "./TestProjects/glomap/glomap/scene/image_pair.h"



namespace glomap {

namespace {



class ViewGraphTest_95 : public ::testing::Test {

protected:

    ViewGraph view_graph;



    void SetUp() override {

        // Initialize the image_pairs map with some test data

        ImagePair valid_pair1(1, 2);

        ImagePair valid_pair2(2, 3);

        ImagePair invalid_pair(4, 5);

        invalid_pair.is_valid = false;



        view_graph.image_pairs[colmap::ImagePairToPairId(1, 2)] = valid_pair1;

        view_graph.image_pairs[colmap::ImagePairToPairId(2, 3)] = valid_pair2;

        view_graph.image_pairs[colmap::ImagePairToPairId(4, 5)] = invalid_pair;

    }

};



TEST_F(ViewGraphTest_95, CreateImageAdjacencyList_ValidPairs_95) {

    auto adjacency_list = view_graph.CreateImageAdjacencyList();

    

    EXPECT_EQ(adjacency_list.size(), 3);

    EXPECT_TRUE(adjacency_list.find(1) != adjacency_list.end());

    EXPECT_TRUE(adjacency_list.find(2) != adjacency_list.end());

    EXPECT_TRUE(adjacency_list.find(3) != adjacency_list.end());



    EXPECT_EQ(adjacency_list[1].size(), 1);

    EXPECT_EQ(adjacency_list[2].size(), 2);

    EXPECT_EQ(adjacency_list[3].size(), 1);



    EXPECT_TRUE(adjacency_list[1].find(2) != adjacency_list[1].end());

    EXPECT_TRUE(adjacency_list[2].find(1) != adjacency_list[2].end());

    EXPECT_TRUE(adjacency_list[2].find(3) != adjacency_list[2].end());

    EXPECT_TRUE(adjacency_list[3].find(2) != adjacency_list[3].end());

}



TEST_F(ViewGraphTest_95, CreateImageAdjacencyList_NoPairs_95) {

    view_graph.image_pairs.clear();

    auto adjacency_list = view_graph.CreateImageAdjacencyList();



    EXPECT_EQ(adjacency_list.size(), 0);

}



TEST_F(ViewGraphTest_95, CreateImageAdjacencyList_OnlyInvalidPair_95) {

    view_graph.image_pairs.clear();

    ImagePair invalid_pair(4, 5);

    invalid_pair.is_valid = false;

    view_graph.image_pairs[colmap::ImagePairToPairId(4, 5)] = invalid_pair;



    auto adjacency_list = view_graph.CreateImageAdjacencyList();



    EXPECT_EQ(adjacency_list.size(), 0);

}



} // namespace

} // namespace glomap
