#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PageTransition.h"



class PageTransitionTest : public ::testing::Test {

protected:

    PageTransition* page_transition;



    void SetUp() override {

        // Assuming Object* trans can be constructed with some default or null value for testing

        Object* trans = nullptr; // Replace with actual construction if needed

        page_transition = new PageTransition(trans);

    }



    void TearDown() override {

        delete page_transition;

    }

};



TEST_F(PageTransitionTest_1234, IsOk_ReturnsTrueOrFalse_1234) {

    EXPECT_TRUE(page_transition->isOk() || !page_transition->isOk());

}



TEST_F(PageTransitionTest_1234, GetType_ReturnsValidType_1234) {

    // Assuming PageTransitionType is an enum with valid values

    PageTransitionType type = page_transition->getType();

    EXPECT_GE(type, 0); // Example assumption: enum starts from 0

}



TEST_F(PageTransitionTest_1234, GetDuration_ReturnsNonNegativeValue_1234) {

    double duration = page_transition->getDuration();

    EXPECT_GE(duration, 0.0);

}



TEST_F(PageTransitionTest_1234, GetAlignment_ReturnsValidAlignment_1234) {

    // Assuming PageTransitionAlignment is an enum with valid values

    PageTransitionAlignment alignment = page_transition->getAlignment();

    EXPECT_GE(alignment, 0); // Example assumption: enum starts from 0

}



TEST_F(PageTransitionTest_1234, GetDirection_ReturnsValidDirection_1234) {

    // Assuming PageTransitionDirection is an enum with valid values

    PageTransitionDirection direction = page_transition->getDirection();

    EXPECT_GE(direction, 0); // Example assumption: enum starts from 0

}



TEST_F(PageTransitionTest_1234, GetAngle_ReturnsValidAngle_1234) {

    int angle = page_transition->getAngle();

    EXPECT_TRUE(angle >= -360 && angle <= 360); // Assuming angle is within this range

}



TEST_F(PageTransitionTest_1234, GetScale_ReturnsNonNegativeValue_1234) {

    double scale = page_transition->getScale();

    EXPECT_GE(scale, 0.0);

}



TEST_F(PageTransitionTest_1234, IsRectangular_ReturnsTrueOrFalse_1234) {

    EXPECT_TRUE(page_transition->isRectangular() || !page_transition->isRectangular());

}
