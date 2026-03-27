#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest : public ::testing::Test {

protected:

    void SetUp() override {

        document = new XMLDocument();

        root = new XMLElement("root");

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



TEST_F(XMLHandleTest_120, FirstChild_ReturnsValidXMLHandleForExistingChild_120) {

    XMLElement* child = new XMLElement("child");

    root->InsertEndChild(child);

    XMLHandle childHandle = handle.FirstChild();

    EXPECT_NE(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_120, FirstChild_ReturnsInvalidXMLHandleForNoChildren_120) {

    XMLHandle childHandle = handle.FirstChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_120, FirstChildElement_ReturnsValidXMLHandleForExistingChild_120) {

    XMLElement* child = new XMLElement("child");

    root->InsertEndChild(child);

    XMLHandle childHandle = handle.FirstChildElement("child");

    EXPECT_NE(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_120, FirstChildElement_ReturnsInvalidXMLHandleForNonExistingChild_120) {

    XMLElement* child = new XMLElement("child");

    root->InsertEndChild(child);

    XMLHandle childHandle = handle.FirstChildElement("nonexistent");

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_120, LastChild_ReturnsValidXMLHandleForExistingChild_120) {

    XMLElement* child = new XMLElement("child");

    root->InsertEndChild(child);

    XMLHandle childHandle = handle.LastChild();

    EXPECT_NE(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_120, LastChild_ReturnsInvalidXMLHandleForNoChildren_120) {

    XMLHandle childHandle = handle.LastChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_120, LastChildElement_ReturnsValidXMLHandleForExistingChild_120) {

    XMLElement* child = new XMLElement("child");

    root->InsertEndChild(child);

    XMLHandle childHandle = handle.LastChildElement("child");

    EXPECT_NE(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_120, LastChildElement_ReturnsInvalidXMLHandleForNonExistingChild_120) {

    XMLElement* child = new XMLElement("child");

    root->InsertEndChild(child);

    XMLHandle childHandle = handle.LastChildElement("nonexistent");

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_120, ToNode_ReturnsCorrectNode_120) {

    EXPECT_EQ(handle.ToNode(), static_cast<XMLNode*>(root));

}



TEST_F(XMLHandleTest_120, ToElement_ReturnsCorrectElement_120) {

    EXPECT_EQ(handle.ToElement(), root);

}
