#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "CertificateInfo.h"

#include "GPGMECryptoSignBackend.cc"  // Assuming this file contains the implementation



using namespace ::testing;



TEST(getEntityInfoFromKey_1953, NormalOperation_1953) {

    std::string_view dnString = "CN=John Doe,O=Example Corp,EMAIL=john.doe@example.com";

    X509CertificateInfo::EntityInfo info = getEntityInfoFromKey(dnString);

    

    EXPECT_EQ(info.commonName, "John Doe");

    EXPECT_EQ(info.organization, "Example Corp");

    EXPECT_EQ(info.email, "john.doe@example.com");

    EXPECT_EQ(info.distinguishedName, std::string{dnString});

}



TEST(getEntityInfoFromKey_1953, MissingFields_1953) {

    std::string_view dnString = "CN=Jane Doe";

    X509CertificateInfo::EntityInfo info = getEntityInfoFromKey(dnString);

    

    EXPECT_EQ(info.commonName, "Jane Doe");

    EXPECT_EQ(info.organization, "");

    EXPECT_EQ(info.email, "");

    EXPECT_EQ(info.distinguishedName, std::string{dnString});

}



TEST(getEntityInfoFromKey_1953, EmptyDNString_1953) {

    std::string_view dnString = "";

    X509CertificateInfo::EntityInfo info = getEntityInfoFromKey(dnString);

    

    EXPECT_EQ(info.commonName, "");

    EXPECT_EQ(info.organization, "");

    EXPECT_EQ(info.email, "");

    EXPECT_EQ(info.distinguishedName, "");

}



TEST(getEntityInfoFromKey_1953, OnlyEmail_1953) {

    std::string_view dnString = "EMAIL=jane.doe@example.com";

    X509CertificateInfo::EntityInfo info = getEntityInfoFromKey(dnString);

    

    EXPECT_EQ(info.commonName, "");

    EXPECT_EQ(info.organization, "");

    EXPECT_EQ(info.email, "jane.doe@example.com");

    EXPECT_EQ(info.distinguishedName, std::string{dnString});

}



TEST(getEntityInfoFromKey_1953, OnlyOrganization_1953) {

    std::string_view dnString = "O=Acme Corp";

    X509CertificateInfo::EntityInfo info = getEntityInfoFromKey(dnString);

    

    EXPECT_EQ(info.commonName, "");

    EXPECT_EQ(info.organization, "Acme Corp");

    EXPECT_EQ(info.email, "");

    EXPECT_EQ(info.distinguishedName, std::string{dnString});

}



TEST(getEntityInfoFromKey_1953, RepeatedFields_1953) {

    std::string_view dnString = "CN=John Doe,CN=Jane Doe,O=Example Corp";

    X509CertificateInfo::EntityInfo info = getEntityInfoFromKey(dnString);

    

    EXPECT_EQ(info.commonName, "John Doe");

    EXPECT_EQ(info.organization, "Example Corp");

    EXPECT_EQ(info.email, "");

    EXPECT_EQ(info.distinguishedName, std::string{dnString});

}
