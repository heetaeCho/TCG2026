#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_187 : public ::testing::Test {

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



TEST_F(XMLNodeTest_187, DeleteChildren_NoChildren_187) {

    // No children to delete

    node->DeleteChildren();

    EXPECT_EQ(node->FirstChild(), nullptr);

    EXPECT_EQ(node->LastChild(), nullptr);

}



TEST_F(XMLNodeTest_187, DeleteChildren_OneChild_187) {

    XMLNode* child = new XMLNode(doc);

    node->InsertEndChild(child);

    node->DeleteChildren();

    EXPECT_EQ(node->FirstChild(), nullptr);

    EXPECT_EQ(node->LastChild(), nullptr);

}



TEST_F(XMLNodeTest_187, DeleteChildren_MultipleChildren_187) {

    XMLNode* child1 = new XMLNode(doc);

    XMLNode* child2 = new XMLNode(doc);

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    node->DeleteChildren();

    EXPECT_EQ(node->FirstChild(), nullptr);

    EXPECT_EQ(node->LastChild(), nullptr);

}



TEST_F(XMLNodeTest_187, DeleteChildren_ChildrenWithSubchildren_187) {

    XMLNode* child = new XMLNode(doc);

    XMLNode* subchild = new XMLNode(doc);

    child->InsertEndChild(subchild);

    node->InsertEndChild(child);

    node->DeleteChildren();

    EXPECT_EQ(node->FirstChild(), nullptr);

    EXPECT_EQ(node->LastChild(), nullptr);

}
