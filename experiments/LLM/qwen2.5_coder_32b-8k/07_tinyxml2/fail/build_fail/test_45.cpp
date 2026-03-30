#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest : public ::testing::Test {

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



TEST_F(XMLNodeTest_45, ToComment_ReturnsNullptr_45) {

    EXPECT_EQ(node->ToComment(), nullptr);

}



TEST_F(XMLNodeTest_45, ChildElementCount_Default_ReturnsZero_45) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_45, ChildElementCount_WithSpecificValue_ReturnsZero_45) {

    EXPECT_EQ(node->ChildElementCount("someValue"), 0);

}



TEST_F(XMLNodeTest_45, Value_Default_ReturnsEmptyString_45) {

    EXPECT_STREQ(node->Value(), "");

}



TEST_F(XMLNodeTest_45, SetValue_ChangesValue_CanBeRetrieved_45) {

    node->SetValue("newValue", false);

    EXPECT_STREQ(node->Value(), "newValue");

}



TEST_F(XMLNodeTest_45, FirstChildElement_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->FirstChildElement(), nullptr);

}



TEST_F(XMLNodeTest_45, LastChildElement_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->LastChildElement(), nullptr);

}



TEST_F(XMLNodeTest_45, PreviousSiblingElement_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->PreviousSiblingElement(), nullptr);

}



TEST_F(XMLNodeTest_45, NextSiblingElement_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->NextSiblingElement(), nullptr);

}



TEST_F(XMLNodeTest_45, InsertEndChild_ValidNode_ReturnsInsertedNode_45) {

    XMLNode* child = new XMLNode(&doc);

    EXPECT_EQ(node->InsertEndChild(child), child);

}



TEST_F(XMLNodeTest_45, InsertFirstChild_ValidNode_ReturnsInsertedNode_45) {

    XMLNode* child = new XMLNode(&doc);

    EXPECT_EQ(node->InsertFirstChild(child), child);

}



TEST_F(XMLNodeTest_45, InsertAfterChild_ValidNodes_ReturnsInsertedNode_45) {

    XMLNode* firstChild = new XMLNode(&doc);

    XMLNode* secondChild = new XMLNode(&doc);

    node->InsertEndChild(firstChild);

    EXPECT_EQ(node->InsertAfterChild(firstChild, secondChild), secondChild);

}



TEST_F(XMLNodeTest_45, DeleteChildren_NoChildren_DoesNotCrash_45) {

    node->DeleteChildren();  // No children to delete

}



TEST_F(XMLNodeTest_45, DeleteChild_ValidNode_DeletesNode_45) {

    XMLNode* child = new XMLNode(&doc);

    node->InsertEndChild(child);

    node->DeleteChild(child);

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_45, ShallowClone_ReturnsNonNullPointer_45) {

    XMLNode* clone = node->ShallowClone(&doc);

    EXPECT_NE(clone, nullptr);

    delete clone;

}



TEST_F(XMLNodeTest_45, DeepClone_ReturnsNonNullPointer_45) {

    XMLNode* clone = node->DeepClone(&doc);

    EXPECT_NE(clone, nullptr);

    delete clone;

}



TEST_F(XMLNodeTest_45, ShallowEqual_SameNode_ReturnsTrue_45) {

    EXPECT_TRUE(node->ShallowEqual(node));

}



TEST_F(XMLNodeTest_45, Accept_NullVisitor_ReturnsFalse_45) {

    XMLVisitor* visitor = nullptr;

    EXPECT_FALSE(node->Accept(visitor));

}



TEST_F(XMLNodeTest_45, GetDocument_Default_ReturnsCorrectDocument_45) {

    EXPECT_EQ(node->GetDocument(), &doc);

}



TEST_F(XMLNodeTest_45, ToElement_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->ToElement(), nullptr);

}



TEST_F(XMLNodeTest_45, ToText_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->ToText(), nullptr);

}



TEST_F(XMLNodeTest_45, ToDocument_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->ToDocument(), nullptr);

}



TEST_F(XMLNodeTest_45, ToDeclaration_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->ToDeclaration(), nullptr);

}



TEST_F(XMLNodeTest_45, ToUnknown_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->ToUnknown(), nullptr);

}



TEST_F(XMLNodeTest_45, GetLineNum_Default_ReturnsZero_45) {

    EXPECT_EQ(node->GetLineNum(), 0);

}



TEST_F(XMLNodeTest_45, Parent_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->Parent(), nullptr);

}



TEST_F(XMLNodeTest_45, NoChildren_Default_ReturnsTrue_45) {

    EXPECT_TRUE(node->NoChildren());

}



TEST_F(XMLNodeTest_45, FirstChild_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->FirstChild(), nullptr);

}



TEST_F(XMLNodeTest_45, LastChild_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->LastChild(), nullptr);

}



TEST_F(XMLNodeTest_45, PreviousSibling_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->PreviousSibling(), nullptr);

}



TEST_F(XMLNodeTest_45, NextSibling_Default_ReturnsNullptr_45) {

    EXPECT_EQ(node->NextSibling(), nullptr);

}



TEST_F(XMLNodeTest_45, LinkEndChild_ValidNode_ReturnsInsertedNode_45) {

    XMLNode* child = new XMLNode(&doc);

    EXPECT_EQ(node->LinkEndChild(child), child);

}



TEST_F(XMLNodeTest_45, SetUserData_AnyData_CanBeRetrieved_45) {

    void* data = reinterpret_cast<void*>(0x1234);

    node->SetUserData(data);

    EXPECT_EQ(node->GetUserData(), data);

}
