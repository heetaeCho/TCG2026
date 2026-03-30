#include <gtest/gtest.h>

#include "CertificateInfo.h"



// Mocking CERTName for testing purposes

class MockCERTName {

public:

    MOCK_METHOD(char*, CERT_NameToAscii, (), (const));

    MOCK_METHOD(char*, CERT_GetCommonName, (), (const));

    MOCK_METHOD(char*, CERT_GetCertEmailAddress, (), (const));

    MOCK_METHOD(char*, CERT_GetOrgName, (), (const));

};



// Test Fixture

class GetEntityInfoTest_1795 : public ::testing::Test {

protected:

    MockCERTName mockCERTName;

    CERTName* entityName;



    void SetUp() override {

        entityName = reinterpret_cast<CERTName*>(&mockCERTName);

    }



    void TearDown() override {

        entityName = nullptr;

    }

};



// Normal Operation

TEST_F(GetEntityInfoTest_1795, AllFieldsPresent_1795) {

    EXPECT_CALL(mockCERTName, CERT_NameToAscii()).WillOnce(::testing::Return(strdup("CN=John Doe,O=Example,L=City,C=US")));

    EXPECT_CALL(mockCERTName, CERT_GetCommonName()).WillOnce(::testing::Return(strdup("John Doe")));

    EXPECT_CALL(mockCERTName, CERT_GetCertEmailAddress()).WillOnce(::testing::Return(strdup("john.doe@example.com")));

    EXPECT_CALL(mockCERTName, CERT_GetOrgName()).WillOnce(::testing::Return(strdup("Example")));



    X509CertificateInfo::EntityInfo info = getEntityInfo(entityName);

    EXPECT_EQ(info.distinguishedName, "CN=John Doe,O=Example,L=City,C=US");

    EXPECT_EQ(info.commonName, "John Doe");

    EXPECT_EQ(info.email, "john.doe@example.com");

    EXPECT_EQ(info.organization, "Example");

}



// Boundary Conditions

TEST_F(GetEntityInfoTest_1795, EmptyFields_1795) {

    EXPECT_CALL(mockCERTName, CERT_NameToAscii()).WillOnce(::testing::Return(strdup("")));

    EXPECT_CALL(mockCERTName, CERT_GetCommonName()).WillOnce(::testing::Return(strdup("")));

    EXPECT_CALL(mockCERTName, CERT_GetCertEmailAddress()).WillOnce(::testing::Return(strdup("")));

    EXPECT_CALL(mockCERTName, CERT_GetOrgName()).WillOnce(::testing::Return(strdup("")));



    X509CertificateInfo::EntityInfo info = getEntityInfo(entityName);

    EXPECT_EQ(info.distinguishedName, "");

    EXPECT_EQ(info.commonName, "");

    EXPECT_EQ(info.email, "");

    EXPECT_EQ(info.organization, "");

}



// Exceptional or Error Cases

TEST_F(GetEntityInfoTest_1795, NullEntityName_1795) {

    X509CertificateInfo::EntityInfo info = getEntityInfo(nullptr);

    EXPECT_EQ(info.distinguishedName, "");

    EXPECT_EQ(info.commonName, "");

    EXPECT_EQ(info.email, "");

    EXPECT_EQ(info.organization, "");

}



TEST_F(GetEntityInfoTest_1795, NullDistinguishedName_1795) {

    EXPECT_CALL(mockCERTName, CERT_NameToAscii()).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(mockCERTName, CERT_GetCommonName()).WillOnce(::testing::Return(strdup("John Doe")));

    EXPECT_CALL(mockCERTName, CERT_GetCertEmailAddress()).WillOnce(::testing::Return(strdup("john.doe@example.com")));

    EXPECT_CALL(mockCERTName, CERT_GetOrgName()).WillOnce(::testing::Return(strdup("Example")));



    X509CertificateInfo::EntityInfo info = getEntityInfo(entityName);

    EXPECT_EQ(info.distinguishedName, "");

    EXPECT_EQ(info.commonName, "John Doe");

    EXPECT_EQ(info.email, "john.doe@example.com");

    EXPECT_EQ(info.organization, "Example");

}



TEST_F(GetEntityInfoTest_1795, NullCommonName_1795) {

    EXPECT_CALL(mockCERTName, CERT_NameToAscii()).WillOnce(::testing::Return(strdup("CN=John Doe,O=Example,L=City,C=US")));

    EXPECT_CALL(mockCERTName, CERT_GetCommonName()).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(mockCERTName, CERT_GetCertEmailAddress()).WillOnce(::testing::Return(strdup("john.doe@example.com")));

    EXPECT_CALL(mockCERTName, CERT_GetOrgName()).WillOnce(::testing::Return(strdup("Example")));



    X509CertificateInfo::EntityInfo info = getEntityInfo(entityName);

    EXPECT_EQ(info.distinguishedName, "CN=John Doe,O=Example,L=City,C=US");

    EXPECT_EQ(info.commonName, "");

    EXPECT_EQ(info.email, "john.doe@example.com");

    EXPECT_EQ(info.organization, "Example");

}



TEST_F(GetEntityInfoTest_1795, NullEmail_1795) {

    EXPECT_CALL(mockCERTName, CERT_NameToAscii()).WillOnce(::testing::Return(strdup("CN=John Doe,O=Example,L=City,C=US")));

    EXPECT_CALL(mockCERTName, CERT_GetCommonName()).WillOnce(::testing::Return(strdup("John Doe")));

    EXPECT_CALL(mockCERTName, CERT_GetCertEmailAddress()).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(mockCERTName, CERT_GetOrgName()).WillOnce(::testing::Return(strdup("Example")));



    X509CertificateInfo::EntityInfo info = getEntityInfo(entityName);

    EXPECT_EQ(info.distinguishedName, "CN=John Doe,O=Example,L=City,C=US");

    EXPECT_EQ(info.commonName, "John Doe");

    EXPECT_EQ(info.email, "");

    EXPECT_EQ(info.organization, "Example");

}



TEST_F(GetEntityInfoTest_1795, NullOrganization_1795) {

    EXPECT_CALL(mockCERTName, CERT_NameToAscii()).WillOnce(::testing::Return(strdup("CN=John Doe,O=Example,L=City,C=US")));

    EXPECT_CALL(mockCERTName, CERT_GetCommonName()).WillOnce(::testing::Return(strdup("John Doe")));

    EXPECT_CALL(mockCERTName, CERT_GetCertEmailAddress()).WillOnce(::testing::Return(strdup("john.doe@example.com")));

    EXPECT_CALL(mockCERTName, CERT_GetOrgName()).WillOnce(::testing::Return(nullptr));



    X509CertificateInfo::EntityInfo info = getEntityInfo(entityName);

    EXPECT_EQ(info.distinguishedName, "CN=John Doe,O=Example,L=City,C=US");

    EXPECT_EQ(info.commonName, "John Doe");

    EXPECT_EQ(info.email, "john.doe@example.com");

    EXPECT_EQ(info.organization, "");

}
