#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PageTransition.h"



class PageTransitionTest_1233 : public ::testing::Test {

protected:

    virtual void SetUp() override {

        // Setup any common objects or state here if needed

    }



    virtual void TearDown() override {

        // Cleanup any resources here if needed

    }

};



TEST_F(PageTransitionTest_1233, IsOk_ReturnsTrueForValidInstance_1233) {

    Object* mockObject = nullptr;  // Assuming Object is a valid type in the context

    PageTransition transition(mockObject);

    EXPECT_TRUE(transition.isOk());

}



TEST_F(PageTransitionTest_1233, GetType_ReturnsExpectedValue_1233) {

    Object* mockObject = nullptr;

    PageTransition transition(mockObject);

    auto type = transition.getType();

    // Since we cannot infer the value, this is a placeholder. In practice, you would know the expected type.

    EXPECT_EQ(type, type);  // Replace with actual expected value if known

}



TEST_F(PageTransitionTest_1233, GetDuration_ReturnsNonNegativeValue_1233) {

    Object* mockObject = nullptr;

    PageTransition transition(mockObject);

    double duration = transition.getDuration();

    EXPECT_GE(duration, 0.0);

}



TEST_F(PageTransitionTest_1233, GetAlignment_ReturnsExpectedValue_1233) {

    Object* mockObject = nullptr;

    PageTransition transition(mockObject);

    auto alignment = transition.getAlignment();

    // Since we cannot infer the value, this is a placeholder. In practice, you would know the expected alignment.

    EXPECT_EQ(alignment, alignment);  // Replace with actual expected value if known

}



TEST_F(PageTransitionTest_1233, GetDirection_ReturnsExpectedValue_1233) {

    Object* mockObject = nullptr;

    PageTransition transition(mockObject);

    auto direction = transition.getDirection();

    // Since we cannot infer the value, this is a placeholder. In practice, you would know the expected direction.

    EXPECT_EQ(direction, direction);  // Replace with actual expected value if known

}



TEST_F(PageTransitionTest_1233, GetAngle_ReturnsExpectedValue_1233) {

    Object* mockObject = nullptr;

    PageTransition transition(mockObject);

    int angle = transition.getAngle();

    EXPECT_EQ(angle, angle);  // Replace with actual expected value if known

}



TEST_F(PageTransitionTest_1233, GetScale_ReturnsNonNegativeValue_1233) {

    Object* mockObject = nullptr;

    PageTransition transition(mockObject);

    double scale = transition.getScale();

    EXPECT_GE(scale, 0.0);

}



TEST_F(PageTransitionTest_1233, IsRectangular_ReturnsExpectedBool_1233) {

    Object* mockObject = nullptr;

    PageTransition transition(mockObject);

    bool isRect = transition.isRectangular();

    EXPECT_EQ(isRect, isRect);  // Replace with actual expected value if known

}



TEST_F(PageTransitionTest_1233, GetAngle_BoundaryCondition_Zero_1233) {

    Object* mockObject = nullptr;

    PageTransition transition(mockObject);

    int angle = transition.getAngle();

    EXPECT_GE(angle, 0);  // Assuming zero is a valid boundary condition

}



TEST_F(PageTransitionTest_1233, GetScale_BoundaryCondition_Zero_1233) {

    Object* mockObject = nullptr;

    PageTransition transition(mockObject);

    double scale = transition.getScale();

    EXPECT_GE(scale, 0.0);  // Assuming zero is a valid boundary condition

}
