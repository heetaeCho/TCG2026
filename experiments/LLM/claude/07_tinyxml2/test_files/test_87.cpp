#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryFloatAttributeTest_87 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: QueryFloatAttribute returns XML_NO_ATTRIBUTE when attribute does not exist
TEST_F(QueryFloatAttributeTest_87, NonExistentAttributeReturnsNoAttribute_87) {
    const char* xml = "<element />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("nonexistent", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test: QueryFloatAttribute successfully reads a valid float attribute
TEST_F(QueryFloatAttributeTest_87, ValidFloatAttributeReturnsSuccess_87) {
    const char* xml = "<element attr=\"3.14\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("attr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 3.14f);
}

// Test: QueryFloatAttribute reads an integer value as float
TEST_F(QueryFloatAttributeTest_87, IntegerValueAsFloatReturnsSuccess_87) {
    const char* xml = "<element attr=\"42\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("attr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 42.0f);
}

// Test: QueryFloatAttribute returns WRONG_ATTRIBUTE_TYPE for non-numeric string
TEST_F(QueryFloatAttributeTest_87, NonNumericStringReturnsWrongType_87) {
    const char* xml = "<element attr=\"hello\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("attr", &value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryFloatAttribute reads negative float value
TEST_F(QueryFloatAttributeTest_87, NegativeFloatValueReturnsSuccess_87) {
    const char* xml = "<element attr=\"-2.5\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("attr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, -2.5f);
}

// Test: QueryFloatAttribute reads zero value
TEST_F(QueryFloatAttributeTest_87, ZeroValueReturnsSuccess_87) {
    const char* xml = "<element attr=\"0.0\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 1.0f;
    XMLError result = element->QueryFloatAttribute("attr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 0.0f);
}

// Test: QueryFloatAttribute with very large float value
TEST_F(QueryFloatAttributeTest_87, LargeFloatValueReturnsSuccess_87) {
    const char* xml = "<element attr=\"1.0e+30\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("attr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 1.0e+30f);
}

// Test: QueryFloatAttribute with very small float value
TEST_F(QueryFloatAttributeTest_87, SmallFloatValueReturnsSuccess_87) {
    const char* xml = "<element attr=\"1.0e-10\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("attr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 1.0e-10f);
}

// Test: QueryFloatAttribute with empty string attribute value
TEST_F(QueryFloatAttributeTest_87, EmptyStringAttributeReturnsWrongType_87) {
    const char* xml = "<element attr=\"\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("attr", &value);
    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryFloatAttribute selects correct attribute among multiple
TEST_F(QueryFloatAttributeTest_87, CorrectAttributeSelectedAmongMultiple_87) {
    const char* xml = "<element a=\"1.1\" b=\"2.2\" c=\"3.3\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("b", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 2.2f);
}

// Test: QueryFloatAttribute with attribute set via SetAttribute(float)
TEST_F(QueryFloatAttributeTest_87, SetAttributeFloatThenQuery_87) {
    const char* xml = "<element />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    element->SetAttribute("myattr", 99.5f);
    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("myattr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 99.5f);
}

// Test: QueryFloatAttribute on element with no attributes at all
TEST_F(QueryFloatAttributeTest_87, ElementWithNoAttributesReturnsNoAttribute_87) {
    const char* xml = "<root><child>text</child></root>";
    doc.Parse(xml);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    float value = 0.0f;
    XMLError result = root->QueryFloatAttribute("anything", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test: QueryFloatAttribute with attribute name that is a substring of existing
TEST_F(QueryFloatAttributeTest_87, SubstringAttributeNameReturnsNoAttribute_87) {
    const char* xml = "<element myattr=\"1.0\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("my", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test: QueryFloatAttribute with positive sign prefix
TEST_F(QueryFloatAttributeTest_87, PositiveSignPrefixReturnsSuccess_87) {
    const char* xml = "<element attr=\"+5.5\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("attr", &value);
    // Depending on implementation, +5.5 may or may not parse. Check for success or wrong type.
    if (result == XML_SUCCESS) {
        EXPECT_FLOAT_EQ(value, 5.5f);
    } else {
        EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);
    }
}

// Test: QueryFloatAttribute after deleting the attribute returns NO_ATTRIBUTE
TEST_F(QueryFloatAttributeTest_87, DeletedAttributeReturnsNoAttribute_87) {
    const char* xml = "<element attr=\"1.5\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    element->DeleteAttribute("attr");
    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("attr", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}

// Test: QueryFloatAttribute with scientific notation
TEST_F(QueryFloatAttributeTest_87, ScientificNotationReturnsSuccess_87) {
    const char* xml = "<element attr=\"3.14e2\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("attr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 314.0f);
}

// Test: QueryFloatAttribute case sensitivity of attribute names
TEST_F(QueryFloatAttributeTest_87, CaseSensitiveAttributeName_87) {
    const char* xml = "<element Attr=\"1.0\" attr=\"2.0\" />";
    doc.Parse(xml);
    XMLElement* element = doc.RootElement();
    ASSERT_NE(element, nullptr);

    float value = 0.0f;
    XMLError result = element->QueryFloatAttribute("Attr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 1.0f);

    result = element->QueryFloatAttribute("attr", &value);
    EXPECT_EQ(result, XML_SUCCESS);
    EXPECT_FLOAT_EQ(value, 2.0f);

    result = element->QueryFloatAttribute("ATTR", &value);
    EXPECT_EQ(result, XML_NO_ATTRIBUTE);
}
