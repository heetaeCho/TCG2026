// TEST_ID: 72
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeInt64ValueTest_72 : public ::testing::Test {
protected:
    static const XMLAttribute* GetAttr(XMLDocument& doc, const char* xml, const char* attrName) {
        doc.Parse(xml);
        XMLElement* root = doc.RootElement();
        EXPECT_NE(root, nullptr);
        if (!root) return nullptr;

        const XMLAttribute* attr = root->FindAttribute(attrName);
        EXPECT_NE(attr, nullptr);
        return attr;
    }
};

TEST_F(XMLAttributeInt64ValueTest_72, Int64Value_ParsesPositiveValue_72) {
    XMLDocument doc;
    const XMLAttribute* attr = GetAttr(doc, "<r a='123'/>", "a");
    ASSERT_NE(attr, nullptr);

    EXPECT_EQ(attr->Int64Value(), static_cast<int64_t>(123));
}

TEST_F(XMLAttributeInt64ValueTest_72, Int64Value_ParsesNegativeValue_72) {
    XMLDocument doc;
    const XMLAttribute* attr = GetAttr(doc, "<r a='-45'/>", "a");
    ASSERT_NE(attr, nullptr);

    EXPECT_EQ(attr->Int64Value(), static_cast<int64_t>(-45));
}

TEST_F(XMLAttributeInt64ValueTest_72, Int64Value_ReturnsMaxInt64WhenSetAsNumber_72) {
    XMLDocument doc;
    doc.Parse("<r/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const int64_t kMax = std::numeric_limits<int64_t>::max();
    root->SetAttribute("a", kMax);

    const XMLAttribute* attr = root->FindAttribute("a");
    ASSERT_NE(attr, nullptr);

    EXPECT_EQ(attr->Int64Value(), kMax);
}

TEST_F(XMLAttributeInt64ValueTest_72, Int64Value_ReturnsMinInt64WhenSetAsNumber_72) {
    XMLDocument doc;
    doc.Parse("<r/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    const int64_t kMin = std::numeric_limits<int64_t>::min();
    root->SetAttribute("a", kMin);

    const XMLAttribute* attr = root->FindAttribute("a");
    ASSERT_NE(attr, nullptr);

    EXPECT_EQ(attr->Int64Value(), kMin);
}

TEST_F(XMLAttributeInt64ValueTest_72, Int64Value_InvalidTextReturnsDefaultZero_72) {
    XMLDocument doc;
    const XMLAttribute* attr = GetAttr(doc, "<r a='not_a_number'/>", "a");
    ASSERT_NE(attr, nullptr);

    // Int64Value() initializes the output to 0 before calling QueryInt64Value.
    EXPECT_EQ(attr->Int64Value(), static_cast<int64_t>(0));
}

TEST_F(XMLAttributeInt64ValueTest_72, Int64Value_OutOfRangeTextReturnsDefaultZero_72) {
    // One more than INT64_MAX.
    XMLDocument doc;
    const XMLAttribute* attr = GetAttr(doc, "<r a='9223372036854775808'/>", "a");
    ASSERT_NE(attr, nullptr);

    // Int64Value() initializes the output to 0 before calling QueryInt64Value.
    EXPECT_EQ(attr->Int64Value(), static_cast<int64_t>(0));
}
