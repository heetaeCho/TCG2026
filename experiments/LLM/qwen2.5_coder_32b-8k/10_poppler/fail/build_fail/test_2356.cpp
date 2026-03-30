#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler-form-field.h>

#include <cstring>



// Mocking external dependencies if necessary (none in this case)



TEST_F(PopplerSigningDataTest_2356, SetDestinationFilename_Success_2356) {

    PopplerSigningData signing_data;

    memset(&signing_data, 0, sizeof(signing_data));



    const gchar* filename = "test.pdf";

    poppler_signing_data_set_destination_filename(&signing_data, filename);



    ASSERT_STREQ(signing_data.destination_filename, filename);

    g_free(signing_data.destination_filename); // Clean up

}



TEST_F(PopplerSigningDataTest_2356, SetDestinationFilename_NullPointer_SigningData_2356) {

    const gchar* filename = "test.pdf";

    poppler_signing_data_set_destination_filename(nullptr, filename);



    // No change expected as function returns early

}



TEST_F(PopplerSigningDataTest_2356, SetDestinationFilename_NullPointer_Filename_2356) {

    PopplerSigningData signing_data;

    memset(&signing_data, 0, sizeof(signing_data));



    poppler_signing_data_set_destination_filename(&signing_data, nullptr);



    // No change expected as function returns early

}



TEST_F(PopplerSigningDataTest_2356, SetDestinationFilename_SameFilename_NoChange_2356) {

    PopplerSigningData signing_data;

    memset(&signing_data, 0, sizeof(signing_data));



    const gchar* filename = "test.pdf";

    poppler_signing_data_set_destination_filename(&signing_data, filename);

    poppler_signing_data_set_destination_filename(&signing_data, filename);



    ASSERT_STREQ(signing_data.destination_filename, filename);

    g_free(signing_data.destination_filename); // Clean up

}



TEST_F(PopplerSigningDataTest_2356, SetDestinationFilename_DifferentFilename_UpdateSuccess_2356) {

    PopplerSigningData signing_data;

    memset(&signing_data, 0, sizeof(signing_data));



    const gchar* filename1 = "test.pdf";

    const gchar* filename2 = "another_test.pdf";



    poppler_signing_data_set_destination_filename(&signing_data, filename1);

    poppler_signing_data_set_destination_filename(&signing_data, filename2);



    ASSERT_STREQ(signing_data.destination_filename, filename2);

    g_free(signing_data.destination_filename); // Clean up

}
