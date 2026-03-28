#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"



using namespace re2;



class ProgTest_112 : public ::testing::Test {

protected:

    Prog* prog;



    void SetUp() override {

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }

};



TEST_F(ProgTest_112, DefaultStartValue_112) {

    EXPECT_EQ(prog->start(), 0);

}



TEST_F(ProgTest_112, SetAndGetStartValue_112) {

    int new_start = 42;

    prog->set_start(new_start);

    EXPECT_EQ(prog->start(), new_start);

}



TEST_F(ProgTest_112, DefaultReversedValue_112) {

    EXPECT_FALSE(prog->reversed());

}



TEST_F(ProgTest_112, SetAndGetReversedValue_112) {

    prog->set_reversed(true);

    EXPECT_TRUE(prog->reversed());



    prog->set_reversed(false);

    EXPECT_FALSE(prog->reversed());

}



TEST_F(ProgTest_112, DefaultAnchorStartValue_112) {

    EXPECT_FALSE(prog->anchor_start());

}



TEST_F(ProgTest_112, SetAndGetAnchorStartValue_112) {

    prog->set_anchor_start(true);

    EXPECT_TRUE(prog->anchor_start());



    prog->set_anchor_start(false);

    EXPECT_FALSE(prog->anchor_start());

}



TEST_F(ProgTest_112, DefaultAnchorEndValue_112) {

    EXPECT_FALSE(prog->anchor_end());

}



TEST_F(ProgTest_112, SetAndGetAnchorEndValue_112) {

    prog->set_anchor_end(true);

    EXPECT_TRUE(prog->anchor_end());



    prog->set_anchor_end(false);

    EXPECT_FALSE(prog->anchor_end());

}



TEST_F(ProgTest_112, DefaultDFAMemValue_112) {

    EXPECT_EQ(prog->dfa_mem(), 0);

}



TEST_F(ProgTest_112, SetAndGetDFAMemValue_112) {

    int64_t new_dfa_mem = 1024;

    prog->set_dfa_mem(new_dfa_mem);

    EXPECT_EQ(prog->dfa_mem(), new_dfa_mem);

}
