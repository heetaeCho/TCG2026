#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PageTransition.h"

#include <memory>



// Mocking Object for testing purposes

class MockObject {

public:

    virtual ~MockObject() = default;

};



using ::testing::Return;



TEST_F(PageTransitionTest_1231, IsOk_ReturnsTrue_1231) {

    auto mockObject = std::make_unique<MockObject>();

    PageTransition transition(mockObject.get());

    EXPECT_TRUE(transition.isOk());

}



TEST_F(PageTransitionTest_1231, GetDuration_DefaultValue_1231) {

    auto mockObject = std::make_unique<MockObject>();

    PageTransition transition(mockObject.get());

    EXPECT_DOUBLE_EQ(transition.getDuration(), 0.0);

}



TEST_F(PageTransitionTest_1231, GetType_ReturnsDefaultValue_1231) {

    auto mockObject = std::make_unique<MockObject>();

    PageTransition transition(mockObject.get());

    EXPECT_EQ(transition.getType(), PageTransitionType::Unknown); // Assuming default type is Unknown

}



TEST_F(PageTransitionTest_1231, GetAlignment_ReturnsDefaultValue_1231) {

    auto mockObject = std::make_unique<MockObject>();

    PageTransition transition(mockObject.get());

    EXPECT_EQ(transition.getAlignment(), PageTransitionAlignment::Unknown); // Assuming default alignment is Unknown

}



TEST_F(PageTransitionTest_1231, GetDirection_ReturnsDefaultValue_1231) {

    auto mockObject = std::make_unique<MockObject>();

    PageTransition transition(mockObject.get());

    EXPECT_EQ(transition.getDirection(), PageTransitionDirection::Unknown); // Assuming default direction is Unknown

}



TEST_F(PageTransitionTest_1231, GetAngle_DefaultValue_1231) {

    auto mockObject = std::make_unique<MockObject>();

    PageTransition transition(mockObject.get());

    EXPECT_EQ(transition.getAngle(), 0);

}



TEST_F(PageTransitionTest_1231, GetScale_DefaultValue_1231) {

    auto mockObject = std::make_unique<MockObject>();

    PageTransition transition(mockObject.get());

    EXPECT_DOUBLE_EQ(transition.getScale(), 1.0); // Assuming default scale is 1.0

}



TEST_F(PageTransitionTest_1231, IsRectangular_DefaultValue_1231) {

    auto mockObject = std::make_unique<MockObject>();

    PageTransition transition(mockObject.get());

    EXPECT_FALSE(transition.isRectangular());

}
