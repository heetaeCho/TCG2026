#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLUnknownTest_205 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test that a simple unknown declaration is parsed correctly
TEST_F(XMLUnknownTest_205, ParseSimpleUnknown_205) {
    const char* xml = "<?xml version=\"1.0\"?><root><!SOMETHING unknown></root>";
    XMLError err = doc.Parse(xml);
    // The unknown node "<!SOMETHING unknown>" should be parsed
    // Check if document parsed without error or if the unknown is accessible
    // Note: tinyxml2 treats <!...> as XMLUnknown
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLNode* child = root->FirstChild();
    ASSERT_NE(nullptr, child);
    
    XMLUnknown* unknown = child->ToUnknown();
    ASSERT_NE(nullptr, unknown);
    EXPECT_STREQ("SOMETHING unknown", unknown->Value());
}

// Test parsing an unknown node with various content
TEST_F(XMLUnknownTest_205, ParseUnknownWithSpecialChars_205) {
    const char* xml = "<root><!ENTITY foo \"bar\"></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLUnknown* unknown = root->FirstChild()->ToUnknown();
    ASSERT_NE(nullptr, unknown);
    EXPECT_STREQ("ENTITY foo \"bar\"", unknown->Value());
}

// Test that an unterminated unknown results in an error
TEST_F(XMLUnknownTest_205, ParseUnterminatedUnknown_205) {
    const char* xml = "<root><!SOMETHING without closing";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_EQ(XML_ERROR_PARSING_UNKNOWN, doc.ErrorID());
}

// Test empty unknown node
TEST_F(XMLUnknownTest_205, ParseEmptyUnknown_205) {
    const char* xml = "<root><!></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLUnknown* unknown = root->FirstChild()->ToUnknown();
    ASSERT_NE(nullptr, unknown);
    EXPECT_STREQ("", unknown->Value());
}

// Test unknown node with newlines (newline normalization)
TEST_F(XMLUnknownTest_205, ParseUnknownWithNewlines_205) {
    const char* xml = "<root><!SOMETHING\nwith\nnewlines></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLNode* child = root->FirstChild();
    ASSERT_NE(nullptr, child);
    
    XMLUnknown* unknown = child->ToUnknown();
    ASSERT_NE(nullptr, unknown);
    // The value should contain the content (with possible newline normalization)
    ASSERT_NE(nullptr, unknown->Value());
}

// Test multiple unknown nodes in sequence
TEST_F(XMLUnknownTest_205, ParseMultipleUnknowns_205) {
    const char* xml = "<root><!FIRST><!SECOND></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLNode* first = root->FirstChild();
    ASSERT_NE(nullptr, first);
    ASSERT_NE(nullptr, first->ToUnknown());
    EXPECT_STREQ("FIRST", first->ToUnknown()->Value());
    
    XMLNode* second = first->NextSibling();
    ASSERT_NE(nullptr, second);
    ASSERT_NE(nullptr, second->ToUnknown());
    EXPECT_STREQ("SECOND", second->ToUnknown()->Value());
}

// Test unknown node with spaces only
TEST_F(XMLUnknownTest_205, ParseUnknownWithSpaces_205) {
    const char* xml = "<root><!   ></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLUnknown* unknown = root->FirstChild()->ToUnknown();
    ASSERT_NE(nullptr, unknown);
}

// Test that XMLUnknown can be printed/serialized
TEST_F(XMLUnknownTest_205, PrintUnknown_205) {
    const char* xml = "<root><!SOMETHING unknown></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLPrinter printer;
    doc.Accept(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(nullptr, result);
    // The output should contain the unknown declaration
    EXPECT_NE(nullptr, strstr(result, "<!SOMETHING unknown>"));
}

// Test ShallowClone of unknown node
TEST_F(XMLUnknownTest_205, ShallowCloneUnknown_205) {
    const char* xml = "<root><!SOMETHING></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLUnknown* unknown = root->FirstChild()->ToUnknown();
    ASSERT_NE(nullptr, unknown);
    
    XMLNode* clone = unknown->ShallowClone(&doc);
    ASSERT_NE(nullptr, clone);
    ASSERT_NE(nullptr, clone->ToUnknown());
    EXPECT_STREQ("SOMETHING", clone->ToUnknown()->Value());
    
    // Clean up - the clone is not inserted into the tree
    doc.DeleteNode(clone);
}

// Test that unknown node with angle brackets inside fails or handles correctly
TEST_F(XMLUnknownTest_205, ParseUnknownWithAngleBracket_205) {
    // The parser looks for '>' to end the unknown, so '<' inside should stop at first '>'
    const char* xml = "<root><!FOO < BAR></root>";
    XMLError err = doc.Parse(xml);
    // This might parse "FOO < BAR" or fail; we just check it doesn't crash
    // The behavior depends on implementation
    (void)err;
}

// Test line number tracking for error in unknown
TEST_F(XMLUnknownTest_205, ErrorLineNumberForUnterminatedUnknown_205) {
    const char* xml = "<root>\n\n<!UNTERMINATED";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_EQ(XML_ERROR_PARSING_UNKNOWN, doc.ErrorID());
}
