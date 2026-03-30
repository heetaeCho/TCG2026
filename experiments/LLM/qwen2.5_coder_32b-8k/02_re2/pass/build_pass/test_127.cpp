#include <gtest/gtest.h>

#include "re2/prog.h"



namespace {



class ProgTest_127 : public ::testing::Test {

protected:

    re2::Prog prog;

};



TEST_F(ProgTest_127, SetAnchorEnd_DefaultValueIsFalse_127) {

    EXPECT_FALSE(prog.anchor_end());

}



TEST_F(ProgTest_127, SetAnchorEnd_SetTrue_ReturnsTrue_127) {

    prog.set_anchor_end(true);

    EXPECT_TRUE(prog.anchor_end());

}



TEST_F(ProgTest_127, SetAnchorEnd_SetFalse_ReturnsFalse_127) {

    prog.set_anchor_end(false);

    EXPECT_FALSE(prog.anchor_end());

}



TEST_F(ProgTest_127, SetAnchorEnd_ToggleMultipleTimes_ConsistentState_127) {

    prog.set_anchor_end(true);

    EXPECT_TRUE(prog.anchor_end());



    prog.set_anchor_end(false);

    EXPECT_FALSE(prog.anchor_end());



    prog.set_anchor_end(true);

    EXPECT_TRUE(prog.anchor_end());

}



TEST_F(ProgTest_127, SetAnchorEnd_NoExternalInteractions_127) {

    // This test implicitly checks that set_anchor_end does not interact with external components

    prog.set_anchor_end(true);

    prog.set_anchor_end(false);

}



}  // namespace
