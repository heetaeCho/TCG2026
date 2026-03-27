#include <gtest/gtest.h>

#include "Annot.h"



// Mock class for testing AnnotBorder

class MockAnnotBorder : public AnnotBorder {

public:

    MOCK_METHOD(AnnotBorderStyle, getStyle, (), (const, override));

};



TEST_F(MockAnnotBorderTest_749, GetStyle_ReturnsExpectedValue_749) {

    // Arrange

    MockAnnotBorder mockBorder;

    EXPECT_CALL(mockBorder, getStyle()).WillOnce(::testing::Return(annotBorderStyleSolid));



    // Act

    AnnotBorderStyle result = mockBorder.getStyle();



    // Assert

    EXPECT_EQ(result, annotBorderStyleSolid);

}



TEST_F(MockAnnotBorderTest_749, GetStyle_ReturnsAnotherExpectedValue_749) {

    // Arrange

    MockAnnotBorder mockBorder;

    EXPECT_CALL(mockBorder, getStyle()).WillOnce(::testing::Return(annotBorderStyleDashed));



    // Act

    AnnotBorderStyle result = mockBorder.getStyle();



    // Assert

    EXPECT_EQ(result, annotBorderStyleDashed);

}



TEST_F(MockAnnotBorderTest_749, GetStyle_ReturnsDefaultStyleIfNotSet_749) {

    // Arrange

    MockAnnotBorder mockBorder;

    EXPECT_CALL(mockBorder, getStyle()).WillOnce(::testing::Return(annotBorderStyleNone));



    // Act

    AnnotBorderStyle result = mockBorder.getStyle();



    // Assert

    EXPECT_EQ(result, annotBorderStyleNone);

}
