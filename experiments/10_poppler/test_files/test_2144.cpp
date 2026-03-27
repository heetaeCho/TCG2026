#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <fcntl.h>

#include <unistd.h>

#include <errno.h>

#include <cstdio>

#include "poppler-document.cc"

#include "Object.h"



using namespace testing;



class PopplerDocumentTest : public ::testing::Test {

protected:

    void SetUp() override {

        error = nullptr;

    }



    void TearDown() override {

        if (error) {

            g_error_free(error);

        }

    }



    GError *error;

};



TEST_F(PopplerDocumentTest_2144, NormalOperation_2144) {

    int fd = open("test.pdf", O_RDONLY);

    ASSERT_NE(fd, -1);



    PopplerDocument* doc = poppler_document_new_from_fd(fd, nullptr, &error);

    EXPECT_NE(doc, nullptr);

    EXPECT_EQ(error, nullptr);



    close(fd);

}



TEST_F(PopplerDocumentTest_2144, InvalidFD_2144) {

    int invalid_fd = -1;

    PopplerDocument* doc = poppler_document_new_from_fd(invalid_fd, nullptr, &error);

    EXPECT_EQ(doc, nullptr);

    ASSERT_NE(error, nullptr);



    EXPECT_STREQ(g_quark_to_string(error->domain), g_quark_to_string(G_FILE_ERROR));

    EXPECT_EQ(error->code, G_FILE_ERROR_FAILED);

}



TEST_F(PopplerDocumentTest_2144, NonReadableFD_2144) {

    int pipefd[2];

    ASSERT_EQ(pipe(pipefd), 0);



    close(pipefd[0]); // Close read end

    PopplerDocument* doc = poppler_document_new_from_fd(pipefd[1], nullptr, &error);

    EXPECT_EQ(doc, nullptr);

    ASSERT_NE(error, nullptr);



    EXPECT_STREQ(g_quark_to_string(error->domain), g_quark_to_string(G_FILE_ERROR));

    EXPECT_EQ(error->code, G_FILE_ERROR_BADF);



    close(pipefd[1]);

}



TEST_F(PopplerDocumentTest_2144, InvalidFileDescriptorType_2144) {

    int fd = open("test.pdf", O_WRONLY);

    ASSERT_NE(fd, -1);



    PopplerDocument* doc = poppler_document_new_from_fd(fd, nullptr, &error);

    EXPECT_EQ(doc, nullptr);

    ASSERT_NE(error, nullptr);



    EXPECT_STREQ(g_quark_to_string(error->domain), g_quark_to_string(G_FILE_ERROR));

    EXPECT_EQ(error->code, G_FILE_ERROR_BADF);



    close(fd);

}



TEST_F(PopplerDocumentTest_2144, EncryptedPDFWithPassword_2144) {

    int fd = open("encrypted_test.pdf", O_RDONLY);

    ASSERT_NE(fd, -1);



    PopplerDocument* doc = poppler_document_new_from_fd(fd, "correct_password", &error);

    EXPECT_NE(doc, nullptr);

    EXPECT_EQ(error, nullptr);



    close(fd);

}



TEST_F(PopplerDocumentTest_2144, EncryptedPDFWithIncorrectPassword_2144) {

    int fd = open("encrypted_test.pdf", O_RDONLY);

    ASSERT_NE(fd, -1);



    PopplerDocument* doc = poppler_document_new_from_fd(fd, "incorrect_password", &error);

    EXPECT_EQ(doc, nullptr);

    ASSERT_NE(error, nullptr);



    close(fd);

}



TEST_F(PopplerDocumentTest_2144, EncryptedPDFWithoutPassword_2144) {

    int fd = open("encrypted_test.pdf", O_RDONLY);

    ASSERT_NE(fd, -1);



    PopplerDocument* doc = poppler_document_new_from_fd(fd, nullptr, &error);

    EXPECT_EQ(doc, nullptr);

    ASSERT_NE(error, nullptr);



    close(fd);

}



TEST_F(PopplerDocumentTest_2144, InvalidFile_2144) {

    int fd = open("nonexistent.pdf", O_RDONLY);

    EXPECT_EQ(fd, -1);



    PopplerDocument* doc = poppler_document_new_from_fd(fd, nullptr, &error);

    EXPECT_EQ(doc, nullptr);

    ASSERT_NE(error, nullptr);



    EXPECT_STREQ(g_quark_to_string(error->domain), g_quark_to_string(G_FILE_ERROR));

}



TEST_F(PopplerDocumentTest_2144, ReadFromStdin_2144) {

    int fd = fileno(stdin);

    PopplerDocument* doc = poppler_document_new_from_fd(fd, nullptr, &error);



    // Assuming stdin is not readable, which would be a failure case.

    EXPECT_EQ(doc, nullptr);

    ASSERT_NE(error, nullptr);

}



TEST_F(PopplerDocumentTest_2144, ReadFromNonRegularFile_2144) {

    int pipefd[2];

    ASSERT_EQ(pipe(pipefd), 0);



    PopplerDocument* doc = poppler_document_new_from_fd(pipefd[0], nullptr, &error);

    EXPECT_NE(doc, nullptr); // Assuming the pipe is readable and contains a valid PDF

    EXPECT_EQ(error, nullptr);



    close(pipefd[0]);

    close(pipefd[1]);

}
