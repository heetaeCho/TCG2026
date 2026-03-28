#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryUnsigned64TextTest_247 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test: Valid unsigned 64-bit integer text returns XML_SUCCESS
TEST_F(QueryUnsigned64TextTest_247, ValidUnsigned64Text_247) {
    doc.Parse("<root>12345</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 12345ULL);
}

// Test: Zero value returns XML_SUCCESS
TEST_F(QueryUnsigned64TextTest_247, ZeroValue_247) {
    doc.Parse("<root>0</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 999;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 0ULL);
}

// Test: Large uint64 value near max returns XML_SUCCESS
TEST_F(QueryUnsigned64TextTest_247, LargeUnsigned64Value_247) {
    doc.Parse("<root>18446744073709551615</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, UINT64_MAX);
}

// Test: Empty element with no text node returns XML_NO_TEXT_NODE
TEST_F(QueryUnsigned64TextTest_247, NoTextNode_247) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Self-closing element with no text returns XML_NO_TEXT_NODE
TEST_F(QueryUnsigned64TextTest_247, SelfClosingElement_247) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Non-numeric text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryUnsigned64TextTest_247, NonNumericText_247) {
    doc.Parse("<root>hello</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Negative number text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryUnsigned64TextTest_247, NegativeNumberText_247) {
    doc.Parse("<root>-1</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    // Negative numbers should fail for unsigned conversion
    EXPECT_NE(err, XML_SUCCESS);
}

// Test: Floating point text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryUnsigned64TextTest_247, FloatingPointText_247) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Text with only whitespace content
TEST_F(QueryUnsigned64TextTest_247, WhitespaceOnlyText_247) {
    doc.Parse("<root>   </root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    // Whitespace-only text cannot be converted to a number
    EXPECT_NE(err, XML_SUCCESS);
}

// Test: Element with child element instead of text node returns XML_NO_TEXT_NODE
TEST_F(QueryUnsigned64TextTest_247, ChildElementInsteadOfText_247) {
    doc.Parse("<root><child>42</child></root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Valid number with leading/trailing spaces
TEST_F(QueryUnsigned64TextTest_247, NumberWithSpaces_247) {
    doc.Parse("<root> 42 </root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    // Depending on implementation, spaces may or may not be trimmed
    // We just verify it doesn't crash and returns a valid error code
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Value of 1 returns XML_SUCCESS
TEST_F(QueryUnsigned64TextTest_247, ValueOfOne_247) {
    doc.Parse("<root>1</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 1ULL);
}

// Test: Mixed alphanumeric text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryUnsigned64TextTest_247, MixedAlphanumericText_247) {
    doc.Parse("<root>123abc</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Moderately large number
TEST_F(QueryUnsigned64TextTest_247, ModerateLargeNumber_247) {
    doc.Parse("<root>9999999999</root>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 9999999999ULL);
}

// Test: Empty string text
TEST_F(QueryUnsigned64TextTest_247, EmptyStringInTextNode_247) {
    // This creates an element with text content that's empty
    XMLDocument doc2;
    doc2.Parse("<root></root>");
    XMLElement* elem = doc2.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);
    // Add empty text
    elem->SetText("");

    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    // Empty string can't be converted
    EXPECT_NE(err, XML_NO_TEXT_NODE);
    // It should have a text node but can't convert
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: SetText with uint64 then QueryUnsigned64Text roundtrip
TEST_F(QueryUnsigned64TextTest_247, SetTextAndQueryRoundtrip_247) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.FirstChildElement("root");
    ASSERT_NE(elem, nullptr);

    uint64_t original = 1234567890123456789ULL;
    elem->SetText(original);

    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Text(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, original);
}
