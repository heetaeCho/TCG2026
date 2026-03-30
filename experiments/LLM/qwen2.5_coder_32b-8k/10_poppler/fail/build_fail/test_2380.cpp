#include <gtest/gtest.h>

#include "poppler-form-field.h"



class PopplerSigningDataTest_2380 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = static_cast<PopplerSigningData*>(g_malloc0(sizeof(PopplerSigningData)));

    }



    void TearDown() override {

        poppler_signing_data_set_field_partial_name(signing_data, nullptr);

        g_free(signing_data);

    }



    PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2380, SetFieldPartialName_Successful_2380) {

    const gchar* expected = "test_field";

    poppler_signing_data_set_field_partial_name(signing_data, expected);

    EXPECT_STREQ(expected, signing_data->field_partial_name);

}



TEST_F(PopplerSigningDataTest_2380, SetFieldPartialName_NullPointer_SigningData_2380) {

    const gchar* field_name = "test_field";

    poppler_signing_data_set_field_partial_name(nullptr, field_name);

    EXPECT_EQ(signing_data->field_partial_name, nullptr);

}



TEST_F(PopplerSigningDataTest_2380, SetFieldPartialName_NullPointer_FieldPartialName_2380) {

    const gchar* expected = nullptr;

    poppler_signing_data_set_field_partial_name(signing_data, expected);

    EXPECT_EQ(signing_data->field_partial_name, expected);

}



TEST_F(PopplerSigningDataTest_2380, SetFieldPartialName_UpdateExisting_2380) {

    const gchar* initial = "initial_field";

    poppler_signing_data_set_field_partial_name(signing_data, initial);

    EXPECT_STREQ(initial, signing_data->field_partial_name);



    const gchar* updated = "updated_field";

    poppler_signing_data_set_field_partial_name(signing_data, updated);

    EXPECT_STREQ(updated, signing_data->field_partial_name);

}
