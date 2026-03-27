#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "poppler-private.h"



using namespace ::testing;



// Mock for PopplerStructureElement

class MockPopplerStructureElement : public PopplerStructureElement {

public:

    MOCK_METHOD(PopplerStructureElementKind, get_kind, (), (const));

    MOCK_METHOD(const Object*, attr_value_or_default, (Attribute), (const));

};



TEST_F(MockPopplerStructureElementTest_2591, GetTableRowSpan_ReturnsCorrectValue_2591) {

    MockPopplerStructureElement mock_element;

    EXPECT_CALL(mock_element, get_kind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_TABLE));



    Object mock_object(42);  // Assuming RowSpan value is 42

    EXPECT_CALL(mock_element, attr_value_or_default(Attribute::RowSpan)).WillOnce(Return(&mock_object));



    guint result = poppler_structure_element_get_table_row_span(&mock_element);

    EXPECT_EQ(result, 42u);

}



TEST_F(MockPopplerStructureElementTest_2591, GetTableRowSpan_ReturnsZeroForNonTableKind_2591) {

    MockPopplerStructureElement mock_element;

    EXPECT_CALL(mock_element, get_kind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_SPAN));



    guint result = poppler_structure_element_get_table_row_span(&mock_element);

    EXPECT_EQ(result, 0u);

}



TEST_F(MockPopplerStructureElementTest_2591, GetTableRowSpan_ReturnsZeroIfAttributeNotFound_2591) {

    MockPopplerStructureElement mock_element;

    EXPECT_CALL(mock_element, get_kind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_TABLE));

    EXPECT_CALL(mock_element, attr_value_or_default(Attribute::RowSpan)).WillOnce(Return(nullptr));



    guint result = poppler_structure_element_get_table_row_span(&mock_element);

    EXPECT_EQ(result, 0u);

}
