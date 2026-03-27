#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Page.h"



class PageMock : public Page {

public:

    MOCK_CONST_METHOD0(getRotate, int());

    MOCK_CONST_METHOD0(getCropWidth, double());

    MOCK_CONST_METHOD0(getCropHeight, double());



    PageMock(PDFDoc *docA, int numA, Object &&pageDict, Ref pageRefA, std::unique_ptr<PageAttrs> attrsA)

        : Page(docA, numA, std::move(pageDict), pageRefA, std::move(attrsA)) {}

};



class PopplerPageTest_2458 : public ::testing::Test {

protected:

    PDFDoc *doc = nullptr;

    int pageNum = 1;

    Object pageDict;

    Ref pageRef;

    std::unique_ptr<PageAttrs> attrs = std::make_unique<PageAttrs>();

    PageMock page{doc, pageNum, std::move(pageDict), pageRef, std::move(attrs)};



    void SetUp() override {

        // Default setup for all tests

        EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(0));

        EXPECT_CALL(page, getCropWidth()).WillRepeatedly(testing::Return(100.0));

        EXPECT_CALL(page, getCropHeight()).WillRepeatedly(testing::Return(200.0));

    }

};



TEST_F(PopplerPageTest_2458, NoRotation_NoChange_2458) {

    double x = 10.0;

    double y = 20.0;

    _page_unrotate_xy(&page, &x, &y);

    EXPECT_EQ(x, 10.0);

    EXPECT_EQ(y, 20.0);

}



TEST_F(PopplerPageTest_2458, Rotation90_CorrectChange_2458) {

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(90));

    double x = 10.0;

    double y = 20.0;

    _page_unrotate_xy(&page, &x, &y);

    EXPECT_EQ(x, 180.0);

    EXPECT_EQ(y, 10.0);

}



TEST_F(PopplerPageTest_2458, Rotation180_CorrectChange_2458) {

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(180));

    double x = 10.0;

    double y = 20.0;

    _page_unrotate_xy(&page, &x, &y);

    EXPECT_EQ(x, 90.0);

    EXPECT_EQ(y, 180.0);

}



TEST_F(PopplerPageTest_2458, Rotation270_CorrectChange_2458) {

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(270));

    double x = 10.0;

    double y = 20.0;

    _page_unrotate_xy(&page, &x, &y);

    EXPECT_EQ(x, 20.0);

    EXPECT_EQ(y, 90.0);

}



TEST_F(PopplerPageTest_2458, BoundaryConditions_2458) {

    // Test boundary conditions for x and y

    double x = 0.0;

    double y = 0.0;

    _page_unrotate_xy(&page, &x, &y);

    EXPECT_EQ(x, 0.0);

    EXPECT_EQ(y, 0.0);



    x = 100.0;

    y = 200.0;

    _page_unrotate_xy(&page, &x, &y);

    EXPECT_EQ(x, 100.0);

    EXPECT_EQ(y, 200.0);

}



TEST_F(PopplerPageTest_2458, Rotation90_BoundaryConditions_2458) {

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(90));

    double x = 100.0;

    double y = 0.0;

    _page_unrotate_xy(&page, &x, &y);

    EXPECT_EQ(x, 200.0);

    EXPECT_EQ(y, 100.0);



    x = 0.0;

    y = 200.0;

    _page_unrotate_xy(&page, &x, &y);

    EXPECT_EQ(x, 0.0);

    EXPECT_EQ(y, 0.0);

}



TEST_F(PopplerPageTest_2458, Rotation180_BoundaryConditions_2458) {

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(180));

    double x = 100.0;

    double y = 0.0;

    _page_unrotate_xy(&page, &x, &y);

    EXPECT_EQ(x, 0.0);

    EXPECT_EQ(y, 200.0);



    x = 0.0;

    y = 200.0;

    _page_unrotate_xy(&page, &x, &y);

    EXPECT_EQ(x, 100.0);

    EXPECT_EQ(y, 0.0);

}



TEST_F(PopplerPageTest_2458, Rotation270_BoundaryConditions_2458) {

    EXPECT_CALL(page, getRotate()).WillRepeatedly(testing::Return(270));

    double x = 100.0;

    double y = 0.0;

    _page_unrotate_xy(&page, &x, &y);

    EXPECT_EQ(x, 0.0);

    EXPECT_EQ(y, 100.0);



    x = 0.0;

    y = 200.0;

    _page_unrotate_xy(&page, &x, &y);

    EXPECT_EQ(x, 200.0);

    EXPECT_EQ(y, 0.0);

}
