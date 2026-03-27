#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"



using ::testing::IsNull;

using ::testing::NotNull;



class PopplerSigningDataTest_2358 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = static_cast<PopplerSigningData*>(g_malloc0(sizeof(PopplerSigningData)));

        certificate_info = static_cast<PopplerCertificateInfo*>(g_malloc0(sizeof(PopplerCertificateInfo)));



        certificate_info->id = g_strdup("12345");

        certificate_info->subject_common_name = g_strdup("John Doe");

    }



    void TearDown() override {

        if (signing_data) {

            poppler_signing_data_free(signing_data);

            signing_data = nullptr;

        }

        if (certificate_info) {

            poppler_certificate_info_free(certificate_info);

            certificate_info = nullptr;

        }

    }



    PopplerSigningData* signing_data;

    PopplerCertificateInfo* certificate_info;

};



TEST_F(PopplerSigningDataTest_2358, SetCertificateInfo_NormalOperation_2358) {

    poppler_signing_data_set_certificate_info(signing_data, certificate_info);

    EXPECT_STREQ(signing_data->certificate_info->id, "12345");

    EXPECT_STREQ(signing_data->certificate_info->subject_common_name, "John Doe");

}



TEST_F(PopplerSigningDataTest_2358, SetCertificateInfo_SameCertificateInfo_NoChange_2358) {

    poppler_signing_data_set_certificate_info(signing_data, certificate_info);

    PopplerCertificateInfo* same_certificate_info = poppler_certificate_info_copy(certificate_info);

    poppler_signing_data_set_certificate_info(signing_data, same_certificate_info);



    EXPECT_STREQ(signing_data->certificate_info->id, "12345");

    EXPECT_STREQ(signing_data->certificate_info->subject_common_name, "John Doe");



    // Free the copied certificate info

    poppler_certificate_info_free(same_certificate_info);

}



TEST_F(PopplerSigningDataTest_2358, SetCertificateInfo_NullSigningData_DoesNothing_2358) {

    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_set_certificate_info(nullptr, certificate_info));

}



TEST_F(PopplerSigningDataTest_2358, SetCertificateInfo_NullCertificateInfo_DoesNothing_2358) {

    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_set_certificate_info(signing_data, nullptr));

}
