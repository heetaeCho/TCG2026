#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the necessary headers for PopplerSignatureInfo and GDateTime are included



extern "C" {

    struct _PopplerSignatureInfo;

    typedef struct _PopplerSignatureInfo PopplerSignatureInfo;

    GDateTime* poppler_signature_info_get_local_signing_time(const PopplerSignatureInfo *siginfo);

}



class PopplerSignatureInfoTest_2331 : public ::testing::Test {

protected:

    void SetUp() override {

        siginfo = static_cast<PopplerSignatureInfo*>(g_malloc0(sizeof(PopplerSignatureInfo)));

        // Initialize any necessary fields in siginfo for testing

    }



    void TearDown() override {

        g_free(siginfo);

    }



    PopplerSignatureInfo* siginfo;

};



TEST_F(PopplerSignatureInfoTest_2331, GetLocalSigningTime_ReturnsNull_WhenSigInfoIsNull_2331) {

    GDateTime* result = poppler_signature_info_get_local_signing_time(nullptr);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerSignatureInfoTest_2331, GetLocalSigningTime_ReturnsLocalSigningTime_WhenValidSigInfo_2331) {

    GDateTime* expectedTime = reinterpret_cast<GDateTime*>(0x12345678); // Mock address

    siginfo->local_signing_time = reinterpret_cast<int*>(expectedTime);



    GDateTime* result = poppler_signature_info_get_local_signing_time(siginfo);

    EXPECT_EQ(result, expectedTime);

}
