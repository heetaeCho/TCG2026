#include <gtest/gtest.h>

#include "regex_yaml.h"



using namespace YAML;



class RegExTest_157 : public ::testing::Test {

protected:

    virtual void SetUp() {}

    virtual void TearDown() {}

};



TEST_F(RegExTest_157, OperatorNotNormalOperation_157) {

    RegEx ex('a');

    RegEx result = !ex;

    

    EXPECT_EQ(result.m_params.size(), 1);

    EXPECT_EQ(result.m_op, REGEX_NOT);

    EXPECT_EQ(result.m_params[0].m_a, 'a');

}



TEST_F(RegExTest_157, OperatorNotBoundaryConditionEmptyRegex_157) {

    RegEx ex;

    RegEx result = !ex;

    

    EXPECT_EQ(result.m_params.size(), 1);

    EXPECT_EQ(result.m_op, REGEX_NOT);

    EXPECT_EQ(result.m_params[0].m_op, REGEX_EMPTY);

}



TEST_F(RegExTest_157, OperatorNotBoundaryConditionRangeRegex_157) {

    RegEx ex('a', 'z');

    RegEx result = !ex;

    

    EXPECT_EQ(result.m_params.size(), 1);

    EXPECT_EQ(result.m_op, REGEX_NOT);

    EXPECT_EQ(result.m_params[0].m_a, 'a');

    EXPECT_EQ(result.m_params[0].m_z, 'z');

}



TEST_F(RegExTest_157, OperatorNotBoundaryConditionComplexRegex_157) {

    RegEx ex1('a'), ex2('b');

    RegEx or_ex = ex1 | ex2;

    RegEx result = !or_ex;

    

    EXPECT_EQ(result.m_params.size(), 1);

    EXPECT_EQ(result.m_op, REGEX_NOT);

    EXPECT_EQ(result.m_params[0].m_op, REGEX_OR);

    EXPECT_EQ(result.m_params[0].m_params.size(), 2);

}



TEST_F(RegExTest_157, OperatorNotMatchesMethod_157) {

    RegEx ex('a');

    RegEx not_ex = !ex;

    

    EXPECT_TRUE(not_ex.Matches('b'));

    EXPECT_FALSE(not_ex.Matches('a'));

}
