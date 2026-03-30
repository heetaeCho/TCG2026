#include <gtest/gtest.h>

#include "regex_yaml.h"



using namespace YAML;



class RegExTest_159 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(RegExTest_159, OperatorAnd_NormalOperation_159) {

    RegEx ex1('a');

    RegEx ex2('b');

    RegEx result = ex1 & ex2;



    EXPECT_EQ(result.m_op, REGEX_AND);

    EXPECT_EQ(result.m_params.size(), 2);

    EXPECT_EQ(result.m_params[0].m_a, 'a');

    EXPECT_EQ(result.m_params[1].m_a, 'b');

}



TEST_F(RegExTest_159, OperatorAnd_BoundaryCondition_EmptyParams_159) {

    RegEx ex1;

    RegEx ex2('b');

    RegEx result = ex1 & ex2;



    EXPECT_EQ(result.m_op, REGEX_AND);

    EXPECT_EQ(result.m_params.size(), 2);

    EXPECT_EQ(result.m_params[0].m_op, REGEX_EMPTY);

    EXPECT_EQ(result.m_params[1].m_a, 'b');

}



TEST_F(RegExTest_159, Matches_Char_NormalOperation_159) {

    RegEx ex('a');

    bool matches = ex.Matches('a');



    EXPECT_TRUE(matches);

}



TEST_F(RegExTest_159, Matches_String_NormalOperation_159) {

    RegEx ex("abc", REGEX_SEQ);

    bool matches = ex.Matches("abc");



    EXPECT_TRUE(matches);

}



TEST_F(RegExTest_159, Matches_Char_BoundaryCondition_EmptyString_159) {

    RegEx ex;

    bool matches = ex.Matches('\0');



    EXPECT_FALSE(matches);

}



TEST_F(RegExTest_159, Match_String_NormalOperation_159) {

    RegEx ex("abc", REGEX_SEQ);

    int matchPos = ex.Match("abc");



    EXPECT_EQ(matchPos, 3);

}



TEST_F(RegExTest_159, Match_String_BoundaryCondition_EmptyString_159) {

    RegEx ex;

    int matchPos = ex.Match("");



    EXPECT_EQ(matchPos, 0);

}
