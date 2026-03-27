#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-form.h"
#include "SignatureInfo.h"
#include "FormWidgetSignature.h"
#include "GooString.h"

namespace Poppler {

class MockSignatureInfo : public SignatureInfo {
public:
    MOCK_METHOD(const SignatureValidationStatus, getSignatureValStatus, (), (const, override));
    MOCK_METHOD(const std::string, getSignerName, (), (const, override));
    MOCK_METHOD(const std::string, getSubjectDN, (), (const, override));
    MOCK_METHOD(const GooString&, getLocation, (), (const, override));
    MOCK_METHOD(const GooString&, getReason, (), (const, override));
    MOCK_METHOD(const HashAlgorithm, getHashAlgorithm, (), (const, override));
    MOCK_METHOD(time_t, getSigningTime, (), (const, override));
    MOCK_METHOD(const X509CertificateInfo*, getCertificateInfo, (), (const, override));
};

class MockFormWidgetSignature : public FormWidgetSignature {
public:
    MOCK_METHOD(std::vector<Goffset>, getSignedRangeBounds, (), (const, override));
    MOCK_METHOD(std::pair<std::optional<std::vector<unsigned char>>, int64_t>, getCheckedSignature, (), (const, override));
};

TEST(SignatureValidationInfoTest_1369, fromInternal_ReturnsValidSignature_WhenValidSignatureStatus) {
    // Arrange
    MockSignatureInfo mockSignatureInfo;
    MockFormWidgetSignature mockFormWidgetSignature;
    
    SignatureInfo signatureInfo;
    FormWidgetSignature formWidgetSignature(nullptr, nullptr, 0, Ref(), nullptr);

    // Setting up expectations for the mock object
    EXPECT_CALL(mockSignatureInfo, getSignatureValStatus()).WillOnce(testing::Return(SIGNATURE_VALID));
    EXPECT_CALL(mockSignatureInfo, getSignerName()).WillOnce(testing::Return("John Doe"));
    EXPECT_CALL(mockSignatureInfo, getSubjectDN()).WillOnce(testing::Return("CN=John Doe"));
    EXPECT_CALL(mockSignatureInfo, getLocation()).WillOnce(testing::Return(GooString("New York")));
    EXPECT_CALL(mockSignatureInfo, getReason()).WillOnce(testing::Return(GooString("Test Reason")));
    EXPECT_CALL(mockSignatureInfo, getHashAlgorithm()).WillOnce(testing::Return(HashAlgorithm::SHA256));
    EXPECT_CALL(mockSignatureInfo, getSigningTime()).WillOnce(testing::Return(1632567890));

    std::vector<Goffset> rangeBounds = {100, 200, 300, 400};
    EXPECT_CALL(mockFormWidgetSignature, getSignedRangeBounds()).WillOnce(testing::Return(rangeBounds));

    std::optional<std::vector<unsigned char>> checkedSignature = std::vector<unsigned char>{0x12, 0x34, 0x56, 0x78};
    EXPECT_CALL(mockFormWidgetSignature, getCheckedSignature()).WillOnce(testing::Return(std::make_pair(checkedSignature, 1234)));

    // Act
    SignatureValidationInfo result = fromInternal(&mockSignatureInfo, &mockFormWidgetSignature);

    // Assert
    EXPECT_EQ(result.signature_status, SignatureValidationInfo::SignatureValid);
    EXPECT_EQ(result.signer_name.toStdString(), "John Doe");
    EXPECT_EQ(result.signer_subject_dn.toStdString(), "CN=John Doe");
    EXPECT_EQ(result.location.toStr(), "New York");
    EXPECT_EQ(result.reason.toStr(), "Test Reason");
    EXPECT_EQ(result.hash_algorithm, HashAlgorithm::SHA256);
    EXPECT_EQ(result.signing_time, 1632567890);
    EXPECT_EQ(result.range_bounds.size(), 4);
    EXPECT_EQ(result.range_bounds[0], 100);
    EXPECT_EQ(result.signature.size(), 4);
}

TEST(SignatureValidationInfoTest_1370, fromInternal_SetsSignatureStatus_WhenInvalidSignatureStatus) {
    // Arrange
    MockSignatureInfo mockSignatureInfo;
    MockFormWidgetSignature mockFormWidgetSignature;
    
    // Setting up expectations for the mock object
    EXPECT_CALL(mockSignatureInfo, getSignatureValStatus()).WillOnce(testing::Return(SIGNATURE_INVALID));

    // Act
    SignatureValidationInfo result = fromInternal(&mockSignatureInfo, &mockFormWidgetSignature);

    // Assert
    EXPECT_EQ(result.signature_status, SignatureValidationInfo::SignatureInvalid);
}

TEST(SignatureValidationInfoTest_1371, fromInternal_SetsSignatureStatus_WhenDigestMismatch) {
    // Arrange
    MockSignatureInfo mockSignatureInfo;
    MockFormWidgetSignature mockFormWidgetSignature;

    // Setting up expectations for the mock object
    EXPECT_CALL(mockSignatureInfo, getSignatureValStatus()).WillOnce(testing::Return(SIGNATURE_DIGEST_MISMATCH));

    // Act
    SignatureValidationInfo result = fromInternal(&mockSignatureInfo, &mockFormWidgetSignature);

    // Assert
    EXPECT_EQ(result.signature_status, SignatureValidationInfo::SignatureDigestMismatch);
}

TEST(SignatureValidationInfoTest_1372, fromInternal_SetsCertificateStatusInProgress) {
    // Arrange
    MockSignatureInfo mockSignatureInfo;
    MockFormWidgetSignature mockFormWidgetSignature;

    // Act
    SignatureValidationInfo result = fromInternal(&mockSignatureInfo, &mockFormWidgetSignature);

    // Assert
    EXPECT_EQ(result.certificate_status, SignatureValidationInfo::CertificateVerificationInProgress);
}

TEST(SignatureValidationInfoTest_1373, fromInternal_HandlesEmptySignedRangeBounds) {
    // Arrange
    MockSignatureInfo mockSignatureInfo;
    MockFormWidgetSignature mockFormWidgetSignature;
    
    std::vector<Goffset> rangeBounds = {};
    EXPECT_CALL(mockFormWidgetSignature, getSignedRangeBounds()).WillOnce(testing::Return(rangeBounds));

    // Act
    SignatureValidationInfo result = fromInternal(&mockSignatureInfo, &mockFormWidgetSignature);

    // Assert
    EXPECT_EQ(result.range_bounds.size(), 0);
}

}  // namespace Poppler