// pdfsig_getReadableSigState_test_2676.cc
#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SignatureInfo.h"

// pdfsig.cc is a utility program in many Poppler trees and may define `main`.
// To safely include it into this test TU (so we can call the `static` helper),
// rename `main` if it exists.
#define main pdfsig_main_for_test_2676
#include "TestProjects/poppler/utils/pdfsig.cc"
#undef main

namespace {

class GetReadableSigStateTest_2676 : public ::testing::Test {};

TEST_F(GetReadableSigStateTest_2676, ReturnsValidMessageForSignatureValid_2676)
{
    EXPECT_STREQ("Signature is Valid.", getReadableSigState(SIGNATURE_VALID));
}

TEST_F(GetReadableSigStateTest_2676, ReturnsInvalidMessageForSignatureInvalid_2676)
{
    EXPECT_STREQ("Signature is Invalid.", getReadableSigState(SIGNATURE_INVALID));
}

TEST_F(GetReadableSigStateTest_2676, ReturnsDigestMismatchMessage_2676)
{
    EXPECT_STREQ("Digest Mismatch.", getReadableSigState(SIGNATURE_DIGEST_MISMATCH));
}

TEST_F(GetReadableSigStateTest_2676, ReturnsDecodingErrorMessage_2676)
{
    EXPECT_STREQ("Document isn't signed or corrupted data.",
                 getReadableSigState(SIGNATURE_DECODING_ERROR));
}

TEST_F(GetReadableSigStateTest_2676, ReturnsNotVerifiedMessage_2676)
{
    EXPECT_STREQ("Signature has not yet been verified.", getReadableSigState(SIGNATURE_NOT_VERIFIED));
}

TEST_F(GetReadableSigStateTest_2676, ReturnsNotFoundMessage_2676)
{
    EXPECT_STREQ("Signature not found.", getReadableSigState(SIGNATURE_NOT_FOUND));
}

TEST_F(GetReadableSigStateTest_2676, ReturnsUnknownMessageForGenericError_2676)
{
    // Boundary/enum coverage: SIGNATURE_GENERIC_ERROR exists in the enum but is
    // not handled explicitly by the switch in the provided snippet.
    EXPECT_STREQ("Unknown Validation Failure.", getReadableSigState(SIGNATURE_GENERIC_ERROR));
}

TEST_F(GetReadableSigStateTest_2676, ReturnsUnknownMessageForOutOfRangeEnumValue_2676)
{
    // Boundary/error case: value outside the defined enum range should hit default.
    const auto unknown_high = static_cast<SignatureValidationStatus>(9999);
    EXPECT_STREQ("Unknown Validation Failure.", getReadableSigState(unknown_high));

    const auto unknown_low = static_cast<SignatureValidationStatus>(-1);
    EXPECT_STREQ("Unknown Validation Failure.", getReadableSigState(unknown_low));
}

} // namespace