#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "Object.h"



using namespace testing;



class PopplerStructureElementTest_2595 : public ::testing::Test {

protected:

    void SetUp() override {

        element = new PopplerStructureElement();

    }



    void TearDown() override {

        delete element;

    }



    PopplerStructureElement* element;

};



TEST_F(PopplerStructureElementTest_2595, GetTableSummary_ReturnsNull_WhenObjectIsNull_2595) {

    EXPECT_EQ(poppler_structure_element_get_table_summary(element), nullptr);

}



TEST_F(PopplerStructureElementTest_2595, GetTableSummary_ReturnsUtf8String_WhenObjectIsString_2595) {

    // Assuming attr_value_or_default returns a string Object

    const char* expected = "summary";

    Object mockObject(expected);

    EXPECT_CALL(mockObject, isString()).WillOnce(Return(true));

    EXPECT_CALL(mockObject, getString()).WillOnce(Return(new GooString(expected)));



    element->elem->attr_value_or_default = [&mockObject](Attribute::Summary) { return &mockObject; };



    gchar* result = poppler_structure_element_get_table_summary(element);

    ASSERT_STREQ(result, expected);

    g_free(result);

}



TEST_F(PopplerStructureElementTest_2595, GetTableSummary_ReturnsName_WhenObjectIsName_2595) {

    // Assuming attr_value_or_default returns a name Object

    const char* expected = "summary";

    Object mockObject(expected);

    EXPECT_CALL(mockObject, isString()).WillOnce(Return(false));

    EXPECT_CALL(mockObject, isName()).WillOnce(Return(true));

    EXPECT_CALL(mockObject, getName()).WillOnce(Return(expected));



    element->elem->attr_value_or_default = [&mockObject](Attribute::Summary) { return &mockObject; };



    gchar* result = poppler_structure_element_get_table_summary(element);

    ASSERT_STREQ(result, expected);

    g_free(result);

}



TEST_F(PopplerStructureElementTest_2595, GetTableSummary_ReturnsNull_WhenObjectTypeIsUnknown_2595) {

    // Assuming attr_value_or_default returns an object of unknown type

    Object mockObject;

    EXPECT_CALL(mockObject, isString()).WillOnce(Return(false));

    EXPECT_CALL(mockObject, isName()).WillOnce(Return(false));



    element->elem->attr_value_or_default = [&mockObject](Attribute::Summary) { return &mockObject; };



    EXPECT_EQ(poppler_structure_element_get_table_summary(element), nullptr);

}
