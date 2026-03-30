// File: tests/xmlwriter_writeAttribute_cstr_tests_478.cpp

#include <gtest/gtest.h>
#include <sstream>

// Include the real headers from your project build; paths may differ.
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

namespace {

using Catch::XmlWriter;
using Catch::StringRef;

// We do not depend on XmlFormatting values or semantics.
// Passing 0 is allowed because the API takes it by value;
// we treat formatting as an opaque flag.
static constexpr auto FMT0 = static_cast<Catch::XmlFormatting>(0);

// Small helper that runs a writer scenario and returns resulting stream text.
template <typename AttrName, typename AttrValue>
std::string WriteOneAttributeScenario(const AttrName& name,
                                      const AttrValue& value) {
    std::ostringstream os;
    XmlWriter w(os);

    // We only rely on public observable behavior: that these calls compile
    // and produce some output (or none). We do not assert any concrete XML,
    // we only compare equality between two flows in tests.
    w.startElement("root", FMT0)
     .writeAttribute(name, value)
     .endElement(FMT0);

    return os.str();
}

template <typename AttrName, typename AttrValue1, typename AttrValue2>
std::string WriteTwoAttributesScenario(const AttrName& name1,
                                       const AttrValue1& value1,
                                       const AttrName& name2,
                                       const AttrValue2& value2) {
    std::ostringstream os;
    XmlWriter w(os);
    w.startElement("root", FMT0)
     .writeAttribute(name1, value1)
     .writeAttribute(name2, value2)
     .endElement(FMT0);
    return os.str();
}

} // namespace

// --- Tests ---

// Verifies that the const char* overload supports chaining by returning *this.
TEST(XmlWriter_WriteAttributeCStr_478, ReturnsSelfForChaining_478) {
    std::ostringstream os;
    XmlWriter w(os);

    // Expect the returned reference to be the same object.
    auto* addr_before = &w;
    auto* addr_after  = &w.writeAttribute(StringRef("k"), "v");
    EXPECT_EQ(addr_before, addr_after);
}

// The core forwarding property: calling with const char* should have the same
// externally observable effect as calling with StringRef of the same text.
TEST(XmlWriter_WriteAttributeCStr_478, MatchesStringRefSingleAttribute_478) {
    const std::string via_cstr =
        WriteOneAttributeScenario(StringRef("key"), "value");
    const std::string via_sref =
        WriteOneAttributeScenario(StringRef("key"), StringRef("value"));

    EXPECT_EQ(via_cstr, via_sref);
}

// Multiple attributes: equality of full output across overloads.
TEST(XmlWriter_WriteAttributeCStr_478, MatchesStringRefMultipleAttributes_478) {
    const std::string via_cstr_sref =
        WriteTwoAttributesScenario(StringRef("a"), "1", StringRef("b"), StringRef("2"));
    const std::string via_sref_cstr =
        WriteTwoAttributesScenario(StringRef("a"), StringRef("1"), StringRef("b"), "2");

    EXPECT_EQ(via_cstr_sref, via_sref_cstr);
}

// Boundary: empty attribute name (if accepted by the implementation).
// We DO NOT assert the exact output, only equivalence between overloads.
TEST(XmlWriter_WriteAttributeCStr_478, EmptyAttributeNameEquivalence_478) {
    const std::string via_cstr =
        WriteOneAttributeScenario(StringRef(""), "v");
    const std::string via_sref =
        WriteOneAttributeScenario(StringRef(""), StringRef("v"));

    EXPECT_EQ(via_cstr, via_sref);
}

// Boundary: empty attribute value.
// Again, we compare outputs across overloads without asserting formatting.
TEST(XmlWriter_WriteAttributeCStr_478, EmptyAttributeValueEquivalence_478) {
    const std::string via_cstr =
        WriteOneAttributeScenario(StringRef("k"), "");
    const std::string via_sref =
        WriteOneAttributeScenario(StringRef("k"), StringRef(""));

    EXPECT_EQ(via_cstr, via_sref);
}

// Special characters in the value: ensure identical escaping/formatting
// is applied regardless of overload chosen.
TEST(XmlWriter_WriteAttributeCStr_478, SpecialCharactersEquivalence_478) {
    // Includes characters often requiring XML escaping.
    const char* special = "a&b<c>d\"e'f";

    const std::string via_cstr =
        WriteOneAttributeScenario(StringRef("k"), special);
    const std::string via_sref =
        WriteOneAttributeScenario(StringRef("k"), StringRef(special));

    EXPECT_EQ(via_cstr, via_sref);
}
