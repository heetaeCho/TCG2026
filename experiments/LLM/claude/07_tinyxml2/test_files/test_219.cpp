#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// We need to create XMLAttribute instances through the XMLDocument/XMLElement API
// since the constructor is private and the destructor is virtual private.

class XMLAttributeTest_219 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem;

    void SetUp() override {
        elem = doc.NewElement("test");
        doc.InsertFirstChild(elem);
    }
};

// Test SetAttribute(int) with a positive value
TEST_F(XMLAttributeTest_219, SetAttributeIntPositive_219) {
    elem->SetAttribute("attr", 42);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "42");
    EXPECT_EQ(attr->IntValue(), 42);
}

// Test SetAttribute(int) with zero
TEST_F(XMLAttributeTest_219, SetAttributeIntZero_219) {
    elem->SetAttribute("attr", 0);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "0");
    EXPECT_EQ(attr->IntValue(), 0);
}

// Test SetAttribute(int) with a negative value
TEST_F(XMLAttributeTest_219, SetAttributeIntNegative_219) {
    elem->SetAttribute("attr", -100);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "-100");
    EXPECT_EQ(attr->IntValue(), -100);
}

// Test SetAttribute(int) with INT_MAX
TEST_F(XMLAttributeTest_219, SetAttributeIntMax_219) {
    elem->SetAttribute("attr", INT_MAX);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    XMLError err = attr->QueryIntValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, INT_MAX);
}

// Test SetAttribute(int) with INT_MIN
TEST_F(XMLAttributeTest_219, SetAttributeIntMin_219) {
    elem->SetAttribute("attr", INT_MIN);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    XMLError err = attr->QueryIntValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, INT_MIN);
}

// Test SetAttribute(int) with value 1
TEST_F(XMLAttributeTest_219, SetAttributeIntOne_219) {
    elem->SetAttribute("attr", 1);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "1");
}

// Test SetAttribute(int) with value -1
TEST_F(XMLAttributeTest_219, SetAttributeIntNegativeOne_219) {
    elem->SetAttribute("attr", -1);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "-1");
}

// Test QueryIntValue returns correct value after SetAttribute(int)
TEST_F(XMLAttributeTest_219, QueryIntValueAfterSetInt_219) {
    elem->SetAttribute("attr", 12345);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    XMLError err = attr->QueryIntValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 12345);
}

// Test overwriting an attribute with SetAttribute(int)
TEST_F(XMLAttributeTest_219, SetAttributeIntOverwrite_219) {
    elem->SetAttribute("attr", 10);
    elem->SetAttribute("attr", 20);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 20);
}

// Test SetAttribute(unsigned int)
TEST_F(XMLAttributeTest_219, SetAttributeUnsigned_219) {
    elem->SetAttribute("attr", (unsigned int)999);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    unsigned int val = 0;
    XMLError err = attr->QueryUnsignedValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 999u);
}

// Test SetAttribute(bool) true
TEST_F(XMLAttributeTest_219, SetAttributeBoolTrue_219) {
    elem->SetAttribute("attr", true);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

// Test SetAttribute(bool) false
TEST_F(XMLAttributeTest_219, SetAttributeBoolFalse_219) {
    elem->SetAttribute("attr", false);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    bool val = true;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(val);
}

// Test SetAttribute(double)
TEST_F(XMLAttributeTest_219, SetAttributeDouble_219) {
    elem->SetAttribute("attr", 3.14159);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    XMLError err = attr->QueryDoubleValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 3.14159, 1e-5);
}

// Test SetAttribute(float)
TEST_F(XMLAttributeTest_219, SetAttributeFloat_219) {
    elem->SetAttribute("attr", 2.5f);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    float val = 0.0f;
    XMLError err = attr->QueryFloatValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 2.5f, 1e-5f);
}

// Test SetAttribute(const char*)
TEST_F(XMLAttributeTest_219, SetAttributeString_219) {
    elem->SetAttribute("attr", "hello");
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello");
}

// Test SetAttribute(int64_t)
TEST_F(XMLAttributeTest_219, SetAttributeInt64_219) {
    int64_t bigVal = 9223372036854775807LL; // INT64_MAX
    elem->SetAttribute("attr", bigVal);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int64_t val = 0;
    XMLError err = attr->QueryInt64Value(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, bigVal);
}

// Test SetAttribute(uint64_t)
TEST_F(XMLAttributeTest_219, SetAttributeUint64_219) {
    uint64_t bigVal = 18446744073709551615ULL; // UINT64_MAX
    elem->SetAttribute("attr", bigVal);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    uint64_t val = 0;
    XMLError err = attr->QueryUnsigned64Value(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, bigVal);
}

// Test Name() returns correct attribute name
TEST_F(XMLAttributeTest_219, AttributeName_219) {
    elem->SetAttribute("myattr", 42);
    const XMLAttribute* attr = elem->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
}

// Test Next() attribute chaining
TEST_F(XMLAttributeTest_219, NextAttribute_219) {
    elem->SetAttribute("first", 1);
    elem->SetAttribute("second", 2);
    const XMLAttribute* attr = elem->FirstAttribute();
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "first");
    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "second");
    EXPECT_EQ(next->Next(), nullptr);
}

// Test QueryIntValue returns error when attribute has non-integer value
TEST_F(XMLAttributeTest_219, QueryIntValueNonInteger_219) {
    elem->SetAttribute("attr", "notanumber");
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    XMLError err = attr->QueryIntValue(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test that setting int then querying double works (cross-type query)
TEST_F(XMLAttributeTest_219, SetIntQueryDouble_219) {
    elem->SetAttribute("attr", 42);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    XMLError err = attr->QueryDoubleValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

// Test SetAttribute(int) with large positive number
TEST_F(XMLAttributeTest_219, SetAttributeIntLargePositive_219) {
    elem->SetAttribute("attr", 2147483647);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "2147483647");
}

// Test that the value is preserved through print/parse round-trip
TEST_F(XMLAttributeTest_219, RoundTripInt_219) {
    elem->SetAttribute("num", -99999);
    
    XMLPrinter printer;
    doc.Print(&printer);
    
    XMLDocument doc2;
    doc2.Parse(printer.CStr());
    EXPECT_EQ(doc2.ErrorID(), XML_SUCCESS);
    
    const XMLElement* elem2 = doc2.FirstChildElement("test");
    ASSERT_NE(elem2, nullptr);
    int val = 0;
    XMLError err = elem2->QueryIntAttribute("num", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, -99999);
}

// Test multiple SetAttribute(int) calls on same attribute
TEST_F(XMLAttributeTest_219, MultipleSetAttributeInt_219) {
    elem->SetAttribute("attr", 1);
    elem->SetAttribute("attr", 2);
    elem->SetAttribute("attr", 3);
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 3);
}

// Test GetLineNum returns a valid line number
TEST_F(XMLAttributeTest_219, GetLineNum_219) {
    const char* xml = "<root attr=\"42\"/>";
    doc.Parse(xml);
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_GE(attr->GetLineNum(), 1);
}
