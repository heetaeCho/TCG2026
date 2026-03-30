// File: test_xmltext_parsedeep_193.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLTextParseDeepTest_193 : public ::testing::Test {
protected:
    static XMLText* FirstText(XMLDocument& doc) {
        XMLElement* root = doc.RootElement();
        if (!root) return nullptr;
        return root->FirstChild() ? root->FirstChild()->ToText() : nullptr;
    }
};

TEST_F(XMLTextParseDeepTest_193, ParsesNormalTextNode_193) {
    XMLDocument doc;
    ASSERT_EQ(XML_SUCCESS, doc.Parse("<root>Hello</root>"));
    ASSERT_FALSE(doc.Error());

    XMLText* text = FirstText(doc);
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("Hello", text->Value());
}

TEST_F(XMLTextParseDeepTest_193, ParsesCDataTextNode_193) {
    XMLDocument doc;
    ASSERT_EQ(XML_SUCCESS, doc.Parse("<root><![CDATA[1<2&3]]></root>"));
    ASSERT_FALSE(doc.Error());

    XMLText* text = FirstText(doc);
    ASSERT_NE(nullptr, text);

    // CDATA content should be preserved verbatim.
    EXPECT_STREQ("1<2&3", text->Value());
    EXPECT_TRUE(text->CData());
}

TEST_F(XMLTextParseDeepTest_193, ParsesEntitiesWhenProcessEntitiesOn_193) {
    XMLDocument doc;
    // Default in tinyxml2 is typically to process entities; explicitly set to be clear.
    doc.SetProcessEntities(true);

    ASSERT_EQ(XML_SUCCESS, doc.Parse("<root>Tom &amp; Jerry</root>"));
    ASSERT_FALSE(doc.Error());

    XMLText* text = FirstText(doc);
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("Tom & Jerry", text->Value());
}

TEST_F(XMLTextParseDeepTest_193, LeavesEntitiesWhenProcessEntitiesOff_193) {
    XMLDocument doc;
    doc.SetProcessEntities(false);

    ASSERT_EQ(XML_SUCCESS, doc.Parse("<root>Tom &amp; Jerry</root>"));
    ASSERT_FALSE(doc.Error());

    XMLText* text = FirstText(doc);
    ASSERT_NE(nullptr, text);

    // When entities are not processed, they should be left in the text.
    EXPECT_STREQ("Tom &amp; Jerry", text->Value());
}

TEST_F(XMLTextParseDeepTest_193, CollapsesWhitespaceWhenWhitespaceModeCollapse_193) {
    XMLDocument doc;
    doc.SetWhitespaceMode(COLLAPSE_WHITESPACE);

    ASSERT_EQ(XML_SUCCESS, doc.Parse("<root>  a \n\t b  </root>"));
    ASSERT_FALSE(doc.Error());

    XMLText* text = FirstText(doc);
    ASSERT_NE(nullptr, text);

    // With COLLAPSE_WHITESPACE, sequences of whitespace are expected to collapse.
    EXPECT_STREQ("a b", text->Value());
}

TEST_F(XMLTextParseDeepTest_193, UnterminatedCDataSetsParsingCDataError_193) {
    XMLDocument doc;

    // Missing "]]>" terminator for CDATA.
    doc.Parse("<root><![CDATA[unterminated</root>");
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(XML_ERROR_PARSING_CDATA, doc.ErrorID());
}

TEST_F(XMLTextParseDeepTest_193, InvalidUtf8InTextReportsAnError_193) {
    XMLDocument doc;

    // Create a buffer containing invalid UTF-8 sequence: 0xC3 0x28
    // (0xC3 expects a continuation byte, but 0x28 is not one).
    const char xml[] = "<root>\xC3\x28</root>";

    doc.Parse(xml);
    EXPECT_TRUE(doc.Error());

    // Different tinyxml2 builds/configurations may report different specific parsing errors
    // for invalid character data; assert it is some error rather than overfitting.
    EXPECT_NE(XML_SUCCESS, doc.ErrorID());
}
