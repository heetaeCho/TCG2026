#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_42 : public ::testing::Test {

protected:

    XMLDocument* doc;

    XMLNode* node;



    void SetUp() override {

        doc = new XMLDocument();

        node = new XMLNode(doc);

    }



    void TearDown() override {

        delete node;

        delete doc;

    }

};



TEST_F(XMLNodeTest_42, GetDocument_ReturnsValidPointer_42) {

    EXPECT_NE(node->GetDocument(), nullptr);

}



TEST_F(XMLNodeTest_42, ChildElementCount_NoChildren_ReturnsZero_42) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_42, ChildElementCount_WithChildren_ReturnsCorrectCount_42) {

    XMLElement* child1 = doc->NewElement("child");

    XMLElement* child2 = doc->NewElement("child");

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    EXPECT_EQ(node->ChildElementCount(), 2);

}



TEST_F(XMLNodeTest_42, ChildElementCount_WithNamedChildren_ReturnsCorrectCount_42) {

    XMLElement* child1 = doc->NewElement("child");

    XMLElement* child2 = doc->NewElement("otherChild");

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    EXPECT_EQ(node->ChildElementCount("child"), 1);

}



TEST_F(XMLNodeTest_42, Value_Default_ReturnsEmptyString_42) {

    EXPECT_STREQ(node->Value(), "");

}



TEST_F(XMLNodeTest_42, SetValue_ChangesValue_Correctly_42) {

    node->SetValue("testValue");

    EXPECT_STREQ(node->Value(), "testValue");

}



TEST_F(XMLNodeTest_42, FirstChildElement_NoChildren_ReturnsNull_42) {

    EXPECT_EQ(node->FirstChildElement(), nullptr);

}



TEST_F(XMLNodeTest_42, LastChildElement_NoChildren_ReturnsNull_42) {

    EXPECT_EQ(node->LastChildElement(), nullptr);

}



TEST_F(XMLNodeTest_42, PreviousSiblingElement_NoSiblings_ReturnsNull_42) {

    EXPECT_EQ(node->PreviousSiblingElement(), nullptr);

}



TEST_F(XMLNodeTest_42, NextSiblingElement_NoSiblings_ReturnsNull_42) {

    EXPECT_EQ(node->NextSiblingElement(), nullptr);

}



TEST_F(XMLNodeTest_42, InsertEndChild_AddsChild_Correctly_42) {

    XMLElement* child = doc->NewElement("child");

    node->InsertEndChild(child);

    EXPECT_EQ(node->FirstChildElement()->Value(), "child");

}



TEST_F(XMLNodeTest_42, InsertFirstChild_AddsChild_Correctly_42) {

    XMLElement* child1 = doc->NewElement("child1");

    XMLElement* child2 = doc->NewElement("child2");

    node->InsertFirstChild(child1);

    node->InsertFirstChild(child2);

    EXPECT_EQ(node->FirstChildElement()->Value(), "child2");

}



TEST_F(XMLNodeTest_42, InsertAfterChild_AddsChild_Correctly_42) {

    XMLElement* child1 = doc->NewElement("child1");

    XMLElement* child2 = doc->NewElement("child2");

    node->InsertEndChild(child1);

    node->InsertAfterChild(child1, child2);

    EXPECT_EQ(node->FirstChildElement()->NextSiblingElement()->Value(), "child2");

}



TEST_F(XMLNodeTest_42, DeleteChildren_RemovesAllChildren_Correctly_42) {

    XMLElement* child1 = doc->NewElement("child1");

    XMLElement* child2 = doc->NewElement("child2");

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    node->DeleteChildren();

    EXPECT_EQ(node->FirstChildElement(), nullptr);

}



TEST_F(XMLNodeTest_42, DeleteChild_RemovesSpecificChild_Correctly_42) {

    XMLElement* child1 = doc->NewElement("child1");

    XMLElement* child2 = doc->NewElement("child2");

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    node->DeleteChild(child1);

    EXPECT_EQ(node->FirstChildElement()->Value(), "child2");

}



TEST_F(XMLNodeTest_42, Parent_Default_ReturnsNull_42) {

    EXPECT_EQ(node->Parent(), nullptr);

}



TEST_F(XMLNodeTest_42, NoChildren_NoChildren_ReturnsTrue_42) {

    EXPECT_TRUE(node->NoChildren());

}



TEST_F(XMLNodeTest_42, FirstChild_NoChildren_ReturnsNull_42) {

    EXPECT_EQ(node->FirstChild(), nullptr);

}



TEST_F(XMLNodeTest_42, LastChild_NoChildren_ReturnsNull_42) {

    EXPECT_EQ(node->LastChild(), nullptr);

}



TEST_F(XMLNodeTest_42, PreviousSibling_NoSiblings_ReturnsNull_42) {

    EXPECT_EQ(node->PreviousSibling(), nullptr);

}



TEST_F(XMLNodeTest_42, NextSibling_NoSiblings_ReturnsNull_42) {

    EXPECT_EQ(node->NextSibling(), nullptr);

}
