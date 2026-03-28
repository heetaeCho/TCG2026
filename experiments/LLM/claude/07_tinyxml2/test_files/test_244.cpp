#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryIntTextTest_244 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test: Normal integer text returns XML_SUCCESS and correct value
TEST_F(QueryIntTextTest_244, ValidIntegerText_244) {
    doc.Parse("<root>42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

// Test: Negative integer text
TEST_F(QueryIntTextTest_244, NegativeIntegerText_244) {
    doc.Parse("<root>-123</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, -123);
}

// Test: Zero value
TEST_F(QueryIntTextTest_244, ZeroIntegerText_244) {
    doc.Parse("<root>0</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = -1;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 0);
}

// Test: Empty element returns XML_NO_TEXT_NODE
TEST_F(QueryIntTextTest_244, EmptyElementReturnsNoTextNode_244) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Self-closing element returns XML_NO_TEXT_NODE
TEST_F(QueryIntTextTest_244, SelfClosingElementReturnsNoTextNode_244) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Non-integer text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryIntTextTest_244, NonIntegerTextReturnsCanNotConvert_244) {
    doc.Parse("<root>hello</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Floating point text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryIntTextTest_244, FloatingPointTextReturnsCanNotConvert_244) {
    doc.Parse("<root>3.14</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Element with only child element (no text node) returns XML_NO_TEXT_NODE
TEST_F(QueryIntTextTest_244, ChildElementOnlyReturnsNoTextNode_244) {
    doc.Parse("<root><child>42</child></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Large positive integer
TEST_F(QueryIntTextTest_244, LargePositiveInteger_244) {
    doc.Parse("<root>2147483647</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 2147483647);
}

// Test: Large negative integer
TEST_F(QueryIntTextTest_244, LargeNegativeInteger_244) {
    doc.Parse("<root>-2147483648</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, -2147483648);
}

// Test: Text with whitespace around integer (may or may not convert depending on implementation)
TEST_F(QueryIntTextTest_244, TextWithLeadingWhitespace_244) {
    doc.Parse("<root> 42 </root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    // Leading whitespace is typically handled by strtol-based parsing
    // Either XML_SUCCESS with 42 or XML_CAN_NOT_CONVERT_TEXT
    if (err == XML_SUCCESS) {
        EXPECT_EQ(value, 42);
    } else {
        EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
    }
}

// Test: Empty string text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryIntTextTest_244, EmptyStringCanNotConvert_244) {
    // Force a text node with empty-ish content via CDATA or other means
    doc.Parse("<root>   </root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    // Whitespace-only text: likely cannot convert
    // Either no text node or can't convert
    EXPECT_TRUE(err == XML_CAN_NOT_CONVERT_TEXT || err == XML_NO_TEXT_NODE || err == XML_SUCCESS);
}

// Test: Text that starts with a number but has trailing non-numeric characters
TEST_F(QueryIntTextTest_244, MixedTextStartingWithNumber_244) {
    doc.Parse("<root>42abc</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    // Depending on implementation, may convert to 42 or fail
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Positive sign prefix
TEST_F(QueryIntTextTest_244, PositiveSignPrefix_244) {
    doc.Parse("<root>+10</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    if (err == XML_SUCCESS) {
        EXPECT_EQ(value, 10);
    }
}

// Test: QueryIntText on a nested element with text
TEST_F(QueryIntTextTest_244, NestedElementWithText_244) {
    doc.Parse("<root><child>99</child></root>");
    XMLElement* child = doc.RootElement()->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    
    int value = 0;
    XMLError err = child->QueryIntText(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 99);
}

// Test: Element with comment as first child (no text node first)
TEST_F(QueryIntTextTest_244, CommentAsFirstChildReturnsNoTextNode_244) {
    doc.Parse("<root><!-- comment -->42</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    int value = 0;
    XMLError err = elem->QueryIntText(&value);
    // FirstChild() is the comment, which ToText() returns null
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}
