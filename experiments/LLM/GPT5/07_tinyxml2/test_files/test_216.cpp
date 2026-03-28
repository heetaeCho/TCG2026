// File: ./TestProjects/tinyxml2/test_xmlattribute_queryfloatvalue_216.cpp

#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <string>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeQueryFloatValueTest_216 : public ::testing::Test {
protected:
    // Parses `xml`, returns the attribute pointer for `attrName` on the first element named `elementName`.
    // Fails the test if parsing or lookup fails.
    const XMLAttribute* ParseAndGetAttr(const char* xml,
                                       const char* elementName,
                                       const char* attrName) {
        doc_.Clear();
        ASSERT_NE(xml, nullptr);
        XMLError err = doc_.Parse(xml);
        ASSERT_EQ(err, XML_SUCCESS);

        XMLElement* elem = doc_.FirstChildElement(elementName);
        ASSERT_NE(elem, nullptr);

        const XMLAttribute* attr = elem->FindAttribute(attrName);
        ASSERT_NE(attr, nullptr);

        return attr;
    }

    XMLDocument doc_;
};

}  // namespace

TEST_F(XMLAttributeQueryFloatValueTest_216, ParsesSimpleDecimal_216) {
    const XMLAttribute* attr =
        ParseAndGetAttr(R"(<root a="3.14"/>)", "root", "a");

    float out = 0.0f;
    const XMLError err = attr->QueryFloatValue(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(out, 3.14f, 1e-6f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, ParsesIntegerAsFloat_216) {
    const XMLAttribute* attr =
        ParseAndGetAttr(R"(<root a="42"/>)", "root", "a");

    float out = 0.0f;
    const XMLError err = attr->QueryFloatValue(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(out, 42.0f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, ParsesNegativeFloat_216) {
    const XMLAttribute* attr =
        ParseAndGetAttr(R"(<root a="-0.5"/>)", "root", "a");

    float out = 0.0f;
    const XMLError err = attr->QueryFloatValue(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FLOAT_EQ(out, -0.5f);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, RejectsNonNumericString_216) {
    const XMLAttribute* attr =
        ParseAndGetAttr(R"(<root a="not_a_number"/>)", "root", "a");

    float out = 123.0f;  // sentinel (do not assume it remains unchanged)
    const XMLError err = attr->QueryFloatValue(&out);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, RejectsEmptyString_216) {
    const XMLAttribute* attr =
        ParseAndGetAttr(R"(<root a=""/>)", "root", "a");

    float out = 123.0f;
    const XMLError err = attr->QueryFloatValue(&out);

    EXPECT_EQ(err, XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryFloatValueTest_216, ParsesLargeButFiniteValueFromString_216) {
    // Use a value comfortably within float range to avoid overflow/implementation-specific behavior.
    const XMLAttribute* attr =
        ParseAndGetAttr(R"(<root a="1.0e10"/>)", "root", "a");

    float out = 0.0f;
    const XMLError err = attr->QueryFloatValue(&out);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(std::isfinite(out));
    EXPECT_NEAR(out, 1.0e10f, 1.0e5f);  // allow some tolerance for float precision
}
