#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeTest_74 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test UnsignedValue with a valid unsigned integer attribute
TEST_F(XMLAttributeTest_74, UnsignedValue_ValidUnsigned_74) {
    const char* xml = "<root attr=\"42\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 42u);
}

// Test UnsignedValue with zero
TEST_F(XMLAttributeTest_74, UnsignedValue_Zero_74) {
    const char* xml = "<root attr=\"0\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 0u);
}

// Test UnsignedValue with a large unsigned value
TEST_F(XMLAttributeTest_74, UnsignedValue_LargeValue_74) {
    const char* xml = "<root attr=\"4294967295\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 4294967295u);
}

// Test UnsignedValue with non-numeric string returns default (0)
TEST_F(XMLAttributeTest_74, UnsignedValue_NonNumericReturnsDefault_74) {
    const char* xml = "<root attr=\"hello\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    // When QueryUnsignedValue fails, the value should remain 0 (initialized)
    EXPECT_EQ(attr->UnsignedValue(), 0u);
}

// Test IntValue with valid integer
TEST_F(XMLAttributeTest_74, IntValue_ValidInt_74) {
    const char* xml = "<root attr=\"-123\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), -123);
}

// Test IntValue with zero
TEST_F(XMLAttributeTest_74, IntValue_Zero_74) {
    const char* xml = "<root attr=\"0\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 0);
}

// Test Int64Value with valid int64
TEST_F(XMLAttributeTest_74, Int64Value_ValidInt64_74) {
    const char* xml = "<root attr=\"9223372036854775807\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), INT64_C(9223372036854775807));
}

// Test Unsigned64Value with valid uint64
TEST_F(XMLAttributeTest_74, Unsigned64Value_ValidUint64_74) {
    const char* xml = "<root attr=\"18446744073709551615\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), UINT64_C(18446744073709551615));
}

// Test BoolValue with true
TEST_F(XMLAttributeTest_74, BoolValue_True_74) {
    const char* xml = "<root attr=\"true\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), true);
}

// Test BoolValue with false
TEST_F(XMLAttributeTest_74, BoolValue_False_74) {
    const char* xml = "<root attr=\"false\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), false);
}

// Test DoubleValue with valid double
TEST_F(XMLAttributeTest_74, DoubleValue_Valid_74) {
    const char* xml = "<root attr=\"3.14159\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 3.14159);
}

// Test FloatValue with valid float
TEST_F(XMLAttributeTest_74, FloatValue_Valid_74) {
    const char* xml = "<root attr=\"2.5\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 2.5f);
}

// Test Name returns the attribute name
TEST_F(XMLAttributeTest_74, Name_ReturnsCorrectName_74) {
    const char* xml = "<root myattr=\"value\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
}

// Test Value returns the attribute value
TEST_F(XMLAttributeTest_74, Value_ReturnsCorrectValue_74) {
    const char* xml = "<root attr=\"somevalue\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "somevalue");
}

// Test QueryIntValue with valid value
TEST_F(XMLAttributeTest_74, QueryIntValue_Valid_74) {
    const char* xml = "<root attr=\"99\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    XMLError err = attr->QueryIntValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 99);
}

// Test QueryIntValue with non-numeric value
TEST_F(XMLAttributeTest_74, QueryIntValue_NonNumeric_74) {
    const char* xml = "<root attr=\"abc\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    XMLError err = attr->QueryIntValue(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryUnsignedValue with valid value
TEST_F(XMLAttributeTest_74, QueryUnsignedValue_Valid_74) {
    const char* xml = "<root attr=\"100\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    unsigned val = 0;
    XMLError err = attr->QueryUnsignedValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 100u);
}

// Test QueryUnsignedValue with non-numeric value
TEST_F(XMLAttributeTest_74, QueryUnsignedValue_NonNumeric_74) {
    const char* xml = "<root attr=\"xyz\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    unsigned val = 0;
    XMLError err = attr->QueryUnsignedValue(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryBoolValue with valid bool
TEST_F(XMLAttributeTest_74, QueryBoolValue_Valid_74) {
    const char* xml = "<root attr=\"true\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

// Test QueryBoolValue with non-boolean value
TEST_F(XMLAttributeTest_74, QueryBoolValue_Invalid_74) {
    const char* xml = "<root attr=\"notabool\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryDoubleValue with valid double
TEST_F(XMLAttributeTest_74, QueryDoubleValue_Valid_74) {
    const char* xml = "<root attr=\"1.618\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    XMLError err = attr->QueryDoubleValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 1.618);
}

// Test QueryFloatValue with valid float
TEST_F(XMLAttributeTest_74, QueryFloatValue_Valid_74) {
    const char* xml = "<root attr=\"1.5\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    float val = 0.0f;
    XMLError err = attr->QueryFloatValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 1.5f);
}

// Test QueryInt64Value with valid value
TEST_F(XMLAttributeTest_74, QueryInt64Value_Valid_74) {
    const char* xml = "<root attr=\"-9223372036854775807\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int64_t val = 0;
    XMLError err = attr->QueryInt64Value(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, INT64_C(-9223372036854775807));
}

// Test QueryUnsigned64Value with valid value
TEST_F(XMLAttributeTest_74, QueryUnsigned64Value_Valid_74) {
    const char* xml = "<root attr=\"12345678901234567890\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    uint64_t val = 0;
    XMLError err = attr->QueryUnsigned64Value(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, UINT64_C(12345678901234567890));
}

// Test SetAttribute with const char*
TEST_F(XMLAttributeTest_74, SetAttribute_String_74) {
    const char* xml = "<root attr=\"old\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", "new");
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "new");
}

// Test SetAttribute with int
TEST_F(XMLAttributeTest_74, SetAttribute_Int_74) {
    const char* xml = "<root attr=\"0\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", -42);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), -42);
}

// Test SetAttribute with unsigned
TEST_F(XMLAttributeTest_74, SetAttribute_Unsigned_74) {
    const char* xml = "<root attr=\"0\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 42u);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 42u);
}

// Test SetAttribute with bool
TEST_F(XMLAttributeTest_74, SetAttribute_Bool_74) {
    const char* xml = "<root attr=\"0\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", true);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), true);
}

// Test SetAttribute with double
TEST_F(XMLAttributeTest_74, SetAttribute_Double_74) {
    const char* xml = "<root attr=\"0\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 3.14);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->DoubleValue(), 3.14, 0.001);
}

// Test SetAttribute with float
TEST_F(XMLAttributeTest_74, SetAttribute_Float_74) {
    const char* xml = "<root attr=\"0\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 2.5f);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 2.5f);
}

// Test SetAttribute with int64_t
TEST_F(XMLAttributeTest_74, SetAttribute_Int64_74) {
    const char* xml = "<root attr=\"0\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", INT64_C(9223372036854775807));
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), INT64_C(9223372036854775807));
}

// Test SetAttribute with uint64_t
TEST_F(XMLAttributeTest_74, SetAttribute_Uint64_74) {
    const char* xml = "<root attr=\"0\"/>";
    doc.Parse(xml);
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", UINT64_C(18446744073709551615));
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), UINT64_C(18446744073709551615));
}

// Test Next attribute
TEST_F(XMLAttributeTest_74, Next_MultipleAttributes_74) {
    const char* xml = "<root a=\"1\" b=\"2\" c=\"3\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("a");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "a");
    
    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "b");
    
    const XMLAttribute* next2 = next->Next();
    ASSERT_NE(next2, nullptr);
    EXPECT_STREQ(next2->Name(), "c");
    
    EXPECT_EQ(next2->Next(), nullptr);
}

// Test GetLineNum
TEST_F(XMLAttributeTest_74, GetLineNum_74) {
    const char* xml = "<root attr=\"value\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    // Line number should be positive (at least 1)
    EXPECT_GE(attr->GetLineNum(), 1);
}

// Test UnsignedValue with empty string
TEST_F(XMLAttributeTest_74, UnsignedValue_EmptyString_74) {
    const char* xml = "<root attr=\"\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    // Should return default 0 since empty string can't be parsed
    EXPECT_EQ(attr->UnsignedValue(), 0u);
}

// Test BoolValue with numeric 1
TEST_F(XMLAttributeTest_74, BoolValue_NumericOne_74) {
    const char* xml = "<root attr=\"1\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), true);
}

// Test BoolValue with numeric 0
TEST_F(XMLAttributeTest_74, BoolValue_NumericZero_74) {
    const char* xml = "<root attr=\"0\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), false);
}

// Test negative value through QueryUnsignedValue
TEST_F(XMLAttributeTest_74, QueryUnsignedValue_NegativeValue_74) {
    const char* xml = "<root attr=\"-1\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    unsigned val = 0;
    XMLError err = attr->QueryUnsignedValue(&val);
    // Implementation-dependent: negative may fail or wrap around
    // We just check it doesn't crash
    (void)err;
    (void)val;
}

// Test floating point through QueryIntValue (should fail)
TEST_F(XMLAttributeTest_74, QueryIntValue_FloatString_74) {
    const char* xml = "<root attr=\"3.14\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    XMLError err = attr->QueryIntValue(&val);
    // May or may not succeed depending on implementation; just ensure no crash
    (void)err;
}

// Test DoubleValue with negative
TEST_F(XMLAttributeTest_74, DoubleValue_Negative_74) {
    const char* xml = "<root attr=\"-99.99\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), -99.99);
}

// Test IntValue with positive boundary
TEST_F(XMLAttributeTest_74, IntValue_MaxInt_74) {
    const char* xml = "<root attr=\"2147483647\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 2147483647);
}

// Test IntValue with negative boundary
TEST_F(XMLAttributeTest_74, IntValue_MinInt_74) {
    const char* xml = "<root attr=\"-2147483648\"/>";
    doc.Parse(xml);
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    XMLError err = attr->QueryIntValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, -2147483648);
}
