#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgTest_121 : public ::testing::Test {

protected:

    Prog* prog_;



    void SetUp() override {

        prog_ = new Prog();

    }



    void TearDown() override {

        delete prog_;

    }

};



TEST_F(ProgTest_121, BitStateTextMaxSize_DefaultValue_121) {

    EXPECT_EQ(prog_->bit_state_text_max_size(), 0);

}



TEST_F(ProgTest_121, BitStateTextMaxSize_SetValue_121) {

    prog_->set_dfa_mem(1024); // Assuming set_dfa_mem affects bit_state_text_max_size_

    EXPECT_EQ(prog_->bit_state_text_max_size(), 1024);

}



TEST_F(ProgTest_121, BitStateTextMaxSize_BoundaryCondition_121) {

    prog_->set_dfa_mem(0);

    EXPECT_EQ(prog_->bit_state_text_max_size(), 0);



    prog_->set_dfa_mem(SIZE_MAX);

    EXPECT_EQ(prog_->bit_state_text_max_size(), SIZE_MAX);

}



TEST_F(ProgTest_121, BitStateTextMaxSize_ExceptionalCase_121) {

    // No exceptional case for bit_state_text_max_size as it directly returns a private member

}
