#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgTest_123 : public ::testing::Test {

protected:

    Prog* prog;



    void SetUp() override {

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }

};



TEST_F(ProgTest_123, SetDFAMem_NormalOperation_123) {

    int64_t mem_value = 1024;

    prog->set_dfa_mem(mem_value);

    EXPECT_EQ(prog->dfa_mem(), mem_value);

}



TEST_F(ProgTest_123, SetDFAMem_BoundaryCondition_Zero_123) {

    int64_t mem_value = 0;

    prog->set_dfa_mem(mem_value);

    EXPECT_EQ(prog->dfa_mem(), mem_value);

}



TEST_F(ProgTest_123, SetDFAMem_BoundaryCondition_MaxInt_123) {

    int64_t mem_value = INT64_MAX;

    prog->set_dfa_mem(mem_value);

    EXPECT_EQ(prog->dfa_mem(), mem_value);

}
