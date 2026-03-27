#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <string>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class DoubleAttributeTest_233 : public ::testing::Test {
protected:
    static XMLElement* ParseSingleElement(XMLDocument& doc, const char* xml) {
        ASSERT_NE(xml, nullptr);
        const XMLError err = doc.Parse(xml);
        ASSERT_EQ(err, XML_SUCCESS);
        XMLElement* elem = doc.FirstChildElement("root");
        ASSERT_NE(elem, nullptr);
        return elem;
    }
};

TEST_F(DoubleAttributeTest_233, ReturnsParsedDoubleWhenPresent_233) {
    XMLDocument doc;
    XMLElement* root = ParseSingleElement(doc, R"(<root pi="3.25"/>)");

    const double v = root->DoubleAttribute("pi", -1.0);
    EXPECT_DOUBLE_EQ(v, 3.25);
}

TEST_F(DoubleAttributeTest_233, ReturnsDefaultWhenMissing_233) {
    XMLDocument doc;
    XMLElement* root = ParseSingleElement(doc, R"(<root other="1.0"/>)");

    const double def = 9.5;
    const double v = root->DoubleAttribute("pi", def);
    EXPECT_DOUBLE_EQ(v, def);
}

TEST_F(DoubleAttributeTest_233, ReturnsDefaultWhenValueInvalid_233) {
    XMLDocument doc;
    XMLElement* root = ParseSingleElement(doc, R"(<root pi="not_a_number"/>)");

    const double def = 123.456;
    const double v = root->DoubleAttribute("pi", def);
    EXPECT_DOUBLE_EQ(v, def);
}

TEST_F(DoubleAttributeTest_233, ParsesScientificNotation_233) {
    XMLDocument doc;
    XMLElement* root = ParseSingleElement(doc, R"(<root a="1.25e2" b="-4.0E-1"/>)");

    EXPECT_DOUBLE_EQ(root->DoubleAttribute("a", 0.0), 125.0);
    EXPECT_DOUBLE_EQ(root->DoubleAttribute("b", 0.0), -0.4);
}

TEST_F(DoubleAttributeTest_233, HandlesLargeMagnitudeValues_233) {
    XMLDocument doc;

    // Use a well-known string representation for DBL_MAX.
    constexpr double kMax = std::numeric_limits<double>::max();
    XMLElement* root = ParseSingleElement(doc, R"(<root big="1.7976931348623157e308"/>)");

    const double v = root->DoubleAttribute("big", 0.0);

    // Expect the parsed value to be very close to max (commonly exact for this literal).
    EXPECT_NEAR(v, kMax, kMax * 1e-15);
}

TEST_F(DoubleAttributeTest_233, ReturnsDefaultForEmptyNameWhenNotFound_233) {
    XMLDocument doc;
    XMLElement* root = ParseSingleElement(doc, R"(<root pi="3.14"/>)");

    const double def = -7.0;
    const double v = root->DoubleAttribute("", def);
    EXPECT_DOUBLE_EQ(v, def);
}

}  // namespace
