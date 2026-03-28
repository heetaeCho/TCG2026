#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest_129 : public ::testing::Test {

protected:

    virtual void SetUp() {

        xmlDoc = new XMLDocument();

        rootElement = xmlDoc->NewElement("Root");

        xmlDoc->InsertFirstChild(rootElement);

        xmlHandle = XMLHandle(rootElement);

    }



    virtual void TearDown() {

        delete xmlDoc;

    }



    XMLDocument* xmlDoc;

    XMLElement* rootElement;

    XMLHandle xmlHandle;

};



TEST_F(XMLHandleTest_129, ToElement_ReturnsValidPointer_129) {

    EXPECT_NE(xmlHandle.ToElement(), nullptr);

}



TEST_F(XMLHandleTest_129, ToElement_ReturnsNullForInvalidNode_129) {

    XMLHandle invalidHandle(nullptr);

    EXPECT_EQ(invalidHandle.ToElement(), nullptr);

}



TEST_F(XMLHandleTest_129, FirstChild_ReturnsValidXMLHandle_129) {

    XMLElement* child = xmlDoc->NewElement("Child");

    rootElement->InsertFirstChild(child);

    XMLHandle childHandle = xmlHandle.FirstChild();

    EXPECT_NE(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_129, FirstChild_ReturnsNullIfNoChildren_129) {

    XMLHandle childHandle = xmlHandle.FirstChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_129, FirstChildElement_ReturnsValidXMLHandle_129) {

    XMLElement* child = xmlDoc->NewElement("Child");

    rootElement->InsertFirstChild(child);

    XMLHandle childHandle = xmlHandle.FirstChildElement();

    EXPECT_NE(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_129, FirstChildElement_ReturnsNullIfNoMatchingChildren_129) {

    XMLElement* child = xmlDoc->NewElement("Child");

    rootElement->InsertFirstChild(child);

    XMLHandle childHandle = xmlHandle.FirstChildElement("NonExistent");

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_129, LastChild_ReturnsValidXMLHandle_129) {

    XMLElement* child = xmlDoc->NewElement("Child");

    rootElement->InsertEndChild(child);

    XMLHandle childHandle = xmlHandle.LastChild();

    EXPECT_NE(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_129, LastChild_ReturnsNullIfNoChildren_129) {

    XMLHandle childHandle = xmlHandle.LastChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_129, LastChildElement_ReturnsValidXMLHandle_129) {

    XMLElement* child = xmlDoc->NewElement("Child");

    rootElement->InsertEndChild(child);

    XMLHandle childHandle = xmlHandle.LastChildElement();

    EXPECT_NE(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_129, LastChildElement_ReturnsNullIfNoMatchingChildren_129) {

    XMLElement* child = xmlDoc->NewElement("Child");

    rootElement->InsertEndChild(child);

    XMLHandle childHandle = xmlHandle.LastChildElement("NonExistent");

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_129, PreviousSibling_ReturnsNullForRoot_129) {

    XMLHandle siblingHandle = xmlHandle.PreviousSibling();

    EXPECT_EQ(siblingHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_129, NextSibling_ReturnsNullForRoot_129) {

    XMLHandle siblingHandle = xmlHandle.NextSibling();

    EXPECT_EQ(siblingHandle.ToNode(), nullptr);

}
