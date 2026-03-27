#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLHandleTest_119 : public ::testing::Test {

protected:

    XMLNode* node = nullptr;

    XMLHandle handle;



    void SetUp() override {

        node = new XMLNode();

        handle = XMLHandle(node);

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(XMLHandleTest_119, AssignmentOperatorSameObject_119) {

    XMLHandle anotherHandle(node);

    anotherHandle = handle;

    EXPECT_EQ(anotherHandle.ToNode(), node);

}



TEST_F(XMLHandleTest_119, FirstChildOnEmptyNode_119) {

    XMLHandle firstChild = handle.FirstChild();

    EXPECT_EQ(firstChild.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_119, LastChildOnEmptyNode_119) {

    XMLHandle lastChild = handle.LastChild();

    EXPECT_EQ(lastChild.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_119, PreviousSiblingOnRootNode_119) {

    XMLHandle previousSibling = handle.PreviousSibling();

    EXPECT_EQ(previousSibling.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_119, NextSiblingOnRootNode_119) {

    XMLHandle nextSibling = handle.NextSibling();

    EXPECT_EQ(nextSibling.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_119, FirstChildElementWithNullName_119) {

    XMLHandle firstChildElement = handle.FirstChildElement(nullptr);

    EXPECT_EQ(firstChildElement.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_119, LastChildElementWithNullName_119) {

    XMLHandle lastChildElement = handle.LastChildElement(nullptr);

    EXPECT_EQ(lastChildElement.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_119, PreviousSiblingElementWithNullName_119) {

    XMLHandle previousSiblingElement = handle.PreviousSiblingElement(nullptr);

    EXPECT_EQ(previousSiblingElement.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_119, NextSiblingElementWithNullName_119) {

    XMLHandle nextSiblingElement = handle.NextSiblingElement(nullptr);

    EXPECT_EQ(nextSiblingElement.ToNode(), nullptr);

}



TEST_F(XMLHandleTest_119, ToNodeReturnsOriginalNode_119) {

    EXPECT_EQ(handle.ToNode(), node);

}



TEST_F(XMLHandleTest_119, ToElementOnNonElementNode_119) {

    XMLElement* element = handle.ToElement();

    EXPECT_EQ(element, nullptr);

}



TEST_F(XMLHandleTest_119, ToTextOnNonTextNode_119) {

    XMLText* text = handle.ToText();

    EXPECT_EQ(text, nullptr);

}



TEST_F(XMLHandleTest_119, ToUnknownOnNonUnknownNode_119) {

    XMLUnknown* unknown = handle.ToUnknown();

    EXPECT_EQ(unknown, nullptr);

}



TEST_F(XMLHandleTest_119, ToDeclarationOnNonDeclarationNode_119) {

    XMLDeclaration* declaration = handle.ToDeclaration();

    EXPECT_EQ(declaration, nullptr);

}
