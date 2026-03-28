#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "poppler-private.h"



class PopplerStructureElementTest_2558 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a valid PopplerStructureElement

        element = reinterpret_cast<PopplerStructureElement*>(malloc(sizeof(PopplerStructureElement)));

        element->elem = new StructElement();



        // Initialize a valid PopplerColor

        color = new PopplerColor();

    }



    void TearDown() override {

        // Clean up the allocated memory

        delete element->elem;

        free(element);

        delete color;

    }



    PopplerStructureElement* element;

    PopplerColor* color;

};



TEST_F(PopplerStructureElementTest_2558, GetBackgroundColor_ValidElementAndColor_ReturnsTrue_2558) {

    // Assuming the element has a background color attribute set

    EXPECT_TRUE(poppler_structure_element_get_background_color(element, color));

}



TEST_F(PopplerStructureElementTest_2558, GetBackgroundColor_ElementIsNull_ReturnsFalse_2558) {

    EXPECT_FALSE(poppler_structure_element_get_background_color(nullptr, color));

}



TEST_F(PopplerStructureElementTest_2558, GetBackgroundColor_ColorIsNull_ReturnsFalse_2558) {

    EXPECT_FALSE(poppler_structure_element_get_background_color(element, nullptr));

}



TEST_F(PopplerStructureElementTest_2558, GetBackgroundColor_NoBackgroundColorAttribute_ReturnsFalse_2558) {

    // Assuming the element does not have a background color attribute set

    EXPECT_FALSE(poppler_structure_element_get_background_color(element, color));

}
