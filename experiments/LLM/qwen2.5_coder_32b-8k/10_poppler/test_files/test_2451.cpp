#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"

#include "PSOutputDev.h"



using namespace testing;



// Mock class for PSOutputDev to verify interactions

class MockPSOutputDev : public PSOutputDev {

public:

    MOCK_METHOD(void, displayPage, (Gfx *gfxA, int pageNum, double hDPI, double vDPI, int rotate, bool useMediaBox, bool crop, bool printing), (override));

};



// Fixture for PopplerPage tests

class PopplerPageTest_2451 : public ::testing::Test {

protected:

    void SetUp() override {

        document = new PopplerDocument();

        ps_file = new PopplerPSFile();

        ps_file->document = document;

        page = new PopplerPage();

        page->index = 0; // Assuming index is set to 0 for simplicity

        ps_file->first_page = 1;

        ps_file->last_page = 1;

        ps_file->paper_width = 595.276;

        ps_file->paper_height = 841.89;

        ps_file->duplex = 0;

    }



    void TearDown() override {

        delete page;

        delete document;

        delete ps_file;

    }



    PopplerDocument *document;

    PopplerPSFile *ps_file;

    PopplerPage *page;

};



TEST_F(PopplerPageTest_2451, RenderToPS_NormalOperation_FD_2451) {

    int fd = 1; // Simulate a valid file descriptor

    ps_file->fd = fd;



    MockPSOutputDev *mock_out = new MockPSOutputDev();

    EXPECT_CALL(*mock_out, displayPage(_, Eq(1), Eq(72.0), Eq(72.0), Eq(0), Eq(false), Eq(true), Eq(false))).Times(1);

    ps_file->out = mock_out;



    poppler_page_render_to_ps(page, ps_file);



    delete mock_out;

}



TEST_F(PopplerPageTest_2451, RenderToPS_NormalOperation_Filename_2451) {

    const char *filename = "test.ps";

    ps_file->filename = strdup(filename);

    ps_file->fd = -1; // Simulate no file descriptor



    MockPSOutputDev *mock_out = new MockPSOutputDev();

    EXPECT_CALL(*mock_out, displayPage(_, Eq(1), Eq(72.0), Eq(72.0), Eq(0), Eq(false), Eq(true), Eq(false))).Times(1);

    ps_file->out = mock_out;



    poppler_page_render_to_ps(page, ps_file);



    delete mock_out;

    free(ps_file->filename);

}



TEST_F(PopplerPageTest_2451, RenderToPS_PSFileNull_2451) {

    EXPECT_DEATH(poppler_page_render_to_ps(page, nullptr), ".*");

}



TEST_F(PopplerPageTest_2451, RenderToPS_PageNull_2451) {

    EXPECT_DEATH(poppler_page_render_to_ps(nullptr, ps_file), ".*");

}



TEST_F(PopplerPageTest_2451, RenderToPS_OutAlreadySet_2451) {

    ps_file->out = new PSOutputDev();



    MockPSOutputDev *mock_out = static_cast<MockPSOutputDev*>(ps_file->out);

    EXPECT_CALL(*mock_out, displayPage(_, Eq(1), Eq(72.0), Eq(72.0), Eq(0), Eq(false), Eq(true), Eq(false))).Times(1);



    poppler_page_render_to_ps(page, ps_file);



    delete mock_out;

}
