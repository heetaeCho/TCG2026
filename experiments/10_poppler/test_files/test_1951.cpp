#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GPGMECryptoSignBackend.cc" // Assuming the function is in this file or linked appropriately



namespace {



class GpgMEResultMock : public GpgME::VerificationResult {

public:

    MOCK_CONST_METHOD0(numSignatures, size_t());

    MOCK_CONST_METHOD1(signature, GpgME::Signature(size_t));

};



TEST(GpgMESignatureTest_1951, GetSignature_ValidIndex_1951) {

    GpgMEResultMock mockResult;

    GpgME::Signature expectedSignature;



    EXPECT_CALL(mockResult, numSignatures()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockResult, signature(0)).WillOnce(::testing::Return(expectedSignature));



    auto result = getSignature(mockResult, 0);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, expectedSignature);

}



TEST(GpgMESignatureTest_1951, GetSignature_OutOfBoundsIndex_1951) {

    GpgMEResultMock mockResult;



    EXPECT_CALL(mockResult, numSignatures()).WillOnce(::testing::Return(2));



    auto result = getSignature(mockResult, 3);

    EXPECT_FALSE(result.has_value());

}



TEST(GpgMESignatureTest_1951, GetSignature_BoundaryIndex_1951) {

    GpgMEResultMock mockResult;

    GpgME::Signature expectedSignature;



    EXPECT_CALL(mockResult, numSignatures()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockResult, signature(1)).WillOnce(::testing::Return(expectedSignature));



    auto result = getSignature(mockResult, 1);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, expectedSignature);

}



TEST(GpgMESignatureTest_1951, GetSignature_ZeroSignatures_1951) {

    GpgMEResultMock mockResult;



    EXPECT_CALL(mockResult, numSignatures()).WillOnce(::testing::Return(0));



    auto result = getSignature(mockResult, 0);

    EXPECT_FALSE(result.has_value());

}



} // namespace
