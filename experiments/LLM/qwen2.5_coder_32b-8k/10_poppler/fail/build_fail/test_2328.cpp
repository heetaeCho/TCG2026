#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking the PopplerCertificateInfo structure for completeness in test setup

struct PopplerCertificateInfo {

    // Assuming some members here for demonstration; actual implementation not needed

};



// Mocking the PopplerSignatureInfo structure to facilitate testing

struct PopplerSignatureInfo {

    int sig_status;

    int cert_status;

    char *signer_name;

    int *local_signing_time;

    PopplerCertificateInfo *certificate_info;

};



// Test fixture for poppler_signature_info_get_certificate_info function

class PopplerSignatureInfoTest_2328 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a sample PopplerSignatureInfo structure for testing

        testSigInfo = new PopplerSignatureInfo();

        testSigInfo->certificate_info = nullptr;  // Default to null for some tests

    }



    void TearDown() override {

        // Clean up the allocated memory after each test

        delete testSigInfo;

    }



    PopplerSignatureInfo *testSigInfo;

};



// Test case to check normal operation when certificate_info is not null

TEST_F(PopplerSignatureInfoTest_2328, GetCertificateInfo_NormalOperation_2328) {

    // Arrange: Set up a valid PopplerCertificateInfo object and assign it to testSigInfo

    PopplerCertificateInfo *expectedCertInfo = new PopplerCertificateInfo();

    testSigInfo->certificate_info = expectedCertInfo;



    // Act: Call the function under test

    PopplerCertificateInfo *result = poppler_signature_info_get_certificate_info(testSigInfo);



    // Assert: Verify that the returned certificate info matches the expected one

    EXPECT_EQ(result, expectedCertInfo);



    // Clean up allocated memory for the mock certificate info object

    delete expectedCertInfo;

}



// Test case to check boundary condition when siginfo is null

TEST_F(PopplerSignatureInfoTest_2328, GetCertificateInfo_NullSiginfo_2328) {

    // Arrange: Set siginfo to nullptr

    PopplerSignatureInfo *nullSiginfo = nullptr;



    // Act & Assert: Verify that the function returns NULL when siginfo is null

    EXPECT_EQ(poppler_signature_info_get_certificate_info(nullSiginfo), nullptr);

}



// Test case to check boundary condition when certificate_info is null

TEST_F(PopplerSignatureInfoTest_2328, GetCertificateInfo_NullCertificateInfo_2328) {

    // Arrange: Ensure testSigInfo->certificate_info is already set to nullptr in SetUp



    // Act & Assert: Verify that the function returns NULL when certificate_info is null

    EXPECT_EQ(poppler_signature_info_get_certificate_info(testSigInfo), nullptr);

}
