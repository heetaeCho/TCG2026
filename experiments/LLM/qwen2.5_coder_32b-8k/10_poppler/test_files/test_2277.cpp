#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-attachment.h"

#include <glib.h>



class PopplerAttachmentTest_2277 : public ::testing::Test {

protected:

    GError *error = nullptr;

    PopplerAttachment *attachment;



    void SetUp() override {

        attachment = g_new0(PopplerAttachment, 1);

    }



    void TearDown() override {

        if (error) {

            g_error_free(error);

        }

        g_free(attachment);

    }



    // Mock function to simulate file operations

    static FILE* openFileMock(const char *filename, const char *mode) {

        return fopen(filename, mode);

    }

};



TEST_F(PopplerAttachmentTest_2277, SaveSuccessful_2277) {

    const char *filename = "test_save_successful.txt";

    FILE *f = fopen(filename, "wb");

    fclose(f);



    gboolean result = poppler_attachment_save(attachment, filename, &error);

    EXPECT_TRUE(result);

    EXPECT_EQ(error, nullptr);



    remove(filename);  // Clean up

}



TEST_F(PopplerAttachmentTest_2277, SaveFailsWithInvalidFilename_2277) {

    const char *invalid_filename = "/nonexistent/path/test_save_fails.txt";



    gboolean result = poppler_attachment_save(attachment, invalid_filename, &error);

    EXPECT_FALSE(result);

    EXPECT_NE(error, nullptr);



    g_error_free(error);

    error = nullptr;

}



TEST_F(PopplerAttachmentTest_2277, SaveFailsWithNullFilename_2277) {

    const char *null_filename = nullptr;



    gboolean result = poppler_attachment_save(attachment, null_filename, &error);

    EXPECT_FALSE(result);

    EXPECT_NE(error, nullptr);



    g_error_free(error);

    error = nullptr;

}



TEST_F(PopplerAttachmentTest_2277, SaveFailsWithNullAttachment_2277) {

    const char *filename = "test_save_fails.txt";

    FILE *f = fopen(filename, "wb");

    fclose(f);



    gboolean result = poppler_attachment_save(nullptr, filename, &error);

    EXPECT_FALSE(result);

    EXPECT_EQ(error, nullptr);



    remove(filename);  // Clean up

}



TEST_F(PopplerAttachmentTest_2277, SaveFailsWithFileCloseError_2277) {

    const char *filename = "test_save_close_error.txt";

    FILE *f = fopen(filename, "wb");

    fclose(f);



    // Simulate a file close error by deleting the file while it's open

    unlink(filename);

    f = fopen(filename, "ab");  // Reopen to get a valid FILE*

    fclose(f);  // Now close should fail



    gboolean result = poppler_attachment_save(attachment, filename, &error);

    EXPECT_FALSE(result);

    EXPECT_NE(error, nullptr);



    g_error_free(error);

    error = nullptr;



    remove(filename);  // Clean up

}
