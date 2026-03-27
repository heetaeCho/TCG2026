#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest : public ::testing::Test {

protected:

    virtual void SetUp() {

        doc = new XMLDocument();

        node = new XMLNode(doc);

    }



    virtual void TearDown() {

        delete node;

        delete doc;

    }



    XMLDocument* doc;

    XMLNode* node;

};



TEST_F(XMLNodeTest_50, Parent_ReturnsNullForRootNode_50) {

    EXPECT_EQ(node->Parent(), nullptr);

}



TEST_F(XMLNodeTest_50, Value_DefaultValueIsEmptyString_50) {

    EXPECT_STREQ(node->Value(), "");

}



TEST_F(XMLNodeTest_50, SetValue_ChangesTheValue_50) {

    const char* newValue = "testValue";

    node->SetValue(newValue);

    EXPECT_STREQ(node->Value(), newValue);

}



TEST_F(XMLNodeTest_50, ChildElementCount_DefaultIsZero_50) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_50, ChildElementCount_WithSpecificNameIsZero_50) {

    const char* name = "test";

    EXPECT_EQ(node->ChildElementCount(name), 0);

}



TEST_F(XMLNodeTest_50, FirstChild_ReturnsNullByDefault_50) {

    EXPECT_EQ(node->FirstChild(), nullptr);

}



TEST_F(XMLNodeTest_50, LastChild_ReturnsNullByDefault_50) {

    EXPECT_EQ(node->LastChild(), nullptr);

}



TEST_F(XMLNodeTest_50, PreviousSibling_ReturnsNullByDefault_50) {

    EXPECT_EQ(node->PreviousSibling(), nullptr);

}



TEST_F(XMLNodeTest_50, NextSibling_ReturnsNullByDefault_50) {

    EXPECT_EQ(node->NextSibling(), nullptr);

}



TEST_F(XMLNodeTest_50, NoChildren_ReturnsTrueByDefault_50) {

    EXPECT_TRUE(node->NoChildren());

}



TEST_F(XMLNodeTest_50, GetDocument_ReturnsCorrectDocument_50) {

    EXPECT_EQ(node->GetDocument(), doc);

}



TEST_F(XMLNodeTest_50, GetLineNum_DefaultIsZero_50) {

    EXPECT_EQ(node->GetLineNum(), 0);

}
