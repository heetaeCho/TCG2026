#include <gtest/gtest.h>

#include "poppler-structure-element.h"

#include "poppler-private.h"

#include "Object.h"



using namespace testing;



// Mocking a way to set attributes for PopplerStructureElement

class MockPopplerStructureElement : public PopplerStructureElement {

public:

    MOCK_METHOD(guint, get_kind, (), (const));

    MOCK_METHOD(const Object*, attr_value_or_default, (Attribute), (const));

};



TEST_F(PopplerStructureElementTest_2592, InvalidKindReturnsZero_2592) {

    MockPopplerStructureElement element;

    EXPECT_CALL(element, get_kind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_TEXT));



    guint result = poppler_structure_element_get_table_column_span(&element);

    EXPECT_EQ(result, 0u);

}



TEST_F(PopplerStructureElementTest_2592, ValidKindAndValidAttributeReturnsSpan_2592) {

    MockPopplerStructureElement element;

    EXPECT_CALL(element, get_kind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_TABLE));



    const Object expectedObject = Object(static_cast<int>(3));

    EXPECT_CALL(element, attr_value_or_default(Attribute::ColSpan)).WillOnce(Return(&expectedObject));



    guint result = poppler_structure_element_get_table_column_span(&element);

    EXPECT_EQ(result, 3u);

}



TEST_F(PopplerStructureElementTest_2592, ValidKindAndNullAttributeReturnsZero_2592) {

    MockPopplerStructureElement element;

    EXPECT_CALL(element, get_kind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_TABLE));



    const Object* nullObject = nullptr;

    EXPECT_CALL(element, attr_value_or_default(Attribute::ColSpan)).WillOnce(Return(nullObject));



    guint result = poppler_structure_element_get_table_column_span(&element);

    EXPECT_EQ(result, 0u);

}



TEST_F(PopplerStructureElementTest_2592, ValidKindAndNonIntAttributeReturnsZero_2592) {

    MockPopplerStructureElement element;

    EXPECT_CALL(element, get_kind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_TABLE));



    const Object expectedObject = Object(static_cast<bool>(true));

    EXPECT_CALL(element, attr_value_or_default(Attribute::ColSpan)).WillOnce(Return(&expectedObject));



    guint result = poppler_structure_element_get_table_column_span(&element);

    EXPECT_EQ(result, 0u);

}



TEST_F(PopplerStructureElementTest_2592, ValidKindAndZeroSpanReturnsZero_2592) {

    MockPopplerStructureElement element;

    EXPECT_CALL(element, get_kind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_TABLE));



    const Object expectedObject = Object(static_cast<int>(0));

    EXPECT_CALL(element, attr_value_or_default(Attribute::ColSpan)).WillOnce(Return(&expectedObject));



    guint result = poppler_structure_element_get_table_column_span(&element);

    EXPECT_EQ(result, 0u);

}



TEST_F(PopplerStructureElementTest_2592, ValidKindAndLargeSpanReturnsSpan_2592) {

    MockPopplerStructureElement element;

    EXPECT_CALL(element, get_kind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_TABLE));



    const Object expectedObject = Object(static_cast<int>(1024));

    EXPECT_CALL(element, attr_value_or_default(Attribute::ColSpan)).WillOnce(Return(&expectedObject));



    guint result = poppler_structure_element_get_table_column_span(&element);

    EXPECT_EQ(result, 1024u);

}
