// File: ./TestProjects/tinyxml2/tests/xmlnode_nochildren_test_51.cpp

#include <gtest/gtest.h>
#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLNodeNoChildrenTest_51 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLNodeNoChildrenTest_51, NewDocumentHasNoChildren_51) {
    // A newly constructed XMLDocument should have no children.
    EXPECT_TRUE(doc_.NoChildren());
}

TEST_F(XMLNodeNoChildrenTest_51, DocumentNoChildrenBecomesFalseAfterInsertEndChild_51) {
    // After inserting a child into the document, it should report having children.
    XMLElement* root = doc_.NewElement("root");
    ASSERT_NE(root, nullptr);

    XMLNode* inserted = doc_.InsertEndChild(root);
    ASSERT_EQ(inserted, root);

    EXPECT_FALSE(doc_.NoChildren());
}

TEST_F(XMLNodeNoChildrenTest_51, DocumentNoChildrenReturnsTrueAfterDeleteChildren_51) {
    // Insert a child, verify, then delete children and verify again.
    XMLElement* root = doc_.NewElement("root");
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(doc_.InsertEndChild(root), root);
    ASSERT_FALSE(doc_.NoChildren());

    doc_.DeleteChildren();
    EXPECT_TRUE(doc_.NoChildren());
}

TEST_F(XMLNodeNoChildrenTest_51, ElementNoChildrenTransitionsWithChildAddAndDelete_51) {
    // Verify NoChildren behavior on a non-document node as well.
    XMLElement* parent = doc_.NewElement("parent");
    ASSERT_NE(parent, nullptr);
    ASSERT_EQ(doc_.InsertEndChild(parent), parent);
    EXPECT_TRUE(parent->NoChildren()); // parent starts with no children

    XMLElement* child = doc_.NewElement("child");
    ASSERT_NE(child, nullptr);
    ASSERT_EQ(parent->InsertEndChild(child), child);

    EXPECT_FALSE(parent->NoChildren());

    parent->DeleteChildren();
    EXPECT_TRUE(parent->NoChildren());
}

TEST_F(XMLNodeNoChildrenTest_51, InsertEndChildWithNullDoesNotCreateChildren_51) {
    // If inserting nullptr is handled as a no-op, the document should remain without children.
    // (This test verifies observable behavior without assuming internal implementation details.)
    EXPECT_TRUE(doc_.NoChildren());

    XMLNode* inserted = doc_.InsertEndChild(nullptr);
    EXPECT_EQ(inserted, nullptr);

    EXPECT_TRUE(doc_.NoChildren());
}
