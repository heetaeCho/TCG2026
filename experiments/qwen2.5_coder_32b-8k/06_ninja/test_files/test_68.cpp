#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



using ::testing::Return;



class EdgeMock : public Edge {

public:

    MOCK_CONST_METHOD0(critical_path_weight, int64_t());

};



TEST_F(EdgePriorityLessTest_68, NormalOperation_EqualWeightsDifferentIDs_68) {

    EdgeMock e1;

    EdgeMock e2;

    EXPECT_CALL(e1, critical_path_weight()).WillRepeatedly(Return(5));

    EXPECT_CALL(e2, critical_path_weight()).WillRepeatedly(Return(5));



    e1.id_ = 1;

    e2.id_ = 2;



    EdgePriorityLess comparator;

    EXPECT_TRUE(comparator(&e1, &e2));

}



TEST_F(EdgePriorityLessTest_68, NormalOperation_DifferentWeightsSameIDs_68) {

    EdgeMock e1;

    EdgeMock e2;

    EXPECT_CALL(e1, critical_path_weight()).WillRepeatedly(Return(3));

    EXPECT_CALL(e2, critical_path_weight()).WillRepeatedly(Return(5));



    e1.id_ = 1;

    e2.id_ = 1;



    EdgePriorityLess comparator;

    EXPECT_TRUE(comparator(&e1, &e2));

}



TEST_F(EdgePriorityLessTest_68, BoundaryCondition_SameWeightsSameIDs_68) {

    EdgeMock e1;

    EdgeMock e2;

    EXPECT_CALL(e1, critical_path_weight()).WillRepeatedly(Return(5));

    EXPECT_CALL(e2, critical_path_weight()).WillRepeatedly(Return(5));



    e1.id_ = 1;

    e2.id_ = 1;



    EdgePriorityLess comparator;

    EXPECT_FALSE(comparator(&e1, &e2));

}



TEST_F(EdgePriorityLessTest_68, BoundaryCondition_ZeroWeightsDifferentIDs_68) {

    EdgeMock e1;

    EdgeMock e2;

    EXPECT_CALL(e1, critical_path_weight()).WillRepeatedly(Return(0));

    EXPECT_CALL(e2, critical_path_weight()).WillRepeatedly(Return(0));



    e1.id_ = 1;

    e2.id_ = 2;



    EdgePriorityLess comparator;

    EXPECT_TRUE(comparator(&e1, &e2));

}



TEST_F(EdgePriorityLessTest_68, ExceptionalCase_NegativeWeightsSameIDs_68) {

    EdgeMock e1;

    EdgeMock e2;

    EXPECT_CALL(e1, critical_path_weight()).WillRepeatedly(Return(-5));

    EXPECT_CALL(e2, critical_path_weight()).WillRepeatedly(Return(-5));



    e1.id_ = 1;

    e2.id_ = 1;



    EdgePriorityLess comparator;

    EXPECT_FALSE(comparator(&e1, &e2));

}



TEST_F(EdgePriorityLessTest_68, ExceptionalCase_NegativeWeightsDifferentIDs_68) {

    EdgeMock e1;

    EdgeMock e2;

    EXPECT_CALL(e1, critical_path_weight()).WillRepeatedly(Return(-3));

    EXPECT_CALL(e2, critical_path_weight()).WillRepeatedly(Return(-5));



    e1.id_ = 1;

    e2.id_ = 2;



    EdgePriorityLess comparator;

    EXPECT_FALSE(comparator(&e1, &e2));

}
