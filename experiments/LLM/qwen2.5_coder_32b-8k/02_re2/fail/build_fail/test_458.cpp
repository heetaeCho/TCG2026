#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"



using ::testing::_;

using ::testing::Return;



class ProgTest : public ::testing::Test {

protected:

    re2::Prog prog;

};



TEST_F(ProgTest_458, PossibleMatchRange_ReturnsTrueForValidInput_458) {

    std::string min = "";

    std::string max = "";

    int maxlen = 10;



    EXPECT_CALL(prog.GetDFA(re2::Prog::kLongestMatch), PossibleMatchRange(_, _, _))

        .WillOnce(Return(true));



    bool result = prog.PossibleMatchRange(&min, &max, maxlen);

    EXPECT_TRUE(result);

}



TEST_F(ProgTest_458, PossibleMatchRange_ReturnsFalseForInvalidInput_458) {

    std::string min = "";

    std::string max = "";

    int maxlen = 10;



    EXPECT_CALL(prog.GetDFA(re2::Prog::kLongestMatch), PossibleMatchRange(_, _, _))

        .WillOnce(Return(false));



    bool result = prog.PossibleMatchRange(&min, &max, maxlen);

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_458, PossibleMatchRange_HandlesBoundaryConditions_458) {

    std::string min = "";

    std::string max = "";

    int maxlen = 0;



    EXPECT_CALL(prog.GetDFA(re2::Prog::kLongestMatch), PossibleMatchRange(_, _, _))

        .WillOnce(Return(false));



    bool result = prog.PossibleMatchRange(&min, &max, maxlen);

    EXPECT_FALSE(result);



    maxlen = -1;

    EXPECT_CALL(prog.GetDFA(re2::Prog::kLongestMatch), PossibleMatchRange(_, _, _))

        .WillOnce(Return(false));



    result = prog.PossibleMatchRange(&min, &max, maxlen);

    EXPECT_FALSE(result);

}
