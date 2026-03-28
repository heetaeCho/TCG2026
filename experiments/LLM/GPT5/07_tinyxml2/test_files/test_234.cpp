// TEST_ID: 234
#include <cfloat>
#include <cmath>

#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class FloatAttributeTest_234 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        // Create a minimal document with a single element to test against.
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
    }
};

TEST_F(FloatAttributeTest_234, ReturnsDefaultWhenAttributeMissing_234) {
    const float defaultValue = 3.14f;

    // Attribute does not exist -> should return provided default value.
    EXPECT_FLOAT_EQ(elem->FloatAttribute("missing", defaultValue), defaultValue);
}

TEST_F(FloatAttributeTest_234, ReturnsValueWhenAttributeSetWithFloatOverload_234) {
    const float setValue = 1.25f;
    const float defaultValue = 9.99f;

    elem->SetAttribute("pi", setValue);

    // Attribute exists and is set as float -> should return stored value.
    EXPECT_FLOAT_EQ(elem->FloatAttribute("pi", defaultValue), setValue);
}

TEST_F(FloatAttributeTest_234, ReturnsUpdatedValueAfterAttributeOverwritten_234) {
    const float initial = 2.5f;
    const float updated = -7.75f;

    elem->SetAttribute("v", initial);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("v", 0.0f), initial);

    elem->SetAttribute("v", updated);
    EXPECT_FLOAT_EQ(elem->FloatAttribute("v", 0.0f), updated);
}

TEST_F(FloatAttributeTest_234, ReturnsDefaultWhenAttributeValueIsNonNumericString_234) {
    const float defaultValue = -0.5f;

    // Set a non-numeric string value.
    elem->SetAttribute("bad", "not_a_number");

    // If parsing/query fails, FloatAttribute should fall back to defaultValue.
    EXPECT_FLOAT_EQ(elem->FloatAttribute("bad", defaultValue), defaultValue);
}

TEST_F(FloatAttributeTest_234, ReturnsDefaultWhenNameIsEmptyString_234) {
    const float defaultValue = 42.0f;

    // Empty attribute name: treat as not found / not queryable via interface.
    EXPECT_FLOAT_EQ(elem->FloatAttribute("", defaultValue), defaultValue);
}

TEST_F(FloatAttributeTest_234, HandlesBoundaryFloatValues_234) {
    struct Case {
        const char* name;
        float value;
    };

    const Case cases[] = {
        {"zero", 0.0f},
        {"neg", -123.456f},
        {"min_pos", FLT_MIN},  // smallest positive normalized float
        {"max", FLT_MAX},
    };

    for (const auto& c : cases) {
        elem->SetAttribute(c.name, c.value);
        EXPECT_FLOAT_EQ(elem->FloatAttribute(c.name, 0.0f), c.value) << "name=" << c.name;
    }
}
