#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include <GpgME/VerificationResult.h> // Assuming this header is available

// The given function to be tested
static std::optional<GpgME::Signature> getSignature(const GpgME::VerificationResult &result, size_t signatureNumber) {
    if (result.numSignatures() > signatureNumber) {
        return result.signature(signatureNumber);
    }
    return std::nullopt;
}

// Mock class for GpgME::VerificationResult
class MockVerificationResult : public GpgME::VerificationResult {
public:
    MOCK_METHOD(size_t, numSignatures, (), (const, override));
    MOCK_METHOD(GpgME::Signature, signature, (size_t), (const, override));
};

// Unit test class
class GpgMEVerificationTest_1951 : public ::testing::Test {
protected:
    MockVerificationResult mockResult;
};

// Test: Verify that the function returns the correct signature when signatureNumber is valid
TEST_F(GpgMEVerificationTest_1951, GetSignatureReturnsValidSignature_1951) {
    size_t signatureNumber = 0;
    GpgME::Signature expectedSignature; // Assuming some valid signature
    EXPECT_CALL(mockResult, numSignatures())
        .WillOnce(testing::Return(1));
    EXPECT_CALL(mockResult, signature(signatureNumber))
        .WillOnce(testing::Return(expectedSignature));

    auto result = getSignature(mockResult, signatureNumber);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expectedSignature);
}

// Test: Verify that the function returns nullopt when signatureNumber is out of range
TEST_F(GpgMEVerificationTest_1951, GetSignatureReturnsNullOptForOutOfRange_1951) {
    size_t signatureNumber = 1;  // Out of range, assuming there is only one signature
    EXPECT_CALL(mockResult, numSignatures())
        .WillOnce(testing::Return(1));

    auto result = getSignature(mockResult, signatureNumber);

    ASSERT_FALSE(result.has_value());
}

// Test: Verify that the function behaves when there are no signatures
TEST_F(GpgMEVerificationTest_1951, GetSignatureReturnsNullOptWhenNoSignatures_1951) {
    size_t signatureNumber = 0;  // No signatures available
    EXPECT_CALL(mockResult, numSignatures())
        .WillOnce(testing::Return(0));

    auto result = getSignature(mockResult, signatureNumber);

    ASSERT_FALSE(result.has_value());
}