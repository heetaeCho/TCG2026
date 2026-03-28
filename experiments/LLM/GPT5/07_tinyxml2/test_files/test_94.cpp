#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLElementQueryAttributeDoubleTest_94 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* ParseSingleElement(const char* xml) {
        doc.Clear();
        EXPECT_EQ(doc.Parse(xml), XML_SUCCESS);
        XMLElement* e = doc.FirstChildElement();
        EXPECT_NE(e, nullptr);
        return e;
    }

    static void ExpectQueryAttributeMatchesQueryDoubleAttribute(XMLElement* elem,
                                                               const char* attrName,
                                                               double initialSentinel = 12345.6789) {
        ASSERT_NE(elem, nullptr);
        ASSERT_NE(attrName, nullptr);

        double v1 = initialSentinel;
        double v2 = initialSentinel;

        const XMLError r1 = elem->QueryAttribute(attrName, &v1);
        const XMLError r2 = elem->QueryDoubleAttribute(attrName, &v2);

        EXPECT_EQ(r1, r2);
        // Since QueryAttribute(double*) is specified as forwarding to QueryDoubleAttribute,
        // the observable output should match when both are called on the same element/attribute.
        EXPECT_DOUBLE_EQ(v1, v2);
    }
};

TEST_F(XMLElementQueryAttributeDoubleTest_94, ParsesValidDoubleAttribute_94) {
    XMLElement* e = ParseSingleElement("<root a=\"3.14159\"/>");
    ExpectQueryAttributeMatchesQueryDoubleAttribute(e, "a");
}

TEST_F(XMLElementQueryAttributeDoubleTest_94, ParsesNegativeDoubleAttribute_94) {
    XMLElement* e = ParseSingleElement("<root a=\"-2.5\"/>");
    ExpectQueryAttributeMatchesQueryDoubleAttribute(e, "a");
}

TEST_F(XMLElementQueryAttributeDoubleTest_94, ParsesScientificNotation_94) {
    XMLElement* e = ParseSingleElement("<root a=\"1.25e3\"/>");
    ExpectQueryAttributeMatchesQueryDoubleAttribute(e, "a");
}

TEST_F(XMLElementQueryAttributeDoubleTest_94, MissingAttributeReturnsSameErrorAndSameOutput_94) {
    XMLElement* e = ParseSingleElement("<root other=\"7.0\"/>");

    // Check both the return code and that the observed output behavior matches.
    ExpectQueryAttributeMatchesQueryDoubleAttribute(e, "a", /*initialSentinel=*/-999.0);
}

TEST_F(XMLElementQueryAttributeDoubleTest_94, NonNumericAttributeReturnsSameErrorAndSameOutput_94) {
    XMLElement* e = ParseSingleElement("<root a=\"not_a_number\"/>");
    ExpectQueryAttributeMatchesQueryDoubleAttribute(e, "a", /*initialSentinel=*/42.0);
}

TEST_F(XMLElementQueryAttributeDoubleTest_94, EmptyStringAttributeReturnsSameErrorAndSameOutput_94) {
    XMLElement* e = ParseSingleElement("<root a=\"\"/>");
    ExpectQueryAttributeMatchesQueryDoubleAttribute(e, "a", /*initialSentinel=*/0.25);
}

TEST_F(XMLElementQueryAttributeDoubleTest_94, DifferentAttributesBehaveIndependently_94) {
    XMLElement* e = ParseSingleElement("<root a=\"10.0\" b=\"-0.5\"/>");
    ExpectQueryAttributeMatchesQueryDoubleAttribute(e, "a");
    ExpectQueryAttributeMatchesQueryDoubleAttribute(e, "b");
}
