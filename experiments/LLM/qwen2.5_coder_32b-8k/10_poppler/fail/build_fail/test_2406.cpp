#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    struct _PopplerCertificateInfo { 

        char * id; 

        char * subject_common_name; 

        char * subject_organization; 

        char * subject_email; 

        char * issuer_common_name; 

        char * issuer_organization; 

        char * issuer_email; 

        void* issued; 

        void* expires; 

    };



    typedef struct _PopplerCertificateInfo PopplerCertificateInfo;



    void poppler_certificate_info_free(PopplerCertificateInfo *certificate_info);

}



class PopplerCertificateInfoTest_2406 : public ::testing::Test {

protected:

    virtual void SetUp() override {

        certificate_info = new PopplerCertificateInfo();

        certificate_info->id = g_strdup("test_id");

        certificate_info->subject_common_name = g_strdup("test_subject_common_name");

        certificate_info->subject_organization = g_strdup("test_subject_organization");

        certificate_info->subject_email = g_strdup("test_subject_email");

        certificate_info->issuer_common_name = g_strdup("test_issuer_common_name");

        certificate_info->issuer_organization = g_strdup("test_issuer_organization");

        certificate_info->issuer_email = g_strdup("test_issuer_email");

        // Assuming issued and expires are GDateTime pointers, which we don't have direct access to create

        // For simplicity, we set them to non-null values.

        certificate_info->issued = reinterpret_cast<void*>(1);

        certificate_info->expires = reinterpret_cast<void*>(2);

    }



    virtual void TearDown() override {

        poppler_certificate_info_free(certificate_info);

    }



    PopplerCertificateInfo* certificate_info;

};



TEST_F(PopplerCertificateInfoTest_2406, FreeNullPointer_2406) {

    poppler_certificate_info_free(nullptr);

}



TEST_F(PopplerCertificateInfoTest_2406, FreeValidPointer_2406) {

    // The setup already allocated a valid pointer, so we just call the free function

    // No assertion needed as the function should not crash and properly release memory.

    poppler_certificate_info_free(certificate_info);

}



TEST_F(PopplerCertificateInfoTest_2406, FreeMultipleTimes_2406) {

    // The setup already allocated a valid pointer

    poppler_certificate_info_free(certificate_info);

    // Calling free again should not cause issues as the pointers inside are set to null after first free.

    poppler_certificate_info_free(certificate_info);  // This line should not crash

}



TEST_F(PopplerCertificateInfoTest_2406, FreeWithNullMembers_2406) {

    g_clear_pointer(&certificate_info->id, g_free);

    g_clear_pointer(&certificate_info->subject_common_name, g_free);

    g_clear_pointer(&certificate_info->subject_organization, g_free);

    g_clear_pointer(&certificate_info->subject_email, g_free);

    g_clear_pointer(&certificate_info->issuer_common_name, g_free);

    g_clear_pointer(&certificate_info->issuer_organization, g_free);

    g_clear_pointer(&certificate_info->issuer_email, g_free);

    g_clear_pointer(&certificate_info->issued, g_date_time_unref);

    g_clear_pointer(&certificate_info->expires, g_date_time_unref);



    // Now all members are null, calling free should not cause issues.

    poppler_certificate_info_free(certificate_info);

}
