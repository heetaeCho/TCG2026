#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_42 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// ============================================================
// GetDocument Tests
// ============================================================

TEST_F(XMLNodeTest_42, GetDocument_ReturnsNonNull_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    const XMLDocument* d = root->GetDocument();
    ASSERT_NE(d, nullptr);
    EXPECT_EQ(d, &doc);
}

TEST_F(XMLNodeTest_42, GetDocument_OnDocumentItself_42) {
    const XMLDocument* d = doc.GetDocument();
    ASSERT_NE(d, nullptr);
    EXPECT_EQ(d, &doc);
}

TEST_F(XMLNodeTest_42, GetDocument_ChildReturnsParentDocument_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    EXPECT_EQ(child->GetDocument(), &doc);
}

// ============================================================
// Value / SetValue Tests
// ============================================================

TEST_F(XMLNodeTest_42, Value_ElementName_42) {
    XMLElement* root = doc.NewElement("testElement");
    doc.InsertEndChild(root);
    EXPECT_STREQ(root->Value(), "testElement");
}

TEST_F(XMLNodeTest_42, SetValue_ChangesValue_42) {
    XMLElement* root = doc.NewElement("original");
    doc.InsertEndChild(root);
    root->SetValue("modified", false);
    EXPECT_STREQ(root->Value(), "modified");
}

TEST_F(XMLNodeTest_42, SetValue_StaticMem_42) {
    XMLElement* root = doc.NewElement("original");
    doc.InsertEndChild(root);
    root->SetValue("static_value", true);
    EXPECT_STREQ(root->Value(), "static_value");
}

// ============================================================
// NoChildren Tests
// ============================================================

TEST_F(XMLNodeTest_42, NoChildren_EmptyElement_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_TRUE(root->NoChildren());
}

TEST_F(XMLNodeTest_42, NoChildren_WithChild_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    EXPECT_FALSE(root->NoChildren());
}

// ============================================================
// InsertEndChild Tests
// ============================================================

TEST_F(XMLNodeTest_42, InsertEndChild_SingleChild_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->InsertEndChild(child);
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(root->NoChildren());
    EXPECT_STREQ(root->FirstChild()->Value(), "child");
    EXPECT_STREQ(root->LastChild()->Value(), "child");
}

TEST_F(XMLNodeTest_42, InsertEndChild_MultipleChildren_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    EXPECT_STREQ(root->FirstChild()->Value(), "child1");
    EXPECT_STREQ(root->LastChild()->Value(), "child2");
}

// ============================================================
// InsertFirstChild Tests
// ============================================================

TEST_F(XMLNodeTest_42, InsertFirstChild_BeforeExisting_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertFirstChild(child2);
    EXPECT_STREQ(root->FirstChild()->Value(), "child2");
    EXPECT_STREQ(root->LastChild()->Value(), "child1");
}

TEST_F(XMLNodeTest_42, InsertFirstChild_EmptyParent_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->InsertFirstChild(child);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(root->FirstChild()->Value(), "child");
}

// ============================================================
// InsertAfterChild Tests
// ============================================================

TEST_F(XMLNodeTest_42, InsertAfterChild_InMiddle_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");
    root->InsertEndChild(child1);
    root->InsertEndChild(child3);
    root->InsertAfterChild(child1, child2);
    
    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "child1");
    const XMLNode* second = first->NextSibling();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Value(), "child2");
    const XMLNode* third = second->NextSibling();
    ASSERT_NE(third, nullptr);
    EXPECT_STREQ(third->Value(), "child3");
}

TEST_F(XMLNodeTest_42, InsertAfterChild_AtEnd_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertAfterChild(child1, child2);
    EXPECT_STREQ(root->LastChild()->Value(), "child2");
}

// ============================================================
// DeleteChildren Tests
// ============================================================

TEST_F(XMLNodeTest_42, DeleteChildren_RemovesAll_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));
    EXPECT_FALSE(root->NoChildren());
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

TEST_F(XMLNodeTest_42, DeleteChildren_EmptyElement_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

// ============================================================
// DeleteChild Tests
// ============================================================

TEST_F(XMLNodeTest_42, DeleteChild_RemovesSpecificChild_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->DeleteChild(child1);
    EXPECT_STREQ(root->FirstChild()->Value(), "child2");
}

// ============================================================
// Parent Tests
// ============================================================

TEST_F(XMLNodeTest_42, Parent_RootParentIsDocument_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->Parent(), &doc);
}

TEST_F(XMLNodeTest_42, Parent_ChildParentIsRoot_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    EXPECT_EQ(child->Parent(), root);
}

// ============================================================
// FirstChild / LastChild Tests
// ============================================================

TEST_F(XMLNodeTest_42, FirstChild_ReturnsFirstInserted_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("beta"));
    ASSERT_NE(root->FirstChild(), nullptr);
    EXPECT_STREQ(root->FirstChild()->Value(), "alpha");
}

TEST_F(XMLNodeTest_42, LastChild_ReturnsLastInserted_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("beta"));
    ASSERT_NE(root->LastChild(), nullptr);
    EXPECT_STREQ(root->LastChild()->Value(), "beta");
}

TEST_F(XMLNodeTest_42, FirstChild_NullWhenEmpty_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->FirstChild(), nullptr);
}

TEST_F(XMLNodeTest_42, LastChild_NullWhenEmpty_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->LastChild(), nullptr);
}

// ============================================================
// FirstChildElement / LastChildElement Tests
// ============================================================

TEST_F(XMLNodeTest_42, FirstChildElement_NoFilter_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("beta"));
    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "alpha");
}

TEST_F(XMLNodeTest_42, FirstChildElement_WithNameFilter_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("beta"));
    XMLElement* found = root->FirstChildElement("beta");
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(found->Value(), "beta");
}

TEST_F(XMLNodeTest_42, FirstChildElement_NotFound_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("alpha"));
    XMLElement* found = root->FirstChildElement("gamma");
    EXPECT_EQ(found, nullptr);
}

TEST_F(XMLNodeTest_42, LastChildElement_NoFilter_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("beta"));
    XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "beta");
}

TEST_F(XMLNodeTest_42, LastChildElement_WithNameFilter_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("beta"));
    root->InsertEndChild(doc.NewElement("alpha"));
    XMLElement* last = root->LastChildElement("alpha");
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "alpha");
    // Verify it's the last "alpha", not the first
    EXPECT_EQ(last->NextSiblingElement("alpha"), nullptr);
}

// ============================================================
// NextSibling / PreviousSibling Tests
// ============================================================

TEST_F(XMLNodeTest_42, NextSibling_Traversal_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));
    
    const XMLNode* node = root->FirstChild();
    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->Value(), "a");
    node = node->NextSibling();
    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->Value(), "b");
    node = node->NextSibling();
    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->Value(), "c");
    node = node->NextSibling();
    EXPECT_EQ(node, nullptr);
}

TEST_F(XMLNodeTest_42, PreviousSibling_Traversal_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));
    
    const XMLNode* node = root->LastChild();
    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->Value(), "c");
    node = node->PreviousSibling();
    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->Value(), "b");
    node = node->PreviousSibling();
    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->Value(), "a");
    node = node->PreviousSibling();
    EXPECT_EQ(node, nullptr);
}

// ============================================================
// NextSiblingElement / PreviousSiblingElement Tests
// ============================================================

TEST_F(XMLNodeTest_42, NextSiblingElement_WithName_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("a"));
    
    XMLElement* first_a = root->FirstChildElement("a");
    ASSERT_NE(first_a, nullptr);
    XMLElement* second_a = first_a->NextSiblingElement("a");
    ASSERT_NE(second_a, nullptr);
    EXPECT_STREQ(second_a->Value(), "a");
    EXPECT_NE(first_a, second_a);
}

TEST_F(XMLNodeTest_42, PreviousSiblingElement_WithName_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("a"));
    
    XMLElement* last_a = root->LastChildElement("a");
    ASSERT_NE(last_a, nullptr);
    XMLElement* first_a = last_a->PreviousSiblingElement("a");
    ASSERT_NE(first_a, nullptr);
    EXPECT_STREQ(first_a->Value(), "a");
    EXPECT_NE(first_a, last_a);
}

// ============================================================
// ChildElementCount Tests
// ============================================================

TEST_F(XMLNodeTest_42, ChildElementCount_Empty_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->ChildElementCount(), 0);
}

TEST_F(XMLNodeTest_42, ChildElementCount_Multiple_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("c"));
    EXPECT_EQ(root->ChildElementCount(), 3);
}

TEST_F(XMLNodeTest_42, ChildElementCount_WithNameFilter_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    root->InsertEndChild(doc.NewElement("a"));
    EXPECT_EQ(root->ChildElementCount("a"), 2);
    EXPECT_EQ(root->ChildElementCount("b"), 1);
    EXPECT_EQ(root->ChildElementCount("c"), 0);
}

// ============================================================
// DeepClone Tests
// ============================================================

TEST_F(XMLNodeTest_42, DeepClone_CopiesTree_42) {
    XMLDocument srcDoc;
    srcDoc.Parse("<root><child attr=\"val\"><grandchild/></child></root>");
    ASSERT_FALSE(srcDoc.Error());
    
    XMLDocument targetDoc;
    const XMLNode* clone = srcDoc.RootElement()->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(const_cast<XMLNode*>(clone));
    
    ASSERT_NE(targetDoc.RootElement(), nullptr);
    EXPECT_STREQ(targetDoc.RootElement()->Value(), "root");
    XMLElement* childClone = targetDoc.RootElement()->FirstChildElement("child");
    ASSERT_NE(childClone, nullptr);
    EXPECT_STREQ(childClone->Attribute("attr"), "val");
    ASSERT_NE(childClone->FirstChildElement("grandchild"), nullptr);
}

TEST_F(XMLNodeTest_42, DeepClone_ToSameDocument_42) {
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());
    
    const XMLNode* clone = doc.RootElement()->DeepClone(&doc);
    ASSERT_NE(clone, nullptr);
    EXPECT_STREQ(clone->Value(), "root");
}

// ============================================================
// ToElement / ToText / ToComment / ToDocument / ToDeclaration / ToUnknown
// ============================================================

TEST_F(XMLNodeTest_42, ToElement_OnElement_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_NE(root->ToElement(), nullptr);
    EXPECT_EQ(root->ToText(), nullptr);
    EXPECT_EQ(root->ToComment(), nullptr);
    EXPECT_EQ(root->ToDocument(), nullptr);
    EXPECT_EQ(root->ToDeclaration(), nullptr);
    EXPECT_EQ(root->ToUnknown(), nullptr);
}

TEST_F(XMLNodeTest_42, ToDocument_OnDocument_42) {
    EXPECT_NE(doc.ToDocument(), nullptr);
    EXPECT_EQ(doc.ToElement(), nullptr);
}

TEST_F(XMLNodeTest_42, ToComment_OnComment_42) {
    XMLComment* comment = doc.NewComment("test comment");
    doc.InsertEndChild(comment);
    EXPECT_NE(comment->ToComment(), nullptr);
    EXPECT_EQ(comment->ToElement(), nullptr);
}

TEST_F(XMLNodeTest_42, ToText_OnText_42) {
    doc.Parse("<root>hello</root>");
    XMLNode* textNode = doc.RootElement()->FirstChild();
    ASSERT_NE(textNode, nullptr);
    EXPECT_NE(textNode->ToText(), nullptr);
    EXPECT_EQ(textNode->ToElement(), nullptr);
}

TEST_F(XMLNodeTest_42, ToDeclaration_OnDeclaration_42) {
    XMLDeclaration* decl = doc.NewDeclaration();
    doc.InsertFirstChild(decl);
    EXPECT_NE(decl->ToDeclaration(), nullptr);
    EXPECT_EQ(decl->ToElement(), nullptr);
}

TEST_F(XMLNodeTest_42, ToUnknown_OnUnknown_42) {
    XMLUnknown* unknown = doc.NewUnknown("something");
    doc.InsertEndChild(unknown);
    EXPECT_NE(unknown->ToUnknown(), nullptr);
    EXPECT_EQ(unknown->ToElement(), nullptr);
}

// ============================================================
// UserData Tests
// ============================================================

TEST_F(XMLNodeTest_42, UserData_DefaultNull_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(root->GetUserData(), nullptr);
}

TEST_F(XMLNodeTest_42, UserData_SetAndGet_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    int data = 42;
    root->SetUserData(&data);
    EXPECT_EQ(root->GetUserData(), &data);
}

TEST_F(XMLNodeTest_42, UserData_SetToNull_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    int data = 42;
    root->SetUserData(&data);
    root->SetUserData(nullptr);
    EXPECT_EQ(root->GetUserData(), nullptr);
}

// ============================================================
// GetLineNum Tests
// ============================================================

TEST_F(XMLNodeTest_42, GetLineNum_ParsedDocument_42) {
    const char* xml = "<root>\n  <child/>\n</root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetLineNum(), 1);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->GetLineNum(), 2);
}

// ============================================================
// LinkEndChild (alias for InsertEndChild) Tests
// ============================================================

TEST_F(XMLNodeTest_42, LinkEndChild_Works_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->LinkEndChild(child);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(root->LastChild()->Value(), "child");
}

// ============================================================
// Accept (Visitor) Tests
// ============================================================

TEST_F(XMLNodeTest_42, Accept_PrinterVisitor_42) {
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());
    XMLPrinter printer;
    doc.Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
    EXPECT_NE(std::string(result).find("child"), std::string::npos);
}

// ============================================================
// Boundary: Inserting child from different document
// ============================================================

TEST_F(XMLNodeTest_42, InsertEndChild_FromDifferentDocument_42) {
    // Nodes from a different document should not be insertable (or handled gracefully)
    XMLDocument doc2;
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* foreign = doc2.NewElement("foreign");
    // The behavior here depends on implementation - it may return null
    XMLNode* result = root->InsertEndChild(foreign);
    // If the implementation guards against cross-doc insertion, result should be null
    // We just verify it doesn't crash; the exact behavior depends on implementation
    (void)result;
}

// ============================================================
// Parse and structure Tests
// ============================================================

TEST_F(XMLNodeTest_42, Parse_ComplexStructure_42) {
    const char* xml = 
        "<root>"
        "  <a><x/><y/></a>"
        "  <b/>"
        "  <c><z/></c>"
        "</root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 3);
    
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    EXPECT_EQ(a->ChildElementCount(), 2);
    
    XMLElement* b = a->NextSiblingElement();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Value(), "b");
    EXPECT_TRUE(b->NoChildren());
    
    XMLElement* c = root->LastChildElement("c");
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->ChildElementCount(), 1);
}

// ============================================================
// ShallowClone / ShallowEqual Tests
// ============================================================

TEST_F(XMLNodeTest_42, ShallowClone_Element_42) {
    doc.Parse("<root attr=\"val\"><child/></root>");
    ASSERT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLNode* clone = root->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    EXPECT_STREQ(clone->Value(), "root");
    // ShallowClone should not copy children
    EXPECT_TRUE(clone->NoChildren());
}

TEST_F(XMLNodeTest_42, ShallowEqual_SameElements_42) {
    doc.Parse("<root attr=\"val\"/>");
    ASSERT_FALSE(doc.Error());
    
    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    ASSERT_FALSE(doc2.Error());
    
    EXPECT_TRUE(doc.RootElement()->ShallowEqual(doc2.RootElement()));
}

TEST_F(XMLNodeTest_42, ShallowEqual_DifferentElements_42) {
    doc.Parse("<root attr=\"val\"/>");
    ASSERT_FALSE(doc.Error());
    
    XMLDocument doc2;
    doc2.Parse("<other attr=\"val\"/>");
    ASSERT_FALSE(doc2.Error());
    
    EXPECT_FALSE(doc.RootElement()->ShallowEqual(doc2.RootElement()));
}

// ============================================================
// Edge case: Empty string element name
// ============================================================

TEST_F(XMLNodeTest_42, FirstChildElement_EmptyName_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("child"));
    // Passing nullptr should return the first child element
    XMLElement* found = root->FirstChildElement(nullptr);
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(found->Value(), "child");
}

TEST_F(XMLNodeTest_42, LastChildElement_NullName_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));
    XMLElement* found = root->LastChildElement(nullptr);
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(found->Value(), "b");
}

// ============================================================
// Delete and re-add Tests
// ============================================================

TEST_F(XMLNodeTest_42, DeleteAndReinsert_42) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    
    EXPECT_EQ(root->ChildElementCount(), 2);
    root->DeleteChild(child1);
    EXPECT_EQ(root->ChildElementCount(), 1);
    
    XMLElement* child3 = doc.NewElement("child3");
    root->InsertFirstChild(child3);
    EXPECT_EQ(root->ChildElementCount(), 2);
    EXPECT_STREQ(root->FirstChildElement()->Value(), "child3");
    EXPECT_STREQ(root->LastChildElement()->Value(), "child2");
}
