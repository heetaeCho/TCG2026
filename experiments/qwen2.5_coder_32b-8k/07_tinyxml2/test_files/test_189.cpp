#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_189 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLNode* parent;

    XMLNode* child;



    void SetUp() override {

        parent = new XMLNode(&doc);

        child = new XMLNode(&doc);

    }



    void TearDown() override {

        delete parent;

        delete child;

    }

};



TEST_F(XMLNodeTest_189, InsertEndChild_ValidNode_189) {

    EXPECT_EQ(parent->InsertEndChild(child), child);

    EXPECT_EQ(child->_parent, parent);

    EXPECT_EQ(parent->_firstChild, child);

    EXPECT_EQ(parent->_lastChild, child);

}



TEST_F(XMLNodeTest_189, InsertEndChild_SecondNode_189) {

    XMLNode* secondChild = new XMLNode(&doc);

    parent->InsertEndChild(child);

    parent->InsertEndChild(secondChild);



    EXPECT_EQ(parent->_firstChild, child);

    EXPECT_EQ(parent->_lastChild, secondChild);

    EXPECT_EQ(child->_next, secondChild);

    EXPECT_EQ(secondChild->_prev, child);

    delete secondChild;

}



TEST_F(XMLNodeTest_189, InsertEndChild_SameDocumentRequired_189) {

    XMLDocument anotherDoc;

    XMLNode* invalidChild = new XMLNode(&anotherDoc);



    EXPECT_EQ(parent->InsertEndChild(invalidChild), nullptr);

    delete invalidChild;

}



TEST_F(XMLNodeTest_189, InsertEndChild_NullPointer_189) {

    EXPECT_EQ(parent->InsertEndChild(nullptr), nullptr);

}
