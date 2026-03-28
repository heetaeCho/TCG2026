#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeTest_71 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test IntValue with a valid integer attribute
TEST_F(XMLAttributeTest_71, IntValue_ValidInteger_71) {
    doc.Parse("<root attr=\"42\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 42);
}

// Test IntValue with zero
TEST_F(XMLAttributeTest_71, IntValue_Zero_71) {
    doc.Parse("<root attr=\"0\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 0);
}

// Test IntValue with negative integer
TEST_F(XMLAttributeTest_71, IntValue_NegativeInteger_71) {
    doc.Parse("<root attr=\"-100\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), -100);
}

// Test IntValue with non-numeric string (should return default 0)
TEST_F(XMLAttributeTest_71, IntValue_NonNumericString_71) {
    doc.Parse("<root attr=\"hello\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 0);
}

// Test IntValue with large positive integer
TEST_F(XMLAttributeTest_71, IntValue_LargePositive_71) {
    doc.Parse("<root attr=\"2147483647\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 2147483647);
}

// Test IntValue with large negative integer
TEST_F(XMLAttributeTest_71, IntValue_LargeNegative_71) {
    doc.Parse("<root attr=\"-2147483648\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), -2147483648);
}

// Test QueryIntValue returns XML_SUCCESS for valid integer
TEST_F(XMLAttributeTest_71, QueryIntValue_ValidInteger_71) {
    doc.Parse("<root attr=\"123\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    XMLError err = attr->QueryIntValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 123);
}

// Test QueryIntValue returns error for non-numeric
TEST_F(XMLAttributeTest_71, QueryIntValue_NonNumeric_71) {
    doc.Parse("<root attr=\"abc\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int val = 999;
    XMLError err = attr->QueryIntValue(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test UnsignedValue
TEST_F(XMLAttributeTest_71, UnsignedValue_Valid_71) {
    doc.Parse("<root attr=\"42\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 42u);
}

// Test QueryUnsignedValue
TEST_F(XMLAttributeTest_71, QueryUnsignedValue_Valid_71) {
    doc.Parse("<root attr=\"255\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    unsigned int val = 0;
    XMLError err = attr->QueryUnsignedValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 255u);
}

// Test Int64Value
TEST_F(XMLAttributeTest_71, Int64Value_Valid_71) {
    doc.Parse("<root attr=\"9223372036854775807\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), 9223372036854775807LL);
}

// Test QueryInt64Value
TEST_F(XMLAttributeTest_71, QueryInt64Value_Valid_71) {
    doc.Parse("<root attr=\"-9223372036854775807\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int64_t val = 0;
    XMLError err = attr->QueryInt64Value(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, -9223372036854775807LL);
}

// Test Unsigned64Value
TEST_F(XMLAttributeTest_71, Unsigned64Value_Valid_71) {
    doc.Parse("<root attr=\"18446744073709551615\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 18446744073709551615ULL);
}

// Test BoolValue true
TEST_F(XMLAttributeTest_71, BoolValue_True_71) {
    doc.Parse("<root attr=\"true\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

// Test BoolValue false
TEST_F(XMLAttributeTest_71, BoolValue_False_71) {
    doc.Parse("<root attr=\"false\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_FALSE(attr->BoolValue());
}

// Test QueryBoolValue
TEST_F(XMLAttributeTest_71, QueryBoolValue_Valid_71) {
    doc.Parse("<root attr=\"true\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

// Test QueryBoolValue with invalid value
TEST_F(XMLAttributeTest_71, QueryBoolValue_Invalid_71) {
    doc.Parse("<root attr=\"maybe\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    bool val = true;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test DoubleValue
TEST_F(XMLAttributeTest_71, DoubleValue_Valid_71) {
    doc.Parse("<root attr=\"3.14159\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 3.14159);
}

// Test QueryDoubleValue
TEST_F(XMLAttributeTest_71, QueryDoubleValue_Valid_71) {
    doc.Parse("<root attr=\"-2.718\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    XMLError err = attr->QueryDoubleValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, -2.718);
}

// Test QueryDoubleValue with non-numeric
TEST_F(XMLAttributeTest_71, QueryDoubleValue_Invalid_71) {
    doc.Parse("<root attr=\"notanumber\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    XMLError err = attr->QueryDoubleValue(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test FloatValue
TEST_F(XMLAttributeTest_71, FloatValue_Valid_71) {
    doc.Parse("<root attr=\"1.5\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 1.5f);
}

// Test QueryFloatValue
TEST_F(XMLAttributeTest_71, QueryFloatValue_Valid_71) {
    doc.Parse("<root attr=\"2.5\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    float val = 0.0f;
    XMLError err = attr->QueryFloatValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

// Test Name
TEST_F(XMLAttributeTest_71, Name_Valid_71) {
    doc.Parse("<root myattr=\"value\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
}

// Test Value
TEST_F(XMLAttributeTest_71, Value_Valid_71) {
    doc.Parse("<root attr=\"hello world\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello world");
}

// Test SetAttribute with const char*
TEST_F(XMLAttributeTest_71, SetAttribute_String_71) {
    doc.Parse("<root attr=\"old\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", "new_value");
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "new_value");
}

// Test SetAttribute with int
TEST_F(XMLAttributeTest_71, SetAttribute_Int_71) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 99);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 99);
}

// Test SetAttribute with unsigned int
TEST_F(XMLAttributeTest_71, SetAttribute_Unsigned_71) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 42u);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 42u);
}

// Test SetAttribute with bool
TEST_F(XMLAttributeTest_71, SetAttribute_Bool_71) {
    doc.Parse("<root attr=\"false\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", true);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

// Test SetAttribute with double
TEST_F(XMLAttributeTest_71, SetAttribute_Double_71) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 3.14);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->DoubleValue(), 3.14, 0.001);
}

// Test SetAttribute with float
TEST_F(XMLAttributeTest_71, SetAttribute_Float_71) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", 1.5f);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_FLOAT_EQ(attr->FloatValue(), 1.5f);
}

// Test SetAttribute with int64_t
TEST_F(XMLAttributeTest_71, SetAttribute_Int64_71) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", (int64_t)123456789012345LL);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), 123456789012345LL);
}

// Test SetAttribute with uint64_t
TEST_F(XMLAttributeTest_71, SetAttribute_Uint64_71) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", (uint64_t)18446744073709551615ULL);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 18446744073709551615ULL);
}

// Test Next returns next attribute
TEST_F(XMLAttributeTest_71, Next_MultipleAttributes_71) {
    doc.Parse("<root first=\"1\" second=\"2\" third=\"3\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "first");
    
    attr = attr->Next();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "second");
    
    attr = attr->Next();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "third");
    
    attr = attr->Next();
    EXPECT_EQ(attr, nullptr);
}

// Test Next returns nullptr when no next attribute
TEST_F(XMLAttributeTest_71, Next_SingleAttribute_71) {
    doc.Parse("<root only=\"1\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Next(), nullptr);
}

// Test GetLineNum
TEST_F(XMLAttributeTest_71, GetLineNum_71) {
    doc.Parse("<root attr=\"value\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_GE(attr->GetLineNum(), 1);
}

// Test IntValue with empty string value
TEST_F(XMLAttributeTest_71, IntValue_EmptyString_71) {
    doc.Parse("<root attr=\"\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    // Should return 0 (default) since empty string is not a valid integer
    EXPECT_EQ(attr->IntValue(), 0);
}

// Test IntValue with floating point value (should truncate or parse partially)
TEST_F(XMLAttributeTest_71, IntValue_FloatingPoint_71) {
    doc.Parse("<root attr=\"3.7\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    // Behavior may vary; just ensure it doesn't crash
    int val = attr->IntValue();
    (void)val;
}

// Test BoolValue with numeric 1
TEST_F(XMLAttributeTest_71, BoolValue_NumericOne_71) {
    doc.Parse("<root attr=\"1\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_TRUE(attr->BoolValue());
}

// Test BoolValue with numeric 0
TEST_F(XMLAttributeTest_71, BoolValue_NumericZero_71) {
    doc.Parse("<root attr=\"0\"/>");
    const XMLAttribute* attr = doc.FirstChildElement("root")->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_FALSE(attr->BoolValue());
}

// Test that SetAttribute with negative int works correctly
TEST_F(XMLAttributeTest_71, SetAttribute_NegativeInt_71) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", -500);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), -500);
}

// Test IntValue after setting attribute to string representation of int
TEST_F(XMLAttributeTest_71, IntValue_AfterSetAttribute_71) {
    doc.Parse("<root attr=\"0\"/>");
    XMLElement* elem = doc.FirstChildElement("root");
    elem->SetAttribute("attr", "12345");
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 12345);
}
