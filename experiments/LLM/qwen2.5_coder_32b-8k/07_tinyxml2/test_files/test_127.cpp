#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest : public ::testing::Test {

protected:

    void SetUp() override {

        document = new XMLDocument();

        root = document->NewElement("Root");

        document->InsertEndChild(root);

        handle = XMLHandle(root);

    }



    void TearDown() override {

        delete document;

    }



    XMLDocument* document;

    XMLElement* root;

    XMLHandle handle;

};



TEST_F(XMLHandleTest_127, NextSiblingElement_NoNextSibling_127) {

    XMLHandle nextSibling = handle.NextSiblingElement();

    EXPECT_EQ(nextSibling.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_127, NextSiblingElement_WithNextSibling_127) {

    XMLElement* sibling = document->NewElement("Sibling");

    root->_parent->InsertEndChild(sibling);

    XMLHandle nextSibling = handle.NextSiblingElement();

    EXPECT_EQ(nextSibling.ToNode(), sibling);

}



TEST_F(XMLHandleTest_127, NextSiblingElement_WithSpecificName_127) {

    XMLElement* sibling = document->NewElement("Sibling");

    root->_parent->InsertEndChild(sibling);

    XMLHandle nextSibling = handle.NextSiblingElement("Sibling");

    EXPECT_EQ(nextSibling.ToNode(), sibling);

}



TEST_F(XMLHandleTest_127, NextSiblingElement_WrongName_127) {

    XMLElement* sibling = document->NewElement("Different");

    root->_parent->InsertEndChild(sibling);

    XMLHandle nextSibling = handle.NextSiblingElement("Sibling");

    EXPECT_EQ(nextSibling.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_127, NextSiblingElement_NoParent_127) {

    root->_parent = nullptr;

    XMLHandle nextSibling = handle.NextSiblingElement();

    EXPECT_EQ(nextSibling.ToNode(), nullptr);

}
