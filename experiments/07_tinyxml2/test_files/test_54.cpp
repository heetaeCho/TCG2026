#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_54 : public ::testing::Test {

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



TEST_F(XMLNodeTest_54, LastChild_ReturnsNullForNoChildren_54) {

    EXPECT_EQ(node->LastChild(), nullptr);

}



TEST_F(XMLNodeTest_54, Value_DefaultIsEmptyString_54) {

    EXPECT_STREQ(node->Value(), "");

}



TEST_F(XMLNodeTest_54, SetValue_ChangesValue_54) {

    node->SetValue("test");

    EXPECT_STREQ(node->Value(), "test");

}



TEST_F(XMLNodeTest_54, ChildElementCount_DefaultIsZero_54) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_54, DeleteChildren_NoChildrenDoesNothing_54) {

    node->DeleteChildren();

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_54, InsertEndChild_AddsChild_54) {

    XMLNode* child = new XMLNode(doc);

    node->InsertEndChild(child);

    EXPECT_NE(node->LastChild(), nullptr);

}



TEST_F(XMLNodeTest_54, DeleteChild_RemovesChild_54) {

    XMLNode* child = new XMLNode(doc);

    node->InsertEndChild(child);

    node->DeleteChild(child);

    EXPECT_EQ(node->ChildElementCount(), 0);

}
