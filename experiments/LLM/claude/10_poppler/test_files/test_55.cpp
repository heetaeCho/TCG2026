#include <gtest/gtest.h>
#include "SignatureInfo.h"

class SignatureInfoTest_55 : public ::testing::Test {
protected:
    SignatureInfo sigInfo;
};

// Test default construction - signature validation status should be NOT_VERIFIED
TEST_F(SignatureInfoTest_55, DefaultSignatureValStatus_55) {
    EXPECT_EQ(sigInfo.getSignatureValStatus(), SIGNATURE_NOT_VERIFIED);
}

// Test default construction - signer name should be empty
TEST_F(SignatureInfoTest_55, DefaultSignerNameIsEmpty_55) {
    EXPECT_TRUE(sigInfo.getSignerName().empty());
}

// Test default construction - subject DN should be empty
TEST_F(SignatureInfoTest_55, DefaultSubjectDNIsEmpty_55) {
    EXPECT_TRUE(sigInfo.getSubjectDN().empty());
}

// Test default construction - hash algorithm should be Unknown
TEST_F(SignatureInfoTest_55, DefaultHashAlgorithmIsUnknown_55) {
    EXPECT_EQ(sigInfo.getHashAlgorithm(), HashAlgorithm::Unknown);
}

// Test default construction - signing time should be 0
TEST_F(SignatureInfoTest_55, DefaultSigningTimeIsZero_55) {
    EXPECT_EQ(sigInfo.getSigningTime(), 0);
}

// Test default construction - subfilter supported should be false
TEST_F(SignatureInfoTest_55, DefaultSubfilterSupportedIsFalse_55) {
    EXPECT_FALSE(sigInfo.isSubfilterSupported());
}

// Test default construction - certificate info should be null
TEST_F(SignatureInfoTest_55, DefaultCertificateInfoIsNull_55) {
    EXPECT_EQ(sigInfo.getCertificateInfo(), nullptr);
}

// Test setSignatureValStatus and getSignatureValStatus
TEST_F(SignatureInfoTest_55, SetAndGetSignatureValStatus_55) {
    sigInfo.setSignatureValStatus(SIGNATURE_VALID);
    EXPECT_EQ(sigInfo.getSignatureValStatus(), SIGNATURE_VALID);
}

TEST_F(SignatureInfoTest_55, SetSignatureValStatusInvalid_55) {
    sigInfo.setSignatureValStatus(SIGNATURE_INVALID);
    EXPECT_EQ(sigInfo.getSignatureValStatus(), SIGNATURE_INVALID);
}

TEST_F(SignatureInfoTest_55, SetSignatureValStatusDigestMismatch_55) {
    sigInfo.setSignatureValStatus(SIGNATURE_DIGEST_MISMATCH);
    EXPECT_EQ(sigInfo.getSignatureValStatus(), SIGNATURE_DIGEST_MISMATCH);
}

TEST_F(SignatureInfoTest_55, SetSignatureValStatusDecodingError_55) {
    sigInfo.setSignatureValStatus(SIGNATURE_DECODING_ERROR);
    EXPECT_EQ(sigInfo.getSignatureValStatus(), SIGNATURE_DECODING_ERROR);
}

// Test setSignerName and getSignerName
TEST_F(SignatureInfoTest_55, SetAndGetSignerName_55) {
    sigInfo.setSignerName("John Doe");
    EXPECT_EQ(sigInfo.getSignerName(), "John Doe");
}

TEST_F(SignatureInfoTest_55, SetSignerNameEmpty_55) {
    sigInfo.setSignerName("");
    EXPECT_TRUE(sigInfo.getSignerName().empty());
}

TEST_F(SignatureInfoTest_55, SetSignerNameOverwrite_55) {
    sigInfo.setSignerName("First");
    sigInfo.setSignerName("Second");
    EXPECT_EQ(sigInfo.getSignerName(), "Second");
}

// Test setSubjectDN and getSubjectDN
TEST_F(SignatureInfoTest_55, SetAndGetSubjectDN_55) {
    sigInfo.setSubjectDN("CN=Test,O=Org");
    EXPECT_EQ(sigInfo.getSubjectDN(), "CN=Test,O=Org");
}

TEST_F(SignatureInfoTest_55, SetSubjectDNEmpty_55) {
    sigInfo.setSubjectDN("");
    EXPECT_TRUE(sigInfo.getSubjectDN().empty());
}

// Test setHashAlgorithm and getHashAlgorithm
TEST_F(SignatureInfoTest_55, SetAndGetHashAlgorithmSha1_55) {
    sigInfo.setHashAlgorithm(HashAlgorithm::Sha1);
    EXPECT_EQ(sigInfo.getHashAlgorithm(), HashAlgorithm::Sha1);
}

TEST_F(SignatureInfoTest_55, SetAndGetHashAlgorithmSha256_55) {
    sigInfo.setHashAlgorithm(HashAlgorithm::Sha256);
    EXPECT_EQ(sigInfo.getHashAlgorithm(), HashAlgorithm::Sha256);
}

TEST_F(SignatureInfoTest_55, SetAndGetHashAlgorithmSha512_55) {
    sigInfo.setHashAlgorithm(HashAlgorithm::Sha512);
    EXPECT_EQ(sigInfo.getHashAlgorithm(), HashAlgorithm::Sha512);
}

// Test setSigningTime and getSigningTime
TEST_F(SignatureInfoTest_55, SetAndGetSigningTime_55) {
    time_t testTime = 1609459200; // 2021-01-01 00:00:00 UTC
    sigInfo.setSigningTime(testTime);
    EXPECT_EQ(sigInfo.getSigningTime(), testTime);
}

TEST_F(SignatureInfoTest_55, SetSigningTimeZero_55) {
    sigInfo.setSigningTime(0);
    EXPECT_EQ(sigInfo.getSigningTime(), 0);
}

TEST_F(SignatureInfoTest_55, SetSigningTimeLargeValue_55) {
    time_t largeTime = 2147483647; // Max 32-bit time
    sigInfo.setSigningTime(largeTime);
    EXPECT_EQ(sigInfo.getSigningTime(), largeTime);
}

// Test setSubFilterSupport and isSubfilterSupported
TEST_F(SignatureInfoTest_55, SetSubFilterSupportTrue_55) {
    sigInfo.setSubFilterSupport(true);
    EXPECT_TRUE(sigInfo.isSubfilterSupported());
}

TEST_F(SignatureInfoTest_55, SetSubFilterSupportFalse_55) {
    sigInfo.setSubFilterSupport(false);
    EXPECT_FALSE(sigInfo.isSubfilterSupported());
}

TEST_F(SignatureInfoTest_55, SetSubFilterSupportToggle_55) {
    sigInfo.setSubFilterSupport(true);
    EXPECT_TRUE(sigInfo.isSubfilterSupported());
    sigInfo.setSubFilterSupport(false);
    EXPECT_FALSE(sigInfo.isSubfilterSupported());
}

// Test setLocation and getLocation
TEST_F(SignatureInfoTest_55, SetAndGetLocation_55) {
    auto loc = std::make_unique<GooString>("New York");
    sigInfo.setLocation(std::move(loc));
    EXPECT_EQ(sigInfo.getLocation().toStr(), "New York");
}

TEST_F(SignatureInfoTest_55, SetLocationEmpty_55) {
    auto loc = std::make_unique<GooString>("");
    sigInfo.setLocation(std::move(loc));
    EXPECT_EQ(sigInfo.getLocation().toStr(), "");
}

// Test setReason and getReason
TEST_F(SignatureInfoTest_55, SetAndGetReason_55) {
    auto reason = std::make_unique<GooString>("Approval");
    sigInfo.setReason(std::move(reason));
    EXPECT_EQ(sigInfo.getReason().toStr(), "Approval");
}

TEST_F(SignatureInfoTest_55, SetReasonEmpty_55) {
    auto reason = std::make_unique<GooString>("");
    sigInfo.setReason(std::move(reason));
    EXPECT_EQ(sigInfo.getReason().toStr(), "");
}

// Test setCertificateInfo and getCertificateInfo
TEST_F(SignatureInfoTest_55, SetAndGetCertificateInfo_55) {
    auto certInfo = std::make_unique<X509CertificateInfo>();
    X509CertificateInfo *rawPtr = certInfo.get();
    sigInfo.setCertificateInfo(std::move(certInfo));
    EXPECT_EQ(sigInfo.getCertificateInfo(), rawPtr);
}

TEST_F(SignatureInfoTest_55, SetCertificateInfoOverwrite_55) {
    auto certInfo1 = std::make_unique<X509CertificateInfo>();
    auto certInfo2 = std::make_unique<X509CertificateInfo>();
    X509CertificateInfo *rawPtr2 = certInfo2.get();
    sigInfo.setCertificateInfo(std::move(certInfo1));
    sigInfo.setCertificateInfo(std::move(certInfo2));
    EXPECT_EQ(sigInfo.getCertificateInfo(), rawPtr2);
}

// Test that copy constructor is deleted (compile-time check - just verify it compiles with no copy)
TEST_F(SignatureInfoTest_55, NoCopyConstructor_55) {
    EXPECT_FALSE(std::is_copy_constructible<SignatureInfo>::value);
}

// Test that copy assignment is deleted
TEST_F(SignatureInfoTest_55, NoCopyAssignment_55) {
    EXPECT_FALSE(std::is_copy_assignable<SignatureInfo>::value);
}

// Test setting multiple fields together
TEST_F(SignatureInfoTest_55, SetMultipleFields_55) {
    sigInfo.setSignerName("Jane Smith");
    sigInfo.setSubjectDN("CN=Jane Smith,O=Test Org");
    sigInfo.setSignatureValStatus(SIGNATURE_VALID);
    sigInfo.setHashAlgorithm(HashAlgorithm::Sha256);
    sigInfo.setSigningTime(1609459200);
    sigInfo.setSubFilterSupport(true);

    EXPECT_EQ(sigInfo.getSignerName(), "Jane Smith");
    EXPECT_EQ(sigInfo.getSubjectDN(), "CN=Jane Smith,O=Test Org");
    EXPECT_EQ(sigInfo.getSignatureValStatus(), SIGNATURE_VALID);
    EXPECT_EQ(sigInfo.getHashAlgorithm(), HashAlgorithm::Sha256);
    EXPECT_EQ(sigInfo.getSigningTime(), 1609459200);
    EXPECT_TRUE(sigInfo.isSubfilterSupported());
}

// Test signer name with special characters
TEST_F(SignatureInfoTest_55, SetSignerNameSpecialCharacters_55) {
    sigInfo.setSignerName("José García-López");
    EXPECT_EQ(sigInfo.getSignerName(), "José García-López");
}

// Test subject DN with complex DN string
TEST_F(SignatureInfoTest_55, SetSubjectDNComplex_55) {
    sigInfo.setSubjectDN("CN=Test User,OU=Dev,O=Company Inc.,L=City,ST=State,C=US");
    EXPECT_EQ(sigInfo.getSubjectDN(), "CN=Test User,OU=Dev,O=Company Inc.,L=City,ST=State,C=US");
}
