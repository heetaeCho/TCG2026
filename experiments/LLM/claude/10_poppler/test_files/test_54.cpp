#include <gtest/gtest.h>
#include "SignatureInfo.h"

class SignatureInfoTest_54 : public ::testing::Test {
protected:
    void SetUp() override {
        sigInfo = std::make_unique<SignatureInfo>();
    }

    void TearDown() override {
        sigInfo.reset();
    }

    std::unique_ptr<SignatureInfo> sigInfo;
};

// Test default construction and initial values
TEST_F(SignatureInfoTest_54, DefaultConstruction_SignatureValStatus_54) {
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_NOT_VERIFIED);
}

TEST_F(SignatureInfoTest_54, DefaultConstruction_SignerName_54) {
    EXPECT_TRUE(sigInfo->getSignerName().empty());
}

TEST_F(SignatureInfoTest_54, DefaultConstruction_SubjectDN_54) {
    EXPECT_TRUE(sigInfo->getSubjectDN().empty());
}

TEST_F(SignatureInfoTest_54, DefaultConstruction_HashAlgorithm_54) {
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Unknown);
}

TEST_F(SignatureInfoTest_54, DefaultConstruction_SigningTime_54) {
    EXPECT_EQ(sigInfo->getSigningTime(), 0);
}

TEST_F(SignatureInfoTest_54, DefaultConstruction_SubfilterSupported_54) {
    EXPECT_FALSE(sigInfo->isSubfilterSupported());
}

TEST_F(SignatureInfoTest_54, DefaultConstruction_CertificateInfo_54) {
    EXPECT_EQ(sigInfo->getCertificateInfo(), nullptr);
}

// Test setters and getters for SignatureValStatus
TEST_F(SignatureInfoTest_54, SetSignatureValStatus_Valid_54) {
    sigInfo->setSignatureValStatus(SIGNATURE_VALID);
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_VALID);
}

TEST_F(SignatureInfoTest_54, SetSignatureValStatus_Invalid_54) {
    sigInfo->setSignatureValStatus(SIGNATURE_INVALID);
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_INVALID);
}

TEST_F(SignatureInfoTest_54, SetSignatureValStatus_DigestMismatch_54) {
    sigInfo->setSignatureValStatus(SIGNATURE_DIGEST_MISMATCH);
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_DIGEST_MISMATCH);
}

TEST_F(SignatureInfoTest_54, SetSignatureValStatus_DecodingError_54) {
    sigInfo->setSignatureValStatus(SIGNATURE_DECODING_ERROR);
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_DECODING_ERROR);
}

// Test setters and getters for SignerName
TEST_F(SignatureInfoTest_54, SetSignerName_NonEmpty_54) {
    sigInfo->setSignerName("John Doe");
    EXPECT_EQ(sigInfo->getSignerName(), "John Doe");
}

TEST_F(SignatureInfoTest_54, SetSignerName_Empty_54) {
    sigInfo->setSignerName("");
    EXPECT_TRUE(sigInfo->getSignerName().empty());
}

TEST_F(SignatureInfoTest_54, SetSignerName_Overwrite_54) {
    sigInfo->setSignerName("First");
    sigInfo->setSignerName("Second");
    EXPECT_EQ(sigInfo->getSignerName(), "Second");
}

TEST_F(SignatureInfoTest_54, SetSignerName_SpecialChars_54) {
    sigInfo->setSignerName("Ñoño Müller");
    EXPECT_EQ(sigInfo->getSignerName(), "Ñoño Müller");
}

// Test setters and getters for SubjectDN
TEST_F(SignatureInfoTest_54, SetSubjectDN_NonEmpty_54) {
    sigInfo->setSubjectDN("CN=John Doe,O=Example,C=US");
    EXPECT_EQ(sigInfo->getSubjectDN(), "CN=John Doe,O=Example,C=US");
}

TEST_F(SignatureInfoTest_54, SetSubjectDN_Empty_54) {
    sigInfo->setSubjectDN("");
    EXPECT_TRUE(sigInfo->getSubjectDN().empty());
}

TEST_F(SignatureInfoTest_54, SetSubjectDN_Overwrite_54) {
    sigInfo->setSubjectDN("CN=First");
    sigInfo->setSubjectDN("CN=Second");
    EXPECT_EQ(sigInfo->getSubjectDN(), "CN=Second");
}

// Test setters and getters for HashAlgorithm
TEST_F(SignatureInfoTest_54, SetHashAlgorithm_Sha1_54) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha1);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Sha1);
}

TEST_F(SignatureInfoTest_54, SetHashAlgorithm_Sha256_54) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha256);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Sha256);
}

TEST_F(SignatureInfoTest_54, SetHashAlgorithm_Sha384_54) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha384);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Sha384);
}

TEST_F(SignatureInfoTest_54, SetHashAlgorithm_Sha512_54) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha512);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Sha512);
}

TEST_F(SignatureInfoTest_54, SetHashAlgorithm_Unknown_54) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha256);
    sigInfo->setHashAlgorithm(HashAlgorithm::Unknown);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Unknown);
}

// Test setters and getters for SigningTime
TEST_F(SignatureInfoTest_54, SetSigningTime_NonZero_54) {
    time_t t = 1609459200; // 2021-01-01 00:00:00 UTC
    sigInfo->setSigningTime(t);
    EXPECT_EQ(sigInfo->getSigningTime(), t);
}

TEST_F(SignatureInfoTest_54, SetSigningTime_Zero_54) {
    sigInfo->setSigningTime(0);
    EXPECT_EQ(sigInfo->getSigningTime(), 0);
}

TEST_F(SignatureInfoTest_54, SetSigningTime_Overwrite_54) {
    sigInfo->setSigningTime(1000);
    sigInfo->setSigningTime(2000);
    EXPECT_EQ(sigInfo->getSigningTime(), 2000);
}

TEST_F(SignatureInfoTest_54, SetSigningTime_LargeValue_54) {
    time_t t = 2147483647; // Max 32-bit signed time_t
    sigInfo->setSigningTime(t);
    EXPECT_EQ(sigInfo->getSigningTime(), t);
}

// Test SubfilterSupported
TEST_F(SignatureInfoTest_54, SetSubFilterSupport_True_54) {
    sigInfo->setSubFilterSupport(true);
    EXPECT_TRUE(sigInfo->isSubfilterSupported());
}

TEST_F(SignatureInfoTest_54, SetSubFilterSupport_False_54) {
    sigInfo->setSubFilterSupport(false);
    EXPECT_FALSE(sigInfo->isSubfilterSupported());
}

TEST_F(SignatureInfoTest_54, SetSubFilterSupport_Toggle_54) {
    sigInfo->setSubFilterSupport(true);
    EXPECT_TRUE(sigInfo->isSubfilterSupported());
    sigInfo->setSubFilterSupport(false);
    EXPECT_FALSE(sigInfo->isSubfilterSupported());
    sigInfo->setSubFilterSupport(true);
    EXPECT_TRUE(sigInfo->isSubfilterSupported());
}

// Test Location
TEST_F(SignatureInfoTest_54, SetLocation_Valid_54) {
    auto loc = std::make_unique<GooString>("New York");
    sigInfo->setLocation(std::move(loc));
    EXPECT_EQ(sigInfo->getLocation().toStr(), "New York");
}

TEST_F(SignatureInfoTest_54, SetLocation_Empty_54) {
    auto loc = std::make_unique<GooString>("");
    sigInfo->setLocation(std::move(loc));
    EXPECT_EQ(sigInfo->getLocation().toStr(), "");
}

TEST_F(SignatureInfoTest_54, SetLocation_Overwrite_54) {
    auto loc1 = std::make_unique<GooString>("First");
    sigInfo->setLocation(std::move(loc1));
    auto loc2 = std::make_unique<GooString>("Second");
    sigInfo->setLocation(std::move(loc2));
    EXPECT_EQ(sigInfo->getLocation().toStr(), "Second");
}

// Test Reason
TEST_F(SignatureInfoTest_54, SetReason_Valid_54) {
    auto reason = std::make_unique<GooString>("I approve this document");
    sigInfo->setReason(std::move(reason));
    EXPECT_EQ(sigInfo->getReason().toStr(), "I approve this document");
}

TEST_F(SignatureInfoTest_54, SetReason_Empty_54) {
    auto reason = std::make_unique<GooString>("");
    sigInfo->setReason(std::move(reason));
    EXPECT_EQ(sigInfo->getReason().toStr(), "");
}

TEST_F(SignatureInfoTest_54, SetReason_Overwrite_54) {
    auto r1 = std::make_unique<GooString>("Reason1");
    sigInfo->setReason(std::move(r1));
    auto r2 = std::make_unique<GooString>("Reason2");
    sigInfo->setReason(std::move(r2));
    EXPECT_EQ(sigInfo->getReason().toStr(), "Reason2");
}

// Test CertificateInfo
TEST_F(SignatureInfoTest_54, SetCertificateInfo_Valid_54) {
    auto certInfo = std::make_unique<X509CertificateInfo>();
    const X509CertificateInfo* rawPtr = certInfo.get();
    sigInfo->setCertificateInfo(std::move(certInfo));
    EXPECT_EQ(sigInfo->getCertificateInfo(), rawPtr);
}

TEST_F(SignatureInfoTest_54, SetCertificateInfo_Nullptr_54) {
    sigInfo->setCertificateInfo(std::unique_ptr<X509CertificateInfo>(nullptr));
    EXPECT_EQ(sigInfo->getCertificateInfo(), nullptr);
}

TEST_F(SignatureInfoTest_54, SetCertificateInfo_Overwrite_54) {
    auto certInfo1 = std::make_unique<X509CertificateInfo>();
    sigInfo->setCertificateInfo(std::move(certInfo1));

    auto certInfo2 = std::make_unique<X509CertificateInfo>();
    const X509CertificateInfo* rawPtr2 = certInfo2.get();
    sigInfo->setCertificateInfo(std::move(certInfo2));
    EXPECT_EQ(sigInfo->getCertificateInfo(), rawPtr2);
}

// Test that copy constructor and assignment operator are deleted (compile-time check, 
// but we verify the object works correctly with move semantics if applicable)
TEST_F(SignatureInfoTest_54, MultipleSettersDoNotInterfere_54) {
    sigInfo->setSignerName("Test Signer");
    sigInfo->setSubjectDN("CN=Test");
    sigInfo->setSignatureValStatus(SIGNATURE_VALID);
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha256);
    sigInfo->setSigningTime(1609459200);
    sigInfo->setSubFilterSupport(true);

    EXPECT_EQ(sigInfo->getSignerName(), "Test Signer");
    EXPECT_EQ(sigInfo->getSubjectDN(), "CN=Test");
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_VALID);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Sha256);
    EXPECT_EQ(sigInfo->getSigningTime(), 1609459200);
    EXPECT_TRUE(sigInfo->isSubfilterSupported());
}

// Test default location and reason
TEST_F(SignatureInfoTest_54, DefaultLocation_54) {
    const GooString& loc = sigInfo->getLocation();
    EXPECT_EQ(loc.getLength(), 0);
}

TEST_F(SignatureInfoTest_54, DefaultReason_54) {
    const GooString& reason = sigInfo->getReason();
    EXPECT_EQ(reason.getLength(), 0);
}
