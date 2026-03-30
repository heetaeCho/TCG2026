#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLNode* node;

    XMLHandle handle;



    void SetUp() override {

        node = new XMLNode(&doc);

        handle = XMLHandle(node);

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(XMLHandleTest_132, ToDeclaration_ReturnsNullForNonDeclarationNode_132) {

    EXPECT_EQ(handle.ToDeclaration(), nullptr);

}



TEST_F(XMLHandleTest_132, ToDeclaration_ReturnsNonNullForDeclarationNode_132) {

    XMLDeclaration* decl = doc.NewDeclaration();

    handle = XMLHandle(decl);

    EXPECT_NE(handle.ToDeclaration(), nullptr);

}



// Additional tests for boundary conditions and exceptional cases



TEST_F(XMLHandleTest_132, FirstChild_ReturnsNullWhenNoChildren_132) {

    EXPECT_EQ(handle.FirstChild().ToNode(), nullptr);

}



TEST_F(XMLHandleTest_132, LastChild_ReturnsNullWhenNoChildren_132) {

    EXPECT_EQ(handle.LastChild().ToNode(), nullptr);

}



TEST_F(XMLHandleTest_132, PreviousSibling_ReturnsNullWhenNoSiblings_132) {

    EXPECT_EQ(handle.PreviousSibling().ToNode(), nullptr);

}



TEST_F(XMLHandleTest_132, NextSibling_ReturnsNullWhenNoSiblings_132) {

    EXPECT_EQ(handle.NextSibling().ToNode(), nullptr);

}



// Tests for ToElement, ToText, ToUnknown methods can be added similarly

// if there are specific scenarios or boundary conditions to cover.



TEST_F(XMLHandleTest_132, FirstChildElement_ReturnsNullWhenNoElements_132) {

    EXPECT_EQ(handle.FirstChildElement().ToNode(), nullptr);

}



TEST_F(XMLHandleTest_132, LastChildElement_ReturnsNullWhenNoElements_132) {

    EXPECT_EQ(handle.LastChildElement().ToNode(), nullptr);

}



TEST_F(XMLHandleTest_132, PreviousSiblingElement_ReturnsNullWhenNoSiblings_132) {

    EXPECT_EQ(handle.PreviousSiblingElement().ToNode(), nullptr);

}



TEST_F(XMLHandleTest_132, NextSiblingElement_ReturnsNullWhenNoSiblings_132) {

    EXPECT_EQ(handle.NextSiblingElement().ToNode(), nullptr);

}
