#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"



// Mocking external collaborators if needed (none in this case)

class PopplerStructureElementTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary test state

        poppler_structure_element = new PopplerStructureElement();

    }



    void TearDown() override {

        // Clean up any resources used by tests

        delete poppler_structure_element;

    }



    PopplerStructureElement* poppler_structure_element;

};



TEST_F(PopplerStructureElementTest_2561, GetBorderThickness_ValidPointer_ReturnsTrue_2561) {

    gdouble border_thicknesses[4];

    EXPECT_TRUE(poppler_structure_element_get_border_thickness(poppler_structure_element, border_thicknesses));

}



TEST_F(PopplerStructureElementTest_2561, GetBorderThickness_NullPointer_ReturnsFalse_2561) {

    EXPECT_FALSE(poppler_structure_element_get_border_thickness(nullptr, nullptr));

}



TEST_F(PopplerStructureElementTest_2561, GetBorderThickness_ValidElementWithoutBorder_ReturnsFalse_2561) {

    gdouble border_thicknesses[4];

    // Assuming the element does not have BorderThickness attribute

    EXPECT_FALSE(poppler_structure_element_get_border_thickness(poppler_structure_element, border_thicknesses));

}



TEST_F(PopplerStructureElementTest_2561, GetBorderThickness_ValidElementWithBorder_ReturnsTrue_2561) {

    gdouble border_thicknesses[4];

    // Assuming the element has BorderThickness attribute

    EXPECT_TRUE(poppler_structure_element_get_border_thickness(poppler_structure_element, border_thicknesses));

}



TEST_F(PopplerStructureElementTest_2561, GetBorderThickness_NullBorderThicknessArray_ReturnsFalse_2561) {

    EXPECT_FALSE(poppler_structure_element_get_border_thickness(poppler_structure_element, nullptr));

}
