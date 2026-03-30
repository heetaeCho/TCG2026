#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/processors/relpose_filter.h"

#include "glomap/scene/view_graph.h"

#include "glomap/scene/image_pair.h"



namespace glomap {

using ::testing::ElementsAre;



class RelPoseFilterTest_82 : public ::testing::Test {

protected:

    ViewGraph view_graph;

    ImagePair image_pair1, image_pair2, image_pair3;



    void SetUp() override {

        image_pair1.image_id1 = 1;

        image_pair1.image_id2 = 2;

        image_pair1.pair_id = 101;

        image_pair1.matches.resize(10);

        image_pair1.inliers = {1, 2, 3, 4};



        image_pair2.image_id1 = 3;

        image_pair2.image_id2 = 4;

        image_pair2.pair_id = 102;

        image_pair2.matches.resize(15);

        image_pair2.inliers = {1, 2, 3, 4, 5};



        image_pair3.image_id1 = 5;

        image_pair3.image_id2 = 6;

        image_pair3.pair_id = 103;

        image_pair3.matches.resize(8);

        image_pair3.inliers = {1, 2};



        view_graph.image_pairs = {

            {image_pair1.pair_id, image_pair1},

            {image_pair2.pair_id, image_pair2},

            {image_pair3.pair_id, image_pair3}

        };

    }

};



TEST_F(RelPoseFilterTest_82, FilterInlierRatio_NormalOperation_82) {

    RelPoseFilter::FilterInlierRatio(view_graph, 0.3);

    EXPECT_TRUE(view_graph.image_pairs[image_pair1.pair_id].is_valid);

    EXPECT_TRUE(view_graph.image_pairs[image_pair2.pair_id].is_valid);

    EXPECT_FALSE(view_graph.image_pairs[image_pair3.pair_id].is_valid);

}



TEST_F(RelPoseFilterTest_82, FilterInlierRatio_BoundaryCondition_82) {

    RelPoseFilter::FilterInlierRatio(view_graph, 0.5);

    EXPECT_TRUE(view_graph.image_pairs[image_pair1.pair_id].is_valid);

    EXPECT_TRUE(view_graph.image_pairs[image_pair2.pair_id].is_valid);

    EXPECT_FALSE(view_graph.image_pairs[image_pair3.pair_id].is_valid);



    RelPoseFilter::FilterInlierRatio(view_graph, 0.6);

    EXPECT_TRUE(view_graph.image_pairs[image_pair1.pair_id].is_valid);

    EXPECT_TRUE(view_graph.image_pairs[image_pair2.pair_id].is_valid);

    EXPECT_FALSE(view_graph.image_pairs[image_pair3.pair_id].is_valid);



    RelPoseFilter::FilterInlierRatio(view_graph, 0.4);

    EXPECT_TRUE(view_graph.image_pairs[image_pair1.pair_id].is_valid);

    EXPECT_TRUE(view_graph.image_pairs[image_pair2.pair_id].is_valid);

    EXPECT_FALSE(view_graph.image_pairs[image_pair3.pair_id].is_valid);



    RelPoseFilter::FilterInlierRatio(view_graph, 0.25);

    EXPECT_TRUE(view_graph.image_pairs[image_pair1.pair_id].is_valid);

    EXPECT_TRUE(view_graph.image_pairs[image_pair2.pair_id].is_valid);

    EXPECT_TRUE(view_graph.image_pairs[image_pair3.pair_id].is_valid);

}



TEST_F(RelPoseFilterTest_82, FilterInlierRatio_ErrorCase_ZeroMatches_82) {

    image_pair1.matches.resize(0);

    RelPoseFilter::FilterInlierRatio(view_graph, 0.5);

    EXPECT_FALSE(view_graph.image_pairs[image_pair1.pair_id].is_valid);

}



TEST_F(RelPoseFilterTest_82, FilterInlierRatio_ErrorCase_NegativeMinInlierRatio_82) {

    EXPECT_THROW(RelPoseFilter::FilterInlierRatio(view_graph, -0.1), std::exception);

}



TEST_F(RelPoseFilterTest_82, FilterInlierRatio_ErrorCase_GreaterThanOneMinInlierRatio_82) {

    EXPECT_THROW(RelPoseFilter::FilterInlierRatio(view_graph, 1.1), std::exception);

}

} // namespace glomap
