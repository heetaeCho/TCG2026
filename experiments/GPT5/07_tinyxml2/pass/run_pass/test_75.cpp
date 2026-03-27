// File: ./TestProjects/tinyxml2/tests/xmlattribute_boolvalue_test_75.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeBoolValueTest_75 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root = nullptr;

    void SetUp() override {
        // Include a mix of values; tests will not assume which strings are accepted as "true/false".
        const char* xml =
            "<root a=\"1\" b=\"0\" c=\"true\" d=\"false\" e=\"notabool\" />";
        ASSERT_EQ(XML_SUCCESS, doc.Parse(xml));
        root = doc.FirstChildElement("root");
        ASSERT_NE(nullptr, root);
    }

    const XMLAttribute* Attr(const char* name) {
        // FindAttribute exists in tinyxml2's public API; use it to avoid relying on internal state.
        const XMLAttribute* a = root->FindAttribute(name);
        EXPECT_NE(nullptr, a) << "Expected attribute '" << name << "' to exist in test XML.";
        return a;
    }
};

}  // namespace

TEST_F(XMLAttributeBoolValueTest_75, BoolValueMatchesQueryBoolValueOnSuccess_75) {
    // For several candidate boolean-like strings, assert:
    // - If QueryBoolValue succeeds, BoolValue() returns the same result it queried into.
    // - If it fails, BoolValue() must return false (it initializes to false then queries).
    const char* names[] = {"a", "b", "c", "d"};

    for (const char* n : names) {
        const XMLAttribute* attr = Attr(n);
        ASSERT_NE(nullptr, attr);

        bool queried = true;  // sentinel
        const XMLError err = attr->QueryBoolValue(&queried);

        if (err == XML_SUCCESS) {
            EXPECT_EQ(queried, attr->BoolValue()) << "Attribute '" << n << "'";
        } else {
            EXPECT_FALSE(attr->BoolValue()) << "Attribute '" << n << "' (QueryBoolValue failed)";
        }
    }
}

TEST_F(XMLAttributeBoolValueTest_75, BoolValueReturnsFalseWhenQueryBoolValueFails_75) {
    const XMLAttribute* attr = Attr("e");
    ASSERT_NE(nullptr, attr);

    bool queried = true;  // sentinel (should remain true if implementation doesn't touch on error)
    const XMLError err = attr->QueryBoolValue(&queried);

    // We don't assume which exact error code, only that parsing "notabool" is not a successful bool query.
    EXPECT_NE(XML_SUCCESS, err);

    // Based on the provided implementation:
    // bool b=false; QueryBoolValue(&b); return b;
    EXPECT_FALSE(attr->BoolValue());
}

TEST_F(XMLAttributeBoolValueTest_75, BoolValueIsDeterministicAcrossMultipleCalls_75) {
    const XMLAttribute* attr = Attr("a");
    ASSERT_NE(nullptr, attr);

    const bool v1 = attr->BoolValue();
    const bool v2 = attr->BoolValue();
    const bool v3 = attr->BoolValue();

    EXPECT_EQ(v1, v2);
    EXPECT_EQ(v2, v3);
}

TEST_F(XMLAttributeBoolValueTest_75, MissingAttributeFindAttributeReturnsNull_75) {
    const XMLAttribute* missing = root->FindAttribute("does_not_exist");
    EXPECT_EQ(nullptr, missing);
}
