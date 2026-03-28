#include <gtest/gtest.h>

#include <tinyxml2.h>



using namespace tinyxml2;



class XMLNodeTest_188 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLNode* parent;

    XMLNode* child;



    void SetUp() override {

        parent = new XMLNode(&doc);

        child = new XMLNode(&doc);

        parent->InsertEndChild(child);

    }



    void TearDown() override {

        delete parent;

    }

};



TEST_F(XMLNodeTest_188, DeleteChild_RemovesChildFromParent_188) {

    EXPECT_EQ(parent->FirstChild(), child);

    parent->DeleteChild(child);

    EXPECT_EQ(parent->FirstChild(), nullptr);

}



TEST_F(XMLNodeTest_188, DeleteChild_SetsChildPointersToNull_188) {

    parent->DeleteChild(child);

    EXPECT_EQ(child->_prev, nullptr);

    EXPECT_EQ(child->_next, nullptr);

    EXPECT_EQ(child->_parent, nullptr);

}



TEST_F(XMLNodeTest_188, DeleteChild_NonExistingChildDoesNothing_188) {

    XMLNode* nonExistingChild = new XMLNode(&doc);

    parent->DeleteChild(nonExistingChild);

    EXPECT_EQ(parent->FirstChild(), child); // Original child should still be there

    delete nonExistingChild;

}



TEST_F(XMLNodeTest_188, DeleteChild_NonMatchingDocumentThrowsAssertion_188) {

    XMLDocument otherDoc;

    XMLNode* wrongDocumentChild = new XMLNode(&otherDoc);

    EXPECT_DEATH(parent->DeleteChild(wrongDocumentChild), "TIXMLASSERT");

    delete wrongDocumentChild;

}



TEST_F(XMLNodeTest_188, DeleteChild_WrongParentThrowsAssertion_188) {

    XMLNode otherParent(&doc);

    EXPECT_DEATH(otherParent.DeleteChild(child), "TIXMLASSERT");

}
