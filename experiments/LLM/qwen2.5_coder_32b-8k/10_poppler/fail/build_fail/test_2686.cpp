#include <gtest/gtest.h>

#include "./TestProjects/poppler/utils/pdfsig.cc"

#include "./TestProjects/poppler/poppler/CertificateInfo.h"



class CertificateTypeToStringTest_2686 : public ::testing::Test {

protected:

    // No additional setup needed for these simple tests.

};



TEST_F(CertificateTypeToStringTest_2686, X509_ReturnsSMime_2686) {

    EXPECT_STREQ(typeToString(CertificateType::X509), "S/Mime");

}



TEST_F(CertificateTypeToStringTest_2686, PGP_ReturnsPGP_2686) {

    EXPECT_STREQ(typeToString(CertificateType::PGP), "PGP");

}



TEST_F(CertificateTypeToStringTest_2686, InvalidCertificateType_ReturnsEmptyString_2686) {

    // Assuming an invalid type is any value not explicitly defined in the enum.

    // Since we can't directly create an invalid CertificateType, this test checks

    // behavior for an undefined enum value. This might need adjustment based on actual usage.

    EXPECT_STREQ(typeToString(static_cast<CertificateType>(-1)), "");

}
