#include <gtest/gtest.h>

#include "./TestProjects/poppler/qt5/src/poppler-form.cc"

#include "./TestProjects/poppler/poppler/CertificateInfo.h"



using namespace Poppler;



class CertificateTypeConversionTest_1366 : public ::testing::Test {

protected:

    // No additional setup needed for this simple function test

};



TEST_F(CertificateTypeConversionTest_1366, ConvertPGPToCertificateTypePGP_1366) {

    EXPECT_EQ(fromPopplerCore(CertificateType::PGP), CertificateInfo::CertificateType::PGP);

}



TEST_F(CertificateTypeConversionTest_1366, ConvertX509ToCertificateTypeX509_1366) {

    EXPECT_EQ(fromPopplerCore(CertificateType::X509), CertificateInfo::CertificateType::X509);

}



TEST_F(CertificateTypeConversionTest_1366, DefaultFallbackToX509_1366) {

    // Assuming an invalid enum value is provided, it should fallback to X509

    EXPECT_EQ(fromPopplerCore(static_cast<CertificateType>(-1)), CertificateInfo::CertificateType::X509);

}
