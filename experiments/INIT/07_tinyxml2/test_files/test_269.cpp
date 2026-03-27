// File: ./TestProjects/tinyxml2/tests/XMLDocumentMarkInUseTest_269.cpp

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLDocumentMarkInUseTest_269 : public ::testing::Test {
protected:
    XMLDocument doc;
};

TEST_F(XMLDocumentMarkInUseTest_269, MarkInUse_WithUnlinkedNode_DoesNotCrash_269) {
    XMLNode* node = doc.NewElement("e");  // Newly created nodes are typically unlinked.
    ASSERT_NE(node, nullptr);

    // Observable behavior: should not crash for a valid, unlinked node.
    doc.MarkInUse(node);
}

TEST_F(XMLDocumentMarkInUseTest_269, MarkInUse_CalledTwiceOnSameUnlinkedNode_DoesNotCrash_269) {
    XMLNode* node = doc.NewElement("e");
    ASSERT_NE(node, nullptr);

    // Observable behavior: repeated calls should not crash.
    doc.MarkInUse(node);
    doc.MarkInUse(node);
}

TEST_F(XMLDocumentMarkInUseTest_269, MarkInUse_WithNullNode_DeathInDebug_269) {
#ifndef NDEBUG
    // MarkInUse asserts on null input in debug builds.
    EXPECT_DEATH_IF_SUPPORTED(doc.MarkInUse(nullptr), "");
#else
    // In release builds asserts are commonly compiled out; verify it doesn't crash.
    doc.MarkInUse(nullptr);
#endif
}

TEST_F(XMLDocumentMarkInUseTest_269, MarkInUse_WithLinkedNode_DeathInDebug_269) {
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);

    // Link the node so it has a parent.
    ASSERT_NE(doc.InsertEndChild(root), nullptr);

#ifndef NDEBUG
    // MarkInUse asserts that the node has no parent in debug builds.
    EXPECT_DEATH_IF_SUPPORTED(doc.MarkInUse(root), "");
#else
    // In release builds asserts are commonly compiled out; verify it doesn't crash.
    doc.MarkInUse(root);
#endif
}
