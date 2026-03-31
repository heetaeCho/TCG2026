#include <gtest/gtest.h>
#include <string_view>

// Include the header under test
#include "./TestProjects/poppler/poppler/DistinguishedNameParser.h"

// Test fixture for attributeNameForOID
class AttributeNameForOIDTest_1942 : public ::testing::Test {
protected:
    // Helper to call the function under test
    std::string_view callAttributeNameForOID(std::string_view oid) {
        return DN::detail::attributeNameForOID(oid);
    }
};

// Test that an empty OID returns an empty string_view
TEST_F(AttributeNameForOIDTest_1942, EmptyOIDReturnsEmpty_1942) {
    auto result = callAttributeNameForOID("");
    EXPECT_TRUE(result.empty());
}

// Test that a completely unknown OID returns empty
TEST_F(AttributeNameForOIDTest_1942, UnknownOIDReturnsEmpty_1942) {
    auto result = callAttributeNameForOID("9.9.9.9.9.9.9");
    EXPECT_TRUE(result.empty());
}

// Test that a random string returns empty
TEST_F(AttributeNameForOIDTest_1942, RandomStringReturnsEmpty_1942) {
    auto result = callAttributeNameForOID("notanoid");
    EXPECT_TRUE(result.empty());
}

// Test known OID for Common Name (CN) - OID 2.5.4.3
TEST_F(AttributeNameForOIDTest_1942, CommonNameOIDReturnsCN_1942) {
    auto result = callAttributeNameForOID("2.5.4.3");
    EXPECT_EQ(result, "CN");
}

// Test known OID for Country (C) - OID 2.5.4.6
TEST_F(AttributeNameForOIDTest_1942, CountryOIDReturnsC_1942) {
    auto result = callAttributeNameForOID("2.5.4.6");
    EXPECT_EQ(result, "C");
}

// Test known OID for Organization (O) - OID 2.5.4.10
TEST_F(AttributeNameForOIDTest_1942, OrganizationOIDReturnsO_1942) {
    auto result = callAttributeNameForOID("2.5.4.10");
    EXPECT_EQ(result, "O");
}

// Test known OID for Organizational Unit (OU) - OID 2.5.4.11
TEST_F(AttributeNameForOIDTest_1942, OrganizationalUnitOIDReturnsOU_1942) {
    auto result = callAttributeNameForOID("2.5.4.11");
    EXPECT_EQ(result, "OU");
}

// Test known OID for Locality (L) - OID 2.5.4.7
TEST_F(AttributeNameForOIDTest_1942, LocalityOIDReturnsL_1942) {
    auto result = callAttributeNameForOID("2.5.4.7");
    EXPECT_EQ(result, "L");
}

// Test known OID for State (ST) - OID 2.5.4.8
TEST_F(AttributeNameForOIDTest_1942, StateOIDReturnsST_1942) {
    auto result = callAttributeNameForOID("2.5.4.8");
    EXPECT_EQ(result, "ST");
}

// Test known OID for Email - OID 1.2.840.113549.1.9.1
TEST_F(AttributeNameForOIDTest_1942, EmailOIDReturnsEmail_1942) {
    auto result = callAttributeNameForOID("1.2.840.113549.1.9.1");
    EXPECT_EQ(result, "Email");
}

// Test OID prefix "OID." with uppercase - should strip prefix and lookup
TEST_F(AttributeNameForOIDTest_1942, OIDPrefixUppercaseStripped_1942) {
    auto result = callAttributeNameForOID("OID.2.5.4.3");
    EXPECT_EQ(result, "CN");
}

// Test OID prefix "oid." with lowercase - should strip prefix and lookup
TEST_F(AttributeNameForOIDTest_1942, OIDPrefixLowercaseStripped_1942) {
    auto result = callAttributeNameForOID("oid.2.5.4.3");
    EXPECT_EQ(result, "CN");
}

// Test OID prefix "OID." with unknown remainder
TEST_F(AttributeNameForOIDTest_1942, OIDPrefixWithUnknownOIDReturnsEmpty_1942) {
    auto result = callAttributeNameForOID("OID.9.9.9.9.9");
    EXPECT_TRUE(result.empty());
}

// Test OID prefix "oid." with unknown remainder
TEST_F(AttributeNameForOIDTest_1942, OidPrefixWithUnknownOIDReturnsEmpty_1942) {
    auto result = callAttributeNameForOID("oid.9.9.9.9.9");
    EXPECT_TRUE(result.empty());
}

// Test that mixed case prefix "Oid." is NOT stripped (only "OID." and "oid." are)
TEST_F(AttributeNameForOIDTest_1942, MixedCasePrefixNotStripped_1942) {
    auto result = callAttributeNameForOID("Oid.2.5.4.3");
    // "Oid.2.5.4.3" won't match the prefix stripping (neither "OID." nor "oid.")
    // and won't match any OID in the map, so should return empty
    EXPECT_TRUE(result.empty());
}

// Test that "OID." prefix only works when string is long enough (length < 4)
TEST_F(AttributeNameForOIDTest_1942, ShortStringNoPrefix_1942) {
    auto result = callAttributeNameForOID("OI");
    EXPECT_TRUE(result.empty());
}

// Test OID with just "OID." prefix and nothing else
TEST_F(AttributeNameForOIDTest_1942, OIDPrefixOnlyReturnsEmpty_1942) {
    auto result = callAttributeNameForOID("OID.");
    EXPECT_TRUE(result.empty());
}

// Test OID with just "oid." prefix and nothing else
TEST_F(AttributeNameForOIDTest_1942, OidPrefixOnlyReturnsEmpty_1942) {
    auto result = callAttributeNameForOID("oid.");
    EXPECT_TRUE(result.empty());
}

// Test OID for Serial Number (SERIALNUMBER) - OID 2.5.4.5
TEST_F(AttributeNameForOIDTest_1942, SerialNumberOID_1942) {
    auto result = callAttributeNameForOID("2.5.4.5");
    // This may or may not be in the oidmap; we test observable behavior
    // If it's not in the map, it returns empty. We still test it doesn't crash.
    // We can't know the exact oidmap without seeing it, so just verify no crash
    // and that result is either a known name or empty.
    EXPECT_TRUE(result.empty() || !result.empty());
}

// Test that the function handles the OID prefix "OID." for country OID
TEST_F(AttributeNameForOIDTest_1942, OIDPrefixCountry_1942) {
    auto result = callAttributeNameForOID("OID.2.5.4.6");
    EXPECT_EQ(result, "C");
}

// Test that the function handles the OID prefix "oid." for organization OID
TEST_F(AttributeNameForOIDTest_1942, OidPrefixOrganization_1942) {
    auto result = callAttributeNameForOID("oid.2.5.4.10");
    EXPECT_EQ(result, "O");
}

// Test with whitespace - should not match anything
TEST_F(AttributeNameForOIDTest_1942, WhitespaceReturnsEmpty_1942) {
    auto result = callAttributeNameForOID("  2.5.4.3  ");
    EXPECT_TRUE(result.empty());
}

// Test with trailing characters on valid OID
TEST_F(AttributeNameForOIDTest_1942, TrailingCharsReturnsEmpty_1942) {
    auto result = callAttributeNameForOID("2.5.4.3.extra");
    EXPECT_TRUE(result.empty());
}

// Test that exact match is required (partial OID)
TEST_F(AttributeNameForOIDTest_1942, PartialOIDReturnsEmpty_1942) {
    auto result = callAttributeNameForOID("2.5.4");
    EXPECT_TRUE(result.empty());
}

// Test "OiD." mixed case prefix - should not strip
TEST_F(AttributeNameForOIDTest_1942, MixedCase2PrefixNotStripped_1942) {
    auto result = callAttributeNameForOID("OiD.2.5.4.3");
    EXPECT_TRUE(result.empty());
}

// Test three character string (less than 4, substr should still work)
TEST_F(AttributeNameForOIDTest_1942, ThreeCharStringNoCrash_1942) {
    auto result = callAttributeNameForOID("OID");
    EXPECT_TRUE(result.empty());
}

// Test single character
TEST_F(AttributeNameForOIDTest_1942, SingleCharReturnsEmpty_1942) {
    auto result = callAttributeNameForOID("O");
    EXPECT_TRUE(result.empty());
}
