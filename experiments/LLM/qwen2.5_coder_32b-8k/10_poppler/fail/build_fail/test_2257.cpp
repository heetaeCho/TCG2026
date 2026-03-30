#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"

#include "poppler-private.h"



class PopplerPSFileTest_2257 : public ::testing::Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));

    }



    void TearDown() override {

        g_object_unref(document);

    }



    PopplerDocument *document;

};



TEST_F(PopplerPSFileTest_2257, CreateWithValidParameters_2257) {

    int fd = 1;

    int first_page = 0;

    int n_pages = 1;



    PopplerPSFile* ps_file = poppler_ps_file_new_fd(document, fd, first_page, n_pages);

    

    EXPECT_NE(ps_file, nullptr);

    EXPECT_EQ(ps_file->document, document);

    EXPECT_EQ(ps_file->fd, fd);

    EXPECT_EQ(ps_file->first_page, first_page + 1);

    EXPECT_EQ(ps_file->last_page, first_page + 1 + n_pages - 1);



    g_object_unref(ps_file);

}



TEST_F(PopplerPSFileTest_2257, CreateWithFirstPageZero_2257) {

    int fd = 1;

    int first_page = 0;

    int n_pages = 1;



    PopplerPSFile* ps_file = poppler_ps_file_new_fd(document, fd, first_page, n_pages);

    

    EXPECT_NE(ps_file, nullptr);

    EXPECT_EQ(ps_file->first_page, 1);

    EXPECT_EQ(ps_file->last_page, 1);



    g_object_unref(ps_file);

}



TEST_F(PopplerPSFileTest_2257, CreateWithNPagesOne_2257) {

    int fd = 1;

    int first_page = 0;

    int n_pages = 1;



    PopplerPSFile* ps_file = poppler_ps_file_new_fd(document, fd, first_page, n_pages);

    

    EXPECT_NE(ps_file, nullptr);

    EXPECT_EQ(ps_file->last_page, 1);



    g_object_unref(ps_file);

}



TEST_F(PopplerPSFileTest_2257, CreateWithNullDocument_2257) {

    int fd = 1;

    int first_page = 0;

    int n_pages = 1;



    PopplerPSFile* ps_file = poppler_ps_file_new_fd(nullptr, fd, first_page, n_pages);

    

    EXPECT_EQ(ps_file, nullptr);

}



TEST_F(PopplerPSFileTest_2257, CreateWithInvalidFD_2257) {

    int fd = -1;

    int first_page = 0;

    int n_pages = 1;



    PopplerPSFile* ps_file = poppler_ps_file_new_fd(document, fd, first_page, n_pages);

    

    EXPECT_EQ(ps_file, nullptr);

}



TEST_F(PopplerPSFileTest_2257, CreateWithZeroPages_2257) {

    int fd = 1;

    int first_page = 0;

    int n_pages = 0;



    PopplerPSFile* ps_file = poppler_ps_file_new_fd(document, fd, first_page, n_pages);

    

    EXPECT_EQ(ps_file, nullptr);

}



TEST_F(PopplerPSFileTest_2257, CreateWithNegativePages_2257) {

    int fd = 1;

    int first_page = 0;

    int n_pages = -1;



    PopplerPSFile* ps_file = poppler_ps_file_new_fd(document, fd, first_page, n_pages);

    

    EXPECT_EQ(ps_file, nullptr);

}
