#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "Object.h"



using namespace testing;



class PopplerStructureElementTest_2590 : public ::testing::Test {

protected:

    struct _PopplerStructureElement* poppler_structure_element;



    void SetUp() override {

        poppler_structure_element = new _PopplerStructureElement();

    }



    void TearDown() override {

        delete poppler_structure_element;

    }

};



TEST_F(PopplerStructureElementTest_2590, GetFormDescription_ReturnsNullForNonFormKind_2590) {

    // Arrange

    EXPECT_CALL(*poppler_structure_element->elem, getKind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_DOCUMENT));



    // Act & Assert

    EXPECT_EQ(poppler_structure_element_get_form_description(poppler_structure_element), nullptr);

}



TEST_F(PopplerStructureElementTest_2590, GetFormDescription_ReturnsNullForMissingDescAttribute_2590) {

    // Arrange

    EXPECT_CALL(*poppler_structure_element->elem, getKind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_FORM));

    EXPECT_CALL(*poppler_structure_element->elem, attr_value_or_default(Attribute::Desc)).WillOnce(Return(nullptr));



    // Act & Assert

    EXPECT_EQ(poppler_structure_element_get_form_description(poppler_structure_element), nullptr);

}



TEST_F(PopplerStructureElementTest_2590, GetFormDescription_ReturnsStringForStringDescAttribute_2590) {

    // Arrange

    const char* expected_desc = "Sample Description";

    Object mock_object(Object::stringA, expected_desc);

    EXPECT_CALL(*poppler_structure_element->elem, getKind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_FORM));

    EXPECT_CALL(*poppler_structure_element->elem, attr_value_or_default(Attribute::Desc)).WillOnce(Return(&mock_object));



    // Act

    gchar* result = poppler_structure_element_get_form_description(poppler_structure_element);



    // Assert

    ASSERT_NE(result, nullptr);

    EXPECT_STREQ(result, expected_desc);

    g_free(result);  // Free the allocated memory by _poppler_goo_string_to_utf8

}



TEST_F(PopplerStructureElementTest_2590, GetFormDescription_ReturnsNameForNameDescAttribute_2590) {

    // Arrange

    const char* expected_desc = "Sample Name";

    Object mock_object(Object::nameA, expected_desc);

    EXPECT_CALL(*poppler_structure_element->elem, getKind()).WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_FORM));

    EXPECT_CALL(*poppler_structure_element->elem, attr_value_or_default(Attribute::Desc)).WillOnce(Return(&mock_object));



    // Act

    gchar* result = poppler_structure_element_get_form_description(poppler_structure_element);



    // Assert

    ASSERT_NE(result, nullptr);

    EXPECT_STREQ(result, expected_desc);

    g_free(result);  // Free the allocated memory by g_strdup

}
