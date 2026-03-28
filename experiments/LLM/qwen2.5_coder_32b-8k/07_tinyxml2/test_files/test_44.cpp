#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_44 : public ::testing::Test {

protected:

    virtual void SetUp() override {

        doc = new XMLDocument();

        node = new XMLNode(doc);

    }



    virtual void TearDown() override {

        delete node;

        delete doc;

    }



    XMLDocument* doc;

    XMLNode* node;

};



TEST_F(XMLNodeTest_44, ToText_ReturnsNullptr_44) {

    EXPECT_EQ(node->ToText(), nullptr);

}



TEST_F(XMLNodeTest_44, ChildElementCount_Default_ReturnsZero_44) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_44, Value_Default_ReturnsEmptyString_44) {

    EXPECT_STREQ(node->Value(), "");

}



TEST_F(XMLNodeTest_44, SetValueAndGet_ReturnsSetValue_44) {

    const char* testValue = "testValue";

    node->SetValue(testValue);

    EXPECT_STREQ(node->Value(), testValue);

}



TEST_F(XMLNodeTest_44, InsertEndChildAndGet_ReturnsInsertedNode_44) {

    XMLNode* childNode = new XMLNode(doc);

    node->InsertEndChild(childNode);

    EXPECT_EQ(node->FirstChild(), childNode);

}



TEST_F(XMLNodeTest_44, DeleteChildren_AfterInsert_NoChildrenLeft_44) {

    XMLNode* childNode = new XMLNode(doc);

    node->InsertEndChild(childNode);

    node->DeleteChildren();

    EXPECT_EQ(node->FirstChild(), nullptr);

}



TEST_F(XMLNodeTest_44, DeleteChild_AfterInsert_ChildDeleted_44) {

    XMLNode* childNode = new XMLNode(doc);

    node->InsertEndChild(childNode);

    node->DeleteChild(childNode);

    EXPECT_EQ(node->FirstChild(), nullptr);

}
