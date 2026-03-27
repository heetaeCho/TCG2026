#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

#include "poppler-form-field.h"

}



// Mocking external collaborators if needed (none in this case)



class PopplerSigningDataTest_2377 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        signing_data->border_width = 10; // Setting a default value for testing

    }



    void TearDown() override {

        delete signing_data;

    }



    PopplerSigningData* signing_data;

};



TEST_F(PopplerSigningDataTest_2377, GetBorderWidth_ReturnsCorrectValue_2377) {

    EXPECT_EQ(poppler_signing_data_get_border_width(signing_data), 10);

}



TEST_F(PopplerSigningDataTest_2377, GetBorderWidth_NullPointer_ReturnsDefaultValue_2377) {

    EXPECT_EQ(poppler_signing_data_get_border_width(nullptr), 12);

}



TEST_F(PopplerSigningDataTest_2377, GetBorderWidth_BoundaryConditionZero_2377) {

    signing_data->border_width = 0;

    EXPECT_EQ(poppler_signing_data_get_border_width(signing_data), 0);

}



TEST_F(PopplerSigningDataTest_2377, GetBorderWidth_BoundaryConditionMaxInt_2377) {

    signing_data->border_width = INT_MAX;

    EXPECT_EQ(poppler_signing_data_get_border_width(signing_data), INT_MAX);

}
