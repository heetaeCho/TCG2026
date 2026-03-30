// TEST_ID: 76
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeDoubleValueTest_76 : public ::testing::Test {
protected:
    // Parses <root a="..."/> and returns the attribute pointer (or nullptr on failure).
    const XMLAttribute* ParseAttr(const char* attrValue) {
        doc_.Clear();

        std::string xml = "<root a=\"";
        xml += (attrValue ? attrValue : "");
        xml += "\"/>";

        XMLError err = doc_.Parse(xml.c_str());
        if (err != XML_SUCCESS) return nullptr;

        XMLElement* root = doc_.FirstChildElement("root");
        if (!root) return nullptr;

        // Rely on TinyXML-2 public API to obtain an XMLAttribute instance.
        return root->FindAttribute("a");
    }

    XMLDocument doc_;
};

}  // namespace

TEST_F(XMLAttributeDoubleValueTest_76, ReturnsExpectedForSimpleDecimal_76) {
    const XMLAttribute* a = ParseAttr("3.25");
    ASSERT_NE(a, nullptr);

    EXPECT_DOUBLE_EQ(a->DoubleValue(), 3.25);
}

TEST_F(XMLAttributeDoubleValueTest_76, ReturnsExpectedForNegativeValue_76) {
    const XMLAttribute* a = ParseAttr("-12.5");
    ASSERT_NE(a, nullptr);

    EXPECT_DOUBLE_EQ(a->DoubleValue(), -12.5);
}

TEST_F(XMLAttributeDoubleValueTest_76, ReturnsExpectedForIntegerString_76) {
    const XMLAttribute* a = ParseAttr("42");
    ASSERT_NE(a, nullptr);

    EXPECT_DOUBLE_EQ(a->DoubleValue(), 42.0);
}

TEST_F(XMLAttributeDoubleValueTest_76, ReturnsExpectedForScientificNotation_76) {
    const XMLAttribute* a = ParseAttr("1e3");
    ASSERT_NE(a, nullptr);

    EXPECT_DOUBLE_EQ(a->DoubleValue(), 1000.0);
}

TEST_F(XMLAttributeDoubleValueTest_76, ReturnsExpectedForLeadingPlusSign_76) {
    const XMLAttribute* a = ParseAttr("+2.5");
    ASSERT_NE(a, nullptr);

    EXPECT_DOUBLE_EQ(a->DoubleValue(), 2.5);
}

TEST_F(XMLAttributeDoubleValueTest_76, ReturnsDefaultForNonNumericString_76) {
    const XMLAttribute* a = ParseAttr("not_a_number");
    ASSERT_NE(a, nullptr);

    // Observable behavior via the interface: DoubleValue() returns some double.
    // For an invalid numeric value, it is expected to fall back to the default produced by DoubleValue().
    EXPECT_DOUBLE_EQ(a->DoubleValue(), 0.0);
}

TEST_F(XMLAttributeDoubleValueTest_76, ReturnsDefaultForEmptyString_76) {
    const XMLAttribute* a = ParseAttr("");
    ASSERT_NE(a, nullptr);

    EXPECT_DOUBLE_EQ(a->DoubleValue(), 0.0);
}

TEST_F(XMLAttributeDoubleValueTest_76, ReturnsDefaultForWhitespaceOnly_76) {
    const XMLAttribute* a = ParseAttr("   ");
    ASSERT_NE(a, nullptr);

    EXPECT_DOUBLE_EQ(a->DoubleValue(), 0.0);
}

TEST_F(XMLAttributeDoubleValueTest_76, ReturnsSameOnRepeatedCalls_76) {
    const XMLAttribute* a = ParseAttr("6.125");
    ASSERT_NE(a, nullptr);

    const double v1 = a->DoubleValue();
    const double v2 = a->DoubleValue();
    EXPECT_DOUBLE_EQ(v1, v2);
}

TEST_F(XMLAttributeDoubleValueTest_76, CanReadMultipleAttributesIndependently_76) {
    doc_.Clear();
    const char* xml = "<root a=\"1.5\" b=\"-2.25\"/>";

    ASSERT_EQ(doc_.Parse(xml), XML_SUCCESS);
    XMLElement* root = doc_.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLAttribute* a = root->FindAttribute("a");
    const XMLAttribute* b = root->FindAttribute("b");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    EXPECT_DOUBLE_EQ(a->DoubleValue(), 1.5);
    EXPECT_DOUBLE_EQ(b->DoubleValue(), -2.25);
}
