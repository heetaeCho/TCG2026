#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_62 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// ==================== GetUserData / SetUserData Tests ====================

TEST_F(XMLNodeTest_62, GetUserDataReturnsNullByDefault_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_EQ(nullptr, root->GetUserData());
}

TEST_F(XMLNodeTest_62, SetUserDataAndRetrieve_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    int data = 42;
    root->SetUserData(&data);
    EXPECT_EQ(&data, root->GetUserData());
}

TEST_F(XMLNodeTest_62, SetUserDataToNull_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    int data = 10;
    root->SetUserData(&data);
    EXPECT_EQ(&data, root->GetUserData());
    root->SetUserData(nullptr);
    EXPECT_EQ(nullptr, root->GetUserData());
}

// ==================== Value / SetValue Tests ====================

TEST_F(XMLNodeTest_62, ElementValueMatchesTagName_62) {
    XMLElement* root = doc.NewElement("testElement");
    doc.InsertFirstChild(root);
    EXPECT_STREQ("testElement", root->Value());
}

TEST_F(XMLNodeTest_62, SetValueChangesNodeValue_62) {
    XMLElement* root = doc.NewElement("original");
    doc.InsertFirstChild(root);
    root->SetValue("modified", false);
    EXPECT_STREQ("modified", root->Value());
}

TEST_F(XMLNodeTest_62, SetValueStaticMem_62) {
    XMLElement* root = doc.NewElement("original");
    doc.InsertFirstChild(root);
    root->SetValue("static_value", true);
    EXPECT_STREQ("static_value", root->Value());
}

// ==================== NoChildren Tests ====================

TEST_F(XMLNodeTest_62, NoChildrenReturnsTrueWhenEmpty_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_TRUE(root->NoChildren());
}

TEST_F(XMLNodeTest_62, NoChildrenReturnsFalseWhenHasChildren_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertFirstChild(child);
    EXPECT_FALSE(root->NoChildren());
}

// ==================== InsertEndChild Tests ====================

TEST_F(XMLNodeTest_62, InsertEndChildAddsChild_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->InsertEndChild(child);
    EXPECT_EQ(child, result);
    EXPECT_FALSE(root->NoChildren());
}

TEST_F(XMLNodeTest_62, InsertEndChildMultiple_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    EXPECT_EQ(child1, root->FirstChild());
    EXPECT_EQ(child2, root->LastChild());
}

// ==================== InsertFirstChild Tests ====================

TEST_F(XMLNodeTest_62, InsertFirstChildAddsAtBeginning_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertFirstChild(child2);
    EXPECT_EQ(child2, root->FirstChild());
    EXPECT_EQ(child1, root->LastChild());
}

// ==================== InsertAfterChild Tests ====================

TEST_F(XMLNodeTest_62, InsertAfterChildInsertsCorrectly_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child3 = doc.NewElement("child3");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child3);
    root->InsertAfterChild(child1, child2);
    
    EXPECT_EQ(child1, root->FirstChild());
    EXPECT_EQ(child2, child1->NextSibling());
    EXPECT_EQ(child3, child2->NextSibling());
}

// ==================== FirstChild / LastChild Tests ====================

TEST_F(XMLNodeTest_62, FirstChildReturnsNullWhenNoChildren_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_EQ(nullptr, root->FirstChild());
}

TEST_F(XMLNodeTest_62, LastChildReturnsNullWhenNoChildren_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_EQ(nullptr, root->LastChild());
}

TEST_F(XMLNodeTest_62, FirstChildReturnsCorrectChild_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    EXPECT_EQ(child1, root->FirstChild());
}

TEST_F(XMLNodeTest_62, LastChildReturnsCorrectChild_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    EXPECT_EQ(child2, root->LastChild());
}

// ==================== FirstChildElement / LastChildElement Tests ====================

TEST_F(XMLNodeTest_62, FirstChildElementReturnsNullWhenNoElements_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_EQ(nullptr, root->FirstChildElement());
}

TEST_F(XMLNodeTest_62, FirstChildElementByName_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    EXPECT_EQ(child2, root->FirstChildElement("beta"));
}

TEST_F(XMLNodeTest_62, FirstChildElementByNameNotFound_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("alpha");
    root->InsertEndChild(child1);
    EXPECT_EQ(nullptr, root->FirstChildElement("nonexistent"));
}

TEST_F(XMLNodeTest_62, LastChildElementByName_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    XMLElement* child3 = doc.NewElement("alpha");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);
    EXPECT_EQ(child3, root->LastChildElement("alpha"));
}

// ==================== Sibling Tests ====================

TEST_F(XMLNodeTest_62, NextSiblingReturnsCorrectNode_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    EXPECT_EQ(child2, child1->NextSibling());
}

TEST_F(XMLNodeTest_62, PreviousSiblingReturnsCorrectNode_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    EXPECT_EQ(child1, child2->PreviousSibling());
}

TEST_F(XMLNodeTest_62, NextSiblingReturnsNullAtEnd_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    root->InsertEndChild(child1);
    EXPECT_EQ(nullptr, child1->NextSibling());
}

TEST_F(XMLNodeTest_62, PreviousSiblingReturnsNullAtBeginning_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    root->InsertEndChild(child1);
    EXPECT_EQ(nullptr, child1->PreviousSibling());
}

TEST_F(XMLNodeTest_62, NextSiblingElementByName_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    XMLElement* child3 = doc.NewElement("gamma");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);
    EXPECT_EQ(child3, child1->NextSiblingElement("gamma"));
}

TEST_F(XMLNodeTest_62, PreviousSiblingElementByName_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("alpha");
    XMLElement* child2 = doc.NewElement("beta");
    XMLElement* child3 = doc.NewElement("gamma");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->InsertEndChild(child3);
    EXPECT_EQ(child1, child3->PreviousSiblingElement("alpha"));
}

// ==================== Parent Tests ====================

TEST_F(XMLNodeTest_62, ParentReturnsCorrectParent_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    EXPECT_EQ(root, child->Parent());
}

TEST_F(XMLNodeTest_62, RootParentIsDocument_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_EQ(&doc, root->Parent());
}

// ==================== DeleteChildren Tests ====================

TEST_F(XMLNodeTest_62, DeleteChildrenRemovesAll_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    EXPECT_FALSE(root->NoChildren());
    root->DeleteChildren();
    EXPECT_TRUE(root->NoChildren());
}

// ==================== DeleteChild Tests ====================

TEST_F(XMLNodeTest_62, DeleteChildRemovesSpecificChild_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child1);
    root->InsertEndChild(child2);
    root->DeleteChild(child1);
    EXPECT_EQ(child2, root->FirstChild());
    EXPECT_EQ(child2, root->LastChild());
}

// ==================== ChildElementCount Tests ====================

TEST_F(XMLNodeTest_62, ChildElementCountZeroWhenEmpty_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_EQ(0, root->ChildElementCount());
}

TEST_F(XMLNodeTest_62, ChildElementCountReturnsCorrectCount_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->InsertEndChild(doc.NewElement("child1"));
    root->InsertEndChild(doc.NewElement("child2"));
    root->InsertEndChild(doc.NewElement("child3"));
    EXPECT_EQ(3, root->ChildElementCount());
}

TEST_F(XMLNodeTest_62, ChildElementCountByName_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->InsertEndChild(doc.NewElement("alpha"));
    root->InsertEndChild(doc.NewElement("beta"));
    root->InsertEndChild(doc.NewElement("alpha"));
    EXPECT_EQ(2, root->ChildElementCount("alpha"));
    EXPECT_EQ(1, root->ChildElementCount("beta"));
    EXPECT_EQ(0, root->ChildElementCount("gamma"));
}

// ==================== GetDocument Tests ====================

TEST_F(XMLNodeTest_62, GetDocumentReturnsOwningDocument_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_EQ(&doc, root->GetDocument());
}

// ==================== ToElement Tests ====================

TEST_F(XMLNodeTest_62, ToElementReturnsNonNullForElement_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_NE(nullptr, root->ToElement());
}

TEST_F(XMLNodeTest_62, ToTextReturnsNullForElement_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_EQ(nullptr, root->ToText());
}

TEST_F(XMLNodeTest_62, ToCommentReturnsNullForElement_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_EQ(nullptr, root->ToComment());
}

TEST_F(XMLNodeTest_62, ToDocumentReturnsNullForElement_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    EXPECT_EQ(nullptr, root->ToDocument());
}

// ==================== DeepClone Tests ====================

TEST_F(XMLNodeTest_62, DeepCloneClonesTree_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    XMLElement* grandchild = doc.NewElement("grandchild");
    child->InsertEndChild(grandchild);
    
    XMLDocument targetDoc;
    XMLNode* cloned = root->DeepClone(&targetDoc);
    targetDoc.InsertFirstChild(cloned);
    
    EXPECT_NE(nullptr, cloned);
    EXPECT_NE(nullptr, cloned->ToElement());
    EXPECT_STREQ("root", cloned->Value());
    EXPECT_NE(nullptr, cloned->FirstChildElement("child"));
    EXPECT_NE(nullptr, cloned->FirstChildElement("child")->FirstChildElement("grandchild"));
}

// ==================== GetLineNum Tests ====================

TEST_F(XMLNodeTest_62, GetLineNumForParsedDocument_62) {
    const char* xml = "<root>\n  <child/>\n</root>";
    XMLDocument parsedDoc;
    parsedDoc.Parse(xml);
    ASSERT_EQ(XML_SUCCESS, parsedDoc.ErrorID());
    XMLElement* root = parsedDoc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(1, root->GetLineNum());
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_EQ(2, child->GetLineNum());
}

// ==================== Comment Node Tests ====================

TEST_F(XMLNodeTest_62, CommentNodeToComment_62) {
    XMLComment* comment = doc.NewComment("test comment");
    doc.InsertFirstChild(comment);
    EXPECT_NE(nullptr, comment->ToComment());
    EXPECT_EQ(nullptr, comment->ToElement());
}

// ==================== Text Node Tests ====================

TEST_F(XMLNodeTest_62, TextNodeToText_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLText* text = doc.NewText("hello");
    root->InsertEndChild(text);
    EXPECT_NE(nullptr, text->ToText());
    EXPECT_EQ(nullptr, text->ToElement());
}

// ==================== Declaration Node Tests ====================

TEST_F(XMLNodeTest_62, DeclarationNodeToDeclaration_62) {
    XMLDeclaration* decl = doc.NewDeclaration();
    doc.InsertFirstChild(decl);
    EXPECT_NE(nullptr, decl->ToDeclaration());
    EXPECT_EQ(nullptr, decl->ToElement());
}

// ==================== LinkEndChild (alias) Tests ====================

TEST_F(XMLNodeTest_62, LinkEndChildBehavesLikeInsertEndChild_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = root->LinkEndChild(child);
    EXPECT_EQ(child, result);
    EXPECT_EQ(child, root->LastChild());
}

// ==================== Mixed Children Types ====================

TEST_F(XMLNodeTest_62, ChildElementCountIgnoresNonElements_62) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->InsertEndChild(doc.NewElement("elem1"));
    root->InsertEndChild(doc.NewComment("a comment"));
    root->InsertEndChild(doc.NewElement("elem2"));
    root->InsertEndChild(doc.NewText("some text"));
    EXPECT_EQ(2, root->ChildElementCount());
}

// ==================== Parsing XML Tests ====================

TEST_F(XMLNodeTest_62, ParseAndNavigate_62) {
    const char* xml = "<root><a><b/></a><c/></root>";
    XMLDocument parsedDoc;
    parsedDoc.Parse(xml);
    ASSERT_EQ(XML_SUCCESS, parsedDoc.ErrorID());
    
    XMLElement* root = parsedDoc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("root", root->Value());
    
    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(nullptr, a);
    
    XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(nullptr, b);
    
    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(nullptr, c);
    
    EXPECT_EQ(nullptr, c->NextSiblingElement());
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLNodeTest_62, ShallowEqualSameElement_62) {
    XMLElement* e1 = doc.NewElement("test");
    XMLElement* e2 = doc.NewElement("test");
    EXPECT_TRUE(e1->ShallowEqual(e2));
}

TEST_F(XMLNodeTest_62, ShallowEqualDifferentElement_62) {
    XMLElement* e1 = doc.NewElement("test1");
    XMLElement* e2 = doc.NewElement("test2");
    EXPECT_FALSE(e1->ShallowEqual(e2));
}

// ==================== InsertEndChild with null or wrong doc ====================

TEST_F(XMLNodeTest_62, InsertChildFromDifferentDocument_62) {
    XMLDocument doc2;
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* foreignChild = doc2.NewElement("foreign");
    // Inserting from a different document should fail (return null)
    XMLNode* result = root->InsertEndChild(foreignChild);
    EXPECT_EQ(nullptr, result);
}

// ==================== Accept (Visitor) Test ====================

TEST_F(XMLNodeTest_62, AcceptWithPrinter_62) {
    const char* xml = "<root><child attr=\"val\"/></root>";
    XMLDocument parsedDoc;
    parsedDoc.Parse(xml);
    ASSERT_EQ(XML_SUCCESS, parsedDoc.ErrorID());
    
    XMLPrinter printer;
    parsedDoc.Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(nullptr, result);
    // The output should contain the root element
    EXPECT_NE(nullptr, strstr(result, "root"));
    EXPECT_NE(nullptr, strstr(result, "child"));
}

// ==================== Document as XMLNode ====================

TEST_F(XMLNodeTest_62, DocumentToDocumentReturnsNonNull_62) {
    EXPECT_NE(nullptr, doc.ToDocument());
}

TEST_F(XMLNodeTest_62, DocumentToElementReturnsNull_62) {
    EXPECT_EQ(nullptr, doc.ToElement());
}

// ==================== ShallowClone Tests ====================

TEST_F(XMLNodeTest_62, ShallowCloneElement_62) {
    XMLElement* root = doc.NewElement("root");
    root->SetAttribute("key", "value");
    doc.InsertFirstChild(root);
    root->InsertEndChild(doc.NewElement("child"));
    
    XMLDocument targetDoc;
    XMLNode* cloned = root->ShallowClone(&targetDoc);
    ASSERT_NE(nullptr, cloned);
    EXPECT_NE(nullptr, cloned->ToElement());
    EXPECT_STREQ("root", cloned->Value());
    // Shallow clone should not clone children
    EXPECT_TRUE(cloned->NoChildren());
    // Clean up: the cloned node should be attached or deleted
    targetDoc.InsertFirstChild(cloned);
}
