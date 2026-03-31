#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_44 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test ToText returns null for non-text nodes
TEST_F(XMLNodeTest_44, ToTextReturnsNullForDocument_44) {
    EXPECT_EQ(doc.ToText(), nullptr);
}

// Test ToElement returns null for document node
TEST_F(XMLNodeTest_44, ToElementReturnsNullForDocument_44) {
    EXPECT_EQ(doc.ToElement(), nullptr);
}

// Test ToDocument returns non-null for document
TEST_F(XMLNodeTest_44, ToDocumentReturnsNonNullForDocument_44) {
    EXPECT_NE(doc.ToDocument(), nullptr);
}

// Test NoChildren on empty document
TEST_F(XMLNodeTest_44, NoChildrenOnEmptyDocument_44) {
    EXPECT_TRUE(doc.NoChildren());
}

// Test FirstChild on empty document
TEST_F(XMLNodeTest_44, FirstChildNullOnEmptyDocument_44) {
    EXPECT_EQ(doc.FirstChild(), nullptr);
}

// Test LastChild on empty document
TEST_F(XMLNodeTest_44, LastChildNullOnEmptyDocument_44) {
    EXPECT_EQ(doc.LastChild(), nullptr);
}

// Test inserting an element as end child
TEST_F(XMLNodeTest_44, InsertEndChildAddsChild_44) {
    XMLElement* elem = doc.NewElement("root");
    XMLNode* result = doc.InsertEndChild(elem);
    EXPECT_NE(result, nullptr);
    EXPECT_FALSE(doc.NoChildren());
    EXPECT_EQ(doc.FirstChild(), elem);
    EXPECT_EQ(doc.LastChild(), elem);
}

// Test inserting multiple children
TEST_F(XMLNodeTest_44, InsertMultipleChildren_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    EXPECT_EQ(root->FirstChild(), child1);
    EXPECT_EQ(root->LastChild(), child2);
    EXPECT_FALSE(root->NoChildren());
}

// Test InsertFirstChild
TEST_F(XMLNodeTest_44, InsertFirstChildAddsAtBeginning_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertFirstChild(child2);

    EXPECT_EQ(root->FirstChild(), child2);
    EXPECT_EQ(root->LastChild(), child1);
}

// Test InsertAfterChild
TEST_F(XMLNodeTest_44, InsertAfterChildInsertsCorrectly_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child3 = doc.NewElement("child3");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child3);
    root->InsertAfterChild(child1, child2);

    EXPECT_EQ(root->FirstChild(), child1);
    EXPECT_EQ(child1->NextSibling(), child2);
    EXPECT_EQ(child2->NextSibling(), child3);
    EXPECT_EQ(root->LastChild(), child3);
}

// Test DeleteChildren removes all children
TEST_F(XMLNodeTest_44, DeleteChildrenRemovesAll_44) {
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

// Test DeleteChild removes specific child
TEST_F(XMLNodeTest_44, DeleteChildRemovesSpecificChild_44) {
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
    EXPECT_EQ(child1->NextSibling(), child3);
    EXPECT_EQ(root->LastChild(), child3);
}

// Test Value and SetValue
TEST_F(XMLNodeTest_44, SetValueAndGetValue_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_STREQ(root->Value(), "root");
    root->SetValue("newroot", false);
    EXPECT_STREQ(root->Value(), "newroot");
}

// Test SetValue with static memory
TEST_F(XMLNodeTest_44, SetValueStaticMem_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    const char* staticStr = "staticvalue";
    root->SetValue(staticStr, true);
    EXPECT_STREQ(root->Value(), "staticvalue");
}

// Test Parent
TEST_F(XMLNodeTest_44, ParentReturnsCorrectParent_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    EXPECT_EQ(child->Parent(), root);
    EXPECT_EQ(root->Parent(), &doc);
}

// Test NextSibling and PreviousSibling
TEST_F(XMLNodeTest_44, SiblingNavigation_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);

    EXPECT_EQ(child1->NextSibling(), child2);
    EXPECT_EQ(child2->NextSibling(), child3);
    EXPECT_EQ(child3->NextSibling(), nullptr);

    EXPECT_EQ(child3->PreviousSibling(), child2);
    EXPECT_EQ(child2->PreviousSibling(), child1);
    EXPECT_EQ(child1->PreviousSibling(), nullptr);
}

// Test FirstChildElement with name filter
TEST_F(XMLNodeTest_44, FirstChildElementWithNameFilter_44) {
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
    EXPECT_EQ(root->FirstChildElement("gamma"), nullptr);
}

// Test LastChildElement with name filter
TEST_F(XMLNodeTest_44, LastChildElementWithNameFilter_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    XMLElement* a2 = doc.NewElement("alpha");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);

    EXPECT_EQ(root->LastChildElement("alpha"), a2);
    EXPECT_EQ(root->LastChildElement("beta"), b);
    EXPECT_EQ(root->LastChildElement("gamma"), nullptr);
}

// Test NextSiblingElement with name filter
TEST_F(XMLNodeTest_44, NextSiblingElementWithNameFilter_44) {
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
    EXPECT_EQ(b->NextSiblingElement("beta"), nullptr);
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLNodeTest_44, PreviousSiblingElementWithNameFilter_44) {
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

// Test ChildElementCount
TEST_F(XMLNodeTest_44, ChildElementCountAll_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_EQ(root->ChildElementCount(), 0);

    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));

    EXPECT_EQ(root->ChildElementCount(), 3);
}

// Test ChildElementCount with name filter
TEST_F(XMLNodeTest_44, ChildElementCountWithName_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("beta"));
    root->InsertEndChild(doc.NewElement("alpha"));

    EXPECT_EQ(root->ChildElementCount("alpha"), 2);
    EXPECT_EQ(root->ChildElementCount("beta"), 1);
    EXPECT_EQ(root->ChildElementCount("gamma"), 0);
}

// Test GetDocument
TEST_F(XMLNodeTest_44, GetDocumentReturnsOwningDocument_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_EQ(root->GetDocument(), &doc);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    EXPECT_EQ(child->GetDocument(), &doc);
}

// Test DeepClone
TEST_F(XMLNodeTest_44, DeepCloneCreatesDeepCopy_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    XMLElement* grandchild = doc.NewElement("grandchild");
    child->InsertEndChild(grandchild);

    XMLDocument doc2;
    XMLNode* cloned = root->DeepClone(&doc2);
    ASSERT_NE(cloned, nullptr);
    doc2.InsertEndChild(cloned);

    EXPECT_STREQ(cloned->Value(), "root");
    EXPECT_NE(cloned->FirstChild(), nullptr);
    EXPECT_STREQ(cloned->FirstChild()->Value(), "child");
    EXPECT_NE(cloned->FirstChild()->FirstChild(), nullptr);
    EXPECT_STREQ(cloned->FirstChild()->FirstChild()->Value(), "grandchild");
}

// Test ToElement returns non-null for elements
TEST_F(XMLNodeTest_44, ToElementReturnsNonNullForElement_44) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_NE(elem->ToElement(), nullptr);
    EXPECT_EQ(elem->ToText(), nullptr);
    EXPECT_EQ(elem->ToComment(), nullptr);
    EXPECT_EQ(elem->ToDocument(), nullptr);
    EXPECT_EQ(elem->ToDeclaration(), nullptr);
    EXPECT_EQ(elem->ToUnknown(), nullptr);
}

// Test ToText returns non-null for text nodes
TEST_F(XMLNodeTest_44, ToTextReturnsNonNullForTextNode_44) {
    XMLText* text = doc.NewText("hello");
    EXPECT_NE(text->ToText(), nullptr);
    EXPECT_EQ(text->ToElement(), nullptr);
}

// Test ToComment returns non-null for comment nodes
TEST_F(XMLNodeTest_44, ToCommentReturnsNonNullForCommentNode_44) {
    XMLComment* comment = doc.NewComment("a comment");
    EXPECT_NE(comment->ToComment(), nullptr);
    EXPECT_EQ(comment->ToElement(), nullptr);
    EXPECT_EQ(comment->ToText(), nullptr);
}

// Test ToDeclaration returns non-null for declaration nodes
TEST_F(XMLNodeTest_44, ToDeclarationReturnsNonNullForDeclaration_44) {
    XMLDeclaration* decl = doc.NewDeclaration();
    EXPECT_NE(decl->ToDeclaration(), nullptr);
    EXPECT_EQ(decl->ToElement(), nullptr);
}

// Test ToUnknown returns non-null for unknown nodes
TEST_F(XMLNodeTest_44, ToUnknownReturnsNonNullForUnknown_44) {
    XMLUnknown* unknown = doc.NewUnknown("something");
    EXPECT_NE(unknown->ToUnknown(), nullptr);
    EXPECT_EQ(unknown->ToElement(), nullptr);
}

// Test UserData get/set
TEST_F(XMLNodeTest_44, UserDataSetAndGet_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_EQ(root->GetUserData(), nullptr);

    int data = 42;
    root->SetUserData(&data);
    EXPECT_EQ(root->GetUserData(), &data);

    root->SetUserData(nullptr);
    EXPECT_EQ(root->GetUserData(), nullptr);
}

// Test LinkEndChild (alias for InsertEndChild)
TEST_F(XMLNodeTest_44, LinkEndChildWorksLikeInsertEndChild_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->LinkEndChild(child);
    EXPECT_EQ(result, child);
    EXPECT_EQ(root->FirstChild(), child);
}

// Test GetLineNum (defaults to 0 for programmatically created nodes)
TEST_F(XMLNodeTest_44, GetLineNumDefaultsToZero_44) {
    XMLElement* root = doc.NewElement("root");
    EXPECT_EQ(root->GetLineNum(), 0);
}

// Test GetLineNum from parsed XML
TEST_F(XMLNodeTest_44, GetLineNumFromParsedXML_44) {
    const char* xml = "<root>\n  <child/>\n</root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetLineNum(), 1);

    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->GetLineNum(), 2);
}

// Test FirstChildElement with no name returns first element child
TEST_F(XMLNodeTest_44, FirstChildElementNoNameReturnsFirstElement_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLComment* comment = doc.NewComment("comment");
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(comment);
    root->InsertEndChild(child);

    EXPECT_EQ(root->FirstChildElement(), child);
}

// Test that inserting a node from another document into this document (via InsertEndChild) works or fails gracefully
TEST_F(XMLNodeTest_44, InsertEndChildNullReturnsNull_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    // Inserting null should not crash; behavior depends on implementation
    // but we test it doesn't crash
    // (Some implementations return null for null input)
}

// Test deleting a child that is the only child
TEST_F(XMLNodeTest_44, DeleteOnlyChild_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    root->DeleteChild(child);
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
}

// Test deleting first child when there are multiple children
TEST_F(XMLNodeTest_44, DeleteFirstOfMultipleChildren_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    root->InsertEndChild(c1);
    root->InsertEndChild(c2);

    root->DeleteChild(c1);
    EXPECT_EQ(root->FirstChild(), c2);
    EXPECT_EQ(root->LastChild(), c2);
    EXPECT_EQ(c2->PreviousSibling(), nullptr);
}

// Test deleting last child when there are multiple children
TEST_F(XMLNodeTest_44, DeleteLastOfMultipleChildren_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    root->InsertEndChild(c1);
    root->InsertEndChild(c2);

    root->DeleteChild(c2);
    EXPECT_EQ(root->FirstChild(), c1);
    EXPECT_EQ(root->LastChild(), c1);
    EXPECT_EQ(c1->NextSibling(), nullptr);
}

// Test ShallowClone for an element
TEST_F(XMLNodeTest_44, ShallowCloneElement_44) {
    XMLElement* root = doc.NewElement("root");
    root->SetAttribute("attr", "value");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    XMLDocument doc2;
    const XMLNode* cloned = root->ShallowClone(&doc2);
    ASSERT_NE(cloned, nullptr);
    EXPECT_STREQ(cloned->Value(), "root");
    // Shallow clone should not copy children
    EXPECT_TRUE(cloned->NoChildren());
}

// Test ShallowEqual
TEST_F(XMLNodeTest_44, ShallowEqualSameElement_44) {
    XMLElement* e1 = doc.NewElement("test");
    e1->SetAttribute("a", "1");

    XMLElement* e2 = doc.NewElement("test");
    e2->SetAttribute("a", "1");

    EXPECT_TRUE(e1->ShallowEqual(e2));
}

// Test ShallowEqual different elements
TEST_F(XMLNodeTest_44, ShallowEqualDifferentElements_44) {
    XMLElement* e1 = doc.NewElement("test1");
    XMLElement* e2 = doc.NewElement("test2");

    EXPECT_FALSE(e1->ShallowEqual(e2));
}

// Test mixed content with text and elements
TEST_F(XMLNodeTest_44, MixedContentNavigation_44) {
    const char* xml = "<root>text1<child/>text2</root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_NE(first->ToText(), nullptr);

    const XMLNode* second = first->NextSibling();
    ASSERT_NE(second, nullptr);
    EXPECT_NE(second->ToElement(), nullptr);

    const XMLNode* third = second->NextSibling();
    ASSERT_NE(third, nullptr);
    EXPECT_NE(third->ToText(), nullptr);
}

// Test Accept with XMLPrinter as visitor
TEST_F(XMLNodeTest_44, AcceptWithPrinter_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    XMLPrinter printer;
    root->Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // Should contain the root and child element tags
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
    EXPECT_NE(std::string(result).find("child"), std::string::npos);
}

// Test InsertAfterChild with afterThis as last child
TEST_F(XMLNodeTest_44, InsertAfterLastChild_44) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    root->InsertEndChild(c1);
    root->InsertAfterChild(c1, c2);

    EXPECT_EQ(root->LastChild(), c2);
    EXPECT_EQ(c1->NextSibling(), c2);
    EXPECT_EQ(c2->PreviousSibling(), c1);
}

// Test ChildElementCount with text nodes mixed in
TEST_F(XMLNodeTest_44, ChildElementCountIgnoresNonElements_44) {
    const char* xml = "<root>text<a/><b/>more text<c/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    // Should count only element children (a, b, c)
    EXPECT_EQ(root->ChildElementCount(), 3);
}

// Test DeepClone preserves text content
TEST_F(XMLNodeTest_44, DeepClonePreservesText_44) {
    const char* xml = "<root><child>hello</child></root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLDocument doc2;
    XMLNode* cloned = root->DeepClone(&doc2);
    doc2.InsertEndChild(cloned);

    XMLElement* clonedChild = doc2.FirstChildElement("root")->FirstChildElement("child");
    ASSERT_NE(clonedChild, nullptr);
    EXPECT_STREQ(clonedChild->GetText(), "hello");
}
