#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "./TestProjects/poppler/glib/poppler-form-field.h"

}



using ::testing::NotNull;

using ::testing::IsNull;



class PopplerSigningDataTest_2388 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = static_cast<PopplerSigningData*>(g_malloc0(sizeof(PopplerSigningData)));

    }



    void TearDown() override {

        poppler_signing_data_set_password(signing_data, nullptr);

        g_free(signing_data);

    }



    PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2388, SetPassword_NullSigningData_2388) {

    const gchar *password = "test";

    poppler_signing_data_set_password(nullptr, password);

    // No observable effect expected

}



TEST_F(PopplerSigningDataTest_2388, SetPassword_NullPassword_2388) {

    poppler_signing_data_set_password(signing_data, nullptr);

    EXPECT_EQ(signing_data->password, static_cast<gchar*>(nullptr));

}



TEST_F(PopplerSigningDataTest_2388, SetPassword_NewPassword_2388) {

    const gchar *password = "test";

    poppler_signing_data_set_password(signing_data, password);

    EXPECT_STREQ(signing_data->password, password);

}



TEST_F(PopplerSigningDataTest_2388, SetPassword_SamePassword_NoChange_2388) {

    const gchar *password = "test";

    poppler_signing_data_set_password(signing_data, password);

    poppler_signing_data_set_password(signing_data, password);

    EXPECT_STREQ(signing_data->password, password);

}



TEST_F(PopplerSigningDataTest_2388, SetPassword_ChangePassword_2388) {

    const gchar *initial_password = "test";

    const gchar *new_password = "new_test";

    poppler_signing_data_set_password(signing_data, initial_password);

    poppler_signing_data_set_password(signing_data, new_password);

    EXPECT_STREQ(signing_data->password, new_password);

}



TEST_F(PopplerSigningDataTest_2388, SetPassword_EmptyString_PasswordSet_2388) {

    const gchar *empty_string = "";

    poppler_signing_data_set_password(signing_data, empty_string);

    EXPECT_STREQ(signing_data->password, empty_string);

}
