#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_56 : public ::testing::Test {

protected:

    virtual void SetUp() {

        doc = new XMLDocument();

        root = doc->NewElement("Root");

        child1 = doc->NewElement("Child1");

        child2 = doc->NewElement("Child2");



        doc->InsertFirstChild(root);

        root->InsertEndChild(child1);

        root->InsertEndChild(child2);

    }



    virtual void TearDown() {

        delete doc;

    }



    XMLDocument* doc;

    XMLElement* root;

    XMLElement* child1;

    XMLElement* child2;

};



TEST_F(XMLNodeTest_56, PreviousSibling_ReturnsPreviousSibling_56) {

    EXPECT_EQ(child2->PreviousSibling(), child1);

}



TEST_F(XMLNodeTest_56, PreviousSibling_RootHasNoPreviousSibling_56) {

    EXPECT_EQ(root->PreviousSibling(), nullptr);

}



TEST_F(XMLNodeTest_56, ChildElementCount_ReturnsCorrectCountWithName_56) {

    EXPECT_EQ(root->ChildElementCount("Child1"), 1);

    EXPECT_EQ(root->ChildElementCount("Child2"), 1);

    EXPECT_EQ(root->ChildElementCount("NonExistent"), 0);

}



TEST_F(XMLNodeTest_56, ChildElementCount_ReturnsCorrectTotalCount_56) {

    EXPECT_EQ(root->ChildElementCount(), 2);

}



TEST_F(XMLNodeTest_56, Value_ReturnsSetValue_56) {

    root->SetValue("NewRoot");

    EXPECT_STREQ(root->Value(), "NewRoot");

}



TEST_F(XMLNodeTest_56, FirstChild_ReturnsFirstChild_56) {

    EXPECT_EQ(root->FirstChild(), child1);

}



TEST_F(XMLNodeTest_56, LastChild_ReturnsLastChild_56) {

    EXPECT_EQ(root->LastChild(), child2);

}



TEST_F(XMLNodeTest_56, DeleteChildren_RemovesAllChildren_56) {

    root->DeleteChildren();

    EXPECT_TRUE(root->NoChildren());

}



TEST_F(XMLNodeTest_56, DeleteChild_RemovesSpecificChild_56) {

    root->DeleteChild(child1);

    EXPECT_EQ(root->FirstChild(), child2);

    EXPECT_TRUE(child1->Parent() == nullptr);

}



TEST_F(XMLNodeTest_56, InsertEndChild_AddsToEnd_56) {

    XMLElement* newChild = doc->NewElement("NewChild");

    root->InsertEndChild(newChild);

    EXPECT_EQ(root->LastChild(), newChild);

}



TEST_F(XMLNodeTest_56, InsertFirstChild_AddsToFront_56) {

    XMLElement* newChild = doc->NewElement("NewChild");

    root->InsertFirstChild(newChild);

    EXPECT_EQ(root->FirstChild(), newChild);

}



TEST_F(XMLNodeTest_56, InsertAfterChild_InsertsAfterSpecifiedChild_56) {

    XMLElement* newChild = doc->NewElement("NewChild");

    root->InsertAfterChild(child1, newChild);

    EXPECT_EQ(child1->NextSibling(), newChild);

}
