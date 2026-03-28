#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-form-field.cc"



// Mocking external dependencies if necessary (none in this case)



struct PopplerCertificateInfo {

    char * id;

    char * subject_common_name;

    char * subject_organization;

    char * subject_email;

    char * issuer_common_name;

    char * issuer_organization;

    char * issuer_email;

    int * issued;

    int * expires;

};



// Test fixture for poppler_certificate_info_get_id

class PopplerCertificateInfoTest : public ::testing::Test {

protected:

    void SetUp() override {

        certificate_info = new PopplerCertificateInfo();

        certificate_info->id = strdup("test_id");

    }



    void TearDown() override {

        free(certificate_info->id);

        delete certificate_info;

    }



    PopplerCertificateInfo *certificate_info;

};



// Test case for normal operation

TEST_F(PopplerCertificateInfoTest, GetId_ReturnsCorrectValue_2395) {

    const char* result = poppler_certificate_info_get_id(certificate_info);

    EXPECT_STREQ(result, "test_id");

}



// Test case for boundary condition: null input

TEST(PopplerCertificateInfoTest, GetId_NullInput_ReturnsNull_2395) {

    const char* result = poppler_certificate_info_get_id(nullptr);

    EXPECT_EQ(result, nullptr);

}
