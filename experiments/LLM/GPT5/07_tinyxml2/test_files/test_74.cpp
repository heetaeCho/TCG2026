// TEST_ID: 74
#include <limits>

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeUnsignedValueTest_74 : public ::testing::Test {
protected:
    static const XMLAttribute* GetAttr(const char* xml, const char* attrName) {
        XMLDocument doc;
        ASSERT_EQ(doc.Parse(xml), XML_SUCCESS);

        const XMLElement* root = doc.RootElement();
        ASSERT_NE(root, nullptr);

        const XMLAttribute* attr = root->FindAttribute(attrName);
        ASSERT_NE(attr, nullptr);
        return attr;
    }
};

TEST_F(XMLAttributeUnsignedValueTest_74, ReturnsParsedUnsignedForValidNumber_74) {
    const XMLAttribute* attr = GetAttr("<root a='123'/>", "a");
    EXPECT_EQ(attr->UnsignedValue(), 123u);
}

TEST_F(XMLAttributeUnsignedValueTest_74, ReturnsZeroForZeroString_74) {
    const XMLAttribute* attr = GetAttr("<root a='0'/>", "a");
    EXPECT_EQ(attr->UnsignedValue(), 0u);
}

TEST_F(XMLAttributeUnsignedValueTest_74, ReturnsMaxUnsignedForMaxValue_74) {
    const unsigned maxU = (std::numeric_limits<unsigned>::max)();
    // Use unsigned long long for safe formatting on all platforms.
    const unsigned long long maxULL = static_cast<unsigned long long>(maxU);

    char xml[128];
    std::snprintf(xml, sizeof(xml), "<root a='%llu'/>", maxULL);

    const XMLAttribute* attr = GetAttr(xml, "a");
    EXPECT_EQ(attr->UnsignedValue(), maxU);
}

TEST_F(XMLAttributeUnsignedValueTest_74, ReturnsZeroForNonNumericValue_74) {
    const XMLAttribute* attr = GetAttr("<root a='abc'/>", "a");
    EXPECT_EQ(attr->UnsignedValue(), 0u);
}

TEST_F(XMLAttributeUnsignedValueTest_74, ReturnsZeroForNegativeNumberString_74) {
    const XMLAttribute* attr = GetAttr("<root a='-1'/>", "a");
    EXPECT_EQ(attr->UnsignedValue(), 0u);
}

TEST_F(XMLAttributeUnsignedValueTest_74, HandlesLeadingTrailingWhitespace_74) {
    const XMLAttribute* attr = GetAttr("<root a='  42  '/>", "a");
    EXPECT_EQ(attr->UnsignedValue(), 42u);
}

}  // namespace
