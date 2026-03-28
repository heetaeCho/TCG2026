#include <gtest/gtest.h>
#include <string>
#include <string_view>

// Include the implementation to access the static function
// In practice, this would be done through a test-accessible wrapper
#include "poppler/CertificateInfo.h"
#include "poppler/GPGMECryptoSignBackend.cc"

using namespace std;

class GetEntityInfoFromKeyTest_1953 : public ::testing::Test {
protected:
};

TEST_F(GetEntityInfoFromKeyTest_1953, EmptyString_1953)
{
    auto info = getEntityInfoFromKey("");
    EXPECT_EQ(info.commonName, "");
    EXPECT_EQ(info.organization, "");
    EXPECT_EQ(info.email, "");
    EXPECT_EQ(info.distinguishedName, "");
}

TEST_F(GetEntityInfoFromKeyTest_1953, OnlyCN_1953)
{
    auto info = getEntityInfoFromKey("CN=John Doe");
    EXPECT_EQ(info.commonName, "John Doe");
    EXPECT_EQ(info.organization, "");
    EXPECT_EQ(info.email, "");
    EXPECT_EQ(info.distinguishedName, "CN=John Doe");
}

TEST_F(GetEntityInfoFromKeyTest_1953, OnlyOrganization_1953)
{
    auto info = getEntityInfoFromKey("O=Acme Corp");
    EXPECT_EQ(info.commonName, "");
    EXPECT_EQ(info.organization, "Acme Corp");
    EXPECT_EQ(info.email, "");
    EXPECT_EQ(info.distinguishedName, "O=Acme Corp");
}

TEST_F(GetEntityInfoFromKeyTest_1953, OnlyEmail_1953)
{
    auto info = getEntityInfoFromKey("EMAIL=john@example.com");
    EXPECT_EQ(info.commonName, "");
    EXPECT_EQ(info.organization, "");
    EXPECT_EQ(info.email, "john@example.com");
    EXPECT_EQ(info.distinguishedName, "EMAIL=john@example.com");
}

TEST_F(GetEntityInfoFromKeyTest_1953, AllFieldsPresent_1953)
{
    auto info = getEntityInfoFromKey("CN=John Doe,O=Acme Corp,EMAIL=john@example.com");
    EXPECT_EQ(info.commonName, "John Doe");
    EXPECT_EQ(info.organization, "Acme Corp");
    EXPECT_EQ(info.email, "john@example.com");
    EXPECT_EQ(info.distinguishedName, "CN=John Doe,O=Acme Corp,EMAIL=john@example.com");
}

TEST_F(GetEntityInfoFromKeyTest_1953, DistinguishedNamePreservedExactly_1953)
{
    std::string_view dn = "CN=Test User,O=Test Org,EMAIL=test@test.com,OU=Engineering";
    auto info = getEntityInfoFromKey(dn);
    EXPECT_EQ(info.distinguishedName, std::string(dn));
}

TEST_F(GetEntityInfoFromKeyTest_1953, UnknownFieldsIgnored_1953)
{
    auto info = getEntityInfoFromKey("OU=Engineering,L=City,ST=State,C=US");
    EXPECT_EQ(info.commonName, "");
    EXPECT_EQ(info.organization, "");
    EXPECT_EQ(info.email, "");
    EXPECT_EQ(info.distinguishedName, "OU=Engineering,L=City,ST=State,C=US");
}

TEST_F(GetEntityInfoFromKeyTest_1953, MultipleCNReturnsFirst_1953)
{
    auto info = getEntityInfoFromKey("CN=First,CN=Second");
    EXPECT_EQ(info.commonName, "First");
}

TEST_F(GetEntityInfoFromKeyTest_1953, MixedFieldsWithExtraAttributes_1953)
{
    auto info = getEntityInfoFromKey("CN=Jane Smith,OU=Dev,O=BigCorp,C=US,EMAIL=jane@bigcorp.com");
    EXPECT_EQ(info.commonName, "Jane Smith");
    EXPECT_EQ(info.organization, "BigCorp");
    EXPECT_EQ(info.email, "jane@bigcorp.com");
}
