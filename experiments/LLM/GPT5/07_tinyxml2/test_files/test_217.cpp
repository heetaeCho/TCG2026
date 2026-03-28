// TEST_ID: 217
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeQueryDoubleValueTest_217 : public ::testing::Test {
protected:
    // Helper: parse XML and return the attribute pointer for (elementName, attrName).
    const XMLAttribute* GetAttr(const char* xml,
                                const char* elementName,
                                const char* attrName) {
        doc_.Clear();
        ASSERT_EQ(doc_.Parse(xml), XML_SUCCESS);

        XMLElement* elem = doc_.FirstChildElement(elementName);
        ASSERT_NE(elem, nullptr);

        const XMLAttribute* attr = elem->FindAttribute(attrName);
        ASSERT_NE(attr, nullptr);
        return attr;
    }

    XMLDocument doc_;
};

}  // namespace

TEST_F(XMLAttributeQueryDoubleValueTest_217, QueryDoubleValue_ParsesSimpleDecimal_217) {
    const char* xml = "<root a=\"3.14\"/>";
    const XMLAttribute* attr = GetAttr(xml, "root", "a");

    double out = 0.0;
    EXPECT_EQ(attr->QueryDoubleValue(&out), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(out, 3.14);
}

TEST_F(XMLAttributeQueryDoubleValueTest_217, QueryDoubleValue_ParsesNegativeAndZero_217) {
    const char* xml = "<root a=\"-0.0\" b=\"-42.5\"/>";
    const XMLAttribute* a = GetAttr(xml, "root", "a");
    const XMLAttribute* b = GetAttr(xml, "root", "b");

    double outA = 1.0;
    double outB = 0.0;

    EXPECT_EQ(a->QueryDoubleValue(&outA), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(outA, -0.0);

    EXPECT_EQ(b->QueryDoubleValue(&outB), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(outB, -42.5);
}

TEST_F(XMLAttributeQueryDoubleValueTest_217, QueryDoubleValue_ParsesScientificNotation_217) {
    const char* xml = "<root a=\"1e2\" b=\"-2.5E-3\"/>";
    const XMLAttribute* a = GetAttr(xml, "root", "a");
    const XMLAttribute* b = GetAttr(xml, "root", "b");

    double outA = 0.0;
    double outB = 0.0;

    EXPECT_EQ(a->QueryDoubleValue(&outA), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(outA, 100.0);

    EXPECT_EQ(b->QueryDoubleValue(&outB), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(outB, -0.0025);
}

TEST_F(XMLAttributeQueryDoubleValueTest_217, QueryDoubleValue_RejectsNonNumericString_217) {
    const char* xml = "<root a=\"not_a_number\"/>";
    const XMLAttribute* attr = GetAttr(xml, "root", "a");

    double out = 123.0;  // value is not part of the contract on failure; just provide a valid pointer.
    EXPECT_EQ(attr->QueryDoubleValue(&out), XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryDoubleValueTest_217, QueryDoubleValue_RejectsEmptyString_217) {
    const char* xml = "<root a=\"\"/>";
    const XMLAttribute* attr = GetAttr(xml, "root", "a");

    double out = 0.0;
    EXPECT_EQ(attr->QueryDoubleValue(&out), XML_WRONG_ATTRIBUTE_TYPE);
}

TEST_F(XMLAttributeQueryDoubleValueTest_217, QueryDoubleValue_ParsesLargeMagnitudeValue_217) {
    // Use a value commonly representable as a double (and typically parseable).
    const char* xml = "<root a=\"1.7976931348623157e308\"/>";
    const XMLAttribute* attr = GetAttr(xml, "root", "a");

    double out = 0.0;
    EXPECT_EQ(attr->QueryDoubleValue(&out), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(out, 1.7976931348623157e308);
}
