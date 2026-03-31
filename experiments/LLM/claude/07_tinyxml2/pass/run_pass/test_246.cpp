#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryInt64TextTest_246 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test: Normal positive integer text returns XML_SUCCESS and correct value
TEST_F(QueryInt64TextTest_246, PositiveIntegerText_246) {
    doc.Parse("<root>12345</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 0;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 12345);
}

// Test: Normal negative integer text returns XML_SUCCESS and correct value
TEST_F(QueryInt64TextTest_246, NegativeIntegerText_246) {
    doc.Parse("<root>-98765</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 0;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, -98765);
}

// Test: Zero text returns XML_SUCCESS and zero value
TEST_F(QueryInt64TextTest_246, ZeroText_246) {
    doc.Parse("<root>0</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = -1;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 0);
}

// Test: Large positive int64 value near max
TEST_F(QueryInt64TextTest_246, LargePositiveInt64_246) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 0;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, INT64_MAX);
}

// Test: Large negative int64 value near min
TEST_F(QueryInt64TextTest_246, LargeNegativeInt64_246) {
    doc.Parse("<root>-9223372036854775808</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 0;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, INT64_MIN);
}

// Test: Empty element (no text node) returns XML_NO_TEXT_NODE
TEST_F(QueryInt64TextTest_246, EmptyElement_246) {
    doc.Parse("<root></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 42;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Self-closing element (no text node) returns XML_NO_TEXT_NODE
TEST_F(QueryInt64TextTest_246, SelfClosingElement_246) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 42;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Non-numeric text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryInt64TextTest_246, NonNumericText_246) {
    doc.Parse("<root>hello</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 42;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Floating point text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryInt64TextTest_246, FloatingPointText_246) {
    doc.Parse("<root>3.14</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 42;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Element with only child element (no text node) returns XML_NO_TEXT_NODE
TEST_F(QueryInt64TextTest_246, ChildElementInsteadOfText_246) {
    doc.Parse("<root><child>123</child></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 42;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Text with whitespace around number (checking if conversion handles it)
TEST_F(QueryInt64TextTest_246, TextWithWhitespace_246) {
    doc.Parse("<root>  42  </root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 0;
    XMLError err = root->QueryInt64Text(&val);
    // The behavior depends on XMLUtil::ToInt64 handling of whitespace
    // It should either succeed or fail to convert
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Text with mixed content (number followed by text)
TEST_F(QueryInt64TextTest_246, MixedContent_246) {
    doc.Parse("<root>123abc</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 0;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Empty string text returns XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryInt64TextTest_246, WhitespaceOnlyPreserved_246) {
    // An element with just whitespace might be treated as text or not
    doc.Parse("<root> </root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 0;
    XMLError err = root->QueryInt64Text(&val);
    // Whitespace-only text should fail conversion
    EXPECT_TRUE(err == XML_CAN_NOT_CONVERT_TEXT || err == XML_NO_TEXT_NODE);
}

// Test: Value of 1 (single digit)
TEST_F(QueryInt64TextTest_246, SingleDigit_246) {
    doc.Parse("<root>7</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 0;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 7);
}

// Test: Negative single digit
TEST_F(QueryInt64TextTest_246, NegativeSingleDigit_246) {
    doc.Parse("<root>-1</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    int64_t val = 0;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, -1);
}

// Test: Using SetText with int64 and then querying
TEST_F(QueryInt64TextTest_246, SetTextThenQuery_246) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    root->SetText(static_cast<int64_t>(999999999999LL));
    
    int64_t val = 0;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 999999999999LL);
}
