#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"



// Mocking GDateTime for testing purposes

class MockGDateTime {

public:

    MOCK_METHOD0(get_year, int());

    MOCK_METHOD0(get_month, int());

    MOCK_METHOD0(get_day_of_month, int());

};



TEST(PopplerCertificateInfoTest_2402, GetIssuanceTime_NullPointer_2402) {

    PopplerCertificateInfo *certificate_info = nullptr;

    EXPECT_EQ(poppler_certificate_info_get_issuance_time(certificate_info), nullptr);

}



TEST(PopplerCertificateInfoTest_2402, GetIssuanceTime_NormalOperation_2402) {

    int issuance_time_value = 1672531200; // Example timestamp

    PopplerCertificateInfo certificate_info;

    certificate_info.issued = &issuance_time_value;



    GDateTime *result = poppler_certificate_info_get_issuance_time(&certificate_info);

    EXPECT_NE(result, nullptr);



    // Assuming GDateTime is correctly set based on the timestamp

    // Here we just check if the returned pointer is not null

}



TEST(PopplerCertificateInfoTest_2402, GetIssuanceTime_BoundaryCondition_2402) {

    int issuance_time_value = 0; // Minimum possible timestamp (1970-01-01)

    PopplerCertificateInfo certificate_info;

    certificate_info.issued = &issuance_time_value;



    GDateTime *result = poppler_certificate_info_get_issuance_time(&certificate_info);

    EXPECT_NE(result, nullptr);



    // Assuming GDateTime is correctly set based on the timestamp

    // Here we just check if the returned pointer is not null

}



TEST(PopplerCertificateInfoTest_2402, GetIssuanceTime_ExceptionalCase_2402) {

    int issuance_time_value = -1; // Invalid timestamp

    PopplerCertificateInfo certificate_info;

    certificate_info.issued = &issuance_time_value;



    GDateTime *result = poppler_certificate_info_get_issuance_time(&certificate_info);

    EXPECT_NE(result, nullptr);



    // Assuming GDateTime is correctly set based on the timestamp

    // Here we just check if the returned pointer is not null

}

```


