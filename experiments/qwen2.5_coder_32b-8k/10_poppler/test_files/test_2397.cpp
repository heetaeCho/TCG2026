#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"



// Mocking the PopplerCertificateInfo structure for testing purposes

struct PopplerCertificateInfo {

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



// Test fixture for poppler_certificate_info_get_subject_organization

class PopplerCertificateInfoTest_2397 : public ::testing::Test {

protected:

    PopplerCertificateInfo certificateInfo;



    void SetUp() override {

        // Initialize the certificateInfo structure with default values

        certificateInfo.id = nullptr;

        certificateInfo.subject_common_name = nullptr;

        certificateInfo.subject_organization = strdup("Example Org");

        certificateInfo.subject_email = nullptr;

        certificateInfo.issuer_common_name = nullptr;

        certificateInfo.issuer_organization = nullptr;

        certificateInfo.issuer_email = nullptr;

        certificateInfo.issued = nullptr;

        certificateInfo.expires = nullptr;

    }



    void TearDown() override {

        // Free allocated memory

        free(certificateInfo.subject_organization);

    }

};



// Test normal operation where subject_organization is set

TEST_F(PopplerCertificateInfoTest_2397, GetSubjectOrganization_NormalOperation_2397) {

    const char* result = poppler_certificate_info_get_subject_organization(&certificateInfo);

    ASSERT_STREQ(result, "Example Org");

}



// Test boundary condition where certificate_info is nullptr

TEST_F(PopplerCertificateInfoTest_2397, GetSubjectOrganization_NullptrInput_2397) {

    const char* result = poppler_certificate_info_get_subject_organization(nullptr);

    EXPECT_EQ(result, nullptr);

}



// Test boundary condition where subject_organization is nullptr

TEST_F(PopplerCertificateInfoTest_2397, GetSubjectOrganization_SubjectOrganizationNullptr_2397) {

    free(certificateInfo.subject_organization);

    certificateInfo.subject_organization = nullptr;

    const char* result = poppler_certificate_info_get_subject_organization(&certificateInfo);

    EXPECT_EQ(result, nullptr);

}
