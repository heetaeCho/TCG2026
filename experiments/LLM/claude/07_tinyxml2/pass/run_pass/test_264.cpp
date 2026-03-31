#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementParseDeepTest_264 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test parsing a simple self-closing element
TEST_F(XMLElementParseDeepTest_264, ParseSimpleSelfClosingElement_264) {
    const char* xml = "<element/>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "element");
}

// Test parsing an element with open and close tags
TEST_F(XMLElementParseDeepTest_264, ParseOpenCloseElement_264) {
    const char* xml = "<root></root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "root");
}

// Test parsing an element with attributes
TEST_F(XMLElementParseDeepTest_264, ParseElementWithAttributes_264) {
    const char* xml = "<element attr1=\"value1\" attr2=\"value2\"/>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("attr1"), "value1");
    EXPECT_STREQ(elem->Attribute("attr2"), "value2");
}

// Test parsing nested elements
TEST_F(XMLElementParseDeepTest_264, ParseNestedElements_264) {
    const char* xml = "<parent><child/></parent>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* parent = doc.FirstChildElement("parent");
    ASSERT_NE(parent, nullptr);
    const XMLElement* child = parent->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
}

// Test parsing element with text content
TEST_F(XMLElementParseDeepTest_264, ParseElementWithText_264) {
    const char* xml = "<element>Hello World</element>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->GetText(), "Hello World");
}

// Test parsing element with leading whitespace
TEST_F(XMLElementParseDeepTest_264, ParseElementWithLeadingWhitespace_264) {
    const char* xml = "   <element/>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "element");
}

// Test parsing empty document returns error
TEST_F(XMLElementParseDeepTest_264, ParseEmptyDocument_264) {
    const char* xml = "";
    doc.Parse(xml);
    EXPECT_TRUE(doc.Error());
}

// Test parsing malformed XML
TEST_F(XMLElementParseDeepTest_264, ParseMalformedXML_264) {
    const char* xml = "<element>";
    doc.Parse(xml);
    EXPECT_TRUE(doc.Error());
}

// Test closing type for self-closing element
TEST_F(XMLElementParseDeepTest_264, ClosingTypeSelfClosing_264) {
    const char* xml = "<element/>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ClosingType(), XMLElement::CLOSED);
}

// Test closing type for open element
TEST_F(XMLElementParseDeepTest_264, ClosingTypeOpen_264) {
    const char* xml = "<element></element>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ClosingType(), XMLElement::OPEN);
}

// Test parsing deeply nested elements
TEST_F(XMLElementParseDeepTest_264, ParseDeeplyNestedElements_264) {
    const char* xml = "<a><b><c><d>text</d></c></b></a>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* a = doc.FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    const XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    const XMLElement* c = b->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    const XMLElement* d = c->FirstChildElement("d");
    ASSERT_NE(d, nullptr);
    EXPECT_STREQ(d->GetText(), "text");
}

// Test parsing element with multiple children
TEST_F(XMLElementParseDeepTest_264, ParseMultipleChildren_264) {
    const char* xml = "<root><child1/><child2/><child3/></root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_NE(root->FirstChildElement("child1"), nullptr);
    EXPECT_NE(root->FirstChildElement("child2"), nullptr);
    EXPECT_NE(root->FirstChildElement("child3"), nullptr);
}

// Test parsing element with mismatched tags
TEST_F(XMLElementParseDeepTest_264, ParseMismatchedTags_264) {
    const char* xml = "<open></close>";
    doc.Parse(xml);
    EXPECT_TRUE(doc.Error());
}

// Test parsing element with attributes and children
TEST_F(XMLElementParseDeepTest_264, ParseElementWithAttributesAndChildren_264) {
    const char* xml = "<root attr=\"val\"><child>text</child></root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("attr"), "val");
    const XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->GetText(), "text");
}

// Test parsing with whitespace between elements
TEST_F(XMLElementParseDeepTest_264, ParseWithWhitespaceBetweenElements_264) {
    const char* xml = "<root>  <child/>  </root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
}

// Test parsing element with newlines
TEST_F(XMLElementParseDeepTest_264, ParseElementWithNewlines_264) {
    const char* xml = "<root>\n  <child/>\n</root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
}

// Test line number tracking during parsing
TEST_F(XMLElementParseDeepTest_264, ParseLineNumberTracking_264) {
    const char* xml = "<root>\n<child/>\n</root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetLineNum(), 1);
    const XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->GetLineNum(), 2);
}

// Test parsing element with no name (should fail)
TEST_F(XMLElementParseDeepTest_264, ParseElementNoName_264) {
    const char* xml = "< />";
    doc.Parse(xml);
    EXPECT_TRUE(doc.Error());
}

// Test parsing only whitespace
TEST_F(XMLElementParseDeepTest_264, ParseOnlyWhitespace_264) {
    const char* xml = "   \n\t  ";
    doc.Parse(xml);
    EXPECT_TRUE(doc.Error());
}

// Test parsing element with special characters in attribute values
TEST_F(XMLElementParseDeepTest_264, ParseElementWithSpecialCharsInAttr_264) {
    const char* xml = "<element attr=\"a&amp;b\"/>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Attribute("attr"), "a&b");
}

// Test parsing XML declaration followed by element
TEST_F(XMLElementParseDeepTest_264, ParseWithDeclaration_264) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
}

// Test parsing element with sibling elements at root level (should handle correctly via document)
TEST_F(XMLElementParseDeepTest_264, ParseSiblingElementsUnderRoot_264) {
    const char* xml = "<root><a/><b/></root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    const XMLElement* b = a->NextSiblingElement("b");
    ASSERT_NE(b, nullptr);
}

// Test element child element count after parsing
TEST_F(XMLElementParseDeepTest_264, ChildElementCountAfterParse_264) {
    const char* xml = "<root><a/><b/><c/></root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 3);
}

// Test parsing empty self-closing element has no children
TEST_F(XMLElementParseDeepTest_264, SelfClosingHasNoChildren_264) {
    const char* xml = "<element/>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    const XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(elem->NoChildren());
}

// Test parsing element with numeric name
TEST_F(XMLElementParseDeepTest_264, ParseElementInvalidNameStartsWithNumber_264) {
    const char* xml = "<123element/>";
    doc.Parse(xml);
    // Names starting with numbers are invalid in XML
    EXPECT_TRUE(doc.Error());
}
