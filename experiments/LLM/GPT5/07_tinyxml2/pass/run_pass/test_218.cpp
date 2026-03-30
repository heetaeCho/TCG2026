// File: ./TestProjects/tinyxml2/tests/xmlattribute_setattribute_charptr_218.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLAttributeSetAttributeCharPtrTest_218 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
        elem->SetAttribute("attr", "initial");
    }

    // tinyxml2 exposes attributes as const via FindAttribute/FirstAttribute,
    // but the underlying attribute belongs to a non-const element; we only
    // use const_cast to call the public non-const XMLAttribute::SetAttribute.
    XMLAttribute* GetAttrMutable() {
        const XMLAttribute* cattr = elem->FindAttribute("attr");
        EXPECT_NE(cattr, nullptr);
        return const_cast<XMLAttribute*>(cattr);
    }
};

TEST_F(XMLAttributeSetAttributeCharPtrTest_218, SetAttributeUpdatesValue_218) {
    XMLAttribute* attr = GetAttrMutable();
    ASSERT_NE(attr, nullptr);

    attr->SetAttribute("updated");

    ASSERT_NE(attr->Value(), nullptr);
    EXPECT_STREQ(attr->Value(), "updated");
}

TEST_F(XMLAttributeSetAttributeCharPtrTest_218, SetAttributeEmptyStringResultsInEmptyValue_218) {
    XMLAttribute* attr = GetAttrMutable();
    ASSERT_NE(attr, nullptr);

    attr->SetAttribute("");

    ASSERT_NE(attr->Value(), nullptr);
    EXPECT_STREQ(attr->Value(), "");
}

TEST_F(XMLAttributeSetAttributeCharPtrTest_218, SetAttributeCalledMultipleTimesLastValueWins_218) {
    XMLAttribute* attr = GetAttrMutable();
    ASSERT_NE(attr, nullptr);

    attr->SetAttribute("one");
    ASSERT_NE(attr->Value(), nullptr);
    EXPECT_STREQ(attr->Value(), "one");

    attr->SetAttribute("two");
    ASSERT_NE(attr->Value(), nullptr);
    EXPECT_STREQ(attr->Value(), "two");

    attr->SetAttribute("three");
    ASSERT_NE(attr->Value(), nullptr);
    EXPECT_STREQ(attr->Value(), "three");
}

TEST_F(XMLAttributeSetAttributeCharPtrTest_218, SetAttributePreservesWhitespaceAndSymbols_218) {
    XMLAttribute* attr = GetAttrMutable();
    ASSERT_NE(attr, nullptr);

    const char* v = "  a\tb\nc  !@#$%^&*()_+-=[]{};:'\",.<>/?\\|  ";
    attr->SetAttribute(v);

    ASSERT_NE(attr->Value(), nullptr);
    EXPECT_STREQ(attr->Value(), v);
}
