#include <gtest/gtest.h>

#include "poppler/PageTransition.h"



class PageTransitionTest_1229 : public ::testing::Test {

protected:

    // Assuming a mock Object class or using a real one for testing purposes

    // For simplicity, let's assume we have an Object* that can be created and destroyed without issues.

    Object* obj;



    void SetUp() override {

        obj = new Object();

    }



    void TearDown() override {

        delete obj;

    }

};



TEST_F(PageTransitionTest_1229, IsOk_ReturnsTrueForValidObject_1229) {

    PageTransition pt(obj);

    EXPECT_TRUE(pt.isOk());

}



TEST_F(PageTransitionTest_1229, GetType_ReturnsDefaultType_1229) {

    PageTransition pt(obj);

    EXPECT_EQ(pt.getType(), PageTransitionType::UNKNOWN); // Assuming UNKNOWN is a default type

}



TEST_F(PageTransitionTest_1229, GetDuration_ReturnsNonNegativeValue_1229) {

    PageTransition pt(obj);

    EXPECT_GE(pt.getDuration(), 0.0);

}



TEST_F(PageTransitionTest_1229, GetAlignment_ReturnsDefaultAlignment_1229) {

    PageTransition pt(obj);

    EXPECT_EQ(pt.getAlignment(), PageTransitionAlignment::HORIZONTAL); // Assuming HORIZONTAL is a default alignment

}



TEST_F(PageTransitionTest_1229, GetDirection_ReturnsDefaultDirection_1229) {

    PageTransition pt(obj);

    EXPECT_EQ(pt.getDirection(), PageTransitionDirection::NORMAL); // Assuming NORMAL is a default direction

}



TEST_F(PageTransitionTest_1229, GetAngle_ReturnsZeroForDefaultObject_1229) {

    PageTransition pt(obj);

    EXPECT_EQ(pt.getAngle(), 0);

}



TEST_F(PageTransitionTest_1229, GetScale_ReturnsOneForDefaultObject_1229) {

    PageTransition pt(obj);

    EXPECT_DOUBLE_EQ(pt.getScale(), 1.0);

}



TEST_F(PageTransitionTest_1229, IsRectangular_ReturnsFalseByDefault_1229) {

    PageTransition pt(obj);

    EXPECT_FALSE(pt.isRectangular());

}
