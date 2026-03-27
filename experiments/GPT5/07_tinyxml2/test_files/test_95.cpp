// File: ./TestProjects/tinyxml2/tests/XMLElementQueryAttributeFloatTest_95.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace tinyxml2 {

class XMLElementQueryAttributeFloatTest_95 : public ::testing::Test {
protected:
    static XMLElement* ParseAndGetRoot(XMLDocument& doc, const char* xml) {
        ASSERT_NE(xml, nullptr);
        const XMLError err = doc.Parse(xml);
        ASSERT_EQ(err, XML_SUCCESS);

        XMLElement* root = doc.FirstChildElement("root");
        ASSERT_NE(root, nullptr);
        return root;
    }
};

TEST_F(XMLElementQueryAttributeFloatTest_95, QueryAttributeFloat_ParsesValidFloat_95) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, R"(<root f="3.5"/>)");

    float v = 0.0f;
    const XMLError err = root->QueryAttribute("f", &v);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(v, 3.5f);
}

TEST_F(XMLElementQueryAttributeFloatTest_95, QueryAttributeFloat_ParsesScientificNotation_95) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, R"(<root f="1.25e2"/>)");

    float v = 0.0f;
    const XMLError err = root->QueryAttribute("f", &v);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(v, 125.0f);
}

TEST_F(XMLElementQueryAttributeFloatTest_95, QueryAttributeFloat_ParsesNegativeFloat_95) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, R"(<root f="-0.75"/>)");

    float v = 0.0f;
    const XMLError err = root->QueryAttribute("f", &v);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(v, -0.75f);
}

TEST_F(XMLElementQueryAttributeFloatTest_95, QueryAttributeFloat_MissingAttribute_ReturnsNoAttribute_95) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, R"(<root other="1.0"/>)");

    float v = 123.0f;
    const XMLError err = root->QueryAttribute("f", &v);

    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    // Value may or may not be modified on error; only verify the observable error code.
}

TEST_F(XMLElementQueryAttributeFloatTest_95, QueryAttributeFloat_WrongType_ReturnsWrongAttributeType_95) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, R"(<root f="not_a_number"/>)");

    float v = 0.0f;
    const XMLError err = root->QueryAttribute("f", &v);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLElementQueryAttributeFloatTest_95, QueryAttributeFloat_EmptyString_ReturnsWrongAttributeType_95) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, R"(<root f=""/>)");

    float v = 0.0f;
    const XMLError err = root->QueryAttribute("f", &v);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLElementQueryAttributeFloatTest_95, QueryAttributeFloat_BehavesSameAsQueryFloatAttribute_95) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, R"(<root f="42.25"/>)");

    float viaOverload = 0.0f;
    float viaDirect = 0.0f;

    const XMLError err1 = root->QueryAttribute("f", &viaOverload);
    const XMLError err2 = root->QueryFloatAttribute("f", &viaDirect);

    EXPECT_EQ(err1, err2);
    if (err1 == XML_SUCCESS) {
        EXPECT_FLOAT_EQ(viaOverload, viaDirect);
    }
}

TEST_F(XMLElementQueryAttributeFloatTest_95, QueryAttributeFloat_ParsesLargeMagnitudeValue_95) {
    // Use a magnitude that's large but typically representable in float.
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, R"(<root f="3.0e20"/>)");

    float v = 0.0f;
    const XMLError err = root->QueryAttribute("f", &v);

    // Behavior for extreme values can vary (overflow/inf) depending on implementation.
    // We only assert success vs. failure and, on success, that the value is finite-or-not as produced.
    EXPECT_EQ(err, XML_SUCCESS);
    // If it parsed successfully, it should not stay at the initial value in typical cases.
    // Still, keep this expectation weak to avoid assuming implementation details.
    EXPECT_NE(v, 0.0f);
}

}  // namespace tinyxml2
