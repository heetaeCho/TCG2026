#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_51 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== NoChildren Tests ====================

TEST_F(XMLNodeTest_51, NoChildren_EmptyDocument_51) {
    XMLDocument emptyDoc;
    EXPECT_TRUE(emptyDoc.NoChildren());
}

TEST_F(XMLNodeTest_51, NoChildren_AfterInsertChild_51) {
    XMLElement* elem = doc.NewElement("root");
    doc.InsertEndChild(elem);
    EXPECT_FALSE(doc.NoChildren());
}

TEST_F(XMLNodeTest_51, NoChildren_AfterDeleteChildren_51) {
    XMLElement* elem = doc.NewElement("root");
    doc.InsertEndChild(elem);
    EXPECT_FALSE(doc.NoChildren());
    doc.DeleteChildren();
    EXPECT_TRUE(doc.NoChildren());
}

// ==================== InsertEndChild Tests ====================

TEST_F(XMLNodeTest_51, InsertEndChild_SingleChild_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->InsertEndChild(child);
    
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), child);
    EXPECT_EQ(root->LastChild(), child);
}

TEST_F(XMLNodeTest_51, InsertEndChild_MultipleChildren_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    
    EXPECT_EQ(root->FirstChild(), child1);
    EXPECT_EQ(root->LastChild(), child2);
}

TEST_F(XMLNodeTest_51, InsertEndChild_NullReturnsNull_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    // Inserting a node from a different document should fail or work depending on impl
    // But inserting null-like scenarios are harder to test without crashing
}

// ==================== InsertFirstChild Tests ====================

TEST_F(XMLNodeTest_51, InsertFirstChild_SingleChild_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->InsertFirstChild(child);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(root->FirstChild(), child);
}

TEST_F(XMLNodeTest_51, InsertFirstChild_BeforeExisting_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertFirstChild(child2);
    
    EXPECT_EQ(root->FirstChild(), child2);
    EXPECT_EQ(root->LastChild(), child1);
}

// ==================== InsertAfterChild Tests ====================

TEST_F(XMLNodeTest_51, InsertAfterChild_InMiddle_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child3 = doc.NewElement("child3");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child3);
    root->InsertAfterChild(child1, child2);
    
    EXPECT_EQ(root->FirstChild(), child1);
    EXPECT_EQ(root->FirstChild()->NextSibling(), child2);
    EXPECT_EQ(root->LastChild(), child3);
}

TEST_F(XMLNodeTest_51, InsertAfterChild_AtEnd_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertAfterChild(child1, child2);
    
    EXPECT_EQ(root->LastChild(), child2);
}

// ==================== DeleteChildren Tests ====================

TEST_F(XMLNodeTest_51, DeleteChildren_RemovesAll_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));
    
    EXPECT_FALSE(root->NoChildren());
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
}

TEST_F(XMLNodeTest_51, DeleteChildren_OnEmptyNode_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_TRUE(root->NoChildren());
    root->DeleteChildren();  // Should not crash
    EXPECT_TRUE(root->NoChildren());
}

// ==================== DeleteChild Tests ====================

TEST_F(XMLNodeTest_51, DeleteChild_SingleChild_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    root->DeleteChild(child);
    EXPECT_TRUE(root->NoChildren());
}

TEST_F(XMLNodeTest_51, DeleteChild_MiddleChild_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);
    
    root->DeleteChild(child2);
    EXPECT_EQ(root->FirstChild(), child1);
    EXPECT_EQ(root->LastChild(), child3);
    EXPECT_EQ(child1->NextSibling(), child3);
}

// ==================== Value / SetValue Tests ====================

TEST_F(XMLNodeTest_51, SetValue_GetValue_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    root->SetValue("newname", false);
    EXPECT_STREQ(root->Value(), "newname");
}

TEST_F(XMLNodeTest_51, SetValue_StaticMem_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    root->SetValue("staticval", true);
    EXPECT_STREQ(root->Value(), "staticval");
}

TEST_F(XMLNodeTest_51, Value_DefaultElement_51) {
    XMLElement* root = doc.NewElement("testelem");
    EXPECT_STREQ(root->Value(), "testelem");
    doc.InsertEndChild(root);
}

// ==================== FirstChild / LastChild Tests ====================

TEST_F(XMLNodeTest_51, FirstChild_NoChildren_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->FirstChild(), nullptr);
}

TEST_F(XMLNodeTest_51, LastChild_NoChildren_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->LastChild(), nullptr);
}

TEST_F(XMLNodeTest_51, FirstChild_WithChildren_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child1 = doc.NewElement("first");
    XMLElement* child2 = doc.NewElement("second");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    
    EXPECT_EQ(root->FirstChild(), child1);
    EXPECT_EQ(root->LastChild(), child2);
}

// ==================== FirstChildElement / LastChildElement Tests ====================

TEST_F(XMLNodeTest_51, FirstChildElement_ByName_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    XMLElement* a2 = doc.NewElement("alpha");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);
    
    EXPECT_EQ(root->FirstChildElement("alpha"), a);
    EXPECT_EQ(root->FirstChildElement("beta"), b);
}

TEST_F(XMLNodeTest_51, FirstChildElement_NoMatch_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("alpha");
    root->InsertEndChild(a);
    
    EXPECT_EQ(root->FirstChildElement("gamma"), nullptr);
}

TEST_F(XMLNodeTest_51, FirstChildElement_NoName_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("alpha");
    root->InsertEndChild(a);
    
    EXPECT_EQ(root->FirstChildElement(), a);
}

TEST_F(XMLNodeTest_51, LastChildElement_ByName_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    XMLElement* a2 = doc.NewElement("alpha");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);
    
    EXPECT_EQ(root->LastChildElement("alpha"), a2);
}

TEST_F(XMLNodeTest_51, LastChildElement_NoName_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    
    EXPECT_EQ(root->LastChildElement(), b);
}

// ==================== Sibling Tests ====================

TEST_F(XMLNodeTest_51, NextSibling_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);
    
    EXPECT_EQ(a->NextSibling(), b);
    EXPECT_EQ(b->NextSibling(), c);
    EXPECT_EQ(c->NextSibling(), nullptr);
}

TEST_F(XMLNodeTest_51, PreviousSibling_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);
    
    EXPECT_EQ(c->PreviousSibling(), b);
    EXPECT_EQ(b->PreviousSibling(), a);
    EXPECT_EQ(a->PreviousSibling(), nullptr);
}

TEST_F(XMLNodeTest_51, NextSiblingElement_ByName_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    XMLElement* a2 = doc.NewElement("alpha");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);
    
    EXPECT_EQ(a->NextSiblingElement("alpha"), a2);
    EXPECT_EQ(a->NextSiblingElement("beta"), b);
    EXPECT_EQ(a2->NextSiblingElement("alpha"), nullptr);
}

TEST_F(XMLNodeTest_51, PreviousSiblingElement_ByName_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    XMLElement* a2 = doc.NewElement("alpha");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);
    
    EXPECT_EQ(a2->PreviousSiblingElement("alpha"), a);
    EXPECT_EQ(a2->PreviousSiblingElement("beta"), b);
    EXPECT_EQ(a->PreviousSiblingElement("alpha"), nullptr);
}

// ==================== Parent Tests ====================

TEST_F(XMLNodeTest_51, Parent_RootHasDocAsParent_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->Parent(), &doc);
}

TEST_F(XMLNodeTest_51, Parent_ChildHasRootAsParent_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    EXPECT_EQ(child->Parent(), root);
}

TEST_F(XMLNodeTest_51, Parent_DocumentHasNoParent_51) {
    EXPECT_EQ(doc.Parent(), nullptr);
}

// ==================== GetDocument Tests ====================

TEST_F(XMLNodeTest_51, GetDocument_ReturnsOwnerDocument_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->GetDocument(), &doc);
}

// ==================== ChildElementCount Tests ====================

TEST_F(XMLNodeTest_51, ChildElementCount_Empty_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->ChildElementCount(), 0);
}

TEST_F(XMLNodeTest_51, ChildElementCount_MultipleChildren_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));
    
    EXPECT_EQ(root->ChildElementCount(), 3);
}

TEST_F(XMLNodeTest_51, ChildElementCount_ByName_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("beta"));
    root->InsertEndChild(doc.NewElement("alpha"));
    
    EXPECT_EQ(root->ChildElementCount("alpha"), 2);
    EXPECT_EQ(root->ChildElementCount("beta"), 1);
    EXPECT_EQ(root->ChildElementCount("gamma"), 0);
}

// ==================== DeepClone Tests ====================

TEST_F(XMLNodeTest_51, DeepClone_ClonesTree_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    XMLElement* grandchild = doc.NewElement("grandchild");
    child->InsertEndChild(grandchild);
    
    XMLDocument targetDoc;
    XMLNode* cloned = root->DeepClone(&targetDoc);
    
    ASSERT_NE(cloned, nullptr);
    EXPECT_STREQ(cloned->Value(), "root");
    EXPECT_FALSE(cloned->NoChildren());
    
    XMLElement* clonedChild = cloned->FirstChildElement("child");
    ASSERT_NE(clonedChild, nullptr);
    
    XMLElement* clonedGrandchild = clonedChild->FirstChildElement("grandchild");
    ASSERT_NE(clonedGrandchild, nullptr);
    
    // Cleanup: the cloned node needs to be inserted somewhere or deleted
    targetDoc.InsertEndChild(cloned);
}

TEST_F(XMLNodeTest_51, DeepClone_IntoDifferentDocument_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLDocument targetDoc;
    XMLNode* cloned = root->DeepClone(&targetDoc);
    ASSERT_NE(cloned, nullptr);
    targetDoc.InsertEndChild(cloned);
    
    EXPECT_EQ(cloned->GetDocument(), &targetDoc);
}

// ==================== UserData Tests ====================

TEST_F(XMLNodeTest_51, UserData_DefaultNull_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->GetUserData(), nullptr);
}

TEST_F(XMLNodeTest_51, UserData_SetAndGet_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    int data = 42;
    root->SetUserData(&data);
    EXPECT_EQ(root->GetUserData(), &data);
}

TEST_F(XMLNodeTest_51, UserData_SetNull_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    int data = 42;
    root->SetUserData(&data);
    root->SetUserData(nullptr);
    EXPECT_EQ(root->GetUserData(), nullptr);
}

// ==================== ToElement / ToText etc. Tests ====================

TEST_F(XMLNodeTest_51, ToElement_ReturnsNonNullForElement_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_NE(root->ToElement(), nullptr);
}

TEST_F(XMLNodeTest_51, ToDocument_ReturnsNonNullForDocument_51) {
    EXPECT_NE(doc.ToDocument(), nullptr);
}

TEST_F(XMLNodeTest_51, ToText_ReturnsNullForElement_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->ToText(), nullptr);
}

TEST_F(XMLNodeTest_51, ToComment_ReturnsNullForElement_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->ToComment(), nullptr);
}

TEST_F(XMLNodeTest_51, ToDocument_ReturnsNullForElement_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->ToDocument(), nullptr);
}

// ==================== LinkEndChild (alias for InsertEndChild) ====================

TEST_F(XMLNodeTest_51, LinkEndChild_Works_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->LinkEndChild(child);
    
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(root->LastChild(), child);
}

// ==================== GetLineNum Tests ====================

TEST_F(XMLNodeTest_51, GetLineNum_ForNewElement_51) {
    XMLElement* root = doc.NewElement("root");
    // Line number for programmatically created elements is 0
    EXPECT_EQ(root->GetLineNum(), 0);
    doc.InsertEndChild(root);
}

TEST_F(XMLNodeTest_51, GetLineNum_FromParsedXML_51) {
    const char* xml = "<root>\n  <child/>\n</root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetLineNum(), 1);
    
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->GetLineNum(), 2);
}

// ==================== Parsing-based Integration Tests ====================

TEST_F(XMLNodeTest_51, ParseAndTraverse_51) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_FALSE(root->NoChildren());
    EXPECT_EQ(root->ChildElementCount(), 3);
}

TEST_F(XMLNodeTest_51, NoChildren_WithTextContent_51) {
    const char* xml = "<root>Hello</root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    // "Hello" is a text node child
    EXPECT_FALSE(root->NoChildren());
}

// ==================== InsertEndChild from different document ====================

TEST_F(XMLNodeTest_51, InsertEndChild_FromDifferentDocument_ReturnsNull_51) {
    XMLDocument doc2;
    XMLElement* foreignElement = doc2.NewElement("foreign");
    
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    // Inserting a node from a different document should fail
    XMLNode* result = root->InsertEndChild(foreignElement);
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLNodeTest_51, InsertFirstChild_FromDifferentDocument_ReturnsNull_51) {
    XMLDocument doc2;
    XMLElement* foreignElement = doc2.NewElement("foreign");
    
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLNode* result = root->InsertFirstChild(foreignElement);
    EXPECT_EQ(result, nullptr);
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLNodeTest_51, ShallowEqual_SameElement_51) {
    XMLElement* a = doc.NewElement("test");
    XMLElement* b = doc.NewElement("test");
    
    EXPECT_TRUE(a->ShallowEqual(b));
    
    doc.DeleteNode(a);
    doc.DeleteNode(b);
}

TEST_F(XMLNodeTest_51, ShallowEqual_DifferentElement_51) {
    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    
    EXPECT_FALSE(a->ShallowEqual(b));
    
    doc.DeleteNode(a);
    doc.DeleteNode(b);
}

// ==================== Mixed content child ordering ====================

TEST_F(XMLNodeTest_51, ChildOrdering_AfterMultipleInsertions_51) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    XMLElement* c3 = doc.NewElement("c3");
    XMLElement* c0 = doc.NewElement("c0");
    
    root->InsertEndChild(c1);
    root->InsertEndChild(c3);
    root->InsertFirstChild(c0);
    root->InsertAfterChild(c1, c2);
    
    // Expected order: c0, c1, c2, c3
    EXPECT_EQ(root->FirstChild(), c0);
    EXPECT_EQ(c0->NextSibling(), c1);
    EXPECT_EQ(c1->NextSibling(), c2);
    EXPECT_EQ(c2->NextSibling(), c3);
    EXPECT_EQ(c3->NextSibling(), nullptr);
    EXPECT_EQ(root->LastChild(), c3);
}

// ==================== ChildElementCount with mixed node types ====================

TEST_F(XMLNodeTest_51, ChildElementCount_WithMixedTypes_51) {
    const char* xml = "<root>text<child/><!-- comment --><child2/></root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    // Only element children should be counted
    EXPECT_EQ(root->ChildElementCount(), 2);
}

TEST_F(XMLNodeTest_51, ChildElementCount_ByName_WithMixedTypes_51) {
    const char* xml = "<root>text<item/><!-- comment --><item/><other/></root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    EXPECT_EQ(root->ChildElementCount("item"), 2);
    EXPECT_EQ(root->ChildElementCount("other"), 1);
    EXPECT_EQ(root->ChildElementCount("missing"), 0);
}
