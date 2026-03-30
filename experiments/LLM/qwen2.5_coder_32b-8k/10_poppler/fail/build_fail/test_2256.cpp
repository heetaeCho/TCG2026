#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"

#include "poppler-private.h"



class PopplerPSFileTest : public ::testing::Test {

protected:

    PopplerDocument* document;

    

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));

    }



    void TearDown() override {

        g_object_unref(document);

    }

};



TEST_F(PopplerPSFileTest_2256, NormalOperation_2256) {

    const char* filename = "test.ps";

    int first_page = 0;

    int n_pages = 1;



    PopplerPSFile* ps_file = poppler_ps_file_new(document, filename, first_page, n_pages);

    ASSERT_NE(ps_file, nullptr);



    EXPECT_STREQ(ps_file->filename, filename);

    EXPECT_EQ(ps_file->first_page, first_page + 1);

    EXPECT_EQ(ps_file->last_page, first_page + n_pages);



    g_object_unref(ps_file);

}



TEST_F(PopplerPSFileTest_2256, BoundaryCondition_FirstPageZero_2256) {

    const char* filename = "test.ps";

    int first_page = 0;

    int n_pages = 1;



    PopplerPSFile* ps_file = poppler_ps_file_new(document, filename, first_page, n_pages);

    ASSERT_NE(ps_file, nullptr);



    EXPECT_EQ(ps_file->first_page, 1);

    EXPECT_EQ(ps_file->last_page, 1);



    g_object_unref(ps_file);

}



TEST_F(PopplerPSFileTest_2256, BoundaryCondition_NPagesOne_2256) {

    const char* filename = "test.ps";

    int first_page = 0;

    int n_pages = 1;



    PopplerPSFile* ps_file = poppler_ps_file_new(document, filename, first_page, n_pages);

    ASSERT_NE(ps_file, nullptr);



    EXPECT_EQ(ps_file->last_page, ps_file->first_page);



    g_object_unref(ps_file);

}



TEST_F(PopplerPSFileTest_2256, ExceptionalCase_DocumentNull_2256) {

    const char* filename = "test.ps";

    int first_page = 0;

    int n_pages = 1;



    PopplerDocument* null_document = nullptr;

    PopplerPSFile* ps_file = poppler_ps_file_new(null_document, filename, first_page, n_pages);

    EXPECT_EQ(ps_file, nullptr);

}



TEST_F(PopplerPSFileTest_2256, ExceptionalCase_FilenameNull_2256) {

    const char* null_filename = nullptr;

    int first_page = 0;

    int n_pages = 1;



    PopplerPSFile* ps_file = poppler_ps_file_new(document, null_filename, first_page, n_pages);

    EXPECT_EQ(ps_file, nullptr);

}



TEST_F(PopplerPSFileTest_2256, ExceptionalCase_NPagesZero_2256) {

    const char* filename = "test.ps";

    int first_page = 0;

    int n_pages = 0;



    PopplerPSFile* ps_file = poppler_ps_file_new(document, filename, first_page, n_pages);

    EXPECT_EQ(ps_file, nullptr);

}



TEST_F(PopplerPSFileTest_2256, ExceptionalCase_NPagesNegative_2256) {

    const char* filename = "test.ps";

    int first_page = 0;

    int n_pages = -1;



    PopplerPSFile* ps_file = poppler_ps_file_new(document, filename, first_page, n_pages);

    EXPECT_EQ(ps_file, nullptr);

}
