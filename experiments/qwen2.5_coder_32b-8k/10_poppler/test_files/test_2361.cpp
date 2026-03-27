#include <gtest/gtest.h>

#include "poppler-form-field.cc"



TEST(poppler_signing_data_get_page_2361, NormalOperation_2361) {

    PopplerSigningData data;

    data.page = 5;

    EXPECT_EQ(poppler_signing_data_get_page(&data), 5);

}



TEST(poppler_signing_data_get_page_2361, NullPointer_2361) {

    EXPECT_EQ(poppler_signing_data_get_page(nullptr), 0);

}



TEST(poppler_signing_data_get_page_2361, BoundaryConditionMin_2361) {

    PopplerSigningData data;

    data.page = INT_MIN;

    EXPECT_EQ(poppler_signing_data_get_page(&data), INT_MIN);

}



TEST(poppler_signing_data_get_page_2361, BoundaryConditionMax_2361) {

    PopplerSigningData data;

    data.page = INT_MAX;

    EXPECT_EQ(poppler_signing_data_get_page(&data), INT_MAX);

}
