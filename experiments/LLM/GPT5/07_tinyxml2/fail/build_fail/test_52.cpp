// File: ./TestProjects/tinyxml2/test_xmlnode_firstchild_52.cpp

#include <gtest/gtest.h>
#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLNodeFirstChildTest_52 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* MakeRoot() {
        XMLElement* root = doc.NewElement("root");
        ASSERT_NE(root, nullptr);
        XMLNode* inserted = doc.InsertEndChild(root);
        EXPECT_EQ(inserted, root);
        return root;
    }
};

TEST_F(XMLNodeFirstChildTest_52, NoChildrenReturnsNull_52) {
    XMLElement* root = MakeRoot();

    const XMLNode* croot = root;
    EXPECT_EQ(croot->FirstChild(), nullptr);
}

TEST_F(XMLNodeFirstChildTest_52, LinkEndChildMakesFirstChildNonNullAndEqualToInserted_52) {
    XMLElement* root = MakeRoot();

    XMLElement* child = doc.NewElement("child");
    ASSERT_NE(child, nullptr);

    XMLNode* linked = root->LinkEndChild(child);
    EXPECT_EQ(linked, child);

    const XMLNode* croot = root;
    EXPECT_EQ(croot->FirstChild(), child);
}

TEST_F(XMLNodeFirstChildTest_52, InsertFirstChildUpdatesFirstChildToNewNode_52) {
    XMLElement* root = MakeRoot();

    XMLElement* childA = doc.NewElement("A");
    XMLElement* childB = doc.NewElement("B");
    ASSERT_NE(childA, nullptr);
    ASSERT_NE(childB, nullptr);

    // Establish an initial first child.
    ASSERT_EQ(root->LinkEndChild(childA), childA);
    ASSERT_EQ(root->FirstChild(), childA);

    // Insert a new node at the front; FirstChild() should now reflect it.
    XMLNode* inserted = root->InsertFirstChild(childB);
    EXPECT_EQ(inserted, childB);

    const XMLNode* croot = root;
    EXPECT_EQ(croot->FirstChild(), childB);
}

TEST_F(XMLNodeFirstChildTest_52, DeleteChildrenResetsFirstChildToNull_52) {
    XMLElement* root = MakeRoot();

    XMLElement* child = doc.NewElement("child");
    ASSERT_NE(child, nullptr);
    ASSERT_EQ(root->LinkEndChild(child), child);
    ASSERT_NE(root->FirstChild(), nullptr);

    root->DeleteChildren();

    const XMLNode* croot = root;
    EXPECT_EQ(croot->FirstChild(), nullptr);
}
