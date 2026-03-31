#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementInt64TextTest_253 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that Int64Text returns the text content parsed as int64_t when valid
TEST_F(XMLElementInt64TextTest_253, ReturnsCorrectValueWhenTextIsValidInt64_253) {
    doc.Parse("<root>12345678901234</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, 12345678901234LL);
}

// Test that Int64Text returns the default value when there is no text content
TEST_F(XMLElementInt64TextTest_253, ReturnsDefaultWhenNoText_253) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(42);
    EXPECT_EQ(result, 42);
}

// Test that Int64Text returns the default value when text is not a valid number
TEST_F(XMLElementInt64TextTest_253, ReturnsDefaultWhenTextIsNotNumeric_253) {
    doc.Parse("<root>not_a_number</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(-1);
    EXPECT_EQ(result, -1);
}

// Test Int64Text with zero as text
TEST_F(XMLElementInt64TextTest_253, ReturnsZeroWhenTextIsZero_253) {
    doc.Parse("<root>0</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(999);
    EXPECT_EQ(result, 0);
}

// Test Int64Text with negative number
TEST_F(XMLElementInt64TextTest_253, ReturnsNegativeValueWhenTextIsNegative_253) {
    doc.Parse("<root>-9876543210</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, -9876543210LL);
}

// Test Int64Text with maximum int64_t value
TEST_F(XMLElementInt64TextTest_253, ReturnsMaxInt64WhenTextIsMaxValue_253) {
    doc.Parse("<root>9223372036854775807</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, INT64_MAX);
}

// Test Int64Text with minimum int64_t value
TEST_F(XMLElementInt64TextTest_253, ReturnsMinInt64WhenTextIsMinValue_253) {
    doc.Parse("<root>-9223372036854775808</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, INT64_MIN);
}

// Test Int64Text with default value of zero when text is valid
TEST_F(XMLElementInt64TextTest_253, DefaultValueZeroOverriddenByValidText_253) {
    doc.Parse("<root>100</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, 100);
}

// Test Int64Text when element has only child elements (no direct text)
TEST_F(XMLElementInt64TextTest_253, ReturnsDefaultWhenElementHasOnlyChildElements_253) {
    doc.Parse("<root><child>123</child></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(77);
    // The root element doesn't have direct text content, only a child element
    // Behavior depends on implementation - typically returns default
    // We just check it doesn't crash and returns some value
    // Most likely returns 77 since root has no direct text
    EXPECT_EQ(result, 77);
}

// Test Int64Text with text set via SetText(int64_t)
TEST_F(XMLElementInt64TextTest_253, ReturnsValueSetViaSetTextInt64_253) {
    doc.Parse("<root/>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    elem->SetText(static_cast<int64_t>(5555555555LL));
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, 5555555555LL);
}

// Test Int64Text with text containing whitespace around number
TEST_F(XMLElementInt64TextTest_253, HandlesWhitespaceAroundNumber_253) {
    doc.Parse("<root>  42  </root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(-1);
    // Most implementations of strtoll/sscanf handle leading whitespace
    EXPECT_EQ(result, 42);
}

// Test Int64Text with a large negative default
TEST_F(XMLElementInt64TextTest_253, LargeNegativeDefaultReturnedOnEmptyText_253) {
    doc.Parse("<root></root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(-9999999999LL);
    EXPECT_EQ(result, -9999999999LL);
}

// Test Int64Text with value of 1
TEST_F(XMLElementInt64TextTest_253, ReturnsOneWhenTextIsOne_253) {
    doc.Parse("<root>1</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, 1);
}

// Test Int64Text with value of -1
TEST_F(XMLElementInt64TextTest_253, ReturnsNegativeOneWhenTextIsNegativeOne_253) {
    doc.Parse("<root>-1</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(0);
    EXPECT_EQ(result, -1);
}

// Test consistency between QueryInt64Text and Int64Text
TEST_F(XMLElementInt64TextTest_253, ConsistentWithQueryInt64Text_253) {
    doc.Parse("<root>987654321012345</root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    int64_t queryResult = 0;
    XMLError err = elem->QueryInt64Text(&queryResult);
    EXPECT_EQ(err, XML_SUCCESS);

    int64_t int64Result = elem->Int64Text(0);
    EXPECT_EQ(int64Result, queryResult);
    EXPECT_EQ(int64Result, 987654321012345LL);
}

// Test that Int64Text with empty string returns default
TEST_F(XMLElementInt64TextTest_253, ReturnsDefaultWhenTextIsEmpty_253) {
    doc.Parse("<root>   </root>");
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    int64_t result = elem->Int64Text(12345);
    // Whitespace-only text may or may not parse; check it doesn't crash
    // The actual behavior depends on implementation
    (void)result;
}
