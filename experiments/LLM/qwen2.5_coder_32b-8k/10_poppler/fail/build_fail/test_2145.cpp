#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <glib-object.h>



// Mocking GError for testing purposes

class MockGError {

public:

    MOCK_METHOD3(set_error, void(GQuark domain, gint code, const gchar* message));

};



extern "C" gboolean handle_save_error(int err_code, GError** error);



TEST(handle_save_error_Test_2145, NormalOperation_NoError_2145) {

    GError* error = nullptr;

    EXPECT_TRUE(handle_save_error(errNone, &error));

    EXPECT_EQ(error, nullptr);

}



TEST(handle_save_error_Test_2145, OpenFileError_2145) {

    MockGError mockGError;

    GError* error = nullptr;



    EXPECT_CALL(mockGError, set_error(POPPLER_ERROR, POPPLER_ERROR_OPEN_FILE, "Failed to open file for writing"))

        .WillOnce(testing::SetArgReferee<0>(error));



    EXPECT_FALSE(handle_save_error(errOpenFile, &error));

    EXPECT_NE(error, nullptr);

    g_clear_error(&error);

}



TEST(handle_save_error_Test_2145, EncryptedError_2145) {

    MockGError mockGError;

    GError* error = nullptr;



    EXPECT_CALL(mockGError, set_error(POPPLER_ERROR, POPPLER_ERROR_ENCRYPTED, "Document is encrypted"))

        .WillOnce(testing::SetArgReferee<0>(error));



    EXPECT_FALSE(handle_save_error(errEncrypted, &error));

    EXPECT_NE(error, nullptr);

    g_clear_error(&error);

}



TEST(handle_save_error_Test_2145, DefaultError_2145) {

    MockGError mockGError;

    GError* error = nullptr;



    EXPECT_CALL(mockGError, set_error(POPPLER_ERROR, POPPLER_ERROR_INVALID, "Failed to save document"))

        .WillOnce(testing::SetArgReferee<0>(error));



    EXPECT_FALSE(handle_save_error(-1, &error)); // Using -1 as an arbitrary default error code

    EXPECT_NE(error, nullptr);

    g_clear_error(&error);

}

```


