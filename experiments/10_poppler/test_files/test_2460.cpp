#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Page.h"

#include "poppler/Annot.h"



using namespace testing;



// Mock classes for dependencies

class MockPage : public Page {

public:

    MOCK_CONST_METHOD0(getRotate, int());

};



class MockAnnot : public Annot {

public:

    MOCK_CONST_METHOD0(getFlags, unsigned int());

};



// Test fixture

class UnrotateRectForAnnotAndPageTest : public ::testing::Test {

protected:

    MockPage mock_page;

    MockAnnot mock_annot;



    double x1 = 0.0;

    double y1 = 0.0;

    double x2 = 100.0;

    double y2 = 100.0;



    void SetUp() override {

        // Default setup for tests

        EXPECT_CALL(mock_page, getRotate()).WillRepeatedly(Return(0)); // No rotation by default

        EXPECT_CALL(mock_annot, getFlags()).WillRepeatedly(Return(0)); // No special flags by default

    }

};



// Test cases



TEST_F(UnrotateRectForAnnotAndPageTest, NormalOperation_NoRotation_2460) {

    _unrotate_rect_for_annot_and_page(&mock_page, &mock_annot, &x1, &y1, &x2, &y2);

    EXPECT_EQ(x1, 0.0);

    EXPECT_EQ(y1, 0.0);

    EXPECT_EQ(x2, 100.0);

    EXPECT_EQ(y2, 100.0);

}



TEST_F(UnrotateRectForAnnotAndPageTest, NormalOperation_WithRotation_FlagNoRotate_2460) {

    EXPECT_CALL(mock_page, getRotate()).WillRepeatedly(Return(90)); // Rotate by 90 degrees

    EXPECT_CALL(mock_annot, getFlags()).WillRepeatedly(Return(Annot::flagNoRotate));



    _unrotate_rect_for_annot_and_page(&mock_page, &mock_annot, &x1, &y1, &x2, &y2);

    EXPECT_EQ(x1, 0.0);

    EXPECT_EQ(y1, -100.0);

    EXPECT_EQ(x2, 100.0);

    EXPECT_EQ(y2, 0.0);

}



TEST_F(UnrotateRectForAnnotAndPageTest, BoundaryConditions_RectNotNormalized_2460) {

    x1 = 100.0;

    y1 = 100.0;

    x2 = 0.0;

    y2 = 0.0;



    _unrotate_rect_for_annot_and_page(&mock_page, &mock_annot, &x1, &y1, &x2, &y2);

    EXPECT_EQ(x1, 0.0);

    EXPECT_EQ(y1, 100.0);

    EXPECT_EQ(x2, 100.0);

    EXPECT_EQ(y2, 0.0);

}



TEST_F(UnrotateRectForAnnotAndPageTest, BoundaryConditions_ZeroSizedRectangle_2460) {

    x1 = 50.0;

    y1 = 50.0;

    x2 = 50.0;

    y2 = 50.0;



    _unrotate_rect_for_annot_and_page(&mock_page, &mock_annot, &x1, &y1, &x2, &y2);

    EXPECT_EQ(x1, 50.0);

    EXPECT_EQ(y1, 50.0);

    EXPECT_EQ(x2, 50.0);

    EXPECT_EQ(y2, 50.0);

}



TEST_F(UnrotateRectForAnnotAndPageTest, ExceptionalCase_UnsupportedRotation_2460) {

    EXPECT_CALL(mock_page, getRotate()).WillRepeatedly(Return(30)); // Unsupported rotation



    _unrotate_rect_for_annot_and_page(&mock_page, &mock_annot, &x1, &y1, &x2, &y2);

    EXPECT_EQ(x1, 0.0);

    EXPECT_EQ(y1, 0.0);

    EXPECT_EQ(x2, 100.0);

    EXPECT_EQ(y2, 100.0);

}
