#include <gtest/gtest.h>

#include "PageTransition.h"



// Assuming Object is defined somewhere in the codebase

class Object {

    // Mock class for Object since it's not provided in the snippet

};



TEST(PageTransitionTest_1235, IsRectangular_ReturnsTrue_1235) {

    Object obj;  // Mock object to pass to PageTransition constructor

    PageTransition transition(&obj);

    

    EXPECT_TRUE(transition.isRectangular());

}



TEST(PageTransitionTest_1235, IsRectangular_ReturnsFalse_1235) {

    Object obj;  // Mock object to pass to PageTransition constructor

    PageTransition transition(&obj);

    

    EXPECT_FALSE(transition.isRectangular());

}



TEST(PageTransitionTest_1235, IsOk_NormalCase_1235) {

    Object obj;  // Mock object to pass to PageTransition constructor

    PageTransition transition(&obj);

    

    EXPECT_TRUE(transition.isOk());  // Assuming normal case should return true

}



TEST(PageTransitionTest_1235, GetType_ReturnsExpectedType_1235) {

    Object obj;  // Mock object to pass to PageTransition constructor

    PageTransition transition(&obj);

    

    EXPECT_EQ(transition.getType(), static_cast<PageTransitionType>(0));  // Assuming default type is 0

}



TEST(PageTransitionTest_1235, GetDuration_ReturnsExpectedValue_1235) {

    Object obj;  // Mock object to pass to PageTransition constructor

    PageTransition transition(&obj);

    

    EXPECT_DOUBLE_EQ(transition.getDuration(), 1.0);  // Assuming default duration is 1.0

}



TEST(PageTransitionTest_1235, GetAlignment_ReturnsExpectedAlignment_1235) {

    Object obj;  // Mock object to pass to PageTransition constructor

    PageTransition transition(&obj);

    

    EXPECT_EQ(transition.getAlignment(), static_cast<PageTransitionAlignment>(0));  // Assuming default alignment is 0

}



TEST(PageTransitionTest_1235, GetDirection_ReturnsExpectedDirection_1235) {

    Object obj;  // Mock object to pass to PageTransition constructor

    PageTransition transition(&obj);

    

    EXPECT_EQ(transition.getDirection(), static_cast<PageTransitionDirection>(0));  // Assuming default direction is 0

}



TEST(PageTransitionTest_1235, GetAngle_ReturnsExpectedValue_1235) {

    Object obj;  // Mock object to pass to PageTransition constructor

    PageTransition transition(&obj);

    

    EXPECT_EQ(transition.getAngle(), 0);  // Assuming default angle is 0

}



TEST(PageTransitionTest_1235, GetScale_ReturnsExpectedValue_1235) {

    Object obj;  // Mock object to pass to PageTransition constructor

    PageTransition transition(&obj);

    

    EXPECT_DOUBLE_EQ(transition.getScale(), 1.0);  // Assuming default scale is 1.0

}



TEST(PageTransitionTest_1235, IsOk_ErrorCase_1235) {

    Object obj;  // Mock object to pass to PageTransition constructor

    PageTransition transition(&obj);

    

    EXPECT_FALSE(transition.isOk());  // Assuming error case should return false

}
