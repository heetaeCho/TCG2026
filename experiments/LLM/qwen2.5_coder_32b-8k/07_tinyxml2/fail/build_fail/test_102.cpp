#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLDocument* doc;

    XMLElement* element;



    void SetUp() override {

        doc = new XMLDocument();

        element = doc->NewElement("testElement");

        ASSERT_NE(element, nullptr);

        doc->InsertFirstChild(element);

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(XMLElementTest_102, SetAttributeBool_NormalOperation_102) {

    element->SetAttribute("isActive", true);

    EXPECT_EQ(element->BoolAttribute("isActive"), true);



    element->SetAttribute("isActive", false);

    EXPECT_EQ(element->BoolAttribute("isActive"), false);

}



TEST_F(XMLElementTest_102, SetAttributeBool_BoundaryConditions_102) {

    // Test with empty attribute name

    element->SetAttribute("", true);

    EXPECT_FALSE(element->FindAttribute("") != nullptr);



    // Test with null attribute name

    element->SetAttribute(nullptr, false);

    EXPECT_FALSE(element->FindAttribute(nullptr) != nullptr);

}



TEST_F(XMLElementTest_102, SetAttributeBool_ExceptionalCases_102) {

    // No exceptional cases expected based on the provided interface

}
