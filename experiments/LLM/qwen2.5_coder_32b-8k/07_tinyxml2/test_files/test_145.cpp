#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLConstHandleTest_145 : public ::testing::Test {

protected:

    XMLNode* node;

    XMLConstHandle handle;



    void SetUp() override {

        node = new XMLNode(nullptr);

        handle = XMLConstHandle(node);

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(XMLConstHandleTest_145, ToUnknown_ReturnsNull_145) {

    EXPECT_EQ(handle.ToUnknown(), nullptr);

}



TEST_F(XMLConstHandleTest_145, FirstChild_ReturnsEmptyHandle_145) {

    XMLConstHandle childHandle = handle.FirstChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_145, FirstChildElement_ReturnsEmptyHandle_145) {

    XMLConstHandle childHandle = handle.FirstChildElement("test");

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_145, LastChild_ReturnsEmptyHandle_145) {

    XMLConstHandle childHandle = handle.LastChild();

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_145, LastChildElement_ReturnsEmptyHandle_145) {

    XMLConstHandle childHandle = handle.LastChildElement("test");

    EXPECT_EQ(childHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_145, PreviousSibling_ReturnsEmptyHandle_145) {

    XMLConstHandle siblingHandle = handle.PreviousSibling();

    EXPECT_EQ(siblingHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_145, PreviousSiblingElement_ReturnsEmptyHandle_145) {

    XMLConstHandle siblingHandle = handle.PreviousSiblingElement("test");

    EXPECT_EQ(siblingHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_145, NextSibling_ReturnsEmptyHandle_145) {

    XMLConstHandle siblingHandle = handle.NextSibling();

    EXPECT_EQ(siblingHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_145, NextSiblingElement_ReturnsEmptyHandle_145) {

    XMLConstHandle siblingHandle = handle.NextSiblingElement("test");

    EXPECT_EQ(siblingHandle.ToNode(), nullptr);

}



TEST_F(XMLConstHandleTest_145, ToNode_ReturnsOriginalNode_145) {

    EXPECT_EQ(handle.ToNode(), node);

}



TEST_F(XMLConstHandleTest_145, ToElement_ReturnsNull_145) {

    EXPECT_EQ(handle.ToElement(), nullptr);

}



TEST_F(XMLConstHandleTest_145, ToText_ReturnsNull_145) {

    EXPECT_EQ(handle.ToText(), nullptr);

}



TEST_F(XMLConstHandleTest_145, ToDeclaration_ReturnsNull_145) {

    EXPECT_EQ(handle.ToDeclaration(), nullptr);

}
