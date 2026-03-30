#include <gtest/gtest.h>

#include "re2/prog.h"



class ProgTest_118 : public ::testing::Test {

protected:

    re2::Prog prog;

};



TEST_F(ProgTest_118, SetReversed_DefaultValueIsFalse_118) {

    EXPECT_FALSE(prog.reversed());

}



TEST_F(ProgTest_118, SetReversed_ValueCanBeSetToTrue_118) {

    prog.set_reversed(true);

    EXPECT_TRUE(prog.reversed());

}



TEST_F(ProgTest_118, SetReversed_ValueCanBeSetToFalse_118) {

    prog.set_reversed(false);

    EXPECT_FALSE(prog.reversed());

}



TEST_F(ProgTest_118, SetReversed_ToggleBetweenTrueAndFalse_118) {

    prog.set_reversed(true);

    EXPECT_TRUE(prog.reversed());

    prog.set_reversed(false);

    EXPECT_FALSE(prog.reversed());

}
