// tests/string_matcher_base_describe_218_test.cpp
#include <gtest/gtest.h>
#include <string>

// Headers under test (paths based on the prompt)
#include "catch2/matchers/catch_matchers_string.hpp"

using namespace Catch;
using namespace Catch::Matchers;

// Minimal concrete matcher to instantiate StringMatcherBase.
// We do not test match() here; it's just to satisfy the abstract base.
class DummyStringMatcher_218 : public StringMatcherBase {
public:
    DummyStringMatcher_218(StringRef operation, const CasedString& comparator)
        : StringMatcherBase(operation, comparator) {}

    // Provide a trivial implementation to make the class concrete.
    bool match(std::string const&) const override { return false; }
};

// ---------- Tests ----------

TEST(StringMatcherBaseDescribe_218, BasicComposition_218) {
    // Arrange
    const std::string compStr = "abc";
    CasedString comp(compStr, CaseSensitive::Yes);
    DummyStringMatcher_218 matcher(StringRef("contains"), comp);

    // Act
    const std::string desc = matcher.describe();

    // Assert
    // Expected is exactly: <op> + ': "' + <comparator.m_str> + '"' + <suffix>
    const std::string expected =
        std::string("contains: \"") + comp.m_str + "\"" + std::string(comp.caseSensitivitySuffix());
    EXPECT_EQ(desc, expected);
}

TEST(StringMatcherBaseDescribe_218, EmptyComparatorString_218) {
    // Arrange
    const std::string emptyStr = "";
    CasedString comp(emptyStr, CaseSensitive::Yes);
    DummyStringMatcher_218 matcher(StringRef("equals"), comp);

    // Act
    const std::string desc = matcher.describe();

    // Assert
    const std::string expected =
        std::string("equals: \"\"") + std::string(comp.caseSensitivitySuffix());
    EXPECT_EQ(desc, expected);
}

TEST(StringMatcherBaseDescribe_218, OperationWithSpaces_218) {
    // Arrange
    const std::string compStr = "needle";
    CasedString comp(compStr, CaseSensitive::Yes);

    // Operation supplied via StringRef should be preserved verbatim
    DummyStringMatcher_218 matcher(StringRef("starts with"), comp);

    // Act
    const std::string desc = matcher.describe();

    // Assert
    const std::string expected =
        std::string("starts with: \"") + comp.m_str + "\"" + std::string(comp.caseSensitivitySuffix());
    EXPECT_EQ(desc, expected);
}

TEST(StringMatcherBaseDescribe_218, CaseSensitivityAffectsSuffix_218) {
    // Arrange
    const std::string compStr = "Value";
    CasedString compSensitive(compStr, CaseSensitive::Yes);
    CasedString compInsensitive(compStr, CaseSensitive::No);

    DummyStringMatcher_218 m1(StringRef("match"), compSensitive);
    DummyStringMatcher_218 m2(StringRef("match"), compInsensitive);

    // Act
    const std::string d1 = m1.describe();
    const std::string d2 = m2.describe();

    // Assert
    // We do not assume what the suffix is, only that differing case-sensitivity
    // settings produce different final descriptions (observable behavior).
    EXPECT_NE(d1, d2);
}

TEST(StringMatcherBaseDescribe_218, LongComparatorString_218) {
    // Arrange
    const std::string longStr(1024, 'x');  // boundary-ish size
    CasedString comp(longStr, CaseSensitive::No);
    DummyStringMatcher_218 matcher(StringRef("contains"), comp);

    // Act
    const std::string desc = matcher.describe();

    // Assert
    // Ensure full content is included and properly quoted + suffixed.
    ASSERT_GE(desc.size(), longStr.size());  // sanity: description should be at least as long
    const std::string expectedPrefix = "contains: \"";
    ASSERT_TRUE(desc.rfind(expectedPrefix, 0) == 0); // starts with expected op + opening quote
    // Ends with suffix (unknown exact value) but must contain the quoted payload exactly.
    const auto quotePos = desc.find('"', expectedPrefix.size());
    ASSERT_NE(quotePos, std::string::npos);
    const std::string inside = desc.substr(expectedPrefix.size(),
                                           quotePos - expectedPrefix.size());
    EXPECT_EQ(inside, longStr);
    // There should be a closing quote immediately after the payload.
    EXPECT_EQ(desc[expectedPrefix.size() + longStr.size()], '"');
    // Suffix follows the trailing quote (could be empty or non-empty).
    // No further structural assertions needed beyond presence.
}
