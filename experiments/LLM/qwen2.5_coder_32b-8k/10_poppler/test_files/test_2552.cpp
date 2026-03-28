#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "./TestProjects/poppler/glib/poppler-structure-element.h"

}



class PopplerStructureElementTest_2552 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Initialize any necessary resources here

        poppler_structure_element = static_cast<PopplerStructureElement*>(g_malloc0(sizeof(PopplerStructureElement)));

        G_TYPE_INIT();  // Ensure GType system is initialized if necessary

    }



    virtual void TearDown() {

        // Clean up resources after each test

        g_free(poppler_structure_element);

    }



    PopplerStructureElement* poppler_structure_element;

};



TEST_F(PopplerStructureElementTest_2552, GetWritingMode_ValidElement_2552) {

    // Arrange: Set up a valid PopplerStructureElement

    poppler_structure_element->elem = /* assume some valid initialization */ nullptr;



    // Act: Call the function under test

    PopplerStructureWritingMode mode = poppler_structure_element_get_writing_mode(poppler_structure_element);



    // Assert: Verify that the function returns an expected value

    EXPECT_TRUE(mode >= POPPLER_STRUCTURE_WRITING_MODE_LTR && mode <= POPPLER_STRUCTURE_WRITING_MODE_UNKNOWN);

}



TEST_F(PopplerStructureElementTest_2552, GetWritingMode_NullElement_2552) {

    // Arrange: Set up a null PopplerStructureElement

    poppler_structure_element = nullptr;



    // Act: Call the function under test

    PopplerStructureWritingMode mode = poppler_structure_element_get_writing_mode(poppler_structure_element);



    // Assert: Verify that the function returns the default value when the element is null

    EXPECT_EQ(mode, EnumNameValue<PopplerStructureWritingMode>::values[0].value);

}



TEST_F(PopplerStructureElementTest_2552, GetWritingMode_InvalidElement_2552) {

    // Arrange: Set up an invalid PopplerStructureElement (not of type POPPLER_IS_STRUCTURE_ELEMENT)

    poppler_structure_element->elem = /* assume some invalid initialization */ reinterpret_cast<const StructElement*>(0x1);



    // Act: Call the function under test

    PopplerStructureWritingMode mode = poppler_structure_element_get_writing_mode(poppler_structure_element);



    // Assert: Verify that the function returns the default value when the element is invalid

    EXPECT_EQ(mode, EnumNameValue<PopplerStructureWritingMode>::values[0].value);

}
