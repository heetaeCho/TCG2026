#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_191 : public ::testing::Test {

protected:

    void SetUp() override {

        document = new XMLDocument();

        parent = new XMLNode(document);

        child1 = new XMLNode(document);

        child2 = new XMLNode(document);

        child3 = new XMLNode(document);



        parent->InsertEndChild(child1);

        parent->InsertEndChild(child2);

    }



    void TearDown() override {

        delete document;

    }



    XMLDocument* document;

    XMLNode* parent;

    XMLNode* child1;

    XMLNode* child2;

    XMLNode* child3;

};



TEST_F(XMLNodeTest_191, InsertAfterChild_NormalOperation_191) {

    XMLNode* result = parent->InsertAfterChild(child1, child3);

    EXPECT_EQ(result, child3);

    EXPECT_EQ(child1->_next, child3);

    EXPECT_EQ(child3->_prev, child1);

    EXPECT_EQ(child3->_next, child2);

    EXPECT_EQ(child2->_prev, child3);

}



TEST_F(XMLNodeTest_191, InsertAfterChild_InsertAtEnd_191) {

    XMLNode* result = parent->InsertAfterChild(child2, child3);

    EXPECT_EQ(result, child3);

    EXPECT_EQ(child2->_next, child3);

    EXPECT_EQ(child3->_prev, child2);

    EXPECT_EQ(child3->_next, nullptr);

}



TEST_F(XMLNodeTest_191, InsertAfterChild_InsertSameNode_191) {

    XMLNode* result = parent->InsertAfterChild(child1, child1);

    EXPECT_EQ(result, child1);

    EXPECT_EQ(child1->_prev, nullptr);

    EXPECT_EQ(child1->_next, child2);

}



TEST_F(XMLNodeTest_191, InsertAfterChild_DifferentDocument_191) {

    XMLDocument* otherDoc = new XMLDocument();

    XMLNode* otherNode = new XMLNode(otherDoc);



    XMLNode* result = parent->InsertAfterChild(child1, otherNode);

    EXPECT_EQ(result, nullptr);

    delete otherDoc;

}



TEST_F(XMLNodeTest_191, InsertAfterChild_AfterNull_191) {

    XMLNode* result = parent->InsertAfterChild(nullptr, child3);

    EXPECT_EQ(result, nullptr);

}



TEST_F(XMLNodeTest_191, InsertAfterChild_AddNull_191) {

    XMLNode* result = parent->InsertAfterChild(child1, nullptr);

    EXPECT_EQ(result, nullptr);

}
