#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_48 : public ::testing::Test {

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



TEST_F(XMLNodeTest_48, Value_DefaultValue_ReturnsEmptyString_48) {

    EXPECT_STREQ("", node->Value());

}



TEST_F(XMLNodeTest_48, SetValue_ChangesValue_CanRetrieveSameValue_48) {

    const char* testValue = "testValue";

    node->SetValue(testValue, false);

    EXPECT_STREQ(testValue, node->Value());

}



TEST_F(XMLNodeTest_48, ChildElementCount_NoChildren_ReturnsZero_48) {

    EXPECT_EQ(0, node->ChildElementCount());

}



TEST_F(XMLNodeTest_48, InsertEndChild_AddsChild_ChildElementCountIncreases_48) {

    XMLNode* child = new XMLNode(doc);

    node->InsertEndChild(child);

    EXPECT_EQ(1, node->ChildElementCount());

}



TEST_F(XMLNodeTest_48, DeleteChildren_RemovesAllChildren_CountReturnsZero_48) {

    XMLNode* child1 = new XMLNode(doc);

    XMLNode* child2 = new XMLNode(doc);

    node->InsertEndChild(child1);

    node->InsertEndChild(child2);

    node->DeleteChildren();

    EXPECT_EQ(0, node->ChildElementCount());

}



TEST_F(XMLNodeTest_48, DeleteChild_RemovesSpecificChild_CountDecreases_48) {

    XMLNode* child = new XMLNode(doc);

    node->InsertEndChild(child);

    node->DeleteChild(child);

    EXPECT_EQ(0, node->ChildElementCount());

}



TEST_F(XMLNodeTest_48, ToUnknown_Default_ReturnsNullptr_48) {

    EXPECT_EQ(nullptr, node->ToUnknown());

}



TEST_F(XMLNodeTest_48, GetDocument_ReturnsValidPointer_48) {

    EXPECT_EQ(doc, node->GetDocument());

}
