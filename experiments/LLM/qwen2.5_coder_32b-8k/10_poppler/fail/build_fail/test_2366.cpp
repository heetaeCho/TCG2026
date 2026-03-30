#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "poppler-page.h"



class PopplerSigningDataTest_2366 : public ::testing::Test {

protected:

    void SetUp() override {

        signing_data = new PopplerSigningData();

        signature_rect = new PopplerRectangle{0, 0};

    }



    void TearDown() override {

        delete signing_data;

        delete signature_rect;

    }



    PopplerSigningData* signing_data;

    PopplerRectangle* signature_rect;

};



TEST_F(PopplerSigningDataTest_2366, SetSignatureRectangle_NormalOperation_2366) {

    PopplerRectangle rect = {10, 20};

    poppler_signing_data_set_signature_rectangle(signing_data, &rect);

    EXPECT_EQ(signing_data->signature_rect.x2, rect.x2);

    EXPECT_EQ(signing_data->signature_rect.y2, rect.y2);

}



TEST_F(PopplerSigningDataTest_2366, SetSignatureRectangle_ZeroValues_2366) {

    poppler_signing_data_set_signature_rectangle(signing_data, signature_rect);

    EXPECT_EQ(signing_data->signature_rect.x2, 0);

    EXPECT_EQ(signing_data->signature_rect.y2, 0);

}



TEST_F(PopplerSigningDataTest_2366, SetSignatureRectangle_NegativeValues_2366) {

    PopplerRectangle rect = {-10, -20};

    poppler_signing_data_set_signature_rectangle(signing_data, &rect);

    EXPECT_EQ(signing_data->signature_rect.x2, rect.x2);

    EXPECT_EQ(signing_data->signature_rect.y2, rect.y2);

}



TEST_F(PopplerSigningDataTest_2366, SetSignatureRectangle_NullSigningData_2366) {

    PopplerRectangle rect = {10, 20};

    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_set_signature_rectangle(nullptr, &rect));

}



TEST_F(PopplerSigningDataTest_2366, SetSignatureRectangle_NullSignatureRect_2366) {

    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_set_signature_rectangle(signing_data, nullptr));

}
