#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"



// Mocking external collaborators if necessary (none needed in this case)



class PopplerSigningDataTest_2367 : public ::testing::Test {

protected:

    PopplerSigningData *signing_data;



    void SetUp() override {

        signing_data = new PopplerSigningData();

        // Initialize the structure with some values

        signing_data->signature_rect.x1 = 0;

        signing_data->signature_rect.y1 = 0;

        signing_data->signature_rect.x2 = 100;

        signing_data->signature_rect.y2 = 200;

    }



    void TearDown() override {

        delete signing_data;

    }

};



TEST_F(PopplerSigningDataTest_2367, GetSignatureRectangle_ReturnsCorrectPointer_2367) {

    const PopplerRectangle *rect = poppler_signing_data_get_signature_rectangle(signing_data);

    EXPECT_EQ(rect, &signing_data->signature_rect);

}



TEST_F(PopplerSigningDataTest_2367, GetSignatureRectangle_ReturnsNullptrForNullInput_2367) {

    const PopplerRectangle *rect = poppler_signing_data_get_signature_rectangle(nullptr);

    EXPECT_EQ(rect, nullptr);

}
