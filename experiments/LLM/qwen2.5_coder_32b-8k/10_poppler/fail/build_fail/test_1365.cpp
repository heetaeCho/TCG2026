#include <gtest/gtest.h>

#include "TestProjects/poppler/qt5/src/poppler-form.cc"

#include "TestProjects/poppler/poppler/CertificateInfo.h"



namespace Poppler {

    namespace Testing {



class CertificateInfoKeyLocationTest : public ::testing::Test {

protected:

};



TEST_F(CertificateInfoKeyLocationTest, ConvertComputer_1365) {

    EXPECT_EQ(CertificateInfo::KeyLocation::Computer, fromPopplerCore(KeyLocation::Computer));

}



TEST_F(CertificateInfoKeyLocationTest, ConvertOther_1365) {

    EXPECT_EQ(CertificateInfo::KeyLocation::Other, fromPopplerCore(KeyLocation::Other));

}



TEST_F(CertificateInfoKeyLocationTest, ConvertHardwareToken_1365) {

    EXPECT_EQ(CertificateInfo::KeyLocation::HardwareToken, fromPopplerCore(KeyLocation::HardwareToken));

}



TEST_F(CertificateInfoKeyLocationTest, ConvertUnknown_1365) {

    EXPECT_EQ(CertificateInfo::KeyLocation::Unknown, fromPopplerCore(KeyLocation::Unknown));

}



TEST_F(CertificateInfoKeyLocationTest, DefaultCase_1365) {

    KeyLocation invalidLocation = static_cast<KeyLocation>(42); // Invalid enum value

    EXPECT_EQ(CertificateInfo::KeyLocation::Unknown, fromPopplerCore(invalidLocation));

}



} // namespace Testing

} // namespace Poppler
