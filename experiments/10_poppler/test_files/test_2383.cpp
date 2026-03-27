#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"



class PopplerSigningDataTest_2383 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        signing_data->reason = nullptr;

    }



    void TearDown() override {

        if (signing_data) {

            g_free(signing_data->reason);

            delete signing_data;

        }

    }



    PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2383, GetReason_ReturnsNullptrWhenNotSet_2383) {

    EXPECT_EQ(poppler_signing_data_get_reason(signing_data), nullptr);

}



TEST_F(PopplerSigningDataTest_2383, GetReason_ReturnsCorrectValueWhenSet_2383) {

    signing_data->reason = g_strdup("Approval");

    EXPECT_STREQ(poppler_signing_data_get_reason(signing_data), "Approval");

}



TEST_F(PopplerSigningDataTest_2383, GetReason_HandlesNullInputGracefully_2383) {

    EXPECT_EQ(poppler_signing_data_get_reason(nullptr), nullptr);

}
