#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest_125 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup a simple XML document and nodes for testing

        doc = new XMLDocument();

        rootElement = doc->NewElement("Root");

        doc->InsertFirstChild(rootElement);



        childElement1 = doc->NewElement("Child");

        childElement2 = doc->NewElement("Sibling");



        rootElement->LinkEndChild(childElement1);

        childElement1->LinkEndChild(childElement2);

    }



    void TearDown() override {

        delete doc;

    }



    XMLDocument* doc;

    XMLElement* rootElement;

    XMLElement* childElement1;

    XMLElement* childElement2;

};



TEST_F(XMLHandleTest_125, PreviousSiblingElement_NoPreviousSibling_125) {

    XMLHandle handle(childElement1);

    XMLHandle previousSibling = handle.PreviousSiblingElement();

    EXPECT_EQ(previousSibling.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_125, PreviousSiblingElement_WithPreviousSibling_125) {

    XMLHandle handle(childElement2);

    XMLHandle previousSibling = handle.PreviousSiblingElement();

    EXPECT_EQ(previousSibling.ToNode(), childElement1);

}



TEST_F(XMLHandleTest_125, PreviousSiblingElement_WithNameMatch_125) {

    XMLHandle handle(childElement2);

    XMLHandle previousSibling = handle.PreviousSiblingElement("Child");

    EXPECT_EQ(previousSibling.ToNode(), childElement1);

}



TEST_F(XMLHandleTest_125, PreviousSiblingElement_WithNameNoMatch_125) {

    XMLHandle handle(childElement2);

    XMLHandle previousSibling = handle.PreviousSiblingElement("NonExistent");

    EXPECT_EQ(previousSibling.ToNode(), nullptr);

}
