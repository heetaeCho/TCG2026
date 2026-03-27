#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "Object.h"



using namespace testing;



class PopplerStructureElementTest_2584 : public ::testing::Test {

protected:

    struct _PopplerStructureElement* poppler_structure_element;

    

    void SetUp() override {

        poppler_structure_element = new _PopplerStructureElement();

    }



    void TearDown() override {

        delete poppler_structure_element;

    }

};



TEST_F(PopplerStructureElementTest_2584, GetColumnCount_NormalOperation_2584) {

    // Assuming attr_value_or_default and Attribute::ColumnCount are set up to return a valid Object with an integer.

    EXPECT_CALL(*poppler_structure_element->elem, getAttribute(Attribute::ColumnCount))

        .WillOnce(Return(Object(10)));



    guint column_count = poppler_structure_element_get_column_count(poppler_structure_element);

    EXPECT_EQ(column_count, 10u);

}



TEST_F(PopplerStructureElementTest_2584, GetColumnCount_BoundaryCondition_Zero_2584) {

    // Assuming attr_value_or_default and Attribute::ColumnCount are set up to return a valid Object with zero.

    EXPECT_CALL(*poppler_structure_element->elem, getAttribute(Attribute::ColumnCount))

        .WillOnce(Return(Object(0)));



    guint column_count = poppler_structure_element_get_column_count(poppler_structure_element);

    EXPECT_EQ(column_count, 0u);

}



TEST_F(PopplerStructureElementTest_2584, GetColumnCount_ErrorCase_NotGrouping_2584) {

    // Assuming poppler_structure_element_is_grouping returns false.

    EXPECT_CALL(*poppler_structure_element->elem, isGrouping())

        .WillOnce(Return(false));



    guint column_count = poppler_structure_element_get_column_count(poppler_structure_element);

    EXPECT_EQ(column_count, 0u);

}



TEST_F(PopplerStructureElementTest_2584, GetColumnCount_ErrorCase_AttributeNotFound_2584) {

    // Assuming attr_value_or_default returns a null Object when the attribute is not found.

    EXPECT_CALL(*poppler_structure_element->elem, getAttribute(Attribute::ColumnCount))

        .WillOnce(Return(Object()));



    guint column_count = poppler_structure_element_get_column_count(poppler_structure_element);

    EXPECT_EQ(column_count, 0u);

}



TEST_F(PopplerStructureElementTest_2584, GetColumnCount_ErrorCase_AttributeNotInteger_2584) {

    // Assuming attr_value_or_default returns a non-integer Object.

    EXPECT_CALL(*poppler_structure_element->elem, getAttribute(Attribute::ColumnCount))

        .WillOnce(Return(Object("not an integer")));



    guint column_count = poppler_structure_element_get_column_count(poppler_structure_element);

    EXPECT_EQ(column_count, 0u);

}
