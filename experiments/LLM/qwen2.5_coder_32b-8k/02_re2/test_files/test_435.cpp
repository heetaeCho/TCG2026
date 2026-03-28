#include <gtest/gtest.h>

#include "dfa.h"



namespace re2 {



class DFAStateTest_435 : public ::testing::Test {

protected:

    DFA::State state;

};



TEST_F(DFAStateTest_435, IsMatch_ReturnsFalse_WhenFlagIsZero_435) {

    state.flag_ = 0;

    EXPECT_FALSE(state.IsMatch());

}



TEST_F(DFAStateTest_435, IsMatch_ReturnsTrue_WhenFlagHasMatchBitSet_435) {

    state.flag_ = DFA::kFlagMatch;

    EXPECT_TRUE(state.IsMatch());

}



TEST_F(DFAStateTest_435, IsMatch_ReturnsFalse_WhenFlagHasOtherBitsSetButNotMatch_435) {

    state.flag_ = 0xFF ^ DFA::kFlagMatch; // All bits set except match bit

    EXPECT_FALSE(state.IsMatch());

}



} // namespace re2

```


