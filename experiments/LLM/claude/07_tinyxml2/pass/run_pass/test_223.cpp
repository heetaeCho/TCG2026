#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Since XMLAttribute has a private constructor and destructor, we need to
// create it through the XML document infrastructure.
class XMLAttributeTest_223 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem;

    void SetUp() override {
        doc.Parse("<root attr=\"initial\"/>");
        elem = doc.RootElement();
        ASSERT_NE(elem, nullptr);
    }
};

// Test SetAttribute(bool) with true value
TEST_F(XMLAttributeTest_223, SetAttributeBoolTrue_223) {
    elem->SetAttribute("attr", true);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test SetAttribute(bool) with false value
TEST_F(XMLAttributeTest_223, SetAttributeBoolFalse_223) {
    elem->SetAttribute("attr", false);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    bool value = true;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

// Test that SetAttribute(bool) with true produces expected string value
TEST_F(XMLAttributeTest_223, SetAttributeBoolTrueStringValue_223) {
    elem->SetAttribute("attr", true);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    const char* val = attr->Value();
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "true");
}

// Test that SetAttribute(bool) with false produces expected string value
TEST_F(XMLAttributeTest_223, SetAttributeBoolFalseStringValue_223) {
    elem->SetAttribute("attr", false);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    const char* val = attr->Value();
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val, "false");
}

// Test BoolValue() convenience method after setting true
TEST_F(XMLAttributeTest_223, BoolValueAfterSetTrue_223) {
    elem->SetAttribute("attr", true);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

// Test BoolValue() convenience method after setting false
TEST_F(XMLAttributeTest_223, BoolValueAfterSetFalse_223) {
    elem->SetAttribute("attr", false);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_FALSE(attr->BoolValue());
}

// Test SetAttribute(int) 
TEST_F(XMLAttributeTest_223, SetAttributeInt_223) {
    elem->SetAttribute("attr", 42);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 42);
}

// Test SetAttribute(int) with negative value
TEST_F(XMLAttributeTest_223, SetAttributeIntNegative_223) {
    elem->SetAttribute("attr", -100);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, -100);
}

// Test SetAttribute(int) with zero
TEST_F(XMLAttributeTest_223, SetAttributeIntZero_223) {
    elem->SetAttribute("attr", 0);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int value = -1;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 0);
}

// Test SetAttribute(unsigned int)
TEST_F(XMLAttributeTest_223, SetAttributeUnsigned_223) {
    elem->SetAttribute("attr", (unsigned int)12345);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    unsigned int value = 0;
    XMLError err = attr->QueryUnsignedValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 12345u);
}

// Test SetAttribute(int64_t)
TEST_F(XMLAttributeTest_223, SetAttributeInt64_223) {
    int64_t bigVal = 9223372036854775807LL;  // INT64_MAX
    elem->SetAttribute("attr", bigVal);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int64_t value = 0;
    XMLError err = attr->QueryInt64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, bigVal);
}

// Test SetAttribute(uint64_t)
TEST_F(XMLAttributeTest_223, SetAttributeUint64_223) {
    uint64_t bigVal = 18446744073709551615ULL;  // UINT64_MAX
    elem->SetAttribute("attr", bigVal);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, bigVal);
}

// Test SetAttribute(double)
TEST_F(XMLAttributeTest_223, SetAttributeDouble_223) {
    elem->SetAttribute("attr", 3.14159);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    double value = 0.0;
    XMLError err = attr->QueryDoubleValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(value, 3.14159, 1e-5);
}

// Test SetAttribute(float)
TEST_F(XMLAttributeTest_223, SetAttributeFloat_223) {
    elem->SetAttribute("attr", 2.71f);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    float value = 0.0f;
    XMLError err = attr->QueryFloatValue(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(value, 2.71f, 1e-2);
}

// Test SetAttribute(const char*)
TEST_F(XMLAttributeTest_223, SetAttributeString_223) {
    elem->SetAttribute("attr", "hello world");
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello world");
}

// Test SetAttribute(const char*) with empty string
TEST_F(XMLAttributeTest_223, SetAttributeEmptyString_223) {
    elem->SetAttribute("attr", "");
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "");
}

// Test QueryBoolValue with non-bool string returns error
TEST_F(XMLAttributeTest_223, QueryBoolValueWithNonBoolString_223) {
    elem->SetAttribute("attr", "notabool");
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    bool value = false;
    XMLError err = attr->QueryBoolValue(&value);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryIntValue with non-int string returns error
TEST_F(XMLAttributeTest_223, QueryIntValueWithNonIntString_223) {
    elem->SetAttribute("attr", "abc");
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int value = 0;
    XMLError err = attr->QueryIntValue(&value);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test overwriting attribute value with bool after int
TEST_F(XMLAttributeTest_223, OverwriteIntWithBool_223) {
    elem->SetAttribute("attr", 42);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 42);

    elem->SetAttribute("attr", true);
    attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "true");
}

// Test overwriting attribute value with false after true
TEST_F(XMLAttributeTest_223, OverwriteTrueWithFalse_223) {
    elem->SetAttribute("attr", true);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());

    elem->SetAttribute("attr", false);
    attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_FALSE(attr->BoolValue());
}

// Test Name() of attribute
TEST_F(XMLAttributeTest_223, AttributeName_223) {
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "attr");
}

// Test multiple attributes
TEST_F(XMLAttributeTest_223, MultipleAttributes_223) {
    doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* a = elem->FindAttribute("a");
    const XMLAttribute* b = elem->FindAttribute("b");
    const XMLAttribute* c = elem->FindAttribute("c");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    ASSERT_NE(c, nullptr);

    EXPECT_STREQ(a->Value(), "1");
    EXPECT_STREQ(b->Value(), "2");
    EXPECT_STREQ(c->Value(), "3");
}

// Test Next() traversal
TEST_F(XMLAttributeTest_223, NextAttributeTraversal_223) {
    doc.Parse("<root first=\"1\" second=\"2\"/>");
    elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);

    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "first");

    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "second");

    EXPECT_EQ(next->Next(), nullptr);
}

// Test SetAttribute(bool) true then query round-trip through document serialization
TEST_F(XMLAttributeTest_223, BoolRoundTripThroughPrint_223) {
    elem->SetAttribute("attr", true);

    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);

    XMLDocument doc2;
    doc2.Parse(result);
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    bool value = false;
    XMLError err = elem2->QueryBoolAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

// Test SetAttribute(bool) false then query round-trip through document serialization
TEST_F(XMLAttributeTest_223, BoolFalseRoundTripThroughPrint_223) {
    elem->SetAttribute("attr", false);

    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);

    XMLDocument doc2;
    doc2.Parse(result);
    XMLElement* elem2 = doc2.RootElement();
    ASSERT_NE(elem2, nullptr);

    bool value = true;
    XMLError err = elem2->QueryBoolAttribute("attr", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

// Test SetBoolSerialization customization
TEST_F(XMLAttributeTest_223, CustomBoolSerialization_223) {
    XMLUtil::SetBoolSerialization("yes", "no");

    elem->SetAttribute("attr", true);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "yes");

    elem->SetAttribute("attr", false);
    attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "no");

    // Reset to default
    XMLUtil::SetBoolSerialization(nullptr, nullptr);
}

// Test SetBoolSerialization reset to default
TEST_F(XMLAttributeTest_223, ResetBoolSerializationToDefault_223) {
    XMLUtil::SetBoolSerialization("yes", "no");
    XMLUtil::SetBoolSerialization(nullptr, nullptr);

    elem->SetAttribute("attr", true);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "true");

    elem->SetAttribute("attr", false);
    attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "false");
}

// Test IntValue() convenience method
TEST_F(XMLAttributeTest_223, IntValueConvenience_223) {
    elem->SetAttribute("attr", 999);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 999);
}

// Test UnsignedValue() convenience method
TEST_F(XMLAttributeTest_223, UnsignedValueConvenience_223) {
    elem->SetAttribute("attr", (unsigned)4294967295u);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 4294967295u);
}

// Test DoubleValue() convenience method
TEST_F(XMLAttributeTest_223, DoubleValueConvenience_223) {
    elem->SetAttribute("attr", 1.23456789);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->DoubleValue(), 1.23456789, 1e-7);
}

// Test FloatValue() convenience method
TEST_F(XMLAttributeTest_223, FloatValueConvenience_223) {
    elem->SetAttribute("attr", 1.5f);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->FloatValue(), 1.5f, 1e-5);
}

// Test Int64Value() convenience method
TEST_F(XMLAttributeTest_223, Int64ValueConvenience_223) {
    int64_t val = -9223372036854775807LL;
    elem->SetAttribute("attr", val);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), val);
}

// Test Unsigned64Value() convenience method
TEST_F(XMLAttributeTest_223, Unsigned64ValueConvenience_223) {
    uint64_t val = 12345678901234567ULL;
    elem->SetAttribute("attr", val);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), val);
}
