// File: test_xmlelement_queryfloatattribute_87.cpp

#include <gtest/gtest.h>
#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class QueryFloatAttributeTest_87 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        // XMLElement ctor is private; create via XMLDocument factory.
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
    }
};

TEST_F(QueryFloatAttributeTest_87, MissingAttributeReturnsNoAttribute_87) {
    float out = 123.456f;
    const XMLError err = elem->QueryFloatAttribute("missing", &out);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

TEST_F(QueryFloatAttributeTest_87, FloatAttributeParsesValue_87) {
    elem->SetAttribute("pi", 3.14159f);

    float out = 0.0f;
    const XMLError err = elem->QueryFloatAttribute("pi", &out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(out, 3.14159f);
}

TEST_F(QueryFloatAttributeTest_87, IntAttributeParsesAsFloat_87) {
    elem->SetAttribute("count", 42);

    float out = 0.0f;
    const XMLError err = elem->QueryFloatAttribute("count", &out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(out, 42.0f);
}

TEST_F(QueryFloatAttributeTest_87, NegativeFloatParsesValue_87) {
    elem->SetAttribute("neg", -12.5f);

    float out = 0.0f;
    const XMLError err = elem->QueryFloatAttribute("neg", &out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(out, -12.5f);
}

TEST_F(QueryFloatAttributeTest_87, ScientificNotationStringParsesValue_87) {
    // Use string form to exercise parsing (no assumptions about formatting).
    elem->SetAttribute("sci", "1e-3");

    float out = 0.0f;
    const XMLError err = elem->QueryFloatAttribute("sci", &out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(out, 0.001f);
}

TEST_F(QueryFloatAttributeTest_87, NonNumericStringReturnsWrongAttributeType_87) {
    elem->SetAttribute("bad", "not-a-number");

    float out = 0.0f;
    const XMLError err = elem->QueryFloatAttribute("bad", &out);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(QueryFloatAttributeTest_87, OverwritingAttributeUpdatesQueriedValue_87) {
    elem->SetAttribute("v", 1.0f);

    float out1 = 0.0f;
    ASSERT_EQ(elem->QueryFloatAttribute("v", &out1), XML_SUCCESS);
    EXPECT_FLOAT_EQ(out1, 1.0f);

    elem->SetAttribute("v", 2.5f);

    float out2 = 0.0f;
    ASSERT_EQ(elem->QueryFloatAttribute("v", &out2), XML_SUCCESS);
    EXPECT_FLOAT_EQ(out2, 2.5f);
}
