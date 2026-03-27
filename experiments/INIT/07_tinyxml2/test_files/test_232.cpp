// TEST_ID: 232
// File: tinyxml2_boolattribute_test_232.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class BoolAttributeTest_232 : public ::testing::Test {
protected:
    tinyxml2::XMLDocument doc_;

    tinyxml2::XMLElement* ParseSingleElement(const char* xml) {
        doc_.Clear();
        const tinyxml2::XMLError err = doc_.Parse(xml);
        EXPECT_EQ(err, tinyxml2::XML_SUCCESS) << "XML parse failed for: " << (xml ? xml : "(null)");
        return doc_.RootElement();
    }

    // Oracle using only public interface: emulate what BoolAttribute does by
    // starting from default and calling QueryBoolAttribute.
    bool ExpectedViaQueryBoolAttribute(const tinyxml2::XMLElement* elem,
                                       const char* attrName,
                                       bool defaultValue) const {
        bool b = defaultValue;
        (void)elem->QueryBoolAttribute(attrName, &b);
        return b;
    }
};

TEST_F(BoolAttributeTest_232, ReturnsDefaultWhenAttributeMissing_232) {
    tinyxml2::XMLElement* elem = ParseSingleElement("<root/>");
    ASSERT_NE(elem, nullptr);

    EXPECT_EQ(elem->BoolAttribute("missing", true), true);
    EXPECT_EQ(elem->BoolAttribute("missing", false), false);

    // Cross-check with the public oracle.
    EXPECT_EQ(elem->BoolAttribute("missing", true),
              ExpectedViaQueryBoolAttribute(elem, "missing", true));
    EXPECT_EQ(elem->BoolAttribute("missing", false),
              ExpectedViaQueryBoolAttribute(elem, "missing", false));
}

TEST_F(BoolAttributeTest_232, MatchesQueryBoolAttributeForValidAndInvalidValues_232) {
    // We don't assume what strings are valid booleans; we only require
    // BoolAttribute to behave consistently with QueryBoolAttribute.
    tinyxml2::XMLElement* elem =
        ParseSingleElement("<root a='true' b='false' c='1' d='0' e='notabool' f=''/>");
    ASSERT_NE(elem, nullptr);

    struct Case { const char* name; bool def; };
    const Case cases[] = {
        {"a", false}, {"a", true},
        {"b", false}, {"b", true},
        {"c", false}, {"c", true},
        {"d", false}, {"d", true},
        {"e", false}, {"e", true},
        {"f", false}, {"f", true},
    };

    for (const auto& tc : cases) {
        const bool expected = ExpectedViaQueryBoolAttribute(elem, tc.name, tc.def);
        const bool actual = elem->BoolAttribute(tc.name, tc.def);
        EXPECT_EQ(actual, expected) << "Attribute name: " << tc.name << ", default: " << tc.def;
    }
}

TEST_F(BoolAttributeTest_232, DifferentDefaultsOnlyMatterWhenQueryDoesNotOverride_232) {
    // If QueryBoolAttribute does not override (e.g., missing or wrong type),
    // BoolAttribute should return the provided default.
    tinyxml2::XMLElement* elem = ParseSingleElement("<root bad='notabool'/>");
    ASSERT_NE(elem, nullptr);

    const bool expected_true = ExpectedViaQueryBoolAttribute(elem, "bad", true);
    const bool expected_false = ExpectedViaQueryBoolAttribute(elem, "bad", false);

    EXPECT_EQ(elem->BoolAttribute("bad", true), expected_true);
    EXPECT_EQ(elem->BoolAttribute("bad", false), expected_false);

    // Also check missing attribute behaves the same way.
    EXPECT_EQ(elem->BoolAttribute("missing", true),
              ExpectedViaQueryBoolAttribute(elem, "missing", true));
    EXPECT_EQ(elem->BoolAttribute("missing", false),
              ExpectedViaQueryBoolAttribute(elem, "missing", false));
}

TEST_F(BoolAttributeTest_232, EmptyAttributeNameBehavesLikeQueryBoolAttribute_232) {
    tinyxml2::XMLElement* elem = ParseSingleElement("<root x='true'/>");
    ASSERT_NE(elem, nullptr);

    // Avoid nullptr (potentially undefined). Empty string is a safe boundary input.
    const char* empty = "";

    EXPECT_EQ(elem->BoolAttribute(empty, true),
              ExpectedViaQueryBoolAttribute(elem, empty, true));
    EXPECT_EQ(elem->BoolAttribute(empty, false),
              ExpectedViaQueryBoolAttribute(elem, empty, false));
}

}  // namespace
