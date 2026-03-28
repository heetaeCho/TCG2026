#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "poppler-private.h"



using namespace testing;



class PopplerStructureElementTest_2557 : public Test {

protected:

    void SetUp() override {

        // Initialize a valid PopplerStructureElement for use in tests

        poppler_structure_element = static_cast<PopplerStructureElement*>(g_malloc0(sizeof(PopplerStructureElement)));

        color = static_cast<PopplerColor*>(g_malloc0(sizeof(PopplerColor)));

    }



    void TearDown() override {

        // Clean up allocated memory after each test

        g_free(poppler_structure_element);

        g_free(color);

    }



    PopplerStructureElement* poppler_structure_element;

    PopplerColor* color;

};



TEST_F(PopplerStructureElementTest_2557, GetColorWithNullElement_2557) {

    EXPECT_FALSE(poppler_structure_element_get_color(nullptr, color));

}



TEST_F(PopplerStructureElementTest_2557, GetColorWithNullColor_2557) {

    EXPECT_FALSE(poppler_structure_element_get_color(poppler_structure_element, nullptr));

}



TEST_F(PopplerStructureElementTest_2557, GetColorWithoutColorAttribute_2557) {

    EXPECT_CALL(*this, attr_value_or_default(_, Attribute::Color)).WillOnce(Return(nullptr));

    EXPECT_FALSE(poppler_structure_element_get_color(poppler_structure_element, color));

}



TEST_F(PopplerStructureElementTest_2557, GetColorWithValidColorAttribute_2557) {

    const Object* mockObject = static_cast<const Object*>(g_malloc0(sizeof(Object)));

    EXPECT_CALL(*this, attr_value_or_default(_, Attribute::Color)).WillOnce(Return(mockObject));

    EXPECT_TRUE(poppler_structure_element_get_color(poppler_structure_element, color));

    g_free(const_cast<Object*>(mockObject));

}
