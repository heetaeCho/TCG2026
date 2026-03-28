#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

#include <cstdint>
#include <limits>

using namespace tinyxml2;

class XMLAttributeUnsigned64ValueTest_73 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLAttributeUnsigned64ValueTest_73, ReturnsValueForZero_73) {
    XMLElement* elem = doc_.NewElement("e");
    ASSERT_NE(elem, nullptr);

    const char* kAttr = "a";
    elem->SetAttribute(kAttr, static_cast<uint64_t>(0));

    const XMLAttribute* attr = elem->FindAttribute(kAttr);
    ASSERT_NE(attr, nullptr);

    EXPECT_EQ(attr->Unsigned64Value(), 0u);
}

TEST_F(XMLAttributeUnsigned64ValueTest_73, ReturnsValueForTypicalNumber_73) {
    XMLElement* elem = doc_.NewElement("e");
    ASSERT_NE(elem, nullptr);

    const char* kAttr = "a";
    const uint64_t expected = 123456789012345ULL;
    elem->SetAttribute(kAttr, expected);

    const XMLAttribute* attr = elem->FindAttribute(kAttr);
    ASSERT_NE(attr, nullptr);

    EXPECT_EQ(attr->Unsigned64Value(), expected);
}

TEST_F(XMLAttributeUnsigned64ValueTest_73, ReturnsMaxForUint64Max_73) {
    XMLElement* elem = doc_.NewElement("e");
    ASSERT_NE(elem, nullptr);

    const char* kAttr = "a";
    const uint64_t expected = (std::numeric_limits<uint64_t>::max)();
    elem->SetAttribute(kAttr, expected);

    const XMLAttribute* attr = elem->FindAttribute(kAttr);
    ASSERT_NE(attr, nullptr);

    EXPECT_EQ(attr->Unsigned64Value(), expected);
}

TEST_F(XMLAttributeUnsigned64ValueTest_73, ReturnsZeroForNonNumericString_73) {
    XMLElement* elem = doc_.NewElement("e");
    ASSERT_NE(elem, nullptr);

    const char* kAttr = "a";
    elem->SetAttribute(kAttr, "not_a_number");

    const XMLAttribute* attr = elem->FindAttribute(kAttr);
    ASSERT_NE(attr, nullptr);

    // Observable wrapper behavior: it initializes to 0 and queries into it.
    EXPECT_EQ(attr->Unsigned64Value(), 0u);
}

TEST_F(XMLAttributeUnsigned64ValueTest_73, ReturnsZeroForNegativeString_73) {
    XMLElement* elem = doc_.NewElement("e");
    ASSERT_NE(elem, nullptr);

    const char* kAttr = "a";
    elem->SetAttribute(kAttr, "-1");

    const XMLAttribute* attr = elem->FindAttribute(kAttr);
    ASSERT_NE(attr, nullptr);

    EXPECT_EQ(attr->Unsigned64Value(), 0u);
}
