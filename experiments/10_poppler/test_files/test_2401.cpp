#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-form-field.cc"



// Define a mock structure for PopplerCertificateInfo

struct MockPopplerCertificateInfo : public _PopplerCertificateInfo {

    MockPopplerCertificateInfo(const char* issuer_email) {

        this->issuer_email = strdup(issuer_email);

    }

    ~MockPopplerCertificateInfo() {

        free(this->issuer_email);

    }

};



TEST(poppler_certificate_info_get_issuer_email_Test_2401, NormalOperation_2401) {

    MockPopplerCertificateInfo mockCert("test@example.com");

    EXPECT_STREQ(poppler_certificate_info_get_issuer_email(&mockCert), "test@example.com");

}



TEST(poppler_certificate_info_get_issuer_email_Test_2401, NullInput_2401) {

    const char* result = poppler_certificate_info_get_issuer_email(nullptr);

    EXPECT_EQ(result, nullptr);

}



TEST(poppler_certificate_info_get_issuer_email_Test_2401, EmptyEmail_2401) {

    MockPopplerCertificateInfo mockCert("");

    EXPECT_STREQ(poppler_certificate_info_get_issuer_email(&mockCert), "");

}



TEST(poppler_certificate_info_get_issuer_email_Test_2401, LongEmail_2401) {

    std::string longEmail(256, 'a'); // A very long email address

    longEmail += "@example.com";

    MockPopplerCertificateInfo mockCert(longEmail.c_str());

    EXPECT_STREQ(poppler_certificate_info_get_issuer_email(&mockCert), longEmail.c_str());

}
