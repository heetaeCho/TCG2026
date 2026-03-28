// TEST_ID: 223
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeSetAttributeBoolTest_223 : public ::testing::Test {
protected:
    void TearDown() override {
        // Reset to a known default so we don't leak global state across tests.
        // (tinyxml2 uses global bool serialization strings.)
        XMLUtil::SetBoolSerialization("true", "false");
    }

    static XMLAttribute* GetMutableAttribute(XMLElement* elem, const char* name) {
        const XMLAttribute* attr = elem->FindAttribute(name);
        return const_cast<XMLAttribute*>(attr); // Safe for testing: we created/own the element/attribute.
    }
};

} // namespace

TEST_F(XMLAttributeSetAttributeBoolTest_223, SetTrueThenQueryBoolValueReportsTrue_223) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("root");
    ASSERT_NE(elem, nullptr);
    doc.InsertEndChild(elem);

    // Ensure the attribute exists (XMLAttribute has a private ctor in tinyxml2).
    elem->SetAttribute("flag", false);

    XMLAttribute* attr = GetMutableAttribute(elem, "flag");
    ASSERT_NE(attr, nullptr);

    attr->SetAttribute(true);

    bool out = false;
    EXPECT_EQ(attr->QueryBoolValue(&out), XML_SUCCESS);
    EXPECT_TRUE(out);
    EXPECT_TRUE(attr->BoolValue());
}

TEST_F(XMLAttributeSetAttributeBoolTest_223, SetFalseThenQueryBoolValueReportsFalse_223) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("root");
    ASSERT_NE(elem, nullptr);
    doc.InsertEndChild(elem);

    elem->SetAttribute("flag", true);

    XMLAttribute* attr = GetMutableAttribute(elem, "flag");
    ASSERT_NE(attr, nullptr);

    attr->SetAttribute(false);

    bool out = true;
    EXPECT_EQ(attr->QueryBoolValue(&out), XML_SUCCESS);
    EXPECT_FALSE(out);
    EXPECT_FALSE(attr->BoolValue());
}

TEST_F(XMLAttributeSetAttributeBoolTest_223, MultipleSetsLastWriteWins_223) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("root");
    ASSERT_NE(elem, nullptr);
    doc.InsertEndChild(elem);

    elem->SetAttribute("flag", false);

    XMLAttribute* attr = GetMutableAttribute(elem, "flag");
    ASSERT_NE(attr, nullptr);

    attr->SetAttribute(true);
    attr->SetAttribute(false);
    attr->SetAttribute(true);

    bool out = false;
    EXPECT_EQ(attr->QueryBoolValue(&out), XML_SUCCESS);
    EXPECT_TRUE(out);
}

TEST_F(XMLAttributeSetAttributeBoolTest_223, RespectsCustomBoolSerializationStrings_223) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("root");
    ASSERT_NE(elem, nullptr);
    doc.InsertEndChild(elem);

    elem->SetAttribute("flag", false);

    XMLAttribute* attr = GetMutableAttribute(elem, "flag");
    ASSERT_NE(attr, nullptr);

    XMLUtil::SetBoolSerialization("YES", "NO");

    attr->SetAttribute(true);
    ASSERT_NE(attr->Value(), nullptr);
    EXPECT_STREQ(attr->Value(), "YES");

    attr->SetAttribute(false);
    ASSERT_NE(attr->Value(), nullptr);
    EXPECT_STREQ(attr->Value(), "NO");

    // Also verify parsing round-trip stays consistent with the stored string.
    bool out = true;
    EXPECT_EQ(attr->QueryBoolValue(&out), XML_SUCCESS);
    EXPECT_FALSE(out);
}

TEST_F(XMLAttributeSetAttributeBoolTest_223, CustomSerializationNonEmptyStringsAreStoredVerbatim_223) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("root");
    ASSERT_NE(elem, nullptr);
    doc.InsertEndChild(elem);

    elem->SetAttribute("flag", false);

    XMLAttribute* attr = GetMutableAttribute(elem, "flag");
    ASSERT_NE(attr, nullptr);

    // Keep strings comfortably below BUF_SIZE to avoid depending on any truncation behavior.
    XMLUtil::SetBoolSerialization("TrueValue_Custom_123", "FalseValue_Custom_456");

    attr->SetAttribute(true);
    EXPECT_STREQ(attr->Value(), "TrueValue_Custom_123");

    attr->SetAttribute(false);
    EXPECT_STREQ(attr->Value(), "FalseValue_Custom_456");
}
