#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_52 : public ::testing::Test {

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



TEST_F(XMLNodeTest_52, FirstChild_ReturnsNull_WhenNoChildren_52) {

    EXPECT_EQ(node->FirstChild(), nullptr);

}



TEST_F(XMLNodeTest_52, Value_DefaultIsEmptyString_52) {

    EXPECT_STREQ(node->Value(), "");

}



TEST_F(XMLNodeTest_52, SetValue_ChangesValue_52) {

    node->SetValue("test", false);

    EXPECT_STREQ(node->Value(), "test");

}



TEST_F(XMLNodeTest_52, ChildElementCount_ReturnsZero_WhenNoChildren_52) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_52, InsertEndChild_IncreasesChildCount_52) {

    XMLNode* child = new XMLNode(doc);

    node->InsertEndChild(child);

    EXPECT_EQ(node->ChildElementCount(), 1);

}



TEST_F(XMLNodeTest_52, DeleteChildren_DecreasesChildCountToZero_52) {

    XMLNode* child = new XMLNode(doc);

    node->InsertEndChild(child);

    node->DeleteChildren();

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_52, DeleteChild_RemovesSpecificChild_52) {

    XMLNode* child1 = new XMLNode(doc);

    XMLNode* child2 = new XMLNode(doc);

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    node->DeleteChild(child1);

    EXPECT_EQ(node->ChildElementCount(), 1);

}



TEST_F(XMLNodeTest_52, GetDocument_ReturnsCorrectDocument_52) {

    EXPECT_EQ(node->GetDocument(), doc);

}
