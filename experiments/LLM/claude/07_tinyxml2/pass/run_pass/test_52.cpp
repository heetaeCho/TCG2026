#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_52 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test that a new document has no children
TEST_F(XMLNodeTest_52, NewDocumentHasNoChildren_52) {
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(doc.FirstChild(), nullptr);
    EXPECT_EQ(doc.LastChild(), nullptr);
}

// Test FirstChild returns nullptr when no children exist
TEST_F(XMLNodeTest_52, FirstChildReturnsNullWhenEmpty_52) {
    const XMLNode* firstChild = doc.FirstChild();
    EXPECT_EQ(firstChild, nullptr);
}

// Test LastChild returns nullptr when no children exist
TEST_F(XMLNodeTest_52, LastChildReturnsNullWhenEmpty_52) {
    const XMLNode* lastChild = doc.LastChild();
    EXPECT_EQ(lastChild, nullptr);
}

// Test InsertEndChild adds a child
TEST_F(XMLNodeTest_52, InsertEndChildAddsChild_52) {
    XMLElement* elem = doc.NewElement("test");
    XMLNode* result = doc.InsertEndChild(elem);
    EXPECT_NE(result, nullptr);
    EXPECT_FALSE(doc.NoChildren());
    EXPECT_EQ(doc.FirstChild(), elem);
    EXPECT_EQ(doc.LastChild(), elem);
}

// Test InsertFirstChild adds a child at the beginning
TEST_F(XMLNodeTest_52, InsertFirstChildAddsChildAtBeginning_52) {
    XMLElement* elem1 = doc.NewElement("first");
    XMLElement* elem2 = doc.NewElement("second");
    doc.InsertEndChild(elem1);
    doc.InsertFirstChild(elem2);
    EXPECT_EQ(doc.FirstChild(), elem2);
    EXPECT_EQ(doc.LastChild(), elem1);
}

// Test InsertAfterChild inserts in the correct position
TEST_F(XMLNodeTest_52, InsertAfterChildInsertsCorrectly_52) {
    XMLElement* elem1 = doc.NewElement("first");
    XMLElement* elem2 = doc.NewElement("second");
    XMLElement* elem3 = doc.NewElement("third");
    doc.InsertEndChild(elem1);
    doc.InsertEndChild(elem3);
    doc.InsertAfterChild(elem1, elem2);
    
    const XMLNode* child = doc.FirstChild();
    EXPECT_EQ(child, elem1);
    child = child->NextSibling();
    EXPECT_EQ(child, elem2);
    child = child->NextSibling();
    EXPECT_EQ(child, elem3);
}

// Test DeleteChildren removes all children
TEST_F(XMLNodeTest_52, DeleteChildrenRemovesAllChildren_52) {
    XMLElement* elem1 = doc.NewElement("first");
    XMLElement* elem2 = doc.NewElement("second");
    doc.InsertEndChild(elem1);
    doc.InsertEndChild(elem2);
    EXPECT_FALSE(doc.NoChildren());
    doc.DeleteChildren();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(doc.FirstChild(), nullptr);
}

// Test DeleteChild removes specific child
TEST_F(XMLNodeTest_52, DeleteChildRemovesSpecificChild_52) {
    XMLElement* elem1 = doc.NewElement("first");
    XMLElement* elem2 = doc.NewElement("second");
    XMLElement* elem3 = doc.NewElement("third");
    doc.InsertEndChild(elem1);
    doc.InsertEndChild(elem2);
    doc.InsertEndChild(elem3);
    
    doc.DeleteChild(elem2);
    
    const XMLNode* child = doc.FirstChild();
    EXPECT_EQ(child, elem1);
    child = child->NextSibling();
    EXPECT_EQ(child, elem3);
    EXPECT_EQ(child->NextSibling(), nullptr);
}

// Test NoChildren returns true for empty node
TEST_F(XMLNodeTest_52, NoChildrenReturnsTrueWhenEmpty_52) {
    EXPECT_TRUE(doc.NoChildren());
}

// Test NoChildren returns false when children exist
TEST_F(XMLNodeTest_52, NoChildrenReturnsFalseWhenChildrenExist_52) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_FALSE(doc.NoChildren());
}

// Test Value and SetValue
TEST_F(XMLNodeTest_52, SetValueAndGetValue_52) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertEndChild(elem);
    EXPECT_STREQ(elem->Value(), "original");
    elem->SetValue("changed", false);
    EXPECT_STREQ(elem->Value(), "changed");
}

// Test SetValue with static memory
TEST_F(XMLNodeTest_52, SetValueStaticMem_52) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertEndChild(elem);
    elem->SetValue("static_value", true);
    EXPECT_STREQ(elem->Value(), "static_value");
}

// Test Parent returns correct parent
TEST_F(XMLNodeTest_52, ParentReturnsCorrectParent_52) {
    XMLElement* parent = doc.NewElement("parent");
    XMLElement* child = doc.NewElement("child");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(child);
    EXPECT_EQ(child->Parent(), parent);
}

// Test Parent returns nullptr for root children
TEST_F(XMLNodeTest_52, ParentOfRootChildIsDocument_52) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(elem->Parent(), &doc);
}

// Test NextSibling and PreviousSibling
TEST_F(XMLNodeTest_52, SiblingNavigation_52) {
    XMLElement* elem1 = doc.NewElement("first");
    XMLElement* elem2 = doc.NewElement("second");
    XMLElement* elem3 = doc.NewElement("third");
    doc.InsertEndChild(elem1);
    doc.InsertEndChild(elem2);
    doc.InsertEndChild(elem3);
    
    EXPECT_EQ(elem1->NextSibling(), elem2);
    EXPECT_EQ(elem2->NextSibling(), elem3);
    EXPECT_EQ(elem3->NextSibling(), nullptr);
    
    EXPECT_EQ(elem3->PreviousSibling(), elem2);
    EXPECT_EQ(elem2->PreviousSibling(), elem1);
    EXPECT_EQ(elem1->PreviousSibling(), nullptr);
}

// Test FirstChildElement with name filter
TEST_F(XMLNodeTest_52, FirstChildElementWithNameFilter_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    XMLElement* child3 = doc.NewElement("alpha");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->InsertEndChild(child3);
    
    const XMLElement* found = parent->FirstChildElement("beta");
    EXPECT_EQ(found, child2);
    
    const XMLElement* foundAlpha = parent->FirstChildElement("alpha");
    EXPECT_EQ(foundAlpha, child1);
}

// Test FirstChildElement with no name returns first element
TEST_F(XMLNodeTest_52, FirstChildElementNoNameReturnsFirst_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    
    const XMLElement* found = parent->FirstChildElement();
    EXPECT_EQ(found, child1);
}

// Test FirstChildElement returns nullptr when not found
TEST_F(XMLNodeTest_52, FirstChildElementReturnsNullWhenNotFound_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child = doc.NewElement("alpha");
    parent->InsertEndChild(child);
    
    const XMLElement* found = parent->FirstChildElement("nonexistent");
    EXPECT_EQ(found, nullptr);
}

// Test LastChildElement with name filter
TEST_F(XMLNodeTest_52, LastChildElementWithNameFilter_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    XMLElement* child3 = doc.NewElement("alpha");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->InsertEndChild(child3);
    
    const XMLElement* found = parent->LastChildElement("alpha");
    EXPECT_EQ(found, child3);
}

// Test LastChildElement with no name returns last element
TEST_F(XMLNodeTest_52, LastChildElementNoNameReturnsLast_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    
    const XMLElement* found = parent->LastChildElement();
    EXPECT_EQ(found, child2);
}

// Test NextSiblingElement with name filter
TEST_F(XMLNodeTest_52, NextSiblingElementWithNameFilter_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    XMLElement* child3 = doc.NewElement("alpha");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->InsertEndChild(child3);
    
    const XMLElement* found = child1->NextSiblingElement("alpha");
    EXPECT_EQ(found, child3);
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLNodeTest_52, PreviousSiblingElementWithNameFilter_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    XMLElement* child3 = doc.NewElement("alpha");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->InsertEndChild(child3);
    
    const XMLElement* found = child3->PreviousSiblingElement("alpha");
    EXPECT_EQ(found, child1);
}

// Test ChildElementCount
TEST_F(XMLNodeTest_52, ChildElementCountReturnsCorrectCount_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    EXPECT_EQ(parent->ChildElementCount(), 0);
    
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    XMLElement* child3 = doc.NewElement("alpha");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->InsertEndChild(child3);
    
    EXPECT_EQ(parent->ChildElementCount(), 3);
}

// Test ChildElementCount with name filter
TEST_F(XMLNodeTest_52, ChildElementCountWithNameFilter_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    XMLElement* child3 = doc.NewElement("alpha");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->InsertEndChild(child3);
    
    EXPECT_EQ(parent->ChildElementCount("alpha"), 2);
    EXPECT_EQ(parent->ChildElementCount("beta"), 1);
    EXPECT_EQ(parent->ChildElementCount("gamma"), 0);
}

// Test GetDocument returns the owning document
TEST_F(XMLNodeTest_52, GetDocumentReturnsOwningDocument_52) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(elem->GetDocument(), &doc);
}

// Test DeepClone
TEST_F(XMLNodeTest_52, DeepCloneCreatesIndependentCopy_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    
    XMLDocument doc2;
    XMLNode* cloned = parent->DeepClone(&doc2);
    doc2.InsertEndChild(cloned);
    
    EXPECT_NE(cloned, nullptr);
    EXPECT_STREQ(cloned->Value(), "parent");
    EXPECT_FALSE(cloned->NoChildren());
    EXPECT_STREQ(cloned->FirstChild()->Value(), "child");
    
    // Verify independence
    parent->DeleteChildren();
    EXPECT_TRUE(parent->NoChildren());
    EXPECT_FALSE(cloned->NoChildren());
}

// Test UserData
TEST_F(XMLNodeTest_52, UserDataSetAndGet_52) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    EXPECT_EQ(elem->GetUserData(), nullptr);
    
    int data = 42;
    elem->SetUserData(&data);
    EXPECT_EQ(elem->GetUserData(), &data);
    EXPECT_EQ(*static_cast<int*>(elem->GetUserData()), 42);
}

// Test UserData default is nullptr
TEST_F(XMLNodeTest_52, UserDataDefaultIsNull_52) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(elem->GetUserData(), nullptr);
}

// Test ToElement returns non-null for elements
TEST_F(XMLNodeTest_52, ToElementReturnsNonNullForElement_52) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_NE(elem->ToElement(), nullptr);
    EXPECT_EQ(elem->ToText(), nullptr);
    EXPECT_EQ(elem->ToComment(), nullptr);
    EXPECT_EQ(elem->ToDocument(), nullptr);
    EXPECT_EQ(elem->ToDeclaration(), nullptr);
    EXPECT_EQ(elem->ToUnknown(), nullptr);
}

// Test ToDocument returns non-null for document
TEST_F(XMLNodeTest_52, ToDocumentReturnsNonNullForDocument_52) {
    EXPECT_NE(doc.ToDocument(), nullptr);
    EXPECT_EQ(doc.ToElement(), nullptr);
}

// Test LinkEndChild (same as InsertEndChild)
TEST_F(XMLNodeTest_52, LinkEndChildAddsChild_52) {
    XMLElement* elem = doc.NewElement("test");
    XMLNode* result = doc.LinkEndChild(elem);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(doc.FirstChild(), elem);
}

// Test multiple inserts maintain order
TEST_F(XMLNodeTest_52, MultipleInsertsMaintainOrder_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    for (int i = 0; i < 10; ++i) {
        char name[32];
        snprintf(name, sizeof(name), "child%d", i);
        XMLElement* child = doc.NewElement(name);
        parent->InsertEndChild(child);
    }
    
    EXPECT_EQ(parent->ChildElementCount(), 10);
    
    const XMLNode* node = parent->FirstChild();
    EXPECT_STREQ(node->Value(), "child0");
    
    node = parent->LastChild();
    EXPECT_STREQ(node->Value(), "child9");
}

// Test InsertFirstChild with multiple children
TEST_F(XMLNodeTest_52, InsertFirstChildMultipleTimes_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("first");
    XMLElement* child2 = doc.NewElement("second");
    XMLElement* child3 = doc.NewElement("third");
    
    parent->InsertFirstChild(child1);
    parent->InsertFirstChild(child2);
    parent->InsertFirstChild(child3);
    
    // Order should be: third, second, first
    const XMLNode* node = parent->FirstChild();
    EXPECT_STREQ(node->Value(), "third");
    node = node->NextSibling();
    EXPECT_STREQ(node->Value(), "second");
    node = node->NextSibling();
    EXPECT_STREQ(node->Value(), "first");
    EXPECT_EQ(node->NextSibling(), nullptr);
}

// Test InsertAfterChild at the end
TEST_F(XMLNodeTest_52, InsertAfterChildAtEnd_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("first");
    XMLElement* child2 = doc.NewElement("second");
    parent->InsertEndChild(child1);
    parent->InsertAfterChild(child1, child2);
    
    EXPECT_EQ(parent->LastChild(), child2);
    EXPECT_EQ(child1->NextSibling(), child2);
}

// Test DeleteChild - deleting first child
TEST_F(XMLNodeTest_52, DeleteFirstChild_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("first");
    XMLElement* child2 = doc.NewElement("second");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    
    parent->DeleteChild(child1);
    EXPECT_EQ(parent->FirstChild(), child2);
    EXPECT_EQ(parent->ChildElementCount(), 1);
}

// Test DeleteChild - deleting last child
TEST_F(XMLNodeTest_52, DeleteLastChild_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("first");
    XMLElement* child2 = doc.NewElement("second");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    
    parent->DeleteChild(child2);
    EXPECT_EQ(parent->LastChild(), child1);
    EXPECT_EQ(parent->ChildElementCount(), 1);
}

// Test DeleteChildren on empty node
TEST_F(XMLNodeTest_52, DeleteChildrenOnEmptyNode_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    // Should not crash
    parent->DeleteChildren();
    EXPECT_TRUE(parent->NoChildren());
}

// Test GetLineNum
TEST_F(XMLNodeTest_52, GetLineNumForParsedDocument_52) {
    const char* xml = "<root>\n<child/>\n</root>";
    XMLDocument doc2;
    doc2.Parse(xml);
    EXPECT_EQ(doc2.ErrorID(), XML_SUCCESS);
    
    const XMLElement* root = doc2.FirstChildElement("root");
    EXPECT_NE(root, nullptr);
    EXPECT_EQ(root->GetLineNum(), 1);
    
    const XMLElement* child = root->FirstChildElement("child");
    EXPECT_NE(child, nullptr);
    EXPECT_EQ(child->GetLineNum(), 2);
}

// Test parsing and tree structure
TEST_F(XMLNodeTest_52, ParseAndNavigateTree_52) {
    const char* xml = "<root><a><b/></a><c/></root>";
    doc.Parse(xml);
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    
    const XMLElement* root = doc.FirstChildElement("root");
    EXPECT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 2);
    
    const XMLElement* a = root->FirstChildElement("a");
    EXPECT_NE(a, nullptr);
    
    const XMLElement* b = a->FirstChildElement("b");
    EXPECT_NE(b, nullptr);
    EXPECT_TRUE(b->NoChildren());
    
    const XMLElement* c = root->LastChildElement("c");
    EXPECT_NE(c, nullptr);
}

// Test DeepClone to same document
TEST_F(XMLNodeTest_52, DeepCloneToSameDocument_52) {
    const char* xml = "<root><child attr=\"val\">text</child></root>";
    doc.Parse(xml);
    
    const XMLElement* root = doc.FirstChildElement("root");
    XMLNode* cloned = root->DeepClone(&doc);
    EXPECT_NE(cloned, nullptr);
    EXPECT_STREQ(cloned->Value(), "root");
    
    // Clean up by inserting into doc
    doc.InsertEndChild(cloned);
}

// Test ShallowEqual
TEST_F(XMLNodeTest_52, ShallowEqualComparison_52) {
    const char* xml1 = "<root><child/></root>";
    XMLDocument doc1;
    doc1.Parse(xml1);
    
    const char* xml2 = "<root><child/></root>";
    XMLDocument doc2;
    doc2.Parse(xml2);
    
    const XMLNode* node1 = doc1.FirstChildElement("root");
    const XMLNode* node2 = doc2.FirstChildElement("root");
    
    EXPECT_TRUE(node1->ShallowEqual(node2));
}

// Test ShallowEqual with different nodes
TEST_F(XMLNodeTest_52, ShallowEqualDifferentNodes_52) {
    const char* xml1 = "<root/>";
    XMLDocument doc1;
    doc1.Parse(xml1);
    
    const char* xml2 = "<other/>";
    XMLDocument doc2;
    doc2.Parse(xml2);
    
    const XMLNode* node1 = doc1.FirstChildElement("root");
    const XMLNode* node2 = doc2.FirstChildElement("other");
    
    EXPECT_FALSE(node1->ShallowEqual(node2));
}

// Test with text nodes
TEST_F(XMLNodeTest_52, TextNodeNavigation_52) {
    const char* xml = "<root>Hello World</root>";
    doc.Parse(xml);
    
    const XMLElement* root = doc.FirstChildElement("root");
    EXPECT_NE(root, nullptr);
    
    const XMLNode* textNode = root->FirstChild();
    EXPECT_NE(textNode, nullptr);
    EXPECT_STREQ(textNode->Value(), "Hello World");
}

// Test with comment nodes
TEST_F(XMLNodeTest_52, CommentNodeNavigation_52) {
    const char* xml = "<root><!-- comment --><child/></root>";
    doc.Parse(xml);
    
    const XMLElement* root = doc.FirstChildElement("root");
    EXPECT_NE(root, nullptr);
    
    const XMLNode* first = root->FirstChild();
    EXPECT_NE(first, nullptr);
    EXPECT_NE(first->ToComment(), nullptr);
}

// Test NextSiblingElement with no match returns nullptr
TEST_F(XMLNodeTest_52, NextSiblingElementNoMatch_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    
    const XMLElement* found = child1->NextSiblingElement("gamma");
    EXPECT_EQ(found, nullptr);
}

// Test PreviousSiblingElement with no match returns nullptr
TEST_F(XMLNodeTest_52, PreviousSiblingElementNoMatch_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    
    const XMLElement* found = child2->PreviousSiblingElement("gamma");
    EXPECT_EQ(found, nullptr);
}

// Test single child - first and last are the same
TEST_F(XMLNodeTest_52, SingleChildFirstAndLastAreSame_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child = doc.NewElement("only");
    parent->InsertEndChild(child);
    
    EXPECT_EQ(parent->FirstChild(), parent->LastChild());
    EXPECT_EQ(parent->FirstChildElement(), parent->LastChildElement());
}

// Test ChildElementCount with name on empty parent
TEST_F(XMLNodeTest_52, ChildElementCountWithNameOnEmptyParent_52) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    EXPECT_EQ(parent->ChildElementCount("anything"), 0);
    EXPECT_EQ(parent->ChildElementCount(), 0);
}

// Test document Value
TEST_F(XMLNodeTest_52, DocumentValue_52) {
    // XMLDocument's value is typically empty or implementation-defined
    // Just ensure it doesn't crash
    const char* val = doc.Value();
    EXPECT_NE(val, nullptr);
}

// Test that inserting a node from the same document reparents it
TEST_F(XMLNodeTest_52, InsertReparentsNode_52) {
    XMLElement* parent1 = doc.NewElement("parent1");
    XMLElement* parent2 = doc.NewElement("parent2");
    XMLElement* child = doc.NewElement("child");
    doc.InsertEndChild(parent1);
    doc.InsertEndChild(parent2);
    parent1->InsertEndChild(child);
    
    EXPECT_EQ(child->Parent(), parent1);
    
    // Move child to parent2
    parent2->InsertEndChild(child);
    
    EXPECT_EQ(child->Parent(), parent2);
    EXPECT_TRUE(parent1->NoChildren());
    EXPECT_FALSE(parent2->NoChildren());
}
