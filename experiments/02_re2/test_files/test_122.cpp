#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgTest_122 : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_122, DefaultDfaMemIsZero_122) {

    EXPECT_EQ(prog.dfa_mem(), 0);

}



TEST_F(ProgTest_122, SetDfaMemAndGetReturnsSameValue_122) {

    int64_t test_value = 1024;

    prog.set_dfa_mem(test_value);

    EXPECT_EQ(prog.dfa_mem(), test_value);

}



TEST_F(ProgTest_122, BoundaryConditionForDfaMem_122) {

    prog.set_dfa_mem(std::numeric_limits<int64_t>::max());

    EXPECT_EQ(prog.dfa_mem(), std::numeric_limits<int64_t>::max());



    prog.set_dfa_mem(std::numeric_limits<int64_t>::min());

    EXPECT_EQ(prog.dfa_mem(), std::numeric_limits<int64_t>::min());

}



TEST_F(ProgTest_122, DefaultAnchorStartIsFalse_122) {

    EXPECT_FALSE(prog.anchor_start());

}



TEST_F(ProgTest_122, SetAnchorStartAndGetReturnsSameValue_122) {

    prog.set_anchor_start(true);

    EXPECT_TRUE(prog.anchor_start());



    prog.set_anchor_start(false);

    EXPECT_FALSE(prog.anchor_start());

}



TEST_F(ProgTest_122, DefaultAnchorEndIsFalse_122) {

    EXPECT_FALSE(prog.anchor_end());

}



TEST_F(ProgTest_122, SetAnchorEndAndGetReturnsSameValue_122) {

    prog.set_anchor_end(true);

    EXPECT_TRUE(prog.anchor_end());



    prog.set_anchor_end(false);

    EXPECT_FALSE(prog.anchor_end());

}



TEST_F(ProgTest_122, DefaultReversedIsFalse_122) {

    EXPECT_FALSE(prog.reversed());

}



TEST_F(ProgTest_122, SetReversedAndGetReturnsSameValue_122) {

    prog.set_reversed(true);

    EXPECT_TRUE(prog.reversed());



    prog.set_reversed(false);

    EXPECT_FALSE(prog.reversed());

}



TEST_F(ProgTest_122, DefaultStartIsZero_122) {

    EXPECT_EQ(prog.start(), 0);

}



TEST_F(ProgTest_122, SetStartAndGetReturnsSameValue_122) {

    int test_value = 5;

    prog.set_start(test_value);

    EXPECT_EQ(prog.start(), test_value);



    prog.set_start(-1); // Testing negative value

    EXPECT_EQ(prog.start(), -1);

}



TEST_F(ProgTest_122, DefaultStartUnanchoredIsZero_122) {

    EXPECT_EQ(prog.start_unanchored(), 0);

}



TEST_F(ProgTest_122, SetStartUnanchoredAndGetReturnsSameValue_122) {

    int test_value = 5;

    prog.set_start_unanchored(test_value);

    EXPECT_EQ(prog.start_unanchored(), test_value);



    prog.set_start_unanchored(-1); // Testing negative value

    EXPECT_EQ(prog.start_unanchored(), -1);

}
