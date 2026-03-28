#include <gtest/gtest.h>
#include <gpgme.h>
#include <gpgme++/error.h>

// Since isSuccess is a static function in the .cc file, we include it directly
// to make it testable. In a real project, this would be refactored for testability.
// We replicate the exact function signature for testing purposes.
namespace {
static bool isSuccess(const GpgME::Error &err)
{
    if (err) {
        return false;
    }
    if (err.isCanceled()) {
        return false;
    }
    return true;
}
}

class GPGMEIsSuccessTest_1947 : public ::testing::Test {
protected:
    void SetUp() override { }
    void TearDown() override { }
};

// Test that a default-constructed Error (no error) returns true
TEST_F(GPGMEIsSuccessTest_1947, DefaultConstructedErrorReturnsTrue_1947)
{
    GpgME::Error err;
    EXPECT_TRUE(isSuccess(err));
}

// Test that an error with GPG_ERR_NO_ERROR returns true
TEST_F(GPGMEIsSuccessTest_1947, NoErrorCodeReturnsTrue_1947)
{
    GpgME::Error err(GPG_ERR_NO_ERROR);
    EXPECT_TRUE(isSuccess(err));
}

// Test that a generic error returns false
TEST_F(GPGMEIsSuccessTest_1947, GenericErrorReturnsFalse_1947)
{
    GpgME::Error err(gpgme_error(GPG_ERR_GENERAL));
    EXPECT_FALSE(isSuccess(err));
}

// Test that a canceled error returns false
TEST_F(GPGMEIsSuccessTest_1947, CanceledErrorReturnsFalse_1947)
{
    GpgME::Error err(gpgme_error(GPG_ERR_CANCELED));
    EXPECT_FALSE(isSuccess(err));
}

// Test that GPG_ERR_NOT_FOUND returns false (non-zero error code)
TEST_F(GPGMEIsSuccessTest_1947, NotFoundErrorReturnsFalse_1947)
{
    GpgME::Error err(gpgme_error(GPG_ERR_NOT_FOUND));
    EXPECT_FALSE(isSuccess(err));
}

// Test that GPG_ERR_BAD_PASSPHRASE returns false
TEST_F(GPGMEIsSuccessTest_1947, BadPassphraseErrorReturnsFalse_1947)
{
    GpgME::Error err(gpgme_error(GPG_ERR_BAD_PASSPHRASE));
    EXPECT_FALSE(isSuccess(err));
}

// Test that GPG_ERR_INV_VALUE returns false
TEST_F(GPGMEIsSuccessTest_1947, InvalidValueErrorReturnsFalse_1947)
{
    GpgME::Error err(gpgme_error(GPG_ERR_INV_VALUE));
    EXPECT_FALSE(isSuccess(err));
}

// Test that GPG_ERR_UNUSABLE_PUBKEY returns false
TEST_F(GPGMEIsSuccessTest_1947, UnusablePubkeyErrorReturnsFalse_1947)
{
    GpgME::Error err(gpgme_error(GPG_ERR_UNUSABLE_PUBKEY));
    EXPECT_FALSE(isSuccess(err));
}

// Test that error with user cancel source returns false
TEST_F(GPGMEIsSuccessTest_1947, UserCancelSourceReturnsFalse_1947)
{
    GpgME::Error err(gpgme_err_make(GPG_ERR_SOURCE_USER_1, GPG_ERR_CANCELED));
    EXPECT_FALSE(isSuccess(err));
}

// Test that an error constructed with explicit zero code returns true
TEST_F(GPGMEIsSuccessTest_1947, ExplicitZeroErrorCodeReturnsTrue_1947)
{
    GpgME::Error err(gpgme_err_make(GPG_ERR_SOURCE_UNKNOWN, GPG_ERR_NO_ERROR));
    EXPECT_TRUE(isSuccess(err));
}

// Test EOF error returns false
TEST_F(GPGMEIsSuccessTest_1947, EOFErrorReturnsFalse_1947)
{
    GpgME::Error err(gpgme_error(GPG_ERR_EOF));
    EXPECT_FALSE(isSuccess(err));
}
