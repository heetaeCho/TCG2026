#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_53 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that FirstChildElement returns nullptr when document is empty
TEST_F(XMLNodeTest_53, FirstChildElement_EmptyDocument_ReturnsNull_53) {
    XMLElement* result = doc.FirstChildElement();
    EXPECT_EQ(result, nullptr);
}

// Test that FirstChildElement with name returns nullptr when no matching element
TEST_F(XMLNodeTest_53, FirstChildElement_NoMatchingName_ReturnsNull_53) {
    doc.Parse("<root><child1/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* result = root->FirstChildElement("nonexistent");
    EXPECT_EQ(result, nullptr);
}

// Test that FirstChildElement returns the first child element
TEST_F(XMLNodeTest_53, FirstChildElement_ReturnsFirstChild_53) {
    doc.Parse("<root><child1/><child2/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Name(), "child1");
}

// Test that FirstChildElement with name returns matching element
TEST_F(XMLNodeTest_53, FirstChildElement_WithName_ReturnsMatchingChild_53) {
    doc.Parse("<root><child1/><child2/><child3/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* result = root->FirstChildElement("child2");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->Name(), "child2");
}

// Test LastChildElement returns last child element
TEST_F(XMLNodeTest_53, LastChildElement_ReturnsLastChild_53) {
    doc.Parse("<root><child1/><child2/><child3/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "child3");
}

// Test LastChildElement with name
TEST_F(XMLNodeTest_53, LastChildElement_WithName_ReturnsMatchingLast_53) {
    doc.Parse("<root><item/><other/><item/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* last = root->LastChildElement("item");
    ASSERT_NE(last, nullptr);
    // The last "item" should be the second one (third child overall)
    EXPECT_STREQ(last->Name(), "item");
    // Verify it's actually the last by checking no next sibling with same name
    EXPECT_EQ(last->NextSiblingElement("item"), nullptr);
}

// Test NextSiblingElement
TEST_F(XMLNodeTest_53, NextSiblingElement_ReturnsNextSibling_53) {
    doc.Parse("<root><child1/><child2/><child3/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    XMLElement* second = first->NextSiblingElement();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Name(), "child2");
}

// Test NextSiblingElement with name
TEST_F(XMLNodeTest_53, NextSiblingElement_WithName_ReturnsMatchingSibling_53) {
    doc.Parse("<root><a/><b/><c/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* first = root->FirstChildElement("a");
    ASSERT_NE(first, nullptr);
    XMLElement* bElem = first->NextSiblingElement("b");
    ASSERT_NE(bElem, nullptr);
    EXPECT_STREQ(bElem->Name(), "b");
}

// Test PreviousSiblingElement
TEST_F(XMLNodeTest_53, PreviousSiblingElement_ReturnsPreviousSibling_53) {
    doc.Parse("<root><child1/><child2/><child3/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    XMLElement* prev = last->PreviousSiblingElement();
    ASSERT_NE(prev, nullptr);
    EXPECT_STREQ(prev->Name(), "child2");
}

// Test PreviousSiblingElement with name
TEST_F(XMLNodeTest_53, PreviousSiblingElement_WithName_ReturnsMatchingPrevious_53) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* c = root->LastChildElement("c");
    ASSERT_NE(c, nullptr);
    XMLElement* a = c->PreviousSiblingElement("a");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Name(), "a");
}

// Test NoChildren returns true for empty element
TEST_F(XMLNodeTest_53, NoChildren_EmptyElement_ReturnsTrue_53) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(root->NoChildren());
}

// Test NoChildren returns false for element with children
TEST_F(XMLNodeTest_53, NoChildren_WithChildren_ReturnsFalse_53) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_FALSE(root->NoChildren());
}

// Test InsertEndChild
TEST_F(XMLNodeTest_53, InsertEndChild_AddsChildAtEnd_53) {
    doc.Parse("<root><child1/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* newChild = doc.NewElement("child2");
    XMLNode* result = root->InsertEndChild(newChild);
    ASSERT_NE(result, nullptr);
    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "child2");
}

// Test InsertFirstChild
TEST_F(XMLNodeTest_53, InsertFirstChild_AddsChildAtBeginning_53) {
    doc.Parse("<root><child2/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* newChild = doc.NewElement("child1");
    XMLNode* result = root->InsertFirstChild(newChild);
    ASSERT_NE(result, nullptr);
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Name(), "child1");
}

// Test InsertAfterChild
TEST_F(XMLNodeTest_53, InsertAfterChild_AddsChildAfterSpecified_53) {
    doc.Parse("<root><child1/><child3/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child1 = root->FirstChildElement("child1");
    ASSERT_NE(child1, nullptr);
    XMLElement* newChild = doc.NewElement("child2");
    XMLNode* result = root->InsertAfterChild(child1, newChild);
    ASSERT_NE(result, nullptr);
    XMLElement* second = child1->NextSiblingElement();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Name(), "child2");
}

// Test DeleteChildren
TEST_F(XMLNodeTest_53, DeleteChildren_RemovesAllChildren_53) {
    doc.Parse("<root><child1/><child2/><child3/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_FALSE(root->NoChildren());
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

// Test DeleteChild
TEST_F(XMLNodeTest_53, DeleteChild_RemovesSpecificChild_53) {
    doc.Parse("<root><child1/><child2/><child3/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child2 = root->FirstChildElement("child2");
    ASSERT_NE(child2, nullptr);
    root->DeleteChild(child2);
    XMLElement* result = root->FirstChildElement("child2");
    EXPECT_EQ(result, nullptr);
}

// Test Value
TEST_F(XMLNodeTest_53, Value_ReturnsElementName_53) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Value(), "root");
}

// Test SetValue
TEST_F(XMLNodeTest_53, SetValue_ChangesValue_53) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetValue("newroot", false);
    EXPECT_STREQ(root->Value(), "newroot");
}

// Test ChildElementCount with no children
TEST_F(XMLNodeTest_53, ChildElementCount_NoChildren_ReturnsZero_53) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 0);
}

// Test ChildElementCount with children
TEST_F(XMLNodeTest_53, ChildElementCount_WithChildren_ReturnsCount_53) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 3);
}

// Test ChildElementCount with name filter
TEST_F(XMLNodeTest_53, ChildElementCount_WithName_ReturnsFilteredCount_53) {
    doc.Parse("<root><item/><other/><item/><item/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount("item"), 3);
    EXPECT_EQ(root->ChildElementCount("other"), 1);
    EXPECT_EQ(root->ChildElementCount("nonexistent"), 0);
}

// Test GetDocument
TEST_F(XMLNodeTest_53, GetDocument_ReturnsOwnerDocument_53) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetDocument(), &doc);
}

// Test Parent
TEST_F(XMLNodeTest_53, Parent_ReturnsParentNode_53) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    const XMLNode* parent = child->Parent();
    ASSERT_NE(parent, nullptr);
    EXPECT_EQ(parent, root);
}

// Test FirstChild and LastChild
TEST_F(XMLNodeTest_53, FirstChild_LastChild_53) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* first = root->FirstChild();
    const XMLNode* last = root->LastChild();
    ASSERT_NE(first, nullptr);
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(first->Value(), "a");
    EXPECT_STREQ(last->Value(), "b");
}

// Test NextSibling and PreviousSibling
TEST_F(XMLNodeTest_53, NextSibling_PreviousSibling_53) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    const XMLNode* second = first->NextSibling();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Value(), "b");
    const XMLNode* backToFirst = second->PreviousSibling();
    ASSERT_NE(backToFirst, nullptr);
    EXPECT_EQ(backToFirst, first);
}

// Test DeepClone
TEST_F(XMLNodeTest_53, DeepClone_ClonesSubtree_53) {
    doc.Parse("<root><child attr=\"val\"><grandchild/></child></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLDocument targetDoc;
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);

    XMLElement* clonedRoot = targetDoc.FirstChildElement("root");
    ASSERT_NE(clonedRoot, nullptr);
    XMLElement* clonedChild = clonedRoot->FirstChildElement("child");
    ASSERT_NE(clonedChild, nullptr);
    EXPECT_STREQ(clonedChild->Attribute("attr"), "val");
    XMLElement* clonedGrandchild = clonedChild->FirstChildElement("grandchild");
    EXPECT_NE(clonedGrandchild, nullptr);
}

// Test UserData
TEST_F(XMLNodeTest_53, UserData_SetAndGet_53) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetUserData(), nullptr);
    int data = 42;
    root->SetUserData(&data);
    EXPECT_EQ(root->GetUserData(), &data);
}

// Test ToElement
TEST_F(XMLNodeTest_53, ToElement_ReturnsElement_53) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_NE(root->ToElement(), nullptr);
    EXPECT_EQ(root->ToText(), nullptr);
    EXPECT_EQ(root->ToComment(), nullptr);
    EXPECT_EQ(root->ToDocument(), nullptr);
    EXPECT_EQ(root->ToDeclaration(), nullptr);
    EXPECT_EQ(root->ToUnknown(), nullptr);
}

// Test LinkEndChild (alias for InsertEndChild)
TEST_F(XMLNodeTest_53, LinkEndChild_AddsChildAtEnd_53) {
    doc.Parse("<root><child1/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* newChild = doc.NewElement("child2");
    XMLNode* result = root->LinkEndChild(newChild);
    ASSERT_NE(result, nullptr);
    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Name(), "child2");
}

// Test FirstChildElement on document level
TEST_F(XMLNodeTest_53, FirstChildElement_DocumentLevel_53) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

// Test FirstChildElement with null name returns first element child
TEST_F(XMLNodeTest_53, FirstChildElement_NullName_ReturnsFirstElement_53) {
    doc.Parse("<root><alpha/><beta/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* first = root->FirstChildElement(nullptr);
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Name(), "alpha");
}

// Test NextSiblingElement returns nullptr when no more siblings
TEST_F(XMLNodeTest_53, NextSiblingElement_NoMoreSiblings_ReturnsNull_53) {
    doc.Parse("<root><only/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* only = root->FirstChildElement("only");
    ASSERT_NE(only, nullptr);
    EXPECT_EQ(only->NextSiblingElement(), nullptr);
}

// Test PreviousSiblingElement returns nullptr for first child
TEST_F(XMLNodeTest_53, PreviousSiblingElement_FirstChild_ReturnsNull_53) {
    doc.Parse("<root><first/><second/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* first = root->FirstChildElement("first");
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(first->PreviousSiblingElement(), nullptr);
}

// Test inserting child from different document
TEST_F(XMLNodeTest_53, InsertEndChild_DifferentDocument_ReturnsNull_53) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLDocument otherDoc;
    XMLElement* foreignChild = otherDoc.NewElement("foreign");
    // Inserting a node from a different document should fail
    XMLNode* result = root->InsertEndChild(foreignChild);
    EXPECT_EQ(result, nullptr);
}

// Test multiple levels of nesting with FirstChildElement
TEST_F(XMLNodeTest_53, FirstChildElement_DeepNesting_53) {
    doc.Parse("<a><b><c><d/></c></b></a>");
    XMLElement* a = doc.FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    XMLElement* c = b->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    XMLElement* d = c->FirstChildElement("d");
    ASSERT_NE(d, nullptr);
    EXPECT_STREQ(d->Name(), "d");
    EXPECT_TRUE(d->NoChildren());
}

// Test GetLineNum returns a non-negative value
TEST_F(XMLNodeTest_53, GetLineNum_ReturnsNonNegative_53) {
    doc.Parse("<root>\n<child/>\n</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_GE(root->GetLineNum(), 0);
}

// Test ShallowEqual
TEST_F(XMLNodeTest_53, ShallowEqual_SameElement_53) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* root2 = doc2.FirstChildElement("root");
    ASSERT_NE(root2, nullptr);

    EXPECT_TRUE(root->ShallowEqual(root2));
}

// Test ShallowEqual with different elements
TEST_F(XMLNodeTest_53, ShallowEqual_DifferentElements_53) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLDocument doc2;
    doc2.Parse("<other attr=\"val\"/>");
    XMLElement* other = doc2.FirstChildElement("other");
    ASSERT_NE(other, nullptr);

    EXPECT_FALSE(root->ShallowEqual(other));
}

// Test SetValue with staticMem true
TEST_F(XMLNodeTest_53, SetValue_StaticMem_53) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    static const char staticName[] = "staticroot";
    root->SetValue(staticName, true);
    EXPECT_STREQ(root->Value(), "staticroot");
}

// Test inserting into empty element
TEST_F(XMLNodeTest_53, InsertEndChild_EmptyElement_53) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(root->NoChildren());
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    EXPECT_FALSE(root->NoChildren());
    EXPECT_EQ(root->FirstChildElement(), root->LastChildElement());
}

// Test InsertFirstChild into element with existing children
TEST_F(XMLNodeTest_53, InsertFirstChild_ExistingChildren_53) {
    doc.Parse("<root><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* a = doc.NewElement("a");
    root->InsertFirstChild(a);
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Name(), "a");
    EXPECT_EQ(root->ChildElementCount(), 3);
}

// Test ChildElementCount after modifications
TEST_F(XMLNodeTest_53, ChildElementCount_AfterModifications_53) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 2);

    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(c);
    EXPECT_EQ(root->ChildElementCount(), 3);

    root->DeleteChild(root->FirstChildElement("a"));
    EXPECT_EQ(root->ChildElementCount(), 2);

    root->DeleteChildren();
    EXPECT_EQ(root->ChildElementCount(), 0);
}
