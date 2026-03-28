#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeTest_185 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test SetValue with staticMem = false (dynamic string)
TEST_F(XMLNodeTest_185, SetValueDynamic_185) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetValue("NewValue", false);
    EXPECT_STREQ("NewValue", elem->Value());
}

// Test SetValue with staticMem = true (interned string)
TEST_F(XMLNodeTest_185, SetValueStatic_185) {
    XMLElement* elem = doc.NewElement("test");
    const char* staticStr = "StaticValue";
    elem->SetValue(staticStr, true);
    EXPECT_STREQ("StaticValue", elem->Value());
}

// Test SetValue with empty string, staticMem = false
TEST_F(XMLNodeTest_185, SetValueEmptyStringDynamic_185) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetValue("", false);
    EXPECT_STREQ("", elem->Value());
}

// Test SetValue with empty string, staticMem = true
TEST_F(XMLNodeTest_185, SetValueEmptyStringStatic_185) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetValue("", true);
    EXPECT_STREQ("", elem->Value());
}

// Test SetValue overwriting previous value (dynamic)
TEST_F(XMLNodeTest_185, SetValueOverwriteDynamic_185) {
    XMLElement* elem = doc.NewElement("original");
    EXPECT_STREQ("original", elem->Value());
    elem->SetValue("updated", false);
    EXPECT_STREQ("updated", elem->Value());
}

// Test SetValue overwriting previous value (static)
TEST_F(XMLNodeTest_185, SetValueOverwriteStatic_185) {
    XMLElement* elem = doc.NewElement("original");
    EXPECT_STREQ("original", elem->Value());
    elem->SetValue("updated_static", true);
    EXPECT_STREQ("updated_static", elem->Value());
}

// Test SetValue multiple times alternating between static and dynamic
TEST_F(XMLNodeTest_185, SetValueAlternateStaticDynamic_185) {
    XMLElement* elem = doc.NewElement("start");
    
    elem->SetValue("dynamic1", false);
    EXPECT_STREQ("dynamic1", elem->Value());
    
    elem->SetValue("static1", true);
    EXPECT_STREQ("static1", elem->Value());
    
    elem->SetValue("dynamic2", false);
    EXPECT_STREQ("dynamic2", elem->Value());
}

// Test SetValue with a long string
TEST_F(XMLNodeTest_185, SetValueLongString_185) {
    XMLElement* elem = doc.NewElement("test");
    std::string longStr(1000, 'A');
    elem->SetValue(longStr.c_str(), false);
    EXPECT_STREQ(longStr.c_str(), elem->Value());
}

// Test SetValue with special characters
TEST_F(XMLNodeTest_185, SetValueSpecialCharacters_185) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetValue("value<with>&\"special'chars", false);
    EXPECT_STREQ("value<with>&\"special'chars", elem->Value());
}

// Test Value() returns correct initial value from NewElement
TEST_F(XMLNodeTest_185, ValueReturnsInitialElementName_185) {
    XMLElement* elem = doc.NewElement("MyElement");
    EXPECT_STREQ("MyElement", elem->Value());
}

// Test NoChildren on a fresh element
TEST_F(XMLNodeTest_185, NoChildrenOnFreshElement_185) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_TRUE(elem->NoChildren());
}

// Test InsertEndChild and verify child exists
TEST_F(XMLNodeTest_185, InsertEndChildAddsChild_185) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("child");
    XMLNode* result = parent->InsertEndChild(child);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(parent->NoChildren());
    EXPECT_STREQ("child", parent->FirstChild()->Value());
}

// Test InsertFirstChild
TEST_F(XMLNodeTest_185, InsertFirstChildAddsChild_185) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertFirstChild(child2);
    EXPECT_STREQ("child2", parent->FirstChild()->Value());
    EXPECT_STREQ("child1", parent->LastChild()->Value());
}

// Test InsertAfterChild
TEST_F(XMLNodeTest_185, InsertAfterChildInsertsCorrectly_185) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    XMLElement* child3 = doc.NewElement("child3");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child3);
    parent->InsertAfterChild(child1, child2);
    
    const XMLNode* first = parent->FirstChild();
    EXPECT_STREQ("child1", first->Value());
    const XMLNode* second = first->NextSibling();
    EXPECT_STREQ("child2", second->Value());
    const XMLNode* third = second->NextSibling();
    EXPECT_STREQ("child3", third->Value());
}

// Test DeleteChildren
TEST_F(XMLNodeTest_185, DeleteChildrenRemovesAll_185) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("c1"));
    parent->InsertEndChild(doc.NewElement("c2"));
    parent->InsertEndChild(doc.NewElement("c3"));
    EXPECT_FALSE(parent->NoChildren());
    parent->DeleteChildren();
    EXPECT_TRUE(parent->NoChildren());
}

// Test DeleteChild removes specific child
TEST_F(XMLNodeTest_185, DeleteChildRemovesSpecificChild_185) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child1 = doc.NewElement("child1");
    XMLElement* child2 = doc.NewElement("child2");
    parent->InsertEndChild(child1);
    parent->InsertEndChild(child2);
    parent->DeleteChild(child1);
    EXPECT_STREQ("child2", parent->FirstChild()->Value());
    EXPECT_EQ(parent->FirstChild(), parent->LastChild());
}

// Test ChildElementCount
TEST_F(XMLNodeTest_185, ChildElementCountReturnsCorrectCount_185) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("a"));
    parent->InsertEndChild(doc.NewElement("b"));
    parent->InsertEndChild(doc.NewElement("c"));
    EXPECT_EQ(3, parent->ChildElementCount());
}

// Test ChildElementCount with name filter
TEST_F(XMLNodeTest_185, ChildElementCountWithNameFilter_185) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("item"));
    parent->InsertEndChild(doc.NewElement("other"));
    parent->InsertEndChild(doc.NewElement("item"));
    EXPECT_EQ(2, parent->ChildElementCount("item"));
    EXPECT_EQ(1, parent->ChildElementCount("other"));
    EXPECT_EQ(0, parent->ChildElementCount("nonexistent"));
}

// Test Parent returns null for root-level element
TEST_F(XMLNodeTest_185, ParentOfDocChildIsDocument_185) {
    XMLElement* elem = doc.NewElement("root");
    doc.InsertEndChild(elem);
    EXPECT_EQ(&doc, elem->Parent());
}

// Test FirstChildElement and LastChildElement
TEST_F(XMLNodeTest_185, FirstAndLastChildElement_185) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("first"));
    parent->InsertEndChild(doc.NewElement("middle"));
    parent->InsertEndChild(doc.NewElement("last"));
    
    EXPECT_STREQ("first", parent->FirstChildElement()->Value());
    EXPECT_STREQ("last", parent->LastChildElement()->Value());
}

// Test FirstChildElement with name
TEST_F(XMLNodeTest_185, FirstChildElementWithName_185) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    parent->InsertEndChild(doc.NewElement("alpha"));
    parent->InsertEndChild(doc.NewElement("beta"));
    parent->InsertEndChild(doc.NewElement("alpha"));
    
    const XMLElement* found = parent->FirstChildElement("beta");
    EXPECT_NE(nullptr, found);
    EXPECT_STREQ("beta", found->Value());
}

// Test NextSiblingElement and PreviousSiblingElement
TEST_F(XMLNodeTest_185, SiblingNavigation_185) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* c1 = doc.NewElement("c1");
    XMLElement* c2 = doc.NewElement("c2");
    XMLElement* c3 = doc.NewElement("c3");
    parent->InsertEndChild(c1);
    parent->InsertEndChild(c2);
    parent->InsertEndChild(c3);
    
    EXPECT_EQ(c2, c1->NextSiblingElement());
    EXPECT_EQ(c3, c2->NextSiblingElement());
    EXPECT_EQ(nullptr, c3->NextSiblingElement());
    
    EXPECT_EQ(c2, c3->PreviousSiblingElement());
    EXPECT_EQ(c1, c2->PreviousSiblingElement());
    EXPECT_EQ(nullptr, c1->PreviousSiblingElement());
}

// Test DeepClone
TEST_F(XMLNodeTest_185, DeepCloneCreatesIndependentCopy_185) {
    XMLDocument srcDoc;
    srcDoc.Parse("<root><child attr=\"val\">text</child></root>");
    
    XMLDocument destDoc;
    const XMLNode* cloned = srcDoc.RootElement()->DeepClone(&destDoc);
    destDoc.InsertEndChild(const_cast<XMLNode*>(cloned));
    
    EXPECT_STREQ("root", destDoc.RootElement()->Value());
    EXPECT_STREQ("child", destDoc.RootElement()->FirstChildElement()->Value());
}

// Test GetLineNum returns a non-negative value
TEST_F(XMLNodeTest_185, GetLineNumNonNegative_185) {
    doc.Parse("<root>\n<child/>\n</root>");
    EXPECT_GE(doc.RootElement()->GetLineNum(), 1);
}

// Test UserData set and get
TEST_F(XMLNodeTest_185, UserDataSetAndGet_185) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    int myData = 42;
    elem->SetUserData(&myData);
    EXPECT_EQ(&myData, elem->GetUserData());
}

// Test UserData is initially null
TEST_F(XMLNodeTest_185, UserDataInitiallyNull_185) {
    XMLElement* elem = doc.NewElement("test");
    EXPECT_EQ(nullptr, elem->GetUserData());
}

// Test SetValue on a text node
TEST_F(XMLNodeTest_185, SetValueOnTextNode_185) {
    doc.Parse("<root>original text</root>");
    XMLNode* textNode = doc.RootElement()->FirstChild();
    ASSERT_NE(nullptr, textNode);
    ASSERT_NE(nullptr, textNode->ToText());
    
    textNode->SetValue("new text", false);
    EXPECT_STREQ("new text", textNode->Value());
}

// Test SetValue on a comment node
TEST_F(XMLNodeTest_185, SetValueOnCommentNode_185) {
    doc.Parse("<root><!-- a comment --></root>");
    XMLNode* commentNode = doc.RootElement()->FirstChild();
    ASSERT_NE(nullptr, commentNode);
    ASSERT_NE(nullptr, commentNode->ToComment());
    
    commentNode->SetValue("new comment", false);
    EXPECT_STREQ("new comment", commentNode->Value());
}

// Test that FirstChild returns null on empty node
TEST_F(XMLNodeTest_185, FirstChildNullOnEmpty_185) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->FirstChild());
}

// Test that LastChild returns null on empty node
TEST_F(XMLNodeTest_185, LastChildNullOnEmpty_185) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(nullptr, elem->LastChild());
}

// Test ChildElementCount on empty element
TEST_F(XMLNodeTest_185, ChildElementCountZeroOnEmpty_185) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    EXPECT_EQ(0, elem->ChildElementCount());
}

// Test multiple SetValue calls preserve only the latest
TEST_F(XMLNodeTest_185, MultipleSetValueKeepsLatest_185) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetValue("first", false);
    elem->SetValue("second", true);
    elem->SetValue("third", false);
    
    EXPECT_STREQ("third", elem->Value());
}

// Test SetValue with single character
TEST_F(XMLNodeTest_185, SetValueSingleChar_185) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetValue("X", false);
    EXPECT_STREQ("X", elem->Value());
}

// Test SetValue with single character static
TEST_F(XMLNodeTest_185, SetValueSingleCharStatic_185) {
    XMLElement* elem = doc.NewElement("test");
    elem->SetValue("Y", true);
    EXPECT_STREQ("Y", elem->Value());
}

// Test LinkEndChild (alias for InsertEndChild)
TEST_F(XMLNodeTest_185, LinkEndChildWorks_185) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    XMLElement* child = doc.NewElement("linked");
    XMLNode* result = parent->LinkEndChild(child);
    EXPECT_NE(nullptr, result);
    EXPECT_STREQ("linked", parent->FirstChild()->Value());
}

// Test NextSiblingElement with name filter
TEST_F(XMLNodeTest_185, NextSiblingElementWithName_185) {
    doc.Parse("<root><a/><b/><a/><c/></root>");
    XMLElement* root = doc.RootElement();
    XMLElement* first = root->FirstChildElement("a");
    ASSERT_NE(nullptr, first);
    XMLElement* nextA = first->NextSiblingElement("a");
    ASSERT_NE(nullptr, nextA);
    EXPECT_STREQ("a", nextA->Value());
    // Make sure it's actually the second 'a', not the first
    EXPECT_NE(first, nextA);
}

// Test GetDocument returns the owning document
TEST_F(XMLNodeTest_185, GetDocumentReturnsOwner_185) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    EXPECT_EQ(&doc, elem->GetDocument());
}
