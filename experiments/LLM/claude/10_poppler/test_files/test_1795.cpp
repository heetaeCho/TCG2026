#include <gtest/gtest.h>
#include <string>

// NSS headers
#include <nss.h>
#include <cert.h>
#include <pk11pub.h>
#include <secmod.h>
#include <seccomon.h>

#include "CertificateInfo.h"

// Include the .cc file to access the static function
// This is necessary because getEntityInfo has internal linkage
#include "NSSCryptoSignBackend.cc"

using namespace std;

class NSSTestEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        if (NSS_NoDB_Init(nullptr) != SECSuccess) {
            FAIL() << "Failed to initialize NSS";
        }
    }
    void TearDown() override {
        NSS_Shutdown();
    }
};

static ::testing::Environment *const nss_env =
    ::testing::AddGlobalTestEnvironment(new NSSTestEnvironment);

class GetEntityInfoTest_1795 : public ::testing::Test {
protected:
    CERTName *createCERTName(const char *dnString) {
        CERTName *name = CERT_AsciiToName(dnString);
        return name;
    }
};

TEST_F(GetEntityInfoTest_1795, NullEntityNameReturnsEmptyInfo_1795) {
    X509CertificateInfo::EntityInfo info = getEntityInfo(nullptr);
    EXPECT_TRUE(info.commonName.empty());
    EXPECT_TRUE(info.distinguishedName.empty());
    EXPECT_TRUE(info.email.empty());
    EXPECT_TRUE(info.organization.empty());
}

TEST_F(GetEntityInfoTest_1795, ValidNameWithCN_1795) {
    CERTName *name = createCERTName("CN=John Doe");
    ASSERT_NE(name, nullptr);

    X509CertificateInfo::EntityInfo info = getEntityInfo(name);

    EXPECT_EQ(info.commonName, "John Doe");
    EXPECT_FALSE(info.distinguishedName.empty());

    CERT_DestroyName(name);
}

TEST_F(GetEntityInfoTest_1795, ValidNameWithOrganization_1795) {
    CERTName *name = createCERTName("CN=Test User,O=Test Corp");
    ASSERT_NE(name, nullptr);

    X509CertificateInfo::EntityInfo info = getEntityInfo(name);

    EXPECT_EQ(info.commonName, "Test User");
    EXPECT_EQ(info.organization, "Test Corp");
    EXPECT_FALSE(info.distinguishedName.empty());

    CERT_DestroyName(name);
}

TEST_F(GetEntityInfoTest_1795, ValidNameWithEmail_1795) {
    CERTName *name = createCERTName("CN=Test User,E=test@example.com,O=TestOrg");
    ASSERT_NE(name, nullptr);

    X509CertificateInfo::EntityInfo info = getEntityInfo(name);

    EXPECT_EQ(info.commonName, "Test User");
    EXPECT_EQ(info.email, "test@example.com");
    EXPECT_EQ(info.organization, "TestOrg");
    EXPECT_FALSE(info.distinguishedName.empty());

    CERT_DestroyName(name);
}

TEST_F(GetEntityInfoTest_1795, ValidNameWithAllFields_1795) {
    CERTName *name = createCERTName("CN=Jane Smith,E=jane@example.org,O=Acme Inc");
    ASSERT_NE(name, nullptr);

    X509CertificateInfo::EntityInfo info = getEntityInfo(name);

    EXPECT_EQ(info.commonName, "Jane Smith");
    EXPECT_EQ(info.email, "jane@example.org");
    EXPECT_EQ(info.organization, "Acme Inc");
    EXPECT_FALSE(info.distinguishedName.empty());

    CERT_DestroyName(name);
}

TEST_F(GetEntityInfoTest_1795, NameWithOnlyOrganization_1795) {
    CERTName *name = createCERTName("O=Solo Org");
    ASSERT_NE(name, nullptr);

    X509CertificateInfo::EntityInfo info = getEntityInfo(name);

    EXPECT_TRUE(info.commonName.empty());
    EXPECT_EQ(info.organization, "Solo Org");
    EXPECT_FALSE(info.distinguishedName.empty());

    CERT_DestroyName(name);
}

TEST_F(GetEntityInfoTest_1795, DistinguishedNameIsPopulated_1795) {
    CERTName *name = createCERTName("CN=DN Test,O=DN Org");
    ASSERT_NE(name, nullptr);

    X509CertificateInfo::EntityInfo info = getEntityInfo(name);

    // DN should contain the components
    EXPECT_FALSE(info.distinguishedName.empty());
    EXPECT_NE(info.distinguishedName.find("DN Test"), std::string::npos);
    EXPECT_NE(info.distinguishedName.find("DN Org"), std::string::npos);

    CERT_DestroyName(name);
}
