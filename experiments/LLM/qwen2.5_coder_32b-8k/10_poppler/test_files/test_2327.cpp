#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"



// Mocking external collaborators if needed (none in this case)



TEST(PopplerSignatureInfoTest_2327, GetSignatureStatus_ValidPointer_ReturnsStoredStatus_2327) {

    PopplerSignatureInfo siginfo;

    siginfo.sig_status = POPPLER_SIGNATURE_VALID;



    EXPECT_EQ(poppler_signature_info_get_signature_status(&siginfo), POPPLER_SIGNATURE_VALID);

}



TEST(PopplerSignatureInfoTest_2327, GetSignatureStatus_NullPointer_ReturnsGenericError_2327) {

    const PopplerSignatureInfo *nullSiginfo = nullptr;



    EXPECT_EQ(poppler_signature_info_get_signature_status(nullSiginfo), POPPLER_SIGNATURE_GENERIC_ERROR);

}



TEST(PopplerSignatureInfoTest_2327, GetSignatureStatus_DifferentValidStatus_ReturnsCorrectly_2327) {

    PopplerSignatureInfo siginfo;

    siginfo.sig_status = POPPLER_SIGNATURE_INVALID;



    EXPECT_EQ(poppler_signature_info_get_signature_status(&siginfo), POPPLER_SIGNATURE_INVALID);

}
