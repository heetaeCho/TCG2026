#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GpgME/Error.h"  // Include GpgME::Error header (make sure to adjust this based on your actual include path)

namespace {

class GPGMECryptoSignBackendTest_1947 : public ::testing::Test {
protected:
    // Any setup or teardown steps can go here
};

TEST_F(GPGMECryptoSignBackendTest_1947, isSuccess_ReturnsFalse_WhenErrorIsTrue_1947) {
    // Given an error that is not canceled
    GpgME::Error error;
    ON_CALL(error, isCanceled()).WillByDefault(testing::Return(false));
    EXPECT_CALL(error, operator bool()).WillOnce(testing::Return(true));
    
    // When calling isSuccess with this error
    bool result = isSuccess(error);
    
    // Then it should return false
    EXPECT_FALSE(result);
}

TEST_F(GPGMECryptoSignBackendTest_1947, isSuccess_ReturnsFalse_WhenErrorIsCanceled_1947) {
    // Given an error that is canceled
    GpgME::Error error;
    ON_CALL(error, isCanceled()).WillByDefault(testing::Return(true));
    EXPECT_CALL(error, operator bool()).WillOnce(testing::Return(true));

    // When calling isSuccess with this canceled error
    bool result = isSuccess(error);
    
    // Then it should return false
    EXPECT_FALSE(result);
}

TEST_F(GPGMECryptoSignBackendTest_1947, isSuccess_ReturnsTrue_WhenNoError_1947) {
    // Given no error (i.e., the error object is 'false')
    GpgME::Error error;
    EXPECT_CALL(error, operator bool()).WillOnce(testing::Return(false));
    
    // When calling isSuccess with this error
    bool result = isSuccess(error);
    
    // Then it should return true
    EXPECT_TRUE(result);
}

TEST_F(GPGMECryptoSignBackendTest_1947, isSuccess_ReturnsTrue_WhenErrorIsFalseAndNotCanceled_1947) {
    // Given an error that is false and not canceled
    GpgME::Error error;
    ON_CALL(error, isCanceled()).WillByDefault(testing::Return(false));
    EXPECT_CALL(error, operator bool()).WillOnce(testing::Return(false));
    
    // When calling isSuccess with this error
    bool result = isSuccess(error);
    
    // Then it should return true
    EXPECT_TRUE(result);
}

}  // namespace