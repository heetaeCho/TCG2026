#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_58 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument();

        root = new XMLElement("root");

        node1 = new XMLElement("child1");

        node2 = new XMLElement("child2");



        doc->InsertEndChild(root);

        root->InsertEndChild(node1);

        root->InsertEndChild(node2);

    }



    void TearDown() override {

        delete doc;

    }



    XMLDocument* doc;

    XMLElement* root;

    XMLElement* node1;

    XMLElement* node2;

};



TEST_F(XMLNodeTest_58, NextSiblingReturnsNextSibling_58) {

    EXPECT_EQ(node2, node1->NextSibling());

}



TEST_F(XMLNodeTest_58, NextSiblingOfLastChildIsNull_58) {

    EXPECT_EQ(nullptr, node2->NextSibling());

}



TEST_F(XMLNodeTest_58, ChildElementCountCountsChildren_58) {

    EXPECT_EQ(2, root->ChildElementCount());

}



TEST_F(XMLNodeTest_58, ChildElementCountWithSpecificValueCountsMatchingChildren_58) {

    EXPECT_EQ(1, root->ChildElementCount("child1"));

}



TEST_F(XMLNodeTest_58, ChildElementCountWithNonExistentValueReturnsZero_58) {

    EXPECT_EQ(0, root->ChildElementCount("nonexistent"));

}



TEST_F(XMLNodeTest_58, ValueReturnsCorrectValue_58) {

    EXPECT_STREQ("root", root->Value());

}



TEST_F(XMLNodeTest_58, SetValueChangesValue_58) {

    node1->SetValue("newchild1");

    EXPECT_STREQ("newchild1", node1->Value());

}



TEST_F(XMLNodeTest_58, FirstChildReturnsFirstChild_58) {

    EXPECT_EQ(node1, root->FirstChild());

}



TEST_F(XMLNodeTest_58, LastChildReturnsLastChild_58) {

    EXPECT_EQ(node2, root->LastChild());

}



TEST_F(XMLNodeTest_58, PreviousSiblingOfFirstElementIsNull_58) {

    EXPECT_EQ(nullptr, node1->PreviousSibling());

}



TEST_F(XMLNodeTest_58, PreviousSiblingReturnsPreviousSibling_58) {

    EXPECT_EQ(node1, node2->PreviousSibling());

}



TEST_F(XMLNodeTest_58, DeleteChildRemovesChild_58) {

    root->DeleteChild(node1);

    EXPECT_EQ(1, root->ChildElementCount());

}



TEST_F(XMLNodeTest_58, DeleteChildrenRemovesAllChildren_58) {

    root->DeleteChildren();

    EXPECT_EQ(0, root->ChildElementCount());

}
