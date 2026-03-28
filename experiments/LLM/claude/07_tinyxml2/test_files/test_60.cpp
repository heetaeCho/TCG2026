#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_60 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ============================================================
// LinkEndChild / InsertEndChild Tests
// ============================================================

TEST_F(XMLNodeTest_60, LinkEndChild_AddsChildToEnd_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->LinkEndChild(child1);
    root->LinkEndChild(child2);

    ASSERT_NE(root->FirstChild(), nullptr);
    ASSERT_NE(root->LastChild(), nullptr);
    EXPECT_STREQ(root->FirstChildElement()->Name(), "child1");
    EXPECT_STREQ(root->LastChildElement()->Name(), "child2");
}

TEST_F(XMLNodeTest_60, InsertEndChild_AddsChildToEnd_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->InsertEndChild(child);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, child);
    EXPECT_STREQ(root->FirstChildElement()->Name(), "child");
}

TEST_F(XMLNodeTest_60, InsertEndChild_MultipleChildren_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    for (int i = 0; i < 5; i++) {
        char name[32];
        snprintf(name, sizeof(name), "child%d", i);
        XMLElement* child = doc.NewElement(name);
        root->InsertEndChild(child);
    }

    EXPECT_STREQ(root->FirstChildElement()->Name(), "child0");
    EXPECT_STREQ(root->LastChildElement()->Name(), "child4");
}

// ============================================================
// InsertFirstChild Tests
// ============================================================

TEST_F(XMLNodeTest_60, InsertFirstChild_AddsChildToBeginning_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->InsertEndChild(child1);
    root->InsertFirstChild(child2);

    EXPECT_STREQ(root->FirstChildElement()->Name(), "child2");
    EXPECT_STREQ(root->LastChildElement()->Name(), "child1");
}

TEST_F(XMLNodeTest_60, InsertFirstChild_OnEmptyNode_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->InsertFirstChild(child);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, child);
    EXPECT_STREQ(root->FirstChildElement()->Name(), "child");
    EXPECT_STREQ(root->LastChildElement()->Name(), "child");
}

// ============================================================
// InsertAfterChild Tests
// ============================================================

TEST_F(XMLNodeTest_60, InsertAfterChild_InsertsInMiddle_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");

    root->InsertEndChild(child1);
    root->InsertEndChild(child3);
    root->InsertAfterChild(child1, child2);

    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Name(), "child1");

    XMLElement* second = first->NextSiblingElement();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Name(), "child2");

    XMLElement* third = second->NextSiblingElement();
    ASSERT_NE(third, nullptr);
    EXPECT_STREQ(third->Name(), "child3");
}

TEST_F(XMLNodeTest_60, InsertAfterChild_AfterLastChild_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->InsertEndChild(child1);
    root->InsertAfterChild(child1, child2);

    EXPECT_STREQ(root->LastChildElement()->Name(), "child2");
}

// ============================================================
// DeleteChildren Tests
// ============================================================

TEST_F(XMLNodeTest_60, DeleteChildren_RemovesAllChildren_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("child1"));
    root->InsertEndChild(doc.NewElement("child2"));
    root->InsertEndChild(doc.NewElement("child3"));

    EXPECT_FALSE(root->NoChildren());

    root->DeleteChildren();

    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
}

TEST_F(XMLNodeTest_60, DeleteChildren_OnEmptyNode_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_TRUE(root->NoChildren());
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

// ============================================================
// DeleteChild Tests
// ============================================================

TEST_F(XMLNodeTest_60, DeleteChild_RemovesSpecificChild_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");

    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);

    root->DeleteChild(child2);

    XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Name(), "child1");

    XMLElement* second = first->NextSiblingElement();
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->Name(), "child3");

    EXPECT_EQ(second->NextSiblingElement(), nullptr);
}

TEST_F(XMLNodeTest_60, DeleteChild_RemoveFirstChild_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    root->DeleteChild(child1);

    EXPECT_STREQ(root->FirstChildElement()->Name(), "child2");
}

TEST_F(XMLNodeTest_60, DeleteChild_RemoveLastChild_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    root->DeleteChild(child2);

    EXPECT_STREQ(root->LastChildElement()->Name(), "child1");
}

// ============================================================
// NoChildren Tests
// ============================================================

TEST_F(XMLNodeTest_60, NoChildren_ReturnsTrueWhenEmpty_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_TRUE(root->NoChildren());
}

TEST_F(XMLNodeTest_60, NoChildren_ReturnsFalseWhenHasChildren_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("child"));

    EXPECT_FALSE(root->NoChildren());
}

// ============================================================
// Value / SetValue Tests
// ============================================================

TEST_F(XMLNodeTest_60, Value_ReturnsElementName_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_STREQ(root->Value(), "root");
}

TEST_F(XMLNodeTest_60, SetValue_ChangesValue_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->SetValue("newroot", false);

    EXPECT_STREQ(root->Value(), "newroot");
}

TEST_F(XMLNodeTest_60, SetValue_StaticMem_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->SetValue("staticroot", true);

    EXPECT_STREQ(root->Value(), "staticroot");
}

// ============================================================
// Parent Tests
// ============================================================

TEST_F(XMLNodeTest_60, Parent_ReturnsParentNode_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    EXPECT_EQ(child->Parent(), root);
}

TEST_F(XMLNodeTest_60, Parent_RootParentIsDocument_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_EQ(root->Parent(), &doc);
}

// ============================================================
// FirstChild / LastChild Tests
// ============================================================

TEST_F(XMLNodeTest_60, FirstChild_ReturnsFirstChild_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    EXPECT_EQ(root->FirstChild(), child1);
}

TEST_F(XMLNodeTest_60, LastChild_ReturnsLastChild_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    EXPECT_EQ(root->LastChild(), child2);
}

TEST_F(XMLNodeTest_60, FirstChild_ReturnsNullWhenEmpty_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_EQ(root->FirstChild(), nullptr);
}

TEST_F(XMLNodeTest_60, LastChild_ReturnsNullWhenEmpty_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_EQ(root->LastChild(), nullptr);
}

// ============================================================
// FirstChildElement / LastChildElement with name filter
// ============================================================

TEST_F(XMLNodeTest_60, FirstChildElement_WithName_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("beta"));
    root->InsertEndChild(doc.NewElement("alpha"));

    const XMLElement* found = root->FirstChildElement("beta");
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(found->Name(), "beta");
}

TEST_F(XMLNodeTest_60, FirstChildElement_WithNonexistentName_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("alpha"));

    const XMLElement* found = root->FirstChildElement("gamma");
    EXPECT_EQ(found, nullptr);
}

TEST_F(XMLNodeTest_60, LastChildElement_WithName_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* a1 = doc.NewElement("alpha");
    XMLElement* b1 = doc.NewElement("beta");
    XMLElement* a2 = doc.NewElement("alpha");

    root->InsertEndChild(a1);
    root->InsertEndChild(b1);
    root->InsertEndChild(a2);

    const XMLElement* found = root->LastChildElement("alpha");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, a2);
}

TEST_F(XMLNodeTest_60, FirstChildElement_NoName_ReturnsFirst_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    EXPECT_EQ(root->FirstChildElement(), child1);
}

TEST_F(XMLNodeTest_60, LastChildElement_NoName_ReturnsLast_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    EXPECT_EQ(root->LastChildElement(), child2);
}

// ============================================================
// Sibling Navigation Tests
// ============================================================

TEST_F(XMLNodeTest_60, NextSibling_ReturnsNextNode_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    EXPECT_EQ(child1->NextSibling(), child2);
}

TEST_F(XMLNodeTest_60, PreviousSibling_ReturnsPrevNode_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    root->InsertEndChild(child1);
    root->InsertEndChild(child2);

    EXPECT_EQ(child2->PreviousSibling(), child1);
}

TEST_F(XMLNodeTest_60, NextSibling_ReturnsNullAtEnd_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    EXPECT_EQ(child->NextSibling(), nullptr);
}

TEST_F(XMLNodeTest_60, PreviousSibling_ReturnsNullAtBeginning_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    EXPECT_EQ(child->PreviousSibling(), nullptr);
}

TEST_F(XMLNodeTest_60, NextSiblingElement_WithName_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    XMLElement* c = doc.NewElement("gamma");

    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);

    EXPECT_EQ(a->NextSiblingElement("gamma"), c);
}

TEST_F(XMLNodeTest_60, PreviousSiblingElement_WithName_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    XMLElement* c = doc.NewElement("gamma");

    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);

    EXPECT_EQ(c->PreviousSiblingElement("alpha"), a);
}

// ============================================================
// ChildElementCount Tests
// ============================================================

TEST_F(XMLNodeTest_60, ChildElementCount_ReturnsCorrectCount_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("child1"));
    root->InsertEndChild(doc.NewElement("child2"));
    root->InsertEndChild(doc.NewElement("child3"));

    EXPECT_EQ(root->ChildElementCount(), 3);
}

TEST_F(XMLNodeTest_60, ChildElementCount_ReturnsZeroWhenEmpty_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_EQ(root->ChildElementCount(), 0);
}

TEST_F(XMLNodeTest_60, ChildElementCount_WithName_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("beta"));
    root->InsertEndChild(doc.NewElement("alpha"));

    EXPECT_EQ(root->ChildElementCount("alpha"), 2);
    EXPECT_EQ(root->ChildElementCount("beta"), 1);
    EXPECT_EQ(root->ChildElementCount("gamma"), 0);
}

// ============================================================
// GetDocument Tests
// ============================================================

TEST_F(XMLNodeTest_60, GetDocument_ReturnsOwningDocument_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_EQ(root->GetDocument(), &doc);
}

TEST_F(XMLNodeTest_60, GetDocument_ChildReturnsOwningDocument_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    EXPECT_EQ(child->GetDocument(), &doc);
}

// ============================================================
// DeepClone Tests
// ============================================================

TEST_F(XMLNodeTest_60, DeepClone_ClonesTree_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    XMLElement* grandchild = doc.NewElement("grandchild");
    child->InsertEndChild(grandchild);

    XMLDocument targetDoc;
    XMLNode* cloned = root->DeepClone(&targetDoc);
    targetDoc.InsertEndChild(cloned);

    ASSERT_NE(cloned, nullptr);
    ASSERT_NE(cloned->ToElement(), nullptr);
    EXPECT_STREQ(cloned->ToElement()->Name(), "root");

    XMLElement* clonedChild = cloned->FirstChildElement("child");
    ASSERT_NE(clonedChild, nullptr);

    XMLElement* clonedGrandchild = clonedChild->FirstChildElement("grandchild");
    ASSERT_NE(clonedGrandchild, nullptr);
}

TEST_F(XMLNodeTest_60, DeepClone_IsIndependent_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    XMLDocument targetDoc;
    XMLNode* cloned = root->DeepClone(&targetDoc);
    targetDoc.InsertEndChild(cloned);

    // Modifying original shouldn't affect clone
    root->DeleteChildren();

    EXPECT_TRUE(root->NoChildren());
    ASSERT_NE(cloned->FirstChildElement("child"), nullptr);
}

// ============================================================
// UserData Tests
// ============================================================

TEST_F(XMLNodeTest_60, UserData_DefaultNull_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_EQ(root->GetUserData(), nullptr);
}

TEST_F(XMLNodeTest_60, UserData_SetAndGet_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    int data = 42;
    root->SetUserData(&data);

    EXPECT_EQ(root->GetUserData(), &data);
    EXPECT_EQ(*static_cast<int*>(root->GetUserData()), 42);
}

TEST_F(XMLNodeTest_60, UserData_SetToNull_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    int data = 42;
    root->SetUserData(&data);
    root->SetUserData(nullptr);

    EXPECT_EQ(root->GetUserData(), nullptr);
}

// ============================================================
// ToElement / ToText / ToComment / ToDocument Tests
// ============================================================

TEST_F(XMLNodeTest_60, ToElement_ReturnsNonNullForElement_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    EXPECT_NE(root->ToElement(), nullptr);
    EXPECT_EQ(root->ToText(), nullptr);
    EXPECT_EQ(root->ToComment(), nullptr);
    EXPECT_EQ(root->ToDocument(), nullptr);
}

TEST_F(XMLNodeTest_60, ToDocument_ForDocument_60) {
    EXPECT_NE(doc.ToDocument(), nullptr);
    EXPECT_EQ(doc.ToElement(), nullptr);
}

TEST_F(XMLNodeTest_60, ToComment_ForComment_60) {
    XMLComment* comment = doc.NewComment("a comment");
    doc.InsertEndChild(comment);

    EXPECT_NE(comment->ToComment(), nullptr);
    EXPECT_EQ(comment->ToElement(), nullptr);
}

TEST_F(XMLNodeTest_60, ToText_ForText_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLText* text = doc.NewText("hello");
    root->InsertEndChild(text);

    EXPECT_NE(text->ToText(), nullptr);
    EXPECT_EQ(text->ToElement(), nullptr);
}

// ============================================================
// LinkEndChild is alias for InsertEndChild
// ============================================================

TEST_F(XMLNodeTest_60, LinkEndChild_SameAsInsertEndChild_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");

    XMLNode* result1 = root->InsertEndChild(child1);
    XMLNode* result2 = root->LinkEndChild(child2);

    EXPECT_EQ(result1, child1);
    EXPECT_EQ(result2, child2);
    EXPECT_EQ(root->FirstChild(), child1);
    EXPECT_EQ(root->LastChild(), child2);
}

// ============================================================
// Boundary: Single child operations
// ============================================================

TEST_F(XMLNodeTest_60, SingleChild_DeleteMakesEmpty_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    EXPECT_FALSE(root->NoChildren());
    root->DeleteChild(child);
    EXPECT_TRUE(root->NoChildren());
}

TEST_F(XMLNodeTest_60, SingleChild_IsFirstAndLast_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    EXPECT_EQ(root->FirstChild(), child);
    EXPECT_EQ(root->LastChild(), child);
    EXPECT_EQ(child->NextSibling(), nullptr);
    EXPECT_EQ(child->PreviousSibling(), nullptr);
}

// ============================================================
// GetLineNum test
// ============================================================

TEST_F(XMLNodeTest_60, GetLineNum_ForNewElement_60) {
    XMLElement* root = doc.NewElement("root");
    // Newly created elements typically have line num 0
    EXPECT_EQ(root->GetLineNum(), 0);
    doc.InsertEndChild(root);
}

TEST_F(XMLNodeTest_60, GetLineNum_AfterParsing_60) {
    const char* xml = "<root>\n  <child/>\n</root>";
    XMLDocument parsedDoc;
    parsedDoc.Parse(xml);

    XMLElement* root = parsedDoc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_GE(root->GetLineNum(), 1);

    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_GE(child->GetLineNum(), 1);
}

// ============================================================
// Mixed content: text and elements
// ============================================================

TEST_F(XMLNodeTest_60, MixedContent_TextAndElements_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLText* text = doc.NewText("hello ");
    XMLElement* child = doc.NewElement("b");
    XMLText* text2 = doc.NewText(" world");

    root->InsertEndChild(text);
    root->InsertEndChild(child);
    root->InsertEndChild(text2);

    EXPECT_EQ(root->FirstChild(), text);
    EXPECT_EQ(root->LastChild(), text2);
    // Only element children count
    EXPECT_EQ(root->ChildElementCount(), 1);
}

// ============================================================
// InsertAfterChild with nullptr afterThis
// ============================================================

TEST_F(XMLNodeTest_60, InsertAfterChild_NullAfterThis_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    // Passing nullptr for afterThis - behavior may vary, just ensure no crash
    // and check return value
    XMLNode* result = root->InsertAfterChild(nullptr, child);
    // According to tinyxml2, if afterThis is null, it returns null
    // (or inserts at beginning depending on version). We just check for non-crash.
    // The result may be null.
    (void)result;
}

// ============================================================
// ShallowClone / ShallowEqual
// ============================================================

TEST_F(XMLNodeTest_60, ShallowClone_ClonesWithoutChildren_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    root->SetAttribute("attr", "value");

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    XMLDocument targetDoc;
    XMLNode* cloned = root->ShallowClone(&targetDoc);
    ASSERT_NE(cloned, nullptr);
    targetDoc.InsertEndChild(cloned);

    EXPECT_STREQ(cloned->ToElement()->Name(), "root");
    EXPECT_TRUE(cloned->NoChildren());
    EXPECT_STREQ(cloned->ToElement()->Attribute("attr"), "value");
}

TEST_F(XMLNodeTest_60, ShallowEqual_SameElement_60) {
    XMLElement* e1 = doc.NewElement("test");
    e1->SetAttribute("a", "1");

    XMLElement* e2 = doc.NewElement("test");
    e2->SetAttribute("a", "1");

    EXPECT_TRUE(e1->ShallowEqual(e2));

    doc.InsertEndChild(e1);
    // e2 not inserted but that's fine for comparison
}

TEST_F(XMLNodeTest_60, ShallowEqual_DifferentElements_60) {
    XMLElement* e1 = doc.NewElement("test1");
    XMLElement* e2 = doc.NewElement("test2");

    EXPECT_FALSE(e1->ShallowEqual(e2));

    doc.InsertEndChild(e1);
}

// ============================================================
// Accept (XMLVisitor) Tests
// ============================================================

TEST_F(XMLNodeTest_60, Accept_XMLPrinter_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);

    XMLPrinter printer;
    root->Accept(&printer);

    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // Should contain the element tags
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
    EXPECT_NE(std::string(result).find("child"), std::string::npos);
}

// ============================================================
// Document-level operations
// ============================================================

TEST_F(XMLNodeTest_60, Document_ParseAndNavigate_60) {
    const char* xml =
        "<root>"
        "  <a>1</a>"
        "  <b>2</b>"
        "  <c>3</c>"
        "</root>";

    XMLDocument parsedDoc;
    EXPECT_EQ(parsedDoc.Parse(xml), XML_SUCCESS);

    XMLElement* root = parsedDoc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->ChildElementCount(), 3);

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->GetText(), "1");

    XMLElement* c = root->LastChildElement("c");
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->GetText(), "3");
}

// ============================================================
// Insert child from different document should fail or be handled
// ============================================================

TEST_F(XMLNodeTest_60, InsertEndChild_FromSameDocument_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->InsertEndChild(child);

    EXPECT_NE(result, nullptr);
    EXPECT_EQ(child->GetDocument(), &doc);
}

// ============================================================
// Multiple delete and re-add
// ============================================================

TEST_F(XMLNodeTest_60, DeleteAndReaddChildren_60) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    root->InsertEndChild(doc.NewElement("a"));
    root->InsertEndChild(doc.NewElement("b"));

    EXPECT_EQ(root->ChildElementCount(), 2);

    root->DeleteChildren();
    EXPECT_EQ(root->ChildElementCount(), 0);

    root->InsertEndChild(doc.NewElement("c"));
    root->InsertEndChild(doc.NewElement("d"));
    root->InsertEndChild(doc.NewElement("e"));

    EXPECT_EQ(root->ChildElementCount(), 3);
    EXPECT_STREQ(root->FirstChildElement()->Name(), "c");
    EXPECT_STREQ(root->LastChildElement()->Name(), "e");
}
