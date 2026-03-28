#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

    #include "poppler-form-field.h"

}



class PopplerCertificateInfoTest_2408 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any state before each test (if necessary)

    }



    void TearDown() override {

        // Cleanup any state after each test (if necessary)

    }

};



TEST_F(PopplerCertificateInfoTest_2408, GetCertificateInfoById_NormalOperation_2408) {

    const char* id = "valid_id";

    PopplerCertificateInfo* info = poppler_get_certificate_info_by_id(id);

    if (info != nullptr) {

        poppler_certificate_info_free(info);

    }

    // Assuming valid ID should return non-null pointer

    EXPECT_NE(info, nullptr);

}



TEST_F(PopplerCertificateInfoTest_2408, GetCertificateInfoById_NotFound_2408) {

    const char* id = "non_existent_id";

    PopplerCertificateInfo* info = poppler_get_certificate_info_by_id(id);

    // Assuming non-existent ID should return null pointer

    EXPECT_EQ(info, nullptr);

}



TEST_F(PopplerCertificateInfoTest_2408, GetCertificateInfoById_EmptyId_2408) {

    const char* id = "";

    PopplerCertificateInfo* info = poppler_get_certificate_info_by_id(id);

    // Assuming empty ID should return null pointer

    EXPECT_EQ(info, nullptr);

}



TEST_F(PopplerCertificateInfoTest_2408, GetCertificateInfoById_NullId_2408) {

    const char* id = nullptr;

    PopplerCertificateInfo* info = poppler_get_certificate_info_by_id(id);

    // Assuming null ID should return null pointer

    EXPECT_EQ(info, nullptr);

}
