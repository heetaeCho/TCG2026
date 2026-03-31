#include <gtest/gtest.h>
#include "tinyxml2.h"
#include <cstdint>
#include <climits>
#include <string>

using namespace tinyxml2;

// Helper: XMLAttribute is typically created through XMLDocument/XMLElement,
// since its constructor is private. We use the tinyxml2 API to create elements
// with attributes and then test the attribute behavior.

class XMLAttributeTest_221 : public ::testing::Test {
protected:
    XMLDocument doc;

    // Helper to create an element with a named attribute and return the attribute
    XMLElement* CreateElementWithAttribute(const char* attrName, const char* attrValue) {
        XMLElement* elem = doc.NewElement("test");
        doc.InsertFirstChild(elem);
        elem->SetAttribute(attrName, attrValue);
        return elem;
    }

    const XMLAttribute* GetAttribute(XMLElement* elem, const char* name) {
        return elem->FindAttribute(name);
    }
};

// Test SetAttribute(int64_t) with a positive value
TEST_F(XMLAttributeTest_221, SetAttributeInt64Positive_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", static_cast<int64_t>(1234567890123LL));
    
    int64_t result = 0;
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    XMLError err = attr->QueryInt64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 1234567890123LL);
}

// Test SetAttribute(int64_t) with zero
TEST_F(XMLAttributeTest_221, SetAttributeInt64Zero_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", static_cast<int64_t>(0));
    
    int64_t result = -1;
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    XMLError err = attr->QueryInt64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 0);
}

// Test SetAttribute(int64_t) with a negative value
TEST_F(XMLAttributeTest_221, SetAttributeInt64Negative_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", static_cast<int64_t>(-9876543210LL));
    
    int64_t result = 0;
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    XMLError err = attr->QueryInt64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, -9876543210LL);
}

// Test SetAttribute(int64_t) with INT64_MAX
TEST_F(XMLAttributeTest_221, SetAttributeInt64Max_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    int64_t maxVal = INT64_MAX;
    elem->SetAttribute("val", maxVal);
    
    int64_t result = 0;
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    XMLError err = attr->QueryInt64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, maxVal);
}

// Test SetAttribute(int64_t) with INT64_MIN
TEST_F(XMLAttributeTest_221, SetAttributeInt64Min_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    int64_t minVal = INT64_MIN;
    elem->SetAttribute("val", minVal);
    
    int64_t result = 0;
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    XMLError err = attr->QueryInt64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, minVal);
}

// Test SetAttribute(int64_t) value is reflected in Value() as a string
TEST_F(XMLAttributeTest_221, SetAttributeInt64ValueString_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", static_cast<int64_t>(42));
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "42");
}

// Test SetAttribute(int64_t) with negative value reflected in Value() string
TEST_F(XMLAttributeTest_221, SetAttributeInt64NegativeValueString_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", static_cast<int64_t>(-100));
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "-100");
}

// Test SetAttribute(int64_t) overwriting a previous value
TEST_F(XMLAttributeTest_221, SetAttributeInt64Overwrite_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", static_cast<int64_t>(100));
    elem->SetAttribute("val", static_cast<int64_t>(200));
    
    int64_t result = 0;
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    XMLError err = attr->QueryInt64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 200);
}

// Test SetAttribute(int64_t) with a value that fits in int range
TEST_F(XMLAttributeTest_221, SetAttributeInt64SmallValue_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", static_cast<int64_t>(1));
    
    int64_t result = 0;
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    XMLError err = attr->QueryInt64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 1);
}

// Test SetAttribute(int64_t) with -1
TEST_F(XMLAttributeTest_221, SetAttributeInt64NegativeOne_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", static_cast<int64_t>(-1));
    
    int64_t result = 0;
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    XMLError err = attr->QueryInt64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, -1);
}

// Test Int64Value() convenience method after SetAttribute(int64_t)
TEST_F(XMLAttributeTest_221, Int64ValueConvenience_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", static_cast<int64_t>(999999999999LL));
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), 999999999999LL);
}

// Test that setting int64_t attribute doesn't affect other attributes
TEST_F(XMLAttributeTest_221, SetAttributeInt64DoesNotAffectOthers_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("a", "hello");
    elem->SetAttribute("b", static_cast<int64_t>(12345));
    
    const XMLAttribute* attrA = elem->FindAttribute("a");
    const XMLAttribute* attrB = elem->FindAttribute("b");
    ASSERT_NE(attrA, nullptr);
    ASSERT_NE(attrB, nullptr);
    EXPECT_STREQ(attrA->Value(), "hello");
    EXPECT_EQ(attrB->Int64Value(), 12345);
}

// Test that int64_t value beyond int range is handled correctly
TEST_F(XMLAttributeTest_221, SetAttributeInt64BeyondIntRange_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    int64_t largeVal = static_cast<int64_t>(INT_MAX) + 1;
    elem->SetAttribute("val", largeVal);
    
    int64_t result = 0;
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    XMLError err = attr->QueryInt64Value(&result);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, largeVal);
}

// Test that querying as int when value is out of int range returns error or wrong value
// This tests QueryIntValue on a large int64 value
TEST_F(XMLAttributeTest_221, SetAttributeInt64QueryAsInt_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    int64_t largeVal = 9999999999999LL;
    elem->SetAttribute("val", largeVal);
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    // The Value() string should represent the large number
    std::string valStr = attr->Value();
    EXPECT_EQ(valStr, "9999999999999");
}

// Test SetAttribute(int64_t) and then printing the document
TEST_F(XMLAttributeTest_221, SetAttributeInt64PrintDocument_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", static_cast<int64_t>(7777777777LL));
    
    XMLPrinter printer;
    doc.Print(&printer);
    std::string output = printer.CStr();
    EXPECT_NE(output.find("7777777777"), std::string::npos);
}

// Test multiple SetAttribute(int64_t) calls on different attributes
TEST_F(XMLAttributeTest_221, SetMultipleInt64Attributes_221) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("x", static_cast<int64_t>(111));
    elem->SetAttribute("y", static_cast<int64_t>(222));
    elem->SetAttribute("z", static_cast<int64_t>(333));
    
    EXPECT_EQ(elem->FindAttribute("x")->Int64Value(), 111);
    EXPECT_EQ(elem->FindAttribute("y")->Int64Value(), 222);
    EXPECT_EQ(elem->FindAttribute("z")->Int64Value(), 333);
}
