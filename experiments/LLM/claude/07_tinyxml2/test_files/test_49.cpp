#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_49 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// --- GetLineNum Tests ---

TEST_F(XMLNodeTest_49, GetLineNum_DefaultIsZero_49) {
    // A freshly created document node should have line number 0
    EXPECT_EQ(doc.GetLineNum(), 0);
}

TEST_F(XMLNodeTest_49, GetLineNum_AfterParsing_49) {
    const char* xml = "<root>\n<child/>\n</root>";
    doc.Parse(xml);
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetLineNum(), 1);
    
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->GetLineNum(), 2);
}

// --- Value / SetValue Tests ---

TEST_F(XMLNodeTest_49, Value_DocumentNode_49) {
    // XMLDocument value is typically empty or set by parsing
    const char* val = doc.Value();
    // Just ensure it doesn't crash and returns something
    ASSERT_NE(val, nullptr);
}

TEST_F(XMLNodeTest_49, SetValue_ElementNode_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Value(), "root");
    
    root->SetValue("newname", false);
    EXPECT_STREQ(root->Value(), "newname");
}

TEST_F(XMLNodeTest_49, SetValue_StaticMem_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    static const char* staticName = "staticname";
    root->SetValue(staticName, true);
    EXPECT_STREQ(root->Value(), "staticname");
}

// --- NoChildren / FirstChild / LastChild Tests ---

TEST_F(XMLNodeTest_49, NoChildren_EmptyElement_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(root->NoChildren());
}

TEST_F(XMLNodeTest_49, NoChildren_WithChildren_49) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_FALSE(root->NoChildren());
}

TEST_F(XMLNodeTest_49, FirstChild_ReturnsFirstChild_49) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");
}

TEST_F(XMLNodeTest_49, LastChild_ReturnsLastChild_49) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLNode* last = root->LastChild();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "b");
}

TEST_F(XMLNodeTest_49, FirstChild_NoChildren_ReturnsNull_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->FirstChild(), nullptr);
}

TEST_F(XMLNodeTest_49, LastChild_NoChildren_ReturnsNull_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
}

// --- FirstChildElement / LastChildElement Tests ---

TEST_F(XMLNodeTest_49, FirstChildElement_ByName_49) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Value(), "b");
}

TEST_F(XMLNodeTest_49, FirstChildElement_NullName_ReturnsFirst_49) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");
}

TEST_F(XMLNodeTest_49, FirstChildElement_NonExistent_ReturnsNull_49) {
    doc.Parse("<root><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* notfound = root->FirstChildElement("zzz");
    EXPECT_EQ(notfound, nullptr);
}

TEST_F(XMLNodeTest_49, LastChildElement_ByName_49) {
    doc.Parse("<root><a/><b/><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLElement* lastA = root->LastChildElement("a");
    ASSERT_NE(lastA, nullptr);
    EXPECT_STREQ(lastA->Value(), "a");
    
    // The last "a" should be different from the first "a"
    const XMLElement* firstA = root->FirstChildElement("a");
    ASSERT_NE(firstA, nullptr);
    EXPECT_NE(firstA, lastA);
}

TEST_F(XMLNodeTest_49, LastChildElement_NullName_49) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "b");
}

// --- Sibling Tests ---

TEST_F(XMLNodeTest_49, NextSibling_49) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLNode* a = root->FirstChild();
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Value(), "a");
    
    const XMLNode* b = a->NextSibling();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Value(), "b");
    
    const XMLNode* c = b->NextSibling();
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->Value(), "c");
    
    const XMLNode* end = c->NextSibling();
    EXPECT_EQ(end, nullptr);
}

TEST_F(XMLNodeTest_49, PreviousSibling_49) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLNode* c = root->LastChild();
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->Value(), "c");
    
    const XMLNode* b = c->PreviousSibling();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Value(), "b");
    
    const XMLNode* a = b->PreviousSibling();
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Value(), "a");
    
    EXPECT_EQ(a->PreviousSibling(), nullptr);
}

TEST_F(XMLNodeTest_49, NextSiblingElement_ByName_49) {
    doc.Parse("<root><a/><b/><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* firstA = root->FirstChildElement("a");
    ASSERT_NE(firstA, nullptr);
    
    XMLElement* secondA = firstA->NextSiblingElement("a");
    ASSERT_NE(secondA, nullptr);
    EXPECT_STREQ(secondA->Value(), "a");
    EXPECT_NE(firstA, secondA);
}

TEST_F(XMLNodeTest_49, PreviousSiblingElement_ByName_49) {
    doc.Parse("<root><a/><b/><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* lastA = root->LastChildElement("a");
    ASSERT_NE(lastA, nullptr);
    
    XMLElement* prevA = lastA->PreviousSiblingElement("a");
    ASSERT_NE(prevA, nullptr);
    EXPECT_STREQ(prevA->Value(), "a");
    EXPECT_NE(lastA, prevA);
}

// --- Parent Tests ---

TEST_F(XMLNodeTest_49, Parent_ReturnsParentNode_49) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    
    const XMLNode* parent = child->Parent();
    EXPECT_EQ(parent, root);
}

TEST_F(XMLNodeTest_49, Parent_RootParentIsDocument_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLNode* parent = root->Parent();
    EXPECT_EQ(parent, &doc);
}

// --- InsertEndChild Tests ---

TEST_F(XMLNodeTest_49, InsertEndChild_AddsToEnd_49) {
    doc.Parse("<root><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* newElem = doc.NewElement("b");
    XMLNode* result = root->InsertEndChild(newElem);
    ASSERT_NE(result, nullptr);
    
    const XMLNode* last = root->LastChild();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "b");
}

TEST_F(XMLNodeTest_49, InsertEndChild_ToEmptyNode_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(root->NoChildren());
    
    XMLElement* newElem = doc.NewElement("child");
    root->InsertEndChild(newElem);
    
    EXPECT_FALSE(root->NoChildren());
    EXPECT_STREQ(root->FirstChild()->Value(), "child");
}

// --- InsertFirstChild Tests ---

TEST_F(XMLNodeTest_49, InsertFirstChild_AddsToBeginning_49) {
    doc.Parse("<root><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* newElem = doc.NewElement("a");
    XMLNode* result = root->InsertFirstChild(newElem);
    ASSERT_NE(result, nullptr);
    
    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");
}

// --- InsertAfterChild Tests ---

TEST_F(XMLNodeTest_49, InsertAfterChild_InsertsCorrectly_49) {
    doc.Parse("<root><a/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    
    XMLElement* b = doc.NewElement("b");
    XMLNode* result = root->InsertAfterChild(a, b);
    ASSERT_NE(result, nullptr);
    
    // Verify order: a, b, c
    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");
    
    const XMLNode* second = first->NextSibling();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Value(), "b");
    
    const XMLNode* third = second->NextSibling();
    ASSERT_NE(third, nullptr);
    EXPECT_STREQ(third->Value(), "c");
}

// --- DeleteChildren Tests ---

TEST_F(XMLNodeTest_49, DeleteChildren_RemovesAllChildren_49) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_FALSE(root->NoChildren());
    
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
}

TEST_F(XMLNodeTest_49, DeleteChildren_OnEmptyNode_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(root->NoChildren());
    
    // Should not crash
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

// --- DeleteChild Tests ---

TEST_F(XMLNodeTest_49, DeleteChild_RemovesSpecificChild_49) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    
    root->DeleteChild(b);
    
    // b should be gone; a and c remain
    XMLElement* bAfter = root->FirstChildElement("b");
    EXPECT_EQ(bAfter, nullptr);
    
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* c = a->NextSiblingElement();
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->Value(), "c");
}

// --- ChildElementCount Tests ---

TEST_F(XMLNodeTest_49, ChildElementCount_AllChildren_49) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    EXPECT_EQ(root->ChildElementCount(), 3);
}

TEST_F(XMLNodeTest_49, ChildElementCount_Empty_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    EXPECT_EQ(root->ChildElementCount(), 0);
}

TEST_F(XMLNodeTest_49, ChildElementCount_ByName_49) {
    doc.Parse("<root><a/><b/><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    EXPECT_EQ(root->ChildElementCount("a"), 2);
    EXPECT_EQ(root->ChildElementCount("b"), 1);
    EXPECT_EQ(root->ChildElementCount("z"), 0);
}

// --- DeepClone Tests ---

TEST_F(XMLNodeTest_49, DeepClone_ClonesTree_49) {
    doc.Parse("<root><child attr=\"val\"><subchild/></child></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLDocument targetDoc;
    XMLNode* cloned = root->DeepClone(&targetDoc);
    ASSERT_NE(cloned, nullptr);
    targetDoc.InsertEndChild(cloned);
    
    XMLElement* clonedRoot = targetDoc.FirstChildElement("root");
    ASSERT_NE(clonedRoot, nullptr);
    
    XMLElement* clonedChild = clonedRoot->FirstChildElement("child");
    ASSERT_NE(clonedChild, nullptr);
    EXPECT_STREQ(clonedChild->Attribute("attr"), "val");
    
    XMLElement* clonedSubchild = clonedChild->FirstChildElement("subchild");
    ASSERT_NE(clonedSubchild, nullptr);
}

// --- GetDocument Tests ---

TEST_F(XMLNodeTest_49, GetDocument_ReturnsOwningDocument_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    EXPECT_EQ(root->GetDocument(), &doc);
}

// --- ToElement Tests ---

TEST_F(XMLNodeTest_49, ToElement_OnElement_ReturnsSelf_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    EXPECT_NE(root->ToElement(), nullptr);
    EXPECT_EQ(root->ToElement(), root);
}

TEST_F(XMLNodeTest_49, ToDocument_OnDocument_ReturnsSelf_49) {
    EXPECT_NE(doc.ToDocument(), nullptr);
}

TEST_F(XMLNodeTest_49, ToComment_OnElement_ReturnsNull_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    EXPECT_EQ(root->ToComment(), nullptr);
}

TEST_F(XMLNodeTest_49, ToText_OnElement_ReturnsNull_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    EXPECT_EQ(root->ToText(), nullptr);
}

// --- UserData Tests ---

TEST_F(XMLNodeTest_49, UserData_SetAndGet_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    int data = 42;
    root->SetUserData(&data);
    
    void* retrieved = root->GetUserData();
    EXPECT_EQ(retrieved, &data);
    EXPECT_EQ(*static_cast<int*>(retrieved), 42);
}

TEST_F(XMLNodeTest_49, UserData_DefaultIsNull_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    EXPECT_EQ(root->GetUserData(), nullptr);
}

TEST_F(XMLNodeTest_49, UserData_SetNull_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    int data = 10;
    root->SetUserData(&data);
    EXPECT_EQ(root->GetUserData(), &data);
    
    root->SetUserData(nullptr);
    EXPECT_EQ(root->GetUserData(), nullptr);
}

// --- LinkEndChild Tests (deprecated alias for InsertEndChild) ---

TEST_F(XMLNodeTest_49, LinkEndChild_Works_49) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->LinkEndChild(child);
    EXPECT_NE(result, nullptr);
    
    EXPECT_FALSE(root->NoChildren());
    EXPECT_STREQ(root->FirstChild()->Value(), "child");
}

// --- Parsing with comments and text ---

TEST_F(XMLNodeTest_49, Comment_ToComment_49) {
    doc.Parse("<root><!-- a comment --></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_NE(firstChild->ToComment(), nullptr);
}

TEST_F(XMLNodeTest_49, TextNode_ToText_49) {
    doc.Parse("<root>hello</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_NE(firstChild->ToText(), nullptr);
}

// --- ShallowClone / ShallowEqual Tests ---

TEST_F(XMLNodeTest_49, ShallowClone_Element_49) {
    doc.Parse("<root attr=\"val\"><child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLDocument cloneDoc;
    const XMLNode* cloned = root->ShallowClone(&cloneDoc);
    ASSERT_NE(cloned, nullptr);
    
    // ShallowClone should not clone children
    EXPECT_TRUE(cloned->NoChildren());
    EXPECT_STREQ(cloned->Value(), "root");
}

TEST_F(XMLNodeTest_49, ShallowEqual_SameElement_49) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* root2 = doc2.FirstChildElement("root");
    ASSERT_NE(root2, nullptr);
    
    EXPECT_TRUE(root->ShallowEqual(root2));
}

TEST_F(XMLNodeTest_49, ShallowEqual_DifferentElement_49) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* other = doc2.FirstChildElement("other");
    ASSERT_NE(other, nullptr);
    
    EXPECT_FALSE(root->ShallowEqual(other));
}

// --- Multiple InsertEndChild calls ---

TEST_F(XMLNodeTest_49, InsertEndChild_MultipleChildren_Order_49) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));
    
    EXPECT_EQ(root->ChildElementCount(), 3);
    
    XMLElement* e = root->FirstChildElement();
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->Value(), "a");
    
    e = e->NextSiblingElement();
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->Value(), "b");
    
    e = e->NextSiblingElement();
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->Value(), "c");
    
    e = e->NextSiblingElement();
    EXPECT_EQ(e, nullptr);
}

// --- InsertAfterChild at end ---

TEST_F(XMLNodeTest_49, InsertAfterChild_AtEnd_49) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* b = root->LastChildElement("b");
    ASSERT_NE(b, nullptr);
    
    XMLElement* c = doc.NewElement("c");
    root->InsertAfterChild(b, c);
    
    const XMLNode* last = root->LastChild();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "c");
}

// --- Declaration node ---

TEST_F(XMLNodeTest_49, Declaration_ToDeclaration_49) {
    doc.Parse("<?xml version=\"1.0\"?><root/>");
    const XMLNode* firstChild = doc.FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_NE(firstChild->ToDeclaration(), nullptr);
}

// --- Unknown node ---

TEST_F(XMLNodeTest_49, Unknown_ToUnknown_49) {
    doc.Parse("<root><!SOMETHING unknown></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLNode* child = root->FirstChild();
    // Depending on parse behavior, unknown nodes might appear
    if (child != nullptr) {
        // If parsed as unknown, ToUnknown should not be null
        // Otherwise, just ensure no crash
        (void)child->ToUnknown();
    }
}

// --- DeleteChild first and last ---

TEST_F(XMLNodeTest_49, DeleteChild_FirstChild_49) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* a = root->FirstChildElement("a");
    root->DeleteChild(a);
    
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "b");
    EXPECT_EQ(root->ChildElementCount(), 2);
}

TEST_F(XMLNodeTest_49, DeleteChild_LastChild_49) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* c = root->LastChildElement("c");
    root->DeleteChild(c);
    
    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "b");
    EXPECT_EQ(root->ChildElementCount(), 2);
}

// --- Single child operations ---

TEST_F(XMLNodeTest_49, SingleChild_FirstAndLastAreSame_49) {
    doc.Parse("<root><only/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    EXPECT_EQ(root->FirstChild(), root->LastChild());
    EXPECT_EQ(root->FirstChildElement(), root->LastChildElement());
}

TEST_F(XMLNodeTest_49, DeleteChild_OnlyChild_49) {
    doc.Parse("<root><only/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* only = root->FirstChildElement("only");
    root->DeleteChild(only);
    
    EXPECT_TRUE(root->NoChildren());
}

// --- InsertFirstChild with existing children ---

TEST_F(XMLNodeTest_49, InsertFirstChild_ExistingChildren_49) {
    doc.Parse("<root><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* a = doc.NewElement("a");
    root->InsertFirstChild(a);
    
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");
    EXPECT_EQ(root->ChildElementCount(), 3);
}

// --- Const correctness: calling const versions ---

TEST_F(XMLNodeTest_49, ConstAccess_49) {
    doc.Parse("<root><child/></root>");
    const XMLDocument& constDoc = doc;
    
    const XMLElement* root = constDoc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_STREQ(firstChild->Value(), "child");
    
    const XMLNode* parent = firstChild->Parent();
    EXPECT_EQ(parent, root);
    
    EXPECT_FALSE(root->NoChildren());
    EXPECT_EQ(root->GetDocument(), &doc);
}

// --- ChildElementCount with mixed node types ---

TEST_F(XMLNodeTest_49, ChildElementCount_MixedNodes_49) {
    doc.Parse("<root>text<child/><!-- comment --><child2/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    // ChildElementCount should count only element children
    EXPECT_EQ(root->ChildElementCount(), 2);
}

// --- GetLineNum multiline ---

TEST_F(XMLNodeTest_49, GetLineNum_MultipleLevels_49) {
    const char* xml = 
        "<root>\n"
        "  <a>\n"
        "    <b/>\n"
        "  </a>\n"
        "</root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetLineNum(), 1);
    
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    EXPECT_EQ(a->GetLineNum(), 2);
    
    XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    EXPECT_EQ(b->GetLineNum(), 3);
}
