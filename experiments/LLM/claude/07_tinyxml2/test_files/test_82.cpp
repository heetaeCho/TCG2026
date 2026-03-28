#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryUnsignedAttributeTest_82 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test: QueryUnsignedAttribute returns XML_NO_ATTRIBUTE when attribute doesn't exist
TEST_F(QueryUnsignedAttributeTest_82, NonExistentAttributeReturnsNoAttribute_82) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("nonexistent", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test: QueryUnsignedAttribute returns XML_SUCCESS for a valid unsigned integer attribute
TEST_F(QueryUnsignedAttributeTest_82, ValidUnsignedAttributeReturnsSuccess_82) {
    doc.Parse("<root val=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("val", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 42u);
}

// Test: QueryUnsignedAttribute returns XML_SUCCESS for zero value
TEST_F(QueryUnsignedAttributeTest_82, ZeroValueAttribute_82) {
    doc.Parse("<root val=\"0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 999;
    XMLError result = root->QueryUnsignedAttribute("val", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 0u);
}

// Test: QueryUnsignedAttribute with a large unsigned value
TEST_F(QueryUnsignedAttributeTest_82, LargeUnsignedValue_82) {
    doc.Parse("<root val=\"4294967295\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("val", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 4294967295u);
}

// Test: QueryUnsignedAttribute returns wrong type for non-numeric string
TEST_F(QueryUnsignedAttributeTest_82, NonNumericStringReturnsWrongType_82) {
    doc.Parse("<root val=\"hello\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("val", &value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryUnsignedAttribute with an empty string attribute
TEST_F(QueryUnsignedAttributeTest_82, EmptyStringAttributeReturnsWrongType_82) {
    doc.Parse("<root val=\"\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("val", &value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryUnsignedAttribute with multiple attributes, querying the correct one
TEST_F(QueryUnsignedAttributeTest_82, MultipleAttributesQueryCorrectOne_82) {
    doc.Parse("<root a=\"10\" b=\"20\" c=\"30\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("b", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 20u);
}

// Test: QueryUnsignedAttribute with multiple attributes, querying non-existent one
TEST_F(QueryUnsignedAttributeTest_82, MultipleAttributesQueryNonExistent_82) {
    doc.Parse("<root a=\"10\" b=\"20\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("d", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test: QueryUnsignedAttribute with floating point value returns wrong type
TEST_F(QueryUnsignedAttributeTest_82, FloatingPointValueReturnsWrongType_82) {
    doc.Parse("<root val=\"3.14\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("val", &value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryUnsignedAttribute with negative value
TEST_F(QueryUnsignedAttributeTest_82, NegativeValueBehavior_82) {
    doc.Parse("<root val=\"-1\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("val", &value);
    // Negative values may or may not be parsed as unsigned; just check it doesn't crash
    // The behavior may vary, but we check it returns either SUCCESS or WRONG_ATTRIBUTE_TYPE
    EXPECT_TRUE(result == XML_SUCCESS || result == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryUnsignedAttribute after SetAttribute with unsigned value
TEST_F(QueryUnsignedAttributeTest_82, SetThenQueryUnsignedAttribute_82) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    root->SetAttribute("count", (unsigned int)100);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("count", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 100u);
}

// Test: QueryUnsignedAttribute with value "1"
TEST_F(QueryUnsignedAttributeTest_82, ValueOne_82) {
    doc.Parse("<root val=\"1\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("val", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 1u);
}

// Test: QueryUnsignedAttribute with leading/trailing spaces in value
TEST_F(QueryUnsignedAttributeTest_82, ValueWithSpaces_82) {
    doc.Parse("<root val=\" 42 \"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("val", &value);
    // Leading spaces might be handled; behavior depends on implementation
    EXPECT_TRUE(result == XML_SUCCESS || result == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryUnsignedAttribute case sensitivity of attribute name
TEST_F(QueryUnsignedAttributeTest_82, AttributeNameCaseSensitive_82) {
    doc.Parse("<root Val=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    // Query with different case
    XMLError result = root->QueryUnsignedAttribute("val", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
    
    // Query with correct case
    result = root->QueryUnsignedAttribute("Val", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 42u);
}

// Test: QueryUnsignedAttribute on element with no attributes
TEST_F(QueryUnsignedAttributeTest_82, ElementWithNoAttributes_82) {
    doc.Parse("<root></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("anything", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test: QueryUnsignedAttribute with hex-like string
TEST_F(QueryUnsignedAttributeTest_82, HexStringValue_82) {
    doc.Parse("<root val=\"0xFF\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("val", &value);
    // Hex parsing behavior depends on implementation
    EXPECT_TRUE(result == XML_SUCCESS || result == XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryUnsignedAttribute after deleting and re-adding attribute
TEST_F(QueryUnsignedAttributeTest_82, DeleteAndReAddAttribute_82) {
    doc.Parse("<root val=\"10\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    root->DeleteAttribute("val");
    
    unsigned int value = 0;
    XMLError result = root->QueryUnsignedAttribute("val", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
    
    root->SetAttribute("val", (unsigned int)55);
    result = root->QueryUnsignedAttribute("val", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 55u);
}

// Test: QueryUnsignedAttribute on nested element
TEST_F(QueryUnsignedAttributeTest_82, NestedElementAttribute_82) {
    doc.Parse("<root><child val=\"77\"/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    
    unsigned int value = 0;
    XMLError result = child->QueryUnsignedAttribute("val", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_EQ(value, 77u);
}

// Test: QueryUnsignedAttribute does not modify value on failure (no attribute)
TEST_F(QueryUnsignedAttributeTest_82, ValueUnchangedOnNoAttribute_82) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    unsigned int value = 12345;
    XMLError result = root->QueryUnsignedAttribute("missing", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
    EXPECT_EQ(value, 12345u);
}
