#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

    #include "./TestProjects/poppler/glib/poppler-form-field.cc"

}



using namespace testing;



// Test fixture for PopplerCertificateInfo tests

class PopplerCertificateInfoTest_2399 : public ::testing::Test {

protected:

    void SetUp() override {

        // Allocate memory for the certificate info structure

        cert_info = new _PopplerCertificateInfo;

        cert_info->issuer_common_name = strdup("Example Issuer");

    }



    void TearDown() override {

        // Free allocated memory

        free(cert_info->issuer_common_name);

        delete cert_info;

    }



    PopplerCertificateInfo *cert_info;

};



// Test to verify normal operation when a valid certificate info is passed

TEST_F(PopplerCertificateInfoTest_2399, ValidCertificateInfo_2399) {

    const char *result = poppler_certificate_info_get_issuer_common_name(cert_info);

    EXPECT_STREQ(result, "Example Issuer");

}



// Test to verify behavior when a null certificate info is passed

TEST_F(PopplerCertificateInfoTest_2399, NullCertificateInfo_2399) {

    const char *result = poppler_certificate_info_get_issuer_common_name(nullptr);

    EXPECT_EQ(result, nullptr);

}
