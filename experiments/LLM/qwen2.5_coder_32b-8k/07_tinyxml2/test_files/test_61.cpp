#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_61 : public ::testing::Test {

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



TEST_F(XMLNodeTest_61, SetAndGetUserData_NormalOperation_61) {

    void* userData = reinterpret_cast<void*>(0x12345678);

    node->SetUserData(userData);

    EXPECT_EQ(node->GetUserData(), userData);

}



TEST_F(XMLNodeTest_61, SetAndGetUserData_NullData_61) {

    void* userData = nullptr;

    node->SetUserData(userData);

    EXPECT_EQ(node->GetUserData(), userData);

}



TEST_F(XMLNodeTest_61, ChildElementCount_DefaultValue_61) {

    EXPECT_EQ(node->ChildElementCount(), 0);

}



TEST_F(XMLNodeTest_61, GetDocument_ReturnsValidPointer_61) {

    EXPECT_NE(node->GetDocument(), nullptr);

}



TEST_F(XMLNodeTest_61, Parent_DefaultIsNullptr_61) {

    EXPECT_EQ(node->Parent(), nullptr);

}



TEST_F(XMLNodeTest_61, NoChildren_ReturnsTrueInitially_61) {

    EXPECT_TRUE(node->NoChildren());

}



TEST_F(XMLNodeTest_61, FirstChild_DefaultIsNullptr_61) {

    EXPECT_EQ(node->FirstChild(), nullptr);

}



TEST_F(XMLNodeTest_61, LastChild_DefaultIsNullptr_61) {

    EXPECT_EQ(node->LastChild(), nullptr);

}



TEST_F(XMLNodeTest_61, PreviousSibling_DefaultIsNullptr_61) {

    EXPECT_EQ(node->PreviousSibling(), nullptr);

}



TEST_F(XMLNodeTest_61, NextSibling_DefaultIsNullptr_61) {

    EXPECT_EQ(node->NextSibling(), nullptr);

}



TEST_F(XMLNodeTest_61, GetLineNum_DefaultIsZero_61) {

    EXPECT_EQ(node->GetLineNum(), 0);

}



TEST_F(XMLNodeTest_61, ToElement_ReturnsNullptr_61) {

    EXPECT_EQ(node->ToElement(), nullptr);

}



TEST_F(XMLNodeTest_61, ToText_ReturnsNullptr_61) {

    EXPECT_EQ(node->ToText(), nullptr);

}



TEST_F(XMLNodeTest_61, ToComment_ReturnsNullptr_61) {

    EXPECT_EQ(node->ToComment(), nullptr);

}



TEST_F(XMLNodeTest_61, ToDocument_ReturnsNullptr_61) {

    EXPECT_EQ(node->ToDocument(), nullptr);

}



TEST_F(XMLNodeTest_61, ToDeclaration_ReturnsNullptr_61) {

    EXPECT_EQ(node->ToDeclaration(), nullptr);

}



TEST_F(XMLNodeTest_61, ToUnknown_ReturnsNullptr_61) {

    EXPECT_EQ(node->ToUnknown(), nullptr);

}
