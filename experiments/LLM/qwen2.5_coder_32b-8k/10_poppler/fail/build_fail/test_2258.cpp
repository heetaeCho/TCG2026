#include <gtest/gtest.h>

#include "poppler-document.cc"

#include "poppler-private.h"



// Mock class for PSOutputDev to use with Google Mock if needed

class MockPSOutputDev {

public:

    MOCK_METHOD(void, someMethod, (), ());

};



class PopplerPSFileTest_2258 : public ::testing::Test {

protected:

    void SetUp() override {

        ps_file = new PopplerPSFile();

        ps_file->out = nullptr; // Ensure out is initially nullptr

    }



    void TearDown() override {

        delete ps_file;

    }



    PopplerPSFile* ps_file;

};



TEST_F(PopplerPSFileTest_2258, SetPaperSize_NormalOperation_2258) {

    poppler_ps_file_set_paper_size(ps_file, 8.5, 11.0);

    EXPECT_EQ(ps_file->paper_width, 8.5);

    EXPECT_EQ(ps_file->paper_height, 11.0);

}



TEST_F(PopplerPSFileTest_2258, SetPaperSize_ZeroWidth_2258) {

    poppler_ps_file_set_paper_size(ps_file, 0, 11.0);

    EXPECT_EQ(ps_file->paper_width, 0);

    EXPECT_EQ(ps_file->paper_height, 11.0);

}



TEST_F(PopplerPSFileTest_2258, SetPaperSize_ZeroHeight_2258) {

    poppler_ps_file_set_paper_size(ps_file, 8.5, 0);

    EXPECT_EQ(ps_file->paper_width, 8.5);

    EXPECT_EQ(ps_file->paper_height, 0);

}



TEST_F(PopplerPSFileTest_2258, SetPaperSize_NegativeWidth_2258) {

    poppler_ps_file_set_paper_size(ps_file, -1, 11.0);

    EXPECT_EQ(ps_file->paper_width, -1);

    EXPECT_EQ(ps_file->paper_height, 11.0);

}



TEST_F(PopplerPSFileTest_2258, SetPaperSize_NegativeHeight_2258) {

    poppler_ps_file_set_paper_size(ps_file, 8.5, -1);

    EXPECT_EQ(ps_file->paper_width, 8.5);

    EXPECT_EQ(ps_file->paper_height, -1);

}



TEST_F(PopplerPSFileTest_2258, SetPaperSize_OutNotNull_2258) {

    PSOutputDev* mockOut = new MockPSOutputDev();

    ps_file->out = mockOut;

    poppler_ps_file_set_paper_size(ps_file, 8.5, 11.0);

    EXPECT_EQ(ps_file->paper_width, 8.5);

    EXPECT_EQ(ps_file->paper_height, 11.0);

    delete mockOut;

}
