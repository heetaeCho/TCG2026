#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_58 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test NextSibling returns null when there is no sibling
TEST_F(XMLNodeTest_58, NextSiblingReturnsNullWhenNoSibling_58) {
    doc.Parse("<root><child/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->NextSibling(), nullptr);
}

// Test NextSibling returns the next sibling when it exists
TEST_F(XMLNodeTest_58, NextSiblingReturnsNextSiblingWhenExists_58) {
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* a = root->FirstChild();
    ASSERT_NE(a, nullptr);
    const XMLNode* b = a->NextSibling();
    ASSERT_NE(b, nullptr);
    const XMLNode* c = b->NextSibling();
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->NextSibling(), nullptr);
}

// Test FirstChild and LastChild
TEST_F(XMLNodeTest_58, FirstChildAndLastChild_58) {
    doc.Parse("<root><first/><middle/><last/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLNode* first = root->FirstChild();
    const XMLNode* last = root->LastChild();
    ASSERT_NE(first, nullptr);
    ASSERT_NE(last, nullptr);
    EXPECT_NE(first, last);
}

// Test NoChildren returns true for empty element
TEST_F(XMLNodeTest_58, NoChildrenReturnsTrueForEmptyElement_58) {
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(root->NoChildren());
}

// Test NoChildren returns false when children exist
TEST_F(XMLNodeTest_58, NoChildrenReturnsFalseWhenChildrenExist_58) {
    doc.Parse("<root><child/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_FALSE(root->NoChildren());
}

// Test Parent
TEST_F(XMLNodeTest_58, ParentReturnsCorrectParent_58) {
    doc.Parse("<root><child/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->Parent(), root);
}

// Test root's parent is the document
TEST_F(XMLNodeTest_58, RootParentIsDocument_58) {
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Parent(), &doc);
}

// Test PreviousSibling
TEST_F(XMLNodeTest_58, PreviousSiblingReturnsCorrectNode_58) {
    doc.Parse("<root><a/><b/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* a = root->FirstChild();
    ASSERT_NE(a, nullptr);
    const XMLNode* b = a->NextSibling();
    ASSERT_NE(b, nullptr);
    EXPECT_EQ(b->PreviousSibling(), a);
    EXPECT_EQ(a->PreviousSibling(), nullptr);
}

// Test Value
TEST_F(XMLNodeTest_58, ValueReturnsElementName_58) {
    doc.Parse("<root><child/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Value(), "root");
}

// Test SetValue
TEST_F(XMLNodeTest_58, SetValueChangesValue_58) {
    doc.Parse("<root><child/></root>");
    XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetValue("newname", false);
    EXPECT_STREQ(root->Value(), "newname");
}

// Test FirstChildElement with name filter
TEST_F(XMLNodeTest_58, FirstChildElementWithNameFilter_58) {
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Value(), "b");
}

// Test FirstChildElement with no match
TEST_F(XMLNodeTest_58, FirstChildElementNoMatch_58) {
    doc.Parse("<root><a/><b/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* z = root->FirstChildElement("z");
    EXPECT_EQ(z, nullptr);
}

// Test LastChildElement
TEST_F(XMLNodeTest_58, LastChildElementReturnsLastMatch_58) {
    doc.Parse("<root><a/><b/><a/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* lastA = root->LastChildElement("a");
    ASSERT_NE(lastA, nullptr);
    // The last 'a' should not have a next sibling element named 'a'
    EXPECT_EQ(lastA->NextSiblingElement("a"), nullptr);
}

// Test NextSiblingElement with name
TEST_F(XMLNodeTest_58, NextSiblingElementWithName_58) {
    doc.Parse("<root><a/><b/><a id='2'/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* firstA = root->FirstChildElement("a");
    ASSERT_NE(firstA, nullptr);
    const XMLElement* secondA = firstA->NextSiblingElement("a");
    ASSERT_NE(secondA, nullptr);
    EXPECT_STREQ(secondA->Value(), "a");
}

// Test PreviousSiblingElement with name
TEST_F(XMLNodeTest_58, PreviousSiblingElementWithName_58) {
    doc.Parse("<root><a/><b/><a/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* lastA = root->LastChildElement("a");
    ASSERT_NE(lastA, nullptr);
    const XMLElement* firstA = lastA->PreviousSiblingElement("a");
    ASSERT_NE(firstA, nullptr);
    EXPECT_EQ(firstA, root->FirstChildElement("a"));
}

// Test InsertEndChild
TEST_F(XMLNodeTest_58, InsertEndChildAddsToEnd_58) {
    doc.Parse("<root><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* newChild = doc.NewElement("b");
    XMLNode* result = root->InsertEndChild(newChild);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(root->LastChildElement("b"), newChild);
}

// Test InsertFirstChild
TEST_F(XMLNodeTest_58, InsertFirstChildAddsToFront_58) {
    doc.Parse("<root><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* newChild = doc.NewElement("b");
    XMLNode* result = root->InsertFirstChild(newChild);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(root->FirstChild(), newChild);
}

// Test InsertAfterChild
TEST_F(XMLNodeTest_58, InsertAfterChildInsertsCorrectly_58) {
    doc.Parse("<root><a/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* b = doc.NewElement("b");
    XMLNode* result = root->InsertAfterChild(a, b);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(a->NextSibling(), b);
}

// Test DeleteChildren
TEST_F(XMLNodeTest_58, DeleteChildrenRemovesAllChildren_58) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_FALSE(root->NoChildren());
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

// Test DeleteChild
TEST_F(XMLNodeTest_58, DeleteChildRemovesSpecificChild_58) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    root->DeleteChild(b);
    EXPECT_EQ(root->FirstChildElement("b"), nullptr);
}

// Test ChildElementCount with no filter
TEST_F(XMLNodeTest_58, ChildElementCountReturnsCorrectCount_58) {
    doc.Parse("<root><a/><b/><c/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 3);
}

// Test ChildElementCount with name filter
TEST_F(XMLNodeTest_58, ChildElementCountWithNameFilter_58) {
    doc.Parse("<root><a/><b/><a/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount("a"), 2);
    EXPECT_EQ(root->ChildElementCount("b"), 1);
    EXPECT_EQ(root->ChildElementCount("z"), 0);
}

// Test ChildElementCount on empty element
TEST_F(XMLNodeTest_58, ChildElementCountOnEmptyElement_58) {
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 0);
}

// Test GetDocument
TEST_F(XMLNodeTest_58, GetDocumentReturnsOwningDocument_58) {
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetDocument(), &doc);
}

// Test DeepClone
TEST_F(XMLNodeTest_58, DeepCloneCreatesIndependentCopy_58) {
    doc.Parse("<root><a><b/></a></root>");
    XMLDocument targetDoc;
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);
    
    const XMLElement* cloneRoot = targetDoc.FirstChildElement("root");
    ASSERT_NE(cloneRoot, nullptr);
    const XMLElement* cloneA = cloneRoot->FirstChildElement("a");
    ASSERT_NE(cloneA, nullptr);
    const XMLElement* cloneB = cloneA->FirstChildElement("b");
    ASSERT_NE(cloneB, nullptr);
}

// Test UserData
TEST_F(XMLNodeTest_58, UserDataSetAndGet_58) {
    doc.Parse("<root/>");
    XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    EXPECT_EQ(root->GetUserData(), nullptr);
    
    int myData = 42;
    root->SetUserData(&myData);
    EXPECT_EQ(root->GetUserData(), &myData);
}

// Test ToElement on element node
TEST_F(XMLNodeTest_58, ToElementReturnsNonNullForElement_58) {
    doc.Parse("<root/>");
    XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_NE(root->ToElement(), nullptr);
    EXPECT_EQ(root->ToText(), nullptr);
    EXPECT_EQ(root->ToComment(), nullptr);
    EXPECT_EQ(root->ToDeclaration(), nullptr);
    EXPECT_EQ(root->ToUnknown(), nullptr);
}

// Test ToDocument on document node
TEST_F(XMLNodeTest_58, ToDocumentReturnsNonNullForDocument_58) {
    XMLNode* docNode = &doc;
    EXPECT_NE(docNode->ToDocument(), nullptr);
    EXPECT_EQ(docNode->ToElement(), nullptr);
}

// Test ToComment on comment node
TEST_F(XMLNodeTest_58, ToCommentReturnsNonNullForComment_58) {
    doc.Parse("<root><!-- comment --></root>");
    XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_NE(child->ToComment(), nullptr);
    EXPECT_EQ(child->ToElement(), nullptr);
}

// Test ToText on text node
TEST_F(XMLNodeTest_58, ToTextReturnsNonNullForText_58) {
    doc.Parse("<root>hello</root>");
    XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_NE(child->ToText(), nullptr);
    EXPECT_EQ(child->ToElement(), nullptr);
}

// Test ToDeclaration on declaration node
TEST_F(XMLNodeTest_58, ToDeclarationReturnsNonNullForDeclaration_58) {
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    XMLNode* child = doc.FirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_NE(child->ToDeclaration(), nullptr);
}

// Test NextSibling traversal through all siblings
TEST_F(XMLNodeTest_58, NextSiblingTraversalComplete_58) {
    doc.Parse("<root><a/><b/><c/><d/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    int count = 0;
    for (const XMLNode* node = root->FirstChild(); node != nullptr; node = node->NextSibling()) {
        count++;
    }
    EXPECT_EQ(count, 4);
}

// Test NextSibling on document level with multiple root-level items
TEST_F(XMLNodeTest_58, NextSiblingAtDocumentLevel_58) {
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    const XMLNode* first = doc.FirstChild();
    ASSERT_NE(first, nullptr);
    const XMLNode* second = first->NextSibling();
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second->NextSibling(), nullptr);
}

// Test InsertEndChild with null returns null or handles gracefully
TEST_F(XMLNodeTest_58, InsertAfterChildWithNullAfterThis_58) {
    doc.Parse("<root><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* newElem = doc.NewElement("b");
    // InsertAfterChild with null afterThis should behave consistently
    // (implementation-defined, but shouldn't crash)
    XMLNode* result = root->InsertAfterChild(nullptr, newElem);
    // Result may be null if afterThis is required to be valid
    // We just verify it doesn't crash
    (void)result;
}

// Test LinkEndChild (alias for InsertEndChild)
TEST_F(XMLNodeTest_58, LinkEndChildAddsChild_58) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child = doc.NewElement("linked");
    XMLNode* result = root->LinkEndChild(child);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(root->FirstChildElement("linked"), child);
}

// Test GetLineNum returns non-negative
TEST_F(XMLNodeTest_58, GetLineNumReturnsNonNegative_58) {
    doc.Parse("<root>\n<child/>\n</root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_GE(root->GetLineNum(), 1);
    const XMLNode* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_GE(child->GetLineNum(), 1);
}

// Test ShallowEqual on matching elements
TEST_F(XMLNodeTest_58, ShallowEqualOnSimilarElements_58) {
    doc.Parse("<root><a x='1'/></root>");
    XMLDocument doc2;
    doc2.Parse("<root><a x='1'/></root>");
    
    const XMLNode* node1 = doc.FirstChildElement("root")->FirstChildElement("a");
    const XMLNode* node2 = doc2.FirstChildElement("root")->FirstChildElement("a");
    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    EXPECT_TRUE(node1->ShallowEqual(node2));
}

// Test ShallowEqual on different elements
TEST_F(XMLNodeTest_58, ShallowEqualOnDifferentElements_58) {
    doc.Parse("<root><a x='1'/></root>");
    XMLDocument doc2;
    doc2.Parse("<root><b y='2'/></root>");
    
    const XMLNode* node1 = doc.FirstChildElement("root")->FirstChildElement("a");
    const XMLNode* node2 = doc2.FirstChildElement("root")->FirstChildElement("b");
    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    EXPECT_FALSE(node1->ShallowEqual(node2));
}

// Test ShallowClone
TEST_F(XMLNodeTest_58, ShallowCloneCreatesShallowCopy_58) {
    doc.Parse("<root><a><b/></a></root>");
    XMLDocument targetDoc;
    const XMLNode* a = doc.FirstChildElement("root")->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    
    XMLNode* clone = a->ShallowClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);
    
    // Shallow clone should not have children
    EXPECT_TRUE(clone->NoChildren());
    EXPECT_STREQ(clone->Value(), "a");
}

// Test mixed content with text and elements
TEST_F(XMLNodeTest_58, MixedContentNextSibling_58) {
    doc.Parse("<root>text<a/>more</root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    ASSERT_NE(first->ToText(), nullptr);
    
    const XMLNode* second = first->NextSibling();
    ASSERT_NE(second, nullptr);
    ASSERT_NE(second->ToElement(), nullptr);
    
    const XMLNode* third = second->NextSibling();
    ASSERT_NE(third, nullptr);
    ASSERT_NE(third->ToText(), nullptr);
    
    EXPECT_EQ(third->NextSibling(), nullptr);
}

// Test SetValue with staticMem true
TEST_F(XMLNodeTest_58, SetValueStaticMem_58) {
    doc.Parse("<root/>");
    XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    static const char staticName[] = "staticname";
    root->SetValue(staticName, true);
    EXPECT_STREQ(root->Value(), "staticname");
}

// Test FirstChildElement with no argument (defaults to null)
TEST_F(XMLNodeTest_58, FirstChildElementNoArgument_58) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");
}

// Test LastChildElement with no argument
TEST_F(XMLNodeTest_58, LastChildElementNoArgument_58) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "b");
}

// Test NextSiblingElement with no argument
TEST_F(XMLNodeTest_58, NextSiblingElementNoArgument_58) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* next = a->NextSiblingElement();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Value(), "b");
}

// Test PreviousSiblingElement with no argument
TEST_F(XMLNodeTest_58, PreviousSiblingElementNoArgument_58) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* b = root->LastChildElement("b");
    ASSERT_NE(b, nullptr);
    XMLElement* prev = b->PreviousSiblingElement();
    ASSERT_NE(prev, nullptr);
    EXPECT_STREQ(prev->Value(), "a");
}

// Test inserting element from different document (cross-document insert should fail or handle)
TEST_F(XMLNodeTest_58, InsertChildFromDifferentDocument_58) {
    doc.Parse("<root/>");
    XMLDocument otherDoc;
    XMLElement* otherElem = otherDoc.NewElement("other");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    // Inserting a child from a different document - behavior is implementation-defined
    // but should not crash. Many implementations return null.
    // We just ensure it doesn't crash.
    XMLNode* result = root->InsertEndChild(otherElem);
    (void)result;
}

// Test Accept with XMLVisitor (using XMLPrinter as a concrete visitor)
TEST_F(XMLNodeTest_58, AcceptWithPrinter_58) {
    doc.Parse("<root><child/></root>");
    XMLPrinter printer;
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    bool result = root->Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // The output should contain "root" and "child"
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
    EXPECT_NE(std::string(output).find("child"), std::string::npos);
}
