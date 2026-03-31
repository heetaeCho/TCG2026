#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cmath>
#include <limits>
#include <string>
#include <cstring>

using namespace tinyxml2;

class XMLElementSetTextTest_242 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
        // Create a root element for testing
    }
};

// ==================== SetText(float) Tests ====================

TEST_F(XMLElementSetTextTest_242, SetTextFloat_PositiveValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(3.14f);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(3.14f, result, 0.001f);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_NegativeValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(-2.5f);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(-2.5f, result, 0.001f);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_Zero_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(0.0f);
    
    float result = 1.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(0.0f, result);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_LargeValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(1.0e10f);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(1.0e10f, result, 1.0e5f);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_SmallValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(1.0e-10f);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(1.0e-10f, result, 1.0e-15f);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_NegativeZero_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(-0.0f);
    
    float result = 1.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(0.0f, result);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_One_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(1.0f);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(1.0f, result);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_NegativeOne_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(-1.0f);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(-1.0f, result);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_GetTextReturnsNonNull_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(42.5f);
    
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_TRUE(strlen(text) > 0);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_OverwritesPreviousText_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText("old text");
    elem->SetText(99.9f);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(99.9f, result, 0.1f);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_OverwritesPreviousFloatText_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(1.0f);
    elem->SetText(2.0f);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(2.0f, result);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_MaxFloat_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    float maxVal = std::numeric_limits<float>::max();
    elem->SetText(maxVal);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    // The value should be recoverable
    EXPECT_TRUE(std::isfinite(result));
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_MinPositiveFloat_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    float minVal = std::numeric_limits<float>::min();
    elem->SetText(minVal);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(result > 0.0f);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_LowestFloat_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    float lowestVal = std::numeric_limits<float>::lowest();
    elem->SetText(lowestVal);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(result < 0.0f);
}

TEST_F(XMLElementSetTextTest_242, SetTextFloat_ReadableAsDouble_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(3.14f);
    
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(3.14, result, 0.01);
}

// ==================== SetText with other types for comparison ====================

TEST_F(XMLElementSetTextTest_242, SetTextInt_BasicValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(42);
    
    int result = 0;
    XMLError err = elem->QueryIntText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(42, result);
}

TEST_F(XMLElementSetTextTest_242, SetTextDouble_BasicValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(3.14159);
    
    double result = 0.0;
    XMLError err = elem->QueryDoubleText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(3.14159, result, 0.0001);
}

TEST_F(XMLElementSetTextTest_242, SetTextBool_TrueValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(true);
    
    bool result = false;
    XMLError err = elem->QueryBoolText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_TRUE(result);
}

TEST_F(XMLElementSetTextTest_242, SetTextBool_FalseValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(false);
    
    bool result = true;
    XMLError err = elem->QueryBoolText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(result);
}

TEST_F(XMLElementSetTextTest_242, SetTextUnsigned_BasicValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((unsigned)12345);
    
    unsigned result = 0;
    XMLError err = elem->QueryUnsignedText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(12345u, result);
}

TEST_F(XMLElementSetTextTest_242, SetTextInt64_BasicValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((int64_t)1234567890123LL);
    
    int64_t result = 0;
    XMLError err = elem->QueryInt64Text(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(1234567890123LL, result);
}

TEST_F(XMLElementSetTextTest_242, SetTextUint64_BasicValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText((uint64_t)9876543210ULL);
    
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Text(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(9876543210ULL, result);
}

TEST_F(XMLElementSetTextTest_242, SetTextString_BasicValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText("Hello World");
    
    const char* text = elem->GetText();
    ASSERT_NE(nullptr, text);
    EXPECT_STREQ("Hello World", text);
}

// ==================== Query text when no text set ====================

TEST_F(XMLElementSetTextTest_242, QueryFloatText_NoText_ReturnsError_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_NE(XML_SUCCESS, err);
}

TEST_F(XMLElementSetTextTest_242, GetText_NoText_ReturnsNull_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    
    const char* text = elem->GetText();
    EXPECT_EQ(nullptr, text);
}

// ==================== FloatText with default value ====================

TEST_F(XMLElementSetTextTest_242, FloatText_WithValue_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(7.5f);
    
    float result = elem->FloatText(0.0f);
    EXPECT_NEAR(7.5f, result, 0.01f);
}

TEST_F(XMLElementSetTextTest_242, FloatText_NoValue_ReturnsDefault_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    
    float result = elem->FloatText(99.9f);
    EXPECT_FLOAT_EQ(99.9f, result);
}

// ==================== XMLUtil::ToStr(float) tests ====================

TEST_F(XMLElementSetTextTest_242, XMLUtilToStrFloat_BasicConversion_242) {
    char buf[200];
    XMLUtil::ToStr(3.14f, buf, 200);
    
    float parsed = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buf, &parsed));
    EXPECT_NEAR(3.14f, parsed, 0.001f);
}

TEST_F(XMLElementSetTextTest_242, XMLUtilToStrFloat_Zero_242) {
    char buf[200];
    XMLUtil::ToStr(0.0f, buf, 200);
    
    float parsed = 1.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buf, &parsed));
    EXPECT_FLOAT_EQ(0.0f, parsed);
}

TEST_F(XMLElementSetTextTest_242, XMLUtilToStrFloat_NegativeValue_242) {
    char buf[200];
    XMLUtil::ToStr(-5.5f, buf, 200);
    
    float parsed = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat(buf, &parsed));
    EXPECT_NEAR(-5.5f, parsed, 0.001f);
}

TEST_F(XMLElementSetTextTest_242, XMLUtilToFloat_ValidString_242) {
    float value = 0.0f;
    EXPECT_TRUE(XMLUtil::ToFloat("3.14", &value));
    EXPECT_NEAR(3.14f, value, 0.001f);
}

TEST_F(XMLElementSetTextTest_242, XMLUtilToFloat_InvalidString_242) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("notanumber", &value));
}

TEST_F(XMLElementSetTextTest_242, XMLUtilToFloat_EmptyString_242) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat("", &value));
}

TEST_F(XMLElementSetTextTest_242, XMLUtilToFloat_NullString_242) {
    float value = 0.0f;
    EXPECT_FALSE(XMLUtil::ToFloat(nullptr, &value));
}

// ==================== Attribute-related tests ====================

TEST_F(XMLElementSetTextTest_242, SetAttribute_Float_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 1.5f);
    
    float result = elem->FloatAttribute("val", 0.0f);
    EXPECT_NEAR(1.5f, result, 0.001f);
}

TEST_F(XMLElementSetTextTest_242, FloatAttribute_DefaultWhenMissing_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    
    float result = elem->FloatAttribute("missing", 42.0f);
    EXPECT_FLOAT_EQ(42.0f, result);
}

TEST_F(XMLElementSetTextTest_242, QueryFloatAttribute_Success_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 9.8f);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(9.8f, result, 0.01f);
}

TEST_F(XMLElementSetTextTest_242, QueryFloatAttribute_NoAttribute_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("missing", &result);
    EXPECT_NE(XML_SUCCESS, err);
}

// ==================== SetText(float) followed by different SetText ====================

TEST_F(XMLElementSetTextTest_242, SetTextFloat_ThenSetTextInt_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(3.14f);
    elem->SetText(42);
    
    int result = 0;
    XMLError err = elem->QueryIntText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(42, result);
}

TEST_F(XMLElementSetTextTest_242, SetTextInt_ThenSetTextFloat_242) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetText(42);
    elem->SetText(3.14f);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(3.14f, result, 0.01f);
}

// ==================== Printing test to verify round-trip ====================

TEST_F(XMLElementSetTextTest_242, SetTextFloat_DocumentRoundTrip_242) {
    XMLElement* elem = doc.NewElement("value");
    doc.InsertFirstChild(elem);
    elem->SetText(2.718f);
    
    XMLPrinter printer;
    doc.Print(&printer);
    
    const char* xmlStr = printer.CStr();
    ASSERT_NE(nullptr, xmlStr);
    
    XMLDocument doc2;
    XMLError err = doc2.Parse(xmlStr);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc2.FirstChildElement("value");
    ASSERT_NE(nullptr, root);
    
    float result = 0.0f;
    err = root->QueryFloatText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_NEAR(2.718f, result, 0.01f);
}
