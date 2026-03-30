#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "Object.h"



using namespace testing;



class PopplerStructureElementTest_2593 : public ::testing::Test {

protected:

    struct _PopplerStructureElement element;

    PopplerStructureElement* poppler_structure_element = &element;



    void SetUp() override {

        // Initialize the structure element to a default state

        element.elem = nullptr;

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(PopplerStructureElementTest_2593, GetTableHeaders_ReturnsNullForNonTableKind_2593) {

    // Arrange: Set the kind of the structure element to something other than TABLE

    ON_CALL(*poppler_structure_element_get_kind(poppler_structure_element), getType())

        .WillByDefault(Return(POPPLER_STRUCTURE_ELEMENT_PARAGRAPH));



    // Act & Assert: Call get_table_headers and expect nullptr

    EXPECT_EQ(nullptr, poppler_structure_element_get_table_headers(poppler_structure_element));

}



TEST_F(PopplerStructureElementTest_2593, GetTableHeaders_ReturnsNullForMissingHeadersAttribute_2593) {

    // Arrange: Set the kind of the structure element to TABLE and simulate a missing headers attribute

    EXPECT_CALL(*poppler_structure_element_get_kind(poppler_structure_element), getType())

        .WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_TABLE));

    const Object* value = nullptr;



    // Act & Assert: Call get_table_headers and expect nullptr

    EXPECT_EQ(nullptr, poppler_structure_element_get_table_headers(poppler_structure_element));

}



TEST_F(PopplerStructureElementTest_2593, GetTableHeaders_ReturnsNullForNonArrayHeadersAttribute_2593) {

    // Arrange: Set the kind of the structure element to TABLE and simulate a non-array headers attribute

    EXPECT_CALL(*poppler_structure_element_get_kind(poppler_structure_element), getType())

        .WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_TABLE));

    Object nonArrayObject;

    nonArrayObject.setToNull();  // Non-array type



    const Object* value = &nonArrayObject;



    // Act & Assert: Call get_table_headers and expect nullptr

    EXPECT_EQ(nullptr, poppler_structure_element_get_table_headers(poppler_structure_element));

}



TEST_F(PopplerStructureElementTest_2593, GetTableHeaders_ReturnsEmptyArrayForEmptyHeadersAttribute_2593) {

    // Arrange: Set the kind of the structure element to TABLE and simulate an empty array headers attribute

    EXPECT_CALL(*poppler_structure_element_get_kind(poppler_structure_element), getType())

        .WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_TABLE));

    Object arrayObject;

    arrayObject.setArray(new Array());  // Empty array



    const Object* value = &arrayObject;



    // Act: Call get_table_headers

    gchar** result = poppler_structure_element_get_table_headers(poppler_structure_element);



    // Assert: Check that the returned array is empty and properly terminated with nullptr

    EXPECT_EQ(nullptr, result[0]);

    g_free(result);

}



TEST_F(PopplerStructureElementTest_2593, GetTableHeaders_ReturnsArrayWithStringsAndNames_2593) {

    // Arrange: Set the kind of the structure element to TABLE and simulate a headers attribute with strings and names

    EXPECT_CALL(*poppler_structure_element_get_kind(poppler_structure_element), getType())

        .WillOnce(Return(POPPLER_STRUCTURE_ELEMENT_TABLE));

    

    Object arrayObject;

    Array* array = new Array();

    array->arrayAdd(Object(std::string("Header1")));

    array->arrayAdd(Object("Name1"));

    arrayObject.setArray(array);



    const Object* value = &arrayObject;



    // Act: Call get_table_headers

    gchar** result = poppler_structure_element_get_table_headers(poppler_structure_element);



    // Assert: Check that the returned array contains "Header1" and "Name1", properly terminated with nullptr

    EXPECT_STREQ("Header1", result[0]);

    EXPECT_STREQ("Name1", result[1]);

    EXPECT_EQ(nullptr, result[2]);



    // Clean up allocated memory

    g_free(result[0]);

    g_free(result[1]);

    g_free(result);

}
