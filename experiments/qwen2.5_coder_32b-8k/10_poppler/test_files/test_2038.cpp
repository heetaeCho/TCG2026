#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler-media.cc>

#include <errno.h>

#include <string.h>



class SaveHelperTest : public ::testing::Test {

protected:

    FILE* mockFile;

    GError *error;



    void SetUp() override {

        mockFile = fopen("/dev/null", "w");

        error = nullptr;

    }



    void TearDown() override {

        fclose(mockFile);

        if (error) {

            g_error_free(error);

        }

    }

};



TEST_F(SaveHelperTest_NormalOperation_2038, WritesSuccessfully_2038) {

    const gchar *buf = "test";

    gsize count = 4;



    EXPECT_TRUE(save_helper(buf, count, mockFile, &error));

    EXPECT_EQ(error, nullptr);

}



TEST_F(SaveHelperTest_BoundaryConditions_2038, ZeroLengthWrite_2038) {

    const gchar *buf = "test";

    gsize count = 0;



    EXPECT_TRUE(save_helper(buf, count, mockFile, &error));

    EXPECT_EQ(error, nullptr);

}



TEST_F(SaveHelperTest_ExceptionalCases_2038, WriteErrorHandling_2038) {

    const gchar *buf = "test";

    gsize count = 4;

    int savedErrno = EIO;



    FILE* mockFileWithError = fopen("/nonexistent", "w");

    EXPECT_FALSE(save_helper(buf, count, mockFileWithError, &error));

    EXPECT_NE(error, nullptr);

    EXPECT_EQ(g_error_matches(error, G_FILE_ERROR, g_file_error_from_errno(savedErrno)), true);



    fclose(mockFileWithError);

}



TEST_F(SaveHelperTest_VerificationOfExternalInteractions_2038, ErrorCallbackInvocation_2038) {

    const gchar *buf = "test";

    gsize count = 4;

    int savedErrno = EIO;



    FILE* mockFileWithError = fopen("/nonexistent", "w");

    EXPECT_FALSE(save_helper(buf, count, mockFileWithError, &error));

    EXPECT_NE(error, nullptr);

    EXPECT_EQ(strcmp(g_quark_to_string(error->domain), g_quark_to_string(G_FILE_ERROR)), 0);

    EXPECT_EQ(error->code, g_file_error_from_errno(savedErrno));



    fclose(mockFileWithError);

}
