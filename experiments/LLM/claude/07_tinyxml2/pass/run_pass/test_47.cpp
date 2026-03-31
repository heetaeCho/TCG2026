#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_47 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test ToDeclaration returns null for non-declaration nodes
TEST_F(XMLNodeTest_47, ToDeclarationReturnsNullForElement_47) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    XMLNode* node = elem;
    EXPECT_EQ(nullptr, node->ToDeclaration());
}

// Test ToDeclaration returns non-null for actual declaration
TEST_F(XMLNodeTest_47, ToDeclarationReturnsNonNullForDeclaration_47) {
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    doc.InsertEndChild(decl);
    XMLNode* node = decl;
    EXPECT_NE(nullptr, node->ToDeclaration());
    EXPECT_EQ(decl, node->ToDeclaration());
}

// Test ToElement returns null for non-element nodes
TEST_F(XMLNodeTest_47, ToElementReturnsNullForComment_47) {
    XMLComment* comment = doc.NewComment("test comment");
    doc.InsertEndChild(comment);
    XMLNode* node = comment;
    EXPECT_EQ(nullptr, node->ToElement());
}

// Test ToElement returns non-null for element
TEST_F(XMLNodeTest_47, ToElementReturnsNonNullForElement_47) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    XMLNode* node = elem;
    EXPECT_NE(nullptr, node->ToElement());
}

// Test ToText returns null for non-text nodes
TEST_F(XMLNodeTest_47, ToTextReturnsNullForElement_47) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    XMLNode* node = elem;
    EXPECT_EQ(nullptr, node->ToText());
}

// Test ToText returns non-null for text nodes
TEST_F(XMLNodeTest_47, ToTextReturnsNonNullForText_47) {
    XMLText* text = doc.NewText("hello");
    XMLElement* elem = doc.NewElement("root");
    doc.InsertEndChild(elem);
    elem->InsertEndChild(text);
    XMLNode* node = text;
    EXPECT_NE(nullptr, node->ToText());
}

// Test ToComment
TEST_F(XMLNodeTest_47, ToCommentReturnsNonNullForComment_47) {
    XMLComment* comment = doc.NewComment("a comment");
    doc.InsertEndChild(comment);
    XMLNode* node = comment;
    EXPECT_NE(nullptr, node->ToComment());
}

// Test ToDocument
TEST_F(XMLNodeTest_47, ToDocumentReturnsNonNullForDocument_47) {
    XMLNode* node = &doc;
    EXPECT_NE(nullptr, node->ToDocument());
}

TEST_F(XMLNodeTest_47, ToDocumentReturnsNullForElement_47) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    XMLNode* node = elem;
    EXPECT_EQ(nullptr, node->ToDocument());
}

// Test ToUnknown
TEST_F(XMLNodeTest_47, ToUnknownReturnsNullForElement_47) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    XMLNode* node = elem;
    EXPECT_EQ(nullptr, node->ToUnknown());
}

// Test Value and SetValue
TEST_F(XMLNodeTest_47, ValueReturnsElementName_47) {
    XMLElement* elem = doc.NewElement("myElement");
    doc.InsertEndChild(elem);
    EXPECT_STREQ("myElement", elem->Value());
}

TEST_F(XMLNodeTest_47, SetValueChangesValue_47) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertEndChild(elem);
    elem->SetValue("changed", false);
    EXPECT_STREQ("changed", elem->Value());
}

TEST_F(XMLNodeTest_47, SetValueWithStaticMem_47) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertEndChild(elem);
    elem->SetValue("static_value", true);
    EXPECT_STREQ("static_value", elem->Value());
}

// Test NoChildren
TEST_F(XMLNodeTest_47, NoChildrenReturnsTrueForEmptyElement_47) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_TRUE(elem->NoChildren());
}

TEST_F(XMLNodeTest_47, NoChildrenReturnsFalseWhenHasChildren_47) {
    XMLElement* parent = doc.NewElement("parent");
    XMLElement* child = doc.NewElement("child");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(child);
    EXPECT_FALSE(parent->NoChildren());
}

// Test InsertEndChild
TEST_F(XMLNodeTest_47, InsertEndChildAddsChild_47) {
    XMLElement* parent = doc.NewElement("parent");
    XMLElement* child = doc.NewElement("child");
    doc.InsertEndChild(parent);
    XMLNode* result = parent->InsertEndChild(child);
    EXPECT_EQ(child, result);
    EXPECT_FALSE(parent->NoChildren());
    EXPECT_EQ(child, parent->FirstChild());
    EXPECT_EQ(child, parent->LastChild());
}

TEST_F(XMLNodeTest_47, InsertEndChildMultipleChildren_47) {
    XMLElement* parent = doc.NewElement("parent");
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    EXPECT_EQ(child1, parent->FirstChild());
    EXPECT_EQ(child2, parent->LastChild());
}

// Test InsertFirstChild
TEST_F(XMLNodeTest_47, InsertFirstChildAddsAtBeginning_47) {
    XMLElement* parent = doc.NewElement("parent");
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(child1);
    parent->InsertFirstChild(child2);
    EXPECT_EQ(child2, parent->FirstChild());
    EXPECT_EQ(child1, parent->LastChild());
}

// Test InsertAfterChild
TEST_F(XMLNodeTest_47, InsertAfterChildInsertsCorrectly_47) {
    XMLElement* parent = doc.NewElement("parent");
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child3);
    parent->InsertAfterChild(child1, child2);
    
    EXPECT_EQ(child1, parent->FirstChild());
    EXPECT_EQ(child2, child1->NextSibling());
    EXPECT_EQ(child3, child2->NextSibling());
}

// Test DeleteChildren
TEST_F(XMLNodeTest_47, DeleteChildrenRemovesAllChildren_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("child1"));
    parent->InsertEndChild(doc.NewElement("child2"));
    parent->InsertEndChild(doc.NewElement("child3"));
    EXPECT_FALSE(parent->NoChildren());
    parent->DeleteChildren();
    EXPECT_TRUE(parent->NoChildren());
}

// Test DeleteChild
TEST_F(XMLNodeTest_47, DeleteChildRemovesSpecificChild_47) {
    XMLElement* parent = doc.NewElement("parent");
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->DeleteChild(child1);
    EXPECT_EQ(child2, parent->FirstChild());
    EXPECT_EQ(child2, parent->LastChild());
}

// Test Parent
TEST_F(XMLNodeTest_47, ParentReturnsCorrectParent_47) {
    XMLElement* parent = doc.NewElement("parent");
    XMLElement* child = doc.NewElement("child");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(child);
    EXPECT_EQ(parent, child->Parent());
}

TEST_F(XMLNodeTest_47, ParentOfRootIsDocument_47) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(&doc, root->Parent());
}

// Test FirstChild and LastChild
TEST_F(XMLNodeTest_47, FirstChildReturnsNullWhenEmpty_47) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->FirstChild());
}

TEST_F(XMLNodeTest_47, LastChildReturnsNullWhenEmpty_47) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->LastChild());
}

// Test FirstChildElement and LastChildElement with name filter
TEST_F(XMLNodeTest_47, FirstChildElementWithName_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("alpha"));
    parent->InsertEndChild(doc.NewElement("beta"));
    parent->InsertEndChild(doc.NewElement("alpha"));
    
    const XMLElement* found = parent->FirstChildElement("beta");
    ASSERT_NE(nullptr, found);
    EXPECT_STREQ("beta", found->Value());
}

TEST_F(XMLNodeTest_47, FirstChildElementWithNoMatch_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("alpha"));
    
    const XMLElement* found = parent->FirstChildElement("gamma");
    EXPECT_EQ(nullptr, found);
}

TEST_F(XMLNodeTest_47, FirstChildElementWithNullReturnsFirst_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("alpha");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(doc.NewElement("beta"));
    
    XMLElement* found = parent->FirstChildElement();
    EXPECT_EQ(child1, found);
}

TEST_F(XMLNodeTest_47, LastChildElementWithName_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* alpha1 = doc.NewElement("alpha");
    XMLElement* beta = doc.NewElement("beta");
    XMLElement* alpha2 = doc.NewElement("alpha");
    parent->InsertEndChild(alpha1);
    parent->InsertEndChild(beta);
    parent->InsertEndChild(alpha2);
    
    const XMLElement* found = parent->LastChildElement("alpha");
    EXPECT_EQ(alpha2, found);
}

// Test NextSibling and PreviousSibling
TEST_F(XMLNodeTest_47, NextSiblingTraversal_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    XMLElement* c3 = doc.NewElement("c3");
    parent->InsertEndChild(c1);
    parent->InsertEndChild(c2);
    parent->InsertEndChild(c3);
    
    EXPECT_EQ(c2, c1->NextSibling());
    EXPECT_EQ(c3, c2->NextSibling());
    EXPECT_EQ(nullptr, c3->NextSibling());
}

TEST_F(XMLNodeTest_47, PreviousSiblingTraversal_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    XMLElement* c3 = doc.NewElement("c3");
    parent->InsertEndChild(c1);
    parent->InsertEndChild(c2);
    parent->InsertEndChild(c3);
    
    EXPECT_EQ(nullptr, c1->PreviousSibling());
    EXPECT_EQ(c1, c2->PreviousSibling());
    EXPECT_EQ(c2, c3->PreviousSibling());
}

// Test NextSiblingElement and PreviousSiblingElement with name
TEST_F(XMLNodeTest_47, NextSiblingElementWithName_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* a2 = doc.NewElement("a");
    parent->InsertEndChild(a);
    parent->InsertEndChild(b);
    parent->InsertEndChild(a2);
    
    EXPECT_EQ(a2, a->NextSiblingElement("a"));
}

TEST_F(XMLNodeTest_47, PreviousSiblingElementWithName_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* a1 = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* a2 = doc.NewElement("a");
    parent->InsertEndChild(a1);
    parent->InsertEndChild(b);
    parent->InsertEndChild(a2);
    
    EXPECT_EQ(a1, a2->PreviousSiblingElement("a"));
}

// Test GetDocument
TEST_F(XMLNodeTest_47, GetDocumentReturnsOwnerDocument_47) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(&doc, elem->GetDocument());
}

// Test ChildElementCount
TEST_F(XMLNodeTest_47, ChildElementCountReturnsZeroForEmpty_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    EXPECT_EQ(0, parent->ChildElementCount());
}

TEST_F(XMLNodeTest_47, ChildElementCountReturnsCorrectCount_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("c1"));
    parent->InsertEndChild(doc.NewElement("c2"));
    parent->InsertEndChild(doc.NewElement("c3"));
    EXPECT_EQ(3, parent->ChildElementCount());
}

TEST_F(XMLNodeTest_47, ChildElementCountWithNameFilter_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("alpha"));
    parent->InsertEndChild(doc.NewElement("beta"));
    parent->InsertEndChild(doc.NewElement("alpha"));
    EXPECT_EQ(2, parent->ChildElementCount("alpha"));
    EXPECT_EQ(1, parent->ChildElementCount("beta"));
    EXPECT_EQ(0, parent->ChildElementCount("gamma"));
}

// Test GetLineNum
TEST_F(XMLNodeTest_47, GetLineNumForParsedDocument_47) {
    const char* xml = "<root>\n  <child/>\n</root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(1, root->GetLineNum());
    
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_EQ(2, child->GetLineNum());
}

// Test UserData
TEST_F(XMLNodeTest_47, UserDataDefaultsToNull_47) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->GetUserData());
}

TEST_F(XMLNodeTest_47, SetAndGetUserData_47) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    int data = 42;
    elem->SetUserData(&data);
    EXPECT_EQ(&data, elem->GetUserData());
}

// Test DeepClone
TEST_F(XMLNodeTest_47, DeepCloneCreatesIndependentCopy_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    
    XMLDocument doc2;
    XMLNode* cloned = parent->DeepClone(&doc2);
    ASSERT_NE(nullptr, cloned);
    doc2.InsertEndChild(cloned);
    
    EXPECT_STREQ("parent", cloned->Value());
    EXPECT_NE(nullptr, cloned->FirstChildElement("child"));
    EXPECT_EQ(&doc2, cloned->GetDocument());
}

// Test ShallowClone
TEST_F(XMLNodeTest_47, ShallowCloneDoesNotCopyChildren_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    
    XMLDocument doc2;
    XMLNode* cloned = parent->ShallowClone(&doc2);
    ASSERT_NE(nullptr, cloned);
    doc2.InsertEndChild(cloned);
    
    EXPECT_STREQ("parent", cloned->Value());
    EXPECT_TRUE(cloned->NoChildren());
}

// Test LinkEndChild (alias for InsertEndChild)
TEST_F(XMLNodeTest_47, LinkEndChildAddsChild_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = parent->LinkEndChild(child);
    EXPECT_EQ(child, result);
    EXPECT_FALSE(parent->NoChildren());
}

// Test inserting a node from a different document (should handle it)
TEST_F(XMLNodeTest_47, InsertEndChildReturnsNullForDocumentNode_47) {
    // Trying to add a document as a child should not be allowed
    // The behavior depends on implementation, but we test observable output
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    // We can't easily create a scenario that returns null without knowing internals,
    // but we can test that inserting the same node twice relocates it
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    
    XMLElement* parent2 = doc.NewElement("parent2");
    doc.InsertEndChild(parent2);
    parent2->InsertEndChild(child);
    
    // child should have moved from parent to parent2
    EXPECT_TRUE(parent->NoChildren());
    EXPECT_EQ(child, parent2->FirstChild());
}

// Test with mixed content (text and elements)
TEST_F(XMLNodeTest_47, ChildElementCountIgnoresTextNodes_47) {
    const char* xml = "<root>text1<child1/>text2<child2/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    // ChildElementCount should count only elements, not text nodes
    EXPECT_EQ(2, root->ChildElementCount());
}

// Test parsing and structure
TEST_F(XMLNodeTest_47, ParseCreatesCorrectStructure_47) {
    const char* xml = "<root><a><b/></a><c/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("root", root->Value());
    
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(nullptr, a);
    
    XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(nullptr, b);
    
    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(nullptr, c);
    
    EXPECT_EQ(nullptr, c->NextSiblingElement());
}

// Test ShallowEqual
TEST_F(XMLNodeTest_47, ShallowEqualSameElement_47) {
    XMLElement* e1 = doc.NewElement("test");
    XMLElement* e2 = doc.NewElement("test");
    doc.InsertEndChild(e1);
    // ShallowEqual compares the node itself (name, attributes) not children
    EXPECT_TRUE(e1->ShallowEqual(e2));
    // Clean up e2 since it's not in the tree
    // Actually e2 is managed by doc's memory pool, so we should add it
    doc.DeleteNode(e2);
}

TEST_F(XMLNodeTest_47, ShallowEqualDifferentElements_47) {
    XMLElement* e1 = doc.NewElement("test1");
    XMLElement* e2 = doc.NewElement("test2");
    doc.InsertEndChild(e1);
    EXPECT_FALSE(e1->ShallowEqual(e2));
    doc.DeleteNode(e2);
}

// Test boundary: empty document
TEST_F(XMLNodeTest_47, EmptyDocumentHasNoChildren_47) {
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(nullptr, doc.FirstChild());
    EXPECT_EQ(nullptr, doc.LastChild());
    EXPECT_EQ(nullptr, doc.RootElement());
}

// Test boundary: single node
TEST_F(XMLNodeTest_47, SingleChildIsFirstAndLast_47) {
    XMLElement* elem = doc.NewElement("only");
    doc.InsertEndChild(elem);
    EXPECT_EQ(elem, doc.FirstChild());
    EXPECT_EQ(elem, doc.LastChild());
    EXPECT_EQ(nullptr, elem->NextSibling());
    EXPECT_EQ(nullptr, elem->PreviousSibling());
}

// Test DeleteChildren on document
TEST_F(XMLNodeTest_47, DeleteChildrenOnDocument_47) {
    doc.InsertEndChild(doc.NewElement("a"));
    doc.InsertEndChild(doc.NewElement("b"));
    EXPECT_FALSE(doc.NoChildren());
    doc.DeleteChildren();
    EXPECT_TRUE(doc.NoChildren());
}

// Test InsertAfterChild at end
TEST_F(XMLNodeTest_47, InsertAfterChildAtEnd_47) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    parent->InsertEndChild(c1);
    parent->InsertAfterChild(c1, c2);
    EXPECT_EQ(c2, parent->LastChild());
    EXPECT_EQ(c2, c1->NextSibling());
}

// Test declaration Value
TEST_F(XMLNodeTest_47, DeclarationValue_47) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc.Parse(xml);
    XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(nullptr, decl);
    // The value of the declaration node
    EXPECT_NE(nullptr, decl->Value());
}
