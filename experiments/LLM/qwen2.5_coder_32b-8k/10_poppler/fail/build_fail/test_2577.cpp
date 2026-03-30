#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "poppler-private.h"



using namespace testing;



class PopplerStructureElementTest_2577 : public Test {

protected:

    void SetUp() override {

        // Initialize a mock PopplerStructureElement

        poppler_structure_element = new _PopplerStructureElement();

        // Assume some basic setup for the structure element

    }



    void TearDown() override {

        delete poppler_structure_element;

    }



    _PopplerStructureElement* poppler_structure_element;

};



TEST_F(PopplerStructureElementTest_2577, GetLineHeight_ReturnsNegativeOneForNormal_2577) {

    // Arrange

    const Object value("Name", "Normal");

    EXPECT_CALL(*poppler_structure_element, attr_value_or_default(Attribute::LineHeight))

        .WillOnce(Return(&value));



    // Act

    double result = poppler_structure_element_get_line_height(poppler_structure_element);



    // Assert

    ASSERT_EQ(result, -1.0);

}



TEST_F(PopplerStructureElementTest_2577, GetLineHeight_ReturnsNegativeOneForAuto_2577) {

    // Arrange

    const Object value("Name", "Auto");

    EXPECT_CALL(*poppler_structure_element, attr_value_or_default(Attribute::LineHeight))

        .WillOnce(Return(&value));



    // Act

    double result = poppler_structure_element_get_line_height(poppler_structure_element);



    // Assert

    ASSERT_EQ(result, -1.0);

}



TEST_F(PopplerStructureElementTest_2577, GetLineHeight_ReturnsNumericValue_2577) {

    // Arrange

    const Object value(3.5);

    EXPECT_CALL(*poppler_structure_element, attr_value_or_default(Attribute::LineHeight))

        .WillOnce(Return(&value));



    // Act

    double result = poppler_structure_element_get_line_height(poppler_structure_element);



    // Assert

    ASSERT_EQ(result, 3.5);

}



TEST_F(PopplerStructureElementTest_2577, GetLineHeight_ReturnsNANForNonInlineElement_2577) {

    // Arrange

    EXPECT_CALL(*poppler_structure_element, poppler_structure_element_is_inline())

        .WillOnce(Return(false));



    // Act

    double result = poppler_structure_element_get_line_height(poppler_structure_element);



    // Assert

    ASSERT_TRUE(std::isnan(result));

}



TEST_F(PopplerStructureElementTest_2577, GetLineHeight_ReturnsNANForNullValue_2577) {

    // Arrange

    const Object value = Object::null();

    EXPECT_CALL(*poppler_structure_element, attr_value_or_default(Attribute::LineHeight))

        .WillOnce(Return(&value));



    // Act

    double result = poppler_structure_element_get_line_height(poppler_structure_element);



    // Assert

    ASSERT_TRUE(std::isnan(result));

}
