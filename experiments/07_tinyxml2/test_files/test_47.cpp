#include <gtest/gtest.h>

#include <tinyxml2.h>



using namespace tinyxml2;



class XMLNodeTest : public ::testing::Test {

protected:

    XMLDocument document;

    XMLNode* node;



    void SetUp() override {

        node = new XMLNode(&document);

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(XMLNodeTest_47, ToDeclaration_ReturnsNullptr_47) {

    EXPECT_EQ(node->ToDeclaration(), nullptr);

}



TEST_F(XMLNodeTest_47, ChildElementCount_DefaultZero_47) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_47, ChildElementCount_WithSpecificValueZero_47) {

    EXPECT_EQ(node->ChildElementCount("some_value"), 0);

}



TEST_F(XMLNodeTest_47, Value_DefaultEmptyString_47) {

    EXPECT_STREQ(node->Value(), "");

}



TEST_F(XMLNodeTest_47, SetValue_ChangesValue_47) {

    node->SetValue("test_value", false);

    EXPECT_STREQ(node->Value(), "test_value");

}



TEST_F(XMLNodeTest_47, GetDocument_ReturnsCorrectDocument_47) {

    EXPECT_EQ(node->GetDocument(), &document);

}



TEST_F(XMLNodeTest_47, ShallowClone_ReturnsNullptr_Default_47) {

    EXPECT_EQ(node->ShallowClone(&document), nullptr);

}



TEST_F(XMLNodeTest_47, DeepClone_ReturnsNullptr_Default_47) {

    EXPECT_EQ(node->DeepClone(&document), nullptr);

}



TEST_F(XMLNodeTest_47, DeleteChildren_NoChildrenInitially_47) {

    node->DeleteChildren();

    EXPECT_TRUE(node->NoChildren());

}



TEST_F(XMLNodeTest_47, InsertEndChild_ReturnsInsertedNode_47) {

    XMLNode* child = new XMLNode(&document);

    EXPECT_EQ(node->InsertEndChild(child), child);

}



TEST_F(XMLNodeTest_47, InsertFirstChild_ReturnsInsertedNode_47) {

    XMLNode* child = new XMLNode(&document);

    EXPECT_EQ(node->InsertFirstChild(child), child);

}



TEST_F(XMLNodeTest_47, InsertAfterChild_ReturnsInsertedNode_47) {

    XMLNode* firstChild = new XMLNode(&document);

    node->InsertEndChild(firstChild);

    XMLNode* secondChild = new XMLNode(&document);

    EXPECT_EQ(node->InsertAfterChild(firstChild, secondChild), secondChild);

}



TEST_F(XMLNodeTest_47, DeleteChild_RemovesChild_47) {

    XMLNode* child = new XMLNode(&document);

    node->InsertEndChild(child);

    node->DeleteChild(child);

    EXPECT_TRUE(node->NoChildren());

}



TEST_F(XMLNodeTest_47, GetLineNum_ReturnsZero_Default_47) {

    EXPECT_EQ(node->GetLineNum(), 0);

}



TEST_F(XMLNodeTest_47, Parent_ReturnsNullptr_Default_47) {

    EXPECT_EQ(node->Parent(), nullptr);

}



TEST_F(XMLNodeTest_47, NoChildren_ReturnsTrue_Default_47) {

    EXPECT_TRUE(node->NoChildren());

}



TEST_F(XMLNodeTest_47, FirstChild_ReturnsNullptr_NoChildren_47) {

    EXPECT_EQ(node->FirstChild(), nullptr);

}



TEST_F(XMLNodeTest_47, LastChild_ReturnsNullptr_NoChildren_47) {

    EXPECT_EQ(node->LastChild(), nullptr);

}



TEST_F(XMLNodeTest_47, PreviousSibling_ReturnsNullptr_Default_47) {

    EXPECT_EQ(node->PreviousSibling(), nullptr);

}



TEST_F(XMLNodeTest_47, NextSibling_ReturnsNullptr_Default_47) {

    EXPECT_EQ(node->NextSibling(), nullptr);

}



TEST_F(XMLNodeTest_47, LinkEndChild_ReturnsInsertedNode_47) {

    XMLNode* child = new XMLNode(&document);

    EXPECT_EQ(node->LinkEndChild(child), child);

}



TEST_F(XMLNodeTest_47, SetUserData_SetsCorrectData_47) {

    void* data = reinterpret_cast<void*>(0x12345678);

    node->SetUserData(data);

    EXPECT_EQ(node->GetUserData(), data);

}
