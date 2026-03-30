#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-form-field.cc"



// Mocking external collaborators if needed (none in this case)



// Test fixture for PopplerSigningData tests

class PopplerSigningDataTest_2359 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a sample PopplerSigningData structure for testing

        signing_data = new PopplerSigningData;

        signing_data->certificate_info = nullptr;  // Default to no certificate info

    }



    void TearDown() override {

        // Clean up after each test

        delete signing_data;

    }



    PopplerSigningData* signing_data;

};



// Test case for normal operation with certificate info available

TEST_F(PopplerSigningDataTest_2359, GetCertificateInfo_Available_2359) {

    // Arrange: Set up a valid certificate_info in the signing_data

    PopplerCertificateInfo mock_certificate_info;

    signing_data->certificate_info = &mock_certificate_info;



    // Act: Call the function under test

    const PopplerCertificateInfo* result = poppler_signing_data_get_certificate_info(signing_data);



    // Assert: Verify that the returned certificate info matches the expected value

    EXPECT_EQ(result, &mock_certificate_info);

}



// Test case for normal operation with no certificate info available

TEST_F(PopplerSigningDataTest_2359, GetCertificateInfo_NotAvailable_2359) {

    // Arrange: Ensure signing_data->certificate_info is nullptr

    signing_data->certificate_info = nullptr;



    // Act: Call the function under test

    const PopplerCertificateInfo* result = poppler_signing_data_get_certificate_info(signing_data);



    // Assert: Verify that the returned certificate info is nullptr

    EXPECT_EQ(result, nullptr);

}



// Test case for boundary condition with nullptr signing_data input

TEST_F(PopplerSigningDataTest_2359, GetCertificateInfo_NullptrInput_2359) {

    // Arrange: Use a nullptr as input to the function



    // Act: Call the function under test with nullptr

    const PopplerCertificateInfo* result = poppler_signing_data_get_certificate_info(nullptr);



    // Assert: Verify that the returned certificate info is nullptr

    EXPECT_EQ(result, nullptr);

}



// Test case for verification of external interactions (none in this case)

// This function does not interact with any external collaborators, so no tests are needed here.

```


