#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"



// Assuming PopplerSignatureInfo is a typedef to _PopplerSignatureInfo for simplicity

typedef struct _PopplerSignatureInfo PopplerSignatureInfo;



class SignatureInfoTest : public ::testing::Test {

protected:

    void SetUp() override {

        siginfo = new PopplerSignatureInfo();

        siginfo->signer_name = strdup("John Doe");

    }



    void TearDown() override {

        free(siginfo->signer_name);

        delete siginfo;

    }



    PopplerSignatureInfo* siginfo;

};



TEST_F(SignatureInfoTest_2330, GetSignerName_ReturnsCorrectName_2330) {

    EXPECT_STREQ("John Doe", poppler_signature_info_get_signer_name(siginfo));

}



TEST_F(SignatureInfoTest_2330, GetSignerName_NullSiginfo_ReturnsNull_2330) {

    EXPECT_EQ(nullptr, poppler_signature_info_get_signer_name(nullptr));

}
