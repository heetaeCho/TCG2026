#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.cc"

#include "StructElement.h"



class PopplerStructureElementTest_2516 : public ::testing::Test {

protected:

    void SetUp() override {

        // Mocking a PopplerDocument and StructElement for testing

        document = reinterpret_cast<PopplerDocument*>(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr, NULL));

        element = new StructElement(nullptr, nullptr, nullptr);

        poppler_structure_element = _poppler_structure_element_new(document, element);

    }



    void TearDown() override {

        g_object_unref(document);

        delete element;

        g_object_unref(poppler_structure_element);

    }



    PopplerDocument* document;

    StructElement* element;

    PopplerStructureElement* poppler_structure_element;

};



TEST_F(PopplerStructureElementTest_2516, NewElementInitializesCorrectly_2516) {

    EXPECT_EQ(poppler_structure_element->document, document);

    EXPECT_EQ(poppler_structure_element->elem, element);

}



TEST_F(PopplerStructureElementTest_2516, NullDocumentThrowsAssertion_2516) {

    EXPECT_DEATH(_poppler_structure_element_new(nullptr, element), ".*g_assertion failed.*");

}



TEST_F(PopplerStructureElementTest_2516, NullElementThrowsAssertion_2516) {

    EXPECT_DEATH(_poppler_structure_element_new(document, nullptr), ".*g_assertion failed.*");

}
