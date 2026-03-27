#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest : public ::testing::Test {

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



TEST_F(XMLNodeTest_49, GetLineNum_DefaultValue_49) {

    EXPECT_EQ(node->GetLineNum(), 0);

}



TEST_F(XMLNodeTest_49, GetValue_DefaultValue_49) {

    EXPECT_STREQ(node->Value(), "");

}



TEST_F(XMLNodeTest_49, SetValue_ChangesValue_49) {

    node->SetValue("test", false);

    EXPECT_STREQ(node->Value(), "test");

}



TEST_F(XMLNodeTest_49, ChildElementCount_NoChildren_ReturnsZero_49) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_49, FirstChild_NoChildren_ReturnsNull_49) {

    EXPECT_EQ(node->FirstChild(), nullptr);

}



TEST_F(XMLNodeTest_49, LastChild_NoChildren_ReturnsNull_49) {

    EXPECT_EQ(node->LastChild(), nullptr);

}



TEST_F(XMLNodeTest_49, PreviousSibling_NoSiblings_ReturnsNull_49) {

    EXPECT_EQ(node->PreviousSibling(), nullptr);

}



TEST_F(XMLNodeTest_49, NextSibling_NoSiblings_ReturnsNull_49) {

    EXPECT_EQ(node->NextSibling(), nullptr);

}



TEST_F(XMLNodeTest_49, InsertEndChild_AddsChild_49) {

    XMLNode* child = new XMLNode(doc);

    node->InsertEndChild(child);

    EXPECT_EQ(node->FirstChild(), child);

    EXPECT_EQ(node->LastChild(), child);

    EXPECT_EQ(node->ChildElementCount(), 1);

}



TEST_F(XMLNodeTest_49, InsertFirstChild_AddsChild_49) {

    XMLNode* child = new XMLNode(doc);

    node->InsertFirstChild(child);

    EXPECT_EQ(node->FirstChild(), child);

    EXPECT_EQ(node->LastChild(), child);

    EXPECT_EQ(node->ChildElementCount(), 1);

}



TEST_F(XMLNodeTest_49, InsertAfterChild_AddsChild_49) {

    XMLNode* firstChild = new XMLNode(doc);

    node->InsertEndChild(firstChild);

    XMLNode* secondChild = new XMLNode(doc);

    node->InsertAfterChild(firstChild, secondChild);

    EXPECT_EQ(node->FirstChild(), firstChild);

    EXPECT_EQ(node->LastChild(), secondChild);

    EXPECT_EQ(node->ChildElementCount(), 2);

}



TEST_F(XMLNodeTest_49, DeleteChildren_RemovesAllChildren_49) {

    XMLNode* child1 = new XMLNode(doc);

    XMLNode* child2 = new XMLNode(doc);

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    node->DeleteChildren();

    EXPECT_EQ(node->FirstChild(), nullptr);

    EXPECT_EQ(node->LastChild(), nullptr);

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_49, DeleteChild_RemovesSpecificChild_49) {

    XMLNode* child1 = new XMLNode(doc);

    XMLNode* child2 = new XMLNode(doc);

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    node->DeleteChild(child1);

    EXPECT_EQ(node->FirstChild(), child2);

    EXPECT_EQ(node->LastChild(), child2);

    EXPECT_EQ(node->ChildElementCount(), 1);

}
