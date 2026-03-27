#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the function and structure are declared in a header file

extern "C" {

    struct _PopplerCertificateInfo;

    typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

    GDateTime *poppler_certificate_info_get_expiration_time(const PopplerCertificateInfo *certificate_info);

}



// Mocking GDateTime is not necessary as it's an external library type.

// We will focus on testing the function's behavior with valid and invalid inputs.



class PopplerCertificateInfoTest : public ::testing::Test {

protected:

    void SetUp() override {

        certificate_info = new PopplerCertificateInfo();

        certificate_info->expires = new int(1672531200); // Example expiration time (January 1, 2023)

    }



    void TearDown() override {

        delete certificate_info->expires;

        delete certificate_info;

    }



    PopplerCertificateInfo* certificate_info;

};



TEST_F(PopplerCertificateInfoTest_2403, GetExpirationTime_NormalOperation_2403) {

    GDateTime* result = poppler_certificate_info_get_expiration_time(certificate_info);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(g_date_time_to_unix(result), *certificate_info->expires);

}



TEST_F(PopplerCertificateInfoTest_2403, GetExpirationTime_NullPointer_2403) {

    GDateTime* result = poppler_certificate_info_get_expiration_time(nullptr);

    EXPECT_EQ(result, nullptr);

}
