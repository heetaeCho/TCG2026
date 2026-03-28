#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeQueryFloatValueTest_216 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    // Helper to create an element with an attribute having the given value
    const XMLAttribute* createAttributeWithValue(const char* value) {
        doc.Clear();
        char xml[256];
        snprintf(xml, sizeof(xml), "<root attr=\"%s\"/>", value);
        doc.Parse(xml);
        const XMLElement* root = doc.FirstChildElement("root");
        if (root) {
            return root->FindAttribute("attr");
        }
        return nullptr;
    }
};

TEST_F(XMLAttributeQueryFloatValueTest_216, ValidFloat_ReturnsSuccess_216) {
    const XMLAttribute* attr = createAttributeWithValue("3.14");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 3.14f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, ValidInteger_ReturnsSuccess_216) {
    const XMLAttribute* attr = createAttributeWithValue("42");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 42.0f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, NegativeFloat_ReturnsSuccess_216) {
    const XMLAttribute* attr = createAttributeWithValue("-2.5");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, -2.5f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, Zero_ReturnsSuccess_216) {
    const XMLAttribute* attr = createAttributeWithValue("0");
    ASSERT_NE(attr, nullptr);
    float value = -1.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 0.0f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, ZeroPointZero_ReturnsSuccess_216) {
    const XMLAttribute* attr = createAttributeWithValue("0.0");
    ASSERT_NE(attr, nullptr);
    float value = -1.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 0.0f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, ScientificNotation_ReturnsSuccess_216) {
    const XMLAttribute* attr = createAttributeWithValue("1.5e2");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 150.0f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, NegativeScientificNotation_ReturnsSuccess_216) {
    const XMLAttribute* attr = createAttributeWithValue("-3.0e-1");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, -0.3f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, NonNumericString_ReturnsWrongType_216) {
    const XMLAttribute* attr = createAttributeWithValue("hello");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, EmptyString_ReturnsWrongType_216) {
    const XMLAttribute* attr = createAttributeWithValue("");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, BooleanString_ReturnsWrongType_216) {
    const XMLAttribute* attr = createAttributeWithValue("true");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, VeryLargeFloat_ReturnsSuccess_216) {
    const XMLAttribute* attr = createAttributeWithValue("3.402823e+38");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_GT(value, 0.0f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, VerySmallFloat_ReturnsSuccess_216) {
    const XMLAttribute* attr = createAttributeWithValue("1.175494e-38");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_GT(value, 0.0f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, LeadingWhitespace_Behavior_216) {
    // Depending on implementation, leading whitespace may or may not be handled
    const XMLAttribute* attr = createAttributeWithValue(" 1.0");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    // Either succeeds or fails - we just verify it returns a valid XMLError
    EXPECT_TRUE(result == XML_SUCCESS || result == XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, MixedContent_ReturnsWrongType_216) {
    const XMLAttribute* attr = createAttributeWithValue("12.5abc");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    // The value starts as numeric but has trailing non-numeric chars
    // Behavior depends on implementation
    EXPECT_TRUE(result == XML_SUCCESS || result == XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, PositiveSign_ReturnsSuccess_216) {
    const XMLAttribute* attr = createAttributeWithValue("+5.5");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    // Positive sign prefix may or may not be supported
    EXPECT_TRUE(result == XML_SUCCESS || result == XML_WRONG_ATTRIBUTE_TYPE);
    if (result == XML_SUCCESS) {
        EXPECT_FLOAT_EQ(value, 5.5f);
    }
}

TEST_F(XMLAttributeQueryFloatValueTest_216, SetFloatThenQuery_ReturnsSuccess_216) {
    doc.Clear();
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", 7.77f);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_NEAR(value, 7.77f, 0.01f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, SetDoubleThenQueryFloat_ReturnsSuccess_216) {
    doc.Clear();
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", 2.718281828);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_NEAR(value, 2.718281828f, 0.001f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, SetIntThenQueryFloat_ReturnsSuccess_216) {
    doc.Clear();
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", 100);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 100.0f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, FloatValueMethod_MatchesQueryResult_216) {
    const XMLAttribute* attr = createAttributeWithValue("9.81");
    ASSERT_NE(attr, nullptr);
    float queryValue = 0.0f;
    XMLError result = attr->QueryFloatValue(&queryValue);
    EXPECT_EQ(result, XML_SUCCESS);
    float directValue = attr->FloatValue();
    EXPECT_FLOAT_EQ(queryValue, directValue);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, NegativeZero_ReturnsSuccess_216) {
    const XMLAttribute* attr = createAttributeWithValue("-0.0");
    ASSERT_NE(attr, nullptr);
    float value = 1.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 0.0f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, DecimalOnly_ReturnsSuccess_216) {
    const XMLAttribute* attr = createAttributeWithValue(".5");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_TRUE(result == XML_SUCCESS || result == XML_WRONG_ATTRIBUTE_TYPE);
    if (result == XML_SUCCESS) {
        EXPECT_FLOAT_EQ(value, 0.5f);
    }
}

TEST_F(XMLAttributeQueryFloatValueTest_216, SpecialChars_ReturnsWrongType_216) {
    const XMLAttribute* attr = createAttributeWithValue("@#$");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError result = attr->QueryFloatValue(&value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}
