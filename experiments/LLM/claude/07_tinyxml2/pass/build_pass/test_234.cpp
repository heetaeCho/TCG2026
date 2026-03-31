#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementFloatAttributeTest_234 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test that FloatAttribute returns the set float value when the attribute exists
TEST_F(XMLElementFloatAttributeTest_234, ReturnsSetFloatValue_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("value", 3.14f);
    
    float result = elem->FloatAttribute("value", 0.0f);
    EXPECT_FLOAT_EQ(result, 3.14f);
}

// Test that FloatAttribute returns the default value when the attribute does not exist
TEST_F(XMLElementFloatAttributeTest_234, ReturnsDefaultWhenAttributeMissing_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    
    float result = elem->FloatAttribute("nonexistent", 42.5f);
    EXPECT_FLOAT_EQ(result, 42.5f);
}

// Test that FloatAttribute returns the default value of 0.0 when no attribute and default is 0
TEST_F(XMLElementFloatAttributeTest_234, ReturnsZeroDefault_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    
    float result = elem->FloatAttribute("missing", 0.0f);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Test that FloatAttribute handles negative float values
TEST_F(XMLElementFloatAttributeTest_234, HandlesNegativeFloat_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("neg", -123.456f);
    
    float result = elem->FloatAttribute("neg", 0.0f);
    EXPECT_FLOAT_EQ(result, -123.456f);
}

// Test that FloatAttribute handles zero value attribute
TEST_F(XMLElementFloatAttributeTest_234, HandlesZeroValue_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("zero", 0.0f);
    
    float result = elem->FloatAttribute("zero", 99.9f);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Test that FloatAttribute handles very large float values
TEST_F(XMLElementFloatAttributeTest_234, HandlesLargeFloat_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("big", 1.0e30f);
    
    float result = elem->FloatAttribute("big", 0.0f);
    EXPECT_FLOAT_EQ(result, 1.0e30f);
}

// Test that FloatAttribute handles very small float values
TEST_F(XMLElementFloatAttributeTest_234, HandlesSmallFloat_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("small", 1.0e-30f);
    
    float result = elem->FloatAttribute("small", 0.0f);
    EXPECT_FLOAT_EQ(result, 1.0e-30f);
}

// Test that FloatAttribute returns default when attribute has non-numeric string value
TEST_F(XMLElementFloatAttributeTest_234, ReturnsDefaultForNonNumericString_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("text", "hello");
    
    float result = elem->FloatAttribute("text", 7.77f);
    // Non-numeric string - QueryFloatAttribute should fail, default returned
    // The exact behavior depends on implementation, but we expect either 7.77 or 0
    // Based on typical tinyxml2 behavior, non-parseable returns default
    EXPECT_FLOAT_EQ(result, 7.77f);
}

// Test FloatAttribute with negative default value
TEST_F(XMLElementFloatAttributeTest_234, NegativeDefaultValue_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    
    float result = elem->FloatAttribute("missing", -99.99f);
    EXPECT_FLOAT_EQ(result, -99.99f);
}

// Test FloatAttribute after attribute is deleted
TEST_F(XMLElementFloatAttributeTest_234, ReturnsDefaultAfterAttributeDeleted_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 5.5f);
    
    EXPECT_FLOAT_EQ(elem->FloatAttribute("val", 0.0f), 5.5f);
    
    elem->DeleteAttribute("val");
    
    float result = elem->FloatAttribute("val", 1.1f);
    EXPECT_FLOAT_EQ(result, 1.1f);
}

// Test FloatAttribute with multiple attributes on the same element
TEST_F(XMLElementFloatAttributeTest_234, MultipleAttributes_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("a", 1.1f);
    elem->SetAttribute("b", 2.2f);
    elem->SetAttribute("c", 3.3f);
    
    EXPECT_FLOAT_EQ(elem->FloatAttribute("a", 0.0f), 1.1f);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("b", 0.0f), 2.2f);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("c", 0.0f), 3.3f);
}

// Test FloatAttribute with attribute set as integer
TEST_F(XMLElementFloatAttributeTest_234, IntegerAttributeAsFloat_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("intval", 42);
    
    float result = elem->FloatAttribute("intval", 0.0f);
    EXPECT_FLOAT_EQ(result, 42.0f);
}

// Test FloatAttribute with attribute updated/overwritten
TEST_F(XMLElementFloatAttributeTest_234, OverwrittenAttribute_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 1.0f);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("val", 0.0f), 1.0f);
    
    elem->SetAttribute("val", 2.0f);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("val", 0.0f), 2.0f);
}

// Test FloatAttribute parsed from XML string
TEST_F(XMLElementFloatAttributeTest_234, ParsedFromXMLString_234) {
    const char* xml = "<root value=\"6.28\"/>";
    doc.Parse(xml);
    
    XMLElement* elem = doc.RootElement();
    ASSERT_NE(elem, nullptr);
    
    float result = elem->FloatAttribute("value", 0.0f);
    EXPECT_FLOAT_EQ(result, 6.28f);
}

// Test FloatAttribute with empty string attribute name query
TEST_F(XMLElementFloatAttributeTest_234, EmptyAttributeName_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("val", 5.0f);
    
    float result = elem->FloatAttribute("", 99.0f);
    EXPECT_FLOAT_EQ(result, 99.0f);
}

// Test FloatAttribute with attribute set as double
TEST_F(XMLElementFloatAttributeTest_234, DoubleAttributeAsFloat_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    elem->SetAttribute("dblval", 3.14159265358979);
    
    float result = elem->FloatAttribute("dblval", 0.0f);
    EXPECT_NEAR(result, 3.14159265f, 1e-5f);
}

// Test FloatAttribute default value with max float
TEST_F(XMLElementFloatAttributeTest_234, MaxFloatDefault_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    
    float result = elem->FloatAttribute("missing", std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(result, std::numeric_limits<float>::max());
}

// Test FloatAttribute default value with min float
TEST_F(XMLElementFloatAttributeTest_234, MinFloatDefault_234) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    
    float result = elem->FloatAttribute("missing", std::numeric_limits<float>::lowest());
    EXPECT_FLOAT_EQ(result, std::numeric_limits<float>::lowest());
}
