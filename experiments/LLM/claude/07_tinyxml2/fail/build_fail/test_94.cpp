#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementTest_94 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== QueryAttribute (double overload) ====================

TEST_F(XMLElementTest_94, QueryAttributeDouble_ValidAttribute_94) {
    doc.Parse("<root val=\"3.14\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 3.14);
}

TEST_F(XMLElementTest_94, QueryAttributeDouble_NonExistentAttribute_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 99.0;
    XMLError err = root->QueryAttribute("missing", &value);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 99.0); // value should remain unchanged
}

TEST_F(XMLElementTest_94, QueryAttributeDouble_NonNumericAttribute_94) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_94, QueryAttributeDouble_IntegerValueAsDouble_94) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 42.0);
}

TEST_F(XMLElementTest_94, QueryAttributeDouble_NegativeValue_94) {
    doc.Parse("<root val=\"-2.718\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, -2.718);
}

TEST_F(XMLElementTest_94, QueryAttributeDouble_ZeroValue_94) {
    doc.Parse("<root val=\"0.0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 99.0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 0.0);
}

TEST_F(XMLElementTest_94, QueryAttributeDouble_ScientificNotation_94) {
    doc.Parse("<root val=\"1.5e2\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 150.0);
}

// ==================== QueryAttribute (int overload) ====================

TEST_F(XMLElementTest_94, QueryAttributeInt_ValidAttribute_94) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST_F(XMLElementTest_94, QueryAttributeInt_NonExistentAttribute_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int value = -1;
    XMLError err = root->QueryAttribute("missing", &value);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_EQ(value, -1);
}

TEST_F(XMLElementTest_94, QueryAttributeInt_NegativeValue_94) {
    doc.Parse("<root val=\"-100\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, -100);
}

// ==================== QueryAttribute (unsigned int overload) ====================

TEST_F(XMLElementTest_94, QueryAttributeUnsigned_ValidAttribute_94) {
    doc.Parse("<root val=\"100\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    unsigned int value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 100u);
}

TEST_F(XMLElementTest_94, QueryAttributeUnsigned_NonExistent_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    unsigned int value = 55;
    XMLError err = root->QueryAttribute("nope", &value);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_EQ(value, 55u);
}

// ==================== QueryAttribute (int64_t overload) ====================

TEST_F(XMLElementTest_94, QueryAttributeInt64_ValidAttribute_94) {
    doc.Parse("<root val=\"9223372036854775807\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int64_t value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_94, QueryAttributeInt64_NonExistent_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int64_t value = -1;
    XMLError err = root->QueryAttribute("missing", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== QueryAttribute (uint64_t overload) ====================

TEST_F(XMLElementTest_94, QueryAttributeUnsigned64_ValidAttribute_94) {
    doc.Parse("<root val=\"18446744073709551615\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    uint64_t value = 0;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_C(18446744073709551615));
}

// ==================== QueryAttribute (bool overload) ====================

TEST_F(XMLElementTest_94, QueryAttributeBool_TrueValue_94) {
    doc.Parse("<root val=\"true\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    bool value = false;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_94, QueryAttributeBool_FalseValue_94) {
    doc.Parse("<root val=\"false\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    bool value = true;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

TEST_F(XMLElementTest_94, QueryAttributeBool_NonExistent_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    bool value = true;
    XMLError err = root->QueryAttribute("missing", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== QueryAttribute (float overload) ====================

TEST_F(XMLElementTest_94, QueryAttributeFloat_ValidAttribute_94) {
    doc.Parse("<root val=\"1.5\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    float value = 0.0f;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 1.5f);
}

TEST_F(XMLElementTest_94, QueryAttributeFloat_NonExistent_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    float value = 99.0f;
    XMLError err = root->QueryAttribute("nope", &value);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 99.0f);
}

// ==================== QueryAttribute (const char* overload) ====================

TEST_F(XMLElementTest_94, QueryAttributeString_ValidAttribute_94) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const char* value = nullptr;
    XMLError err = root->QueryAttribute("val", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "hello");
}

TEST_F(XMLElementTest_94, QueryAttributeString_NonExistent_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const char* value = nullptr;
    XMLError err = root->QueryAttribute("missing", &value);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== SetAttribute / Attribute ====================

TEST_F(XMLElementTest_94, SetAttributeString_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetAttribute("name", "value");
    const char* result = root->Attribute("name");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "value");
}

TEST_F(XMLElementTest_94, SetAttributeInt_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetAttribute("count", 42);
    int value = 0;
    XMLError err = root->QueryAttribute("count", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST_F(XMLElementTest_94, SetAttributeUnsigned_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetAttribute("count", (unsigned)100);
    unsigned value = 0;
    XMLError err = root->QueryAttribute("count", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 100u);
}

TEST_F(XMLElementTest_94, SetAttributeInt64_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetAttribute("big", INT64_C(9223372036854775807));
    int64_t value = 0;
    XMLError err = root->QueryAttribute("big", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_94, SetAttributeUint64_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetAttribute("big", UINT64_C(18446744073709551615));
    uint64_t value = 0;
    XMLError err = root->QueryAttribute("big", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_C(18446744073709551615));
}

TEST_F(XMLElementTest_94, SetAttributeBool_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetAttribute("flag", true);
    bool value = false;
    XMLError err = root->QueryAttribute("flag", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLElementTest_94, SetAttributeDouble_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetAttribute("pi", 3.14159);
    double value = 0.0;
    XMLError err = root->QueryAttribute("pi", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(value, 3.14159, 1e-4);
}

TEST_F(XMLElementTest_94, SetAttributeFloat_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetAttribute("ratio", 2.5f);
    float value = 0.0f;
    XMLError err = root->QueryAttribute("ratio", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 2.5f);
}

// ==================== Attribute with value check ====================

TEST_F(XMLElementTest_94, Attribute_WithMatchingValue_94) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const char* result = root->Attribute("key", "val");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "val");
}

TEST_F(XMLElementTest_94, Attribute_WithNonMatchingValue_94) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const char* result = root->Attribute("key", "other");
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLElementTest_94, Attribute_NonExistentKey_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const char* result = root->Attribute("missing");
    EXPECT_EQ(result, nullptr);
}

// ==================== *Attribute with default ====================

TEST_F(XMLElementTest_94, IntAttribute_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int val = root->IntAttribute("missing", 77);
    EXPECT_EQ(val, 77);
}

TEST_F(XMLElementTest_94, IntAttribute_Exists_94) {
    doc.Parse("<root val=\"10\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int val = root->IntAttribute("val", 77);
    EXPECT_EQ(val, 10);
}

TEST_F(XMLElementTest_94, UnsignedAttribute_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    unsigned val = root->UnsignedAttribute("missing", 99u);
    EXPECT_EQ(val, 99u);
}

TEST_F(XMLElementTest_94, Int64Attribute_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int64_t val = root->Int64Attribute("missing", INT64_C(123456789));
    EXPECT_EQ(val, INT64_C(123456789));
}

TEST_F(XMLElementTest_94, Unsigned64Attribute_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    uint64_t val = root->Unsigned64Attribute("missing", UINT64_C(999));
    EXPECT_EQ(val, UINT64_C(999));
}

TEST_F(XMLElementTest_94, BoolAttribute_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    bool val = root->BoolAttribute("missing", true);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_94, DoubleAttribute_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double val = root->DoubleAttribute("missing", 1.23);
    EXPECT_DOUBLE_EQ(val, 1.23);
}

TEST_F(XMLElementTest_94, FloatAttribute_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    float val = root->FloatAttribute("missing", 4.5f);
    EXPECT_FLOAT_EQ(val, 4.5f);
}

// ==================== DeleteAttribute ====================

TEST_F(XMLElementTest_94, DeleteAttribute_Existing_94) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->DeleteAttribute("key");
    const char* result = root->Attribute("key");
    EXPECT_EQ(result, nullptr);
}

TEST_F(XMLElementTest_94, DeleteAttribute_NonExisting_94) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    // Should not crash
    root->DeleteAttribute("nonexistent");
    const char* result = root->Attribute("key");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "val");
}

// ==================== FindAttribute ====================

TEST_F(XMLElementTest_94, FindAttribute_Existing_94) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = root->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "key");
    EXPECT_STREQ(attr->Value(), "val");
}

TEST_F(XMLElementTest_94, FindAttribute_NonExisting_94) {
    doc.Parse("<root key=\"val\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = root->FindAttribute("nope");
    EXPECT_EQ(attr, nullptr);
}

// ==================== FirstAttribute ====================

TEST_F(XMLElementTest_94, FirstAttribute_HasAttributes_94) {
    doc.Parse("<root a=\"1\" b=\"2\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = root->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
}

TEST_F(XMLElementTest_94, FirstAttribute_NoAttributes_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLAttribute* attr = root->FirstAttribute();
    EXPECT_EQ(attr, nullptr);
}

// ==================== GetText / SetText ====================

TEST_F(XMLElementTest_94, GetText_WithTextContent_94) {
    doc.Parse("<root>Hello World</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Hello World");
}

TEST_F(XMLElementTest_94, GetText_NoTextContent_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const char* text = root->GetText();
    EXPECT_EQ(text, nullptr);
}

TEST_F(XMLElementTest_94, SetText_String_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetText("test text");
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "test text");
}

TEST_F(XMLElementTest_94, SetText_Int_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetText(42);
    int val = 0;
    XMLError err = root->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_94, SetText_UnsignedInt_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetText((unsigned int)100);
    unsigned int val = 0;
    XMLError err = root->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

TEST_F(XMLElementTest_94, SetText_Int64_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetText(INT64_C(9223372036854775807));
    int64_t val = 0;
    XMLError err = root->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, INT64_C(9223372036854775807));
}

TEST_F(XMLElementTest_94, SetText_Uint64_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetText(UINT64_C(18446744073709551615));
    uint64_t val = 0;
    XMLError err = root->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, UINT64_C(18446744073709551615));
}

TEST_F(XMLElementTest_94, SetText_Bool_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetText(true);
    bool val = false;
    XMLError err = root->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_94, SetText_Double_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetText(3.14);
    double val = 0.0;
    XMLError err = root->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 1e-4);
}

TEST_F(XMLElementTest_94, SetText_Float_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetText(2.5f);
    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

// ==================== QueryXXXText ====================

TEST_F(XMLElementTest_94, QueryIntText_Valid_94) {
    doc.Parse("<root>123</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int val = 0;
    XMLError err = root->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 123);
}

TEST_F(XMLElementTest_94, QueryIntText_NoText_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int val = -1;
    XMLError err = root->QueryIntText(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementTest_94, QueryUnsignedText_Valid_94) {
    doc.Parse("<root>456</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    unsigned val = 0;
    XMLError err = root->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 456u);
}

TEST_F(XMLElementTest_94, QueryBoolText_True_94) {
    doc.Parse("<root>true</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    bool val = false;
    XMLError err = root->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_94, QueryBoolText_False_94) {
    doc.Parse("<root>false</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    bool val = true;
    XMLError err = root->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(val);
}

TEST_F(XMLElementTest_94, QueryDoubleText_Valid_94) {
    doc.Parse("<root>2.71828</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double val = 0.0;
    XMLError err = root->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 2.71828, 1e-4);
}

TEST_F(XMLElementTest_94, QueryFloatText_Valid_94) {
    doc.Parse("<root>1.5</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    float val = 0.0f;
    XMLError err = root->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 1.5f);
}

// ==================== *Text with default ====================

TEST_F(XMLElementTest_94, IntText_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int val = root->IntText(42);
    EXPECT_EQ(val, 42);
}

TEST_F(XMLElementTest_94, IntText_WithValue_94) {
    doc.Parse("<root>10</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int val = root->IntText(42);
    EXPECT_EQ(val, 10);
}

TEST_F(XMLElementTest_94, UnsignedText_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    unsigned val = root->UnsignedText(55u);
    EXPECT_EQ(val, 55u);
}

TEST_F(XMLElementTest_94, Int64Text_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    int64_t val = root->Int64Text(INT64_C(999));
    EXPECT_EQ(val, INT64_C(999));
}

TEST_F(XMLElementTest_94, Unsigned64Text_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    uint64_t val = root->Unsigned64Text(UINT64_C(888));
    EXPECT_EQ(val, UINT64_C(888));
}

TEST_F(XMLElementTest_94, BoolText_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    bool val = root->BoolText(true);
    EXPECT_TRUE(val);
}

TEST_F(XMLElementTest_94, DoubleText_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double val = root->DoubleText(6.28);
    EXPECT_DOUBLE_EQ(val, 6.28);
}

TEST_F(XMLElementTest_94, FloatText_Default_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    float val = root->FloatText(3.0f);
    EXPECT_FLOAT_EQ(val, 3.0f);
}

// ==================== Name / SetName ====================

TEST_F(XMLElementTest_94, Name_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    EXPECT_STREQ(root->Name(), "root");
}

TEST_F(XMLElementTest_94, SetName_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetName("newname");
    EXPECT_STREQ(root->Name(), "newname");
}

// ==================== ToElement ====================

TEST_F(XMLElementTest_94, ToElement_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLElement* elem = root->ToElement();
    EXPECT_EQ(elem, root);
}

// ==================== InsertNewChildElement ====================

TEST_F(XMLElementTest_94, InsertNewChildElement_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->Name(), "child");
    EXPECT_EQ(root->FirstChildElement("child"), child);
}

// ==================== InsertNewComment ====================

TEST_F(XMLElementTest_94, InsertNewComment_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLComment* comment = root->InsertNewComment("test comment");
    ASSERT_NE(comment, nullptr);
}

// ==================== InsertNewText ====================

TEST_F(XMLElementTest_94, InsertNewText_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLText* text = root->InsertNewText("some text");
    ASSERT_NE(text, nullptr);

    const char* content = root->GetText();
    ASSERT_NE(content, nullptr);
    EXPECT_STREQ(content, "some text");
}

// ==================== InsertNewDeclaration ====================

TEST_F(XMLElementTest_94, InsertNewDeclaration_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLDeclaration* decl = root->InsertNewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

// ==================== InsertNewUnknown ====================

TEST_F(XMLElementTest_94, InsertNewUnknown_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLUnknown* unknown = root->InsertNewUnknown("something");
    ASSERT_NE(unknown, nullptr);
}

// ==================== ShallowClone ====================

TEST_F(XMLElementTest_94, ShallowClone_94) {
    doc.Parse("<root attr=\"val\"><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLDocument doc2;
    XMLNode* clone = root->ShallowClone(&doc2);
    ASSERT_NE(clone, nullptr);

    XMLElement* cloneElem = clone->ToElement();
    ASSERT_NE(cloneElem, nullptr);
    EXPECT_STREQ(cloneElem->Name(), "root");
    EXPECT_STREQ(cloneElem->Attribute("attr"), "val");
    // ShallowClone should not clone children
    EXPECT_EQ(cloneElem->FirstChildElement(), nullptr);
}

// ==================== ShallowEqual ====================

TEST_F(XMLElementTest_94, ShallowEqual_SameNameAndAttributes_94) {
    doc.Parse("<root attr=\"val\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root attr=\"val\"/>");
    XMLElement* root2 = doc2.RootElement();
    ASSERT_NE(root2, nullptr);

    EXPECT_TRUE(root->ShallowEqual(root2));
}

TEST_F(XMLElementTest_94, ShallowEqual_DifferentName_94) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLDocument doc2;
    doc2.Parse("<other/>");
    XMLElement* root2 = doc2.RootElement();
    ASSERT_NE(root2, nullptr);

    EXPECT_FALSE(root->ShallowEqual(root2));
}

TEST_F(XMLElementTest_94, ShallowEqual_DifferentAttributes_94) {
    doc.Parse("<root a=\"1\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLDocument doc2;
    doc2.Parse("<root a=\"2\"/>");
    XMLElement* root2 = doc2.RootElement();
    ASSERT_NE(root2, nullptr);

    EXPECT_FALSE(root->ShallowEqual(root2));
}

// ==================== Multiple attributes ====================

TEST_F(XMLElementTest_94, MultipleAttributes_94) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    EXPECT_STREQ(root->Attribute("a"), "1");
    EXPECT_STREQ(root->Attribute("b"), "2");
    EXPECT_STREQ(root->Attribute("c"), "3");
}

TEST_F(XMLElementTest_94, OverwriteAttribute_94) {
    doc.Parse("<root key=\"old\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetAttribute("key", "new");
    EXPECT_STREQ(root->Attribute("key"), "new");
}

// ==================== Empty string attribute ====================

TEST_F(XMLElementTest_94, EmptyStringAttribute_94) {
    doc.Parse("<root val=\"\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const char* result = root->Attribute("val");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// ==================== SetText replaces existing text ====================

TEST_F(XMLElementTest_94, SetText_ReplacesExisting_94) {
    doc.Parse("<root>old text</root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetText("new text");
    const char*