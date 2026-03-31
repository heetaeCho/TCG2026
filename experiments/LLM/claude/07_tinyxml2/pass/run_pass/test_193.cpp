#include "tinyxml2.h"
#include <gtest/gtest.h>
#include <cstring>

using namespace tinyxml2;

class XMLTextTest_193 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test normal text parsing
TEST_F(XMLTextTest_193, ParseSimpleText_193) {
    const char* xml = "<root>Hello World</root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLText* text = root->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "Hello World");
}

// Test CDATA parsing
TEST_F(XMLTextTest_193, ParseCDataSection_193) {
    const char* xml = "<root><![CDATA[Some <special> & data]]></root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLText* text = root->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->CData());
    EXPECT_STREQ(text->Value(), "Some <special> & data");
}

// Test empty text
TEST_F(XMLTextTest_193, ParseEmptyText_193) {
    const char* xml = "<root></root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    // Empty element should have no children
    EXPECT_EQ(root->FirstChild(), nullptr);
}

// Test text with entities
TEST_F(XMLTextTest_193, ParseTextWithEntities_193) {
    doc.SetBOM(false);
    const char* xml = "<root>a &amp; b</root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "a & b");
}

// Test text with entity processing disabled
TEST_F(XMLTextTest_193, ParseTextWithoutEntityProcessing_193) {
    const char* xml = "<root>a &amp; b</root>";
    doc.SetBOM(false);
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_NE(root->GetText(), nullptr);
}

// Test CDATA with no closing tag - should produce error
TEST_F(XMLTextTest_193, ParseCDataMissingClose_193) {
    const char* xml = "<root><![CDATA[unterminated cdata</root>";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test text with whitespace collapsing
TEST_F(XMLTextTest_193, ParseTextWhitespaceCollapse_193) {
    const char* xml = "<root>  hello   world  </root>";
    doc.SetBOM(false);
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_NE(root->GetText(), nullptr);
}

// Test CDATA with newlines
TEST_F(XMLTextTest_193, ParseCDataWithNewlines_193) {
    const char* xml = "<root><![CDATA[line1\nline2\nline3]]></root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLText* text = root->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->CData());
}

// Test text node is not CDATA
TEST_F(XMLTextTest_193, RegularTextIsNotCData_193) {
    const char* xml = "<root>regular text</root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLText* text = root->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_FALSE(text->CData());
}

// Test multiple text and element children
TEST_F(XMLTextTest_193, ParseMixedContent_193) {
    const char* xml = "<root>text1<child/>text2</root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    ASSERT_NE(first->ToText(), nullptr);
    EXPECT_STREQ(first->Value(), "text1");
}

// Test CDATA empty content
TEST_F(XMLTextTest_193, ParseEmptyCData_193) {
    const char* xml = "<root><![CDATA[]]></root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
}

// Test text with special XML characters as entities
TEST_F(XMLTextTest_193, ParseTextWithLtEntity_193) {
    const char* xml = "<root>a &lt; b</root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "a < b");
}

// Test text with gt entity
TEST_F(XMLTextTest_193, ParseTextWithGtEntity_193) {
    const char* xml = "<root>a &gt; b</root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "a > b");
}

// Test CDATA preserves entities literally
TEST_F(XMLTextTest_193, CDataPreservesEntitiesLiterally_193) {
    const char* xml = "<root><![CDATA[a &amp; b]]></root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLText* text = root->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->CData());
    // CDATA should preserve the literal &amp; without interpretation
    EXPECT_STREQ(text->Value(), "a &amp; b");
}

// Test parsing text that consists only of whitespace
TEST_F(XMLTextTest_193, ParseWhitespaceOnlyText_193) {
    const char* xml = "<root>   </root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
}

// Test unterminated text (no closing tag)
TEST_F(XMLTextTest_193, ParseUnterminatedElement_193) {
    const char* xml = "<root>unterminated text";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test numeric character reference in text
TEST_F(XMLTextTest_193, ParseTextWithNumericCharRef_193) {
    const char* xml = "<root>&#65;</root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "A");
}

// Test CDATA followed by regular text
TEST_F(XMLTextTest_193, CDataFollowedByText_193) {
    const char* xml = "<root><![CDATA[cdata]]>text</root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    const XMLText* cdataText = first->ToText();
    ASSERT_NE(cdataText, nullptr);
    EXPECT_TRUE(cdataText->CData());
    EXPECT_STREQ(cdataText->Value(), "cdata");
}
