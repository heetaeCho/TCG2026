#include <gtest/gtest.h>

#include "re2/prog.h"



namespace re2 {



class ProgTest : public ::testing::Test {

protected:

    Prog* prog;



    void SetUp() override {

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }

};



TEST_F(ProgTest_110, GreedyAltMatchByteRange_110) {

    Inst inst;

    inst.InitAlt(1, 2);

    prog->inst(1)->InitByteRange(97, 122, 0, 3);



    EXPECT_TRUE(inst.greedy(prog));

}



TEST_F(ProgTest_110, GreedyAltMatchNopByteRange_110) {

    Inst inst;

    inst.InitAlt(1, 2);

    prog->inst(1)->InitNop(4);

    prog->inst(4)->InitByteRange(97, 122, 0, 3);



    EXPECT_TRUE(inst.greedy(prog));

}



TEST_F(ProgTest_110, NonGreedyAltMatchNopNotByteRange_110) {

    Inst inst;

    inst.InitAlt(1, 2);

    prog->inst(1)->InitNop(4);

    prog->inst(4)->InitNop(5);



    EXPECT_FALSE(inst.greedy(prog));

}



TEST_F(ProgTest_110, NonGreedyNotAltMatch_110) {

    Inst inst;

    inst.InitByteRange(97, 122, 0, 3);



    EXPECT_FALSE(inst.greedy(prog));

}



} // namespace re2
