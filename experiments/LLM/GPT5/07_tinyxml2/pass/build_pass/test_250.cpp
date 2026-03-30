// TEST_ID: 250
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class QueryFloatTextTest_250 : public ::testing::Test {
protected:
    // Helper: parse XML and return the first element with the given name.
    // (Keeps tests focused on the public interface behavior.)
    static XMLElement* ParseAndGet(XMLDocument& doc, const char* xml, const char* elementName) {
        EXPECT_EQ(doc.Parse(xml), XML_SUCCESS);
        XMLElement* root = doc.RootElement();
        EXPECT_NE(root, nullptr);
        if (!root) return nullptr;

        if (strcmp(root->Name(), elementName) == 0) {
            return root;
        }
        return root->FirstChildElement(elementName);
    }
};

TEST_F(QueryFloatTextTest_250, ParsesValidFloatText_250) {
    XMLDocument doc;
    XMLElement* elem = ParseAndGet(doc, "<root>1.25</root>", "root");
    ASSERT_NE(elem, nullptr);

    float v = 0.0f;
    const XMLError err = elem->QueryFloatText(&v);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(v, 1.25f);
}

TEST_F(QueryFloatTextTest_250, ParsesNegativeFloatText_250) {
    XMLDocument doc;
    XMLElement* elem = ParseAndGet(doc, "<root>-2.5</root>", "root");
    ASSERT_NE(elem, nullptr);

    float v = 0.0f;
    const XMLError err = elem->QueryFloatText(&v);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(v, -2.5f);
}

TEST_F(QueryFloatTextTest_250, ReturnsNoTextNodeWhenElementIsEmpty_250) {
    XMLDocument doc;
    XMLElement* elem = ParseAndGet(doc, "<root/>", "root");
    ASSERT_NE(elem, nullptr);

    float v = 123.0f;
    const XMLError err = elem->QueryFloatText(&v);

    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

TEST_F(QueryFloatTextTest_250, ReturnsNoTextNodeWhenFirstChildIsElement_250) {
    // First child is an element, not a text node.
    XMLDocument doc;
    XMLElement* elem = ParseAndGet(doc, "<root><child/></root>", "root");
    ASSERT_NE(elem, nullptr);

    float v = 123.0f;
    const XMLError err = elem->QueryFloatText(&v);

    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

TEST_F(QueryFloatTextTest_250, ReturnsCannotConvertTextForNonNumericText_250) {
    XMLDocument doc;
    XMLElement* elem = ParseAndGet(doc, "<root>not_a_number</root>", "root");
    ASSERT_NE(elem, nullptr);

    float v = 0.0f;
    const XMLError err = elem->QueryFloatText(&v);

    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

TEST_F(QueryFloatTextTest_250, ReturnsCannotConvertTextForEmptyTextNode_250) {
    // Element has a text node, but it is empty.
    XMLDocument doc;
    XMLElement* elem = ParseAndGet(doc, "<root></root>", "root");
    ASSERT_NE(elem, nullptr);

    float v = 0.0f;
    const XMLError err = elem->QueryFloatText(&v);

    // Observable error behavior: empty text should not convert to a float.
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}
