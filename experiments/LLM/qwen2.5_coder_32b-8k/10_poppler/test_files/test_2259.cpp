#include <gtest/gtest.h>

#include "poppler-document.cc"

#include "poppler-private.h"



class PopplerPSFileTest_2259 : public ::testing::Test {

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



TEST_F(PopplerPSFileTest_2259, SetDuplexTrueWhenOutIsNull_2259) {

    poppler_ps_file_set_duplex(ps_file, TRUE);

    EXPECT_EQ(ps_file->duplex, 1); // TRUE is typically represented as 1 in C

}



TEST_F(PopplerPSFileTest_2259, SetDuplexFalseWhenOutIsNull_2259) {

    poppler_ps_file_set_duplex(ps_file, FALSE);

    EXPECT_EQ(ps_file->duplex, 0); // FALSE is typically represented as 0 in C

}



TEST_F(PopplerPSFileTest_2259, SetDuplexTrueWhenOutIsNotNull_2259) {

    ps_file->out = new PSOutputDev(); // Simulate out being not nullptr

    poppler_ps_file_set_duplex(ps_file, TRUE);

    EXPECT_EQ(ps_file->duplex, 0); // duplex should remain unchanged due to the g_return_if_fail condition

    delete ps_file->out;

}



TEST_F(PopplerPSFileTest_2259, SetDuplexFalseWhenOutIsNotNull_2259) {

    ps_file->out = new PSOutputDev(); // Simulate out being not nullptr

    poppler_ps_file_set_duplex(ps_file, FALSE);

    EXPECT_EQ(ps_file->duplex, 0); // duplex should remain unchanged due to the g_return_if_fail condition

    delete ps_file->out;

}
