#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Annot.h"



using namespace testing;



class AnnotBorderMock : public AnnotBorder {

public:

    MOCK_METHOD(void, setWidth, (double new_width), (override));

    MOCK_CONST_METHOD0(getWidth, double());

};



TEST_F(AnnotBorderTest_746, SetWidth_NormalOperation_746) {

    AnnotBorder annotBorder;

    EXPECT_NO_THROW(annotBorder.setWidth(1.5));

}



TEST_F(AnnotBorderTest_746, GetWidth_AfterSetWidth_746) {

    AnnotBorder annotBorder;

    annotBorder.setWidth(2.0);

    EXPECT_DOUBLE_EQ(annotBorder.getWidth(), 2.0);

}



TEST_F(AnnotBorderTest_746, SetWidth_BoundaryCondition_Zero_746) {

    AnnotBorder annotBorder;

    EXPECT_NO_THROW(annotBorder.setWidth(0.0));

}



TEST_F(AnnotBorderTest_746, GetWidth_AfterSetWidth_Zero_746) {

    AnnotBorder annotBorder;

    annotBorder.setWidth(0.0);

    EXPECT_DOUBLE_EQ(annotBorder.getWidth(), 0.0);

}



TEST_F(AnnotBorderTest_746, SetWidth_BoundaryCondition_Negative_746) {

    AnnotBorder annotBorder;

    EXPECT_NO_THROW(annotBorder.setWidth(-1.5));

}



TEST_F(AnnotBorderTest_746, GetWidth_AfterSetWidth_Negative_746) {

    AnnotBorder annotBorder;

    annotBorder.setWidth(-1.5);

    EXPECT_DOUBLE_EQ(annotBorder.getWidth(), -1.5);

}
