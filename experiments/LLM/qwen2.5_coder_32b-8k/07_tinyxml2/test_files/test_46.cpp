#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_46 : public ::testing::Test {

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



TEST_F(XMLNodeTest_46, ToDocumentReturnsNonNullPointer_46) {

    EXPECT_NE(node->ToDocument(), nullptr);

}



TEST_F(XMLNodeTest_46, ValueInitiallyEmptyString_46) {

    EXPECT_STREQ(node->Value(), "");

}



TEST_F(XMLNodeTest_46, SetValueChangesValue_46) {

    node->SetValue("test", false);

    EXPECT_STREQ(node->Value(), "test");

}



TEST_F(XMLNodeTest_46, ChildElementCountInitiallyZero_46) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_46, InsertEndChildIncreasesChildCount_46) {

    XMLNode* child = new XMLNode(&doc);

    node->InsertEndChild(child);

    EXPECT_EQ(node->ChildElementCount(), 1);

    delete child;

}



TEST_F(XMLNodeTest_46, DeleteChildrenResetsChildCount_46) {

    XMLNode* child = new XMLNode(&doc);

    node->InsertEndChild(child);

    node->DeleteChildren();

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_46, InsertFirstChildWorksCorrectly_46) {

    XMLNode* child1 = new XMLNode(&doc);

    XMLNode* child2 = new XMLNode(&doc);

    node->InsertFirstChild(child1);

    node->InsertFirstChild(child2);

    EXPECT_EQ(node->ChildElementCount(), 2);

    EXPECT_EQ(node->FirstChild(), child2);

    delete child1;

    delete child2;

}



TEST_F(XMLNodeTest_46, InsertAfterChildWorksCorrectly_46) {

    XMLNode* child1 = new XMLNode(&doc);

    XMLNode* child2 = new XMLNode(&doc);

    XMLNode* child3 = new XMLNode(&doc);

    node->InsertEndChild(child1);

    node->InsertAfterChild(child1, child2);

    node->InsertAfterChild(child1, child3);

    EXPECT_EQ(node->ChildElementCount(), 3);

    EXPECT_EQ(child1->NextSibling(), child3);

    EXPECT_EQ(child3->NextSibling(), child2);

    delete child1;

    delete child2;

    delete child3;

}



TEST_F(XMLNodeTest_46, DeleteChildReducesChildCount_46) {

    XMLNode* child = new XMLNode(&doc);

    node->InsertEndChild(child);

    node->DeleteChild(child);

    EXPECT_EQ(node->ChildElementCount(), 0);

}
