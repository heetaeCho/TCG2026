#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/processors/relpose_filter.h"

#include "glomap/scene/image_pair.h"

#include "glomap/scene/view_graph.h"



using namespace glomap;



class RelPoseFilterTest_81 : public ::testing::Test {

protected:

    ViewGraph view_graph;

};



TEST_F(RelPoseFilterTest_81, FilterInlierNum_NoPairs_81) {

    int min_inlier_num = 5;

    RelPoseFilter::FilterInlierNum(view_graph, min_inlier_num);

    EXPECT_TRUE(view_graph.image_pairs.empty());

}



TEST_F(RelPoseFilterTest_81, FilterInlierNum_AllValid_81) {

    ImagePair pair1(1, 2);

    pair1.inliers = {1, 2, 3, 4, 5};

    ImagePair pair2(3, 4);

    pair2.inliers = {1, 2, 3, 4, 5, 6};



    view_graph.image_pairs[pair1.pair_id] = pair1;

    view_graph.image_pairs[pair2.pair_id] = pair2;



    int min_inlier_num = 5;

    RelPoseFilter::FilterInlierNum(view_graph, min_inlier_num);



    EXPECT_EQ(view_graph.image_pairs.size(), 2);

    EXPECT_TRUE(view_graph.image_pairs[pair1.pair_id].is_valid);

    EXPECT_TRUE(view_graph.image_pairs[pair2.pair_id].is_valid);

}



TEST_F(RelPoseFilterTest_81, FilterInlierNum_SomeInvalid_81) {

    ImagePair pair1(1, 2);

    pair1.inliers = {1, 2, 3};

    ImagePair pair2(3, 4);

    pair2.inliers = {1, 2, 3, 4, 5};



    view_graph.image_pairs[pair1.pair_id] = pair1;

    view_graph.image_pairs[pair2.pair_id] = pair2;



    int min_inlier_num = 4;

    RelPoseFilter::FilterInlierNum(view_graph, min_inlier_num);



    EXPECT_EQ(view_graph.image_pairs.size(), 2);

    EXPECT_FALSE(view_graph.image_pairs[pair1.pair_id].is_valid);

    EXPECT_TRUE(view_graph.image_pairs[pair2.pair_id].is_valid);

}



TEST_F(RelPoseFilterTest_81, FilterInlierNum_AllInvalid_81) {

    ImagePair pair1(1, 2);

    pair1.inliers = {1, 2};

    ImagePair pair2(3, 4);

    pair2.inliers = {1, 2};



    view_graph.image_pairs[pair1.pair_id] = pair1;

    view_graph.image_pairs[pair2.pair_id] = pair2;



    int min_inlier_num = 3;

    RelPoseFilter::FilterInlierNum(view_graph, min_inlier_num);



    EXPECT_EQ(view_graph.image_pairs.size(), 2);

    EXPECT_FALSE(view_graph.image_pairs[pair1.pair_id].is_valid);

    EXPECT_FALSE(view_graph.image_pairs[pair2.pair_id].is_valid);

}



TEST_F(RelPoseFilterTest_81, FilterInlierNum_BoundaryCondition_81) {

    ImagePair pair1(1, 2);

    pair1.inliers = {1, 2, 3};

    ImagePair pair2(3, 4);

    pair2.inliers = {1, 2, 3};



    view_graph.image_pairs[pair1.pair_id] = pair1;

    view_graph.image_pairs[pair2.pair_id] = pair2;



    int min_inlier_num = 3;

    RelPoseFilter::FilterInlierNum(view_graph, min_inlier_num);



    EXPECT_EQ(view_graph.image_pairs.size(), 2);

    EXPECT_TRUE(view_graph.image_pairs[pair1.pair_id].is_valid);

    EXPECT_TRUE(view_graph.image_pairs[pair2.pair_id].is_valid);

}



TEST_F(RelPoseFilterTest_81, FilterInlierNum_MinInliersZero_81) {

    ImagePair pair1(1, 2);

    pair1.inliers = {};

    ImagePair pair2(3, 4);

    pair2.inliers = {1};



    view_graph.image_pairs[pair1.pair_id] = pair1;

    view_graph.image_pairs[pair2.pair_id] = pair2;



    int min_inlier_num = 0;

    RelPoseFilter::FilterInlierNum(view_graph, min_inlier_num);



    EXPECT_EQ(view_graph.image_pairs.size(), 2);

    EXPECT_TRUE(view_graph.image_pairs[pair1.pair_id].is_valid);

    EXPECT_TRUE(view_graph.image_pairs[pair2.pair_id].is_valid);

}



TEST_F(RelPoseFilterTest_81, FilterInlierNum_NegativeMinInliers_81) {

    ImagePair pair1(1, 2);

    pair1.inliers = {1, 2};

    ImagePair pair2(3, 4);

    pair2.inliers = {};



    view_graph.image_pairs[pair1.pair_id] = pair1;

    view_graph.image_pairs[pair2.pair_id] = pair2;



    int min_inlier_num = -1;

    RelPoseFilter::FilterInlierNum(view_graph, min_inlier_num);



    EXPECT_EQ(view_graph.image_pairs.size(), 2);

    EXPECT_TRUE(view_graph.image_pairs[pair1.pair_id].is_valid);

    EXPECT_TRUE(view_graph.image_pairs[pair2.pair_id].is_valid);

}
