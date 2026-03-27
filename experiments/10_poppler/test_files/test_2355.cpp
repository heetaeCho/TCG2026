#include <gtest/gtest.h>

#include "poppler-form-field.cc"



TEST(poppler_signing_data_free_Test_2355, NullPointerTest_2355) {

    PopplerSigningData* signing_data = nullptr;

    poppler_signing_data_free(signing_data);

    // Expect no crash and no operation since the pointer is null.

}



TEST(poppler_signing_data_free_Test_2355, BasicFreeTest_2355) {

    PopplerSigningData* signing_data = (PopplerSigningData*)g_malloc0(sizeof(PopplerSigningData));

    poppler_signing_data_free(signing_data);

    // Expect the memory to be freed without issues.

}



TEST(poppler_signing_data_free_Test_2355, FullFieldsTest_2355) {

    PopplerSigningData* signing_data = (PopplerSigningData*)g_malloc0(sizeof(PopplerSigningData));

    signing_data->destination_filename = g_strdup("test_destination");

    signing_data->signature_text = g_strdup("test_signature");

    signing_data->signature_text_left = g_strdup("test_signature_left");

    signing_data->field_partial_name = g_strdup("test_field_partial_name");

    signing_data->reason = g_strdup("test_reason");

    signing_data->location = g_strdup("test_location");

    signing_data->image_path = g_strdup("test_image_path");

    signing_data->password = g_strdup("test_password");

    signing_data->document_owner_password = g_strdup("test_document_owner_password");

    signing_data->document_user_password = g_strdup("test_document_user_password");



    poppler_signing_data_free(signing_data);

    // Expect all strings to be freed and memory of the struct to be released.

}



TEST(poppler_signing_data_free_Test_2355, PartialFieldsTest_2355) {

    PopplerSigningData* signing_data = (PopplerSigningData*)g_malloc0(sizeof(PopplerSigningData));

    signing_data->destination_filename = g_strdup("test_destination");

    signing_data->field_partial_name = g_strdup("test_field_partial_name");

    signing_data->document_user_password = g_strdup("test_document_user_password");



    poppler_signing_data_free(signing_data);

    // Expect only the allocated strings to be freed and memory of the struct to be released.

}



TEST(poppler_signing_data_free_Test_2355, PasswordFieldsTest_2355) {

    PopplerSigningData* signing_data = (PopplerSigningData*)g_malloc0(sizeof(PopplerSigningData));

    signing_data->password = g_strdup("test_password");

    signing_data->document_owner_password = g_strdup("test_document_owner_password");

    signing_data->document_user_password = g_strdup("test_document_user_password");



    poppler_signing_data_free(signing_data);

    // Expect passwords to be zeroed out and memory of the struct to be released.

}
