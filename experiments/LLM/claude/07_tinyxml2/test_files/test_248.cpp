#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryBoolTextTest_248 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test: QueryBoolText returns XML_SUCCESS and sets bval to true for "true"
TEST_F(QueryBoolTextTest_248, ReturnsTrueForTrueText_248) {
    doc.Parse("<element>true</element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool bval = false;
    XMLError err = elem->QueryBoolText(&bval);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(bval);
}

// Test: QueryBoolText returns XML_SUCCESS and sets bval to false for "false"
TEST_F(QueryBoolTextTest_248, ReturnsFalseForFalseText_248) {
    doc.Parse("<element>false</element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool bval = true;
    XMLError err = elem->QueryBoolText(&bval);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(bval);
}

// Test: QueryBoolText returns XML_SUCCESS for "1" (treated as true)
TEST_F(QueryBoolTextTest_248, ReturnsTrueForOneText_248) {
    doc.Parse("<element>1</element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool bval = false;
    XMLError err = elem->QueryBoolText(&bval);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(bval);
}

// Test: QueryBoolText returns XML_SUCCESS for "0" (treated as false)
TEST_F(QueryBoolTextTest_248, ReturnsFalseForZeroText_248) {
    doc.Parse("<element>0</element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool bval = true;
    XMLError err = elem->QueryBoolText(&bval);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(bval);
}

// Test: QueryBoolText returns XML_CAN_NOT_CONVERT_TEXT for non-boolean text
TEST_F(QueryBoolTextTest_248, ReturnsCanNotConvertForNonBoolText_248) {
    doc.Parse("<element>notabool</element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool bval = false;
    XMLError err = elem->QueryBoolText(&bval);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: QueryBoolText returns XML_NO_TEXT_NODE for empty element
TEST_F(QueryBoolTextTest_248, ReturnsNoTextNodeForEmptyElement_248) {
    doc.Parse("<element></element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool bval = false;
    XMLError err = elem->QueryBoolText(&bval);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: QueryBoolText returns XML_NO_TEXT_NODE for self-closing element
TEST_F(QueryBoolTextTest_248, ReturnsNoTextNodeForSelfClosingElement_248) {
    doc.Parse("<element/>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool bval = false;
    XMLError err = elem->QueryBoolText(&bval);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: QueryBoolText returns XML_NO_TEXT_NODE when first child is not text (e.g., child element)
TEST_F(QueryBoolTextTest_248, ReturnsNoTextNodeWhenFirstChildIsElement_248) {
    doc.Parse("<element><child/></element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool bval = false;
    XMLError err = elem->QueryBoolText(&bval);
    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

// Test: QueryBoolText returns XML_CAN_NOT_CONVERT_TEXT for numeric non-bool text
TEST_F(QueryBoolTextTest_248, ReturnsCanNotConvertForNumericNonBoolText_248) {
    doc.Parse("<element>42</element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool bval = false;
    XMLError err = elem->QueryBoolText(&bval);
    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

// Test: QueryBoolText handles "True" (case variation)
TEST_F(QueryBoolTextTest_248, HandlesCaseVariationTrue_248) {
    doc.Parse("<element>True</element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool bval = false;
    XMLError err = elem->QueryBoolText(&bval);
    // Depending on implementation, it may or may not handle case-insensitive
    // We just verify it returns a valid XMLError
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_CAN_NOT_CONVERT_TEXT);
}

// Test: QueryBoolText handles "FALSE" (uppercase)
TEST_F(QueryBoolTextTest_248, HandlesCaseVariationFALSE_248) {
    doc.Parse("<element>FALSE</element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool bval = true;
    XMLError err = elem->QueryBoolText(&bval);
    // Depending on implementation, may or may not handle case-insensitive
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_CAN_NOT_CONVERT_TEXT);
}

// Test: QueryBoolText with empty string text node
TEST_F(QueryBoolTextTest_248, ReturnsCanNotConvertForEmptyStringText_248) {
    // An element with whitespace-only text content
    doc.Parse("<element> </element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool bval = false;
    XMLError err = elem->QueryBoolText(&bval);
    // It should either have no text node or fail to convert
    EXPECT_TRUE(err == XML_CAN_NOT_CONVERT_TEXT || err == XML_NO_TEXT_NODE);
}

// Test: Using BoolText with default value on empty element
TEST_F(QueryBoolTextTest_248, BoolTextReturnsDefaultForEmptyElement_248) {
    doc.Parse("<element/>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool result = elem->BoolText(true);
    EXPECT_TRUE(result);

    result = elem->BoolText(false);
    EXPECT_FALSE(result);
}

// Test: Using BoolText with default value on valid bool text
TEST_F(QueryBoolTextTest_248, BoolTextReturnsValueForValidBoolText_248) {
    doc.Parse("<element>true</element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool result = elem->BoolText(false);
    EXPECT_TRUE(result);
}

// Test: Using BoolText with default value on non-convertible text
TEST_F(QueryBoolTextTest_248, BoolTextReturnsDefaultForNonConvertibleText_248) {
    doc.Parse("<element>hello</element>");
    XMLElement* elem = doc.FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    bool result = elem->BoolText(true);
    EXPECT_TRUE(result);

    result = elem->BoolText(false);
    EXPECT_FALSE(result);
}

// Test: SetText(bool) followed by QueryBoolText
TEST_F(QueryBoolTextTest_248, SetTextBoolThenQueryBoolText_248) {
    doc.Parse("<root><element/></root>");
    XMLElement* elem = doc.FirstChildElement("root")->FirstChildElement("element");
    ASSERT_NE(elem, nullptr);

    elem->SetText(true);
    bool bval = false;
    XMLError err = elem->QueryBoolText(&bval);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(bval);

    elem->SetText(false);
    bval = true;
    err = elem->QueryBoolText(&bval);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(bval);
}
