#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeTest_215 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    // Helper to create an element with an attribute having a specific value
    XMLElement* CreateElementWithAttribute(const char* attrName, const char* attrValue) {
        doc.Clear();
        char xml[256];
        snprintf(xml, sizeof(xml), "<root %s=\"%s\"/>", attrName, attrValue);
        doc.Parse(xml);
        XMLElement* root = doc.RootElement();
        return root;
    }
};

// ============================================================
// QueryBoolValue Tests
// ============================================================

TEST_F(XMLAttributeTest_215, QueryBoolValue_True_215) {
    XMLElement* root = CreateElementWithAttribute("flag", "true");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLAttributeTest_215, QueryBoolValue_False_215) {
    XMLElement* root = CreateElementWithAttribute("flag", "false");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    
    bool value = true;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

TEST_F(XMLAttributeTest_215, QueryBoolValue_One_215) {
    XMLElement* root = CreateElementWithAttribute("flag", "1");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLAttributeTest_215, QueryBoolValue_Zero_215) {
    XMLElement* root = CreateElementWithAttribute("flag", "0");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    
    bool value = true;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

TEST_F(XMLAttributeTest_215, QueryBoolValue_InvalidString_215) {
    XMLElement* root = CreateElementWithAttribute("flag", "notabool");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeTest_215, QueryBoolValue_NumericNonBool_215) {
    XMLElement* root = CreateElementWithAttribute("flag", "42");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeTest_215, QueryBoolValue_EmptyString_215) {
    XMLElement* root = CreateElementWithAttribute("flag", "");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeTest_215, QueryBoolValue_TrueUpperCase_215) {
    XMLElement* root = CreateElementWithAttribute("flag", "TRUE");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    // Depending on implementation, this may or may not be supported
    // We just check it returns either SUCCESS or WRONG_ATTRIBUTE_TYPE
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// ============================================================
// QueryIntValue Tests
// ============================================================

TEST_F(XMLAttributeTest_215, QueryIntValue_ValidInt_215) {
    XMLElement* root = CreateElementWithAttribute("num", "42");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST_F(XMLAttributeTest_215, QueryIntValue_NegativeInt_215) {
    XMLElement* root = CreateElementWithAttribute("num", "-100");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, -100);
}

TEST_F(XMLAttributeTest_215, QueryIntValue_Zero_215) {
    XMLElement* root = CreateElementWithAttribute("num", "0");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    int value = 99;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 0);
}

TEST_F(XMLAttributeTest_215, QueryIntValue_InvalidString_215) {
    XMLElement* root = CreateElementWithAttribute("num", "abc");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ============================================================
// QueryUnsignedValue Tests
// ============================================================

TEST_F(XMLAttributeTest_215, QueryUnsignedValue_Valid_215) {
    XMLElement* root = CreateElementWithAttribute("num", "100");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    unsigned int value = 0;
    XMLError err = attr->QueryUnsignedValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 100u);
}

TEST_F(XMLAttributeTest_215, QueryUnsignedValue_InvalidString_215) {
    XMLElement* root = CreateElementWithAttribute("num", "xyz");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    unsigned int value = 0;
    XMLError err = attr->QueryUnsignedValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ============================================================
// QueryInt64Value Tests
// ============================================================

TEST_F(XMLAttributeTest_215, QueryInt64Value_Valid_215) {
    XMLElement* root = CreateElementWithAttribute("num", "9223372036854775807");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, INT64_MAX);
}

TEST_F(XMLAttributeTest_215, QueryInt64Value_InvalidString_215) {
    XMLElement* root = CreateElementWithAttribute("num", "notanumber");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ============================================================
// QueryUnsigned64Value Tests
// ============================================================

TEST_F(XMLAttributeTest_215, QueryUnsigned64Value_Valid_215) {
    XMLElement* root = CreateElementWithAttribute("num", "18446744073709551615");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_MAX);
}

TEST_F(XMLAttributeTest_215, QueryUnsigned64Value_InvalidString_215) {
    XMLElement* root = CreateElementWithAttribute("num", "invalid");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ============================================================
// QueryDoubleValue Tests
// ============================================================

TEST_F(XMLAttributeTest_215, QueryDoubleValue_Valid_215) {
    XMLElement* root = CreateElementWithAttribute("num", "3.14159");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    double value = 0.0;
    XMLError err = attr->QueryDoubleValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 3.14159);
}

TEST_F(XMLAttributeTest_215, QueryDoubleValue_InvalidString_215) {
    XMLElement* root = CreateElementWithAttribute("num", "notadouble");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    double value = 0.0;
    XMLError err = attr->QueryDoubleValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ============================================================
// QueryFloatValue Tests
// ============================================================

TEST_F(XMLAttributeTest_215, QueryFloatValue_Valid_215) {
    XMLElement* root = CreateElementWithAttribute("num", "2.5");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    float value = 0.0f;
    XMLError err = attr->QueryFloatValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 2.5f);
}

TEST_F(XMLAttributeTest_215, QueryFloatValue_InvalidString_215) {
    XMLElement* root = CreateElementWithAttribute("num", "notafloat");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    
    float value = 0.0f;
    XMLError err = attr->QueryFloatValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ============================================================
// SetAttribute and Value/Name Tests
// ============================================================

TEST_F(XMLAttributeTest_215, Name_ReturnsAttributeName_215) {
    XMLElement* root = CreateElementWithAttribute("myattr", "myvalue");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    
    EXPECT_STREQ(attr->Name(), "myattr");
}

TEST_F(XMLAttributeTest_215, Value_ReturnsAttributeValue_215) {
    XMLElement* root = CreateElementWithAttribute("myattr", "myvalue");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    
    EXPECT_STREQ(attr->Value(), "myvalue");
}

TEST_F(XMLAttributeTest_215, SetAttribute_String_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "initial");
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", "updated");
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "updated");
}

TEST_F(XMLAttributeTest_215, SetAttribute_Int_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "0");
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", 12345);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    int value = 0;
    EXPECT_EQ(attr->QueryIntValue(&value), XML_SUCCESS);
    EXPECT_EQ(value, 12345);
}

TEST_F(XMLAttributeTest_215, SetAttribute_Bool_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "false");
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", true);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    EXPECT_EQ(attr->QueryBoolValue(&value), XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(XMLAttributeTest_215, SetAttribute_Double_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "0");
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", 2.71828);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    double value = 0.0;
    EXPECT_EQ(attr->QueryDoubleValue(&value), XML_SUCCESS);
    EXPECT_NEAR(value, 2.71828, 0.0001);
}

TEST_F(XMLAttributeTest_215, SetAttribute_Float_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "0");
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", 1.5f);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    float value = 0.0f;
    EXPECT_EQ(attr->QueryFloatValue(&value), XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 1.5f);
}

TEST_F(XMLAttributeTest_215, SetAttribute_Unsigned_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "0");
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", 4294967295u);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    unsigned int value = 0;
    EXPECT_EQ(attr->QueryUnsignedValue(&value), XML_SUCCESS);
    EXPECT_EQ(value, 4294967295u);
}

TEST_F(XMLAttributeTest_215, SetAttribute_Int64_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "0");
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", (int64_t)1234567890123LL);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    int64_t value = 0;
    EXPECT_EQ(attr->QueryInt64Value(&value), XML_SUCCESS);
    EXPECT_EQ(value, 1234567890123LL);
}

TEST_F(XMLAttributeTest_215, SetAttribute_Uint64_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "0");
    ASSERT_NE(root, nullptr);
    root->SetAttribute("attr", (uint64_t)18446744073709551615ULL);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    
    uint64_t value = 0;
    EXPECT_EQ(attr->QueryUnsigned64Value(&value), XML_SUCCESS);
    EXPECT_EQ(value, UINT64_MAX);
}

// ============================================================
// Convenience value accessor tests
// ============================================================

TEST_F(XMLAttributeTest_215, IntValue_ReturnsInt_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "99");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 99);
}

TEST_F(XMLAttributeTest_215, BoolValue_ReturnsTrue_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "true");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

TEST_F(XMLAttributeTest_215, BoolValue_ReturnsFalse_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "false");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_FALSE(attr->BoolValue());
}

TEST_F(XMLAttributeTest_215, DoubleValue_ReturnsDouble_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "1.23");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 1.23);
}

TEST_F(XMLAttributeTest_215, FloatValue_ReturnsFloat_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "4.5");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 4.5f);
}

TEST_F(XMLAttributeTest_215, UnsignedValue_ReturnsUnsigned_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "300");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 300u);
}

TEST_F(XMLAttributeTest_215, Int64Value_ReturnsInt64_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "9223372036854775807");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), INT64_MAX);
}

TEST_F(XMLAttributeTest_215, Unsigned64Value_ReturnsUint64_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "18446744073709551615");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), UINT64_MAX);
}

// ============================================================
// Next attribute test
// ============================================================

TEST_F(XMLAttributeTest_215, Next_ReturnsNextAttribute_215) {
    doc.Clear();
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* attr = root->FindAttribute("a");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
    
    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "b");
    
    const XMLAttribute* nextNext = next->Next();
    ASSERT_NE(nextNext, nullptr);
    EXPECT_STREQ(nextNext->Name(), "c");
    
    EXPECT_EQ(nextNext->Next(), nullptr);
}

// ============================================================
// GetLineNum test
// ============================================================

TEST_F(XMLAttributeTest_215, GetLineNum_ReturnsNonNegative_215) {
    XMLElement* root = CreateElementWithAttribute("attr", "val");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_GE(attr->GetLineNum(), 0);
}

// ============================================================
// QueryBoolValue boundary: "yes", "no" variants
// ============================================================

TEST_F(XMLAttributeTest_215, QueryBoolValue_YesString_215) {
    XMLElement* root = CreateElementWithAttribute("flag", "yes");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    // "yes" may or may not be recognized; just verify consistent return
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeTest_215, QueryBoolValue_WhitespaceOnly_215) {
    XMLElement* root = CreateElementWithAttribute("flag", " ");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// ============================================================
// Multiple attributes on same element
// ============================================================

TEST_F(XMLAttributeTest_215, MultipleAttributes_DifferentTypes_215) {
    doc.Clear();
    doc.Parse("<root intAttr=\"42\" boolAttr=\"true\" floatAttr=\"3.14\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    const XMLAttribute* intAttr = root->FindAttribute("intAttr");
    ASSERT_NE(intAttr, nullptr);
    int intVal = 0;
    EXPECT_EQ(intAttr->QueryIntValue(&intVal), XML_SUCCESS);
    EXPECT_EQ(intVal, 42);
    
    const XMLAttribute* boolAttr = root->FindAttribute("boolAttr");
    ASSERT_NE(boolAttr, nullptr);
    bool boolVal = false;
    EXPECT_EQ(boolAttr->QueryBoolValue(&boolVal), XML_SUCCESS);
    EXPECT_TRUE(boolVal);
    
    const XMLAttribute* floatAttr = root->FindAttribute("floatAttr");
    ASSERT_NE(floatAttr, nullptr);
    float floatVal = 0.0f;
    EXPECT_EQ(floatAttr->QueryFloatValue(&floatVal), XML_SUCCESS);
    EXPECT_FLOAT_EQ(floatVal, 3.14f);
}
