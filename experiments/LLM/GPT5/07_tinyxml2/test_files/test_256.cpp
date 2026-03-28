// File: tinyxml2_doubletext_test_256.cpp

#include <gtest/gtest.h>
#include <cmath>
#include <limits>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLElementDoubleTextTest_256 : public ::testing::Test {
protected:
    static const XMLElement* ParseRoot(const char* xml, XMLDocument& doc) {
        ASSERT_NE(xml, nullptr);
        const XMLError err = doc.Parse(xml);
        ASSERT_EQ(err, XML_SUCCESS) << "XML parse failed with error: " << err;
        const XMLElement* root = doc.RootElement();
        ASSERT_NE(root, nullptr);
        return root;
    }
};

}  // namespace

TEST_F(XMLElementDoubleTextTest_256, ReturnsParsedDoubleWhenTextIsValid_256) {
    XMLDocument doc;
    const XMLElement* root = ParseRoot("<root>3.14159</root>", doc);

    const double out = root->DoubleText(-1.0);

    EXPECT_DOUBLE_EQ(out, 3.14159);
}

TEST_F(XMLElementDoubleTextTest_256, ReturnsDefaultWhenElementHasNoText_256) {
    XMLDocument doc;
    const XMLElement* root = ParseRoot("<root/>", doc);

    const double out = root->DoubleText(123.456);

    EXPECT_DOUBLE_EQ(out, 123.456);
}

TEST_F(XMLElementDoubleTextTest_256, ReturnsDefaultWhenTextIsNonNumeric_256) {
    XMLDocument doc;
    const XMLElement* root = ParseRoot("<root>not-a-number</root>", doc);

    const double out = root->DoubleText(-42.0);

    EXPECT_DOUBLE_EQ(out, -42.0);
}

TEST_F(XMLElementDoubleTextTest_256, ParsesWithLeadingAndTrailingWhitespace_256) {
    XMLDocument doc;
    const XMLElement* root = ParseRoot("<root>  \n\t -2.5 \r\n </root>", doc);

    const double out = root->DoubleText(0.0);

    EXPECT_DOUBLE_EQ(out, -2.5);
}

TEST_F(XMLElementDoubleTextTest_256, ParsesScientificNotation_256) {
    XMLDocument doc;
    const XMLElement* root = ParseRoot("<root>1.25e3</root>", doc);

    const double out = root->DoubleText(0.0);

    EXPECT_DOUBLE_EQ(out, 1250.0);
}

TEST_F(XMLElementDoubleTextTest_256, PropagatesNaNDefaultWhenTextIsInvalid_256) {
    XMLDocument doc;
    const XMLElement* root = ParseRoot("<root>invalid</root>", doc);

    const double nanDefault = std::numeric_limits<double>::quiet_NaN();
    const double out = root->DoubleText(nanDefault);

    EXPECT_TRUE(std::isnan(out));
}

TEST_F(XMLElementDoubleTextTest_256, HandlesVeryLargeMagnitudeInputIfRepresentable_256) {
    XMLDocument doc;
    // This is within the typical finite range of double parsing.
    const XMLElement* root = ParseRoot("<root>1.7976931348623157e308</root>", doc);

    const double out = root->DoubleText(0.0);

    EXPECT_DOUBLE_EQ(out, 1.7976931348623157e308);
}
