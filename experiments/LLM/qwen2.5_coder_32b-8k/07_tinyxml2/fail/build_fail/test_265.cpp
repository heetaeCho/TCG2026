#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("TestElement");

        element->SetAttribute("attribute1", "value1");

        element->SetAttribute("attribute2", 42);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_265, ShallowCloneWithNullDoc_265) {

    XMLElement* clonedElement = element->ShallowClone(nullptr);



    EXPECT_NE(clonedElement, nullptr);

    EXPECT_STREQ(clonedElement->Value(), "TestElement");

    EXPECT_STREQ(clonedElement->Attribute("attribute1"), "value1");

    EXPECT_EQ(clonedElement->IntAttribute("attribute2"), 42);



    delete clonedElement;

}



TEST_F(XMLElementTest_265, ShallowCloneWithProvidedDoc_265) {

    XMLDocument anotherDoc;

    XMLElement* clonedElement = element->ShallowClone(&anotherDoc);



    EXPECT_NE(clonedElement, nullptr);

    EXPECT_STREQ(clonedElement->Value(), "TestElement");

    EXPECT_STREQ(clonedElement->Attribute("attribute1"), "value1");

    EXPECT_EQ(clonedElement->IntAttribute("attribute2"), 42);

    EXPECT_EQ(clonedElement->GetDocument(), &anotherDoc);



    delete clonedElement;

}



TEST_F(XMLElementTest_265, ShallowCloneWithEmptyElement_265) {

    XMLElement* emptyElement = doc.NewElement("");

    XMLElement* clonedElement = emptyElement->ShallowClone(&doc);



    EXPECT_NE(clonedElement, nullptr);

    EXPECT_STREQ(clonedElement->Value(), "");

    

    delete emptyElement;

    delete clonedElement;

}



TEST_F(XMLElementTest_265, ShallowCloneWithNoAttributes_265) {

    XMLElement* noAttrElement = doc.NewElement("NoAttrElement");

    XMLElement* clonedElement = noAttrElement->ShallowClone(&doc);



    EXPECT_NE(clonedElement, nullptr);

    EXPECT_STREQ(clonedElement->Value(), "NoAttrElement");

    EXPECT_EQ(clonedElement->FirstAttribute(), nullptr);



    delete noAttrElement;

    delete clonedElement;

}
