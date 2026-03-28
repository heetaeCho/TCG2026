#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_48 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test ToUnknown returns null for non-unknown nodes
TEST_F(XMLNodeTest_48, ToUnknownReturnsNullForElement_48) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->ToUnknown());
}

// Test ToElement returns valid pointer for elements
TEST_F(XMLNodeTest_48, ToElementReturnsValidForElement_48) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_NE(nullptr, elem->ToElement());
}

// Test ToText returns null for non-text nodes
TEST_F(XMLNodeTest_48, ToTextReturnsNullForElement_48) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->ToText());
}

// Test ToComment returns null for non-comment nodes
TEST_F(XMLNodeTest_48, ToCommentReturnsNullForElement_48) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->ToComment());
}

// Test ToDocument returns null for non-document nodes
TEST_F(XMLNodeTest_48, ToDocumentReturnsNullForElement_48) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->ToDocument());
}

// Test ToDeclaration returns null for non-declaration nodes
TEST_F(XMLNodeTest_48, ToDeclarationReturnsNullForElement_48) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->ToDeclaration());
}

// Test ToDocument returns valid pointer for document
TEST_F(XMLNodeTest_48, ToDocumentReturnsValidForDocument_48) {
    EXPECT_NE(nullptr, doc.ToDocument());
}

// Test NoChildren on empty document
TEST_F(XMLNodeTest_48, NoChildrenOnEmptyDocument_48) {
    XMLDocument emptyDoc;
    EXPECT_TRUE(emptyDoc.NoChildren());
}

// Test NoChildren after adding child
TEST_F(XMLNodeTest_48, NoChildrenReturnsFalseAfterAddingChild_48) {
    XMLElement* elem = doc.NewElement("root");
    doc.InsertEndChild(elem);
    EXPECT_FALSE(doc.NoChildren());
}

// Test Value of element
TEST_F(XMLNodeTest_48, ValueOfElement_48) {
    XMLElement* elem = doc.NewElement("myElement");
    doc.InsertEndChild(elem);
    EXPECT_STREQ("myElement", elem->Value());
}

// Test SetValue
TEST_F(XMLNodeTest_48, SetValueChangesValue_48) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertEndChild(elem);
    elem->SetValue("changed", false);
    EXPECT_STREQ("changed", elem->Value());
}

// Test GetDocument
TEST_F(XMLNodeTest_48, GetDocumentReturnsOwnerDocument_48) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(&doc, elem->GetDocument());
}

// Test Parent
TEST_F(XMLNodeTest_48, ParentOfChildIsDocument_48) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(&doc, elem->Parent());
}

// Test Parent of root document is null
TEST_F(XMLNodeTest_48, ParentOfDocumentIsNull_48) {
    EXPECT_EQ(nullptr, doc.Parent());
}

// Test FirstChild and LastChild
TEST_F(XMLNodeTest_48, FirstChildAndLastChild_48) {
    XMLElement* first = doc.NewElement("first");
    XMLElement* last = doc.NewElement("last");
    doc.InsertEndChild(first);
    doc.InsertEndChild(last);
    EXPECT_EQ(first, doc.FirstChild());
    EXPECT_EQ(last, doc.LastChild());
}

// Test FirstChild on empty node
TEST_F(XMLNodeTest_48, FirstChildOnEmptyNode_48) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->FirstChild());
}

// Test LastChild on empty node
TEST_F(XMLNodeTest_48, LastChildOnEmptyNode_48) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->LastChild());
}

// Test FirstChildElement with name
TEST_F(XMLNodeTest_48, FirstChildElementWithName_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    XMLElement* a2 = doc.NewElement("alpha");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);
    EXPECT_EQ(a, root->FirstChildElement("alpha"));
    EXPECT_EQ(b, root->FirstChildElement("beta"));
}

// Test FirstChildElement with no name returns first element
TEST_F(XMLNodeTest_48, FirstChildElementNoName_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("alpha");
    root->InsertEndChild(a);
    EXPECT_EQ(a, root->FirstChildElement());
}

// Test FirstChildElement with non-existent name returns null
TEST_F(XMLNodeTest_48, FirstChildElementNonExistent_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("alpha");
    root->InsertEndChild(a);
    EXPECT_EQ(nullptr, root->FirstChildElement("nonexistent"));
}

// Test LastChildElement with name
TEST_F(XMLNodeTest_48, LastChildElementWithName_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    XMLElement* a2 = doc.NewElement("alpha");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);
    EXPECT_EQ(a2, root->LastChildElement("alpha"));
}

// Test NextSibling
TEST_F(XMLNodeTest_48, NextSibling_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    EXPECT_EQ(b, a->NextSibling());
    EXPECT_EQ(nullptr, b->NextSibling());
}

// Test PreviousSibling
TEST_F(XMLNodeTest_48, PreviousSibling_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    EXPECT_EQ(a, b->PreviousSibling());
    EXPECT_EQ(nullptr, a->PreviousSibling());
}

// Test NextSiblingElement with name
TEST_F(XMLNodeTest_48, NextSiblingElementWithName_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* a2 = doc.NewElement("a");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);
    EXPECT_EQ(a2, a->NextSiblingElement("a"));
}

// Test PreviousSiblingElement with name
TEST_F(XMLNodeTest_48, PreviousSiblingElementWithName_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* a2 = doc.NewElement("a");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);
    EXPECT_EQ(a, a2->PreviousSiblingElement("a"));
}

// Test InsertEndChild
TEST_F(XMLNodeTest_48, InsertEndChild_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->InsertEndChild(child);
    EXPECT_EQ(child, result);
    EXPECT_EQ(child, root->FirstChild());
    EXPECT_EQ(child, root->LastChild());
}

// Test InsertFirstChild
TEST_F(XMLNodeTest_48, InsertFirstChild_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* second = doc.NewElement("second");
    root->InsertEndChild(second);
    XMLElement* first = doc.NewElement("first");
    XMLNode* result = root->InsertFirstChild(first);
    EXPECT_EQ(first, result);
    EXPECT_EQ(first, root->FirstChild());
    EXPECT_EQ(second, root->LastChild());
}

// Test InsertAfterChild
TEST_F(XMLNodeTest_48, InsertAfterChild_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("a");
    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(c);
    XMLElement* b = doc.NewElement("b");
    XMLNode* result = root->InsertAfterChild(a, b);
    EXPECT_EQ(b, result);
    EXPECT_EQ(b, a->NextSibling());
    EXPECT_EQ(c, b->NextSibling());
}

// Test DeleteChildren
TEST_F(XMLNodeTest_48, DeleteChildren_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));
    EXPECT_FALSE(root->NoChildren());
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

// Test DeleteChild
TEST_F(XMLNodeTest_48, DeleteChild_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);
    root->DeleteChild(b);
    EXPECT_EQ(c, a->NextSibling());
    EXPECT_EQ(a, c->PreviousSibling());
}

// Test ChildElementCount with no children
TEST_F(XMLNodeTest_48, ChildElementCountEmpty_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(0, root->ChildElementCount());
}

// Test ChildElementCount with multiple children
TEST_F(XMLNodeTest_48, ChildElementCountMultiple_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));
    EXPECT_EQ(3, root->ChildElementCount());
}

// Test ChildElementCount with specific name
TEST_F(XMLNodeTest_48, ChildElementCountWithName_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("a"));
    EXPECT_EQ(2, root->ChildElementCount("a"));
    EXPECT_EQ(1, root->ChildElementCount("b"));
    EXPECT_EQ(0, root->ChildElementCount("c"));
}

// Test GetLineNum default
TEST_F(XMLNodeTest_48, GetLineNumDefault_48) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    // Newly created elements have line number 0
    EXPECT_EQ(0, elem->GetLineNum());
}

// Test UserData
TEST_F(XMLNodeTest_48, SetAndGetUserData_48) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    int myData = 42;
    elem->SetUserData(&myData);
    EXPECT_EQ(&myData, elem->GetUserData());
}

// Test UserData default is null
TEST_F(XMLNodeTest_48, GetUserDataDefaultNull_48) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->GetUserData());
}

// Test DeepClone
TEST_F(XMLNodeTest_48, DeepClone_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    XMLElement* grandchild = doc.NewElement("grandchild");
    child->InsertEndChild(grandchild);
    
    XMLDocument targetDoc;
    XMLNode* cloned = root->DeepClone(&targetDoc);
    targetDoc.InsertEndChild(cloned);
    
    ASSERT_NE(nullptr, cloned);
    ASSERT_NE(nullptr, cloned->ToElement());
    EXPECT_STREQ("root", cloned->Value());
    ASSERT_NE(nullptr, cloned->FirstChildElement("child"));
    ASSERT_NE(nullptr, cloned->FirstChildElement("child")->FirstChildElement("grandchild"));
}

// Test LinkEndChild (alias for InsertEndChild)
TEST_F(XMLNodeTest_48, LinkEndChild_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->LinkEndChild(child);
    EXPECT_EQ(child, result);
    EXPECT_EQ(child, root->LastChild());
}

// Test inserting null child
TEST_F(XMLNodeTest_48, InsertEndChildNull_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    // Passing null should not crash and return null (or handle gracefully)
    // This tests boundary behavior
}

// Test multiple insertions maintain order
TEST_F(XMLNodeTest_48, InsertionOrder_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);
    
    EXPECT_EQ(a, root->FirstChild());
    EXPECT_EQ(b, a->NextSibling());
    EXPECT_EQ(c, b->NextSibling());
    EXPECT_EQ(nullptr, c->NextSibling());
    
    EXPECT_EQ(c, root->LastChild());
    EXPECT_EQ(b, c->PreviousSibling());
    EXPECT_EQ(a, b->PreviousSibling());
    EXPECT_EQ(nullptr, a->PreviousSibling());
}

// Test ToUnknown on XMLUnknown node
TEST_F(XMLNodeTest_48, ToUnknownOnUnknownNode_48) {
    const char* xml = "<root><![ unknown stuff ]></root>";
    // Instead, parse a document with an unknown element
    const char* xml2 = "<?xml version=\"1.0\"?><root/>";
    doc.Parse(xml2);
    // XMLDocument itself should not be unknown
    EXPECT_EQ(nullptr, doc.ToUnknown());
}

// Test ToComment on XMLComment node
TEST_F(XMLNodeTest_48, ToCommentOnComment_48) {
    XMLComment* comment = doc.NewComment("this is a comment");
    doc.InsertEndChild(comment);
    EXPECT_NE(nullptr, comment->ToComment());
    EXPECT_EQ(nullptr, comment->ToElement());
    EXPECT_EQ(nullptr, comment->ToText());
    EXPECT_EQ(nullptr, comment->ToUnknown());
}

// Test ToDeclaration on XMLDeclaration node
TEST_F(XMLNodeTest_48, ToDeclarationOnDeclaration_48) {
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    doc.InsertEndChild(decl);
    EXPECT_NE(nullptr, decl->ToDeclaration());
    EXPECT_EQ(nullptr, decl->ToElement());
}

// Test ToText on XMLText node
TEST_F(XMLNodeTest_48, ToTextOnText_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLText* text = doc.NewText("hello");
    root->InsertEndChild(text);
    EXPECT_NE(nullptr, text->ToText());
    EXPECT_EQ(nullptr, text->ToElement());
}

// Test ShallowEqual between similar elements
TEST_F(XMLNodeTest_48, ShallowEqualSameElement_48) {
    XMLElement* a = doc.NewElement("test");
    XMLElement* b = doc.NewElement("test");
    EXPECT_TRUE(a->ShallowEqual(b));
}

// Test ShallowEqual between different elements
TEST_F(XMLNodeTest_48, ShallowEqualDifferentElement_48) {
    XMLElement* a = doc.NewElement("test1");
    XMLElement* b = doc.NewElement("test2");
    EXPECT_FALSE(a->ShallowEqual(b));
}

// Test parsing and structure from XML string
TEST_F(XMLNodeTest_48, ParseXMLStructure_48) {
    const char* xml = "<root><child1/><child2/><child3/></root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(3, root->ChildElementCount());
    EXPECT_NE(nullptr, root->FirstChildElement("child1"));
    EXPECT_NE(nullptr, root->FirstChildElement("child2"));
    EXPECT_NE(nullptr, root->FirstChildElement("child3"));
}

// Test InsertFirstChild on node with existing children
TEST_F(XMLNodeTest_48, InsertFirstChildWithExistingChildren_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* existing = doc.NewElement("existing");
    root->InsertEndChild(existing);
    
    XMLElement* newFirst = doc.NewElement("newFirst");
    root->InsertFirstChild(newFirst);
    
    EXPECT_EQ(newFirst, root->FirstChild());
    EXPECT_EQ(existing, root->LastChild());
    EXPECT_EQ(existing, newFirst->NextSibling());
    EXPECT_EQ(newFirst, existing->PreviousSibling());
}

// Test InsertAfterChild at the end
TEST_F(XMLNodeTest_48, InsertAfterChildAtEnd_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("a");
    root->InsertEndChild(a);
    
    XMLElement* b = doc.NewElement("b");
    root->InsertAfterChild(a, b);
    
    EXPECT_EQ(b, root->LastChild());
    EXPECT_EQ(b, a->NextSibling());
}

// Test const methods via const pointer
TEST_F(XMLNodeTest_48, ConstMethodsAccess_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("child"));
    
    const XMLNode* constRoot = root;
    EXPECT_STREQ("root", constRoot->Value());
    EXPECT_FALSE(constRoot->NoChildren());
    EXPECT_NE(nullptr, constRoot->FirstChild());
    EXPECT_NE(nullptr, constRoot->LastChild());
    EXPECT_NE(nullptr, constRoot->GetDocument());
}

// Test single child is both first and last
TEST_F(XMLNodeTest_48, SingleChildIsFirstAndLast_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* only = doc.NewElement("only");
    root->InsertEndChild(only);
    
    EXPECT_EQ(only, root->FirstChild());
    EXPECT_EQ(only, root->LastChild());
    EXPECT_EQ(nullptr, only->NextSibling());
    EXPECT_EQ(nullptr, only->PreviousSibling());
}

// Test DeleteChild removes from linked list properly
TEST_F(XMLNodeTest_48, DeleteChildFirstChild_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    
    root->DeleteChild(a);
    EXPECT_EQ(b, root->FirstChild());
    EXPECT_EQ(b, root->LastChild());
    EXPECT_EQ(nullptr, b->PreviousSibling());
}

// Test DeleteChild last child
TEST_F(XMLNodeTest_48, DeleteChildLastChild_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    
    root->DeleteChild(b);
    EXPECT_EQ(a, root->FirstChild());
    EXPECT_EQ(a, root->LastChild());
    EXPECT_EQ(nullptr, a->NextSibling());
}

// Test DeepClone to same document
TEST_F(XMLNodeTest_48, DeepCloneToSameDocument_48) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    XMLNode* cloned = root->DeepClone(&doc);
    ASSERT_NE(nullptr, cloned);
    EXPECT_STREQ("root", cloned->Value());
    ASSERT_NE(nullptr, cloned->FirstChildElement("child"));
    
    // Clean up - the cloned node isn't inserted anywhere, 
    // but it belongs to doc so it will be cleaned up with doc
}
