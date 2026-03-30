#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLElement tests
class XMLElementTest_104 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* element;

    void SetUp() override {
        element = doc.NewElement("TestElement");
        doc.InsertEndChild(element);
    }
};

// Normal operation: set a single float attribute and verify retrieval
TEST_F(XMLElementTest_104, SetFloatAttribute_Normal_104) {
    float value = 3.14159f;
    element->SetAttribute("pi", value);

    float queriedValue = element->FloatAttribute("pi", 0.0f);
    EXPECT_FLOAT_EQ(queriedValue, value);
}

// Boundary condition: set attribute to 0.0
TEST_F(XMLElementTest_104, SetFloatAttribute_ZeroValue_104) {
    element->SetAttribute("zero", 0.0f);
    float queriedValue = element->FloatAttribute("zero", 1.0f);
    EXPECT_FLOAT_EQ(queriedValue, 0.0f);
}

// Boundary condition: set attribute to very large float
TEST_F(XMLElementTest_104, SetFloatAttribute_MaxFloat_104) {
    float maxFloat = std::numeric_limits<float>::max();
    element->SetAttribute("max", maxFloat);
    float queriedValue = element->FloatAttribute("max", 0.0f);
    EXPECT_FLOAT_EQ(queriedValue, maxFloat);
}

// Boundary condition: set attribute to very small (negative) float
TEST_F(XMLElementTest_104, SetFloatAttribute_MinFloat_104) {
    float minFloat = -std::numeric_limits<float>::max();
    element->SetAttribute("min", minFloat);
    float queriedValue = element->FloatAttribute("min", 0.0f);
    EXPECT_FLOAT_EQ(queriedValue, minFloat);
}

// Exceptional case: set attribute with empty name
TEST_F(XMLElementTest_104, SetFloatAttribute_EmptyName_104) {
    element->SetAttribute("", 1.23f);
    // Expect querying with empty name returns default value (attribute not found)
    float queriedValue = element->FloatAttribute("", 0.0f);
    EXPECT_FLOAT_EQ(queriedValue, 0.0f);
}

// Exceptional case: set attribute with nullptr name
TEST_F(XMLElementTest_104, SetFloatAttribute_NullptrName_104) {
    // According to tinyxml2 spec, passing nullptr should be ignored, no crash
    element->SetAttribute(nullptr, 1.23f);
    // Querying with nullptr should also return default value
    float queriedValue = element->FloatAttribute(nullptr, 0.0f);
    EXPECT_FLOAT_EQ(queriedValue, 0.0f);
}

// Normal operation: overwrite existing float attribute
TEST_F(XMLElementTest_104, SetFloatAttribute_Overwrite_104) {
    element->SetAttribute("value", 1.0f);
    element->SetAttribute("value", 2.0f);

    float queriedValue = element->FloatAttribute("value", 0.0f);
    EXPECT_FLOAT_EQ(queriedValue, 2.0f);
}

// Normal operation: multiple float attributes
TEST_F(XMLElementTest_104, SetFloatAttribute_Multiple_104) {
    element->SetAttribute("attr1", 1.1f);
    element->SetAttribute("attr2", 2.2f);
    element->SetAttribute("attr3", 3.3f);

    EXPECT_FLOAT_EQ(element->FloatAttribute("attr1", 0.0f), 1.1f);
    EXPECT_FLOAT_EQ(element->FloatAttribute("attr2", 0.0f), 2.2f);
    EXPECT_FLOAT_EQ(element->FloatAttribute("attr3", 0.0f), 3.3f);
}
