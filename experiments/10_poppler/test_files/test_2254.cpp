#include <gtest/gtest.h>

#include "poppler-document.cc"

#include "poppler-private.h"



class PopplerPSFileTest : public ::testing::Test {

protected:

    PopplerPSFile ps_file;



    void SetUp() override {

        poppler_ps_file_init(&ps_file);

    }

};



TEST_F(PopplerPSFileTest_2254, OutIsNullptrAfterInit_2254) {

    EXPECT_EQ(ps_file.out, nullptr);

}



TEST_F(PopplerPSFileTest_2254, FDIsNegativeOneAfterInit_2254) {

    EXPECT_EQ(ps_file.fd, -1);

}



TEST_F(PopplerPSFileTest_2254, FilenameIsNullptrAfterInit_2254) {

    EXPECT_EQ(ps_file.filename, nullptr);

}



TEST_F(PopplerPSFileTest_2254, PaperWidthIsNegativeOneAfterInit_2254) {

    EXPECT_EQ(ps_file.paper_width, -1);

}



TEST_F(PopplerPSFileTest_2254, PaperHeightIsNegativeOneAfterInit_2254) {

    EXPECT_EQ(ps_file.paper_height, -1);

}



TEST_F(PopplerPSFileTest_2254, DuplexIsFalseAfterInit_2254) {

    EXPECT_FALSE(ps_file.duplex);

}
