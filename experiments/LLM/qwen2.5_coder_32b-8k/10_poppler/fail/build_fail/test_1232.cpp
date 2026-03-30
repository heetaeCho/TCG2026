#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PageTransition.h"



class PageTransitionTest_1232 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Assuming Object* trans can be created and passed here for testing.

        // Since the internal logic is unknown, we cannot create a valid Object*.

        // For the sake of this example, we will assume a mock or dummy object creation.

        Object* trans = nullptr; // This should be replaced with actual object creation if possible.

        pageTransition = std::make_unique<PageTransition>(trans);

    }



    virtual void TearDown() {

        pageTransition.reset();

    }



    std::unique_ptr<PageTransition> pageTransition;

};



TEST_F(PageTransitionTest_1232, IsOk_ReturnsTrue_1232) {

    EXPECT_TRUE(pageTransition->isOk());

}



TEST_F(PageTransitionTest_1232, GetType_ReturnsDefaultType_1232) {

    PageTransitionType type = pageTransition->getType();

    // Assuming default value is PageTransitionType::None or similar

    EXPECT_EQ(type, PageTransitionType::None);

}



TEST_F(PageTransitionTest_1232, GetDuration_ReturnsDefaultDuration_1232) {

    double duration = pageTransition->getDuration();

    // Assuming default value is 0.0 or similar

    EXPECT_DOUBLE_EQ(duration, 0.0);

}



TEST_F(PageTransitionTest_1232, GetAlignment_ReturnsDefaultAlignment_1232) {

    PageTransitionAlignment alignment = pageTransition->getAlignment();

    // Assuming default value is PageTransitionAlignment::H or similar

    EXPECT_EQ(alignment, PageTransitionAlignment::H);

}



TEST_F(PageTransitionTest_1232, GetDirection_ReturnsDefaultDirection_1232) {

    PageTransitionDirection direction = pageTransition->getDirection();

    // Assuming default value is PageTransitionDirection::L or similar

    EXPECT_EQ(direction, PageTransitionDirection::L);

}



TEST_F(PageTransitionTest_1232, GetAngle_ReturnsDefaultAngle_1232) {

    int angle = pageTransition->getAngle();

    // Assuming default value is 0 or similar

    EXPECT_EQ(angle, 0);

}



TEST_F(PageTransitionTest_1232, GetScale_ReturnsDefaultScale_1232) {

    double scale = pageTransition->getScale();

    // Assuming default value is 1.0 or similar

    EXPECT_DOUBLE_EQ(scale, 1.0);

}



TEST_F(PageTransitionTest_1232, IsRectangular_ReturnsDefaultBoolean_1232) {

    bool rectangular = pageTransition->isRectangular();

    // Assuming default value is false or similar

    EXPECT_FALSE(rectangular);

}
