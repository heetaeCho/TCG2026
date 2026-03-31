#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryDoubleTextTest_249 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test: QueryDoubleText returns XML_SUCCESS for a valid double text
TEST_F(QueryDoubleTextTest_249, ValidDoubleText_249) {
    doc.Parse("<root>3.14159</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(dval, 3.14159);
}

// Test: QueryDoubleText returns XML_SUCCESS for an integer text (convertible to double)
TEST_F(QueryDoubleTextTest_249, IntegerText_249) {
    doc.Parse("<root>42</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(dval, 42.0);
}

// Test: QueryDoubleText returns XML_SUCCESS for negative double text
TEST_F(QueryDoubleTextTest_249, NegativeDoubleText_249) {
    doc.Parse("<root>-2.718</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(dval, -2.718);
}

// Test: QueryDoubleText returns XML_SUCCESS for zero
TEST_F(QueryDoubleTextTest_249, ZeroText_249) {
    doc.Parse("<root>0</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = -1.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(dval, 0.0);
}

// Test: QueryDoubleText returns XML_SUCCESS for scientific notation
TEST_F(QueryDoubleTextTest_249, ScientificNotationText_249) {
    doc.Parse("<root>1.5e10</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(dval, 1.5e10);
}

// Test: QueryDoubleText returns XML_CAN_NOT_CONVERT_TEXT for non-numeric text
TEST_F(QueryDoubleTextTest_249, NonNumericText_249) {
    doc.Parse("<root>hello</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: QueryDoubleText returns XML_NO_TEXT_NODE for an element with no children
TEST_F(QueryDoubleTextTest_249, EmptyElement_249) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_NO_TEXT_NODE);
}

// Test: QueryDoubleText returns XML_NO_TEXT_NODE for element with only child elements (no text)
TEST_F(QueryDoubleTextTest_249, ChildElementInsteadOfText_249) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_NO_TEXT_NODE);
}

// Test: QueryDoubleText returns XML_SUCCESS for very small double
TEST_F(QueryDoubleTextTest_249, VerySmallDouble_249) {
    doc.Parse("<root>0.000000001</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(dval, 0.000000001);
}

// Test: QueryDoubleText returns XML_SUCCESS for very large double
TEST_F(QueryDoubleTextTest_249, VeryLargeDouble_249) {
    doc.Parse("<root>1.7976931348623157e+308</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(dval, 1.7976931348623157e+308);
}

// Test: QueryDoubleText returns XML_CAN_NOT_CONVERT_TEXT for empty text node
TEST_F(QueryDoubleTextTest_249, EmptyTextContent_249) {
    doc.Parse("<root></root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    // Empty element with no actual text content - depends on whether parser creates a text node
    // For "<root></root>", typically no text child is created
    EXPECT_EQ(result, XML_NO_TEXT_NODE);
}

// Test: QueryDoubleText with negative scientific notation
TEST_F(QueryDoubleTextTest_249, NegativeScientificNotation_249) {
    doc.Parse("<root>-3.5e-4</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(dval, -3.5e-4);
}

// Test: QueryDoubleText returns XML_CAN_NOT_CONVERT_TEXT for mixed text
TEST_F(QueryDoubleTextTest_249, MixedAlphaNumericText_249) {
    doc.Parse("<root>12abc</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    // "12abc" is not a valid double, so it should fail to convert
    EXPECT_EQ(result, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: QueryDoubleText with zero in decimal form
TEST_F(QueryDoubleTextTest_249, ZeroDecimalText_249) {
    doc.Parse("<root>0.0</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = -1.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(dval, 0.0);
}

// Test: QueryDoubleText with whitespace-only text
TEST_F(QueryDoubleTextTest_249, WhitespaceOnlyText_249) {
    // When whitespace mode preserves whitespace, the text node has just spaces
    doc.Parse("<root>   </root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    // Whitespace-only text likely can't convert to double
    // It might be XML_NO_TEXT_NODE or XML_CAN_NOT_CONVERT_TEXT depending on parser behavior
    EXPECT_TRUE(result == XML_CAN_NOT_CONVERT_TEXT || result == XML_NO_TEXT_NODE);
}

// Test: QueryDoubleText with positive sign prefix
TEST_F(QueryDoubleTextTest_249, PositiveSignPrefix_249) {
    doc.Parse("<root>+5.5</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    // Depending on implementation, +5.5 may or may not be valid
    if (result == XML_SUCCESS) {
        EXPECT_DOUBLE_EQ(dval, 5.5);
    } else {
        EXPECT_EQ(result, XML_CAN_NOT_CONVERT_TEXT);
    }
}

// Test: SetText with double then QueryDoubleText
TEST_F(QueryDoubleTextTest_249, SetTextThenQueryDoubleText_249) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    root->SetText(99.99);

    double dval = 0.0;
    XMLError result = root->QueryDoubleText(&dval);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_NEAR(dval, 99.99, 0.001);
}
