#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeFloatValueTest_77 : public ::testing::Test {
protected:
    // Parses `xml`, returns the first attribute with name `attrName` on the first <root/> element.
    const XMLAttribute* ParseAndGetAttr(const char* xml, const char* attrName) {
        doc_.Clear();
        ASSERT_EQ(XML_SUCCESS, doc_.Parse(xml));

        const XMLElement* root = doc_.FirstChildElement("root");
        ASSERT_NE(nullptr, root);

        const XMLAttribute* attr = root->FindAttribute(attrName);
        ASSERT_NE(nullptr, attr);
        return attr;
    }

    XMLDocument doc_;
};

TEST_F(XMLAttributeFloatValueTest_77, FloatValue_ParsesSimpleDecimal_77) {
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="1.5"/>)", "a");
    EXPECT_FLOAT_EQ(1.5f, attr->FloatValue());
}

TEST_F(XMLAttributeFloatValueTest_77, FloatValue_ParsesNegativeDecimal_77) {
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="-2.25"/>)", "a");
    EXPECT_FLOAT_EQ(-2.25f, attr->FloatValue());
}

TEST_F(XMLAttributeFloatValueTest_77, FloatValue_ParsesIntegerAsFloat_77) {
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="42"/>)", "a");
    EXPECT_FLOAT_EQ(42.0f, attr->FloatValue());
}

TEST_F(XMLAttributeFloatValueTest_77, FloatValue_ParsesScientificNotation_77) {
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="1e3"/>)", "a");
    EXPECT_FLOAT_EQ(1000.0f, attr->FloatValue());
}

TEST_F(XMLAttributeFloatValueTest_77, FloatValue_InvalidTextReturnsDefaultZero_77) {
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="not_a_number"/>)", "a");
    EXPECT_FLOAT_EQ(0.0f, attr->FloatValue());
}

TEST_F(XMLAttributeFloatValueTest_77, FloatValue_EmptyStringReturnsDefaultZero_77) {
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a=""/>)", "a");
    EXPECT_FLOAT_EQ(0.0f, attr->FloatValue());
}

TEST_F(XMLAttributeFloatValueTest_77, FloatValue_DoesNotChangeAttributeText_77) {
    const XMLAttribute* attr = ParseAndGetAttr(R"(<root a="3.25"/>)", "a");
    ASSERT_STREQ("3.25", attr->Value());

    (void)attr->FloatValue();

    // Value() should remain the original textual representation after FloatValue().
    EXPECT_STREQ("3.25", attr->Value());
}

}  // namespace
