#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryUnsignedTextTest_245 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test: Valid unsigned integer text returns XML_SUCCESS and correct value
TEST_F(QueryUnsignedTextTest_245, ValidUnsignedText_245) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42u);
}

// Test: Zero value text returns XML_SUCCESS
TEST_F(QueryUnsignedTextTest_245, ZeroValueText_245) {
    doc.Parse("<root>0</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 999;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 0u);
}

// Test: Large unsigned value
TEST_F(QueryUnsignedTextTest_245, LargeUnsignedValue_245) {
    doc.Parse("<root>4294967295</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 4294967295u);
}

// Test: Non-numeric text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryUnsignedTextTest_245, NonNumericText_245) {
    doc.Parse("<root>hello</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Empty element (no text node) returns XML_NO_TEXT_NODE
TEST_F(QueryUnsignedTextTest_245, EmptyElement_245) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Self-closing element (no children) returns XML_NO_TEXT_NODE
TEST_F(QueryUnsignedTextTest_245, SelfClosingElement_245) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Element with child element (not text) returns XML_NO_TEXT_NODE
TEST_F(QueryUnsignedTextTest_245, ChildElementInsteadOfText_245) {
    doc.Parse("<root><child>42</child></root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Negative number text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryUnsignedTextTest_245, NegativeNumberText_245) {
    doc.Parse("<root>-1</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Floating point text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryUnsignedTextTest_245, FloatingPointText_245) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Text with leading whitespace (valid unsigned)
TEST_F(QueryUnsignedTextTest_245, TextWithWhitespace_245) {
    doc.Parse("<root>  123  </root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    // The behavior depends on XMLUtil::ToUnsigned handling of whitespace
    // We just check that the function returns a valid XMLError
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Text with mixed alphanumeric content
TEST_F(QueryUnsignedTextTest_245, MixedAlphanumericText_245) {
    doc.Parse("<root>123abc</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Single digit value
TEST_F(QueryUnsignedTextTest_245, SingleDigitValue_245) {
    doc.Parse("<root>7</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 7u);
}

// Test: Value 1
TEST_F(QueryUnsignedTextTest_245, ValueOne_245) {
    doc.Parse("<root>1</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 1u);
}

// Test: Using SetText then QueryUnsignedText roundtrip
TEST_F(QueryUnsignedTextTest_245, SetTextRoundTrip_245) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    elem->SetText(12345u);
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 12345u);
}

// Test: Empty string text
TEST_F(QueryUnsignedTextTest_245, EmptyStringText_245) {
    // An element with explicitly empty text content
    doc.Parse("<root> </root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    // Whitespace-only text node: ToUnsigned likely fails
    EXPECT_TRUE(err == XML_CAN_NOT_CONVERT_TEXT || err == XML_NO_TEXT_NODE);
}
