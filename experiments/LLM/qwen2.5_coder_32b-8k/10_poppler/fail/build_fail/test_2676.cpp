#include <gtest/gtest.h>



// Assuming getReadableSigState is in a namespace or can be accessed directly

extern const char *getReadableSigState(SignatureValidationStatus sig_vs);



TEST(GetReadableSigStateTest_2676, ValidSignature_2676) {

    EXPECT_STREQ(getReadableSigState(SIGNATURE_VALID), "Signature is Valid.");

}



TEST(GetReadableSigStateTest_2676, InvalidSignature_2676) {

    EXPECT_STREQ(getReadableSigState(SIGNATURE_INVALID), "Signature is Invalid.");

}



TEST(GetReadableSigStateTest_2676, DigestMismatch_2676) {

    EXPECT_STREQ(getReadableSigState(SIGNATURE_DIGEST_MISMATCH), "Digest Mismatch.");

}



TEST(GetReadableSigStateTest_2676, DecodingError_2676) {

    EXPECT_STREQ(getReadableSigState(SIGNATURE_DECODING_ERROR), "Document isn't signed or corrupted data.");

}



TEST(GetReadableSigStateTest_2676, GenericError_2676) {

    EXPECT_STREQ(getReadableSigState(SIGNATURE_GENERIC_ERROR), "Unknown Validation Failure.");

}



TEST(GetReadableSigStateTest_2676, NotFound_2676) {

    EXPECT_STREQ(getReadableSigState(SIGNATURE_NOT_FOUND), "Signature not found.");

}



TEST(GetReadableSigStateTest_2676, NotVerified_2676) {

    EXPECT_STREQ(getReadableSigState(SIGNATURE_NOT_VERIFIED), "Signature has not yet been verified.");

}



TEST(GetReadableSigStateTest_2676, UnknownStatus_2676) {

    EXPECT_STREQ(getReadableSigState(static_cast<SignatureValidationStatus>(-1)), "Unknown Validation Failure.");

}
