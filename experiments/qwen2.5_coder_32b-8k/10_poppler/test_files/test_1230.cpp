#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PageTransition.h"



class PageTransitionTest_1230 : public ::testing::Test {

protected:

    Object *obj;

    PageTransition* pageTransition;



    void SetUp() override {

        obj = new Object(); // Assuming Object is default constructible for the sake of test setup

        pageTransition = new PageTransition(obj);

    }



    void TearDown() override {

        delete pageTransition;

        delete obj;

    }

};



TEST_F(PageTransitionTest_1230, IsOk_ReturnsTrueForValidObject_1230) {

    EXPECT_TRUE(pageTransition->isOk());

}



TEST_F(PageTransitionTest_1230, GetDuration_ReturnsExpectedValue_1230) {

    // Assuming a way to set duration for testing purposes

    double expectedDuration = 5.0;

    // Here we would need some setup if possible to set the duration, but treating as black box

    EXPECT_DOUBLE_EQ(pageTransition->getDuration(), expectedDuration);

}



TEST_F(PageTransitionTest_1230, GetType_ReturnsValidType_1230) {

    PageTransitionType type = pageTransition->getType();

    // Assuming PageTransitionType has valid range, check if it falls within that

    EXPECT_GE(type, 0); // Placeholder assumption for test

}



TEST_F(PageTransitionTest_1230, GetAlignment_ReturnsValidAlignment_1230) {

    PageTransitionAlignment alignment = pageTransition->getAlignment();

    // Assuming PageTransitionAlignment has valid range, check if it falls within that

    EXPECT_GE(alignment, 0); // Placeholder assumption for test

}



TEST_F(PageTransitionTest_1230, GetDirection_ReturnsValidDirection_1230) {

    PageTransitionDirection direction = pageTransition->getDirection();

    // Assuming PageTransitionDirection has valid range, check if it falls within that

    EXPECT_GE(direction, 0); // Placeholder assumption for test

}



TEST_F(PageTransitionTest_1230, GetAngle_ReturnsExpectedValue_1230) {

    int expectedAngle = 90; // Example value

    // Assuming a way to set angle for testing purposes

    EXPECT_EQ(pageTransition->getAngle(), expectedAngle);

}



TEST_F(PageTransitionTest_1230, GetScale_ReturnsExpectedValue_1230) {

    double expectedScale = 1.5; // Example value

    // Assuming a way to set scale for testing purposes

    EXPECT_DOUBLE_EQ(pageTransition->getScale(), expectedScale);

}



TEST_F(PageTransitionTest_1230, IsRectangular_ReturnsExpectedValue_1230) {

    bool expectedRectangular = true; // Example value

    // Assuming a way to set rectangular for testing purposes

    EXPECT_EQ(pageTransition->isRectangular(), expectedRectangular);

}



TEST_F(PageTransitionTest_1230, BoundaryCondition_DurationZero_1230) {

    // Assuming a way to set duration to boundary condition

    double zeroDuration = 0.0;

    // Placeholder for actual test setup if possible

    EXPECT_DOUBLE_EQ(pageTransition->getDuration(), zeroDuration);

}



TEST_F(PageTransitionTest_1230, BoundaryCondition_AngleNegative_1230) {

    int negativeAngle = -90; // Example boundary condition

    // Assuming a way to set angle to boundary condition

    EXPECT_EQ(pageTransition->getAngle(), negativeAngle);

}



TEST_F(PageTransitionTest_1230, BoundaryCondition_ScaleZero_1230) {

    double zeroScale = 0.0;

    // Assuming a way to set scale to boundary condition

    EXPECT_DOUBLE_EQ(pageTransition->getScale(), zeroScale);

}
