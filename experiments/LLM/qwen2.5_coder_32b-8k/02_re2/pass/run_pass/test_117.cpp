#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class ProgTest_117 : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_117, ReversedInitialValue_117) {

    EXPECT_FALSE(prog.reversed());

}



TEST_F(ProgTest_117, SetReversedTrue_117) {

    prog.set_reversed(true);

    EXPECT_TRUE(prog.reversed());

}



TEST_F(ProgTest_117, SetReversedFalse_117) {

    prog.set_reversed(false);

    EXPECT_FALSE(prog.reversed());

}
