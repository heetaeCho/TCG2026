#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_50 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// ==================== Parent Tests ====================

TEST_F(XMLNodeTest_50, RootElementParentIsDocument_50) {
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChild();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->Parent(), &doc);
}

TEST_F(XMLNodeTest_50, DocumentHasNoParent_50) {
    EXPECT_EQ(doc.Parent(), nullptr);
}

TEST_F(XMLNodeTest_50, ChildElementParentIsCorrect_50) {
    doc.Parse("<root><child/></root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->Parent(), root);
}

// ==================== NoChildren Tests ====================

TEST_F(XMLNodeTest_50, EmptyDocumentNoChildren_50) {
    EXPECT_TRUE(doc.NoChildren());
}

TEST_F(XMLNodeTest_50, DocumentWithChildHasChildren_50) {
    doc.Parse("<root/>");
    EXPECT_FALSE(doc.NoChildren());
}

TEST_F(XMLNodeTest_50, EmptyElementNoChildren_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(root->NoChildren());
}

TEST_F(XMLNodeTest_50, ElementWithChildHasChildren_50) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_FALSE(root->NoChildren());
}

// ==================== Value Tests ====================

TEST_F(XMLNodeTest_50, ElementValueIsTagName_50) {
    doc.Parse("<root/>");
    const XMLNode* root = doc.FirstChild();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Value(), "root");
}

TEST_F(XMLNodeTest_50, TextNodeValueIsText_50) {
    doc.Parse("<root>Hello World</root>");
    const XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* text = root->FirstChild();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "Hello World");
}

TEST_F(XMLNodeTest_50, SetValueChangesValue_50) {
    doc.Parse("<root/>");
    XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetValue("newname", false);
    EXPECT_STREQ(root->Value(), "newname");
}

TEST_F(XMLNodeTest_50, SetValueStaticMem_50) {
    doc.Parse("<root/>");
    XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    static const char* staticName = "staticname";
    root->SetValue(staticName, true);
    EXPECT_STREQ(root->Value(), "staticname");
}

// ==================== FirstChild / LastChild Tests ====================

TEST_F(XMLNodeTest_50, FirstChildReturnsFirstChild_50) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");
}

TEST_F(XMLNodeTest_50, LastChildReturnsLastChild_50) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* last = root->LastChild();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "c");
}

TEST_F(XMLNodeTest_50, FirstChildNullWhenEmpty_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->FirstChild(), nullptr);
}

TEST_F(XMLNodeTest_50, LastChildNullWhenEmpty_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
}

// ==================== FirstChildElement / LastChildElement Tests ====================

TEST_F(XMLNodeTest_50, FirstChildElementByName_50) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Value(), "b");
}

TEST_F(XMLNodeTest_50, FirstChildElementNoName_50) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* first = root->FirstChildElement();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");
}

TEST_F(XMLNodeTest_50, LastChildElementByName_50) {
    doc.Parse("<root><a/><b/><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* lastA = root->LastChildElement("a");
    ASSERT_NE(lastA, nullptr);
    // The last 'a' should not be the first 'a'
    EXPECT_NE(lastA, root->FirstChildElement("a"));
}

TEST_F(XMLNodeTest_50, LastChildElementNoName_50) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* last = root->LastChildElement();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "c");
}

TEST_F(XMLNodeTest_50, FirstChildElementNotFound_50) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->FirstChildElement("z"), nullptr);
}

TEST_F(XMLNodeTest_50, LastChildElementNotFound_50) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->LastChildElement("z"), nullptr);
}

// ==================== Sibling Tests ====================

TEST_F(XMLNodeTest_50, NextSiblingTraversal_50) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* a = root->FirstChild();
    ASSERT_NE(a, nullptr);
    const XMLNode* b = a->NextSibling();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Value(), "b");
    const XMLNode* c = b->NextSibling();
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->Value(), "c");
    EXPECT_EQ(c->NextSibling(), nullptr);
}

TEST_F(XMLNodeTest_50, PreviousSiblingTraversal_50) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* c = root->LastChild();
    ASSERT_NE(c, nullptr);
    const XMLNode* b = c->PreviousSibling();
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Value(), "b");
    const XMLNode* a = b->PreviousSibling();
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Value(), "a");
    EXPECT_EQ(a->PreviousSibling(), nullptr);
}

TEST_F(XMLNodeTest_50, NextSiblingElementByName_50) {
    doc.Parse("<root><a/><b/><a/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* firstA = root->FirstChildElement("a");
    ASSERT_NE(firstA, nullptr);
    XMLElement* secondA = firstA->NextSiblingElement("a");
    ASSERT_NE(secondA, nullptr);
    EXPECT_NE(firstA, secondA);
    EXPECT_STREQ(secondA->Value(), "a");
}

TEST_F(XMLNodeTest_50, PreviousSiblingElementByName_50) {
    doc.Parse("<root><a/><b/><a/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    XMLElement* prevA = c->PreviousSiblingElement("a");
    ASSERT_NE(prevA, nullptr);
    EXPECT_STREQ(prevA->Value(), "a");
}

TEST_F(XMLNodeTest_50, NextSiblingElementNoName_50) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    XMLElement* next = a->NextSiblingElement();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Value(), "b");
}

// ==================== InsertEndChild Tests ====================

TEST_F(XMLNodeTest_50, InsertEndChildAddsToEnd_50) {
    doc.Parse("<root><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* newElem = doc.NewElement("b");
    XMLNode* result = root->InsertEndChild(newElem);
    EXPECT_NE(result, nullptr);
    const XMLNode* last = root->LastChild();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "b");
}

TEST_F(XMLNodeTest_50, InsertEndChildToEmpty_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* newElem = doc.NewElement("child");
    root->InsertEndChild(newElem);
    EXPECT_FALSE(root->NoChildren());
    EXPECT_STREQ(root->FirstChild()->Value(), "child");
    EXPECT_STREQ(root->LastChild()->Value(), "child");
}

// ==================== InsertFirstChild Tests ====================

TEST_F(XMLNodeTest_50, InsertFirstChildAddsToBeginning_50) {
    doc.Parse("<root><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* newElem = doc.NewElement("a");
    XMLNode* result = root->InsertFirstChild(newElem);
    EXPECT_NE(result, nullptr);
    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "a");
}

TEST_F(XMLNodeTest_50, InsertFirstChildToEmpty_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* newElem = doc.NewElement("first");
    root->InsertFirstChild(newElem);
    EXPECT_FALSE(root->NoChildren());
    EXPECT_STREQ(root->FirstChild()->Value(), "first");
}

// ==================== InsertAfterChild Tests ====================

TEST_F(XMLNodeTest_50, InsertAfterChildInMiddle_50) {
    doc.Parse("<root><a/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* a = root->FirstChild();
    ASSERT_NE(a, nullptr);
    XMLElement* b = doc.NewElement("b");
    XMLNode* result = root->InsertAfterChild(a, b);
    EXPECT_NE(result, nullptr);
    // Order should be a, b, c
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

TEST_F(XMLNodeTest_50, InsertAfterChildAtEnd_50) {
    doc.Parse("<root><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* a = root->FirstChild();
    XMLElement* b = doc.NewElement("b");
    root->InsertAfterChild(a, b);
    const XMLNode* last = root->LastChild();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "b");
}

// ==================== DeleteChildren Tests ====================

TEST_F(XMLNodeTest_50, DeleteChildrenRemovesAll_50) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_FALSE(root->NoChildren());
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
}

TEST_F(XMLNodeTest_50, DeleteChildrenOnEmpty_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->DeleteChildren(); // Should not crash
    EXPECT_TRUE(root->NoChildren());
}

// ==================== DeleteChild Tests ====================

TEST_F(XMLNodeTest_50, DeleteChildRemovesSpecificChild_50) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    root->DeleteChild(b);
    EXPECT_EQ(root->FirstChildElement("b"), nullptr);
    // a and c should remain
    EXPECT_NE(root->FirstChildElement("a"), nullptr);
    EXPECT_NE(root->FirstChildElement("c"), nullptr);
}

TEST_F(XMLNodeTest_50, DeleteChildFirstChild_50) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* a = root->FirstChild();
    root->DeleteChild(a);
    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_STREQ(first->Value(), "b");
}

TEST_F(XMLNodeTest_50, DeleteChildLastChild_50) {
    doc.Parse("<root><a/><b/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* b = root->LastChild();
    root->DeleteChild(b);
    const XMLNode* last = root->LastChild();
    ASSERT_NE(last, nullptr);
    EXPECT_STREQ(last->Value(), "a");
}

// ==================== ChildElementCount Tests ====================

TEST_F(XMLNodeTest_50, ChildElementCountAll_50) {
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 3);
}

TEST_F(XMLNodeTest_50, ChildElementCountByName_50) {
    doc.Parse("<root><a/><b/><a/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount("a"), 2);
    EXPECT_EQ(root->ChildElementCount("b"), 1);
    EXPECT_EQ(root->ChildElementCount("c"), 1);
    EXPECT_EQ(root->ChildElementCount("z"), 0);
}

TEST_F(XMLNodeTest_50, ChildElementCountEmpty_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 0);
}

TEST_F(XMLNodeTest_50, ChildElementCountDoesNotCountText_50) {
    doc.Parse("<root>text<a/>more text</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 1);
}

// ==================== GetDocument Tests ====================

TEST_F(XMLNodeTest_50, GetDocumentReturnsOwningDocument_50) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetDocument(), &doc);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->GetDocument(), &doc);
}

// ==================== DeepClone Tests ====================

TEST_F(XMLNodeTest_50, DeepCloneCreatesIdenticalTree_50) {
    doc.Parse("<root><a><b/></a><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLDocument targetDoc;
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);
    
    XMLElement* clonedRoot = targetDoc.FirstChildElement("root");
    ASSERT_NE(clonedRoot, nullptr);
    EXPECT_STREQ(clonedRoot->Value(), "root");
    
    XMLElement* clonedA = clonedRoot->FirstChildElement("a");
    ASSERT_NE(clonedA, nullptr);
    XMLElement* clonedB = clonedA->FirstChildElement("b");
    ASSERT_NE(clonedB, nullptr);
    XMLElement* clonedC = clonedRoot->FirstChildElement("c");
    ASSERT_NE(clonedC, nullptr);
}

TEST_F(XMLNodeTest_50, DeepCloneIntoDifferentDocument_50) {
    doc.Parse("<root attr='value'>text</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLDocument targetDoc;
    XMLNode* clone = root->DeepClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    targetDoc.InsertEndChild(clone);
    
    EXPECT_EQ(clone->GetDocument(), &targetDoc);
}

// ==================== UserData Tests ====================

TEST_F(XMLNodeTest_50, UserDataDefaultNull_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetUserData(), nullptr);
}

TEST_F(XMLNodeTest_50, SetAndGetUserData_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    int data = 42;
    root->SetUserData(&data);
    EXPECT_EQ(root->GetUserData(), &data);
}

TEST_F(XMLNodeTest_50, SetUserDataToNull_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    int data = 42;
    root->SetUserData(&data);
    root->SetUserData(nullptr);
    EXPECT_EQ(root->GetUserData(), nullptr);
}

// ==================== ToElement / ToText / ToComment / ToDocument / ToDeclaration / ToUnknown ====================

TEST_F(XMLNodeTest_50, ToElementReturnsNonNull_50) {
    doc.Parse("<root/>");
    XMLNode* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_NE(root->ToElement(), nullptr);
    EXPECT_EQ(root->ToText(), nullptr);
    EXPECT_EQ(root->ToComment(), nullptr);
    EXPECT_EQ(root->ToDocument(), nullptr);
    EXPECT_EQ(root->ToDeclaration(), nullptr);
    EXPECT_EQ(root->ToUnknown(), nullptr);
}

TEST_F(XMLNodeTest_50, ToTextReturnsNonNull_50) {
    doc.Parse("<root>hello</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* text = root->FirstChild();
    ASSERT_NE(text, nullptr);
    EXPECT_NE(text->ToText(), nullptr);
    EXPECT_EQ(text->ToElement(), nullptr);
}

TEST_F(XMLNodeTest_50, ToCommentReturnsNonNull_50) {
    doc.Parse("<root><!-- comment --></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* comment = root->FirstChild();
    ASSERT_NE(comment, nullptr);
    EXPECT_NE(comment->ToComment(), nullptr);
    EXPECT_EQ(comment->ToElement(), nullptr);
}

TEST_F(XMLNodeTest_50, ToDocumentReturnsNonNull_50) {
    XMLNode* docNode = &doc;
    EXPECT_NE(docNode->ToDocument(), nullptr);
    EXPECT_EQ(docNode->ToElement(), nullptr);
}

TEST_F(XMLNodeTest_50, ToDeclarationReturnsNonNull_50) {
    doc.Parse("<?xml version='1.0'?><root/>");
    XMLNode* first = doc.FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_NE(first->ToDeclaration(), nullptr);
}

// ==================== GetLineNum Tests ====================

TEST_F(XMLNodeTest_50, GetLineNumForParsedElement_50) {
    doc.Parse("<root>\n<child/>\n</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetLineNum(), 1);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->GetLineNum(), 2);
}

// ==================== LinkEndChild Tests (Alias for InsertEndChild) ====================

TEST_F(XMLNodeTest_50, LinkEndChildAddsToEnd_50) {
    doc.Parse("<root><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLElement* b = doc.NewElement("b");
    XMLNode* result = root->LinkEndChild(b);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(root->LastChild()->Value(), "b");
}

// ==================== Complex Tree Operations ====================

TEST_F(XMLNodeTest_50, MultiLevelTreeTraversal_50) {
    doc.Parse("<root><a><a1/><a2/></a><b><b1/></b></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    EXPECT_EQ(a->ChildElementCount(), 2);
    
    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    EXPECT_EQ(b->ChildElementCount(), 1);
    
    XMLElement* a1 = a->FirstChildElement("a1");
    ASSERT_NE(a1, nullptr);
    EXPECT_TRUE(a1->NoChildren());
    EXPECT_EQ(a1->Parent(), a);
}

TEST_F(XMLNodeTest_50, InsertAndDeleteMaintainsStructure_50) {
    doc.Parse("<root><a/><c/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    // Insert b between a and c
    XMLNode* a = root->FirstChild();
    XMLElement* b = doc.NewElement("b");
    root->InsertAfterChild(a, b);
    
    EXPECT_EQ(root->ChildElementCount(), 3);
    
    // Delete a
    root->DeleteChild(a);
    EXPECT_EQ(root->ChildElementCount(), 2);
    EXPECT_STREQ(root->FirstChild()->Value(), "b");
    EXPECT_STREQ(root->LastChild()->Value(), "c");
}

// ==================== Boundary: Single child operations ====================

TEST_F(XMLNodeTest_50, SingleChildFirstAndLastAreSame_50) {
    doc.Parse("<root><only/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->FirstChild(), root->LastChild());
    EXPECT_EQ(root->FirstChildElement(), root->LastChildElement());
}

TEST_F(XMLNodeTest_50, DeleteOnlyChild_50) {
    doc.Parse("<root><only/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* only = root->FirstChild();
    root->DeleteChild(only);
    EXPECT_TRUE(root->NoChildren());
    EXPECT_EQ(root->FirstChild(), nullptr);
    EXPECT_EQ(root->LastChild(), nullptr);
}

// ==================== ShallowEqual / ShallowClone via Element ====================

TEST_F(XMLNodeTest_50, ShallowCloneElement_50) {
    doc.Parse("<root attr='value'><child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLDocument targetDoc;
    const XMLNode* clone = root->ShallowClone(&targetDoc);
    ASSERT_NE(clone, nullptr);
    // ShallowClone should not copy children
    EXPECT_TRUE(clone->NoChildren());
}

TEST_F(XMLNodeTest_50, ShallowEqualSameElements_50) {
    doc.Parse("<root attr='value'/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLDocument doc2;
    doc2.Parse("<root attr='value'/>");
    XMLElement* root2 = doc2.FirstChildElement("root");
    ASSERT_NE(root2, nullptr);
    
    EXPECT_TRUE(root->ShallowEqual(root2));
}

TEST_F(XMLNodeTest_50, ShallowEqualDifferentElements_50) {
    doc.Parse("<root attr='value1'/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLDocument doc2;
    doc2.Parse("<root attr='value2'/>");
    XMLElement* root2 = doc2.FirstChildElement("root");
    ASSERT_NE(root2, nullptr);
    
    EXPECT_FALSE(root->ShallowEqual(root2));
}

// ==================== Accept (Visitor) Tests ====================

TEST_F(XMLNodeTest_50, AcceptWithPrinter_50) {
    doc.Parse("<root><child/></root>");
    XMLPrinter printer;
    doc.Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // The output should contain root and child
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
    EXPECT_NE(std::string(result).find("child"), std::string::npos);
}

// ==================== Error case: InsertEndChild from different document ====================

TEST_F(XMLNodeTest_50, InsertChildFromDifferentDocumentReturnsNull_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLDocument otherDoc;
    XMLElement* foreign = otherDoc.NewElement("foreign");
    
    // Inserting a node from a different document should fail
    XMLNode* result = root->InsertEndChild(foreign);
    // Per tinyxml2 behavior, this should return null
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLNodeTest_50, InsertFirstChildFromDifferentDocumentReturnsNull_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLDocument otherDoc;
    XMLElement* foreign = otherDoc.NewElement("foreign");
    
    XMLNode* result = root->InsertFirstChild(foreign);
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLNodeTest_50, InsertAfterChildFromDifferentDocumentReturnsNull_50) {
    doc.Parse("<root><a/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLNode* a = root->FirstChild();
    
    XMLDocument otherDoc;
    XMLElement* foreign = otherDoc.NewElement("foreign");
    
    XMLNode* result = root->InsertAfterChild(a, foreign);
    EXPECT_EQ(result, nullptr);
}

// ==================== Multiple insertions ====================

TEST_F(XMLNodeTest_50, MultipleInsertionsOrder_50) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    root->InsertEndChild(doc.NewElement("c"));
    root->InsertFirstChild(doc.NewElement("a"));
    XMLNode* a = root->FirstChild();
    root->InsertAfterChild(a, doc.NewElement("b"));
    
    EXPECT_EQ(root->ChildElementCount(), 3);
    EXPECT_STREQ(root->FirstChildElement()->Value(), "a");
    EXPECT_STREQ(root->FirstChildElement()->NextSiblingElement()->Value(), "b");
    EXPECT_STREQ(root->LastChildElement()->Value(), "c");
}
