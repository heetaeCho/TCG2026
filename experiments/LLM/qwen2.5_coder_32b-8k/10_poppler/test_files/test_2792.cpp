#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include "HtmlOutputDev.cc"



using namespace testing;



class MockGfxState : public GfxState {

public:

    MOCK_METHOD(void, transform, (double x1, double y1, double *x2, double *y2), (const, override));

};



TEST(HtmlImageTest_2792, ConstructWithValidFileNameAndState_2792) {

    MockGfxState mockState;

    EXPECT_CALL(mockState, transform(0, 0, _, _)).Times(1);

    EXPECT_CALL(mockState, transform(1, 1, _, _)).Times(1);



    HtmlImage image("test_image.png", &mockState);

    EXPECT_EQ(image.fName, "test_image.png");

}



TEST(HtmlImageTest_2792, TransformCalledWithCorrectArguments_2792) {

    MockGfxState mockState;

    double xMin, yMax, xMax, yMin;

    EXPECT_CALL(mockState, transform(0, 0, Pointee(DoubleEq(0.0)), Pointee(DoubleEq(1.0)))).WillOnce(DoAll(SetArgReferee<2>(xMin), SetArgReferee<3>(yMax)));

    EXPECT_CALL(mockState, transform(1, 1, Pointee(DoubleEq(1.0)), Pointee(DoubleEq(0.0)))).WillOnce(DoAll(SetArgReferee<2>(xMax), SetArgReferee<3>(yMin)));



    HtmlImage image("test_image.png", &mockState);

}



TEST(HtmlImageTest_2792, DeletedCopyConstructor_2792) {

    MockGfxState mockState;

    HtmlImage original("original_image.png", &mockState);



    EXPECT_DEATH(HtmlImage copy = original;, "");

}



TEST(HtmlImageTest_2792, DeletedCopyAssignmentOperator_2792) {

    MockGfxState mockState;

    HtmlImage original("original_image.png", &mockState);

    HtmlImage other("other_image.png", &mockState);



    EXPECT_DEATH(other = original;, "");

}
