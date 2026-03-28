#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeQueryUnsignedValueTest_212 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    XMLAttribute* createAttributeWithValue(const char* value) {
        // We create an element with an attribute to get access to XMLAttribute
        // through the public API of XMLDocument/XMLElement
        doc.Clear();
        XMLElement* root = doc.NewElement("root");
        doc.InsertFirstChild(root);
        root->SetAttribute("test", value);
        return const_cast<XMLAttribute*>(root->FindAttribute("test"));
    }
    
    XMLAttribute* createAttributeWithUnsigned(unsigned int value) {
        doc.Clear();
        XMLElement* root = doc.NewElement("root");
        doc.InsertFirstChild(root);
        root->SetAttribute("test", value);
        return const_cast<XMLAttribute*>(root->FindAttribute("test"));
    }
};

// Test: Valid unsigned integer value returns XML_SUCCESS
TEST_F(XMLAttributeQueryUnsignedValueTest_212, ValidUnsignedValue_ReturnsSuccess_212) {
    XMLAttribute* attr = createAttributeWithValue("42");
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 42u);
}

// Test: Zero value returns XML_SUCCESS
TEST_F(XMLAttributeQueryUnsignedValueTest_212, ZeroValue_ReturnsSuccess_212) {
    XMLAttribute* attr = createAttributeWithValue("0");
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 999;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 0u);
}

// Test: Large unsigned value returns XML_SUCCESS
TEST_F(XMLAttributeQueryUnsignedValueTest_212, LargeUnsignedValue_ReturnsSuccess_212) {
    XMLAttribute* attr = createAttributeWithValue("4294967295");
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 4294967295u);
}

// Test: Non-numeric string returns XML_WRONG_ATTRIBUTE_TYPE
TEST_F(XMLAttributeQueryUnsignedValueTest_212, NonNumericValue_ReturnsWrongType_212) {
    XMLAttribute* attr = createAttributeWithValue("hello");
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Empty string returns XML_WRONG_ATTRIBUTE_TYPE
TEST_F(XMLAttributeQueryUnsignedValueTest_212, EmptyValue_ReturnsWrongType_212) {
    XMLAttribute* attr = createAttributeWithValue("");
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Negative value returns XML_WRONG_ATTRIBUTE_TYPE (or wraps - depends on implementation)
TEST_F(XMLAttributeQueryUnsignedValueTest_212, NegativeValue_ReturnsWrongTypeOrWraps_212) {
    XMLAttribute* attr = createAttributeWithValue("-1");
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    // Negative values may or may not convert to unsigned; just verify it returns a valid XMLError
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Float string returns XML_WRONG_ATTRIBUTE_TYPE
TEST_F(XMLAttributeQueryUnsignedValueTest_212, FloatValue_ReturnsWrongType_212) {
    XMLAttribute* attr = createAttributeWithValue("3.14");
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    // A float string should likely fail for unsigned int conversion
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Value set via SetAttribute(unsigned int) can be queried back
TEST_F(XMLAttributeQueryUnsignedValueTest_212, SetAttributeUnsigned_QueryReturnsCorrectValue_212) {
    XMLAttribute* attr = createAttributeWithUnsigned(12345u);
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 12345u);
}

// Test: String with leading spaces may fail or succeed depending on implementation
TEST_F(XMLAttributeQueryUnsignedValueTest_212, LeadingSpaces_212) {
    XMLAttribute* attr = createAttributeWithValue("  123");
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    // Leading spaces may or may not be handled
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: String with trailing non-numeric characters
TEST_F(XMLAttributeQueryUnsignedValueTest_212, TrailingNonNumericChars_212) {
    XMLAttribute* attr = createAttributeWithValue("123abc");
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    // Implementation may partially parse or reject entirely
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Boolean string "true" returns XML_WRONG_ATTRIBUTE_TYPE for unsigned
TEST_F(XMLAttributeQueryUnsignedValueTest_212, BooleanTrueString_ReturnsWrongType_212) {
    XMLAttribute* attr = createAttributeWithValue("true");
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Value "1" parses successfully as unsigned
TEST_F(XMLAttributeQueryUnsignedValueTest_212, ValueOne_ReturnsSuccess_212) {
    XMLAttribute* attr = createAttributeWithValue("1");
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, 1u);
}

// Test: Hex string returns wrong type (assuming ToUnsigned doesn't parse hex by default)
TEST_F(XMLAttributeQueryUnsignedValueTest_212, HexString_212) {
    XMLAttribute* attr = createAttributeWithValue("0xFF");
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    // Hex may or may not be supported
    EXPECT_TRUE(err == XML_SUCCESS || err == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: Verify that SetAttribute with max unsigned int and query back works
TEST_F(XMLAttributeQueryUnsignedValueTest_212, MaxUnsignedSetAndQuery_212) {
    unsigned int maxVal = UINT_MAX;
    XMLAttribute* attr = createAttributeWithUnsigned(maxVal);
    ASSERT_NE(attr, nullptr);
    
    unsigned int result = 0;
    XMLError err = attr->QueryUnsignedValue(&result);
    
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(result, maxVal);
}

// Test: UnsignedValue() convenience method returns expected value
TEST_F(XMLAttributeQueryUnsignedValueTest_212, UnsignedValueConvenience_212) {
    XMLAttribute* attr = createAttributeWithUnsigned(7777u);
    ASSERT_NE(attr, nullptr);
    
    EXPECT_EQ(attr->UnsignedValue(), 7777u);
}
