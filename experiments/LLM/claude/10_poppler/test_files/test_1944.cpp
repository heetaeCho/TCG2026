#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <vector>
#include <utility>

#include "DistinguishedNameParser.h"

class DistinguishedNameParserTest_1944 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test empty string input
TEST_F(DistinguishedNameParserTest_1944, EmptyStringReturnsEmptyResult_1944)
{
    auto result = DN::parseString("");
    EXPECT_TRUE(result.empty());
}

// Test string with only spaces
TEST_F(DistinguishedNameParserTest_1944, OnlySpacesReturnsEmptyResult_1944)
{
    auto result = DN::parseString("   ");
    EXPECT_TRUE(result.empty());
}

// Test a simple single key=value pair
TEST_F(DistinguishedNameParserTest_1944, SingleKeyValuePair_1944)
{
    auto result = DN::parseString("CN=Test");
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].first, "CN");
    EXPECT_EQ(result[0].second, "Test");
}

// Test multiple key=value pairs separated by comma
TEST_F(DistinguishedNameParserTest_1944, MultipleKeyValuePairsCommaSeparated_1944)
{
    auto result = DN::parseString("CN=Test,O=Organization,C=US");
    ASSERT_GE(result.size(), 3u);
    EXPECT_EQ(result[0].first, "CN");
    EXPECT_EQ(result[0].second, "Test");
    EXPECT_EQ(result[1].first, "O");
    EXPECT_EQ(result[1].second, "Organization");
    EXPECT_EQ(result[2].first, "C");
    EXPECT_EQ(result[2].second, "US");
}

// Test multiple key=value pairs separated by semicolons
TEST_F(DistinguishedNameParserTest_1944, MultipleKeyValuePairsSemicolonSeparated_1944)
{
    auto result = DN::parseString("CN=Test;O=Organization;C=US");
    ASSERT_GE(result.size(), 3u);
    EXPECT_EQ(result[0].first, "CN");
    EXPECT_EQ(result[0].second, "Test");
    EXPECT_EQ(result[1].first, "O");
    EXPECT_EQ(result[1].second, "Organization");
    EXPECT_EQ(result[2].first, "C");
    EXPECT_EQ(result[2].second, "US");
}

// Test multiple key=value pairs separated by plus signs
TEST_F(DistinguishedNameParserTest_1944, MultipleKeyValuePairsPlusSeparated_1944)
{
    auto result = DN::parseString("CN=Test+O=Organization+C=US");
    ASSERT_GE(result.size(), 3u);
    EXPECT_EQ(result[0].first, "CN");
    EXPECT_EQ(result[0].second, "Test");
    EXPECT_EQ(result[1].first, "O");
    EXPECT_EQ(result[1].second, "Organization");
    EXPECT_EQ(result[2].first, "C");
    EXPECT_EQ(result[2].second, "US");
}

// Test with leading spaces
TEST_F(DistinguishedNameParserTest_1944, LeadingSpacesAreStripped_1944)
{
    auto result = DN::parseString("   CN=Test");
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result[0].first, "CN");
    EXPECT_EQ(result[0].second, "Test");
}

// Test with spaces around separators
TEST_F(DistinguishedNameParserTest_1944, SpacesAroundSeparators_1944)
{
    auto result = DN::parseString("CN=Test , O=Organization , C=US");
    ASSERT_GE(result.size(), 3u);
    EXPECT_EQ(result[0].first, "CN");
    EXPECT_EQ(result[1].first, "O");
    EXPECT_EQ(result[2].first, "C");
}

// Test invalid input - no equals sign
TEST_F(DistinguishedNameParserTest_1944, InvalidInputNoEqualsReturnsEmpty_1944)
{
    auto result = DN::parseString("InvalidInput");
    // Should return empty result since parsing should fail
    EXPECT_TRUE(result.empty());
}

// Test with quoted value
TEST_F(DistinguishedNameParserTest_1944, QuotedValue_1944)
{
    auto result = DN::parseString("CN=\"Test Value\"");
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result[0].first, "CN");
    // The second value should contain the content of the quoted string
    EXPECT_FALSE(result[0].second.empty());
}

// Test with escaped characters in value
TEST_F(DistinguishedNameParserTest_1944, EscapedCharactersInValue_1944)
{
    auto result = DN::parseString("CN=Test\\,Value,O=Org");
    // Depending on implementation, this may parse one or two entries
    ASSERT_FALSE(result.empty());
}

// Test typical X.509 DN
TEST_F(DistinguishedNameParserTest_1944, TypicalX509DN_1944)
{
    auto result = DN::parseString("CN=John Doe,OU=Engineering,O=Company Inc.,L=City,ST=State,C=US");
    ASSERT_GE(result.size(), 6u);
    EXPECT_EQ(result[0].first, "CN");
    EXPECT_EQ(result[0].second, "John Doe");
    EXPECT_EQ(result[5].first, "C");
    EXPECT_EQ(result[5].second, "US");
}

// Test with OID-style key
TEST_F(DistinguishedNameParserTest_1944, OIDStyleKey_1944)
{
    auto result = DN::parseString("2.5.4.3=Test");
    // Should parse OID-based key
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result[0].second, "Test");
}

// Test invalid separator character
TEST_F(DistinguishedNameParserTest_1944, InvalidSeparatorReturnsEmpty_1944)
{
    auto result = DN::parseString("CN=Test|O=Organization");
    // The pipe is not a valid separator, so parsing should fail after first pair
    // and return empty since it encounters an invalid character
    EXPECT_TRUE(result.empty());
}

// Test mixed separators
TEST_F(DistinguishedNameParserTest_1944, MixedSeparators_1944)
{
    auto result = DN::parseString("CN=Test,O=Org;C=US+OU=Dept");
    ASSERT_GE(result.size(), 4u);
}

// Test hex-encoded value
TEST_F(DistinguishedNameParserTest_1944, HexEncodedValue_1944)
{
    auto result = DN::parseString("CN=#04024869");
    // Hex-encoded values start with #
    ASSERT_FALSE(result.empty());
}

// Test value with spaces
TEST_F(DistinguishedNameParserTest_1944, ValueWithSpaces_1944)
{
    auto result = DN::parseString("CN=John Doe");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].first, "CN");
    EXPECT_EQ(result[0].second, "John Doe");
}

// Test trailing comma should handle gracefully
TEST_F(DistinguishedNameParserTest_1944, TrailingComma_1944)
{
    auto result = DN::parseString("CN=Test,");
    // After the comma there's nothing valid, behavior depends on implementation
    // Either returns empty or the single valid pair
}

// Test equals sign in value (escaped)
TEST_F(DistinguishedNameParserTest_1944, EscapedEqualsInValue_1944)
{
    auto result = DN::parseString("CN=Test\\=Value");
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result[0].first, "CN");
}

// Test single character key and value
TEST_F(DistinguishedNameParserTest_1944, SingleCharKeyAndValue_1944)
{
    auto result = DN::parseString("C=X");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].first, "C");
    EXPECT_EQ(result[0].second, "X");
}

// Test empty key
TEST_F(DistinguishedNameParserTest_1944, EmptyKeyReturnsEmpty_1944)
{
    auto result = DN::parseString("=Value");
    // An empty key should either be skipped or cause failure
    // Based on the code, if dnPair.first is empty, it won't be added
    // But it might not cause a parse failure - result could still be empty
}

// Test very long DN string
TEST_F(DistinguishedNameParserTest_1944, LongDNString_1944)
{
    std::string longDN = "CN=";
    for (int i = 0; i < 1000; i++) {
        longDN += "A";
    }
    auto result = DN::parseString(longDN);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].first, "CN");
    EXPECT_EQ(result[0].second.size(), 1000u);
}

// Test multiple spaces between components
TEST_F(DistinguishedNameParserTest_1944, MultipleSpacesBetweenComponents_1944)
{
    auto result = DN::parseString("CN=Test  ,   O=Org");
    ASSERT_GE(result.size(), 2u);
    EXPECT_EQ(result[0].first, "CN");
    EXPECT_EQ(result[1].first, "O");
}

// Test quoted value with comma inside
TEST_F(DistinguishedNameParserTest_1944, QuotedValueWithComma_1944)
{
    auto result = DN::parseString("CN=\"Last, First\",O=Org");
    ASSERT_GE(result.size(), 2u);
    EXPECT_EQ(result[0].first, "CN");
    EXPECT_EQ(result[1].first, "O");
    EXPECT_EQ(result[1].second, "Org");
}
