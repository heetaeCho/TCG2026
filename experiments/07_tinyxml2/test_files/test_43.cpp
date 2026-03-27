#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_43 : public ::testing::Test {

protected:

    virtual void SetUp() {

        document = new XMLDocument();

        node = new XMLNode(document);

    }



    virtual void TearDown() {

        delete node;

        delete document;

    }



    XMLDocument* document;

    XMLNode* node;

};



TEST_F(XMLNodeTest_43, ToElement_ReturnsNullptr_43) {

    EXPECT_EQ(node->ToElement(), nullptr);

}



TEST_F(XMLNodeTest_43, Value_DefaultIsEmptyString_43) {

    EXPECT_STREQ(node->Value(), "");

}



TEST_F(XMLNodeTest_43, SetValueAndGet_43) {

    node->SetValue("testValue", false);

    EXPECT_STREQ(node->Value(), "testValue");

}



TEST_F(XMLNodeTest_43, ChildElementCount_NoChildren_ReturnsZero_43) {

    EXPECT_EQ(node->ChildElementCount(), 0);

    EXPECT_EQ(node->ChildElementCount("nonExistent"), 0);

}



TEST_F(XMLNodeTest_43, FirstAndLastChildElement_NoChildren_ReturnsNullptr_43) {

    EXPECT_EQ(node->FirstChildElement(), nullptr);

    EXPECT_EQ(node->LastChildElement(), nullptr);

}



TEST_F(XMLNodeTest_43, PreviousSiblingElement_NoSiblings_ReturnsNullptr_43) {

    EXPECT_EQ(node->PreviousSiblingElement(), nullptr);

}



TEST_F(XMLNodeTest_43, NextSiblingElement_NoSiblings_ReturnsNullptr_43) {

    EXPECT_EQ(node->NextSiblingElement(), nullptr);

}



TEST_F(XMLNodeTest_43, InsertEndChildAndGetFirstChild_43) {

    XMLNode* child = new XMLNode(document);

    node->InsertEndChild(child);

    EXPECT_EQ(node->FirstChild(), child);

    delete child;

}



TEST_F(XMLNodeTest_43, DeleteChildren_NoChildren_DoesNothing_43) {

    node->DeleteChildren();

    EXPECT_EQ(node->NoChildren(), true);

}



TEST_F(XMLNodeTest_43, InsertEndChildAndDeleteChild_43) {

    XMLNode* child = new XMLNode(document);

    node->InsertEndChild(child);

    EXPECT_FALSE(node->NoChildren());

    node->DeleteChild(child);

    EXPECT_TRUE(node->NoChildren());

}
