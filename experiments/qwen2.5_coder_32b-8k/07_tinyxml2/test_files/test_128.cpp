#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest_128 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Setup a mock node for testing.

        _mockNode = new XMLNode();

        _handle = XMLHandle(_mockNode);

    }



    virtual void TearDown() {

        delete _mockNode;

    }



    XMLNode* _mockNode;

    XMLHandle _handle;

};



TEST_F(XMLHandleTest_128, ToNode_ReturnsCorrectPointer_128) {

    EXPECT_EQ(_mockNode, _handle.ToNode());

}



TEST_F(XMLHandleTest_128, FirstChild_ReturnsNullForNoChildren_128) {

    XMLHandle childHandle = _handle.FirstChild();

    EXPECT_EQ(nullptr, childHandle.ToNode());

}



TEST_F(XMLHandleTest_128, LastChild_ReturnsNullForNoChildren_128) {

    XMLHandle childHandle = _handle.LastChild();

    EXPECT_EQ(nullptr, childHandle.ToNode());

}



TEST_F(XMLHandleTest_128, PreviousSibling_ReturnsNullAsSingleNode_128) {

    XMLHandle siblingHandle = _handle.PreviousSibling();

    EXPECT_EQ(nullptr, siblingHandle.ToNode());

}



TEST_F(XMLHandleTest_128, NextSibling_ReturnsNullAsSingleNode_128) {

    XMLHandle siblingHandle = _handle.NextSibling();

    EXPECT_EQ(nullptr, siblingHandle.ToNode());

}



TEST_F(XMLHandleTest_128, FirstChildElement_ReturnsNullForNoChildren_128) {

    XMLHandle childHandle = _handle.FirstChildElement("dummy");

    EXPECT_EQ(nullptr, childHandle.ToNode());

}



TEST_F(XMLHandleTest_128, LastChildElement_ReturnsNullForNoChildren_128) {

    XMLHandle childHandle = _handle.LastChildElement("dummy");

    EXPECT_EQ(nullptr, childHandle.ToNode());

}



TEST_F(XMLHandleTest_128, PreviousSiblingElement_ReturnsNullAsSingleNode_128) {

    XMLHandle siblingHandle = _handle.PreviousSiblingElement("dummy");

    EXPECT_EQ(nullptr, siblingHandle.ToNode());

}



TEST_F(XMLHandleTest_128, NextSiblingElement_ReturnsNullAsSingleNode_128) {

    XMLHandle siblingHandle = _handle.NextSiblingElement("dummy");

    EXPECT_EQ(nullptr, siblingHandle.ToNode());

}



TEST_F(XMLHandleTest_128, ToElement_ReturnsNullForNonElement_128) {

    XMLElement* element = _handle.ToElement();

    EXPECT_EQ(nullptr, element);

}



TEST_F(XMLHandleTest_128, ToText_ReturnsNullForNonText_128) {

    XMLText* text = _handle.ToText();

    EXPECT_EQ(nullptr, text);

}



TEST_F(XMLHandleTest_128, ToUnknown_ReturnsNullForNonUnknown_128) {

    XMLUnknown* unknown = _handle.ToUnknown();

    EXPECT_EQ(nullptr, unknown);

}



TEST_F(XMLHandleTest_128, ToDeclaration_ReturnsNullForNonDeclaration_128) {

    XMLDeclaration* declaration = _handle.ToDeclaration();

    EXPECT_EQ(nullptr, declaration);

}
