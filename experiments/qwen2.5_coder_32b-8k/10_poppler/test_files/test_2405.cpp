#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"



// Mocking GDateTime for g_date_time_ref and g_date_time_unref

class MockGDateTime {

public:

    MOCK_METHOD(GDateTime*, g_date_time_ref, (GDateTime* datetime), ());

    MOCK_METHOD(void, g_date_time_unref, (GDateTime* datetime), ());

};



extern "C" {

    GDateTime* g_date_time_ref(GDateTime* datetime) {

        return MockGDateTime::g_date_time_ref(datetime);

    }



    void g_date_time_unref(GDateTime* datetime) {

        MockGDateTime::g_date_time_unref(datetime);

    }

}



class PopplerCertificateInfoTest : public ::testing::Test {

protected:

    void SetUp() override {

        mock_gdatetime = new MockGDateTime();

        ON_CALL(*mock_gdatetime, g_date_time_ref(testing::_)).WillByDefault(testing::ReturnArgument<0>());

    }



    void TearDown() override {

        delete mock_gdatetime;

    }



    static PopplerCertificateInfo* createPopplerCertificateInfo() {

        PopplerCertificateInfo* info = new PopplerCertificateInfo();

        info->id = g_strdup("test_id");

        info->subject_common_name = g_strdup("test_subject_common_name");

        info->subject_organization = g_strdup("test_subject_organization");

        info->subject_email = g_strdup("test_subject_email");

        info->issuer_common_name = g_strdup("test_issuer_common_name");

        info->issuer_organization = g_strdup("test_issuer_organization");

        info->issuer_email = g_strdup("test_issuer_email");

        info->issued = reinterpret_cast<GDateTime*>(0x12345678); // Mocking a GDateTime pointer

        info->expires = reinterpret_cast<GDateTime*>(0x87654321); // Mocking a GDateTime pointer

        return info;

    }



    static void freePopplerCertificateInfo(PopplerCertificateInfo* info) {

        g_free(info->id);

        g_free(info->subject_common_name);

        g_free(info->subject_organization);

        g_free(info->subject_email);

        g_free(info->issuer_common_name);

        g_free(info->issuer_organization);

        g_free(info->issuer_email);

        delete info;

    }



    MockGDateTime* mock_gdatetime;

};



TEST_F(PopplerCertificateInfoTest, CopyNormalOperation_2405) {

    PopplerCertificateInfo* original = createPopplerCertificateInfo();

    EXPECT_CALL(*mock_gdatetime, g_date_time_ref(original->issued)).Times(1);

    EXPECT_CALL(*mock_gdatetime, g_date_time_ref(original->expires)).Times(1);



    PopplerCertificateInfo* copy = poppler_certificate_info_copy(original);

    ASSERT_NE(copy, nullptr);



    EXPECT_STREQ(copy->id, original->id);

    EXPECT_STREQ(copy->subject_common_name, original->subject_common_name);

    EXPECT_STREQ(copy->subject_organization, original->subject_organization);

    EXPECT_STREQ(copy->subject_email, original->subject_email);

    EXPECT_STREQ(copy->issuer_common_name, original->issuer_common_name);

    EXPECT_STREQ(copy->issuer_organization, original->issuer_organization);

    EXPECT_STREQ(copy->issuer_email, original->issuer_email);

    EXPECT_EQ(copy->issued, original->issued);

    EXPECT_EQ(copy->expires, original->expires);



    freePopplerCertificateInfo(original);

    g_free(copy->id);

    g_free(copy->subject_common_name);

    g_free(copy->subject_organization);

    g_free(copy->subject_email);

    g_free(copy->issuer_common_name);

    g_free(copy->issuer_organization);

    g_free(copy->issuer_email);

    EXPECT_CALL(*mock_gdatetime, g_date_time_unref(copy->issued)).Times(1);

    EXPECT_CALL(*mock_gdatetime, g_date_time_unref(copy->expires)).Times(1);

    freePopplerCertificateInfo(copy);

}



TEST_F(PopplerCertificateInfoTest, CopyNullPointer_2405) {

    PopplerCertificateInfo* copy = poppler_certificate_info_copy(nullptr);

    EXPECT_EQ(copy, nullptr);

}
