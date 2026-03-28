#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for MarkInUse tests
class MarkInUseTest_269 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test that MarkInUse works with a newly created (unlinked) element
TEST_F(MarkInUseTest_269, MarkInUseOnNewElement_269) {
    XMLElement* elem = doc->NewElement("test");
    // NewElement creates an unlinked node; MarkInUse should not crash
    // and should remove it from the unlinked list
    doc->MarkInUse(elem);
    // After marking in use, we can still delete it properly
    doc->DeleteNode(elem);
}

// Test that MarkInUse works with a newly created comment node
TEST_F(MarkInUseTest_269, MarkInUseOnNewComment_269) {
    XMLComment* comment = doc->NewComment("test comment");
    doc->MarkInUse(comment);
    doc->DeleteNode(comment);
}

// Test that MarkInUse works with a newly created text node
TEST_F(MarkInUseTest_269, MarkInUseOnNewText_269) {
    XMLText* text = doc->NewText("test text");
    doc->MarkInUse(text);
    doc->DeleteNode(text);
}

// Test that MarkInUse works with a newly created declaration node
TEST_F(MarkInUseTest_269, MarkInUseOnNewDeclaration_269) {
    XMLDeclaration* decl = doc->NewDeclaration("xml version=\"1.0\"");
    doc->MarkInUse(decl);
    doc->DeleteNode(decl);
}

// Test that MarkInUse works with a newly created unknown node
TEST_F(MarkInUseTest_269, MarkInUseOnNewUnknown_269) {
    XMLUnknown* unknown = doc->NewUnknown("unknown");
    doc->MarkInUse(unknown);
    doc->DeleteNode(unknown);
}

// Test that calling MarkInUse multiple times on the same node doesn't crash
// (second call should be a no-op since it's already removed from unlinked list)
TEST_F(MarkInUseTest_269, MarkInUseCalledTwice_269) {
    XMLElement* elem = doc->NewElement("test");
    doc->MarkInUse(elem);
    // Calling again should not crash - node is no longer in unlinked list
    doc->MarkInUse(elem);
    doc->DeleteNode(elem);
}

// Test MarkInUse with multiple unlinked nodes
TEST_F(MarkInUseTest_269, MarkInUseMultipleUnlinkedNodes_269) {
    XMLElement* elem1 = doc->NewElement("first");
    XMLElement* elem2 = doc->NewElement("second");
    XMLElement* elem3 = doc->NewElement("third");

    // Mark the middle one in use
    doc->MarkInUse(elem2);
    
    // Mark the first one
    doc->MarkInUse(elem1);
    
    // Mark the last one
    doc->MarkInUse(elem3);

    doc->DeleteNode(elem1);
    doc->DeleteNode(elem2);
    doc->DeleteNode(elem3);
}

// Test that MarkInUse works correctly in conjunction with InsertEndChild
// After inserting a child, it's linked. MarkInUse should handle nodes
// that aren't in the unlinked list gracefully (though typically called on unlinked nodes).
TEST_F(MarkInUseTest_269, MarkInUseAfterInsertEndChild_269) {
    XMLElement* elem = doc->NewElement("child");
    // Insert into document - this links the node
    doc->InsertEndChild(elem);
    // The node is now linked (_parent != 0), so we shouldn't call MarkInUse on it
    // (it would violate the assertion that _parent == 0)
    // This test verifies the normal workflow: create, then either MarkInUse or InsertEndChild
}

// Test MarkInUse preserves the node for later use
TEST_F(MarkInUseTest_269, MarkInUsePreservesNodeForLaterInsertion_269) {
    XMLElement* elem = doc->NewElement("deferred");
    elem->SetAttribute("key", "value");
    
    // Mark in use before clearing
    doc->MarkInUse(elem);
    
    // Now insert it into the document
    doc->InsertEndChild(elem);
    
    // Verify the element is properly in the document
    XMLElement* root = doc->FirstChildElement("deferred");
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("key"), "value");
}

// Test that after MarkInUse, Clear() on document still works correctly
TEST_F(MarkInUseTest_269, ClearAfterMarkInUse_269) {
    XMLElement* elem = doc->NewElement("test");
    doc->MarkInUse(elem);
    doc->InsertEndChild(elem);
    
    // Clear should clean up everything
    doc->Clear();
    
    EXPECT_TRUE(doc->NoChildren());
}

// Test MarkInUse with a node created from parsing
TEST_F(MarkInUseTest_269, MarkInUseWithParsedDocument_269) {
    const char* xml = "<root><child/></root>";
    doc->Parse(xml);
    ASSERT_FALSE(doc->Error());
    
    // Create a new unlinked element
    XMLElement* newElem = doc->NewElement("newnode");
    doc->MarkInUse(newElem);
    
    // Insert into the parsed tree
    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);
    root->InsertEndChild(newElem);
    
    // Verify it's there
    XMLElement* found = root->FirstChildElement("newnode");
    ASSERT_NE(found, nullptr);
}

// Test MarkInUse with many unlinked nodes to exercise the DynArray
TEST_F(MarkInUseTest_269, MarkInUseManyNodes_269) {
    const int NUM_NODES = 20;
    XMLElement* elements[NUM_NODES];
    
    for (int i = 0; i < NUM_NODES; ++i) {
        elements[i] = doc->NewElement("elem");
    }
    
    // Mark them in use in reverse order
    for (int i = NUM_NODES - 1; i >= 0; --i) {
        doc->MarkInUse(elements[i]);
    }
    
    // Clean up by inserting and then clearing
    for (int i = 0; i < NUM_NODES; ++i) {
        doc->InsertEndChild(elements[i]);
    }
    doc->Clear();
}

// Test that MarkInUse on a node that was never in the unlinked list
// (already removed) doesn't crash - it just does nothing
TEST_F(MarkInUseTest_269, MarkInUseOnAlreadyMarkedNode_269) {
    XMLElement* elem = doc->NewElement("test");
    
    // First call removes from unlinked list
    doc->MarkInUse(elem);
    
    // Second call - node not in unlinked list anymore, should be safe
    doc->MarkInUse(elem);
    
    // Third call for good measure
    doc->MarkInUse(elem);
    
    doc->DeleteNode(elem);
}

// Test MarkInUse with different node types mixed
TEST_F(MarkInUseTest_269, MarkInUseMixedNodeTypes_269) {
    XMLElement* elem = doc->NewElement("element");
    XMLComment* comment = doc->NewComment("comment");
    XMLText* text = doc->NewText("text");
    XMLDeclaration* decl = doc->NewDeclaration();
    XMLUnknown* unknown = doc->NewUnknown("unknown");
    
    // Mark all in use in arbitrary order
    doc->MarkInUse(text);
    doc->MarkInUse(elem);
    doc->MarkInUse(unknown);
    doc->MarkInUse(decl);
    doc->MarkInUse(comment);
    
    // Clean up
    doc->DeleteNode(elem);
    doc->DeleteNode(comment);
    doc->DeleteNode(text);
    doc->DeleteNode(decl);
    doc->DeleteNode(unknown);
}

// Test that document properly handles DeepCopy after MarkInUse
TEST_F(MarkInUseTest_269, DeepCopyAfterMarkInUse_269) {
    doc->Parse("<root><child attr=\"val\"/></root>");
    ASSERT_FALSE(doc->Error());
    
    XMLElement* newElem = doc->NewElement("extra");
    doc->MarkInUse(newElem);
    doc->RootElement()->InsertEndChild(newElem);
    
    XMLDocument target;
    doc->DeepCopy(&target);
    
    ASSERT_NE(target.RootElement(), nullptr);
    XMLElement* extraInCopy = target.RootElement()->FirstChildElement("extra");
    ASSERT_NE(extraInCopy, nullptr);
}
