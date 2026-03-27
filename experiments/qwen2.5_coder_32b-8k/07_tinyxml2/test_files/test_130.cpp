#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest_130 : public ::testing::Test {

protected:

    virtual void SetUp() {

        xmlDoc = new XMLDocument();

        root = xmlDoc->NewElement("Root");

        xmlDoc->InsertEndChild(root);

        xmlHandle = XMLHandle(root);

    }



    virtual void TearDown() {

        delete xmlDoc;

    }



    XMLDocument* xmlDoc;

    XMLElement* root;

    XMLHandle xmlHandle;

};



TEST_F(XMLHandleTest_130, ToText_ReturnsNullForNonTextNodes_130) {

    EXPECT_EQ(xmlHandle.ToText(), nullptr);

}



TEST_F(XMLHandleTest_130, ToNode_ReturnsRootNode_130) {

    EXPECT_EQ(xmlHandle.ToNode(), root);

}



TEST_F(XMLHandleTest_130, FirstChild_ReturnsNullForEmptyElement_130) {

    XMLHandle childHandle = xmlHandle.FirstChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_130, FirstChildElement_ReturnsNullForNonExistentElement_130) {

    XMLHandle childHandle = xmlHandle.FirstChildElement("NonExistent");

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_130, LastChild_ReturnsNullForEmptyElement_130) {

    XMLHandle childHandle = xmlHandle.LastChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_130, LastChildElement_ReturnsNullForNonExistentElement_130) {

    XMLHandle childHandle = xmlHandle.LastChildElement("NonExistent");

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_130, PreviousSibling_ReturnsNullForRoot_130) {

    XMLHandle siblingHandle = xmlHandle.PreviousSibling();

    EXPECT_EQ(siblingHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_130, NextSibling_ReturnsNullForRoot_130) {

    XMLHandle siblingHandle = xmlHandle.NextSibling();

    EXPECT_EQ(siblingHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_130, ToElement_ReturnsRootNode_130) {

    XMLElement* element = xmlHandle.ToElement();

    EXPECT_EQ(element, root);

}
