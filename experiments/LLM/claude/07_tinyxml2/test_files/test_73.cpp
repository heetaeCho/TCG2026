#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeTest_73 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* CreateElementWithAttribute(const char* attrName, const char* attrValue) {
        doc.Clear();
        XMLElement* elem = doc.NewElement("test");
        doc.InsertFirstChild(elem);
        elem->SetAttribute(attrName, attrValue);
        return elem;
    }
};

// Test Unsigned64Value with a normal positive integer
TEST_F(XMLAttributeTest_73, Unsigned64Value_NormalPositiveValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "12345");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 12345ULL);
}

// Test Unsigned64Value with zero
TEST_F(XMLAttributeTest_73, Unsigned64Value_Zero_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 0ULL);
}

// Test Unsigned64Value with max uint64 value
TEST_F(XMLAttributeTest_73, Unsigned64Value_MaxUint64_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "18446744073709551615");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), UINT64_MAX);
}

// Test Unsigned64Value with large value
TEST_F(XMLAttributeTest_73, Unsigned64Value_LargeValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "9999999999999999999");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 9999999999999999999ULL);
}

// Test Unsigned64Value set via SetAttribute with uint64_t
TEST_F(XMLAttributeTest_73, Unsigned64Value_SetViaUint64SetAttribute_73) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", (uint64_t)42);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 42ULL);
}

// Test Unsigned64Value with non-numeric string returns default (0)
TEST_F(XMLAttributeTest_73, Unsigned64Value_NonNumericString_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "hello");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    // When query fails, the initial value (0) should be returned
    EXPECT_EQ(attr->Unsigned64Value(), 0ULL);
}

// Test Unsigned64Value with empty string
TEST_F(XMLAttributeTest_73, Unsigned64Value_EmptyString_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 0ULL);
}

// Test IntValue normal operation
TEST_F(XMLAttributeTest_73, IntValue_NormalValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "42");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 42);
}

// Test IntValue with negative
TEST_F(XMLAttributeTest_73, IntValue_NegativeValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "-100");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), -100);
}

// Test Int64Value normal operation
TEST_F(XMLAttributeTest_73, Int64Value_NormalValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "9223372036854775807");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), INT64_MAX);
}

// Test UnsignedValue normal operation
TEST_F(XMLAttributeTest_73, UnsignedValue_NormalValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "4294967295");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), UINT32_MAX);
}

// Test BoolValue with true
TEST_F(XMLAttributeTest_73, BoolValue_True_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "true");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), true);
}

// Test BoolValue with false
TEST_F(XMLAttributeTest_73, BoolValue_False_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "false");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), false);
}

// Test DoubleValue normal operation
TEST_F(XMLAttributeTest_73, DoubleValue_NormalValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "3.14159");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 3.14159);
}

// Test FloatValue normal operation
TEST_F(XMLAttributeTest_73, FloatValue_NormalValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "2.5");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 2.5f);
}

// Test Name returns correct attribute name
TEST_F(XMLAttributeTest_73, Name_ReturnsCorrectName_73) {
    XMLElement* elem = CreateElementWithAttribute("myattr", "123");
    const XMLAttribute* attr = elem->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
}

// Test Value returns correct attribute value
TEST_F(XMLAttributeTest_73, Value_ReturnsCorrectValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "hello world");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello world");
}

// Test QueryUnsigned64Value returns XML_SUCCESS for valid value
TEST_F(XMLAttributeTest_73, QueryUnsigned64Value_ValidValue_ReturnsSuccess_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "100");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    uint64_t result = 0;
    XMLError err = attr->QueryUnsigned64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 100ULL);
}

// Test QueryUnsigned64Value returns error for non-numeric
TEST_F(XMLAttributeTest_73, QueryUnsigned64Value_InvalidValue_ReturnsError_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "abc");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    uint64_t result = 999;
    XMLError err = attr->QueryUnsigned64Value(&result);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryIntValue returns XML_SUCCESS for valid int
TEST_F(XMLAttributeTest_73, QueryIntValue_ValidValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "-42");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    int result = 0;
    XMLError err = attr->QueryIntValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, -42);
}

// Test QueryBoolValue with invalid string
TEST_F(XMLAttributeTest_73, QueryBoolValue_InvalidString_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "notabool");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    bool result = false;
    XMLError err = attr->QueryBoolValue(&result);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test SetAttribute with int and query back
TEST_F(XMLAttributeTest_73, SetAttribute_Int_73) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 77);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 77);
}

// Test SetAttribute with double and query back
TEST_F(XMLAttributeTest_73, SetAttribute_Double_73) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 1.5);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 1.5);
}

// Test SetAttribute with bool true
TEST_F(XMLAttributeTest_73, SetAttribute_BoolTrue_73) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", true);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), true);
}

// Test SetAttribute with bool false
TEST_F(XMLAttributeTest_73, SetAttribute_BoolFalse_73) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", false);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), false);
}

// Test SetAttribute with float
TEST_F(XMLAttributeTest_73, SetAttribute_Float_73) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 3.5f);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 3.5f);
}

// Test Next returns nullptr when no next attribute
TEST_F(XMLAttributeTest_73, Next_SingleAttribute_ReturnsNull_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "1");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    // With only one attribute, Next() may or may not be null depending on
    // whether there are other attributes. For a single attribute, it should be null.
    EXPECT_EQ(attr->Next(), nullptr);
}

// Test Next returns next attribute when multiple exist
TEST_F(XMLAttributeTest_73, Next_MultipleAttributes_ReturnsNextAttribute_73) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("a", "1");
    elem->SetAttribute("b", "2");
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
    // Verify the next attribute exists and has a name
    EXPECT_TRUE(next->Name() != nullptr);
}

// Test Unsigned64Value with value set as uint64_t via SetAttribute
TEST_F(XMLAttributeTest_73, Unsigned64Value_SetAsUint64_MaxValue_73) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", UINT64_MAX);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), UINT64_MAX);
}

// Test Unsigned64Value with value 1
TEST_F(XMLAttributeTest_73, Unsigned64Value_One_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "1");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 1ULL);
}

// Test parsing XML with attribute and reading Unsigned64Value
TEST_F(XMLAttributeTest_73, Unsigned64Value_FromParsedXML_73) {
    const char* xml = "<root attr=\"555666777888999\"/>";
    doc.Parse(xml);
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 555666777888999ULL);
}

// Test GetLineNum returns a non-negative value
TEST_F(XMLAttributeTest_73, GetLineNum_NonNegative_73) {
    const char* xml = "<root attr=\"1\"/>";
    doc.Parse(xml);
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_GE(attr->GetLineNum(), 1);
}

// Test Int64Value with negative value
TEST_F(XMLAttributeTest_73, Int64Value_NegativeValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "-9223372036854775808");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), INT64_MIN);
}

// Test QueryDoubleValue with valid double
TEST_F(XMLAttributeTest_73, QueryDoubleValue_ValidValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "1.23e10");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(result, 1.23e10);
}

// Test QueryFloatValue with valid float
TEST_F(XMLAttributeTest_73, QueryFloatValue_ValidValue_73) {
    XMLElement* elem = CreateElementWithAttribute("val", "1.5");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    float result = 0.0f;
    XMLError err = attr->QueryFloatValue(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(result, 1.5f);
}

// Test SetAttribute with int64_t
TEST_F(XMLAttributeTest_73, SetAttribute_Int64_73) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", (int64_t)-999999999999LL);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), -999999999999LL);
}

// Test SetAttribute with unsigned int
TEST_F(XMLAttributeTest_73, SetAttribute_UnsignedInt_73) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", (unsigned int)4294967295U);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 4294967295U);
}

// Test SetAttribute with string
TEST_F(XMLAttributeTest_73, SetAttribute_String_73) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", "test string");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "test string");
}
