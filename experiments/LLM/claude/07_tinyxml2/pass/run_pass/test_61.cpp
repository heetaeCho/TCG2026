#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_61 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// ==================== UserData Tests ====================

TEST_F(XMLNodeTest_61, SetAndGetUserData_61) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    int myData = 42;
    elem->SetUserData(&myData);
    
    void* retrieved = elem->GetUserData();
    EXPECT_EQ(retrieved, &myData);
    EXPECT_EQ(*static_cast<int*>(retrieved), 42);
}

TEST_F(XMLNodeTest_61, UserDataDefaultsToNull_61) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    EXPECT_EQ(elem->GetUserData(), nullptr);
}

TEST_F(XMLNodeTest_61, SetUserDataToNull_61) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    int myData = 10;
    elem->SetUserData(&myData);
    EXPECT_EQ(elem->GetUserData(), &myData);
    
    elem->SetUserData(nullptr);
    EXPECT_EQ(elem->GetUserData(), nullptr);
}

// ==================== Value Tests ====================

TEST_F(XMLNodeTest_61, ElementValueIsTagName_61) {
    XMLElement* elem = doc.NewElement("MyElement");
    doc.InsertEndChild(elem);
    
    EXPECT_STREQ(elem->Value(), "MyElement");
}

TEST_F(XMLNodeTest_61, SetValueChangesValue_61) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertEndChild(elem);
    
    elem->SetValue("modified", false);
    EXPECT_STREQ(elem->Value(), "modified");
}

TEST_F(XMLNodeTest_61, SetValueStaticMem_61) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertEndChild(elem);
    
    static const char* staticStr = "staticValue";
    elem->SetValue(staticStr, true);
    EXPECT_STREQ(elem->Value(), "staticValue");
}

// ==================== Child Insertion Tests ====================

TEST_F(XMLNodeTest_61, InsertEndChild_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    
    XMLNode* result1 = parent->InsertEndChild(child1);
    XMLNode* result2 = parent->InsertEndChild(child2);
    
    EXPECT_EQ(result1, child1);
    EXPECT_EQ(result2, child2);
    
    EXPECT_STREQ(parent->FirstChildElement()->Value(), "child1");
    EXPECT_STREQ(parent->LastChildElement()->Value(), "child2");
}

TEST_F(XMLNodeTest_61, InsertFirstChild_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    
    parent->InsertFirstChild(child1);
    parent->InsertFirstChild(child2);
    
    EXPECT_STREQ(parent->FirstChildElement()->Value(), "child2");
    EXPECT_STREQ(parent->LastChildElement()->Value(), "child1");
}

TEST_F(XMLNodeTest_61, InsertAfterChild_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child3 = doc.NewElement("child3");
    XMLElement* child2 = doc.NewElement("child2");
    
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child3);
    parent->InsertAfterChild(child1, child2);
    
    EXPECT_STREQ(parent->FirstChildElement()->Value(), "child1");
    EXPECT_STREQ(parent->FirstChildElement()->NextSiblingElement()->Value(), "child2");
    EXPECT_STREQ(parent->LastChildElement()->Value(), "child3");
}

TEST_F(XMLNodeTest_61, LinkEndChildSameAsInsertEndChild_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = parent->LinkEndChild(child);
    
    EXPECT_EQ(result, child);
    EXPECT_STREQ(parent->FirstChildElement()->Value(), "child");
}

// ==================== NoChildren / FirstChild / LastChild Tests ====================

TEST_F(XMLNodeTest_61, NoChildrenWhenEmpty_61) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    
    EXPECT_TRUE(elem->NoChildren());
}

TEST_F(XMLNodeTest_61, NoChildrenFalseWithChildren_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    
    EXPECT_FALSE(parent->NoChildren());
}

TEST_F(XMLNodeTest_61, FirstChildAndLastChildNull_61) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    
    EXPECT_EQ(elem->FirstChild(), nullptr);
    EXPECT_EQ(elem->LastChild(), nullptr);
}

TEST_F(XMLNodeTest_61, FirstChildAndLastChildSingle_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    
    EXPECT_EQ(parent->FirstChild(), child);
    EXPECT_EQ(parent->LastChild(), child);
}

// ==================== Sibling Tests ====================

TEST_F(XMLNodeTest_61, NextSiblingAndPreviousSibling_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");
    
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->InsertEndChild(child3);
    
    EXPECT_EQ(child1->NextSibling(), child2);
    EXPECT_EQ(child2->NextSibling(), child3);
    EXPECT_EQ(child3->NextSibling(), nullptr);
    
    EXPECT_EQ(child3->PreviousSibling(), child2);
    EXPECT_EQ(child2->PreviousSibling(), child1);
    EXPECT_EQ(child1->PreviousSibling(), nullptr);
}

TEST_F(XMLNodeTest_61, NextSiblingElement_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* a2 = doc.NewElement("a");
    
    parent->InsertEndChild(a);
    parent->InsertEndChild(b);
    parent->InsertEndChild(a2);
    
    EXPECT_EQ(a->NextSiblingElement("b"), b);
    EXPECT_EQ(a->NextSiblingElement("a"), a2);
    EXPECT_EQ(b->NextSiblingElement("a"), a2);
}

TEST_F(XMLNodeTest_61, PreviousSiblingElement_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* a = doc.NewElement("a");
    XMLElement* b = doc.NewElement("b");
    XMLElement* a2 = doc.NewElement("a");
    
    parent->InsertEndChild(a);
    parent->InsertEndChild(b);
    parent->InsertEndChild(a2);
    
    EXPECT_EQ(a2->PreviousSiblingElement("b"), b);
    EXPECT_EQ(a2->PreviousSiblingElement("a"), a);
}

// ==================== FirstChildElement / LastChildElement with name ====================

TEST_F(XMLNodeTest_61, FirstChildElementByName_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    XMLElement* a2 = doc.NewElement("alpha");
    
    parent->InsertEndChild(a);
    parent->InsertEndChild(b);
    parent->InsertEndChild(a2);
    
    EXPECT_EQ(parent->FirstChildElement("alpha"), a);
    EXPECT_EQ(parent->FirstChildElement("beta"), b);
    EXPECT_EQ(parent->FirstChildElement("gamma"), nullptr);
}

TEST_F(XMLNodeTest_61, LastChildElementByName_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    XMLElement* a2 = doc.NewElement("alpha");
    
    parent->InsertEndChild(a);
    parent->InsertEndChild(b);
    parent->InsertEndChild(a2);
    
    EXPECT_EQ(parent->LastChildElement("alpha"), a2);
    EXPECT_EQ(parent->LastChildElement("beta"), b);
    EXPECT_EQ(parent->LastChildElement("gamma"), nullptr);
}

TEST_F(XMLNodeTest_61, FirstChildElementNoName_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* a = doc.NewElement("alpha");
    parent->InsertEndChild(a);
    
    EXPECT_EQ(parent->FirstChildElement(), a);
}

TEST_F(XMLNodeTest_61, LastChildElementNoName_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* a = doc.NewElement("alpha");
    XMLElement* b = doc.NewElement("beta");
    parent->InsertEndChild(a);
    parent->InsertEndChild(b);
    
    EXPECT_EQ(parent->LastChildElement(), b);
}

// ==================== Parent Tests ====================

TEST_F(XMLNodeTest_61, ParentIsCorrect_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    
    EXPECT_EQ(child->Parent(), parent);
    EXPECT_EQ(parent->Parent(), &doc);
}

// ==================== DeleteChildren Tests ====================

TEST_F(XMLNodeTest_61, DeleteChildrenRemovesAll_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    parent->InsertEndChild(doc.NewElement("child1"));
    parent->InsertEndChild(doc.NewElement("child2"));
    parent->InsertEndChild(doc.NewElement("child3"));
    
    EXPECT_FALSE(parent->NoChildren());
    
    parent->DeleteChildren();
    
    EXPECT_TRUE(parent->NoChildren());
    EXPECT_EQ(parent->FirstChild(), nullptr);
    EXPECT_EQ(parent->LastChild(), nullptr);
}

TEST_F(XMLNodeTest_61, DeleteChildRemovesSpecific_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");
    
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->InsertEndChild(child3);
    
    parent->DeleteChild(child2);
    
    EXPECT_EQ(parent->FirstChildElement(), child1);
    EXPECT_EQ(child1->NextSiblingElement(), child3);
    EXPECT_EQ(parent->LastChildElement(), child3);
}

// ==================== ChildElementCount Tests ====================

TEST_F(XMLNodeTest_61, ChildElementCountZero_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    EXPECT_EQ(parent->ChildElementCount(), 0);
}

TEST_F(XMLNodeTest_61, ChildElementCountMultiple_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    parent->InsertEndChild(doc.NewElement("a"));
    parent->InsertEndChild(doc.NewElement("b"));
    parent->InsertEndChild(doc.NewElement("a"));
    
    EXPECT_EQ(parent->ChildElementCount(), 3);
}

TEST_F(XMLNodeTest_61, ChildElementCountByName_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    parent->InsertEndChild(doc.NewElement("a"));
    parent->InsertEndChild(doc.NewElement("b"));
    parent->InsertEndChild(doc.NewElement("a"));
    
    EXPECT_EQ(parent->ChildElementCount("a"), 2);
    EXPECT_EQ(parent->ChildElementCount("b"), 1);
    EXPECT_EQ(parent->ChildElementCount("c"), 0);
}

// ==================== GetDocument Tests ====================

TEST_F(XMLNodeTest_61, GetDocumentReturnsOwningDocument_61) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    EXPECT_EQ(elem->GetDocument(), &doc);
}

// ==================== DeepClone Tests ====================

TEST_F(XMLNodeTest_61, DeepCloneCreatesIndependentCopy_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    
    XMLElement* grandchild = doc.NewElement("grandchild");
    child->InsertEndChild(grandchild);
    
    XMLDocument targetDoc;
    XMLNode* cloned = parent->DeepClone(&targetDoc);
    targetDoc.InsertEndChild(cloned);
    
    ASSERT_NE(cloned, nullptr);
    ASSERT_NE(cloned->ToElement(), nullptr);
    EXPECT_STREQ(cloned->Value(), "parent");
    
    XMLElement* clonedChild = cloned->FirstChildElement("child");
    ASSERT_NE(clonedChild, nullptr);
    
    XMLElement* clonedGrandchild = clonedChild->FirstChildElement("grandchild");
    ASSERT_NE(clonedGrandchild, nullptr);
    
    // Verify independence
    EXPECT_NE(clonedChild, child);
    EXPECT_NE(clonedGrandchild, grandchild);
}

// ==================== ToElement / ToText / ToComment / ToDocument / ToDeclaration / ToUnknown ====================

TEST_F(XMLNodeTest_61, ToElementOnElement_61) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    EXPECT_NE(elem->ToElement(), nullptr);
    EXPECT_EQ(elem->ToText(), nullptr);
    EXPECT_EQ(elem->ToComment(), nullptr);
    EXPECT_EQ(elem->ToDocument(), nullptr);
    EXPECT_EQ(elem->ToDeclaration(), nullptr);
    EXPECT_EQ(elem->ToUnknown(), nullptr);
}

TEST_F(XMLNodeTest_61, ToDocumentOnDocument_61) {
    EXPECT_NE(doc.ToDocument(), nullptr);
    EXPECT_EQ(doc.ToElement(), nullptr);
}

TEST_F(XMLNodeTest_61, ToCommentOnComment_61) {
    XMLComment* comment = doc.NewComment("a comment");
    doc.InsertEndChild(comment);
    
    EXPECT_NE(comment->ToComment(), nullptr);
    EXPECT_EQ(comment->ToElement(), nullptr);
}

TEST_F(XMLNodeTest_61, ToTextOnText_61) {
    XMLText* text = doc.NewText("some text");
    XMLElement* elem = doc.NewElement("holder");
    doc.InsertEndChild(elem);
    elem->InsertEndChild(text);
    
    EXPECT_NE(text->ToText(), nullptr);
    EXPECT_EQ(text->ToElement(), nullptr);
}

TEST_F(XMLNodeTest_61, ToDeclarationOnDeclaration_61) {
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    doc.InsertEndChild(decl);
    
    EXPECT_NE(decl->ToDeclaration(), nullptr);
    EXPECT_EQ(decl->ToElement(), nullptr);
}

// ==================== Parsing / Integration Tests ====================

TEST_F(XMLNodeTest_61, ParseAndTraverseTree_61) {
    const char* xml = "<root><a><b/></a><c/></root>";
    doc.Parse(xml);
    
    ASSERT_EQ(doc.ErrorID(), 0);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    
    XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    
    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    
    EXPECT_EQ(a->NextSiblingElement(), c);
    EXPECT_EQ(c->PreviousSiblingElement(), a);
}

// ==================== InsertEndChild with null ====================

TEST_F(XMLNodeTest_61, InsertEndChildFromDifferentDocument_61) {
    XMLDocument doc2;
    XMLElement* foreignChild = doc2.NewElement("foreign");
    
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    // Inserting node from different document should fail / return null
    XMLNode* result = parent->InsertEndChild(foreignChild);
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLNodeTest_61, InsertFirstChildFromDifferentDocument_61) {
    XMLDocument doc2;
    XMLElement* foreignChild = doc2.NewElement("foreign");
    
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLNode* result = parent->InsertFirstChild(foreignChild);
    EXPECT_EQ(result, nullptr);
}

// ==================== GetLineNum ====================

TEST_F(XMLNodeTest_61, GetLineNumAfterParse_61) {
    const char* xml = "<root>\n  <child/>\n</root>";
    doc.Parse(xml);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetLineNum(), 1);
    
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->GetLineNum(), 2);
}

// ==================== ShallowEqual / ShallowClone ====================

TEST_F(XMLNodeTest_61, ShallowCloneElement_61) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetAttribute("attr", "value");
    doc.InsertEndChild(elem);
    
    XMLNode* cloned = elem->ShallowClone(&doc);
    ASSERT_NE(cloned, nullptr);
    ASSERT_NE(cloned->ToElement(), nullptr);
    EXPECT_STREQ(cloned->Value(), "test");
    EXPECT_STREQ(cloned->ToElement()->Attribute("attr"), "value");
    
    // Shallow clone should not have children
    EXPECT_TRUE(cloned->NoChildren());
    
    // Clean up - the cloned node is not inserted into tree
    doc.DeleteNode(cloned);
}

TEST_F(XMLNodeTest_61, ShallowEqualSameElements_61) {
    XMLElement* elem1 = doc.NewElement("test");
    elem1->SetAttribute("key", "val");
    
    XMLElement* elem2 = doc.NewElement("test");
    elem2->SetAttribute("key", "val");
    
    EXPECT_TRUE(elem1->ShallowEqual(elem2));
    
    doc.DeleteNode(elem1);
    doc.DeleteNode(elem2);
}

TEST_F(XMLNodeTest_61, ShallowEqualDifferentElements_61) {
    XMLElement* elem1 = doc.NewElement("test1");
    XMLElement* elem2 = doc.NewElement("test2");
    
    EXPECT_FALSE(elem1->ShallowEqual(elem2));
    
    doc.DeleteNode(elem1);
    doc.DeleteNode(elem2);
}

// ==================== DeleteChild from middle preserves siblings ====================

TEST_F(XMLNodeTest_61, DeleteFirstChildPreservesRest_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    XMLElement* c3 = doc.NewElement("c3");
    
    parent->InsertEndChild(c1);
    parent->InsertEndChild(c2);
    parent->InsertEndChild(c3);
    
    parent->DeleteChild(c1);
    
    EXPECT_EQ(parent->FirstChildElement(), c2);
    EXPECT_EQ(parent->LastChildElement(), c3);
    EXPECT_EQ(c2->PreviousSibling(), nullptr);
}

TEST_F(XMLNodeTest_61, DeleteLastChildPreservesRest_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    XMLElement* c3 = doc.NewElement("c3");
    
    parent->InsertEndChild(c1);
    parent->InsertEndChild(c2);
    parent->InsertEndChild(c3);
    
    parent->DeleteChild(c3);
    
    EXPECT_EQ(parent->FirstChildElement(), c1);
    EXPECT_EQ(parent->LastChildElement(), c2);
    EXPECT_EQ(c2->NextSibling(), nullptr);
}

// ==================== Multiple user data overwrites ====================

TEST_F(XMLNodeTest_61, UserDataOverwrite_61) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    int a = 1, b = 2, c = 3;
    
    elem->SetUserData(&a);
    EXPECT_EQ(elem->GetUserData(), &a);
    
    elem->SetUserData(&b);
    EXPECT_EQ(elem->GetUserData(), &b);
    
    elem->SetUserData(&c);
    EXPECT_EQ(elem->GetUserData(), &c);
}

// ==================== Accept visitor ====================

TEST_F(XMLNodeTest_61, AcceptVisitorPrinter_61) {
    const char* xml = "<root><child>text</child></root>";
    doc.Parse(xml);
    
    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    EXPECT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
    EXPECT_NE(std::string(output).find("child"), std::string::npos);
    EXPECT_NE(std::string(output).find("text"), std::string::npos);
}

// ==================== Const correctness via parsed doc ====================

TEST_F(XMLNodeTest_61, ConstAccessors_61) {
    const char* xml = "<root><a/><b/></root>";
    doc.Parse(xml);
    
    const XMLDocument& constDoc = doc;
    const XMLElement* root = constDoc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    
    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    
    const XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    
    EXPECT_EQ(a->NextSiblingElement("b"), b);
    EXPECT_EQ(b->PreviousSiblingElement("a"), a);
    
    EXPECT_EQ(root->ChildElementCount(), 2);
    EXPECT_EQ(root->ChildElementCount("a"), 1);
}

// ==================== InsertAfterChild at end ====================

TEST_F(XMLNodeTest_61, InsertAfterLastChild_61) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    XMLElement* c3 = doc.NewElement("c3");
    
    parent->InsertEndChild(c1);
    parent->InsertEndChild(c2);
    
    parent->InsertAfterChild(c2, c3);
    
    EXPECT_EQ(parent->LastChildElement(), c3);
    EXPECT_EQ(c2->NextSiblingElement(), c3);
    EXPECT_EQ(c3->PreviousSiblingElement(), c2);
}
