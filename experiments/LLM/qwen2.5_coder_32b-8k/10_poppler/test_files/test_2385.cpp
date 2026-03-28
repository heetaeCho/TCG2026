#include <gtest/gtest.h>

#include "poppler-form-field.h"

#include <gmock/gmock.h>



using namespace testing;



class PopplerSigningDataTest_2385 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        signing_data->location = strdup("Example Location");

    }



    void TearDown() override {

        free(signing_data->location);

        delete signing_data;

    }



    PopplerSigningData *signing_data;

};



TEST_F(PopplerSigningDataTest_2385, GetLocation_ReturnsCorrectLocation_2385) {

    EXPECT_STREQ("Example Location", poppler_signing_data_get_location(signing_data));

}



TEST_F(PopplerSigningDataTest_2385, GetLocation_ReturnsNullForNullInput_2385) {

    EXPECT_EQ(nullptr, poppler_signing_data_get_location(nullptr));

}



TEST_F(PopplerSigningDataTest_2385, GetLocation_HandlesEmptyString_2385) {

    free(signing_data->location);

    signing_data->location = strdup("");

    EXPECT_STREQ("", poppler_signing_data_get_location(signing_data));

}
