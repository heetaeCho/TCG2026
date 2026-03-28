#include <gtest/gtest.h>

#include "regex_yaml.h"



using namespace YAML;



class RegExTest_158 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RegExTest_158, OperatorOrNormalOperation_158) {

    RegEx ex1('a');

    RegEx ex2('b');

    RegEx result = ex1 | ex2;

    

    EXPECT_TRUE(result.Matches('a'));

    EXPECT_TRUE(result.Matches('b'));

    EXPECT_FALSE(result.Matches('c'));

}



TEST_F(RegExTest_158, OperatorOrBoundaryConditions_158) {

    RegEx ex1('a');

    RegEx ex2('\0'); // Null character

    RegEx result = ex1 | ex2;

    

    EXPECT_TRUE(result.Matches('a'));

    EXPECT_TRUE(result.Matches('\0'));

    EXPECT_FALSE(result.Matches('b'));

}



TEST_F(RegExTest_158, OperatorOrExceptionalCases_158) {

    // Assuming Matches does not throw exceptions for invalid characters

    RegEx ex1('a');

    RegEx ex2(128); // Invalid ASCII character

    RegEx result = ex1 | ex2;

    

    EXPECT_TRUE(result.Matches('a'));

    EXPECT_FALSE(result.Matches(static_cast<char>(128)));

}



TEST_F(RegExTest_158, OperatorOrEmptyStringMatch_158) {

    RegEx emptyRegex("");

    RegEx anyChar('.');

    RegEx result = emptyRegex | anyChar;



    EXPECT_TRUE(result.Matches('a'));

    EXPECT_TRUE(result.Matches('\0')); // Assuming empty regex matches everything or nothing

}



TEST_F(RegExTest_158, OperatorOrSameCharacterMatch_158) {

    RegEx ex1('x');

    RegEx ex2('x');

    RegEx result = ex1 | ex2;



    EXPECT_TRUE(result.Matches('x'));

    EXPECT_FALSE(result.Matches('y'));

}



TEST_F(RegExTest_158, OperatorOrComplexExpression_158) {

    RegEx ex1("abc", REGEX_SEQ);

    RegEx ex2("def", REGEX_SEQ);

    RegEx result = ex1 | ex2;



    EXPECT_TRUE(result.Matches("abc"));

    EXPECT_TRUE(result.Matches("def"));

    EXPECT_FALSE(result.Matches("abcd"));

}
