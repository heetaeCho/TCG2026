#include <gtest/gtest.h>

#include "poppler-form-field.h"



// Mock class for PopplerSigningData if needed (not required in this case)



TEST(poppler_signing_data_set_page_Test_2360, SetValidPageNumber_2360) {

    PopplerSigningData signing_data;

    int page_number = 5;



    poppler_signing_data_set_page(&signing_data, page_number);



    EXPECT_EQ(signing_data.page, page_number);

}



TEST(poppler_signing_data_set_page_Test_2360, SetZeroPageNumber_2360) {

    PopplerSigningData signing_data;

    int page_number = 0;



    poppler_signing_data_set_page(&signing_data, page_number);



    EXPECT_EQ(signing_data.page, page_number);

}



TEST(poppler_signing_data_set_page_Test_2360, SetNegativePageNumber_2360) {

    PopplerSigningData signing_data;

    int initial_page = signing_data.page; // Assuming default initialized to 0 or any valid value

    int page_number = -1;



    poppler_signing_data_set_page(&signing_data, page_number);



    EXPECT_EQ(signing_data.page, initial_page); // Page should remain unchanged

}



TEST(poppler_signing_data_set_page_Test_2360, SetLargePageNumber_2360) {

    PopplerSigningData signing_data;

    int page_number = 100; // Arbitrary large number



    poppler_signing_data_set_page(&signing_data, page_number);



    EXPECT_EQ(signing_data.page, page_number);

}



TEST(poppler_signing_data_set_page_Test_2360, NullPointer_2360) {

    int page_number = 5;



    // This should not cause a crash; g_return_if_fail will handle it

    poppler_signing_data_set_page(nullptr, page_number);



    // No expectations as function returns early

}
