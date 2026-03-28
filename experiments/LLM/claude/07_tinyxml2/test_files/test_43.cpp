#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_43 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test ToElement on XMLNode base returns null
TEST_F(XMLNodeTest_43, ToElementOnDocumentReturnsNull_43) {
    // XMLDocument is an XMLNode, but ToElement should return null for non-element nodes
    XMLNode* node = &doc;
    EXPECT_EQ(nullptr, node->ToElement());
}

// Test that a newly created document has no children
TEST_F(XMLNodeTest_43, NewDocumentNoChildren_43) {
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(nullptr, doc.FirstChild());
    EXPECT_EQ(nullptr, doc.LastChild());
}

// Test creating an element and checking ToElement
TEST_F(XMLNodeTest_43, ElementToElementReturnsNonNull_43) {
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(nullptr, elem);
    EXPECT_NE(nullptr, elem->ToElement());
}

// Test InsertEndChild adds child
TEST_F(XMLNodeTest_43, InsertEndChildAddsChild_43) {
    XMLElement* elem = doc.NewElement("child");
    XMLNode* result = doc.InsertEndChild(elem);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(doc.NoChildren());
    EXPECT_EQ(elem, doc.FirstChild());
    EXPECT_EQ(elem, doc.LastChild());
}

// Test InsertFirstChild adds child at beginning
TEST_F(XMLNodeTest_43, InsertFirstChildAddsAtBeginning_43) {
    XMLElement* first = doc.NewElement("first");
    XMLElement* second = doc.NewElement("second");
    doc.InsertEndChild(second);
    doc.InsertFirstChild(first);
    EXPECT_EQ(first, doc.FirstChild());
    EXPECT_EQ(second, doc.LastChild());
}

// Test InsertAfterChild
TEST_F(XMLNodeTest_43, InsertAfterChildInsertsCorrectly_43) {
    XMLElement* first = doc.NewElement("first");
    XMLElement* third = doc.NewElement("third");
    XMLElement* second = doc.NewElement("second");
    doc.InsertEndChild(first);
    doc.InsertEndChild(third);
    doc.InsertAfterChild(first, second);
    
    EXPECT_EQ(first, doc.FirstChild());
    EXPECT_EQ(third, doc.LastChild());
    EXPECT_EQ(second, first->NextSibling());
    EXPECT_EQ(second, third->PreviousSibling());
}

// Test DeleteChildren removes all children
TEST_F(XMLNodeTest_43, DeleteChildrenRemovesAll_43) {
    doc.InsertEndChild(doc.NewElement("a"));
    doc.InsertEndChild(doc.NewElement("b"));
    doc.InsertEndChild(doc.NewElement("c"));
    EXPECT_FALSE(doc.NoChildren());
    doc.DeleteChildren();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(nullptr, doc.FirstChild());
    EXPECT_EQ(nullptr, doc.LastChild());
}

// Test DeleteChild removes specific child
TEST_F(XMLNodeTest_43, DeleteChildRemovesSpecificChild_43) {
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    doc.InsertEndChild(a);
    doc.InsertEndChild(b);
    doc.InsertEndChild(c);
    doc.DeleteChild(b);
    EXPECT_EQ(a, doc.FirstChild());
    EXPECT_EQ(c, doc.LastChild());
    EXPECT_EQ(c, a->NextSibling());
}

// Test Value and SetValue
TEST_F(XMLNodeTest_43, SetValueAndGetValue_43) {
    XMLElement* elem = doc.NewElement("original");
    ASSERT_NE(nullptr, elem);
    EXPECT_STREQ("original", elem->Value());
    elem->SetValue("modified", false);
    EXPECT_STREQ("modified", elem->Value());
}

// Test SetValue with staticMem = true
TEST_F(XMLNodeTest_43, SetValueStaticMem_43) {
    XMLElement* elem = doc.NewElement("test");
    const char* staticStr = "static_value";
    elem->SetValue(staticStr, true);
    EXPECT_STREQ("static_value", elem->Value());
}

// Test FirstChildElement with name filter
TEST_F(XMLNodeTest_43, FirstChildElementWithName_43) {
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
    EXPECT_EQ(nullptr, root->FirstChildElement("gamma"));
}

// Test FirstChildElement without name returns first element child
TEST_F(XMLNodeTest_43, FirstChildElementNoName_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("alpha");
    root->InsertEndChild(a);
    
    EXPECT_EQ(a, root->FirstChildElement());
}

// Test LastChildElement with name filter
TEST_F(XMLNodeTest_43, LastChildElementWithName_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a1 = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    XMLElement* a2 = doc.NewElement("alpha");
    root->InsertEndChild(a1);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);
    
    EXPECT_EQ(a2, root->LastChildElement("alpha"));
    EXPECT_EQ(b, root->LastChildElement("beta"));
}

// Test LastChildElement without name
TEST_F(XMLNodeTest_43, LastChildElementNoName_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    
    EXPECT_EQ(b, root->LastChildElement());
}

// Test NextSiblingElement
TEST_F(XMLNodeTest_43, NextSiblingElement_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);
    
    EXPECT_EQ(b, a->NextSiblingElement());
    EXPECT_EQ(c, b->NextSiblingElement());
    EXPECT_EQ(nullptr, c->NextSiblingElement());
}

// Test NextSiblingElement with name
TEST_F(XMLNodeTest_43, NextSiblingElementWithName_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* a2 = doc.NewElement("a");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);
    
    EXPECT_EQ(a2, a->NextSiblingElement("a"));
    EXPECT_EQ(b, a->NextSiblingElement("b"));
}

// Test PreviousSiblingElement
TEST_F(XMLNodeTest_43, PreviousSiblingElement_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);
    
    EXPECT_EQ(nullptr, a->PreviousSiblingElement());
    EXPECT_EQ(a, b->PreviousSiblingElement());
    EXPECT_EQ(b, c->PreviousSiblingElement());
}

// Test PreviousSiblingElement with name
TEST_F(XMLNodeTest_43, PreviousSiblingElementWithName_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* a2 = doc.NewElement("a");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);
    
    EXPECT_EQ(a, a2->PreviousSiblingElement("a"));
    EXPECT_EQ(b, a2->PreviousSiblingElement("b"));
}

// Test Parent
TEST_F(XMLNodeTest_43, ParentReturnsCorrectNode_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    EXPECT_EQ(root, child->Parent());
    EXPECT_EQ(&doc, root->Parent());
}

// Test GetDocument
TEST_F(XMLNodeTest_43, GetDocumentReturnsOwningDocument_43) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(&doc, elem->GetDocument());
}

// Test NoChildren on empty element
TEST_F(XMLNodeTest_43, NoChildrenOnEmptyElement_43) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_TRUE(elem->NoChildren());
}

// Test NoChildren on element with children
TEST_F(XMLNodeTest_43, NoChildrenReturnsFalseWhenHasChildren_43) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("child"));
    EXPECT_FALSE(parent->NoChildren());
}

// Test ChildElementCount with no children
TEST_F(XMLNodeTest_43, ChildElementCountZero_43) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(0, elem->ChildElementCount());
}

// Test ChildElementCount with multiple children
TEST_F(XMLNodeTest_43, ChildElementCountMultiple_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));
    EXPECT_EQ(3, root->ChildElementCount());
}

// Test ChildElementCount with name filter
TEST_F(XMLNodeTest_43, ChildElementCountWithNameFilter_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("a"));
    EXPECT_EQ(2, root->ChildElementCount("a"));
    EXPECT_EQ(1, root->ChildElementCount("b"));
    EXPECT_EQ(0, root->ChildElementCount("c"));
}

// Test UserData
TEST_F(XMLNodeTest_43, SetAndGetUserData_43) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    int data = 42;
    elem->SetUserData(&data);
    EXPECT_EQ(&data, elem->GetUserData());
}

// Test UserData default is null
TEST_F(XMLNodeTest_43, UserDataDefaultNull_43) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->GetUserData());
}

// Test DeepClone
TEST_F(XMLNodeTest_43, DeepCloneCreatesIndependentCopy_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    XMLElement* grandchild = doc.NewElement("grandchild");
    child->InsertEndChild(grandchild);
    
    XMLDocument doc2;
    XMLNode* cloned = root->DeepClone(&doc2);
    ASSERT_NE(nullptr, cloned);
    doc2.InsertEndChild(cloned);
    
    ASSERT_NE(nullptr, cloned->ToElement());
    EXPECT_STREQ("root", cloned->Value());
    ASSERT_NE(nullptr, cloned->FirstChildElement("child"));
    ASSERT_NE(nullptr, cloned->FirstChildElement("child")->FirstChildElement("grandchild"));
}

// Test ToText on element returns null
TEST_F(XMLNodeTest_43, ToTextOnElementReturnsNull_43) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->ToText());
}

// Test ToComment on element returns null
TEST_F(XMLNodeTest_43, ToCommentOnElementReturnsNull_43) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->ToComment());
}

// Test ToDocument on element returns null
TEST_F(XMLNodeTest_43, ToDocumentOnElementReturnsNull_43) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->ToDocument());
}

// Test ToDocument on document returns non-null
TEST_F(XMLNodeTest_43, ToDocumentOnDocumentReturnsNonNull_43) {
    XMLNode* node = &doc;
    EXPECT_NE(nullptr, node->ToDocument());
}

// Test ToDeclaration on element returns null
TEST_F(XMLNodeTest_43, ToDeclarationOnElementReturnsNull_43) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->ToDeclaration());
}

// Test ToUnknown on element returns null
TEST_F(XMLNodeTest_43, ToUnknownOnElementReturnsNull_43) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->ToUnknown());
}

// Test LinkEndChild (alias for InsertEndChild)
TEST_F(XMLNodeTest_43, LinkEndChildAddsChild_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->LinkEndChild(child);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(child, root->FirstChild());
}

// Test inserting multiple children and traversal via NextSibling
TEST_F(XMLNodeTest_43, TraversalViaNextSibling_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);
    
    const XMLNode* current = root->FirstChild();
    EXPECT_EQ(a, current);
    current = current->NextSibling();
    EXPECT_EQ(b, current);
    current = current->NextSibling();
    EXPECT_EQ(c, current);
    current = current->NextSibling();
    EXPECT_EQ(nullptr, current);
}

// Test traversal via PreviousSibling
TEST_F(XMLNodeTest_43, TraversalViaPreviousSibling_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);
    
    const XMLNode* current = root->LastChild();
    EXPECT_EQ(c, current);
    current = current->PreviousSibling();
    EXPECT_EQ(b, current);
    current = current->PreviousSibling();
    EXPECT_EQ(a, current);
    current = current->PreviousSibling();
    EXPECT_EQ(nullptr, current);
}

// Test InsertEndChild with null returns null
TEST_F(XMLNodeTest_43, InsertEndChildNull_43) {
    XMLNode* result = doc.InsertEndChild(nullptr);
    EXPECT_EQ(nullptr, result);
}

// Test InsertFirstChild with null returns null
TEST_F(XMLNodeTest_43, InsertFirstChildNull_43) {
    XMLNode* result = doc.InsertFirstChild(nullptr);
    EXPECT_EQ(nullptr, result);
}

// Test FirstChild and LastChild with single child are same
TEST_F(XMLNodeTest_43, SingleChildFirstAndLastSame_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* only = doc.NewElement("only");
    root->InsertEndChild(only);
    
    EXPECT_EQ(root->FirstChild(), root->LastChild());
}

// Test deep hierarchy
TEST_F(XMLNodeTest_43, DeepHierarchy_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* current = root;
    for (int i = 0; i < 10; i++) {
        XMLElement* child = doc.NewElement("level");
        current->InsertEndChild(child);
        current = child;
    }
    
    // Traverse back up
    const XMLNode* node = current;
    int depth = 0;
    while (node->Parent() != nullptr && node->Parent() != &doc) {
        node = node->Parent();
        depth++;
    }
    EXPECT_EQ(10, depth);
}

// Test parsing a simple XML via document
TEST_F(XMLNodeTest_43, ParseSimpleXML_43) {
    const char* xml = "<root><child/><child2>text</child2></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("root", root->Value());
    
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    
    XMLElement* child2 = root->FirstChildElement("child2");
    ASSERT_NE(nullptr, child2);
}

// Test GetLineNum is non-negative after parse
TEST_F(XMLNodeTest_43, GetLineNumAfterParse_43) {
    const char* xml = "<root>\n<child/>\n</root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    EXPECT_GE(root->GetLineNum(), 1);
    
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_GE(child->GetLineNum(), 1);
}

// Test DeleteChild on the only child makes parent empty
TEST_F(XMLNodeTest_43, DeleteOnlyChild_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    EXPECT_FALSE(root->NoChildren());
    root->DeleteChild(child);
    EXPECT_TRUE(root->NoChildren());
}

// Test InsertAfterChild with null afterThis
TEST_F(XMLNodeTest_43, InsertAfterChildNullAfterThis_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    
    // When afterThis is null, behavior may vary - test it doesn't crash
    XMLNode* result = root->InsertAfterChild(nullptr, child);
    // Implementation typically returns null when afterThis is null
    // But we just test it doesn't crash; result could be null
    (void)result;
}

// Test ShallowClone on an element
TEST_F(XMLNodeTest_43, ShallowCloneElement_43) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    elem->SetAttribute("attr", "value");
    
    XMLDocument doc2;
    const XMLNode* cloned = elem->ShallowClone(&doc2);
    ASSERT_NE(nullptr, cloned);
    EXPECT_STREQ("test", cloned->Value());
    // Shallow clone should not have children
    EXPECT_TRUE(cloned->NoChildren());
}

// Test that FirstChildElement returns null when no elements match
TEST_F(XMLNodeTest_43, FirstChildElementNoMatch_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("alpha"));
    
    EXPECT_EQ(nullptr, root->FirstChildElement("nonexistent"));
}

// Test that LastChildElement returns null when no elements match
TEST_F(XMLNodeTest_43, LastChildElementNoMatch_43) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("alpha"));
    
    EXPECT_EQ(nullptr, root->LastChildElement("nonexistent"));
}

// Test moving child between documents via DeepClone
TEST_F(XMLNodeTest_43, DeepCloneBetweenDocuments_43) {
    const char* xml = "<root><a><b>text</b></a></root>";
    doc.Parse(xml);
    
    XMLDocument doc2;
    XMLNode* cloned = doc.FirstChildElement("root")->DeepClone(&doc2);
    doc2.InsertEndChild(cloned);
    
    EXPECT_NE(nullptr, doc2.FirstChildElement("root"));
    EXPECT_NE(nullptr, doc2.FirstChildElement("root")->FirstChildElement("a"));
    EXPECT_NE(nullptr, doc2.FirstChildElement("root")->FirstChildElement("a")->FirstChildElement("b"));
}
