#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_181 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLNode* node;



    void SetUp() override {

        node = new XMLNode(&doc);

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(XMLNodeTest_181, ChildElementCount_ReturnsZero_181) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_181, Value_DefaultConstructor_ReturnsEmptyString_181) {

    EXPECT_STREQ(node->Value(), "");

}



TEST_F(XMLNodeTest_181, SetValue_ChangesValue_181) {

    node->SetValue("test", false);

    EXPECT_STREQ(node->Value(), "test");

}



TEST_F(XMLNodeTest_181, DeleteChildren_NoChildren_181) {

    node->DeleteChildren();

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_181, InsertEndChild_AddsChild_181) {

    XMLNode* child = new XMLNode(&doc);

    node->InsertEndChild(child);

    EXPECT_EQ(node->ChildElementCount(), 1);

    delete child;

}



TEST_F(XMLNodeTest_181, InsertFirstChild_AddsChild_181) {

    XMLNode* child = new XMLNode(&doc);

    node->InsertFirstChild(child);

    EXPECT_EQ(node->ChildElementCount(), 1);

    delete child;

}



TEST_F(XMLNodeTest_181, DeleteChild_RemovesChild_181) {

    XMLNode* child = new XMLNode(&doc);

    node->InsertEndChild(child);

    node->DeleteChild(child);

    EXPECT_EQ(node->ChildElementCount(), 0);

    delete child;

}



TEST_F(XMLNodeTest_181, FirstChild_ReturnsNullptr_NoChildren_181) {

    EXPECT_EQ(node->FirstChild(), nullptr);

}



TEST_F(XMLNodeTest_181, LastChild_ReturnsNullptr_NoChildren_181) {

    EXPECT_EQ(node->LastChild(), nullptr);

}
