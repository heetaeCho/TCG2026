#include <gtest/gtest.h>

#include "eval_env.h"

#include <string>



using namespace std;



class EvalStringTest_19 : public ::testing::Test {

protected:

    EvalString eval_string;

};



TEST_F(EvalStringTest_19, ClearRemovesContent_19) {

    eval_string.AddText("test");

    ASSERT_FALSE(eval_string.empty());

    eval_string.Clear();

    EXPECT_TRUE(eval_string.empty());

}



TEST_F(EvalStringTest_19, AddTextIncreasesSize_19) {

    eval_string.AddText("test");

    EXPECT_FALSE(eval_string.empty());

}



TEST_F(EvalStringTest_19, AddSpecialIncreasesSize_19) {

    eval_string.AddSpecial("special");

    EXPECT_FALSE(eval_string.empty());

}



TEST_F(EvalStringTest_19, EmptyInitially_19) {

    EXPECT_TRUE(eval_string.empty());

}



TEST_F(EvalStringTest_19, UnparseReturnsEmptyString_19) {

    EXPECT_EQ("", eval_string.Unparse());

}



TEST_F(EvalStringTest_19, SerializeReturnsEmptyString_19) {

    EXPECT_EQ("", eval_string.Serialize());

}
