#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    const char *poppler_certificate_info_get_issuer_organization(const PopplerCertificateInfo *certificate_info);

}



struct PopplerCertificateInfo {

    public:

        char * id;

        char * subject_common_name;

        char * subject_organization;

        char * subject_email;

        char * issuer_common_name;

        char * issuer_organization;

        char * issuer_email;

        int * issued;

        int * expires;

};



class CertificateInfoTest_2400 : public ::testing::Test {

protected:

    PopplerCertificateInfo cert_info;



    void SetUp() override {

        // Initialize the certificate info with some default values

        cert_info.id = strdup("123");

        cert_info.subject_common_name = strdup("John Doe");

        cert_info.subject_organization = strdup("Example Corp");

        cert_info.subject_email = strdup("john.doe@example.com");

        cert_info.issuer_common_name = strdup("Jane Smith");

        cert_info.issuer_organization = strdup("Issuer Corp");

        cert_info.issuer_email = strdup("jane.smith@issuer.com");

        cert_info.issued = new int(1609459200); // January 1, 2021

        cert_info.expires = new int(1640995200); // December 31, 2021

    }



    void TearDown() override {

        // Clean up the allocated memory

        free(cert_info.id);

        free(cert_info.subject_common_name);

        free(cert_info.subject_organization);

        free(cert_info.subject_email);

        free(cert_info.issuer_common_name);

        free(cert_info.issuer_organization);

        free(cert_info.issuer_email);

        delete cert_info.issued;

        delete cert_info.expires;

    }

};



TEST_F(CertificateInfoTest_2400, ValidIssuerOrganization_2400) {

    const char* result = poppler_certificate_info_get_issuer_organization(&cert_info);

    EXPECT_STREQ(result, "Issuer Corp");

}



TEST_F(CertificateInfoTest_2400, NullCertificateInfo_2400) {

    const char* result = poppler_certificate_info_get_issuer_organization(nullptr);

    EXPECT_EQ(result, nullptr);

}



TEST_F(CertificateInfoTest_2400, EmptyIssuerOrganization_2400) {

    free(cert_info.issuer_organization);

    cert_info.issuer_organization = strdup("");

    const char* result = poppler_certificate_info_get_issuer_organization(&cert_info);

    EXPECT_STREQ(result, "");

}



TEST_F(CertificateInfoTest_2400, NonEmptyIssuerOrganization_2400) {

    free(cert_info.issuer_organization);

    cert_info.issuer_organization = strdup("New Issuer Corp");

    const char* result = poppler_certificate_info_get_issuer_organization(&cert_info);

    EXPECT_STREQ(result, "New Issuer Corp");

}
