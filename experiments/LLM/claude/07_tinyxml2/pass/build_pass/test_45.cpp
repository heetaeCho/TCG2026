#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_45 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// --- ToComment Tests ---

TEST_F(XMLNodeTest_45, ToCommentReturnsNullForElement_45) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->ToComment());
}

TEST_F(XMLNodeTest_45, ToCommentReturnsNonNullForComment_45) {
    XMLComment* comment = doc.NewComment("This is a comment");
    doc.InsertEndChild(comment);
    EXPECT_NE(nullptr, comment->ToComment());
    EXPECT_EQ(comment, comment->ToComment());
}

TEST_F(XMLNodeTest_45, ToCommentReturnsNullForText_45) {
    XMLElement* elem = doc.NewElement("root");
    doc.InsertEndChild(elem);
    XMLText* text = doc.NewText("hello");
    elem->InsertEndChild(text);
    EXPECT_EQ(nullptr, text->ToComment());
}

TEST_F(XMLNodeTest_45, ToCommentReturnsNullForDeclaration_45) {
    XMLDeclaration* decl = doc.NewDeclaration();
    doc.InsertEndChild(decl);
    EXPECT_EQ(nullptr, decl->ToComment());
}

TEST_F(XMLNodeTest_45, ToCommentReturnsNullForUnknown_45) {
    XMLUnknown* unknown = doc.NewUnknown("something");
    doc.InsertEndChild(unknown);
    EXPECT_EQ(nullptr, unknown->ToComment());
}

TEST_F(XMLNodeTest_45, ToCommentReturnsNullForDocument_45) {
    XMLNode* docNode = &doc;
    EXPECT_EQ(nullptr, docNode->ToComment());
}

// --- Value and SetValue Tests ---

TEST_F(XMLNodeTest_45, ElementValueMatchesTagName_45) {
    XMLElement* elem = doc.NewElement("myElement");
    doc.InsertEndChild(elem);
    EXPECT_STREQ("myElement", elem->Value());
}

TEST_F(XMLNodeTest_45, CommentValueMatchesText_45) {
    XMLComment* comment = doc.NewComment("my comment text");
    doc.InsertEndChild(comment);
    EXPECT_STREQ("my comment text", comment->Value());
}

TEST_F(XMLNodeTest_45, SetValueChangesValue_45) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertEndChild(elem);
    elem->SetValue("changed", false);
    EXPECT_STREQ("changed", elem->Value());
}

// --- NoChildren Tests ---

TEST_F(XMLNodeTest_45, NoChildrenReturnsTrueWhenEmpty_45) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_TRUE(elem->NoChildren());
}

TEST_F(XMLNodeTest_45, NoChildrenReturnsFalseWhenHasChild_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    EXPECT_FALSE(parent->NoChildren());
}

// --- InsertEndChild Tests ---

TEST_F(XMLNodeTest_45, InsertEndChildAddsChild_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = parent->InsertEndChild(child);
    EXPECT_EQ(child, result);
    EXPECT_FALSE(parent->NoChildren());
    EXPECT_EQ(child, parent->FirstChild());
    EXPECT_EQ(child, parent->LastChild());
}

TEST_F(XMLNodeTest_45, InsertEndChildMultipleChildren_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    EXPECT_EQ(child1, parent->FirstChild());
    EXPECT_EQ(child2, parent->LastChild());
}

// --- InsertFirstChild Tests ---

TEST_F(XMLNodeTest_45, InsertFirstChildAddsAtBeginning_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertFirstChild(child2);
    EXPECT_EQ(child2, parent->FirstChild());
    EXPECT_EQ(child1, parent->LastChild());
}

// --- InsertAfterChild Tests ---

TEST_F(XMLNodeTest_45, InsertAfterChildInsertsCorrectly_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child3 = doc.NewElement("child3");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child3);
    parent->InsertAfterChild(child1, child2);

    EXPECT_EQ(child1, parent->FirstChild());
    EXPECT_EQ(child2, child1->NextSibling());
    EXPECT_EQ(child3, child2->NextSibling());
}

// --- DeleteChildren Tests ---

TEST_F(XMLNodeTest_45, DeleteChildrenRemovesAll_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("c1"));
    parent->InsertEndChild(doc.NewElement("c2"));
    parent->InsertEndChild(doc.NewElement("c3"));
    EXPECT_FALSE(parent->NoChildren());
    parent->DeleteChildren();
    EXPECT_TRUE(parent->NoChildren());
}

// --- DeleteChild Tests ---

TEST_F(XMLNodeTest_45, DeleteChildRemovesSpecificChild_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->DeleteChild(child1);
    EXPECT_EQ(child2, parent->FirstChild());
    EXPECT_EQ(child2, parent->LastChild());
}

// --- FirstChild / LastChild Tests ---

TEST_F(XMLNodeTest_45, FirstChildAndLastChildNullWhenEmpty_45) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->FirstChild());
    EXPECT_EQ(nullptr, elem->LastChild());
}

// --- FirstChildElement / LastChildElement Tests ---

TEST_F(XMLNodeTest_45, FirstChildElementByName_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("alpha"));
    parent->InsertEndChild(doc.NewElement("beta"));
    parent->InsertEndChild(doc.NewElement("gamma"));

    XMLElement* found = parent->FirstChildElement("beta");
    ASSERT_NE(nullptr, found);
    EXPECT_STREQ("beta", found->Value());
}

TEST_F(XMLNodeTest_45, FirstChildElementReturnsNullIfNotFound_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("alpha"));
    EXPECT_EQ(nullptr, parent->FirstChildElement("nonexistent"));
}

TEST_F(XMLNodeTest_45, LastChildElementByName_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* a1 = doc.NewElement("alpha");
    XMLElement* a2 = doc.NewElement("alpha");
    parent->InsertEndChild(a1);
    parent->InsertEndChild(doc.NewElement("beta"));
    parent->InsertEndChild(a2);

    XMLElement* found = parent->LastChildElement("alpha");
    ASSERT_NE(nullptr, found);
    EXPECT_EQ(a2, found);
}

// --- Sibling Navigation Tests ---

TEST_F(XMLNodeTest_45, NextSiblingNavigation_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    parent->InsertEndChild(c1);
    parent->InsertEndChild(c2);
    EXPECT_EQ(c2, c1->NextSibling());
    EXPECT_EQ(nullptr, c2->NextSibling());
}

TEST_F(XMLNodeTest_45, PreviousSiblingNavigation_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    parent->InsertEndChild(c1);
    parent->InsertEndChild(c2);
    EXPECT_EQ(c1, c2->PreviousSibling());
    EXPECT_EQ(nullptr, c1->PreviousSibling());
}

TEST_F(XMLNodeTest_45, NextSiblingElementByName_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* c1 = doc.NewElement("alpha");
    XMLElement* c2 = doc.NewElement("beta");
    XMLElement* c3 = doc.NewElement("alpha");
    parent->InsertEndChild(c1);
    parent->InsertEndChild(c2);
    parent->InsertEndChild(c3);

    XMLElement* found = c1->NextSiblingElement("alpha");
    EXPECT_EQ(c3, found);
}

TEST_F(XMLNodeTest_45, PreviousSiblingElementByName_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* c1 = doc.NewElement("alpha");
    XMLElement* c2 = doc.NewElement("beta");
    XMLElement* c3 = doc.NewElement("alpha");
    parent->InsertEndChild(c1);
    parent->InsertEndChild(c2);
    parent->InsertEndChild(c3);

    XMLElement* found = c3->PreviousSiblingElement("alpha");
    EXPECT_EQ(c1, found);
}

// --- Parent Tests ---

TEST_F(XMLNodeTest_45, ParentReturnsCorrectParent_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    EXPECT_EQ(parent, child->Parent());
}

TEST_F(XMLNodeTest_45, ParentOfRootIsDocument_45) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    EXPECT_EQ(&doc, root->Parent());
}

// --- GetDocument Tests ---

TEST_F(XMLNodeTest_45, GetDocumentReturnsOwningDocument_45) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(&doc, elem->GetDocument());
}

// --- ChildElementCount Tests ---

TEST_F(XMLNodeTest_45, ChildElementCountReturnsZeroWhenEmpty_45) {
    XMLElement* elem = doc.NewElement("parent");
    doc.InsertEndChild(elem);
    EXPECT_EQ(0, elem->ChildElementCount());
}

TEST_F(XMLNodeTest_45, ChildElementCountReturnsCorrectCount_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("c1"));
    parent->InsertEndChild(doc.NewElement("c2"));
    parent->InsertEndChild(doc.NewElement("c3"));
    EXPECT_EQ(3, parent->ChildElementCount());
}

TEST_F(XMLNodeTest_45, ChildElementCountByName_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("alpha"));
    parent->InsertEndChild(doc.NewElement("beta"));
    parent->InsertEndChild(doc.NewElement("alpha"));
    EXPECT_EQ(2, parent->ChildElementCount("alpha"));
    EXPECT_EQ(1, parent->ChildElementCount("beta"));
    EXPECT_EQ(0, parent->ChildElementCount("gamma"));
}

// --- DeepClone Tests ---

TEST_F(XMLNodeTest_45, DeepCloneClonesTree_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    XMLElement* grandchild = doc.NewElement("grandchild");
    child->InsertEndChild(grandchild);

    XMLDocument targetDoc;
    const XMLNode* clone = parent->DeepClone(&targetDoc);
    ASSERT_NE(nullptr, clone);
    targetDoc.InsertEndChild(const_cast<XMLNode*>(clone));

    EXPECT_STREQ("parent", clone->Value());
    ASSERT_NE(nullptr, clone->FirstChild());
    EXPECT_STREQ("child", clone->FirstChild()->Value());
    ASSERT_NE(nullptr, clone->FirstChild()->FirstChild());
    EXPECT_STREQ("grandchild", clone->FirstChild()->FirstChild()->Value());
}

// --- UserData Tests ---

TEST_F(XMLNodeTest_45, SetAndGetUserData_45) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    int myData = 42;
    elem->SetUserData(&myData);
    EXPECT_EQ(&myData, elem->GetUserData());
}

TEST_F(XMLNodeTest_45, GetUserDataDefaultIsNull_45) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->GetUserData());
}

// --- ToElement Tests ---

TEST_F(XMLNodeTest_45, ToElementReturnsNonNullForElement_45) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_NE(nullptr, elem->ToElement());
    EXPECT_EQ(elem, elem->ToElement());
}

TEST_F(XMLNodeTest_45, ToElementReturnsNullForComment_45) {
    XMLComment* comment = doc.NewComment("test");
    doc.InsertEndChild(comment);
    EXPECT_EQ(nullptr, comment->ToElement());
}

// --- ToText Tests ---

TEST_F(XMLNodeTest_45, ToTextReturnsNonNullForText_45) {
    XMLElement* elem = doc.NewElement("root");
    doc.InsertEndChild(elem);
    XMLText* text = doc.NewText("hello");
    elem->InsertEndChild(text);
    EXPECT_NE(nullptr, text->ToText());
}

TEST_F(XMLNodeTest_45, ToTextReturnsNullForElement_45) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->ToText());
}

// --- ToDocument Tests ---

TEST_F(XMLNodeTest_45, ToDocumentReturnsNonNullForDocument_45) {
    XMLNode* docNode = &doc;
    EXPECT_NE(nullptr, docNode->ToDocument());
}

TEST_F(XMLNodeTest_45, ToDocumentReturnsNullForElement_45) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->ToDocument());
}

// --- ToDeclaration Tests ---

TEST_F(XMLNodeTest_45, ToDeclarationReturnsNonNullForDeclaration_45) {
    XMLDeclaration* decl = doc.NewDeclaration();
    doc.InsertEndChild(decl);
    EXPECT_NE(nullptr, decl->ToDeclaration());
}

TEST_F(XMLNodeTest_45, ToDeclarationReturnsNullForElement_45) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->ToDeclaration());
}

// --- ToUnknown Tests ---

TEST_F(XMLNodeTest_45, ToUnknownReturnsNonNullForUnknown_45) {
    XMLUnknown* unknown = doc.NewUnknown("something");
    doc.InsertEndChild(unknown);
    EXPECT_NE(nullptr, unknown->ToUnknown());
}

TEST_F(XMLNodeTest_45, ToUnknownReturnsNullForElement_45) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->ToUnknown());
}

// --- GetLineNum Tests ---

TEST_F(XMLNodeTest_45, GetLineNumForProgrammaticallyCreatedNode_45) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    // Programmatically created nodes typically have line num 0
    EXPECT_EQ(0, elem->GetLineNum());
}

TEST_F(XMLNodeTest_45, GetLineNumAfterParsing_45) {
    const char* xml = "<root>\n  <child/>\n</root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(1, root->GetLineNum());
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    EXPECT_EQ(2, child->GetLineNum());
}

// --- LinkEndChild Tests (alias for InsertEndChild) ---

TEST_F(XMLNodeTest_45, LinkEndChildWorks_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = parent->LinkEndChild(child);
    EXPECT_EQ(child, result);
    EXPECT_EQ(child, parent->LastChild());
}

// --- Boundary: Inserting null child ---

TEST_F(XMLNodeTest_45, InsertEndChildWithNullReturnsNull_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    // Passing null should be handled gracefully
    XMLNode* result = parent->InsertEndChild(nullptr);
    EXPECT_EQ(nullptr, result);
}

TEST_F(XMLNodeTest_45, InsertFirstChildWithNullReturnsNull_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLNode* result = parent->InsertFirstChild(nullptr);
    EXPECT_EQ(nullptr, result);
}

// --- ShallowEqual Tests ---

TEST_F(XMLNodeTest_45, ShallowEqualSameComment_45) {
    XMLComment* c1 = doc.NewComment("hello");
    XMLComment* c2 = doc.NewComment("hello");
    EXPECT_TRUE(c1->ShallowEqual(c2));
}

TEST_F(XMLNodeTest_45, ShallowEqualDifferentComment_45) {
    XMLComment* c1 = doc.NewComment("hello");
    XMLComment* c2 = doc.NewComment("world");
    EXPECT_FALSE(c1->ShallowEqual(c2));
}

// --- Parsing from XML string ---

TEST_F(XMLNodeTest_45, ParsedDocumentStructure_45) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("root", root->Value());
    EXPECT_EQ(3, root->ChildElementCount());
}

// --- Mixed content: comments, elements, text ---

TEST_F(XMLNodeTest_45, ChildElementCountIgnoresNonElements_45) {
    const char* xml = "<root>text<!-- comment --><child/></root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    // ChildElementCount should count only elements
    EXPECT_EQ(1, root->ChildElementCount());
    // But FirstChild should be the text node
    ASSERT_NE(nullptr, root->FirstChild());
    EXPECT_NE(nullptr, root->FirstChild()->ToText());
}

// --- Accept with XMLVisitor ---

TEST_F(XMLNodeTest_45, AcceptVisitorOnComment_45) {
    XMLComment* comment = doc.NewComment("test comment");
    doc.InsertEndChild(comment);
    XMLPrinter printer;
    bool result = comment->Accept(&printer);
    EXPECT_TRUE(result);
    // The printer should have produced some output containing the comment
    const char* output = printer.CStr();
    ASSERT_NE(nullptr, output);
    EXPECT_NE(nullptr, strstr(output, "test comment"));
}

// --- DeepClone to different document ---

TEST_F(XMLNodeTest_45, DeepCloneToSameDocument_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("child"));

    const XMLNode* clone = parent->DeepClone(&doc);
    ASSERT_NE(nullptr, clone);
    EXPECT_STREQ("parent", clone->Value());
    EXPECT_NE(parent, clone); // should be a different node
}

// --- SetValue with static memory flag ---

TEST_F(XMLNodeTest_45, SetValueStaticMem_45) {
    XMLElement* elem = doc.NewElement("original");
    doc.InsertEndChild(elem);
    static const char staticStr[] = "static_value";
    elem->SetValue(staticStr, true);
    EXPECT_STREQ("static_value", elem->Value());
}

// --- FirstChildElement with null name returns first element ---

TEST_F(XMLNodeTest_45, FirstChildElementNullNameReturnsFirst_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* c1 = doc.NewElement("alpha");
    XMLElement* c2 = doc.NewElement("beta");
    parent->InsertEndChild(c1);
    parent->InsertEndChild(c2);
    EXPECT_EQ(c1, parent->FirstChildElement());
    EXPECT_EQ(c1, parent->FirstChildElement(nullptr));
}

TEST_F(XMLNodeTest_45, LastChildElementNullNameReturnsLast_45) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* c1 = doc.NewElement("alpha");
    XMLElement* c2 = doc.NewElement("beta");
    parent->InsertEndChild(c1);
    parent->InsertEndChild(c2);
    EXPECT_EQ(c2, parent->LastChildElement());
    EXPECT_EQ(c2, parent->LastChildElement(nullptr));
}
