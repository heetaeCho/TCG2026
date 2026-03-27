#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-form-field.cc"



TEST(PopplerCertificateInfoTest_2394, NewReturnsNonNullPointer_2394) {

    PopplerCertificateInfo* info = poppler_certificate_info_new();

    EXPECT_NE(info, nullptr);

    g_free(info);  // Clean up the allocated memory

}



TEST(PopplerCertificateInfoTest_2394, NewInitializesMemoryToZero_2394) {

    PopplerCertificateInfo* info = poppler_certificate_info_new();

    for (size_t i = 0; i < sizeof(PopplerCertificateInfo); ++i) {

        EXPECT_EQ(((char*)info)[i], 0);

    }

    g_free(info);  // Clean up the allocated memory

}
