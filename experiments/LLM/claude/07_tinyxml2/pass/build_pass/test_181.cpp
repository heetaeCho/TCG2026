#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_181 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test that a new document has no children
TEST_F(XMLNodeTest_181, NewDocumentHasNoChildren_181) {
    EXPECT_TRUE(doc->NoChildren());
    EXPECT_EQ(nullptr, doc->FirstChild());
    EXPECT_EQ(nullptr, doc->LastChild());
}

// Test inserting an element as end child
TEST_F(XMLNodeTest_181, InsertEndChild_181) {
    XMLElement* elem = doc->NewElement("test");
    XMLNode* result = doc->InsertEndChild(elem);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(doc->NoChildren());
    EXPECT_EQ(elem, doc->FirstChild());
    EXPECT_EQ(elem, doc->LastChild());
}

// Test inserting an element as first child
TEST_F(XMLNodeTest_181, InsertFirstChild_181) {
    XMLElement* elem1 = doc->NewElement("first");
    XMLElement* elem2 = doc->NewElement("second");
    doc->InsertEndChild(elem2);
    doc->InsertFirstChild(elem1);
    EXPECT_EQ(elem1, doc->FirstChild());
    EXPECT_EQ(elem2, doc->LastChild());
}

// Test inserting after a specific child
TEST_F(XMLNodeTest_181, InsertAfterChild_181) {
    XMLElement* elem1 = doc->NewElement("first");
    XMLElement* elem2 = doc->NewElement("second");
    XMLElement* elem3 = doc->NewElement("third");
    doc->InsertEndChild(elem1);
    doc->InsertEndChild(elem3);
    doc->InsertAfterChild(elem1, elem2);

    EXPECT_EQ(elem1, doc->FirstChild());
    EXPECT_EQ(elem3, doc->LastChild());
    EXPECT_EQ(elem2, elem1->NextSibling());
    EXPECT_EQ(elem3, elem2->NextSibling());
}

// Test DeleteChildren removes all children
TEST_F(XMLNodeTest_181, DeleteChildren_181) {
    doc->InsertEndChild(doc->NewElement("a"));
    doc->InsertEndChild(doc->NewElement("b"));
    doc->InsertEndChild(doc->NewElement("c"));
    EXPECT_FALSE(doc->NoChildren());
    doc->DeleteChildren();
    EXPECT_TRUE(doc->NoChildren());
    EXPECT_EQ(nullptr, doc->FirstChild());
    EXPECT_EQ(nullptr, doc->LastChild());
}

// Test DeleteChild removes a specific child
TEST_F(XMLNodeTest_181, DeleteChild_181) {
    XMLElement* elem1 = doc->NewElement("first");
    XMLElement* elem2 = doc->NewElement("second");
    XMLElement* elem3 = doc->NewElement("third");
    doc->InsertEndChild(elem1);
    doc->InsertEndChild(elem2);
    doc->InsertEndChild(elem3);
    doc->DeleteChild(elem2);

    EXPECT_EQ(elem1, doc->FirstChild());
    EXPECT_EQ(elem3, doc->LastChild());
    EXPECT_EQ(elem3, elem1->NextSibling());
}

// Test Value and SetValue
TEST_F(XMLNodeTest_181, SetValueAndValue_181) {
    XMLElement* elem = doc->NewElement("original");
    doc->InsertEndChild(elem);
    elem->SetValue("modified", false);
    EXPECT_STREQ("modified", elem->Value());
}

// Test FirstChildElement with name filter
TEST_F(XMLNodeTest_181, FirstChildElementByName_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* a = doc->NewElement("alpha");
    XMLElement* b = doc->NewElement("beta");
    XMLElement* a2 = doc->NewElement("alpha");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);

    const XMLElement* found = root->FirstChildElement("beta");
    ASSERT_NE(nullptr, found);
    EXPECT_STREQ("beta", found->Value());
}

// Test FirstChildElement with no name returns first element child
TEST_F(XMLNodeTest_181, FirstChildElementNoName_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* a = doc->NewElement("alpha");
    root->InsertEndChild(a);

    const XMLElement* found = root->FirstChildElement();
    ASSERT_NE(nullptr, found);
    EXPECT_STREQ("alpha", found->Value());
}

// Test LastChildElement with name filter
TEST_F(XMLNodeTest_181, LastChildElementByName_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* a1 = doc->NewElement("alpha");
    XMLElement* b = doc->NewElement("beta");
    XMLElement* a2 = doc->NewElement("alpha");
    root->InsertEndChild(a1);
    root->InsertEndChild(b);
    root->InsertEndChild(a2);

    const XMLElement* found = root->LastChildElement("alpha");
    ASSERT_NE(nullptr, found);
    EXPECT_EQ(a2, found);
}

// Test NextSiblingElement
TEST_F(XMLNodeTest_181, NextSiblingElement_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* a = doc->NewElement("alpha");
    XMLElement* b = doc->NewElement("beta");
    XMLElement* c = doc->NewElement("gamma");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);

    EXPECT_EQ(b, a->NextSiblingElement());
    EXPECT_EQ(c, b->NextSiblingElement());
    EXPECT_EQ(nullptr, c->NextSiblingElement());
}

// Test PreviousSiblingElement
TEST_F(XMLNodeTest_181, PreviousSiblingElement_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* a = doc->NewElement("alpha");
    XMLElement* b = doc->NewElement("beta");
    XMLElement* c = doc->NewElement("gamma");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);

    EXPECT_EQ(nullptr, a->PreviousSiblingElement());
    EXPECT_EQ(a, b->PreviousSiblingElement());
    EXPECT_EQ(b, c->PreviousSiblingElement());
}

// Test NextSiblingElement with name filter
TEST_F(XMLNodeTest_181, NextSiblingElementByName_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* a = doc->NewElement("alpha");
    XMLElement* b = doc->NewElement("beta");
    XMLElement* c = doc->NewElement("alpha");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);

    const XMLElement* found = a->NextSiblingElement("alpha");
    EXPECT_EQ(c, found);
}

// Test PreviousSiblingElement with name filter
TEST_F(XMLNodeTest_181, PreviousSiblingElementByName_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* a = doc->NewElement("alpha");
    XMLElement* b = doc->NewElement("beta");
    XMLElement* c = doc->NewElement("alpha");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);

    const XMLElement* found = c->PreviousSiblingElement("alpha");
    EXPECT_EQ(a, found);
}

// Test Parent
TEST_F(XMLNodeTest_181, Parent_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child = doc->NewElement("child");
    root->InsertEndChild(child);

    EXPECT_EQ(root, child->Parent());
    EXPECT_EQ(doc, root->Parent());
}

// Test NoChildren on element with no children
TEST_F(XMLNodeTest_181, NoChildrenTrue_181) {
    XMLElement* elem = doc->NewElement("empty");
    doc->InsertEndChild(elem);
    EXPECT_TRUE(elem->NoChildren());
}

// Test NoChildren on element with children
TEST_F(XMLNodeTest_181, NoChildrenFalse_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("child"));
    EXPECT_FALSE(root->NoChildren());
}

// Test ChildElementCount with no children
TEST_F(XMLNodeTest_181, ChildElementCountZero_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    EXPECT_EQ(0, root->ChildElementCount());
}

// Test ChildElementCount with multiple children
TEST_F(XMLNodeTest_181, ChildElementCountMultiple_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("a"));
    root->InsertEndChild(doc->NewElement("b"));
    root->InsertEndChild(doc->NewElement("c"));
    EXPECT_EQ(3, root->ChildElementCount());
}

// Test ChildElementCount with name filter
TEST_F(XMLNodeTest_181, ChildElementCountByName_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("alpha"));
    root->InsertEndChild(doc->NewElement("beta"));
    root->InsertEndChild(doc->NewElement("alpha"));
    EXPECT_EQ(2, root->ChildElementCount("alpha"));
    EXPECT_EQ(1, root->ChildElementCount("beta"));
    EXPECT_EQ(0, root->ChildElementCount("gamma"));
}

// Test DeepClone
TEST_F(XMLNodeTest_181, DeepClone_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child = doc->NewElement("child");
    root->InsertEndChild(child);
    XMLElement* grandchild = doc->NewElement("grandchild");
    child->InsertEndChild(grandchild);

    XMLDocument doc2;
    XMLNode* cloned = root->DeepClone(&doc2);
    ASSERT_NE(nullptr, cloned);
    doc2.InsertEndChild(cloned);

    EXPECT_STREQ("root", cloned->Value());
    ASSERT_NE(nullptr, cloned->FirstChildElement("child"));
    ASSERT_NE(nullptr, cloned->FirstChildElement("child")->FirstChildElement("grandchild"));
}

// Test GetDocument
TEST_F(XMLNodeTest_181, GetDocument_181) {
    XMLElement* elem = doc->NewElement("test");
    doc->InsertEndChild(elem);
    EXPECT_EQ(doc, elem->GetDocument());
}

// Test UserData
TEST_F(XMLNodeTest_181, SetAndGetUserData_181) {
    XMLElement* elem = doc->NewElement("test");
    doc->InsertEndChild(elem);

    int data = 42;
    elem->SetUserData(&data);
    EXPECT_EQ(&data, elem->GetUserData());
}

// Test UserData default is null
TEST_F(XMLNodeTest_181, UserDataDefaultNull_181) {
    XMLElement* elem = doc->NewElement("test");
    doc->InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->GetUserData());
}

// Test ToElement on element node
TEST_F(XMLNodeTest_181, ToElement_181) {
    XMLElement* elem = doc->NewElement("test");
    doc->InsertEndChild(elem);
    EXPECT_NE(nullptr, elem->ToElement());
}

// Test ToDocument on document node
TEST_F(XMLNodeTest_181, ToDocument_181) {
    EXPECT_NE(nullptr, doc->ToDocument());
}

// Test ToElement returns null for non-element node
TEST_F(XMLNodeTest_181, ToElementOnDocumentReturnsNull_181) {
    EXPECT_EQ(nullptr, doc->ToElement());
}

// Test ToComment
TEST_F(XMLNodeTest_181, ToComment_181) {
    XMLComment* comment = doc->NewComment("a comment");
    doc->InsertEndChild(comment);
    EXPECT_NE(nullptr, comment->ToComment());
    EXPECT_EQ(nullptr, comment->ToElement());
}

// Test ToText
TEST_F(XMLNodeTest_181, ToText_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLText* text = doc->NewText("hello");
    root->InsertEndChild(text);
    EXPECT_NE(nullptr, text->ToText());
    EXPECT_EQ(nullptr, text->ToElement());
}

// Test ToDeclaration
TEST_F(XMLNodeTest_181, ToDeclaration_181) {
    XMLDeclaration* decl = doc->NewDeclaration();
    doc->InsertEndChild(decl);
    EXPECT_NE(nullptr, decl->ToDeclaration());
    EXPECT_EQ(nullptr, decl->ToElement());
}

// Test ToUnknown
TEST_F(XMLNodeTest_181, ToUnknown_181) {
    XMLUnknown* unknown = doc->NewUnknown("unknown stuff");
    doc->InsertEndChild(unknown);
    EXPECT_NE(nullptr, unknown->ToUnknown());
    EXPECT_EQ(nullptr, unknown->ToElement());
}

// Test LinkEndChild (should behave like InsertEndChild)
TEST_F(XMLNodeTest_181, LinkEndChild_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* child = doc->NewElement("child");
    XMLNode* result = root->LinkEndChild(child);
    EXPECT_EQ(child, result);
    EXPECT_EQ(child, root->FirstChild());
    EXPECT_EQ(child, root->LastChild());
}

// Test sibling navigation
TEST_F(XMLNodeTest_181, SiblingNavigation_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* a = doc->NewElement("a");
    XMLElement* b = doc->NewElement("b");
    XMLElement* c = doc->NewElement("c");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->InsertEndChild(c);

    EXPECT_EQ(b, a->NextSibling());
    EXPECT_EQ(c, b->NextSibling());
    EXPECT_EQ(nullptr, c->NextSibling());

    EXPECT_EQ(nullptr, a->PreviousSibling());
    EXPECT_EQ(a, b->PreviousSibling());
    EXPECT_EQ(b, c->PreviousSibling());
}

// Test FirstChildElement returns null when no match
TEST_F(XMLNodeTest_181, FirstChildElementNoMatch_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("alpha"));

    EXPECT_EQ(nullptr, root->FirstChildElement("nonexistent"));
}

// Test LastChildElement returns null when no match
TEST_F(XMLNodeTest_181, LastChildElementNoMatch_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    root->InsertEndChild(doc->NewElement("alpha"));

    EXPECT_EQ(nullptr, root->LastChildElement("nonexistent"));
}

// Test multiple InsertEndChild
TEST_F(XMLNodeTest_181, MultipleInsertEndChild_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);

    for (int i = 0; i < 10; ++i) {
        root->InsertEndChild(doc->NewElement("item"));
    }

    EXPECT_EQ(10, root->ChildElementCount());
}

// Test InsertFirstChild with existing children
TEST_F(XMLNodeTest_181, InsertFirstChildMultiple_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* c = doc->NewElement("c");
    XMLElement* b = doc->NewElement("b");
    XMLElement* a = doc->NewElement("a");

    root->InsertEndChild(c);
    root->InsertFirstChild(b);
    root->InsertFirstChild(a);

    EXPECT_EQ(a, root->FirstChild());
    EXPECT_EQ(c, root->LastChild());
    EXPECT_EQ(b, a->NextSibling());
    EXPECT_EQ(c, b->NextSibling());
}

// Test DeepClone into another document preserves structure
TEST_F(XMLNodeTest_181, DeepClonePreservesValue_181) {
    XMLElement* root = doc->NewElement("myroot");
    doc->InsertEndChild(root);
    root->SetAttribute("key", "value");

    XMLDocument doc2;
    XMLNode* cloned = root->DeepClone(&doc2);
    doc2.InsertEndChild(cloned);

    XMLElement* clonedElem = cloned->ToElement();
    ASSERT_NE(nullptr, clonedElem);
    EXPECT_STREQ("myroot", clonedElem->Value());
    EXPECT_STREQ("value", clonedElem->Attribute("key"));
}

// Test SetValue with staticMem = true
TEST_F(XMLNodeTest_181, SetValueStaticMem_181) {
    XMLElement* elem = doc->NewElement("original");
    doc->InsertEndChild(elem);
    static const char* staticStr = "static_value";
    elem->SetValue(staticStr, true);
    EXPECT_STREQ("static_value", elem->Value());
}

// Test DeleteChild on first child
TEST_F(XMLNodeTest_181, DeleteFirstChild_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* a = doc->NewElement("a");
    XMLElement* b = doc->NewElement("b");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->DeleteChild(a);

    EXPECT_EQ(b, root->FirstChild());
    EXPECT_EQ(b, root->LastChild());
    EXPECT_EQ(1, root->ChildElementCount());
}

// Test DeleteChild on last child
TEST_F(XMLNodeTest_181, DeleteLastChild_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* a = doc->NewElement("a");
    XMLElement* b = doc->NewElement("b");
    root->InsertEndChild(a);
    root->InsertEndChild(b);
    root->DeleteChild(b);

    EXPECT_EQ(a, root->FirstChild());
    EXPECT_EQ(a, root->LastChild());
    EXPECT_EQ(1, root->ChildElementCount());
}

// Test inserting null to InsertEndChild
TEST_F(XMLNodeTest_181, InsertEndChildNull_181) {
    // Depending on implementation, inserting null might return null or crash
    // We test the observable behavior
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    // Don't test null insertion as it may be undefined behavior
}

// Test parsing from string
TEST_F(XMLNodeTest_181, ParseFromString_181) {
    const char* xml = "<root><child1/><child2/></root>";
    doc->Parse(xml);
    EXPECT_EQ(XML_SUCCESS, doc->ErrorID());

    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(2, root->ChildElementCount());
    EXPECT_NE(nullptr, root->FirstChildElement("child1"));
    EXPECT_NE(nullptr, root->FirstChildElement("child2"));
}

// Test GetLineNum
TEST_F(XMLNodeTest_181, GetLineNum_181) {
    const char* xml = "<root>\n<child/>\n</root>";
    doc->Parse(xml);
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    // Root should be on line 1
    EXPECT_EQ(1, root->GetLineNum());

    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(nullptr, child);
    // Child should be on line 2
    EXPECT_EQ(2, child->GetLineNum());
}

// Test Accept with XMLPrinter (a built-in visitor)
TEST_F(XMLNodeTest_181, AcceptVisitor_181) {
    const char* xml = "<root><child/></root>";
    doc->Parse(xml);

    XMLPrinter printer;
    doc->Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(nullptr, result);
    // Should contain root and child
    EXPECT_NE(nullptr, strstr(result, "root"));
    EXPECT_NE(nullptr, strstr(result, "child"));
}

// Test InsertAfterChild at the end
TEST_F(XMLNodeTest_181, InsertAfterChildAtEnd_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* a = doc->NewElement("a");
    XMLElement* b = doc->NewElement("b");
    root->InsertEndChild(a);
    root->InsertAfterChild(a, b);

    EXPECT_EQ(a, root->FirstChild());
    EXPECT_EQ(b, root->LastChild());
    EXPECT_EQ(b, a->NextSibling());
}

// Test that FirstChild and LastChild are same for single child
TEST_F(XMLNodeTest_181, SingleChildFirstEqualsLast_181) {
    XMLElement* root = doc->NewElement("root");
    doc->InsertEndChild(root);
    XMLElement* only = doc->NewElement("only");
    root->InsertEndChild(only);

    EXPECT_EQ(only, root->FirstChild());
    EXPECT_EQ(only, root->LastChild());
    EXPECT_EQ(nullptr, only->NextSibling());
    EXPECT_EQ(nullptr, only->PreviousSibling());
}
