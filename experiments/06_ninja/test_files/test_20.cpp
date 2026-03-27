#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "eval_env.h"



class EvalStringTest_20 : public ::testing::Test {

protected:

    EvalString eval_string;

};



TEST_F(EvalStringTest_20, Empty_ReturnsTrueForDefaultConstructed_20) {

    EXPECT_TRUE(eval_string.empty());

}



TEST_F(EvalStringTest_20, AddText_MakesNotEmpty_20) {

    eval_string.AddText("some text");

    EXPECT_FALSE(eval_string.empty());

}



TEST_F(EvalStringTest_20, AddSpecial_MakesNotEmpty_20) {

    eval_string.AddSpecial("special text");

    EXPECT_FALSE(eval_string.empty());

}



TEST_F(EvalStringTest_20, Clear_ReturnsEmptyAfterAddingText_20) {

    eval_string.AddText("some text");

    eval_string.Clear();

    EXPECT_TRUE(eval_string.empty());

}



TEST_F(EvalStringTest_20, Clear_ReturnsEmptyAfterAddingSpecial_20) {

    eval_string.AddSpecial("special text");

    eval_string.Clear();

    EXPECT_TRUE(eval_string.empty());

}
