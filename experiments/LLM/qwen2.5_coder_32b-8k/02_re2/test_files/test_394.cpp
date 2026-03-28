#include <gtest/gtest.h>

#include "re2/prog.h"



namespace re2 {



class ProgInstTest_394 : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_394, InitMatch_SetsOpcodeToMatch_394) {

    int test_id = 10;

    inst.InitMatch(test_id);

    EXPECT_EQ(inst.opcode(), kInstMatch);

}



TEST_F(ProgInstTest_394, InitMatch_SetsMatchIdCorrectly_394) {

    int test_id = 20;

    inst.InitMatch(test_id);

    EXPECT_EQ(inst.match_id(), test_id);

}



TEST_F(ProgInstTest_394, InitMatch_DoesNotAffectOtherFields_394) {

    int test_id = 30;

    inst.InitByteRange(1, 2, 3, 4);

    inst.InitMatch(test_id);



    EXPECT_EQ(inst.opcode(), kInstMatch);

    EXPECT_EQ(inst.match_id(), test_id);

    // Assuming other fields should not be affected by InitMatch

    // This assumes that InitByteRange sets some fields we can check.

    EXPECT_NE(inst.lo(), 0); 

    EXPECT_NE(inst.hi(), 0);

    EXPECT_NE(inst.foldcase(), 0);

    EXPECT_NE(inst.out(), 0);

}



TEST_F(ProgInstTest_394, MatchId_ReturnsInitializedValue_394) {

    int test_id = 40;

    inst.InitMatch(test_id);

    EXPECT_EQ(inst.match_id(), test_id);

}



TEST_F(ProgInstTest_394, Opcode_ReturnsCorrectValueAfterInitMatch_394) {

    inst.InitMatch(50);

    EXPECT_EQ(inst.opcode(), kInstMatch);

}



} // namespace re2
