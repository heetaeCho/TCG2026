#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetAttributeFloatTest_104 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem;

    void SetUp() override {
        elem = doc.NewElement("TestElement");
        doc.InsertFirstChild(elem);
    }
};

// Test setting a float attribute with a normal positive value
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributePositiveValue_104) {
    elem->SetAttribute("value", 3.14f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("value", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(3.14f, result);
}

// Test setting a float attribute with a negative value
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeNegativeValue_104) {
    elem->SetAttribute("neg", -2.5f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("neg", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(-2.5f, result);
}

// Test setting a float attribute with zero
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeZero_104) {
    elem->SetAttribute("zero", 0.0f);
    float result = 1.0f;
    XMLError err = elem->QueryFloatAttribute("zero", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(0.0f, result);
}

// Test setting a float attribute with a very small value
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeVerySmallValue_104) {
    elem->SetAttribute("tiny", 1.0e-10f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("tiny", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(1.0e-10f, result);
}

// Test setting a float attribute with a very large value
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeVeryLargeValue_104) {
    elem->SetAttribute("big", 1.0e30f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("big", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(1.0e30f, result);
}

// Test overwriting an existing float attribute with a new float value
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeOverwrite_104) {
    elem->SetAttribute("val", 1.0f);
    elem->SetAttribute("val", 99.99f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(99.99f, result);
}

// Test that setting a float attribute creates the attribute if it doesn't exist
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeCreatesAttribute_104) {
    // Initially, the attribute should not exist
    const XMLAttribute* attr = elem->FindAttribute("newattr");
    EXPECT_EQ(nullptr, attr);

    elem->SetAttribute("newattr", 42.0f);

    attr = elem->FindAttribute("newattr");
    EXPECT_NE(nullptr, attr);
    EXPECT_FLOAT_EQ(42.0f, attr->FloatValue());
}

// Test setting multiple different float attributes
TEST_F(XMLElementSetAttributeFloatTest_104, SetMultipleFloatAttributes_104) {
    elem->SetAttribute("a", 1.1f);
    elem->SetAttribute("b", 2.2f);
    elem->SetAttribute("c", 3.3f);

    EXPECT_FLOAT_EQ(1.1f, elem->FloatAttribute("a"));
    EXPECT_FLOAT_EQ(2.2f, elem->FloatAttribute("b"));
    EXPECT_FLOAT_EQ(3.3f, elem->FloatAttribute("c"));
}

// Test that FloatAttribute returns default value when attribute doesn't exist
TEST_F(XMLElementSetAttributeFloatTest_104, FloatAttributeDefaultValue_104) {
    float result = elem->FloatAttribute("nonexistent", -1.0f);
    EXPECT_FLOAT_EQ(-1.0f, result);
}

// Test setting a float attribute with negative zero
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeNegativeZero_104) {
    elem->SetAttribute("negzero", -0.0f);
    float result = 1.0f;
    XMLError err = elem->QueryFloatAttribute("negzero", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    // -0.0 and 0.0 should compare equal
    EXPECT_FLOAT_EQ(0.0f, result);
}

// Test that SetAttribute with float overwrites a previously set string attribute
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatOverwritesStringAttribute_104) {
    elem->SetAttribute("mixed", "hello");
    elem->SetAttribute("mixed", 7.77f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("mixed", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(7.77f, result);
}

// Test that SetAttribute with float overwrites a previously set int attribute
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatOverwritesIntAttribute_104) {
    elem->SetAttribute("num", 42);
    elem->SetAttribute("num", 3.14f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("num", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(3.14f, result);
}

// Test that the attribute name is correctly stored
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeNameCorrect_104) {
    elem->SetAttribute("myFloatAttr", 5.5f);
    const XMLAttribute* attr = elem->FindAttribute("myFloatAttr");
    EXPECT_NE(nullptr, attr);
    EXPECT_STREQ("myFloatAttr", attr->Name());
}

// Test float attribute with max float value
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeMaxFloat_104) {
    float maxVal = std::numeric_limits<float>::max();
    elem->SetAttribute("maxfloat", maxVal);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("maxfloat", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(maxVal, result);
}

// Test float attribute with min positive normal float value
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeMinFloat_104) {
    float minVal = std::numeric_limits<float>::min();
    elem->SetAttribute("minfloat", minVal);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("minfloat", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(minVal, result);
}

// Test float attribute with lowest (most negative) float value
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeLowestFloat_104) {
    float lowestVal = std::numeric_limits<float>::lowest();
    elem->SetAttribute("lowestfloat", lowestVal);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("lowestfloat", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(lowestVal, result);
}

// Test querying a float attribute that was never set returns error
TEST_F(XMLElementSetAttributeFloatTest_104, QueryFloatAttributeNotFound_104) {
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("doesnotexist", &result);
    EXPECT_NE(XML_SUCCESS, err);
}

// Test that the attribute value is accessible via the Value() string method
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeValueString_104) {
    elem->SetAttribute("strcheck", 1.5f);
    const XMLAttribute* attr = elem->FindAttribute("strcheck");
    EXPECT_NE(nullptr, attr);
    // The value should be a string representation of 1.5
    EXPECT_NE(nullptr, attr->Value());
}

// Test setting float on an attribute that was deleted and recreated
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAfterDelete_104) {
    elem->SetAttribute("temp", 10.0f);
    elem->DeleteAttribute("temp");
    // After deletion, FindAttribute should return null
    EXPECT_EQ(nullptr, elem->FindAttribute("temp"));
    // Set again
    elem->SetAttribute("temp", 20.0f);
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("temp", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(20.0f, result);
}

// Test setting float attribute value of 1.0
TEST_F(XMLElementSetAttributeFloatTest_104, SetFloatAttributeOne_104) {
    elem->SetAttribute("one", 1.0f);
    EXPECT_FLOAT_EQ(1.0f, elem->FloatAttribute("one"));
}

// Test that Attribute() (string query) returns non-null after setting float
TEST_F(XMLElementSetAttributeFloatTest_104, AttributeStringAfterSetFloat_104) {
    elem->SetAttribute("fattr", 2.718f);
    const char* val = elem->Attribute("fattr");
    EXPECT_NE(nullptr, val);
}
