// File: ./TestProjects/tinyxml2/tests/xml_document_delete_node_test_278.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLDocumentDeleteNodeTest_278 : public ::testing::Test {
protected:
    // Use typical tinyxml2 constructor signature (processEntities, whitespaceMode).
    XMLDocumentDeleteNodeTest_278()
        : doc(true, XMLDocument::PRESERVE_WHITESPACE),
          otherDoc(true, XMLDocument::PRESERVE_WHITESPACE) {}

    XMLDocument doc;
    XMLDocument otherDoc;
};

TEST_F(XMLDocumentDeleteNodeTest_278, DeleteChild_RemovesFromParent_278) {
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);

    XMLElement* child = doc.NewElement("child");
    ASSERT_NE(child, nullptr);

    // Build tree: doc -> root -> child
    ASSERT_NE(doc.InsertEndChild(root), nullptr);
    ASSERT_NE(root->InsertEndChild(child), nullptr);

    ASSERT_EQ(doc.RootElement(), root);
    ASSERT_EQ(root->FirstChildElement("child"), child);
    ASSERT_EQ(root->ChildElementCount(), 1);

    // Act
    doc.DeleteNode(child);

    // Verify observable effects through public API: child removed from root.
    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->FirstChildElement("child"), nullptr);
    EXPECT_EQ(root->ChildElementCount(), 0);

    // Root should remain.
    EXPECT_EQ(doc.RootElement(), root);
}

TEST_F(XMLDocumentDeleteNodeTest_278, DeleteRoot_RemovesFromDocument_278) {
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);

    ASSERT_NE(doc.InsertEndChild(root), nullptr);
    ASSERT_EQ(doc.RootElement(), root);
    ASSERT_EQ(doc.FirstChildElement("root"), root);

    // Act
    doc.DeleteNode(root);

    // Verify document no longer has a root/children.
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_EQ(doc.FirstChild(), nullptr);
    EXPECT_EQ(doc.FirstChildElement("root"), nullptr);
}

TEST_F(XMLDocumentDeleteNodeTest_278, DeleteUnlinkedNode_DoesNotChangeDocumentTree_278) {
    // Document initially has no children.
    ASSERT_EQ(doc.FirstChild(), nullptr);
    ASSERT_EQ(doc.RootElement(), nullptr);

    // Create an unlinked node (no parent).
    XMLElement* orphan = doc.NewElement("orphan");
    ASSERT_NE(orphan, nullptr);
    ASSERT_EQ(orphan->Parent(), nullptr);

    // Act: deleting an unlinked node should be safe and should not affect doc tree.
    doc.DeleteNode(orphan);

    // Verify doc tree still empty.
    EXPECT_EQ(doc.FirstChild(), nullptr);
    EXPECT_EQ(doc.RootElement(), nullptr);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNullptr_TriggersAssert_278) {
    // The implementation asserts on null.
    EXPECT_DEATH({ doc.DeleteNode(nullptr); }, ".*");
}

TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeFromDifferentDocument_TriggersAssert_278) {
    // Node belongs to doc, but we try to delete it via otherDoc; implementation asserts node->_document == this.
    XMLElement* foreign = doc.NewElement("foreign");
    ASSERT_NE(foreign, nullptr);

    EXPECT_DEATH({ otherDoc.DeleteNode(foreign); }, ".*");
}
#endif
