// TEST_ID: 50
#include <gtest/gtest.h>
#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLNodeParentTest_50 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLNodeParentTest_50, DocumentHasNoParent_50) {
    const XMLNode* docNode = &doc_;
    EXPECT_EQ(docNode->Parent(), nullptr);
}

TEST_F(XMLNodeParentTest_50, NewElementNotInsertedHasNoParent_50) {
    XMLElement* e = doc_.NewElement("e");
    ASSERT_NE(e, nullptr);

    const XMLNode* node = e;
    EXPECT_EQ(node->Parent(), nullptr);
}

TEST_F(XMLNodeParentTest_50, InsertEndChildIntoDocumentSetsParentToDocument_50) {
    XMLElement* root = doc_.NewElement("root");
    ASSERT_NE(root, nullptr);

    XMLNode* inserted = doc_.InsertEndChild(root);
    ASSERT_EQ(inserted, root);

    const XMLNode* childNode = root;
    EXPECT_EQ(childNode->Parent(), static_cast<const XMLNode*>(&doc_));
}

TEST_F(XMLNodeParentTest_50, LinkEndChildIntoElementSetsParentToThatElement_50) {
    XMLElement* root = doc_.NewElement("root");
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(doc_.InsertEndChild(root), root);

    XMLElement* child = doc_.NewElement("child");
    ASSERT_NE(child, nullptr);

    XMLNode* linked = root->LinkEndChild(child);
    ASSERT_EQ(linked, child);

    const XMLNode* childNode = child;
    EXPECT_EQ(childNode->Parent(), static_cast<const XMLNode*>(root));
}

TEST_F(XMLNodeParentTest_50, InsertFirstChildIntoElementSetsParentToThatElement_50) {
    XMLElement* root = doc_.NewElement("root");
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(doc_.InsertEndChild(root), root);

    XMLElement* child = doc_.NewElement("child");
    ASSERT_NE(child, nullptr);

    XMLNode* inserted = root->InsertFirstChild(child);
    ASSERT_EQ(inserted, child);

    const XMLNode* childNode = child;
    EXPECT_EQ(childNode->Parent(), static_cast<const XMLNode*>(root));
}

TEST_F(XMLNodeParentTest_50, InsertAfterChildSetsParentToThatElement_50) {
    XMLElement* root = doc_.NewElement("root");
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(doc_.InsertEndChild(root), root);

    XMLElement* first = doc_.NewElement("first");
    XMLElement* second = doc_.NewElement("second");
    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);

    ASSERT_EQ(root->InsertEndChild(first), first);

    XMLNode* insertedAfter = root->InsertAfterChild(first, second);
    ASSERT_EQ(insertedAfter, second);

    const XMLNode* firstNode = first;
    const XMLNode* secondNode = second;
    EXPECT_EQ(firstNode->Parent(), static_cast<const XMLNode*>(root));
    EXPECT_EQ(secondNode->Parent(), static_cast<const XMLNode*>(root));
}

TEST_F(XMLNodeParentTest_50, NestedInsertionCreatesExpectedParentChain_50) {
    XMLElement* root = doc_.NewElement("root");
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(doc_.InsertEndChild(root), root);

    XMLElement* mid = doc_.NewElement("mid");
    XMLElement* leaf = doc_.NewElement("leaf");
    ASSERT_NE(mid, nullptr);
    ASSERT_NE(leaf, nullptr);

    ASSERT_EQ(root->InsertEndChild(mid), mid);
    ASSERT_EQ(mid->InsertEndChild(leaf), leaf);

    const XMLNode* leafNode = leaf;
    const XMLNode* midNode = mid;

    EXPECT_EQ(leafNode->Parent(), midNode);
    EXPECT_EQ(midNode->Parent(), static_cast<const XMLNode*>(root));
    EXPECT_EQ(static_cast<const XMLNode*>(root)->Parent(), static_cast<const XMLNode*>(&doc_));
}
