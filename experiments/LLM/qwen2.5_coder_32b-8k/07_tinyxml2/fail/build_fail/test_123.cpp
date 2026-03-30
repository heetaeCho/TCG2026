#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest_123 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* rootElement;

    XMLHandle handle;



    void SetUp() override {

        rootElement = doc.NewElement("Root");

        doc.InsertFirstChild(rootElement);

        handle = XMLHandle(rootElement);

    }

};



TEST_F(XMLHandleTest_123, LastChildElement_ReturnsNullForEmptyChildren_123) {

    EXPECT_EQ(handle.LastChildElement(), nullptr);

}



TEST_F(XMLHandleTest_123, LastChildElement_ReturnsLastElementWithMatchingName_123) {

    XMLElement* child1 = doc.NewElement("Child");

    XMLElement* child2 = doc.NewElement("Target");

    rootElement->InsertEndChild(child1);

    rootElement->InsertEndChild(child2);



    XMLHandle lastHandle = handle.LastChildElement("Target");

    EXPECT_EQ(lastHandle.ToNode(), child2);

}



TEST_F(XMLHandleTest_123, LastChildElement_ReturnsNullForNonMatchingName_123) {

    XMLElement* child1 = doc.NewElement("Child");

    rootElement->InsertEndChild(child1);



    XMLHandle lastHandle = handle.LastChildElement("Target");

    EXPECT_EQ(lastHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_123, LastChildElement_ReturnsLastOfMultipleMatchingElements_123) {

    XMLElement* child1 = doc.NewElement("Target");

    XMLElement* child2 = doc.NewElement("Target");

    rootElement->InsertEndChild(child1);

    rootElement->InsertEndChild(child2);



    XMLHandle lastHandle = handle.LastChildElement("Target");

    EXPECT_EQ(lastHandle.ToNode(), child2);

}



TEST_F(XMLHandleTest_123, LastChildElement_IgnoresCaseForMatchingName_123) {

    XMLElement* child1 = doc.NewElement("target");

    rootElement->InsertEndChild(child1);



    XMLHandle lastHandle = handle.LastChildElement("Target");

    EXPECT_EQ(lastHandle.ToNode(), child1);

}
