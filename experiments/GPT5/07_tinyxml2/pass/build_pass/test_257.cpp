// TEST_ID: 257
// File: ./TestProjects/tinyxml2/tinyxml2_floattext_test_257.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

XMLElement* ParseSingleElement(XMLDocument& doc, const char* xml) {
    // We assume Parse exists and returns an error code, but we don't depend on its exact enum value here.
    // If parsing fails, RootElement() will be null and the ASSERTs will fail clearly.
    doc.Parse(xml);
    return doc.RootElement();
}

}  // namespace

class FloatTextTest_257 : public ::testing::Test {};

TEST_F(FloatTextTest_257, ReturnsParsedFloatWhenTextIsValid_257) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root>3.5</root>");
    ASSERT_NE(elem, nullptr);

    const float out = elem->FloatText(123.0f);
    EXPECT_FLOAT_EQ(out, 3.5f);
}

TEST_F(FloatTextTest_257, ReturnsDefaultWhenElementHasNoText_257) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root/>");
    ASSERT_NE(elem, nullptr);

    const float def = 7.25f;
    const float out = elem->FloatText(def);
    EXPECT_FLOAT_EQ(out, def);
}

TEST_F(FloatTextTest_257, ReturnsDefaultWhenTextIsEmpty_257) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root></root>");
    ASSERT_NE(elem, nullptr);

    const float def = -1.0f;
    const float out = elem->FloatText(def);
    EXPECT_FLOAT_EQ(out, def);
}

TEST_F(FloatTextTest_257, ReturnsDefaultWhenTextIsNotNumeric_257) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root>not_a_number</root>");
    ASSERT_NE(elem, nullptr);

    const float def = 42.0f;
    const float out = elem->FloatText(def);
    EXPECT_FLOAT_EQ(out, def);
}

TEST_F(FloatTextTest_257, ParsesWithLeadingAndTrailingWhitespace_257) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root> \n\t -2.25 \r\n </root>");
    ASSERT_NE(elem, nullptr);

    const float out = elem->FloatText(0.0f);
    EXPECT_FLOAT_EQ(out, -2.25f);
}

TEST_F(FloatTextTest_257, ParsesScientificNotation_257) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root>1.25e2</root>");
    ASSERT_NE(elem, nullptr);

    const float out = elem->FloatText(0.0f);
    EXPECT_FLOAT_EQ(out, 125.0f);
}

TEST_F(FloatTextTest_257, HandlesPlusSign_257) {
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root>+4.0</root>");
    ASSERT_NE(elem, nullptr);

    const float out = elem->FloatText(-9.0f);
    EXPECT_FLOAT_EQ(out, 4.0f);
}

TEST_F(FloatTextTest_257, ReturnsDefaultForChildTextWhenRootHasNoDirectText_257) {
    // Root element has a child text node, but no direct text content as a single text value.
    // This checks an error-ish/boundary scenario via the public interface only.
    XMLDocument doc;
    XMLElement* elem = ParseSingleElement(doc, "<root><child>5</child></root>");
    ASSERT_NE(elem, nullptr);

    const float def = 9.0f;
    const float out = elem->FloatText(def);
    EXPECT_FLOAT_EQ(out, def);
}
