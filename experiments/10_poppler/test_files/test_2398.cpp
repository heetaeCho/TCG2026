#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"



class PopplerCertificateInfoTest_2398 : public ::testing::Test {

protected:

    void SetUp() override {

        certificate_info = new _PopplerCertificateInfo();

        certificate_info->subject_email = strdup("test@example.com");

    }



    void TearDown() override {

        free(certificate_info->subject_email);

        delete certificate_info;

    }



    _PopplerCertificateInfo* certificate_info;

};



TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_ReturnsCorrectEmail_2398) {

    const char* email = poppler_certificate_info_get_subject_email(certificate_info);

    EXPECT_STREQ(email, "test@example.com");

}



TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_NullPointer_ReturnsNull_2398) {

    const char* email = poppler_certificate_info_get_subject_email(nullptr);

    EXPECT_EQ(email, nullptr);

}



TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_EmptyString_ReturnsEmpty_2398) {

    free(certificate_info->subject_email);

    certificate_info->subject_email = strdup("");

    const char* email = poppler_certificate_info_get_subject_email(certificate_info);

    EXPECT_STREQ(email, "");

}



TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_LongString_ReturnsLongString_2398) {

    free(certificate_info->subject_email);

    certificate_info->subject_email = strdup("a very long email address that should be returned correctly@example.com");

    const char* email = poppler_certificate_info_get_subject_email(certificate_info);

    EXPECT_STREQ(email, "a very long email address that should be returned correctly@example.com");

}
