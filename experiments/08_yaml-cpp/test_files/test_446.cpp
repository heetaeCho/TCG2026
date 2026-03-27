#include <gtest/gtest.h>

#include "emitterstate.h"



using namespace YAML;



class EmitterStateTest : public ::testing::Test {

protected:

    EmitterState emitterState;

};



TEST_F(EmitterStateTest_446, InitialStateIsGood_446) {

    EXPECT_TRUE(emitterState.good());

}



TEST_F(EmitterStateTest_446, SetErrorChangesStateToNotGood_446) {

    emitterState.SetError("test error");

    EXPECT_FALSE(emitterState.good());

}



TEST_F(EmitterStateTest_446, GetLastErrorReturnsSetError_446) {

    const std::string testError = "test error";

    emitterState.SetError(testError);

    EXPECT_EQ(emitterState.GetLastError(), testError);

}



TEST_F(EmitterStateTest_446, GetLastErrorReturnsEmptyStringInitially_446) {

    EXPECT_TRUE(emitterState.GetLastError().empty());

}
