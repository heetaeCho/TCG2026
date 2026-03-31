#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <optional>
#include <utility>

#include "./TestProjects/poppler/poppler/DistinguishedNameParser.h"

using DN::detail::parse_dn_part;

class ParseDnPartTest_1943 : public ::testing::Test {
protected:
};

// ============================================================
// Normal operation tests
// ============================================================

TEST_F(ParseDnPartTest_1943, SimpleKeyValuePair_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John Doe");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John Doe");
}

TEST_F(ParseDnPartTest_1943, KeyValueWithTrailingComma_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John Doe,O=Example");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John Doe");
    // remaining should start with ",O=Example"
    ASSERT_TRUE(remaining.has_value());
    EXPECT_FALSE(remaining->empty());
    EXPECT_EQ(remaining->front(), ',');
}

TEST_F(ParseDnPartTest_1943, KeyValueWithSpacesAroundEquals_1943) {
    auto [remaining, kv] = parse_dn_part("CN = John Doe");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John Doe");
}

TEST_F(ParseDnPartTest_1943, KeyValueTrailingSpacesRemovedFromValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John Doe   ");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John Doe");
}

TEST_F(ParseDnPartTest_1943, TrailingSpacesOnKeyRemoved_1943) {
    auto [remaining, kv] = parse_dn_part("CN   =Value");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "Value");
}

TEST_F(ParseDnPartTest_1943, QuotedValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=\"John Doe\"");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John Doe");
}

TEST_F(ParseDnPartTest_1943, QuotedValueWithEscapedQuote_1943) {
    auto [remaining, kv] = parse_dn_part("CN=\"John \\\"Doe\\\"\"");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John \"Doe\"");
}

TEST_F(ParseDnPartTest_1943, QuotedValueWithSpecialChars_1943) {
    auto [remaining, kv] = parse_dn_part("CN=\"Value,with+special;chars\"");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "Value,with+special;chars");
}

TEST_F(ParseDnPartTest_1943, HexStringValue_1943) {
    // #4142 should decode to "AB"
    auto [remaining, kv] = parse_dn_part("CN=#4142");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "AB");
}

TEST_F(ParseDnPartTest_1943, HexStringValueUpperCase_1943) {
    auto [remaining, kv] = parse_dn_part("CN=#4A4B");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "JK");
}

TEST_F(ParseDnPartTest_1943, EscapedCommaInValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John\\,Doe");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John,Doe");
}

TEST_F(ParseDnPartTest_1943, EscapedEqualsInValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John\\=Doe");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John=Doe");
}

TEST_F(ParseDnPartTest_1943, EscapedPlusInValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John\\+Doe");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John+Doe");
}

TEST_F(ParseDnPartTest_1943, EscapedBackslashInValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John\\\\Doe");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John\\Doe");
}

TEST_F(ParseDnPartTest_1943, EscapedHexDigitsInValue_1943) {
    // \41 should decode to 'A'
    auto [remaining, kv] = parse_dn_part("CN=\\41B");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "AB");
}

TEST_F(ParseDnPartTest_1943, EscapedSpaceAtEndPreservesIt_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John\\ ");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John ");
}

TEST_F(ParseDnPartTest_1943, ValueStopsAtComma_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John,O=Org");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John");
    EXPECT_EQ(remaining->front(), ',');
}

TEST_F(ParseDnPartTest_1943, ValueStopsAtSemicolon_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John;O=Org");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John");
    EXPECT_EQ(remaining->front(), ';');
}

TEST_F(ParseDnPartTest_1943, ValueStopsAtPlus_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John+O=Org");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John");
    EXPECT_EQ(remaining->front(), '+');
}

// ============================================================
// Boundary condition tests
// ============================================================

TEST_F(ParseDnPartTest_1943, EmptyString_1943) {
    auto [remaining, kv] = parse_dn_part("");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, OnlyEquals_1943) {
    auto [remaining, kv] = parse_dn_part("=");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, EqualsAtStart_1943) {
    auto [remaining, kv] = parse_dn_part("=value");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, KeyWithNoValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, NoEqualsSign_1943) {
    auto [remaining, kv] = parse_dn_part("CNValue");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, SingleCharKey_1943) {
    auto [remaining, kv] = parse_dn_part("C=US");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "C");
    EXPECT_EQ(kv.second, "US");
}

TEST_F(ParseDnPartTest_1943, SingleCharValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=X");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "X");
}

TEST_F(ParseDnPartTest_1943, HexStringOddDigits_1943) {
    // Odd number of hex digits should fail
    auto [remaining, kv] = parse_dn_part("CN=#414");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, HexStringEmpty_1943) {
    // # with no hex digits should fail
    auto [remaining, kv] = parse_dn_part("CN=#");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, HexStringWithNonHex_1943) {
    // # followed by non-hex should fail (0 valid hex digits)
    auto [remaining, kv] = parse_dn_part("CN=#GG");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, UnterminatedQuotedString_1943) {
    auto [remaining, kv] = parse_dn_part("CN=\"unterminated");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, EmptyQuotedString_1943) {
    auto [remaining, kv] = parse_dn_part("CN=\"\"");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "");
}

TEST_F(ParseDnPartTest_1943, QuoteInUnquotedValueFails_1943) {
    auto [remaining, kv] = parse_dn_part("CN=val\"ue");
    EXPECT_FALSE(remaining.has_value());
}

// ============================================================
// Exceptional / Error case tests
// ============================================================

TEST_F(ParseDnPartTest_1943, BackslashAtEndOfUnquotedValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=value\\");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, BackslashFollowedByInvalidChar_1943) {
    // Backslash followed by non-special, non-hex char
    auto [remaining, kv] = parse_dn_part("CN=value\\z");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, BackslashFollowedBySingleHexDigit_1943) {
    // Only one hex digit after backslash (need 2)
    auto [remaining, kv] = parse_dn_part("CN=value\\4");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, BackslashAtEndOfQuotedValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=\"value\\\"");
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, EscapedHashInValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=val\\#ue");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "val#ue");
}

TEST_F(ParseDnPartTest_1943, EscapedSemicolonInValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=val\\;ue");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "val;ue");
}

TEST_F(ParseDnPartTest_1943, EscapedLessThanInValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=val\\<ue");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "val<ue");
}

TEST_F(ParseDnPartTest_1943, EscapedGreaterThanInValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=val\\>ue");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "val>ue");
}

TEST_F(ParseDnPartTest_1943, EscapedQuoteInUnquotedValue_1943) {
    auto [remaining, kv] = parse_dn_part("CN=val\\\"ue");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "val\"ue");
}

TEST_F(ParseDnPartTest_1943, MultipleSpacesAfterEquals_1943) {
    auto [remaining, kv] = parse_dn_part("CN=   Value");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "Value");
}

TEST_F(ParseDnPartTest_1943, ValueWithInternalSpaces_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John  Doe");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John  Doe");
}

TEST_F(ParseDnPartTest_1943, OnlySpacesAfterEquals_1943) {
    auto [remaining, kv] = parse_dn_part("CN=   ");
    // After removing leading spaces, the value would be empty, which should be handled
    // The trailing spaces should be removed, resulting in empty string
    // Actually, after leading space removal, if empty, it returns {}
    EXPECT_FALSE(remaining.has_value());
}

TEST_F(ParseDnPartTest_1943, HexStringWithMixedCase_1943) {
    auto [remaining, kv] = parse_dn_part("CN=#4a4B");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "JK");
}

TEST_F(ParseDnPartTest_1943, HexStringFollowedByComma_1943) {
    auto [remaining, kv] = parse_dn_part("CN=#4142,O=Org");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "AB");
    EXPECT_FALSE(remaining->empty());
    EXPECT_EQ(remaining->front(), ',');
}

TEST_F(ParseDnPartTest_1943, QuotedValueFollowedByComma_1943) {
    auto [remaining, kv] = parse_dn_part("CN=\"John\",O=Org");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John");
}

TEST_F(ParseDnPartTest_1943, QuotedValueWithBackslashNonQuote_1943) {
    auto [remaining, kv] = parse_dn_part("CN=\"val\\xue\"");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    // Backslash followed by non-quote in quoted string should preserve both chars
    EXPECT_EQ(kv.second, "val\\xue");
}

TEST_F(ParseDnPartTest_1943, ValueStopsAtLessThan_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John<rest");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John");
    EXPECT_EQ(remaining->front(), '<');
}

TEST_F(ParseDnPartTest_1943, ValueStopsAtGreaterThan_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John>rest");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John");
    EXPECT_EQ(remaining->front(), '>');
}

TEST_F(ParseDnPartTest_1943, ValueStopsAtHash_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John#rest");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John");
    EXPECT_EQ(remaining->front(), '#');
}

TEST_F(ParseDnPartTest_1943, ValueStopsAtEquals_1943) {
    auto [remaining, kv] = parse_dn_part("CN=John=rest");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John");
    EXPECT_EQ(remaining->front(), '=');
}

TEST_F(ParseDnPartTest_1943, HexValueFourBytes_1943) {
    // #48454C4C -> "HELL"
    auto [remaining, kv] = parse_dn_part("CN=#48454C4C");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "HELL");
}

TEST_F(ParseDnPartTest_1943, UnescapedTrailingSpacesRemoved_1943) {
    // Trailing unescaped spaces should be removed
    auto [remaining, kv] = parse_dn_part("CN=John   ");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John");
}

TEST_F(ParseDnPartTest_1943, EscapedTrailingSpacePreserved_1943) {
    // Escaped trailing space should be preserved
    auto [remaining, kv] = parse_dn_part("CN=John\\ ");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "John ");
}

TEST_F(ParseDnPartTest_1943, MultipleEqualsSigns_1943) {
    // First = is the separator, rest is value
    auto [remaining, kv] = parse_dn_part("CN=a\\=b");
    ASSERT_TRUE(remaining.has_value());
    EXPECT_EQ(kv.first, "CN");
    EXPECT_EQ(kv.second, "a=b");
}
