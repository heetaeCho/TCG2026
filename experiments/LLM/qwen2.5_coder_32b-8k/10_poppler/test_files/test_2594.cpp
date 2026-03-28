#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "poppler-private.h"



class PopplerStructureElementTest : public ::testing::Test {

protected:

    struct _PopplerStructureElement element;

    PopplerStructureElement* poppler_structure_element = reinterpret_cast<PopplerStructureElement*>(&element);



    void SetUp() override {

        // Initialize elem to a default value that is not POPPLER_STRUCTURE_ELEMENT_TABLE

        element.elem = nullptr;

    }

};



TEST_F(PopplerStructureElementTest_2594, GetTableScope_NormalOperation_2594) {

    // Setup: Set the kind of structure element to POPPLER_STRUCTURE_ELEMENT_TABLE

    element.elem = reinterpret_cast<const StructElement*>(POPPLER_STRUCTURE_ELEMENT_TABLE);



    // Exercise: Call the function under test

    PopplerStructureTableScope scope = poppler_structure_element_get_table_scope(poppler_structure_element);



    // Verify: Check that the correct table scope is returned

    EXPECT_EQ(scope, EnumNameValue<PopplerStructureTableScope>::values[0].value);

}



TEST_F(PopplerStructureElementTest_2594, GetTableScope_BoundaryCondition_WrongKind_2594) {

    // Setup: Ensure the kind of structure element is not POPPLER_STRUCTURE_ELEMENT_TABLE

    element.elem = reinterpret_cast<const StructElement*>(POPPLER_STRUCTURE_ELEMENT_DOCUMENT);



    // Exercise and Verify: Check that an error is returned when the kind does not match

    EXPECT_DEATH(poppler_structure_element_get_table_scope(poppler_structure_element), ".*");

}



TEST_F(PopplerStructureElementTest_2594, GetTableScope_ExceptionalCase_NullPointer_2594) {

    // Setup: Pass a null pointer to the function

    PopplerStructureElement* null_element = nullptr;



    // Exercise and Verify: Check that an error is returned when the input is null

    EXPECT_DEATH(poppler_structure_element_get_table_scope(null_element), ".*");

}
