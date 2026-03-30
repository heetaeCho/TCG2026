#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgTest_125 : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_125, SetAnchorStart_DefaultValue_125) {

    EXPECT_FALSE(prog.anchor_start());

}



TEST_F(ProgTest_125, SetAnchorStart_SetTrue_125) {

    prog.set_anchor_start(true);

    EXPECT_TRUE(prog.anchor_start());

}



TEST_F(ProgTest_125, SetAnchorStart_SetFalse_125) {

    prog.set_anchor_start(false);

    EXPECT_FALSE(prog.anchor_start());

}



TEST_F(ProgTest_125, SetAnchorStart_ToggleMultipleTimes_125) {

    prog.set_anchor_start(true);

    EXPECT_TRUE(prog.anchor_start());



    prog.set_anchor_start(false);

    EXPECT_FALSE(prog.anchor_start());



    prog.set_anchor_start(true);

    EXPECT_TRUE(prog.anchor_start());

}
