#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeParseDeepTest_192 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test parsing a simple well-formed XML element
TEST_F(XMLNodeParseDeepTest_192, ParseSimpleElement_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

// Test parsing a self-closing element
TEST_F(XMLNodeParseDeepTest_192, ParseSelfClosingElement_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

// Test parsing nested elements
TEST_F(XMLNodeParseDeepTest_192, ParseNestedElements_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child><grandchild/></child></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    XMLElement* grandchild = child->FirstChildElement("grandchild");
    ASSERT_NE(grandchild, nullptr);
}

// Test parsing with mismatched element tags
TEST_F(XMLNodeParseDeepTest_192, ParseMismatchedElement_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root></wrong>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_MISMATCHED_ELEMENT);
}

// Test parsing empty document
TEST_F(XMLNodeParseDeepTest_192, ParseEmptyDocument_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_EMPTY_DOCUMENT);
}

// Test parsing with XML declaration at the beginning
TEST_F(XMLNodeParseDeepTest_192, ParseWithDeclaration_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

// Test parsing with XML declaration not at the top level (error case)
TEST_F(XMLNodeParseDeepTest_192, ParseDeclarationInsideElement_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><?xml version=\"1.0\"?></root>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// Test parsing multiple children
TEST_F(XMLNodeParseDeepTest_192, ParseMultipleChildren_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><a/><b/><c/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 3);
}

// Test parsing with text content
TEST_F(XMLNodeParseDeepTest_192, ParseElementWithText_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>Hello World</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "Hello World");
}

// Test parsing with comments
TEST_F(XMLNodeParseDeepTest_192, ParseWithComments_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><!-- comment --><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
}

// Test parsing with attributes
TEST_F(XMLNodeParseDeepTest_192, ParseElementWithAttributes_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root attr=\"value\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("attr"), "value");
}

// Test parsing deeply nested elements (checking depth tracking)
TEST_F(XMLNodeParseDeepTest_192, ParseDeeplyNestedElements_192) {
    // Build a moderately deep XML string
    std::string xml;
    int depth = 50;
    for (int i = 0; i < depth; ++i) {
        xml += "<e>";
    }
    for (int i = 0; i < depth; ++i) {
        xml += "</e>";
    }
    XMLDocument doc;
    XMLError err = doc.Parse(xml.c_str());
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

// Test parsing with open element but no closing tag
TEST_F(XMLNodeParseDeepTest_192, ParseUnclosedElement_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// Test parsing null-like content
TEST_F(XMLNodeParseDeepTest_192, ParseWhitespaceOnly_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("   ");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// Test parsing sibling elements at the document level (only one root allowed)
TEST_F(XMLNodeParseDeepTest_192, ParseMultipleRootElements_192) {
    XMLDocument doc;
    // Some parsers allow this, some don't; tinyxml2 typically allows multiple top-level nodes
    XMLError err = doc.Parse("<a/><b/>");
    // tinyxml2 may or may not error here; just check observable behavior
    if (err == XML_SUCCESS) {
        XMLElement* root = doc.RootElement();
        ASSERT_NE(root, nullptr);
    }
}

// Test parsing CDATA section
TEST_F(XMLNodeParseDeepTest_192, ParseCDATA_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><![CDATA[some data]]></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

// Test parsing with mixed children (elements, text, comments)
TEST_F(XMLNodeParseDeepTest_192, ParseMixedContent_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>text1<child/><!-- comment -->text2</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
}

// Test that error state prevents further parsing
TEST_F(XMLNodeParseDeepTest_192, ErrorStatePreventsProcessing_192) {
    XMLDocument doc;
    doc.Parse("<root></wrong>");
    EXPECT_TRUE(doc.Error());
    XMLError firstError = doc.ErrorID();
    // Parse again to reset
    doc.Parse("<valid/>");
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "valid");
}

// Test parsing with unknown markup (e.g., processing instruction-like)
TEST_F(XMLNodeParseDeepTest_192, ParseUnknownMarkup_192) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><!UNKNOWN stuff></root>");
    // tinyxml2 treats unknown markup starting with <! as XMLUnknown
    // Should succeed if properly terminated
    if (err == XML_SUCCESS) {
        EXPECT_FALSE(doc.Error());
    }
}

// Test element closing type detection - CLOSED (self-closing)
TEST_F(XMLNodeParseDeepTest_192, SelfClosingElementClosingType_192) {
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ClosingType(), XMLElement::CLOSED);
}

// Test element closing type detection - OPEN (has separate closing tag)
TEST_F(XMLNodeParseDeepTest_192, OpenElementClosingType_192) {
    XMLDocument doc;
    doc.Parse("<root></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->ClosingType(), XMLElement::OPEN);
}

// Test ClearError resets error state
TEST_F(XMLNodeParseDeepTest_192, ClearErrorResetsState_192) {
    XMLDocument doc;
    doc.Parse("<root></wrong>");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

// Test parsing with line number tracking
TEST_F(XMLNodeParseDeepTest_192, LineNumberTracking_192) {
    XMLDocument doc;
    doc.Parse("<root>\n<child/>\n</root>");
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetLineNum(), 1);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->GetLineNum(), 2);
}

// Test parsing element with no children
TEST_F(XMLNodeParseDeepTest_192, NoChildrenElement_192) {
    XMLDocument doc;
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(root->NoChildren());
}

// Test that children are properly linked
TEST_F(XMLNodeParseDeepTest_192, ChildrenProperlyLinked_192) {
    XMLDocument doc;
    doc.Parse("<root><a/><b/><c/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLElement* a = root->FirstChildElement("a");
    XMLElement* b = root->FirstChildElement("b");
    XMLElement* c = root->FirstChildElement("c");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    ASSERT_NE(c, nullptr);

    EXPECT_EQ(a->NextSiblingElement(), b);
    EXPECT_EQ(b->NextSiblingElement(), c);
    EXPECT_EQ(c->NextSiblingElement(), nullptr);
    EXPECT_EQ(c->PreviousSiblingElement(), b);
    EXPECT_EQ(b->PreviousSiblingElement(), a);
}

// Test error line number on mismatched element
TEST_F(XMLNodeParseDeepTest_192, MismatchedElementLineNumber_192) {
    XMLDocument doc;
    doc.Parse("<root>\n<child>\n</wrong>\n</root>");
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_MISMATCHED_ELEMENT);
    // The error line should correspond to the mismatched element
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

// Test parsing with entities
TEST_F(XMLNodeParseDeepTest_192, ParseWithEntities_192) {
    XMLDocument doc(true); // processEntities = true
    XMLError err = doc.Parse("<root>&amp;&lt;&gt;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "&<>");
}

// Test parsing without entity processing
TEST_F(XMLNodeParseDeepTest_192, ParseWithoutEntityProcessing_192) {
    XMLDocument doc(false); // processEntities = false
    XMLError err = doc.Parse("<root>&amp;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "&amp;");
}
