// File: ./TestProjects/tinyxml2/xmltext_shallowequal_test_195.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLTextShallowEqualTest_195 : public ::testing::Test {
protected:
    // Parses XML and returns the first text node under the document's root element.
    // Returns nullptr if parsing fails or the structure doesn't match expectations.
    static XMLText* FirstRootText(XMLDocument& doc, const char* xml) {
        if (doc.Parse(xml) != XML_SUCCESS) {
            return nullptr;
        }
        XMLElement* root = doc.RootElement();
        if (!root) {
            return nullptr;
        }
        return root->FirstChild() ? root->FirstChild()->ToText() : nullptr;
    }

    // Parses XML and returns the first child node under the document's root element.
    static XMLNode* FirstRootChild(XMLDocument& doc, const char* xml) {
        if (doc.Parse(xml) != XML_SUCCESS) {
            return nullptr;
        }
        XMLElement* root = doc.RootElement();
        if (!root) {
            return nullptr;
        }
        return root->FirstChild();
    }
};

}  // namespace

TEST_F(XMLTextShallowEqualTest_195, SameTextValue_ReturnsTrue_195) {
    XMLDocument docA;
    XMLDocument docB;

    XMLText* textA = FirstRootText(docA, "<root>hello</root>");
    XMLText* textB = FirstRootText(docB, "<root>hello</root>");

    ASSERT_NE(textA, nullptr);
    ASSERT_NE(textB, nullptr);

    EXPECT_TRUE(textA->ShallowEqual(textB));
    EXPECT_TRUE(textB->ShallowEqual(textA));
}

TEST_F(XMLTextShallowEqualTest_195, DifferentTextValue_ReturnsFalse_195) {
    XMLDocument docA;
    XMLDocument docB;

    XMLText* textA = FirstRootText(docA, "<root>hello</root>");
    XMLText* textB = FirstRootText(docB, "<root>world</root>");

    ASSERT_NE(textA, nullptr);
    ASSERT_NE(textB, nullptr);

    EXPECT_FALSE(textA->ShallowEqual(textB));
    EXPECT_FALSE(textB->ShallowEqual(textA));
}

TEST_F(XMLTextShallowEqualTest_195, CaseDifference_IsNotEqual_195) {
    XMLDocument docA;
    XMLDocument docB;

    XMLText* textA = FirstRootText(docA, "<root>Hello</root>");
    XMLText* textB = FirstRootText(docB, "<root>hello</root>");

    ASSERT_NE(textA, nullptr);
    ASSERT_NE(textB, nullptr);

    EXPECT_FALSE(textA->ShallowEqual(textB));
}

TEST_F(XMLTextShallowEqualTest_195, CompareIsNotTextNode_ReturnsFalse_195) {
    XMLDocument docText;
    XMLDocument docElem;

    XMLText* text = FirstRootText(docText, "<root>hello</root>");
    ASSERT_NE(text, nullptr);

    XMLNode* childElem = FirstRootChild(docElem, "<root><child/></root>");
    ASSERT_NE(childElem, nullptr);
    ASSERT_EQ(childElem->ToText(), nullptr);  // Sanity: it's not a text node.

    EXPECT_FALSE(text->ShallowEqual(childElem));
}

TEST_F(XMLTextShallowEqualTest_195, EmptyTextComparedToEmptyText_ReturnsTrue_195) {
    // Use explicit empty text node under root element: <root></root> has no child text node in many parsers,
    // so use a self-contained empty text via entity that produces empty content, or whitespace-only and then
    // normalize by using exact same source.
    //
    // Here we use an empty string value represented as <![CDATA[]]> which should create a text node with empty value
    // in typical tinyxml2 behavior. If the parser doesn't create a text node, the test will fail early (by design).
    XMLDocument docA;
    XMLDocument docB;

    XMLText* textA = FirstRootText(docA, "<root><![CDATA[]]></root>");
    XMLText* textB = FirstRootText(docB, "<root><![CDATA[]]></root>");

    ASSERT_NE(textA, nullptr);
    ASSERT_NE(textB, nullptr);

    EXPECT_TRUE(textA->ShallowEqual(textB));
}

TEST_F(XMLTextShallowEqualTest_195, WhitespaceTextComparedToDifferentWhitespace_ReturnsFalse_195) {
    XMLDocument docA;
    XMLDocument docB;

    XMLText* textA = FirstRootText(docA, "<root> </root>");    // one space
    XMLText* textB = FirstRootText(docB, "<root>\n</root>");   // newline

    ASSERT_NE(textA, nullptr);
    ASSERT_NE(textB, nullptr);

    // ShallowEqual uses string equality on Value(), so different whitespace should not match.
    EXPECT_FALSE(textA->ShallowEqual(textB));
}

TEST_F(XMLTextShallowEqualTest_195, NullCompare_TriggersAssertOrDeath_195) {
    XMLDocument doc;
    XMLText* text = FirstRootText(doc, "<root>hello</root>");
    ASSERT_NE(text, nullptr);

    // The implementation contains TIXMLASSERT(compare).
    // In builds where assertions are enabled, this should crash/abort; otherwise behavior may be undefined.
    EXPECT_DEATH_IF_SUPPORTED(
        {
            (void)text->ShallowEqual(nullptr);
        },
        ".*"
    );
}
