#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



class PopplerPSFileTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a mock document and PSOutputDev for testing

        mock_document = new PopplerDocument();

        mock_out = new PSOutputDev();



        ps_file = static_cast<PopplerPSFile*>(g_object_new(POPPLER_TYPE_PS_FILE, nullptr));

        ps_file->document = mock_document;

        ps_file->out = mock_out;

        ps_file->filename = g_strdup("test.ps");

        ps_file->first_page = 0;

        ps_file->last_page = 1;

        ps_file->paper_width = 595.276; // A4 width in points

        ps_file->paper_height = 841.890; // A4 height in points

        ps_file->duplex = 0;

    }



    void TearDown() override {

        poppler_ps_file_free(ps_file);

        g_free(mock_document);

        g_free(mock_out);

    }



    PopplerPSFile *ps_file;

    PopplerDocument *mock_document;

    PSOutputDev *mock_out;

};



TEST_F(PopplerPSFileTest_2260, FreeNullPointerDoesNotCrash_2260) {

    poppler_ps_file_free(nullptr); // Should not cause a crash

}



TEST_F(PopplerPSFileTest_2260, FreeValidPointerReducesRefCount_2260) {

    g_object_ref(ps_file); // Increase ref count to 2

    EXPECT_EQ(G_OBJECT(ps_file)->ref_count, 2);



    poppler_ps_file_free(ps_file); // Decrease ref count to 1



    EXPECT_EQ(G_OBJECT(ps_file)->ref_count, 1);

}



TEST_F(PopplerPSFileTest_2260, FreeTwiceDoesNotCrash_2260) {

    poppler_ps_file_free(ps_file); // First free

    poppler_ps_file_free(ps_file); // Second free should not cause a crash



    ps_file = nullptr; // Prevent double-free in TearDown

}
