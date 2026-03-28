#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest_497 : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_497, SetPreCommentIndent_ValidValue_ReturnsTrue_497) {

    EXPECT_TRUE(emitterState.SetPreCommentIndent(10, FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_497, SetPreCommentIndent_ZeroValue_ReturnsFalse_497) {

    EXPECT_FALSE(emitterState.SetPreCommentIndent(0, FmtScope::LOCAL));

}



TEST_F(EmitterStateTest_497, SetPreCommentIndent_GlobalScope_ReturnsTrue_497) {

    EXPECT_TRUE(emitterState.SetPreCommentIndent(5, FmtScope::GLOBAL));

}



TEST_F(EmitterStateTest_497, SetPreCommentIndent_MaxSize_ReturnsTrue_497) {

    EXPECT_TRUE(emitterState.SetPreCommentIndent(std::numeric_limits<std::size_t>::max(), FmtScope::LOCAL));

}
