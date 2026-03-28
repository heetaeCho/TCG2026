#include <gtest/gtest.h>
#include "SignatureInfo.h"

// Declare the function under test (it's static in the original file, so we need to include it or redefine the declaration)
// Since it's a static function in a .cc file, we need to include the source or replicate the declaration for testing.
// We'll include the implementation file directly to access the static function.
#include "pdfsig.cc"

class GetReadableSigStateTest_2676 : public ::testing::Test {
protected:
};

TEST_F(GetReadableSigStateTest_2676, SignatureValid_2676) {
    const char *result = getReadableSigState(SIGNATURE_VALID);
    EXPECT_STREQ(result, "Signature is Valid.");
}

TEST_F(GetReadableSigStateTest_2676, SignatureInvalid_2676) {
    const char *result = getReadableSigState(SIGNATURE_INVALID);
    EXPECT_STREQ(result, "Signature is Invalid.");
}

TEST_F(GetReadableSigStateTest_2676, SignatureDigestMismatch_2676) {
    const char *result = getReadableSigState(SIGNATURE_DIGEST_MISMATCH);
    EXPECT_STREQ(result, "Digest Mismatch.");
}

TEST_F(GetReadableSigStateTest_2676, SignatureDecodingError_2676) {
    const char *result = getReadableSigState(SIGNATURE_DECODING_ERROR);
    EXPECT_STREQ(result, "Document isn't signed or corrupted data.");
}

TEST_F(GetReadableSigStateTest_2676, SignatureNotVerified_2676) {
    const char *result = getReadableSigState(SIGNATURE_NOT_VERIFIED);
    EXPECT_STREQ(result, "Signature has not yet been verified.");
}

TEST_F(GetReadableSigStateTest_2676, SignatureNotFound_2676) {
    const char *result = getReadableSigState(SIGNATURE_NOT_FOUND);
    EXPECT_STREQ(result, "Signature not found.");
}

TEST_F(GetReadableSigStateTest_2676, SignatureGenericError_FallsToDefault_2676) {
    const char *result = getReadableSigState(SIGNATURE_GENERIC_ERROR);
    EXPECT_STREQ(result, "Unknown Validation Failure.");
}

TEST_F(GetReadableSigStateTest_2676, UnknownValueFallsToDefault_2676) {
    const char *result = getReadableSigState(static_cast<SignatureValidationStatus>(999));
    EXPECT_STREQ(result, "Unknown Validation Failure.");
}

TEST_F(GetReadableSigStateTest_2676, NegativeValueFallsToDefault_2676) {
    const char *result = getReadableSigState(static_cast<SignatureValidationStatus>(-1));
    EXPECT_STREQ(result, "Unknown Validation Failure.");
}

TEST_F(GetReadableSigStateTest_2676, ReturnValueIsNotNull_2676) {
    // Verify that no valid enum value returns null
    EXPECT_NE(getReadableSigState(SIGNATURE_VALID), nullptr);
    EXPECT_NE(getReadableSigState(SIGNATURE_INVALID), nullptr);
    EXPECT_NE(getReadableSigState(SIGNATURE_DIGEST_MISMATCH), nullptr);
    EXPECT_NE(getReadableSigState(SIGNATURE_DECODING_ERROR), nullptr);
    EXPECT_NE(getReadableSigState(SIGNATURE_GENERIC_ERROR), nullptr);
    EXPECT_NE(getReadableSigState(SIGNATURE_NOT_FOUND), nullptr);
    EXPECT_NE(getReadableSigState(SIGNATURE_NOT_VERIFIED), nullptr);
}

TEST_F(GetReadableSigStateTest_2676, AllEnumValuesProduceNonEmptyStrings_2676) {
    EXPECT_STRNE(getReadableSigState(SIGNATURE_VALID), "");
    EXPECT_STRNE(getReadableSigState(SIGNATURE_INVALID), "");
    EXPECT_STRNE(getReadableSigState(SIGNATURE_DIGEST_MISMATCH), "");
    EXPECT_STRNE(getReadableSigState(SIGNATURE_DECODING_ERROR), "");
    EXPECT_STRNE(getReadableSigState(SIGNATURE_GENERIC_ERROR), "");
    EXPECT_STRNE(getReadableSigState(SIGNATURE_NOT_FOUND), "");
    EXPECT_STRNE(getReadableSigState(SIGNATURE_NOT_VERIFIED), "");
}

TEST_F(GetReadableSigStateTest_2676, LargeEnumValueFallsToDefault_2676) {
    const char *result = getReadableSigState(static_cast<SignatureValidationStatus>(100));
    EXPECT_STREQ(result, "Unknown Validation Failure.");
}
