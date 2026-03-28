#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_269 : public ::testing::Test {

protected:

    XMLDocument* doc;

    XMLNode* node;



    void SetUp() override {

        doc = new XMLDocument();

        node = new XMLNode(doc);

        node->_parent = nullptr;  // Ensure the node is not linked initially

    }



    void TearDown() override {

        delete node;

        delete doc;

    }

};



TEST_F(XMLDocumentTest_269, MarkInUse_RemovesNodeFromUnlinked_269) {

    doc->_unlinked.Push(node);

    EXPECT_EQ(doc->_unlinked.Size(), 1U);



    doc->MarkInUse(node);

    EXPECT_EQ(doc->_unlinked.Size(), 0U);

}



TEST_F(XMLDocumentTest_269, MarkInUse_IgnoresNodeIfAlreadyLinked_269) {

    node->_parent = reinterpret_cast<XMLNode*>(1);  // Simulate the node being linked

    doc->_unlinked.Push(node);



    doc->MarkInUse(node);

    EXPECT_EQ(doc->_unlinked.Size(), 1U);

}



TEST_F(XMLDocumentTest_269, MarkInUse_IgnoresNullNode_269) {

    doc->_unlinked.Push(node);



    doc->MarkInUse(nullptr);

    EXPECT_EQ(doc->_unlinked.Size(), 1U);

}



TEST_F(XMLDocumentTest_269, MarkInUse_NoOpIfNodeNotFound_269) {

    XMLNode* anotherNode = new XMLNode(doc);

    anotherNode->_parent = nullptr;

    doc->_unlinked.Push(anotherNode);



    doc->MarkInUse(node);  // node is not in the unlinked list

    EXPECT_EQ(doc->_unlinked.Size(), 1U);



    delete anotherNode;

}
