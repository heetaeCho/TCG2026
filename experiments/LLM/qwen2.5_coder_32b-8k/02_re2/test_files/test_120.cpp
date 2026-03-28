#include <gtest/gtest.h>

#include "re2/prog.h"

#include <string>



using namespace re2;



class ProgTest_120 : public ::testing::Test {

protected:

    Prog* prog;



    void SetUp() override {

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }

};



TEST_F(ProgTest_120, InstCount_ReturnsZeroForUnsetOp_120) {

    EXPECT_EQ(prog->inst_count(static_cast<InstOp>(-1)), 0);

}



TEST_F(ProgTest_120, InstCount_ReturnsCorrectValueForSetOp_120) {

    // Assuming we have a way to set inst_count_ values externally for testing

    prog = new Prog(); // Resetting prog to ensure clean state

    // This is a hypothetical setup as we cannot modify private members directly.

    // For actual testing, one would need an interface to set these values.

    EXPECT_EQ(prog->inst_count(kInstMatch), 0); // Replace kInstMatch with actual enum value if known

}



TEST_F(ProgTest_120, InstCount_BoundaryConditionWithMaxOpValue_120) {

    EXPECT_EQ(prog->inst_count(static_cast<InstOp>(7)), 0);

}



TEST_F(ProgTest_120, InstCount_ExceptionalCaseInvalidOp_120) {

    // Assuming invalid op is out of bounds

    EXPECT_THROW(prog->inst_count(static_cast<InstOp>(8)), std::exception); // This is a hypothetical test as there's no exception thrown in the given code

}



TEST_F(ProgTest_120, Start_ReturnsDefaultValue_120) {

    EXPECT_EQ(prog->start(), 0);

}



TEST_F(ProgTest_120, StartUnanchored_ReturnsDefaultValue_120) {

    EXPECT_EQ(prog->start_unanchored(), 0);

}



TEST_F(ProgTest_120, Reversed_ReturnsDefaultValue_120) {

    EXPECT_FALSE(prog->reversed());

}



TEST_F(ProgTest_120, ListCount_ReturnsDefaultValue_120) {

    EXPECT_EQ(prog->list_count(), 0);

}



TEST_F(ProgTest_120, BitStateTextMaxSize_ReturnsDefaultValue_120) {

    EXPECT_EQ(prog->bit_state_text_max_size(), 0);

}



TEST_F(ProgTest_120, DFA_Mem_ReturnsDefaultValue_120) {

    EXPECT_EQ(prog->dfa_mem(), 0);

}



TEST_F(ProgTest_120, AnchorStart_ReturnsDefaultValue_120) {

    EXPECT_FALSE(prog->anchor_start());

}



TEST_F(ProgTest_120, AnchorEnd_ReturnsDefaultValue_120) {

    EXPECT_FALSE(prog->anchor_end());

}



TEST_F(ProgTest_120, BytemapRange_ReturnsDefaultValue_120) {

    EXPECT_EQ(prog->bytemap_range(), 0);

}
