#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_62 : public ::testing::Test {

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



TEST_F(XMLNodeTest_62, GetUserData_DefaultValue_62) {

    EXPECT_EQ(node->GetUserData(), nullptr);

}



TEST_F(XMLNodeTest_62, SetAndGetUserData_NormalOperation_62) {

    void* userData = reinterpret_cast<void*>(0x12345678);

    node->SetUserData(userData);

    EXPECT_EQ(node->GetUserData(), userData);

}



TEST_F(XMLNodeTest_62, ChildElementCount_NoChildren_62) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_62, ChildElementCount_WithChildren_62) {

    XMLNode* child1 = new XMLNode(doc);

    XMLNode* child2 = new XMLNode(doc);

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    EXPECT_EQ(node->ChildElementCount(), 2);

    delete child1;

    delete child2;

}



TEST_F(XMLNodeTest_62, ChildElementCount_WithValueFilter_NoMatchingChildren_62) {

    XMLNode* child = new XMLNode(doc);

    node->InsertEndChild(child);

    EXPECT_EQ(node->ChildElementCount("nonexistent"), 0);

    delete child;

}



TEST_F(XMLNodeTest_62, ChildElementCount_WithValueFilter_MatchingChildren_62) {

    XMLElement* child1 = doc->NewElement("test");

    XMLElement* child2 = doc->NewElement("test");

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    EXPECT_EQ(node->ChildElementCount("test"), 2);

    delete child1;

    delete child2;

}



TEST_F(XMLNodeTest_62, FirstChild_NoChildren_62) {

    EXPECT_EQ(node->FirstChild(), nullptr);

}



TEST_F(XMLNodeTest_62, FirstChild_WithChildren_62) {

    XMLNode* child = new XMLNode(doc);

    node->InsertEndChild(child);

    EXPECT_EQ(node->FirstChild(), child);

    delete child;

}



TEST_F(XMLNodeTest_62, LastChild_NoChildren_62) {

    EXPECT_EQ(node->LastChild(), nullptr);

}



TEST_F(XMLNodeTest_62, LastChild_WithChildren_62) {

    XMLNode* child1 = new XMLNode(doc);

    XMLNode* child2 = new XMLNode(doc);

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    EXPECT_EQ(node->LastChild(), child2);

    delete child1;

    delete child2;

}



TEST_F(XMLNodeTest_62, PreviousSibling_NoPreviousSibling_62) {

    EXPECT_EQ(node->PreviousSibling(), nullptr);

}



TEST_F(XMLNodeTest_62, NextSibling_NoNextSibling_62) {

    EXPECT_EQ(node->NextSibling(), nullptr);

}



TEST_F(XMLNodeTest_62, DeleteChildren_NoChildren_62) {

    node->DeleteChildren();

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_62, DeleteChildren_WithChildren_62) {

    XMLNode* child1 = new XMLNode(doc);

    XMLNode* child2 = new XMLNode(doc);

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    node->DeleteChildren();

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_62, DeleteChild_NoSuchChild_62) {

    XMLNode* child = new XMLNode(doc);

    node->DeleteChild(child);

    delete child;

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_62, DeleteChild_ExistingChild_62) {

    XMLNode* child = new XMLNode(doc);

    node->InsertEndChild(child);

    node->DeleteChild(child);

    EXPECT_EQ(node->ChildElementCount(), 0);

}
