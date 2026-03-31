#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeValueTest_184 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test that Value() on a document node returns null
TEST_F(XMLNodeValueTest_184, DocumentValueReturnsNull_184) {
    const char* val = doc->Value();
    EXPECT_EQ(val, nullptr);
}

// Test that Value() on an element node returns the element name
TEST_F(XMLNodeValueTest_184, ElementValueReturnsTagName_184) {
    doc->Parse("<root/>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Value(), "root");
}

// Test that Value() returns the correct value after SetValue
TEST_F(XMLNodeValueTest_184, SetValueThenGetValue_184) {
    doc->Parse("<root/>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetValue("newname", false);
    EXPECT_STREQ(root->Value(), "newname");
}

// Test that Value() on a text node returns the text content
TEST_F(XMLNodeValueTest_184, TextNodeValueReturnsText_184) {
    doc->Parse("<root>Hello World</root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);
    EXPECT_STREQ(textNode->Value(), "Hello World");
}

// Test that Value() on a comment node returns the comment content
TEST_F(XMLNodeValueTest_184, CommentNodeValueReturnsComment_184) {
    doc->Parse("<!-- This is a comment --><root/>");
    const XMLNode* child = doc->FirstChild();
    ASSERT_NE(child, nullptr);
    ASSERT_NE(child->ToComment(), nullptr);
    EXPECT_STREQ(child->Value(), " This is a comment ");
}

// Test that Value() on a declaration node returns the declaration content
TEST_F(XMLNodeValueTest_184, DeclarationNodeValue_184) {
    doc->Parse("<?xml version=\"1.0\"?><root/>");
    const XMLNode* child = doc->FirstChild();
    ASSERT_NE(child, nullptr);
    ASSERT_NE(child->ToDeclaration(), nullptr);
    const char* val = child->Value();
    ASSERT_NE(val, nullptr);
    // Declaration value should contain version info
    EXPECT_NE(std::string(val).find("xml"), std::string::npos);
}

// Test that Value() with SetValue using staticMem=true works
TEST_F(XMLNodeValueTest_184, SetValueStaticMem_184) {
    doc->Parse("<root/>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetValue("staticname", true);
    EXPECT_STREQ(root->Value(), "staticname");
}

// Test that Value() on a nested element returns correct name
TEST_F(XMLNodeValueTest_184, NestedElementValue_184) {
    doc->Parse("<root><child><grandchild/></child></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Value(), "child");
    const XMLElement* grandchild = child->FirstChildElement("grandchild");
    ASSERT_NE(grandchild, nullptr);
    EXPECT_STREQ(grandchild->Value(), "grandchild");
}

// Test that Value() with empty element name
TEST_F(XMLNodeValueTest_184, EmptyTextValue_184) {
    doc->Parse("<root></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Value(), "root");
    // No children because no text content
    EXPECT_TRUE(root->NoChildren());
}

// Test Value() after modifying value multiple times
TEST_F(XMLNodeValueTest_184, MultipleSetValue_184) {
    doc->Parse("<root/>");
    XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetValue("first", false);
    EXPECT_STREQ(root->Value(), "first");
    root->SetValue("second", false);
    EXPECT_STREQ(root->Value(), "second");
    root->SetValue("third", false);
    EXPECT_STREQ(root->Value(), "third");
}

// Test that Value() on an XMLUnknown node returns content
TEST_F(XMLNodeValueTest_184, UnknownNodeValue_184) {
    doc->Parse("<!DOCTYPE html><root/>");
    const XMLNode* child = doc->FirstChild();
    ASSERT_NE(child, nullptr);
    const char* val = child->Value();
    ASSERT_NE(val, nullptr);
}

// Test Value() with special characters in element name
TEST_F(XMLNodeValueTest_184, SpecialCharactersInValue_184) {
    doc->Parse("<root>Text with &amp; special &lt;chars&gt;</root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);
    // The text should have decoded entities
    EXPECT_STREQ(textNode->Value(), "Text with & special <chars>");
}

// Test Value() on a CDATA section
TEST_F(XMLNodeValueTest_184, CDATAValue_184) {
    doc->Parse("<root><![CDATA[Some CDATA content]]></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Value(), "Some CDATA content");
}

// Test that document created fresh has null Value
TEST_F(XMLNodeValueTest_184, FreshDocumentValueIsNull_184) {
    XMLDocument freshDoc;
    EXPECT_EQ(freshDoc.Value(), nullptr);
}

// Test Value() after deep clone preserves value
TEST_F(XMLNodeValueTest_184, DeepClonePreservesValue_184) {
    doc->Parse("<root><child>text</child></root>");
    const XMLElement* root = doc->FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    XMLDocument targetDoc;
    XMLNode* cloned = root->DeepClone(&targetDoc);
    ASSERT_NE(cloned, nullptr);
    EXPECT_STREQ(cloned->Value(), "root");

    const XMLElement* clonedChild = cloned->FirstChildElement("child");
    ASSERT_NE(clonedChild, nullptr);
    EXPECT_STREQ(clonedChild->Value(), "child");

    targetDoc.DeleteNode(cloned);
}
