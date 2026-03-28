#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

#include "poppler-form-field.h"

}



using namespace testing;



class PopplerCertificateInfoTest : public ::testing::Test {

protected:

    void SetUp() override {

        certificate_info = new _PopplerCertificateInfo();

        certificate_info->subject_common_name = strdup("test_subject");

    }



    void TearDown() override {

        free(certificate_info->subject_common_name);

        delete certificate_info;

    }



    PopplerCertificateInfo* certificate_info;

};



TEST_F(PopplerCertificateInfoTest_2396, GetSubjectCommonName_ReturnsCorrectValue_2396) {

    EXPECT_STREQ("test_subject", poppler_certificate_info_get_subject_common_name(certificate_info));

}



TEST_F(PopplerCertificateInfoTest_2396, GetSubjectCommonName_ReturnsNullForNullInput_2396) {

    EXPECT_EQ(nullptr, poppler_certificate_info_get_subject_common_name(nullptr));

}
