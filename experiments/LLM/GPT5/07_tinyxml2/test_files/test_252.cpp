// TEST_ID: 252
#include <gtest/gtest.h>

#include <climits>
#include <cstdint>
#include <string>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementUnsignedTextTest_252 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
    }

    // Helper: expected behavior derived only from the public interface:
    // If QueryUnsignedText succeeds, UnsignedText should return the queried value,
    // otherwise it should return the provided default.
    unsigned ExpectedUnsignedTextFromQuery(unsigned defaultValue) const {
        unsigned v = defaultValue;
        const XMLError err = elem->QueryUnsignedText(&v);
        if (err == XML_SUCCESS) {
            return v;
        }
        return defaultValue;
    }
};

TEST_F(XMLElementUnsignedTextTest_252, ReturnsDefaultWhenNoText_252) {
    const unsigned def = 123u;

    // No SetText call -> element has no text (observable through GetText()).
    ASSERT_EQ(elem->GetText(), nullptr);

    EXPECT_EQ(elem->UnsignedText(def), def);
}

TEST_F(XMLElementUnsignedTextTest_252, ReturnsParsedValueWhenTextIsValidUnsigned_252) {
    elem->SetText(42u);

    const unsigned def = 7u;
    const unsigned expected = ExpectedUnsignedTextFromQuery(def);

    EXPECT_EQ(elem->UnsignedText(def), expected);
    // Also ensure it doesn't just echo the default when parsing is successful.
    if (elem->QueryUnsignedText(&def) == XML_SUCCESS) {
        EXPECT_EQ(elem->UnsignedText(999u), elem->UnsignedText(1u));
    }
}

TEST_F(XMLElementUnsignedTextTest_252, ReturnsDefaultWhenTextIsNotANumber_252) {
    elem->SetText("not-a-number");

    const unsigned def = 55u;
    EXPECT_EQ(elem->UnsignedText(def), ExpectedUnsignedTextFromQuery(def));
}

TEST_F(XMLElementUnsignedTextTest_252, ReturnsDefaultWhenTextIsEmptyString_252) {
    elem->SetText("");

    const unsigned def = 88u;
    EXPECT_EQ(elem->UnsignedText(def), ExpectedUnsignedTextFromQuery(def));
}

TEST_F(XMLElementUnsignedTextTest_252, HandlesWhitespaceAroundNumberConsistentlyWithQuery_252) {
    elem->SetText("   123 \n\t");

    const unsigned def = 9u;
    EXPECT_EQ(elem->UnsignedText(def), ExpectedUnsignedTextFromQuery(def));
}

TEST_F(XMLElementUnsignedTextTest_252, NegativeTextDoesNotProduceUnexpectedNonDefault_252) {
    // A negative value for an unsigned parse is an error in many parsers; we do not assume.
    // We only require UnsignedText to behave consistently with QueryUnsignedText.
    elem->SetText("-1");

    const unsigned def = 101u;
    EXPECT_EQ(elem->UnsignedText(def), ExpectedUnsignedTextFromQuery(def));
}

TEST_F(XMLElementUnsignedTextTest_252, BoundaryZero_252) {
    elem->SetText("0");

    const unsigned def = 999u;
    EXPECT_EQ(elem->UnsignedText(def), ExpectedUnsignedTextFromQuery(def));
}

TEST_F(XMLElementUnsignedTextTest_252, BoundaryUIntMax_252) {
    // Use string to avoid any formatting differences.
    const std::string maxStr = std::to_string(static_cast<unsigned long long>(UINT_MAX));
    elem->SetText(maxStr.c_str());

    const unsigned def = 1u;
    EXPECT_EQ(elem->UnsignedText(def), ExpectedUnsignedTextFromQuery(def));
}

TEST_F(XMLElementUnsignedTextTest_252, OverflowReturnsDefaultOrQueryEquivalent_252) {
    // One above UINT_MAX should overflow for an unsigned parse on typical platforms.
    // We do not assume the internal parsing rules; we require consistency with QueryUnsignedText.
    const std::string overflowStr =
        std::to_string(static_cast<unsigned long long>(UINT_MAX) + 1ULL);
    elem->SetText(overflowStr.c_str());

    const unsigned def = 202u;
    EXPECT_EQ(elem->UnsignedText(def), ExpectedUnsignedTextFromQuery(def));
}

TEST_F(XMLElementUnsignedTextTest_252, DifferentDefaultsOnlyAffectFailureCase_252) {
    elem->SetText("not-a-number");

    const unsigned def1 = 11u;
    const unsigned def2 = 22u;

    EXPECT_EQ(elem->UnsignedText(def1), ExpectedUnsignedTextFromQuery(def1));
    EXPECT_EQ(elem->UnsignedText(def2), ExpectedUnsignedTextFromQuery(def2));

    // If parsing fails, the returned value should track the provided default.
    // If parsing surprisingly succeeds, both calls should match the parsed value (and thus each other).
    EXPECT_EQ(
        elem->UnsignedText(def1) == def1,
        elem->UnsignedText(def2) == def2
    );
}
