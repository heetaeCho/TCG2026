#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <string>
#include <optional>

#include "poppler-form.h"
#include "poppler-qt5.h"
#include "SignatureInfo.h"
#include "Form.h"
#include "GooString.h"

// Since fromInternal is a static (file-local) function in poppler-form.cc,
// we test through the public API that exercises it, or test the types it produces.
// We focus on SignatureValidationInfo observable behavior.

namespace {

class SignatureValidationInfoTest_1369 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test SignatureValidationInfo default construction behavior
TEST_F(SignatureValidationInfoTest_1369, DefaultConstruction_1369) {
    // SignatureValidationInfo should be constructible
    // Testing through the public Poppler Qt5 API
    Poppler::SignatureValidationInfo info;
    // Default should have some defined state
    EXPECT_EQ(info.signatureStatus(), Poppler::SignatureValidationInfo::SignatureNotVerified);
}

TEST_F(SignatureValidationInfoTest_1369, CopyConstruction_1369) {
    Poppler::SignatureValidationInfo info;
    Poppler::SignatureValidationInfo copy(info);
    EXPECT_EQ(copy.signatureStatus(), info.signatureStatus());
}

TEST_F(SignatureValidationInfoTest_1369, Assignment_1369) {
    Poppler::SignatureValidationInfo info;
    Poppler::SignatureValidationInfo other;
    other = info;
    EXPECT_EQ(other.signatureStatus(), info.signatureStatus());
}

// Test SignatureInfo status mapping values
class SignatureInfoTest_1369 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(SignatureInfoTest_1369, DefaultSignatureStatus_1369) {
    SignatureInfo si;
    EXPECT_EQ(si.getSignatureValStatus(), SIGNATURE_NOT_VERIFIED);
}

TEST_F(SignatureInfoTest_1369, SetSignatureValid_1369) {
    SignatureInfo si;
    si.setSignatureValStatus(SIGNATURE_VALID);
    EXPECT_EQ(si.getSignatureValStatus(), SIGNATURE_VALID);
}

TEST_F(SignatureInfoTest_1369, SetSignatureInvalid_1369) {
    SignatureInfo si;
    si.setSignatureValStatus(SIGNATURE_INVALID);
    EXPECT_EQ(si.getSignatureValStatus(), SIGNATURE_INVALID);
}

TEST_F(SignatureInfoTest_1369, SetSignatureDigestMismatch_1369) {
    SignatureInfo si;
    si.setSignatureValStatus(SIGNATURE_DIGEST_MISMATCH);
    EXPECT_EQ(si.getSignatureValStatus(), SIGNATURE_DIGEST_MISMATCH);
}

TEST_F(SignatureInfoTest_1369, SetSignatureDecodingError_1369) {
    SignatureInfo si;
    si.setSignatureValStatus(SIGNATURE_DECODING_ERROR);
    EXPECT_EQ(si.getSignatureValStatus(), SIGNATURE_DECODING_ERROR);
}

TEST_F(SignatureInfoTest_1369, SetSignatureGenericError_1369) {
    SignatureInfo si;
    si.setSignatureValStatus(SIGNATURE_GENERIC_ERROR);
    EXPECT_EQ(si.getSignatureValStatus(), SIGNATURE_GENERIC_ERROR);
}

TEST_F(SignatureInfoTest_1369, SetSignatureNotFound_1369) {
    SignatureInfo si;
    si.setSignatureValStatus(SIGNATURE_NOT_FOUND);
    EXPECT_EQ(si.getSignatureValStatus(), SIGNATURE_NOT_FOUND);
}

TEST_F(SignatureInfoTest_1369, SetSignerName_1369) {
    SignatureInfo si;
    si.setSignerName("Test Signer");
    EXPECT_EQ(si.getSignerName(), "Test Signer");
}

TEST_F(SignatureInfoTest_1369, SetSubjectDN_1369) {
    SignatureInfo si;
    si.setSubjectDN("CN=Test,O=TestOrg");
    EXPECT_EQ(si.getSubjectDN(), "CN=Test,O=TestOrg");
}

TEST_F(SignatureInfoTest_1369, SetEmptySignerName_1369) {
    SignatureInfo si;
    si.setSignerName("");
    EXPECT_EQ(si.getSignerName(), "");
}

TEST_F(SignatureInfoTest_1369, SetSigningTime_1369) {
    SignatureInfo si;
    time_t now = time(nullptr);
    si.setSigningTime(now);
    EXPECT_EQ(si.getSigningTime(), now);
}

TEST_F(SignatureInfoTest_1369, DefaultSigningTime_1369) {
    SignatureInfo si;
    EXPECT_EQ(si.getSigningTime(), 0);
}

TEST_F(SignatureInfoTest_1369, SetHashAlgorithm_1369) {
    SignatureInfo si;
    si.setHashAlgorithm(HashAlgorithm::Sha256);
    EXPECT_EQ(si.getHashAlgorithm(), HashAlgorithm::Sha256);
}

TEST_F(SignatureInfoTest_1369, DefaultHashAlgorithm_1369) {
    SignatureInfo si;
    EXPECT_EQ(si.getHashAlgorithm(), HashAlgorithm::Unknown);
}

TEST_F(SignatureInfoTest_1369, SetLocation_1369) {
    SignatureInfo si;
    auto loc = std::make_unique<GooString>("Test Location");
    si.setLocation(std::move(loc));
    EXPECT_EQ(si.getLocation().toStr(), "Test Location");
}

TEST_F(SignatureInfoTest_1369, SetReason_1369) {
    SignatureInfo si;
    auto reason = std::make_unique<GooString>("Approval");
    si.setReason(std::move(reason));
    EXPECT_EQ(si.getReason().toStr(), "Approval");
}

TEST_F(SignatureInfoTest_1369, DefaultCertificateInfoIsNull_1369) {
    SignatureInfo si;
    EXPECT_EQ(si.getCertificateInfo(), nullptr);
}

TEST_F(SignatureInfoTest_1369, SubfilterSupportDefault_1369) {
    SignatureInfo si;
    EXPECT_FALSE(si.isSubfilterSupported());
}

TEST_F(SignatureInfoTest_1369, SetSubfilterSupport_1369) {
    SignatureInfo si;
    si.setSubFilterSupport(true);
    EXPECT_TRUE(si.isSubfilterSupported());
}

TEST_F(SignatureInfoTest_1369, SetSubfilterSupportFalse_1369) {
    SignatureInfo si;
    si.setSubFilterSupport(true);
    si.setSubFilterSupport(false);
    EXPECT_FALSE(si.isSubfilterSupported());
}

// Test SignatureValidationInfo accessors
TEST_F(SignatureValidationInfoTest_1369, SignerName_1369) {
    Poppler::SignatureValidationInfo info;
    // Default signer name should be empty
    EXPECT_TRUE(info.signerName().isEmpty());
}

TEST_F(SignatureValidationInfoTest_1369, SignerSubjectDN_1369) {
    Poppler::SignatureValidationInfo info;
    EXPECT_TRUE(info.signerSubjectDN().isEmpty());
}

TEST_F(SignatureValidationInfoTest_1369, Location_1369) {
    Poppler::SignatureValidationInfo info;
    EXPECT_TRUE(info.location().isEmpty());
}

TEST_F(SignatureValidationInfoTest_1369, Reason_1369) {
    Poppler::SignatureValidationInfo info;
    EXPECT_TRUE(info.reason().isEmpty());
}

TEST_F(SignatureValidationInfoTest_1369, SigningTime_1369) {
    Poppler::SignatureValidationInfo info;
    EXPECT_EQ(info.signingTime(), 0);
}

TEST_F(SignatureValidationInfoTest_1369, HashAlgorithm_1369) {
    Poppler::SignatureValidationInfo info;
    EXPECT_EQ(info.hashAlgorithm(), Poppler::SignatureValidationInfo::HashAlgorithmUnknown);
}

TEST_F(SignatureValidationInfoTest_1369, CertificateStatus_1369) {
    Poppler::SignatureValidationInfo info;
    // Check that certificate status has a defined value
    auto status = info.certificateStatus();
    // Just verify it doesn't crash and returns a valid enum value
    EXPECT_GE(static_cast<int>(status), 0);
}

TEST_F(SignatureValidationInfoTest_1369, SignedRangeBounds_1369) {
    Poppler::SignatureValidationInfo info;
    EXPECT_TRUE(info.signedRangeBounds().isEmpty());
}

TEST_F(SignatureValidationInfoTest_1369, Signature_1369) {
    Poppler::SignatureValidationInfo info;
    EXPECT_TRUE(info.signature().isEmpty());
}

// Enum value coverage tests
TEST_F(SignatureInfoTest_1369, AllSignatureStatusEnumValues_1369) {
    EXPECT_EQ(SIGNATURE_VALID, 0);
    EXPECT_EQ(SIGNATURE_INVALID, 1);
    EXPECT_EQ(SIGNATURE_DIGEST_MISMATCH, 2);
    EXPECT_EQ(SIGNATURE_DECODING_ERROR, 3);
    EXPECT_EQ(SIGNATURE_GENERIC_ERROR, 4);
    EXPECT_EQ(SIGNATURE_NOT_FOUND, 5);
    EXPECT_EQ(SIGNATURE_NOT_VERIFIED, 6);
}

// Test that setting various statuses cycles correctly
TEST_F(SignatureInfoTest_1369, StatusCycling_1369) {
    SignatureInfo si;
    
    si.setSignatureValStatus(SIGNATURE_VALID);
    EXPECT_EQ(si.getSignatureValStatus(), SIGNATURE_VALID);
    
    si.setSignatureValStatus(SIGNATURE_NOT_FOUND);
    EXPECT_EQ(si.getSignatureValStatus(), SIGNATURE_NOT_FOUND);
    
    si.setSignatureValStatus(SIGNATURE_GENERIC_ERROR);
    EXPECT_EQ(si.getSignatureValStatus(), SIGNATURE_GENERIC_ERROR);
}

// Test with special characters in signer name
TEST_F(SignatureInfoTest_1369, SpecialCharactersSignerName_1369) {
    SignatureInfo si;
    si.setSignerName("Tëst Sïgnér (Org) <email@test.com>");
    EXPECT_EQ(si.getSignerName(), "Tëst Sïgnér (Org) <email@test.com>");
}

// Test with long signer name
TEST_F(SignatureInfoTest_1369, LongSignerName_1369) {
    SignatureInfo si;
    std::string longName(1000, 'A');
    si.setSignerName(longName);
    EXPECT_EQ(si.getSignerName(), longName);
}

// Test boundary time values
TEST_F(SignatureInfoTest_1369, MaxSigningTime_1369) {
    SignatureInfo si;
    time_t maxTime = std::numeric_limits<time_t>::max();
    si.setSigningTime(maxTime);
    EXPECT_EQ(si.getSigningTime(), maxTime);
}

TEST_F(SignatureInfoTest_1369, NegativeSigningTime_1369) {
    SignatureInfo si;
    si.setSigningTime(-1);
    EXPECT_EQ(si.getSigningTime(), -1);
}

// Test empty location and reason
TEST_F(SignatureInfoTest_1369, EmptyLocation_1369) {
    SignatureInfo si;
    auto loc = std::make_unique<GooString>("");
    si.setLocation(std::move(loc));
    EXPECT_EQ(si.getLocation().toStr(), "");
}

TEST_F(SignatureInfoTest_1369, EmptyReason_1369) {
    SignatureInfo si;
    auto reason = std::make_unique<GooString>("");
    si.setReason(std::move(reason));
    EXPECT_EQ(si.getReason().toStr(), "");
}

} // namespace
