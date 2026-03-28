#include <gtest/gtest.h>

#include "Page.h"

#include <memory>



// Mock class for PageAttrs to use in tests if needed.

class MockPageAttrs : public PageAttrs {

public:

    MOCK_CONST_METHOD0(getRotate, int());

};



TEST_F(PageTest_713, GetRotate_ReturnsCorrectValue_713) {

    // Arrange

    MockPageAttrs mockAttrs;

    EXPECT_CALL(mockAttrs, getRotate()).WillOnce(::testing::Return(90));

    Page page(nullptr, 1, std::move(Object()), Ref(), std::make_unique<MockPageAttrs>(mockAttrs));



    // Act & Assert

    EXPECT_EQ(page.getRotate(), 90);

}



TEST_F(PageTest_713, GetRotate_ReturnsZeroByDefault_713) {

    // Arrange

    MockPageAttrs mockAttrs;

    EXPECT_CALL(mockAttrs, getRotate()).WillOnce(::testing::Return(0));

    Page page(nullptr, 1, std::move(Object()), Ref(), std::make_unique<MockPageAttrs>(mockAttrs));



    // Act & Assert

    EXPECT_EQ(page.getRotate(), 0);

}



TEST_F(PageTest_713, GetRotate_ReturnsNegativeValue_713) {

    // Arrange

    MockPageAttrs mockAttrs;

    EXPECT_CALL(mockAttrs, getRotate()).WillOnce(::testing::Return(-90));

    Page page(nullptr, 1, std::move(Object()), Ref(), std::make_unique<MockPageAttrs>(mockAttrs));



    // Act & Assert

    EXPECT_EQ(page.getRotate(), -90);

}



TEST_F(PageTest_713, GetRotate_ReturnsPositiveValue_713) {

    // Arrange

    MockPageAttrs mockAttrs;

    EXPECT_CALL(mockAttrs, getRotate()).WillOnce(::testing::Return(180));

    Page page(nullptr, 1, std::move(Object()), Ref(), std::make_unique<MockPageAttrs>(mockAttrs));



    // Act & Assert

    EXPECT_EQ(page.getRotate(), 180);

}
