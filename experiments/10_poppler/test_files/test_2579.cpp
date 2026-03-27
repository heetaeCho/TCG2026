#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/glib/poppler-structure-element.h"

#include "TestProjects/poppler/poppler/Object.h"



using namespace testing;



class PopplerStructureElementTest_2579 : public ::testing::Test {

protected:

    struct _PopplerStructureElement element;

    PopplerStructureElement* poppler_structure_element;



    void SetUp() override {

        poppler_structure_element = reinterpret_cast<PopplerStructureElement*>(&element);

    }

};



TEST_F(PopplerStructureElementTest_2579, GetTextDecorationThickness_ReturnsNaNWhenNotInline_2579) {

    EXPECT_CALL(element.elem->attributes, isInline()).WillOnce(Return(false));

    double result = poppler_structure_element_get_text_decoration_thickness(poppler_structure_element);

    EXPECT_EQ(result, NAN);

}



TEST_F(PopplerStructureElementTest_2579, GetTextDecorationThickness_ReturnsNaNWhenValueIsNull_2579) {

    EXPECT_CALL(element.elem->attributes, isInline()).WillOnce(Return(true));

    EXPECT_CALL(attr_value_or_default(poppler_structure_element, Attribute::TextDecorationThickness)).WillOnce(Return(nullptr));

    double result = poppler_structure_element_get_text_decoration_thickness(poppler_structure_element);

    EXPECT_EQ(result, NAN);

}



TEST_F(PopplerStructureElementTest_2579, GetTextDecorationThickness_ReturnsCorrectValueWhenValid_2579) {

    const Object mock_value(10.5);

    EXPECT_CALL(element.elem->attributes, isInline()).WillOnce(Return(true));

    EXPECT_CALL(attr_value_or_default(poppler_structure_element, Attribute::TextDecorationThickness)).WillOnce(Return(&mock_value));

    double result = poppler_structure_element_get_text_decoration_thickness(poppler_structure_element);

    EXPECT_EQ(result, 10.5);

}



TEST_F(PopplerStructureElementTest_2579, GetTextDecorationThickness_ReturnsNaNWhenObjectIsNotNumber_2579) {

    const Object mock_value("not_a_number");

    EXPECT_CALL(element.elem->attributes, isInline()).WillOnce(Return(true));

    EXPECT_CALL(attr_value_or_default(poppler_structure_element, Attribute::TextDecorationThickness)).WillOnce(Return(&mock_value));

    double result = poppler_structure_element_get_text_decoration_thickness(poppler_structure_element);

    EXPECT_EQ(result, NAN);

}
