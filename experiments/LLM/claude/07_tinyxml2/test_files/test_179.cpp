#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLDocumentIdentifyTest_179 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test identification of XML declaration (<?...?>)
TEST_F(XMLDocumentIdentifyTest_179, IdentifyXMLDeclaration_179) {
    XMLDocument doc;
    char input[] = "<?xml version=\"1.0\"?>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToDeclaration(), nullptr);
    // p should be advanced past "<?", so it should point to "xml version..."
    EXPECT_EQ(result, input + 2);
}

// Test identification of XML comment (<!--...-->)
TEST_F(XMLDocumentIdentifyTest_179, IdentifyXMLComment_179) {
    XMLDocument doc;
    char input[] = "<!--This is a comment-->";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToComment(), nullptr);
    // p should be advanced past "<!--"
    EXPECT_EQ(result, input + 4);
}

// Test identification of CDATA section (<![CDATA[...]]>)
TEST_F(XMLDocumentIdentifyTest_179, IdentifyCDATA_179) {
    XMLDocument doc;
    char input[] = "<![CDATA[some data]]>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    XMLText* text = node->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->CData());
    // p should be advanced past "<![CDATA["
    EXPECT_EQ(result, input + 9);
}

// Test identification of DTD/Unknown (<!...>)
TEST_F(XMLDocumentIdentifyTest_179, IdentifyDTD_179) {
    XMLDocument doc;
    char input[] = "<!DOCTYPE html>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToUnknown(), nullptr);
    // p should be advanced past "<!"
    EXPECT_EQ(result, input + 2);
}

// Test identification of XML element (<...>)
TEST_F(XMLDocumentIdentifyTest_179, IdentifyElement_179) {
    XMLDocument doc;
    char input[] = "<root>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToElement(), nullptr);
    // p should be advanced past "<"
    EXPECT_EQ(result, input + 1);
}

// Test identification of plain text (no leading <)
TEST_F(XMLDocumentIdentifyTest_179, IdentifyText_179) {
    XMLDocument doc;
    char input[] = "Hello World";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToText(), nullptr);
    // For text, p should be backed up to the start
    EXPECT_EQ(result, input);
}

// Test that empty string returns null node
TEST_F(XMLDocumentIdentifyTest_179, IdentifyEmptyString_179) {
    XMLDocument doc;
    char input[] = "";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    EXPECT_EQ(node, nullptr);
    EXPECT_EQ(result, input);
}

// Test with only whitespace - should return null node
TEST_F(XMLDocumentIdentifyTest_179, IdentifyOnlyWhitespace_179) {
    XMLDocument doc;
    char input[] = "   \t\n  ";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    EXPECT_EQ(node, nullptr);
}

// Test with leading whitespace before element
TEST_F(XMLDocumentIdentifyTest_179, IdentifyElementWithLeadingWhitespace_179) {
    XMLDocument doc;
    char input[] = "   <element>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToElement(), nullptr);
}

// Test with leading whitespace before comment
TEST_F(XMLDocumentIdentifyTest_179, IdentifyCommentWithLeadingWhitespace_179) {
    XMLDocument doc;
    char input[] = "  <!--comment-->";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToComment(), nullptr);
}

// Test with leading whitespace before declaration
TEST_F(XMLDocumentIdentifyTest_179, IdentifyDeclarationWithLeadingWhitespace_179) {
    XMLDocument doc;
    char input[] = "  <?xml version=\"1.0\"?>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToDeclaration(), nullptr);
}

// Test that CDATA node has CData flag set to true
TEST_F(XMLDocumentIdentifyTest_179, CDATAHasCDataFlag_179) {
    XMLDocument doc;
    char input[] = "<![CDATA[test]]>";
    XMLNode* node = nullptr;
    doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    XMLText* text = node->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->CData());
}

// Test text node does not have CData flag
TEST_F(XMLDocumentIdentifyTest_179, TextDoesNotHaveCDataFlag_179) {
    XMLDocument doc;
    char input[] = "plain text";
    XMLNode* node = nullptr;
    doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    XMLText* text = node->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_FALSE(text->CData());
}

// Test PEDANTIC_WHITESPACE mode with closing tag and first=true and leading whitespace
TEST_F(XMLDocumentIdentifyTest_179, PedanticWhitespaceClosingTagFirst_179) {
    XMLDocument doc(true, PEDANTIC_WHITESPACE);
    char input[] = " </root>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, true);
    ASSERT_NE(node, nullptr);
    // In PEDANTIC_WHITESPACE with first=true, leading whitespace before closing tag
    // should create a text node and back up to start
    XMLText* text = node->ToText();
    EXPECT_NE(text, nullptr);
    EXPECT_EQ(result, input);
}

// Test PEDANTIC_WHITESPACE mode with closing tag and first=false
TEST_F(XMLDocumentIdentifyTest_179, PedanticWhitespaceClosingTagNotFirst_179) {
    XMLDocument doc(true, PEDANTIC_WHITESPACE);
    char input[] = " </root>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    // When first=false, should be identified as an element even in PEDANTIC mode
    // The closing tag starts with "</" which starts with "<"
    // Since first is false, the special PEDANTIC branch is not taken
    EXPECT_NE(node->ToElement(), nullptr);
}

// Test non-PEDANTIC whitespace with closing tag
TEST_F(XMLDocumentIdentifyTest_179, NonPedanticWhitespaceClosingTag_179) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    char input[] = " </root>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, true);
    ASSERT_NE(node, nullptr);
    // In non-pedantic mode, closing tag should be identified as element
    EXPECT_NE(node->ToElement(), nullptr);
}

// Test identification through Parse - full XML document with declaration
TEST_F(XMLDocumentIdentifyTest_179, ParseFullDocument_179) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\"?><root>text</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

// Test identification through Parse - document with comment
TEST_F(XMLDocumentIdentifyTest_179, ParseDocumentWithComment_179) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><!--comment--></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_NE(child->ToComment(), nullptr);
}

// Test identification through Parse - document with CDATA
TEST_F(XMLDocumentIdentifyTest_179, ParseDocumentWithCDATA_179) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><![CDATA[some <data>]]></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    const XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    const XMLText* text = child->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->CData());
}

// Test that Identify handles a single < character followed by non-element chars as text
TEST_F(XMLDocumentIdentifyTest_179, IdentifySingleLessThan_179) {
    XMLDocument doc;
    // "< " doesn't match any known header pattern except element,
    // but space is not a valid name start char - let's test what happens
    // Actually "<" followed by space still matches elementHeader "<"
    char input[] = "< space";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    // It should match "<" as element header
    EXPECT_NE(node->ToElement(), nullptr);
}

// Test multiple nodes identified via parsing
TEST_F(XMLDocumentIdentifyTest_179, ParseMultipleElements_179) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><a/><b/><c/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    int count = 0;
    for (const XMLNode* child = root->FirstChild(); child; child = child->NextSibling()) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test that line number is tracked correctly
TEST_F(XMLDocumentIdentifyTest_179, LineNumberTracking_179) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root>\n<!--comment-->\n</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetLineNum(), 1);
    const XMLNode* comment = root->FirstChild();
    // Skip text nodes if any
    while (comment && comment->ToText()) {
        comment = comment->NextSibling();
    }
    if (comment && comment->ToComment()) {
        EXPECT_EQ(comment->GetLineNum(), 2);
    }
}

// Test PEDANTIC_WHITESPACE without leading whitespace before closing tag (first=true)
TEST_F(XMLDocumentIdentifyTest_179, PedanticWhitespaceNoLeadingWhitespace_179) {
    XMLDocument doc(true, PEDANTIC_WHITESPACE);
    char input[] = "</root>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, true);
    ASSERT_NE(node, nullptr);
    // No whitespace before </root>, so p == start, condition p != start is false
    // Should be identified as element
    EXPECT_NE(node->ToElement(), nullptr);
}

// Test that DTD-like unknown nodes are correctly identified
TEST_F(XMLDocumentIdentifyTest_179, IdentifyUnknownDTD_179) {
    XMLDocument doc;
    XMLError err = doc.Parse("<!DOCTYPE test><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    // The document should have parsed successfully with an unknown node and root element
    EXPECT_NE(doc.RootElement(), nullptr);
}

// Test with COLLAPSE_WHITESPACE mode
TEST_F(XMLDocumentIdentifyTest_179, CollapseWhitespaceMode_179) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    char input[] = "  <element>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToElement(), nullptr);
}

// Test that a text node with special characters is identified as text
TEST_F(XMLDocumentIdentifyTest_179, IdentifyTextWithSpecialChars_179) {
    XMLDocument doc;
    char input[] = "abc&lt;def";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToText(), nullptr);
    EXPECT_EQ(result, input);
}

// Test identification of newline-only content
TEST_F(XMLDocumentIdentifyTest_179, IdentifyNewlineOnly_179) {
    XMLDocument doc;
    char input[] = "\n";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    // Whitespace is skipped; after skipping, we reach null terminator
    EXPECT_EQ(node, nullptr);
}

// Verify returned pointer for CDATA identification
TEST_F(XMLDocumentIdentifyTest_179, CDATAReturnPointer_179) {
    XMLDocument doc;
    char input[] = "<![CDATA[content]]>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    // Should point past "<![CDATA[" which is 9 characters
    EXPECT_EQ(result, input + 9);
}

// Verify returned pointer for DTD identification
TEST_F(XMLDocumentIdentifyTest_179, DTDReturnPointer_179) {
    XMLDocument doc;
    char input[] = "<!DOCTYPE html>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, false);
    ASSERT_NE(node, nullptr);
    // Should point past "<!" which is 2 characters
    EXPECT_EQ(result, input + 2);
}

// Test PEDANTIC_WHITESPACE: leading whitespace before element (not closing tag), first=true
TEST_F(XMLDocumentIdentifyTest_179, PedanticWhitespaceOpeningTagFirst_179) {
    XMLDocument doc(true, PEDANTIC_WHITESPACE);
    char input[] = " <root>";
    XMLNode* node = nullptr;
    char* result = doc.Identify(input, &node, true);
    ASSERT_NE(node, nullptr);
    // For opening tag with PEDANTIC and first=true, the *(p+1) is 'r', not '/',
    // so the normal element path should be taken
    EXPECT_NE(node->ToElement(), nullptr);
}
