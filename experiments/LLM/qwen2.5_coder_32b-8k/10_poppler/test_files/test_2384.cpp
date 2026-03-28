#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"



using namespace testing;



class PopplerSigningDataTest_2384 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = g_new0(_PopplerSigningData, 1);

    }



    void TearDown() override {

        poppler_signing_data_set_location(signing_data, nullptr); // Free any allocated memory

        g_free(signing_data);

    }



    _PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2384, SetLocation_NormalOperation_2384) {

    const gchar* location = "New Location";

    poppler_signing_data_set_location(signing_data, location);

    EXPECT_STREQ(location, signing_data->location);

}



TEST_F(PopplerSigningDataTest_2384, SetLocation_BoundaryEmptyString_2384) {

    const gchar* location = "";

    poppler_signing_data_set_location(signing_data, location);

    EXPECT_STREQ(location, signing_data->location);

}



TEST_F(PopplerSigningDataTest_2384, SetLocation_NoChangeSameLocation_2384) {

    const gchar* initial_location = "Initial Location";

    signing_data->location = g_strdup(initial_location);



    poppler_signing_data_set_location(signing_data, initial_location);

    EXPECT_STREQ(initial_location, signing_data->location);

}



TEST_F(PopplerSigningDataTest_2384, SetLocation_ExceptionalNullPointer_2384) {

    const gchar* location = "New Location";

    EXPECT_DEATH(poppler_signing_data_set_location(nullptr, location), "");

}



TEST_F(PopplerSigningDataTest_2384, SetLocation_ExceptionalNullString_2384) {

    poppler_signing_data_set_location(signing_data, nullptr);

    EXPECT_EQ(nullptr, signing_data->location);

}
