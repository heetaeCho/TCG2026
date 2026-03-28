#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLDocument::DeleteNode tests
class XMLDocumentDeleteNodeTest_278 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test: DeleteNode removes a child element from the document
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeRemovesChildElement_278) {
    doc.Parse("<root><child1/><child2/></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    
    doc.DeleteNode(child1);
    
    XMLElement* found = root->FirstChildElement("child1");
    EXPECT_EQ(found, nullptr);
    
    // child2 should still exist
    XMLElement* child2 = root->FirstChildElement("child2");
    EXPECT_NE(child2, nullptr);
}

// Test: DeleteNode removes the root element
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeRemovesRootElement_278) {
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    doc.DeleteNode(root);
    
    EXPECT_EQ(doc.RootElement(), nullptr);
}

// Test: DeleteNode on a deeply nested element
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeRemovesDeeplyNestedElement_278) {
    doc.Parse("<root><a><b><c/></b></a></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    XMLElement* a = root->FirstChildElement("a");
    XMLElement* b = a->FirstChildElement("b");
    XMLElement* c = b->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    
    doc.DeleteNode(c);
    
    EXPECT_EQ(b->FirstChildElement("c"), nullptr);
    EXPECT_TRUE(b->NoChildren());
}

// Test: DeleteNode on an element with children deletes them too
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeRemovesSubtree_278) {
    doc.Parse("<root><parent><child1/><child2/><child3/></parent></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    XMLElement* parent = root->FirstChildElement("parent");
    ASSERT_NE(parent, nullptr);
    
    doc.DeleteNode(parent);
    
    EXPECT_EQ(root->FirstChildElement("parent"), nullptr);
    EXPECT_TRUE(root->NoChildren());
}

// Test: DeleteNode on a newly created unlinked node (no parent)
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeOnUnlinkedNewElement_278) {
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(elem, nullptr);
    
    // elem has no parent, so it should go through the else branch
    doc.DeleteNode(elem);
    
    // No crash means success; the node was properly deleted
    SUCCEED();
}

// Test: DeleteNode on a comment node
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeRemovesComment_278) {
    doc.Parse("<root><!-- my comment --><child/></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    
    // The first child should be the comment
    const XMLComment* comment = firstChild->ToComment();
    ASSERT_NE(comment, nullptr);
    
    doc.DeleteNode(const_cast<XMLNode*>(firstChild));
    
    // After deletion, first child should be the element "child"
    XMLElement* child = root->FirstChildElement("child");
    EXPECT_NE(child, nullptr);
    EXPECT_EQ(root->FirstChild(), child);
}

// Test: DeleteNode on a text node
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeRemovesTextNode_278) {
    doc.Parse("<root>Hello World</root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);
    ASSERT_NE(textNode->ToText(), nullptr);
    
    doc.DeleteNode(textNode);
    
    EXPECT_TRUE(root->NoChildren());
}

// Test: DeleteNode on a newly created unlinked comment (no parent)
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeOnUnlinkedNewComment_278) {
    XMLComment* comment = doc.NewComment("test comment");
    ASSERT_NE(comment, nullptr);
    
    doc.DeleteNode(comment);
    SUCCEED();
}

// Test: DeleteNode on a newly created unlinked text (no parent)
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeOnUnlinkedNewText_278) {
    XMLText* text = doc.NewText("test text");
    ASSERT_NE(text, nullptr);
    
    doc.DeleteNode(text);
    SUCCEED();
}

// Test: DeleteNode on a newly created unlinked declaration (no parent)
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeOnUnlinkedNewDeclaration_278) {
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
    
    doc.DeleteNode(decl);
    SUCCEED();
}

// Test: DeleteNode on a newly created unlinked unknown (no parent)
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeOnUnlinkedNewUnknown_278) {
    XMLUnknown* unknown = doc.NewUnknown("something");
    ASSERT_NE(unknown, nullptr);
    
    doc.DeleteNode(unknown);
    SUCCEED();
}

// Test: DeleteNode middle child preserves siblings
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeMiddleChildPreservesSiblings_278) {
    doc.Parse("<root><a/><b/><c/></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    
    doc.DeleteNode(b);
    
    XMLElement* a = root->FirstChildElement("a");
    XMLElement* c = root->FirstChildElement("c");
    EXPECT_NE(a, nullptr);
    EXPECT_NE(c, nullptr);
    EXPECT_EQ(root->FirstChildElement("b"), nullptr);
    
    // a's next sibling element should be c
    EXPECT_EQ(a->NextSiblingElement(), c);
}

// Test: DeleteNode first child preserves remaining children
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeFirstChildPreservesRemaining_278) {
    doc.Parse("<root><a/><b/><c/></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    
    doc.DeleteNode(a);
    
    EXPECT_EQ(root->FirstChildElement("a"), nullptr);
    XMLElement* b = root->FirstChildElement("b");
    XMLElement* c = root->FirstChildElement("c");
    EXPECT_NE(b, nullptr);
    EXPECT_NE(c, nullptr);
    EXPECT_EQ(root->FirstChildElement(), b);
}

// Test: DeleteNode last child preserves remaining children
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeLastChildPreservesRemaining_278) {
    doc.Parse("<root><a/><b/><c/></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    
    doc.DeleteNode(c);
    
    EXPECT_EQ(root->FirstChildElement("c"), nullptr);
    XMLElement* a = root->FirstChildElement("a");
    XMLElement* b = root->FirstChildElement("b");
    EXPECT_NE(a, nullptr);
    EXPECT_NE(b, nullptr);
    EXPECT_EQ(root->LastChildElement(), b);
}

// Test: DeleteNode only child leaves parent with no children
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeOnlyChildLeavesParentEmpty_278) {
    doc.Parse("<root><only/></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    XMLElement* only = root->FirstChildElement("only");
    ASSERT_NE(only, nullptr);
    
    doc.DeleteNode(only);
    
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
}

// Test: DeleteNode after inserting a created element
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteNodeAfterInsert_278) {
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    XMLElement* newElem = doc.NewElement("inserted");
    root->InsertEndChild(newElem);
    
    EXPECT_NE(root->FirstChildElement("inserted"), nullptr);
    
    doc.DeleteNode(newElem);
    
    EXPECT_EQ(root->FirstChildElement("inserted"), nullptr);
    EXPECT_TRUE(root->NoChildren());
}

// Test: Delete multiple nodes sequentially
TEST_F(XMLDocumentDeleteNodeTest_278, DeleteMultipleNodesSequentially_278) {
    doc.Parse("<root><a/><b/><c/><d/></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    
    // Delete all children one by one
    while (XMLElement* child = root->FirstChildElement()) {
        doc.DeleteNode(child);
    }
    
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->ChildElementCount(), 0);
}

// Test: ChildElementCount decreases after DeleteNode
TEST_F(XMLDocumentDeleteNodeTest_278, ChildElementCountDecreasesAfterDelete_278) {
    doc.Parse("<root><a/><b/><c/></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    EXPECT_EQ(root->ChildElementCount(), 3);
    
    XMLElement* b = root->FirstChildElement("b");
    doc.DeleteNode(b);
    
    EXPECT_EQ(root->ChildElementCount(), 2);
}

// Test: Document can still be used after deleting all nodes
TEST_F(XMLDocumentDeleteNodeTest_278, DocumentUsableAfterDeletingAllNodes_278) {
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    doc.DeleteNode(root);
    
    EXPECT_EQ(doc.RootElement(), nullptr);
    
    // Parse new content
    XMLError err = doc.Parse("<newroot><newchild/></newroot>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "newroot");
}
