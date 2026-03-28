#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/ninja/src/graph.h"

#include "./TestProjects/ninja/src/state.h"



using ::testing::NiceMock;

using ::testing::Return;



class EdgeMock : public Edge {

public:

    MOCK_CONST_METHOD0(weight, int());

    MOCK_CONST_METHOD0(rule, const Rule&());

    MOCK_CONST_METHOD0(pool, Pool*());

};



TEST_F(WeightedEdgeCmpTest_79, CompareDifferentWeights_79) {

    EdgeMock edge1;

    EdgeMock edge2;



    EXPECT_CALL(edge1, weight()).WillOnce(Return(5));

    EXPECT_CALL(edge2, weight()).WillOnce(Return(10));



    WeightedEdgeCmp cmp;

    ASSERT_TRUE(cmp(&edge1, &edge2));

}



TEST_F(WeightedEdgeCmpTest_79, CompareSameWeightsDifferentEdges_79) {

    EdgeMock edge1;

    EdgeMock edge2;



    EXPECT_CALL(edge1, weight()).WillOnce(Return(5));

    EXPECT_CALL(edge2, weight()).WillOnce(Return(5));



    WeightedEdgeCmp cmp;

    ASSERT_FALSE(cmp(&edge1, &edge2));  // Assuming EdgePriorityGreater returns false for same priority

}



TEST_F(WeightedEdgeCmpTest_79, CompareNullEdges_79) {

    EdgeMock edge;



    WeightedEdgeCmp cmp;

    ASSERT_TRUE(cmp(nullptr, &edge));

    ASSERT_FALSE(cmp(&edge, nullptr));

}



TEST_F(WeightedEdgeCmpTest_79, CompareSameEdge_79) {

    EdgeMock edge;



    WeightedEdgeCmp cmp;

    ASSERT_FALSE(cmp(&edge, &edge));

}
