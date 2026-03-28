#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_51 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLNode* node;



    void SetUp() override {

        node = new XMLNode(&doc);

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(XMLNodeTest_51, NoChildrenInitially_51) {

    EXPECT_TRUE(node->NoChildren());

}



TEST_F(XMLNodeTest_51, ChildElementCountZeroInitially_51) {

    EXPECT_EQ(0, node->ChildElementCount());

}



TEST_F(XMLNodeTest_51, ValueEmptyStringInitially_51) {

    EXPECT_STREQ("", node->Value());

}



TEST_F(XMLNodeTest_51, SetValueAndGetCorrectly_51) {

    const char* testValue = "testValue";

    node->SetValue(testValue);

    EXPECT_STREQ(testValue, node->Value());

}



TEST_F(XMLNodeTest_51, InsertEndChildIncreasesChildCount_51) {

    XMLNode* child = new XMLNode(&doc);

    node->InsertEndChild(child);

    EXPECT_FALSE(node->NoChildren());

    EXPECT_EQ(1, node->ChildElementCount());

}



TEST_F(XMLNodeTest_51, DeleteChildrenSetsNoChildren_51) {

    XMLNode* child = new XMLNode(&doc);

    node->InsertEndChild(child);

    node->DeleteChildren();

    EXPECT_TRUE(node->NoChildren());

    EXPECT_EQ(0, node->ChildElementCount());

}



TEST_F(XMLNodeTest_51, DeleteSpecificChildReducesChildCount_51) {

    XMLNode* child = new XMLNode(&doc);

    node->InsertEndChild(child);

    node->DeleteChild(child);

    EXPECT_TRUE(node->NoChildren());

    EXPECT_EQ(0, node->ChildElementCount());

}



TEST_F(XMLNodeTest_51, InsertFirstChildWorksCorrectly_51) {

    XMLNode* child = new XMLNode(&doc);

    node->InsertFirstChild(child);

    EXPECT_FALSE(node->NoChildren());

    EXPECT_EQ(1, node->ChildElementCount());

    EXPECT_EQ(child, node->FirstChild());

}



TEST_F(XMLNodeTest_51, InsertAfterChildWorksCorrectly_51) {

    XMLNode* child1 = new XMLNode(&doc);

    XMLNode* child2 = new XMLNode(&doc);

    node->InsertEndChild(child1);

    node->InsertAfterChild(child1, child2);

    EXPECT_EQ(2, node->ChildElementCount());

    EXPECT_EQ(child2, child1->NextSibling());

}



TEST_F(XMLNodeTest_51, DeepCloneCreatesIndependentCopy_51) {

    const char* testValue = "testValue";

    node->SetValue(testValue);



    XMLDocument targetDoc;

    XMLNode* clone = node->DeepClone(&targetDoc);

    EXPECT_STREQ(testValue, clone->Value());

    EXPECT_EQ(node->GetDocument(), &doc);

    EXPECT_EQ(clone->GetDocument(), &targetDoc);

}



TEST_F(XMLNodeTest_51, ShallowCloneCreatesIndependentCopy_51) {

    const char* testValue = "testValue";

    node->SetValue(testValue);



    XMLDocument targetDoc;

    XMLNode* clone = node->ShallowClone(&targetDoc)->ToNode();

    EXPECT_STREQ(testValue, clone->Value());

    EXPECT_EQ(node->GetDocument(), &doc);

    EXPECT_EQ(clone->GetDocument(), &targetDoc);

}



TEST_F(XMLNodeTest_51, GetLineNumReturnsDefaultZero_51) {

    EXPECT_EQ(0, node->GetLineNum());

}
