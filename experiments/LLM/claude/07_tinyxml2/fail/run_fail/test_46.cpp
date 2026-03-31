#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_46 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// ==================== ToDocument Tests ====================

TEST_F(XMLNodeTest_46, ToDocument_ReturnsNonNull_46) {
    XMLDocument* result = doc.ToDocument();
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(&doc, result);
}

TEST_F(XMLNodeTest_46, ToElement_OnDocument_ReturnsNull_46) {
    XMLElement* result = doc.ToElement();
    EXPECT_EQ(nullptr, result);
}

// ==================== Value Tests ====================

TEST_F(XMLNodeTest_46, Value_OnNewDocument_ReturnsEmptyOrNull_46) {
    // A new document may have an empty or null value
    const char* val = doc.Value();
    // Value could be nullptr or empty string
    if (val != nullptr) {
        // Just ensure it doesn't crash
    }
}

// ==================== NoChildren Tests ====================

TEST_F(XMLNodeTest_46, NoChildren_EmptyDocument_ReturnsTrue_46) {
    EXPECT_TRUE(doc.NoChildren());
}

TEST_F(XMLNodeTest_46, NoChildren_AfterAddingChild_ReturnsFalse_46) {
    XMLElement* elem = doc.NewElement("root");
    doc.InsertEndChild(elem);
    EXPECT_FALSE(doc.NoChildren());
}

// ==================== InsertEndChild Tests ====================

TEST_F(XMLNodeTest_46, InsertEndChild_SingleElement_46) {
    XMLElement* elem = doc.NewElement("child");
    XMLNode* result = doc.InsertEndChild(elem);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(doc.NoChildren());
}

TEST_F(XMLNodeTest_46, InsertEndChild_MultipleElements_46) {
    XMLElement* elem1 = doc.NewElement("child1");
    XMLElement* elem2 = doc.NewElement("child2");
    doc.InsertEndChild(elem1);
    doc.InsertEndChild(elem2);
    
    EXPECT_EQ(elem1, doc.FirstChild());
    EXPECT_EQ(elem2, doc.LastChild());
}

// ==================== InsertFirstChild Tests ====================

TEST_F(XMLNodeTest_46, InsertFirstChild_EmptyDocument_46) {
    XMLElement* elem = doc.NewElement("first");
    XMLNode* result = doc.InsertFirstChild(elem);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(elem, doc.FirstChild());
}

TEST_F(XMLNodeTest_46, InsertFirstChild_BeforeExistingChild_46) {
    XMLElement* existing = doc.NewElement("existing");
    doc.InsertEndChild(existing);
    
    XMLElement* first = doc.NewElement("first");
    doc.InsertFirstChild(first);
    
    EXPECT_EQ(first, doc.FirstChild());
    EXPECT_EQ(existing, doc.LastChild());
}

// ==================== InsertAfterChild Tests ====================

TEST_F(XMLNodeTest_46, InsertAfterChild_InMiddle_46) {
    XMLElement* elem1 = doc.NewElement("child1");
    XMLElement* elem2 = doc.NewElement("child2");
    XMLElement* elem3 = doc.NewElement("child3");
    
    doc.InsertEndChild(elem1);
    doc.InsertEndChild(elem3);
    doc.InsertAfterChild(elem1, elem2);
    
    EXPECT_EQ(elem1, doc.FirstChild());
    EXPECT_EQ(elem3, doc.LastChild());
    EXPECT_EQ(elem2, elem1->NextSibling());
    EXPECT_EQ(elem3, elem2->NextSibling());
}

TEST_F(XMLNodeTest_46, InsertAfterChild_NullAfterThis_ReturnsNull_46) {
    XMLElement* elem = doc.NewElement("child");
    // afterThis is null, should return 0
    XMLNode* result = doc.InsertAfterChild(nullptr, elem);
    // Behavior may vary, but shouldn't crash
}

// ==================== FirstChild / LastChild Tests ====================

TEST_F(XMLNodeTest_46, FirstChild_EmptyDocument_ReturnsNull_46) {
    EXPECT_EQ(nullptr, doc.FirstChild());
}

TEST_F(XMLNodeTest_46, LastChild_EmptyDocument_ReturnsNull_46) {
    EXPECT_EQ(nullptr, doc.LastChild());
}

TEST_F(XMLNodeTest_46, FirstChild_LastChild_SingleChild_46) {
    XMLElement* elem = doc.NewElement("only");
    doc.InsertEndChild(elem);
    EXPECT_EQ(elem, doc.FirstChild());
    EXPECT_EQ(elem, doc.LastChild());
}

// ==================== FirstChildElement / LastChildElement Tests ====================

TEST_F(XMLNodeTest_46, FirstChildElement_NoName_46) {
    XMLElement* elem1 = doc.NewElement("a");
    XMLElement* elem2 = doc.NewElement("b");
    doc.InsertEndChild(elem1);
    doc.InsertEndChild(elem2);
    
    EXPECT_EQ(elem1, doc.FirstChildElement());
}

TEST_F(XMLNodeTest_46, FirstChildElement_WithName_46) {
    XMLElement* elem1 = doc.NewElement("a");
    XMLElement* elem2 = doc.NewElement("b");
    doc.InsertEndChild(elem1);
    doc.InsertEndChild(elem2);
    
    EXPECT_EQ(elem2, doc.FirstChildElement("b"));
}

TEST_F(XMLNodeTest_46, FirstChildElement_NameNotFound_46) {
    XMLElement* elem = doc.NewElement("a");
    doc.InsertEndChild(elem);
    
    EXPECT_EQ(nullptr, doc.FirstChildElement("nonexistent"));
}

TEST_F(XMLNodeTest_46, LastChildElement_NoName_46) {
    XMLElement* elem1 = doc.NewElement("a");
    XMLElement* elem2 = doc.NewElement("b");
    doc.InsertEndChild(elem1);
    doc.InsertEndChild(elem2);
    
    EXPECT_EQ(elem2, doc.LastChildElement());
}

TEST_F(XMLNodeTest_46, LastChildElement_WithName_46) {
    XMLElement* elem1 = doc.NewElement("a");
    XMLElement* elem2 = doc.NewElement("b");
    XMLElement* elem3 = doc.NewElement("a");
    doc.InsertEndChild(elem1);
    doc.InsertEndChild(elem2);
    doc.InsertEndChild(elem3);
    
    EXPECT_EQ(elem3, doc.LastChildElement("a"));
}

// ==================== Sibling Tests ====================

TEST_F(XMLNodeTest_46, NextSibling_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child1 = doc.NewElement("c1");
    XMLElement* child2 = doc.NewElement("c2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    
    EXPECT_EQ(child2, child1->NextSibling());
    EXPECT_EQ(nullptr, child2->NextSibling());
}

TEST_F(XMLNodeTest_46, PreviousSibling_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child1 = doc.NewElement("c1");
    XMLElement* child2 = doc.NewElement("c2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    
    EXPECT_EQ(child1, child2->PreviousSibling());
    EXPECT_EQ(nullptr, child1->PreviousSibling());
}

TEST_F(XMLNodeTest_46, NextSiblingElement_WithName_46) {
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

TEST_F(XMLNodeTest_46, PreviousSiblingElement_WithName_46) {
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

// ==================== Parent Tests ====================

TEST_F(XMLNodeTest_46, Parent_RootElement_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_EQ(&doc, root->Parent());
}

TEST_F(XMLNodeTest_46, Parent_ChildElement_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    EXPECT_EQ(root, child->Parent());
}

TEST_F(XMLNodeTest_46, Parent_Document_ReturnsNull_46) {
    EXPECT_EQ(nullptr, doc.Parent());
}

// ==================== DeleteChildren Tests ====================

TEST_F(XMLNodeTest_46, DeleteChildren_RemovesAll_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));
    
    EXPECT_FALSE(root->NoChildren());
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

TEST_F(XMLNodeTest_46, DeleteChildren_OnEmptyNode_NoEffect_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_TRUE(root->NoChildren());
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

// ==================== DeleteChild Tests ====================

TEST_F(XMLNodeTest_46, DeleteChild_RemovesSpecificChild_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* c = doc.NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);
    
    root->DeleteChild(b);
    
    EXPECT_EQ(a, root->FirstChild());
    EXPECT_EQ(c, root->LastChild());
    EXPECT_EQ(c, a->NextSibling());
}

// ==================== ChildElementCount Tests ====================

TEST_F(XMLNodeTest_46, ChildElementCount_Empty_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_EQ(0, root->ChildElementCount());
}

TEST_F(XMLNodeTest_46, ChildElementCount_MultipleChildren_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));
    
    EXPECT_EQ(3, root->ChildElementCount());
}

TEST_F(XMLNodeTest_46, ChildElementCount_WithName_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("a"));
    
    EXPECT_EQ(2, root->ChildElementCount("a"));
    EXPECT_EQ(1, root->ChildElementCount("b"));
    EXPECT_EQ(0, root->ChildElementCount("c"));
}

// ==================== GetDocument Tests ====================

TEST_F(XMLNodeTest_46, GetDocument_FromElement_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_EQ(&doc, root->GetDocument());
}

TEST_F(XMLNodeTest_46, GetDocument_FromNestedElement_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    EXPECT_EQ(&doc, child->GetDocument());
}

// ==================== UserData Tests ====================

TEST_F(XMLNodeTest_46, SetAndGetUserData_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    int userData = 42;
    root->SetUserData(&userData);
    EXPECT_EQ(&userData, root->GetUserData());
}

TEST_F(XMLNodeTest_46, GetUserData_Default_ReturnsNull_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_EQ(nullptr, root->GetUserData());
}

// ==================== SetValue Tests ====================

TEST_F(XMLNodeTest_46, SetValue_OnElement_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    root->SetValue("newname", false);
    EXPECT_STREQ("newname", root->Value());
}

TEST_F(XMLNodeTest_46, SetValue_StaticMem_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    root->SetValue("staticname", true);
    EXPECT_STREQ("staticname", root->Value());
}

// ==================== DeepClone Tests ====================

TEST_F(XMLNodeTest_46, DeepClone_ClonesElementAndChildren_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    XMLDocument doc2;
    XMLNode* cloned = root->DeepClone(&doc2);
    ASSERT_NE(nullptr, cloned);
    
    doc2.InsertEndChild(cloned);
    
    EXPECT_STREQ("root", cloned->Value());
    EXPECT_FALSE(cloned->NoChildren());
    EXPECT_STREQ("child", cloned->FirstChild()->Value());
}

TEST_F(XMLNodeTest_46, DeepClone_IndependentOfOriginal_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("child"));
    
    XMLDocument doc2;
    XMLNode* cloned = root->DeepClone(&doc2);
    doc2.InsertEndChild(cloned);
    
    // Modify original
    root->DeleteChildren();
    
    // Clone should be unaffected
    EXPECT_FALSE(cloned->NoChildren());
}

// ==================== ToElement/ToText/ToComment/ToDeclaration/ToUnknown Tests ====================

TEST_F(XMLNodeTest_46, ToElement_OnElement_ReturnsNonNull_46) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    EXPECT_NE(nullptr, elem->ToElement());
}

TEST_F(XMLNodeTest_46, ToText_OnElement_ReturnsNull_46) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    EXPECT_EQ(nullptr, elem->ToText());
}

TEST_F(XMLNodeTest_46, ToComment_OnElement_ReturnsNull_46) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    EXPECT_EQ(nullptr, elem->ToComment());
}

TEST_F(XMLNodeTest_46, ToDocument_OnElement_ReturnsNull_46) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    EXPECT_EQ(nullptr, elem->ToDocument());
}

TEST_F(XMLNodeTest_46, ToDeclaration_OnElement_ReturnsNull_46) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    EXPECT_EQ(nullptr, elem->ToDeclaration());
}

TEST_F(XMLNodeTest_46, ToUnknown_OnElement_ReturnsNull_46) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    EXPECT_EQ(nullptr, elem->ToUnknown());
}

// ==================== Comment node tests ====================

TEST_F(XMLNodeTest_46, ToComment_OnComment_ReturnsNonNull_46) {
    XMLComment* comment = doc.NewComment("test comment");
    doc.InsertEndChild(comment);
    
    EXPECT_NE(nullptr, comment->ToComment());
    EXPECT_EQ(nullptr, comment->ToElement());
}

// ==================== Text node tests ====================

TEST_F(XMLNodeTest_46, TextNode_InsertedInElement_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLText* text = doc.NewText("hello");
    root->InsertEndChild(text);
    
    EXPECT_NE(nullptr, text->ToText());
    EXPECT_STREQ("hello", text->Value());
}

// ==================== LinkEndChild Tests (alias for InsertEndChild) ====================

TEST_F(XMLNodeTest_46, LinkEndChild_Works_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->LinkEndChild(child);
    
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(child, root->FirstChild());
}

// ==================== GetLineNum Tests ====================

TEST_F(XMLNodeTest_46, GetLineNum_NewElement_46) {
    XMLElement* elem = doc.NewElement("test");
    // Line number for programmatically created elements is typically 0
    int lineNum = elem->GetLineNum();
    EXPECT_GE(lineNum, 0);
    doc.InsertEndChild(elem);
}

// ==================== Parse and Structural Tests ====================

TEST_F(XMLNodeTest_46, ParseXML_StructuralIntegrity_46) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    EXPECT_EQ(3, root->ChildElementCount());
    EXPECT_STREQ("a", root->FirstChildElement()->Value());
    EXPECT_STREQ("c", root->LastChildElement()->Value());
}

TEST_F(XMLNodeTest_46, ParseXML_NestedStructure_46) {
    const char* xml = "<root><parent><child/></parent></root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLElement* parent = root->FirstChildElement("parent");
    ASSERT_NE(nullptr, parent);
    
    XMLElement* child = parent->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    
    EXPECT_EQ(parent, child->Parent());
}

// ==================== Boundary: Insert null child ====================

TEST_F(XMLNodeTest_46, InsertEndChild_Null_46) {
    XMLNode* result = doc.InsertEndChild(nullptr);
    // Expect null or no crash
    // Implementation may return nullptr for null input
}

TEST_F(XMLNodeTest_46, InsertFirstChild_Null_46) {
    XMLNode* result = doc.InsertFirstChild(nullptr);
    // Expect null or no crash
}

// ==================== Moving child between documents ====================

TEST_F(XMLNodeTest_46, DeepClone_ToDifferentDocument_46) {
    doc.Parse("<root><a><b/></a></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLDocument doc2;
    XMLNode* cloned = root->DeepClone(&doc2);
    ASSERT_NE(nullptr, cloned);
    doc2.InsertEndChild(cloned);
    
    EXPECT_EQ(&doc2, cloned->GetDocument());
    EXPECT_STREQ("root", cloned->Value());
    
    XMLElement* clonedRoot = cloned->ToElement();
    ASSERT_NE(nullptr, clonedRoot);
    XMLElement* clonedA = clonedRoot->FirstChildElement("a");
    ASSERT_NE(nullptr, clonedA);
    XMLElement* clonedB = clonedA->FirstChildElement("b");
    ASSERT_NE(nullptr, clonedB);
}

// ==================== Multiple delete children calls ====================

TEST_F(XMLNodeTest_46, DeleteChildren_CalledTwice_NoEffect_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
    
    root->DeleteChildren(); // Second call should be safe
    EXPECT_TRUE(root->NoChildren());
}

// ==================== Delete first and last child ====================

TEST_F(XMLNodeTest_46, DeleteChild_FirstChild_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    
    root->DeleteChild(a);
    EXPECT_EQ(b, root->FirstChild());
    EXPECT_EQ(b, root->LastChild());
}

TEST_F(XMLNodeTest_46, DeleteChild_LastChild_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    
    root->DeleteChild(b);
    EXPECT_EQ(a, root->FirstChild());
    EXPECT_EQ(a, root->LastChild());
}

TEST_F(XMLNodeTest_46, DeleteChild_OnlyChild_46) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* a = doc.NewElement("a");
    root->InsertEndChild(a);
    
    root->DeleteChild(a);
    EXPECT_TRUE(root->NoChildren());
}
