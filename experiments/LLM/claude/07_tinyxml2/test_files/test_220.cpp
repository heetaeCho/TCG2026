#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper: Since XMLAttribute has a private constructor, we need to create attributes
// through the XMLDocument/XMLElement API.
class XMLAttributeTest_220 : public ::testing::Test {
protected:
    XMLDocument doc;

    // Helper to create an element with an attribute and return the attribute
    const XMLAttribute* CreateAttribute(const char* elemName, const char* attrName, const char* attrValue) {
        XMLElement* elem = doc.NewElement(elemName);
        doc.InsertFirstChild(elem);
        elem->SetAttribute(attrName, attrValue);
        return elem->FindAttribute(attrName);
    }

    XMLElement* CreateElement(const char* elemName) {
        XMLElement* elem = doc.NewElement(elemName);
        doc.InsertFirstChild(elem);
        return elem;
    }
};

// Test SetAttribute with unsigned int value 0
TEST_F(XMLAttributeTest_220, SetAttributeUnsignedZero_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", (unsigned)0);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "0");
}

// Test SetAttribute with unsigned int value 1
TEST_F(XMLAttributeTest_220, SetAttributeUnsignedOne_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", (unsigned)1);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "1");
}

// Test SetAttribute with a typical unsigned int value
TEST_F(XMLAttributeTest_220, SetAttributeUnsignedTypical_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", (unsigned)42);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "42");
}

// Test SetAttribute with unsigned int max value
TEST_F(XMLAttributeTest_220, SetAttributeUnsignedMax_220) {
    XMLElement* elem = CreateElement("test");
    unsigned maxVal = 4294967295U; // UINT_MAX for 32-bit
    elem->SetAttribute("val", maxVal);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "4294967295");
}

// Test SetAttribute with a large unsigned int value
TEST_F(XMLAttributeTest_220, SetAttributeUnsignedLarge_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", (unsigned)1000000);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "1000000");
}

// Test that QueryUnsignedValue roundtrips correctly
TEST_F(XMLAttributeTest_220, SetAttributeUnsignedQueryRoundtrip_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", (unsigned)12345);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    unsigned result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 12345U);
}

// Test UnsignedValue() convenience method after SetAttribute unsigned
TEST_F(XMLAttributeTest_220, SetAttributeUnsignedValueMethod_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", (unsigned)9999);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 9999U);
}

// Test that setting unsigned attribute overwrites a previous string value
TEST_F(XMLAttributeTest_220, SetAttributeUnsignedOverwritesString_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", "hello");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello");

    elem->SetAttribute("val", (unsigned)77);
    attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "77");
}

// Test SetAttribute with int value
TEST_F(XMLAttributeTest_220, SetAttributeInt_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", (int)-42);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "-42");
}

// Test SetAttribute with int and QueryIntValue roundtrip
TEST_F(XMLAttributeTest_220, SetAttributeIntQueryRoundtrip_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", (int)100);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    int result = 0;
    XMLError err = attr->QueryIntValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 100);
}

// Test SetAttribute with bool true
TEST_F(XMLAttributeTest_220, SetAttributeBoolTrue_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", true);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    bool result = false;
    XMLError err = attr->QueryBoolValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(result);
}

// Test SetAttribute with bool false
TEST_F(XMLAttributeTest_220, SetAttributeBoolFalse_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", false);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    bool result = true;
    XMLError err = attr->QueryBoolValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(result);
}

// Test SetAttribute with double
TEST_F(XMLAttributeTest_220, SetAttributeDouble_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", 3.14);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(result, 3.14, 0.001);
}

// Test SetAttribute with float
TEST_F(XMLAttributeTest_220, SetAttributeFloat_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", 2.5f);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    float result = 0.0f;
    XMLError err = attr->QueryFloatValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(result, 2.5f, 0.001f);
}

// Test SetAttribute with int64_t
TEST_F(XMLAttributeTest_220, SetAttributeInt64_220) {
    XMLElement* elem = CreateElement("test");
    int64_t bigVal = 9223372036854775807LL; // INT64_MAX
    elem->SetAttribute("val", bigVal);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    int64_t result = 0;
    XMLError err = attr->QueryInt64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, bigVal);
}

// Test SetAttribute with uint64_t
TEST_F(XMLAttributeTest_220, SetAttributeUint64_220) {
    XMLElement* elem = CreateElement("test");
    uint64_t bigVal = 18446744073709551615ULL; // UINT64_MAX
    elem->SetAttribute("val", bigVal);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    uint64_t result = 0;
    XMLError err = attr->QueryUnsigned64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, bigVal);
}

// Test SetAttribute with const char* (string)
TEST_F(XMLAttributeTest_220, SetAttributeString_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", "hello world");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello world");
}

// Test Name() returns the correct attribute name
TEST_F(XMLAttributeTest_220, AttributeName_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("myattr", "myval");
    const XMLAttribute* attr = elem->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
}

// Test QueryIntValue returns error for non-integer string
TEST_F(XMLAttributeTest_220, QueryIntValueNonIntError_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", "notanumber");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    int result = 0;
    XMLError err = attr->QueryIntValue(&result);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryUnsignedValue returns error for non-unsigned string
TEST_F(XMLAttributeTest_220, QueryUnsignedValueNonUnsignedError_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", "abc");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    unsigned result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryBoolValue returns error for non-bool string
TEST_F(XMLAttributeTest_220, QueryBoolValueNonBoolError_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", "notbool");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    bool result = false;
    XMLError err = attr->QueryBoolValue(&result);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test multiple attributes on same element and Next()
TEST_F(XMLAttributeTest_220, AttributeNext_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("a", "1");
    elem->SetAttribute("b", "2");
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "b");
    EXPECT_EQ(next->Next(), nullptr);
}

// Test SetAttribute unsigned multiple times overwrites
TEST_F(XMLAttributeTest_220, SetAttributeUnsignedMultipleTimes_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", (unsigned)10);
    elem->SetAttribute("val", (unsigned)20);
    elem->SetAttribute("val", (unsigned)30);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "30");
    EXPECT_EQ(attr->UnsignedValue(), 30U);
}

// Test SetAttribute with empty string
TEST_F(XMLAttributeTest_220, SetAttributeEmptyString_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", "");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "");
}

// Test IntValue convenience after setting int
TEST_F(XMLAttributeTest_220, IntValueConvenience_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", (int)-999);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), -999);
}

// Test DoubleValue convenience after setting double
TEST_F(XMLAttributeTest_220, DoubleValueConvenience_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", 1.23);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->DoubleValue(), 1.23, 0.001);
}

// Test FloatValue convenience after setting float
TEST_F(XMLAttributeTest_220, FloatValueConvenience_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", 4.56f);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->FloatValue(), 4.56f, 0.01f);
}

// Test BoolValue convenience
TEST_F(XMLAttributeTest_220, BoolValueConvenience_220) {
    XMLElement* elem = CreateElement("test");
    elem->SetAttribute("val", true);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

// Test Int64Value convenience
TEST_F(XMLAttributeTest_220, Int64ValueConvenience_220) {
    XMLElement* elem = CreateElement("test");
    int64_t v = -1234567890123LL;
    elem->SetAttribute("val", v);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), v);
}

// Test Unsigned64Value convenience
TEST_F(XMLAttributeTest_220, Unsigned64ValueConvenience_220) {
    XMLElement* elem = CreateElement("test");
    uint64_t v = 1234567890123ULL;
    elem->SetAttribute("val", v);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), v);
}

// Test that unsigned value serialized can be parsed back from XML
TEST_F(XMLAttributeTest_220, UnsignedAttributeSerializeDeserialize_220) {
    XMLDocument doc1;
    XMLElement* elem = doc1.NewElement("root");
    doc1.InsertFirstChild(elem);
    elem->SetAttribute("count", (unsigned)256);

    XMLPrinter printer;
    doc1.Print(&printer);
    const char* xmlStr = printer.CStr();

    XMLDocument doc2;
    doc2.Parse(xmlStr);
    const XMLElement* root = doc2.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    unsigned val = 0;
    XMLError err = root->QueryUnsignedAttribute("count", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 256U);
}
