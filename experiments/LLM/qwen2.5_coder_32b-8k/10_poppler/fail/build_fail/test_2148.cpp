#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <glib.h>

#include "poppler-document.h"

#include "poppler-private.h"



using namespace testing;



class PopplerDocumentTest_2148 : public Test {

protected:

    PopplerDocument *document;

    GError *error = nullptr;



    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_malloc0(sizeof(PopplerDocument)));

        document->parent_instance = 42; // Assuming some value for testing

        document->initer = 1; // Assuming initialized

        document->layers_rbgroups = nullptr;

        document->output_dev = nullptr;

    }



    void TearDown() override {

        g_clear_error(&error);

        g_free(document);

    }

};



TEST_F(PopplerDocumentTest_2148, SaveToFD_SuccessWithChanges_2148) {

    int fd = dup(1); // Duplicate stdout for testing

    ASSERT_NE(fd, -1);



    EXPECT_TRUE(poppler_document_save_to_fd(document, fd, TRUE, &error));

    EXPECT_EQ(error, nullptr);



    close(fd);

}



TEST_F(PopplerDocumentTest_2148, SaveToFD_SuccessWithoutChanges_2148) {

    int fd = dup(1); // Duplicate stdout for testing

    ASSERT_NE(fd, -1);



    EXPECT_TRUE(poppler_document_save_to_fd(document, fd, FALSE, &error));

    EXPECT_EQ(error, nullptr);



    close(fd);

}



TEST_F(PopplerDocumentTest_2148, SaveToFD_InvalidFD_2148) {

    int invalid_fd = -1;



    EXPECT_FALSE(poppler_document_save_to_fd(document, invalid_fd, TRUE, &error));

    EXPECT_NE(error, nullptr);



    g_clear_error(&error);

}



TEST_F(PopplerDocumentTest_2148, SaveToFD_FileOpenError_2148) {

    int fd = 999; // Assuming an invalid file descriptor



    EXPECT_FALSE(poppler_document_save_to_fd(document, fd, TRUE, &error));

    EXPECT_NE(error, nullptr);



    g_clear_error(&error);

}



TEST_F(PopplerDocumentTest_2148, SaveToFD_NullErrorPointer_2148) {

    int fd = dup(1); // Duplicate stdout for testing

    ASSERT_NE(fd, -1);



    EXPECT_TRUE(poppler_document_save_to_fd(document, fd, TRUE, nullptr));



    close(fd);

}
