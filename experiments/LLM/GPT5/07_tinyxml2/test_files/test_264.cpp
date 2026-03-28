// File: XMLElementParseDeepTest_264.cpp
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementParseDeepTest_264 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

// Normal operation: leading whitespace/newlines are skipped and line numbers advance.
// This exercises XMLUtil::SkipWhiteSpace usage inside XMLElement::ParseDeep.
TEST_F(XMLElementParseDeepTest_264, RootElementLineNumberAccountsForLeadingWhitespace_264) {
    // Root starts on line 3.
    const char* xml =
        "\n"
        "\n"
        "   <root/>\n";

    const XMLError err = doc_.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);

    XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");

    // tinyxml2 line numbers are 1-based.
    EXPECT_EQ(root->GetLineNum(), 3);
}

// Normal operation: element name parsing works after whitespace.
TEST_F(XMLElementParseDeepTest_264, ParsesElementNameAfterWhitespace_264) {
    const char* xml = " \t\r\n<alpha></alpha>";
    const XMLError err = doc_.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);

    XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "alpha");
}

// Boundary/variant: self-closing element should be reported as CLOSED via ClosingType().
// This is an observable effect of parsing the start tag and its closing style.
TEST_F(XMLElementParseDeepTest_264, SelfClosingElementHasClosedClosingType_264) {
    const char* xml = "<root/>";
    const XMLError err = doc_.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);

    XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->ClosingType(), XMLElement::CLOSED);
}

// Boundary/variant: non-self-closing element should be OPEN (not CLOSED).
TEST_F(XMLElementParseDeepTest_264, NonSelfClosingElementHasOpenClosingType_264) {
    const char* xml = "<root></root>";
    const XMLError err = doc_.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);

    XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->ClosingType(), XMLElement::OPEN);
}

// Normal operation: attributes are parsed and observable through Attribute().
TEST_F(XMLElementParseDeepTest_264, ParsesAttributesOnElement_264) {
    const char* xml = "<root a=\"1\" b='two' c=\"three\"/>";
    const XMLError err = doc_.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);

    XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);

    EXPECT_STREQ(root->Attribute("a"), "1");
    EXPECT_STREQ(root->Attribute("b"), "two");
    EXPECT_STREQ(root->Attribute("c"), "three");
}

// Normal operation: attributes + children parse together (attributes parsed before descending).
TEST_F(XMLElementParseDeepTest_264, ParsesAttributesAndThenChildren_264) {
    const char* xml = "<root id=\"X\"><child/></root>";
    const XMLError err = doc_.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);

    XMLElement* root = doc_.RootElement();
    ASSERT_NE(root, nullptr);

    EXPECT_STREQ(root->Attribute("id"), "X");

    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(child->ClosingType(), XMLElement::CLOSED);
}

// Error case: missing element name should fail parsing.
// This targets the observable outcome of ParseName producing an empty name.
TEST_F(XMLElementParseDeepTest_264, MissingElementNameFailsParsing_264) {
    const char* xml = "<></>";
    const XMLError err = doc_.Parse(xml);

    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_EQ(doc_.RootElement(), nullptr);
}

// Error case: stray closing tag at top-level should fail parsing.
// This exercises handling of a tag starting with "</" (closing-type path).
TEST_F(XMLElementParseDeepTest_264, StrayClosingTagAtDocumentStartFailsParsing_264) {
    const char* xml = "</root>";
    const XMLError err = doc_.Parse(xml);

    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_EQ(doc_.RootElement(), nullptr);
}

// Error case: mismatched end tag should fail parsing (ParseDeep will descend into XMLNode parsing).
TEST_F(XMLElementParseDeepTest_264, MismatchedEndTagFailsParsing_264) {
    const char* xml = "<root></notroot>";
    const XMLError err = doc_.Parse(xml);

    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_EQ(doc_.RootElement(), nullptr);
}

// Boundary: deep nesting still parses and returns a consistent tree.
// (We don't assume internal recursion details; we only validate observable structure.)
TEST_F(XMLElementParseDeepTest_264, DeeplyNestedElementsParseIntoTree_264) {
    const char* xml = "<a><b><c><d/></c></b></a>";
    const XMLError err = doc_.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);

    XMLElement* a = doc_.RootElement();
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Name(), "a");

    XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    XMLElement* c = b->FirstChildElement("c");
    ASSERT_NE(c, nullptr);

    XMLElement* d = c->FirstChildElement("d");
    ASSERT_NE(d, nullptr);
    EXPECT_EQ(d->ClosingType(), XMLElement::CLOSED);
}
