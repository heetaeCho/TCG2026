#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_447 : public ::testing::Test {

protected:

    EmitterState emitter_state;

};



TEST_F(EmitterStateTest_447, CurIndent_DefaultValue_447) {

    EXPECT_EQ(emitter_state.CurIndent(), 0);

}



TEST_F(EmitterStateTest_447, SetIndent_ValidValue_447) {

    ASSERT_TRUE(emitter_state.SetIndent(2, FmtScope::value::LOCAL));

    EXPECT_EQ(emitter_state.CurIndent(), 2);

}



TEST_F(EmitterStateTest_447, SetIndent_ZeroValue_447) {

    ASSERT_TRUE(emitter_state.SetIndent(0, FmtScope::value::LOCAL));

    EXPECT_EQ(emitter_state.CurIndent(), 0);

}



TEST_F(EmitterStateTest_447, SetIndent_LargeValue_447) {

    ASSERT_TRUE(emitter_state.SetIndent(1024, FmtScope::value::LOCAL));

    EXPECT_EQ(emitter_state.CurIndent(), 1024);

}



TEST_F(EmitterStateTest_447, SetIndent_NegativeValue_447) {

    // Assuming negative values are not allowed and should return false

    EXPECT_FALSE(emitter_state.SetIndent(-1, FmtScope::value::LOCAL));

    EXPECT_EQ(emitter_state.CurIndent(), 0);

}



TEST_F(EmitterStateTest_447, SetIndent_OutOfRangeValue_447) {

    // Assuming there is an upper limit for indentation

    EXPECT_FALSE(emitter_state.SetIndent(1000000, FmtScope::value::LOCAL));

    EXPECT_EQ(emitter_state.CurIndent(), 0);

}



TEST_F(EmitterStateTest_447, SetIndent_GlobalScope_447) {

    ASSERT_TRUE(emitter_state.SetIndent(4, FmtScope::value::GLOBAL));

    EXPECT_EQ(emitter_state.CurIndent(), 4);



    EmitterState another_emitter_state;

    EXPECT_EQ(another_emitter_state.CurIndent(), 4);

}



TEST_F(EmitterStateTest_447, Good_DefaultValue_447) {

    EXPECT_TRUE(emitter_state.good());

}



TEST_F(EmitterStateTest_447, SetError_ChangesGoodStatus_447) {

    emitter_state.SetError("An error occurred");

    EXPECT_FALSE(emitter_state.good());

    EXPECT_EQ(emitter_state.GetLastError(), "An error occurred");

}



TEST_F(EmitterStateTest_447, GetLastError_DefaultValue_447) {

    EXPECT_TRUE(emitter_state.GetLastError().empty());

}
