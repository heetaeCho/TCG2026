#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Page.h"



class PageMock : public Page {

public:

    MOCK_METHOD(int, getRotate, (), (const));

    MOCK_METHOD(double, getCropWidth, (), (const));

    MOCK_METHOD(double, getCropHeight, (), (const));



    using Page::Page;

};



class PageRotationTest_2457 : public ::testing::Test {

protected:

    std::unique_ptr<PageMock> page;



    void SetUp() override {

        page = std::make_unique<PageMock>();

    }

};



TEST_F(PageRotationTest_2457, NoRotation_NoChange_2457) {

    EXPECT_CALL(*page, getRotate()).WillOnce(::testing::Return(0));

    double x = 1.0;

    double y = 1.0;

    _page_rotate_xy(page.get(), &x, &y);

    EXPECT_EQ(x, 1.0);

    EXPECT_EQ(y, 1.0);

}



TEST_F(PageRotationTest_2457, Rotation90_DimensionsSwappedAndYInverted_2457) {

    EXPECT_CALL(*page, getRotate()).WillOnce(::testing::Return(90));

    EXPECT_CALL(*page, getCropWidth()).WillOnce(::testing::Return(10.0));

    EXPECT_CALL(*page, getCropHeight()).WillOnce(::testing::Return(20.0));



    double x = 5.0;

    double y = 8.0;

    _page_rotate_xy(page.get(), &x, &y);

    EXPECT_EQ(x, 12.0); // y (8) inverted in new width (20)

    EXPECT_EQ(y, 5.0); // x (5) swapped with y

}



TEST_F(PageRotationTest_2457, Rotation180_XYInverted_2457) {

    EXPECT_CALL(*page, getRotate()).WillOnce(::testing::Return(180));

    EXPECT_CALL(*page, getCropWidth()).WillOnce(::testing::Return(10.0));

    EXPECT_CALL(*page, getCropHeight()).WillOnce(::testing::Return(20.0));



    double x = 5.0;

    double y = 8.0;

    _page_rotate_xy(page.get(), &x, &y);

    EXPECT_EQ(x, 5.0); // x (5) inverted in width (10)

    EXPECT_EQ(y, 12.0); // y (8) inverted in height (20)

}



TEST_F(PageRotationTest_2457, Rotation270_DimensionsSwappedAndXInverted_2457) {

    EXPECT_CALL(*page, getRotate()).WillOnce(::testing::Return(270));

    EXPECT_CALL(*page, getCropWidth()).WillOnce(::testing::Return(10.0));

    EXPECT_CALL(*page, getCropHeight()).WillOnce(::testing::Return(20.0));



    double x = 5.0;

    double y = 8.0;

    _page_rotate_xy(page.get(), &x, &y);

    EXPECT_EQ(x, 15.0); // width (10) - y (5)

    EXPECT_EQ(y, 5.0); // x (5) swapped with y

}



TEST_F(PageRotationTest_2457, BoundaryCondition_Rotation90_ZeroXZeroY_2457) {

    EXPECT_CALL(*page, getRotate()).WillOnce(::testing::Return(90));

    EXPECT_CALL(*page, getCropWidth()).WillOnce(::testing::Return(10.0));

    EXPECT_CALL(*page, getCropHeight()).WillOnce(::testing::Return(20.0));



    double x = 0.0;

    double y = 0.0;

    _page_rotate_xy(page.get(), &x, &y);

    EXPECT_EQ(x, 20.0); // height (20) - y (0)

    EXPECT_EQ(y, 0.0); // x (0) swapped with y

}



TEST_F(PageRotationTest_2457, BoundaryCondition_Rotation180_ZeroXZeroY_2457) {

    EXPECT_CALL(*page, getRotate()).WillOnce(::testing::Return(180));

    EXPECT_CALL(*page, getCropWidth()).WillOnce(::testing::Return(10.0));

    EXPECT_CALL(*page, getCropHeight()).WillOnce(::testing::Return(20.0));



    double x = 0.0;

    double y = 0.0;

    _page_rotate_xy(page.get(), &x, &y);

    EXPECT_EQ(x, 10.0); // width (10) - x (0)

    EXPECT_EQ(y, 20.0); // height (20) - y (0)

}



TEST_F(PageRotationTest_2457, BoundaryCondition_Rotation270_ZeroXZeroY_2457) {

    EXPECT_CALL(*page, getRotate()).WillOnce(::testing::Return(270));

    EXPECT_CALL(*page, getCropWidth()).WillOnce(::testing::Return(10.0));

    EXPECT_CALL(*page, getCropHeight()).WillOnce(::testing::Return(20.0));



    double x = 0.0;

    double y = 0.0;

    _page_rotate_xy(page.get(), &x, &y);

    EXPECT_EQ(x, 10.0); // width (10) - y (0)

    EXPECT_EQ(y, 0.0); // x (0) swapped with y

}
