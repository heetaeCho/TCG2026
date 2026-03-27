#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "./TestProjects/poppler/glib/poppler-form-field.cc"

}



using ::testing::Eq;

using ::testing::IsNull;

using ::testing::NotNull;



class PopplerSigningDataTest_2382 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new _PopplerSigningData();

        memset(signing_data, 0, sizeof(_PopplerSigningData));

    }



    void TearDown() override {

        poppler_signing_data_set_reason(signing_data, nullptr);

        delete signing_data;

    }



    _PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2382, SetReason_NormalOperation_2382) {

    const gchar* reason = "Approval";

    poppler_signing_data_set_reason(signing_data, reason);

    EXPECT_STREQ(signing_data->reason, reason);

}



TEST_F(PopplerSigningDataTest_2382, SetReason_SameReason_NoChange_2382) {

    const gchar* reason = "Approval";

    signing_data->reason = g_strdup(reason);

    poppler_signing_data_set_reason(signing_data, reason);

    EXPECT_STREQ(signing_data->reason, reason);

}



TEST_F(PopplerSigningDataTest_2382, SetReason_NullReason_NoChange_2382) {

    signing_data->reason = g_strdup("Initial Reason");

    poppler_signing_data_set_reason(signing_data, nullptr);

    EXPECT_STREQ(signing_data->reason, "Initial Reason");

}



TEST_F(PopplerSigningDataTest_2382, SetReason_NullData_NoOperation_2382) {

    const gchar* reason = "Approval";

    poppler_signing_data_set_reason(nullptr, reason);

    // No change expected as function should return early

}



TEST_F(PopplerSigningDataTest_2382, SetReason_EmptyString_ValidOperation_2382) {

    const gchar* reason = "";

    poppler_signing_data_set_reason(signing_data, reason);

    EXPECT_STREQ(signing_data->reason, "");

}
