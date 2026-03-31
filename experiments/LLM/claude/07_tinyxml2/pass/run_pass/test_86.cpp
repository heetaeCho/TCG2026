#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementQueryDoubleAttributeTest_86 : public ::testing::Test {
protected:
    XMLDocument doc;

    void SetUp() override {
    }
};

// Test: QueryDoubleAttribute returns XML_SUCCESS for a valid double attribute
TEST_F(XMLElementQueryDoubleAttributeTest_86, ValidDoubleAttribute_86) {
    doc.Parse("<root value=\"3.14\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("value", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 3.14);
}

// Test: QueryDoubleAttribute returns XML_NO_ATTRIBUTE when attribute does not exist
TEST_F(XMLElementQueryDoubleAttributeTest_86, NonExistentAttribute_86) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test: QueryDoubleAttribute returns XML_WRONG_ATTRIBUTE_TYPE for non-numeric string
TEST_F(XMLElementQueryDoubleAttributeTest_86, WrongAttributeType_86) {
    doc.Parse("<root value=\"not_a_number\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("value", &value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryDoubleAttribute handles integer value correctly (integer is valid double)
TEST_F(XMLElementQueryDoubleAttributeTest_86, IntegerValueAsDouble_86) {
    doc.Parse("<root value=\"42\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("value", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 42.0);
}

// Test: QueryDoubleAttribute handles negative double value
TEST_F(XMLElementQueryDoubleAttributeTest_86, NegativeDoubleValue_86) {
    doc.Parse("<root value=\"-2.718\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("value", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, -2.718);
}

// Test: QueryDoubleAttribute handles zero value
TEST_F(XMLElementQueryDoubleAttributeTest_86, ZeroValue_86) {
    doc.Parse("<root value=\"0.0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 999.0;
    XMLError err = root->QueryDoubleAttribute("value", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 0.0);
}

// Test: QueryDoubleAttribute handles very large double value
TEST_F(XMLElementQueryDoubleAttributeTest_86, VeryLargeValue_86) {
    doc.Parse("<root value=\"1.7976931348623157e+308\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("value", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 1.7976931348623157e+308);
}

// Test: QueryDoubleAttribute handles very small positive double value
TEST_F(XMLElementQueryDoubleAttributeTest_86, VerySmallPositiveValue_86) {
    doc.Parse("<root value=\"2.2250738585072014e-308\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("value", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(value, 2.2250738585072014e-308, 1e-320);
}

// Test: QueryDoubleAttribute with scientific notation
TEST_F(XMLElementQueryDoubleAttributeTest_86, ScientificNotation_86) {
    doc.Parse("<root value=\"1.5e10\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("value", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 1.5e10);
}

// Test: QueryDoubleAttribute with empty string attribute
TEST_F(XMLElementQueryDoubleAttributeTest_86, EmptyStringAttribute_86) {
    doc.Parse("<root value=\"\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("value", &value);
    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

// Test: QueryDoubleAttribute with multiple attributes, querying the correct one
TEST_F(XMLElementQueryDoubleAttributeTest_86, MultipleAttributes_86) {
    doc.Parse("<root a=\"1.1\" b=\"2.2\" c=\"3.3\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("b", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 2.2);
}

// Test: QueryDoubleAttribute with multiple attributes, querying a missing one
TEST_F(XMLElementQueryDoubleAttributeTest_86, MultipleAttributesMissingOne_86) {
    doc.Parse("<root a=\"1.1\" b=\"2.2\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("c", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test: QueryDoubleAttribute with attribute set via SetAttribute(double)
TEST_F(XMLElementQueryDoubleAttributeTest_86, SetAttributeThenQuery_86) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    root->SetAttribute("pi", 3.14159265358979);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("pi", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(value, 3.14159265358979, 1e-10);
}

// Test: QueryDoubleAttribute with negative zero
TEST_F(XMLElementQueryDoubleAttributeTest_86, NegativeZero_86) {
    doc.Parse("<root value=\"-0.0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 1.0;
    XMLError err = root->QueryDoubleAttribute("value", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 0.0);
}

// Test: QueryDoubleAttribute does not modify value on missing attribute
TEST_F(XMLElementQueryDoubleAttributeTest_86, ValueUnchangedOnMissing_86) {
    doc.Parse("<root/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 99.99;
    XMLError err = root->QueryDoubleAttribute("missing", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_DOUBLE_EQ(value, 99.99);
}

// Test: QueryDoubleAttribute with attribute name that is a substring of existing attribute
TEST_F(XMLElementQueryDoubleAttributeTest_86, SubstringAttributeName_86) {
    doc.Parse("<root value_long=\"5.5\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("value", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test: QueryDoubleAttribute with positive sign prefix
TEST_F(XMLElementQueryDoubleAttributeTest_86, PositiveSignPrefix_86) {
    doc.Parse("<root value=\"+1.5\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    XMLError err = root->QueryDoubleAttribute("value", &value);
    // Depending on implementation, +1.5 may be parsed correctly
    if (err == XML_SUCCESS) {
        EXPECT_DOUBLE_EQ(value, 1.5);
    } else {
        EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
    }
}

// Test: QueryDoubleAttribute case sensitivity of attribute name
TEST_F(XMLElementQueryDoubleAttributeTest_86, CaseSensitiveName_86) {
    doc.Parse("<root Value=\"1.0\"/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    double value = 0.0;
    // "value" (lowercase) should not match "Value" (uppercase first letter)
    XMLError err = root->QueryDoubleAttribute("value", &value);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);

    // "Value" should match
    err = root->QueryDoubleAttribute("Value", &value);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(value, 1.0);
}
