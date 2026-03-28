#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeQueryUnsigned64Test_214 : public ::testing::Test {
protected:
    XMLDocument doc;

    // Helper to create an element with an attribute having the given value
    const XMLAttribute* createAttributeWithValue(const char* value) {
        doc.Clear();
        XMLElement* root = doc.NewElement("root");
        doc.InsertFirstChild(root);
        root->SetAttribute("testattr", value);
        return root->FindAttribute("testattr");
    }
};

// Test: Valid unsigned 64-bit integer value
TEST_F(XMLAttributeQueryUnsigned64Test_214, ValidUnsigned64Value_214) {
    const XMLAttribute* attr = createAttributeWithValue("12345");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 12345ULL);
}

// Test: Zero value
TEST_F(XMLAttributeQueryUnsigned64Test_214, ZeroValue_214) {
    const XMLAttribute* attr = createAttributeWithValue("0");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 999;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 0ULL);
}

// Test: Large unsigned 64-bit value (max uint64_t)
TEST_F(XMLAttributeQueryUnsigned64Test_214, MaxUnsigned64Value_214) {
    const XMLAttribute* attr = createAttributeWithValue("18446744073709551615");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_MAX);
}

// Test: Non-numeric string returns wrong attribute type
TEST_F(XMLAttributeQueryUnsigned64Test_214, NonNumericString_214) {
    const XMLAttribute* attr = createAttributeWithValue("hello");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Empty string returns wrong attribute type
TEST_F(XMLAttributeQueryUnsigned64Test_214, EmptyString_214) {
    const XMLAttribute* attr = createAttributeWithValue("");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Negative value returns wrong attribute type
TEST_F(XMLAttributeQueryUnsigned64Test_214, NegativeValue_214) {
    const XMLAttribute* attr = createAttributeWithValue("-1");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    // Negative values should not parse as unsigned 64
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Floating point string returns wrong attribute type
TEST_F(XMLAttributeQueryUnsigned64Test_214, FloatingPointString_214) {
    const XMLAttribute* attr = createAttributeWithValue("3.14");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: String with leading spaces might or might not parse
TEST_F(XMLAttributeQueryUnsigned64Test_214, LeadingWhitespace_214) {
    const XMLAttribute* attr = createAttributeWithValue("  42");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    // Behavior depends on implementation; just verify it returns a valid XMLError
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
    if (err == XML_SUCCESS) {
        EXPECT_EQ(value, 42ULL);
    }
}

// Test: Mixed alphanumeric string
TEST_F(XMLAttributeQueryUnsigned64Test_214, MixedAlphanumeric_214) {
    const XMLAttribute* attr = createAttributeWithValue("123abc");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Value set via SetAttribute(uint64_t) then queried
TEST_F(XMLAttributeQueryUnsigned64Test_214, SetAndQueryUnsigned64_214) {
    doc.Clear();
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->SetAttribute("val", static_cast<uint64_t>(9876543210ULL));
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 9876543210ULL);
}

// Test: Value "1" should be a valid unsigned64
TEST_F(XMLAttributeQueryUnsigned64Test_214, ValueOne_214) {
    const XMLAttribute* attr = createAttributeWithValue("1");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, 1ULL);
}

// Test: Boolean string "true" returns wrong attribute type
TEST_F(XMLAttributeQueryUnsigned64Test_214, BooleanTrueString_214) {
    const XMLAttribute* attr = createAttributeWithValue("true");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Unsigned64Value convenience method
TEST_F(XMLAttributeQueryUnsigned64Test_214, Unsigned64ValueConvenience_214) {
    doc.Clear();
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    root->SetAttribute("val", static_cast<uint64_t>(42ULL));
    const XMLAttribute* attr = root->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 42ULL);
}

// Test: Large value just under max
TEST_F(XMLAttributeQueryUnsigned64Test_214, LargeValueBelowMax_214) {
    const XMLAttribute* attr = createAttributeWithValue("18446744073709551614");
    ASSERT_NE(attr, nullptr);
    uint64_t value = 0;
    XMLError err = attr->QueryUnsigned64Value(&value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(value, UINT64_MAX - 1);
}
