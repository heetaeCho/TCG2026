#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLDocumentParseTest_283 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// ==================== Normal Operation Tests ====================

TEST_F(XMLDocumentParseTest_283, ParseValidSimpleXML_283) {
    const char* xml = "<root></root>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(nullptr, doc.RootElement());
}

TEST_F(XMLDocumentParseTest_283, ParseValidXMLWithContent_283) {
    const char* xml = "<root><child>text</child></root>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(nullptr, doc.RootElement());
    EXPECT_NE(nullptr, doc.RootElement()->FirstChildElement("child"));
}

TEST_F(XMLDocumentParseTest_283, ParseWithAutoDetectedLength_283) {
    const char* xml = "<root/>";
    XMLError err = doc.Parse(xml, static_cast<size_t>(-1));
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(nullptr, doc.RootElement());
}

TEST_F(XMLDocumentParseTest_283, ParseValidXMLWithAttributes_283) {
    const char* xml = "<root attr=\"value\"/>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("value", root->Attribute("attr"));
}

TEST_F(XMLDocumentParseTest_283, ParseValidXMLWithDeclaration_283) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseValidXMLWithComment_283) {
    const char* xml = "<!-- comment --><root/>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseValidXMLWithNestedElements_283) {
    const char* xml = "<a><b><c><d>deep</d></c></b></a>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseMultipleTimes_283) {
    const char* xml1 = "<first/>";
    XMLError err1 = doc.Parse(xml1, strlen(xml1));
    EXPECT_EQ(XML_SUCCESS, err1);
    EXPECT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("first", doc.RootElement()->Name());

    const char* xml2 = "<second/>";
    XMLError err2 = doc.Parse(xml2, strlen(xml2));
    EXPECT_EQ(XML_SUCCESS, err2);
    EXPECT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("second", doc.RootElement()->Name());
}

TEST_F(XMLDocumentParseTest_283, ParseWithExplicitLength_283) {
    // Pass a string with extra garbage after nBytes
    const char* xml = "<root/>GARBAGE";
    XMLError err = doc.Parse(xml, 7); // only "<root/>"
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("root", doc.RootElement()->Name());
}

TEST_F(XMLDocumentParseTest_283, ParseSelfClosingElement_283) {
    const char* xml = "<empty/>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    EXPECT_TRUE(doc.RootElement()->NoChildren());
}

TEST_F(XMLDocumentParseTest_283, ParseTextContent_283) {
    const char* xml = "<root>Hello World</root>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("Hello World", doc.RootElement()->GetText());
}

// ==================== Boundary Condition Tests ====================

TEST_F(XMLDocumentParseTest_283, ParseNullPointer_283) {
    XMLError err = doc.Parse(nullptr, 10);
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseZeroLength_283) {
    const char* xml = "<root/>";
    XMLError err = doc.Parse(xml, 0);
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseEmptyString_283) {
    const char* xml = "";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseEmptyStringWithNullTerminator_283) {
    const char* xml = "";
    XMLError err = doc.Parse(xml, static_cast<size_t>(-1));
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseNullWithZeroLength_283) {
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseNullWithAutoLength_283) {
    XMLError err = doc.Parse(nullptr, static_cast<size_t>(-1));
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseMinimalValidXML_283) {
    const char* xml = "<a/>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseSingleCharLength_283) {
    // Passing just "<" should result in a parse error
    const char* xml = "<root/>";
    XMLError err = doc.Parse(xml, 1);
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

// ==================== Error Case Tests ====================

TEST_F(XMLDocumentParseTest_283, ParseMismatchedTags_283) {
    const char* xml = "<root><child></root>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseMalformedXML_283) {
    const char* xml = "<root><";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseUnclosedTag_283) {
    const char* xml = "<root>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseNotXML_283) {
    const char* xml = "This is not XML";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseMismatchedElementError_283) {
    const char* xml = "<root></notroot>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_ERROR_MISMATCHED_ELEMENT, err);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ErrorIDMatchesErrorState_283) {
    const char* xml = "";
    doc.Parse(xml, static_cast<size_t>(-1));
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, doc.ErrorID());
}

TEST_F(XMLDocumentParseTest_283, ErrorClearedOnSuccessfulReparse_283) {
    // First parse fails
    doc.Parse("", static_cast<size_t>(-1));
    EXPECT_TRUE(doc.Error());

    // Second parse succeeds and should clear the error
    XMLError err = doc.Parse("<root/>", static_cast<size_t>(-1));
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ChildrenClearedOnError_283) {
    // First parse succeeds
    doc.Parse("<root><child/></root>", static_cast<size_t>(-1));
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(nullptr, doc.RootElement());

    // Second parse fails - children should be cleaned up
    doc.Parse("<root><child></root>", static_cast<size_t>(-1));
    EXPECT_TRUE(doc.Error());
    // After error, there should be no root element
    EXPECT_EQ(nullptr, doc.RootElement());
}

TEST_F(XMLDocumentParseTest_283, ParseWithWhitespaceOnly_283) {
    const char* xml = "   \n\t  ";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
}

// ==================== ErrorName and ErrorStr Tests ====================

TEST_F(XMLDocumentParseTest_283, ErrorNameReturnsValidString_283) {
    doc.Parse("", static_cast<size_t>(-1));
    EXPECT_TRUE(doc.Error());
    const char* name = doc.ErrorName();
    EXPECT_NE(nullptr, name);
    EXPECT_GT(strlen(name), 0u);
}

TEST_F(XMLDocumentParseTest_283, ErrorStrReturnsValidString_283) {
    doc.Parse("", static_cast<size_t>(-1));
    EXPECT_TRUE(doc.Error());
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(nullptr, errStr);
}

TEST_F(XMLDocumentParseTest_283, NoErrorAfterValidParse_283) {
    doc.Parse("<root/>", static_cast<size_t>(-1));
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
}

// ==================== ClearError Tests ====================

TEST_F(XMLDocumentParseTest_283, ClearErrorResetsErrorState_283) {
    doc.Parse("", static_cast<size_t>(-1));
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
}

// ==================== ErrorIDToName Tests ====================

TEST_F(XMLDocumentParseTest_283, ErrorIDToNameForSuccess_283) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(nullptr, name);
}

TEST_F(XMLDocumentParseTest_283, ErrorIDToNameForEmptyDocument_283) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_EMPTY_DOCUMENT);
    EXPECT_NE(nullptr, name);
    EXPECT_GT(strlen(name), 0u);
}

// ==================== Process Entities Tests ====================

TEST(XMLDocumentConstructor_283, DefaultProcessEntities_283) {
    XMLDocument doc(true);
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST(XMLDocumentConstructor_283, DisableProcessEntities_283) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.ProcessEntities());
}

// ==================== XMLDocument with multiple children ====================

TEST_F(XMLDocumentParseTest_283, ParseMultipleChildElements_283) {
    const char* xml = "<root><a/><b/><c/></root>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_SUCCESS, err);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(3, root->ChildElementCount());
}

TEST_F(XMLDocumentParseTest_283, ParseXMLWithCDATA_283) {
    const char* xml = "<root><![CDATA[Some <data>]]></root>";
    XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentParseTest_283, ParseLargerDocument_283) {
    std::string xml = "<root>";
    for (int i = 0; i < 100; ++i) {
        xml += "<item id=\"" + std::to_string(i) + "\">value</item>";
    }
    xml += "</root>";
    XMLError err = doc.Parse(xml.c_str(), xml.size());
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(100, doc.RootElement()->ChildElementCount());
}

TEST_F(XMLDocumentParseTest_283, ParsePartialLengthValidSubstring_283) {
    // Only parse the first element out of a longer buffer
    const char* xml = "<a/><b/>";
    XMLError err = doc.Parse(xml, 4); // "<a/>"
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("a", doc.RootElement()->Name());
}

// ==================== ErrorLineNum Tests ====================

TEST_F(XMLDocumentParseTest_283, ErrorLineNumAfterEmptyDocument_283) {
    doc.Parse("", static_cast<size_t>(-1));
    EXPECT_TRUE(doc.Error());
    // Line number should be 0 for empty document
    EXPECT_EQ(0, doc.ErrorLineNum());
}

TEST_F(XMLDocumentParseTest_283, ErrorLineNumOnMismatch_283) {
    const char* xml = "<root>\n<child>\n</root>";
    doc.Parse(xml, static_cast<size_t>(-1));
    EXPECT_TRUE(doc.Error());
    // Error line should be > 0 for content with newlines
    EXPECT_GT(doc.ErrorLineNum(), 0);
}
