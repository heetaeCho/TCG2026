#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_460 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_460, DefaultIndentIsZero_460) {

    EXPECT_EQ(emitter_state.GetIndent(), 0);

}



TEST_F(EmitterStateTest_460, SetIndentAndGetIndent_460) {

    EXPECT_TRUE(emitter_state.SetIndent(4, FmtScope::value::LOCAL));

    EXPECT_EQ(emitter_state.GetIndent(), 4);

}



TEST_F(EmitterStateTest_460, SetIndentToZero_460) {

    emitter_state.SetIndent(4, FmtScope::value::LOCAL);

    EXPECT_TRUE(emitter_state.SetIndent(0, FmtScope::value::LOCAL));

    EXPECT_EQ(emitter_state.GetIndent(), 0);

}



TEST_F(EmitterStateTest_460, SetInvalidIndentFails_460) {

    // Assuming invalid indent is negative (though size_t cannot be negative)

    // This test will check if setting an out-of-range value fails.

    EXPECT_FALSE(emitter_state.SetIndent(static_cast<std::size_t>(-1), FmtScope::value::LOCAL));

}



TEST_F(EmitterStateTest_460, GetIndentAfterResettingSettings_460) {

    emitter_state.SetIndent(4, FmtScope::value::LOCAL);

    emitter_state.ClearModifiedSettings();

    EXPECT_EQ(emitter_state.GetIndent(), 0);

}
