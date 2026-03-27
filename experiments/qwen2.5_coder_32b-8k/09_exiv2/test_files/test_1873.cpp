#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMLParserAdapter.hpp"



using namespace ::testing;



class XMLNodeTest_1873 : public Test {

protected:

    XML_NodePtr root;

    std::string nsURI = "http://example.com";

    std::string localName = "element";



    void SetUp() override {

        root.reset(new XML_Node(nullptr, "root", 0));

    }



    void TearDown() override {

        root.reset();

    }

};



TEST_F(XMLNodeTest_1873, IsWhitespaceNode_ReturnsFalseForNonWhitespace_1873) {

    EXPECT_FALSE(root->IsWhitespaceNode());

}



TEST_F(XMLNodeTest_1873, IsLeafContentNode_ReturnsFalseForEmptyNode_1873) {

    EXPECT_FALSE(root->IsLeafContentNode());

}



TEST_F(XMLNodeTest_1873, IsEmptyLeafNode_ReturnsTrueForEmptyNode_1873) {

    EXPECT_TRUE(root->IsEmptyLeafNode());

}



TEST_F(XMLNodeTest_1873, GetAttrValue_ReturnsNullptrForNonExistentAttribute_1873) {

    EXPECT_STREQ(nullptr, root->GetAttrValue("nonexistent"));

}



TEST_F(XMLNodeTest_1873, SetAndGetAttrValue_SuccessfulRoundTrip_1873) {

    root->SetAttrValue("attr", "value");

    EXPECT_STREQ("value", root->GetAttrValue("attr"));

}



TEST_F(XMLNodeTest_1873, GetLeafContentValue_ReturnsEmptyStringForNoContent_1873) {

    EXPECT_EQ("", root->GetLeafContentValue());

}



TEST_F(XMLNodeTest_1873, SetAndGetLeafContentValue_SuccessfulRoundTrip_1873) {

    root->SetLeafContentValue("content");

    EXPECT_STREQ("content", root->GetLeafContentValue());

}



TEST_F(XMLNodeTest_1873, CountNamedElements_ReturnsZeroForNonExistentElement_1873) {

    EXPECT_EQ(0U, root->CountNamedElements(nsURI.c_str(), localName.c_str()));

}



TEST_F(XMLNodeTest_1873, GetNamedElement_ReturnsNullptrForNonExistentElement_1873) {

    EXPECT_EQ(nullptr, root->GetNamedElement(nsURI.c_str(), localName.c_str(), 0));

}



TEST_F(XMLNodeTest_1873, RemoveAttrs_DoesNotCrashWhenNoAttributes_1873) {

    root->RemoveAttrs();

    // No assertion needed, just checking for crash

}



TEST_F(XMLNodeTest_1873, RemoveContent_DoesNotCrashWhenNoContent_1873) {

    root->RemoveContent();

    // No assertion needed, just checking for crash

}



TEST_F(XMLNodeTest_1873, ClearNode_RemovesAllAttributesAndContent_1873) {

    root->SetAttrValue("attr", "value");

    root->SetLeafContentValue("content");

    root->ClearNode();

    EXPECT_STREQ(nullptr, root->GetAttrValue("attr"));

    EXPECT_EQ("", root->GetLeafContentValue());

}
