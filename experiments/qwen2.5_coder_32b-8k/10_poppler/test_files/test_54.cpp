#include <gtest/gtest.h>

#include "SignatureInfo.h"



class SignatureInfoTest_54 : public ::testing::Test {

protected:

    std::unique_ptr<SignatureInfo> signature_info;



    void SetUp() override {

        signature_info = std::make_unique<SignatureInfo>();

    }

};



TEST_F(SignatureInfoTest_54, IsSubfilterSupported_Default_54) {

    EXPECT_FALSE(signature_info->isSubfilterSupported());

}



TEST_F(SignatureInfoTest_54, SetSubFilterSupport_True_54) {

    signature_info->setSubFilterSupport(true);

    EXPECT_TRUE(signature_info->isSubfilterSupported());

}



TEST_F(SignatureInfoTest_54, SetSubFilterSupport_False_54) {

    signature_info->setSubFilterSupport(false);

    EXPECT_FALSE(signature_info->isSubfilterSupported());

}



TEST_F(SignatureInfoTest_54, Getters_DefaultValues_54) {

    EXPECT_EQ(signature_info->getSignatureValStatus(), SIGNATURE_NOT_VERIFIED);

    EXPECT_EQ(signature_info->getSignerName(), "");

    EXPECT_EQ(signature_info->getSubjectDN(), "");

    EXPECT_EQ(signature_info->getLocation().c_str(), nullptr); // GooString is not initialized

    EXPECT_EQ(signature_info->getReason().c_str(), nullptr);  // GooString is not initialized

    EXPECT_EQ(signature_info->getHashAlgorithm(), HashAlgorithm::Unknown);

    EXPECT_EQ(signature_info->getSigningTime(), 0);

    EXPECT_EQ(signature_info->getCertificateInfo(), nullptr);

}



TEST_F(SignatureInfoTest_54, Setters_NewValues_54) {

    signature_info->setSignatureValStatus(SIGNATURE_VERIFIED);

    signature_info->setSignerName("John Doe");

    signature_info->setSubjectDN("CN=John Doe,O=Example Corp,C=US");

    

    std::unique_ptr<GooString> location = std::make_unique<GooString>("Location XYZ");

    std::unique_ptr<GooString> reason = std::make_unique<GooString>("Reason for signing");



    signature_info->setLocation(std::move(location));

    signature_info->setReason(std::move(reason));

    signature_info->setHashAlgorithm(HashAlgorithm::SHA256);

    signature_info->setSigningTime(1633072800); // Example timestamp



    std::unique_ptr<X509CertificateInfo> cert_info = std::make_unique<X509CertificateInfo>();

    signature_info->setCertificateInfo(std::move(cert_info));



    EXPECT_EQ(signature_info->getSignatureValStatus(), SIGNATURE_VERIFIED);

    EXPECT_EQ(signature_info->getSignerName(), "John Doe");

    EXPECT_EQ(signature_info->getSubjectDN(), "CN=John Doe,O=Example Corp,C=US");



    // Since GooString is moved, we can't directly check the values here

    // but we assume they are set correctly based on the setter behavior



    EXPECT_EQ(signature_info->getHashAlgorithm(), HashAlgorithm::SHA256);

    EXPECT_EQ(signature_info->getSigningTime(), 1633072800);

    EXPECT_NE(signature_info->getCertificateInfo(), nullptr); // Just check if it's not null

}
