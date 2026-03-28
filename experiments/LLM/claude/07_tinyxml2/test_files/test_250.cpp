#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryFloatTextTest_250 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test: Normal float value in element text
TEST_F(QueryFloatTextTest_250, ValidFloatText_ReturnsSuccess_250) {
    doc.Parse("<root>3.14</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 3.14f);
}

// Test: Integer value in element text (should be convertible to float)
TEST_F(QueryFloatTextTest_250, IntegerTextAsFloat_ReturnsSuccess_250) {
    doc.Parse("<root>42</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 42.0f);
}

// Test: Negative float value
TEST_F(QueryFloatTextTest_250, NegativeFloatText_ReturnsSuccess_250) {
    doc.Parse("<root>-2.718</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, -2.718f);
}

// Test: Zero value
TEST_F(QueryFloatTextTest_250, ZeroFloatText_ReturnsSuccess_250) {
    doc.Parse("<root>0.0</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = -1.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 0.0f);
}

// Test: Non-numeric text should return XML_CAN_NOT_CONVERT_TEXT
TEST_F(QueryFloatTextTest_250, NonNumericText_ReturnsCanNotConvert_250) {
    doc.Parse("<root>hello</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Empty element (no text node) should return XML_NO_TEXT_NODE
TEST_F(QueryFloatTextTest_250, EmptyElement_ReturnsNoTextNode_250) {
    doc.Parse("<root></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Self-closing element (no children) should return XML_NO_TEXT_NODE
TEST_F(QueryFloatTextTest_250, SelfClosingElement_ReturnsNoTextNode_250) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Element with only child element (no text node first child)
TEST_F(QueryFloatTextTest_250, ChildElementOnly_ReturnsNoTextNode_250) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Very large float value
TEST_F(QueryFloatTextTest_250, LargeFloatValue_ReturnsSuccess_250) {
    doc.Parse("<root>1.0e+30</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 1.0e+30f);
}

// Test: Very small float value
TEST_F(QueryFloatTextTest_250, SmallFloatValue_ReturnsSuccess_250) {
    doc.Parse("<root>1.0e-30</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 1.0e-30f);
}

// Test: Text with whitespace around number
TEST_F(QueryFloatTextTest_250, WhitespaceAroundNumber_250) {
    doc.Parse("<root>  5.5  </root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    // The behavior may vary; we just check it doesn't crash and returns a valid error code
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Text containing only whitespace
TEST_F(QueryFloatTextTest_250, WhitespaceOnlyText_250) {
    // When text is only whitespace, tinyxml2 may treat it differently
    doc.Parse("<root>   </root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    // Could be XML_NO_TEXT_NODE or XML_CAN_NOT_CONVERT_TEXT depending on whitespace handling
    EXPECT_TRUE(err == XML_NO_TEXT_NODE || err == XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Using SetText with float then QueryFloatText
TEST_F(QueryFloatTextTest_250, SetTextThenQuery_ReturnsSuccess_250) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    root->SetText(1.23f);
    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 1.23f, 0.01f);
}

// Test: Mixed content where first child is an element, not text
TEST_F(QueryFloatTextTest_250, FirstChildIsElement_ReturnsNoTextNode_250) {
    doc.Parse("<root><child/>3.14</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    // First child is an element, not text, so should return XML_NO_TEXT_NODE
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: Positive sign float
TEST_F(QueryFloatTextTest_250, PositiveSignFloat_ReturnsSuccess_250) {
    doc.Parse("<root>+7.5</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    // May or may not parse "+7.5" successfully depending on implementation
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_CAN_NOT_CONVERT_TEXT);
    if (err == XML_SUCCESS) {
        EXPECT_FLOAT_EQ(val, 7.5f);
    }
}

// Test: Boolean-like text should fail conversion
TEST_F(QueryFloatTextTest_250, BooleanText_CanNotConvert_250) {
    doc.Parse("<root>true</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: Empty string text
TEST_F(QueryFloatTextTest_250, EmptyStringInText_250) {
    // Force an empty text node by using SetText
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetText("");

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}
