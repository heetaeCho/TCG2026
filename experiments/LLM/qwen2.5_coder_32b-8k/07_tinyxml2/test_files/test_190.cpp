#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_190 : public ::testing::Test {

protected:

    void SetUp() override {

        document = new XMLDocument();

        parent = new XMLNode(document);

    }



    void TearDown() override {

        delete parent;

        delete document;

    }



    XMLDocument* document;

    XMLNode* parent;

};



TEST_F(XMLNodeTest_190, InsertFirstChild_ReturnsInsertedNode_190) {

    XMLNode* child = new XMLNode(document);

    EXPECT_EQ(parent->InsertFirstChild(child), child);

    delete child;

}



TEST_F(XMLNodeTest_190, InsertFirstChild_SetsChildParent_190) {

    XMLNode* child = new XMLNode(document);

    parent->InsertFirstChild(child);

    EXPECT_EQ(child->_parent, parent);

    delete child;

}



TEST_F(XMLNodeTest_190, InsertFirstChild_MakesChildFirstAndLast_WhenNoChildren_190) {

    XMLNode* child = new XMLNode(document);

    parent->InsertFirstChild(child);

    EXPECT_EQ(parent->_firstChild, child);

    EXPECT_EQ(parent->_lastChild, child);

    delete child;

}



TEST_F(XMLNodeTest_190, InsertFirstChild_PreservesExistingFirstAndLast_WhenChildrenExist_190) {

    XMLNode* firstChild = new XMLNode(document);

    XMLNode* secondChild = new XMLNode(document);

    parent->InsertFirstChild(firstChild);

    parent->InsertFirstChild(secondChild);



    EXPECT_EQ(parent->_firstChild, secondChild);

    EXPECT_EQ(parent->_lastChild, firstChild);



    delete secondChild;

    delete firstChild;

}



TEST_F(XMLNodeTest_190, InsertFirstChild_SetsLinksCorrectly_WhenChildrenExist_190) {

    XMLNode* firstChild = new XMLNode(document);

    XMLNode* secondChild = new XMLNode(document);

    parent->InsertFirstChild(firstChild);

    parent->InsertFirstChild(secondChild);



    EXPECT_EQ(secondChild->_next, firstChild);

    EXPECT_EQ(firstChild->_prev, secondChild);



    delete secondChild;

    delete firstChild;

}



TEST_F(XMLNodeTest_190, InsertFirstChild_ReturnsNull_WhenDocumentMismatch_190) {

    XMLDocument* otherDocument = new XMLDocument();

    XMLNode* child = new XMLNode(otherDocument);

    EXPECT_EQ(parent->InsertFirstChild(child), nullptr);



    delete otherDocument;

    delete child;

}



TEST_F(XMLNodeTest_190, InsertFirstChild_AssertsOnNullPointer_WhenAddingNull_190) {

    EXPECT_DEATH(parent->InsertFirstChild(nullptr), "TIXMLASSERT\\(addThis\\)");

}
