#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_278 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument(false, Whitespace::COLLAPSE_WHITESPACE);

        node = new XMLNode(doc);

    }



    void TearDown() override {

        delete node;

        delete doc;

    }



    XMLDocument* doc;

    XMLNode* node;

};



TEST_F(XMLDocumentTest_278, DeleteNode_NormalOperation_278) {

    node->_parent = nullptr; // Simulate node without parent

    EXPECT_NO_THROW(doc->DeleteNode(node));

}



TEST_F(XMLDocumentTest_278, DeleteNode_NodeWithParent_278) {

    XMLNode* parent = new XMLNode(doc);

    node->_parent = parent;

    doc->InsertEndChild(node);



    EXPECT_NO_THROW(doc->DeleteNode(node));



    delete parent; // Cleanup

}



TEST_F(XMLDocumentTest_278, DeleteNode_NodeInMemPool_278) {

    node->_memPool = new MemPool();

    node->_parent = nullptr;



    EXPECT_CALL(*node->_memPool, SetTracked()).Times(1);

    doc->DeleteNode(node);



    delete node->_memPool; // Cleanup

}



TEST_F(XMLDocumentTest_278, DeleteNode_NullPointer_278) {

    XMLNode* nullNode = nullptr;

    EXPECT_THROW(doc->DeleteNode(nullNode), std::exception); // Assuming TIXMLASSERT throws an exception

}



TEST_F(XMLDocumentTest_278, DeleteNode_NodeNotInThisDoc_278) {

    XMLDocument otherDoc(false, Whitespace::COLLAPSE_WHITESPACE);

    node->_document = &otherDoc;



    EXPECT_THROW(doc->DeleteNode(node), std::exception); // Assuming TIXMLASSERT throws an exception



    delete &otherDoc; // Cleanup

}



TEST_F(XMLDocumentTest_278, DeleteNode_MultipleNodes_278) {

    XMLNode* node1 = new XMLNode(doc);

    XMLNode* node2 = new XMLNode(doc);



    doc->InsertEndChild(node1);

    doc->InsertEndChild(node2);



    EXPECT_NO_THROW(doc->DeleteNode(node1));

    EXPECT_NO_THROW(doc->DeleteNode(node2));



    delete node1;

    delete node2;

}
